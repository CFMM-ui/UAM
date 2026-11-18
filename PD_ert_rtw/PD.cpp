//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PD.cpp
//
// Code generated for Simulink model 'PD'.
//
// Model version                  : 1.68
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Thu Oct 22 16:39:09 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "PD.h"
#include "rtwtypes.h"
#include <cmath>
#include <cstring>
#include <emmintrin.h>

// Function for MATLAB Function: '<S1>/MATLAB Function1'
void PD::mldivide_j(const real_T A[64], real_T B_1[8])
{
  real_T b_A[64];
  real_T smax;
  int32_T iy;
  int32_T jj;
  int8_T ipiv[8];
  std::memcpy(&b_A[0], &A[0], sizeof(real_T) << 6U);
  for (int32_T j{0}; j < 8; j++) {
    ipiv[j] = static_cast<int8_T>(j + 1);
  }

  for (int32_T j{0}; j < 7; j++) {
    int32_T b_ix;
    int32_T c_k;
    int32_T vectorUB;
    jj = j * 9;
    iy = 9 - j;
    b_ix = 0;
    smax = std::abs(b_A[jj]);
    for (c_k = 2; c_k < iy; c_k++) {
      real_T s;
      s = std::abs(b_A[(jj + c_k) - 1]);
      if (s > smax) {
        b_ix = c_k - 1;
        smax = s;
      }
    }

    if (b_A[jj + b_ix] != 0.0) {
      if (b_ix != 0) {
        iy = j + b_ix;
        ipiv[j] = static_cast<int8_T>(iy + 1);
        for (b_ix = 0; b_ix < 8; b_ix++) {
          c_k = (b_ix << 3) + j;
          smax = b_A[c_k];
          b_A[c_k] = b_A[iy];
          b_A[iy] = smax;
          iy += 8;
        }
      }

      iy = (jj - j) + 8;
      c_k = (((((iy - jj) - 1) / 2) << 1) + jj) + 2;
      vectorUB = c_k - 2;
      for (b_ix = jj + 2; b_ix <= vectorUB; b_ix += 2) {
        __m128d tmp;
        tmp = _mm_loadu_pd(&b_A[b_ix - 1]);
        _mm_storeu_pd(&b_A[b_ix - 1], _mm_div_pd(tmp, _mm_set1_pd(b_A[jj])));
      }

      for (b_ix = c_k; b_ix <= iy; b_ix++) {
        b_A[b_ix - 1] /= b_A[jj];
      }
    }

    iy = 6 - j;
    b_ix = jj + 10;
    for (c_k = 0; c_k <= iy; c_k++) {
      smax = b_A[((c_k << 3) + jj) + 8];
      if (smax != 0.0) {
        int32_T c;
        c = (b_ix - j) + 6;
        for (vectorUB = b_ix; vectorUB <= c; vectorUB++) {
          b_A[vectorUB - 1] += b_A[((jj + vectorUB) - b_ix) + 1] * -smax;
        }
      }

      b_ix += 8;
    }
  }

  for (int32_T j{0}; j < 7; j++) {
    int8_T ipiv_0;
    ipiv_0 = ipiv[j];
    if (j + 1 != ipiv_0) {
      smax = B_1[j];
      B_1[j] = B_1[ipiv_0 - 1];
      B_1[ipiv_0 - 1] = smax;
    }
  }

  for (int32_T j{0}; j < 8; j++) {
    jj = j << 3;
    if (B_1[j] != 0.0) {
      for (iy = j + 2; iy < 9; iy++) {
        B_1[iy - 1] -= b_A[(iy + jj) - 1] * B_1[j];
      }
    }
  }

  for (int32_T j{7}; j >= 0; j--) {
    jj = j << 3;
    smax = B_1[j];
    if (smax != 0.0) {
      B_1[j] = smax / b_A[j + jj];
      for (iy = 0; iy < j; iy++) {
        B_1[iy] -= b_A[iy + jj] * B_1[j];
      }
    }
  }
}

