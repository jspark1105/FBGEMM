/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "FbgemmFP16UKernelsAvx512_256.h"

namespace fbgemm {

void __attribute__((noinline)) gemmkernel_7x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm15,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm16,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm14,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm15,ymm14\t\n"
      "vfmadd231ps ymm1,ymm16,ymm14\t\n"
      "vbroadcastss ymm14,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm15,ymm14\t\n"
      "vfmadd231ps ymm3,ymm16,ymm14\t\n"
      "vbroadcastss ymm14,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm15,ymm14\t\n"
      "vfmadd231ps ymm5,ymm16,ymm14\t\n"
      "vbroadcastss ymm14,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm15,ymm14\t\n"
      "vfmadd231ps ymm7,ymm16,ymm14\t\n"
      "vbroadcastss ymm14,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm15,ymm14\t\n"
      "vfmadd231ps ymm9,ymm16,ymm14\t\n"
      "vbroadcastss ymm14,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm15,ymm14\t\n"
      "vfmadd231ps ymm11,ymm16,ymm14\t\n"
      "vbroadcastss ymm14,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm15,ymm14\t\n"
      "vfmadd231ps ymm13,ymm16,ymm14\t\n"
      "add r9,28\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}
void __attribute__((noinline)) gemmkernel_8x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"
      "vxorps ymm14,ymm14,ymm14\t\n"
      "vxorps ymm15,ymm15,ymm15\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm17,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm18,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm17,ymm16\t\n"
      "vfmadd231ps ymm1,ymm18,ymm16\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm17,ymm16\t\n"
      "vfmadd231ps ymm3,ymm18,ymm16\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm17,ymm16\t\n"
      "vfmadd231ps ymm5,ymm18,ymm16\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm17,ymm16\t\n"
      "vfmadd231ps ymm7,ymm18,ymm16\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm17,ymm16\t\n"
      "vfmadd231ps ymm9,ymm18,ymm16\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm17,ymm16\t\n"
      "vfmadd231ps ymm11,ymm18,ymm16\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm17,ymm16\t\n"
      "vfmadd231ps ymm13,ymm18,ymm16\t\n"
      "vbroadcastss ymm16,DWORD PTR [r9+28]\t\n"
      "vfmadd231ps ymm14,ymm17,ymm16\t\n"
      "vfmadd231ps ymm15,ymm18,ymm16\t\n"
      "add r9,32\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm14,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vfmadd231ps ymm15,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}
void __attribute__((noinline)) gemmkernel_9x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"
      "vxorps ymm14,ymm14,ymm14\t\n"
      "vxorps ymm15,ymm15,ymm15\t\n"
      "vxorps ymm16,ymm16,ymm16\t\n"
      "vxorps ymm17,ymm17,ymm17\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm19,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm20,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm19,ymm18\t\n"
      "vfmadd231ps ymm1,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm19,ymm18\t\n"
      "vfmadd231ps ymm3,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm19,ymm18\t\n"
      "vfmadd231ps ymm5,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm19,ymm18\t\n"
      "vfmadd231ps ymm7,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm19,ymm18\t\n"
      "vfmadd231ps ymm9,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm19,ymm18\t\n"
      "vfmadd231ps ymm11,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm19,ymm18\t\n"
      "vfmadd231ps ymm13,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+28]\t\n"
      "vfmadd231ps ymm14,ymm19,ymm18\t\n"
      "vfmadd231ps ymm15,ymm20,ymm18\t\n"
      "vbroadcastss ymm18,DWORD PTR [r9+32]\t\n"
      "vfmadd231ps ymm16,ymm19,ymm18\t\n"
      "vfmadd231ps ymm17,ymm20,ymm18\t\n"
      "add r9,36\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm14,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vfmadd231ps ymm15,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm16,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vfmadd231ps ymm17,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}
void __attribute__((noinline)) gemmkernel_10x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"
      "vxorps ymm14,ymm14,ymm14\t\n"
      "vxorps ymm15,ymm15,ymm15\t\n"
      "vxorps ymm16,ymm16,ymm16\t\n"
      "vxorps ymm17,ymm17,ymm17\t\n"
      "vxorps ymm18,ymm18,ymm18\t\n"
      "vxorps ymm19,ymm19,ymm19\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm21,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm22,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm21,ymm20\t\n"
      "vfmadd231ps ymm1,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm21,ymm20\t\n"
      "vfmadd231ps ymm3,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm21,ymm20\t\n"
      "vfmadd231ps ymm5,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm21,ymm20\t\n"
      "vfmadd231ps ymm7,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm21,ymm20\t\n"
      "vfmadd231ps ymm9,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm21,ymm20\t\n"
      "vfmadd231ps ymm11,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm21,ymm20\t\n"
      "vfmadd231ps ymm13,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+28]\t\n"
      "vfmadd231ps ymm14,ymm21,ymm20\t\n"
      "vfmadd231ps ymm15,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+32]\t\n"
      "vfmadd231ps ymm16,ymm21,ymm20\t\n"
      "vfmadd231ps ymm17,ymm22,ymm20\t\n"
      "vbroadcastss ymm20,DWORD PTR [r9+36]\t\n"
      "vfmadd231ps ymm18,ymm21,ymm20\t\n"
      "vfmadd231ps ymm19,ymm22,ymm20\t\n"
      "add r9,40\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm14,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vfmadd231ps ymm15,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm16,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vfmadd231ps ymm17,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm18,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vfmadd231ps ymm19,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}
void __attribute__((noinline)) gemmkernel_11x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"
      "vxorps ymm14,ymm14,ymm14\t\n"
      "vxorps ymm15,ymm15,ymm15\t\n"
      "vxorps ymm16,ymm16,ymm16\t\n"
      "vxorps ymm17,ymm17,ymm17\t\n"
      "vxorps ymm18,ymm18,ymm18\t\n"
      "vxorps ymm19,ymm19,ymm19\t\n"
      "vxorps ymm20,ymm20,ymm20\t\n"
      "vxorps ymm21,ymm21,ymm21\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm23,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm24,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm23,ymm22\t\n"
      "vfmadd231ps ymm1,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm23,ymm22\t\n"
      "vfmadd231ps ymm3,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm23,ymm22\t\n"
      "vfmadd231ps ymm5,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm23,ymm22\t\n"
      "vfmadd231ps ymm7,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm23,ymm22\t\n"
      "vfmadd231ps ymm9,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm23,ymm22\t\n"
      "vfmadd231ps ymm11,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm23,ymm22\t\n"
      "vfmadd231ps ymm13,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+28]\t\n"
      "vfmadd231ps ymm14,ymm23,ymm22\t\n"
      "vfmadd231ps ymm15,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+32]\t\n"
      "vfmadd231ps ymm16,ymm23,ymm22\t\n"
      "vfmadd231ps ymm17,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+36]\t\n"
      "vfmadd231ps ymm18,ymm23,ymm22\t\n"
      "vfmadd231ps ymm19,ymm24,ymm22\t\n"
      "vbroadcastss ymm22,DWORD PTR [r9+40]\t\n"
      "vfmadd231ps ymm20,ymm23,ymm22\t\n"
      "vfmadd231ps ymm21,ymm24,ymm22\t\n"
      "add r9,44\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm14,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vfmadd231ps ymm15,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm16,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vfmadd231ps ymm17,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm18,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vfmadd231ps ymm19,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm20,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vfmadd231ps ymm21,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}
void __attribute__((noinline)) gemmkernel_12x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"
      "vxorps ymm14,ymm14,ymm14\t\n"
      "vxorps ymm15,ymm15,ymm15\t\n"
      "vxorps ymm16,ymm16,ymm16\t\n"
      "vxorps ymm17,ymm17,ymm17\t\n"
      "vxorps ymm18,ymm18,ymm18\t\n"
      "vxorps ymm19,ymm19,ymm19\t\n"
      "vxorps ymm20,ymm20,ymm20\t\n"
      "vxorps ymm21,ymm21,ymm21\t\n"
      "vxorps ymm22,ymm22,ymm22\t\n"
      "vxorps ymm23,ymm23,ymm23\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm25,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm26,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm25,ymm24\t\n"
      "vfmadd231ps ymm1,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm25,ymm24\t\n"
      "vfmadd231ps ymm3,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm25,ymm24\t\n"
      "vfmadd231ps ymm5,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm25,ymm24\t\n"
      "vfmadd231ps ymm7,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm25,ymm24\t\n"
      "vfmadd231ps ymm9,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm25,ymm24\t\n"
      "vfmadd231ps ymm11,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm25,ymm24\t\n"
      "vfmadd231ps ymm13,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+28]\t\n"
      "vfmadd231ps ymm14,ymm25,ymm24\t\n"
      "vfmadd231ps ymm15,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+32]\t\n"
      "vfmadd231ps ymm16,ymm25,ymm24\t\n"
      "vfmadd231ps ymm17,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+36]\t\n"
      "vfmadd231ps ymm18,ymm25,ymm24\t\n"
      "vfmadd231ps ymm19,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+40]\t\n"
      "vfmadd231ps ymm20,ymm25,ymm24\t\n"
      "vfmadd231ps ymm21,ymm26,ymm24\t\n"
      "vbroadcastss ymm24,DWORD PTR [r9+44]\t\n"
      "vfmadd231ps ymm22,ymm25,ymm24\t\n"
      "vfmadd231ps ymm23,ymm26,ymm24\t\n"
      "add r9,48\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm22\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm23\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm14,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vfmadd231ps ymm15,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm16,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vfmadd231ps ymm17,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm18,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vfmadd231ps ymm19,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm20,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vfmadd231ps ymm21,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm22,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm22\t\n"
      "vfmadd231ps ymm23,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm23\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}
void __attribute__((noinline)) gemmkernel_13x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"
      "vxorps ymm14,ymm14,ymm14\t\n"
      "vxorps ymm15,ymm15,ymm15\t\n"
      "vxorps ymm16,ymm16,ymm16\t\n"
      "vxorps ymm17,ymm17,ymm17\t\n"
      "vxorps ymm18,ymm18,ymm18\t\n"
      "vxorps ymm19,ymm19,ymm19\t\n"
      "vxorps ymm20,ymm20,ymm20\t\n"
      "vxorps ymm21,ymm21,ymm21\t\n"
      "vxorps ymm22,ymm22,ymm22\t\n"
      "vxorps ymm23,ymm23,ymm23\t\n"
      "vxorps ymm24,ymm24,ymm24\t\n"
      "vxorps ymm25,ymm25,ymm25\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm27,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm28,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm27,ymm26\t\n"
      "vfmadd231ps ymm1,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm27,ymm26\t\n"
      "vfmadd231ps ymm3,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm27,ymm26\t\n"
      "vfmadd231ps ymm5,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm27,ymm26\t\n"
      "vfmadd231ps ymm7,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm27,ymm26\t\n"
      "vfmadd231ps ymm9,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm27,ymm26\t\n"
      "vfmadd231ps ymm11,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm27,ymm26\t\n"
      "vfmadd231ps ymm13,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+28]\t\n"
      "vfmadd231ps ymm14,ymm27,ymm26\t\n"
      "vfmadd231ps ymm15,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+32]\t\n"
      "vfmadd231ps ymm16,ymm27,ymm26\t\n"
      "vfmadd231ps ymm17,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+36]\t\n"
      "vfmadd231ps ymm18,ymm27,ymm26\t\n"
      "vfmadd231ps ymm19,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+40]\t\n"
      "vfmadd231ps ymm20,ymm27,ymm26\t\n"
      "vfmadd231ps ymm21,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+44]\t\n"
      "vfmadd231ps ymm22,ymm27,ymm26\t\n"
      "vfmadd231ps ymm23,ymm28,ymm26\t\n"
      "vbroadcastss ymm26,DWORD PTR [r9+48]\t\n"
      "vfmadd231ps ymm24,ymm27,ymm26\t\n"
      "vfmadd231ps ymm25,ymm28,ymm26\t\n"
      "add r9,52\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm22\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm23\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm24\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm25\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm14,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vfmadd231ps ymm15,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm16,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vfmadd231ps ymm17,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm18,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vfmadd231ps ymm19,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm20,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vfmadd231ps ymm21,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm22,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm22\t\n"
      "vfmadd231ps ymm23,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm23\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm24,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm24\t\n"
      "vfmadd231ps ymm25,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm25\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}
void __attribute__((noinline)) gemmkernel_14x2_Avx512_256_fA0fB0fC0(GemmParams* gp) {
  asm volatile(
#if !defined(__clang__)
      "mov r14, %[gp]\t\n"
#else
      "mov %[gp], %%r14\t\n"
      ".intel_syntax noprefix\t\n"
#endif

      // Copy parameters
      // k
      "mov r8, [r14 + 0]\t\n"
      // A
      "mov r9, [r14 + 8]\t\n"
      // B
      "mov r10, [r14 + 16]\t\n"
      // beta
      "mov r15, [r14 + 24]\t\n"
      // accum
      "mov rdx, [r14 + 32]\t\n"
      // C
      "mov r12, [r14 + 40]\t\n"
      // ldc
      "mov r13, [r14 + 48]\t\n"
      // b_block_cols
      "mov rdi, [r14 + 56]\t\n"
      // b_block_size
      "mov rsi, [r14 + 64]\t\n"
      // Make copies of A and C
      "mov rax, r9\t\n"
      "mov rcx, r12\t\n"

      "mov rbx, 0\t\n"
      "loop_outter%=:\t\n"
      "mov r14, 0\t\n"
      "vxorps ymm0,ymm0,ymm0\t\n"
      "vxorps ymm1,ymm1,ymm1\t\n"
      "vxorps ymm2,ymm2,ymm2\t\n"
      "vxorps ymm3,ymm3,ymm3\t\n"
      "vxorps ymm4,ymm4,ymm4\t\n"
      "vxorps ymm5,ymm5,ymm5\t\n"
      "vxorps ymm6,ymm6,ymm6\t\n"
      "vxorps ymm7,ymm7,ymm7\t\n"
      "vxorps ymm8,ymm8,ymm8\t\n"
      "vxorps ymm9,ymm9,ymm9\t\n"
      "vxorps ymm10,ymm10,ymm10\t\n"
      "vxorps ymm11,ymm11,ymm11\t\n"
      "vxorps ymm12,ymm12,ymm12\t\n"
      "vxorps ymm13,ymm13,ymm13\t\n"
      "vxorps ymm14,ymm14,ymm14\t\n"
      "vxorps ymm15,ymm15,ymm15\t\n"
      "vxorps ymm16,ymm16,ymm16\t\n"
      "vxorps ymm17,ymm17,ymm17\t\n"
      "vxorps ymm18,ymm18,ymm18\t\n"
      "vxorps ymm19,ymm19,ymm19\t\n"
      "vxorps ymm20,ymm20,ymm20\t\n"
      "vxorps ymm21,ymm21,ymm21\t\n"
      "vxorps ymm22,ymm22,ymm22\t\n"
      "vxorps ymm23,ymm23,ymm23\t\n"
      "vxorps ymm24,ymm24,ymm24\t\n"
      "vxorps ymm25,ymm25,ymm25\t\n"
      "vxorps ymm26,ymm26,ymm26\t\n"
      "vxorps ymm27,ymm27,ymm27\t\n"


      "loop_inner%=:\t\n"

      "vcvtph2ps ymm29,XMMWORD PTR [r10 + 0]\t\n"
      "vcvtph2ps ymm30,XMMWORD PTR [r10 + 16]\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+0]\t\n"
      "vfmadd231ps ymm0,ymm29,ymm28\t\n"
      "vfmadd231ps ymm1,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+4]\t\n"
      "vfmadd231ps ymm2,ymm29,ymm28\t\n"
      "vfmadd231ps ymm3,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+8]\t\n"
      "vfmadd231ps ymm4,ymm29,ymm28\t\n"
      "vfmadd231ps ymm5,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+12]\t\n"
      "vfmadd231ps ymm6,ymm29,ymm28\t\n"
      "vfmadd231ps ymm7,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+16]\t\n"
      "vfmadd231ps ymm8,ymm29,ymm28\t\n"
      "vfmadd231ps ymm9,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+20]\t\n"
      "vfmadd231ps ymm10,ymm29,ymm28\t\n"
      "vfmadd231ps ymm11,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+24]\t\n"
      "vfmadd231ps ymm12,ymm29,ymm28\t\n"
      "vfmadd231ps ymm13,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+28]\t\n"
      "vfmadd231ps ymm14,ymm29,ymm28\t\n"
      "vfmadd231ps ymm15,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+32]\t\n"
      "vfmadd231ps ymm16,ymm29,ymm28\t\n"
      "vfmadd231ps ymm17,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+36]\t\n"
      "vfmadd231ps ymm18,ymm29,ymm28\t\n"
      "vfmadd231ps ymm19,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+40]\t\n"
      "vfmadd231ps ymm20,ymm29,ymm28\t\n"
      "vfmadd231ps ymm21,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+44]\t\n"
      "vfmadd231ps ymm22,ymm29,ymm28\t\n"
      "vfmadd231ps ymm23,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+48]\t\n"
      "vfmadd231ps ymm24,ymm29,ymm28\t\n"
      "vfmadd231ps ymm25,ymm30,ymm28\t\n"
      "vbroadcastss ymm28,DWORD PTR [r9+52]\t\n"
      "vfmadd231ps ymm26,ymm29,ymm28\t\n"
      "vfmadd231ps ymm27,ymm30,ymm28\t\n"
      "add r9,56\t\n"
      "add r10,32\t\n"
      "inc r14\t\n"
      "cmp r14, r8\t\n"
      "jl loop_inner%=\t\n"

      "L_exit%=:\t\n"

      "cmp rdx, 1\t\n"
      "je L_accum%=\t\n"
      // Dump C
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm22\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm23\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm24\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm25\t\n"
      "add r12, r13\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm26\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm27\t\n"
      "add r12, r13\t\n"
      "jmp L_done%=\t\n"

      "L_accum%=:\t\n"
      // Dump C with accumulate
      "vbroadcastss ymm31,DWORD PTR [r15]\t\n"
      "vfmadd231ps ymm0,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm0\t\n"
      "vfmadd231ps ymm1,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm1\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm2,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm2\t\n"
      "vfmadd231ps ymm3,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm3\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm4,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm4\t\n"
      "vfmadd231ps ymm5,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm5\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm6,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm6\t\n"
      "vfmadd231ps ymm7,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm7\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm8,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm8\t\n"
      "vfmadd231ps ymm9,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm9\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm10,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm10\t\n"
      "vfmadd231ps ymm11,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm11\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm12,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm12\t\n"
      "vfmadd231ps ymm13,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm13\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm14,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm14\t\n"
      "vfmadd231ps ymm15,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm15\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm16,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm16\t\n"
      "vfmadd231ps ymm17,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm17\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm18,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm18\t\n"
      "vfmadd231ps ymm19,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm19\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm20,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm20\t\n"
      "vfmadd231ps ymm21,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm21\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm22,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm22\t\n"
      "vfmadd231ps ymm23,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm23\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm24,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm24\t\n"
      "vfmadd231ps ymm25,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm25\t\n"
      "add r12, r13\t\n"
      "vfmadd231ps ymm26,ymm31,ymmword PTR [r12 + 0]\t\n"
      "vmovups ymmword PTR [r12 + 0], ymm26\t\n"
      "vfmadd231ps ymm27,ymm31,ymmword PTR [r12 + 32]\t\n"
      "vmovups ymmword PTR [r12 + 32], ymm27\t\n"
      "add r12, r13\t\n"

      "L_done%=:\t\n"

      // next outer iteration
      "add rcx, 64\t\n"
      "mov r12, rcx\t\n"
      "mov r9, rax\t\n"
      "inc rbx\t\n"
      "cmp rbx, rdi\t\n"
      "jl loop_outter%=\t\n"
      :
      : [gp] "rm"(gp)
      : "r8",
        "r9",
        "r10",
        "r11",
        "r15",
        "r13",
        "r14",
        "rax",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "rbx",
        "r12",
        "memory");
}

} // namespace fbgemm
