/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include <algorithm>
#include <ostream>
#include <random>
#include <stdexcept>

#include <gtest/gtest.h>

#include "fbgemm/Fbgemm.h"
#include "fbgemm/Utils.h"
#include "src/RefImplementations.h"

using namespace std;
using namespace fbgemm;

static vector<vector<int>> GetInputs_() {
  vector<vector<int>> input_dims = {
      // num_rows, block_size
      {1500, 1},
      {1500, 4},
      {10, 8},
      {1500, 16},
      {1, 8},
      {1, 16},
      {1500, 24},
      {1500, 32},
      {1500, 40},
      {1500, 64},
      {1500, 80},
      {1500, 128},
      {1500, 384},
  };
  return input_dims;
}

vector<int> prefetch_distances{0, 16, 1000000};

namespace {
class SparseAdagradTest
    : public testing::TestWithParam<tuple<bool, int, bool, bool>> {};
}; // namespace

// Test:
// 64 bit indices
// prefetch distances
// out of bounds indices
// null indices
INSTANTIATE_TEST_CASE_P(
    InstantiationName,
    SparseAdagradTest,
    ::testing::Combine(
        ::testing::Bool(),
        ::testing::ValuesIn(prefetch_distances),
        ::testing::Bool(),
        ::testing::Bool()));

TEST_P(SparseAdagradTest, basicTest) {
  vector<vector<int>> inputs(GetInputs_());
  bool isIndex64b, out_of_bounds, empty_indices;
  int prefetch;
  tie(isIndex64b, prefetch, out_of_bounds, empty_indices) = GetParam();
  empty_indices = false;

  for (auto input : inputs) {
    int num_rows = input[0];
    int block_size = input[1];
    int param_size = num_rows * block_size;

    vector<float> g(param_size); // gradients

    vector<float> h(param_size); // input momentums
    vector<float> w(param_size); // input params
    vector<float> h_ref(param_size);
    vector<float> w_ref(param_size);

    default_random_engine generator;

    normal_distribution<float> h_w_distribution;

    uniform_real_distribution<float> values_gen(0, 10);
    for (int i = 0; i < param_size; i++) {
      h_ref[i] = h[i] = values_gen(generator);
    }
    for (int i = 0; i < param_size; i++) {
      w_ref[i] = w[i] = values_gen(generator);
    }
    for (int i = 0; i < param_size; i++) {
      g[i] = values_gen(generator);
    }

    vector<std::int64_t> indices(num_rows);
    vector<std::int32_t> indices_32(num_rows);
    float epsilon = 1e-5;
    float lr = 0.5;

    uniform_int_distribution<std::int64_t> length_distribution(0, num_rows - 1);
    for (int i = 0; i < num_rows; ++i) {
      indices_32[i] = indices[i] = length_distribution(generator);
    }

    int ret_fbgemm, ret_ref;
    if (isIndex64b) {
      ret_ref = fbgemm::sparse_adagrad_ref(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w_ref.data(), // input parameters
          g.data(), // input gradients
          h_ref.data(), // input momentums
          indices.data(), // indices of each row
          epsilon,
          lr);

      ret_fbgemm = fbgemm::SparseAdaGrad(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w.data(), // input parameters
          g.data(), // input gradients
          h.data(), // input momentums
          indices.data(), // indices of each row
          epsilon,
          lr);
    } else { // 32 bit indices
      ret_ref = fbgemm::sparse_adagrad_ref(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w_ref.data(), // input parameters
          g.data(), // input gradients
          h_ref.data(), // input momentums
          indices_32.data(), // indices of each row
          epsilon,
          lr);

      ret_fbgemm = fbgemm::SparseAdaGrad(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w.data(), // input parameters
          g.data(), // input gradients
          h.data(), // input momentums
          indices_32.data(), // indices of each row
          epsilon,
          lr);
    }

    EXPECT_EQ(ret_fbgemm, ret_ref)
        << "return vals differ, reference is: " << ret_ref
        << " ,fbgemm is: " << ret_fbgemm;
    for (int i = 0; i < h.size(); ++i) {
      EXPECT_EQ(h[i], h_ref[i])
          << "results for h differ at (" << i << ") reference: " << h_ref[i]
          << ", FBGEMM: " << h[i] << " emb dim :" << block_size;
    }
    for (int i = 0; i < w.size(); ++i) {
      EXPECT_EQ(w[i], w_ref[i])
          << "results for h differ at (" << i << ") reference: " << w_ref[i]
          << ", FBGEMM: " << w[i] << " emb dim :" << block_size;
    }
  }
}