// Model step function
void PD::step()
{
  __m128d tmp_4;
  __m128d tmp_5;
  __m128d tmp_6;
  real_T rtb_BMinv[64];
  real_T rtb_ginv[64];
  real_T tmp[64];
  real_T tmp_2[64];
  real_T x[64];
  real_T rtb_fx[8];
  real_T rtb_ginv_0[8];
  real_T tmp_0[8];
  real_T tmp_1[8];
  real_T tmp_3[8];
  real_T tmp_7[2];
  real_T D14;
  real_T D14_tmp;
  real_T D14_tmp_0;
  real_T D14_tmp_1;
  real_T D14_tmp_2;
  real_T D14_tmp_3;
  real_T D14_tmp_4;
  real_T D14_tmp_5;
  real_T D14_tmp_6;
  real_T D14_tmp_7;
  real_T D14_tmp_8;
  real_T D14_tmp_9;
  real_T D14_tmp_a;
  real_T D14_tmp_b;
  real_T D14_tmp_c;
  real_T D14_tmp_d;
  real_T D14_tmp_e;
  real_T D14_tmp_f;
  real_T D14_tmp_tmp;
  real_T D14_tmp_tmp_0;
  real_T D14_tmp_tmp_1;
  real_T D15;
  real_T D15_tmp;
  real_T D15_tmp_0;
  real_T D15_tmp_1;
  real_T D15_tmp_2;
  real_T D15_tmp_tmp;
  real_T D15_tmp_tmp_0;
  real_T D15_tmp_tmp_1;
  real_T D15_tmp_tmp_2;
  real_T D16;
  real_T D16_tmp;
  real_T D16_tmp_0;
  real_T D16_tmp_1;
  real_T D16_tmp_2;
  real_T D16_tmp_3;
  real_T D16_tmp_tmp;
  real_T D17;
  real_T D17_tmp;
  real_T D17_tmp_0;
  real_T D17_tmp_1;
  real_T D17_tmp_2;
  real_T D17_tmp_3;
  real_T D17_tmp_4;
  real_T D17_tmp_5;
  real_T D17_tmp_6;
  real_T D17_tmp_7;
  real_T D17_tmp_8;
  real_T D17_tmp_tmp;
  real_T D17_tmp_tmp_0;
  real_T D17_tmp_tmp_1;
  real_T D17_tmp_tmp_2;
  real_T D17_tmp_tmp_3;
  real_T D17_tmp_tmp_4;
  real_T D18;
  real_T D18_tmp;
  real_T D24;
  real_T D24_tmp;
  real_T D24_tmp_0;
  real_T D24_tmp_1;
  real_T D24_tmp_2;
  real_T D24_tmp_3;
  real_T D25;
  real_T D27;
  real_T D27_tmp;
  real_T D27_tmp_0;
  real_T D27_tmp_1;
  real_T D34;
  real_T D34_tmp;
  real_T D34_tmp_0;
  real_T D34_tmp_1;
  real_T D34_tmp_2;
  real_T D34_tmp_3;
  real_T D35;
  real_T D37;
  real_T D37_tmp;
  real_T D38;
  real_T D45_tmp;
  real_T D45_tmp_0;
  real_T D45_tmp_1;
  real_T D46;
  real_T D46_tmp;
  real_T D46_tmp_0;
  real_T D46_tmp_1;
  real_T D46_tmp_2;
  real_T D46_tmp_3;
  real_T D46_tmp_4;
  real_T D46_tmp_5;
  real_T D46_tmp_6;
  real_T D46_tmp_7;
  real_T D46_tmp_8;
  real_T D46_tmp_9;
  real_T D46_tmp_a;
  real_T D46_tmp_b;
  real_T D46_tmp_c;
  real_T D46_tmp_d;
  real_T D46_tmp_e;
  real_T D46_tmp_f;
  real_T D46_tmp_g;
  real_T D46_tmp_h;
  real_T D46_tmp_i;
  real_T D46_tmp_j;
  real_T D46_tmp_k;
  real_T D46_tmp_l;
  real_T D46_tmp_m;
  real_T D46_tmp_n;
  real_T D46_tmp_o;
  real_T D46_tmp_tmp;
  real_T D46_tmp_tmp_0;
  real_T D46_tmp_tmp_1;
  real_T D46_tmp_tmp_2;
  real_T D46_tmp_tmp_3;
  real_T D46_tmp_tmp_4;
  real_T D46_tmp_tmp_5;
  real_T D46_tmp_tmp_6;
  real_T D46_tmp_tmp_7;
  real_T D46_tmp_tmp_8;
  real_T D46_tmp_tmp_9;
  real_T D47;
  real_T D47_tmp;
  real_T D47_tmp_0;
  real_T D47_tmp_1;
  real_T D47_tmp_2;
  real_T D48_tmp;
  real_T D48_tmp_0;
  real_T D56;
  real_T D56_tmp;
  real_T D56_tmp_0;
  real_T D56_tmp_1;
  real_T D56_tmp_2;
  real_T D56_tmp_3;
  real_T D56_tmp_4;
  real_T D56_tmp_5;
  real_T D56_tmp_6;
  real_T D56_tmp_7;
  real_T D56_tmp_8;
  real_T D56_tmp_9;
  real_T D56_tmp_a;
  real_T D56_tmp_b;
  real_T D56_tmp_c;
  real_T D56_tmp_d;
  real_T D56_tmp_e;
  real_T D56_tmp_f;
  real_T D56_tmp_g;
  real_T D56_tmp_h;
  real_T D56_tmp_i;
  real_T D56_tmp_j;
  real_T D56_tmp_k;
  real_T D56_tmp_l;
  real_T D56_tmp_m;
  real_T D56_tmp_n;
  real_T D56_tmp_o;
  real_T D56_tmp_p;
  real_T D56_tmp_q;
  real_T D56_tmp_tmp;
  real_T D56_tmp_tmp_0;
  real_T D56_tmp_tmp_1;
  real_T D56_tmp_tmp_2;
  real_T D56_tmp_tmp_3;
  real_T D56_tmp_tmp_4;
  real_T D56_tmp_tmp_5;
  real_T D56_tmp_tmp_6;
  real_T D56_tmp_tmp_7;
  real_T D56_tmp_tmp_8;
  real_T D56_tmp_tmp_9;
  real_T D56_tmp_tmp_a;
  real_T D56_tmp_tmp_b;
  real_T D56_tmp_tmp_c;
  real_T D56_tmp_tmp_d;
  real_T D56_tmp_tmp_e;
  real_T D56_tmp_tmp_f;
  real_T D56_tmp_tmp_g;
  real_T D56_tmp_tmp_h;
  real_T D56_tmp_tmp_i;
  real_T D56_tmp_tmp_j;
  real_T D56_tmp_tmp_k;
  real_T D56_tmp_tmp_l;
  real_T D56_tmp_tmp_m;
  real_T D56_tmp_tmp_n;
  real_T D56_tmp_tmp_o;
  real_T D56_tmp_tmp_p;
  real_T D56_tmp_tmp_q;
  real_T D56_tmp_tmp_r;
  real_T D56_tmp_tmp_tmp;
  real_T D57;
  real_T ab_a;
  real_T rtb_ginv_tmp;
  real_T rtb_ginv_tmp_0;
  real_T rtb_ginv_tmp_1;
  real_T rtb_ginv_tmp_2;
  real_T rtb_ginv_tmp_3;
  real_T rtb_ginv_tmp_4;
  real_T rtb_ginv_tmp_5;
  real_T rtb_ginv_tmp_6;
  real_T rtb_ginv_tmp_7;
  real_T rtb_ginv_tmp_8;
  real_T rtb_ginv_tmp_9;
  real_T rtb_ginv_tmp_a;
  real_T rtb_ginv_tmp_b;
  real_T rtb_ginv_tmp_c;
  real_T rtb_ginv_tmp_d;
  real_T rtb_ginv_tmp_e;
  real_T rtb_ginv_tmp_f;
  real_T rtb_ginv_tmp_g;
  real_T rtb_ginv_tmp_h;
  real_T rtb_ginv_tmp_i;
  real_T rtb_ginv_tmp_tmp;
  real_T rtb_ginv_tmp_tmp_0;
  real_T rtb_ginv_tmp_tmp_1;
  real_T rtb_ginv_tmp_tmp_2;
  real_T rtb_ginv_tmp_tmp_3;
  real_T rtb_ginv_tmp_tmp_4;
  real_T s;
  real_T smax;
  real_T tmp_10;
  real_T tmp_11;
  real_T tmp_12;
  real_T tmp_13;
  real_T tmp_14;
  real_T tmp_15;
  real_T tmp_16;
  real_T tmp_17;
  real_T tmp_18;
  real_T tmp_19;
  real_T tmp_1a;
  real_T tmp_1b;
  real_T tmp_1c;
  real_T tmp_1d;
  real_T tmp_1e;
  real_T tmp_1f;
  real_T tmp_1g;
  real_T tmp_1h;
  real_T tmp_1i;
  real_T tmp_1j;
  real_T tmp_1k;
  real_T tmp_1l;
  real_T tmp_1m;
  real_T tmp_1n;
  real_T tmp_1o;
  real_T tmp_1p;
  real_T tmp_1q;
  real_T tmp_1r;
  real_T tmp_1s;
  real_T tmp_1t;
  real_T tmp_1u;
  real_T tmp_1v;
  real_T tmp_1w;
  real_T tmp_1x;
  real_T tmp_1y;
  real_T tmp_1z;
  real_T tmp_20;
  real_T tmp_21;
  real_T tmp_22;
  real_T tmp_23;
  real_T tmp_24;
  real_T tmp_25;
  real_T tmp_26;
  real_T tmp_27;
  real_T tmp_28;
  real_T tmp_29;
  real_T tmp_2a;
  real_T tmp_2b;
  real_T tmp_2c;
  real_T tmp_2d;
  real_T tmp_2e;
  real_T tmp_2f;
  real_T tmp_2g;
  real_T tmp_2h;
  real_T tmp_2i;
  real_T tmp_2j;
  real_T tmp_2k;
  real_T tmp_2l;
  real_T tmp_2m;
  real_T tmp_2n;
  real_T tmp_2o;
  real_T tmp_2p;
  real_T tmp_2q;
  real_T tmp_2r;
  real_T tmp_2s;
  real_T tmp_2t;
  real_T tmp_2u;
  real_T tmp_2v;
  real_T tmp_2w;
  real_T tmp_2x;
  real_T tmp_2y;
  real_T tmp_2z;
  real_T tmp_30;
  real_T tmp_31;
  real_T tmp_32;
  real_T tmp_33;
  real_T tmp_34;
  real_T tmp_35;
  real_T tmp_36;
  real_T tmp_37;
  real_T tmp_38;
  real_T tmp_39;
  real_T tmp_3a;
  real_T tmp_3b;
  real_T tmp_3c;
  real_T tmp_3d;
  real_T tmp_3e;
  real_T tmp_3f;
  real_T tmp_3g;
  real_T tmp_3h;
  real_T tmp_3i;
  real_T tmp_3j;
  real_T tmp_3k;
  real_T tmp_3l;
  real_T tmp_3m;
  real_T tmp_3n;
  real_T tmp_3o;
  real_T tmp_3p;
  real_T tmp_3q;
  real_T tmp_3r;
  real_T tmp_3s;
  real_T tmp_3t;
  real_T tmp_3u;
  real_T tmp_3v;
  real_T tmp_3w;
  real_T tmp_3x;
  real_T tmp_3y;
  real_T tmp_3z;
  real_T tmp_40;
  real_T tmp_41;
  real_T tmp_42;
  real_T tmp_43;
  real_T tmp_44;
  real_T tmp_45;
  real_T tmp_46;
  real_T tmp_47;
  real_T tmp_48;
  real_T tmp_49;
  real_T tmp_4a;
  real_T tmp_4b;
  real_T tmp_4c;
  real_T tmp_4d;
  real_T tmp_4e;
  real_T tmp_4f;
  real_T tmp_4g;
  real_T tmp_4h;
  real_T tmp_4i;
  real_T tmp_4j;
  real_T tmp_4k;
  real_T tmp_4l;
  real_T tmp_4m;
  real_T tmp_4n;
  real_T tmp_4o;
  real_T tmp_4p;
  real_T tmp_4q;
  real_T tmp_4r;
  real_T tmp_4s;
  real_T tmp_4t;
  real_T tmp_4u;
  real_T tmp_4v;
  real_T tmp_4w;
  real_T tmp_4x;
  real_T tmp_4y;
  real_T tmp_4z;
  real_T tmp_50;
  real_T tmp_51;
  real_T tmp_52;
  real_T tmp_53;
  real_T tmp_54;
  real_T tmp_55;
  real_T tmp_56;
  real_T tmp_57;
  real_T tmp_58;
  real_T tmp_59;
  real_T tmp_5a;
  real_T tmp_8;
  real_T tmp_9;
  real_T tmp_a;
  real_T tmp_b;
  real_T tmp_c;
  real_T tmp_d;
  real_T tmp_e;
  real_T tmp_f;
  real_T tmp_g;
  real_T tmp_h;
  real_T tmp_i;
  real_T tmp_j;
  real_T tmp_k;
  real_T tmp_l;
  real_T tmp_m;
  real_T tmp_n;
  real_T tmp_o;
  real_T tmp_p;
  real_T tmp_q;
  real_T tmp_r;
  real_T tmp_s;
  real_T tmp_t;
  real_T tmp_tmp;
  real_T tmp_tmp_0;
  real_T tmp_tmp_1;
  real_T tmp_tmp_10;
  real_T tmp_tmp_11;
  real_T tmp_tmp_12;
  real_T tmp_tmp_13;
  real_T tmp_tmp_14;
  real_T tmp_tmp_15;
  real_T tmp_tmp_16;
  real_T tmp_tmp_17;
  real_T tmp_tmp_2;
  real_T tmp_tmp_3;
  real_T tmp_tmp_4;
  real_T tmp_tmp_5;
  real_T tmp_tmp_6;
  real_T tmp_tmp_7;
  real_T tmp_tmp_8;
  real_T tmp_tmp_9;
  real_T tmp_tmp_a;
  real_T tmp_tmp_b;
  real_T tmp_tmp_c;
  real_T tmp_tmp_d;
  real_T tmp_tmp_e;
  real_T tmp_tmp_f;
  real_T tmp_tmp_g;
  real_T tmp_tmp_h;
  real_T tmp_tmp_i;
  real_T tmp_tmp_j;
  real_T tmp_tmp_k;
  real_T tmp_tmp_l;
  real_T tmp_tmp_m;
  real_T tmp_tmp_n;
  real_T tmp_tmp_o;
  real_T tmp_tmp_p;
  real_T tmp_tmp_q;
  real_T tmp_tmp_r;
  real_T tmp_tmp_s;
  real_T tmp_tmp_t;
  real_T tmp_tmp_u;
  real_T tmp_tmp_v;
  real_T tmp_tmp_w;
  real_T tmp_tmp_x;
  real_T tmp_tmp_y;
  real_T tmp_tmp_z;
  real_T tmp_u;
  real_T tmp_v;
  real_T tmp_w;
  real_T tmp_x;
  real_T tmp_y;
  real_T tmp_z;
  real_T w_a;
  real_T w_a_tmp;
  real_T x_a;
  int32_T b_ix;
  int32_T d_k;
  int32_T i;
  int32_T ijA;
  int32_T ix;
  int32_T iy;
  int32_T jj;
  int8_T ipiv[8];
  int8_T p[8];
  int8_T ipiv_0;

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Inport generated from: '<Root>/InBus1_Inport_2'
  //   MATLAB Function: '<Root>/GetBInvMatrix'
  //
  smax = std::sin(rtU.InBus1_Positions[5]);
  D14_tmp = std::sin(rtU.InBus1_Positions[6]);
  s = std::cos(rtU.InBus1_Positions[5]);
  D14_tmp_0 = std::sin(rtU.InBus1_Positions[4]);
  D14_tmp_1 = std::sin(rtU.InBus1_Positions[3]);
  D14_tmp_2 = std::cos(rtU.InBus1_Positions[3]);
  D14_tmp_3 = std::cos(rtU.InBus1_Positions[7]);
  D14_tmp_4 = std::sin(rtU.InBus1_Positions[7]);
  D14_tmp_tmp = rtU.InBus1_Positions[6] + rtU.InBus1_Positions[7];
  D14_tmp_5 = std::sin(D14_tmp_tmp);
  D14_tmp_6 = std::cos(rtU.InBus1_Positions[6]);
  D14_tmp_7 = std::cos(D14_tmp_tmp);
  D14_tmp_8 = 0.01400542 * D14_tmp_3 + 0.040588879999999994;
  D14_tmp_9 = 0.01400542 * D14_tmp_7;
  D14_tmp_tmp_0 = 0.040588879999999994 * D14_tmp;
  D14_tmp_tmp_1 = 0.01400542 * D14_tmp_5;
  D14_tmp_a = D14_tmp_tmp_0 + D14_tmp_tmp_1;
  D14_tmp_b = D14_tmp_a * smax;
  D14_tmp_c = D14_tmp_8 * s;
  D14_tmp_d = 0.01400542 * smax;
  D14_tmp_e = 0.01400542 * s * D14_tmp_4 * D14_tmp_0;
  D14_tmp_f = (-D14_tmp_8 * smax + D14_tmp_e) * D14_tmp_2;
  D14 = (((D14_tmp_d * D14_tmp * D14_tmp_4 + -0.023689199999999997 * smax) +
          D14_tmp_c * D14_tmp * D14_tmp_0) * D14_tmp_2 + ((D14_tmp_9 +
           0.023689199999999997) * s * D14_tmp_0 + D14_tmp_b) * D14_tmp_1) +
    (0.040588879999999994 * s * D14_tmp_1 * D14_tmp_0 + D14_tmp_f) * D14_tmp_6;
  D15_tmp = std::cos(rtU.InBus1_Positions[4]);
  D15_tmp_tmp = rtU.InBus1_Positions[3] + rtU.InBus1_Positions[6];
  D15_tmp_0 = std::cos(D15_tmp_tmp);
  D15_tmp_tmp_0 = D15_tmp_tmp + rtU.InBus1_Positions[7];
  D15_tmp_1 = std::cos(D15_tmp_tmp_0);
  D15_tmp_tmp_1 = 0.040588879999999994 * D15_tmp_0;
  D15_tmp_tmp_2 = 0.01400542 * D15_tmp_1;
  D15_tmp_2 = (0.023689199999999997 * D14_tmp_2 + D15_tmp_tmp_1) + D15_tmp_tmp_2;
  D15 = D15_tmp_2 * -s * D15_tmp;
  D16_tmp_tmp = 0.040588879999999994 * D14_tmp_6;
  D16_tmp = (D16_tmp_tmp + 0.023689199999999997) + D14_tmp_9;
  D16_tmp_0 = D16_tmp * s;
  D16_tmp_1 = D16_tmp * smax;
  D16_tmp_2 = D16_tmp_1 * D14_tmp_0;
  D16_tmp_3 = D14_tmp_b * D14_tmp_0 + D16_tmp_0;
  D16 = (D14_tmp_a * -s + D16_tmp_2) * D14_tmp_2 + D16_tmp_3 * -D14_tmp_1;
  D17_tmp_tmp_0 = D14_tmp_1 * smax;
  D17_tmp_tmp_1 = D14_tmp_2 * s;
  D17_tmp = D17_tmp_tmp_1 * D14_tmp_0 + D17_tmp_tmp_0;
  D17_tmp_0 = 0.09794 * D14_tmp_5;
  D17_tmp_tmp = s * D14_tmp_1;
  D17_tmp_tmp_2 = -D14_tmp_2 * smax;
  D17_tmp_1 = D17_tmp_tmp * D14_tmp_0 + D17_tmp_tmp_2;
  D17_tmp_2 = 0.09794 * D14_tmp_7;
  D17_tmp_3 = 0.17 * D14_tmp_6;
  D17_tmp_4 = 0.17 * D14_tmp + D17_tmp_0;
  D17_tmp_5 = D17_tmp_4 * 0.143;
  D17_tmp_6 = D17_tmp_3 + D17_tmp_2;
  D17_tmp_tmp_3 = smax * D14_tmp;
  D17_tmp_tmp_4 = s * D14_tmp_6;
  D17_tmp_7 = D17_tmp_tmp_4 * D14_tmp_0 + D17_tmp_tmp_3;
  D17_tmp_8 = s * D14_tmp * D14_tmp_0 + -D14_tmp_6 * smax;
  D17 = ((0.01627888 * D14_tmp_1 * D17_tmp_7 + D17_tmp_5 * D17_tmp) + D17_tmp_6 *
         0.143 * D17_tmp_1) + 0.01627888 * D14_tmp_2 * D17_tmp_8;
  D18_tmp = D17_tmp * D17_tmp_0 + D17_tmp_1 * D17_tmp_2;
  D18 = D18_tmp * 0.143;
  D24_tmp = 0.11464 * D14_tmp_6 + 0.08312;
  D24_tmp_0 = (D17_tmp_3 + 0.08312) + D17_tmp_2;
  D24_tmp_1 = D17_tmp_1 * D17_tmp_4;
  D17_tmp_3 = D15_tmp * D15_tmp;
  D24_tmp_2 = 0.08312 * D14_tmp_2;
  D24_tmp_3 = (0.17 * D15_tmp_0 + D24_tmp_2) + 0.09794 * D15_tmp_1;
  D24 = (((D24_tmp * smax * D14_tmp_0 + -0.11464 * s * D14_tmp) * (0.142 *
           D14_tmp_1) + 0.143 * s * D24_tmp_3 * D17_tmp_3) + (0.11464 * smax *
          D14_tmp * D14_tmp_0 + D24_tmp * s) * (0.142 * D14_tmp_2)) + (D24_tmp_0
    * D17_tmp - D24_tmp_1) * (0.143 * D14_tmp_0);
  D25 = -D15_tmp_2 * D15_tmp * smax;
  D17_tmp_5 = ((D24_tmp * -0.142 * D17_tmp - D24_tmp_0 * 0.143 * D17_tmp) +
               0.01627888 * D14_tmp * D17_tmp_1) + D17_tmp_5 * D17_tmp_1;
  D17_tmp_tmp_0 = D17_tmp_tmp_0 * D14_tmp_0 + D17_tmp_tmp_1;
  D27_tmp = D14_tmp_2 * smax * D14_tmp_0;
  D17_tmp_tmp_1 = D17_tmp_tmp - D27_tmp;
  D27_tmp_0 = D17_tmp_tmp_0 * D16_tmp_tmp;
  D27_tmp_1 = D17_tmp_tmp_0 * D14_tmp_9;
  D27 = (D17_tmp_tmp_1 * -D14_tmp_a + D27_tmp_0) + D27_tmp_1;
  D27_tmp += -s * D14_tmp_1;
  D17_tmp_0 = D27_tmp * D17_tmp_0 + D17_tmp_tmp_0 * D17_tmp_2;
  D17_tmp_2 = D17_tmp_0 * 0.143;
  D34_tmp = std::sin(D15_tmp_tmp);
  D34_tmp_0 = std::sin(D15_tmp_tmp_0);
  D34_tmp_1 = 0.040588879999999994 * D34_tmp;
  D34_tmp_2 = 0.01400542 * D34_tmp_0;
  D34_tmp_3 = (0.023689199999999997 * D14_tmp_1 + D34_tmp_1) + D34_tmp_2;
  D34 = D34_tmp_3 * D15_tmp;
  D35 = D15_tmp_2 * D14_tmp_0;
  D37_tmp = D34_tmp_1 + D34_tmp_2;
  D37 = D37_tmp * D15_tmp;
  D38 = 0.01400542 * D15_tmp * D34_tmp_0;
  D45_tmp = rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] * D15_tmp_1;
  D45_tmp_0 = rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D34_tmp_0;
  D45_tmp_1 = ((rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] * D15_tmp_0 +
                D45_tmp) + rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
               D34_tmp) + D45_tmp_0;
  D46_tmp_tmp_5 = rtU.InBus1_Positions[6] - rtU.InBus1_Positions[4];
  D46_tmp = std::sin(D46_tmp_tmp_5);
  D46_tmp_tmp_4 = rtU.InBus1_Positions[4] + rtU.InBus1_Positions[6];
  D46_tmp_0 = std::sin(D46_tmp_tmp_4);
  D46_tmp_tmp = D15_tmp_tmp - rtU.InBus1_Positions[4];
  D46_tmp_1 = std::cos(D46_tmp_tmp);
  D46_tmp_tmp_0 = D15_tmp_tmp_0 - rtU.InBus1_Positions[4];
  D46_tmp_2 = std::cos(D46_tmp_tmp_0);
  D46_tmp_tmp_1 = D15_tmp_tmp + rtU.InBus1_Positions[4];
  D46_tmp_3 = std::cos(D46_tmp_tmp_1);
  D46_tmp_tmp_2 = D15_tmp_tmp_0 + rtU.InBus1_Positions[4];
  D46_tmp_4 = std::cos(D46_tmp_tmp_2);
  D46_tmp_5 = std::sin(D46_tmp_tmp);
  D46_tmp_6 = std::sin(D46_tmp_tmp_0);
  D46_tmp_7 = std::sin(D46_tmp_tmp_1);
  D46_tmp_8 = std::sin(D46_tmp_tmp_2);
  D46_tmp_tmp_6 = rtU.InBus1_Positions[7] - rtU.InBus1_Positions[4];
  D46_tmp_9 = std::sin(D46_tmp_tmp_6);
  D46_tmp_tmp_7 = D14_tmp_tmp - rtU.InBus1_Positions[4];
  D46_tmp_a = std::sin(D46_tmp_tmp_7);
  D46_tmp_tmp_8 = rtU.InBus1_Positions[4] + rtU.InBus1_Positions[7];
  D46_tmp_b = std::sin(D46_tmp_tmp_8);
  D46_tmp_tmp_9 = D14_tmp_tmp + rtU.InBus1_Positions[4];
  D46_tmp_c = std::sin(D46_tmp_tmp_9);
  D46_tmp_tmp_3 = rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D46_tmp_4;
  D46_tmp_d = ((-rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] * D46_tmp_1 -
                rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D46_tmp_2) -
               rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] * D46_tmp_3) -
    D46_tmp_tmp_3;
  D46_tmp_e = rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] * D46_tmp_5;
  D46_tmp_f = 0.004761842800000001 * D46_tmp_9;
  D46_tmp_g = rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] * D46_tmp_6;
  D46_tmp_h = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    D14_tmp_0;
  D46_tmp_i = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    D14_tmp_0;
  D46_tmp_j = -0.0037324216063999997 * D14_tmp_0;
  D46_tmp_k = -0.0027433816695999996 * D14_tmp_0;
  D46_tmp_l = -0.008265400000000001 * D14_tmp_0;
  D46_tmp_m = rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] * D46_tmp_7;
  D46_tmp_n = -0.004761842800000001 * D46_tmp_b;
  D46_tmp_o = rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] * D46_tmp_8;
  D46 = ((((((((((((((((((((0.0027062010112 * D46_tmp + D46_tmp_d) +
    0.0040412944 * D46_tmp) + D46_tmp_e) + D46_tmp_f) + 0.0023282610207999996 *
                        D46_tmp_a) + D46_tmp_g) + D46_tmp_h) + D46_tmp_i) + -2.0
                    * rtConstP.MATLABFunction1_HexaConstants.Inertia[0] *
                    D14_tmp_0) + D46_tmp_j) + -0.0019621373695999996 * D14_tmp_0)
                 + D46_tmp_k) + -0.0019759552383999996 * D14_tmp_0) + D46_tmp_l)
              + -0.0027062010112 * D46_tmp_0) + -0.0040412944 * D46_tmp_0) +
            D46_tmp_m) + D46_tmp_n) + -0.0023282610207999996 * D46_tmp_c) +
         D46_tmp_o) * 0.5;
  D47_tmp = 0.0011641305103999998 * D14_tmp_7;
  D47_tmp_0 = rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] +
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[8];
  D47_tmp_1 = 0.004761842800000001 * D14_tmp_3;
  D47_tmp_2 = (((D47_tmp_0 + 0.0018662108031999999) + 0.0013716908347999998) +
               0.0041327000000000004) + 0.0033737477055999993 * D14_tmp_6;
  D47 = (D47_tmp_2 + D47_tmp_1) + D47_tmp;
  D48_tmp = (rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] +
             0.0013716908347999998) + 0.0023809214000000004 * D14_tmp_3;
  D48_tmp_0 = D48_tmp + D47_tmp;
  D56_tmp_tmp = 2.0 * rtU.InBus1_Positions[3];
  D56_tmp_tmp_9 = D56_tmp_tmp - rtU.InBus1_Positions[4];
  D56_tmp = std::sin(D56_tmp_tmp_9);
  D56_tmp_tmp_1 = D56_tmp_tmp + rtU.InBus1_Positions[6];
  D56_tmp_tmp_6 = D56_tmp_tmp_1 - rtU.InBus1_Positions[4];
  D56_tmp_0 = std::sin(D56_tmp_tmp_6);
  D56_tmp_tmp_tmp = 2.0 * rtU.InBus1_Positions[6];
  D56_tmp_tmp_0 = D56_tmp_tmp + D56_tmp_tmp_tmp;
  D56_tmp_tmp_3 = D56_tmp_tmp_0 - rtU.InBus1_Positions[4];
  D56_tmp_1 = std::sin(D56_tmp_tmp_3);
  D56_tmp_tmp_2 = 2.0 * rtU.InBus1_Positions[7] + D56_tmp_tmp_0;
  D56_tmp_tmp_4 = D56_tmp_tmp_2 - rtU.InBus1_Positions[4];
  D56_tmp_2 = std::sin(D56_tmp_tmp_4);
  D56_tmp_tmp_7 = D56_tmp_tmp + rtU.InBus1_Positions[4];
  D56_tmp_3 = std::sin(D56_tmp_tmp_7);
  D56_tmp_tmp_8 = D56_tmp_tmp_1 + rtU.InBus1_Positions[4];
  D56_tmp_4 = std::sin(D56_tmp_tmp_8);
  D56_tmp_tmp_5 = D56_tmp_tmp_0 + rtU.InBus1_Positions[4];
  D56_tmp_5 = std::sin(D56_tmp_tmp_5);
  D56_tmp_tmp_2 += rtU.InBus1_Positions[4];
  D56_tmp_6 = std::sin(D56_tmp_tmp_2);
  D56_tmp_7 = std::cos(D56_tmp_tmp_3);
  D56_tmp_8 = std::cos(D56_tmp_tmp_4);
  D56_tmp_9 = std::cos(D56_tmp_tmp_5);
  D56_tmp_a = std::cos(D56_tmp_tmp_2);
  D56_tmp_tmp_3 = D56_tmp_tmp_1 + rtU.InBus1_Positions[7];
  D56_tmp_tmp_2 = D56_tmp_tmp_3 - rtU.InBus1_Positions[4];
  D56_tmp_b = std::sin(D56_tmp_tmp_2);
  D56_tmp_tmp_0 += rtU.InBus1_Positions[7];
  D56_tmp_tmp_4 = D56_tmp_tmp_0 - rtU.InBus1_Positions[4];
  D56_tmp_c = std::sin(D56_tmp_tmp_4);
  D56_tmp_tmp_5 = D56_tmp_tmp_3 + rtU.InBus1_Positions[4];
  D56_tmp_d = std::sin(D56_tmp_tmp_5);
  D56_tmp_tmp_0 += rtU.InBus1_Positions[4];
  D56_tmp_e = std::sin(D56_tmp_tmp_0);
  D56_tmp_f = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  D56_tmp_g = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  D56_tmp_h = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  D56_tmp_i = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  D56_tmp_j = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  D56_tmp_k = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  D56_tmp_l = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  D56_tmp_m = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  D56_tmp_n = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  D56_tmp_o = -2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  D56_tmp_tmp_a = rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * D56_tmp;
  D56_tmp_tmp_b = rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D56_tmp;
  D56_tmp_tmp_c = 0.0009810686847999998 * D56_tmp;
  D56_tmp_tmp_d = 0.0009879776191999998 * D56_tmp;
  D56_tmp_tmp_e = rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D56_tmp_1;
  D56_tmp_tmp_f = rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D56_tmp_1;
  D56_tmp_tmp_g = 0.0018662108031999999 * D56_tmp_1;
  D56_tmp_tmp_h = 0.0041327000000000004 * D56_tmp_1;
  D56_tmp_tmp_i = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D56_tmp_2;
  D56_tmp_tmp_j = rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D56_tmp_2;
  D56_tmp_tmp_k = 0.0013716908347999998 * D56_tmp_2;
  D56_tmp_tmp_l = rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * D56_tmp_3;
  D56_tmp_tmp_m = rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D56_tmp_3;
  D56_tmp_tmp_n = 0.0009810686847999998 * D56_tmp_3;
  D56_tmp_tmp_o = rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D56_tmp_5;
  D56_tmp_tmp_p = rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D56_tmp_5;
  D56_tmp_tmp_q = 0.0018662108031999999 * D56_tmp_5;
  D56_tmp_tmp_r = 0.0041327000000000004 * D56_tmp_5;
  D56_tmp = (((((((((((((((((((((((((((((((((((((D56_tmp_n * D46_tmp_1 +
    D56_tmp_f * D56_tmp_7) + D56_tmp_o * D46_tmp_2) + D56_tmp_g * D56_tmp_8) +
    D56_tmp_l * D46_tmp_3) + D56_tmp_f * D56_tmp_9) + D56_tmp_m * D46_tmp_4) +
    D56_tmp_g * D56_tmp_a) + D56_tmp_tmp_a) - D56_tmp_tmp_b) + D56_tmp_tmp_c) +
    D56_tmp_tmp_d) + D56_tmp_h * D46_tmp_5) + 0.0027062010112 * D56_tmp_0) +
    0.0040412944 * D56_tmp_0) - D56_tmp_tmp_e) + D56_tmp_tmp_f) + D56_tmp_tmp_g)
    + D56_tmp_tmp_h) + D56_tmp_i * D46_tmp_6) + 0.0023282610207999996 *
    D56_tmp_b) + 0.004761842800000001 * D56_tmp_c) - D56_tmp_tmp_i) +
    D56_tmp_tmp_j) + D56_tmp_tmp_k) + D56_tmp_tmp_l) - D56_tmp_tmp_m) +
                       D56_tmp_tmp_n) + 0.0009879776191999998 * D56_tmp_3) +
                     D56_tmp_j * D46_tmp_7) + 0.0027062010112 * D56_tmp_4) +
                   0.0040412944 * D56_tmp_4) - D56_tmp_tmp_o) + D56_tmp_tmp_p) +
                D56_tmp_tmp_q) + D56_tmp_tmp_r) + D56_tmp_k * D46_tmp_8) +
             0.0023282610207999996 * D56_tmp_d) + 0.004761842800000001 *
    D56_tmp_e;
  D56_tmp_p = rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D56_tmp_6;
  D56_tmp_q = 0.0013716908347999998 * D56_tmp_6;
  D56 = (((-rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D56_tmp_6 +
           D56_tmp) + D56_tmp_p) + D56_tmp_q) * 0.25;
  D45_tmp += D45_tmp_0;
  w_a_tmp = 0.11464 * D14_tmp;
  D45_tmp_0 = D17_tmp * -D24_tmp + D17_tmp_1 * w_a_tmp;
  D24_tmp_1 += -D24_tmp_0 * D17_tmp;
  D24_tmp = D17_tmp_tmp_1 * D24_tmp + D17_tmp_tmp_0 * w_a_tmp;
  ab_a = D24_tmp_0 * D17_tmp_tmp_1 + D17_tmp_tmp_0 * D17_tmp_4;
  D46_tmp_a *= 0.0011641305103999998;
  D46_tmp_c *= 0.0011641305103999998;
  D24_tmp_0 = (((((((((((((((((0.0013531005056 * D46_tmp + D46_tmp_d) +
    0.0020206472 * D46_tmp) + D46_tmp_e) + D46_tmp_f) + D46_tmp_a) + D46_tmp_g)
    + D46_tmp_h) + D46_tmp_i) + D46_tmp_j) + D46_tmp_k) + D46_tmp_l) -
                    0.0013531005056 * D46_tmp_0) - 0.0020206472 * D46_tmp_0) +
                  D46_tmp_m) + D46_tmp_n) - D46_tmp_c) + D46_tmp_o) * 0.5;
  D46_tmp_g = (((((((((-rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
                       D46_tmp_2 - D46_tmp_tmp_3) + 0.0023809214000000004 *
                      D46_tmp_9) + D46_tmp_a) + D46_tmp_g) + D46_tmp_i) +
                  D46_tmp_k) + -0.0023809214000000004 * D46_tmp_b) - D46_tmp_c)
               + D46_tmp_o) * 0.5;
  D46_tmp_9 = std::cos(D56_tmp_tmp);
  D46_tmp_tmp_3 = D15_tmp_tmp * 2.0;
  D46_tmp_a = std::cos(D46_tmp_tmp_3);
  D46_tmp_b = std::cos(D56_tmp_tmp_1);
  D46_tmp_d = D15_tmp_tmp_0 * 2.0;
  D46_tmp_c = std::cos(D46_tmp_d);
  D46_tmp = std::sin(D56_tmp_tmp_tmp);
  D46_tmp_i = D14_tmp_tmp * 2.0;
  D46_tmp_0 = std::cos(D46_tmp_i);
  D46_tmp_i = std::sin(D46_tmp_i);
  rtb_ginv_tmp_tmp_0 = 2.0 * rtU.InBus1_Positions[4];
  D46_tmp_k = std::sin(rtb_ginv_tmp_tmp_0);
  D46_tmp_o = std::sin(D46_tmp_tmp_3);
  D46_tmp_d = std::sin(D46_tmp_d);
  rtb_ginv_tmp = std::cos(D56_tmp_tmp_3);
  rtb_ginv_tmp_tmp = D46_tmp_tmp_3 + rtU.InBus1_Positions[7];
  D46_tmp_tmp_3 = std::cos(rtb_ginv_tmp_tmp);
  D56_tmp_tmp_tmp = std::cos(D56_tmp_tmp_tmp);
  rtb_ginv[0] = 2.1037999999999997;
  rtb_ginv[8] = 0.0;
  rtb_ginv[16] = 0.0;
  rtb_ginv[24] = D14;
  rtb_ginv[32] = D15;
  rtb_ginv[40] = D16;
  rtb_ginv[48] = D17;
  rtb_ginv[56] = D18;
  rtb_ginv[1] = 0.0;
  rtb_ginv[9] = 2.1037999999999997;
  rtb_ginv[17] = 0.0;
  rtb_ginv[25] = D24;
  rtb_ginv[33] = D25;
  rtb_ginv[41] = D17_tmp_5;
  rtb_ginv[49] = D27;
  rtb_ginv[57] = D17_tmp_2;
  rtb_ginv[2] = 0.0;
  rtb_ginv[10] = 0.0;
  rtb_ginv[18] = 2.1037999999999997;
  rtb_ginv[26] = D34;
  rtb_ginv[34] = D35;
  rtb_ginv[42] = 0.0;
  rtb_ginv[50] = D37;
  rtb_ginv[58] = D38;
  rtb_ginv[3] = D14;
  rtb_ginv[11] = D24;
  rtb_ginv[19] = D34;
  rtb_ginv_tmp_0 = 0.006747495411199999 * D14_tmp_6;
  rtb_ginv_tmp_1 = 0.0023282610207999996 * D14_tmp_7;
  rtb_ginv_tmp_6 = (((((D47_tmp_0 +
                        rtConstP.MATLABFunction1_HexaConstants.Inertia[0]) +
                       0.0018662108031999999) + 0.0009810686847999998) +
                     0.0013716908347999998) + 0.0009879776191999998) +
    0.0041327000000000004;
  rtb_ginv[27] = ((rtb_ginv_tmp_6 + rtb_ginv_tmp_0) + D47_tmp_1) +
    rtb_ginv_tmp_1;
  rtb_ginv[35] = D45_tmp_1;
  rtb_ginv[43] = D46;
  rtb_ginv[51] = D47;
  rtb_ginv[59] = D48_tmp_0;
  rtb_ginv[4] = D15;
  rtb_ginv[12] = D25;
  rtb_ginv[20] = D35;
  rtb_ginv[28] = D45_tmp_1;
  D46_tmp_e = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  D46_tmp_f = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  rtb_ginv_tmp_7 = rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D46_tmp_a;
  rtb_ginv_tmp_8 = 0.0018662108031999999 * D46_tmp_a;
  rtb_ginv_tmp_9 = 0.0041327000000000004 * D46_tmp_a;
  D46_tmp_h = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D46_tmp_c;
  D46_tmp_j = rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D46_tmp_c;
  D46_tmp_l = 0.0013716908347999998 * D46_tmp_c;
  rtb_ginv[36] =
    ((((((((((((((((((((((((((((((rtConstP.MATLABFunction1_ArmConstants.Inertia1[
    0] + rtConstP.MATLABFunction1_ArmConstants.Inertia1[4]) +
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[0]) +
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[4]) +
    rtConstP.MATLABFunction1_HexaConstants.Inertia[4]) +
    rtConstP.MATLABFunction1_HexaConstants.Inertia[8]) + 0.0018662108031999999)
    + 0.0009810686847999998) + 0.0013716908347999998) + 0.0009879776191999998) +
    0.0041327000000000004) + rtConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    D46_tmp_9) - rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D46_tmp_9)
                      + 0.0009810686847999998 * D46_tmp_9) +
                     0.0009879776191999998 * D46_tmp_9) + rtb_ginv_tmp_0) +
                   -rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
                   D46_tmp_a) + rtb_ginv_tmp_7) + rtb_ginv_tmp_8) +
                rtb_ginv_tmp_9) + 0.0027062010112 * D46_tmp_b) + 0.0040412944 *
              D46_tmp_b) + D47_tmp_1) + rtb_ginv_tmp_1) - D46_tmp_h) + D46_tmp_j)
         + D46_tmp_l) + 0.0023282610207999996 * rtb_ginv_tmp) +
       0.004761842800000001 * D46_tmp_tmp_3) + D46_tmp_f * D46_tmp_o) +
     D46_tmp_e * D46_tmp_d) * 0.5;
  rtb_ginv[44] = D56;
  rtb_ginv[52] = D45_tmp_1;
  rtb_ginv[60] = D45_tmp;
  rtb_ginv[5] = D16;
  rtb_ginv[13] = D17_tmp_5;
  rtb_ginv[21] = 0.0;
  rtb_ginv[29] = D46;
  rtb_ginv[37] = D56;
  D46_tmp_m = D14_tmp_2 * D14_tmp_2;
  D46_tmp_n = D14_tmp_6 * D14_tmp_6;
  w_a_tmp = D14_tmp * D14_tmp;
  rtb_ginv_tmp_2 = D14_tmp_1 * D14_tmp_1;
  rtb_ginv_tmp_3 = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] +
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  rtb_ginv_tmp_4 = -rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] +
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  rtb_ginv_tmp_tmp_1 = 2.0 * D14_tmp_2;
  D14 = rtb_ginv_tmp_tmp_1 * D17_tmp_3 * D14_tmp_1;
  rtb_ginv_tmp_5 = D14_tmp_0 * D14_tmp_0;
  rtb_ginv_tmp_a = rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] * D14_tmp_6
    - rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] * D14_tmp;
  rtb_ginv_tmp_b = rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] * D14_tmp_6
    + rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] * D14_tmp;
  rtb_ginv_tmp_c = rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D14_tmp_7
    - rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] * D14_tmp_5;
  rtb_ginv_tmp_d = rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] * D14_tmp_7
    + rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D14_tmp_5;
  rtb_ginv_tmp_e = D46_tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  rtb_ginv_tmp_f = w_a_tmp * rtConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  D46_tmp_n = (D46_tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] +
               w_a_tmp * rtConstP.MATLABFunction1_ArmConstants.Inertia1[0]) +
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[3] * D46_tmp;
  rtb_ginv_tmp_tmp_2 = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] -
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  w_a_tmp = (rtb_ginv_tmp_tmp_2 * D46_tmp_0 + rtb_ginv_tmp_3) + D56_tmp_g *
    D46_tmp_i;
  rtb_ginv_tmp_tmp_3 = rtb_ginv_tmp_4 * D46_tmp_0;
  rtb_ginv_tmp_tmp_4 = D46_tmp_e * D46_tmp_i;
  rtb_ginv_tmp_3 = (rtb_ginv_tmp_tmp_3 + rtb_ginv_tmp_3) + rtb_ginv_tmp_tmp_4;
  rtb_ginv_tmp_g = D46_tmp_m * rtConstP.MATLABFunction1_HexaConstants.Inertia[8];
  rtb_ginv_tmp_h = D17_tmp_3 * rtb_ginv_tmp_2;
  rtb_ginv_tmp_i = D46_tmp_m * D17_tmp_3;
  rtb_ginv[45] =
    ((((((((((((((((((-rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] +
                      rtConstP.MATLABFunction1_ArmConstants.Inertia1[4]) *
                     D14_tmp_6 * D14_tmp +
                     -rtConstP.MATLABFunction1_ArmConstants.Inertia1[3] *
                     D56_tmp_tmp_tmp) * D14 + (D17_tmp_3 *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * rtb_ginv_tmp_2 +
    rtb_ginv_tmp_g * D17_tmp_3)) + ((rtb_ginv_tmp_e + rtb_ginv_tmp_f) +
    -rtConstP.MATLABFunction1_ArmConstants.Inertia1[3] * D46_tmp) *
                   rtb_ginv_tmp_i) + D46_tmp_n * rtb_ginv_tmp_h) + D46_tmp_m *
                 0.5 * D17_tmp_3 * w_a_tmp) + D17_tmp_3 * 0.5 * rtb_ginv_tmp_2 *
                rtb_ginv_tmp_3) + (rtb_ginv_tmp_4 * 0.5 * D46_tmp_i +
    -rtConstP.MATLABFunction1_ArmConstants.Inertia2[3] * D46_tmp_0) * D14) +
              rtb_ginv_tmp_5 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[8])
             + rtb_ginv_tmp_5 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[8])
            + rtb_ginv_tmp_5 * rtConstP.MATLABFunction1_HexaConstants.Inertia[0])
           + D45_tmp_0 * D45_tmp_0 * 0.142) + D24_tmp_1 * D24_tmp_1 * 0.143) +
         D24_tmp * D24_tmp * 0.142) + ab_a * ab_a * 0.143) + rtb_ginv_tmp_a *
       D14_tmp_2 * D46_tmp_k) - rtb_ginv_tmp_b * D14_tmp_1 * D46_tmp_k) +
     rtb_ginv_tmp_c * D14_tmp_2 * D46_tmp_k) - rtb_ginv_tmp_d * D14_tmp_1 *
    D46_tmp_k;
  rtb_ginv[53] = D24_tmp_0;
  rtb_ginv[61] = D46_tmp_g;
  rtb_ginv[6] = D17;
  rtb_ginv[14] = D27;
  rtb_ginv[22] = D37;
  rtb_ginv[30] = D47;
  rtb_ginv[38] = D45_tmp_1;
  rtb_ginv[46] = D24_tmp_0;
  rtb_ginv[54] = (((D47_tmp_0 + 0.0018662108031999999) + 0.0013716908347999998)
                  + 0.0041327000000000004) + D47_tmp_1;
  rtb_ginv[62] = D48_tmp;
  rtb_ginv[7] = D18;
  rtb_ginv[15] = D17_tmp_2;
  rtb_ginv[23] = D38;
  rtb_ginv[31] = D48_tmp_0;
  rtb_ginv[39] = D45_tmp;
  rtb_ginv[47] = D46_tmp_g;
  rtb_ginv[55] = D48_tmp;
  rtb_ginv[63] = rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] +
    0.0013716908347999998;
  D14 = std::sin(D56_tmp_tmp);
  D15 = std::sin(D56_tmp_tmp_1);
  D16 = std::cos(D56_tmp_tmp_6);
  D17 = std::cos(D56_tmp_tmp_7);
  D18 = std::cos(D46_tmp_tmp_4);
  D24 = std::cos(D56_tmp_tmp_8);
  D25 = std::cos(D56_tmp_tmp_9);
  D17_tmp_5 = std::cos(D46_tmp_tmp_5);
  D27 = std::cos(D46_tmp_tmp_6);
  D17_tmp_2 = std::cos(D46_tmp_tmp_7);
  D34 = std::cos(D56_tmp_tmp_2);
  D35 = std::cos(D56_tmp_tmp_4);
  D37 = std::cos(D46_tmp_tmp_8);
  D38 = std::cos(D46_tmp_tmp_9);
  D46_tmp_tmp_5 = std::cos(D56_tmp_tmp_5);
  D46 = std::cos(D56_tmp_tmp_0);
  D47 = std::sin(D56_tmp_tmp_3);
  D56_tmp_tmp_0 = std::sin(rtb_ginv_tmp_tmp);
  D56_tmp_tmp_4 = -2.0 * rtU.InBus1_Positions[4];
  D56 = std::sin(D56_tmp_tmp_1 + D56_tmp_tmp_4);
  D46_tmp_tmp_7 = D46_tmp_tmp * 2.0;
  D57 = std::sin(D46_tmp_tmp_7);
  D46_tmp_tmp_0 *= 2.0;
  D45_tmp = std::sin(D46_tmp_tmp_0);
  w_a = std::sin((-rtU.InBus1_Positions[3] + rtU.InBus1_Positions[4]) * 2.0);
  D56_tmp_tmp_9 = (rtU.InBus1_Positions[3] + rtU.InBus1_Positions[4]) * 2.0;
  x_a = std::sin(D56_tmp_tmp_9);
  D56_tmp_tmp_6 = D46_tmp_tmp_1 * 2.0;
  D24_tmp = std::sin(D56_tmp_tmp_6);
  D56_tmp_tmp_1 = D46_tmp_tmp_2 * 2.0;
  ab_a = std::sin(D56_tmp_tmp_1);
  D24_tmp_0 = std::sin(D56_tmp_tmp_9 + rtU.InBus1_Positions[6]);
  D46_tmp_tmp_9 = D15_tmp_tmp + D56_tmp_tmp_4;
  D46_tmp_g = std::cos(D46_tmp_tmp_9);
  D47_tmp_0 = D15_tmp_tmp_0 + D56_tmp_tmp_4;
  D46_tmp_tmp_2 = std::cos(D47_tmp_0);
  D46_tmp_tmp_1 = std::cos(D46_tmp_tmp_7);
  D46_tmp_tmp_0 = std::cos(D46_tmp_tmp_0);
  D46_tmp_tmp = std::cos(D56_tmp_tmp_6);
  D56_tmp_tmp_1 = std::cos(D56_tmp_tmp_1);
  D15_tmp_tmp += rtb_ginv_tmp_tmp_0;
  D46_tmp_tmp_4 = std::cos(D15_tmp_tmp);
  D15_tmp_tmp_0 += rtb_ginv_tmp_tmp_0;
  D46_tmp_tmp_6 = std::cos(D15_tmp_tmp_0);
  D46_tmp_tmp_7 = std::sin(D46_tmp_tmp_7 + rtU.InBus1_Positions[7]);
  D46_tmp_tmp_8 = std::sin(D56_tmp_tmp_4 + rtU.InBus1_Positions[6]);
  D46_tmp_tmp_9 = std::sin(D46_tmp_tmp_9);
  D47_tmp_0 = std::sin(D47_tmp_0);
  D56_tmp_tmp_3 = std::sin(D56_tmp_tmp_3 + D56_tmp_tmp_4);
  D48_tmp = std::sin((rtU.InBus1_Positions[3] - rtU.InBus1_Positions[4]) * 2.0);
  D56_tmp_tmp = std::sin(rtb_ginv_tmp_tmp_0 + rtU.InBus1_Positions[6]);
  D15_tmp_tmp = std::sin(D15_tmp_tmp);
  D15_tmp_tmp_0 = std::sin(D15_tmp_tmp_0);
  D56_tmp_tmp_9 = std::sin(D56_tmp_tmp_9 + D14_tmp_tmp);
  D56_tmp_tmp_6 = std::sin(D56_tmp_tmp_6 + rtU.InBus1_Positions[7]);
  D56_tmp_tmp_2 = std::sin(D56_tmp_tmp_4 + rtU.InBus1_Positions[7]);
  D56_tmp_tmp_4 = std::sin(D14_tmp_tmp + D56_tmp_tmp_4);
  D56_tmp_tmp_7 = std::sin(rtb_ginv_tmp_tmp_0 + rtU.InBus1_Positions[7]);
  D14_tmp_tmp = std::sin(D14_tmp_tmp + rtb_ginv_tmp_tmp_0);
  rtb_ginv_tmp_tmp_0 = std::cos(rtb_ginv_tmp_tmp_0);
  D14_tmp_c = D14_tmp_c * D14_tmp_0 + D14_tmp_d * D14_tmp_4;
  D14_tmp_d = D14_tmp_a * s;
  D56_tmp_tmp_8 = 2.0 * D14_tmp_1;
  D56_tmp_tmp_5 = 0.09794 * rtU.InBus1_Velocities[7] * 0.143;
  D16_tmp_0 = D16_tmp_0 * D14_tmp_0 + D14_tmp_b;
  rtb_ginv_tmp_tmp = D16_tmp_0 * rtb_ginv_tmp_tmp_1;
  tmp_8 = D14_tmp_d * D14_tmp_0;
  tmp_9 = 2.0 * rtU.InBus1_Velocities[4];
  tmp_a = -2.0 * rtU.InBus1_Velocities[6];
  tmp_49 = -2.0 * D14_tmp_2;
  D14_tmp_d = (D14_tmp_d - D16_tmp_2) * D56_tmp_tmp_8 + D16_tmp_3 * tmp_49;
  D16_tmp_2 = ((rtU.InBus1_Positions[3] - rtU.InBus1_Positions[5]) +
               rtU.InBus1_Positions[6]) + rtU.InBus1_Positions[7];
  D16_tmp_3 = ((rtU.InBus1_Positions[3] + rtU.InBus1_Positions[5]) +
               rtU.InBus1_Positions[6]) + rtU.InBus1_Positions[7];
  tmp_g = 2.0 * rtU.InBus1_Velocities[6];
  tmp_i = 2.0 * s;
  tmp[24] = -(((((((D14_tmp_8 * smax - D14_tmp_e) * D14_tmp_1 + D14_tmp_c *
                   D14_tmp_2) * (tmp_g * D14_tmp_6) + ((tmp_i * D15_tmp_1 *
    D14_tmp_0 + (std::cos(D16_tmp_2) - std::cos(D16_tmp_3))) * D56_tmp_tmp_5 +
    tmp_9 * s * D15_tmp * D34_tmp_3)) + (D14_tmp_c * D14_tmp_1 + D14_tmp_f) *
                 (tmp_a * D14_tmp)) + ((D16_tmp_1 - tmp_8) * D56_tmp_tmp_8 +
    rtb_ginv_tmp_tmp) * rtU.InBus1_Velocities[3]) + D14_tmp_d *
               rtU.InBus1_Velocities[5]) * 0.5);
  tmp[32] = -((((D15_tmp_2 * rtU.InBus1_Velocities[5] * D15_tmp * smax +
                 D56_tmp_tmp_5 * s * D15_tmp * D34_tmp_0) +
                rtU.InBus1_Velocities[6] * s * D15_tmp * D37_tmp) +
               rtU.InBus1_Velocities[3] * s * D15_tmp * D34_tmp_3) +
              rtU.InBus1_Velocities[4] * s * D15_tmp_2 * D14_tmp_0);
  D14_tmp_c = -0.19588 * rtU.InBus1_Velocities[7] * 0.143;
  D14_tmp_8 = -D16_tmp * smax + tmp_8;
  D14_tmp_e = -2.0 * D14_tmp_1;
  tmp[40] = -(((((((D17_tmp_tmp_2 * D14_tmp_0 + D17_tmp_tmp) * -D14_tmp_a +
                   D27_tmp_0) + D27_tmp_1) * tmp_a + (D15_tmp_2 * tmp_9 *
    D15_tmp * smax + (D27_tmp * D14_tmp_5 + D17_tmp_tmp_0 * D14_tmp_7) *
    D14_tmp_c)) + (D14_tmp_8 * D14_tmp_e + rtb_ginv_tmp_tmp) *
                rtU.InBus1_Velocities[5]) + D14_tmp_d * rtU.InBus1_Velocities[3])
              * 0.5);
  D14_tmp_d = 0.09794 * rtU.InBus1_Velocities[4] * 0.143;
  rtb_ginv_tmp_tmp = rtU.InBus1_Velocities[3] + rtU.InBus1_Velocities[6];
  D17_tmp_tmp = rtU.InBus1_Velocities[5] * D14_tmp_0;
  D17_tmp_tmp_2 = 0.11464 * rtU.InBus1_Velocities[4] * 0.142 * D15_tmp;
  D14_tmp_f = rtU.InBus1_Velocities[4] * 0.17 * 0.143 * D15_tmp;
  D16_tmp = D14_tmp_d * D15_tmp;
  D16_tmp_1 = 2.0 * rtU.InBus1_Velocities[5];
  D27_tmp_0 = 0.09794 * rtU.InBus1_Velocities[3] * 0.143;
  D27_tmp_1 = rtU.InBus1_Velocities[6] + rtU.InBus1_Velocities[7];
  tmp_b = D27_tmp_1 * 2.0 + rtU.InBus1_Velocities[3];
  tmp_c = -2.0 * rtU.InBus1_Velocities[5];
  D14_tmp_3 *= D27_tmp_0;
  tmp_d = rtb_ginv_tmp_tmp - D17_tmp_tmp;
  tmp_e = rtb_ginv_tmp_tmp + rtU.InBus1_Velocities[7];
  tmp_f = tmp_e - D17_tmp_tmp;
  tmp_h = tmp_c * 0.040588879999999994;
  tmp_j = rtU.InBus1_Velocities[4] * 0.040588879999999994;
  tmp_k = tmp_c * D14_tmp_0 + tmp_b;
  tmp_1e = 0.22928 * rtU.InBus1_Velocities[5];
  tmp_1h = 0.19588 * rtU.InBus1_Velocities[5];
  tmp_2j = -2.0 * rtU.InBus1_Velocities[3];
  tmp[48] = -(((((((((((((((((D14_tmp_d * D14_tmp_7 * D15_tmp * D14_tmp_1 +
    tmp_j * D14_tmp_6 * D15_tmp * D14_tmp_1) + tmp_1e * 0.142 * D14_tmp_1 *
    D14_tmp) + D16_tmp_1 * 0.17 * 0.143 * D14_tmp_1 * D14_tmp) + D17_tmp_tmp_2 *
    D34_tmp) + D14_tmp_f * D34_tmp) + tmp_1h * 0.143 * D14_tmp_1 * D14_tmp_5) +
                        D16_tmp * D34_tmp_0) + -0.22928 * rtU.InBus1_Velocities
                       [3] * 0.142 * D14_tmp_1 * D14_tmp * D14_tmp_0) + -0.22928
                      * rtU.InBus1_Velocities[6] * 0.142 * D14_tmp_1 * D14_tmp *
                      D14_tmp_0) + tmp_2j * 0.17 * 0.143 * D14_tmp_1 * D14_tmp *
                     D14_tmp_0) + tmp_a * 0.17 * 0.143 * D14_tmp_1 * D14_tmp *
                    D14_tmp_0) + -0.19588 * rtU.InBus1_Velocities[3] * 0.143 *
                   D14_tmp_1 * D14_tmp_5 * D14_tmp_0) + -0.19588 *
                  rtU.InBus1_Velocities[6] * 0.143 * D14_tmp_1 * D14_tmp_5 *
                  D14_tmp_0) + D14_tmp_c * D14_tmp_1 * D14_tmp_5 * D14_tmp_0) *
                s + (tmp_f * D14_tmp_9 + tmp_d * D16_tmp_tmp) * (D56_tmp_tmp_8 *
    smax)) + ((((rtb_ginv_tmp_tmp * 2.0 * 0.040588879999999994 + D14_tmp_3) *
                D14_tmp_0 + tmp_h) * D14_tmp_6 + ((((D17_tmp_tmp_2 * D14_tmp +
    D14_tmp_f * D14_tmp) + D16_tmp * D14_tmp_5) - D27_tmp_0 * D14_tmp *
    D14_tmp_4 * D14_tmp_0) - (D16_tmp_1 - tmp_b * D14_tmp_0) * D14_tmp_9)) * s +
              ((rtU.InBus1_Velocities[3] * D14_tmp_6 * D14_tmp_4 + tmp_k *
                D14_tmp_5) * 0.01400542 + (tmp_d * 0.08117775999999999 +
    D14_tmp_3) * D14_tmp) * smax) * D14_tmp_2) * 0.5);
  D14_tmp_c = tmp_e * D14_tmp_0;
  tmp_a = rtU.InBus1_Velocities[4] * D15_tmp;
  D17_tmp_tmp_2 = 2.0 * D14_tmp_7;
  D14_tmp_f = rtU.InBus1_Velocities[5] - D14_tmp_c;
  tmp[56] = -(((((rtU.InBus1_Velocities[4] * D14_tmp_7 * D15_tmp * D14_tmp_1 +
                  tmp_a * D34_tmp_0) + D56_tmp_tmp_8 * D14_tmp_5 * D14_tmp_f) *
                s + D17_tmp_tmp_2 * D14_tmp_1 * smax * tmp_f) + (((D14_tmp_c -
    rtU.InBus1_Velocities[5]) * D17_tmp_tmp_2 + tmp_a * D14_tmp_5) * s + 2.0 *
    smax * D14_tmp_5 * tmp_f) * D14_tmp_2) * 0.00700271);
  D14_tmp_c = D15_tmp_tmp_1 + D15_tmp_tmp_2;
  D56_tmp_tmp_8 = tmp_a * smax;
  tmp_a = D14_tmp_c * rtU.InBus1_Velocities[6];
  tmp[25] = -(((((((((std::cos(D16_tmp_2 - rtU.InBus1_Positions[4]) - std::cos
                      (D16_tmp_3 - rtU.InBus1_Positions[4])) - std::cos
                     (D16_tmp_2 + rtU.InBus1_Positions[4])) + std::cos(D16_tmp_3
    + rtU.InBus1_Positions[4])) + std::sin(D16_tmp_2) * 2.0) + std::sin
                  (D16_tmp_3) * 2.0) * (-0.024485 * rtU.InBus1_Velocities[7] *
    0.143) + (-rtU.InBus1_Velocities[6] * s * D37_tmp + D34_tmp_3 *
              D56_tmp_tmp_8)) + tmp_a * smax * D14_tmp_0) + (D15_tmp_2 * smax *
    D14_tmp_0 + D34_tmp_3 * -s) * rtU.InBus1_Velocities[3]) + (D16_tmp_0 *
    D14_tmp_1 + D14_tmp_8 * D14_tmp_2) * rtU.InBus1_Velocities[5]);
  D16_tmp_0 = D15_tmp_2 * rtU.InBus1_Velocities[4];
  D16_tmp_2 = rtU.InBus1_Velocities[3] * D15_tmp;
  tmp[33] = -((((-rtU.InBus1_Velocities[5] * s * D15_tmp_2 * D15_tmp +
                 D56_tmp_tmp_5 * D15_tmp * smax * D34_tmp_0) +
                rtU.InBus1_Velocities[6] * D15_tmp * smax * D37_tmp) + D16_tmp_2
               * smax * D34_tmp_3) + D16_tmp_0 * smax * D14_tmp_0);
  D16_tmp_3 = rtU.InBus1_Velocities[5] - rtb_ginv_tmp_tmp * D14_tmp_0;
  D14_tmp_8 = (((tmp_g + rtU.InBus1_Velocities[3]) * 0.17 * 0.143 +
                rtb_ginv_tmp_tmp * 0.22928 * 0.142) + tmp_h * D14_tmp_0) +
    rtU.InBus1_Velocities[3] * 0.17 * 0.143 * rtb_ginv_tmp_5;
  D17_tmp_tmp_2 = 4.0 * rtU.InBus1_Velocities[5];
  D16_tmp = -4.0 * rtU.InBus1_Velocities[6];
  tmp_b = -4.0 * rtU.InBus1_Velocities[7];
  tmp[41] = -((((((((((-3.0 * rtU.InBus1_Velocities[3] + D16_tmp) + tmp_b) +
                     rtU.InBus1_Velocities[3] * rtb_ginv_tmp_tmp_0) +
                    D17_tmp_tmp_2 * D14_tmp_0) * (-0.00700271 * D14_tmp_7) +
                   (-rtU.InBus1_Velocities[5] * D14_tmp_0 +
                    rtU.InBus1_Velocities[3]) * 0.047378399999999994) +
                  D14_tmp_8 * D14_tmp_6) * smax + ((rtU.InBus1_Velocities[4] *
    0.08312 * 0.285 * D15_tmp + D16_tmp_3 * D14_tmp_tmp_0) + D14_tmp_f *
    D14_tmp_tmp_1) * tmp_i) * -D14_tmp_2 + ((((-rtU.InBus1_Velocities[3] *
    D14_tmp_0 + rtU.InBus1_Velocities[5]) * 0.023689199999999997 + D16_tmp_3 *
    D16_tmp_tmp) + D14_tmp_f * D14_tmp_9) * D14_tmp_1 + (D14_tmp_d * D15_tmp_1 *
    D15_tmp + tmp_j * D15_tmp_0 * D15_tmp)) * (-2.0 * s)) + (((rtb_ginv_tmp_5 *
    rtU.InBus1_Velocities[3] + tmp_k) * D14_tmp_tmp_1 + D14_tmp_8 * D14_tmp) *
    D14_tmp_1 + (-rtU.InBus1_Velocities[3] * 0.17 * 0.143 * D15_tmp_0 *
                 D17_tmp_3 - D27_tmp_0 * D15_tmp_1 * D17_tmp_3)) * smax) * 0.5);
  D14_tmp_d = D16_tmp_tmp + D14_tmp_9;
  tmp[49] = -((((D14_tmp_c * rtU.InBus1_Velocities[3] * smax * D14_tmp_0 +
                 (-rtU.InBus1_Velocities[3] * s * D37_tmp + D56_tmp_tmp_8 *
                  D37_tmp)) - (s * D34_tmp_0 - D15_tmp_1 * smax * D14_tmp_0) *
                D56_tmp_tmp_5) + (D14_tmp_c * smax * D14_tmp_0 + D37_tmp * -s) *
               rtU.InBus1_Velocities[6]) + ((D14_tmp_d * s * D14_tmp_0 +
    D14_tmp_b) * D14_tmp_1 + (-D14_tmp_d * smax + tmp_8) * D14_tmp_2) *
              rtU.InBus1_Velocities[5]);
  tmp[57] = -(((((tmp_e - rtU.InBus1_Velocities[4]) * D46_tmp_6 + D16_tmp_1 *
                 D15_tmp_1) - (tmp_e + rtU.InBus1_Velocities[4]) * D46_tmp_8) *
               smax + tmp_i * D34_tmp_0 * tmp_f) * -0.00700271);
  tmp[26] = -(((D56_tmp_tmp_5 * D15_tmp_1 * D15_tmp + tmp_a * D15_tmp) +
               D15_tmp_2 * rtU.InBus1_Velocities[3] * D15_tmp) - D34_tmp_3 *
              rtU.InBus1_Velocities[4] * D14_tmp_0);
  tmp[34] = -(((D16_tmp_0 * D15_tmp - D56_tmp_tmp_5 * D34_tmp_0 * D14_tmp_0) +
               D37_tmp * -rtU.InBus1_Velocities[6] * D14_tmp_0) - D34_tmp_3 *
              rtU.InBus1_Velocities[3] * D14_tmp_0);
  tmp[42] = -0.0;
  tmp[50] = -((tmp_e * 0.09794 * 0.143 * D15_tmp_1 * D15_tmp + rtb_ginv_tmp_tmp *
               0.040588879999999994 * D15_tmp_0 * D15_tmp) - D37_tmp *
              rtU.InBus1_Velocities[4] * D14_tmp_0);
  tmp[58] = -((tmp_e * D15_tmp_1 * D15_tmp - rtU.InBus1_Velocities[4] *
               D34_tmp_0 * D14_tmp_0) * 0.01400542);
  tmp[27] = -(-rtU.InBus1_Velocities[6] * 0.08312 * 0.040588879999999994 *
              D14_tmp - (D27_tmp_1 * 0.08312 * D14_tmp_5 +
    rtU.InBus1_Velocities[7] * 0.17 * D14_tmp_4) * 0.01400542);
  D14_tmp_c = rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * D14;
  D14_tmp_d = rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D14;
  D56_tmp_tmp_8 = 0.0009810686847999998 * D14;
  D56_tmp_tmp_5 = 0.0009879776191999998 * D14;
  D16_tmp_0 = rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D46_tmp_o;
  tmp_8 = rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D46_tmp_o;
  tmp_a = 0.0018662108031999999 * D46_tmp_o;
  D16_tmp_3 = 0.0041327000000000004 * D46_tmp_o;
  tmp_i = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D46_tmp_d;
  D14_tmp_8 = rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D46_tmp_d;
  D14_tmp_f = 0.0013716908347999998 * D46_tmp_d;
  D27_tmp_0 = D56_tmp_h * D46_tmp_1;
  D27_tmp_1 = rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D56_tmp_7;
  D14_tmp_3 = rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D56_tmp_7;
  tmp_h = 0.0018662108031999999 * D56_tmp_7;
  tmp_j = 0.0041327000000000004 * D56_tmp_7;
  tmp_k = 0.004761842800000001 * D27;
  D14_tmp_7 = D56_tmp_i * D46_tmp_2;
  D14_tmp_9 = 0.004761842800000001 * D35;
  D14_tmp_tmp_0 = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D56_tmp_8;
  D14_tmp_tmp_1 = rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D56_tmp_8;
  D14_tmp_b = 0.0013716908347999998 * D56_tmp_8;
  D15_tmp_tmp_1 = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    D15_tmp;
  D15_tmp_tmp_2 = 2.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    D15_tmp;
  D16_tmp_tmp = 0.0037324216063999997 * D15_tmp;
  D34_tmp_3 = 0.0027433816695999996 * D15_tmp;
  D37_tmp = 0.008265400000000001 * D15_tmp;
  rtb_ginv_tmp_5 = D56_tmp_j * D46_tmp_3;
  tmp_1q = rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D56_tmp_9;
  tmp_1r = rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D56_tmp_9;
  tmp_1s = 0.0018662108031999999 * D56_tmp_9;
  tmp_1t = 0.0041327000000000004 * D56_tmp_9;
  tmp_1u = 0.004761842800000001 * D37;
  tmp_1v = D56_tmp_k * D46_tmp_4;
  tmp_1w = 0.004761842800000001 * D46;
  tmp_1x = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D56_tmp_a;
  tmp_1y = rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D56_tmp_a;
  tmp_1z = 0.0013716908347999998 * D56_tmp_a;
  tmp_20 = D56_tmp_l * D46_tmp_5;
  tmp_21 = D46_tmp_f * D56_tmp_1;
  tmp_22 = D56_tmp_m * D46_tmp_6;
  tmp_23 = D46_tmp_e * D56_tmp_2;
  tmp_24 = D56_tmp_n * D46_tmp_7;
  tmp_25 = D46_tmp_f * D56_tmp_5;
  tmp_26 = D56_tmp_o * D46_tmp_8;
  tmp_27 = D46_tmp_e * D56_tmp_6;
  tmp_tmp = (rtConstP.MATLABFunction1_HexaConstants.Inertia[4] -
             rtConstP.MATLABFunction1_HexaConstants.Inertia[8]) +
    0.0019690463039999996;
  tmp_1p = ((((((((((((((((((((((((((((((((((((((((((((((((((((tmp_tmp * D25 +
    0.006747495411199999 * D17_tmp_5) + D27_tmp_0) + 0.0027062010112 * D16) +
    0.0040412944 * D16) - D27_tmp_1) + D14_tmp_3) + tmp_h) + tmp_j) + tmp_k) +
    0.0023282610207999996 * D17_tmp_2) + D14_tmp_7) + 0.0023282610207999996 *
    D34) + D14_tmp_9) - D14_tmp_tmp_0) + D14_tmp_tmp_1) + D14_tmp_b) +
    D15_tmp_tmp_1) + D15_tmp_tmp_2) + 2.0 *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[0] * D15_tmp) + D16_tmp_tmp)
    + 0.0019621373695999996 * D15_tmp) + D34_tmp_3) + 0.0019759552383999996 *
    D15_tmp) + D37_tmp) + rtConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    D17) - rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D17) +
    0.0009810686847999998 * D17) + 0.0009879776191999998 * D17) +
    0.0027062010112 * D18) + 0.0040412944 * D18) + rtb_ginv_tmp_5) +
    0.0027062010112 * D24) + 0.0040412944 * D24) - tmp_1q) + tmp_1r) + tmp_1s) +
    tmp_1t) + tmp_1u) + 0.0023282610207999996 * D38) + tmp_1v) +
                       0.0023282610207999996 * D46_tmp_tmp_5) + tmp_1w) - tmp_1x)
                    + tmp_1y) + tmp_1z) + tmp_20) + tmp_21) + tmp_22) + tmp_23)
              + tmp_24) + tmp_25) + tmp_26) + tmp_27;
  tmp_4k = D56_tmp_f * D46_tmp_a + D56_tmp_g * D46_tmp_c;
  tmp_4l = 0.004761842800000001 * D56_tmp_tmp_0;
  tmp[35] = -(((((((((((((((((tmp_4k + D14_tmp_c) - D14_tmp_d) + D56_tmp_tmp_8)
    + D56_tmp_tmp_5) - D16_tmp_0) + tmp_8) + tmp_a) + D16_tmp_3) +
                      0.0027062010112 * D15) + 0.0040412944 * D15) - tmp_i) +
                   D14_tmp_8) + D14_tmp_f) + 0.0023282610207999996 * D47) +
                tmp_4l) * tmp_9 + tmp_1p * -rtU.InBus1_Velocities[5]) * 0.25);
  tmp_l = -2.0 * rtU.InBus1_Velocities[4];
  tmp_m = tmp_l * 0.0069089343999999995;
  tmp_n = -4.0 * rtU.InBus1_Velocities[4];
  tmp_o = -0.45856 * rtU.InBus1_Velocities[4] * 0.08312 * 0.142;
  tmp_tmp_0 = tmp_n * 0.08312 * 0.17 * 0.143;
  tmp_p = -0.39176 * rtU.InBus1_Velocities[4];
  tmp_q = tmp_p * 0.08312 * 0.143;
  tmp_p = tmp_p * 0.17 * 0.143;
  tmp_r = tmp_n * 0.0069089343999999995;
  tmp_s = tmp_l * rtConstP.MATLABFunction1_HexaConstants.Inertia[4];
  tmp_t = tmp_9 * rtConstP.MATLABFunction1_HexaConstants.Inertia[8];
  tmp_u = tmp_m * 0.142;
  tmp_m *= 0.143;
  tmp_v = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  tmp_w = tmp_9 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  tmp_x = tmp_l * rtConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  tmp_y = -0.0262846592 * rtU.InBus1_Velocities[4] * 0.142;
  tmp_z = tmp_l * 0.028900000000000006 * 0.143;
  tmp_10 = 4.0 * rtU.InBus1_Velocities[4];
  tmp_11 = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  tmp_tmp_1 = tmp_9 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  tmp_tmp_2 = tmp_l * rtConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  tmp_tmp_3 = -0.0191844872 * rtU.InBus1_Velocities[4] * 0.143;
  tmp_12 = tmp_c * 0.0069089343999999995;
  tmp_13 = -0.39176 * rtU.InBus1_Velocities[5];
  tmp_14 = -0.19588 * rtU.InBus1_Velocities[5];
  tmp_15 = rtU.InBus1_Velocities[5] * 0.0069089343999999995;
  tmp_16 = rtConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    rtU.InBus1_Velocities[5];
  tmp_tmp_m = rtU.InBus1_Velocities[5] *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[8];
  tmp_17 = tmp_15 * 0.142;
  tmp_15 *= 0.143;
  tmp_tmp_16 = rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    rtU.InBus1_Velocities[5];
  tmp_tmp_n = rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    rtU.InBus1_Velocities[5];
  tmp_tmp_p = 0.0131423296 * rtU.InBus1_Velocities[5] * 0.142;
  tmp_18 = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  tmp_tmp_q = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    rtU.InBus1_Velocities[5];
  tmp_tmp_r = rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    rtU.InBus1_Velocities[5];
  tmp_tmp_4 = 0.0095922436 * rtU.InBus1_Velocities[5] * 0.143;
  tmp_19 = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  tmp_1a = -0.22928 * rtU.InBus1_Velocities[5] * 0.08312 * 0.142;
  tmp_1b = tmp_c * 0.08312;
  tmp_1c = tmp_14 * 0.08312 * 0.143;
  tmp_14 = tmp_14 * 0.17 * 0.143;
  tmp_1d = 0.17 * D14_tmp_4 + 0.08312 * D14_tmp_5;
  tmp_1f = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  tmp_1g = rtU.InBus1_Velocities[5] * 0.028900000000000006 * 0.143;
  tmp_1i = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  tmp_1j = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  tmp_1k = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  tmp_1l = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  tmp_1m = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  tmp_1n = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  tmp_1o = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  tmp_2i = tmp_s * D25;
  tmp_2k = tmp_t * D25;
  tmp_2l = tmp_u * D25;
  tmp_2m = tmp_m * D25;
  tmp_32 = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  tmp_2n = tmp_32 * D46_tmp_1;
  tmp_2o = tmp_v * D46_tmp_tmp_1;
  tmp_2p = tmp_o * D16;
  tmp_2q = tmp_tmp_0 * D16;
  tmp_2r = tmp_w * D56_tmp_7;
  tmp_2s = tmp_x * D56_tmp_7;
  tmp_2t = tmp_y * D56_tmp_7;
  tmp_2u = tmp_z * D56_tmp_7;
  tmp_33 = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  tmp_2v = tmp_33 * D46_tmp_2;
  tmp_2w = tmp_11 * D46_tmp_tmp_0;
  tmp_2x = tmp_q * D34;
  tmp_2y = tmp_p * D35;
  tmp_2z = tmp_tmp_1 * D56_tmp_8;
  tmp_30 = tmp_tmp_2 * D56_tmp_8;
  tmp_31 = tmp_tmp_3 * D56_tmp_8;
  tmp_34 = tmp_14 * D46_tmp_tmp_7;
  tmp_35 = tmp_1b * 0.17 * 0.143;
  tmp_36 = -4.0 * rtU.InBus1_Velocities[5];
  tmp_37 = tmp_1a * D56;
  tmp_38 = tmp_1c * D56_tmp_tmp_3;
  tmp_39 = tmp_tmp_m * D48_tmp;
  tmp_3z = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  tmp_3a = tmp_3z * D46_tmp_5;
  tmp_3b = tmp_tmp_16 * D57;
  tmp_3c = tmp_tmp_n * D57;
  tmp_3d = tmp_tmp_p * D57;
  tmp_3e = tmp_1g * D57;
  tmp_3f = tmp_18 * D56_tmp_1;
  tmp_44 = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  tmp_3g = tmp_44 * D46_tmp_6;
  tmp_3h = tmp_tmp_q * D45_tmp;
  tmp_3i = tmp_tmp_r * D45_tmp;
  tmp_3j = tmp_tmp_4 * D45_tmp;
  tmp_3k = tmp_19 * D56_tmp_2;
  tmp_3l = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  tmp_3m = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  tmp_3n = tmp_c * rtConstP.MATLABFunction1_HexaConstants.Inertia[4];
  tmp_3s = tmp_16 * w_a;
  tmp_3t = tmp_17 * w_a;
  tmp_3u = tmp_15 * w_a;
  tmp_3v = tmp_16 * x_a;
  tmp_3w = tmp_tmp_m * x_a;
  tmp_3x = tmp_17 * x_a;
  tmp_3y = tmp_15 * x_a;
  tmp_40 = tmp_tmp_16 * D24_tmp;
  tmp_41 = tmp_tmp_n * D24_tmp;
  tmp_42 = tmp_tmp_p * D24_tmp;
  tmp_45 = tmp_tmp_q * ab_a;
  tmp_46 = tmp_tmp_r * ab_a;
  tmp_47 = tmp_tmp_4 * ab_a;
  tmp_4a = tmp_p * D27;
  tmp_4b = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] * D15_tmp;
  tmp_4c = tmp_n * rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] * D15_tmp;
  tmp_4d = -0.0525693184 * rtU.InBus1_Velocities[4] * 0.142 * D15_tmp;
  tmp_4e = -0.0383689744 * rtU.InBus1_Velocities[4] * 0.143 * D15_tmp;
  tmp_4f = tmp_n * 0.028900000000000006 * 0.143 * D15_tmp;
  tmp_4g = tmp_p * D37;
  tmp_58 = D17_tmp_tmp_2 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3] *
    D46_tmp_c;
  tmp_59 = tmp_1m * D46_tmp_tmp_2;
  tmp_4m = ((D17_tmp_tmp_2 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3] *
             D46_tmp_a + tmp_58) + tmp_1l * D46_tmp_g) + tmp_59;
  tmp_4n = tmp_v * D46_tmp_tmp;
  tmp_4o = tmp_11 * D56_tmp_tmp_1;
  tmp_4p = tmp_1n * D46_tmp_tmp_4;
  tmp_4q = tmp_1o * D46_tmp_tmp_6;
  tmp_4r = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    D46_tmp_o;
  tmp_4s = tmp_3l * D46_tmp_o;
  tmp_4t = -0.0262846592 * rtU.InBus1_Velocities[5] * 0.142 * D46_tmp_o;
  tmp_4u = tmp_c * 0.028900000000000006;
  tmp_1b = tmp_1b * 0.17 * 0.143;
  tmp_4v = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    D46_tmp_d;
  tmp_4w = tmp_3m * D46_tmp_d;
  tmp_4x = -0.0191844872 * rtU.InBus1_Velocities[5] * 0.143 * D46_tmp_d;
  tmp_4y = tmp_13 * 0.17 * 0.143 * D56_tmp_tmp_0;
  tmp_4z = tmp_1j * D46_tmp_tmp_9;
  tmp_50 = tmp_1k * D47_tmp_0;
  tmp_51 = 0.78352 * rtU.InBus1_Velocities[7];
  tmp_54 = tmp_1f * D15_tmp_tmp;
  tmp_55 = tmp_1i * D15_tmp_tmp_0;
  tmp_56 = tmp_14 * D56_tmp_tmp_6;
  tmp[43] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    ((((((((((((((((((((((((((((((((((((((((tmp_4m + tmp_2i) + tmp_2k) + tmp_2l)
    + tmp_2m) + tmp_o * D17_tmp_5) + tmp_tmp_0 * D17_tmp_5) + tmp_2n) + tmp_2o)
    + tmp_2p) + tmp_2q) + tmp_2r) + tmp_2s) + tmp_2t) + tmp_2u) + tmp_4a) +
    tmp_q * D17_tmp_2) + tmp_2v) + tmp_2w) + tmp_2x) + tmp_2y) + tmp_2z) +
    tmp_30) + tmp_31) + tmp_4b) + tmp_4c) + tmp_n *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[0] * D15_tmp) + tmp_4d) +
    tmp_r * 0.142 * D15_tmp) + tmp_4e) + tmp_r * 0.143 * D15_tmp) + tmp_4f) +
    tmp_s * D17) + tmp_t * D17) + tmp_u * D17) + tmp_m * D17) + tmp_o * D18) +
    tmp_tmp_0 * D18) + tmp_10 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7]
    * D46_tmp_3) + tmp_4n) + tmp_o * D24) + tmp_tmp_0 * D24) + tmp_w * D56_tmp_9)
    + tmp_x * D56_tmp_9) + tmp_y * D56_tmp_9) + tmp_z * D56_tmp_9) + tmp_4g) +
    tmp_q * D38) + tmp_10 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    D46_tmp_4) + tmp_4o) + tmp_q * D46_tmp_tmp_5) + tmp_p * D46) + tmp_tmp_1 *
    D56_tmp_a) + tmp_tmp_2 * D56_tmp_a) + tmp_tmp_3 * D56_tmp_a) + tmp_4p) +
    tmp_4q) + tmp_3n * D14) + D16_tmp_1 *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D14) + tmp_12 * 0.142 *
    D14) + tmp_12 * 0.143 * D14) + tmp_4r) + tmp_4s) + tmp_4t) + tmp_4u * 0.143 *
    D46_tmp_o) + -0.45856 * rtU.InBus1_Velocities[5] * 0.08312 * 0.142 * D15) +
    tmp_36 * 0.08312 * 0.17 * 0.143 * D15) + tmp_4v) + tmp_4w) + tmp_4x) +
    tmp_13 * 0.08312 * 0.143 * D47) + tmp_4y) + tmp_34) + tmp_4z) + tmp_37) +
    tmp_1b * D56) + tmp_50) + tmp_38) + tmp_39) + tmp_3a) + tmp_3b) - tmp_3c) -
    tmp_3d) - tmp_3e) + tmp_3f) + tmp_3g) + tmp_3h) - tmp_3i) - tmp_3j) + tmp_3k)
    + tmp_51 * 0.143 * tmp_1d * D14_tmp_0) + 8.0 * rtU.InBus1_Velocities[6] *
    0.08312 * D14_tmp_a * D14_tmp_0) + tmp_3s) + tmp_3t) + tmp_3u) - tmp_3v) +
    tmp_3w) - tmp_3x) - tmp_3y) + tmp_10 *
                       rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
                       D46_tmp_7) + tmp_40) - tmp_41) - tmp_42) +
                   -rtU.InBus1_Velocities[5] * 0.028900000000000006 * 0.143 *
                   D24_tmp) + tmp_18 * D56_tmp_5) + tmp_10 *
                 rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D46_tmp_8)
                + tmp_45) - tmp_46) - tmp_47) + tmp_19 * D56_tmp_6) + tmp_54) +
           tmp_55) + tmp_1a * D24_tmp_0) + tmp_35 * D24_tmp_0) + tmp_1c *
        D56_tmp_tmp_9) + tmp_56) * 0.125);
  tmp_n = -0.09794 * rtU.InBus1_Velocities[7];
  tmp_r = D14_tmp_a * 0.08312;
  tmp[51] = -(tmp_n * 0.143 * tmp_1d - tmp_r * tmp_d);
  tmp[59] = -(tmp_1d * -0.01400542 * tmp_f);
  tmp_1e = tmp_1e * 0.08312 * 0.142;
  tmp_12 = D16_tmp_1 * 0.08312;
  tmp_13 = tmp_12 * 0.17 * 0.143;
  tmp_18 = tmp_1h * 0.08312 * 0.143;
  tmp_1h = tmp_1h * 0.17 * 0.143;
  tmp_19 = D16_tmp_1 * 0.0069089343999999995;
  D14_tmp_a = -4.0 * rtU.InBus1_Velocities[3];
  tmp_48 = tmp_10 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  tmp_tmp_o = tmp_48 * D46_tmp_c;
  tmp_2e = 4.0 * rtU.InBus1_Velocities[3];
  tmp_43 = tmp_10 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  tmp_4h = tmp_2e * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  tmp_4i = 4.0 * rtU.InBus1_Velocities[7];
  tmp_4j = 4.0 * rtU.InBus1_Velocities[6];
  rtb_ginv_tmp_tmp = ((((rtb_ginv_tmp_tmp * 4.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] * D15_tmp_0 + tmp_43 *
    D46_tmp_a) + tmp_4h * D15_tmp_1) + tmp_4j *
                       rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
                       D15_tmp_1) + tmp_4i *
                      rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
                      D15_tmp_1) + tmp_tmp_o;
  tmp_tmp_s = tmp_1f * D46_tmp_1;
  tmp_tmp_t = tmp_tmp_16 * D56_tmp_7;
  tmp_tmp_u = tmp_tmp_n * D56_tmp_7;
  tmp_tmp_v = tmp_tmp_p * D56_tmp_7;
  tmp_tmp_w = tmp_1g * D56_tmp_7;
  tmp_tmp_x = tmp_1h * D27;
  tmp_tmp_y = tmp_1i * D46_tmp_2;
  tmp_tmp_z = tmp_1h * D35;
  tmp_tmp_10 = tmp_tmp_q * D56_tmp_8;
  tmp_tmp_11 = tmp_tmp_r * D56_tmp_8;
  tmp_tmp_12 = tmp_tmp_4 * D56_tmp_8;
  tmp_tmp_13 = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    D15_tmp;
  tmp_tmp_14 = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    D15_tmp;
  tmp_3o = 0.0262846592 * rtU.InBus1_Velocities[5] * 0.142;
  tmp_tmp_15 = tmp_3o * D15_tmp;
  tmp_3q = 0.0191844872 * rtU.InBus1_Velocities[5] * 0.143;
  tmp_tmp_17 = tmp_3q * D15_tmp;
  tmp_3r = D16_tmp_1 * 0.028900000000000006 * 0.143;
  tmp_tmp_5 = tmp_3r * D15_tmp;
  tmp_tmp_6 = tmp_1j * D46_tmp_3;
  tmp_tmp_16 *= D56_tmp_9;
  tmp_tmp_n *= D56_tmp_9;
  tmp_tmp_p *= D56_tmp_9;
  tmp_tmp_7 = tmp_1g * D56_tmp_9;
  tmp_tmp_8 = tmp_1h * D37;
  tmp_tmp_9 = tmp_1k * D46_tmp_4;
  tmp_tmp_a = tmp_1h * D46;
  tmp_tmp_q *= D56_tmp_a;
  tmp_tmp_r *= D56_tmp_a;
  tmp_tmp_4 *= D56_tmp_a;
  tmp_tmp_b = D14_tmp_a * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    D34_tmp;
  tmp_tmp_c = D16_tmp * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    D34_tmp;
  tmp_w *= D46_tmp_o;
  tmp_x *= D46_tmp_o;
  tmp_y *= D46_tmp_o;
  tmp_z *= D46_tmp_o;
  tmp_tmp_d = D14_tmp_a * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    D34_tmp_0;
  tmp_tmp_e = D16_tmp * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    D34_tmp_0;
  tmp_tmp_f = tmp_b * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    D34_tmp_0;
  tmp_tmp_1 *= D46_tmp_d;
  tmp_tmp_2 *= D46_tmp_d;
  tmp_tmp_3 *= D46_tmp_d;
  tmp_p *= D56_tmp_tmp_0;
  tmp_tmp_g = tmp_1l * D46_tmp_5;
  tmp_tmp_h = tmp_v * D56_tmp_1;
  tmp_tmp_i = tmp_1m * D46_tmp_6;
  tmp_tmp_j = tmp_11 * D56_tmp_2;
  tmp_tmp_k = tmp_1n * D46_tmp_7;
  tmp_v *= D56_tmp_5;
  tmp_tmp_l = tmp_1o * D46_tmp_8;
  tmp_11 *= D56_tmp_6;
  tmp_3p = tmp_19 * 0.142;
  tmp_19 *= 0.143;
  tmp[28] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((tmp_16 * D25 + rtb_ginv_tmp_tmp) - tmp_tmp_m * D25) + tmp_17 * D25) +
    tmp_15 * D25) + tmp_1e * D17_tmp_5) + tmp_13 * D17_tmp_5) + tmp_tmp_s) +
    tmp_1e * D16) + tmp_13 * D16) - tmp_tmp_t) + tmp_tmp_u) + tmp_tmp_v) +
    tmp_tmp_w) + tmp_tmp_x) + tmp_18 * D17_tmp_2) + tmp_tmp_y) + tmp_18 * D34) +
    tmp_tmp_z) - tmp_tmp_10) + tmp_tmp_11) + tmp_tmp_12) + tmp_tmp_13) +
    tmp_tmp_14) + D16_tmp_1 * rtConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    D15_tmp) + tmp_tmp_15) + tmp_3p * D15_tmp) + tmp_tmp_17) + tmp_19 * D15_tmp)
    + tmp_tmp_5) + tmp_16 * D17) - tmp_tmp_m * D17) + tmp_17 * D17) + tmp_15 *
    D17) + tmp_1e * D18) + tmp_13 * D18) + tmp_tmp_6) + tmp_1e * D24) + tmp_12 *
    0.17 * 0.143 * D24) - tmp_tmp_16) + tmp_tmp_n) + tmp_tmp_p) + tmp_tmp_7) +
    tmp_tmp_8) + tmp_18 * D38) + tmp_tmp_9) + tmp_18 * D46_tmp_tmp_5) +
    tmp_tmp_a) - tmp_tmp_q) + tmp_tmp_r) + tmp_tmp_4) + tmp_s * D14) + tmp_t *
    D14) + tmp_u * D14) + tmp_m * D14) + tmp_tmp_b) + tmp_tmp_c) + tmp_w) +
    tmp_x) + tmp_y) + tmp_z) + tmp_o * D15) + tmp_tmp_0 * D15) + tmp_tmp_d) +
                     tmp_tmp_e) + tmp_tmp_f) + tmp_tmp_1) + tmp_tmp_2) +
                 tmp_tmp_3) + tmp_q * D47) + tmp_p) + tmp_tmp_g) + tmp_tmp_h) +
            tmp_tmp_i) + tmp_tmp_j) + tmp_tmp_k) + tmp_v) + tmp_tmp_l) + tmp_11)
      * 0.25);
  tmp_m = D46_tmp_f * D46_tmp_a + D46_tmp_e * D46_tmp_c;
  tmp_o = -0.004761842800000001 * D56_tmp_tmp_0;
  tmp_tmp_0 = 2.0 * rtU.InBus1_Velocities[7];
  tmp_q = 0.0013531005056 * D14_tmp;
  tmp_s = 0.0020206472 * D15;
  tmp_t = 0.0011641305103999998 * D14_tmp_5;
  tmp_u = 0.0011641305103999998 * D47;
  tmp_12 = (rtb_ginv_tmp_4 + 0.0013716908347999998) * D15_tmp_1 +
    (0.0011641305103999998 * D14_tmp_2 + 0.0023809214000000004 * D15_tmp_0);
  tmp[36] = -((((((((((((((((((tmp_m - D14_tmp_c) + D14_tmp_d) - D56_tmp_tmp_8)
    - D56_tmp_tmp_5) + D16_tmp_0) - tmp_8) - tmp_a) - D16_tmp_3) +
                       -0.0027062010112 * D15) + -0.0040412944 * D15) + tmp_i) -
                    D14_tmp_8) - D14_tmp_f) + -0.0023282610207999996 * D47) +
                 tmp_o) * rtU.InBus1_Velocities[3] + (-2.0 *
    rtU.InBus1_Velocities[7] * tmp_12 * D34_tmp_0 + tmp_tmp_0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[3] * D46_tmp_c)) +
               ((((((((((((((tmp_m - tmp_q) + -0.0020206472 * D14_tmp) +
    D16_tmp_0) - tmp_8) - tmp_a) - D16_tmp_3) + -0.0013531005056 * D15) - tmp_s)
                     - tmp_t) + tmp_i) - D14_tmp_8) - D14_tmp_f) - tmp_u) +
                tmp_o) * rtU.InBus1_Velocities[6]) * 0.5);
  D14_tmp_c = 4.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  D14_tmp_d = 4.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  D56_tmp_tmp_8 = -4.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  D56_tmp_tmp_5 = -4.0 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  tmp_m = 0.0011641305103999998 * D17_tmp_2;
  tmp_o = 0.0011641305103999998 * D34;
  tmp_15 = 0.0011641305103999998 * D38;
  tmp_16 = 0.0011641305103999998 * D46_tmp_tmp_5;
  tmp_tmp_m = 0.0033737477055999993 * D17_tmp_5;
  tmp_17 = 0.0013531005056 * D18;
  tmp_2f = 0.0020206472 * D18;
  tmp_2g = 0.0023809214000000004 * D27 + tmp_m;
  tmp_2h = 0.0023809214000000004 * D37;
  D27_tmp_0 = ((D27_tmp_0 + tmp_tmp_m) + 0.0013531005056 * D16) + 0.0020206472 *
    D16;
  tmp_52 = 0.0013531005056 * D24;
  tmp_53 = 0.0020206472 * D24;
  D27_tmp_1 = (((((((((((((((((((((((((((((((((((((((((D27_tmp_0 - D27_tmp_1) +
    D14_tmp_3) + tmp_h) + tmp_j) + tmp_k) + tmp_m) + D14_tmp_7) + tmp_o) +
    D14_tmp_9) - D14_tmp_tmp_0) + D14_tmp_tmp_1) + D14_tmp_b) + D15_tmp_tmp_1) +
    D15_tmp_tmp_2) + D16_tmp_tmp) + D34_tmp_3) + D37_tmp) + tmp_17) + tmp_2f) +
    rtb_ginv_tmp_5) + tmp_52) + tmp_53) - tmp_1q) + tmp_1r) + tmp_1s) + tmp_1t)
    + tmp_1u) + tmp_15) + tmp_1v) + tmp_16) + tmp_1w) - tmp_1x) + tmp_1y) +
                      tmp_1z) + tmp_20) + tmp_21) + tmp_22) + tmp_23) + tmp_24)
                + tmp_25) + tmp_26) + tmp_27;
  tmp_57 = (((((((((((((((((((tmp_2g + D14_tmp_7) + tmp_o) +
    0.0023809214000000004 * D35) - D14_tmp_tmp_0) + D14_tmp_tmp_1) + D14_tmp_b)
                        + D15_tmp_tmp_2) + D34_tmp_3) + tmp_2h) + tmp_15) +
                    tmp_1v) + tmp_16) + 0.0023809214000000004 * D46) - tmp_1x) +
                tmp_1y) + tmp_1z) + tmp_22) + tmp_23) + tmp_26) + tmp_27;
  tmp[44] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((D14_tmp_c *
    D46_tmp_g + D14_tmp_d * D46_tmp_tmp_2) + D46_tmp_f * D46_tmp_tmp_1) +
    D46_tmp_e * D46_tmp_tmp_0) + D56_tmp_f * D46_tmp_tmp) + D56_tmp_g *
    D56_tmp_tmp_1) + D14_tmp_c * D46_tmp_tmp_4) + D14_tmp_d * D46_tmp_tmp_6) +
    -0.004761842800000001 * D46_tmp_tmp_7) + -0.0027062010112 * D46_tmp_tmp_8) +
    -0.0040412944 * D46_tmp_tmp_8) + D56_tmp_tmp_8 * D46_tmp_tmp_9) +
    -0.0027062010112 * D56) + -0.0040412944 * D56) + -0.004761842800000001 *
    D56_tmp_tmp_2) + -0.0023282610207999996 * D56_tmp_tmp_4) + D56_tmp_tmp_5 *
    D47_tmp_0) + -0.0023282610207999996 * D56_tmp_tmp_3) +
    rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D48_tmp) +
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D57) -
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D57) -
    0.0018662108031999999 * D57) - 0.0041327000000000004 * D57) +
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D45_tmp) -
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D45_tmp) +
    -0.0013716908347999998 * D45_tmp) + -2.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D46_tmp_k) + -2.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] * D46_tmp_k) + 4.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] * D46_tmp_k) + -2.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D46_tmp_k) + -2.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * D46_tmp_k) + 4.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] * D46_tmp_k) + 4.0 *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[0] * D46_tmp_k) + -2.0 *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * D46_tmp_k) + -2.0 *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D46_tmp_k) +
    0.0037324216063999997 * D46_tmp_k) + 0.0019621373695999996 * D46_tmp_k) +
    0.0027433816695999996 * D46_tmp_k) + 0.0019759552383999996 * D46_tmp_k) +
    0.008265400000000001 * D46_tmp_k) +
    rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * w_a) +
    0.0009810686847999998 * w_a) + 0.0009879776191999998 * w_a) +
    rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * x_a) -
    rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * x_a) +
    0.0009810686847999998 * x_a) + 0.0009879776191999998 * x_a) -
                        rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
                        D24_tmp) +
                       rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
                       D24_tmp) + 0.0018662108031999999 * D24_tmp) +
                     0.0041327000000000004 * D24_tmp) -
                    rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * ab_a) +
                   rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] * ab_a) +
                  0.0013716908347999998 * ab_a) + 0.0027062010112 * D56_tmp_tmp)
                + 0.0040412944 * D56_tmp_tmp) + D56_tmp_tmp_8 * D15_tmp_tmp) +
              0.004761842800000001 * D56_tmp_tmp_7) + 0.0023282610207999996 *
             D14_tmp_tmp) + D56_tmp_tmp_5 * D15_tmp_tmp_0) + 0.0027062010112 *
           D24_tmp_0) + 0.0040412944 * D24_tmp_0) + 0.0023282610207999996 *
         D56_tmp_tmp_9) + 0.004761842800000001 * D56_tmp_tmp_6) * (-0.5 *
        rtU.InBus1_Velocities[5]) + ((D27_tmp_1 * rtU.InBus1_Velocities[6] +
         tmp_57 * rtU.InBus1_Velocities[7]) + tmp_1p * rtU.InBus1_Velocities[3]))
      * 0.25);
  D48_tmp = 0.11464 * rtU.InBus1_Velocities[5];
  D14_tmp_c = D48_tmp * 0.08312 * 0.142;
  D14_tmp_d = rtU.InBus1_Velocities[5] * 0.08312 * 0.17;
  D56_tmp_tmp_8 = D14_tmp_d * 0.143;
  D56_tmp_tmp_5 = 0.09794 * rtU.InBus1_Velocities[5];
  tmp_1p = D56_tmp_tmp_5 * 0.08312 * 0.143;
  ab_a = -0.22928 * rtU.InBus1_Velocities[4] * 0.08312 * 0.142;
  D57 = tmp_l * 0.08312 * 0.17 * 0.143;
  x_a = -0.19588 * rtU.InBus1_Velocities[4];
  w_a = x_a * 0.08312 * 0.143;
  tmp_28 = tmp_1p * D17_tmp_2;
  tmp_29 = tmp_1p * D34;
  tmp_2a = tmp_1p * D38;
  tmp_2b = tmp_1p * D46_tmp_tmp_5;
  tmp_2c = w_a * D14_tmp_5;
  tmp_2d = w_a * D47;
  D48_tmp = D48_tmp * 0.08312 * 0.142;
  tmp[52] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((D14_tmp_c
    * D17_tmp_5 + rtb_ginv_tmp_tmp) + D56_tmp_tmp_8 * D17_tmp_5) + tmp_tmp_s) +
    D14_tmp_c * D16) + D56_tmp_tmp_8 * D16) - tmp_tmp_t) + tmp_tmp_u) +
    tmp_tmp_v) + tmp_tmp_w) + tmp_tmp_x) + tmp_28) + tmp_tmp_y) + tmp_29) +
    tmp_tmp_z) - tmp_tmp_10) + tmp_tmp_11) + tmp_tmp_12) + tmp_tmp_13) +
    tmp_tmp_14) + tmp_tmp_15) + tmp_tmp_17) + tmp_tmp_5) + D14_tmp_c * D18) +
    D14_tmp_d * 0.143 * D18) + tmp_tmp_6) + D48_tmp * D24) + D56_tmp_tmp_8 * D24)
    - tmp_tmp_16) + tmp_tmp_n) + tmp_tmp_p) + tmp_tmp_7) + tmp_tmp_8) + tmp_2a)
    + tmp_tmp_9) + tmp_2b) + tmp_tmp_a) - tmp_tmp_q) + tmp_tmp_r) + tmp_tmp_4) +
    ab_a * D14_tmp) + D57 * D14_tmp) + tmp_tmp_b) + tmp_tmp_c) + tmp_w) + tmp_x)
    + tmp_y) + tmp_z) + ab_a * D15) + D57 * D15) + tmp_2c) + tmp_tmp_d) +
                     tmp_tmp_e) + tmp_tmp_f) + tmp_tmp_1) + tmp_tmp_2) +
                 tmp_tmp_3) + tmp_2d) + tmp_p) + tmp_tmp_g) + tmp_tmp_h) +
            tmp_tmp_i) + tmp_tmp_j) + tmp_tmp_k) + tmp_v) + tmp_tmp_l) + tmp_11)
      * 0.25);
  D14_tmp_d = D56_tmp_tmp_5 * 0.17 * 0.143;
  D56_tmp_tmp_5 = x_a * 0.17 * 0.143;
  tmp[60] = -((((((((((((((((((((((((((((((((((tmp_e * 4.0 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D15_tmp_1 + tmp_tmp_o) +
    D14_tmp_d * D27) + tmp_28) + tmp_tmp_y) + tmp_29) + D14_tmp_d * D35) -
    tmp_tmp_10) + tmp_tmp_11) + tmp_tmp_12) + tmp_tmp_14) + tmp_tmp_17) +
    D14_tmp_d * D37) + tmp_2a) + tmp_tmp_9) + tmp_2b) + D14_tmp_d * D46) -
    tmp_tmp_q) + tmp_tmp_r) + tmp_tmp_4) + D56_tmp_tmp_5 * D14_tmp_4) + tmp_2c)
    + tmp_tmp_d) + tmp_tmp_e) + tmp_tmp_f) + tmp_tmp_1) + tmp_tmp_2) + tmp_tmp_3)
                    + tmp_2d) + D56_tmp_tmp_5 * D56_tmp_tmp_0) + tmp_tmp_i) +
                 tmp_tmp_j) + tmp_tmp_l) + tmp_11) * 0.25);
  rtb_ginv_tmp_tmp = rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    D46_tmp_2;
  tmp_e = rtConstP.MATLABFunction1_ArmConstants.Inertia2[7] * D46_tmp_4;
  tmp_p = rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D46_tmp_6;
  tmp_v = rtConstP.MATLABFunction1_ArmConstants.Inertia2[6] * D46_tmp_8;
  tmp_w = D56_tmp_g * D46_tmp_d;
  tmp_x = -0.004761842800000001 * D46_tmp_tmp_3;
  tmp_y = D56_tmp_f * D46_tmp_o;
  tmp_z = rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D56_tmp_6;
  tmp_11 = (tmp_2g + rtb_ginv_tmp_tmp) - tmp_2h;
  rtb_ginv_tmp_tmp = (((((((((((rtConstP.MATLABFunction1_ArmConstants.Inertia1[7]
    * D46_tmp_1 + tmp_tmp_m) + tmp_m) + rtb_ginv_tmp_tmp) - tmp_17) - tmp_2f) +
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[7] * D46_tmp_3) - tmp_15) +
    tmp_e) + rtConstP.MATLABFunction1_ArmConstants.Inertia1[6] * D46_tmp_5) +
                       tmp_p) + rtConstP.MATLABFunction1_ArmConstants.Inertia1[6]
                      * D46_tmp_7) + tmp_v;
  tmp[29] = -(((((((((((((((((((((rtb_ginv_tmp_6 - tmp_tmp * D46_tmp_9) +
    rtb_ginv_tmp_0) + rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    D46_tmp_a) - rtb_ginv_tmp_7) - rtb_ginv_tmp_8) - rtb_ginv_tmp_9) +
    -0.0027062010112 * D46_tmp_b) + -0.0040412944 * D46_tmp_b) + D47_tmp_1) +
    rtb_ginv_tmp_1) + D46_tmp_h) - D46_tmp_j) - D46_tmp_l) +
                     -0.0023282610207999996 * rtb_ginv_tmp) + tmp_x) + tmp_y) +
                  tmp_w) * tmp_l + D45_tmp_1 * tmp_2e) + (((D56_tmp - tmp_z) +
    D56_tmp_p) + D56_tmp_q) * rtU.InBus1_Velocities[5]) * D15_tmp +
               (((((-0.0011641305103999998 * D38 + tmp_11) + tmp_e) + tmp_p) +
                 tmp_v) * tmp_tmp_0 + rtb_ginv_tmp_tmp * tmp_g)) * 0.25);
  tmp_tmp = 2.0 * rtU.InBus1_Velocities[3];
  tmp_tmp_0 = tmp_tmp * 0.0069089343999999995;
  D15_tmp_1 = -0.39176 * rtU.InBus1_Velocities[3];
  D45_tmp_1 = 0.39176 * rtU.InBus1_Velocities[3];
  tmp_tmp_1 = D14_tmp_a * 0.0069089343999999995;
  tmp_tmp_2 = tmp_tmp * rtConstP.MATLABFunction1_HexaConstants.Inertia[4];
  tmp_tmp_3 = tmp_2j * rtConstP.MATLABFunction1_HexaConstants.Inertia[8];
  tmp_tmp_4 = tmp_tmp_0 * 0.142;
  tmp_tmp_0 *= 0.143;
  tmp_tmp_5 = tmp_9 * 0.0069089343999999995;
  D46_tmp_9 = -0.45856 * rtU.InBus1_Velocities[3] * 0.08312 * 0.142;
  D56_tmp = D14_tmp_a * 0.08312 * 0.17 * 0.143;
  D56_tmp_g = 0.45856 * rtU.InBus1_Velocities[3] * 0.08312 * 0.142;
  tmp_tmp_6 = tmp_2e * 0.08312 * 0.17;
  tmp_tmp_7 = tmp_2j * rtConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  tmp_tmp_8 = tmp_tmp * rtConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  tmp_tmp_9 = 0.0262846592 * rtU.InBus1_Velocities[3] * 0.142;
  tmp_tmp_a = tmp_tmp * 0.028900000000000006 * 0.143;
  tmp_tmp_b = D15_tmp_1 * 0.17 * 0.143;
  rtb_ginv_tmp_0 = D15_tmp_1 * 0.08312 * 0.143;
  rtb_ginv_tmp_1 = D45_tmp_1 * 0.08312 * 0.143;
  D45_tmp_1 = D45_tmp_1 * 0.17 * 0.143;
  tmp_tmp_c = 0.39176 * rtU.InBus1_Velocities[4];
  tmp_tmp_d = tmp_2j * rtConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  tmp_tmp *= rtConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  tmp_tmp_e = 0.0191844872 * rtU.InBus1_Velocities[3] * 0.143;
  tmp_tmp_f = D17_tmp_tmp_2 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  tmp_tmp_g = D17_tmp_tmp_2 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  tmp_tmp_h = 0.0011641305103999998 * rtb_ginv_tmp;
  tmp_tmp_i = tmp_2e * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  tmp_tmp_j = tmp_2e * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  tmp_tmp_k = tmp_36 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  tmp_tmp_l = tmp_36 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  tmp_tmp_m = rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] -
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  rtb_ginv_tmp = tmp_tmp_6 * 0.143;
  rtb_ginv_tmp_6 = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  rtb_ginv_tmp_7 = tmp_l * rtConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  rtb_ginv_tmp_8 = tmp_9 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  rtb_ginv_tmp_9 = 0.0262846592 * rtU.InBus1_Velocities[4] * 0.142;
  x_a = tmp_9 * 0.028900000000000006 * 0.143;
  tmp_tmp_n = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  tmp_tmp_o = tmp_tmp_c * 0.17 * 0.143;
  tmp_tmp_p = tmp_l * rtConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  tmp_tmp_q = tmp_9 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  tmp_tmp_r = 0.0191844872 * rtU.InBus1_Velocities[4] * 0.143;
  tmp_tmp_s = D46_tmp_9 * D18;
  tmp_tmp_t = D56_tmp * D18;
  tmp_tmp_u = rtb_ginv_tmp_6 * D46_tmp_tmp;
  tmp_tmp_v = rtb_ginv_tmp_7 * D56_tmp_9;
  tmp_tmp_w = rtb_ginv_tmp_8 * D56_tmp_9;
  tmp_tmp_x = rtb_ginv_tmp_9 * D56_tmp_9;
  tmp_tmp_y = x_a * D56_tmp_9;
  tmp_tmp_z = rtb_ginv_tmp_0 * D38;
  tmp_tmp_10 = tmp_tmp_n * D56_tmp_tmp_1;
  tmp_tmp_11 = tmp_tmp_o * D46;
  tmp_tmp_12 = tmp_tmp_p * D56_tmp_a;
  tmp_tmp_13 = tmp_tmp_q * D56_tmp_a;
  tmp_tmp_14 = tmp_tmp_r * D56_tmp_a;
  tmp_tmp_15 = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  tmp_tmp_16 = tmp_c * rtConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  D46_tmp_9 *= D17_tmp_5;
  D56_tmp *= D17_tmp_5;
  rtb_ginv_tmp_0 *= D17_tmp_2;
  tmp_tmp_17 = tmp_tmp_b * D27;
  D46_tmp_tmp = tmp_1g * D24_tmp;
  D56_tmp_tmp_1 = tmp_43 * D56_tmp_5;
  tmp_g = tmp_48 * D56_tmp_6;
  tmp_2j = tmp_1h * D56_tmp_tmp_6;
  tmp_5a =
    (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((((((((((((((((tmp_tmp_f * D46_tmp_g +
    tmp_tmp_g * D46_tmp_tmp_2) + tmp_tmp_2 * D25) + tmp_2i) + tmp_tmp_3 * D25) +
    tmp_2k) + tmp_tmp_4 * D25) + tmp_2l) + tmp_tmp_0 * D25) + tmp_2m) +
    D46_tmp_9) + D56_tmp) + tmp_2n) + tmp_2o) + D56_tmp_g * D16) + tmp_2p) +
    tmp_tmp_6 * 0.143 * D16) + tmp_2q) + tmp_tmp_7 * D56_tmp_7) + tmp_2r) +
    tmp_tmp_8 * D56_tmp_7) + tmp_2s) + tmp_tmp_9 * D56_tmp_7) + tmp_2t) +
    tmp_tmp_a * D56_tmp_7) + tmp_2u) + tmp_tmp_17) + rtb_ginv_tmp_0) + tmp_2v) +
    tmp_2w) + rtb_ginv_tmp_1 * D34) + tmp_2x) + D45_tmp_1 * D35) + tmp_2y) +
    tmp_tmp_d * D56_tmp_8) + tmp_2z) + tmp_tmp * D56_tmp_8) + tmp_30) +
    tmp_tmp_e * D56_tmp_8) + tmp_31) + D14_tmp_a *
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] * D15_tmp) + D14_tmp_a *
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] * D15_tmp) + D14_tmp_a *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[0] * D15_tmp) + -0.0525693184
    * rtU.InBus1_Velocities[3] * 0.142 * D15_tmp) + tmp_tmp_1 * 0.142 * D15_tmp)
    + -0.0383689744 * rtU.InBus1_Velocities[3] * 0.143 * D15_tmp) + tmp_tmp_1 *
    0.143 * D15_tmp) + D14_tmp_a * 0.028900000000000006 * 0.143 * D15_tmp) +
    tmp_tmp_2 * D17) + tmp_9 * rtConstP.MATLABFunction1_HexaConstants.Inertia[4]
    * D17) + tmp_tmp_3 * D17) + tmp_l *
    rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D17) + tmp_tmp_4 * D17)
    + tmp_tmp_5 * 0.142 * D17) + tmp_tmp_0 * D17) + tmp_tmp_5 * 0.143 * D17) +
    tmp_tmp_s) + tmp_tmp_t) + tmp_32 * D46_tmp_3) + tmp_tmp_u) + D56_tmp_g * D24)
    + 0.45856 * rtU.InBus1_Velocities[4] * 0.08312 * 0.142 * D24) + rtb_ginv_tmp
    * D24) + tmp_10 * 0.08312 * 0.17 * 0.143 * D24) + tmp_tmp_7 * D56_tmp_9) +
    tmp_tmp_v) + tmp_tmp_8 * D56_tmp_9) + tmp_tmp_w) + tmp_tmp_9 * D56_tmp_9) +
    tmp_tmp_x) + tmp_tmp_a * D56_tmp_9) + tmp_tmp_y) + tmp_tmp_b * D37) +
    tmp_tmp_z) + tmp_33 * D46_tmp_4) + tmp_tmp_10) + rtb_ginv_tmp_1 *
    D46_tmp_tmp_5) + tmp_tmp_c * 0.08312 * 0.143 * D46_tmp_tmp_5) + D45_tmp_1 *
    D46) + tmp_tmp_11) + tmp_tmp_d * D56_tmp_a) + tmp_tmp_12) + tmp_tmp *
    D56_tmp_a) + tmp_tmp_13) + tmp_tmp_e * D56_tmp_a) + tmp_tmp_14) + tmp_tmp_f *
    D46_tmp_tmp_4) + tmp_tmp_g * D46_tmp_tmp_6) + ((((((D48_tmp_0 + D46_tmp_h) -
    D46_tmp_j) - D46_tmp_l) - tmp_tmp_h) - 0.0023809214000000004 * D46_tmp_tmp_3)
    + tmp_w) * (tmp_b * D15_tmp)) + ((((((((((((((tmp_tmp_m -
    0.0018662108031999999) - 0.0041327000000000004) * D46_tmp_a + D47_tmp_2) +
    -0.0013531005056 * D46_tmp_b) - 0.0020206472 * D46_tmp_b) + D47_tmp_1) +
    D47_tmp) + D46_tmp_h) - D46_tmp_j) - D46_tmp_l) - tmp_tmp_h) + tmp_x) +
    tmp_y) + tmp_w) * (D16_tmp * D15_tmp)) + tmp_34) + tmp_1a * D46_tmp_tmp_8) +
    tmp_35 * D46_tmp_tmp_8) + tmp_tmp_k * D46_tmp_tmp_9) + tmp_37) + tmp_35 *
    D56) + tmp_14 * D56_tmp_tmp_2) + tmp_1c * D56_tmp_tmp_4) + tmp_tmp_l *
    D47_tmp_0) + tmp_38) + tmp_39) + tmp_3a) + tmp_3b) - tmp_3c) - tmp_3d) -
    tmp_3e) + tmp_tmp_i * D56_tmp_1) + tmp_3f) + tmp_3g) + tmp_3h) - tmp_3i) -
                    tmp_3j) + tmp_tmp_j * D56_tmp_2) + tmp_3k) + tmp_tmp_15 *
                 D46_tmp_k) + tmp_3l * D46_tmp_k) + D17_tmp_tmp_2 *
               rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] * D46_tmp_k) +
              tmp_tmp_16 * D46_tmp_k) + tmp_3m * D46_tmp_k) + D17_tmp_tmp_2 *
            rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] * D46_tmp_k) +
           D17_tmp_tmp_2 * rtConstP.MATLABFunction1_HexaConstants.Inertia[0] *
           D46_tmp_k) + tmp_3n * D46_tmp_k) + tmp_c *
         rtConstP.MATLABFunction1_HexaConstants.Inertia[8] * D46_tmp_k) + tmp_3o
        * D46_tmp_k) + tmp_3p * D46_tmp_k) + tmp_3q * D46_tmp_k) + tmp_19 *
     D46_tmp_k) + tmp_3r * D46_tmp_k;
  tmp[37] = -(((((((((((((((((((((((((((((((tmp_5a + tmp_3s) + tmp_3t) + tmp_3u)
    + tmp_3v) - tmp_3w) + tmp_3x) + tmp_3y) + tmp_3z * D46_tmp_7) - tmp_40) +
    tmp_41) + tmp_42) + D46_tmp_tmp) + tmp_tmp_i * D56_tmp_5) + D56_tmp_tmp_1) +
    tmp_44 * D46_tmp_8) - tmp_45) + tmp_46) + tmp_47) + tmp_tmp_j * D56_tmp_6) +
    tmp_g) + tmp_1e * D56_tmp_tmp) + tmp_13 * D56_tmp_tmp) + tmp_tmp_k *
                      D15_tmp_tmp) + tmp_1h * D56_tmp_tmp_7) + tmp_18 *
                    D14_tmp_tmp) + tmp_tmp_l * D15_tmp_tmp_0) + tmp_1e *
                  D24_tmp_0) + tmp_13 * D24_tmp_0) + tmp_18 * D56_tmp_tmp_9) +
               tmp_2j) * 0.125);
  D17_tmp_tmp_2 = rtb_ginv_tmp_tmp_1 * rtb_ginv_tmp_tmp_0;
  rtb_ginv_tmp_tmp_0 = -2.0 * rtb_ginv_tmp_tmp_0 * D14_tmp_1;
  D16_tmp = 0.11464 * D15_tmp_0 + D24_tmp_2;
  tmp_b = 0.08312 * D14_tmp_1;
  tmp_c = 4.0 * D14_tmp_2;
  tmp_tmp = ((0.17 * D34_tmp + tmp_b) + 0.09794 * D34_tmp_0) * s - D24_tmp_3 *
    smax * D14_tmp_0;
  tmp_tmp_0 = D46_tmp_m * -2.0;
  tmp_w = D46_tmp_f * D56_tmp_tmp_tmp + tmp_tmp_m * D46_tmp;
  tmp_x = tmp_c * D17_tmp_3 * D14_tmp_1 * (rtb_ginv_tmp_tmp_3 +
    rtb_ginv_tmp_tmp_4);
  tmp_y = (rtb_ginv_tmp_tmp_2 * 2.0 * D46_tmp_i + 4.0 *
           rtConstP.MATLABFunction1_ArmConstants.Inertia2[3] * D46_tmp_0) *
    rtb_ginv_tmp_h;
  tmp_10 = (rtb_ginv_tmp_4 * 2.0 * D46_tmp_i + -4.0 *
            rtConstP.MATLABFunction1_ArmConstants.Inertia2[3] * D46_tmp_0) *
    rtb_ginv_tmp_i;
  tmp_tmp_1 = tmp_tmp * 0.572;
  tmp_b = (0.11464 * D34_tmp + tmp_b) * s;
  tmp_tmp_2 = rtb_ginv_tmp_c * D14_tmp_e * D46_tmp_k;
  tmp_tmp_3 = rtb_ginv_tmp_d * tmp_49 * D46_tmp_k;
  tmp[45] = -((((((((((((((((((((tmp_tmp_m * D14_tmp_6 * D14_tmp +
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[3] * D56_tmp_tmp_tmp) *
    (tmp_c * D15_tmp * D14_tmp_1) * D14_tmp_0 + (((D17_tmp_tmp_2 *
    rtb_ginv_tmp_a + rtb_ginv_tmp_tmp_0 * rtb_ginv_tmp_b) + D17_tmp_tmp_2 *
    rtb_ginv_tmp_c) + rtb_ginv_tmp_tmp_0 * rtb_ginv_tmp_d)) + ((D56_tmp_f *
    D14_tmp_6 * D14_tmp + rtb_ginv_tmp_e) + rtb_ginv_tmp_f) * (tmp_tmp_0 *
    D15_tmp) * D14_tmp_0) + -2.0 * D15_tmp * rtb_ginv_tmp_2 * D46_tmp_n *
    D14_tmp_0) - D46_tmp_m * D15_tmp * w_a_tmp * D14_tmp_0) - rtb_ginv_tmp_2 *
    D15_tmp * rtb_ginv_tmp_3 * D14_tmp_0) + rtb_ginv_tmp_tmp_1 * D15_tmp *
    D14_tmp_1 * (D46_tmp_e * D46_tmp_0 + rtb_ginv_tmp_tmp_2 * D46_tmp_i) *
    D14_tmp_0) + D16_tmp * -0.284 * D15_tmp * smax * (tmp_b - D16_tmp * smax *
    D14_tmp_0)) + D24_tmp_3 * -0.286 * D15_tmp * smax * tmp_tmp) + -0.284 * s *
                        D16_tmp * D15_tmp * D45_tmp_0) + -0.286 * s * D24_tmp_3 *
                       D15_tmp * D24_tmp_1) +
                      rtConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
                      D46_tmp_k) +
                     rtConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
                     D46_tmp_k) +
                    rtConstP.MATLABFunction1_HexaConstants.Inertia[0] *
                    D46_tmp_k) - rtb_ginv_tmp_g * D46_tmp_k) - rtb_ginv_tmp_2 *
                  rtConstP.MATLABFunction1_HexaConstants.Inertia[4] * D46_tmp_k)
                 * tmp_9 + ((((((tmp_y + tmp_x) + tmp_10) + D18_tmp * 0.572 *
    D24_tmp_1) + tmp_tmp_1 * D17_tmp_0) + tmp_tmp_2) + tmp_tmp_3) *
                 rtU.InBus1_Velocities[7]) + (((((((((((((D17_tmp_3 * -2.0 * D14
    * (tmp_tmp_m * D56_tmp_tmp_tmp + D56_tmp_f * D46_tmp) + tmp_tmp_0 *
    D17_tmp_3 * tmp_w) + D17_tmp_3 * 2.0 * rtb_ginv_tmp_2 * tmp_w) + tmp_x) +
    tmp_y) + tmp_10) + (D17_tmp * D17_tmp_4 + D17_tmp_1 * D17_tmp_6) * 0.572 *
    D24_tmp_1) + (D17_tmp_tmp_1 * -D17_tmp_4 + D17_tmp_tmp_0 * D17_tmp_6) *
    tmp_tmp_1) + (D17_tmp_7 * D14_tmp_1 + D17_tmp_8 * D14_tmp_2) * (D45_tmp_0 *
    0.06511552)) + ((D14_tmp_6 * smax * D14_tmp_0 + -s * D14_tmp) * (0.11464 *
    D14_tmp_1) + (D17_tmp_tmp_3 * D14_tmp_0 + D17_tmp_tmp_4) * (0.11464 *
    D14_tmp_2)) * ((-D16_tmp * smax * D14_tmp_0 + tmp_b) * 0.568)) +
    rtb_ginv_tmp_a * D14_tmp_e * D46_tmp_k) + rtb_ginv_tmp_b * tmp_49 *
    D46_tmp_k) + tmp_tmp_2) + tmp_tmp_3) * rtU.InBus1_Velocities[6]) -
               (((((((((((((((((((((((((((((((((((((((((D56_tmp_l * D46_tmp_1 +
    D46_tmp_f * D56_tmp_7) + D56_tmp_m * D46_tmp_2) + D46_tmp_e * D56_tmp_8) +
    D56_tmp_n * D46_tmp_3) + D46_tmp_f * D56_tmp_9) + D56_tmp_o * D46_tmp_4) +
    D46_tmp_e * D56_tmp_a) - D56_tmp_tmp_a) + D56_tmp_tmp_b) - D56_tmp_tmp_c) -
    D56_tmp_tmp_d) + D56_tmp_j * D46_tmp_5) + -0.0027062010112 * D56_tmp_0) +
    -0.0040412944 * D56_tmp_0) + D56_tmp_tmp_e) - D56_tmp_tmp_f) - D56_tmp_tmp_g)
    - D56_tmp_tmp_h) + D56_tmp_k * D46_tmp_6) + -0.0023282610207999996 *
    D56_tmp_b) + -0.004761842800000001 * D56_tmp_c) + D56_tmp_tmp_i) -
    D56_tmp_tmp_j) - D56_tmp_tmp_k) - D56_tmp_tmp_l) + D56_tmp_tmp_m) -
    D56_tmp_tmp_n) + -0.0009879776191999998 * D56_tmp_3) + D56_tmp_h * D46_tmp_7)
    + -0.0027062010112 * D56_tmp_4) + -0.0040412944 * D56_tmp_4) + D56_tmp_tmp_o)
                        - D56_tmp_tmp_p) - D56_tmp_tmp_q) - D56_tmp_tmp_r) +
                     D56_tmp_i * D46_tmp_8) + -0.0023282610207999996 * D56_tmp_d)
                   + -0.004761842800000001 * D56_tmp_e) + tmp_z) - D56_tmp_p) -
                D56_tmp_q) * D16_tmp_2) * 0.25);
  rtb_ginv_tmp_tmp_0 = tmp_2e * rtConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  tmp_49 = 0.22928 * rtU.InBus1_Velocities[4] * 0.08312 * 0.142;
  D16_tmp_2 = tmp_9 * 0.08312 * 0.17 * 0.143;
  D14_tmp_e = tmp_2e * rtConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  D17_tmp_tmp_2 = 0.19588 * rtU.InBus1_Velocities[4];
  D16_tmp = D17_tmp_tmp_2 * 0.08312 * 0.143;
  tmp_b = tmp_2e * rtConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  tmp_c = tmp_36 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[3] * D46_tmp_c;
  tmp_tmp = tmp_1o * D46_tmp_tmp_2;
  tmp_tmp_0 = rtb_ginv_tmp_1 * D17_tmp_2;
  tmp_w = w_a * D17_tmp_2;
  tmp_x = D14_tmp_e * D46_tmp_2;
  D46_tmp_tmp_0 *= tmp_tmp_n;
  tmp_y = D16_tmp * D34;
  tmp_z = tmp_tmp_p * D56_tmp_8;
  tmp_10 = tmp_tmp_q * D56_tmp_8;
  tmp_tmp_1 = tmp_tmp_r * D56_tmp_8;
  tmp_tmp_2 = w_a * D38;
  D14_tmp_e *= D46_tmp_4;
  D16_tmp *= D46_tmp_tmp_5;
  D46_tmp_tmp_6 *= tmp_1m;
  tmp_tmp_3 = -0.5876399999999999 * rtU.InBus1_Velocities[5];
  tmp_tmp_m = tmp_tmp_3 * 0.08312 * 0.143 * D14_tmp_5;
  tmp_tmp_16 *= D46_tmp_d;
  tmp_tmp_n = D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    D46_tmp_d;
  tmp_tmp_p = tmp_3q * D46_tmp_d;
  tmp_18 *= D47;
  D56_tmp_tmp_4 *= tmp_1p;
  D47_tmp_0 *= tmp_1i;
  D56_tmp_tmp_3 *= tmp_1p;
  tmp_tmp_q = tmp_4h * D46_tmp_6;
  tmp_tmp_r = tmp_48 * D56_tmp_2;
  tmp_tmp_4 = tmp_4h * D46_tmp_8;
  tmp_e = (((tmp_11 - tmp_15) + tmp_e) + tmp_p) + tmp_v;
  tmp_p = tmp_e * tmp_4i;
  D14_tmp_tmp *= tmp_1p;
  D15_tmp_tmp_0 *= tmp_1k;
  tmp_1p *= D56_tmp_tmp_9;
  tmp_v = D56_tmp_tmp_8 * D46_tmp_tmp_8;
  tmp_11 = D14_tmp_c * D56;
  tmp_19 = D56_tmp_tmp_8 * D56;
  tmp_1g = D14_tmp_c * D56_tmp_tmp;
  D56_tmp_tmp *= D56_tmp_tmp_8;
  tmp_1i = D14_tmp_c * D24_tmp_0;
  D56_tmp_tmp_8 *= D24_tmp_0;
  tmp[53] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((tmp_36 *
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[3] * D46_tmp_a + tmp_c) +
    tmp_1n * D46_tmp_g) + tmp_tmp) + D56_tmp_g * D17_tmp_5) + ab_a * D17_tmp_5)
    + rtb_ginv_tmp * D17_tmp_5) + D57 * D17_tmp_5) + rtb_ginv_tmp_tmp_0 *
    D46_tmp_1) + rtb_ginv_tmp_6 * D46_tmp_tmp_1) + tmp_49 * D16) + D16_tmp_2 *
    D16) + rtb_ginv_tmp_7 * D56_tmp_7) + rtb_ginv_tmp_8 * D56_tmp_7) +
    rtb_ginv_tmp_9 * D56_tmp_7) + x_a * D56_tmp_7) + tmp_4a) + tmp_tmp_0) +
    tmp_w) + tmp_x) + D46_tmp_tmp_0) + tmp_y) + tmp_tmp_o * D35) + tmp_z) +
    tmp_10) + tmp_tmp_1) + tmp_4b) + tmp_4c) + tmp_4d) + tmp_4e) + tmp_4f) +
    tmp_tmp_s) + ab_a * D18) + tmp_tmp_t) + D57 * D18) + rtb_ginv_tmp_tmp_0 *
    D46_tmp_3) + tmp_tmp_u) + tmp_49 * D24) + D16_tmp_2 * D24) + tmp_tmp_v) +
    tmp_tmp_w) + tmp_tmp_x) + tmp_tmp_y) + tmp_4g) + tmp_tmp_z) + tmp_tmp_2) +
    D14_tmp_e) + tmp_tmp_10) + D16_tmp) + tmp_tmp_11) + tmp_tmp_12) + tmp_tmp_13)
    + tmp_tmp_14) + tmp_1l * D46_tmp_tmp_4) + D46_tmp_tmp_6) + -0.68784 *
    rtU.InBus1_Velocities[5] * 0.08312 * 0.142 * D14_tmp) + -6.0 *
    rtU.InBus1_Velocities[5] * 0.08312 * 0.17 * 0.143 * D14_tmp) + tmp_tmp_15 *
    D46_tmp_o) + D16_tmp_1 * rtConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    D46_tmp_o) + tmp_3o * D46_tmp_o) + tmp_3r * D46_tmp_o) + tmp_1e * D15) +
    tmp_13 * D15) + tmp_tmp_m) + tmp_tmp_16) + tmp_tmp_n) + tmp_tmp_p) + tmp_18)
    + 0.39176 * rtU.InBus1_Velocities[5] * 0.17 * 0.143 * D56_tmp_tmp_0) +
    tmp_1h * D46_tmp_tmp_7) + D48_tmp * D46_tmp_tmp_8) + tmp_v) + tmp_1f *
    D46_tmp_tmp_9) + tmp_11) + tmp_19) + D56_tmp_tmp_4) + D47_tmp_0) +
    D56_tmp_tmp_3) + tmp_b * D46_tmp_5) - tmp_3b) + tmp_3c) + tmp_3d) + tmp_3e)
    + tmp_43 * D56_tmp_1) + tmp_tmp_q) + -rtU.InBus1_Velocities[5] *
    rtConstP.MATLABFunction1_ArmConstants.Inertia2[0] * D45_tmp) + tmp_3i) +
    tmp_3j) + tmp_tmp_r) + tmp_b * D46_tmp_7) + -rtU.InBus1_Velocities[5] *
    rtConstP.MATLABFunction1_ArmConstants.Inertia1[0] * D24_tmp) + tmp_41) +
    tmp_42) + D46_tmp_tmp) + D56_tmp_tmp_1) + tmp_tmp_4) + tmp_p) +
                    rtb_ginv_tmp_tmp * tmp_4j) - tmp_45) + tmp_46) + tmp_47) +
                tmp_g) + tmp_1g) + D56_tmp_tmp) + tmp_1j * D15_tmp_tmp) +
            D14_tmp_tmp) + D15_tmp_tmp_0) + tmp_1i) + D56_tmp_tmp_8) + tmp_1p) +
       tmp_2j) * 0.125);
  D46_tmp_tmp_1 = D17_tmp_tmp_2 * 0.17 * 0.143;
  D56_tmp_tmp_1 = D14_tmp_d * D46_tmp_tmp_7;
  D15_tmp_tmp = D14_tmp_d * D56_tmp_tmp_2;
  D46_tmp_tmp_4 = D14_tmp_d * D56_tmp_tmp_7;
  D46_tmp_tmp_7 = D14_tmp_d * D56_tmp_tmp_6;
  tmp[61] = -((((((((((((((((((((((((((((((((((((((((((((((((((((((((tmp_c +
    tmp_tmp) + D45_tmp_1 * D27) + D56_tmp_tmp_5 * D27) + tmp_tmp_0) + tmp_w) +
    tmp_x) + D46_tmp_tmp_0) + tmp_y) + D46_tmp_tmp_1 * D35) + tmp_z) + tmp_10) +
    tmp_tmp_1) + tmp_4c) + tmp_4e) + D15_tmp_1 * 0.17 * 0.143 * D37) +
    D56_tmp_tmp_5 * D37) + tmp_tmp_z) + tmp_tmp_2) + D14_tmp_e) + tmp_tmp_10) +
    D16_tmp) + D46_tmp_tmp_1 * D46) + tmp_tmp_12) + tmp_tmp_13) + tmp_tmp_14) +
    D46_tmp_tmp_6) + tmp_tmp_3 * 0.17 * 0.143 * D14_tmp_4) + tmp_tmp_m) +
    tmp_tmp_16) + tmp_tmp_n) + tmp_tmp_p) + tmp_18) + tmp_1h * D56_tmp_tmp_0) +
    D56_tmp_tmp_1) + D15_tmp_tmp) + D56_tmp_tmp_4) + D47_tmp_0) + D56_tmp_tmp_3)
    + tmp_tmp_q) - tmp_3h) + tmp_3i) + tmp_3j) + tmp_tmp_r) + tmp_tmp_4) + tmp_e
    * tmp_4j) + tmp_p) - tmp_45) + tmp_46) + tmp_47) + tmp_g) + D46_tmp_tmp_4) +
                  D14_tmp_tmp) + D15_tmp_tmp_0) + tmp_1p) + D46_tmp_tmp_7) *
              0.125);
  D46_tmp_tmp_1 = tmp_n * 0.17 * 0.143 * D14_tmp_4;
  D46_tmp_tmp_0 = rtU.InBus1_Velocities[3] - D17_tmp_tmp;
  tmp[30] = -(tmp_r * D46_tmp_tmp_0 + D46_tmp_tmp_1);
  tmp[38] = -((((((((((((((((tmp_4k + tmp_q) + 0.0020206472 * D14_tmp) -
    D16_tmp_0) + tmp_8) + tmp_a) + D16_tmp_3) + 0.0013531005056 * D15) + tmp_s)
                     + tmp_t) - tmp_i) + D14_tmp_8) + D14_tmp_f) + tmp_u) +
                tmp_4l) * tmp_9 - D27_tmp_1 * rtU.InBus1_Velocities[5]) * 0.25);
  D15_tmp_tmp_0 = rtb_ginv_tmp_1 * D38;
  D46_tmp_tmp_6 = 0.5876399999999999 * rtU.InBus1_Velocities[5];
  D46_tmp_tmp_9 = D46_tmp_tmp_6 * 0.08312 * 0.143 * D14_tmp_5;
  D47_tmp_0 = tmp_1c * D47;
  tmp[46] = -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((tmp_4m
    + D46_tmp_9) + D56_tmp) + tmp_2o) + rtb_ginv_tmp_0) + tmp_2w) + D56_tmp_g *
    D18) + rtb_ginv_tmp * D18) + tmp_4n) + D15_tmp_tmp_0) + tmp_4o) + tmp_4p) +
    tmp_4q) + 0.68784 * rtU.InBus1_Velocities[5] * 0.08312 * 0.142 * D14_tmp) +
    6.0 * rtU.InBus1_Velocities[5] * 0.08312 * 0.17 * 0.143 * D14_tmp) + tmp_4r)
    + tmp_4s) + tmp_4t) + tmp_4u * 0.143 * D46_tmp_o) + tmp_1a * D15) + tmp_1b *
    D15) + D46_tmp_tmp_9) + tmp_4v) + tmp_4w) + tmp_4x) + D47_tmp_0) + tmp_4y) +
    tmp_34) - D14_tmp_c * D46_tmp_tmp_8) - tmp_v) + tmp_4z) - tmp_11) - tmp_19)
    - D56_tmp_tmp_4) + tmp_50) - D56_tmp_tmp_3) + tmp_3b) - tmp_3c) - tmp_3d) -
    tmp_3e) + tmp_3h) - tmp_3i) - tmp_3j) + tmp_51 * 0.17 * 0.143 * D14_tmp_4 *
    D14_tmp_0) + tmp_40) - tmp_41) - tmp_42) - D46_tmp_tmp) + tmp_45) - tmp_46)
    - tmp_47) + ((((((((((((((((((((((((((((((((((((((((((-rtConstP.MATLABFunction1_ArmConstants.Inertia1
    [0] * D56_tmp_7 + D27_tmp_0) + D14_tmp_3) + tmp_h) + tmp_j) + tmp_k) + tmp_m)
    + D14_tmp_7) + tmp_o) + D14_tmp_9) - D14_tmp_tmp_0) + D14_tmp_tmp_1) +
    D14_tmp_b) + D15_tmp_tmp_1) + D15_tmp_tmp_2) + D16_tmp_tmp) + D34_tmp_3) +
    D37_tmp) + tmp_17) + tmp_2f) + rtb_ginv_tmp_5) + tmp_52) + tmp_53) - tmp_1q)
    + tmp_1r) + tmp_1s) + tmp_1t) + tmp_1u) + tmp_15) + tmp_1v) + tmp_16) +
    tmp_1w) - tmp_1x) + tmp_1y) + tmp_1z) + tmp_20) + tmp_21) + tmp_22) + tmp_23)
                    + tmp_24) + tmp_25) + tmp_26) + tmp_27) * tmp_l) - tmp_1g) -
                      D56_tmp_tmp) + tmp_54) - D14_tmp_tmp) + tmp_55) - tmp_1i)
                 - D56_tmp_tmp_8) - tmp_1p) + tmp_56) * 0.125);
  tmp[54] = -D46_tmp_tmp_1;
  tmp[62] = -(-0.0023809214000000004 * D14_tmp_4 * tmp_f);
  tmp[31] = -((rtU.InBus1_Velocities[6] * 0.17 * D14_tmp_4 + tmp_1d *
               D46_tmp_tmp_0) * 0.01400542);
  tmp[39] = -((tmp_12 * rtU.InBus1_Velocities[4] * D34_tmp_0 +
               -rtU.InBus1_Velocities[4] *
               rtConstP.MATLABFunction1_ArmConstants.Inertia2[3] * D46_tmp_c) +
              -0.25 * rtU.InBus1_Velocities[5] * tmp_57);
  tmp[47] = -((((((((((((((((((((((((((((((((((tmp_58 + tmp_59) + tmp_tmp_17) +
    rtb_ginv_tmp_0) + tmp_2w) + D45_tmp_1 * D37) + D15_tmp_tmp_0) + tmp_4o) +
    tmp_4q) + D46_tmp_tmp_6 * 0.17 * 0.143 * D14_tmp_4) + D46_tmp_tmp_9) +
    tmp_4v) + tmp_4w) + tmp_4x) + D47_tmp_0) + tmp_14 * D56_tmp_tmp_0) -
    D56_tmp_tmp_1) - D15_tmp_tmp) - D56_tmp_tmp_4) + tmp_50) - D56_tmp_tmp_3) +
    tmp_3h) - tmp_3i) - tmp_3j) + -0.78352 * rtU.InBus1_Velocities[6] * 0.17 *
                        0.143 * D14_tmp_4 * D14_tmp_0) + tmp_45) - tmp_46) -
                     tmp_47) + tmp_57 * tmp_l) - D46_tmp_tmp_4) - D14_tmp_tmp) +
                 tmp_55) + -0.09794 * rtU.InBus1_Velocities[5] * 0.08312 * 0.143
                * D56_tmp_tmp_9) - D46_tmp_tmp_7) * 0.125);
  tmp[55] = -(0.0023809214000000004 * D14_tmp_4 * tmp_d);
  tmp[63] = -0.0;
  std::memset(&tmp[0], 0, 24U * sizeof(real_T));
  std::memset(&tmp_0[0], 0, sizeof(real_T) << 3U);
  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_1 = rtU.InBus1_Velocities[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5 = _mm_loadu_pd(&tmp[(d_k << 3) + i]);
      tmp_6 = _mm_loadu_pd(&tmp_0[i]);
      _mm_storeu_pd(&tmp_0[i], _mm_add_pd(_mm_mul_pd(tmp_5, _mm_set1_pd
        (D46_tmp_tmp_1)), tmp_6));
    }
  }

  tmp_1[0] = 0.0;
  tmp_1[1] = 0.0;
  tmp_1[2] = 20.631230269999996;
  D46_tmp_tmp_1 = -9.80665 * D15_tmp;
  tmp_1[3] = ((-0.023689199999999997 * D14_tmp_1 - D34_tmp_1) - D34_tmp_2) *
    D46_tmp_tmp_1;
  tmp_1[4] = D15_tmp_2 * 9.80665 * D14_tmp_0;
  tmp_1[5] = 0.0;
  tmp_1[6] = (-0.040588879999999994 * D34_tmp - D34_tmp_2) * D46_tmp_tmp_1;
  tmp_1[7] = 0.137346252043 * D15_tmp * D34_tmp_0;
  for (d_k = 0; d_k <= 6; d_k += 2) {
    // MATLAB Function: '<S1>/MATLAB Function1'
    tmp_5 = _mm_loadu_pd(&tmp_0[d_k]);
    tmp_6 = _mm_loadu_pd(&tmp_1[d_k]);
    _mm_storeu_pd(&rtb_fx[d_k], _mm_sub_pd(tmp_5, tmp_6));
  }

  // MATLAB Function: '<S1>/MATLAB Function1'
  mldivide_j(rtb_ginv, rtb_fx);

  // MATLAB Function: '<Root>/GetBInvMatrix' incorporates:
  //   Inport generated from: '<Root>/InBus1_Inport_2'

  D14_tmp = std::tan(rtU.InBus1_Positions[4]);
  std::memset(&x[0], 0, sizeof(real_T) << 6U);
  std::memset(&rtb_BMinv[0], 0, sizeof(real_T) << 6U);
  x[0] = s * D15_tmp;
  x[8] = D17_tmp_1;
  x[16] = D17_tmp;
  x[24] = 0.0;
  x[32] = 0.0;
  x[40] = 0.0;
  x[1] = D15_tmp * smax;
  x[9] = D17_tmp_tmp_0;
  x[17] = D27_tmp;
  x[25] = 0.0;
  x[33] = 0.0;
  x[41] = 0.0;
  x[2] = -D14_tmp_0;
  x[10] = D15_tmp * D14_tmp_1;
  x[18] = D14_tmp_2 * D15_tmp;
  x[26] = 0.0;
  x[34] = 0.0;
  x[42] = 0.0;
  x[3] = 0.0;
  x[11] = 0.0;
  x[19] = 0.0;
  x[27] = 1.0;
  x[35] = D14_tmp_1 * D14_tmp;
  x[43] = D14_tmp_2 * D14_tmp;
  x[4] = 0.0;
  x[12] = 0.0;
  x[20] = 0.0;
  x[28] = 0.0;
  x[36] = D14_tmp_2;
  x[44] = -D14_tmp_1;
  x[5] = 0.0;
  x[13] = 0.0;
  x[21] = 0.0;
  x[29] = 0.0;
  smax = 1.0 / D15_tmp;
  x[37] = smax * D14_tmp_1;
  x[45] = smax * D14_tmp_2;
  x[54] = 1.0;
  x[55] = 0.0;
  x[62] = 0.0;
  x[63] = 1.0;
  for (d_k = 0; d_k < 8; d_k++) {
    ipiv[d_k] = static_cast<int8_T>(d_k + 1);
  }

  for (i = 0; i < 7; i++) {
    jj = i * 9;
    iy = 9 - i;
    b_ix = 0;
    smax = std::abs(x[jj]);
    for (d_k = 2; d_k < iy; d_k++) {
      s = std::abs(x[(jj + d_k) - 1]);
      if (s > smax) {
        b_ix = d_k - 1;
        smax = s;
      }
    }

    if (x[jj + b_ix] != 0.0) {
      if (b_ix != 0) {
        iy = i + b_ix;
        ipiv[i] = static_cast<int8_T>(iy + 1);
        for (ix = 0; ix < 8; ix++) {
          b_ix = (ix << 3) + i;
          smax = x[b_ix];
          x[b_ix] = x[iy];
          x[iy] = smax;
          iy += 8;
        }
      }

      iy = (jj - i) + 8;
      d_k = (((((iy - jj) - 1) / 2) << 1) + jj) + 2;
      ix = d_k - 2;
      for (b_ix = jj + 2; b_ix <= ix; b_ix += 2) {
        tmp_5 = _mm_loadu_pd(&x[b_ix - 1]);
        _mm_storeu_pd(&x[b_ix - 1], _mm_div_pd(tmp_5, _mm_set1_pd(x[jj])));
      }

      for (b_ix = d_k; b_ix <= iy; b_ix++) {
        x[b_ix - 1] /= x[jj];
      }
    }

    iy = 6 - i;
    b_ix = jj + 10;
    for (d_k = 0; d_k <= iy; d_k++) {
      D46_tmp_tmp_1 = x[((d_k << 3) + jj) + 8];
      if (D46_tmp_tmp_1 != 0.0) {
        ix = (b_ix - i) + 6;
        for (ijA = b_ix; ijA <= ix; ijA++) {
          x[ijA - 1] += x[((jj + ijA) - b_ix) + 1] * -D46_tmp_tmp_1;
        }
      }

      b_ix += 8;
    }
  }

  for (d_k = 0; d_k < 8; d_k++) {
    p[d_k] = static_cast<int8_T>(d_k + 1);
  }

  for (i = 0; i < 7; i++) {
    ipiv_0 = ipiv[i];
    if (ipiv_0 > i + 1) {
      jj = p[ipiv_0 - 1];
      p[ipiv_0 - 1] = p[i];
      p[i] = static_cast<int8_T>(jj);
    }
  }

  for (i = 0; i < 8; i++) {
    ijA = (p[i] - 1) << 3;
    rtb_BMinv[i + ijA] = 1.0;
    for (iy = i + 1; iy < 9; iy++) {
      d_k = (ijA + iy) - 1;
      if (rtb_BMinv[d_k] != 0.0) {
        for (b_ix = iy + 1; b_ix < 9; b_ix++) {
          jj = (ijA + b_ix) - 1;
          rtb_BMinv[jj] -= x[(((iy - 1) << 3) + b_ix) - 1] * rtb_BMinv[d_k];
        }
      }
    }
  }

  // MATLAB Function: '<S3>/PD Controller' incorporates:
  //   Constant: '<S3>/Kd'
  //   Constant: '<S3>/Kp'

  tmp[0] = 0.5;
  tmp[8] = 0.0;
  tmp[16] = 0.0;
  tmp[24] = 0.0;
  tmp[32] = 0.0;
  tmp[40] = 0.0;
  tmp[48] = 0.0;
  tmp[56] = 0.0;
  tmp[1] = 0.0;
  tmp[9] = 0.5;
  tmp[17] = 0.0;
  tmp[25] = 0.0;
  tmp[33] = 0.0;
  tmp[41] = 0.0;
  tmp[49] = 0.0;
  tmp[57] = 0.0;
  tmp[2] = 0.0;
  tmp[10] = 0.0;
  tmp[18] = 1.0;
  tmp[26] = 0.0;
  tmp[34] = 0.0;
  tmp[42] = 0.0;
  tmp[50] = 0.0;
  tmp[58] = 0.0;
  tmp[3] = 0.0;
  tmp[11] = 0.0;
  tmp[19] = 0.0;
  tmp[27] = 2.0;
  tmp[35] = 0.0;
  tmp[43] = 0.0;
  tmp[51] = 0.0;
  tmp[59] = 0.0;
  tmp[4] = 0.0;
  tmp[12] = 0.0;
  tmp[20] = 0.0;
  tmp[28] = 0.0;
  tmp[36] = 2.0;
  tmp[44] = 0.0;
  tmp[52] = 0.0;
  tmp[60] = 0.0;
  tmp[5] = 0.0;
  tmp[13] = 0.0;
  tmp[21] = 0.0;
  tmp[29] = 0.0;
  tmp[37] = 0.0;
  tmp[45] = 2.0;
  tmp[53] = 0.0;
  tmp[61] = 0.0;
  tmp[6] = 0.0;
  tmp[14] = 0.0;
  tmp[22] = 0.0;
  tmp[30] = 0.0;
  tmp[38] = 0.0;
  tmp[46] = 0.0;
  tmp[54] = 50.0;
  tmp[62] = 0.0;
  tmp[7] = 0.0;
  tmp[15] = 0.0;
  tmp[23] = 0.0;
  tmp[31] = 0.0;
  tmp[39] = 0.0;
  tmp[47] = 0.0;
  tmp[55] = 0.0;
  tmp[63] = 100.0;
  tmp_2[0] = 0.5;
  tmp_2[8] = 0.0;
  tmp_2[16] = 0.0;
  tmp_2[24] = 0.0;
  tmp_2[32] = 0.0;
  tmp_2[40] = 0.0;
  tmp_2[48] = 0.0;
  tmp_2[56] = 0.0;
  tmp_2[1] = 0.0;
  tmp_2[9] = 0.5;
  tmp_2[17] = 0.0;
  tmp_2[25] = 0.0;
  tmp_2[33] = 0.0;
  tmp_2[41] = 0.0;
  tmp_2[49] = 0.0;
  tmp_2[57] = 0.0;
  tmp_2[2] = 0.0;
  tmp_2[10] = 0.0;
  tmp_2[18] = 1.0;
  tmp_2[26] = 0.0;
  tmp_2[34] = 0.0;
  tmp_2[42] = 0.0;
  tmp_2[50] = 0.0;
  tmp_2[58] = 0.0;
  tmp_2[3] = 0.0;
  tmp_2[11] = 0.0;
  tmp_2[19] = 0.0;
  tmp_2[27] = 2.0;
  tmp_2[35] = 0.0;
  tmp_2[43] = 0.0;
  tmp_2[51] = 0.0;
  tmp_2[59] = 0.0;
  tmp_2[4] = 0.0;
  tmp_2[12] = 0.0;
  tmp_2[20] = 0.0;
  tmp_2[28] = 0.0;
  tmp_2[36] = 2.0;
  tmp_2[44] = 0.0;
  tmp_2[52] = 0.0;
  tmp_2[60] = 0.0;
  tmp_2[5] = 0.0;
  tmp_2[13] = 0.0;
  tmp_2[21] = 0.0;
  tmp_2[29] = 0.0;
  tmp_2[37] = 0.0;
  tmp_2[45] = 2.0;
  tmp_2[53] = 0.0;
  tmp_2[61] = 0.0;
  tmp_2[6] = 0.0;
  tmp_2[14] = 0.0;
  tmp_2[22] = 0.0;
  tmp_2[30] = 0.0;
  tmp_2[38] = 0.0;
  tmp_2[46] = 0.0;
  tmp_2[54] = 50.0;
  tmp_2[62] = 0.0;
  tmp_2[7] = 0.0;
  tmp_2[15] = 0.0;
  tmp_2[23] = 0.0;
  tmp_2[31] = 0.0;
  tmp_2[39] = 0.0;
  tmp_2[47] = 0.0;
  tmp_2[55] = 0.0;
  tmp_2[63] = 100.0;
  for (i = 0; i < 8; i++) {
    // MATLAB Function: '<Root>/GetBInvMatrix'
    jj = i << 3;
    for (iy = 7; iy >= 0; iy--) {
      b_ix = iy << 3;
      d_k = iy + jj;
      D46_tmp_tmp_1 = rtb_BMinv[d_k];
      if (D46_tmp_tmp_1 != 0.0) {
        rtb_BMinv[d_k] = D46_tmp_tmp_1 / x[iy + b_ix];
        for (ix = 0; ix < iy; ix++) {
          ijA = ix + jj;
          rtb_BMinv[ijA] -= x[ix + b_ix] * rtb_BMinv[d_k];
        }
      }
    }

    // Sum: '<S5>/Minus1' incorporates:
    //   Inport generated from: '<Root>/InBus1_Inport_2'
    //   Inport generated from: '<Root>/InBus_Inport_1'
    //   Sum: '<S5>/Minus'
    //
    _mm_storeu_pd(&tmp_7[0], _mm_sub_pd(_mm_set_pd(rtU.InBus_dqd[i],
      rtU.InBus_qd[i]), _mm_set_pd(rtU.InBus1_Velocities[i],
      rtU.InBus1_Positions[i])));

    // Sum: '<S5>/Minus' incorporates:
    //   Inport generated from: '<Root>/InBus_Inport_1'

    tmp_0[i] = tmp_7[0];

    // Sum: '<S5>/Minus1' incorporates:
    //   Inport generated from: '<Root>/InBus_Inport_1'

    tmp_1[i] = tmp_7[1];

    // MATLAB Function: '<S3>/PD Controller'
    tmp_3[i] = 0.0;
  }

  // MATLAB Function: '<S3>/PD Controller'
  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_1 = tmp_0[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5 = _mm_loadu_pd(&tmp[(d_k << 3) + i]);
      tmp_6 = _mm_loadu_pd(&tmp_3[i]);
      _mm_storeu_pd(&tmp_3[i], _mm_add_pd(_mm_mul_pd(tmp_5, _mm_set1_pd
        (D46_tmp_tmp_1)), tmp_6));
    }
  }

  std::memset(&tmp_0[0], 0, sizeof(real_T) << 3U);
  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_1 = tmp_1[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5 = _mm_loadu_pd(&tmp_2[(d_k << 3) + i]);
      tmp_6 = _mm_loadu_pd(&tmp_0[i]);
      _mm_storeu_pd(&tmp_0[i], _mm_add_pd(_mm_mul_pd(tmp_5, _mm_set1_pd
        (D46_tmp_tmp_1)), tmp_6));
    }
  }

  for (d_k = 0; d_k <= 6; d_k += 2) {
    // MATLAB Function: '<S3>/PD Controller' incorporates:
    //   Inport generated from: '<Root>/InBus_Inport_1'
    //   Sum: '<S3>/Add1'
    //   Sum: '<S3>/Sum'

    tmp_5 = _mm_loadu_pd(&tmp_3[d_k]);
    tmp_6 = _mm_loadu_pd(&tmp_0[d_k]);

    // Sum: '<S3>/Add1' incorporates:
    //   Inport generated from: '<Root>/InBus_Inport_1'
    //   MATLAB Function: '<S3>/PD Controller'
    //   Sum: '<S3>/Sum'

    tmp_4 = _mm_loadu_pd(&rtb_fx[d_k]);
    _mm_storeu_pd(&tmp_1[d_k], _mm_sub_pd(_mm_add_pd(_mm_add_pd(tmp_5, tmp_6),
      _mm_loadu_pd(&rtU.InBus_ddqd[d_k])), tmp_4));

    // Product: '<S3>/Matrix Multiply' incorporates:
    //   Inport generated from: '<Root>/InBus_Inport_1'
    //   Sum: '<S3>/Add1'
    //   Sum: '<S3>/Sum'

    _mm_storeu_pd(&rtb_ginv_0[d_k], _mm_set1_pd(0.0));
  }

  for (d_k = 0; d_k < 8; d_k++) {
    // Product: '<S3>/Matrix Multiply'
    D46_tmp_tmp_1 = tmp_1[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5 = _mm_loadu_pd(&rtb_ginv[(d_k << 3) + i]);
      tmp_6 = _mm_loadu_pd(&rtb_ginv_0[i]);
      _mm_storeu_pd(&rtb_ginv_0[i], _mm_add_pd(_mm_mul_pd(tmp_5, _mm_set1_pd
        (D46_tmp_tmp_1)), tmp_6));
    }

    // Product: '<Root>/Matrix Multiply' incorporates:
    //   Outport generated from: '<Root>/Output2'

    rtY.Output2[d_k] = 0.0;
  }

  // Product: '<Root>/Matrix Multiply' incorporates:
  //   Outport generated from: '<Root>/Output2'

  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_1 = rtb_ginv_0[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5 = _mm_loadu_pd(&rtb_BMinv[(d_k << 3) + i]);
      tmp_6 = _mm_loadu_pd(&rtY.Output2[i]);
      _mm_storeu_pd(&rtY.Output2[i], _mm_add_pd(_mm_mul_pd(tmp_5, _mm_set1_pd
        (D46_tmp_tmp_1)), tmp_6));
    }
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The absolute time is the multiplication of "clockTick0"
  //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
  //  overflow during the application lifespan selected.

  (&rtM)->Timing.t[0] =
    ((time_T)(++(&rtM)->Timing.clockTick0)) * (&rtM)->Timing.stepSize0;

  {
    // Update absolute timer for sample time: [0.01s, 0.0s]
    // The "clockTick1" counts the number of times the code of this task has
    //  been executed. The resolution of this integer timer is 0.01, which is the step size
    //  of the task. Size of "clockTick1" ensures timer will not overflow during the
    //  application lifespan selected.

    (&rtM)->Timing.clockTick1++;
  }
}

