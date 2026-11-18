/*
 * mldivide_0QKHZcd4.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PD".
 *
 * Model version              : 1.66
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Thu Oct 22 16:00:40 2026
 * Created for block: PD
 */

#include "rtwtypes.h"
#include "mldivide_0QKHZcd4.h"
#include <cstring>
#include <cmath>
#include <emmintrin.h>

/* Function for MATLAB Function: '<S1>/MATLAB Function1' */
void mldivide_0QKHZcd4(const real_T A[64], real_T B[8])
{
  real_T b_A[64];
  real_T smax;
  int32_T iy;
  int32_T jj;
  int8_T ipiv[8];
  std::memcpy(&b_A[0], &A[0], sizeof(real_T) << 6U);
  for (iy = 0; iy < 8; iy++) {
    ipiv[iy] = static_cast<int8_T>(iy + 1);
  }

  for (int32_T j{0}; j < 7; j++) {
    int32_T b_ix;
    int32_T c_k;
    int32_T ix;
    jj = j * 9;
    iy = 9 - j;
    b_ix = 0;
    ix = jj;
    smax = std::abs(b_A[jj]);
    for (c_k = 2; c_k < iy; c_k++) {
      real_T s;
      s = std::abs(b_A[(ix + c_k) - 1]);
      if (s > smax) {
        b_ix = c_k - 1;
        smax = s;
      }
    }

    if (b_A[jj + b_ix] != 0.0) {
      if (b_ix != 0) {
        iy = j + b_ix;
        ipiv[j] = static_cast<int8_T>(iy + 1);
        b_ix = j;
        for (ix = 0; ix < 8; ix++) {
          c_k = (ix << 3) + b_ix;
          smax = b_A[c_k];
          b_A[c_k] = b_A[iy];
          b_A[iy] = smax;
          iy += 8;
        }
      }

      iy = (jj - j) + 8;
      ix = (((((iy - jj) - 1) / 2) << 1) + jj) + 2;
      c_k = ix - 2;
      for (b_ix = jj + 2; b_ix <= c_k; b_ix += 2) {
        __m128d tmp;
        tmp = _mm_loadu_pd(&b_A[b_ix - 1]);
        tmp = _mm_div_pd(tmp, _mm_set1_pd(b_A[jj]));
        _mm_storeu_pd(&b_A[b_ix - 1], tmp);
      }

      for (b_ix = ix; b_ix <= iy; b_ix++) {
        b_A[b_ix - 1] /= b_A[jj];
      }
    }

    iy = 6 - j;
    b_ix = jj + 10;
    ix = jj + 8;
    for (c_k = 0; c_k <= iy; c_k++) {
      smax = b_A[(c_k << 3) + ix];
      if (smax != 0.0) {
        int32_T c;
        int32_T c_ix;
        smax = -smax;
        c_ix = jj + 1;
        c = (b_ix - j) + 6;
        for (int32_T ijA{b_ix}; ijA <= c; ijA++) {
          b_A[ijA - 1] += b_A[(c_ix + ijA) - b_ix] * smax;
        }
      }

      b_ix += 8;
    }
  }

  for (int32_T j{0}; j < 7; j++) {
    int8_T ipiv_0;
    ipiv_0 = ipiv[j];
    if (j + 1 != ipiv_0) {
      smax = B[j];
      iy = ipiv_0 - 1;
      B[j] = B[iy];
      B[iy] = smax;
    }
  }

  for (int32_T j{0}; j < 8; j++) {
    jj = j << 3;
    if (B[j] != 0.0) {
      for (iy = j + 2; iy < 9; iy++) {
        B[iy - 1] -= b_A[(iy + jj) - 1] * B[j];
      }
    }
  }

  for (int32_T j{7}; j >= 0; j--) {
    jj = j << 3;
    smax = B[j];
    if (smax != 0.0) {
      smax /= b_A[j + jj];
      B[j] = smax;
      for (iy = 0; iy < j; iy++) {
        B[iy] -= b_A[iy + jj] * B[j];
      }
    }
  }
}