TEST_P(SparseAdagradTest, rowwiseTest) {
  vector<vector<int>> inputs(GetInputs_());
  bool isIndex64b, out_of_bounds, empty_indices;
  int prefetch;
  tie(isIndex64b, prefetch, out_of_bounds, empty_indices) = GetParam();
  empty_indices = false;
  prefetch = 16;
  isIndex64b = true;

  for (auto input : inputs) {
    int num_rows = input[0];
    int block_size = input[1];
    int param_size = num_rows * block_size;

    vector<float> g(param_size); // gradients

    vector<float> h(param_size); // input momentums
    vector<float> w(param_size); // input params
    vector<float> h_ref(param_size);
    vector<float> w_ref(param_size);

    default_random_engine generator;
    uniform_real_distribution<float> values_gen(0, 2);
    for (int i = 0; i < param_size; i++) {
      h_ref[i] = h[i] = values_gen(generator);
    }
    for (int i = 0; i < param_size; i++) {
      w_ref[i] = w[i] = values_gen(generator);
    }
    for (int i = 0; i < param_size; i++) {
      g[i] = values_gen(generator);
    }

    vector<std::int64_t> indices(num_rows);
    vector<std::int32_t> indices_32(num_rows);
    float epsilon = 1e-5;
    float lr = 0.5;

    uniform_int_distribution<std::int64_t> length_distribution(
        0, 2 * num_rows - 1);
    for (int i = 0; i < num_rows; ++i) {
      indices[i] = length_distribution(generator);
    }
    copy(begin(indices), end(indices), back_inserter(indices_32));

    int ret_fbgemm, ret_ref;
    if (isIndex64b) {
      ret_ref = fbgemm::rowwise_sparse_adagrad_ref(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w_ref.data(), // input parameters
          g.data(), // input gradients
          h_ref.data(), // input momentums
          indices.data(), // indices of each row
          epsilon,
          lr);

      ret_fbgemm = fbgemm::SparseAdaGrad(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w.data(), // input parameters
          g.data(), // input gradients
          h.data(), // input momentums
          indices.data(), // indices of each row
          epsilon,
          lr,
          true); // rowwise
    } else { // 32 bit indices
      ret_ref = fbgemm::rowwise_sparse_adagrad_ref(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w_ref.data(), // input parameters
          g.data(), // input gradients
          h_ref.data(), // input momentums
          indices_32.data(), // indices of each row
          epsilon,
          lr);

      ret_fbgemm = fbgemm::SparseAdaGrad(
          num_rows, // number of rows reading
          block_size, // number of parameters per rows
          param_size, // total number of parameters
          w.data(), // input parameters
          g.data(), // input gradients
          h.data(), // input momentums
          indices_32.data(), // indices of each row
          epsilon,
          lr,
          true); // rowwise
    }

    EXPECT_EQ(ret_fbgemm, ret_ref)
        << "return vals differ, reference is: " << ret_ref
        << " ,fbgemm is: " << ret_fbgemm;
    for (int i = 0; i < h.size(); ++i) {
      EXPECT_EQ(h[i], h_ref[i])
          << "results for h differ at (" << i << ") reference: " << h_ref[i]
          << ", FBGEMM: " << h[i] << " emb dim :" << block_size;
    }
    for (int i = 0; i < w.size(); ++i) {
      EXPECT_EQ(w[i], w_ref[i])
          << "results for w differ at (" << i << ") reference: " << w_ref[i]
          << ", FBGEMM: " << w[i] << " emb dim :" << block_size;
    }
  }
}