// Model initialize function
void PD::initialize()
{
  // Registration code
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&rtM)->solverInfo, &(&rtM)->Timing.simTimeStep);
    rtsiSetTPtr(&(&rtM)->solverInfo, (&rtM)->getTPtrPtr());
    rtsiSetStepSizePtr(&(&rtM)->solverInfo, &(&rtM)->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&(&rtM)->solverInfo, (&rtM)->getErrorStatusPtr());
    rtsiSetRTModelPtr(&(&rtM)->solverInfo, (&rtM));
  }

  rtsiSetSimTimeStep(&(&rtM)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&rtM)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&rtM)->solverInfo, false);
  rtsiSetSolverName(&(&rtM)->solverInfo,"FixedStepDiscrete");
  (&rtM)->setTPtr(&(&rtM)->Timing.tArray[0]);
  (&rtM)->Timing.stepSize0 = 0.01;
}

time_T** PD::RT_MODEL::getTPtrPtr()
{
  return &(Timing.t);
}

const char_T* PD::RT_MODEL::getErrorStatus() const
{
  return (errorStatus);
}

void PD::RT_MODEL::setErrorStatus(const char_T* const aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

time_T* PD::RT_MODEL::getTPtr() const
{
  return (Timing.t);
}

void PD::RT_MODEL::setTPtr(time_T* aTPtr)
{
  (Timing.t = aTPtr);
}

const char_T** PD::RT_MODEL::getErrorStatusPtr()
{
  return &errorStatus;
}

boolean_T PD::RT_MODEL::isMajorTimeStep() const
{
  return ((Timing.simTimeStep) == MAJOR_TIME_STEP);
}

boolean_T PD::RT_MODEL::isMinorTimeStep() const
{
  return ((Timing.simTimeStep) == MINOR_TIME_STEP);
}

// Constructor
PD::PD() :
  rtU(),
  rtY(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
PD::~PD() = default;

// Real-Time Model get method
PD::RT_MODEL * PD::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
