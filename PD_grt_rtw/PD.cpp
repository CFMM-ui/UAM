/*
 * PD.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PD".
 *
 * Model version              : 1.68
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Thu Oct 22 16:17:52 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "PD.h"
#include "rtwtypes.h"
#include <cmath>
#include <emmintrin.h>
#include <cstring>
#include "PD_private.h"

/* Function for MATLAB Function: '<S1>/MATLAB Function1' */
void PD::PD_mldivide_j(const real_T A[64], real_T B[8])
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

/* Model step function */
void PD::step()
{
  __m128d tmp_5f;
  __m128d tmp_i;
  __m128d tmp_j;
  __m128d tmp_k;
  __m128d tmp_l;
  real_T tmp_1[64];
  real_T tmp_4[64];
  real_T x[64];
  real_T tmp_2[8];
  real_T tmp_3[8];
  real_T tmp_h[2];
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
  real_T D14_tmp_g;
  real_T D14_tmp_h;
  real_T D14_tmp_i;
  real_T D14_tmp_j;
  real_T D14_tmp_k;
  real_T D14_tmp_tmp;
  real_T D14_tmp_tmp_0;
  real_T D14_tmp_tmp_1;
  real_T D14_tmp_tmp_2;
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
  real_T D27_tmp;
  real_T D27_tmp_0;
  real_T D27_tmp_1;
  real_T D27_tmp_2;
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
  real_T D45;
  real_T D45_tmp;
  real_T D45_tmp_0;
  real_T D45_tmp_1;
  real_T D46;
  real_T D46_tmp;
  real_T D46_tmp_0;
  real_T D46_tmp_1;
  real_T D46_tmp_10;
  real_T D46_tmp_11;
  real_T D46_tmp_12;
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
  real_T D46_tmp_p;
  real_T D46_tmp_q;
  real_T D46_tmp_r;
  real_T D46_tmp_s;
  real_T D46_tmp_t;
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
  real_T D46_tmp_tmp_a;
  real_T D46_tmp_tmp_b;
  real_T D46_tmp_tmp_c;
  real_T D46_tmp_tmp_d;
  real_T D46_tmp_tmp_e;
  real_T D46_tmp_tmp_f;
  real_T D46_tmp_u;
  real_T D46_tmp_v;
  real_T D46_tmp_w;
  real_T D46_tmp_x;
  real_T D46_tmp_y;
  real_T D46_tmp_z;
  real_T D47;
  real_T D47_tmp;
  real_T D47_tmp_0;
  real_T D47_tmp_1;
  real_T D47_tmp_2;
  real_T D47_tmp_3;
  real_T D47_tmp_4;
  real_T D47_tmp_5;
  real_T D47_tmp_6;
  real_T D47_tmp_tmp_tmp;
  real_T D48;
  real_T D48_tmp;
  real_T D48_tmp_0;
  real_T D48_tmp_1;
  real_T D48_tmp_tmp;
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
  real_T D56_tmp_r;
  real_T D56_tmp_s;
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
  real_T D67_tmp;
  real_T ginv_tmp;
  real_T ginv_tmp_0;
  real_T ginv_tmp_1;
  real_T ginv_tmp_2;
  real_T ginv_tmp_3;
  real_T ginv_tmp_4;
  real_T ginv_tmp_5;
  real_T ginv_tmp_6;
  real_T ginv_tmp_7;
  real_T ginv_tmp_8;
  real_T ginv_tmp_9;
  real_T ginv_tmp_a;
  real_T ginv_tmp_b;
  real_T ginv_tmp_c;
  real_T ginv_tmp_d;
  real_T ginv_tmp_e;
  real_T ginv_tmp_f;
  real_T ginv_tmp_g;
  real_T ginv_tmp_h;
  real_T ginv_tmp_i;
  real_T ginv_tmp_j;
  real_T ginv_tmp_k;
  real_T ginv_tmp_l;
  real_T ginv_tmp_tmp;
  real_T ginv_tmp_tmp_0;
  real_T ginv_tmp_tmp_1;
  real_T ginv_tmp_tmp_2;
  real_T ginv_tmp_tmp_3;
  real_T ginv_tmp_tmp_4;
  real_T ginv_tmp_tmp_5;
  real_T s;
  real_T smax;
  real_T tmp;
  real_T tmp_0;
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
  real_T tmp_5;
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
  real_T tmp_5b;
  real_T tmp_5c;
  real_T tmp_5d;
  real_T tmp_5e;
  real_T tmp_5g;
  real_T tmp_5h;
  real_T tmp_5i;
  real_T tmp_5j;
  real_T tmp_5k;
  real_T tmp_5l;
  real_T tmp_5m;
  real_T tmp_5n;
  real_T tmp_5o;
  real_T tmp_5p;
  real_T tmp_5q;
  real_T tmp_5r;
  real_T tmp_5s;
  real_T tmp_5t;
  real_T tmp_5u;
  real_T tmp_5v;
  real_T tmp_5w;
  real_T tmp_5x;
  real_T tmp_5y;
  real_T tmp_5z;
  real_T tmp_6;
  real_T tmp_60;
  real_T tmp_61;
  real_T tmp_62;
  real_T tmp_63;
  real_T tmp_64;
  real_T tmp_65;
  real_T tmp_66;
  real_T tmp_67;
  real_T tmp_68;
  real_T tmp_7;
  real_T tmp_8;
  real_T tmp_9;
  real_T tmp_a;
  real_T tmp_b;
  real_T tmp_c;
  real_T tmp_d;
  real_T tmp_e;
  real_T tmp_f;
  real_T tmp_g;
  real_T tmp_m;
  real_T tmp_n;
  real_T tmp_o;
  real_T tmp_p;
  real_T tmp_q;
  real_T tmp_r;
  real_T tmp_s;
  real_T tmp_t;
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
  int32_T c_ix;
  int32_T d;
  int32_T d_k;
  int32_T i;
  int32_T ijA;
  int32_T ix;
  int32_T iy;
  int32_T jj;
  int8_T ipiv[8];
  int8_T p[8];
  int8_T ipiv_0;

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   *  MATLAB Function: '<Root>/GetBInvMatrix'
   * */
  /* :  DM = DMatrix(q, HexaConstants, ArmConstants); */
  /* 'DMatrix:3' mb  = HexaConstants.Mass; */
  /* 'DMatrix:4' ml1 = ArmConstants.Mass1; */
  /* 'DMatrix:5' ml2 = ArmConstants.Mass2; */
  /* 'DMatrix:7' L   = ArmConstants.Hexa_to_joint_L; */
  /* 'DMatrix:9' l1  = ArmConstants.l1_dim(1); */
  /* 'DMatrix:11' c1  = ArmConstants.MC1; */
  /* 'DMatrix:12' c2  = ArmConstants.MC2; */
  /* 'DMatrix:14' Hb = HexaConstants.Inertia; */
  /* 'DMatrix:15' Hbx = Hb(1, 1); */
  /* 'DMatrix:15' Hby = Hb(2, 2); */
  /* 'DMatrix:15' Hbz = Hb(3, 3); */
  /* 'DMatrix:17' H1 = ArmConstants.Inertia1; */
  /* 'DMatrix:18' H1xx = H1(1, 1); */
  /* 'DMatrix:18' H1yy = H1(2, 2); */
  /* 'DMatrix:18' H1zz = H1(3, 3); */
  /* 'DMatrix:19' H1xy = H1(1, 2); */
  /* 'DMatrix:19' H1yz = H1(2, 3); */
  /* 'DMatrix:19' H1zx = H1(1, 3); */
  /* 'DMatrix:21' H2 = ArmConstants.Inertia2; */
  /* 'DMatrix:22' H2xx = H2(1, 1); */
  /* 'DMatrix:22' H2yy = H2(2, 2); */
  /* 'DMatrix:22' H2zz = H2(3, 3); */
  /* 'DMatrix:23' H2xy = H2(1, 2); */
  /* 'DMatrix:23' H2yz = H2(2, 3); */
  /* 'DMatrix:23' H2zx = H2(1, 3); */
  /* 'DMatrix:25' phi = xi(4); */
  /* 'DMatrix:26' th  = xi(5); */
  /* 'DMatrix:27' psi = xi(6); */
  /* 'DMatrix:28' q1  = xi(7); */
  /* 'DMatrix:29' q2  = xi(8); */
  /* 'DMatrix:31' [D11, D12, D13, D14, D15, D16, D17, D18] = get_D1(); */
  /* 'DMatrix:50' D11=mb+ml1+ml2; */
  /* 'DMatrix:51' D12=0; */
  /* 'DMatrix:52' D13=0; */
  /* 'DMatrix:53' D14=sin(phi)*(sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))+ ... */
  /* 'DMatrix:54'   cos(psi)*(L*(ml1+ml2)+c2*ml2*cos(q1+q2))*sin(th))+cos(phi)*(- ... */
  /* 'DMatrix:55'   L*(ml1+ml2)*sin(psi)+c2*ml2*sin(psi)*sin(q1)*sin(q2)+cos(psi)*( ... */
  /* 'DMatrix:56'   c1*ml1+l1*ml2+c2*ml2*cos(q2))*sin(q1)*sin(th))+cos(q1)*((c1*ml1+ ... */
  /* 'DMatrix:57'   l1*ml2)*cos(psi)*sin(phi)*sin(th)+cos(phi)*(-(c1*ml1+l1*ml2+ ... */
  /* 'DMatrix:58'   c2*ml2*cos(q2))*sin(psi)+c2*ml2*cos(psi)*sin(q2)*sin(th))); */
  smax = std::sin(PD_U.InBus1_Positions[5]);
  D14_tmp = std::sin(PD_U.InBus1_Positions[6]);
  s = std::cos(PD_U.InBus1_Positions[5]);
  D14_tmp_0 = std::sin(PD_U.InBus1_Positions[4]);
  D14_tmp_1 = std::sin(PD_U.InBus1_Positions[3]);
  D14_tmp_2 = std::cos(PD_U.InBus1_Positions[3]);
  D14_tmp_3 = std::cos(PD_U.InBus1_Positions[7]);
  D14_tmp_4 = std::sin(PD_U.InBus1_Positions[7]);
  D14_tmp_tmp = PD_U.InBus1_Positions[6] + PD_U.InBus1_Positions[7];
  D14_tmp_5 = std::sin(D14_tmp_tmp);
  D14_tmp_6 = std::cos(PD_U.InBus1_Positions[6]);
  D14_tmp_7 = std::cos(D14_tmp_tmp);
  D14_tmp_8 = PD_P.ArmConstants.MC2 * PD_P.ArmConstants.Mass2;
  D14_tmp_tmp_0 = PD_P.ArmConstants.MC1 * PD_P.ArmConstants.Mass1;
  D14_tmp_9 = PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 + D14_tmp_tmp_0;
  D14_tmp_a = PD_P.ArmConstants.Mass1 + PD_P.ArmConstants.Mass2;
  D14_tmp_b = D14_tmp_8 * D14_tmp_3 + D14_tmp_9;
  D14_tmp_c = D14_tmp_a * PD_P.ArmConstants.Hexa_to_joint_L;
  D14_tmp_d = D14_tmp_8 * D14_tmp_7;
  D14_tmp_tmp_1 = D14_tmp_9 * D14_tmp;
  D14_tmp_tmp_2 = D14_tmp_8 * D14_tmp_5;
  D14_tmp_e = D14_tmp_tmp_1 + D14_tmp_tmp_2;
  D14_tmp_f = D14_tmp_e * smax;
  D14_tmp_g = D14_tmp_b * s;
  D14_tmp_h = D14_tmp_8 * smax;
  D14_tmp_i = D14_tmp_8 * s * D14_tmp_4 * D14_tmp_0;
  D14_tmp_j = (-D14_tmp_b * smax + D14_tmp_i) * D14_tmp_2;
  D14_tmp_k = D14_tmp_a * -PD_P.ArmConstants.Hexa_to_joint_L;
  D14 = (((D14_tmp_h * D14_tmp * D14_tmp_4 + D14_tmp_k * smax) + D14_tmp_g *
          D14_tmp * D14_tmp_0) * D14_tmp_2 + ((D14_tmp_c + D14_tmp_d) * s *
          D14_tmp_0 + D14_tmp_f) * D14_tmp_1) + (D14_tmp_9 * s * D14_tmp_1 *
    D14_tmp_0 + D14_tmp_j) * D14_tmp_6;

  /* 'DMatrix:59' D15=-cos(psi)*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+ ... */
  /* 'DMatrix:60'   c2*ml2*cos(phi+q1+q2))*cos(th); */
  D15_tmp = std::cos(PD_U.InBus1_Positions[4]);
  D15_tmp_tmp = PD_U.InBus1_Positions[3] + PD_U.InBus1_Positions[6];
  D15_tmp_0 = std::cos(D15_tmp_tmp);
  D15_tmp_tmp_0 = D15_tmp_tmp + PD_U.InBus1_Positions[7];
  D15_tmp_1 = std::cos(D15_tmp_tmp_0);
  D15_tmp_tmp_1 = D14_tmp_9 * D15_tmp_0;
  D15_tmp_tmp_2 = D14_tmp_8 * D15_tmp_1;
  D15_tmp_2 = (D14_tmp_c * D14_tmp_2 + D15_tmp_tmp_1) + D15_tmp_tmp_2;
  D15 = D15_tmp_2 * -s * D15_tmp;

  /* 'DMatrix:61' D16=cos(phi)*(-cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+ ... */
  /* 'DMatrix:62'   q2))+(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin( ... */
  /* 'DMatrix:63'   psi)*sin(th))+-sin(phi)*(cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1* ... */
  /* 'DMatrix:64'   ml2)*cos(q1)+c2*ml2*cos(q1+q2))+sin(psi)*((c1*ml1+l1*ml2)*sin(q1) ... */
  /* 'DMatrix:65'   +c2*ml2*sin(q1+q2))*sin(th)); */
  D16_tmp_tmp = D14_tmp_9 * D14_tmp_6;
  D16_tmp = (D16_tmp_tmp + D14_tmp_c) + D14_tmp_d;
  D16_tmp_0 = D16_tmp * s;
  D16_tmp_1 = D16_tmp * smax;
  D16_tmp_2 = D16_tmp_1 * D14_tmp_0;
  D16_tmp_3 = D14_tmp_f * D14_tmp_0 + D16_tmp_0;
  D16 = (D14_tmp_e * -s + D16_tmp_2) * D14_tmp_2 + D16_tmp_3 * -D14_tmp_1;

  /* 'DMatrix:66' D17=ml2*(l1*sin(q1)+c2*sin(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos( ... */
  /* 'DMatrix:67'   psi)*sin(th))+c1*ml1*sin(phi)*(sin(psi)*sin(q1)+cos(psi)*cos(q1)* ... */
  /* 'DMatrix:68'   sin(th))+ml2*(l1*cos(q1)+c2*cos(q1+q2))*(-cos(phi)*sin(psi)+ ... */
  /* 'DMatrix:69'   cos(psi)*sin(phi)*sin(th))+c1*ml1*cos(phi)*(-cos(q1)*sin(psi) ... */
  /* 'DMatrix:70'   +cos(psi)*sin(q1)*sin(th)); */
  D17_tmp_tmp_0 = D14_tmp_1 * smax;
  D17_tmp_tmp_1 = D14_tmp_2 * s;
  D17_tmp = D17_tmp_tmp_1 * D14_tmp_0 + D17_tmp_tmp_0;
  D17_tmp_0 = PD_P.ArmConstants.MC2 * D14_tmp_5;
  D17_tmp_tmp = s * D14_tmp_1;
  D17_tmp_tmp_2 = -D14_tmp_2 * smax;
  D17_tmp_1 = D17_tmp_tmp * D14_tmp_0 + D17_tmp_tmp_2;
  D17_tmp_2 = PD_P.ArmConstants.MC2 * D14_tmp_7;
  D17_tmp_3 = PD_P.ArmConstants.l1_dim * D14_tmp_6;
  D17_tmp_4 = PD_P.ArmConstants.l1_dim * D14_tmp + D17_tmp_0;
  D17_tmp_5 = D17_tmp_4 * PD_P.ArmConstants.Mass2;
  D17_tmp_6 = D17_tmp_3 + D17_tmp_2;
  D17_tmp_tmp_3 = smax * D14_tmp;
  D17_tmp_tmp_4 = s * D14_tmp_6;
  D17_tmp_7 = D17_tmp_tmp_4 * D14_tmp_0 + D17_tmp_tmp_3;
  D17_tmp_8 = s * D14_tmp * D14_tmp_0 + -D14_tmp_6 * smax;
  D17 = ((D14_tmp_tmp_0 * D14_tmp_1 * D17_tmp_7 + D17_tmp_5 * D17_tmp) +
         D17_tmp_6 * PD_P.ArmConstants.Mass2 * D17_tmp_1) + D14_tmp_tmp_0 *
    D14_tmp_2 * D17_tmp_8;

  /* 'DMatrix:71' D18=ml2*(c2*sin(q1+q2)*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+ ... */
  /* 'DMatrix:72'   c2*cos(q1+q2)*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th))); */
  D18_tmp = D17_tmp * D17_tmp_0 + D17_tmp_1 * D17_tmp_2;
  D18 = D18_tmp * PD_P.ArmConstants.Mass2;

  /* 'DMatrix:32' [D22, D23, D24, D25, D26, D27, D28] = get_D2(); */
  /* 'DMatrix:76' D22=mb+ml1+ml2; */
  /* 'DMatrix:77' D23=0; */
  /* 'DMatrix:78' D24=ml2*cos(psi)*(L*cos(phi)+l1*cos(phi+q1)+c2*cos(phi+q1+q2))*cos(th) ... */
  /* 'DMatrix:79'   ^2+ml1*sin(phi)*(-c1*cos(psi)*sin(q1)+(L+c1*cos(q1))*sin( ... */
  /* 'DMatrix:80'   psi)*sin(th))+ml1*cos(phi)*(cos(psi)*(L+c1*cos(q1))+c1*sin(psi)* ... */
  /* 'DMatrix:81'   sin(q1)*sin(th))+ml2*sin(th)*((L+l1*cos(q1)+c2*cos(q1+q2))*(sin( ... */
  /* 'DMatrix:82'   phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))-(l1*sin(q1)+c2*sin( ... */
  /* 'DMatrix:83'   q1+q2))*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th))); */
  D24_tmp = PD_P.ArmConstants.MC1 * D14_tmp_6 +
    PD_P.ArmConstants.Hexa_to_joint_L;
  D24_tmp_0 = (D17_tmp_3 + PD_P.ArmConstants.Hexa_to_joint_L) + D17_tmp_2;
  D24_tmp_1 = D17_tmp_1 * D17_tmp_4;
  D17_tmp_3 = D15_tmp * D15_tmp;
  D24_tmp_2 = PD_P.ArmConstants.Hexa_to_joint_L * D14_tmp_2;
  D24_tmp_3 = (PD_P.ArmConstants.l1_dim * D15_tmp_0 + D24_tmp_2) +
    PD_P.ArmConstants.MC2 * D15_tmp_1;
  D24 = (((D24_tmp * smax * D14_tmp_0 + -PD_P.ArmConstants.MC1 * s * D14_tmp) *
          (PD_P.ArmConstants.Mass1 * D14_tmp_1) + PD_P.ArmConstants.Mass2 * s *
          D24_tmp_3 * D17_tmp_3) + (PD_P.ArmConstants.MC1 * smax * D14_tmp *
          D14_tmp_0 + D24_tmp * s) * (PD_P.ArmConstants.Mass1 * D14_tmp_2)) +
    (D24_tmp_0 * D17_tmp - D24_tmp_1) * (PD_P.ArmConstants.Mass2 * D14_tmp_0);

  /* 'DMatrix:84' D25=-(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2* ... */
  /* 'DMatrix:85'   cos(phi+q1+q2))*cos(th)*sin(psi); */
  D25 = -D15_tmp_2 * D15_tmp * smax;

  /* 'DMatrix:86' D26=-ml1*(L+c1*cos(q1))*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin( ... */
  /* 'DMatrix:87'   th))-ml2*(L+l1*cos(q1)+c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos( ... */
  /* 'DMatrix:88'   phi)*cos(psi)*sin(th))+c1*ml1*sin(q1)*(-cos(phi)*sin(psi)+ ... */
  /* 'DMatrix:89'   cos(psi)*sin(phi)*sin(th))+ml2*(l1*sin(q1)+c2*sin(q1+q2))*(- ... */
  /* 'DMatrix:90'   cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)); */
  D14_tmp_tmp_0 = ((D24_tmp * -PD_P.ArmConstants.Mass1 * D17_tmp - D24_tmp_0 *
                    PD_P.ArmConstants.Mass2 * D17_tmp) + D14_tmp_tmp_0 * D14_tmp
                   * D17_tmp_1) + D17_tmp_5 * D17_tmp_1;

  /* 'DMatrix:91' D27=-((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*(cos(psi)*sin( ... */
  /* 'DMatrix:92'   phi)-cos(phi)*sin(psi)*sin(th))+(c1*ml1+l1*ml2)*cos(q1)*( ... */
  /* 'DMatrix:93'   cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th))+c2*ml2*cos(q1+q2)*( ... */
  /* 'DMatrix:94'   cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th)); */
  D17_tmp_tmp_0 = D17_tmp_tmp_0 * D14_tmp_0 + D17_tmp_tmp_1;
  D27_tmp = D14_tmp_2 * smax * D14_tmp_0;
  D17_tmp_tmp_1 = D17_tmp_tmp - D27_tmp;
  D27_tmp_0 = -D14_tmp_e;
  D27_tmp_1 = D16_tmp_tmp * D17_tmp_tmp_0;
  D27_tmp_2 = D17_tmp_tmp_0 * D14_tmp_d;
  D17_tmp_5 = (D27_tmp_0 * D17_tmp_tmp_1 + D27_tmp_1) + D27_tmp_2;

  /* 'DMatrix:95' D28=ml2*(c2*sin(q1+q2)*(-cos(psi)*sin(phi)+cos(phi)*sin(psi)*sin( ... */
  /* 'DMatrix:96'   th))+c2*cos(q1+q2)*(cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th))); */
  D27_tmp += -s * D14_tmp_1;
  D17_tmp_0 = D27_tmp * D17_tmp_0 + D17_tmp_tmp_0 * D17_tmp_2;
  D17_tmp_2 = D17_tmp_0 * PD_P.ArmConstants.Mass2;

  /* 'DMatrix:33' [D33, D34, D35, D36, D37, D38] = get_D3(); */
  /* 'DMatrix:100' D33=mb+ml1+ml2; */
  /* 'DMatrix:101' D34=cos(th)*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2* ... */
  /* 'DMatrix:102'   ml2*sin(phi+q1+q2)); */
  D34_tmp = std::sin(D15_tmp_tmp);
  D34_tmp_0 = std::sin(D15_tmp_tmp_0);
  D34_tmp_1 = D14_tmp_9 * D34_tmp;
  D34_tmp_2 = D14_tmp_8 * D34_tmp_0;
  D34_tmp_3 = (D14_tmp_c * D14_tmp_1 + D34_tmp_1) + D34_tmp_2;
  D34 = D34_tmp_3 * D15_tmp;

  /* 'DMatrix:103' D35=(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'DMatrix:104'   q1+q2))*sin(th); */
  D35 = D15_tmp_2 * D14_tmp_0;

  /* 'DMatrix:105' D36=0; */
  /* 'DMatrix:106' D37=cos(th)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2)); */
  D37_tmp = D34_tmp_1 + D34_tmp_2;
  D37 = D37_tmp * D15_tmp;

  /* 'DMatrix:107' D38=c2*ml2*cos(th)*sin(phi+q1+q2); */
  D38 = D14_tmp_8 * D15_tmp * D34_tmp_0;

  /* 'DMatrix:34' [D44, D45, D46, D47, D48] = get_D4(); */
  /* 'DMatrix:111' D44=H1zz+H2zz+Hbx+c1^2*ml1+L^2*ml1+c2^2*ml2+L^2*ml2+l1^2*ml2+2* ... */
  /* 'DMatrix:112'   L*(c1*ml1+l1*ml2)*cos(q1)+2*c2*l1*ml2*cos(q2)+2*c2*L*ml2* ... */
  /* 'DMatrix:113'   cos(q1+q2); */
  /* 'DMatrix:114' D45=H1yz*cos(phi+q1)+H2yz*cos(phi+q1+q2)+H1zx*sin(phi+q1)+H2zx*sin(phi+ ... */
  /* 'DMatrix:115'   q1+q2); */
  D45_tmp = PD_P.ArmConstants.Inertia2[7] * D15_tmp_1;
  D45_tmp_0 = PD_P.ArmConstants.Inertia2[6] * D34_tmp_0;
  D45_tmp_1 = ((PD_P.ArmConstants.Inertia1[7] * D15_tmp_0 + D45_tmp) +
               PD_P.ArmConstants.Inertia1[6] * D34_tmp) + D45_tmp_0;
  D45 = D45_tmp_1;

  /* 'DMatrix:116' D46=(1/2)*(-H1zx*cos(phi+q1-th)-H2zx*cos(phi+q1+q2+(-1) ... */
  /* 'DMatrix:117'   *th)-H1zx*cos(phi+q1+th)-H2zx*cos(phi+q1+q2+th)+2*c1* ... */
  /* 'DMatrix:118'   L*ml1*sin(q1-th)+2*L*l1*ml2*sin(q1-th)+H1yz*sin(phi+ ... */
  /* 'DMatrix:119'   q1-th)+2*c2*l1*ml2*sin(q2-th)+2*c2*L*ml2*sin(q1+q2+( ... */
  /* 'DMatrix:120'   -1)*th)+H2yz*sin(phi+q1+q2-th)+(-2)*H1zz*sin(th)+(-2)*H2zz* ... */
  /* 'DMatrix:121'   sin(th)+(-2)*Hbx*sin(th)+(-2)*c1^2*ml1*sin(th)+(-2)*L^2*ml1* ... */
  /* 'DMatrix:122'   sin(th)+(-2)*c2^2*ml2*sin(th)+(-2)*L^2*ml2*sin(th)+(-2)*l1^2* ... */
  /* 'DMatrix:123'   ml2*sin(th)+(-2)*c1*L*ml1*sin(q1+th)+(-2)*L*l1*ml2*sin(q1+th)+ ... */
  /* 'DMatrix:124'   H1yz*sin(phi+q1+th)+(-2)*c2*l1*ml2*sin(q2+th)+(-2)*c2*L*ml2* ... */
  /* 'DMatrix:125'   sin(q1+q2+th)+H2yz*sin(phi+q1+q2+th)); */
  D46_tmp_tmp_7 = PD_U.InBus1_Positions[6] - PD_U.InBus1_Positions[4];
  D46_tmp = std::sin(D46_tmp_tmp_7);
  D46_tmp_tmp_6 = PD_U.InBus1_Positions[4] + PD_U.InBus1_Positions[6];
  D46_tmp_0 = std::sin(D46_tmp_tmp_6);
  D46_tmp_tmp = D15_tmp_tmp - PD_U.InBus1_Positions[4];
  D46_tmp_1 = std::cos(D46_tmp_tmp);
  D46_tmp_tmp_0 = D15_tmp_tmp_0 - PD_U.InBus1_Positions[4];
  D46_tmp_2 = std::cos(D46_tmp_tmp_0);
  D46_tmp_tmp_1 = D15_tmp_tmp + PD_U.InBus1_Positions[4];
  D46_tmp_3 = std::cos(D46_tmp_tmp_1);
  D46_tmp_tmp_2 = D15_tmp_tmp_0 + PD_U.InBus1_Positions[4];
  D46_tmp_4 = std::cos(D46_tmp_tmp_2);
  D46_tmp_5 = std::sin(D46_tmp_tmp);
  D46_tmp_6 = std::sin(D46_tmp_tmp_0);
  D46_tmp_7 = std::sin(D46_tmp_tmp_1);
  D46_tmp_8 = std::sin(D46_tmp_tmp_2);
  D46_tmp_tmp_8 = PD_U.InBus1_Positions[7] - PD_U.InBus1_Positions[4];
  D46_tmp_9 = std::sin(D46_tmp_tmp_8);
  D46_tmp_tmp_9 = D14_tmp_tmp - PD_U.InBus1_Positions[4];
  D46_tmp_a = std::sin(D46_tmp_tmp_9);
  D46_tmp_tmp_a = PD_U.InBus1_Positions[4] + PD_U.InBus1_Positions[7];
  D46_tmp_b = std::sin(D46_tmp_tmp_a);
  D46_tmp_tmp_b = D14_tmp_tmp + PD_U.InBus1_Positions[4];
  D46_tmp_c = std::sin(D46_tmp_tmp_b);
  D46_tmp_d = 2.0 * PD_P.ArmConstants.MC2;
  D46_tmp_tmp_3 = PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Hexa_to_joint_L;
  D46_tmp_e = D46_tmp_tmp_3 * -2.0;
  D46_tmp_f = -2.0 * PD_P.ArmConstants.MC2;
  D46_tmp_g = PD_P.ArmConstants.MC1 * PD_P.ArmConstants.MC1;
  D46_tmp_h = PD_P.ArmConstants.MC2 * PD_P.ArmConstants.MC2;
  D46_tmp_i = PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.l1_dim;
  D46_tmp_tmp_f = D46_tmp_d * PD_P.ArmConstants.l1_dim;
  D46_tmp_j = D46_tmp_tmp_f * PD_P.ArmConstants.Mass2;
  D46_tmp_tmp_f = 2.0 * PD_P.ArmConstants.MC1;
  D46_tmp_k = D46_tmp_tmp_f * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass1;
  D46_tmp_tmp_5 = 2.0 * PD_P.ArmConstants.Hexa_to_joint_L;
  D46_tmp_l = D46_tmp_tmp_5 * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  D46_tmp_m = D46_tmp_d * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass2;
  D46_tmp_tmp_4 = PD_P.ArmConstants.Inertia2[6] * D46_tmp_4;
  D46_tmp_n = ((-PD_P.ArmConstants.Inertia1[6] * D46_tmp_1 -
                PD_P.ArmConstants.Inertia2[6] * D46_tmp_2) -
               PD_P.ArmConstants.Inertia1[6] * D46_tmp_3) - D46_tmp_tmp_4;
  D46_tmp_o = PD_P.ArmConstants.Inertia1[7] * D46_tmp_5;
  D46_tmp_p = D46_tmp_j * D46_tmp_9;
  D46_tmp_q = PD_P.ArmConstants.Inertia2[7] * D46_tmp_6;
  D46_tmp_r = -2.0 * PD_P.ArmConstants.Inertia1[8] * D14_tmp_0;
  D46_tmp_s = -2.0 * PD_P.ArmConstants.Inertia2[8] * D14_tmp_0;
  D46_tmp_tmp_c = D46_tmp_g * -2.0;
  D46_tmp_t = D46_tmp_tmp_c * PD_P.ArmConstants.Mass1 * D14_tmp_0;
  D46_tmp_tmp_d = D46_tmp_h * -2.0;
  D46_tmp_u = D46_tmp_tmp_d * PD_P.ArmConstants.Mass2 * D14_tmp_0;
  D46_tmp_v = D46_tmp_i * -2.0 * PD_P.ArmConstants.Mass2 * D14_tmp_0;
  D46_tmp_w = PD_P.ArmConstants.Inertia1[7] * D46_tmp_7;
  D46_tmp_tmp_e = D46_tmp_f * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  D46_tmp_x = D46_tmp_tmp_e * D46_tmp_b;
  D46_tmp_y = PD_P.ArmConstants.Inertia2[7] * D46_tmp_8;
  D46_tmp_z = -2.0 * PD_P.ArmConstants.MC1;
  D46_tmp_10 = D46_tmp_z * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass1;
  D46_tmp_11 = -2.0 * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  D46_tmp_12 = D46_tmp_f * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass2;
  D46 = ((((((((((((((((((((D46_tmp_k * D46_tmp + D46_tmp_n) + D46_tmp_l *
    D46_tmp) + D46_tmp_o) + D46_tmp_p) + D46_tmp_m * D46_tmp_a) + D46_tmp_q) +
                      D46_tmp_r) + D46_tmp_s) + -2.0 *
                    PD_P.HexaConstants.Inertia[0] * D14_tmp_0) + D46_tmp_t) +
                  D46_tmp_e * PD_P.ArmConstants.Mass1 * D14_tmp_0) + D46_tmp_u)
                + D46_tmp_e * PD_P.ArmConstants.Mass2 * D14_tmp_0) + D46_tmp_v)
              + D46_tmp_10 * D46_tmp_0) + D46_tmp_11 * D46_tmp_0) + D46_tmp_w) +
           D46_tmp_x) + D46_tmp_12 * D46_tmp_c) + D46_tmp_y) * 0.5;

  /* 'DMatrix:126' D47=H1zz+H2zz+c1^2*ml1+c2^2*ml2+l1^2*ml2+L*(c1*ml1+l1*ml2)*cos(q1) ... */
  /* 'DMatrix:127'   +2*c2*l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2); */
  D46_tmp_e = D46_tmp_h * PD_P.ArmConstants.Mass2;
  D47_tmp_tmp_tmp = PD_P.ArmConstants.MC2 * PD_P.ArmConstants.Hexa_to_joint_L;
  D47_tmp_tmp_tmp *= PD_P.ArmConstants.Mass2;
  D47_tmp = D47_tmp_tmp_tmp * D14_tmp_7;
  D47_tmp_0 = D46_tmp_g * PD_P.ArmConstants.Mass1;
  D47_tmp_1 = D46_tmp_i * PD_P.ArmConstants.Mass2;
  D47_tmp_2 = PD_P.ArmConstants.Inertia1[8] + PD_P.ArmConstants.Inertia2[8];
  D47_tmp_3 = D46_tmp_j * D14_tmp_3;
  D47_tmp_4 = ((D47_tmp_0 + D47_tmp_2) + D46_tmp_e) + D47_tmp_1;
  D47_tmp_5 = D14_tmp_9 * PD_P.ArmConstants.Hexa_to_joint_L;
  D47_tmp_6 = D47_tmp_5 * D14_tmp_6 + D47_tmp_4;
  D47 = (D47_tmp_6 + D47_tmp_3) + D47_tmp;

  /* 'DMatrix:128' D48=H2zz+c2^2*ml2+c2*l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2); */
  D48_tmp = PD_P.ArmConstants.MC2 * PD_P.ArmConstants.l1_dim *
    PD_P.ArmConstants.Mass2;
  D48_tmp_tmp = D46_tmp_e + PD_P.ArmConstants.Inertia2[8];
  D48_tmp_0 = D48_tmp * D14_tmp_3 + D48_tmp_tmp;
  D48_tmp_1 = D48_tmp_0 + D47_tmp;
  D48 = D48_tmp_1;

  /* 'DMatrix:35' [D55, D56, D57, D58] = get_D5(); */
  /* 'DMatrix:132' D55=(1/2)*(H1xx+H1yy+H2xx+H2yy+Hby+Hbz+c1^2*ml1+L^2*ml1+c2^2*ml2+ ... */
  /* 'DMatrix:133'   L^2*ml2+l1^2*ml2+Hby*cos(2*phi)-Hbz*cos(2*phi)+L^2*ml1* ... */
  /* 'DMatrix:134'   cos(2*phi)+L^2*ml2*cos(2*phi)+2*L*(c1*ml1+l1*ml2)*cos(q1)+(-1) ... */
  /* 'DMatrix:135'   *H1xx*cos(2*(phi+q1))+H1yy*cos(2*(phi+q1))+c1^2*ml1*cos(2*(phi+ ... */
  /* 'DMatrix:136'   q1))+l1^2*ml2*cos(2*(phi+q1))+2*c1*L*ml1*cos(2*phi+q1)+2*L* ... */
  /* 'DMatrix:137'   l1*ml2*cos(2*phi+q1)+2*c2*l1*ml2*cos(q2)+2*c2*L*ml2*cos(q1+ ... */
  /* 'DMatrix:138'   q2)-H2xx*cos(2*(phi+q1+q2))+H2yy*cos(2*(phi+q1+q2))+c2^2* ... */
  /* 'DMatrix:139'   ml2*cos(2*(phi+q1+q2))+2*c2*L*ml2*cos(2*phi+q1+q2)+2*c2*l1* ... */
  /* 'DMatrix:140'   ml2*cos(2*(phi+q1)+q2)+2*H1xy*sin(2*(phi+q1))+2*H2xy*sin(2*(phi+ ... */
  /* 'DMatrix:141'   q1+q2))); */
  /* 'DMatrix:142' D56=(1/4)*((-2)*H1zx*cos(phi+q1-th)+(-2)*H1xy*cos(2*phi+2*q1+( ... */
  /* 'DMatrix:143'   -1)*th)+(-2)*H2zx*cos(phi+q1+q2-th)+(-2)*H2xy*cos(2*phi+2* ... */
  /* 'DMatrix:144'   q1+2*q2-th)+2*H1zx*cos(phi+q1+th)+(-2)*H1xy*cos(2*phi+2*q1+ ... */
  /* 'DMatrix:145'   th)+2*H2zx*cos(phi+q1+q2+th)+(-2)*H2xy*cos(2*phi+2*q1+2*q2+th)+ ... */
  /* 'DMatrix:146'   Hby*sin(2*phi-th)-Hbz*sin(2*phi-th)+L^2*ml1* ... */
  /* 'DMatrix:147'   sin(2*phi-th)+L^2*ml2*sin(2*phi-th)+2*H1yz*sin(phi+ ... */
  /* 'DMatrix:148'   q1-th)+2*c1*L*ml1*sin(2*phi+q1-th)+2*L*l1*ml2*sin( ... */
  /* 'DMatrix:149'   2*phi+q1-th)-H1xx*sin(2*phi+2*q1-th)+H1yy*sin(2* ... */
  /* 'DMatrix:150'   phi+2*q1-th)+c1^2*ml1*sin(2*phi+2*q1-th)+l1^2*ml2* ... */
  /* 'DMatrix:151'   sin(2*phi+2*q1-th)+2*H2yz*sin(phi+q1+q2-th)+2*c2*L* ... */
  /* 'DMatrix:152'   ml2*sin(2*phi+q1+q2-th)+2*c2*l1*ml2*sin(2*phi+2*q1+q2+(-1) ... */
  /* 'DMatrix:153'   *th)-H2xx*sin(2*phi+2*q1+2*q2-th)+H2yy*sin(2*phi+2* ... */
  /* 'DMatrix:154'   q1+2*q2-th)+c2^2*ml2*sin(2*phi+2*q1+2*q2-th)+Hby* ... */
  /* 'DMatrix:155'   sin(2*phi+th)-Hbz*sin(2*phi+th)+L^2*ml1*sin(2*phi+th)+ ... */
  /* 'DMatrix:156'   L^2*ml2*sin(2*phi+th)+(-2)*H1yz*sin(phi+q1+th)+2*c1*L*ml1*sin( ... */
  /* 'DMatrix:157'   2*phi+q1+th)+2*L*l1*ml2*sin(2*phi+q1+th)-H1xx*sin(2*phi+ ... */
  /* 'DMatrix:158'   2*q1+th)+H1yy*sin(2*phi+2*q1+th)+c1^2*ml1*sin(2*phi+2*q1+th)+ ... */
  /* 'DMatrix:159'   l1^2*ml2*sin(2*phi+2*q1+th)+(-2)*H2yz*sin(phi+q1+q2+th)+2*c2* ... */
  /* 'DMatrix:160'   L*ml2*sin(2*phi+q1+q2+th)+2*c2*l1*ml2*sin(2*phi+2*q1+q2+th)+( ... */
  /* 'DMatrix:161'   -1)*H2xx*sin(2*phi+2*q1+2*q2+th)+H2yy*sin(2*phi+2*q1+2*q2+th)+ ... */
  /* 'DMatrix:162'   c2^2*ml2*sin(2*phi+2*q1+2*q2+th)); */
  D56_tmp_tmp = 2.0 * PD_U.InBus1_Positions[3];
  D56_tmp_tmp_9 = D56_tmp_tmp - PD_U.InBus1_Positions[4];
  D56_tmp = std::sin(D56_tmp_tmp_9);
  D56_tmp_tmp_1 = D56_tmp_tmp + PD_U.InBus1_Positions[6];
  D56_tmp_tmp_6 = D56_tmp_tmp_1 - PD_U.InBus1_Positions[4];
  D56_tmp_0 = std::sin(D56_tmp_tmp_6);
  D56_tmp_tmp_tmp = 2.0 * PD_U.InBus1_Positions[6];
  D56_tmp_tmp_0 = D56_tmp_tmp + D56_tmp_tmp_tmp;
  D56_tmp_tmp_3 = D56_tmp_tmp_0 - PD_U.InBus1_Positions[4];
  D56_tmp_1 = std::sin(D56_tmp_tmp_3);
  D56_tmp_tmp_2 = 2.0 * PD_U.InBus1_Positions[7] + D56_tmp_tmp_0;
  D56_tmp_tmp_4 = D56_tmp_tmp_2 - PD_U.InBus1_Positions[4];
  D56_tmp_2 = std::sin(D56_tmp_tmp_4);
  D56_tmp_tmp_7 = D56_tmp_tmp + PD_U.InBus1_Positions[4];
  D56_tmp_3 = std::sin(D56_tmp_tmp_7);
  D56_tmp_tmp_8 = D56_tmp_tmp_1 + PD_U.InBus1_Positions[4];
  D56_tmp_4 = std::sin(D56_tmp_tmp_8);
  D56_tmp_tmp_5 = D56_tmp_tmp_0 + PD_U.InBus1_Positions[4];
  D56_tmp_5 = std::sin(D56_tmp_tmp_5);
  D56_tmp_tmp_2 += PD_U.InBus1_Positions[4];
  D56_tmp_6 = std::sin(D56_tmp_tmp_2);
  D56_tmp_7 = std::cos(D56_tmp_tmp_3);
  D56_tmp_8 = std::cos(D56_tmp_tmp_4);
  D56_tmp_9 = std::cos(D56_tmp_tmp_5);
  D56_tmp_a = std::cos(D56_tmp_tmp_2);
  D56_tmp_tmp_3 = D56_tmp_tmp_1 + PD_U.InBus1_Positions[7];
  D56_tmp_tmp_2 = D56_tmp_tmp_3 - PD_U.InBus1_Positions[4];
  D56_tmp_b = std::sin(D56_tmp_tmp_2);
  D56_tmp_tmp_0 += PD_U.InBus1_Positions[7];
  D56_tmp_tmp_4 = D56_tmp_tmp_0 - PD_U.InBus1_Positions[4];
  D56_tmp_c = std::sin(D56_tmp_tmp_4);
  D56_tmp_tmp_5 = D56_tmp_tmp_3 + PD_U.InBus1_Positions[4];
  D56_tmp_d = std::sin(D56_tmp_tmp_5);
  D56_tmp_tmp_0 += PD_U.InBus1_Positions[4];
  D56_tmp_e = std::sin(D56_tmp_tmp_0);
  D56_tmp_f = -2.0 * PD_P.ArmConstants.Inertia1[3];
  D56_tmp_g = -2.0 * PD_P.ArmConstants.Inertia2[3];
  D56_tmp_h = D46_tmp_tmp_3 * PD_P.ArmConstants.Mass1;
  D56_tmp_i = D46_tmp_tmp_3 * PD_P.ArmConstants.Mass2;
  D56_tmp_j = 2.0 * PD_P.ArmConstants.Inertia1[7];
  D56_tmp_k = 2.0 * PD_P.ArmConstants.Inertia2[7];
  D56_tmp_l = -2.0 * PD_P.ArmConstants.Inertia1[7];
  D56_tmp_m = -2.0 * PD_P.ArmConstants.Inertia2[7];
  D56_tmp_n = 2.0 * PD_P.ArmConstants.Inertia1[6];
  D56_tmp_o = 2.0 * PD_P.ArmConstants.Inertia2[6];
  D56_tmp_p = -2.0 * PD_P.ArmConstants.Inertia1[6];
  D56_tmp_q = -2.0 * PD_P.ArmConstants.Inertia2[6];
  D56_tmp_r = D56_tmp_p * D46_tmp_1 + D56_tmp_f * D56_tmp_7;
  D56_tmp_s = D56_tmp_q * D46_tmp_2;
  D56_tmp_tmp_a = PD_P.HexaConstants.Inertia[4] * D56_tmp;
  D56_tmp_tmp_b = PD_P.HexaConstants.Inertia[8] * D56_tmp;
  D56_tmp_tmp_c = D56_tmp_h * D56_tmp;
  D56_tmp_tmp_d = D56_tmp_i * D56_tmp;
  D56_tmp_tmp_e = PD_P.ArmConstants.Inertia1[0] * D56_tmp_1;
  D56_tmp_tmp_f = PD_P.ArmConstants.Inertia1[4] * D56_tmp_1;
  D56_tmp_tmp_g = D47_tmp_0 * D56_tmp_1;
  D56_tmp_tmp_h = D47_tmp_1 * D56_tmp_1;
  D56_tmp_tmp_i = PD_P.ArmConstants.Inertia2[0] * D56_tmp_2;
  D56_tmp_tmp_j = PD_P.ArmConstants.Inertia2[4] * D56_tmp_2;
  D56_tmp_tmp_k = D46_tmp_e * D56_tmp_2;
  D56_tmp_tmp_l = PD_P.HexaConstants.Inertia[4] * D56_tmp_3;
  D56_tmp_tmp_m = PD_P.HexaConstants.Inertia[8] * D56_tmp_3;
  D56_tmp_tmp_n = D56_tmp_h * D56_tmp_3;
  D56_tmp_tmp_o = PD_P.ArmConstants.Inertia1[0] * D56_tmp_5;
  D56_tmp_tmp_p = PD_P.ArmConstants.Inertia1[4] * D56_tmp_5;
  D56_tmp_tmp_q = D47_tmp_0 * D56_tmp_5;
  D56_tmp_tmp_r = D47_tmp_1 * D56_tmp_5;
  D56_tmp = ((((((((((((((((((((((((((((((((((((D56_tmp_r + D56_tmp_s) +
    D56_tmp_g * D56_tmp_8) + D56_tmp_n * D46_tmp_3) + D56_tmp_f * D56_tmp_9) +
    D56_tmp_o * D46_tmp_4) + D56_tmp_g * D56_tmp_a) + D56_tmp_tmp_a) -
    D56_tmp_tmp_b) + D56_tmp_tmp_c) + D56_tmp_tmp_d) + D56_tmp_j * D46_tmp_5) +
    D46_tmp_k * D56_tmp_0) + D46_tmp_l * D56_tmp_0) - D56_tmp_tmp_e) +
    D56_tmp_tmp_f) + D56_tmp_tmp_g) + D56_tmp_tmp_h) + D56_tmp_k * D46_tmp_6) +
    D46_tmp_m * D56_tmp_b) + D46_tmp_j * D56_tmp_c) - D56_tmp_tmp_i) +
    D56_tmp_tmp_j) + D56_tmp_tmp_k) + D56_tmp_tmp_l) - D56_tmp_tmp_m) +
                       D56_tmp_tmp_n) + D56_tmp_i * D56_tmp_3) + D56_tmp_l *
                     D46_tmp_7) + D46_tmp_k * D56_tmp_4) + D46_tmp_l * D56_tmp_4)
                  - D56_tmp_tmp_o) + D56_tmp_tmp_p) + D56_tmp_tmp_q) +
               D56_tmp_tmp_r) + D56_tmp_m * D46_tmp_8) + D46_tmp_m * D56_tmp_d)
    + D46_tmp_j * D56_tmp_e;
  D56_tmp_r = PD_P.ArmConstants.Inertia2[4] * D56_tmp_6;
  D56_tmp_s = D46_tmp_e * D56_tmp_6;
  D56 = (((-PD_P.ArmConstants.Inertia2[0] * D56_tmp_6 + D56_tmp) + D56_tmp_r) +
         D56_tmp_s) * 0.25;

  /* 'DMatrix:163' D57=H1yz*cos(phi+q1)+H2yz*cos(phi+q1+q2)+H1zx*sin(phi+q1)+H2zx*sin(phi+ ... */
  /* 'DMatrix:164'   q1+q2); */
  D57 = D45;

  /* 'DMatrix:165' D58=H2yz*cos(phi+q1+q2)+H2zx*sin(phi+q1+q2); */
  D45_tmp += D45_tmp_0;

  /* 'DMatrix:36' [D66, D67, D68] = get_D6(); */
  /* 'DMatrix:169' D66=Hbz*cos(phi)^2*cos(th)^2+Hby*cos(th)^2*sin(phi)^2+2*cos(phi)* ... */
  /* 'DMatrix:170'   cos(th)^2*sin(phi)*(-H1xy*cos(2*q1)+(-H1xx+H1yy)*cos(q1) ... */
  /* 'DMatrix:171'   *sin(q1))+cos(phi)^2*cos(th)^2*(H1xx*cos(q1)^2+H1yy*sin(q1)^2+( ... */
  /* 'DMatrix:172'   -1)*H1xy*sin(2*q1))+cos(th)^2*sin(phi)^2*(H1yy*cos(q1)^2+H1xx* ... */
  /* 'DMatrix:173'   sin(q1)^2+H1xy*sin(2*q1))+(1/2)*cos(phi)^2*cos(th)^2*(H2xx+H2yy+ ... */
  /* 'DMatrix:174'   (H2xx-H2yy)*cos(2*(q1+q2))+(-2)*H2xy*sin(2*(q1+q2)))+(1/2)* ... */
  /* 'DMatrix:175'   cos(th)^2*sin(phi)^2*(H2xx+H2yy+(-H2xx+H2yy)*cos(2*(q1+q2))+ ... */
  /* 'DMatrix:176'   2*H2xy*sin(2*(q1+q2)))+2*cos(phi)*cos(th)^2*sin(phi)*(- ... */
  /* 'DMatrix:177'   H2xy*cos(2*(q1+q2))+(1/2)*(-H2xx+H2yy)*sin(2*(q1+q2)))+H1zz* ... */
  /* 'DMatrix:178'   sin(th)^2+H2zz*sin(th)^2+Hbx*sin(th)^2+ml1*(-(L+c1*cos(q1)) ... */
  /* 'DMatrix:179'   *(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+c1*sin(q1)*(- ... */
  /* 'DMatrix:180'   cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)))^2+ml2*(-(L+l1* ... */
  /* 'DMatrix:181'   cos(q1)+c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th) ... */
  /* 'DMatrix:182'   )+(l1*sin(q1)+c2*sin(q1+q2))*(-cos(phi)*sin(psi)+cos(psi)*sin( ... */
  /* 'DMatrix:183'   phi)*sin(th)))^2+ml1*((L+c1*cos(q1))*(cos(psi)*sin(phi)-cos( ... */
  /* 'DMatrix:184'   phi)*sin(psi)*sin(th))+c1*sin(q1)*(cos(phi)*cos(psi)+sin(phi)*sin( ... */
  /* 'DMatrix:185'   psi)*sin(th)))^2+ml2*((L+l1*cos(q1)+c2*cos(q1+q2))*(cos(psi)*sin( ... */
  /* 'DMatrix:186'   phi)-cos(phi)*sin(psi)*sin(th))+(l1*sin(q1)+c2*sin(q1+q2))*( ... */
  /* 'DMatrix:187'   cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th)))^2+cos(phi)*(H1zx* ... */
  /* 'DMatrix:188'   cos(q1)-H1yz*sin(q1))*sin(2*th)-sin(phi)*(H1yz*cos(q1)+ ... */
  /* 'DMatrix:189'   H1zx*sin(q1))*sin(2*th)+cos(phi)*(H2zx*cos(q1+q2)-H2yz*sin( ... */
  /* 'DMatrix:190'   q1+q2))*sin(2*th)-sin(phi)*(H2yz*cos(q1+q2)+H2zx*sin(q1+q2)) ... */
  /* 'DMatrix:191'   *sin(2*th); */
  w_a_tmp = PD_P.ArmConstants.MC1 * D14_tmp;
  D45_tmp_0 = D17_tmp * -D24_tmp + D17_tmp_1 * w_a_tmp;
  w_a = D45_tmp_0;
  D24_tmp_1 += -D24_tmp_0 * D17_tmp;
  x_a = D24_tmp_1;
  D24_tmp = D17_tmp_tmp_1 * D24_tmp + D17_tmp_tmp_0 * w_a_tmp;
  D24_tmp_0 = D24_tmp_0 * D17_tmp_tmp_1 + D17_tmp_tmp_0 * D17_tmp_4;

  /* 'DMatrix:192' D67=(1/2)*(-H1zx*cos(phi+q1-th)-H2zx*cos(phi+q1+q2+(-1) ... */
  /* 'DMatrix:193'   *th)-H1zx*cos(phi+q1+th)-H2zx*cos(phi+q1+q2+th)+c1*L* ... */
  /* 'DMatrix:194'   ml1*sin(q1-th)+L*l1*ml2*sin(q1-th)+H1yz*sin(phi+q1+(-1) ... */
  /* 'DMatrix:195'   *th)+2*c2*l1*ml2*sin(q2-th)+c2*L*ml2*sin(q1+q2-th)+ ... */
  /* 'DMatrix:196'   H2yz*sin(phi+q1+q2-th)+(-2)*H1zz*sin(th)+(-2)*H2zz*sin(th)+( ... */
  /* 'DMatrix:197'   -2)*c1^2*ml1*sin(th)+(-2)*c2^2*ml2*sin(th)+(-2)*l1^2*ml2* ... */
  /* 'DMatrix:198'   sin(th)-c1*L*ml1*sin(q1+th)-L*l1*ml2*sin(q1+th)+H1yz* ... */
  /* 'DMatrix:199'   sin(phi+q1+th)+(-2)*c2*l1*ml2*sin(q2+th)-c2*L*ml2*sin(q1+ ... */
  /* 'DMatrix:200'   q2+th)+H2yz*sin(phi+q1+q2+th)); */
  w_a_tmp = PD_P.ArmConstants.MC1 * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass1;
  D67_tmp = PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.l1_dim *
    PD_P.ArmConstants.Mass2;
  D46_tmp_a *= D47_tmp_tmp_tmp;
  D46_tmp_c *= D47_tmp_tmp_tmp;
  D46_tmp_n = (((((((((((((((((w_a_tmp * D46_tmp + D46_tmp_n) + D67_tmp *
    D46_tmp) + D46_tmp_o) + D46_tmp_p) + D46_tmp_a) + D46_tmp_q) + D46_tmp_r) +
                        D46_tmp_s) + D46_tmp_t) + D46_tmp_u) + D46_tmp_v) -
                    w_a_tmp * D46_tmp_0) - D67_tmp * D46_tmp_0) + D46_tmp_w) +
                 D46_tmp_x) - D46_tmp_c) + D46_tmp_y) * 0.5;

  /* 'DMatrix:201' D68=(1/2)*(-H2zx*cos(phi+q1+q2-th)-H2zx*cos(phi+q1+q2+ ... */
  /* 'DMatrix:202'   th)+c2*l1*ml2*sin(q2-th)+c2*L*ml2*sin(q1+q2-th)+H2yz* ... */
  /* 'DMatrix:203'   sin(phi+q1+q2-th)+(-2)*H2zz*sin(th)+(-2)*c2^2*ml2*sin(th)+( ... */
  /* 'DMatrix:204'   -1)*c2*l1*ml2*sin(q2+th)-c2*L*ml2*sin(q1+q2+th)+H2yz*sin( ... */
  /* 'DMatrix:205'   phi+q1+q2+th)); */
  D46_tmp_o = -PD_P.ArmConstants.MC2 * PD_P.ArmConstants.l1_dim *
    PD_P.ArmConstants.Mass2;
  D46_tmp_q = (((((((((-PD_P.ArmConstants.Inertia2[6] * D46_tmp_2 -
                       D46_tmp_tmp_4) + D48_tmp * D46_tmp_9) + D46_tmp_a) +
                    D46_tmp_q) + D46_tmp_s) + D46_tmp_u) + D46_tmp_o * D46_tmp_b)
                - D46_tmp_c) + D46_tmp_y) * 0.5;

  /* 'DMatrix:37' [D77, D78] = get_D7(); */
  /* 'DMatrix:209' D77=H1zz+H2zz+c1^2*ml1+c2^2*ml2+l1^2*ml2+2*c2*l1*ml2*cos(q2); */
  /* 'DMatrix:210' D78=H2zz+c2^2*ml2+c2*l1*ml2*cos(q2); */
  /* 'DMatrix:38' D88=H2zz+c2^2*ml2; */
  /* 'DMatrix:40' DM = [D11, D12, D13, D14, D15, D16, D17, D18;... */
  /* 'DMatrix:41'       D12, D22, D23, D24, D25, D26, D27, D28;... */
  /* 'DMatrix:42'       D13, D23, D33, D34, D35, D36, D37, D38;... */
  /* 'DMatrix:43'       D14, D24, D34, D44, D45, D46, D47, D48;... */
  /* 'DMatrix:44'       D15, D25, D35, D45, D55, D56, D57, D58;... */
  /* 'DMatrix:45'       D16, D26, D36, D46, D56, D66, D67, D68;... */
  /* 'DMatrix:46'       D17, D27, D37, D47, D57, D67, D77, D78;... */
  /* 'DMatrix:47'       D18, D28, D38, D48, D58, D68, D78, D88]; */
  D46_tmp_9 = std::cos(D56_tmp_tmp);
  D46_tmp_tmp_4 = D15_tmp_tmp * 2.0;
  D46_tmp_a = std::cos(D46_tmp_tmp_4);
  D46_tmp_b = std::cos(D56_tmp_tmp_1);
  D46_tmp_p = D15_tmp_tmp_0 * 2.0;
  D46_tmp_c = std::cos(D46_tmp_p);
  D46_tmp = std::sin(D56_tmp_tmp_tmp);
  D46_tmp_s = D14_tmp_tmp * 2.0;
  D46_tmp_0 = std::cos(D46_tmp_s);
  D46_tmp_s = std::sin(D46_tmp_s);
  ginv_tmp_tmp_0 = 2.0 * PD_U.InBus1_Positions[4];
  D46_tmp_u = std::sin(ginv_tmp_tmp_0);
  D46_tmp_y = std::sin(D46_tmp_tmp_4);
  D46_tmp_p = std::sin(D46_tmp_p);
  D46_tmp_r = std::cos(D56_tmp_tmp_3);
  ginv_tmp_tmp = D46_tmp_tmp_4 + PD_U.InBus1_Positions[7];
  D46_tmp_tmp_4 = std::cos(ginv_tmp_tmp);
  D56_tmp_tmp_tmp = std::cos(D56_tmp_tmp_tmp);
  D46_tmp_t = (PD_P.HexaConstants.Mass + PD_P.ArmConstants.Mass1) +
    PD_P.ArmConstants.Mass2;
  PD_B.ginv[0] = D46_tmp_t;
  PD_B.ginv[8] = 0.0;
  PD_B.ginv[16] = 0.0;
  PD_B.ginv[24] = D14;
  PD_B.ginv[32] = D15;
  PD_B.ginv[40] = D16;
  PD_B.ginv[48] = D17;
  PD_B.ginv[56] = D18;
  PD_B.ginv[1] = 0.0;
  PD_B.ginv[9] = D46_tmp_t;
  PD_B.ginv[17] = 0.0;
  PD_B.ginv[25] = D24;
  PD_B.ginv[33] = D25;
  PD_B.ginv[41] = D14_tmp_tmp_0;
  PD_B.ginv[49] = D17_tmp_5;
  PD_B.ginv[57] = D17_tmp_2;
  PD_B.ginv[2] = 0.0;
  PD_B.ginv[10] = 0.0;
  PD_B.ginv[18] = D46_tmp_t;
  PD_B.ginv[26] = D34;
  PD_B.ginv[34] = D35;
  PD_B.ginv[42] = 0.0;
  PD_B.ginv[50] = D37;
  PD_B.ginv[58] = D38;
  PD_B.ginv[3] = D14;
  PD_B.ginv[11] = D24;
  PD_B.ginv[19] = D34;
  ginv_tmp_tmp_2 = D14_tmp_9 * D46_tmp_tmp_5;
  D46_tmp_v = ginv_tmp_tmp_2 * D14_tmp_6;
  D46_tmp_w = D46_tmp_m * D14_tmp_7;
  D47_tmp_2 = (((((D47_tmp_2 + PD_P.HexaConstants.Inertia[0]) + D47_tmp_0) +
                 D56_tmp_h) + D46_tmp_e) + D56_tmp_i) + D47_tmp_1;
  PD_B.ginv[27] = ((D47_tmp_2 + D46_tmp_v) + D47_tmp_3) + D46_tmp_w;
  PD_B.ginv[35] = D45;
  PD_B.ginv[43] = D46;
  PD_B.ginv[51] = D47;
  PD_B.ginv[59] = D48;
  PD_B.ginv[4] = D15;
  PD_B.ginv[12] = D25;
  PD_B.ginv[20] = D35;
  PD_B.ginv[28] = D45;
  D46_tmp_x = 2.0 * PD_P.ArmConstants.Inertia2[3];
  ginv_tmp_6 = 2.0 * PD_P.ArmConstants.Inertia1[3];
  ginv_tmp_7 = PD_P.ArmConstants.Inertia1[4] * D46_tmp_a;
  ginv_tmp_8 = D47_tmp_0 * D46_tmp_a;
  ginv_tmp_9 = D47_tmp_1 * D46_tmp_a;
  ginv_tmp_a = PD_P.ArmConstants.Inertia2[0] * D46_tmp_c;
  ginv_tmp_b = PD_P.ArmConstants.Inertia2[4] * D46_tmp_c;
  ginv_tmp_c = D46_tmp_e * D46_tmp_c;
  PD_B.ginv[36] = ((((((((((((((((((((((((((((((PD_P.ArmConstants.Inertia1[0] +
    PD_P.ArmConstants.Inertia1[4]) + PD_P.ArmConstants.Inertia2[0]) +
    PD_P.ArmConstants.Inertia2[4]) + PD_P.HexaConstants.Inertia[4]) +
    PD_P.HexaConstants.Inertia[8]) + D47_tmp_0) + D56_tmp_h) + D46_tmp_e) +
    D56_tmp_i) + D47_tmp_1) + PD_P.HexaConstants.Inertia[4] * D46_tmp_9) -
    PD_P.HexaConstants.Inertia[8] * D46_tmp_9) + D56_tmp_h * D46_tmp_9) +
    D56_tmp_i * D46_tmp_9) + D46_tmp_v) + -PD_P.ArmConstants.Inertia1[0] *
    D46_tmp_a) + ginv_tmp_7) + ginv_tmp_8) + ginv_tmp_9) + D46_tmp_k * D46_tmp_b)
    + D46_tmp_l * D46_tmp_b) + D47_tmp_3) + D46_tmp_w) - ginv_tmp_a) +
                        ginv_tmp_b) + ginv_tmp_c) + D46_tmp_m * D46_tmp_r) +
                     D46_tmp_j * D46_tmp_tmp_4) + ginv_tmp_6 * D46_tmp_y) +
                   D46_tmp_x * D46_tmp_p) * 0.5;
  PD_B.ginv[44] = D56;
  PD_B.ginv[52] = D57;
  PD_B.ginv[60] = D45_tmp;
  PD_B.ginv[5] = D16;
  PD_B.ginv[13] = D14_tmp_tmp_0;
  PD_B.ginv[21] = 0.0;
  PD_B.ginv[29] = D46;
  PD_B.ginv[37] = D56;
  ginv_tmp = D14_tmp_2 * D14_tmp_2;
  ginv_tmp_0 = D14_tmp_6 * D14_tmp_6;
  ginv_tmp_1 = D14_tmp * D14_tmp;
  ginv_tmp_2 = D14_tmp_1 * D14_tmp_1;
  ginv_tmp_3 = PD_P.ArmConstants.Inertia2[0] + PD_P.ArmConstants.Inertia2[4];
  ginv_tmp_4 = -PD_P.ArmConstants.Inertia2[0] + PD_P.ArmConstants.Inertia2[4];
  ginv_tmp_tmp_1 = 2.0 * D14_tmp_2;
  D14 = ginv_tmp_tmp_1 * D17_tmp_3 * D14_tmp_1;
  ginv_tmp_5 = D14_tmp_0 * D14_tmp_0;
  ginv_tmp_d = PD_P.ArmConstants.Inertia1[6] * D14_tmp_6 -
    PD_P.ArmConstants.Inertia1[7] * D14_tmp;
  ginv_tmp_e = PD_P.ArmConstants.Inertia1[7] * D14_tmp_6 +
    PD_P.ArmConstants.Inertia1[6] * D14_tmp;
  ginv_tmp_f = PD_P.ArmConstants.Inertia2[6] * D14_tmp_7 -
    PD_P.ArmConstants.Inertia2[7] * D14_tmp_5;
  ginv_tmp_g = PD_P.ArmConstants.Inertia2[7] * D14_tmp_7 +
    PD_P.ArmConstants.Inertia2[6] * D14_tmp_5;
  ginv_tmp_h = ginv_tmp_0 * PD_P.ArmConstants.Inertia1[0];
  ginv_tmp_i = ginv_tmp_1 * PD_P.ArmConstants.Inertia1[4];
  ginv_tmp_0 = (ginv_tmp_0 * PD_P.ArmConstants.Inertia1[4] + ginv_tmp_1 *
                PD_P.ArmConstants.Inertia1[0]) + PD_P.ArmConstants.Inertia1[3] *
    D46_tmp;
  ginv_tmp_tmp_3 = PD_P.ArmConstants.Inertia2[0] - PD_P.ArmConstants.Inertia2[4];
  ginv_tmp_1 = (ginv_tmp_tmp_3 * D46_tmp_0 + ginv_tmp_3) + D56_tmp_g * D46_tmp_s;
  ginv_tmp_tmp_4 = ginv_tmp_4 * D46_tmp_0;
  ginv_tmp_tmp_5 = D46_tmp_x * D46_tmp_s;
  ginv_tmp_3 = (ginv_tmp_tmp_4 + ginv_tmp_3) + ginv_tmp_tmp_5;
  ginv_tmp_j = ginv_tmp * PD_P.HexaConstants.Inertia[8];
  ginv_tmp_k = D17_tmp_3 * ginv_tmp_2;
  ginv_tmp_l = ginv_tmp * D17_tmp_3;
  PD_B.ginv[45] = ((((((((((((((((((-PD_P.ArmConstants.Inertia1[0] +
    PD_P.ArmConstants.Inertia1[4]) * D14_tmp_6 * D14_tmp +
    -PD_P.ArmConstants.Inertia1[3] * D56_tmp_tmp_tmp) * D14 + (D17_tmp_3 *
    PD_P.HexaConstants.Inertia[4] * ginv_tmp_2 + ginv_tmp_j * D17_tmp_3)) +
    ((ginv_tmp_h + ginv_tmp_i) + -PD_P.ArmConstants.Inertia1[3] * D46_tmp) *
    ginv_tmp_l) + ginv_tmp_0 * ginv_tmp_k) + ginv_tmp * 0.5 * D17_tmp_3 *
    ginv_tmp_1) + D17_tmp_3 * 0.5 * ginv_tmp_2 * ginv_tmp_3) + (ginv_tmp_4 * 0.5
    * D46_tmp_s + -PD_P.ArmConstants.Inertia2[3] * D46_tmp_0) * D14) +
    ginv_tmp_5 * PD_P.ArmConstants.Inertia1[8]) + ginv_tmp_5 *
    PD_P.ArmConstants.Inertia2[8]) + ginv_tmp_5 * PD_P.HexaConstants.Inertia[0])
    + w_a * w_a * PD_P.ArmConstants.Mass1) + x_a * x_a * PD_P.ArmConstants.Mass2)
                       + D24_tmp * D24_tmp * PD_P.ArmConstants.Mass1) +
                      D24_tmp_0 * D24_tmp_0 * PD_P.ArmConstants.Mass2) +
                     ginv_tmp_d * D14_tmp_2 * D46_tmp_u) - ginv_tmp_e *
                    D14_tmp_1 * D46_tmp_u) + ginv_tmp_f * D14_tmp_2 * D46_tmp_u)
    - ginv_tmp_g * D14_tmp_1 * D46_tmp_u;
  PD_B.ginv[53] = D46_tmp_n;
  PD_B.ginv[61] = D46_tmp_q;
  PD_B.ginv[6] = D17;
  PD_B.ginv[14] = D17_tmp_5;
  PD_B.ginv[22] = D37;
  PD_B.ginv[30] = D47;
  PD_B.ginv[38] = D57;
  PD_B.ginv[46] = D46_tmp_n;
  PD_B.ginv[54] = D47_tmp_4 + D47_tmp_3;
  PD_B.ginv[62] = D48_tmp_0;
  PD_B.ginv[7] = D18;
  PD_B.ginv[15] = D17_tmp_2;
  PD_B.ginv[23] = D38;
  PD_B.ginv[31] = D48;
  PD_B.ginv[39] = D45_tmp;
  PD_B.ginv[47] = D46_tmp_q;
  PD_B.ginv[55] = D48_tmp_0;
  PD_B.ginv[63] = D48_tmp_tmp;

  /* :  CM = CMatrix(q, dq, HexaConstants, ArmConstants); */
  /* 'CMatrix:3' ml1 = ArmConstants.Mass1; */
  /* 'CMatrix:4' ml2 = ArmConstants.Mass2; */
  /* 'CMatrix:6' L   = ArmConstants.Hexa_to_joint_L; */
  /* 'CMatrix:8' l1  = ArmConstants.l1_dim(1); */
  /* 'CMatrix:10' c1  = ArmConstants.MC1; */
  /* 'CMatrix:11' c2  = ArmConstants.MC2; */
  /* 'CMatrix:13' Hb = HexaConstants.Inertia; */
  /* 'CMatrix:14' Hbx = Hb(1, 1); */
  /* 'CMatrix:14' Hby = Hb(2, 2); */
  /* 'CMatrix:14' Hbz = Hb(3, 3); */
  /* 'CMatrix:16' H1 = ArmConstants.Inertia1; */
  /* 'CMatrix:17' H1xx = H1(1, 1); */
  /* 'CMatrix:17' H1yy = H1(2, 2); */
  /* 'CMatrix:17' H1zz = H1(3, 3); */
  /* 'CMatrix:18' H1xy = H1(1, 2); */
  /* 'CMatrix:18' H1yz = H1(2, 3); */
  /* 'CMatrix:18' H1zx = H1(1, 3); */
  /* 'CMatrix:20' H2 = ArmConstants.Inertia2; */
  /* 'CMatrix:21' H2xx = H2(1, 1); */
  /* 'CMatrix:21' H2yy = H2(2, 2); */
  /* 'CMatrix:21' H2zz = H2(3, 3); */
  /* 'CMatrix:22' H2xy = H2(1, 2); */
  /* 'CMatrix:22' H2yz = H2(2, 3); */
  /* 'CMatrix:22' H2zx = H2(1, 3); */
  /* 'CMatrix:24' phi = xi(4); */
  /* 'CMatrix:25' th  = xi(5); */
  /* 'CMatrix:26' psi = xi(6); */
  /* 'CMatrix:27' q1  = xi(7); */
  /* 'CMatrix:28' q2  = xi(8); */
  /* 'CMatrix:30' dphi = dxi(4); */
  /* 'CMatrix:31' dth  = dxi(5); */
  /* 'CMatrix:32' dpsi = dxi(6); */
  /* 'CMatrix:33' dq1  = dxi(7); */
  /* 'CMatrix:34' dq2  = dxi(8); */
  /* 'CMatrix:36' [C14, C15, C16, C17, C18] = get_C1(); */
  /* 'CMatrix:58' C14=(1/2)*(2*dth*cos(psi)*cos(th)*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1* ... */
  /* 'CMatrix:59'   ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+c2*dq2*ml2*(cos(phi- ... */
  /* 'CMatrix:60'   psi+q1+q2)-cos(phi+psi+q1+q2)+2*cos(psi)*cos(phi+q1+q2)*sin(th) ... */
  /* 'CMatrix:61'   )+2*dq1*cos(q1)*(cos(phi)*(c2*ml2*sin(psi)*sin(q2)+cos(psi)*( ... */
  /* 'CMatrix:62'   c1*ml1+l1*ml2+c2*ml2*cos(q2))*sin(th))+sin(phi)*((c1*ml1+l1*ml2+ ... */
  /* 'CMatrix:63'   c2*ml2*cos(q2))*sin(psi)-c2*ml2*cos(psi)*sin(q2)*sin(th)))+ ... */
  /* 'CMatrix:64'   (-2)*dq1*sin(q1)*(sin(phi)*(c2*ml2*sin(psi)*sin(q2)+cos(psi)*( ... */
  /* 'CMatrix:65'   c1*ml1+l1*ml2+c2*ml2*cos(q2))*sin(th))+cos(phi)*(-(c1*ml1+ ... */
  /* 'CMatrix:66'   l1*ml2+c2*ml2*cos(q2))*sin(psi)+c2*ml2*cos(psi)*sin(q2)*sin(th)) ... */
  /* 'CMatrix:67'   )+dphi*(2*cos(phi)*(sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2* ... */
  /* 'CMatrix:68'   sin(q1+q2))+cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2* ... */
  /* 'CMatrix:69'   cos(q1+q2))*sin(th))+2*sin(phi)*((L*(ml1+ml2)+(c1*ml1+l1*ml2)* ... */
  /* 'CMatrix:70'   cos(q1)+c2*ml2*cos(q1+q2))*sin(psi)-cos(psi)*((c1*ml1+l1* ... */
  /* 'CMatrix:71'   ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th)))+dpsi*(2*sin(phi)*(cos( ... */
  /* 'CMatrix:72'   psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))-(L*(ml1+ ... */
  /* 'CMatrix:73'   ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(psi)*sin(th)) ... */
  /* 'CMatrix:74'   +(-2)*cos(phi)*(cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+ ... */
  /* 'CMatrix:75'   c2*ml2*cos(q1+q2))+sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin( ... */
  /* 'CMatrix:76'   q1+q2))*sin(th)))); */
  /* 'CMatrix:77' C15=dpsi*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2* ... */
  /* 'CMatrix:78'   cos(phi+q1+q2))*cos(th)*sin(psi)+c2*dq2*ml2*cos(psi)*cos(th)*sin( ... */
  /* 'CMatrix:79'   phi+q1+q2)+dq1*cos(psi)*cos(th)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2* ... */
  /* 'CMatrix:80'   ml2*sin(phi+q1+q2))+dphi*cos(psi)*cos(th)*(L*(ml1+ml2)*sin(phi)+( ... */
  /* 'CMatrix:81'   c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+dth*cos(psi)*( ... */
  /* 'CMatrix:82'   L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'CMatrix:83'   q1+q2))*sin(th); */
  /* 'CMatrix:84' C16=(1/2)*(2*dth*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+ ... */
  /* 'CMatrix:85'   c2*ml2*cos(phi+q1+q2))*cos(th)*sin(psi)+(-2)*c2*dq2*ml2*(sin(q1+ ... */
  /* 'CMatrix:86'   q2)*(-cos(psi)*sin(phi)+cos(phi)*sin(psi)*sin(th))+cos(q1+q2)* ... */
  /* 'CMatrix:87'   (cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th)))+(-2)*dq1*(-(( ... */
  /* 'CMatrix:88'   c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*(cos(psi)*sin(phi)+(-1) ... */
  /* 'CMatrix:89'   *cos(phi)*sin(psi)*sin(th))+(c1*ml1+l1*ml2)*cos(q1)*(cos(phi)* ... */
  /* 'CMatrix:90'   cos(psi)+sin(phi)*sin(psi)*sin(th))+c2*ml2*cos(q1+q2)*(cos(phi)* ... */
  /* 'CMatrix:91'   cos(psi)+sin(phi)*sin(psi)*sin(th)))+dpsi*(2*cos(phi)*(sin(psi)*(( ... */
  /* 'CMatrix:92'   c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))+cos(psi)*(L*(ml1+ml2)+( ... */
  /* 'CMatrix:93'   c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(th))+(-2)*sin(phi) ... */
  /* 'CMatrix:94'   *(-(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))* ... */
  /* 'CMatrix:95'   sin(psi)+cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))* ... */
  /* 'CMatrix:96'   sin(th)))+dphi*(2*sin(phi)*(cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+ ... */
  /* 'CMatrix:97'   c2*ml2*sin(q1+q2))-(L*(ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2* ... */
  /* 'CMatrix:98'   ml2*cos(q1+q2))*sin(psi)*sin(th))+(-2)*cos(phi)*(cos(psi)*(L*( ... */
  /* 'CMatrix:99'   ml1+ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))+sin(psi)*(( ... */
  /* 'CMatrix:100'   c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th)))); */
  /* 'CMatrix:101' C17=(1/2)*(cos(psi)*(dth*(c1*ml1+l1*ml2)*cos(q1)*cos(th)*sin(phi)+ ... */
  /* 'CMatrix:102'   c2*dth*ml2*cos(q1+q2)*cos(th)*sin(phi)+2*c1*dpsi*ml1*sin(phi)* ... */
  /* 'CMatrix:103'   sin(q1)+2*dpsi*l1*ml2*sin(phi)*sin(q1)+c1*dth*ml1*cos(th)*sin( ... */
  /* 'CMatrix:104'   phi+q1)+dth*l1*ml2*cos(th)*sin(phi+q1)+2*c2*dpsi*ml2*sin(phi)* ... */
  /* 'CMatrix:105'   sin(q1+q2)+c2*dth*ml2*cos(th)*sin(phi+q1+q2)+(-2)*c1*dphi*ml1* ... */
  /* 'CMatrix:106'   sin(phi)*sin(q1)*sin(th)+(-2)*c1*dq1*ml1*sin(phi)*sin(q1)*sin( ... */
  /* 'CMatrix:107'   th)+(-2)*dphi*l1*ml2*sin(phi)*sin(q1)*sin(th)+(-2)*dq1*l1*ml2* ... */
  /* 'CMatrix:108'   sin(phi)*sin(q1)*sin(th)+(-2)*c2*dphi*ml2*sin(phi)*sin(q1+q2)* ... */
  /* 'CMatrix:109'   sin(th)+(-2)*c2*dq1*ml2*sin(phi)*sin(q1+q2)*sin(th)+(-2)*c2* ... */
  /* 'CMatrix:110'   dq2*ml2*sin(phi)*sin(q1+q2)*sin(th))+2*sin(phi)*sin(psi)*((c1* ... */
  /* 'CMatrix:111'   ml1+l1*ml2)*cos(q1)*(dphi+dq1-dpsi*sin(th))+c2*ml2*cos(q1+ ... */
  /* 'CMatrix:112'   q2)*(dphi+dq1+dq2-dpsi*sin(th)))+cos(phi)*(cos(psi)*(c1*dth* ... */
  /* 'CMatrix:113'   ml1*cos(th)*sin(q1)+dth*l1*ml2*cos(th)*sin(q1)+c2*dth*ml2*cos( ... */
  /* 'CMatrix:114'   th)*sin(q1+q2)-c2*dphi*ml2*sin(q1)*sin(q2)*sin(th)- ... */
  /* 'CMatrix:115'   c2*ml2*cos(q1+q2)*(2*dpsi-(dphi+2*(dq1+dq2))*sin(th))+cos( ... */
  /* 'CMatrix:116'   q1)*((-2)*dpsi*(c1*ml1+l1*ml2)+(2*(dphi+dq1)*(c1*ml1+l1*ml2)+ ... */
  /* 'CMatrix:117'   c2*dphi*ml2*cos(q2))*sin(th)))+sin(psi)*(c2*ml2*(dphi*cos(q1)* ... */
  /* 'CMatrix:118'   sin(q2)+sin(q1+q2)*(dphi+2*(dq1+dq2)+(-2)*dpsi*sin(th)))+sin(q1)*( ... */
  /* 'CMatrix:119'   c2*dphi*ml2*cos(q2)+2*(c1*ml1+l1*ml2)*(dphi+dq1-dpsi*sin( ... */
  /* 'CMatrix:120'   th)))))); */
  /* 'CMatrix:121' C18=(1/2)*c2*ml2*(2*cos(q1+q2)*sin(phi)*sin(psi)*(dphi+dq1+dq2- ... */
  /* 'CMatrix:122'   dpsi*sin(th))+cos(psi)*(dth*cos(q1+q2)*cos(th)*sin(phi)+dth*cos( ... */
  /* 'CMatrix:123'   th)*sin(phi+q1+q2)+2*sin(phi)*sin(q1+q2)*(dpsi-(dphi+dq1+dq2) ... */
  /* 'CMatrix:124'   *sin(th)))+cos(phi)*(2*sin(psi)*sin(q1+q2)*(dphi+dq1+dq2- ... */
  /* 'CMatrix:125'   dpsi*sin(th))+cos(psi)*(dth*cos(th)*sin(q1+q2)+2*cos(q1+q2)*((-1) ... */
  /* 'CMatrix:126'   *dpsi+(dphi+dq1+dq2)*sin(th))))); */
  /* 'CMatrix:37' [C24, C25, C26, C27, C28] = get_C2(); */
  /* 'CMatrix:130' C24=-dq1*cos(psi)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+ ... */
  /* 'CMatrix:131'   q1+q2))+dth*cos(th)*sin(psi)*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1* ... */
  /* 'CMatrix:132'   ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+(-1/4)*c2*dq2*ml2*(cos( ... */
  /* 'CMatrix:133'   phi-psi+q1+q2-th)-cos(phi+psi+q1+q2-th)- ... */
  /* 'CMatrix:134'   cos(phi-psi+q1+q2+th)+cos(phi+psi+q1+q2+th)+2*sin(phi-psi+ ... */
  /* 'CMatrix:135'   q1+q2)+2*sin(phi+psi+q1+q2))+dq1*((c1*ml1+l1*ml2)*cos(phi+q1)+c2* ... */
  /* 'CMatrix:136'   ml2*cos(phi+q1+q2))*sin(psi)*sin(th)+dphi*(-cos(psi)*(L*(ml1+ ... */
  /* 'CMatrix:137'   ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+( ... */
  /* 'CMatrix:138'   L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'CMatrix:139'   q1+q2))*sin(psi)*sin(th))+dpsi*(sin(phi)*(sin(psi)*((c1*ml1+l1* ... */
  /* 'CMatrix:140'   ml2)*sin(q1)+c2*ml2*sin(q1+q2))+cos(psi)*(L*(ml1+ml2)+(c1*ml1+l1* ... */
  /* 'CMatrix:141'   ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(th))+cos(phi)*(-(L*(ml1+ ... */
  /* 'CMatrix:142'   ml2)+(c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(psi)+cos(psi) ... */
  /* 'CMatrix:143'   *((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th))); */
  /* 'CMatrix:144' C25=-dpsi*cos(psi)*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos( ... */
  /* 'CMatrix:145'   phi+q1)+c2*ml2*cos(phi+q1+q2))*cos(th)+c2*dq2*ml2*cos(th)*sin( ... */
  /* 'CMatrix:146'   psi)*sin(phi+q1+q2)+dq1*cos(th)*sin(psi)*((c1*ml1+l1*ml2)*sin( ... */
  /* 'CMatrix:147'   phi+q1)+c2*ml2*sin(phi+q1+q2))+dphi*cos(th)*sin(psi)*(L*(ml1+ml2) ... */
  /* 'CMatrix:148'   *sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+dth* ... */
  /* 'CMatrix:149'   (L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+ ... */
  /* 'CMatrix:150'   q1+q2))*sin(psi)*sin(th); */
  /* 'CMatrix:151' C26=(1/2)*((-2)*cos(psi)*(dth*(c1*ml1+l1*ml2)*cos(phi+q1)*cos(th)+ ... */
  /* 'CMatrix:152'   c2*dth*ml2*cos(phi+q1+q2)*cos(th)+sin(phi)*(L*(ml1+ml2)*(dpsi+( ... */
  /* 'CMatrix:153'   -1)*dphi*sin(th))+(c1*ml1+l1*ml2)*cos(q1)*(dpsi-(dphi+dq1)* ... */
  /* 'CMatrix:154'   sin(th))+c2*ml2*cos(q1+q2)*(dpsi-(dphi+dq1+dq2)*sin(th))))+( ... */
  /* 'CMatrix:155'   -1)*cos(phi)*(2*cos(psi)*(dth*L*(ml1+ml2)*cos(th)+(c1*ml1+l1* ... */
  /* 'CMatrix:156'   ml2)*sin(q1)*(dpsi-(dphi+dq1)*sin(th))+c2*ml2*sin(q1+q2)*( ... */
  /* 'CMatrix:157'   dpsi-(dphi+dq1+dq2)*sin(th)))+sin(psi)*(2*L*(ml1+ml2)*(dphi+( ... */
  /* 'CMatrix:158'   -1)*dpsi*sin(th))+(-1/2)*c2*ml2*cos(q1+q2)*((-3)*dphi+(-4)*dq1+( ... */
  /* 'CMatrix:159'   -4)*dq2+dphi*cos(2*th)+4*dpsi*sin(th))+cos(q1)*(2*c1*(dphi+dq1) ... */
  /* 'CMatrix:160'   *ml1+(dphi+2*dq1)*l1*ml2+(-2)*dpsi*(c1*ml1+l1*ml2)*sin(th)+ ... */
  /* 'CMatrix:161'   dphi*l1*ml2*sin(th)^2)))+sin(psi)*(-dphi*l1*ml2*cos(phi+q1) ... */
  /* 'CMatrix:162'   *cos(th)^2-c2*dphi*ml2*cos(phi+q1+q2)*cos(th)^2+sin(phi)*( ... */
  /* 'CMatrix:163'   c2*ml2*sin(q1+q2)*(dphi+2*(dq1+dq2)+(-2)*dpsi*sin(th)+dphi*sin( ... */
  /* 'CMatrix:164'   th)^2)+sin(q1)*(2*c1*(dphi+dq1)*ml1+(dphi+2*dq1)*l1*ml2+(-2)* ... */
  /* 'CMatrix:165'   dpsi*(c1*ml1+l1*ml2)*sin(th)+dphi*l1*ml2*sin(th)^2)))); */
  /* 'CMatrix:166' C27=-dphi*cos(psi)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+ ... */
  /* 'CMatrix:167'   q1+q2))+dth*cos(th)*sin(psi)*((c1*ml1+l1*ml2)*sin(phi+q1)+c2* ... */
  /* 'CMatrix:168'   ml2*sin(phi+q1+q2))+dphi*((c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos( ... */
  /* 'CMatrix:169'   phi+q1+q2))*sin(psi)*sin(th)-c2*dq2*ml2*(cos(psi)*sin(phi+ ... */
  /* 'CMatrix:170'   q1+q2)-cos(phi+q1+q2)*sin(psi)*sin(th))+dq1*(-cos(psi)*(( ... */
  /* 'CMatrix:171'   c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))+((c1*ml1+l1* ... */
  /* 'CMatrix:172'   ml2)*cos(phi+q1)+c2*ml2*cos(phi+q1+q2))*sin(psi)*sin(th))+dpsi*( ... */
  /* 'CMatrix:173'   sin(phi)*(sin(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))+ ... */
  /* 'CMatrix:174'   cos(psi)*((c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin(th))+ ... */
  /* 'CMatrix:175'   cos(phi)*(-((c1*ml1+l1*ml2)*cos(q1)+c2*ml2*cos(q1+q2))*sin( ... */
  /* 'CMatrix:176'   psi)+cos(psi)*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2*sin(q1+q2))*sin(th) ... */
  /* 'CMatrix:177'   )); */
  /* 'CMatrix:178' C28=(-1/2)*c2*ml2*(2*cos(psi)*sin(phi+q1+q2)*(dphi+dq1+dq2- ... */
  /* 'CMatrix:179'   dpsi*sin(th))+sin(psi)*(2*dpsi*cos(phi+q1+q2)+(dphi+dq1+dq2- ... */
  /* 'CMatrix:180'   dth)*sin(phi+q1+q2-th)-(dphi+dq1+dq2+dth)*sin(phi+q1+q2+ ... */
  /* 'CMatrix:181'   th))); */
  /* 'CMatrix:38' [C34, C35, C36, C37, C38] = get_C3(); */
  /* 'CMatrix:185' C34=c2*dq2*ml2*cos(phi+q1+q2)*cos(th)+dq1*((c1*ml1+l1*ml2)*cos(phi+ ... */
  /* 'CMatrix:186'   q1)+c2*ml2*cos(phi+q1+q2))*cos(th)+dphi*(L*(ml1+ml2)*cos(phi)+( ... */
  /* 'CMatrix:187'   c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+q1+q2))*cos(th)- ... */
  /* 'CMatrix:188'   dth*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2* ... */
  /* 'CMatrix:189'   sin(phi+q1+q2))*sin(th); */
  /* 'CMatrix:190' C35=dth*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2* ... */
  /* 'CMatrix:191'   cos(phi+q1+q2))*cos(th)-c2*dq2*ml2*sin(phi+q1+q2)*sin(th)+( ... */
  /* 'CMatrix:192'   -1)*dq1*((c1*ml1+l1*ml2)*sin(phi+q1)+c2*ml2*sin(phi+q1+q2))*sin( ... */
  /* 'CMatrix:193'   th)-dphi*(L*(ml1+ml2)*sin(phi)+(c1*ml1+l1*ml2)*sin(phi+q1)+ ... */
  /* 'CMatrix:194'   c2*ml2*sin(phi+q1+q2))*sin(th); */
  /* 'CMatrix:195' C36=0; */
  /* 'CMatrix:196' C37=(dphi+dq1)*(c1*ml1+l1*ml2)*cos(phi+q1)*cos(th)+c2*(dphi+dq1+dq2)* ... */
  /* 'CMatrix:197'   ml2*cos(phi+q1+q2)*cos(th)-dth*((c1*ml1+l1*ml2)*sin(phi+q1)+ ... */
  /* 'CMatrix:198'   c2*ml2*sin(phi+q1+q2))*sin(th); */
  /* 'CMatrix:199' C38=c2*ml2*((dphi+dq1+dq2)*cos(phi+q1+q2)*cos(th)-dth*sin(phi+q1+ ... */
  /* 'CMatrix:200'   q2)*sin(th)); */
  /* 'CMatrix:39' [C44, C45, C46, C47, C48] = get_C4(); */
  /* 'CMatrix:204' C44=-dq1*L*(c1*ml1+l1*ml2)*sin(q1)-c2*ml2*(dq2*l1*sin( ... */
  /* 'CMatrix:205'   q2)+(dq1+dq2)*L*sin(q1+q2)); */
  /* 'CMatrix:206' C45=(1/4)*(2*dth*((-2)*H1xy*cos(2*(phi+q1))+(-2)*H2xy*cos(2*(phi+ ... */
  /* 'CMatrix:207'   q1+q2))+Hby*sin(2*phi)-Hbz*sin(2*phi)+L^2*ml1*sin(2*phi)+ ... */
  /* 'CMatrix:208'   L^2*ml2*sin(2*phi)-H1xx*sin(2*(phi+q1))+H1yy*sin(2*(phi+ ... */
  /* 'CMatrix:209'   q1))+c1^2*ml1*sin(2*(phi+q1))+l1^2*ml2*sin(2*(phi+q1))+2*c1* ... */
  /* 'CMatrix:210'   L*ml1*sin(2*phi+q1)+2*L*l1*ml2*sin(2*phi+q1)-H2xx*sin(2* ... */
  /* 'CMatrix:211'   (phi+q1+q2))+H2yy*sin(2*(phi+q1+q2))+c2^2*ml2*sin(2*(phi+q1+q2))+ ... */
  /* 'CMatrix:212'   2*c2*L*ml2*sin(2*phi+q1+q2)+2*c2*l1*ml2*sin(2*(phi+q1)+q2))+( ... */
  /* 'CMatrix:213'   -1)*dpsi*((Hby-Hbz+L^2*(ml1+ml2))*cos(2*phi-th)+2*L* ... */
  /* 'CMatrix:214'   (c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+2* ... */
  /* 'CMatrix:215'   c1*L*ml1*cos(2*phi+q1-th)+2*L*l1*ml2*cos(2*phi+q1- ... */
  /* 'CMatrix:216'   th)-H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1- ... */
  /* 'CMatrix:217'   th)+c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:218'   -th)+2*c2*l1*ml2*cos(q2-th)+2*c2*L*ml2*cos(q1+q2+(-1) ... */
  /* 'CMatrix:219'   *th)+2*H2yz*cos(phi+q1+q2-th)+2*c2*L*ml2*cos(2*phi+q1+q2+( ... */
  /* 'CMatrix:220'   -1)*th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos( ... */
  /* 'CMatrix:221'   2*phi+2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:222'   c2^2*ml2*cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz* ... */
  /* 'CMatrix:223'   cos(th)+2*Hbx*cos(th)+2*c1^2*ml1*cos(th)+2*L^2*ml1*cos(th)+2* ... */
  /* 'CMatrix:224'   c2^2*ml2*cos(th)+2*L^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+Hby* ... */
  /* 'CMatrix:225'   cos(2*phi+th)-Hbz*cos(2*phi+th)+L^2*ml1*cos(2*phi+th)+ ... */
  /* 'CMatrix:226'   L^2*ml2*cos(2*phi+th)+2*c1*L*ml1*cos(q1+th)+2*L*l1*ml2*cos( ... */
  /* 'CMatrix:227'   q1+th)+(-2)*H1yz*cos(phi+q1+th)+2*c1*L*ml1*cos(2*phi+q1+th)+2* ... */
  /* 'CMatrix:228'   L*l1*ml2*cos(2*phi+q1+th)-H1xx*cos(2*phi+2*q1+th)+H1yy* ... */
  /* 'CMatrix:229'   cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+2*q1+th)+l1^2*ml2*cos( ... */
  /* 'CMatrix:230'   2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+2*c2*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:231'   +(-2)*H2yz*cos(phi+q1+q2+th)+2*c2*L*ml2*cos(2*phi+q1+q2+th)+2* ... */
  /* 'CMatrix:232'   c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:233'   th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:234'   th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:235'   2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:236'   th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2*phi+2*q1+th)+(-2)* ... */
  /* 'CMatrix:237'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))); */
  /* 'CMatrix:238' C46=(1/8)*(4*dpsi*H1xy*cos(2*(phi+q1))+4*dpsi*H2xy*cos(2*(phi+q1+ ... */
  /* 'CMatrix:239'   q2))+2*dpsi*H1zx*cos(phi+q1+(-2)*th)+2*dpsi*H2zx*cos(phi+q1+q2+( ... */
  /* 'CMatrix:240'   -2)*th)+(-2)*dth*Hby*cos(2*phi-th)+2*dth*Hbz*cos(2*phi+( ... */
  /* 'CMatrix:241'   -1)*th)+(-2)*dth*L^2*ml1*cos(2*phi-th)+(-2)*dth*L^2* ... */
  /* 'CMatrix:242'   ml2*cos(2*phi-th)+(-4)*c1*dth*L*ml1*cos(q1-th)+(-4)* ... */
  /* 'CMatrix:243'   dth*L*l1*ml2*cos(q1-th)+(-4)*dth*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:244'   2*dpsi*H1xy*cos(2*(phi+q1-th))+(-4)*c1*dth*L*ml1*cos(2* ... */
  /* 'CMatrix:245'   phi+q1-th)+(-4)*dth*L*l1*ml2*cos(2*phi+q1-th)+2*dth* ... */
  /* 'CMatrix:246'   H1xx*cos(2*phi+2*q1-th)+(-2)*dth*H1yy*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:247'   *th)+(-2)*c1^2*dth*ml1*cos(2*phi+2*q1-th)+(-2)*dth* ... */
  /* 'CMatrix:248'   l1^2*ml2*cos(2*phi+2*q1-th)+(-4)*c2*dth*l1*ml2*cos(q2+( ... */
  /* 'CMatrix:249'   -1)*th)+(-4)*c2*dth*L*ml2*cos(q1+q2-th)+(-4)*dth*H2yz* ... */
  /* 'CMatrix:250'   cos(phi+q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2-th))+(-4) ... */
  /* 'CMatrix:251'   *c2*dth*L*ml2*cos(2*phi+q1+q2-th)+(-4)*c2*dth*l1*ml2* ... */
  /* 'CMatrix:252'   cos(2*phi+2*q1+q2-th)+2*dth*H2xx*cos(2*phi+2*q1+2*q2+(-1) ... */
  /* 'CMatrix:253'   *th)+(-2)*dth*H2yy*cos(2*phi+2*q1+2*q2-th)+(-2)*c2^2* ... */
  /* 'CMatrix:254'   dth*ml2*cos(2*phi+2*q1+2*q2-th)+(-4)*dth*H1zz*cos(th)+(-4) ... */
  /* 'CMatrix:255'   *dth*H2zz*cos(th)+(-4)*dth*Hbx*cos(th)+(-4)*c1^2*dth*ml1*cos( ... */
  /* 'CMatrix:256'   th)+(-4)*dth*L^2*ml1*cos(th)+(-4)*c2^2*dth*ml2*cos(th)+(-4)* ... */
  /* 'CMatrix:257'   dth*L^2*ml2*cos(th)+(-4)*dth*l1^2*ml2*cos(th)+(-2)*dth*Hby* ... */
  /* 'CMatrix:258'   cos(2*phi+th)+2*dth*Hbz*cos(2*phi+th)+(-2)*dth*L^2*ml1*cos(2* ... */
  /* 'CMatrix:259'   phi+th)+(-2)*dth*L^2*ml2*cos(2*phi+th)+(-4)*c1*dth*L*ml1*cos( ... */
  /* 'CMatrix:260'   q1+th)+(-4)*dth*L*l1*ml2*cos(q1+th)+4*dth*H1yz*cos(phi+q1+th)+ ... */
  /* 'CMatrix:261'   2*dpsi*H1xy*cos(2*(phi+q1+th))+(-4)*c1*dth*L*ml1*cos(2*phi+q1+ ... */
  /* 'CMatrix:262'   th)+(-4)*dth*L*l1*ml2*cos(2*phi+q1+th)+2*dth*H1xx*cos(2*phi+ ... */
  /* 'CMatrix:263'   2*q1+th)+(-2)*dth*H1yy*cos(2*phi+2*q1+th)+(-2)*c1^2*dth*ml1* ... */
  /* 'CMatrix:264'   cos(2*phi+2*q1+th)+(-2)*dth*l1^2*ml2*cos(2*phi+2*q1+th)+(-4)* ... */
  /* 'CMatrix:265'   c2*dth*l1*ml2*cos(q2+th)+(-4)*c2*dth*L*ml2*cos(q1+q2+th)+4* ... */
  /* 'CMatrix:266'   dth*H2yz*cos(phi+q1+q2+th)+2*dpsi*H2xy*cos(2*(phi+q1+q2+th))+(-4) ... */
  /* 'CMatrix:267'   *c2*dth*L*ml2*cos(2*phi+q1+q2+th)+(-4)*c2*dth*l1*ml2*cos(2* ... */
  /* 'CMatrix:268'   phi+2*q1+q2+th)+2*dth*H2xx*cos(2*phi+2*q1+2*q2+th)+(-2)*dth* ... */
  /* 'CMatrix:269'   H2yy*cos(2*phi+2*q1+2*q2+th)+(-2)*c2^2*dth*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:270'   q1+2*q2+th)+(-2)*dpsi*H1zx*cos(phi+q1+2*th)+(-2)*dpsi*H2zx*cos( ... */
  /* 'CMatrix:271'   phi+q1+q2+2*th)+(-2)*dpsi*Hby*sin(2*phi)+2*dpsi*Hbz*sin(2*phi)+ ... */
  /* 'CMatrix:272'   (-2)*dpsi*L^2*ml1*sin(2*phi)+(-2)*dpsi*L^2*ml2*sin(2*phi)+ ... */
  /* 'CMatrix:273'   2*dpsi*H1xx*sin(2*(phi+q1))+(-2)*dpsi*H1yy*sin(2*(phi+q1))+(-2) ... */
  /* 'CMatrix:274'   *c1^2*dpsi*ml1*sin(2*(phi+q1))+(-2)*dpsi*l1^2*ml2*sin(2*( ... */
  /* 'CMatrix:275'   phi+q1))+(-4)*c1*dpsi*L*ml1*sin(2*phi+q1)+(-4)*dpsi*L*l1*ml2* ... */
  /* 'CMatrix:276'   sin(2*phi+q1)+2*dpsi*H2xx*sin(2*(phi+q1+q2))+(-2)*dpsi*H2yy*sin( ... */
  /* 'CMatrix:277'   2*(phi+q1+q2))+(-2)*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+(-4)*c2* ... */
  /* 'CMatrix:278'   dpsi*L*ml2*sin(2*phi+q1+q2)+(-4)*c2*dpsi*l1*ml2*sin(2*(phi+q1) ... */
  /* 'CMatrix:279'   +q2)+(-2)*c2*dpsi*l1*ml2*sin(q2+2*(phi+q1-th))+(-2)*dpsi* ... */
  /* 'CMatrix:280'   H1yz*sin(phi+q1+(-2)*th)+(-2)*c1*dpsi*L*ml1*sin(2*phi+q1+(-2)* ... */
  /* 'CMatrix:281'   th)+(-2)*dpsi*L*l1*ml2*sin(2*phi+q1+(-2)*th)+(-2)*dpsi*H2yz* ... */
  /* 'CMatrix:282'   sin(phi+q1+q2+(-2)*th)+(-2)*c2*dpsi*L*ml2*sin(2*phi+q1+q2+(-2)* ... */
  /* 'CMatrix:283'   th)+dpsi*Hbz*sin(2*(phi-th))+(-4)*dth*H1zx*sin(phi+q1- ... */
  /* 'CMatrix:284'   th)+dpsi*H1xx*sin(2*(phi+q1-th))-dpsi*H1yy*sin(2*(phi+ ... */
  /* 'CMatrix:285'   q1-th))-c1^2*dpsi*ml1*sin(2*(phi+q1-th))- ... */
  /* 'CMatrix:286'   dpsi*l1^2*ml2*sin(2*(phi+q1-th))+(-4)*dth*H1xy*sin(2*phi+ ... */
  /* 'CMatrix:287'   2*q1-th)+(-4)*dth*H2zx*sin(phi+q1+q2-th)+dpsi*H2xx* ... */
  /* 'CMatrix:288'   sin(2*(phi+q1+q2-th))-dpsi*H2yy*sin(2*(phi+q1+q2- ... */
  /* 'CMatrix:289'   th))-c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+(-4)*dth* ... */
  /* 'CMatrix:290'   H2xy*sin(2*phi+2*q1+2*q2-th)+8*c2*dq2*ml2*(l1*sin(q2)+L* ... */
  /* 'CMatrix:291'   sin(q1+q2))*sin(th)+8*dq1*L*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2* ... */
  /* 'CMatrix:292'   sin(q1+q2))*sin(th)+dpsi*Hby*sin(2*(-phi+th))+dpsi*L^2*ml1* ... */
  /* 'CMatrix:293'   sin(2*(-phi+th))+dpsi*L^2*ml2*sin(2*(-phi+th))- ... */
  /* 'CMatrix:294'   dpsi*Hby*sin(2*(phi+th))+dpsi*Hbz*sin(2*(phi+th))-dpsi* ... */
  /* 'CMatrix:295'   L^2*ml1*sin(2*(phi+th))-dpsi*L^2*ml2*sin(2*(phi+th))+4* ... */
  /* 'CMatrix:296'   dth*H1zx*sin(phi+q1+th)+dpsi*H1xx*sin(2*(phi+q1+th))-dpsi* ... */
  /* 'CMatrix:297'   H1yy*sin(2*(phi+q1+th))-c1^2*dpsi*ml1*sin(2*(phi+q1+th))+( ... */
  /* 'CMatrix:298'   -1)*dpsi*l1^2*ml2*sin(2*(phi+q1+th))+(-4)*dth*H1xy*sin(2*phi+ ... */
  /* 'CMatrix:299'   2*q1+th)+4*dth*H2zx*sin(phi+q1+q2+th)+dpsi*H2xx*sin(2*(phi+q1+q2+ ... */
  /* 'CMatrix:300'   th))-dpsi*H2yy*sin(2*(phi+q1+q2+th))-c2^2*dpsi*ml2* ... */
  /* 'CMatrix:301'   sin(2*(phi+q1+q2+th))+(-4)*dth*H2xy*sin(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:302'   dpsi*H1yz*sin(phi+q1+2*th)+2*dpsi*H2yz*sin(phi+q1+q2+2*th)+(-2)* ... */
  /* 'CMatrix:303'   c1*dpsi*L*ml1*sin(q1+2*(phi+th))+(-2)*dpsi*L*l1*ml2*sin(q1+2* ... */
  /* 'CMatrix:304'   (phi+th))+(-2)*c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th))+(-2)*c2* ... */
  /* 'CMatrix:305'   dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:306' C47=-c2*dq2*ml2*(l1*sin(q2)+L*sin(q1+q2))-L*((c1*ml1+l1* ... */
  /* 'CMatrix:307'   ml2)*sin(q1)+c2*ml2*sin(q1+q2))*(dphi+dq1-dpsi*sin(th)); */
  /* 'CMatrix:308' C48=-c2*ml2*(l1*sin(q2)+L*sin(q1+q2))*(dphi+dq1+dq2-dpsi* ... */
  /* 'CMatrix:309'   sin(th)); */
  /* 'CMatrix:40' [C54, C55, C56, C57, C58] = get_C5(); */
  /* 'CMatrix:314' C54=(1/4)*(4*(dphi+dq1)*H1zx*cos(phi+q1)+4*dth*H1xy*cos(2*(phi+q1))+ ... */
  /* 'CMatrix:315'   4*dphi*H2zx*cos(phi+q1+q2)+4*dq1*H2zx*cos(phi+q1+q2)+4*dq2* ... */
  /* 'CMatrix:316'   H2zx*cos(phi+q1+q2)+4*dth*H2xy*cos(2*(phi+q1+q2))+dpsi*Hby*cos( ... */
  /* 'CMatrix:317'   2*phi-th)-dpsi*Hbz*cos(2*phi-th)+dpsi*L^2*ml1* ... */
  /* 'CMatrix:318'   cos(2*phi-th)+dpsi*L^2*ml2*cos(2*phi-th)+2*c1*dpsi* ... */
  /* 'CMatrix:319'   L*ml1*cos(q1-th)+2*dpsi*L*l1*ml2*cos(q1-th)+2*dpsi* ... */
  /* 'CMatrix:320'   H1yz*cos(phi+q1-th)+2*c1*dpsi*L*ml1*cos(2*phi+q1-th)+ ... */
  /* 'CMatrix:321'   2*dpsi*L*l1*ml2*cos(2*phi+q1-th)-dpsi*H1xx*cos(2* ... */
  /* 'CMatrix:322'   phi+2*q1-th)+dpsi*H1yy*cos(2*phi+2*q1-th)+c1^2*dpsi* ... */
  /* 'CMatrix:323'   ml1*cos(2*phi+2*q1-th)+dpsi*l1^2*ml2*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:324'   *th)+2*c2*dpsi*l1*ml2*cos(q2-th)+2*c2*dpsi*L*ml2*cos( ... */
  /* 'CMatrix:325'   q1+q2-th)+2*dpsi*H2yz*cos(phi+q1+q2-th)+2*c2*dpsi*L* ... */
  /* 'CMatrix:326'   ml2*cos(2*phi+q1+q2-th)+2*c2*dpsi*l1*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:327'   q2-th)-dpsi*H2xx*cos(2*phi+2*q1+2*q2-th)+dpsi* ... */
  /* 'CMatrix:328'   H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*dpsi*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:329'   q1+2*q2-th)+2*dpsi*H1zz*cos(th)+2*dpsi*H2zz*cos(th)+2* ... */
  /* 'CMatrix:330'   dpsi*Hbx*cos(th)+2*c1^2*dpsi*ml1*cos(th)+2*dpsi*L^2*ml1*cos( ... */
  /* 'CMatrix:331'   th)+2*c2^2*dpsi*ml2*cos(th)+2*dpsi*L^2*ml2*cos(th)+2*dpsi* ... */
  /* 'CMatrix:332'   l1^2*ml2*cos(th)+dpsi*Hby*cos(2*phi+th)-dpsi*Hbz*cos(2* ... */
  /* 'CMatrix:333'   phi+th)+dpsi*L^2*ml1*cos(2*phi+th)+dpsi*L^2*ml2*cos(2*phi+th)+ ... */
  /* 'CMatrix:334'   2*c1*dpsi*L*ml1*cos(q1+th)+2*dpsi*L*l1*ml2*cos(q1+th)+(-2)* ... */
  /* 'CMatrix:335'   dpsi*H1yz*cos(phi+q1+th)+2*c1*dpsi*L*ml1*cos(2*phi+q1+th)+2* ... */
  /* 'CMatrix:336'   dpsi*L*l1*ml2*cos(2*phi+q1+th)-dpsi*H1xx*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:337'   th)+dpsi*H1yy*cos(2*phi+2*q1+th)+c1^2*dpsi*ml1*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:338'   th)+dpsi*l1^2*ml2*cos(2*phi+2*q1+th)+2*c2*dpsi*l1*ml2*cos(q2+ ... */
  /* 'CMatrix:339'   th)+2*c2*dpsi*L*ml2*cos(q1+q2+th)+(-2)*dpsi*H2yz*cos(phi+q1+q2+ ... */
  /* 'CMatrix:340'   th)+2*c2*dpsi*L*ml2*cos(2*phi+q1+q2+th)+2*c2*dpsi*l1*ml2*cos( ... */
  /* 'CMatrix:341'   2*phi+2*q1+q2+th)-dpsi*H2xx*cos(2*phi+2*q1+2*q2+th)+dpsi* ... */
  /* 'CMatrix:342'   H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:343'   q2+th)+(-2)*dth*Hby*sin(2*phi)+2*dth*Hbz*sin(2*phi)+(-2)*dth* ... */
  /* 'CMatrix:344'   L^2*ml1*sin(2*phi)+(-2)*dth*L^2*ml2*sin(2*phi)+(-4)*dphi* ... */
  /* 'CMatrix:345'   H1yz*sin(phi+q1)+(-4)*dq1*H1yz*sin(phi+q1)+2*dth*H1xx*sin(2*( ... */
  /* 'CMatrix:346'   phi+q1))+(-2)*dth*H1yy*sin(2*(phi+q1))+(-2)*c1^2*dth*ml1*sin( ... */
  /* 'CMatrix:347'   2*(phi+q1))+(-2)*dth*l1^2*ml2*sin(2*(phi+q1))+(-4)*c1*dth*L* ... */
  /* 'CMatrix:348'   ml1*sin(2*phi+q1)+(-4)*dth*L*l1*ml2*sin(2*phi+q1)+(-4)*dphi* ... */
  /* 'CMatrix:349'   H2yz*sin(phi+q1+q2)+(-4)*dq1*H2yz*sin(phi+q1+q2)+(-4)*dq2*H2yz* ... */
  /* 'CMatrix:350'   sin(phi+q1+q2)+2*dth*H2xx*sin(2*(phi+q1+q2))+(-2)*dth*H2yy*sin( ... */
  /* 'CMatrix:351'   2*(phi+q1+q2))+(-2)*c2^2*dth*ml2*sin(2*(phi+q1+q2))+(-4)*c2* ... */
  /* 'CMatrix:352'   dth*L*ml2*sin(2*phi+q1+q2)+(-4)*c2*dth*l1*ml2*sin(2*(phi+q1)+ ... */
  /* 'CMatrix:353'   q2)+2*dpsi*H1zx*sin(phi+q1-th)+2*dpsi*H1xy*sin(2*phi+2*q1+ ... */
  /* 'CMatrix:354'   -th)+2*dpsi*H2zx*sin(phi+q1+q2-th)+2*dpsi*H2xy*sin(2* ... */
  /* 'CMatrix:355'   phi+2*q1+2*q2-th)+(-2)*dpsi*H1zx*sin(phi+q1+th)+2*dpsi* ... */
  /* 'CMatrix:356'   H1xy*sin(2*phi+2*q1+th)+(-2)*dpsi*H2zx*sin(phi+q1+q2+th)+2*dpsi* ... */
  /* 'CMatrix:357'   H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:358' C55=(1/2)*(2*dq2*H2xy*cos(2*(phi+q1+q2))+(-2)*dq2*(c2*L*ml2*cos( ... */
  /* 'CMatrix:359'   phi)+c2*l1*ml2*cos(phi+q1)+(-H2xx+H2yy+c2^2*ml2)*cos(phi+q1+ ... */
  /* 'CMatrix:360'   q2))*sin(phi+q1+q2)+dphi*(2*H1xy*cos(2*(phi+q1))+2*H2xy*cos(2*( ... */
  /* 'CMatrix:361'   phi+q1+q2))-Hby*sin(2*phi)+Hbz*sin(2*phi)-L^2*ml1* ... */
  /* 'CMatrix:362'   sin(2*phi)-L^2*ml2*sin(2*phi)+H1xx*sin(2*(phi+q1))- ... */
  /* 'CMatrix:363'   H1yy*sin(2*(phi+q1))-c1^2*ml1*sin(2*(phi+q1))-l1^2* ... */
  /* 'CMatrix:364'   ml2*sin(2*(phi+q1))+(-2)*c1*L*ml1*sin(2*phi+q1)+(-2)*L*l1* ... */
  /* 'CMatrix:365'   ml2*sin(2*phi+q1)+H2xx*sin(2*(phi+q1+q2))-H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:366'   q1+q2))-c2^2*ml2*sin(2*(phi+q1+q2))+(-2)*c2*L*ml2*sin(2* ... */
  /* 'CMatrix:367'   phi+q1+q2)+(-2)*c2*l1*ml2*sin(2*(phi+q1)+q2))+dq1*(2*H1xy*cos( ... */
  /* 'CMatrix:368'   2*(phi+q1))+2*H2xy*cos(2*(phi+q1+q2))-c1*L*ml1*sin(q1)+(-1) ... */
  /* 'CMatrix:369'   *L*l1*ml2*sin(q1)+H1xx*sin(2*(phi+q1))-H1yy*sin(2*(phi+q1) ... */
  /* 'CMatrix:370'   )-c1^2*ml1*sin(2*(phi+q1))-l1^2*ml2*sin(2*(phi+q1))+ ... */
  /* 'CMatrix:371'   -c1*L*ml1*sin(2*phi+q1)-L*l1*ml2*sin(2*phi+q1)- ... */
  /* 'CMatrix:372'   c2*L*ml2*sin(q1+q2)+H2xx*sin(2*(phi+q1+q2))-H2yy*sin(2*( ... */
  /* 'CMatrix:373'   phi+q1+q2))-c2^2*ml2*sin(2*(phi+q1+q2))-c2*L*ml2*sin( ... */
  /* 'CMatrix:374'   2*phi+q1+q2)+(-2)*c2*l1*ml2*sin(2*(phi+q1)+q2))); */
  /* 'CMatrix:375' C56=(1/4)*(dq2*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2- ... */
  /* 'CMatrix:376'   th)+2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2- ... */
  /* 'CMatrix:377'   th)+c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+ ... */
  /* 'CMatrix:378'   2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2* ... */
  /* 'CMatrix:379'   ml2*cos(2*phi+2*q1+2*q2-th)+2*H2zz*cos(th)+2*c2^2*ml2* ... */
  /* 'CMatrix:380'   cos(th)+c2*l1*ml2*cos(q2+th)+c2*L*ml2*cos(q1+q2+th)+(-2)*H2yz* ... */
  /* 'CMatrix:381'   cos(phi+q1+q2+th)+c2*L*ml2*cos(2*phi+q1+q2+th)+c2*l1*ml2*cos(2* ... */
  /* 'CMatrix:382'   phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+th)+H2yy*cos(2* ... */
  /* 'CMatrix:383'   phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+th)+2*H2zx*sin( ... */
  /* 'CMatrix:384'   phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2-th)+(-2)* ... */
  /* 'CMatrix:385'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))+dq1*(L*( ... */
  /* 'CMatrix:386'   c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+c1*L* ... */
  /* 'CMatrix:387'   ml1*cos(2*phi+q1-th)+L*l1*ml2*cos(2*phi+q1-th)- ... */
  /* 'CMatrix:388'   H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:389'   c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:390'   *th)+2*c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:391'   2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2-th)+ ... */
  /* 'CMatrix:392'   2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+2* ... */
  /* 'CMatrix:393'   q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*ml2* ... */
  /* 'CMatrix:394'   cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz*cos(th)+2* ... */
  /* 'CMatrix:395'   c1^2*ml1*cos(th)+2*c2^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+c1* ... */
  /* 'CMatrix:396'   L*ml1*cos(q1+th)+L*l1*ml2*cos(q1+th)+(-2)*H1yz*cos(phi+q1+th)+ ... */
  /* 'CMatrix:397'   c1*L*ml1*cos(2*phi+q1+th)+L*l1*ml2*cos(2*phi+q1+th)-H1xx* ... */
  /* 'CMatrix:398'   cos(2*phi+2*q1+th)+H1yy*cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+ ... */
  /* 'CMatrix:399'   2*q1+th)+l1^2*ml2*cos(2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+ ... */
  /* 'CMatrix:400'   c2*L*ml2*cos(q1+q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos( ... */
  /* 'CMatrix:401'   2*phi+q1+q2+th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx* ... */
  /* 'CMatrix:402'   cos(2*phi+2*q1+2*q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2* ... */
  /* 'CMatrix:403'   cos(2*phi+2*q1+2*q2+th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin( ... */
  /* 'CMatrix:404'   2*phi+2*q1-th)+2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:405'   phi+2*q1+2*q2-th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2* ... */
  /* 'CMatrix:406'   phi+2*q1+th)+(-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+ ... */
  /* 'CMatrix:407'   2*q2+th))+dphi*((Hby-Hbz+L^2*(ml1+ml2))*cos(2*phi-th)+ ... */
  /* 'CMatrix:408'   2*L*(c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:409'   2*c1*L*ml1*cos(2*phi+q1-th)+2*L*l1*ml2*cos(2*phi+q1+(-1) ... */
  /* 'CMatrix:410'   *th)-H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:411'   *th)+c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:412'   q1-th)+2*c2*l1*ml2*cos(q2-th)+2*c2*L*ml2*cos(q1+q2+( ... */
  /* 'CMatrix:413'   -1)*th)+2*H2yz*cos(phi+q1+q2-th)+2*c2*L*ml2*cos(2*phi+q1+ ... */
  /* 'CMatrix:414'   q2-th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx* ... */
  /* 'CMatrix:415'   cos(2*phi+2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:416'   c2^2*ml2*cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz* ... */
  /* 'CMatrix:417'   cos(th)+2*Hbx*cos(th)+2*c1^2*ml1*cos(th)+2*L^2*ml1*cos(th)+2* ... */
  /* 'CMatrix:418'   c2^2*ml2*cos(th)+2*L^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+Hby* ... */
  /* 'CMatrix:419'   cos(2*phi+th)-Hbz*cos(2*phi+th)+L^2*ml1*cos(2*phi+th)+ ... */
  /* 'CMatrix:420'   L^2*ml2*cos(2*phi+th)+2*c1*L*ml1*cos(q1+th)+2*L*l1*ml2*cos( ... */
  /* 'CMatrix:421'   q1+th)+(-2)*H1yz*cos(phi+q1+th)+2*c1*L*ml1*cos(2*phi+q1+th)+2* ... */
  /* 'CMatrix:422'   L*l1*ml2*cos(2*phi+q1+th)-H1xx*cos(2*phi+2*q1+th)+H1yy* ... */
  /* 'CMatrix:423'   cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+2*q1+th)+l1^2*ml2*cos( ... */
  /* 'CMatrix:424'   2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+2*c2*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:425'   +(-2)*H2yz*cos(phi+q1+q2+th)+2*c2*L*ml2*cos(2*phi+q1+q2+th)+2* ... */
  /* 'CMatrix:426'   c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:427'   th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:428'   th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:429'   2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:430'   th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2*phi+2*q1+th)+(-2)* ... */
  /* 'CMatrix:431'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))+(-1/2)* ... */
  /* 'CMatrix:432'   dpsi*(4*H1zx*cos(phi+q1+(-2)*th)+4*H2zx*cos(phi+q1+q2+(-2)*th)+ ... */
  /* 'CMatrix:433'   2*H1xy*cos(2*(phi+q1-th))+2*H2xy*cos(2*(phi+q1+q2-th)) ... */
  /* 'CMatrix:434'   +(-2)*H1xy*cos(2*(phi+q1+th))+(-2)*H2xy*cos(2*(phi+q1+q2+th))+4* ... */
  /* 'CMatrix:435'   H1zx*cos(phi+q1+2*th)+4*H2zx*cos(phi+q1+q2+2*th)+(-2)*c2*l1* ... */
  /* 'CMatrix:436'   ml2*sin(q2+2*(phi+q1-th))+(-2)*c1*L*ml1*sin(q1+(-2)*th)+( ... */
  /* 'CMatrix:437'   -2)*L*l1*ml2*sin(q1+(-2)*th)+(-4)*H1yz*sin(phi+q1+(-2)*th)+(-2) ... */
  /* 'CMatrix:438'   *c1*L*ml1*sin(2*phi+q1+(-2)*th)+(-2)*L*l1*ml2*sin(2*phi+q1+( ... */
  /* 'CMatrix:439'   -2)*th)+(-2)*c2*l1*ml2*sin(q2+(-2)*th)+(-2)*c2*L*ml2*sin(q1+ ... */
  /* 'CMatrix:440'   q2+(-2)*th)+(-4)*H2yz*sin(phi+q1+q2+(-2)*th)+(-2)*c2*L*ml2*sin( ... */
  /* 'CMatrix:441'   2*phi+q1+q2+(-2)*th)+Hbz*sin(2*(phi-th))+H1xx*sin(2*(phi+q1+ ... */
  /* 'CMatrix:442'   -th))-H1yy*sin(2*(phi+q1-th))-c1^2*ml1*sin( ... */
  /* 'CMatrix:443'   2*(phi+q1-th))-l1^2*ml2*sin(2*(phi+q1-th))+H2xx* ... */
  /* 'CMatrix:444'   sin(2*(phi+q1+q2-th))-H2yy*sin(2*(phi+q1+q2-th))+( ... */
  /* 'CMatrix:445'   -1)*c2^2*ml2*sin(2*(phi+q1+q2-th))+(-2)*H1xx*sin(2*th)+( ... */
  /* 'CMatrix:446'   -2)*H1yy*sin(2*th)+4*H1zz*sin(2*th)+(-2)*H2xx*sin(2*th)+(-2)* ... */
  /* 'CMatrix:447'   H2yy*sin(2*th)+4*H2zz*sin(2*th)+4*Hbx*sin(2*th)+(-2)*Hby*sin( ... */
  /* 'CMatrix:448'   2*th)+(-2)*Hbz*sin(2*th)+2*c1^2*ml1*sin(2*th)+2*L^2*ml1* ... */
  /* 'CMatrix:449'   sin(2*th)+2*c2^2*ml2*sin(2*th)+2*L^2*ml2*sin(2*th)+2*l1^2* ... */
  /* 'CMatrix:450'   ml2*sin(2*th)+Hby*sin(2*(-phi+th))+L^2*ml1*sin(2*(- ... */
  /* 'CMatrix:451'   phi+th))+L^2*ml2*sin(2*(-phi+th))+Hby*sin(2*(phi+th))- ... */
  /* 'CMatrix:452'   Hbz*sin(2*(phi+th))+L^2*ml1*sin(2*(phi+th))+L^2*ml2*sin(2*( ... */
  /* 'CMatrix:453'   phi+th))-H1xx*sin(2*(phi+q1+th))+H1yy*sin(2*(phi+q1+th))+ ... */
  /* 'CMatrix:454'   c1^2*ml1*sin(2*(phi+q1+th))+l1^2*ml2*sin(2*(phi+q1+th))- ... */
  /* 'CMatrix:455'   H2xx*sin(2*(phi+q1+q2+th))+H2yy*sin(2*(phi+q1+q2+th))+c2^2*ml2* ... */
  /* 'CMatrix:456'   sin(2*(phi+q1+q2+th))+2*c1*L*ml1*sin(q1+2*th)+2*L*l1*ml2*sin( ... */
  /* 'CMatrix:457'   q1+2*th)+(-4)*H1yz*sin(phi+q1+2*th)+2*c2*l1*ml2*sin(q2+2*th)+ ... */
  /* 'CMatrix:458'   2*c2*L*ml2*sin(q1+q2+2*th)+(-4)*H2yz*sin(phi+q1+q2+2*th)+2*c1* ... */
  /* 'CMatrix:459'   L*ml1*sin(q1+2*(phi+th))+2*L*l1*ml2*sin(q1+2*(phi+th))+2*c2* ... */
  /* 'CMatrix:460'   L*ml2*sin(q1+q2+2*(phi+th))+2*c2*l1*ml2*sin(q2+2*(phi+q1+th)))); */
  /* 'CMatrix:462' C57=(1/4)*(4*(dphi+dq1)*H1zx*cos(phi+q1)+4*dth*H1xy*cos(2*(phi+q1))+ ... */
  /* 'CMatrix:463'   4*dphi*H2zx*cos(phi+q1+q2)+4*dq1*H2zx*cos(phi+q1+q2)+4*dq2* ... */
  /* 'CMatrix:464'   H2zx*cos(phi+q1+q2)+4*dth*H2xy*cos(2*(phi+q1+q2))+c1*dpsi*L* ... */
  /* 'CMatrix:465'   ml1*cos(q1-th)+dpsi*L*l1*ml2*cos(q1-th)+2*dpsi*H1yz* ... */
  /* 'CMatrix:466'   cos(phi+q1-th)+c1*dpsi*L*ml1*cos(2*phi+q1-th)+dpsi*L* ... */
  /* 'CMatrix:467'   l1*ml2*cos(2*phi+q1-th)-dpsi*H1xx*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:468'   *th)+dpsi*H1yy*cos(2*phi+2*q1-th)+c1^2*dpsi*ml1*cos(2* ... */
  /* 'CMatrix:469'   phi+2*q1-th)+dpsi*l1^2*ml2*cos(2*phi+2*q1-th)+2*c2* ... */
  /* 'CMatrix:470'   dpsi*l1*ml2*cos(q2-th)+c2*dpsi*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:471'   2*dpsi*H2yz*cos(phi+q1+q2-th)+c2*dpsi*L*ml2*cos(2*phi+q1+ ... */
  /* 'CMatrix:472'   q2-th)+2*c2*dpsi*l1*ml2*cos(2*phi+2*q1+q2-th)- ... */
  /* 'CMatrix:473'   dpsi*H2xx*cos(2*phi+2*q1+2*q2-th)+dpsi*H2yy*cos(2*phi+2* ... */
  /* 'CMatrix:474'   q1+2*q2-th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:475'   2*dpsi*H1zz*cos(th)+2*dpsi*H2zz*cos(th)+2*c1^2*dpsi*ml1*cos( ... */
  /* 'CMatrix:476'   th)+2*c2^2*dpsi*ml2*cos(th)+2*dpsi*l1^2*ml2*cos(th)+c1*dpsi* ... */
  /* 'CMatrix:477'   L*ml1*cos(q1+th)+dpsi*L*l1*ml2*cos(q1+th)+(-2)*dpsi*H1yz*cos( ... */
  /* 'CMatrix:478'   phi+q1+th)+c1*dpsi*L*ml1*cos(2*phi+q1+th)+dpsi*L*l1*ml2*cos(2* ... */
  /* 'CMatrix:479'   phi+q1+th)-dpsi*H1xx*cos(2*phi+2*q1+th)+dpsi*H1yy*cos(2* ... */
  /* 'CMatrix:480'   phi+2*q1+th)+c1^2*dpsi*ml1*cos(2*phi+2*q1+th)+dpsi*l1^2*ml2* ... */
  /* 'CMatrix:481'   cos(2*phi+2*q1+th)+2*c2*dpsi*l1*ml2*cos(q2+th)+c2*dpsi*L*ml2* ... */
  /* 'CMatrix:482'   cos(q1+q2+th)+(-2)*dpsi*H2yz*cos(phi+q1+q2+th)+c2*dpsi*L*ml2*cos( ... */
  /* 'CMatrix:483'   2*phi+q1+q2+th)+2*c2*dpsi*l1*ml2*cos(2*phi+2*q1+q2+th)- ... */
  /* 'CMatrix:484'   dpsi*H2xx*cos(2*phi+2*q1+2*q2+th)+dpsi*H2yy*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:485'   q2+th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2*q2+th)+(-2)*c1*dth*L* ... */
  /* 'CMatrix:486'   ml1*sin(q1)+(-2)*dth*L*l1*ml2*sin(q1)+(-4)*dphi*H1yz*sin(phi+ ... */
  /* 'CMatrix:487'   q1)+(-4)*dq1*H1yz*sin(phi+q1)+2*dth*H1xx*sin(2*(phi+q1))+(-2)* ... */
  /* 'CMatrix:488'   dth*H1yy*sin(2*(phi+q1))+(-2)*c1^2*dth*ml1*sin(2*(phi+q1))+(-2) ... */
  /* 'CMatrix:489'   *dth*l1^2*ml2*sin(2*(phi+q1))+(-2)*c1*dth*L*ml1*sin(2*phi+ ... */
  /* 'CMatrix:490'   q1)+(-2)*dth*L*l1*ml2*sin(2*phi+q1)+(-2)*c2*dth*L*ml2*sin(q1+ ... */
  /* 'CMatrix:491'   q2)+(-4)*dphi*H2yz*sin(phi+q1+q2)+(-4)*dq1*H2yz*sin(phi+q1+q2)+( ... */
  /* 'CMatrix:492'   -4)*dq2*H2yz*sin(phi+q1+q2)+2*dth*H2xx*sin(2*(phi+q1+q2))+(-2)* ... */
  /* 'CMatrix:493'   dth*H2yy*sin(2*(phi+q1+q2))+(-2)*c2^2*dth*ml2*sin(2*(phi+q1+q2) ... */
  /* 'CMatrix:494'   )+(-2)*c2*dth*L*ml2*sin(2*phi+q1+q2)+(-4)*c2*dth*l1*ml2*sin( ... */
  /* 'CMatrix:495'   2*(phi+q1)+q2)+2*dpsi*H1zx*sin(phi+q1-th)+2*dpsi*H1xy*sin( ... */
  /* 'CMatrix:496'   2*phi+2*q1-th)+2*dpsi*H2zx*sin(phi+q1+q2-th)+2*dpsi* ... */
  /* 'CMatrix:497'   H2xy*sin(2*phi+2*q1+2*q2-th)+(-2)*dpsi*H1zx*sin(phi+q1+th)+ ... */
  /* 'CMatrix:498'   2*dpsi*H1xy*sin(2*phi+2*q1+th)+(-2)*dpsi*H2zx*sin(phi+q1+q2+th)+ ... */
  /* 'CMatrix:499'   2*dpsi*H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:500' C58=(1/4)*(4*(dphi+dq1+dq2)*H2zx*cos(phi+q1+q2)+4*dth*H2xy*cos(2*( ... */
  /* 'CMatrix:501'   phi+q1+q2))+c2*dpsi*l1*ml2*cos(q2-th)+c2*dpsi*L*ml2*cos( ... */
  /* 'CMatrix:502'   q1+q2-th)+2*dpsi*H2yz*cos(phi+q1+q2-th)+c2*dpsi*L* ... */
  /* 'CMatrix:503'   ml2*cos(2*phi+q1+q2-th)+c2*dpsi*l1*ml2*cos(2*phi+2*q1+q2+( ... */
  /* 'CMatrix:504'   -1)*th)-dpsi*H2xx*cos(2*phi+2*q1+2*q2-th)+dpsi*H2yy* ... */
  /* 'CMatrix:505'   cos(2*phi+2*q1+2*q2-th)+c2^2*dpsi*ml2*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:506'   q2-th)+2*dpsi*H2zz*cos(th)+2*c2^2*dpsi*ml2*cos(th)+c2* ... */
  /* 'CMatrix:507'   dpsi*l1*ml2*cos(q2+th)+c2*dpsi*L*ml2*cos(q1+q2+th)+(-2)*dpsi* ... */
  /* 'CMatrix:508'   H2yz*cos(phi+q1+q2+th)+c2*dpsi*L*ml2*cos(2*phi+q1+q2+th)+c2* ... */
  /* 'CMatrix:509'   dpsi*l1*ml2*cos(2*phi+2*q1+q2+th)-dpsi*H2xx*cos(2*phi+2* ... */
  /* 'CMatrix:510'   q1+2*q2+th)+dpsi*H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*dpsi*ml2* ... */
  /* 'CMatrix:511'   cos(2*phi+2*q1+2*q2+th)+(-2)*c2*dth*l1*ml2*sin(q2)+(-2)*c2* ... */
  /* 'CMatrix:512'   dth*L*ml2*sin(q1+q2)+(-4)*dphi*H2yz*sin(phi+q1+q2)+(-4)*dq1* ... */
  /* 'CMatrix:513'   H2yz*sin(phi+q1+q2)+(-4)*dq2*H2yz*sin(phi+q1+q2)+2*dth*H2xx*sin( ... */
  /* 'CMatrix:514'   2*(phi+q1+q2))+(-2)*dth*H2yy*sin(2*(phi+q1+q2))+(-2)*c2^2*dth* ... */
  /* 'CMatrix:515'   ml2*sin(2*(phi+q1+q2))+(-2)*c2*dth*L*ml2*sin(2*phi+q1+q2)+(-2)* ... */
  /* 'CMatrix:516'   c2*dth*l1*ml2*sin(2*(phi+q1)+q2)+2*dpsi*H2zx*sin(phi+q1+q2+(-1) ... */
  /* 'CMatrix:517'   *th)+2*dpsi*H2xy*sin(2*phi+2*q1+2*q2-th)+(-2)*dpsi*H2zx* ... */
  /* 'CMatrix:518'   sin(phi+q1+q2+th)+2*dpsi*H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:41' [C64, C65, C66, C67, C68] = get_C6(); */
  /* 'CMatrix:522' C64=(1/4)*(2*dq2*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2+( ... */
  /* 'CMatrix:523'   -1)*th)+H2yz*cos(phi+q1+q2-th)-c2*l1*ml2*cos(q2+th)+( ... */
  /* 'CMatrix:524'   -1)*c2*L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+H2zx*sin(phi+q1+ ... */
  /* 'CMatrix:525'   q2-th)+H2zx*sin(phi+q1+q2+th))+2*dq1*(L*(c1*ml1+l1*ml2)* ... */
  /* 'CMatrix:526'   cos(q1-th)+H1yz*cos(phi+q1-th)+c2*L*ml2*cos(q1+q2- ... */
  /* 'CMatrix:527'   th)+H2yz*cos(phi+q1+q2-th)-c1*L*ml1*cos(q1+th)-L* ... */
  /* 'CMatrix:528'   l1*ml2*cos(q1+th)+H1yz*cos(phi+q1+th)-c2*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:529'   +H2yz*cos(phi+q1+q2+th)+H1zx*sin(phi+q1-th)+H2zx*sin(phi+q1+q2+ ... */
  /* 'CMatrix:530'   -th)+H1zx*sin(phi+q1+th)+H2zx*sin(phi+q1+q2+th))+cos(th)*(4* ... */
  /* 'CMatrix:531'   dphi*(H1yz*cos(phi+q1)+H2yz*cos(phi+q1+q2)+H1zx*sin(phi+q1)+H2zx* ... */
  /* 'CMatrix:532'   sin(phi+q1+q2))+(-2)*dth*(H1zz+H2zz+Hbx+c1^2*ml1+L^2*ml1+c2^2* ... */
  /* 'CMatrix:533'   ml2+L^2*ml2+l1^2*ml2-(Hby-Hbz+L^2*(ml1+ml2))*cos(2* ... */
  /* 'CMatrix:534'   phi)+2*L*(c1*ml1+l1*ml2)*cos(q1)+H1xx*cos(2*(phi+q1))- ... */
  /* 'CMatrix:535'   H1yy*cos(2*(phi+q1))-c1^2*ml1*cos(2*(phi+q1))-l1^2* ... */
  /* 'CMatrix:536'   ml2*cos(2*(phi+q1))+(-2)*c1*L*ml1*cos(2*phi+q1)+(-2)*L*l1* ... */
  /* 'CMatrix:537'   ml2*cos(2*phi+q1)+2*c2*l1*ml2*cos(q2)+2*c2*L*ml2*cos(q1+q2)+ ... */
  /* 'CMatrix:538'   H2xx*cos(2*(phi+q1+q2))-H2yy*cos(2*(phi+q1+q2))-c2^2* ... */
  /* 'CMatrix:539'   ml2*cos(2*(phi+q1+q2))+(-2)*c2*L*ml2*cos(2*phi+q1+q2)+(-2)*c2* ... */
  /* 'CMatrix:540'   l1*ml2*cos(2*(phi+q1)+q2)+(-2)*H1xy*sin(2*(phi+q1))+(-2)*H2xy* ... */
  /* 'CMatrix:541'   sin(2*(phi+q1+q2)))+dpsi*((-2)*H1zx*cos(phi+q1-th)+(-2)* ... */
  /* 'CMatrix:542'   H1xy*cos(2*phi+2*q1-th)+(-2)*H2zx*cos(phi+q1+q2-th)+( ... */
  /* 'CMatrix:543'   -2)*H2xy*cos(2*phi+2*q1+2*q2-th)+2*H1zx*cos(phi+q1+th)+(-2) ... */
  /* 'CMatrix:544'   *H1xy*cos(2*phi+2*q1+th)+2*H2zx*cos(phi+q1+q2+th)+(-2)*H2xy*cos( ... */
  /* 'CMatrix:545'   2*phi+2*q1+2*q2+th)+Hby*sin(2*phi-th)-Hbz*sin(2*phi+( ... */
  /* 'CMatrix:546'   -1)*th)+L^2*ml1*sin(2*phi-th)+L^2*ml2*sin(2*phi-th) ... */
  /* 'CMatrix:547'   +2*H1yz*sin(phi+q1-th)+2*c1*L*ml1*sin(2*phi+q1-th)+ ... */
  /* 'CMatrix:548'   2*L*l1*ml2*sin(2*phi+q1-th)-H1xx*sin(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:549'   *th)+H1yy*sin(2*phi+2*q1-th)+c1^2*ml1*sin(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:550'   *th)+l1^2*ml2*sin(2*phi+2*q1-th)+2*H2yz*sin(phi+q1+q2+(-1) ... */
  /* 'CMatrix:551'   *th)+2*c2*L*ml2*sin(2*phi+q1+q2-th)+2*c2*l1*ml2*sin(2* ... */
  /* 'CMatrix:552'   phi+2*q1+q2-th)-H2xx*sin(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:553'   H2yy*sin(2*phi+2*q1+2*q2-th)+c2^2*ml2*sin(2*phi+2*q1+2* ... */
  /* 'CMatrix:554'   q2-th)+Hby*sin(2*phi+th)-Hbz*sin(2*phi+th)+L^2*ml1* ... */
  /* 'CMatrix:555'   sin(2*phi+th)+L^2*ml2*sin(2*phi+th)+(-2)*H1yz*sin(phi+q1+th)+2* ... */
  /* 'CMatrix:556'   c1*L*ml1*sin(2*phi+q1+th)+2*L*l1*ml2*sin(2*phi+q1+th)- ... */
  /* 'CMatrix:557'   H1xx*sin(2*phi+2*q1+th)+H1yy*sin(2*phi+2*q1+th)+c1^2*ml1*sin( ... */
  /* 'CMatrix:558'   2*phi+2*q1+th)+l1^2*ml2*sin(2*phi+2*q1+th)+(-2)*H2yz*sin(phi+ ... */
  /* 'CMatrix:559'   q1+q2+th)+2*c2*L*ml2*sin(2*phi+q1+q2+th)+2*c2*l1*ml2*sin(2* ... */
  /* 'CMatrix:560'   phi+2*q1+q2+th)-H2xx*sin(2*phi+2*q1+2*q2+th)+H2yy*sin(2* ... */
  /* 'CMatrix:561'   phi+2*q1+2*q2+th)+c2^2*ml2*sin(2*phi+2*q1+2*q2+th)))); */
  /* 'CMatrix:562' C65=(1/8)*(4*dpsi*H1zx*cos(phi+q1+(-2)*th)+4*dpsi*H2zx*cos(phi+q1+ ... */
  /* 'CMatrix:563'   q2+(-2)*th)+2*dphi*Hby*cos(2*phi-th)+(-2)*dth*Hby*cos(2* ... */
  /* 'CMatrix:564'   phi-th)+(-2)*dphi*Hbz*cos(2*phi-th)+2*dth*Hbz*cos(2* ... */
  /* 'CMatrix:565'   phi-th)+2*dphi*L^2*ml1*cos(2*phi-th)+(-2)*dth*L^2* ... */
  /* 'CMatrix:566'   ml1*cos(2*phi-th)+2*dphi*L^2*ml2*cos(2*phi-th)+(-2) ... */
  /* 'CMatrix:567'   *dth*L^2*ml2*cos(2*phi-th)+(-4)*c1*dphi*L*ml1*cos(q1+( ... */
  /* 'CMatrix:568'   -1)*th)+(-4)*dphi*L*l1*ml2*cos(q1-th)+(-4)*dth*H1yz*cos( ... */
  /* 'CMatrix:569'   phi+q1-th)+2*dpsi*H1xy*cos(2*(phi+q1-th))+4*c1*dphi* ... */
  /* 'CMatrix:570'   L*ml1*cos(2*phi+q1-th)+(-4)*c1*dth*L*ml1*cos(2*phi+q1+( ... */
  /* 'CMatrix:571'   -1)*th)+4*dphi*L*l1*ml2*cos(2*phi+q1-th)+(-4)*dth*L*l1* ... */
  /* 'CMatrix:572'   ml2*cos(2*phi+q1-th)+(-2)*dphi*H1xx*cos(2*phi+2*q1- ... */
  /* 'CMatrix:573'   th)+2*dth*H1xx*cos(2*phi+2*q1-th)+2*dphi*H1yy*cos(2*phi+ ... */
  /* 'CMatrix:574'   2*q1-th)+(-2)*dth*H1yy*cos(2*phi+2*q1-th)+2*c1^2* ... */
  /* 'CMatrix:575'   dphi*ml1*cos(2*phi+2*q1-th)+(-2)*c1^2*dth*ml1*cos(2*phi+ ... */
  /* 'CMatrix:576'   2*q1-th)+2*dphi*l1^2*ml2*cos(2*phi+2*q1-th)+(-2)* ... */
  /* 'CMatrix:577'   dth*l1^2*ml2*cos(2*phi+2*q1-th)+(-4)*c2*dphi*l1*ml2* ... */
  /* 'CMatrix:578'   cos(q2-th)+(-4)*c2*dphi*L*ml2*cos(q1+q2-th)+(-4)*dth* ... */
  /* 'CMatrix:579'   H2yz*cos(phi+q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2-th) ... */
  /* 'CMatrix:580'   )+4*c2*dphi*L*ml2*cos(2*phi+q1+q2-th)+(-4)*c2*dth*L* ... */
  /* 'CMatrix:581'   ml2*cos(2*phi+q1+q2-th)+4*c2*dphi*l1*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:582'   q2-th)+(-4)*c2*dth*l1*ml2*cos(2*phi+2*q1+q2-th)+(-2) ... */
  /* 'CMatrix:583'   *dphi*H2xx*cos(2*phi+2*q1+2*q2-th)+2*dth*H2xx*cos(2*phi+ ... */
  /* 'CMatrix:584'   2*q1+2*q2-th)+2*dphi*H2yy*cos(2*phi+2*q1+2*q2-th)+( ... */
  /* 'CMatrix:585'   -2)*dth*H2yy*cos(2*phi+2*q1+2*q2-th)+2*c2^2*dphi*ml2* ... */
  /* 'CMatrix:586'   cos(2*phi+2*q1+2*q2-th)+(-2)*c2^2*dth*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:587'   q1+2*q2-th)+(-4)*dphi*H1zz*cos(th)+(-4)*dphi*H2zz*cos(th)+( ... */
  /* 'CMatrix:588'   -4)*dphi*Hbx*cos(th)+(-4)*c1^2*dphi*ml1*cos(th)+(-4)*dphi* ... */
  /* 'CMatrix:589'   L^2*ml1*cos(th)+(-4)*c2^2*dphi*ml2*cos(th)+(-4)*dphi*L^2* ... */
  /* 'CMatrix:590'   ml2*cos(th)+(-4)*dphi*l1^2*ml2*cos(th)+2*dphi*Hby*cos(2*phi+ ... */
  /* 'CMatrix:591'   th)+2*dth*Hby*cos(2*phi+th)+(-2)*dphi*Hbz*cos(2*phi+th)+(-2)* ... */
  /* 'CMatrix:592'   dth*Hbz*cos(2*phi+th)+2*dphi*L^2*ml1*cos(2*phi+th)+2*dth* ... */
  /* 'CMatrix:593'   L^2*ml1*cos(2*phi+th)+2*dphi*L^2*ml2*cos(2*phi+th)+2*dth* ... */
  /* 'CMatrix:594'   L^2*ml2*cos(2*phi+th)+(-4)*c1*dphi*L*ml1*cos(q1+th)+(-4)* ... */
  /* 'CMatrix:595'   dphi*L*l1*ml2*cos(q1+th)+(-4)*dth*H1yz*cos(phi+q1+th)+(-2)* ... */
  /* 'CMatrix:596'   dpsi*H1xy*cos(2*(phi+q1+th))+4*c1*dphi*L*ml1*cos(2*phi+q1+th)+ ... */
  /* 'CMatrix:597'   4*c1*dth*L*ml1*cos(2*phi+q1+th)+4*dphi*L*l1*ml2*cos(2*phi+ ... */
  /* 'CMatrix:598'   q1+th)+4*dth*L*l1*ml2*cos(2*phi+q1+th)+(-2)*dphi*H1xx*cos(2* ... */
  /* 'CMatrix:599'   phi+2*q1+th)+(-2)*dth*H1xx*cos(2*phi+2*q1+th)+2*dphi*H1yy*cos( ... */
  /* 'CMatrix:600'   2*phi+2*q1+th)+2*dth*H1yy*cos(2*phi+2*q1+th)+2*c1^2*dphi* ... */
  /* 'CMatrix:601'   ml1*cos(2*phi+2*q1+th)+2*c1^2*dth*ml1*cos(2*phi+2*q1+th)+2* ... */
  /* 'CMatrix:602'   dphi*l1^2*ml2*cos(2*phi+2*q1+th)+2*dth*l1^2*ml2*cos(2*phi+ ... */
  /* 'CMatrix:603'   2*q1+th)+(-4)*c2*dphi*l1*ml2*cos(q2+th)+(-4)*c2*dphi*L*ml2* ... */
  /* 'CMatrix:604'   cos(q1+q2+th)+(-4)*dth*H2yz*cos(phi+q1+q2+th)+(-2)*dpsi*H2xy*cos( ... */
  /* 'CMatrix:605'   2*(phi+q1+q2+th))+4*c2*dphi*L*ml2*cos(2*phi+q1+q2+th)+4*c2* ... */
  /* 'CMatrix:606'   dth*L*ml2*cos(2*phi+q1+q2+th)+4*c2*dphi*l1*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:607'   q1+q2+th)+4*c2*dth*l1*ml2*cos(2*phi+2*q1+q2+th)+(-2)*dphi* ... */
  /* 'CMatrix:608'   H2xx*cos(2*phi+2*q1+2*q2+th)+(-2)*dth*H2xx*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:609'   q2+th)+2*dphi*H2yy*cos(2*phi+2*q1+2*q2+th)+2*dth*H2yy*cos(2* ... */
  /* 'CMatrix:610'   phi+2*q1+2*q2+th)+2*c2^2*dphi*ml2*cos(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:611'   c2^2*dth*ml2*cos(2*phi+2*q1+2*q2+th)+4*dpsi*H1zx*cos(phi+q1+ ... */
  /* 'CMatrix:612'   2*th)+4*dpsi*H2zx*cos(phi+q1+q2+2*th)+(-4)*dq2*cos(th)*(H2zz+ ... */
  /* 'CMatrix:613'   c2^2*ml2+c2*l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2)+H2xx*cos(2*( ... */
  /* 'CMatrix:614'   phi+q1+q2))-H2yy*cos(2*(phi+q1+q2))-c2^2*ml2*cos(2*( ... */
  /* 'CMatrix:615'   phi+q1+q2))-c2*L*ml2*cos(2*phi+q1+q2)-c2*l1*ml2*cos( ... */
  /* 'CMatrix:616'   2*(phi+q1)+q2)+(-2)*H2xy*sin(2*(phi+q1+q2)))+(-4)*dq1*cos(th)*( ... */
  /* 'CMatrix:617'   H1zz+H2zz+c1^2*ml1+c2^2*ml2+l1^2*ml2+L*(c1*ml1+l1*ml2)*cos(q1) ... */
  /* 'CMatrix:618'   +(H1xx-H1yy-c1^2*ml1-l1^2*ml2)*cos(2*(phi+q1))+( ... */
  /* 'CMatrix:619'   -1)*c1*L*ml1*cos(2*phi+q1)-L*l1*ml2*cos(2*phi+q1)+2*c2* ... */
  /* 'CMatrix:620'   l1*ml2*cos(q2)+c2*L*ml2*cos(q1+q2)+H2xx*cos(2*(phi+q1+q2))- ... */
  /* 'CMatrix:621'   H2yy*cos(2*(phi+q1+q2))-c2^2*ml2*cos(2*(phi+q1+q2))- ... */
  /* 'CMatrix:622'   c2*L*ml2*cos(2*phi+q1+q2)+(-2)*c2*l1*ml2*cos(2*(phi+q1)+q2)+( ... */
  /* 'CMatrix:623'   -2)*H1xy*sin(2*(phi+q1))+(-2)*H2xy*sin(2*(phi+q1+q2)))+(-2)*c2* ... */
  /* 'CMatrix:624'   dpsi*l1*ml2*sin(q2+2*(phi+q1-th))+(-2)*c1*dpsi*L*ml1*sin( ... */
  /* 'CMatrix:625'   q1+(-2)*th)+(-2)*dpsi*L*l1*ml2*sin(q1+(-2)*th)+(-4)*dpsi*H1yz* ... */
  /* 'CMatrix:626'   sin(phi+q1+(-2)*th)+(-2)*c1*dpsi*L*ml1*sin(2*phi+q1+(-2)*th)+( ... */
  /* 'CMatrix:627'   -2)*dpsi*L*l1*ml2*sin(2*phi+q1+(-2)*th)+(-2)*c2*dpsi*l1*ml2* ... */
  /* 'CMatrix:628'   sin(q2+(-2)*th)+(-2)*c2*dpsi*L*ml2*sin(q1+q2+(-2)*th)+(-4)* ... */
  /* 'CMatrix:629'   dpsi*H2yz*sin(phi+q1+q2+(-2)*th)+(-2)*c2*dpsi*L*ml2*sin(2*phi+ ... */
  /* 'CMatrix:630'   q1+q2+(-2)*th)+dpsi*Hbz*sin(2*(phi-th))+(-4)*dth*H1zx*sin( ... */
  /* 'CMatrix:631'   phi+q1-th)+dpsi*H1xx*sin(2*(phi+q1-th))-dpsi* ... */
  /* 'CMatrix:632'   H1yy*sin(2*(phi+q1-th))-c1^2*dpsi*ml1*sin(2*(phi+q1+( ... */
  /* 'CMatrix:633'   -1)*th))-dpsi*l1^2*ml2*sin(2*(phi+q1-th))+4*dphi* ... */
  /* 'CMatrix:634'   H1xy*sin(2*phi+2*q1-th)+(-4)*dth*H1xy*sin(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:635'   *th)+(-4)*dth*H2zx*sin(phi+q1+q2-th)+dpsi*H2xx*sin(2*(phi+ ... */
  /* 'CMatrix:636'   q1+q2-th))-dpsi*H2yy*sin(2*(phi+q1+q2-th))- ... */
  /* 'CMatrix:637'   c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+4*dphi*H2xy*sin(2* ... */
  /* 'CMatrix:638'   phi+2*q1+2*q2-th)+(-4)*dth*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:639'   th)+(-2)*dpsi*H1xx*sin(2*th)+(-2)*dpsi*H1yy*sin(2*th)+4*dpsi* ... */
  /* 'CMatrix:640'   H1zz*sin(2*th)+(-2)*dpsi*H2xx*sin(2*th)+(-2)*dpsi*H2yy*sin(2* ... */
  /* 'CMatrix:641'   th)+4*dpsi*H2zz*sin(2*th)+4*dpsi*Hbx*sin(2*th)+(-2)*dpsi*Hby* ... */
  /* 'CMatrix:642'   sin(2*th)+(-2)*dpsi*Hbz*sin(2*th)+2*c1^2*dpsi*ml1*sin(2*th)+ ... */
  /* 'CMatrix:643'   2*dpsi*L^2*ml1*sin(2*th)+2*c2^2*dpsi*ml2*sin(2*th)+2*dpsi* ... */
  /* 'CMatrix:644'   L^2*ml2*sin(2*th)+2*dpsi*l1^2*ml2*sin(2*th)+dpsi*Hby*sin(2* ... */
  /* 'CMatrix:645'   (-phi+th))+dpsi*L^2*ml1*sin(2*(-phi+th))+dpsi*L^2* ... */
  /* 'CMatrix:646'   ml2*sin(2*(-phi+th))+dpsi*Hby*sin(2*(phi+th))-dpsi* ... */
  /* 'CMatrix:647'   Hbz*sin(2*(phi+th))+dpsi*L^2*ml1*sin(2*(phi+th))+dpsi*L^2* ... */
  /* 'CMatrix:648'   ml2*sin(2*(phi+th))+(-4)*dth*H1zx*sin(phi+q1+th)-dpsi*H1xx* ... */
  /* 'CMatrix:649'   sin(2*(phi+q1+th))+dpsi*H1yy*sin(2*(phi+q1+th))+c1^2*dpsi*ml1* ... */
  /* 'CMatrix:650'   sin(2*(phi+q1+th))+dpsi*l1^2*ml2*sin(2*(phi+q1+th))+4*dphi* ... */
  /* 'CMatrix:651'   H1xy*sin(2*phi+2*q1+th)+4*dth*H1xy*sin(2*phi+2*q1+th)+(-4)* ... */
  /* 'CMatrix:652'   dth*H2zx*sin(phi+q1+q2+th)-dpsi*H2xx*sin(2*(phi+q1+q2+th))+ ... */
  /* 'CMatrix:653'   dpsi*H2yy*sin(2*(phi+q1+q2+th))+c2^2*dpsi*ml2*sin(2*(phi+q1+q2+ ... */
  /* 'CMatrix:654'   th))+4*dphi*H2xy*sin(2*phi+2*q1+2*q2+th)+4*dth*H2xy*sin(2*phi+ ... */
  /* 'CMatrix:655'   2*q1+2*q2+th)+2*c1*dpsi*L*ml1*sin(q1+2*th)+2*dpsi*L*l1*ml2* ... */
  /* 'CMatrix:656'   sin(q1+2*th)+(-4)*dpsi*H1yz*sin(phi+q1+2*th)+2*c2*dpsi*l1*ml2* ... */
  /* 'CMatrix:657'   sin(q2+2*th)+2*c2*dpsi*L*ml2*sin(q1+q2+2*th)+(-4)*dpsi*H2yz* ... */
  /* 'CMatrix:658'   sin(phi+q1+q2+2*th)+2*c1*dpsi*L*ml1*sin(q1+2*(phi+th))+2*dpsi* ... */
  /* 'CMatrix:659'   L*l1*ml2*sin(q1+2*(phi+th))+2*c2*dpsi*L*ml2*sin(q1+q2+2*(phi+ ... */
  /* 'CMatrix:660'   th))+2*c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:661' C66=(1/4)*(2*dth*(2*cos(phi)*cos(2*th)*(H1zx*cos(q1)-H1yz* ... */
  /* 'CMatrix:662'   sin(q1))+(-2)*cos(2*th)*sin(phi)*(H1yz*cos(q1)+H1zx*sin(q1))+2* ... */
  /* 'CMatrix:663'   cos(phi)*cos(2*th)*(H2zx*cos(q1+q2)-H2yz*sin(q1+q2))+(-2)* ... */
  /* 'CMatrix:664'   cos(2*th)*sin(phi)*(H2yz*cos(q1+q2)+H2zx*sin(q1+q2))+4*cos(phi)* ... */
  /* 'CMatrix:665'   cos(th)*sin(phi)*(H1xy*cos(2*q1)+(H1xx-H1yy)*cos(q1)*sin(q1) ... */
  /* 'CMatrix:666'   )*sin(th)+(-2)*cos(phi)^2*cos(th)*(H1xx*cos(q1)^2+(-2)*H1xy* ... */
  /* 'CMatrix:667'   cos(q1)*sin(q1)+H1yy*sin(q1)^2)*sin(th)+(-2)*cos(th)*sin(phi)^2* ... */
  /* 'CMatrix:668'   (H1yy*cos(q1)^2+H1xx*sin(q1)^2+H1xy*sin(2*q1))*sin(th)-cos( ... */
  /* 'CMatrix:669'   phi)^2*cos(th)*(H2xx+H2yy+(H2xx-H2yy)*cos(2*(q1+q2))+(-2)* ... */
  /* 'CMatrix:670'   H2xy*sin(2*(q1+q2)))*sin(th)-cos(th)*sin(phi)^2*(H2xx+H2yy+( ... */
  /* 'CMatrix:671'   -H2xx+H2yy)*cos(2*(q1+q2))+2*H2xy*sin(2*(q1+q2)))*sin(th)+2* ... */
  /* 'CMatrix:672'   cos(phi)*cos(th)*sin(phi)*(2*H2xy*cos(2*(q1+q2))+(H2xx-H2yy) ... */
  /* 'CMatrix:673'   *sin(2*(q1+q2)))*sin(th)+(-2)*ml1*(L*cos(phi)+c1*cos(phi+q1))* ... */
  /* 'CMatrix:674'   cos(th)*sin(psi)*(cos(psi)*(L*sin(phi)+c1*sin(phi+q1))-(L* ... */
  /* 'CMatrix:675'   cos(phi)+c1*cos(phi+q1))*sin(psi)*sin(th))+(-2)*ml2*(L*cos(phi)+ ... */
  /* 'CMatrix:676'   l1*cos(phi+q1)+c2*cos(phi+q1+q2))*cos(th)*sin(psi)*(cos(psi)*(L* ... */
  /* 'CMatrix:677'   sin(phi)+l1*sin(phi+q1)+c2*sin(phi+q1+q2))-(L*cos(phi)+l1*cos( ... */
  /* 'CMatrix:678'   phi+q1)+c2*cos(phi+q1+q2))*sin(psi)*sin(th))+(-2)*ml1*cos(psi)*( ... */
  /* 'CMatrix:679'   L*cos(phi)+c1*cos(phi+q1))*cos(th)*(-(L+c1*cos(q1))*(sin(phi) ... */
  /* 'CMatrix:680'   *sin(psi)+cos(phi)*cos(psi)*sin(th))+c1*sin(q1)*(-cos(phi)* ... */
  /* 'CMatrix:681'   sin(psi)+cos(psi)*sin(phi)*sin(th)))+(-2)*ml2*cos(psi)*(L*cos(phi) ... */
  /* 'CMatrix:682'   +l1*cos(phi+q1)+c2*cos(phi+q1+q2))*cos(th)*(-(L+l1*cos(q1)+ ... */
  /* 'CMatrix:683'   c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+(l1* ... */
  /* 'CMatrix:684'   sin(q1)+c2*sin(q1+q2))*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)* ... */
  /* 'CMatrix:685'   sin(th)))+H1zz*sin(2*th)+H2zz*sin(2*th)+Hbx*sin(2*th)-Hbz* ... */
  /* 'CMatrix:686'   cos(phi)^2*sin(2*th)-Hby*sin(phi)^2*sin(2*th))+dq2*(4* ... */
  /* 'CMatrix:687'   cos(phi)*cos(th)^2*sin(phi)*((-H2xx+H2yy)*cos(2*(q1+q2))+2* ... */
  /* 'CMatrix:688'   H2xy*sin(2*(q1+q2)))+cos(th)^2*sin(phi)^2*(4*H2xy*cos(2*(q1+q2) ... */
  /* 'CMatrix:689'   )+2*(H2xx-H2yy)*sin(2*(q1+q2)))+cos(phi)^2*cos(th)^2*((-4) ... */
  /* 'CMatrix:690'   *H2xy*cos(2*(q1+q2))+2*(-H2xx+H2yy)*sin(2*(q1+q2)))+4*ml2*( ... */
  /* 'CMatrix:691'   c2*sin(q1+q2)*(sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+c2* ... */
  /* 'CMatrix:692'   cos(q1+q2)*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)))*(( ... */
  /* 'CMatrix:693'   -1)*(L+l1*cos(q1)+c2*cos(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos( ... */
  /* 'CMatrix:694'   psi)*sin(th))+(l1*sin(q1)+c2*sin(q1+q2))*(-cos(phi)*sin(psi)+ ... */
  /* 'CMatrix:695'   cos(psi)*sin(phi)*sin(th)))+4*ml2*(cos(psi)*(L*sin(phi)+l1*sin( ... */
  /* 'CMatrix:696'   phi+q1)+c2*sin(phi+q1+q2))-(L*cos(phi)+l1*cos(phi+q1)+c2*cos( ... */
  /* 'CMatrix:697'   phi+q1+q2))*sin(psi)*sin(th))*(c2*sin(q1+q2)*(-cos(psi)*sin( ... */
  /* 'CMatrix:698'   phi)+cos(phi)*sin(psi)*sin(th))+c2*cos(q1+q2)*(cos(phi)*cos(psi)+ ... */
  /* 'CMatrix:699'   sin(phi)*sin(psi)*sin(th)))+(-2)*sin(phi)*(H2zx*cos(q1+q2)- ... */
  /* 'CMatrix:700'   H2yz*sin(q1+q2))*sin(2*th)+(-2)*cos(phi)*(H2yz*cos(q1+q2)+H2zx* ... */
  /* 'CMatrix:701'   sin(q1+q2))*sin(2*th))+dq1*((-2)*cos(th)^2*sin(2*phi)*((H1xx+( ... */
  /* 'CMatrix:702'   -1)*H1yy)*cos(2*q1)+(-2)*H1xy*sin(2*q1))+(-2)*cos(phi)^2*cos( ... */
  /* 'CMatrix:703'   th)^2*(2*H1xy*cos(2*q1)+(H1xx-H1yy)*sin(2*q1))+2*cos(th) ... */
  /* 'CMatrix:704'   ^2*sin(phi)^2*(2*H1xy*cos(2*q1)+(H1xx-H1yy)*sin(2*q1))+ ... */
  /* 'CMatrix:705'   4*cos(phi)*cos(th)^2*sin(phi)*((-H2xx+H2yy)*cos(2*(q1+q2))+ ... */
  /* 'CMatrix:706'   2*H2xy*sin(2*(q1+q2)))+cos(th)^2*sin(phi)^2*(4*H2xy*cos(2*(q1+ ... */
  /* 'CMatrix:707'   q2))+2*(H2xx-H2yy)*sin(2*(q1+q2)))+cos(phi)^2*cos(th)^2*(( ... */
  /* 'CMatrix:708'   -4)*H2xy*cos(2*(q1+q2))+2*(-H2xx+H2yy)*sin(2*(q1+q2)))+4* ... */
  /* 'CMatrix:709'   ml2*((l1*sin(q1)+c2*sin(q1+q2))*(sin(phi)*sin(psi)+cos(phi)*cos( ... */
  /* 'CMatrix:710'   psi)*sin(th))+(l1*cos(q1)+c2*cos(q1+q2))*(-cos(phi)*sin(psi)+ ... */
  /* 'CMatrix:711'   cos(psi)*sin(phi)*sin(th)))*(-(L+l1*cos(q1)+c2*cos(q1+q2))*( ... */
  /* 'CMatrix:712'   sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th))+(l1*sin(q1)+c2*sin(q1+ ... */
  /* 'CMatrix:713'   q2))*(-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th)))+4*ml2*( ... */
  /* 'CMatrix:714'   cos(psi)*(L*sin(phi)+l1*sin(phi+q1)+c2*sin(phi+q1+q2))-(L* ... */
  /* 'CMatrix:715'   cos(phi)+l1*cos(phi+q1)+c2*cos(phi+q1+q2))*sin(psi)*sin(th))*((-1) ... */
  /* 'CMatrix:716'   *(l1*sin(q1)+c2*sin(q1+q2))*(cos(psi)*sin(phi)-cos(phi)*sin( ... */
  /* 'CMatrix:717'   psi)*sin(th))+(l1*cos(q1)+c2*cos(q1+q2))*(cos(phi)*cos(psi)+sin( ... */
  /* 'CMatrix:718'   phi)*sin(psi)*sin(th)))+4*c1*ml1*(-(L+c1*cos(q1))*(sin(phi) ... */
  /* 'CMatrix:719'   *sin(psi)+cos(phi)*cos(psi)*sin(th))+c1*sin(q1)*(-cos(phi)* ... */
  /* 'CMatrix:720'   sin(psi)+cos(psi)*sin(phi)*sin(th)))*(sin(phi)*(sin(psi)*sin(q1)+ ... */
  /* 'CMatrix:721'   cos(psi)*cos(q1)*sin(th))+cos(phi)*(-cos(q1)*sin(psi)+cos(psi) ... */
  /* 'CMatrix:722'   *sin(q1)*sin(th)))+4*ml1*(cos(psi)*(L*sin(phi)+c1*sin(phi+q1))+( ... */
  /* 'CMatrix:723'   -1)*(L*cos(phi)+c1*cos(phi+q1))*sin(psi)*sin(th))*(c1*sin(phi)*( ... */
  /* 'CMatrix:724'   -cos(psi)*sin(q1)+cos(q1)*sin(psi)*sin(th))+c1*cos(phi)*(cos( ... */
  /* 'CMatrix:725'   psi)*cos(q1)+sin(psi)*sin(q1)*sin(th)))+(-2)*sin(phi)*(H1zx*cos( ... */
  /* 'CMatrix:726'   q1)-H1yz*sin(q1))*sin(2*th)+(-2)*cos(phi)*(H1yz*cos(q1)+ ... */
  /* 'CMatrix:727'   H1zx*sin(q1))*sin(2*th)+(-2)*sin(phi)*(H2zx*cos(q1+q2)- ... */
  /* 'CMatrix:728'   H2yz*sin(q1+q2))*sin(2*th)+(-2)*cos(phi)*(H2yz*cos(q1+q2)+H2zx* ... */
  /* 'CMatrix:729'   sin(q1+q2))*sin(2*th))-dphi*cos(th)*(2*H1zx*cos(phi+q1+(-1) ... */
  /* 'CMatrix:730'   *th)+2*H1xy*cos(2*phi+2*q1-th)+2*H2zx*cos(phi+q1+q2- ... */
  /* 'CMatrix:731'   th)+2*H2xy*cos(2*phi+2*q1+2*q2-th)+(-2)*H1zx*cos(phi+q1+th) ... */
  /* 'CMatrix:732'   +2*H1xy*cos(2*phi+2*q1+th)+(-2)*H2zx*cos(phi+q1+q2+th)+2*H2xy* ... */
  /* 'CMatrix:733'   cos(2*phi+2*q1+2*q2+th)-Hby*sin(2*phi-th)+Hbz*sin(2* ... */
  /* 'CMatrix:734'   phi-th)-L^2*ml1*sin(2*phi-th)-L^2*ml2* ... */
  /* 'CMatrix:735'   sin(2*phi-th)+(-2)*H1yz*sin(phi+q1-th)+(-2)*c1*L*ml1* ... */
  /* 'CMatrix:736'   sin(2*phi+q1-th)+(-2)*L*l1*ml2*sin(2*phi+q1-th)+H1xx* ... */
  /* 'CMatrix:737'   sin(2*phi+2*q1-th)-H1yy*sin(2*phi+2*q1-th)- ... */
  /* 'CMatrix:738'   c1^2*ml1*sin(2*phi+2*q1-th)-l1^2*ml2*sin(2*phi+2* ... */
  /* 'CMatrix:739'   q1-th)+(-2)*H2yz*sin(phi+q1+q2-th)+(-2)*c2*L*ml2*sin( ... */
  /* 'CMatrix:740'   2*phi+q1+q2-th)+(-2)*c2*l1*ml2*sin(2*phi+2*q1+q2-th)+ ... */
  /* 'CMatrix:741'   H2xx*sin(2*phi+2*q1+2*q2-th)-H2yy*sin(2*phi+2*q1+2* ... */
  /* 'CMatrix:742'   q2-th)-c2^2*ml2*sin(2*phi+2*q1+2*q2-th)- ... */
  /* 'CMatrix:743'   Hby*sin(2*phi+th)+Hbz*sin(2*phi+th)-L^2*ml1*sin(2*phi+th)+ ... */
  /* 'CMatrix:744'   -L^2*ml2*sin(2*phi+th)+2*H1yz*sin(phi+q1+th)+(-2)*c1*L* ... */
  /* 'CMatrix:745'   ml1*sin(2*phi+q1+th)+(-2)*L*l1*ml2*sin(2*phi+q1+th)+H1xx*sin(2* ... */
  /* 'CMatrix:746'   phi+2*q1+th)-H1yy*sin(2*phi+2*q1+th)-c1^2*ml1*sin(2* ... */
  /* 'CMatrix:747'   phi+2*q1+th)-l1^2*ml2*sin(2*phi+2*q1+th)+2*H2yz*sin(phi+ ... */
  /* 'CMatrix:748'   q1+q2+th)+(-2)*c2*L*ml2*sin(2*phi+q1+q2+th)+(-2)*c2*l1*ml2*sin( ... */
  /* 'CMatrix:749'   2*phi+2*q1+q2+th)+H2xx*sin(2*phi+2*q1+2*q2+th)-H2yy*sin(2* ... */
  /* 'CMatrix:750'   phi+2*q1+2*q2+th)-c2^2*ml2*sin(2*phi+2*q1+2*q2+th))); */
  /* 'CMatrix:751' C67=(1/8)*((-4)*dpsi*H1xy*cos(2*(phi+q1))+(-4)*dpsi*H2xy*cos(2*( ... */
  /* 'CMatrix:752'   phi+q1+q2))+(-2)*dpsi*H1zx*cos(phi+q1+(-2)*th)+(-2)*dpsi*H2zx* ... */
  /* 'CMatrix:753'   cos(phi+q1+q2+(-2)*th)+4*c1*dphi*L*ml1*cos(q1-th)+(-2)*c1* ... */
  /* 'CMatrix:754'   dth*L*ml1*cos(q1-th)+4*dphi*L*l1*ml2*cos(q1-th)+(-2) ... */
  /* 'CMatrix:755'   *dth*L*l1*ml2*cos(q1-th)+4*dphi*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:756'   (-2)*dpsi*H1xy*cos(2*(phi+q1-th))+2*c1*dth*L*ml1*cos(2* ... */
  /* 'CMatrix:757'   phi+q1-th)+2*dth*L*l1*ml2*cos(2*phi+q1-th)+(-2)*dth* ... */
  /* 'CMatrix:758'   H1xx*cos(2*phi+2*q1-th)+2*dth*H1yy*cos(2*phi+2*q1- ... */
  /* 'CMatrix:759'   th)+2*c1^2*dth*ml1*cos(2*phi+2*q1-th)+2*dth*l1^2*ml2* ... */
  /* 'CMatrix:760'   cos(2*phi+2*q1-th)+(-4)*c2*dth*l1*ml2*cos(q2-th)+4* ... */
  /* 'CMatrix:761'   c2*dphi*L*ml2*cos(q1+q2-th)+(-2)*c2*dth*L*ml2*cos(q1+q2+( ... */
  /* 'CMatrix:762'   -1)*th)+4*dphi*H2yz*cos(phi+q1+q2-th)+(-2)*dpsi*H2xy*cos( ... */
  /* 'CMatrix:763'   2*(phi+q1+q2-th))+2*c2*dth*L*ml2*cos(2*phi+q1+q2-th)+ ... */
  /* 'CMatrix:764'   4*c2*dth*l1*ml2*cos(2*phi+2*q1+q2-th)+(-2)*dth*H2xx*cos( ... */
  /* 'CMatrix:765'   2*phi+2*q1+2*q2-th)+2*dth*H2yy*cos(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:766'   th)+2*c2^2*dth*ml2*cos(2*phi+2*q1+2*q2-th)+(-4)*dth* ... */
  /* 'CMatrix:767'   H1zz*cos(th)+(-4)*dth*H2zz*cos(th)+(-4)*c1^2*dth*ml1*cos(th)+( ... */
  /* 'CMatrix:768'   -4)*c2^2*dth*ml2*cos(th)+(-4)*dth*l1^2*ml2*cos(th)+(-4)*c1* ... */
  /* 'CMatrix:769'   dphi*L*ml1*cos(q1+th)+(-2)*c1*dth*L*ml1*cos(q1+th)+(-4)*dphi* ... */
  /* 'CMatrix:770'   L*l1*ml2*cos(q1+th)+(-2)*dth*L*l1*ml2*cos(q1+th)+4*dphi*H1yz* ... */
  /* 'CMatrix:771'   cos(phi+q1+th)+(-2)*dpsi*H1xy*cos(2*(phi+q1+th))+2*c1*dth*L* ... */
  /* 'CMatrix:772'   ml1*cos(2*phi+q1+th)+2*dth*L*l1*ml2*cos(2*phi+q1+th)+(-2)*dth* ... */
  /* 'CMatrix:773'   H1xx*cos(2*phi+2*q1+th)+2*dth*H1yy*cos(2*phi+2*q1+th)+2*c1^2* ... */
  /* 'CMatrix:774'   dth*ml1*cos(2*phi+2*q1+th)+2*dth*l1^2*ml2*cos(2*phi+2*q1+th)+ ... */
  /* 'CMatrix:775'   (-4)*c2*dth*l1*ml2*cos(q2+th)+(-4)*c2*dphi*L*ml2*cos(q1+q2+th) ... */
  /* 'CMatrix:776'   +(-2)*c2*dth*L*ml2*cos(q1+q2+th)+4*dphi*H2yz*cos(phi+q1+q2+th)+( ... */
  /* 'CMatrix:777'   -2)*dpsi*H2xy*cos(2*(phi+q1+q2+th))+2*c2*dth*L*ml2*cos(2*phi+ ... */
  /* 'CMatrix:778'   q1+q2+th)+4*c2*dth*l1*ml2*cos(2*phi+2*q1+q2+th)+(-2)*dth*H2xx* ... */
  /* 'CMatrix:779'   cos(2*phi+2*q1+2*q2+th)+2*dth*H2yy*cos(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:780'   c2^2*dth*ml2*cos(2*phi+2*q1+2*q2+th)+2*dpsi*H1zx*cos(phi+q1+ ... */
  /* 'CMatrix:781'   2*th)+2*dpsi*H2zx*cos(phi+q1+q2+2*th)+(-6)*c1*dpsi*L*ml1*sin( ... */
  /* 'CMatrix:782'   q1)+(-6)*dpsi*L*l1*ml2*sin(q1)+(-2)*dpsi*H1xx*sin(2*(phi+q1))+ ... */
  /* 'CMatrix:783'   2*dpsi*H1yy*sin(2*(phi+q1))+2*c1^2*dpsi*ml1*sin(2*(phi+q1))+ ... */
  /* 'CMatrix:784'   2*dpsi*l1^2*ml2*sin(2*(phi+q1))+2*c1*dpsi*L*ml1*sin(2*phi+ ... */
  /* 'CMatrix:785'   q1)+2*dpsi*L*l1*ml2*sin(2*phi+q1)+(-6)*c2*dpsi*L*ml2*sin(q1+ ... */
  /* 'CMatrix:786'   q2)+(-2)*dpsi*H2xx*sin(2*(phi+q1+q2))+2*dpsi*H2yy*sin(2*(phi+q1+ ... */
  /* 'CMatrix:787'   q2))+2*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+2*c2*dpsi*L*ml2*sin( ... */
  /* 'CMatrix:788'   2*phi+q1+q2)+4*c2*dpsi*l1*ml2*sin(2*(phi+q1)+q2)+2*c2*dpsi* ... */
  /* 'CMatrix:789'   l1*ml2*sin(q2+2*(phi+q1-th))+c1*dpsi*L*ml1*sin(q1+(-2)*th) ... */
  /* 'CMatrix:790'   +dpsi*L*l1*ml2*sin(q1+(-2)*th)+2*dpsi*H1yz*sin(phi+q1+(-2)*th)+ ... */
  /* 'CMatrix:791'   c1*dpsi*L*ml1*sin(2*phi+q1+(-2)*th)+dpsi*L*l1*ml2*sin(2*phi+ ... */
  /* 'CMatrix:792'   q1+(-2)*th)+c2*dpsi*L*ml2*sin(q1+q2+(-2)*th)+2*dpsi*H2yz*sin( ... */
  /* 'CMatrix:793'   phi+q1+q2+(-2)*th)+c2*dpsi*L*ml2*sin(2*phi+q1+q2+(-2)*th)+4* ... */
  /* 'CMatrix:794'   dphi*H1zx*sin(phi+q1-th)-dpsi*H1xx*sin(2*(phi+q1- ... */
  /* 'CMatrix:795'   th))+dpsi*H1yy*sin(2*(phi+q1-th))+c1^2*dpsi*ml1*sin(2*( ... */
  /* 'CMatrix:796'   phi+q1-th))+dpsi*l1^2*ml2*sin(2*(phi+q1-th))+4*dth* ... */
  /* 'CMatrix:797'   H1xy*sin(2*phi+2*q1-th)+4*dphi*H2zx*sin(phi+q1+q2-th)+ ... */
  /* 'CMatrix:798'   -dpsi*H2xx*sin(2*(phi+q1+q2-th))+dpsi*H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:799'   q1+q2-th))+c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+4*dth* ... */
  /* 'CMatrix:800'   H2xy*sin(2*phi+2*q1+2*q2-th)+4*dphi*H1zx*sin(phi+q1+th)+( ... */
  /* 'CMatrix:801'   -1)*dpsi*H1xx*sin(2*(phi+q1+th))+dpsi*H1yy*sin(2*(phi+q1+th))+ ... */
  /* 'CMatrix:802'   c1^2*dpsi*ml1*sin(2*(phi+q1+th))+dpsi*l1^2*ml2*sin(2*(phi+q1+ ... */
  /* 'CMatrix:803'   th))+4*dth*H1xy*sin(2*phi+2*q1+th)+4*dphi*H2zx*sin(phi+q1+q2+th) ... */
  /* 'CMatrix:804'   +4*dq2*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:805'   H2yz*cos(phi+q1+q2-th)-c2*l1*ml2*cos(q2+th)-c2* ... */
  /* 'CMatrix:806'   L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+H2zx*sin(phi+q1+q2- ... */
  /* 'CMatrix:807'   th)+H2zx*sin(phi+q1+q2+th))+4*dq1*(L*(c1*ml1+l1*ml2)*cos(q1+(-1) ... */
  /* 'CMatrix:808'   *th)+H1yz*cos(phi+q1-th)+c2*L*ml2*cos(q1+q2-th)+H2yz* ... */
  /* 'CMatrix:809'   cos(phi+q1+q2-th)-c1*L*ml1*cos(q1+th)-L*l1*ml2* ... */
  /* 'CMatrix:810'   cos(q1+th)+H1yz*cos(phi+q1+th)-c2*L*ml2*cos(q1+q2+th)+H2yz* ... */
  /* 'CMatrix:811'   cos(phi+q1+q2+th)+H1zx*sin(phi+q1-th)+H2zx*sin(phi+q1+q2- ... */
  /* 'CMatrix:812'   th)+H1zx*sin(phi+q1+th)+H2zx*sin(phi+q1+q2+th))-dpsi*H2xx*sin( ... */
  /* 'CMatrix:813'   2*(phi+q1+q2+th))+dpsi*H2yy*sin(2*(phi+q1+q2+th))+c2^2*dpsi*ml2* ... */
  /* 'CMatrix:814'   sin(2*(phi+q1+q2+th))+4*dth*H2xy*sin(2*phi+2*q1+2*q2+th)+c1* ... */
  /* 'CMatrix:815'   dpsi*L*ml1*sin(q1+2*th)+dpsi*L*l1*ml2*sin(q1+2*th)+(-2)*dpsi* ... */
  /* 'CMatrix:816'   H1yz*sin(phi+q1+2*th)+c2*dpsi*L*ml2*sin(q1+q2+2*th)+(-2)*dpsi* ... */
  /* 'CMatrix:817'   H2yz*sin(phi+q1+q2+2*th)+c1*dpsi*L*ml1*sin(q1+2*(phi+th))+dpsi* ... */
  /* 'CMatrix:818'   L*l1*ml2*sin(q1+2*(phi+th))+c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th)) ... */
  /* 'CMatrix:819'   +2*c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:820' C68=(1/8)*((-4)*dpsi*H2xy*cos(2*(phi+q1+q2))+(-2)*dpsi*H2zx*cos(phi+ ... */
  /* 'CMatrix:821'   q1+q2+(-2)*th)+4*c2*dphi*l1*ml2*cos(q2-th)+(-2)*c2*dth* ... */
  /* 'CMatrix:822'   l1*ml2*cos(q2-th)+4*c2*dphi*L*ml2*cos(q1+q2-th)+(-2) ... */
  /* 'CMatrix:823'   *c2*dth*L*ml2*cos(q1+q2-th)+4*dphi*H2yz*cos(phi+q1+q2+(-1) ... */
  /* 'CMatrix:824'   *th)+(-2)*dpsi*H2xy*cos(2*(phi+q1+q2-th))+2*c2*dth*L* ... */
  /* 'CMatrix:825'   ml2*cos(2*phi+q1+q2-th)+2*c2*dth*l1*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:826'   q2-th)+(-2)*dth*H2xx*cos(2*phi+2*q1+2*q2-th)+2*dth* ... */
  /* 'CMatrix:827'   H2yy*cos(2*phi+2*q1+2*q2-th)+2*c2^2*dth*ml2*cos(2*phi+ ... */
  /* 'CMatrix:828'   2*q1+2*q2-th)+(-4)*dth*H2zz*cos(th)+(-4)*c2^2*dth*ml2* ... */
  /* 'CMatrix:829'   cos(th)+(-4)*c2*dphi*l1*ml2*cos(q2+th)+(-2)*c2*dth*l1*ml2*cos( ... */
  /* 'CMatrix:830'   q2+th)+(-4)*c2*dphi*L*ml2*cos(q1+q2+th)+(-2)*c2*dth*L*ml2*cos( ... */
  /* 'CMatrix:831'   q1+q2+th)+4*dphi*H2yz*cos(phi+q1+q2+th)+(-2)*dpsi*H2xy*cos(2*( ... */
  /* 'CMatrix:832'   phi+q1+q2+th))+2*c2*dth*L*ml2*cos(2*phi+q1+q2+th)+2*c2*dth*l1* ... */
  /* 'CMatrix:833'   ml2*cos(2*phi+2*q1+q2+th)+(-2)*dth*H2xx*cos(2*phi+2*q1+2*q2+th) ... */
  /* 'CMatrix:834'   +2*dth*H2yy*cos(2*phi+2*q1+2*q2+th)+2*c2^2*dth*ml2*cos(2* ... */
  /* 'CMatrix:835'   phi+2*q1+2*q2+th)+2*dpsi*H2zx*cos(phi+q1+q2+2*th)+(-6)*c2*dpsi* ... */
  /* 'CMatrix:836'   l1*ml2*sin(q2)+(-6)*c2*dpsi*L*ml2*sin(q1+q2)+(-2)*dpsi*H2xx* ... */
  /* 'CMatrix:837'   sin(2*(phi+q1+q2))+2*dpsi*H2yy*sin(2*(phi+q1+q2))+2*c2^2*dpsi* ... */
  /* 'CMatrix:838'   ml2*sin(2*(phi+q1+q2))+2*c2*dpsi*L*ml2*sin(2*phi+q1+q2)+2*c2* ... */
  /* 'CMatrix:839'   dpsi*l1*ml2*sin(2*(phi+q1)+q2)+c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+ ... */
  /* 'CMatrix:840'   -th))+c2*dpsi*l1*ml2*sin(q2+(-2)*th)+c2*dpsi*L*ml2*sin(q1+ ... */
  /* 'CMatrix:841'   q2+(-2)*th)+2*dpsi*H2yz*sin(phi+q1+q2+(-2)*th)+c2*dpsi*L*ml2* ... */
  /* 'CMatrix:842'   sin(2*phi+q1+q2+(-2)*th)+4*dphi*H2zx*sin(phi+q1+q2-th)- ... */
  /* 'CMatrix:843'   dpsi*H2xx*sin(2*(phi+q1+q2-th))+dpsi*H2yy*sin(2*(phi+q1+q2+( ... */
  /* 'CMatrix:844'   -1)*th))+c2^2*dpsi*ml2*sin(2*(phi+q1+q2-th))+4*dth*H2xy* ... */
  /* 'CMatrix:845'   sin(2*phi+2*q1+2*q2-th)+4*dphi*H2zx*sin(phi+q1+q2+th)+4* ... */
  /* 'CMatrix:846'   dq1*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:847'   H2yz*cos(phi+q1+q2-th)-c2*l1*ml2*cos(q2+th)-c2* ... */
  /* 'CMatrix:848'   L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+H2zx*sin(phi+q1+q2- ... */
  /* 'CMatrix:849'   th)+H2zx*sin(phi+q1+q2+th))+4*dq2*(c2*l1*ml2*cos(q2-th)+c2* ... */
  /* 'CMatrix:850'   L*ml2*cos(q1+q2-th)+H2yz*cos(phi+q1+q2-th)-c2*l1* ... */
  /* 'CMatrix:851'   ml2*cos(q2+th)-c2*L*ml2*cos(q1+q2+th)+H2yz*cos(phi+q1+q2+th)+ ... */
  /* 'CMatrix:852'   H2zx*sin(phi+q1+q2-th)+H2zx*sin(phi+q1+q2+th))-dpsi* ... */
  /* 'CMatrix:853'   H2xx*sin(2*(phi+q1+q2+th))+dpsi*H2yy*sin(2*(phi+q1+q2+th))+c2^2* ... */
  /* 'CMatrix:854'   dpsi*ml2*sin(2*(phi+q1+q2+th))+4*dth*H2xy*sin(2*phi+2*q1+2*q2+ ... */
  /* 'CMatrix:855'   th)+c2*dpsi*l1*ml2*sin(q2+2*th)+c2*dpsi*L*ml2*sin(q1+q2+2*th)+ ... */
  /* 'CMatrix:856'   (-2)*dpsi*H2yz*sin(phi+q1+q2+2*th)+c2*dpsi*L*ml2*sin(q1+q2+2*( ... */
  /* 'CMatrix:857'   phi+th))+c2*dpsi*l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:42' [C74, C75, C76, C77, C78] = get_C7(); */
  /* 'CMatrix:861' C74=-c2*dq2*l1*ml2*sin(q2)+L*((c1*ml1+l1*ml2)*sin(q1)+c2*ml2* ... */
  /* 'CMatrix:862'   sin(q1+q2))*(dphi-dpsi*sin(th)); */
  /* 'CMatrix:863' C75=(1/4)*(2*dth*((-2)*H1xy*cos(2*(phi+q1))+(-2)*H2xy*cos(2*(phi+ ... */
  /* 'CMatrix:864'   q1+q2))+c1*L*ml1*sin(q1)+L*l1*ml2*sin(q1)-H1xx*sin(2*(phi+ ... */
  /* 'CMatrix:865'   q1))+H1yy*sin(2*(phi+q1))+c1^2*ml1*sin(2*(phi+q1))+l1^2*ml2* ... */
  /* 'CMatrix:866'   sin(2*(phi+q1))+c1*L*ml1*sin(2*phi+q1)+L*l1*ml2*sin(2*phi+q1)+ ... */
  /* 'CMatrix:867'   c2*L*ml2*sin(q1+q2)-H2xx*sin(2*(phi+q1+q2))+H2yy*sin(2*( ... */
  /* 'CMatrix:868'   phi+q1+q2))+c2^2*ml2*sin(2*(phi+q1+q2))+c2*L*ml2*sin(2*phi+q1+ ... */
  /* 'CMatrix:869'   q2)+2*c2*l1*ml2*sin(2*(phi+q1)+q2))-dpsi*(L*(c1*ml1+l1* ... */
  /* 'CMatrix:870'   ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+c1*L*ml1*cos(2* ... */
  /* 'CMatrix:871'   phi+q1-th)+L*l1*ml2*cos(2*phi+q1-th)-H1xx*cos(2* ... */
  /* 'CMatrix:872'   phi+2*q1-th)+H1yy*cos(2*phi+2*q1-th)+c1^2*ml1*cos(2* ... */
  /* 'CMatrix:873'   phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1-th)+2*c2*l1* ... */
  /* 'CMatrix:874'   ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+2*H2yz*cos(phi+ ... */
  /* 'CMatrix:875'   q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2-th)+2*c2*l1*ml2* ... */
  /* 'CMatrix:876'   cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:877'   th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*ml2*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:878'   2*q2-th)+2*H1zz*cos(th)+2*H2zz*cos(th)+2*c1^2*ml1*cos(th) ... */
  /* 'CMatrix:879'   +2*c2^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+c1*L*ml1*cos(q1+th)+ ... */
  /* 'CMatrix:880'   L*l1*ml2*cos(q1+th)+(-2)*H1yz*cos(phi+q1+th)+c1*L*ml1*cos(2* ... */
  /* 'CMatrix:881'   phi+q1+th)+L*l1*ml2*cos(2*phi+q1+th)-H1xx*cos(2*phi+2*q1+ ... */
  /* 'CMatrix:882'   th)+H1yy*cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+2*q1+th)+l1^2* ... */
  /* 'CMatrix:883'   ml2*cos(2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+c2*L*ml2*cos(q1+ ... */
  /* 'CMatrix:884'   q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos(2*phi+q1+q2+th)+ ... */
  /* 'CMatrix:885'   2*c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:886'   q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2* ... */
  /* 'CMatrix:887'   q2+th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin(2*phi+2*q1-th) ... */
  /* 'CMatrix:888'   +2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:889'   th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2*phi+2*q1+th)+(-2)* ... */
  /* 'CMatrix:890'   H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th))); */
  /* 'CMatrix:891' C76=(1/8)*(4*dpsi*H1xy*cos(2*(phi+q1))+4*dpsi*H2xy*cos(2*(phi+q1+ ... */
  /* 'CMatrix:892'   q2))+2*dpsi*H1zx*cos(phi+q1+(-2)*th)+2*dpsi*H2zx*cos(phi+q1+q2+( ... */
  /* 'CMatrix:893'   -2)*th)+(-4)*c1*dphi*L*ml1*cos(q1-th)+(-4)*dphi*L*l1* ... */
  /* 'CMatrix:894'   ml2*cos(q1-th)+2*dpsi*H1xy*cos(2*(phi+q1-th))+(-4)* ... */
  /* 'CMatrix:895'   c2*dphi*L*ml2*cos(q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2+( ... */
  /* 'CMatrix:896'   -1)*th))+4*c1*dphi*L*ml1*cos(q1+th)+4*dphi*L*l1*ml2*cos(q1+ ... */
  /* 'CMatrix:897'   th)+2*dpsi*H1xy*cos(2*(phi+q1+th))+4*c2*dphi*L*ml2*cos(q1+q2+ ... */
  /* 'CMatrix:898'   th)+2*dpsi*H2xy*cos(2*(phi+q1+q2+th))+(-2)*dpsi*H1zx*cos(phi+q1+ ... */
  /* 'CMatrix:899'   2*th)+(-2)*dpsi*H2zx*cos(phi+q1+q2+2*th)+6*c1*dpsi*L*ml1*sin( ... */
  /* 'CMatrix:900'   q1)+6*dpsi*L*l1*ml2*sin(q1)+2*dpsi*H1xx*sin(2*(phi+q1))+(-2)* ... */
  /* 'CMatrix:901'   dpsi*H1yy*sin(2*(phi+q1))+(-2)*c1^2*dpsi*ml1*sin(2*(phi+q1))+( ... */
  /* 'CMatrix:902'   -2)*dpsi*l1^2*ml2*sin(2*(phi+q1))+(-2)*c1*dpsi*L*ml1*sin(2* ... */
  /* 'CMatrix:903'   phi+q1)+(-2)*dpsi*L*l1*ml2*sin(2*phi+q1)+6*c2*dpsi*L*ml2*sin( ... */
  /* 'CMatrix:904'   q1+q2)+2*dpsi*H2xx*sin(2*(phi+q1+q2))+(-2)*dpsi*H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:905'   q1+q2))+(-2)*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+(-2)*c2*dpsi*L* ... */
  /* 'CMatrix:906'   ml2*sin(2*phi+q1+q2)+(-4)*c2*dpsi*l1*ml2*sin(2*(phi+q1)+q2)+(-2) ... */
  /* 'CMatrix:907'   *c2*dpsi*l1*ml2*sin(q2+2*(phi+q1-th))-c1*dpsi*L* ... */
  /* 'CMatrix:908'   ml1*sin(q1+(-2)*th)-dpsi*L*l1*ml2*sin(q1+(-2)*th)+(-2)* ... */
  /* 'CMatrix:909'   dpsi*H1yz*sin(phi+q1+(-2)*th)-c1*dpsi*L*ml1*sin(2*phi+q1+( ... */
  /* 'CMatrix:910'   -2)*th)-dpsi*L*l1*ml2*sin(2*phi+q1+(-2)*th)-c2* ... */
  /* 'CMatrix:911'   dpsi*L*ml2*sin(q1+q2+(-2)*th)+(-2)*dpsi*H2yz*sin(phi+q1+q2+(-2)* ... */
  /* 'CMatrix:912'   th)-c2*dpsi*L*ml2*sin(2*phi+q1+q2+(-2)*th)+dpsi*H1xx*sin( ... */
  /* 'CMatrix:913'   2*(phi+q1-th))-dpsi*H1yy*sin(2*(phi+q1-th))- ... */
  /* 'CMatrix:914'   c1^2*dpsi*ml1*sin(2*(phi+q1-th))-dpsi*l1^2*ml2*sin( ... */
  /* 'CMatrix:915'   2*(phi+q1-th))+dpsi*H2xx*sin(2*(phi+q1+q2-th))- ... */
  /* 'CMatrix:916'   dpsi*H2yy*sin(2*(phi+q1+q2-th))-c2^2*dpsi*ml2*sin(2* ... */
  /* 'CMatrix:917'   (phi+q1+q2-th))+8*c2*dq2*l1*ml2*sin(q2)*sin(th)+dpsi*H1xx* ... */
  /* 'CMatrix:918'   sin(2*(phi+q1+th))-dpsi*H1yy*sin(2*(phi+q1+th))-c1^2* ... */
  /* 'CMatrix:919'   dpsi*ml1*sin(2*(phi+q1+th))-dpsi*l1^2*ml2*sin(2*(phi+q1+ ... */
  /* 'CMatrix:920'   th))+dpsi*H2xx*sin(2*(phi+q1+q2+th))-dpsi*H2yy*sin(2*(phi+ ... */
  /* 'CMatrix:921'   q1+q2+th))-c2^2*dpsi*ml2*sin(2*(phi+q1+q2+th))+(-2)*dth*( ... */
  /* 'CMatrix:922'   L*(c1*ml1+l1*ml2)*cos(q1-th)+2*H1yz*cos(phi+q1-th)+ ... */
  /* 'CMatrix:923'   c1*L*ml1*cos(2*phi+q1-th)+L*l1*ml2*cos(2*phi+q1-th)+ ... */
  /* 'CMatrix:924'   -H1xx*cos(2*phi+2*q1-th)+H1yy*cos(2*phi+2*q1-th)+ ... */
  /* 'CMatrix:925'   c1^2*ml1*cos(2*phi+2*q1-th)+l1^2*ml2*cos(2*phi+2*q1+(-1) ... */
  /* 'CMatrix:926'   *th)+2*c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+q2-th)+ ... */
  /* 'CMatrix:927'   2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+q2-th)+ ... */
  /* 'CMatrix:928'   2*c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos(2*phi+2* ... */
  /* 'CMatrix:929'   q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+c2^2*ml2* ... */
  /* 'CMatrix:930'   cos(2*phi+2*q1+2*q2-th)+2*H1zz*cos(th)+2*H2zz*cos(th)+2* ... */
  /* 'CMatrix:931'   c1^2*ml1*cos(th)+2*c2^2*ml2*cos(th)+2*l1^2*ml2*cos(th)+c1* ... */
  /* 'CMatrix:932'   L*ml1*cos(q1+th)+L*l1*ml2*cos(q1+th)+(-2)*H1yz*cos(phi+q1+th)+ ... */
  /* 'CMatrix:933'   c1*L*ml1*cos(2*phi+q1+th)+L*l1*ml2*cos(2*phi+q1+th)-H1xx* ... */
  /* 'CMatrix:934'   cos(2*phi+2*q1+th)+H1yy*cos(2*phi+2*q1+th)+c1^2*ml1*cos(2*phi+ ... */
  /* 'CMatrix:935'   2*q1+th)+l1^2*ml2*cos(2*phi+2*q1+th)+2*c2*l1*ml2*cos(q2+th)+ ... */
  /* 'CMatrix:936'   c2*L*ml2*cos(q1+q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos( ... */
  /* 'CMatrix:937'   2*phi+q1+q2+th)+2*c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx* ... */
  /* 'CMatrix:938'   cos(2*phi+2*q1+2*q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2* ... */
  /* 'CMatrix:939'   cos(2*phi+2*q1+2*q2+th)+2*H1zx*sin(phi+q1-th)+2*H1xy*sin( ... */
  /* 'CMatrix:940'   2*phi+2*q1-th)+2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:941'   phi+2*q1+2*q2-th)+(-2)*H1zx*sin(phi+q1+th)+2*H1xy*sin(2* ... */
  /* 'CMatrix:942'   phi+2*q1+th)+(-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+ ... */
  /* 'CMatrix:943'   2*q2+th))-c1*dpsi*L*ml1*sin(q1+2*th)-dpsi*L*l1* ... */
  /* 'CMatrix:944'   ml2*sin(q1+2*th)+2*dpsi*H1yz*sin(phi+q1+2*th)-c2*dpsi*L* ... */
  /* 'CMatrix:945'   ml2*sin(q1+q2+2*th)+2*dpsi*H2yz*sin(phi+q1+q2+2*th)-c1* ... */
  /* 'CMatrix:946'   dpsi*L*ml1*sin(q1+2*(phi+th))-dpsi*L*l1*ml2*sin(q1+2*( ... */
  /* 'CMatrix:947'   phi+th))-c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th))+(-2)*c2*dpsi* ... */
  /* 'CMatrix:948'   l1*ml2*sin(q2+2*(phi+q1+th))); */
  /* 'CMatrix:949' C77=-c2*dq2*l1*ml2*sin(q2); */
  /* 'CMatrix:950' C78=-c2*l1*ml2*sin(q2)*(dphi+dq1+dq2-dpsi*sin(th)); */
  /* 'CMatrix:43' [C84, C85, C86, C87, C88] = get_C8(); */
  /* 'CMatrix:954' C84=c2*ml2*(dq1*l1*sin(q2)+(l1*sin(q2)+L*sin(q1+q2))*(dphi- ... */
  /* 'CMatrix:955'   dpsi*sin(th))); */
  /* 'CMatrix:956' C85=-dth*H2xy*cos(2*(phi+q1+q2))+dth*(c2*L*ml2*cos(phi)+c2*l1* ... */
  /* 'CMatrix:957'   ml2*cos(phi+q1)+(-H2xx+H2yy+c2^2*ml2)*cos(phi+q1+q2))*sin(phi+ ... */
  /* 'CMatrix:958'   q1+q2)+(-1/4)*dpsi*(c2*l1*ml2*cos(q2-th)+c2*L*ml2*cos(q1+ ... */
  /* 'CMatrix:959'   q2-th)+2*H2yz*cos(phi+q1+q2-th)+c2*L*ml2*cos(2*phi+q1+ ... */
  /* 'CMatrix:960'   q2-th)+c2*l1*ml2*cos(2*phi+2*q1+q2-th)-H2xx*cos( ... */
  /* 'CMatrix:961'   2*phi+2*q1+2*q2-th)+H2yy*cos(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:962'   c2^2*ml2*cos(2*phi+2*q1+2*q2-th)+2*H2zz*cos(th)+2*c2^2* ... */
  /* 'CMatrix:963'   ml2*cos(th)+c2*l1*ml2*cos(q2+th)+c2*L*ml2*cos(q1+q2+th)+(-2)* ... */
  /* 'CMatrix:964'   H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos(2*phi+q1+q2+th)+c2*l1*ml2* ... */
  /* 'CMatrix:965'   cos(2*phi+2*q1+q2+th)-H2xx*cos(2*phi+2*q1+2*q2+th)+H2yy* ... */
  /* 'CMatrix:966'   cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2*phi+2*q1+2*q2+th)+2* ... */
  /* 'CMatrix:967'   H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2*phi+2*q1+2*q2-th)+ ... */
  /* 'CMatrix:968'   (-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2*phi+2*q1+2*q2+th)); */
  /* 'CMatrix:969' C86=(1/8)*(4*dpsi*H2xy*cos(2*(phi+q1+q2))+2*dpsi*H2zx*cos(phi+q1+q2+ ... */
  /* 'CMatrix:970'   (-2)*th)+(-4)*c2*dphi*l1*ml2*cos(q2-th)+(-4)*c2*dphi*L* ... */
  /* 'CMatrix:971'   ml2*cos(q1+q2-th)+2*dpsi*H2xy*cos(2*(phi+q1+q2-th))+4* ... */
  /* 'CMatrix:972'   c2*dphi*l1*ml2*cos(q2+th)+4*c2*dphi*L*ml2*cos(q1+q2+th)+2* ... */
  /* 'CMatrix:973'   dpsi*H2xy*cos(2*(phi+q1+q2+th))+(-2)*dpsi*H2zx*cos(phi+q1+q2+2* ... */
  /* 'CMatrix:974'   th)+6*c2*dpsi*l1*ml2*sin(q2)+6*c2*dpsi*L*ml2*sin(q1+q2)+2* ... */
  /* 'CMatrix:975'   dpsi*H2xx*sin(2*(phi+q1+q2))+(-2)*dpsi*H2yy*sin(2*(phi+q1+q2))+( ... */
  /* 'CMatrix:976'   -2)*c2^2*dpsi*ml2*sin(2*(phi+q1+q2))+(-2)*c2*dpsi*L*ml2*sin( ... */
  /* 'CMatrix:977'   2*phi+q1+q2)+(-2)*c2*dpsi*l1*ml2*sin(2*(phi+q1)+q2)-c2* ... */
  /* 'CMatrix:978'   dpsi*l1*ml2*sin(q2+2*(phi+q1-th))-c2*dpsi*l1*ml2* ... */
  /* 'CMatrix:979'   sin(q2+(-2)*th)-c2*dpsi*L*ml2*sin(q1+q2+(-2)*th)+(-2)* ... */
  /* 'CMatrix:980'   dpsi*H2yz*sin(phi+q1+q2+(-2)*th)-c2*dpsi*L*ml2*sin(2*phi+ ... */
  /* 'CMatrix:981'   q1+q2+(-2)*th)+dpsi*H2xx*sin(2*(phi+q1+q2-th))-dpsi* ... */
  /* 'CMatrix:982'   H2yy*sin(2*(phi+q1+q2-th))-c2^2*dpsi*ml2*sin(2*(phi+ ... */
  /* 'CMatrix:983'   q1+q2-th))+(-8)*c2*dq1*l1*ml2*sin(q2)*sin(th)+dpsi*H2xx* ... */
  /* 'CMatrix:984'   sin(2*(phi+q1+q2+th))-dpsi*H2yy*sin(2*(phi+q1+q2+th))- ... */
  /* 'CMatrix:985'   c2^2*dpsi*ml2*sin(2*(phi+q1+q2+th))+(-2)*dth*(c2*l1*ml2*cos( ... */
  /* 'CMatrix:986'   q2-th)+c2*L*ml2*cos(q1+q2-th)+2*H2yz*cos(phi+q1+q2+(-1) ... */
  /* 'CMatrix:987'   *th)+c2*L*ml2*cos(2*phi+q1+q2-th)+c2*l1*ml2*cos(2*phi+2* ... */
  /* 'CMatrix:988'   q1+q2-th)-H2xx*cos(2*phi+2*q1+2*q2-th)+H2yy*cos( ... */
  /* 'CMatrix:989'   2*phi+2*q1+2*q2-th)+c2^2*ml2*cos(2*phi+2*q1+2*q2- ... */
  /* 'CMatrix:990'   th)+2*H2zz*cos(th)+2*c2^2*ml2*cos(th)+c2*l1*ml2*cos(q2+th)+c2* ... */
  /* 'CMatrix:991'   L*ml2*cos(q1+q2+th)+(-2)*H2yz*cos(phi+q1+q2+th)+c2*L*ml2*cos(2* ... */
  /* 'CMatrix:992'   phi+q1+q2+th)+c2*l1*ml2*cos(2*phi+2*q1+q2+th)-H2xx*cos(2* ... */
  /* 'CMatrix:993'   phi+2*q1+2*q2+th)+H2yy*cos(2*phi+2*q1+2*q2+th)+c2^2*ml2*cos(2* ... */
  /* 'CMatrix:994'   phi+2*q1+2*q2+th)+2*H2zx*sin(phi+q1+q2-th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:995'   phi+2*q1+2*q2-th)+(-2)*H2zx*sin(phi+q1+q2+th)+2*H2xy*sin(2* ... */
  /* 'CMatrix:996'   phi+2*q1+2*q2+th))-c2*dpsi*l1*ml2*sin(q2+2*th)-c2* ... */
  /* 'CMatrix:997'   dpsi*L*ml2*sin(q1+q2+2*th)+2*dpsi*H2yz*sin(phi+q1+q2+2*th)+(-1) ... */
  /* 'CMatrix:998'   *c2*dpsi*L*ml2*sin(q1+q2+2*(phi+th))-c2*dpsi*l1*ml2*sin( ... */
  /* 'CMatrix:999'   q2+2*(phi+q1+th))); */
  /* 'CMatrix:1000' C87=c2*l1*ml2*sin(q2)*(dphi+dq1-dpsi*sin(th)); */
  /* 'CMatrix:1001' C88=0; */
  /* 'CMatrix:45' C11_83 = zeros(8, 3); */
  /* 'CMatrix:46' C14_88 = [C14, C15, C16, C17, C18;... */
  /* 'CMatrix:47'           C24, C25, C26, C27, C28;... */
  /* 'CMatrix:48'           C34, C35, C36, C37, C38;... */
  /* 'CMatrix:49'           C44, C45, C46, C47, C48;... */
  /* 'CMatrix:50'           C54, C55, C56, C57, C58;... */
  /* 'CMatrix:51'           C64, C65, C66, C67, C68;... */
  /* 'CMatrix:52'           C74, C75, C76, C77, C78;... */
  /* 'CMatrix:53'           C84, C85, C86, C87, C88]; */
  /* 'CMatrix:55' CM = [C11_83, C14_88]; */
  /* :  Gv = GVector(q, HexaConstants, ArmConstants); */
  /* 'GVector:4' g = 9.80665; */
  /* 'GVector:6' mb  = HexaConstants.Mass; */
  /* 'GVector:7' ml1 = ArmConstants.Mass1; */
  /* 'GVector:8' ml2 = ArmConstants.Mass2; */
  /* 'GVector:10' L   = ArmConstants.Hexa_to_joint_L; */
  /* 'GVector:12' l1  = ArmConstants.l1_dim(1); */
  /* 'GVector:14' c1  = ArmConstants.MC1; */
  /* 'GVector:15' c2  = ArmConstants.MC2; */
  /* 'GVector:17' phi = xi(4); */
  /* 'GVector:18' th  = xi(5); */
  /* 'GVector:20' q1   = xi(7); */
  /* 'GVector:21' q2   = xi(8); */
  /* 'GVector:23' Gv=[0,... */
  /* 'GVector:24'     0,... */
  /* 'GVector:25'     g*(mb+ml1+ml2),... */
  /* 'GVector:26'     -g*cos(th)*(-L*(ml1+ml2)*sin(phi)-(c1*ml1+l1*ml2)*sin(phi+q1)-c2*ml2*sin(phi+q1+q2)),... */
  /* 'GVector:27'     g*(L*(ml1+ml2)*cos(phi)+(c1*ml1+l1*ml2)*cos(phi+q1)+c2*ml2*cos(phi+q1+q2))*sin(th),... */
  /* 'GVector:28'     0,... */
  /* 'GVector:29'     -g*cos(th)*(-(c1*ml1+l1*ml2)*sin(phi+q1)-c2*ml2*sin(phi+q1+q2)),... */
  /* 'GVector:30'     c2*g*ml2*cos(th)*sin(phi+q1+q2)]'; */
  /* :  ginv = DM; */
  /* :  fx = DM\( -CM*dq - Gv ); */
  D14 = std::sin(D56_tmp_tmp);
  D15 = std::sin(D56_tmp_tmp_1);
  D16 = std::cos(D56_tmp_tmp_6);
  D17 = std::cos(D56_tmp_tmp_7);
  D18 = std::cos(D46_tmp_tmp_6);
  D24 = std::cos(D56_tmp_tmp_8);
  D25 = std::cos(D56_tmp_tmp_9);
  D14_tmp_tmp_0 = std::cos(D46_tmp_tmp_7);
  D17_tmp_5 = std::cos(D46_tmp_tmp_8);
  D17_tmp_2 = std::cos(D46_tmp_tmp_9);
  D34 = std::cos(D56_tmp_tmp_2);
  D35 = std::cos(D56_tmp_tmp_4);
  D37 = std::cos(D46_tmp_tmp_a);
  D38 = std::cos(D46_tmp_tmp_b);
  D45 = std::cos(D56_tmp_tmp_5);
  D46 = std::cos(D56_tmp_tmp_0);
  D47 = std::sin(D56_tmp_tmp_3);
  D48 = std::sin(ginv_tmp_tmp);
  D56_tmp_tmp_6 = -2.0 * PD_U.InBus1_Positions[4];
  D56 = std::sin(D56_tmp_tmp_1 + D56_tmp_tmp_6);
  D46_tmp_tmp_8 = D46_tmp_tmp * 2.0;
  D57 = std::sin(D46_tmp_tmp_8);
  D46_tmp_tmp_0 *= 2.0;
  D45_tmp = std::sin(D46_tmp_tmp_0);
  w_a = std::sin((-PD_U.InBus1_Positions[3] + PD_U.InBus1_Positions[4]) * 2.0);
  D48_tmp_tmp = (PD_U.InBus1_Positions[3] + PD_U.InBus1_Positions[4]) * 2.0;
  x_a = std::sin(D48_tmp_tmp);
  D56_tmp_tmp = D46_tmp_tmp_1 * 2.0;
  D24_tmp = std::sin(D56_tmp_tmp);
  D46_tmp_tmp = D46_tmp_tmp_2 * 2.0;
  D24_tmp_0 = std::sin(D46_tmp_tmp);
  D46_tmp_n = std::sin(D48_tmp_tmp + PD_U.InBus1_Positions[6]);
  D46_tmp_tmp_a = D15_tmp_tmp + D56_tmp_tmp_6;
  D46_tmp_q = std::cos(D46_tmp_tmp_a);
  D46_tmp_tmp_b = D15_tmp_tmp_0 + D56_tmp_tmp_6;
  D48_tmp_0 = std::cos(D46_tmp_tmp_b);
  D46_tmp_tmp_2 = std::cos(D46_tmp_tmp_8);
  D46_tmp_tmp_1 = std::cos(D46_tmp_tmp_0);
  D46_tmp_tmp_0 = std::cos(D56_tmp_tmp);
  D46_tmp_tmp = std::cos(D46_tmp_tmp);
  D15_tmp_tmp += ginv_tmp_tmp_0;
  D46_tmp_tmp_7 = std::cos(D15_tmp_tmp);
  D15_tmp_tmp_0 += ginv_tmp_tmp_0;
  D46_tmp_tmp_6 = std::cos(D15_tmp_tmp_0);
  D46_tmp_tmp_8 = std::sin(D46_tmp_tmp_8 + PD_U.InBus1_Positions[7]);
  D46_tmp_tmp_9 = std::sin(D56_tmp_tmp_6 + PD_U.InBus1_Positions[6]);
  D46_tmp_tmp_a = std::sin(D46_tmp_tmp_a);
  D46_tmp_tmp_b = std::sin(D46_tmp_tmp_b);
  D56_tmp_tmp_3 = std::sin(D56_tmp_tmp_3 + D56_tmp_tmp_6);
  D56_tmp_tmp_1 = std::sin((PD_U.InBus1_Positions[3] - PD_U.InBus1_Positions[4])
    * 2.0);
  D47_tmp_4 = std::sin(ginv_tmp_tmp_0 + PD_U.InBus1_Positions[6]);
  D15_tmp_tmp = std::sin(D15_tmp_tmp);
  D15_tmp_tmp_0 = std::sin(D15_tmp_tmp_0);
  D48_tmp_tmp = std::sin(D48_tmp_tmp + D14_tmp_tmp);
  D56_tmp_tmp = std::sin(D56_tmp_tmp + PD_U.InBus1_Positions[7]);
  D56_tmp_tmp_9 = std::sin(D56_tmp_tmp_6 + PD_U.InBus1_Positions[7]);
  D56_tmp_tmp_6 = std::sin(D14_tmp_tmp + D56_tmp_tmp_6);
  D56_tmp_tmp_0 = std::sin(ginv_tmp_tmp_0 + PD_U.InBus1_Positions[7]);
  D14_tmp_tmp = std::sin(D14_tmp_tmp + ginv_tmp_tmp_0);
  ginv_tmp_tmp_0 = std::cos(ginv_tmp_tmp_0);
  D56_tmp_tmp_2 = ((PD_U.InBus1_Positions[3] - PD_U.InBus1_Positions[5]) +
                   PD_U.InBus1_Positions[6]) + PD_U.InBus1_Positions[7];
  D56_tmp_tmp_4 = std::cos(D56_tmp_tmp_2);
  D56_tmp_tmp_7 = ((PD_U.InBus1_Positions[3] + PD_U.InBus1_Positions[5]) +
                   PD_U.InBus1_Positions[6]) + PD_U.InBus1_Positions[7];
  D56_tmp_tmp_8 = std::cos(D56_tmp_tmp_7);
  D56_tmp_tmp_5 = std::cos(D56_tmp_tmp_2 - PD_U.InBus1_Positions[4]);
  ginv_tmp_tmp = std::cos(D56_tmp_tmp_7 - PD_U.InBus1_Positions[4]);
  tmp = std::cos(D56_tmp_tmp_2 + PD_U.InBus1_Positions[4]);
  tmp_0 = std::cos(D56_tmp_tmp_7 + PD_U.InBus1_Positions[4]);
  D56_tmp_tmp_2 = std::sin(D56_tmp_tmp_2);
  D56_tmp_tmp_7 = std::sin(D56_tmp_tmp_7);
  D14_tmp_g = D14_tmp_g * D14_tmp_0 + D14_tmp_h * D14_tmp_4;
  D14_tmp_h = D14_tmp_e * s;
  tmp_m = 2.0 * D14_tmp_1;
  tmp_n = PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[7] *
    PD_P.ArmConstants.Mass2;
  D16_tmp_0 = D16_tmp_0 * D14_tmp_0 + D14_tmp_f;
  tmp_o = D16_tmp_0 * ginv_tmp_tmp_1;
  tmp_p = D14_tmp_h * D14_tmp_0;
  tmp_q = 2.0 * PD_U.InBus1_Velocities[4];
  tmp_r = -2.0 * PD_U.InBus1_Velocities[6];
  tmp_5d = -2.0 * D14_tmp_2;
  D14_tmp_h = (D14_tmp_h - D16_tmp_2) * tmp_m + D16_tmp_3 * tmp_5d;
  D16_tmp_2 = 2.0 * PD_U.InBus1_Velocities[6];
  D16_tmp_3 = 2.0 * s;
  tmp_1[24] = -(((((((D14_tmp_b * smax - D14_tmp_i) * D14_tmp_1 + D14_tmp_g *
                     D14_tmp_2) * (D16_tmp_2 * D14_tmp_6) + ((D16_tmp_3 *
    D15_tmp_1 * D14_tmp_0 + (D56_tmp_tmp_4 - D56_tmp_tmp_8)) * tmp_n + tmp_q * s
    * D15_tmp * D34_tmp_3)) + (D14_tmp_g * D14_tmp_1 + D14_tmp_j) * (tmp_r *
    D14_tmp)) + ((D16_tmp_1 - tmp_p) * tmp_m + tmp_o) * PD_U.InBus1_Velocities[3])
                 + D14_tmp_h * PD_U.InBus1_Velocities[5]) * 0.5);
  tmp_1[32] = -((((D15_tmp_2 * PD_U.InBus1_Velocities[5] * D15_tmp * smax +
                   tmp_n * s * D15_tmp * D34_tmp_0) + PD_U.InBus1_Velocities[6] *
                  s * D15_tmp * D37_tmp) + PD_U.InBus1_Velocities[3] * s *
                 D15_tmp * D34_tmp_3) + PD_U.InBus1_Velocities[4] * s *
                D15_tmp_2 * D14_tmp_0);
  D56_tmp_tmp_4 = D46_tmp_f * PD_U.InBus1_Velocities[7] *
    PD_P.ArmConstants.Mass2;
  D56_tmp_tmp_8 = -D16_tmp * smax + tmp_p;
  D14_tmp_g = -2.0 * D14_tmp_1;
  tmp_1[40] = -(((((((D17_tmp_tmp_2 * D14_tmp_0 + D17_tmp_tmp) * D27_tmp_0 +
                     D27_tmp_1) + D27_tmp_2) * tmp_r + (D15_tmp_2 * tmp_q *
    D15_tmp * smax + (D27_tmp * D14_tmp_5 + D17_tmp_tmp_0 * D14_tmp_7) *
    D56_tmp_tmp_4)) + (D56_tmp_tmp_8 * D14_tmp_g + tmp_o) *
                  PD_U.InBus1_Velocities[5]) + D14_tmp_h *
                 PD_U.InBus1_Velocities[3]) * 0.5);
  D14_tmp_h = PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[4] *
    PD_P.ArmConstants.Mass2;
  tmp_o = PD_U.InBus1_Velocities[3] + PD_U.InBus1_Velocities[6];
  D14_tmp_b = PD_U.InBus1_Velocities[5] * D14_tmp_0;
  D14_tmp_i = PD_P.ArmConstants.MC1 * PD_U.InBus1_Velocities[4] *
    PD_P.ArmConstants.Mass1 * D15_tmp;
  D14_tmp_j = PD_U.InBus1_Velocities[4] * PD_P.ArmConstants.l1_dim *
    PD_P.ArmConstants.Mass2 * D15_tmp;
  D16_tmp = D14_tmp_h * D15_tmp;
  D16_tmp_1 = 2.0 * PD_U.InBus1_Velocities[5];
  D17_tmp_tmp = PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[3] *
    PD_P.ArmConstants.Mass2;
  D17_tmp_tmp_2 = PD_U.InBus1_Velocities[6] + PD_U.InBus1_Velocities[7];
  D27_tmp_0 = D17_tmp_tmp_2 * 2.0 + PD_U.InBus1_Velocities[3];
  D27_tmp_1 = -2.0 * PD_U.InBus1_Velocities[5];
  D27_tmp_2 = tmp_o - D14_tmp_b;
  D14_tmp_3 *= D17_tmp_tmp;
  tmp_s = tmp_o + PD_U.InBus1_Velocities[7];
  tmp_t = tmp_s - D14_tmp_b;
  tmp_u = D14_tmp_9 * D27_tmp_1;
  tmp_v = D14_tmp_9 * PD_U.InBus1_Velocities[4];
  tmp_w = D27_tmp_1 * D14_tmp_0 + D27_tmp_0;
  tmp_1t = D46_tmp_tmp_f * PD_U.InBus1_Velocities[5];
  tmp_1w = D46_tmp_d * PD_U.InBus1_Velocities[5];
  tmp_3p = -2.0 * PD_U.InBus1_Velocities[3];
  tmp_1[48] = -(((((((((((((((((tmp_v * D14_tmp_6 * D15_tmp * D14_tmp_1 +
    D14_tmp_h * D14_tmp_7 * D15_tmp * D14_tmp_1) + tmp_1t *
    PD_P.ArmConstants.Mass1 * D14_tmp_1 * D14_tmp) + D16_tmp_1 *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D14_tmp_1 * D14_tmp) +
    D14_tmp_i * D34_tmp) + D14_tmp_j * D34_tmp) + tmp_1w *
    PD_P.ArmConstants.Mass2 * D14_tmp_1 * D14_tmp_5) + D16_tmp * D34_tmp_0) +
    D46_tmp_z * PD_U.InBus1_Velocities[3] * PD_P.ArmConstants.Mass1 * D14_tmp_1 *
    D14_tmp * D14_tmp_0) + D46_tmp_z * PD_U.InBus1_Velocities[6] *
                        PD_P.ArmConstants.Mass1 * D14_tmp_1 * D14_tmp *
                        D14_tmp_0) + tmp_3p * PD_P.ArmConstants.l1_dim *
                       PD_P.ArmConstants.Mass2 * D14_tmp_1 * D14_tmp * D14_tmp_0)
                      + tmp_r * PD_P.ArmConstants.l1_dim *
                      PD_P.ArmConstants.Mass2 * D14_tmp_1 * D14_tmp * D14_tmp_0)
                     + D46_tmp_f * PD_U.InBus1_Velocities[3] *
                     PD_P.ArmConstants.Mass2 * D14_tmp_1 * D14_tmp_5 * D14_tmp_0)
                    + D46_tmp_f * PD_U.InBus1_Velocities[6] *
                    PD_P.ArmConstants.Mass2 * D14_tmp_1 * D14_tmp_5 * D14_tmp_0)
                   + D56_tmp_tmp_4 * D14_tmp_1 * D14_tmp_5 * D14_tmp_0) * s +
                  (D16_tmp_tmp * D27_tmp_2 + tmp_t * D14_tmp_d) * (tmp_m * smax))
                 + ((((tmp_o * 2.0 * D14_tmp_9 + D14_tmp_3) * D14_tmp_0 + tmp_u)
                     * D14_tmp_6 + ((((D14_tmp_i * D14_tmp + D14_tmp_j * D14_tmp)
    + D16_tmp * D14_tmp_5) - D17_tmp_tmp * D14_tmp * D14_tmp_4 * D14_tmp_0) -
    (D16_tmp_1 - D27_tmp_0 * D14_tmp_0) * D14_tmp_d)) * s +
                    ((PD_U.InBus1_Velocities[3] * D14_tmp_6 * D14_tmp_4 + tmp_w *
                      D14_tmp_5) * D14_tmp_8 + (D14_tmp_9 * 2.0 * D27_tmp_2 +
    D14_tmp_3) * D14_tmp) * smax) * D14_tmp_2) * 0.5);
  D56_tmp_tmp_4 = tmp_s * D14_tmp_0;
  tmp_r = PD_U.InBus1_Velocities[4] * D15_tmp;
  D14_tmp_i = 2.0 * D14_tmp_7;
  D14_tmp_j = PD_U.InBus1_Velocities[5] - D56_tmp_tmp_4;
  tmp_1[56] = -(((((PD_U.InBus1_Velocities[4] * D14_tmp_7 * D15_tmp * D14_tmp_1
                    + tmp_r * D34_tmp_0) + tmp_m * D14_tmp_5 * D14_tmp_j) * s +
                  D14_tmp_i * D14_tmp_1 * smax * tmp_t) + (((D56_tmp_tmp_4 -
    PD_U.InBus1_Velocities[5]) * D14_tmp_i + tmp_r * D14_tmp_5) * s + 2.0 * smax
    * D14_tmp_5 * tmp_t) * D14_tmp_2) * (0.5 * PD_P.ArmConstants.MC2 *
    PD_P.ArmConstants.Mass2));
  D56_tmp_tmp_4 = D15_tmp_tmp_1 + D15_tmp_tmp_2;
  tmp_m = tmp_r * smax;
  tmp_r = D56_tmp_tmp_4 * PD_U.InBus1_Velocities[6];
  tmp_1[25] = -(((((((((D56_tmp_tmp_5 - ginv_tmp_tmp) - tmp) + tmp_0) + 2.0 *
                     D56_tmp_tmp_2) + 2.0 * D56_tmp_tmp_7) * (-0.25 *
    PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[7] * PD_P.ArmConstants.Mass2)
                   + (-PD_U.InBus1_Velocities[6] * s * D37_tmp + D34_tmp_3 *
                      tmp_m)) + tmp_r * smax * D14_tmp_0) + (D15_tmp_2 * smax *
    D14_tmp_0 + D34_tmp_3 * -s) * PD_U.InBus1_Velocities[3]) + (D16_tmp_0 *
    D14_tmp_1 + D56_tmp_tmp_8 * D14_tmp_2) * PD_U.InBus1_Velocities[5]);
  D56_tmp_tmp_2 = D15_tmp_2 * PD_U.InBus1_Velocities[4];
  D56_tmp_tmp_7 = PD_U.InBus1_Velocities[3] * D15_tmp;
  tmp_1[33] = -((((-PD_U.InBus1_Velocities[5] * s * D15_tmp_2 * D15_tmp + tmp_n *
                   D15_tmp * smax * D34_tmp_0) + PD_U.InBus1_Velocities[6] *
                  D15_tmp * smax * D37_tmp) + D56_tmp_tmp_7 * smax * D34_tmp_3)
                + D56_tmp_tmp_2 * smax * D14_tmp_0);
  D56_tmp_tmp_8 = PD_U.InBus1_Velocities[5] - tmp_o * D14_tmp_0;
  D56_tmp_tmp_5 = (((D16_tmp_2 + PD_U.InBus1_Velocities[3]) *
                    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 +
                    D46_tmp_tmp_f * tmp_o * PD_P.ArmConstants.Mass1) + tmp_u *
                   D14_tmp_0) + PD_U.InBus1_Velocities[3] *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * ginv_tmp_5;
  ginv_tmp_tmp = -0.5 * PD_P.ArmConstants.MC2 * PD_P.ArmConstants.Mass2;
  tmp = 4.0 * PD_U.InBus1_Velocities[5];
  tmp_0 = -4.0 * PD_U.InBus1_Velocities[6];
  D16_tmp_0 = -4.0 * PD_U.InBus1_Velocities[7];
  tmp_1[41] = -((((((((((-3.0 * PD_U.InBus1_Velocities[3] + tmp_0) + D16_tmp_0)
                       + PD_U.InBus1_Velocities[3] * ginv_tmp_tmp_0) + tmp *
                      D14_tmp_0) * (ginv_tmp_tmp * D14_tmp_7) +
                     (-PD_U.InBus1_Velocities[5] * D14_tmp_0 +
                      PD_U.InBus1_Velocities[3]) * (D46_tmp_tmp_5 * D14_tmp_a))
                    + D56_tmp_tmp_5 * D14_tmp_6) * smax +
                   ((PD_U.InBus1_Velocities[4] *
                     PD_P.ArmConstants.Hexa_to_joint_L * D14_tmp_a * D15_tmp +
                     D14_tmp_tmp_1 * D56_tmp_tmp_8) + D14_tmp_j * D14_tmp_tmp_2)
                   * D16_tmp_3) * -D14_tmp_2 + ((((-PD_U.InBus1_Velocities[3] *
    D14_tmp_0 + PD_U.InBus1_Velocities[5]) * D14_tmp_c + D16_tmp_tmp *
    D56_tmp_tmp_8) + D14_tmp_j * D14_tmp_d) * D14_tmp_1 + (tmp_v * D15_tmp_0 *
    D15_tmp + D14_tmp_h * D15_tmp_1 * D15_tmp)) * (-2.0 * s)) + (((ginv_tmp_5 *
    PD_U.InBus1_Velocities[3] + tmp_w) * D14_tmp_tmp_2 + D56_tmp_tmp_5 * D14_tmp)
    * D14_tmp_1 + (-PD_U.InBus1_Velocities[3] * PD_P.ArmConstants.l1_dim *
                   PD_P.ArmConstants.Mass2 * D15_tmp_0 * D17_tmp_3 - D17_tmp_tmp
                   * D15_tmp_1 * D17_tmp_3)) * smax) * 0.5);
  D56_tmp_tmp_8 = D16_tmp_tmp + D14_tmp_d;
  tmp_1[49] = -((((D56_tmp_tmp_4 * PD_U.InBus1_Velocities[3] * smax * D14_tmp_0
                   + (-PD_U.InBus1_Velocities[3] * s * D37_tmp + D37_tmp * tmp_m))
                  - (s * D34_tmp_0 - D15_tmp_1 * smax * D14_tmp_0) * tmp_n) +
                 (D56_tmp_tmp_4 * smax * D14_tmp_0 + D37_tmp * -s) *
                 PD_U.InBus1_Velocities[6]) + ((D56_tmp_tmp_8 * s * D14_tmp_0 +
    D14_tmp_f) * D14_tmp_1 + (-D56_tmp_tmp_8 * smax + tmp_p) * D14_tmp_2) *
                PD_U.InBus1_Velocities[5]);
  tmp_1[57] = -(((((tmp_s - PD_U.InBus1_Velocities[4]) * D46_tmp_6 + D16_tmp_1 *
                   D15_tmp_1) - (tmp_s + PD_U.InBus1_Velocities[4]) * D46_tmp_8)
                 * smax + D16_tmp_3 * D34_tmp_0 * tmp_t) * ginv_tmp_tmp);
  tmp_1[26] = -(((tmp_n * D15_tmp_1 * D15_tmp + tmp_r * D15_tmp) + D15_tmp_2 *
                 PD_U.InBus1_Velocities[3] * D15_tmp) - D34_tmp_3 *
                PD_U.InBus1_Velocities[4] * D14_tmp_0);
  tmp_1[34] = -(((D56_tmp_tmp_2 * D15_tmp - tmp_n * D34_tmp_0 * D14_tmp_0) +
                 D37_tmp * -PD_U.InBus1_Velocities[6] * D14_tmp_0) - D34_tmp_3 *
                PD_U.InBus1_Velocities[3] * D14_tmp_0);
  tmp_1[42] = -0.0;
  tmp_1[50] = -((tmp_s * PD_P.ArmConstants.MC2 * PD_P.ArmConstants.Mass2 *
                 D15_tmp_1 * D15_tmp + D14_tmp_9 * tmp_o * D15_tmp_0 * D15_tmp)
                - D37_tmp * PD_U.InBus1_Velocities[4] * D14_tmp_0);
  tmp_1[58] = -((tmp_s * D15_tmp_1 * D15_tmp - PD_U.InBus1_Velocities[4] *
                 D34_tmp_0 * D14_tmp_0) * D14_tmp_8);
  tmp_1[27] = -(-PD_U.InBus1_Velocities[6] * PD_P.ArmConstants.Hexa_to_joint_L *
                D14_tmp_9 * D14_tmp - (D17_tmp_tmp_2 *
    PD_P.ArmConstants.Hexa_to_joint_L * D14_tmp_5 + PD_U.InBus1_Velocities[7] *
    PD_P.ArmConstants.l1_dim * D14_tmp_4) * D14_tmp_8);
  D56_tmp_tmp_2 = D56_tmp_j * D46_tmp_1;
  D56_tmp_tmp_4 = PD_P.ArmConstants.Inertia1[0] * D56_tmp_7;
  D56_tmp_tmp_8 = PD_P.ArmConstants.Inertia1[4] * D56_tmp_7;
  D56_tmp_tmp_5 = D47_tmp_0 * D56_tmp_7;
  ginv_tmp_tmp = D47_tmp_1 * D56_tmp_7;
  D14_tmp_h = D46_tmp_j * D17_tmp_5;
  tmp_m = D46_tmp_tmp_3 * D14_tmp_a + (PD_P.HexaConstants.Inertia[4] -
    PD_P.HexaConstants.Inertia[8]);
  tmp_n = (((((((((tmp_m * D25 + ginv_tmp_tmp_2 * D14_tmp_tmp_0) + D56_tmp_tmp_2)
                 + D46_tmp_k * D16) + D46_tmp_l * D16) - D56_tmp_tmp_4) +
              D56_tmp_tmp_8) + D56_tmp_tmp_5) + ginv_tmp_tmp) + D14_tmp_h) +
    D46_tmp_m * D17_tmp_2;
  tmp_p = D56_tmp_k * D46_tmp_2;
  tmp_r = D46_tmp_tmp_3 * 2.0;
  D16_tmp_3 = D46_tmp_g * 2.0;
  D14_tmp_i = D46_tmp_h * 2.0;
  D14_tmp_j = PD_P.HexaConstants.Inertia[4] * D14;
  D16_tmp = PD_P.HexaConstants.Inertia[8] * D14;
  D17_tmp_tmp = D56_tmp_h * D14;
  D17_tmp_tmp_2 = D56_tmp_i * D14;
  D27_tmp_0 = PD_P.ArmConstants.Inertia1[0] * D46_tmp_y;
  D14_tmp_3 = PD_P.ArmConstants.Inertia1[4] * D46_tmp_y;
  tmp_u = D47_tmp_0 * D46_tmp_y;
  tmp_v = D47_tmp_1 * D46_tmp_y;
  tmp_w = PD_P.ArmConstants.Inertia2[0] * D46_tmp_p;
  D14_tmp_7 = PD_P.ArmConstants.Inertia2[4] * D46_tmp_p;
  D14_tmp_a = D46_tmp_e * D46_tmp_p;
  tmp_n += tmp_p;
  D14_tmp_c = D46_tmp_m * D34;
  D14_tmp_d = D46_tmp_j * D35;
  D14_tmp_tmp_1 = PD_P.ArmConstants.Inertia2[0] * D56_tmp_8;
  D14_tmp_tmp_2 = PD_P.ArmConstants.Inertia2[4] * D56_tmp_8;
  D14_tmp_f = D46_tmp_e * D56_tmp_8;
  D15_tmp_tmp_1 = 2.0 * PD_P.ArmConstants.Inertia1[8] * D15_tmp;
  D15_tmp_tmp_2 = 2.0 * PD_P.ArmConstants.Inertia2[8] * D15_tmp;
  D16_tmp_tmp = D16_tmp_3 * PD_P.ArmConstants.Mass1;
  D34_tmp_3 = D16_tmp_tmp * D15_tmp;
  D37_tmp = D14_tmp_i * PD_P.ArmConstants.Mass2;
  D46_tmp_tmp_5 = D37_tmp * D15_tmp;
  ginv_tmp_tmp_2 = D46_tmp_i * 2.0 * PD_P.ArmConstants.Mass2;
  ginv_tmp_5 = ginv_tmp_tmp_2 * D15_tmp;
  tmp_23 = D56_tmp_l * D46_tmp_3;
  tmp_24 = PD_P.ArmConstants.Inertia1[0] * D56_tmp_9;
  tmp_25 = PD_P.ArmConstants.Inertia1[4] * D56_tmp_9;
  tmp_26 = D47_tmp_0 * D56_tmp_9;
  tmp_27 = D47_tmp_1 * D56_tmp_9;
  tmp_28 = D46_tmp_j * D37;
  tmp_29 = D56_tmp_m * D46_tmp_4;
  tmp_2a = D46_tmp_j * D46;
  tmp_2b = PD_P.ArmConstants.Inertia2[0] * D56_tmp_a;
  tmp_2c = PD_P.ArmConstants.Inertia2[4] * D56_tmp_a;
  tmp_2d = D46_tmp_e * D56_tmp_a;
  D56_tmp_n *= D46_tmp_5;
  tmp_2e = ginv_tmp_6 * D56_tmp_1;
  tmp_2f = D56_tmp_o * D46_tmp_6;
  tmp_2g = D46_tmp_x * D56_tmp_2;
  tmp_2h = D56_tmp_p * D46_tmp_7;
  tmp_2i = ginv_tmp_6 * D56_tmp_5;
  tmp_2j = D56_tmp_q * D46_tmp_8;
  tmp_2k = D46_tmp_x * D56_tmp_6;
  tmp_2l = tmp_r * PD_P.ArmConstants.Mass1;
  tmp_r *= PD_P.ArmConstants.Mass2;
  tmp_n = (((((((((((((((((((((((((((((((((((((((((tmp_n + D14_tmp_c) +
    D14_tmp_d) - D14_tmp_tmp_1) + D14_tmp_tmp_2) + D14_tmp_f) + D15_tmp_tmp_1) +
    D15_tmp_tmp_2) + 2.0 * PD_P.HexaConstants.Inertia[0] * D15_tmp) + D34_tmp_3)
    + tmp_2l * D15_tmp) + D46_tmp_tmp_5) + tmp_r * D15_tmp) + ginv_tmp_5) +
    PD_P.HexaConstants.Inertia[4] * D17) - PD_P.HexaConstants.Inertia[8] * D17)
    + D56_tmp_h * D17) + D56_tmp_i * D17) + D46_tmp_k * D18) + D46_tmp_l * D18)
    + tmp_23) + D46_tmp_k * D24) + D46_tmp_l * D24) - tmp_24) + tmp_25) + tmp_26)
    + tmp_27) + tmp_28) + D46_tmp_m * D38) + tmp_29) + D46_tmp_m * D45) + tmp_2a)
                    - tmp_2b) + tmp_2c) + tmp_2d) + D56_tmp_n) + tmp_2e) +
               tmp_2f) + tmp_2g) + tmp_2h) + tmp_2i) + tmp_2j) + tmp_2k;
  D14_tmp_c = D56_tmp_f * D46_tmp_a + D56_tmp_g * D46_tmp_c;
  tmp_5n = D46_tmp_j * D48;
  tmp_1[35] = -(((((((((((((((((D14_tmp_c + D14_tmp_j) - D16_tmp) + D17_tmp_tmp)
    + D17_tmp_tmp_2) - D27_tmp_0) + D14_tmp_3) + tmp_u) + tmp_v) + D46_tmp_k *
                        D15) + D46_tmp_l * D15) - tmp_w) + D14_tmp_7) +
                    D14_tmp_a) + D46_tmp_m * D47) + tmp_5n) * tmp_q + tmp_n *
                 -PD_U.InBus1_Velocities[5]) * 0.25);
  tmp_x = -2.0 * PD_U.InBus1_Velocities[4];
  tmp_y = tmp_x * D46_tmp_tmp_3;
  tmp_z = -4.0 * PD_U.InBus1_Velocities[4];
  tmp_1g = -4.0 * PD_P.ArmConstants.MC1;
  tmp_10 = tmp_1g * PD_U.InBus1_Velocities[4] *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1;
  tmp_3v = tmp_z * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.l1_dim;
  tmp_3v *= PD_P.ArmConstants.Mass2;
  tmp_1h = -4.0 * PD_P.ArmConstants.MC2;
  tmp_11 = tmp_1h * PD_U.InBus1_Velocities[4];
  tmp_12 = tmp_11 * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  tmp_11 = tmp_11 * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_14 = tmp_x * PD_P.HexaConstants.Inertia[4];
  tmp_15 = tmp_q * PD_P.HexaConstants.Inertia[8];
  tmp_16 = tmp_y * PD_P.ArmConstants.Mass1;
  tmp_y *= PD_P.ArmConstants.Mass2;
  tmp_17 = D16_tmp_1 * PD_P.ArmConstants.Inertia1[3];
  tmp_18 = tmp_q * PD_P.ArmConstants.Inertia1[0];
  tmp_19 = tmp_x * PD_P.ArmConstants.Inertia1[4];
  tmp_1a = D46_tmp_tmp_c * PD_U.InBus1_Velocities[4] * PD_P.ArmConstants.Mass1;
  tmp_1b = tmp_x * D46_tmp_i * PD_P.ArmConstants.Mass2;
  tmp_1d = D16_tmp_1 * PD_P.ArmConstants.Inertia2[3];
  tmp_1z = D16_tmp_1 * PD_P.ArmConstants.Inertia1[6];
  tmp_20 = D16_tmp_1 * PD_P.ArmConstants.Inertia2[6];
  tmp_3o = tmp_14 * D25;
  tmp_3q = tmp_15 * D25;
  tmp_3r = tmp_16 * D25;
  tmp_3s = tmp_y * D25;
  tmp_48 = tmp_z * PD_P.ArmConstants.Inertia1[7];
  tmp_3t = tmp_48 * D46_tmp_1;
  tmp_3u = tmp_17 * D46_tmp_tmp_2;
  tmp_3w = tmp_10 * D16;
  tmp_3x = tmp_3v * D16;
  tmp_3y = tmp_18 * D56_tmp_7;
  tmp_3z = tmp_19 * D56_tmp_7;
  tmp_40 = tmp_1a * D56_tmp_7;
  tmp_41 = tmp_1b * D56_tmp_7;
  tmp_49 = tmp_z * PD_P.ArmConstants.Inertia2[7];
  tmp_42 = tmp_49 * D46_tmp_2;
  tmp_43 = tmp_1d * D46_tmp_tmp_1;
  tmp_44 = tmp_12 * D34;
  tmp_5e = tmp_11 * D17_tmp_5;
  tmp_67 = tmp * PD_P.ArmConstants.Inertia2[3] * D46_tmp_c;
  tmp_68 = tmp_20 * D48_tmp_0;
  tmp_5o = ((tmp * PD_P.ArmConstants.Inertia1[3] * D46_tmp_a + tmp_67) + tmp_1z *
            D46_tmp_q) + tmp_68;
  tmp_9 = ((((((((((((((((((tmp_5o + tmp_3o) + tmp_3q) + tmp_3r) + tmp_3s) +
                        tmp_10 * D14_tmp_tmp_0) + tmp_3v * D14_tmp_tmp_0) +
                      tmp_3t) + tmp_3u) + tmp_3w) + tmp_3x) + tmp_3y) + tmp_3z)
                + tmp_40) + tmp_41) + tmp_5e) + tmp_12 * D17_tmp_2) + tmp_42) +
           tmp_43) + tmp_44;
  tmp_a = tmp_11 * D35;
  tmp_1e = tmp_q * PD_P.ArmConstants.Inertia2[0];
  tmp_b = tmp_1e * D56_tmp_8;
  tmp_c = tmp_x * PD_P.ArmConstants.Inertia2[4];
  tmp_d = D46_tmp_tmp_d * PD_U.InBus1_Velocities[4] * PD_P.ArmConstants.Mass2;
  tmp_5f = _mm_set1_pd(PD_U.InBus1_Velocities[4]);
  tmp_i = _mm_mul_pd(_mm_set1_pd(-4.0), tmp_5f);
  _mm_storeu_pd(&tmp_h[0], tmp_i);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  tmp_e = tmp_h[0];
  tmp_f = tmp_h[1];
  tmp_g = D46_tmp_g * -4.0;
  tmp_13 = tmp_z * D46_tmp_tmp_3;
  tmp_1c = 4.0 * PD_U.InBus1_Velocities[4];
  tmp_1f = D27_tmp_1 * D46_tmp_tmp_3;
  tmp_21 = D27_tmp_1 * PD_P.ArmConstants.Inertia1[6];
  tmp_22 = D27_tmp_1 * PD_P.ArmConstants.Inertia2[6];
  tmp_45 = tmp_c * D56_tmp_8;
  tmp_46 = tmp_d * D56_tmp_8;
  tmp_47 = -4.0 * D46_tmp_h;
  tmp_4b = -4.0 * PD_U.InBus1_Velocities[5];
  tmp_4r = D27_tmp_1 * PD_P.ArmConstants.Inertia1[4];
  tmp_4s = D27_tmp_1 * PD_P.ArmConstants.Inertia2[4];
  tmp_4t = D27_tmp_1 * PD_P.HexaConstants.Inertia[4];
  tmp_5g = tmp_g * PD_U.InBus1_Velocities[4] * PD_P.ArmConstants.Mass1 * D15_tmp;
  tmp_5m = tmp_47 * PD_U.InBus1_Velocities[4];
  tmp_5m = tmp_5m * PD_P.ArmConstants.Mass2 * D15_tmp;
  tmp_5h = tmp_z * D46_tmp_i * PD_P.ArmConstants.Mass2 * D15_tmp;
  tmp_5i = tmp_11 * D37;
  tmp_5p = tmp_17 * D46_tmp_tmp_0;
  tmp_5q = tmp_1d * D46_tmp_tmp;
  tmp_5r = tmp_21 * D46_tmp_tmp_7;
  tmp_5s = tmp_22 * D46_tmp_tmp_6;
  tmp_5t = D16_tmp_1 * PD_P.ArmConstants.Inertia1[0] * D46_tmp_y;
  D46_tmp_tmp_c = D46_tmp_tmp_c * PD_U.InBus1_Velocities[5] *
    PD_P.ArmConstants.Mass1;
  tmp_5u = D27_tmp_1 * D46_tmp_i;
  tmp_5v = tmp_4r * D46_tmp_y;
  D46_tmp_tmp_c *= D46_tmp_y;
  tmp_5u = tmp_5u * PD_P.ArmConstants.Mass2 * D46_tmp_y;
  tmp_5w = D16_tmp_1 * PD_P.ArmConstants.Inertia2[0] * D46_tmp_p;
  tmp_5x = tmp_4s * D46_tmp_p;
  D46_tmp_tmp_d = D46_tmp_tmp_d * PD_U.InBus1_Velocities[5] *
    PD_P.ArmConstants.Mass2 * D46_tmp_p;
  tmp_9 = (((((((((((((((((((((((((((((((((((((((((((((((((tmp_9 + tmp_a) +
    tmp_b) + tmp_45) + tmp_46) + tmp_e * PD_P.ArmConstants.Inertia1[8] * D15_tmp)
    + tmp_f * PD_P.ArmConstants.Inertia2[8] * D15_tmp) + tmp_z *
    PD_P.HexaConstants.Inertia[0] * D15_tmp) + tmp_5g) + tmp_13 *
    PD_P.ArmConstants.Mass1 * D15_tmp) + tmp_5m) + tmp_13 *
    PD_P.ArmConstants.Mass2 * D15_tmp) + tmp_5h) + tmp_14 * D17) + tmp_15 * D17)
    + tmp_16 * D17) + tmp_y * D17) + tmp_10 * D18) + tmp_3v * D18) + tmp_1c *
    PD_P.ArmConstants.Inertia1[7] * D46_tmp_3) + tmp_5p) + tmp_10 * D24) +
    tmp_3v * D24) + tmp_18 * D56_tmp_9) + tmp_19 * D56_tmp_9) + tmp_1a *
    D56_tmp_9) + tmp_1b * D56_tmp_9) + tmp_5i) + tmp_12 * D38) + tmp_1c *
    PD_P.ArmConstants.Inertia2[7] * D46_tmp_4) + tmp_5q) + tmp_12 * D45) +
    tmp_11 * D46) + tmp_1e * D56_tmp_a) + tmp_c * D56_tmp_a) + tmp_d * D56_tmp_a)
                        + tmp_5r) + tmp_5s) + tmp_4t * D14) + D16_tmp_1 *
                     PD_P.HexaConstants.Inertia[8] * D14) + tmp_1f *
                    PD_P.ArmConstants.Mass1 * D14) + tmp_1f *
                   PD_P.ArmConstants.Mass2 * D14) + tmp_5t) + tmp_5v) +
                D46_tmp_tmp_c) + tmp_5u) + tmp_1g * PD_U.InBus1_Velocities[5] *
              PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1 * D15)
             + tmp_4b * PD_P.ArmConstants.Hexa_to_joint_L *
             PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D15) + tmp_5w)
           + tmp_5x) + D46_tmp_tmp_d;
  tmp_e = tmp_1h * PD_U.InBus1_Velocities[5];
  tmp_f = tmp_e * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2 *
    D47;
  tmp_e = tmp_e * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_13 = D46_tmp_f * PD_U.InBus1_Velocities[5];
  tmp_1f = tmp_13 * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_5 = PD_P.ArmConstants.Inertia1[7];
  tmp_6 = D46_tmp_z * PD_U.InBus1_Velocities[5] *
    PD_P.ArmConstants.Hexa_to_joint_L;
  tmp_7 = D27_tmp_1 * PD_P.ArmConstants.Hexa_to_joint_L;
  tmp_8 = PD_P.ArmConstants.l1_dim;
  tmp_1i = D46_tmp_tmp_3 * PD_U.InBus1_Velocities[5];
  tmp_1j = PD_P.HexaConstants.Inertia[4] * PD_U.InBus1_Velocities[5];
  tmp_1k = PD_U.InBus1_Velocities[5] * PD_P.HexaConstants.Inertia[8];
  tmp_1l = tmp_1i * PD_P.ArmConstants.Mass1;
  tmp_1i *= PD_P.ArmConstants.Mass2;
  tmp_1m = PD_P.ArmConstants.Inertia1[0] * PD_U.InBus1_Velocities[5];
  tmp_1n = PD_P.ArmConstants.Inertia1[4] * PD_U.InBus1_Velocities[5];
  D46_tmp_g = D46_tmp_g * PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Mass1;
  tmp_1o = tmp_z * PD_P.ArmConstants.Inertia1[3];
  tmp_1p = PD_P.ArmConstants.Inertia2[0] * PD_U.InBus1_Velocities[5];
  tmp_1q = PD_P.ArmConstants.Inertia2[4] * PD_U.InBus1_Velocities[5];
  tmp_1r = D46_tmp_h * PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Mass2;
  tmp_1s = tmp_z * PD_P.ArmConstants.Inertia2[3];
  tmp_6 *= PD_P.ArmConstants.Mass1;
  tmp_7 = tmp_7 * tmp_8 * PD_P.ArmConstants.Mass2;
  tmp_13 = tmp_13 * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  tmp_8 = PD_P.ArmConstants.l1_dim * D14_tmp_4 +
    PD_P.ArmConstants.Hexa_to_joint_L * D14_tmp_5;
  tmp_1u = D16_tmp_1 * PD_P.ArmConstants.Inertia1[7];
  tmp_1v = D46_tmp_i * PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Mass2;
  tmp_1x = D16_tmp_1 * PD_P.ArmConstants.Inertia2[7];
  tmp_5 *= D27_tmp_1;
  tmp_1y = D27_tmp_1 * PD_P.ArmConstants.Inertia2[7];
  tmp_4a = tmp_1f * D46_tmp_tmp_8;
  tmp_4c = tmp_6 * D56;
  tmp_4d = tmp_7 * D56;
  tmp_4e = tmp_13 * D56_tmp_tmp_3;
  tmp_4f = tmp_1k * D56_tmp_tmp_1;
  tmp_54 = tmp_z * PD_P.ArmConstants.Inertia1[6];
  tmp_4g = tmp_54 * D46_tmp_5;
  tmp_4h = tmp_1m * D57;
  tmp_4i = tmp_1n * D57;
  tmp_4j = D46_tmp_g * D57;
  tmp_4k = tmp_1v * D57;
  tmp_4l = tmp_1o * D56_tmp_1;
  tmp_58 = tmp_z * PD_P.ArmConstants.Inertia2[6];
  tmp_4m = tmp_58 * D46_tmp_6;
  tmp_4n = tmp_1p * D45_tmp;
  tmp_4o = tmp_1q * D45_tmp;
  tmp_4p = tmp_1r * D45_tmp;
  tmp_4q = tmp_1s * D56_tmp_2;
  tmp_4x = tmp_1j * w_a;
  tmp_4y = tmp_1l * w_a;
  tmp_4z = tmp_1i * w_a;
  tmp_50 = tmp_1j * x_a;
  tmp_51 = tmp_1k * x_a;
  tmp_52 = tmp_1l * x_a;
  tmp_53 = tmp_1i * x_a;
  tmp_55 = tmp_1m * D24_tmp;
  tmp_56 = tmp_1n * D24_tmp;
  tmp_57 = D46_tmp_g * D24_tmp;
  tmp_59 = tmp_1p * D24_tmp_0;
  tmp_5a = tmp_1q * D24_tmp_0;
  tmp_5b = tmp_1r * D24_tmp_0;
  tmp_e *= D48;
  tmp_5y = tmp_5 * D46_tmp_tmp_a;
  tmp_5z = tmp_1y * D46_tmp_tmp_b;
  tmp_60 = 8.0 * PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[7];
  tmp_63 = tmp_1u * D15_tmp_tmp;
  tmp_64 = tmp_1x * D15_tmp_tmp_0;
  tmp_65 = tmp_1f * D56_tmp_tmp;
  tmp_1[43] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_9 + tmp_f) +
    tmp_e) + tmp_4a) + tmp_5y) + tmp_4c) + tmp_4d) + tmp_5z) + tmp_4e) + tmp_4f)
    + tmp_4g) + tmp_4h) - tmp_4i) - tmp_4j) - tmp_4k) + tmp_4l) + tmp_4m) +
    tmp_4n) - tmp_4o) - tmp_4p) + tmp_4q) + tmp_60 * PD_P.ArmConstants.Mass2 *
    tmp_8 * D14_tmp_0) + 8.0 * PD_U.InBus1_Velocities[6] *
    PD_P.ArmConstants.Hexa_to_joint_L * D14_tmp_e * D14_tmp_0) + tmp_4x) +
    tmp_4y) + tmp_4z) - tmp_50) + tmp_51) - tmp_52) - tmp_53) + tmp_1c *
    PD_P.ArmConstants.Inertia1[6] * D46_tmp_7) + tmp_55) - tmp_56) - tmp_57) +
    D46_tmp_i * -PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Mass2 * D24_tmp)
    + tmp_1o * D56_tmp_5) + tmp_1c * PD_P.ArmConstants.Inertia2[6] * D46_tmp_8)
    + tmp_59) - tmp_5a) - tmp_5b) + tmp_1s * D56_tmp_6) + tmp_63) + tmp_64) +
                    tmp_6 * D46_tmp_n) + tmp_7 * D46_tmp_n) + tmp_13 *
                  D48_tmp_tmp) + tmp_65) * 0.125);
  tmp_9 = D14_tmp_e * PD_P.ArmConstants.Hexa_to_joint_L;
  tmp_f = -PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[7];
  tmp_1[51] = -(tmp_f * PD_P.ArmConstants.Mass2 * tmp_8 - tmp_9 * D27_tmp_2);
  tmp_1[59] = -(-PD_P.ArmConstants.MC2 * PD_P.ArmConstants.Mass2 * tmp_8 * tmp_t);
  tmp_1t *= PD_P.ArmConstants.Hexa_to_joint_L;
  tmp_1t *= PD_P.ArmConstants.Mass1;
  tmp_1o = D16_tmp_1 * PD_P.ArmConstants.Hexa_to_joint_L;
  tmp_1o = tmp_1o * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_1s = tmp_1w * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  tmp_1w *= PD_P.ArmConstants.l1_dim;
  tmp_1w *= PD_P.ArmConstants.Mass2;
  D14_tmp_e = D16_tmp_1 * D46_tmp_tmp_3;
  tmp_5c = tmp_1c * PD_P.ArmConstants.Inertia2[3];
  tmp_3i = tmp_5c * D46_tmp_c;
  tmp_3j = 4.0 * PD_U.InBus1_Velocities[3];
  tmp_1c *= PD_P.ArmConstants.Inertia1[3];
  tmp_5j = tmp_3j * PD_P.ArmConstants.Inertia2[6];
  tmp_5k = 4.0 * PD_U.InBus1_Velocities[7];
  tmp_5l = 4.0 * PD_U.InBus1_Velocities[6];
  tmp_o = ((((tmp_o * 4.0 * PD_P.ArmConstants.Inertia1[6] * D15_tmp_0 + tmp_1c *
              D46_tmp_a) + tmp_5j * D15_tmp_1) + tmp_5l *
            PD_P.ArmConstants.Inertia2[6] * D15_tmp_1) + tmp_5k *
           PD_P.ArmConstants.Inertia2[6] * D15_tmp_1) + tmp_3i;
  tmp_2m = tmp_1u * D46_tmp_1;
  tmp_2n = tmp_1m * D56_tmp_7;
  tmp_2o = tmp_1n * D56_tmp_7;
  tmp_2p = D46_tmp_g * D56_tmp_7;
  tmp_2q = tmp_1v * D56_tmp_7;
  tmp_2r = tmp_1w * D17_tmp_5;
  tmp_2s = tmp_1x * D46_tmp_2;
  tmp_2t = tmp_1w * D35;
  tmp_2u = tmp_1p * D56_tmp_8;
  tmp_2v = tmp_1q * D56_tmp_8;
  tmp_2w = tmp_1r * D56_tmp_8;
  tmp_2x = D16_tmp_1 * PD_P.ArmConstants.Inertia1[8] * D15_tmp;
  tmp_2y = D16_tmp_1 * PD_P.ArmConstants.Inertia2[8] * D15_tmp;
  tmp_4u = D16_tmp_3 * PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Mass1;
  tmp_2z = tmp_4u * D15_tmp;
  tmp_4w = D14_tmp_i * PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Mass2;
  tmp_30 = tmp_4w * D15_tmp;
  tmp_31 = D16_tmp_1 * D46_tmp_i * PD_P.ArmConstants.Mass2;
  tmp_32 = tmp_31 * D15_tmp;
  tmp_4v = D14_tmp_e * PD_P.ArmConstants.Mass1;
  D14_tmp_e *= PD_P.ArmConstants.Mass2;
  tmp_1i = (((((((((((((((((((((((((((((((tmp_1j * D25 + tmp_o) - tmp_1k * D25)
    + tmp_1l * D25) + tmp_1i * D25) + tmp_1t * D14_tmp_tmp_0) + tmp_1o *
    D14_tmp_tmp_0) + tmp_2m) + tmp_1t * D16) + tmp_1o * D16) - tmp_2n) + tmp_2o)
    + tmp_2p) + tmp_2q) + tmp_2r) + tmp_1s * D17_tmp_2) + tmp_2s) + tmp_1s * D34)
    + tmp_2t) - tmp_2u) + tmp_2v) + tmp_2w) + tmp_2x) + tmp_2y) + D16_tmp_1 *
                   PD_P.HexaConstants.Inertia[0] * D15_tmp) + tmp_2z) + tmp_4v *
                 D15_tmp) + tmp_30) + D14_tmp_e * D15_tmp) + tmp_32) + tmp_1j *
             D17) - tmp_1k * D17) + tmp_1l * D17;
  tmp_i = _mm_set1_pd(PD_U.InBus1_Velocities[5]);
  tmp_j = _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set_pd(2.0,
    PD_P.ArmConstants.Hexa_to_joint_L), _mm_set_pd(PD_P.ArmConstants.MC1,
    PD_P.ArmConstants.Hexa_to_joint_L)), tmp_i), _mm_set_pd
    (PD_P.ArmConstants.Hexa_to_joint_L, PD_P.ArmConstants.Mass2)), _mm_set_pd
                     (PD_P.ArmConstants.Mass1, D17));
  _mm_storeu_pd(&tmp_h[0], tmp_j);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  tmp_1j = tmp_h[0];
  tmp_1k = tmp_h[1];
  tmp_1l = -4.0 * PD_U.InBus1_Velocities[3];
  tmp_1m *= D56_tmp_9;
  tmp_1n *= D56_tmp_9;
  D46_tmp_g *= D56_tmp_9;
  tmp_33 = tmp_1v * D56_tmp_9;
  tmp_34 = tmp_1w * D37;
  tmp_35 = tmp_1y * D46_tmp_4;
  tmp_36 = tmp_1w * D46;
  tmp_1p *= D56_tmp_a;
  tmp_1q *= D56_tmp_a;
  tmp_1r *= D56_tmp_a;
  tmp_37 = tmp_1l * PD_P.ArmConstants.Inertia1[7] * D34_tmp;
  tmp_38 = tmp_0 * PD_P.ArmConstants.Inertia1[7] * D34_tmp;
  tmp_18 *= D46_tmp_y;
  tmp_19 *= D46_tmp_y;
  tmp_1a *= D46_tmp_y;
  tmp_1b *= D46_tmp_y;
  tmp_39 = tmp_1l * PD_P.ArmConstants.Inertia2[7] * D34_tmp_0;
  tmp_3a = tmp_0 * PD_P.ArmConstants.Inertia2[7] * D34_tmp_0;
  tmp_3b = D16_tmp_0 * PD_P.ArmConstants.Inertia2[7] * D34_tmp_0;
  tmp_1e *= D46_tmp_p;
  tmp_c *= D46_tmp_p;
  tmp_d *= D46_tmp_p;
  tmp_11 *= D48;
  tmp_3c = tmp_1z * D46_tmp_5;
  tmp_3d = tmp_17 * D56_tmp_1;
  tmp_3e = tmp_20 * D46_tmp_6;
  tmp_3f = tmp_1d * D56_tmp_2;
  tmp_3g = tmp_21 * D46_tmp_7;
  tmp_17 *= D56_tmp_5;
  tmp_3h = tmp_22 * D46_tmp_8;
  tmp_1d *= D56_tmp_6;
  tmp_1[28] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_1i + tmp_1j) +
    tmp_1k * D18) + tmp_1o * D18) + tmp_5 * D46_tmp_3) + tmp_1t * D24) + tmp_1o *
    D24) - tmp_1m) + tmp_1n) + D46_tmp_g) + tmp_33) + tmp_34) + tmp_1s * D38) +
    tmp_35) + tmp_1s * D45) + tmp_36) - tmp_1p) + tmp_1q) + tmp_1r) + tmp_14 *
    D14) + tmp_15 * D14) + tmp_16 * D14) + tmp_y * D14) + tmp_37) + tmp_38) +
    tmp_18) + tmp_19) + tmp_1a) + tmp_1b) + tmp_10 * D15) + tmp_3v * D15) +
    tmp_39) + tmp_3a) + tmp_3b) + tmp_1e) + tmp_c) + tmp_d) + tmp_12 * D47) +
    tmp_11) + tmp_3c) + tmp_3d) + tmp_3e) + tmp_3f) + tmp_3g) + tmp_17) + tmp_3h)
                 + tmp_1d) * 0.25);
  tmp_y = ginv_tmp_6 * D46_tmp_a + D46_tmp_x * D46_tmp_c;
  tmp_10 = D46_tmp_tmp_e * D48;
  tmp_3v = 2.0 * PD_U.InBus1_Velocities[7];
  tmp_12 = -PD_P.ArmConstants.MC1 * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass1;
  tmp_14 = w_a_tmp * D14_tmp;
  tmp_15 = D67_tmp * D15;
  tmp_16 = D47_tmp_tmp_tmp * D14_tmp_5;
  tmp_1i = D47_tmp_tmp_tmp * D47;
  tmp_1j = (D47_tmp_tmp_tmp * D14_tmp_2 + D48_tmp * D15_tmp_0) + (D46_tmp_e +
    ginv_tmp_4) * D15_tmp_1;
  tmp_1[36] = -((((((((((((((((((tmp_y - D14_tmp_j) + D16_tmp) - D17_tmp_tmp) -
    D17_tmp_tmp_2) + D27_tmp_0) - D14_tmp_3) - tmp_u) - tmp_v) + D46_tmp_10 *
    D15) + D46_tmp_11 * D15) + tmp_w) - D14_tmp_7) - D14_tmp_a) + D46_tmp_12 *
                    D47) + tmp_10) * PD_U.InBus1_Velocities[3] + (-2.0 *
    PD_U.InBus1_Velocities[7] * tmp_1j * D34_tmp_0 + tmp_3v *
    PD_P.ArmConstants.Inertia2[3] * D46_tmp_c)) +
                 (((((((((((((-PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D14_tmp + (tmp_y -
    tmp_14)) + D27_tmp_0) - D14_tmp_3) - tmp_u) - tmp_v) + tmp_12 * D15) -
                        tmp_15) - tmp_16) + tmp_w) - D14_tmp_7) - D14_tmp_a) -
                   tmp_1i) + tmp_10) * PD_U.InBus1_Velocities[6]) * 0.5);
  D14_tmp_j = D47_tmp_5 * D14_tmp_tmp_0;
  D56_tmp_tmp_2 = (D14_tmp_j + D56_tmp_tmp_2) + w_a_tmp * D16;
  D16_tmp = D67_tmp * D16;
  D56_tmp_tmp_2 += D16_tmp;
  D56_tmp_tmp_4 = D56_tmp_tmp_2 - D56_tmp_tmp_4;
  D16_tmp = 4.0 * PD_P.ArmConstants.Inertia1[6];
  D17_tmp_tmp = 4.0 * PD_P.ArmConstants.Inertia2[6];
  D17_tmp_tmp_2 = -4.0 * PD_P.ArmConstants.Inertia1[7];
  tmp_y = -4.0 * PD_P.ArmConstants.Inertia2[7];
  D56_tmp_tmp_1 = (((((((((((((((((((D16_tmp * D46_tmp_q + D17_tmp_tmp *
    D48_tmp_0) + ginv_tmp_6 * D46_tmp_tmp_2) + D46_tmp_x * D46_tmp_tmp_1) +
    D56_tmp_f * D46_tmp_tmp_0) + D56_tmp_g * D46_tmp_tmp) + D16_tmp *
    D46_tmp_tmp_7) + D17_tmp_tmp * D46_tmp_tmp_6) + D46_tmp_tmp_e *
    D46_tmp_tmp_8) + D46_tmp_10 * D46_tmp_tmp_9) + D46_tmp_11 * D46_tmp_tmp_9) +
    D17_tmp_tmp_2 * D46_tmp_tmp_a) + D46_tmp_10 * D56) + D46_tmp_11 * D56) +
                        D46_tmp_tmp_e * D56_tmp_tmp_9) + D46_tmp_12 *
                       D56_tmp_tmp_6) + tmp_y * D46_tmp_tmp_b) + D46_tmp_12 *
                     D56_tmp_tmp_3) + PD_P.HexaConstants.Inertia[8] *
                    D56_tmp_tmp_1) + PD_P.ArmConstants.Inertia1[0] * D57) -
    PD_P.ArmConstants.Inertia1[4] * D57;
  D16_tmp = D47_tmp_0 * D57;
  D17_tmp_tmp = -D46_tmp_h;
  tmp_10 = D47_tmp_tmp_tmp * D17_tmp_2;
  tmp_1k = D47_tmp_tmp_tmp * D34;
  D46_tmp_h = D47_tmp_tmp_tmp * D38;
  D47_tmp_5 = D47_tmp_tmp_tmp * D45;
  tmp_3k = w_a_tmp * D18;
  tmp_3l = D67_tmp * D18;
  tmp_3m = D48_tmp * D17_tmp_5 + tmp_10;
  tmp_3n = D48_tmp * D37;
  tmp_61 = w_a_tmp * D24;
  tmp_62 = D67_tmp * D24;
  D56_tmp_tmp_4 = ((((((((((((((((((((((((((((((((((((((((D56_tmp_tmp_4 +
    D56_tmp_tmp_8) + D56_tmp_tmp_5) + ginv_tmp_tmp) + D14_tmp_h) + tmp_10) +
    tmp_p) + tmp_1k) + D14_tmp_d) - D14_tmp_tmp_1) + D14_tmp_tmp_2) + D14_tmp_f)
    + D15_tmp_tmp_1) + D15_tmp_tmp_2) + D34_tmp_3) + D46_tmp_tmp_5) + ginv_tmp_5)
    + tmp_3k) + tmp_3l) + tmp_23) + tmp_61) + tmp_62) - tmp_24) + tmp_25) +
    tmp_26) + tmp_27) + tmp_28) + D46_tmp_h) + tmp_29) + D47_tmp_5) + tmp_2a) -
    tmp_2b) + tmp_2c) + tmp_2d) + D56_tmp_n) + tmp_2e) + tmp_2f) + tmp_2g) +
                     tmp_2h) + tmp_2i) + tmp_2j) + tmp_2k;
  tmp_66 = (((((((((((((((((((tmp_3m + tmp_p) + tmp_1k) + D48_tmp * D35) -
    D14_tmp_tmp_1) + D14_tmp_tmp_2) + D14_tmp_f) + D15_tmp_tmp_2) +
                       D46_tmp_tmp_5) + tmp_3n) + D46_tmp_h) + tmp_29) +
                   D47_tmp_5) + D48_tmp * D46) - tmp_2b) + tmp_2c) + tmp_2d) +
              tmp_2f) + tmp_2g) + tmp_2j) + tmp_2k;
  tmp_1[44] = -(((((((((((((((((((((((((((((((((((((((((((((D56_tmp_tmp_1 -
    D16_tmp) - D47_tmp_1 * D57) + PD_P.ArmConstants.Inertia2[0] * D45_tmp) -
    PD_P.ArmConstants.Inertia2[4] * D45_tmp) + D17_tmp_tmp *
    PD_P.ArmConstants.Mass2 * D45_tmp) + -2.0 * PD_P.ArmConstants.Inertia1[0] *
    D46_tmp_u) + -2.0 * PD_P.ArmConstants.Inertia1[4] * D46_tmp_u) + 4.0 *
    PD_P.ArmConstants.Inertia1[8] * D46_tmp_u) + -2.0 *
    PD_P.ArmConstants.Inertia2[0] * D46_tmp_u) + -2.0 *
    PD_P.ArmConstants.Inertia2[4] * D46_tmp_u) + 4.0 *
    PD_P.ArmConstants.Inertia2[8] * D46_tmp_u) + 4.0 *
    PD_P.HexaConstants.Inertia[0] * D46_tmp_u) + -2.0 *
    PD_P.HexaConstants.Inertia[4] * D46_tmp_u) + -2.0 *
    PD_P.HexaConstants.Inertia[8] * D46_tmp_u) + D16_tmp_tmp * D46_tmp_u) +
    tmp_2l * D46_tmp_u) + D37_tmp * D46_tmp_u) + tmp_r * D46_tmp_u) +
    ginv_tmp_tmp_2 * D46_tmp_u) + PD_P.HexaConstants.Inertia[4] * w_a) +
    D56_tmp_h * w_a) + D56_tmp_i * w_a) + PD_P.HexaConstants.Inertia[4] * x_a) -
    PD_P.HexaConstants.Inertia[8] * x_a) + D56_tmp_h * x_a) + D56_tmp_i * x_a) -
    PD_P.ArmConstants.Inertia1[0] * D24_tmp) + PD_P.ArmConstants.Inertia1[4] *
    D24_tmp) + D47_tmp_0 * D24_tmp) + D47_tmp_1 * D24_tmp) -
    PD_P.ArmConstants.Inertia2[0] * D24_tmp_0) + PD_P.ArmConstants.Inertia2[4] *
    D24_tmp_0) + D46_tmp_e * D24_tmp_0) + D46_tmp_k * D47_tmp_4) + D46_tmp_l *
    D47_tmp_4) + D17_tmp_tmp_2 * D15_tmp_tmp) + D46_tmp_j * D56_tmp_tmp_0) +
                       D46_tmp_m * D14_tmp_tmp) + tmp_y * D15_tmp_tmp_0) +
                     D46_tmp_k * D46_tmp_n) + D46_tmp_l * D46_tmp_n) + D46_tmp_m
                   * D48_tmp_tmp) + D46_tmp_j * D56_tmp_tmp) * (-0.5 *
    PD_U.InBus1_Velocities[5]) + ((D56_tmp_tmp_4 * PD_U.InBus1_Velocities[6] +
    tmp_66 * PD_U.InBus1_Velocities[7]) + tmp_n * PD_U.InBus1_Velocities[3])) *
                0.25);
  D56_tmp_tmp_1 = PD_P.ArmConstants.MC1 * PD_U.InBus1_Velocities[5];
  D56_tmp_tmp_1 = D56_tmp_tmp_1 * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass1;
  tmp_n = PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Hexa_to_joint_L;
  tmp_n *= PD_P.ArmConstants.l1_dim;
  tmp_n *= PD_P.ArmConstants.Mass2;
  tmp_r = PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[5];
  D16_tmp = tmp_r * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  D17_tmp_tmp = D16_tmp * D17_tmp_2;
  D17_tmp_tmp_2 = D16_tmp * D34;
  tmp_o = (((((((((((((((((((D56_tmp_tmp_1 * D14_tmp_tmp_0 + tmp_o) + tmp_n *
    D14_tmp_tmp_0) + tmp_2m) + D56_tmp_tmp_1 * D16) + tmp_n * D16) - tmp_2n) +
                       tmp_2o) + tmp_2p) + tmp_2q) + tmp_2r) + D17_tmp_tmp) +
                  tmp_2s) + D17_tmp_tmp_2) + tmp_2t) - tmp_2u) + tmp_2v) +
             tmp_2w) + tmp_2x) + tmp_2y) + tmp_2z;
  tmp_i = _mm_mul_pd(_mm_set_pd(PD_P.ArmConstants.MC1, -2.0), tmp_i);
  _mm_storeu_pd(&tmp_h[0], tmp_i);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  D16_tmp_tmp = tmp_h[0];
  D37_tmp = tmp_h[1];
  ginv_tmp_tmp_2 = PD_P.ArmConstants.Hexa_to_joint_L;
  tmp_2l = D46_tmp_z * PD_U.InBus1_Velocities[4] *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1;
  tmp_y = tmp_x * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.l1_dim *
    PD_P.ArmConstants.Mass2;
  tmp_2m = D46_tmp_f * PD_U.InBus1_Velocities[4];
  tmp_2n = tmp_2m * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  tmp_2o = D16_tmp * D38;
  tmp_2p = D16_tmp * D45;
  tmp_2q = tmp_2n * D14_tmp_5;
  tmp_2r = tmp_2n * D47;
  tmp_1[52] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_o + tmp_30) +
    tmp_32) + D56_tmp_tmp_1 * D18) + tmp_n * D18) + D16_tmp_tmp *
    PD_P.ArmConstants.Inertia1[7] * D46_tmp_3) + D37_tmp * ginv_tmp_tmp_2 *
    PD_P.ArmConstants.Mass1 * D24) + tmp_n * D24) - tmp_1m) + tmp_1n) +
    D46_tmp_g) + tmp_33) + tmp_34) + tmp_2o) + tmp_35) + tmp_2p) + tmp_36) -
    tmp_1p) + tmp_1q) + tmp_1r) + tmp_2l * D14_tmp) + tmp_y * D14_tmp) + tmp_37)
    + tmp_38) + tmp_18) + tmp_19) + tmp_1a) + tmp_1b) + tmp_2l * D15) + tmp_y *
    D15) + tmp_2q) + tmp_39) + tmp_3a) + tmp_3b) + tmp_1e) + tmp_c) + tmp_d) +
    tmp_2r) + tmp_11) + tmp_3c) + tmp_3d) + tmp_3e) + tmp_3f) + tmp_3g) + tmp_17)
                  + tmp_3h) + tmp_1d) * 0.25);
  tmp_o = tmp_r * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_r = tmp_2m * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_1[60] = -((((((((((((((((((((((((((((((((((tmp_s * 4.0 *
    PD_P.ArmConstants.Inertia2[6] * D15_tmp_1 + tmp_3i) + tmp_o * D17_tmp_5) +
    D17_tmp_tmp) + tmp_2s) + D17_tmp_tmp_2) + tmp_o * D35) - tmp_2u) + tmp_2v) +
    tmp_2w) + tmp_2y) + tmp_30) + tmp_o * D37) + tmp_2o) + tmp_35) + tmp_2p) +
    tmp_o * D46) - tmp_1p) + tmp_1q) + tmp_1r) + tmp_r * D14_tmp_4) + tmp_2q) +
    tmp_39) + tmp_3a) + tmp_3b) + tmp_1e) + tmp_c) + tmp_d) + tmp_2r) + tmp_r *
                     D48) + tmp_3e) + tmp_3f) + tmp_3h) + tmp_1d) * 0.25);
  D17_tmp_tmp = PD_P.ArmConstants.Inertia2[7] * D46_tmp_2;
  D17_tmp_tmp_2 = PD_P.ArmConstants.Inertia2[7] * D46_tmp_4;
  tmp_s = PD_P.ArmConstants.Inertia2[6] * D46_tmp_6;
  D16_tmp_tmp = PD_P.ArmConstants.Inertia2[6] * D46_tmp_8;
  D37_tmp = D56_tmp_g * D46_tmp_p;
  ginv_tmp_tmp_2 = D46_tmp_tmp_e * D46_tmp_tmp_4;
  tmp_11 = D56_tmp_f * D46_tmp_y;
  tmp_17 = PD_P.ArmConstants.Inertia2[0] * D56_tmp_6;
  tmp_18 = (tmp_3m + D17_tmp_tmp) - tmp_3n;
  D14_tmp_j = (((((((((((PD_P.ArmConstants.Inertia1[7] * D46_tmp_1 + D14_tmp_j)
                        + tmp_10) + D17_tmp_tmp) - tmp_3k) - tmp_3l) +
                    PD_P.ArmConstants.Inertia1[7] * D46_tmp_3) - D46_tmp_h) +
                  D17_tmp_tmp_2) + PD_P.ArmConstants.Inertia1[6] * D46_tmp_5) +
                tmp_s) + PD_P.ArmConstants.Inertia1[6] * D46_tmp_7) +
    D16_tmp_tmp;
  tmp_1[29] = -(((((((((((((((((((((D47_tmp_2 - tmp_m * D46_tmp_9) + D46_tmp_v)
    + PD_P.ArmConstants.Inertia1[0] * D46_tmp_a) - ginv_tmp_7) - ginv_tmp_8) -
    ginv_tmp_9) + D46_tmp_10 * D46_tmp_b) + D46_tmp_11 * D46_tmp_b) + D47_tmp_3)
    + D46_tmp_w) + ginv_tmp_a) - ginv_tmp_b) - ginv_tmp_c) + D46_tmp_12 *
                       D46_tmp_r) + ginv_tmp_tmp_2) + tmp_11) + D37_tmp) * tmp_x
                   + D45_tmp_1 * tmp_3j) + (((D56_tmp - tmp_17) + D56_tmp_r) +
    D56_tmp_s) * PD_U.InBus1_Velocities[5]) * D15_tmp +
                 (((((-PD_P.ArmConstants.MC2 * PD_P.ArmConstants.Hexa_to_joint_L
                      * PD_P.ArmConstants.Mass2 * D38 + tmp_18) + D17_tmp_tmp_2)
                    + tmp_s) + D16_tmp_tmp) * tmp_3v + D14_tmp_j * D16_tmp_2)) *
                0.25);
  tmp_m = 2.0 * PD_U.InBus1_Velocities[3];
  D16_tmp_2 = tmp_m * D46_tmp_tmp_3;
  D17_tmp_tmp = tmp_m * PD_P.HexaConstants.Inertia[4];
  tmp_3v = tmp_3p * PD_P.HexaConstants.Inertia[8];
  tmp_19 = D16_tmp_2 * PD_P.ArmConstants.Mass1;
  D16_tmp_2 *= PD_P.ArmConstants.Mass2;
  tmp_1g = tmp_1g * PD_U.InBus1_Velocities[3] *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1;
  tmp_1a = tmp_1l * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.l1_dim
    * PD_P.ArmConstants.Mass2;
  tmp_1b = tmp * PD_P.ArmConstants.Inertia1[6];
  tmp_1d = tmp * PD_P.ArmConstants.Inertia2[6];
  tmp_1e = tmp_1g * D14_tmp_tmp_0;
  tmp_c = tmp_1a * D14_tmp_tmp_0;
  tmp_3o = (((((((((((tmp_1b * D46_tmp_q + tmp_1d * D48_tmp_0) + D17_tmp_tmp *
                     D25) + tmp_3o) + tmp_3v * D25) + tmp_3q) + tmp_19 * D25) +
                tmp_3r) + D16_tmp_2 * D25) + tmp_3s) + tmp_1e) + tmp_c) + tmp_3t;
  tmp_3q = 4.0 * PD_P.ArmConstants.MC1;
  tmp_3r = tmp_3q * PD_U.InBus1_Velocities[3] *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1;
  tmp_3s = tmp_3j * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.l1_dim;
  tmp_3t = PD_P.ArmConstants.Mass2;
  tmp_1h *= PD_U.InBus1_Velocities[3];
  tmp_d = 4.0 * PD_P.ArmConstants.MC2;
  tmp_1m = tmp_d * PD_U.InBus1_Velocities[3];
  tmp_1n = tmp_1l * D46_tmp_tmp_3;
  D46_tmp_g = tmp_q * D46_tmp_tmp_3;
  tmp_1p = D16_tmp_3 * PD_U.InBus1_Velocities[3] * PD_P.ArmConstants.Mass1;
  tmp_1q = tmp_m * D46_tmp_i * PD_P.ArmConstants.Mass2;
  tmp_1r = tmp_1h * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_1h = tmp_1h * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  tmp_3i = tmp_1m * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  tmp_1m = tmp_1m * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  tmp_2m = tmp_3p * PD_P.ArmConstants.Inertia2[0];
  tmp_2o = tmp_m * PD_P.ArmConstants.Inertia2[4];
  tmp_2p = D14_tmp_i * PD_U.InBus1_Velocities[3] * PD_P.ArmConstants.Mass2;
  tmp_3s *= tmp_3t;
  tmp_3t = D27_tmp_1 * PD_P.ArmConstants.Inertia1[3];
  tmp_1g *= D18;
  tmp_1a *= D18;
  D46_tmp_tmp_0 *= tmp_3t;
  tmp_2q = tmp_1h * D17_tmp_2;
  tmp_2r = tmp_1r * D17_tmp_5;
  tmp_m = ((((((((((((((((((((((((((((((((((((((((((((((((tmp_3o + tmp_3u) +
    tmp_3r * D16) + tmp_3w) + tmp_3s * D16) + tmp_3x) + tmp_3p *
    PD_P.ArmConstants.Inertia1[0] * D56_tmp_7) + tmp_3y) + tmp_m *
    PD_P.ArmConstants.Inertia1[4] * D56_tmp_7) + tmp_3z) + tmp_1p * D56_tmp_7) +
    tmp_40) + tmp_1q * D56_tmp_7) + tmp_41) + tmp_2r) + tmp_2q) + tmp_42) +
    tmp_43) + tmp_3i * D34) + tmp_44) + tmp_1m * D35) + tmp_a) + tmp_2m *
    D56_tmp_8) + tmp_b) + tmp_2o * D56_tmp_8) + tmp_45) + tmp_2p * D56_tmp_8) +
    tmp_46) + tmp_1l * PD_P.ArmConstants.Inertia1[8] * D15_tmp) + tmp_1l *
    PD_P.ArmConstants.Inertia2[8] * D15_tmp) + tmp_1l *
    PD_P.HexaConstants.Inertia[0] * D15_tmp) + tmp_g * PD_U.InBus1_Velocities[3]
    * PD_P.ArmConstants.Mass1 * D15_tmp) + tmp_1n * PD_P.ArmConstants.Mass1 *
    D15_tmp) + tmp_47 * PD_U.InBus1_Velocities[3] * PD_P.ArmConstants.Mass2 *
    D15_tmp) + tmp_1n * PD_P.ArmConstants.Mass2 * D15_tmp) + tmp_1l * D46_tmp_i *
                        PD_P.ArmConstants.Mass2 * D15_tmp) + D17_tmp_tmp * D17)
                      + tmp_q * PD_P.HexaConstants.Inertia[4] * D17) + tmp_3v *
                     D17) + tmp_x * PD_P.HexaConstants.Inertia[8] * D17) +
                   tmp_19 * D17) + D46_tmp_g * PD_P.ArmConstants.Mass1 * D17) +
                 D16_tmp_2 * D17) + D46_tmp_g * PD_P.ArmConstants.Mass2 * D17) +
               tmp_1g) + tmp_1a) + tmp_48 * D46_tmp_3) + D46_tmp_tmp_0) + tmp_3r
           * D24) + tmp_3q * PD_U.InBus1_Velocities[4] *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1 * D24;
  tmp_i = _mm_set1_pd(PD_P.ArmConstants.Hexa_to_joint_L);
  tmp_j = _mm_set1_pd(PD_P.ArmConstants.Mass2);
  tmp_k = _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(4.0),
    _mm_loadu_pd(&PD_U.InBus1_Velocities[3])), tmp_i), _mm_set1_pd
    (PD_P.ArmConstants.l1_dim)), tmp_j), _mm_set1_pd(D24));
  _mm_storeu_pd(&tmp_h[0], tmp_k);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  D16_tmp_2 = tmp_h[0];
  D17_tmp_tmp = tmp_h[1];
  tmp_k = _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(-2.0), _mm_loadu_pd
    (&PD_U.InBus1_Velocities[3])), _mm_set1_pd(PD_P.ArmConstants.Inertia1[0]));
  _mm_storeu_pd(&tmp_h[0], tmp_k);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_3p = tmp_h[0];
  tmp_3v = tmp_h[1];
  tmp_k = _mm_set1_pd(2.0);

  /* Inport generated from: '<Root>/InBus1_Inport_2' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function1'
   */
  tmp_l = _mm_mul_pd(tmp_k, _mm_loadu_pd(&PD_U.InBus1_Velocities[3]));
  _mm_storeu_pd(&tmp_h[0], tmp_l);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  tmp_19 = tmp_h[0];
  tmp_3o = tmp_h[1];
  tmp_48 = tmp_d * PD_U.InBus1_Velocities[4];
  tmp_3w = D47_tmp_tmp_tmp * D46_tmp_r;
  tmp_3x = tmp_3j * PD_P.ArmConstants.Inertia1[3];
  tmp_3y = tmp_4b * PD_P.ArmConstants.Inertia1[7];
  tmp_3z = tmp_4b * PD_P.ArmConstants.Inertia2[7];
  tmp_40 = PD_P.ArmConstants.Inertia1[0] - PD_P.ArmConstants.Inertia1[4];
  D16_tmp_3 = D16_tmp_3 * PD_U.InBus1_Velocities[4] * PD_P.ArmConstants.Mass1;
  tmp_41 = tmp_q * D46_tmp_i * PD_P.ArmConstants.Mass2;
  tmp_42 = tmp_x * PD_P.ArmConstants.Inertia2[0];
  tmp_44 = tmp_q * PD_P.ArmConstants.Inertia2[4];
  D14_tmp_i = D14_tmp_i * PD_U.InBus1_Velocities[4] * PD_P.ArmConstants.Mass2;
  tmp_a = D16_tmp_3 * D56_tmp_9;
  tmp_b = tmp_41 * D56_tmp_9;
  tmp_1h *= D38;
  tmp_g = D27_tmp_1 * PD_P.ArmConstants.Inertia2[3];
  D46_tmp_tmp *= tmp_g;
  tmp_45 = tmp_48 * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D46;
  tmp_46 = tmp_42 * D56_tmp_a;
  tmp_47 = tmp_44 * D56_tmp_a;
  tmp_1l = D14_tmp_i * D56_tmp_a;
  tmp_1n = tmp_1r * D37;
  tmp_0 = (((((((((((((((((((((((((((((((((((((((((((((((((tmp_m + D16_tmp_2) +
    D17_tmp_tmp) + tmp_3p * D56_tmp_9) + tmp_3v * D56_tmp_9) + tmp_19 *
    PD_P.ArmConstants.Inertia1[4] * D56_tmp_9) + tmp_3o *
    PD_P.ArmConstants.Inertia1[4] * D56_tmp_9) + tmp_1p * D56_tmp_9) + tmp_a) +
    tmp_1q * D56_tmp_9) + tmp_b) + tmp_1n) + tmp_1h) + tmp_49 * D46_tmp_4) +
    D46_tmp_tmp) + tmp_3i * D45) + tmp_48 * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass2 * D45) + tmp_1m * D46) + tmp_45) + tmp_2m *
    D56_tmp_a) + tmp_46) + tmp_2o * D56_tmp_a) + tmp_47) + tmp_2p * D56_tmp_a) +
    tmp_1l) + tmp_1b * D46_tmp_tmp_7) + tmp_1d * D46_tmp_tmp_6) +
    ((((((D48_tmp_1 + ginv_tmp_a) - ginv_tmp_b) - ginv_tmp_c) - tmp_3w) -
    D48_tmp * D46_tmp_tmp_4) + D37_tmp) * (D16_tmp_0 * D15_tmp)) +
    ((((((((((((((tmp_40 - D47_tmp_0) - D47_tmp_1) * D46_tmp_a + D47_tmp_6) +
    tmp_12 * D46_tmp_b) - D67_tmp * D46_tmp_b) + D47_tmp_3) + D47_tmp) +
    ginv_tmp_a) - ginv_tmp_b) - ginv_tmp_c) - tmp_3w) + ginv_tmp_tmp_2) + tmp_11)
    + D37_tmp) * (tmp_0 * D15_tmp)) + tmp_4a) + tmp_6 * D46_tmp_tmp_9) + tmp_7 *
    D46_tmp_tmp_9) + tmp_3y * D46_tmp_tmp_a) + tmp_4c) + tmp_4d) + tmp_1f *
    D56_tmp_tmp_9) + tmp_13 * D56_tmp_tmp_6) + tmp_3z * D46_tmp_tmp_b) + tmp_4e)
                     + tmp_4f) + tmp_4g) + tmp_4h) - tmp_4i) - tmp_4j) - tmp_4k)
               + tmp_3x * D56_tmp_1) + tmp_4l) + tmp_4m) + tmp_4n) - tmp_4o) -
    tmp_4p;
  tmp_m = tmp_3j * PD_P.ArmConstants.Inertia2[3];
  D16_tmp_0 = tmp_m * D56_tmp_2;
  D16_tmp_2 = D27_tmp_1 * PD_P.ArmConstants.Inertia1[0];
  D17_tmp_tmp = D27_tmp_1 * PD_P.ArmConstants.Inertia2[0];
  tmp_3p = tmp_1v * D24_tmp;
  D37_tmp = tmp_1c * D56_tmp_5;
  ginv_tmp_tmp_2 = tmp_5c * D56_tmp_6;
  tmp_3v = tmp_1w * D56_tmp_tmp;
  tmp_1[37] = -(((((((((((((((((((((((((((((((((((((((((((((((tmp_0 + D16_tmp_0)
    + tmp_4q) + D16_tmp_2 * D46_tmp_u) + tmp_4r * D46_tmp_u) + tmp *
    PD_P.ArmConstants.Inertia1[8] * D46_tmp_u) + D17_tmp_tmp * D46_tmp_u) +
    tmp_4s * D46_tmp_u) + tmp * PD_P.ArmConstants.Inertia2[8] * D46_tmp_u) + tmp
    * PD_P.HexaConstants.Inertia[0] * D46_tmp_u) + tmp_4t * D46_tmp_u) +
    D27_tmp_1 * PD_P.HexaConstants.Inertia[8] * D46_tmp_u) + tmp_4u * D46_tmp_u)
    + tmp_4v * D46_tmp_u) + tmp_4w * D46_tmp_u) + D14_tmp_e * D46_tmp_u) +
    tmp_31 * D46_tmp_u) + tmp_4x) + tmp_4y) + tmp_4z) + tmp_50) - tmp_51) +
    tmp_52) + tmp_53) + tmp_54 * D46_tmp_7) - tmp_55) + tmp_56) + tmp_57) +
    tmp_3p) + tmp_3x * D56_tmp_5) + D37_tmp) + tmp_58 * D46_tmp_8) - tmp_59) +
    tmp_5a) + tmp_5b) + tmp_m * D56_tmp_6) + ginv_tmp_tmp_2) + tmp_1t *
    D47_tmp_4) + tmp_1o * D47_tmp_4) + tmp_3y * D15_tmp_tmp) + tmp_1w *
                       D56_tmp_tmp_0) + tmp_1s * D14_tmp_tmp) + tmp_3z *
                     D15_tmp_tmp_0) + tmp_1t * D46_tmp_n) + tmp_1o * D46_tmp_n)
                  + tmp_1s * D48_tmp_tmp) + tmp_3v) * 0.125);
  tmp_k = _mm_mul_pd(tmp_k, _mm_set_pd(PD_P.ArmConstants.Inertia1[3],
    PD_P.ArmConstants.Inertia1[6]));
  _mm_storeu_pd(&tmp_h[0], tmp_k);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  tmp = tmp_h[0];
  tmp_0 = tmp_h[1];
  tmp_m = ginv_tmp_tmp_1 * ginv_tmp_tmp_0;
  ginv_tmp_tmp_0 = -2.0 * ginv_tmp_tmp_0 * D14_tmp_1;
  D16_tmp_0 = PD_P.ArmConstants.MC1 * D15_tmp_0 + D24_tmp_2;
  D27_tmp_1 = PD_P.ArmConstants.Hexa_to_joint_L * D14_tmp_1;
  tmp_11 = -2.0 * PD_P.ArmConstants.Mass1;
  tmp_12 = -2.0 * PD_P.ArmConstants.Mass2;
  tmp_19 = 4.0 * D14_tmp_2;
  tmp_1b = ((PD_P.ArmConstants.l1_dim * D34_tmp + D27_tmp_1) +
            PD_P.ArmConstants.MC2 * D34_tmp_0) * s - D24_tmp_3 * smax *
    D14_tmp_0;
  tmp_1d = 4.0 * PD_P.ArmConstants.Mass2;
  tmp_3o = ginv_tmp * -2.0;
  tmp_48 = ginv_tmp_6 * D56_tmp_tmp_tmp + tmp_40 * D46_tmp;
  tmp_3w = tmp_19 * D17_tmp_3 * D14_tmp_1 * (ginv_tmp_tmp_4 + ginv_tmp_tmp_5);
  tmp_3x = (ginv_tmp_tmp_3 * 2.0 * D46_tmp_s + 4.0 * PD_P.ArmConstants.Inertia2
            [3] * D46_tmp_0) * ginv_tmp_k;
  tmp_3y = (ginv_tmp_4 * 2.0 * D46_tmp_s + -4.0 * PD_P.ArmConstants.Inertia2[3] *
            D46_tmp_0) * ginv_tmp_l;
  tmp_3z = tmp_1b * tmp_1d;
  D27_tmp_1 = (PD_P.ArmConstants.MC1 * D34_tmp + D27_tmp_1) * s;
  tmp_49 = ginv_tmp_f * D14_tmp_g * D46_tmp_u;
  tmp_4r = ginv_tmp_g * tmp_5d * D46_tmp_u;
  tmp_1[45] = -((((((((((((((((((((tmp_40 * D14_tmp_6 * D14_tmp +
    PD_P.ArmConstants.Inertia1[3] * D56_tmp_tmp_tmp) * (tmp_19 * D15_tmp *
    D14_tmp_1) * D14_tmp_0 + (((tmp_m * ginv_tmp_d + ginv_tmp_tmp_0 * ginv_tmp_e)
    + tmp_m * ginv_tmp_f) + ginv_tmp_tmp_0 * ginv_tmp_g)) + ((D56_tmp_f *
    D14_tmp_6 * D14_tmp + ginv_tmp_h) + ginv_tmp_i) * (tmp_3o * D15_tmp) *
    D14_tmp_0) + -2.0 * D15_tmp * ginv_tmp_2 * ginv_tmp_0 * D14_tmp_0) -
    ginv_tmp * D15_tmp * ginv_tmp_1 * D14_tmp_0) - ginv_tmp_2 * D15_tmp *
    ginv_tmp_3 * D14_tmp_0) + ginv_tmp_tmp_1 * D15_tmp * D14_tmp_1 * (D46_tmp_x *
    D46_tmp_0 + ginv_tmp_tmp_3 * D46_tmp_s) * D14_tmp_0) + D16_tmp_0 * tmp_11 *
    D15_tmp * smax * (D27_tmp_1 - D16_tmp_0 * smax * D14_tmp_0)) + D24_tmp_3 *
    tmp_12 * D15_tmp * smax * tmp_1b) + tmp_11 * s * D16_tmp_0 * D15_tmp *
    D45_tmp_0) + tmp_12 * s * D24_tmp_3 * D15_tmp * D24_tmp_1) +
                        PD_P.ArmConstants.Inertia1[8] * D46_tmp_u) +
                       PD_P.ArmConstants.Inertia2[8] * D46_tmp_u) +
                      PD_P.HexaConstants.Inertia[0] * D46_tmp_u) - ginv_tmp_j *
                     D46_tmp_u) - ginv_tmp_2 * PD_P.HexaConstants.Inertia[4] *
                    D46_tmp_u) * tmp_q + ((((((tmp_3x + tmp_3w) + tmp_3y) +
    D18_tmp * tmp_1d * D24_tmp_1) + tmp_3z * D17_tmp_0) + tmp_49) + tmp_4r) *
                   PD_U.InBus1_Velocities[7]) + (((((((((((((D17_tmp_3 * -2.0 *
    D14 * (tmp_40 * D56_tmp_tmp_tmp + D56_tmp_f * D46_tmp) + tmp_3o * D17_tmp_3 *
    tmp_48) + D17_tmp_3 * 2.0 * ginv_tmp_2 * tmp_48) + tmp_3w) + tmp_3x) +
    tmp_3y) + (D17_tmp * D17_tmp_4 + D17_tmp_1 * D17_tmp_6) * tmp_1d * D24_tmp_1)
    + (D17_tmp_tmp_1 * -D17_tmp_4 + D17_tmp_tmp_0 * D17_tmp_6) * tmp_3z) +
    tmp_3q * PD_P.ArmConstants.Mass1 * D45_tmp_0 * (D17_tmp_7 * D14_tmp_1 +
    D17_tmp_8 * D14_tmp_2)) + ((D14_tmp_6 * smax * D14_tmp_0 + -s * D14_tmp) *
    (PD_P.ArmConstants.MC1 * D14_tmp_1) + (D17_tmp_tmp_3 * D14_tmp_0 +
    D17_tmp_tmp_4) * (PD_P.ArmConstants.MC1 * D14_tmp_2)) * ((-D16_tmp_0 * smax *
    D14_tmp_0 + D27_tmp_1) * (4.0 * PD_P.ArmConstants.Mass1))) + ginv_tmp_d *
    D14_tmp_g * D46_tmp_u) + ginv_tmp_e * tmp_5d * D46_tmp_u) + tmp_49) + tmp_4r)
                  * PD_U.InBus1_Velocities[6]) -
                 (((((((((((((((((((((((((((((((((((((((((tmp * D46_tmp_1 +
    tmp_0 * D56_tmp_7) + D56_tmp_o * D46_tmp_2) + D46_tmp_x * D56_tmp_8) +
    D56_tmp_p * D46_tmp_3) + ginv_tmp_6 * D56_tmp_9) + D56_tmp_q * D46_tmp_4) +
    D46_tmp_x * D56_tmp_a) - D56_tmp_tmp_a) + D56_tmp_tmp_b) - D56_tmp_tmp_c) -
    D56_tmp_tmp_d) + D56_tmp_l * D46_tmp_5) + D46_tmp_10 * D56_tmp_0) +
    D46_tmp_11 * D56_tmp_0) + D56_tmp_tmp_e) - D56_tmp_tmp_f) - D56_tmp_tmp_g) -
    D56_tmp_tmp_h) + D56_tmp_m * D46_tmp_6) + D46_tmp_12 * D56_tmp_b) +
    D46_tmp_tmp_e * D56_tmp_c) + D56_tmp_tmp_i) - D56_tmp_tmp_j) - D56_tmp_tmp_k)
    - D56_tmp_tmp_l) + D56_tmp_tmp_m) - D56_tmp_tmp_n) + -D46_tmp_tmp_3 *
    PD_P.ArmConstants.Mass2 * D56_tmp_3) + D56_tmp_j * D46_tmp_7) + D46_tmp_10 *
    D56_tmp_4) + D46_tmp_11 * D56_tmp_4) + D56_tmp_tmp_o) - D56_tmp_tmp_p) -
    D56_tmp_tmp_q) - D56_tmp_tmp_r) + D56_tmp_k * D46_tmp_8) + D46_tmp_12 *
                      D56_tmp_d) + D46_tmp_tmp_e * D56_tmp_e) + tmp_17) -
                   D56_tmp_r) - D56_tmp_s) * D56_tmp_tmp_7) * 0.25);
  ginv_tmp_tmp_0 = tmp_3j * PD_P.ArmConstants.Inertia1[7];
  D56_tmp_tmp_7 = D46_tmp_tmp_f * PD_U.InBus1_Velocities[4] *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1;
  tmp = tmp_q * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.l1_dim *
    PD_P.ArmConstants.Mass2;
  tmp_0 = tmp_x * PD_P.ArmConstants.Inertia1[0];
  D14_tmp_g = tmp_q * PD_P.ArmConstants.Inertia1[4];
  tmp_m = tmp_4b * PD_P.ArmConstants.Inertia2[3] * D46_tmp_c;
  D16_tmp_0 = tmp_22 * D48_tmp_0;
  D46_tmp_tmp_2 = (((((((((((((tmp_4b * PD_P.ArmConstants.Inertia1[3] *
    D46_tmp_a + tmp_m) + tmp_21 * D46_tmp_q) + D16_tmp_0) + tmp_3r *
    D14_tmp_tmp_0) + tmp_2l * D14_tmp_tmp_0) + tmp_3s * D14_tmp_tmp_0) + tmp_y *
    D14_tmp_tmp_0) + ginv_tmp_tmp_0 * D46_tmp_1) + tmp_3t * D46_tmp_tmp_2) +
                      D56_tmp_tmp_7 * D16) + tmp * D16) + tmp_0 * D56_tmp_7) +
                   D14_tmp_g * D56_tmp_7) + D16_tmp_3 * D56_tmp_7;
  tmp_5d = tmp_41 * D56_tmp_7;
  tmp_k = _mm_set_pd(-2.0, 4.0);
  tmp_l = _mm_set1_pd(PD_P.ArmConstants.MC2);

  /* Inport generated from: '<Root>/InBus1_Inport_2' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function1'
   */
  tmp_i = _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_mul_pd(tmp_k, tmp_l),
    _mm_loadu_pd(&PD_U.InBus1_Velocities[3])), tmp_i), tmp_j);
  _mm_storeu_pd(&tmp_h[0], tmp_i);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  D16_tmp_3 = tmp_h[0];
  D27_tmp_1 = tmp_h[1];
  tmp_i = _mm_mul_pd(tmp_k, _mm_set_pd(PD_U.InBus1_Velocities[5],
    PD_U.InBus1_Velocities[3]));
  _mm_storeu_pd(&tmp_h[0], tmp_i);

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  tmp_11 = tmp_h[0];
  tmp_12 = tmp_h[1];
  tmp_5f = _mm_mul_pd(_mm_mul_pd(_mm_set_pd(4.0, 2.0), tmp_l), tmp_5f);
  _mm_storeu_pd(&tmp_h[0], tmp_5f);

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  tmp_17 = tmp_h[0];
  tmp_19 = tmp_h[1];
  tmp_1b = tmp_3j * PD_P.ArmConstants.Inertia2[7];
  tmp_1d = D46_tmp_d * PD_U.InBus1_Velocities[4];
  tmp_3o = tmp_1d * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2;
  tmp_3q = tmp_42 * D56_tmp_8;
  tmp_48 = tmp_44 * D56_tmp_8;
  D14_tmp_i *= D56_tmp_8;
  tmp_3t = tmp_z * PD_P.ArmConstants.Inertia2[8] * D15_tmp;
  tmp_3w = tmp_2n * D38;
  tmp_3x = tmp_1b * D46_tmp_4;
  tmp_3y = tmp_3o * D45;
  D46_tmp_tmp_6 *= tmp_20;
  tmp_20 = -6.0 * PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[5];
  tmp_3z = tmp_20 * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2 *
    D14_tmp_5;
  D17_tmp_tmp *= D46_tmp_p;
  D46_tmp_tmp_2 = (((((((((((((((((((((((((((((((((((((((((((((((((D46_tmp_tmp_2
    + tmp_5d) + tmp_5e) + D16_tmp_3 * D17_tmp_2) + D27_tmp_1 * D17_tmp_2) +
    tmp_11 * PD_P.ArmConstants.Inertia2[7] * D46_tmp_2) + tmp_12 *
    PD_P.ArmConstants.Inertia2[3] * D46_tmp_tmp_1) + tmp_17 *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2 * D34) + tmp_19 *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D35) + tmp_3q) + tmp_48)
    + D14_tmp_i) + tmp_z * PD_P.ArmConstants.Inertia1[8] * D15_tmp) + tmp_3t) +
    tmp_5g) + tmp_5m) + tmp_5h) + tmp_1g) + tmp_2l * D18) + tmp_1a) + tmp_y *
    D18) + ginv_tmp_tmp_0 * D46_tmp_3) + D46_tmp_tmp_0) + D56_tmp_tmp_7 * D24) +
    tmp * D24) + tmp_0 * D56_tmp_9) + D14_tmp_g * D56_tmp_9) + tmp_a) + tmp_b) +
    tmp_5i) + tmp_1h) + tmp_3w) + tmp_3x) + D46_tmp_tmp) + tmp_3y) + tmp_45) +
    tmp_46) + tmp_47) + tmp_1l) + tmp_1z * D46_tmp_tmp_7) + D46_tmp_tmp_6) +
    -6.0 * PD_P.ArmConstants.MC1 * PD_U.InBus1_Velocities[5] *
    PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass1 * D14_tmp) +
    -6.0 * PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D14_tmp) + D16_tmp_2 *
    D46_tmp_y) + D16_tmp_1 * PD_P.ArmConstants.Inertia1[4] * D46_tmp_y) + tmp_4u
                       * D46_tmp_y) + tmp_31 * D46_tmp_y) + tmp_1t * D15) +
                    tmp_1o * D15) + tmp_3z) + D17_tmp_tmp;
  D46_tmp_tmp_0 = D16_tmp_1 * PD_P.ArmConstants.Inertia2[4] * D46_tmp_p;
  D46_tmp_tmp_7 = tmp_d * PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.l1_dim;
  ginv_tmp_tmp_0 = PD_P.ArmConstants.Mass2;
  D56_tmp_tmp_7 = tmp_3j * PD_P.ArmConstants.Inertia1[6];
  tmp = tmp_4w * D46_tmp_p;
  tmp_0 = tmp_1s * D47;
  D56_tmp_tmp_6 *= D16_tmp;
  D46_tmp_tmp_b *= tmp_1x;
  D56_tmp_tmp_3 *= D16_tmp;
  D14_tmp_g = tmp_5j * D46_tmp_6;
  tmp_5d = tmp_5c * D56_tmp_2;
  D16_tmp_2 = tmp_5j * D46_tmp_8;
  D16_tmp_3 = (((tmp_18 - D46_tmp_h) + D17_tmp_tmp_2) + tmp_s) + D16_tmp_tmp;
  D16_tmp_1 = D16_tmp_3 * tmp_5k;
  D14_tmp_tmp *= D16_tmp;
  D15_tmp_tmp_0 *= tmp_1y;
  D16_tmp *= D48_tmp_tmp;
  D17_tmp_tmp_2 = D56_tmp_tmp_1 * D46_tmp_tmp_9;
  D46_tmp_tmp_9 *= tmp_n;
  D27_tmp_1 = D56_tmp_tmp_1 * D56;
  tmp_s = tmp_n * D56;
  tmp_1t = D56_tmp_tmp_1 * D47_tmp_4;
  D47_tmp_4 *= tmp_n;
  D56_tmp_tmp_1 *= D46_tmp_n;
  tmp_n *= D46_tmp_n;
  tmp_1[53] = -(((((((((((((((((((((((((((((((((((((((((((((((D46_tmp_tmp_2 +
    D46_tmp_tmp_0) + tmp) + tmp_0) + D46_tmp_tmp_7 * ginv_tmp_tmp_0 * D48) +
    tmp_1w * D46_tmp_tmp_8) + D17_tmp_tmp_2) + D46_tmp_tmp_9) + tmp_1u *
    D46_tmp_tmp_a) + D27_tmp_1) + tmp_s) + D56_tmp_tmp_6) + D46_tmp_tmp_b) +
    D56_tmp_tmp_3) + D56_tmp_tmp_7 * D46_tmp_5) - tmp_4h) + tmp_4i) + tmp_4j) +
    tmp_4k) + tmp_1c * D56_tmp_1) + D14_tmp_g) + -PD_U.InBus1_Velocities[5] *
    PD_P.ArmConstants.Inertia2[0] * D45_tmp) + tmp_4o) + tmp_4p) + tmp_5d) +
    D56_tmp_tmp_7 * D46_tmp_7) + -PD_U.InBus1_Velocities[5] *
    PD_P.ArmConstants.Inertia1[0] * D24_tmp) + tmp_56) + tmp_57) + tmp_3p) +
    D37_tmp) + D16_tmp_2) + D16_tmp_1) + D14_tmp_j * tmp_5l) - tmp_59) + tmp_5a)
    + tmp_5b) + ginv_tmp_tmp_2) + tmp_1t) + D47_tmp_4) + tmp_5 * D15_tmp_tmp) +
                      D14_tmp_tmp) + D15_tmp_tmp_0) + D56_tmp_tmp_1) + tmp_n) +
                  D16_tmp) + tmp_3v) * 0.125);
  D46_tmp_tmp_2 = tmp_1d * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2;
  D46_tmp_tmp_1 = (((((((tmp_1m * D17_tmp_5 + (tmp_m + D16_tmp_0)) + tmp_r *
                        D17_tmp_5) + tmp_3i * D17_tmp_2) + tmp_2n * D17_tmp_2) +
                     tmp_1b * D46_tmp_2) + tmp_g * D46_tmp_tmp_1) + tmp_3o * D34)
    + D46_tmp_tmp_2 * D35;
  D15_tmp_tmp = tmp_o * D46_tmp_tmp_8;
  D46_tmp_tmp_7 = tmp_o * D56_tmp_tmp_9;
  D46_tmp_tmp_8 = tmp_o * D56_tmp_tmp_0;
  D46_tmp_tmp_a = tmp_o * D56_tmp_tmp;
  tmp_1[61] = -(((((((((((((((((((((((((((((((((((((((((((((((D46_tmp_tmp_1 +
    tmp_3q) + tmp_48) + D14_tmp_i) + tmp_3t) + tmp_5m) + tmp_1n) + tmp_r * D37)
    + tmp_1h) + tmp_3w) + tmp_3x) + D46_tmp_tmp) + tmp_3y) + D46_tmp_tmp_2 * D46)
    + tmp_46) + tmp_47) + tmp_1l) + D46_tmp_tmp_6) + tmp_20 *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D14_tmp_4) + tmp_3z) +
    D17_tmp_tmp) + D46_tmp_tmp_0) + tmp) + tmp_0) + tmp_1w * D48) + D15_tmp_tmp)
    + D46_tmp_tmp_7) + D56_tmp_tmp_6) + D46_tmp_tmp_b) + D56_tmp_tmp_3) +
    D14_tmp_g) - tmp_4n) + tmp_4o) + tmp_4p) + tmp_5d) + D16_tmp_2) + D16_tmp_3 *
    tmp_5l) + D16_tmp_1) - tmp_59) + tmp_5a) + tmp_5b) + ginv_tmp_tmp_2) +
                     D46_tmp_tmp_8) + D14_tmp_tmp) + D15_tmp_tmp_0) + D16_tmp) +
                 D46_tmp_tmp_a) * 0.125);
  D46_tmp_tmp_2 = tmp_f * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 *
    D14_tmp_4;
  D46_tmp_tmp_1 = PD_U.InBus1_Velocities[3] - D14_tmp_b;
  tmp_1[30] = -(tmp_9 * D46_tmp_tmp_1 + D46_tmp_tmp_2);
  tmp_1[38] = -((((((((((((((((D14_tmp_c + tmp_14) + D67_tmp * D14_tmp) -
    D27_tmp_0) + D14_tmp_3) + tmp_u) + tmp_v) + w_a_tmp * D15) + tmp_15) +
                       tmp_16) - tmp_w) + D14_tmp_7) + D14_tmp_a) + tmp_1i) +
                  tmp_5n) * tmp_q - D56_tmp_tmp_4 * PD_U.InBus1_Velocities[5]) *
                0.25);
  D46_tmp_tmp_0 = tmp_3i * D38;
  D46_tmp_tmp = (((((((((((((tmp_5o + tmp_1e) + tmp_c) + tmp_3u) + tmp_2q) +
    tmp_43) + tmp_3r * D18) + tmp_3s * D18) + tmp_5p) + D46_tmp_tmp_0) + tmp_5q)
                   + tmp_5r) + tmp_5s) + 6.0 * PD_P.ArmConstants.MC1 *
                 PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Hexa_to_joint_L *
                 PD_P.ArmConstants.Mass1 * D14_tmp) + 6.0 *
    PD_U.InBus1_Velocities[5] * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 * D14_tmp;
  D15_tmp_tmp_0 = 6.0 * PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[5];
  D46_tmp_tmp_6 = (((((((-PD_P.ArmConstants.Inertia1[0] * D56_tmp_7 +
    D56_tmp_tmp_2) + D56_tmp_tmp_8) + D56_tmp_tmp_5) + ginv_tmp_tmp) + D14_tmp_h)
                    + tmp_10) + tmp_p) + tmp_1k;
  D46_tmp_tmp_b = D15_tmp_tmp_0 * PD_P.ArmConstants.Hexa_to_joint_L *
    PD_P.ArmConstants.Mass2 * D14_tmp_5;
  D56_tmp_tmp = tmp_13 * D47;
  tmp_1[46] = -(((((((((((((((((((((((((((((((((((((((((((((((D46_tmp_tmp +
    tmp_5t) + tmp_5v) + D46_tmp_tmp_c) + tmp_5u) + tmp_6 * D15) + tmp_7 * D15) +
    D46_tmp_tmp_b) + tmp_5w) + tmp_5x) + D46_tmp_tmp_d) + D56_tmp_tmp) + tmp_e)
    + tmp_4a) - D17_tmp_tmp_2) - D46_tmp_tmp_9) + tmp_5y) - D27_tmp_1) - tmp_s)
    - D56_tmp_tmp_6) + tmp_5z) - D56_tmp_tmp_3) + tmp_4h) - tmp_4i) - tmp_4j) -
    tmp_4k) + tmp_4n) - tmp_4o) - tmp_4p) + tmp_60 * PD_P.ArmConstants.l1_dim *
    PD_P.ArmConstants.Mass2 * D14_tmp_4 * D14_tmp_0) + tmp_55) - tmp_56) -
    tmp_57) - tmp_3p) + tmp_59) - tmp_5a) - tmp_5b) +
    ((((((((((((((((((((((((((((((((((D46_tmp_tmp_6 + D14_tmp_d) - D14_tmp_tmp_1)
    + D14_tmp_tmp_2) + D14_tmp_f) + D15_tmp_tmp_1) + D15_tmp_tmp_2) + D34_tmp_3)
    + D46_tmp_tmp_5) + ginv_tmp_5) + tmp_3k) + tmp_3l) + tmp_23) + tmp_61) +
    tmp_62) - tmp_24) + tmp_25) + tmp_26) + tmp_27) + tmp_28) + D46_tmp_h) +
    tmp_29) + D47_tmp_5) + tmp_2a) - tmp_2b) + tmp_2c) + tmp_2d) + D56_tmp_n) +
           tmp_2e) + tmp_2f) + tmp_2g) + tmp_2h) + tmp_2i) + tmp_2j) + tmp_2k) *
    tmp_x) - tmp_1t) - D47_tmp_4) + tmp_63) - D14_tmp_tmp) + tmp_64) -
                    D56_tmp_tmp_1) - tmp_n) - D16_tmp) + tmp_65) * 0.125);
  tmp_1[54] = -D46_tmp_tmp_2;
  tmp_1[62] = -(D46_tmp_o * D14_tmp_4 * tmp_t);
  tmp_1[31] = -((PD_U.InBus1_Velocities[6] * PD_P.ArmConstants.l1_dim *
                 D14_tmp_4 + tmp_8 * D46_tmp_tmp_1) * D14_tmp_8);
  tmp_1[39] = -((tmp_1j * PD_U.InBus1_Velocities[4] * D34_tmp_0 +
                 -PD_U.InBus1_Velocities[4] * PD_P.ArmConstants.Inertia2[3] *
                 D46_tmp_c) + -0.25 * PD_U.InBus1_Velocities[5] * tmp_66);
  tmp_1[47] = -((((((((((((((((((((((((((((((((((tmp_67 + tmp_68) + tmp_2r) +
    tmp_2q) + tmp_43) + tmp_1m * D37) + D46_tmp_tmp_0) + tmp_5q) + tmp_5s) +
    D15_tmp_tmp_0 * PD_P.ArmConstants.l1_dim * PD_P.ArmConstants.Mass2 *
    D14_tmp_4) + D46_tmp_tmp_b) + tmp_5w) + tmp_5x) + D46_tmp_tmp_d) +
    D56_tmp_tmp) + tmp_1f * D48) - D15_tmp_tmp) - D46_tmp_tmp_7) - D56_tmp_tmp_6)
    + tmp_5z) - D56_tmp_tmp_3) + tmp_4n) - tmp_4o) - tmp_4p) + -8.0 *
    PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[6] * PD_P.ArmConstants.l1_dim
    * PD_P.ArmConstants.Mass2 * D14_tmp_4 * D14_tmp_0) + tmp_59) - tmp_5a) -
                       tmp_5b) + tmp_66 * tmp_x) - D46_tmp_tmp_8) - D14_tmp_tmp)
                   + tmp_64) + -PD_P.ArmConstants.MC2 * PD_U.InBus1_Velocities[5]
                  * PD_P.ArmConstants.Hexa_to_joint_L * PD_P.ArmConstants.Mass2 *
                  D48_tmp_tmp) - D46_tmp_tmp_a) * 0.125);
  tmp_1[55] = -(D48_tmp * D14_tmp_4 * D27_tmp_2);
  tmp_1[63] = -0.0;
  std::memset(&tmp_1[0], 0, 24U * sizeof(real_T));
  std::memset(&tmp_2[0], 0, sizeof(real_T) << 3U);
  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_2 = PD_U.InBus1_Velocities[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5f = _mm_loadu_pd(&tmp_1[(d_k << 3) + i]);
      tmp_5f = _mm_mul_pd(tmp_5f, _mm_set1_pd(D46_tmp_tmp_2));
      tmp_i = _mm_loadu_pd(&tmp_2[i]);
      tmp_5f = _mm_add_pd(tmp_5f, tmp_i);
      _mm_storeu_pd(&tmp_2[i], tmp_5f);
    }
  }

  tmp_3[0] = 0.0;
  tmp_3[1] = 0.0;
  tmp_3[2] = D46_tmp_t * 9.80665;
  D46_tmp_tmp_2 = -9.80665 * D15_tmp;
  tmp_3[3] = ((D14_tmp_k * D14_tmp_1 - D34_tmp_1) - D34_tmp_2) * D46_tmp_tmp_2;
  tmp_3[4] = D15_tmp_2 * 9.80665 * D14_tmp_0;
  tmp_3[5] = 0.0;
  tmp_3[6] = (-D14_tmp_9 * D34_tmp - D34_tmp_2) * D46_tmp_tmp_2;
  tmp_3[7] = PD_P.ArmConstants.MC2 * 9.80665 * PD_P.ArmConstants.Mass2 * D15_tmp
    * D34_tmp_0;
  for (d_k = 0; d_k <= 6; d_k += 2) {
    /* MATLAB Function: '<S1>/MATLAB Function1' */
    tmp_5f = _mm_loadu_pd(&tmp_2[d_k]);
    tmp_i = _mm_loadu_pd(&tmp_3[d_k]);
    tmp_5f = _mm_sub_pd(tmp_5f, tmp_i);
    _mm_storeu_pd(&PD_B.fx[d_k], tmp_5f);
  }

  /* MATLAB Function: '<S1>/MATLAB Function1' */
  PD_mldivide_j(PD_B.ginv, PD_B.fx);

  /* MATLAB Function: '<Root>/GetBInvMatrix' incorporates:
   *  Inport generated from: '<Root>/InBus1_Inport_2'
   */
  /* :  BM1 = BMatrix(xi); */
  /* 'BMatrix:3' phi = xi(4); */
  /* 'BMatrix:4' th  = xi(5); */
  /* 'BMatrix:5' psi = xi(6); */
  /* 'BMatrix:7' BM=[cos(psi)*cos(th),-cos(phi)*sin(psi)+cos(psi)*sin(phi)*sin(th), ... */
  /* 'BMatrix:8'     sin(phi)*sin(psi)+cos(phi)*cos(psi)*sin(th),0,0,0;... */
  /* 'BMatrix:9'     cos(th)*sin(psi), cos(phi)*cos(psi)+sin(phi)*sin(psi)*sin(th),... */
  /* 'BMatrix:10'     -cos(psi)*sin(phi)+cos(phi)*sin(psi)*sin(th),0,0,0;... */
  /* 'BMatrix:11'     -sin(th),cos(th)*sin(phi),cos(phi)*cos(th),0,0,0;... */
  /* 'BMatrix:12'     0,0,0,1,sin(phi)*tan(th),cos(phi)*tan(th);... */
  /* 'BMatrix:13'     0,0,0,0,cos(phi),-sin(phi);0,0,0,0,sec(th)*sin(phi),cos(phi)*sec(th)]; */
  /* :  BM = blkdiag(BM1, eye(2,2)); */
  D14_tmp = std::tan(PD_U.InBus1_Positions[4]);

  /* :  BMinv = inv(BM); */
  std::memset(&x[0], 0, sizeof(real_T) << 6U);
  std::memset(&PD_B.BMinv[0], 0, sizeof(real_T) << 6U);
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
    p[d_k] = static_cast<int8_T>(d_k + 1);
    ipiv[d_k] = static_cast<int8_T>(d_k + 1);
  }

  for (i = 0; i < 7; i++) {
    jj = i * 9;
    iy = 9 - i;
    b_ix = 0;
    ix = jj;
    smax = std::abs(x[jj]);
    for (d_k = 2; d_k < iy; d_k++) {
      s = std::abs(x[(ix + d_k) - 1]);
      if (s > smax) {
        b_ix = d_k - 1;
        smax = s;
      }
    }

    if (x[jj + b_ix] != 0.0) {
      if (b_ix != 0) {
        iy = i + b_ix;
        ipiv[i] = static_cast<int8_T>(iy + 1);
        b_ix = i;
        for (ix = 0; ix < 8; ix++) {
          d_k = (ix << 3) + b_ix;
          smax = x[d_k];
          x[d_k] = x[iy];
          x[iy] = smax;
          iy += 8;
        }
      }

      iy = (jj - i) + 8;
      ix = (((((iy - jj) - 1) / 2) << 1) + jj) + 2;
      d_k = ix - 2;
      for (b_ix = jj + 2; b_ix <= d_k; b_ix += 2) {
        tmp_5f = _mm_loadu_pd(&x[b_ix - 1]);
        tmp_5f = _mm_div_pd(tmp_5f, _mm_set1_pd(x[jj]));
        _mm_storeu_pd(&x[b_ix - 1], tmp_5f);
      }

      for (b_ix = ix; b_ix <= iy; b_ix++) {
        x[b_ix - 1] /= x[jj];
      }
    }

    iy = 6 - i;
    b_ix = jj + 10;
    ix = jj + 8;
    for (d_k = 0; d_k <= iy; d_k++) {
      D46_tmp_tmp_2 = x[(d_k << 3) + ix];
      if (D46_tmp_tmp_2 != 0.0) {
        smax = -D46_tmp_tmp_2;
        c_ix = jj + 1;
        d = (b_ix - i) + 6;
        for (ijA = b_ix; ijA <= d; ijA++) {
          x[ijA - 1] += x[(c_ix + ijA) - b_ix] * smax;
        }
      }

      b_ix += 8;
    }
  }

  for (i = 0; i < 7; i++) {
    ipiv_0 = ipiv[i];
    if (ipiv_0 > i + 1) {
      iy = ipiv_0 - 1;
      jj = p[iy];
      p[iy] = p[i];
      p[i] = static_cast<int8_T>(jj);
    }
  }

  for (i = 0; i < 8; i++) {
    ipiv_0 = p[i];
    c_ix = (ipiv_0 - 1) << 3;
    PD_B.BMinv[i + c_ix] = 1.0;
    for (iy = i + 1; iy < 9; iy++) {
      d_k = (c_ix + iy) - 1;
      if (PD_B.BMinv[d_k] != 0.0) {
        for (b_ix = iy + 1; b_ix < 9; b_ix++) {
          jj = (c_ix + b_ix) - 1;
          PD_B.BMinv[jj] -= x[(((iy - 1) << 3) + b_ix) - 1] * PD_B.BMinv[d_k];
        }
      }
    }
  }

  /* MATLAB Function: '<S3>/PD Controller' incorporates:
   *  Constant: '<S3>/Kd'
   *  Constant: '<S3>/Kp'
   */
  /* :  kp_m = [kp(1) 0       0     0     0       0     0     0; */
  /* :          0     kp(2)   0     0     0       0     0     0; */
  /* :          0     0       kp(3) 0     0       0     0     0; */
  /* :          0     0       0     kp(4) 0       0     0     0; */
  /* :          0     0       0     0     kp(5)   0     0     0; */
  /* :          0     0       0     0     0       kp(6) 0     0; */
  /* :          0     0       0     0     0       0     kp(7) 0; */
  /* :          0     0       0     0     0       0     0     kp(8)]; */
  /* :  kd_m = [kd(1) 0       0     0     0       0     0     0; */
  /* :          0     kd(2)   0     0     0       0     0     0; */
  /* :          0     0       kd(3) 0     0       0     0     0; */
  /* :          0     0       0     kd(4) 0       0     0     0; */
  /* :          0     0       0     0     kd(5)   0     0     0; */
  /* :          0     0       0     0     0       kd(6) 0     0; */
  /* :          0     0       0     0     0       0     kd(7) 0; */
  /* :          0     0       0     0     0       0     0     kd(8)]; */
  /* :  u_aux = kp_m * e + kd_m * de; */
  tmp_1[0] = PD_P.PID.Kp[0];
  tmp_1[8] = 0.0;
  tmp_1[16] = 0.0;
  tmp_1[24] = 0.0;
  tmp_1[32] = 0.0;
  tmp_1[40] = 0.0;
  tmp_1[48] = 0.0;
  tmp_1[56] = 0.0;
  tmp_1[1] = 0.0;
  tmp_1[9] = PD_P.PID.Kp[1];
  tmp_1[17] = 0.0;
  tmp_1[25] = 0.0;
  tmp_1[33] = 0.0;
  tmp_1[41] = 0.0;
  tmp_1[49] = 0.0;
  tmp_1[57] = 0.0;
  tmp_1[2] = 0.0;
  tmp_1[10] = 0.0;
  tmp_1[18] = PD_P.PID.Kp[2];
  tmp_1[26] = 0.0;
  tmp_1[34] = 0.0;
  tmp_1[42] = 0.0;
  tmp_1[50] = 0.0;
  tmp_1[58] = 0.0;
  tmp_1[3] = 0.0;
  tmp_1[11] = 0.0;
  tmp_1[19] = 0.0;
  tmp_1[27] = PD_P.PID.Kp[3];
  tmp_1[35] = 0.0;
  tmp_1[43] = 0.0;
  tmp_1[51] = 0.0;
  tmp_1[59] = 0.0;
  tmp_1[4] = 0.0;
  tmp_1[12] = 0.0;
  tmp_1[20] = 0.0;
  tmp_1[28] = 0.0;
  tmp_1[36] = PD_P.PID.Kp[4];
  tmp_1[44] = 0.0;
  tmp_1[52] = 0.0;
  tmp_1[60] = 0.0;
  tmp_1[5] = 0.0;
  tmp_1[13] = 0.0;
  tmp_1[21] = 0.0;
  tmp_1[29] = 0.0;
  tmp_1[37] = 0.0;
  tmp_1[45] = PD_P.PID.Kp[5];
  tmp_1[53] = 0.0;
  tmp_1[61] = 0.0;
  tmp_1[6] = 0.0;
  tmp_1[14] = 0.0;
  tmp_1[22] = 0.0;
  tmp_1[30] = 0.0;
  tmp_1[38] = 0.0;
  tmp_1[46] = 0.0;
  tmp_1[54] = PD_P.PID.Kp[6];
  tmp_1[62] = 0.0;
  tmp_1[7] = 0.0;
  tmp_1[15] = 0.0;
  tmp_1[23] = 0.0;
  tmp_1[31] = 0.0;
  tmp_1[39] = 0.0;
  tmp_1[47] = 0.0;
  tmp_1[55] = 0.0;
  tmp_1[63] = PD_P.PID.Kp[7];
  tmp_4[0] = PD_P.PID.Kd[0];
  tmp_4[8] = 0.0;
  tmp_4[16] = 0.0;
  tmp_4[24] = 0.0;
  tmp_4[32] = 0.0;
  tmp_4[40] = 0.0;
  tmp_4[48] = 0.0;
  tmp_4[56] = 0.0;
  tmp_4[1] = 0.0;
  tmp_4[9] = PD_P.PID.Kd[1];
  tmp_4[17] = 0.0;
  tmp_4[25] = 0.0;
  tmp_4[33] = 0.0;
  tmp_4[41] = 0.0;
  tmp_4[49] = 0.0;
  tmp_4[57] = 0.0;
  tmp_4[2] = 0.0;
  tmp_4[10] = 0.0;
  tmp_4[18] = PD_P.PID.Kd[2];
  tmp_4[26] = 0.0;
  tmp_4[34] = 0.0;
  tmp_4[42] = 0.0;
  tmp_4[50] = 0.0;
  tmp_4[58] = 0.0;
  tmp_4[3] = 0.0;
  tmp_4[11] = 0.0;
  tmp_4[19] = 0.0;
  tmp_4[27] = PD_P.PID.Kd[3];
  tmp_4[35] = 0.0;
  tmp_4[43] = 0.0;
  tmp_4[51] = 0.0;
  tmp_4[59] = 0.0;
  tmp_4[4] = 0.0;
  tmp_4[12] = 0.0;
  tmp_4[20] = 0.0;
  tmp_4[28] = 0.0;
  tmp_4[36] = PD_P.PID.Kd[4];
  tmp_4[44] = 0.0;
  tmp_4[52] = 0.0;
  tmp_4[60] = 0.0;
  tmp_4[5] = 0.0;
  tmp_4[13] = 0.0;
  tmp_4[21] = 0.0;
  tmp_4[29] = 0.0;
  tmp_4[37] = 0.0;
  tmp_4[45] = PD_P.PID.Kd[5];
  tmp_4[53] = 0.0;
  tmp_4[61] = 0.0;
  tmp_4[6] = 0.0;
  tmp_4[14] = 0.0;
  tmp_4[22] = 0.0;
  tmp_4[30] = 0.0;
  tmp_4[38] = 0.0;
  tmp_4[46] = 0.0;
  tmp_4[54] = PD_P.PID.Kd[6];
  tmp_4[62] = 0.0;
  tmp_4[7] = 0.0;
  tmp_4[15] = 0.0;
  tmp_4[23] = 0.0;
  tmp_4[31] = 0.0;
  tmp_4[39] = 0.0;
  tmp_4[47] = 0.0;
  tmp_4[55] = 0.0;
  tmp_4[63] = PD_P.PID.Kd[7];
  for (i = 0; i < 8; i++) {
    /* MATLAB Function: '<Root>/GetBInvMatrix' */
    jj = i << 3;
    for (iy = 7; iy >= 0; iy--) {
      b_ix = iy << 3;
      d_k = iy + jj;
      D46_tmp_tmp_2 = PD_B.BMinv[d_k];
      if (D46_tmp_tmp_2 != 0.0) {
        PD_B.BMinv[d_k] = D46_tmp_tmp_2 / x[iy + b_ix];
        for (ix = 0; ix < iy; ix++) {
          c_ix = ix + jj;
          PD_B.BMinv[c_ix] -= x[ix + b_ix] * PD_B.BMinv[d_k];
        }
      }
    }

    /* Sum: '<S5>/Minus1' incorporates:
     *  Inport generated from: '<Root>/InBus1_Inport_2'
     *  Inport generated from: '<Root>/InBus_Inport_1'
     *  Sum: '<S5>/Minus'
     * */
    tmp_5f = _mm_sub_pd(_mm_set_pd(PD_U.InBus_dqd[i], PD_U.InBus_qd[i]),
                        _mm_set_pd(PD_U.InBus1_Velocities[i],
      PD_U.InBus1_Positions[i]));
    _mm_storeu_pd(&tmp_h[0], tmp_5f);

    /* Sum: '<S5>/Minus' */
    PD_B.error_q[i] = tmp_h[0];

    /* Sum: '<S5>/Minus1' */
    PD_B.error_dq[i] = tmp_h[1];

    /* MATLAB Function: '<S3>/PD Controller' */
    tmp_2[i] = 0.0;
  }

  /* MATLAB Function: '<S3>/PD Controller' incorporates:
   *  Sum: '<S5>/Minus'
   *  Sum: '<S5>/Minus1'
   */
  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_2 = PD_B.error_q[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5f = _mm_loadu_pd(&tmp_1[(d_k << 3) + i]);
      tmp_5f = _mm_mul_pd(tmp_5f, _mm_set1_pd(D46_tmp_tmp_2));
      tmp_i = _mm_loadu_pd(&tmp_2[i]);
      tmp_5f = _mm_add_pd(tmp_5f, tmp_i);
      _mm_storeu_pd(&tmp_2[i], tmp_5f);
    }

    tmp_3[d_k] = 0.0;
  }

  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_2 = PD_B.error_dq[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5f = _mm_loadu_pd(&tmp_4[(d_k << 3) + i]);
      tmp_5f = _mm_mul_pd(tmp_5f, _mm_set1_pd(D46_tmp_tmp_2));
      tmp_i = _mm_loadu_pd(&tmp_3[i]);
      tmp_5f = _mm_add_pd(tmp_5f, tmp_i);
      _mm_storeu_pd(&tmp_3[i], tmp_5f);
    }
  }

  for (i = 0; i <= 6; i += 2) {
    tmp_5f = _mm_loadu_pd(&tmp_2[i]);
    tmp_i = _mm_loadu_pd(&tmp_3[i]);
    tmp_5f = _mm_add_pd(tmp_5f, tmp_i);
    _mm_storeu_pd(&PD_B.u_aux[i], tmp_5f);

    /* Sum: '<S3>/Sum' incorporates:
     *  Inport generated from: '<Root>/InBus_Inport_1'
     */
    tmp_i = _mm_loadu_pd(&PD_U.InBus_ddqd[i]);
    tmp_5f = _mm_add_pd(tmp_i, tmp_5f);

    /* Sum: '<S3>/Sum' */
    _mm_storeu_pd(&PD_B.Sum[i], tmp_5f);

    /* Sum: '<S3>/Add1' incorporates:
     *  Sum: '<S3>/Sum'
     */
    tmp_i = _mm_loadu_pd(&PD_B.fx[i]);
    tmp_5f = _mm_sub_pd(tmp_5f, tmp_i);

    /* Sum: '<S3>/Add1' */
    _mm_storeu_pd(&PD_B.Add1[i], tmp_5f);
  }

  /* Product: '<S3>/Matrix Multiply' incorporates:
   *  Sum: '<S3>/Add1'
   */
  std::memcpy(&x[0], &PD_B.ginv[0], sizeof(real_T) << 6U);
  for (d_k = 0; d_k < 8; d_k++) {
    tmp_2[d_k] = PD_B.Add1[d_k];
    PD_B.u[d_k] = 0.0;
  }

  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_2 = tmp_2[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5f = _mm_loadu_pd(&x[(d_k << 3) + i]);
      tmp_5f = _mm_mul_pd(tmp_5f, _mm_set1_pd(D46_tmp_tmp_2));
      tmp_i = _mm_loadu_pd(&PD_B.u[i]);
      tmp_5f = _mm_add_pd(tmp_5f, tmp_i);
      _mm_storeu_pd(&PD_B.u[i], tmp_5f);
    }
  }

  /* End of Product: '<S3>/Matrix Multiply' */

  /* Product: '<Root>/Matrix Multiply' incorporates:
   *  Product: '<S3>/Matrix Multiply'
   */
  std::memcpy(&x[0], &PD_B.BMinv[0], sizeof(real_T) << 6U);
  for (d_k = 0; d_k < 8; d_k++) {
    tmp_2[d_k] = PD_B.u[d_k];
    PD_B.FMTq[d_k] = 0.0;
  }

  for (d_k = 0; d_k < 8; d_k++) {
    D46_tmp_tmp_2 = tmp_2[d_k];
    for (i = 0; i <= 6; i += 2) {
      tmp_5f = _mm_loadu_pd(&x[(d_k << 3) + i]);
      tmp_5f = _mm_mul_pd(tmp_5f, _mm_set1_pd(D46_tmp_tmp_2));
      tmp_i = _mm_loadu_pd(&PD_B.FMTq[i]);
      tmp_5f = _mm_add_pd(tmp_5f, tmp_i);
      _mm_storeu_pd(&PD_B.FMTq[i], tmp_5f);
    }
  }

  /* End of Product: '<Root>/Matrix Multiply' */

  /* Outport generated from: '<Root>/Output2' incorporates:
   *  Product: '<Root>/Matrix Multiply'
   */
  std::memcpy(&PD_Y.Output2[0], &PD_B.FMTq[0], sizeof(real_T) << 3U);

  /* Matfile logging */
  rt_UpdateTXYLogVars((&PD_M)->rtwLogInfo, ((&PD_M)->Timing.t));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal((&PD_M))!=-1) &&
        !((rtmGetTFinal((&PD_M))-(&PD_M)->Timing.t[0]) > (&PD_M)->Timing.t[0] *
          (DBL_EPSILON))) {
      rtmSetErrorStatus((&PD_M), "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++(&PD_M)->Timing.clockTick0)) {
    ++(&PD_M)->Timing.clockTickH0;
  }

  (&PD_M)->Timing.t[0] = (&PD_M)->Timing.clockTick0 * (&PD_M)->Timing.stepSize0
    + (&PD_M)->Timing.clockTickH0 * (&PD_M)->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    (&PD_M)->Timing.clockTick1++;
    if (!(&PD_M)->Timing.clockTick1) {
      (&PD_M)->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void PD::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&PD_M)->solverInfo, &(&PD_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&PD_M)->solverInfo, &rtmGetTPtr((&PD_M)));
    rtsiSetStepSizePtr(&(&PD_M)->solverInfo, &(&PD_M)->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&(&PD_M)->solverInfo, (&rtmGetErrorStatus((&PD_M))));
    rtsiSetRTModelPtr(&(&PD_M)->solverInfo, (&PD_M));
  }

  rtsiSetSimTimeStep(&(&PD_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&PD_M)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&PD_M)->solverInfo, false);
  rtsiSetSolverName(&(&PD_M)->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr((&PD_M), &(&PD_M)->Timing.tArray[0]);
  rtmSetTFinal((&PD_M), 20.0);
  (&PD_M)->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (nullptr);
    (&PD_M)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo((&PD_M)->rtwLogInfo, (nullptr));
    rtliSetLogXSignalPtrs((&PD_M)->rtwLogInfo, (nullptr));
    rtliSetLogT((&PD_M)->rtwLogInfo, "");
    rtliSetLogX((&PD_M)->rtwLogInfo, "");
    rtliSetLogXFinal((&PD_M)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&PD_M)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&PD_M)->rtwLogInfo, 4);
    rtliSetLogMaxRows((&PD_M)->rtwLogInfo, 0);
    rtliSetLogDecimation((&PD_M)->rtwLogInfo, 1);
    rtliSetLogY((&PD_M)->rtwLogInfo, "");
    rtliSetLogYSignalInfo((&PD_M)->rtwLogInfo, (nullptr));
    rtliSetLogYSignalPtrs((&PD_M)->rtwLogInfo, (nullptr));
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime((&PD_M)->rtwLogInfo, 0.0, rtmGetTFinal((&PD_M)),
    (&PD_M)->Timing.stepSize0, (&rtmGetErrorStatus((&PD_M))));
}

/* Model terminate function */
void PD::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
PD::PD() :
  PD_U(),
  PD_Y(),
  PD_B(),
  PD_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
PD::~PD() = default;

/* Real-Time Model get method */
RT_MODEL_PD_T * PD::getRTM()
{
  return (&PD_M);
}
