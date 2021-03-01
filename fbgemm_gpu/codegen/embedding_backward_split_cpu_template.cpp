/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <map>
#include <tuple>

#include <ATen/ATen.h>

#include "codegen/embedding_forward_split_cpu.h"

using namespace at;

{{ "void" if not dense else "Tensor" }}  split_embedding_backward_codegen_{{ optimizer }}_exact_cpu(
    Tensor grad_output,
    Tensor host_weights,
    {% if not dense %}
    Tensor weights_placements,
    {% endif %}
    Tensor weights_offsets,
    Tensor D_offsets,
    int64_t max_D,
    Tensor hash_size_cumsum,
    int64_t total_hash_size_bits,
    Tensor indices,
    Tensor offsets,
    int64_t pooling_mode,
    Tensor indice_weights,
    {% if not dense %}
    bool stochastic_rounding,
    {% endif %}
    {{ args.split_function_args | join(", ") }}
) {
  int64_t T = D_offsets.numel() - 1;
  TORCH_CHECK(T > 0);
  // offsets = [T x B  + 1]
  int64_t B = (offsets.size(0) - 1) / T;
  TORCH_CHECK(B > 0);

  const auto D_offsets_data = D_offsets.accessor<int, 1>();
  const auto weights_offsets_data = weights_offsets.accessor<int64_t, 1>();
  const auto offsets_data = offsets.accessor<int64_t, 1>();
  const auto indices_data = indices.accessor<int64_t, 1>();
  {% if "momentum1_offsets" in args.split_function_arg_names %}
  const auto momentum1_offsets_data = momentum1_offsets.accessor<int64_t, 1>();
  {% endif %}
  {% if "momentum2_offsets" in args.split_function_arg_names %}
  const auto momentum2_offsets_data = momentum2_offsets.accessor<int64_t, 1>();
  {% endif %}

  // Gradients are of type fp32, so weights should not have higher precision
  TORCH_CHECK(host_weights.element_size() <= 4);
  auto grad = zeros_like(host_weights, at::kFloat);

  TORCH_CHECK(host_weights.dim() == 1);
  auto grad_data = grad.accessor<float, 1>();

  // It is assumed that the indice_weights will be of type float
  if (indice_weights.defined())
    TORCH_CHECK(indice_weights.scalar_type() == at::kFloat);
  auto indice_weights_data = indice_weights.defined() ?
    // If indice_weights are not defined, then this accessor won't be used
    indice_weights.accessor<float, 1>()
    : grad.accessor<float, 1>(); // this is just to make compiler happy

  TORCH_CHECK(grad_output.scalar_type() == at::kFloat);
  auto grad_output_data = grad_output.accessor<float, 2>();

  for (int64_t t = 0; t < T; ++t) {
    const auto D_begin = D_offsets_data[t];
    const auto D = D_offsets_data[t + 1] - D_offsets_data[t];
    const auto table_begin = weights_offsets_data[t];
    for (int64_t b = 0; b < B; ++b) {
      const auto pool_begin = offsets_data[t * B + b];
      const auto pool_end = offsets_data[t * B + b + 1];
      const auto L = pool_end - pool_begin;
      const double scale_factor =
          // NOTE: MEAN pooling will not work with indice_weights!
          (pooling_mode == MEAN && !indice_weights.defined() && L > 0) ? 1.0 / L
                                                                       : 1.0;
      for (auto p = pool_begin; p < pool_end; ++p) {
        const int64_t embedding_begin = table_begin + indices_data[p] * D;
        for (int64_t d = 0; d < D; ++d) {
          grad_data[embedding_begin + d] += scale_factor *
              (indice_weights.defined()
                   ? grad_output_data[b][D_begin + d] * indice_weights_data[p]
                   : grad_output_data[b][D_begin + d]);
        }
      }
    }
  }

  {{ split_weight_update_cpu }}

  return {{ "grad" if dense else "" }};
}
