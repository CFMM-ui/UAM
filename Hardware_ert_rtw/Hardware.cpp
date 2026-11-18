//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Hardware.cpp
//
// Code generated for Simulink model 'Hardware'.
//
// Model version                  : 1.61
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Wed Nov  4 15:55:33 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Hardware.h"
#include "rtwtypes.h"
#include "Hardware_types.h"
#include <math.h>
#include "Hardware_private.h"
#include <string.h>

extern "C"
{

#include "rt_nonfinite.h"

}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// Output and update for atomic system:
//    '<S4>/U power x1'
//    '<S4>/U power x2'
//    '<S4>/U power x3'
//    '<S4>/U power x4'
//
void Hardware::Hardware_Upowerx1(const real_T rtu_u[8], const real_T rtu_v[8],
  real_T rty_uv[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    rty_uv[i] = rt_powd_snf(fabs(rtu_u[i]), rtu_v[i]);
  }
}

// Function for MATLAB Function: '<S9>/MATLAB Function1'
void Hardware::Hardware_mldivide_o(const real_T A[64], real_T B[8])
{
  int32_T jj;
  int32_T kAcol;
  memcpy(&Hardware_B.b_A[0], &A[0], sizeof(real_T) << 6U);
  for (int32_T j = 0; j < 8; j++) {
    Hardware_B.ipiv_m[j] = static_cast<int8_T>(j + 1);
  }

  for (int32_T j = 0; j < 7; j++) {
    int32_T a;
    int32_T jA;
    int32_T n;
    int8_T ipiv;
    jj = j * 9;
    n = 9 - j;
    a = 0;
    Hardware_B.smax_h = fabs(Hardware_B.b_A[jj]);
    for (kAcol = 2; kAcol < n; kAcol++) {
      Hardware_B.s_c = fabs(Hardware_B.b_A[(jj + kAcol) - 1]);
      if (Hardware_B.s_c > Hardware_B.smax_h) {
        a = kAcol - 1;
        Hardware_B.smax_h = Hardware_B.s_c;
      }
    }

    if (Hardware_B.b_A[jj + a] != 0.0) {
      if (a != 0) {
        n = j + a;
        Hardware_B.ipiv_m[j] = static_cast<int8_T>(n + 1);
        for (kAcol = 0; kAcol < 8; kAcol++) {
          jA = kAcol << 3;
          a = jA + j;
          Hardware_B.smax_h = Hardware_B.b_A[a];
          jA += n;
          Hardware_B.b_A[a] = Hardware_B.b_A[jA];
          Hardware_B.b_A[jA] = Hardware_B.smax_h;
        }
      }

      n = (jj - j) + 8;
      for (kAcol = jj + 2; kAcol <= n; kAcol++) {
        Hardware_B.b_A[kAcol - 1] /= Hardware_B.b_A[jj];
      }
    }

    a = 6 - j;
    jA = jj + 10;
    for (kAcol = 0; kAcol <= a; kAcol++) {
      Hardware_B.smax_h = Hardware_B.b_A[((kAcol << 3) + jj) + 8];
      if (Hardware_B.smax_h != 0.0) {
        int32_T c;
        c = (jA - j) + 6;
        for (n = jA; n <= c; n++) {
          Hardware_B.b_A[n - 1] += Hardware_B.b_A[((jj + n) - jA) + 1] *
            -Hardware_B.smax_h;
        }
      }

      jA += 8;
    }

    ipiv = Hardware_B.ipiv_m[j];
    if (j + 1 != ipiv) {
      Hardware_B.smax_h = B[j];
      B[j] = B[ipiv - 1];
      B[ipiv - 1] = Hardware_B.smax_h;
    }
  }

  for (int32_T j = 0; j < 8; j++) {
    kAcol = j << 3;
    if (B[j] != 0.0) {
      for (jj = j + 2; jj < 9; jj++) {
        B[jj - 1] -= Hardware_B.b_A[(jj + kAcol) - 1] * B[j];
      }
    }
  }

  for (int32_T j = 7; j >= 0; j--) {
    kAcol = j << 3;
    Hardware_B.smax_h = B[j];
    if (Hardware_B.smax_h != 0.0) {
      B[j] = Hardware_B.smax_h / Hardware_B.b_A[j + kAcol];
      for (jj = 0; jj < j; jj++) {
        B[jj] -= Hardware_B.b_A[jj + kAcol] * B[j];
      }
    }
  }
}

void Hardware::PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T
  *obj, const real_T waypoints[144], const real_T timeData[18])
{
  int32_T b_coeffVec_tmp;
  int32_T b_i;
  int32_T b_j;
  static const int8_T tmp[4] = { 0, 0, 0, 1 };

  memset(&Hardware_B.coefMat[0], 0, 544U * sizeof(real_T));
  for (b_i = 0; b_i < 17; b_i++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    Hardware_B.finalTime = timeData[b_i + 1] - timeData[b_i];
    for (b_j = 0; b_j < 8; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      b_coeffVec_tmp = (b_i << 3) + b_j;
      Hardware_B.b_coeffVec[0] = waypoints[b_coeffVec_tmp];
      Hardware_B.b_coeffVec[1] = obj->VelocityBoundaryCondition[b_coeffVec_tmp];
      b_coeffVec_tmp = ((b_i + 1) << 3) + b_j;
      Hardware_B.waypoints_idx_0 = waypoints[b_coeffVec_tmp] -
        (Hardware_B.finalTime * Hardware_B.b_coeffVec[1] +
         Hardware_B.b_coeffVec[0]);
      Hardware_B.waypoints_idx_1 = obj->VelocityBoundaryCondition[b_coeffVec_tmp]
        - (0.0 * Hardware_B.b_coeffVec[0] + Hardware_B.b_coeffVec[1]);
      Hardware_B.b_coeffVec[3] = Hardware_B.b_coeffVec[0];
      b_coeffVec_tmp = ((b_i << 3) + b_j) + 1;
      Hardware_B.coefMat_tmp = Hardware_B.finalTime * Hardware_B.finalTime;
      Hardware_B.coefMat[b_coeffVec_tmp - 1] = 1.0 / Hardware_B.coefMat_tmp *
        Hardware_B.waypoints_idx_1 + -2.0 / rt_powd_snf(Hardware_B.finalTime,
        3.0) * Hardware_B.waypoints_idx_0;
      Hardware_B.coefMat[b_coeffVec_tmp + 135] = 3.0 / Hardware_B.coefMat_tmp *
        Hardware_B.waypoints_idx_0 + -1.0 / Hardware_B.finalTime *
        Hardware_B.waypoints_idx_1;
      Hardware_B.coefMat[b_coeffVec_tmp + 271] = Hardware_B.b_coeffVec[1];
      Hardware_B.coefMat[b_coeffVec_tmp + 407] = Hardware_B.b_coeffVec[3];
    }
  }

  memset(&Hardware_B.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&Hardware_B.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    b_i = tmp[b_j];
    for (b_coeffVec_tmp = 0; b_coeffVec_tmp < 8; b_coeffVec_tmp++) {
      Hardware_B.coeffMat[b_coeffVec_tmp + 24] += Hardware_B.coefMat[136 * b_j +
        b_coeffVec_tmp] * static_cast<real_T>(b_i);
    }
  }

  memset(&Hardware_B.coefsWithFlatStart[0], 0, 576U * sizeof(real_T));
  memcpy(&Hardware_B.coefsWithFlatStart[0], &Hardware_B.coeffMat[0], sizeof
         (real_T) << 3U);
  memcpy(&Hardware_B.coefsWithFlatStart[144], &Hardware_B.coeffMat[8], sizeof
         (real_T) << 3U);
  memcpy(&Hardware_B.coefsWithFlatStart[288], &Hardware_B.coeffMat[16], sizeof
         (real_T) << 3U);
  memcpy(&Hardware_B.coefsWithFlatStart[432], &Hardware_B.coeffMat[24], sizeof
         (real_T) << 3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&Hardware_B.coefsWithFlatStart[8], &Hardware_B.coefMat[0], 136U *
         sizeof(real_T));
  memcpy(&Hardware_B.coefsWithFlatStart[152], &Hardware_B.coefMat[136], 136U *
         sizeof(real_T));
  memcpy(&Hardware_B.coefsWithFlatStart[296], &Hardware_B.coefMat[272], 136U *
         sizeof(real_T));
  memcpy(&Hardware_B.coefsWithFlatStart[440], &Hardware_B.coefMat[408], 136U *
         sizeof(real_T));
  Hardware_B.breaksWithFlatStart[0] = timeData[0] - 1.0;
  memcpy(&Hardware_B.breaksWithFlatStart[1], &timeData[0], 18U * sizeof(real_T));
  Hardware_B.finalTime = Hardware_B.breaksWithFlatStart[18] -
    Hardware_B.breaksWithFlatStart[17];
  Hardware_B.b_coeffVec[0] = rt_powd_snf(Hardware_B.finalTime, 3.0);
  Hardware_B.b_coeffVec[1] = rt_powd_snf(Hardware_B.finalTime, 2.0);
  Hardware_B.b_coeffVec[2] = rt_powd_snf(Hardware_B.finalTime, 1.0);
  Hardware_B.b_coeffVec[3] = rt_powd_snf(Hardware_B.finalTime, 0.0);
  memset(&Hardware_B.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&Hardware_B.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    Hardware_B.finalTime = Hardware_B.b_coeffVec[b_j];
    for (b_i = 0; b_i < 8; b_i++) {
      Hardware_B.coeffMat[b_i + 24] += Hardware_B.coefsWithFlatStart[(144 * b_j
        + b_i) + 136] * Hardware_B.finalTime;
    }
  }

  memset(&obj->PPDStruct.coefs[0], 0, 608U * sizeof(real_T));
  for (b_j = 0; b_j < 4; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memcpy(&obj->PPDStruct.coefs[b_j * 152], &Hardware_B.coefsWithFlatStart[b_j *
           144], 144U * sizeof(real_T));
    memcpy(&obj->PPDStruct.coefs[b_j * 152 + 144], &Hardware_B.coeffMat[b_j << 3],
           sizeof(real_T) << 3U);
  }

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&obj->PPStruct.breaks[0], &Hardware_B.breaksWithFlatStart[0], 19U *
         sizeof(real_T));
  obj->PPStruct.breaks[19] = Hardware_B.breaksWithFlatStart[18] + 1.0;
  for (b_j = 0; b_j < 608; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    obj->PPStruct.coefs[b_j] = obj->PPDStruct.coefs[b_j];
    obj->PPDStruct.coefs[b_j] = 0.0;
  }

  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 152; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      obj->PPDStruct.coefs[b_j + 152 * (b_i + 1)] = obj->PPStruct.coefs[b_i *
        152 + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  memset(&obj->PPDDStruct.coefs[0], 0, 608U * sizeof(real_T));
  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 152; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      obj->PPDDStruct.coefs[b_j + 152 * (b_i + 1)] = obj->PPDStruct.coefs[b_i *
        152 + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&obj->PPDStruct.breaks[0], &obj->PPStruct.breaks[0], 20U * sizeof
         (real_T));
  memcpy(&obj->PPDDStruct.breaks[0], &obj->PPStruct.breaks[0], 20U * sizeof
         (real_T));
  obj->PPFormUpdatedNeeded = false;
}

void Hardware::Hardware_ppval(const real_T pp_breaks[20], const real_T pp_coefs
  [608], real_T x, real_T v[8])
{
  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  if (rtIsNaN(x)) {
    for (int32_T low_ip1 = 0; low_ip1 < 8; low_ip1++) {
      v[low_ip1] = (rtNaN);
    }
  } else {
    real_T xloc;
    int32_T high_i;
    int32_T low_i;
    int32_T low_ip1;
    int32_T mid_i;
    low_i = 0;
    low_ip1 = 1;
    high_i = 20;
    while (high_i > low_ip1 + 1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (x >= pp_breaks[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i;
      } else {
        high_i = mid_i;
      }
    }

    low_ip1 = low_i << 3;
    xloc = x - pp_breaks[low_i];
    memcpy(&v[0], &pp_coefs[low_ip1], sizeof(real_T) << 3U);
    for (low_i = 0; low_i < 3; low_i++) {
      high_i = ((low_i + 1) * 152 + low_ip1) - 1;
      for (mid_i = 0; mid_i < 8; mid_i++) {
        v[mid_i] = pp_coefs[(high_i + mid_i) + 1] + xloc * v[mid_i];
      }
    }
  }

  // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
}

// Model step function
void Hardware::step()
{
  real_T tmp;
  int32_T i;
  int32_T ijA;
  int32_T jA;
  int8_T ipiv;
  boolean_T exitg1;
  boolean_T propChange;

  // MATLAB Function: '<S2>/GetBInvMatrix' incorporates:
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
  //   MATLAB Function: '<S9>/MATLAB Function1'

  Hardware_B.DigitalClock = cos(Hardware_DW.DiscreteTimeIntegrator_DSTATE[5]);
  Hardware_B.x_tmp = sin(Hardware_DW.DiscreteTimeIntegrator_DSTATE[3]);
  Hardware_B.x_tmp_c = sin(Hardware_DW.DiscreteTimeIntegrator_DSTATE[5]);
  Hardware_B.x_tmp_k = cos(Hardware_DW.DiscreteTimeIntegrator_DSTATE[3]);
  Hardware_B.x_tmp_cx = sin(Hardware_DW.DiscreteTimeIntegrator_DSTATE[4]);
  Hardware_B.x_tmp_b = cos(Hardware_DW.DiscreteTimeIntegrator_DSTATE[4]);
  Hardware_B.smax = tan(Hardware_DW.DiscreteTimeIntegrator_DSTATE[4]);
  memset(&Hardware_B.ginv[0], 0, sizeof(real_T) << 6U);
  memset(&Hardware_B.BMinv[0], 0, sizeof(real_T) << 6U);
  Hardware_B.ginv[0] = Hardware_B.DigitalClock * Hardware_B.x_tmp_b;
  Hardware_B.rtb_ginv_tmp_tmp = Hardware_B.DigitalClock * Hardware_B.x_tmp;
  Hardware_B.rtb_ginv_tmp_tmp_f = -Hardware_B.x_tmp_k * Hardware_B.x_tmp_c;
  Hardware_B.rtb_ginv_tmp_p = Hardware_B.rtb_ginv_tmp_tmp * Hardware_B.x_tmp_cx
    + Hardware_B.rtb_ginv_tmp_tmp_f;
  Hardware_B.ginv[8] = Hardware_B.rtb_ginv_tmp_p;
  Hardware_B.rtb_ginv_tmp_o = Hardware_B.x_tmp * Hardware_B.x_tmp_c;
  Hardware_B.rtb_ginv_tmp_n = Hardware_B.x_tmp_k * Hardware_B.DigitalClock;
  Hardware_B.rtb_ginv_tmp_c = Hardware_B.rtb_ginv_tmp_n * Hardware_B.x_tmp_cx +
    Hardware_B.rtb_ginv_tmp_o;
  Hardware_B.ginv[16] = Hardware_B.rtb_ginv_tmp_c;
  Hardware_B.ginv[24] = 0.0;
  Hardware_B.ginv[32] = 0.0;
  Hardware_B.ginv[40] = 0.0;
  Hardware_B.ginv[1] = Hardware_B.x_tmp_b * Hardware_B.x_tmp_c;
  Hardware_B.rtb_ginv_tmp_o = Hardware_B.rtb_ginv_tmp_o * Hardware_B.x_tmp_cx +
    Hardware_B.rtb_ginv_tmp_n;
  Hardware_B.ginv[9] = Hardware_B.rtb_ginv_tmp_o;
  Hardware_B.rtb_ginv_tmp_n = Hardware_B.x_tmp_k * Hardware_B.x_tmp_c *
    Hardware_B.x_tmp_cx;
  Hardware_B.rtb_ginv_tmp_l = -Hardware_B.DigitalClock * Hardware_B.x_tmp +
    Hardware_B.rtb_ginv_tmp_n;
  Hardware_B.ginv[17] = Hardware_B.rtb_ginv_tmp_l;
  Hardware_B.ginv[25] = 0.0;
  Hardware_B.ginv[33] = 0.0;
  Hardware_B.ginv[41] = 0.0;
  Hardware_B.ginv[2] = -Hardware_B.x_tmp_cx;
  Hardware_B.ginv[10] = Hardware_B.x_tmp_b * Hardware_B.x_tmp;
  Hardware_B.ginv[18] = Hardware_B.x_tmp_k * Hardware_B.x_tmp_b;
  Hardware_B.ginv[26] = 0.0;
  Hardware_B.ginv[34] = 0.0;
  Hardware_B.ginv[42] = 0.0;
  Hardware_B.ginv[3] = 0.0;
  Hardware_B.ginv[11] = 0.0;
  Hardware_B.ginv[19] = 0.0;
  Hardware_B.ginv[27] = 1.0;
  Hardware_B.ginv[35] = Hardware_B.x_tmp * Hardware_B.smax;
  Hardware_B.ginv[43] = Hardware_B.x_tmp_k * Hardware_B.smax;
  Hardware_B.ginv[4] = 0.0;
  Hardware_B.ginv[12] = 0.0;
  Hardware_B.ginv[20] = 0.0;
  Hardware_B.ginv[28] = 0.0;
  Hardware_B.ginv[36] = Hardware_B.x_tmp_k;
  Hardware_B.ginv[44] = -Hardware_B.x_tmp;
  Hardware_B.ginv[5] = 0.0;
  Hardware_B.ginv[13] = 0.0;
  Hardware_B.ginv[21] = 0.0;
  Hardware_B.ginv[29] = 0.0;
  Hardware_B.rtb_ginv_tmp_i = 1.0 / Hardware_B.x_tmp_b;
  Hardware_B.ginv[37] = Hardware_B.rtb_ginv_tmp_i * Hardware_B.x_tmp;
  Hardware_B.ginv[45] = Hardware_B.rtb_ginv_tmp_i * Hardware_B.x_tmp_k;
  Hardware_B.ginv[54] = 1.0;
  Hardware_B.ginv[55] = 0.0;
  Hardware_B.ginv[62] = 0.0;
  Hardware_B.ginv[63] = 1.0;
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    Hardware_B.ipiv[Hardware_B.c_j] = static_cast<int8_T>(Hardware_B.c_j + 1);
  }

  for (Hardware_B.c_j = 0; Hardware_B.c_j < 7; Hardware_B.c_j++) {
    Hardware_B.jj = Hardware_B.c_j * 9;
    i = 9 - Hardware_B.c_j;
    jA = 0;
    Hardware_B.smax = fabs(Hardware_B.ginv[Hardware_B.jj]);
    for (Hardware_B.d_k = 2; Hardware_B.d_k < i; Hardware_B.d_k++) {
      Hardware_B.s = fabs(Hardware_B.ginv[(Hardware_B.jj + Hardware_B.d_k) - 1]);
      if (Hardware_B.s > Hardware_B.smax) {
        jA = Hardware_B.d_k - 1;
        Hardware_B.smax = Hardware_B.s;
      }
    }

    if (Hardware_B.ginv[Hardware_B.jj + jA] != 0.0) {
      if (jA != 0) {
        i = Hardware_B.c_j + jA;
        Hardware_B.ipiv[Hardware_B.c_j] = static_cast<int8_T>(i + 1);
        for (jA = 0; jA < 8; jA++) {
          Hardware_B.kAcol = jA << 3;
          Hardware_B.d_k = Hardware_B.kAcol + Hardware_B.c_j;
          Hardware_B.smax = Hardware_B.ginv[Hardware_B.d_k];
          Hardware_B.kAcol += i;
          Hardware_B.ginv[Hardware_B.d_k] = Hardware_B.ginv[Hardware_B.kAcol];
          Hardware_B.ginv[Hardware_B.kAcol] = Hardware_B.smax;
        }
      }

      i = (Hardware_B.jj - Hardware_B.c_j) + 8;
      for (jA = Hardware_B.jj + 2; jA <= i; jA++) {
        Hardware_B.ginv[jA - 1] /= Hardware_B.ginv[Hardware_B.jj];
      }
    }

    i = 6 - Hardware_B.c_j;
    jA = Hardware_B.jj + 10;
    for (Hardware_B.d_k = 0; Hardware_B.d_k <= i; Hardware_B.d_k++) {
      Hardware_B.D17 = Hardware_B.ginv[((Hardware_B.d_k << 3) + Hardware_B.jj) +
        8];
      if (Hardware_B.D17 != 0.0) {
        Hardware_B.kAcol = (jA - Hardware_B.c_j) + 6;
        for (ijA = jA; ijA <= Hardware_B.kAcol; ijA++) {
          Hardware_B.ginv[ijA - 1] += Hardware_B.ginv[((Hardware_B.jj + ijA) -
            jA) + 1] * -Hardware_B.D17;
        }
      }

      jA += 8;
    }
  }

  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    Hardware_B.p[Hardware_B.c_j] = static_cast<int8_T>(Hardware_B.c_j + 1);
  }

  for (Hardware_B.c_j = 0; Hardware_B.c_j < 7; Hardware_B.c_j++) {
    ipiv = Hardware_B.ipiv[Hardware_B.c_j];
    if (ipiv > Hardware_B.c_j + 1) {
      Hardware_B.jj = Hardware_B.p[ipiv - 1];
      Hardware_B.p[ipiv - 1] = Hardware_B.p[Hardware_B.c_j];
      Hardware_B.p[Hardware_B.c_j] = static_cast<int8_T>(Hardware_B.jj);
    }
  }

  for (jA = 0; jA < 8; jA++) {
    Hardware_B.jj = (Hardware_B.p[jA] - 1) << 3;
    Hardware_B.BMinv[jA + Hardware_B.jj] = 1.0;
    for (Hardware_B.d_k = jA + 1; Hardware_B.d_k < 9; Hardware_B.d_k++) {
      Hardware_B.c_j = (Hardware_B.jj + Hardware_B.d_k) - 1;
      if (Hardware_B.BMinv[Hardware_B.c_j] != 0.0) {
        for (i = Hardware_B.d_k + 1; i < 9; i++) {
          Hardware_B.kAcol = (Hardware_B.jj + i) - 1;
          Hardware_B.BMinv[Hardware_B.kAcol] -= Hardware_B.ginv
            [(((Hardware_B.d_k - 1) << 3) + i) - 1] *
            Hardware_B.BMinv[Hardware_B.c_j];
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    jA = i << 3;
    for (Hardware_B.d_k = 7; Hardware_B.d_k >= 0; Hardware_B.d_k--) {
      Hardware_B.kAcol = Hardware_B.d_k << 3;
      Hardware_B.c_j = Hardware_B.d_k + jA;
      Hardware_B.D17 = Hardware_B.BMinv[Hardware_B.c_j];
      if (Hardware_B.D17 != 0.0) {
        Hardware_B.BMinv[Hardware_B.c_j] = Hardware_B.D17 /
          Hardware_B.ginv[Hardware_B.d_k + Hardware_B.kAcol];
        for (ijA = 0; ijA < Hardware_B.d_k; ijA++) {
          Hardware_B.jj = ijA + jA;
          Hardware_B.BMinv[Hardware_B.jj] -= Hardware_B.ginv[ijA +
            Hardware_B.kAcol] * Hardware_B.BMinv[Hardware_B.c_j];
        }
      }
    }
  }

  // End of MATLAB Function: '<S2>/GetBInvMatrix'

  // MATLAB Function: '<S9>/MATLAB Function1' incorporates:
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'

  Hardware_B.smax = sin(Hardware_DW.DiscreteTimeIntegrator_DSTATE[6]);
  Hardware_B.D14_tmp = cos(Hardware_DW.DiscreteTimeIntegrator_DSTATE[7]);
  Hardware_B.s = sin(Hardware_DW.DiscreteTimeIntegrator_DSTATE[7]);
  Hardware_B.D14_tmp_tmp = Hardware_DW.DiscreteTimeIntegrator_DSTATE[6] +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.D14_tmp_p = sin(Hardware_B.D14_tmp_tmp);
  Hardware_B.D14_tmp_c = cos(Hardware_DW.DiscreteTimeIntegrator_DSTATE[6]);
  Hardware_B.D14_tmp_f = cos(Hardware_B.D14_tmp_tmp);
  Hardware_B.D14_tmp_o = Hardware_P.ArmConstants.MC2 *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D14_tmp_tmp_c = Hardware_P.ArmConstants.MC1 *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.D14_tmp_n = Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 + Hardware_B.D14_tmp_tmp_c;
  Hardware_B.D14_tmp_m = Hardware_P.ArmConstants.Mass1 +
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D14_tmp_cz = Hardware_B.D14_tmp_o * Hardware_B.D14_tmp +
    Hardware_B.D14_tmp_n;
  Hardware_B.D14_tmp_md = Hardware_B.D14_tmp_m *
    Hardware_P.ArmConstants.Hexa_to_joint_L;
  Hardware_B.D14_tmp_m3 = Hardware_B.D14_tmp_o * Hardware_B.D14_tmp_f;
  Hardware_B.D14_tmp_tmp_cg = Hardware_B.D14_tmp_n * Hardware_B.smax;
  Hardware_B.D14_tmp_tmp_f = Hardware_B.D14_tmp_o * Hardware_B.D14_tmp_p;
  Hardware_B.D14_tmp_j = Hardware_B.D14_tmp_tmp_cg + Hardware_B.D14_tmp_tmp_f;
  Hardware_B.D14_tmp_h = Hardware_B.D14_tmp_j * Hardware_B.x_tmp_c;
  Hardware_B.D14_tmp_ch = Hardware_B.D14_tmp_cz * Hardware_B.DigitalClock;
  Hardware_B.D14_tmp_nb = Hardware_B.D14_tmp_o * Hardware_B.x_tmp_c;
  Hardware_B.D14_tmp_i = Hardware_B.D14_tmp_o * Hardware_B.DigitalClock *
    Hardware_B.s * Hardware_B.x_tmp_cx;
  Hardware_B.D14_tmp_jg = (-Hardware_B.D14_tmp_cz * Hardware_B.x_tmp_c +
    Hardware_B.D14_tmp_i) * Hardware_B.x_tmp_k;
  Hardware_B.D14_tmp_js = Hardware_B.D14_tmp_m *
    -Hardware_P.ArmConstants.Hexa_to_joint_L;
  Hardware_B.D14 = (((Hardware_B.D14_tmp_nb * Hardware_B.smax * Hardware_B.s +
                      Hardware_B.D14_tmp_js * Hardware_B.x_tmp_c) +
                     Hardware_B.D14_tmp_ch * Hardware_B.smax *
                     Hardware_B.x_tmp_cx) * Hardware_B.x_tmp_k +
                    ((Hardware_B.D14_tmp_md + Hardware_B.D14_tmp_m3) *
                     Hardware_B.DigitalClock * Hardware_B.x_tmp_cx +
                     Hardware_B.D14_tmp_h) * Hardware_B.x_tmp) +
    (Hardware_B.D14_tmp_n * Hardware_B.DigitalClock * Hardware_B.x_tmp *
     Hardware_B.x_tmp_cx + Hardware_B.D14_tmp_jg) * Hardware_B.D14_tmp_c;
  Hardware_B.D15_tmp_tmp = Hardware_DW.DiscreteTimeIntegrator_DSTATE[3] +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[6];
  Hardware_B.D15_tmp = cos(Hardware_B.D15_tmp_tmp);
  Hardware_B.D15_tmp_tmp_o = Hardware_B.D15_tmp_tmp +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.D15_tmp_g = cos(Hardware_B.D15_tmp_tmp_o);
  Hardware_B.D15_tmp_tmp_d = Hardware_B.D14_tmp_n * Hardware_B.D15_tmp;
  Hardware_B.D15_tmp_tmp_n = Hardware_B.D14_tmp_o * Hardware_B.D15_tmp_g;
  Hardware_B.D15_tmp_a = (Hardware_B.D14_tmp_md * Hardware_B.x_tmp_k +
    Hardware_B.D15_tmp_tmp_d) + Hardware_B.D15_tmp_tmp_n;
  Hardware_B.D15 = Hardware_B.D15_tmp_a * -Hardware_B.DigitalClock *
    Hardware_B.x_tmp_b;
  Hardware_B.D16_tmp_tmp = Hardware_B.D14_tmp_n * Hardware_B.D14_tmp_c;
  Hardware_B.D16_tmp = (Hardware_B.D16_tmp_tmp + Hardware_B.D14_tmp_md) +
    Hardware_B.D14_tmp_m3;
  Hardware_B.D16_tmp_e = Hardware_B.D16_tmp * Hardware_B.DigitalClock;
  Hardware_B.D16_tmp_m = Hardware_B.D16_tmp * Hardware_B.x_tmp_c;
  Hardware_B.D16_tmp_m0 = Hardware_B.D16_tmp_m * Hardware_B.x_tmp_cx;
  Hardware_B.D16_tmp_j = Hardware_B.D14_tmp_h * Hardware_B.x_tmp_cx +
    Hardware_B.D16_tmp_e;
  Hardware_B.D16 = (Hardware_B.D14_tmp_j * -Hardware_B.DigitalClock +
                    Hardware_B.D16_tmp_m0) * Hardware_B.x_tmp_k +
    Hardware_B.D16_tmp_j * -Hardware_B.x_tmp;
  Hardware_B.D17_tmp = Hardware_P.ArmConstants.MC2 * Hardware_B.D14_tmp_p;
  Hardware_B.D17_tmp_p = Hardware_P.ArmConstants.MC2 * Hardware_B.D14_tmp_f;
  Hardware_B.D17_tmp_a = Hardware_P.ArmConstants.l1_dim * Hardware_B.D14_tmp_c;
  Hardware_B.D17_tmp_e = Hardware_P.ArmConstants.l1_dim * Hardware_B.smax +
    Hardware_B.D17_tmp;
  Hardware_B.D17_tmp_i = Hardware_B.D17_tmp_e * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D17_tmp_a4 = Hardware_B.D17_tmp_a + Hardware_B.D17_tmp_p;
  Hardware_B.D17_tmp_tmp = Hardware_B.x_tmp_c * Hardware_B.smax;
  Hardware_B.D17_tmp_tmp_p = Hardware_B.DigitalClock * Hardware_B.D14_tmp_c;
  Hardware_B.D17_tmp_o = Hardware_B.D17_tmp_tmp_p * Hardware_B.x_tmp_cx +
    Hardware_B.D17_tmp_tmp;
  Hardware_B.D17_tmp_j = Hardware_B.DigitalClock * Hardware_B.smax *
    Hardware_B.x_tmp_cx + -Hardware_B.D14_tmp_c * Hardware_B.x_tmp_c;
  Hardware_B.D17 = ((Hardware_B.D14_tmp_tmp_c * Hardware_B.x_tmp *
                     Hardware_B.D17_tmp_o + Hardware_B.D17_tmp_i *
                     Hardware_B.rtb_ginv_tmp_c) + Hardware_B.D17_tmp_a4 *
                    Hardware_P.ArmConstants.Mass2 * Hardware_B.rtb_ginv_tmp_p) +
    Hardware_B.D14_tmp_tmp_c * Hardware_B.x_tmp_k * Hardware_B.D17_tmp_j;
  Hardware_B.D18_tmp = Hardware_B.rtb_ginv_tmp_c * Hardware_B.D17_tmp +
    Hardware_B.rtb_ginv_tmp_p * Hardware_B.D17_tmp_p;
  Hardware_B.D18 = Hardware_B.D18_tmp * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D24_tmp = Hardware_P.ArmConstants.MC1 * Hardware_B.D14_tmp_c +
    Hardware_P.ArmConstants.Hexa_to_joint_L;
  Hardware_B.D24_tmp_a = (Hardware_B.D17_tmp_a +
    Hardware_P.ArmConstants.Hexa_to_joint_L) + Hardware_B.D17_tmp_p;
  Hardware_B.D24_tmp_j = Hardware_B.rtb_ginv_tmp_p * Hardware_B.D17_tmp_e;
  Hardware_B.D17_tmp_a = Hardware_B.x_tmp_b * Hardware_B.x_tmp_b;
  Hardware_B.D24_tmp_jr = Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_B.x_tmp_k;
  Hardware_B.D24_tmp_c = (Hardware_P.ArmConstants.l1_dim * Hardware_B.D15_tmp +
    Hardware_B.D24_tmp_jr) + Hardware_P.ArmConstants.MC2 * Hardware_B.D15_tmp_g;
  Hardware_B.D24 = (((Hardware_B.D24_tmp * Hardware_B.x_tmp_c *
                      Hardware_B.x_tmp_cx + -Hardware_P.ArmConstants.MC1 *
                      Hardware_B.DigitalClock * Hardware_B.smax) *
                     (Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp) +
                     Hardware_P.ArmConstants.Mass2 * Hardware_B.DigitalClock *
                     Hardware_B.D24_tmp_c * Hardware_B.D17_tmp_a) +
                    (Hardware_P.ArmConstants.MC1 * Hardware_B.x_tmp_c *
                     Hardware_B.smax * Hardware_B.x_tmp_cx + Hardware_B.D24_tmp *
                     Hardware_B.DigitalClock) * (Hardware_P.ArmConstants.Mass1 *
    Hardware_B.x_tmp_k)) + (Hardware_B.D24_tmp_a * Hardware_B.rtb_ginv_tmp_c -
    Hardware_B.D24_tmp_j) * (Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_cx);
  Hardware_B.D25 = -Hardware_B.D15_tmp_a * Hardware_B.x_tmp_b *
    Hardware_B.x_tmp_c;
  Hardware_B.D26 = ((Hardware_B.D24_tmp * -Hardware_P.ArmConstants.Mass1 *
                     Hardware_B.rtb_ginv_tmp_c - Hardware_B.D24_tmp_a *
                     Hardware_P.ArmConstants.Mass2 * Hardware_B.rtb_ginv_tmp_c)
                    + Hardware_B.D14_tmp_tmp_c * Hardware_B.smax *
                    Hardware_B.rtb_ginv_tmp_p) + Hardware_B.D17_tmp_i *
    Hardware_B.rtb_ginv_tmp_p;
  Hardware_B.D14_tmp_tmp_c = Hardware_B.rtb_ginv_tmp_tmp -
    Hardware_B.rtb_ginv_tmp_n;
  Hardware_B.D27_tmp = Hardware_B.D16_tmp_tmp * Hardware_B.rtb_ginv_tmp_o;
  Hardware_B.D27_tmp_a = Hardware_B.rtb_ginv_tmp_o * Hardware_B.D14_tmp_m3;
  Hardware_B.D27 = (-Hardware_B.D14_tmp_j * Hardware_B.D14_tmp_tmp_c +
                    Hardware_B.D27_tmp) + Hardware_B.D27_tmp_a;
  Hardware_B.D17_tmp = Hardware_B.rtb_ginv_tmp_l * Hardware_B.D17_tmp +
    Hardware_B.rtb_ginv_tmp_o * Hardware_B.D17_tmp_p;
  Hardware_B.D28 = Hardware_B.D17_tmp * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D17_tmp_p = sin(Hardware_B.D15_tmp_tmp);
  Hardware_B.D17_tmp_i = sin(Hardware_B.D15_tmp_tmp_o);
  Hardware_B.D34_tmp = Hardware_B.D14_tmp_n * Hardware_B.D17_tmp_p;
  Hardware_B.D34_tmp_o = Hardware_B.D14_tmp_o * Hardware_B.D17_tmp_i;
  Hardware_B.D34_tmp_m = (Hardware_B.D14_tmp_md * Hardware_B.x_tmp +
    Hardware_B.D34_tmp) + Hardware_B.D34_tmp_o;
  Hardware_B.D34 = Hardware_B.D34_tmp_m * Hardware_B.x_tmp_b;
  Hardware_B.D35 = Hardware_B.D15_tmp_a * Hardware_B.x_tmp_cx;
  Hardware_B.D37_tmp = Hardware_B.D34_tmp + Hardware_B.D34_tmp_o;
  Hardware_B.D37 = Hardware_B.D37_tmp * Hardware_B.x_tmp_b;
  Hardware_B.D38 = Hardware_B.D14_tmp_o * Hardware_B.x_tmp_b *
    Hardware_B.D17_tmp_i;
  Hardware_B.D45_tmp = Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D15_tmp_g;
  Hardware_B.D45_tmp_a = Hardware_P.ArmConstants.Inertia2[6] *
    Hardware_B.D17_tmp_i;
  Hardware_B.D45 = ((Hardware_P.ArmConstants.Inertia1[7] * Hardware_B.D15_tmp +
                     Hardware_B.D45_tmp) + Hardware_P.ArmConstants.Inertia1[6] *
                    Hardware_B.D17_tmp_p) + Hardware_B.D45_tmp_a;
  Hardware_B.D46_tmp_tmp_m4 = Hardware_DW.DiscreteTimeIntegrator_DSTATE[6] -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp = sin(Hardware_B.D46_tmp_tmp_m4);
  Hardware_B.D46_tmp_tmp_c = Hardware_DW.DiscreteTimeIntegrator_DSTATE[4] +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[6];
  Hardware_B.D46_tmp_g = sin(Hardware_B.D46_tmp_tmp_c);
  Hardware_B.D46_tmp_tmp = Hardware_B.D15_tmp_tmp -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp_m = cos(Hardware_B.D46_tmp_tmp);
  Hardware_B.D46_tmp_tmp_i = Hardware_B.D15_tmp_tmp_o -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp_n = cos(Hardware_B.D46_tmp_tmp_i);
  Hardware_B.D46_tmp_tmp_f = Hardware_B.D15_tmp_tmp +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp_p = cos(Hardware_B.D46_tmp_tmp_f);
  Hardware_B.D46_tmp_tmp_iz = Hardware_B.D15_tmp_tmp_o +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp_l = cos(Hardware_B.D46_tmp_tmp_iz);
  Hardware_B.D46_tmp_j = sin(Hardware_B.D46_tmp_tmp);
  Hardware_B.D46_tmp_ld = sin(Hardware_B.D46_tmp_tmp_i);
  Hardware_B.D46_tmp_lx = sin(Hardware_B.D46_tmp_tmp_f);
  Hardware_B.D46_tmp_nu = sin(Hardware_B.D46_tmp_tmp_iz);
  Hardware_B.D46_tmp_tmp_ad = Hardware_DW.DiscreteTimeIntegrator_DSTATE[7] -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.rtb_ginv_tmp_i = sin(Hardware_B.D46_tmp_tmp_ad);
  Hardware_B.D46_tmp_tmp_k = Hardware_B.D14_tmp_tmp -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp_ln = sin(Hardware_B.D46_tmp_tmp_k);
  Hardware_B.D46_tmp_tmp_pc = Hardware_DW.DiscreteTimeIntegrator_DSTATE[4] +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.D46_tmp_h = sin(Hardware_B.D46_tmp_tmp_pc);
  Hardware_B.D46_tmp_tmp_b = Hardware_B.D14_tmp_tmp +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp_b = sin(Hardware_B.D46_tmp_tmp_b);
  Hardware_B.D46_tmp_f = 2.0 * Hardware_P.ArmConstants.MC2;
  Hardware_B.D46_tmp_tmp_m = Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.Hexa_to_joint_L;
  Hardware_B.D46_tmp_gx = Hardware_B.D46_tmp_tmp_m * -2.0;
  Hardware_B.D46_tmp_c = -2.0 * Hardware_P.ArmConstants.MC2;
  Hardware_B.D46_tmp_o = Hardware_P.ArmConstants.MC1 *
    Hardware_P.ArmConstants.MC1;
  Hardware_B.D46_tmp_lm = Hardware_P.ArmConstants.MC2 *
    Hardware_P.ArmConstants.MC2;
  Hardware_B.D46_tmp_mv = Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.l1_dim;
  Hardware_B.D46_tmp_mj = Hardware_B.D46_tmp_f * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_tmp_g = 2.0 * Hardware_P.ArmConstants.MC1;
  Hardware_B.D46_tmp_mc = Hardware_B.D46_tmp_tmp_g *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D46_tmp_tmp_p = 2.0 * Hardware_P.ArmConstants.Hexa_to_joint_L;
  Hardware_B.D46_tmp_h3 = Hardware_B.D46_tmp_tmp_p *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_pc = Hardware_B.D46_tmp_f *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_tmp_a = Hardware_P.ArmConstants.Inertia2[6] *
    Hardware_B.D46_tmp_l;
  Hardware_B.D46_tmp_e = ((-Hardware_P.ArmConstants.Inertia1[6] *
    Hardware_B.D46_tmp_m - Hardware_P.ArmConstants.Inertia2[6] *
    Hardware_B.D46_tmp_n) - Hardware_P.ArmConstants.Inertia1[6] *
    Hardware_B.D46_tmp_p) - Hardware_B.D46_tmp_tmp_a;
  Hardware_B.D46_tmp_ol = Hardware_P.ArmConstants.Inertia1[7] *
    Hardware_B.D46_tmp_j;
  Hardware_B.D46_tmp_bb = Hardware_B.D46_tmp_mj * Hardware_B.rtb_ginv_tmp_i;
  Hardware_B.D46_tmp_a = Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D46_tmp_ld;
  Hardware_B.D46_tmp_g2 = -2.0 * Hardware_P.ArmConstants.Inertia1[8] *
    Hardware_B.x_tmp_cx;
  Hardware_B.D46_tmp_ex = -2.0 * Hardware_P.ArmConstants.Inertia2[8] *
    Hardware_B.x_tmp_cx;
  Hardware_B.D46_tmp_tmp_cj = Hardware_B.D46_tmp_o * -2.0;
  Hardware_B.D46_tmp_fi = Hardware_B.D46_tmp_tmp_cj *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp_cx;
  Hardware_B.D46_tmp_tmp_m1 = Hardware_B.D46_tmp_lm * -2.0;
  Hardware_B.D46_tmp_h2 = Hardware_B.D46_tmp_tmp_m1 *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_cx;
  Hardware_B.D46_tmp_ei = Hardware_B.D46_tmp_mv * -2.0 *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_cx;
  Hardware_B.D46_tmp_ch = Hardware_P.ArmConstants.Inertia1[7] *
    Hardware_B.D46_tmp_lx;
  Hardware_B.D46_tmp_tmp_pr = Hardware_B.D46_tmp_c *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_ax = Hardware_B.D46_tmp_tmp_pr * Hardware_B.D46_tmp_h;
  Hardware_B.D46_tmp_d = Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D46_tmp_nu;
  Hardware_B.D46_tmp_nr = -2.0 * Hardware_P.ArmConstants.MC1;
  Hardware_B.D46_tmp_jp = Hardware_B.D46_tmp_nr *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D46_tmp_k = -2.0 * Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_mx = Hardware_B.D46_tmp_c *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46 = ((((((((((((((((((((Hardware_B.D46_tmp_mc *
    Hardware_B.D46_tmp + Hardware_B.D46_tmp_e) + Hardware_B.D46_tmp_h3 *
    Hardware_B.D46_tmp) + Hardware_B.D46_tmp_ol) + Hardware_B.D46_tmp_bb) +
    Hardware_B.D46_tmp_pc * Hardware_B.D46_tmp_ln) + Hardware_B.D46_tmp_a) +
    Hardware_B.D46_tmp_g2) + Hardware_B.D46_tmp_ex) + -2.0 *
    Hardware_P.HexaConstants.Inertia[0] * Hardware_B.x_tmp_cx) +
    Hardware_B.D46_tmp_fi) + Hardware_B.D46_tmp_gx *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp_cx) + Hardware_B.D46_tmp_h2)
    + Hardware_B.D46_tmp_gx * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.x_tmp_cx) + Hardware_B.D46_tmp_ei) + Hardware_B.D46_tmp_jp *
    Hardware_B.D46_tmp_g) + Hardware_B.D46_tmp_k * Hardware_B.D46_tmp_g) +
                       Hardware_B.D46_tmp_ch) + Hardware_B.D46_tmp_ax) +
                     Hardware_B.D46_tmp_mx * Hardware_B.D46_tmp_b) +
                    Hardware_B.D46_tmp_d) * 0.5;
  Hardware_B.D47_tmp = Hardware_B.D46_tmp_lm * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D47_tmp_tmp = Hardware_P.ArmConstants.MC2 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_gx = Hardware_B.D47_tmp_tmp * Hardware_B.D14_tmp_f;
  Hardware_B.D47_tmp_c = Hardware_B.D46_tmp_o * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D47_tmp_k = Hardware_B.D46_tmp_mv * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D47_tmp_l = Hardware_P.ArmConstants.Inertia1[8] +
    Hardware_P.ArmConstants.Inertia2[8];
  Hardware_B.D47_tmp_p = Hardware_B.D46_tmp_mj * Hardware_B.D14_tmp;
  Hardware_B.D47_tmp_i = ((Hardware_B.D47_tmp_c + Hardware_B.D47_tmp_l) +
    Hardware_B.D47_tmp) + Hardware_B.D47_tmp_k;
  Hardware_B.D47_tmp_d = Hardware_B.D14_tmp_n *
    Hardware_P.ArmConstants.Hexa_to_joint_L;
  Hardware_B.D47_tmp_l0 = Hardware_B.D47_tmp_d * Hardware_B.D14_tmp_c +
    Hardware_B.D47_tmp_i;
  Hardware_B.D47 = (Hardware_B.D47_tmp_l0 + Hardware_B.D47_tmp_p) +
    Hardware_B.D46_tmp_gx;
  Hardware_B.D48_tmp = Hardware_P.ArmConstants.MC2 *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D48_tmp_tmp = Hardware_B.D47_tmp +
    Hardware_P.ArmConstants.Inertia2[8];
  Hardware_B.D48_tmp_p = Hardware_B.D48_tmp * Hardware_B.D14_tmp +
    Hardware_B.D48_tmp_tmp;
  Hardware_B.D48 = Hardware_B.D48_tmp_p + Hardware_B.D46_tmp_gx;
  Hardware_B.D56_tmp_tmp = 2.0 * Hardware_DW.DiscreteTimeIntegrator_DSTATE[3];
  Hardware_B.D56_tmp_tmp_hc = Hardware_B.D56_tmp_tmp -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp = sin(Hardware_B.D56_tmp_tmp_hc);
  Hardware_B.D56_tmp_tmp_f = Hardware_B.D56_tmp_tmp +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[6];
  Hardware_B.D56_tmp_tmp_oc = Hardware_B.D56_tmp_tmp_f -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_d = sin(Hardware_B.D56_tmp_tmp_oc);
  Hardware_B.D56_tmp_tmp_tmp = 2.0 * Hardware_DW.DiscreteTimeIntegrator_DSTATE[6];
  Hardware_B.D56_tmp_tmp_c = Hardware_B.D56_tmp_tmp + Hardware_B.D56_tmp_tmp_tmp;
  Hardware_B.D56_tmp_tmp_e = Hardware_B.D56_tmp_tmp_c -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_g = sin(Hardware_B.D56_tmp_tmp_e);
  Hardware_B.D56_tmp_tmp_p = 2.0 * Hardware_DW.DiscreteTimeIntegrator_DSTATE[7]
    + Hardware_B.D56_tmp_tmp_c;
  Hardware_B.D56_tmp_tmp_o = Hardware_B.D56_tmp_tmp_p -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_dh = sin(Hardware_B.D56_tmp_tmp_o);
  Hardware_B.D56_tmp_tmp_m = Hardware_B.D56_tmp_tmp +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_dy = sin(Hardware_B.D56_tmp_tmp_m);
  Hardware_B.D56_tmp_tmp_fb = Hardware_B.D56_tmp_tmp_f +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_o = sin(Hardware_B.D56_tmp_tmp_fb);
  Hardware_B.D56_tmp_tmp_h = Hardware_B.D56_tmp_tmp_c +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_b = sin(Hardware_B.D56_tmp_tmp_h);
  Hardware_B.D56_tmp_tmp_p += Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_bs = sin(Hardware_B.D56_tmp_tmp_p);
  Hardware_B.D56_tmp_da = cos(Hardware_B.D56_tmp_tmp_e);
  Hardware_B.D56_tmp_e = cos(Hardware_B.D56_tmp_tmp_o);
  Hardware_B.D56_tmp_bj = cos(Hardware_B.D56_tmp_tmp_h);
  Hardware_B.D56_tmp_j = cos(Hardware_B.D56_tmp_tmp_p);
  Hardware_B.D56_tmp_tmp_e = Hardware_B.D56_tmp_tmp_f +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.D56_tmp_tmp_p = Hardware_B.D56_tmp_tmp_e -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_f = sin(Hardware_B.D56_tmp_tmp_p);
  Hardware_B.D56_tmp_tmp_c += Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.D56_tmp_tmp_o = Hardware_B.D56_tmp_tmp_c -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_a = sin(Hardware_B.D56_tmp_tmp_o);
  Hardware_B.D56_tmp_tmp_h = Hardware_B.D56_tmp_tmp_e +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_ju = sin(Hardware_B.D56_tmp_tmp_h);
  Hardware_B.D56_tmp_tmp_c += Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_jz = sin(Hardware_B.D56_tmp_tmp_c);
  Hardware_B.D56_tmp_l = -2.0 * Hardware_P.ArmConstants.Inertia1[3];
  Hardware_B.D56_tmp_h = -2.0 * Hardware_P.ArmConstants.Inertia2[3];
  Hardware_B.D56_tmp_p = Hardware_B.D46_tmp_tmp_m *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.D56_tmp_p4 = Hardware_B.D46_tmp_tmp_m *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D56_tmp_pm = 2.0 * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.D56_tmp_p2 = 2.0 * Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.D56_tmp_n = -2.0 * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.D56_tmp_k = -2.0 * Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.D56_tmp_n3 = 2.0 * Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.D56_tmp_oy = 2.0 * Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.D56_tmp_gg = -2.0 * Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.D56_tmp_c = -2.0 * Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.D56_tmp_tmp_ob = Hardware_P.HexaConstants.Inertia[4] *
    Hardware_B.D56_tmp;
  Hardware_B.D56_tmp_tmp_l = Hardware_P.HexaConstants.Inertia[8] *
    Hardware_B.D56_tmp;
  Hardware_B.D56_tmp_tmp_k = Hardware_B.D56_tmp_p * Hardware_B.D56_tmp;
  Hardware_B.D56_tmp_tmp_j = Hardware_B.D56_tmp_p4 * Hardware_B.D56_tmp;
  Hardware_B.D56_tmp_tmp_fz = Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_B.D56_tmp_g;
  Hardware_B.D56_tmp_tmp_cm = Hardware_P.ArmConstants.Inertia1[4] *
    Hardware_B.D56_tmp_g;
  Hardware_B.D56_tmp_tmp_fq = Hardware_B.D47_tmp_c * Hardware_B.D56_tmp_g;
  Hardware_B.D56_tmp_tmp_n = Hardware_B.D47_tmp_k * Hardware_B.D56_tmp_g;
  Hardware_B.D56_tmp_tmp_i = Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_B.D56_tmp_dh;
  Hardware_B.D56_tmp_tmp_l4 = Hardware_P.ArmConstants.Inertia2[4] *
    Hardware_B.D56_tmp_dh;
  Hardware_B.D56_tmp_tmp_i3 = Hardware_B.D47_tmp * Hardware_B.D56_tmp_dh;
  Hardware_B.D56_tmp_tmp_k1 = Hardware_P.HexaConstants.Inertia[4] *
    Hardware_B.D56_tmp_dy;
  Hardware_B.D56_tmp_tmp_fc = Hardware_P.HexaConstants.Inertia[8] *
    Hardware_B.D56_tmp_dy;
  Hardware_B.D56_tmp_tmp_a = Hardware_B.D56_tmp_p * Hardware_B.D56_tmp_dy;
  Hardware_B.D56_tmp_tmp_d = Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_B.D56_tmp_b;
  Hardware_B.D56_tmp_tmp_ey = Hardware_P.ArmConstants.Inertia1[4] *
    Hardware_B.D56_tmp_b;
  Hardware_B.D56_tmp_tmp_eh = Hardware_B.D47_tmp_c * Hardware_B.D56_tmp_b;
  Hardware_B.D56_tmp_tmp_b = Hardware_B.D47_tmp_k * Hardware_B.D56_tmp_b;
  Hardware_B.D56_tmp =
    (((((((((((((((((((((((((((((((((((((Hardware_B.D56_tmp_gg *
    Hardware_B.D46_tmp_m + Hardware_B.D56_tmp_l * Hardware_B.D56_tmp_da) +
    Hardware_B.D56_tmp_c * Hardware_B.D46_tmp_n) + Hardware_B.D56_tmp_h *
    Hardware_B.D56_tmp_e) + Hardware_B.D56_tmp_n3 * Hardware_B.D46_tmp_p) +
    Hardware_B.D56_tmp_l * Hardware_B.D56_tmp_bj) + Hardware_B.D56_tmp_oy *
    Hardware_B.D46_tmp_l) + Hardware_B.D56_tmp_h * Hardware_B.D56_tmp_j) +
    Hardware_B.D56_tmp_tmp_ob) - Hardware_B.D56_tmp_tmp_l) +
    Hardware_B.D56_tmp_tmp_k) + Hardware_B.D56_tmp_tmp_j) +
    Hardware_B.D56_tmp_pm * Hardware_B.D46_tmp_j) + Hardware_B.D46_tmp_mc *
    Hardware_B.D56_tmp_d) + Hardware_B.D46_tmp_h3 * Hardware_B.D56_tmp_d) -
    Hardware_B.D56_tmp_tmp_fz) + Hardware_B.D56_tmp_tmp_cm) +
    Hardware_B.D56_tmp_tmp_fq) + Hardware_B.D56_tmp_tmp_n) +
                       Hardware_B.D56_tmp_p2 * Hardware_B.D46_tmp_ld) +
                      Hardware_B.D46_tmp_pc * Hardware_B.D56_tmp_f) +
                     Hardware_B.D46_tmp_mj * Hardware_B.D56_tmp_a) -
                    Hardware_B.D56_tmp_tmp_i) + Hardware_B.D56_tmp_tmp_l4) +
                  Hardware_B.D56_tmp_tmp_i3) + Hardware_B.D56_tmp_tmp_k1) -
                Hardware_B.D56_tmp_tmp_fc) + Hardware_B.D56_tmp_tmp_a) +
              Hardware_B.D56_tmp_p4 * Hardware_B.D56_tmp_dy) +
             Hardware_B.D56_tmp_n * Hardware_B.D46_tmp_lx) +
            Hardware_B.D46_tmp_mc * Hardware_B.D56_tmp_o) +
           Hardware_B.D46_tmp_h3 * Hardware_B.D56_tmp_o) -
          Hardware_B.D56_tmp_tmp_d) + Hardware_B.D56_tmp_tmp_ey) +
        Hardware_B.D56_tmp_tmp_eh) + Hardware_B.D56_tmp_tmp_b) +
      Hardware_B.D56_tmp_k * Hardware_B.D46_tmp_nu) + Hardware_B.D46_tmp_pc *
     Hardware_B.D56_tmp_ju) + Hardware_B.D46_tmp_mj * Hardware_B.D56_tmp_jz;
  Hardware_B.D56_tmp_g4 = Hardware_P.ArmConstants.Inertia2[4] *
    Hardware_B.D56_tmp_bs;
  Hardware_B.D56_tmp_c3 = Hardware_B.D47_tmp * Hardware_B.D56_tmp_bs;
  Hardware_B.D56 = (((-Hardware_P.ArmConstants.Inertia2[0] *
                      Hardware_B.D56_tmp_bs + Hardware_B.D56_tmp) +
                     Hardware_B.D56_tmp_g4) + Hardware_B.D56_tmp_c3) * 0.25;
  Hardware_B.D58 = Hardware_B.D45_tmp + Hardware_B.D45_tmp_a;
  Hardware_B.D45_tmp_a = Hardware_P.ArmConstants.MC1 * Hardware_B.smax;
  Hardware_B.D45_tmp = Hardware_B.rtb_ginv_tmp_c * -Hardware_B.D24_tmp +
    Hardware_B.rtb_ginv_tmp_p * Hardware_B.D45_tmp_a;
  Hardware_B.D24_tmp_j += -Hardware_B.D24_tmp_a * Hardware_B.rtb_ginv_tmp_c;
  Hardware_B.y_a = Hardware_B.D14_tmp_tmp_c * Hardware_B.D24_tmp +
    Hardware_B.rtb_ginv_tmp_o * Hardware_B.D45_tmp_a;
  Hardware_B.ab_a = Hardware_B.D24_tmp_a * Hardware_B.D14_tmp_tmp_c +
    Hardware_B.rtb_ginv_tmp_o * Hardware_B.D17_tmp_e;
  Hardware_B.D24_tmp = Hardware_P.ArmConstants.MC1 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D24_tmp_a = Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_ln *= Hardware_B.D47_tmp_tmp;
  Hardware_B.D46_tmp_b *= Hardware_B.D47_tmp_tmp;
  Hardware_B.D67 = (((((((((((((((((Hardware_B.D24_tmp * Hardware_B.D46_tmp +
    Hardware_B.D46_tmp_e) + Hardware_B.D24_tmp_a * Hardware_B.D46_tmp) +
    Hardware_B.D46_tmp_ol) + Hardware_B.D46_tmp_bb) + Hardware_B.D46_tmp_ln) +
    Hardware_B.D46_tmp_a) + Hardware_B.D46_tmp_g2) + Hardware_B.D46_tmp_ex) +
    Hardware_B.D46_tmp_fi) + Hardware_B.D46_tmp_h2) + Hardware_B.D46_tmp_ei) -
    Hardware_B.D24_tmp * Hardware_B.D46_tmp_g) - Hardware_B.D24_tmp_a *
                        Hardware_B.D46_tmp_g) + Hardware_B.D46_tmp_ch) +
                      Hardware_B.D46_tmp_ax) - Hardware_B.D46_tmp_b) +
                    Hardware_B.D46_tmp_d) * 0.5;
  Hardware_B.D46_tmp = -Hardware_P.ArmConstants.MC2 *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D68 = (((((((((-Hardware_P.ArmConstants.Inertia2[6] *
    Hardware_B.D46_tmp_n - Hardware_B.D46_tmp_tmp_a) + Hardware_B.D48_tmp *
    Hardware_B.rtb_ginv_tmp_i) + Hardware_B.D46_tmp_ln) + Hardware_B.D46_tmp_a)
                        + Hardware_B.D46_tmp_ex) + Hardware_B.D46_tmp_h2) +
                      Hardware_B.D46_tmp * Hardware_B.D46_tmp_h) -
                     Hardware_B.D46_tmp_b) + Hardware_B.D46_tmp_d) * 0.5;
  Hardware_B.rtb_ginv_tmp_n = cos(Hardware_B.D56_tmp_tmp);
  Hardware_B.rtb_ginv_tmp_tmp_o = Hardware_B.D15_tmp_tmp * 2.0;
  Hardware_B.rtb_ginv_tmp_i = cos(Hardware_B.rtb_ginv_tmp_tmp_o);
  Hardware_B.D46_tmp_h = cos(Hardware_B.D56_tmp_tmp_f);
  Hardware_B.rtb_ginv_tmp_tmp_n = Hardware_B.D15_tmp_tmp_o * 2.0;
  Hardware_B.D46_tmp_tmp_a = cos(Hardware_B.rtb_ginv_tmp_tmp_n);
  Hardware_B.D46_tmp_a = sin(Hardware_B.D56_tmp_tmp_tmp);
  Hardware_B.rtb_ginv_tmp_tmp_m = Hardware_B.D14_tmp_tmp * 2.0;
  Hardware_B.D46_tmp_ex = cos(Hardware_B.rtb_ginv_tmp_tmp_m);
  Hardware_B.D46_tmp_h2 = sin(Hardware_B.rtb_ginv_tmp_tmp_m);
  Hardware_B.rtb_ginv_tmp_tmp_m = 2.0 *
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D46_tmp_d = sin(Hardware_B.rtb_ginv_tmp_tmp_m);
  Hardware_B.D46_tmp_g = sin(Hardware_B.rtb_ginv_tmp_tmp_o);
  Hardware_B.D46_tmp_e = sin(Hardware_B.rtb_ginv_tmp_tmp_n);
  Hardware_B.rtb_ginv_tmp = cos(Hardware_B.D56_tmp_tmp_e);
  Hardware_B.rtb_ginv_tmp_tmp_o += Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.D46_tmp_ol = cos(Hardware_B.rtb_ginv_tmp_tmp_o);
  Hardware_B.D56_tmp_tmp_tmp = cos(Hardware_B.D56_tmp_tmp_tmp);
  Hardware_B.D46_tmp_bb = (Hardware_P.HexaConstants.Mass +
    Hardware_P.ArmConstants.Mass1) + Hardware_P.ArmConstants.Mass2;
  Hardware_B.ginv[0] = Hardware_B.D46_tmp_bb;
  Hardware_B.ginv[8] = 0.0;
  Hardware_B.ginv[16] = 0.0;
  Hardware_B.ginv[24] = Hardware_B.D14;
  Hardware_B.ginv[32] = Hardware_B.D15;
  Hardware_B.ginv[40] = Hardware_B.D16;
  Hardware_B.ginv[48] = Hardware_B.D17;
  Hardware_B.ginv[56] = Hardware_B.D18;
  Hardware_B.ginv[1] = 0.0;
  Hardware_B.ginv[9] = Hardware_B.D46_tmp_bb;
  Hardware_B.ginv[17] = 0.0;
  Hardware_B.ginv[25] = Hardware_B.D24;
  Hardware_B.ginv[33] = Hardware_B.D25;
  Hardware_B.ginv[41] = Hardware_B.D26;
  Hardware_B.ginv[49] = Hardware_B.D27;
  Hardware_B.ginv[57] = Hardware_B.D28;
  Hardware_B.ginv[2] = 0.0;
  Hardware_B.ginv[10] = 0.0;
  Hardware_B.ginv[18] = Hardware_B.D46_tmp_bb;
  Hardware_B.ginv[26] = Hardware_B.D34;
  Hardware_B.ginv[34] = Hardware_B.D35;
  Hardware_B.ginv[42] = 0.0;
  Hardware_B.ginv[50] = Hardware_B.D37;
  Hardware_B.ginv[58] = Hardware_B.D38;
  Hardware_B.ginv[3] = Hardware_B.D14;
  Hardware_B.ginv[11] = Hardware_B.D24;
  Hardware_B.ginv[19] = Hardware_B.D34;
  Hardware_B.rtb_ginv_tmp_tmp_n = Hardware_B.D14_tmp_n *
    Hardware_B.D46_tmp_tmp_p;
  Hardware_B.rtb_ginv_tmp_f = Hardware_B.rtb_ginv_tmp_tmp_n *
    Hardware_B.D14_tmp_c;
  Hardware_B.rtb_ginv_tmp_ie = Hardware_B.D46_tmp_pc * Hardware_B.D14_tmp_f;
  Hardware_B.rtb_ginv_tmp_cx = (((((Hardware_B.D47_tmp_l +
    Hardware_P.HexaConstants.Inertia[0]) + Hardware_B.D47_tmp_c) +
    Hardware_B.D56_tmp_p) + Hardware_B.D47_tmp) + Hardware_B.D56_tmp_p4) +
    Hardware_B.D47_tmp_k;
  Hardware_B.ginv[27] = ((Hardware_B.rtb_ginv_tmp_cx + Hardware_B.rtb_ginv_tmp_f)
    + Hardware_B.D47_tmp_p) + Hardware_B.rtb_ginv_tmp_ie;
  Hardware_B.ginv[35] = Hardware_B.D45;
  Hardware_B.ginv[43] = Hardware_B.D46;
  Hardware_B.ginv[51] = Hardware_B.D47;
  Hardware_B.ginv[59] = Hardware_B.D48;
  Hardware_B.ginv[4] = Hardware_B.D15;
  Hardware_B.ginv[12] = Hardware_B.D25;
  Hardware_B.ginv[20] = Hardware_B.D35;
  Hardware_B.ginv[28] = Hardware_B.D45;
  Hardware_B.D15 = 2.0 * Hardware_P.ArmConstants.Inertia2[3];
  Hardware_B.D25 = 2.0 * Hardware_P.ArmConstants.Inertia1[3];
  Hardware_B.rtb_ginv_tmp_if = Hardware_P.ArmConstants.Inertia1[4] *
    Hardware_B.rtb_ginv_tmp_i;
  Hardware_B.rtb_ginv_tmp_d = Hardware_B.D47_tmp_c * Hardware_B.rtb_ginv_tmp_i;
  Hardware_B.rtb_ginv_tmp_g = Hardware_B.D47_tmp_k * Hardware_B.rtb_ginv_tmp_i;
  Hardware_B.D14 = Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_B.D46_tmp_tmp_a;
  Hardware_B.D24 = Hardware_P.ArmConstants.Inertia2[4] *
    Hardware_B.D46_tmp_tmp_a;
  Hardware_B.D35 = Hardware_B.D47_tmp * Hardware_B.D46_tmp_tmp_a;
  Hardware_B.ginv[36] =
    ((((((((((((((((((((((((((((((Hardware_P.ArmConstants.Inertia1[0] +
    Hardware_P.ArmConstants.Inertia1[4]) + Hardware_P.ArmConstants.Inertia2[0])
    + Hardware_P.ArmConstants.Inertia2[4]) + Hardware_P.HexaConstants.Inertia[4])
    + Hardware_P.HexaConstants.Inertia[8]) + Hardware_B.D47_tmp_c) +
    Hardware_B.D56_tmp_p) + Hardware_B.D47_tmp) + Hardware_B.D56_tmp_p4) +
    Hardware_B.D47_tmp_k) + Hardware_P.HexaConstants.Inertia[4] *
    Hardware_B.rtb_ginv_tmp_n) - Hardware_P.HexaConstants.Inertia[8] *
                       Hardware_B.rtb_ginv_tmp_n) + Hardware_B.D56_tmp_p *
                      Hardware_B.rtb_ginv_tmp_n) + Hardware_B.D56_tmp_p4 *
                     Hardware_B.rtb_ginv_tmp_n) + Hardware_B.rtb_ginv_tmp_f) +
                   -Hardware_P.ArmConstants.Inertia1[0] *
                   Hardware_B.rtb_ginv_tmp_i) + Hardware_B.rtb_ginv_tmp_if) +
                 Hardware_B.rtb_ginv_tmp_d) + Hardware_B.rtb_ginv_tmp_g) +
               Hardware_B.D46_tmp_mc * Hardware_B.D46_tmp_h) +
              Hardware_B.D46_tmp_h3 * Hardware_B.D46_tmp_h) +
             Hardware_B.D47_tmp_p) + Hardware_B.rtb_ginv_tmp_ie) -
           Hardware_B.D14) + Hardware_B.D24) + Hardware_B.D35) +
        Hardware_B.D46_tmp_pc * Hardware_B.rtb_ginv_tmp) + Hardware_B.D46_tmp_mj
       * Hardware_B.D46_tmp_ol) + Hardware_B.D25 * Hardware_B.D46_tmp_g) +
     Hardware_B.D15 * Hardware_B.D46_tmp_e) * 0.5;
  Hardware_B.ginv[44] = Hardware_B.D56;
  Hardware_B.ginv[52] = Hardware_B.D45;
  Hardware_B.ginv[60] = Hardware_B.D58;
  Hardware_B.ginv[5] = Hardware_B.D16;
  Hardware_B.ginv[13] = Hardware_B.D26;
  Hardware_B.ginv[21] = 0.0;
  Hardware_B.ginv[29] = Hardware_B.D46;
  Hardware_B.ginv[37] = Hardware_B.D56;
  Hardware_B.D16 = Hardware_B.x_tmp_k * Hardware_B.x_tmp_k;
  Hardware_B.D26 = Hardware_B.D14_tmp_c * Hardware_B.D14_tmp_c;
  Hardware_B.D46 = Hardware_B.smax * Hardware_B.smax;
  Hardware_B.D56 = Hardware_B.x_tmp * Hardware_B.x_tmp;
  Hardware_B.D47_tmp_l = Hardware_P.ArmConstants.Inertia2[0] +
    Hardware_P.ArmConstants.Inertia2[4];
  Hardware_B.D34 = -Hardware_P.ArmConstants.Inertia2[0] +
    Hardware_P.ArmConstants.Inertia2[4];
  Hardware_B.D46_tmp_g2 = 2.0 * Hardware_B.x_tmp_k;
  Hardware_B.rtb_ginv_tmp_ox = Hardware_B.D46_tmp_g2 * Hardware_B.D17_tmp_a *
    Hardware_B.x_tmp;
  Hardware_B.rtb_ginv_tmp_k = Hardware_B.x_tmp_cx * Hardware_B.x_tmp_cx;
  Hardware_B.D46_tmp_fi = Hardware_P.ArmConstants.Inertia1[6] *
    Hardware_B.D14_tmp_c - Hardware_P.ArmConstants.Inertia1[7] * Hardware_B.smax;
  Hardware_B.D46_tmp_ei = Hardware_P.ArmConstants.Inertia1[7] *
    Hardware_B.D14_tmp_c + Hardware_P.ArmConstants.Inertia1[6] * Hardware_B.smax;
  Hardware_B.D46_tmp_ch = Hardware_P.ArmConstants.Inertia2[6] *
    Hardware_B.D14_tmp_f - Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D14_tmp_p;
  Hardware_B.D46_tmp_ax = Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D14_tmp_f + Hardware_P.ArmConstants.Inertia2[6] *
    Hardware_B.D14_tmp_p;
  Hardware_B.D46_tmp_b = Hardware_B.D26 * Hardware_P.ArmConstants.Inertia1[0];
  Hardware_B.D46_tmp_ln = Hardware_B.D46 * Hardware_P.ArmConstants.Inertia1[4];
  Hardware_B.D26 = (Hardware_B.D26 * Hardware_P.ArmConstants.Inertia1[4] +
                    Hardware_B.D46 * Hardware_P.ArmConstants.Inertia1[0]) +
    Hardware_P.ArmConstants.Inertia1[3] * Hardware_B.D46_tmp_a;
  Hardware_B.D45_tmp_a = Hardware_P.ArmConstants.Inertia2[0] -
    Hardware_P.ArmConstants.Inertia2[4];
  Hardware_B.D46 = (Hardware_B.D45_tmp_a * Hardware_B.D46_tmp_ex +
                    Hardware_B.D47_tmp_l) + Hardware_B.D56_tmp_h *
    Hardware_B.D46_tmp_h2;
  Hardware_B.rtb_ginv_tmp_tmp_c = Hardware_B.D34 * Hardware_B.D46_tmp_ex;
  Hardware_B.rtb_ginv_tmp_tmp_p = Hardware_B.D15 * Hardware_B.D46_tmp_h2;
  Hardware_B.D47_tmp_l = (Hardware_B.rtb_ginv_tmp_tmp_c + Hardware_B.D47_tmp_l)
    + Hardware_B.rtb_ginv_tmp_tmp_p;
  Hardware_B.rtb_ginv_tmp_h = Hardware_B.D16 * Hardware_P.HexaConstants.Inertia
    [8];
  Hardware_B.rtb_ginv_tmp_da = Hardware_B.D17_tmp_a * Hardware_B.D56;
  Hardware_B.rtb_ginv_tmp_pi = Hardware_B.D16 * Hardware_B.D17_tmp_a;
  Hardware_B.ginv[45] = ((((((((((((((((((-Hardware_P.ArmConstants.Inertia1[0] +
    Hardware_P.ArmConstants.Inertia1[4]) * Hardware_B.D14_tmp_c *
    Hardware_B.smax + -Hardware_P.ArmConstants.Inertia1[3] *
    Hardware_B.D56_tmp_tmp_tmp) * Hardware_B.rtb_ginv_tmp_ox +
    (Hardware_B.D17_tmp_a * Hardware_P.HexaConstants.Inertia[4] * Hardware_B.D56
     + Hardware_B.rtb_ginv_tmp_h * Hardware_B.D17_tmp_a)) +
    ((Hardware_B.D46_tmp_b + Hardware_B.D46_tmp_ln) +
     -Hardware_P.ArmConstants.Inertia1[3] * Hardware_B.D46_tmp_a) *
    Hardware_B.rtb_ginv_tmp_pi) + Hardware_B.D26 * Hardware_B.rtb_ginv_tmp_da) +
    Hardware_B.D16 * 0.5 * Hardware_B.D17_tmp_a * Hardware_B.D46) +
    Hardware_B.D17_tmp_a * 0.5 * Hardware_B.D56 * Hardware_B.D47_tmp_l) +
    (Hardware_B.D34 * 0.5 * Hardware_B.D46_tmp_h2 +
     -Hardware_P.ArmConstants.Inertia2[3] * Hardware_B.D46_tmp_ex) *
    Hardware_B.rtb_ginv_tmp_ox) + Hardware_B.rtb_ginv_tmp_k *
    Hardware_P.ArmConstants.Inertia1[8]) + Hardware_B.rtb_ginv_tmp_k *
    Hardware_P.ArmConstants.Inertia2[8]) + Hardware_B.rtb_ginv_tmp_k *
    Hardware_P.HexaConstants.Inertia[0]) + Hardware_B.D45_tmp *
    Hardware_B.D45_tmp * Hardware_P.ArmConstants.Mass1) + Hardware_B.D24_tmp_j *
    Hardware_B.D24_tmp_j * Hardware_P.ArmConstants.Mass2) + Hardware_B.y_a *
    Hardware_B.y_a * Hardware_P.ArmConstants.Mass1) + Hardware_B.ab_a *
    Hardware_B.ab_a * Hardware_P.ArmConstants.Mass2) + Hardware_B.D46_tmp_fi *
    Hardware_B.x_tmp_k * Hardware_B.D46_tmp_d) - Hardware_B.D46_tmp_ei *
    Hardware_B.x_tmp * Hardware_B.D46_tmp_d) + Hardware_B.D46_tmp_ch *
    Hardware_B.x_tmp_k * Hardware_B.D46_tmp_d) - Hardware_B.D46_tmp_ax *
    Hardware_B.x_tmp * Hardware_B.D46_tmp_d;
  Hardware_B.ginv[53] = Hardware_B.D67;
  Hardware_B.ginv[61] = Hardware_B.D68;
  Hardware_B.ginv[6] = Hardware_B.D17;
  Hardware_B.ginv[14] = Hardware_B.D27;
  Hardware_B.ginv[22] = Hardware_B.D37;
  Hardware_B.ginv[30] = Hardware_B.D47;
  Hardware_B.ginv[38] = Hardware_B.D45;
  Hardware_B.ginv[46] = Hardware_B.D67;
  Hardware_B.ginv[54] = Hardware_B.D47_tmp_i + Hardware_B.D47_tmp_p;
  Hardware_B.ginv[62] = Hardware_B.D48_tmp_p;
  Hardware_B.ginv[7] = Hardware_B.D18;
  Hardware_B.ginv[15] = Hardware_B.D28;
  Hardware_B.ginv[23] = Hardware_B.D38;
  Hardware_B.ginv[31] = Hardware_B.D48;
  Hardware_B.ginv[39] = Hardware_B.D58;
  Hardware_B.ginv[47] = Hardware_B.D68;
  Hardware_B.ginv[55] = Hardware_B.D48_tmp_p;
  Hardware_B.ginv[63] = Hardware_B.D48_tmp_tmp;
  Hardware_B.D17 = sin(Hardware_B.D56_tmp_tmp);
  Hardware_B.D18 = sin(Hardware_B.D56_tmp_tmp_f);
  Hardware_B.D27 = cos(Hardware_B.D56_tmp_tmp_oc);
  Hardware_B.D56_tmp_tmp_m = cos(Hardware_B.D56_tmp_tmp_m);
  Hardware_B.D46_tmp_tmp_c = cos(Hardware_B.D46_tmp_tmp_c);
  Hardware_B.D56_tmp_tmp_fb = cos(Hardware_B.D56_tmp_tmp_fb);
  Hardware_B.D56_tmp_tmp_hc = cos(Hardware_B.D56_tmp_tmp_hc);
  Hardware_B.D46_tmp_tmp_m4 = cos(Hardware_B.D46_tmp_tmp_m4);
  Hardware_B.D46_tmp_tmp_ad = cos(Hardware_B.D46_tmp_tmp_ad);
  Hardware_B.D46_tmp_tmp_k = cos(Hardware_B.D46_tmp_tmp_k);
  Hardware_B.D56_tmp_tmp_p = cos(Hardware_B.D56_tmp_tmp_p);
  Hardware_B.D56_tmp_tmp_o = cos(Hardware_B.D56_tmp_tmp_o);
  Hardware_B.D46_tmp_tmp_pc = cos(Hardware_B.D46_tmp_tmp_pc);
  Hardware_B.D46_tmp_tmp_b = cos(Hardware_B.D46_tmp_tmp_b);
  Hardware_B.D56_tmp_tmp_h = cos(Hardware_B.D56_tmp_tmp_h);
  Hardware_B.D56_tmp_tmp_c = cos(Hardware_B.D56_tmp_tmp_c);
  Hardware_B.D56_tmp_tmp_oc = sin(Hardware_B.D56_tmp_tmp_e);
  Hardware_B.D28 = sin(Hardware_B.rtb_ginv_tmp_tmp_o);
  Hardware_B.D37 = -2.0 * Hardware_DW.DiscreteTimeIntegrator_DSTATE[4];
  Hardware_B.D56_tmp_tmp_f = sin(Hardware_B.D56_tmp_tmp_f + Hardware_B.D37);
  Hardware_B.D46_tmp_tmp *= 2.0;
  Hardware_B.D38 = sin(Hardware_B.D46_tmp_tmp);
  Hardware_B.D46_tmp_tmp_i *= 2.0;
  Hardware_B.D47_tmp_i = sin(Hardware_B.D46_tmp_tmp_i);
  Hardware_B.D47 = sin((-Hardware_DW.DiscreteTimeIntegrator_DSTATE[3] +
                        Hardware_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  Hardware_B.D48_tmp_tmp = (Hardware_DW.DiscreteTimeIntegrator_DSTATE[3] +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0;
  Hardware_B.D48_tmp_p = sin(Hardware_B.D48_tmp_tmp);
  Hardware_B.D46_tmp_tmp_f *= 2.0;
  Hardware_B.D56_tmp_tmp = sin(Hardware_B.D46_tmp_tmp_f);
  Hardware_B.D46_tmp_tmp_iz *= 2.0;
  Hardware_B.D58 = sin(Hardware_B.D46_tmp_tmp_iz);
  Hardware_B.y_a = sin(Hardware_B.D48_tmp_tmp +
                       Hardware_DW.DiscreteTimeIntegrator_DSTATE[6]);
  Hardware_B.ab_a = Hardware_B.D15_tmp_tmp + Hardware_B.D37;
  Hardware_B.rtb_ginv_tmp_tmp_o = cos(Hardware_B.ab_a);
  Hardware_B.D67 = Hardware_B.D15_tmp_tmp_o + Hardware_B.D37;
  Hardware_B.D68 = cos(Hardware_B.D67);
  Hardware_B.rtb_ginv_tmp_ox = cos(Hardware_B.D46_tmp_tmp);
  Hardware_B.D46_tmp_tmp_i = cos(Hardware_B.D46_tmp_tmp_i);
  Hardware_B.d = cos(Hardware_B.D46_tmp_tmp_f);
  Hardware_B.D46_tmp_tmp_iz = cos(Hardware_B.D46_tmp_tmp_iz);
  Hardware_B.D15_tmp_tmp += Hardware_B.rtb_ginv_tmp_tmp_m;
  Hardware_B.d1 = cos(Hardware_B.D15_tmp_tmp);
  Hardware_B.D15_tmp_tmp_o += Hardware_B.rtb_ginv_tmp_tmp_m;
  Hardware_B.d2 = cos(Hardware_B.D15_tmp_tmp_o);
  Hardware_B.D46_tmp_tmp = sin(Hardware_B.D46_tmp_tmp +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7]);
  Hardware_B.d3 = sin(Hardware_B.D37 +
                      Hardware_DW.DiscreteTimeIntegrator_DSTATE[6]);
  Hardware_B.ab_a = sin(Hardware_B.ab_a);
  Hardware_B.D67 = sin(Hardware_B.D67);
  Hardware_B.D56_tmp_tmp_e = sin(Hardware_B.D56_tmp_tmp_e + Hardware_B.D37);
  Hardware_B.d4 = sin((Hardware_DW.DiscreteTimeIntegrator_DSTATE[3] -
                       Hardware_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  Hardware_B.d5 = sin(Hardware_B.rtb_ginv_tmp_tmp_m +
                      Hardware_DW.DiscreteTimeIntegrator_DSTATE[6]);
  Hardware_B.D15_tmp_tmp = sin(Hardware_B.D15_tmp_tmp);
  Hardware_B.D15_tmp_tmp_o = sin(Hardware_B.D15_tmp_tmp_o);
  Hardware_B.D48_tmp_tmp = sin(Hardware_B.D48_tmp_tmp + Hardware_B.D14_tmp_tmp);
  Hardware_B.D46_tmp_tmp_f = sin(Hardware_B.D46_tmp_tmp_f +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7]);
  Hardware_B.d6 = sin(Hardware_B.D37 +
                      Hardware_DW.DiscreteTimeIntegrator_DSTATE[7]);
  Hardware_B.D37 = sin(Hardware_B.D14_tmp_tmp + Hardware_B.D37);
  Hardware_B.d7 = sin(Hardware_B.rtb_ginv_tmp_tmp_m +
                      Hardware_DW.DiscreteTimeIntegrator_DSTATE[7]);
  Hardware_B.D14_tmp_tmp = sin(Hardware_B.D14_tmp_tmp +
    Hardware_B.rtb_ginv_tmp_tmp_m);
  Hardware_B.rtb_ginv_tmp_tmp_m = cos(Hardware_B.rtb_ginv_tmp_tmp_m);
  Hardware_B.D14_tmp_ch = Hardware_B.D14_tmp_ch * Hardware_B.x_tmp_cx +
    Hardware_B.D14_tmp_nb * Hardware_B.s;
  Hardware_B.D14_tmp_nb = Hardware_B.D14_tmp_j * Hardware_B.DigitalClock;
  Hardware_B.d8 = 2.0 * Hardware_B.x_tmp;
  Hardware_B.d9 = Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D16_tmp_e = Hardware_B.D16_tmp_e * Hardware_B.x_tmp_cx +
    Hardware_B.D14_tmp_h;
  Hardware_B.d10 = Hardware_B.D16_tmp_e * Hardware_B.D46_tmp_g2;
  Hardware_B.d11 = Hardware_B.D14_tmp_nb * Hardware_B.x_tmp_cx;
  Hardware_B.d12 = 2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.d13 = -2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6];
  Hardware_B.d166 = -2.0 * Hardware_B.x_tmp_k;
  Hardware_B.D14_tmp_nb = (Hardware_B.D14_tmp_nb - Hardware_B.D16_tmp_m0) *
    Hardware_B.d8 + Hardware_B.D16_tmp_j * Hardware_B.d166;
  Hardware_B.D16_tmp_m0 = ((Hardware_DW.DiscreteTimeIntegrator_DSTATE[3] -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[5]) +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[6]) +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.D16_tmp_j = ((Hardware_DW.DiscreteTimeIntegrator_DSTATE[3] +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[5]) +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[6]) +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[7];
  Hardware_B.tmp_tmp = 2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6];
  Hardware_B.d19 = 2.0 * Hardware_B.DigitalClock;
  Hardware_B.dv[24] = -(((((((Hardware_B.D14_tmp_cz * Hardware_B.x_tmp_c -
    Hardware_B.D14_tmp_i) * Hardware_B.x_tmp + Hardware_B.D14_tmp_ch *
    Hardware_B.x_tmp_k) * (Hardware_B.tmp_tmp * Hardware_B.D14_tmp_c) +
    ((Hardware_B.d19 * Hardware_B.D15_tmp_g * Hardware_B.x_tmp_cx + (cos
    (Hardware_B.D16_tmp_m0) - cos(Hardware_B.D16_tmp_j))) * Hardware_B.d9 +
     Hardware_B.d12 * Hardware_B.DigitalClock * Hardware_B.x_tmp_b *
     Hardware_B.D34_tmp_m)) + (Hardware_B.D14_tmp_ch * Hardware_B.x_tmp +
    Hardware_B.D14_tmp_jg) * (Hardware_B.d13 * Hardware_B.smax)) +
    ((Hardware_B.D16_tmp_m - Hardware_B.d11) * Hardware_B.d8 + Hardware_B.d10) *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3]) + Hardware_B.D14_tmp_nb *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) * 0.5);
  Hardware_B.dv[32] = -((((Hardware_B.D15_tmp_a *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] * Hardware_B.x_tmp_b *
    Hardware_B.x_tmp_c + Hardware_B.d9 * Hardware_B.DigitalClock *
    Hardware_B.x_tmp_b * Hardware_B.D17_tmp_i) +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] * Hardware_B.DigitalClock *
    Hardware_B.x_tmp_b * Hardware_B.D37_tmp) +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] * Hardware_B.DigitalClock *
    Hardware_B.x_tmp_b * Hardware_B.D34_tmp_m) +
                        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
                        Hardware_B.DigitalClock * Hardware_B.D15_tmp_a *
                        Hardware_B.x_tmp_cx);
  Hardware_B.D14_tmp_ch = Hardware_B.D46_tmp_c *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D14_tmp_cz = -Hardware_B.D16_tmp * Hardware_B.x_tmp_c +
    Hardware_B.d11;
  Hardware_B.D14_tmp_i = -2.0 * Hardware_B.x_tmp;
  Hardware_B.dv[40] = -(((((((Hardware_B.rtb_ginv_tmp_tmp_f *
    Hardware_B.x_tmp_cx + Hardware_B.rtb_ginv_tmp_tmp) * -Hardware_B.D14_tmp_j +
    Hardware_B.D27_tmp) + Hardware_B.D27_tmp_a) * Hardware_B.d13 +
    (Hardware_B.D15_tmp_a * Hardware_B.d12 * Hardware_B.x_tmp_b *
     Hardware_B.x_tmp_c + (Hardware_B.rtb_ginv_tmp_l * Hardware_B.D14_tmp_p +
    Hardware_B.rtb_ginv_tmp_o * Hardware_B.D14_tmp_f) * Hardware_B.D14_tmp_ch))
    + (Hardware_B.D14_tmp_cz * Hardware_B.D14_tmp_i + Hardware_B.d10) *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) + Hardware_B.D14_tmp_nb *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3]) * 0.5);
  Hardware_B.D14_tmp_nb = Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d10 = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6];
  Hardware_B.rtb_ginv_tmp_tmp = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_B.x_tmp_cx;
  Hardware_B.rtb_ginv_tmp_tmp_f = Hardware_P.ArmConstants.MC1 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp_b;
  Hardware_B.rtb_ginv_tmp_l = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.x_tmp_b;
  Hardware_B.D14_tmp_jg = Hardware_B.D14_tmp_nb * Hardware_B.x_tmp_b;
  Hardware_B.D16_tmp = 2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.D16_tmp_m = Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D27_tmp = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7];
  Hardware_B.D27_tmp_a = Hardware_B.D27_tmp * 2.0 +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3];
  Hardware_B.d14 = -2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d15 = Hardware_B.d10 - Hardware_B.rtb_ginv_tmp_tmp;
  Hardware_B.D14_tmp *= Hardware_B.D16_tmp_m;
  Hardware_B.d16 = Hardware_B.d10 + Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7];
  Hardware_B.d17 = Hardware_B.d16 - Hardware_B.rtb_ginv_tmp_tmp;
  Hardware_B.d18 = Hardware_B.D14_tmp_n * Hardware_B.d14;
  Hardware_B.d20 = Hardware_B.D14_tmp_n *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.d21 = Hardware_B.d14 * Hardware_B.x_tmp_cx + Hardware_B.D27_tmp_a;
  Hardware_B.d45 = Hardware_B.D46_tmp_tmp_g *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d48 = Hardware_B.D46_tmp_f *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.tmp_tmp_dd = -2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3];
  Hardware_B.dv[48] = -(((((((((((((((((Hardware_B.d20 * Hardware_B.D14_tmp_c *
    Hardware_B.x_tmp_b * Hardware_B.x_tmp + Hardware_B.D14_tmp_nb *
    Hardware_B.D14_tmp_f * Hardware_B.x_tmp_b * Hardware_B.x_tmp) +
    Hardware_B.d45 * Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp *
    Hardware_B.smax) + Hardware_B.D16_tmp * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp * Hardware_B.smax) +
    Hardware_B.rtb_ginv_tmp_tmp_f * Hardware_B.D17_tmp_p) +
    Hardware_B.rtb_ginv_tmp_l * Hardware_B.D17_tmp_p) + Hardware_B.d48 *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp * Hardware_B.D14_tmp_p) +
    Hardware_B.D14_tmp_jg * Hardware_B.D17_tmp_i) + Hardware_B.D46_tmp_nr *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp * Hardware_B.smax *
    Hardware_B.x_tmp_cx) + Hardware_B.D46_tmp_nr *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp * Hardware_B.smax *
    Hardware_B.x_tmp_cx) + Hardware_B.tmp_tmp_dd *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.x_tmp * Hardware_B.smax * Hardware_B.x_tmp_cx) + Hardware_B.d13 *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.x_tmp * Hardware_B.smax * Hardware_B.x_tmp_cx) +
    Hardware_B.D46_tmp_c * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp * Hardware_B.D14_tmp_p *
    Hardware_B.x_tmp_cx) + Hardware_B.D46_tmp_c *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp * Hardware_B.D14_tmp_p *
    Hardware_B.x_tmp_cx) + Hardware_B.D14_tmp_ch * Hardware_B.x_tmp *
    Hardware_B.D14_tmp_p * Hardware_B.x_tmp_cx) * Hardware_B.DigitalClock +
    (Hardware_B.D16_tmp_tmp * Hardware_B.d15 + Hardware_B.d17 *
     Hardware_B.D14_tmp_m3) * (Hardware_B.d8 * Hardware_B.x_tmp_c)) +
    ((((Hardware_B.d10 * 2.0 * Hardware_B.D14_tmp_n + Hardware_B.D14_tmp) *
       Hardware_B.x_tmp_cx + Hardware_B.d18) * Hardware_B.D14_tmp_c +
      ((((Hardware_B.rtb_ginv_tmp_tmp_f * Hardware_B.smax +
          Hardware_B.rtb_ginv_tmp_l * Hardware_B.smax) + Hardware_B.D14_tmp_jg *
         Hardware_B.D14_tmp_p) - Hardware_B.D16_tmp_m * Hardware_B.smax *
        Hardware_B.s * Hardware_B.x_tmp_cx) - (Hardware_B.D16_tmp -
    Hardware_B.D27_tmp_a * Hardware_B.x_tmp_cx) * Hardware_B.D14_tmp_m3)) *
     Hardware_B.DigitalClock + ((Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_B.D14_tmp_c * Hardware_B.s + Hardware_B.d21 * Hardware_B.D14_tmp_p)
    * Hardware_B.D14_tmp_o + (Hardware_B.D14_tmp_n * 2.0 * Hardware_B.d15 +
    Hardware_B.D14_tmp) * Hardware_B.smax) * Hardware_B.x_tmp_c) *
    Hardware_B.x_tmp_k) * 0.5);
  Hardware_B.D14_tmp_ch = Hardware_B.d16 * Hardware_B.x_tmp_cx;
  Hardware_B.d13 = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_B.x_tmp_b;
  Hardware_B.rtb_ginv_tmp_tmp_f = 2.0 * Hardware_B.D14_tmp_f;
  Hardware_B.rtb_ginv_tmp_l = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] -
    Hardware_B.D14_tmp_ch;
  Hardware_B.dv[56] = -(((((Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_B.D14_tmp_f * Hardware_B.x_tmp_b * Hardware_B.x_tmp +
    Hardware_B.d13 * Hardware_B.D17_tmp_i) + Hardware_B.d8 *
    Hardware_B.D14_tmp_p * Hardware_B.rtb_ginv_tmp_l) * Hardware_B.DigitalClock
    + Hardware_B.rtb_ginv_tmp_tmp_f * Hardware_B.x_tmp * Hardware_B.x_tmp_c *
    Hardware_B.d17) + (((Hardware_B.D14_tmp_ch -
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
                        Hardware_B.rtb_ginv_tmp_tmp_f + Hardware_B.d13 *
                        Hardware_B.D14_tmp_p) * Hardware_B.DigitalClock + 2.0 *
                       Hardware_B.x_tmp_c * Hardware_B.D14_tmp_p *
                       Hardware_B.d17) * Hardware_B.x_tmp_k) * (0.5 *
    Hardware_P.ArmConstants.MC2 * Hardware_P.ArmConstants.Mass2));
  Hardware_B.D14_tmp_ch = Hardware_B.D15_tmp_tmp_d + Hardware_B.D15_tmp_tmp_n;
  Hardware_B.d8 = Hardware_B.d13 * Hardware_B.x_tmp_c;
  Hardware_B.d13 = Hardware_B.D14_tmp_ch *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6];
  Hardware_B.dv[25] = -(((((((((cos(Hardware_B.D16_tmp_m0 -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4]) - cos(Hardware_B.D16_tmp_j -
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4])) - cos(Hardware_B.D16_tmp_m0 +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4])) + cos(Hardware_B.D16_tmp_j +
    Hardware_DW.DiscreteTimeIntegrator_DSTATE[4])) + sin(Hardware_B.D16_tmp_m0) *
    2.0) + sin(Hardware_B.D16_tmp_j) * 2.0) * (-0.25 *
    Hardware_P.ArmConstants.MC2 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7] *
    Hardware_P.ArmConstants.Mass2) +
    (-Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] * Hardware_B.DigitalClock *
     Hardware_B.D37_tmp + Hardware_B.D34_tmp_m * Hardware_B.d8)) +
    Hardware_B.d13 * Hardware_B.x_tmp_c * Hardware_B.x_tmp_cx) +
    (Hardware_B.D15_tmp_a * Hardware_B.x_tmp_c * Hardware_B.x_tmp_cx +
     Hardware_B.D34_tmp_m * -Hardware_B.DigitalClock) *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3]) + (Hardware_B.D16_tmp_e *
    Hardware_B.x_tmp + Hardware_B.D14_tmp_cz * Hardware_B.x_tmp_k) *
                        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]);
  Hardware_B.D16_tmp_e = Hardware_B.D15_tmp_a *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.D16_tmp_m0 = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_B.x_tmp_b;
  Hardware_B.dv[33] = -((((-Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_B.DigitalClock * Hardware_B.D15_tmp_a * Hardware_B.x_tmp_b +
    Hardware_B.d9 * Hardware_B.x_tmp_b * Hardware_B.x_tmp_c *
    Hardware_B.D17_tmp_i) + Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    Hardware_B.x_tmp_b * Hardware_B.x_tmp_c * Hardware_B.D37_tmp) +
    Hardware_B.D16_tmp_m0 * Hardware_B.x_tmp_c * Hardware_B.D34_tmp_m) +
                        Hardware_B.D16_tmp_e * Hardware_B.x_tmp_c *
                        Hardware_B.x_tmp_cx);
  Hardware_B.D16_tmp_j = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] -
    Hardware_B.d10 * Hardware_B.x_tmp_cx;
  Hardware_B.D14_tmp_cz = (((Hardware_B.tmp_tmp +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3]) *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 +
    Hardware_B.D46_tmp_tmp_g * Hardware_B.d10 * Hardware_P.ArmConstants.Mass1) +
    Hardware_B.d18 * Hardware_B.x_tmp_cx) +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.rtb_ginv_tmp_k;
  Hardware_B.rtb_ginv_tmp_tmp_f = -0.5 * Hardware_P.ArmConstants.MC2 *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D14_tmp_jg = 4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.D27_tmp_a = -4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6];
  Hardware_B.D14_tmp = -4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7];
  Hardware_B.dv[41] = -((((((((((-3.0 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] + Hardware_B.D27_tmp_a) +
    Hardware_B.D14_tmp) + Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_B.rtb_ginv_tmp_tmp_m) + Hardware_B.D14_tmp_jg * Hardware_B.x_tmp_cx)
    * (Hardware_B.rtb_ginv_tmp_tmp_f * Hardware_B.D14_tmp_f) +
    (-Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] * Hardware_B.x_tmp_cx +
     Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3]) * (Hardware_B.D46_tmp_tmp_p *
    Hardware_B.D14_tmp_m)) + Hardware_B.D14_tmp_cz * Hardware_B.D14_tmp_c) *
    Hardware_B.x_tmp_c + ((Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_B.D14_tmp_m *
    Hardware_B.x_tmp_b + Hardware_B.D14_tmp_tmp_cg * Hardware_B.D16_tmp_j) +
    Hardware_B.rtb_ginv_tmp_l * Hardware_B.D14_tmp_tmp_f) * Hardware_B.d19) *
    -Hardware_B.x_tmp_k + ((((-Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_B.x_tmp_cx + Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
    Hardware_B.D14_tmp_md + Hardware_B.D16_tmp_tmp * Hardware_B.D16_tmp_j) +
    Hardware_B.rtb_ginv_tmp_l * Hardware_B.D14_tmp_m3) * Hardware_B.x_tmp +
    (Hardware_B.d20 * Hardware_B.D15_tmp * Hardware_B.x_tmp_b +
     Hardware_B.D14_tmp_nb * Hardware_B.D15_tmp_g * Hardware_B.x_tmp_b)) * (-2.0
    * Hardware_B.DigitalClock)) + (((Hardware_B.rtb_ginv_tmp_k *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] + Hardware_B.d21) *
    Hardware_B.D14_tmp_tmp_f + Hardware_B.D14_tmp_cz * Hardware_B.smax) *
    Hardware_B.x_tmp + (-Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
                        Hardware_P.ArmConstants.l1_dim *
                        Hardware_P.ArmConstants.Mass2 * Hardware_B.D15_tmp *
                        Hardware_B.D17_tmp_a - Hardware_B.D16_tmp_m *
                        Hardware_B.D15_tmp_g * Hardware_B.D17_tmp_a)) *
    Hardware_B.x_tmp_c) * 0.5);
  Hardware_B.D14_tmp_nb = Hardware_B.D16_tmp_tmp + Hardware_B.D14_tmp_m3;
  Hardware_B.dv[49] = -((((Hardware_B.D14_tmp_ch *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] * Hardware_B.x_tmp_c *
    Hardware_B.x_tmp_cx + (-Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_B.DigitalClock * Hardware_B.D37_tmp + Hardware_B.D37_tmp *
    Hardware_B.d8)) - (Hardware_B.DigitalClock * Hardware_B.D17_tmp_i -
                       Hardware_B.D15_tmp_g * Hardware_B.x_tmp_c *
                       Hardware_B.x_tmp_cx) * Hardware_B.d9) +
    (Hardware_B.D14_tmp_ch * Hardware_B.x_tmp_c * Hardware_B.x_tmp_cx +
     Hardware_B.D37_tmp * -Hardware_B.DigitalClock) *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6]) + ((Hardware_B.D14_tmp_nb *
    Hardware_B.DigitalClock * Hardware_B.x_tmp_cx + Hardware_B.D14_tmp_h) *
    Hardware_B.x_tmp + (-Hardware_B.D14_tmp_nb * Hardware_B.x_tmp_c +
                        Hardware_B.d11) * Hardware_B.x_tmp_k) *
                        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]);
  Hardware_B.dv[57] = -(((((Hardware_B.d16 -
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4]) * Hardware_B.D46_tmp_ld +
    Hardware_B.D16_tmp * Hardware_B.D15_tmp_g) - (Hardware_B.d16 +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4]) * Hardware_B.D46_tmp_nu) *
    Hardware_B.x_tmp_c + Hardware_B.d19 * Hardware_B.D17_tmp_i * Hardware_B.d17)
                        * Hardware_B.rtb_ginv_tmp_tmp_f);
  Hardware_B.dv[26] = -(((Hardware_B.d9 * Hardware_B.D15_tmp_g *
    Hardware_B.x_tmp_b + Hardware_B.d13 * Hardware_B.x_tmp_b) +
    Hardware_B.D15_tmp_a * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_B.x_tmp_b) - Hardware_B.D34_tmp_m *
                        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
                        Hardware_B.x_tmp_cx);
  Hardware_B.dv[34] = -(((Hardware_B.D16_tmp_e * Hardware_B.x_tmp_b -
    Hardware_B.d9 * Hardware_B.D17_tmp_i * Hardware_B.x_tmp_cx) +
    Hardware_B.D37_tmp * -Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    Hardware_B.x_tmp_cx) - Hardware_B.D34_tmp_m *
                        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
                        Hardware_B.x_tmp_cx);
  Hardware_B.dv[42] = -0.0;
  Hardware_B.dv[50] = -((Hardware_B.d16 * Hardware_P.ArmConstants.MC2 *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.D15_tmp_g * Hardware_B.x_tmp_b +
    Hardware_B.D14_tmp_n * Hardware_B.d10 * Hardware_B.D15_tmp *
    Hardware_B.x_tmp_b) - Hardware_B.D37_tmp *
                        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
                        Hardware_B.x_tmp_cx);
  Hardware_B.dv[58] = -((Hardware_B.d16 * Hardware_B.D15_tmp_g *
    Hardware_B.x_tmp_b - Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_B.D17_tmp_i * Hardware_B.x_tmp_cx) * Hardware_B.D14_tmp_o);
  Hardware_B.dv[27] = -(-Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
                        Hardware_P.ArmConstants.Hexa_to_joint_L *
                        Hardware_B.D14_tmp_n * Hardware_B.smax -
                        (Hardware_B.D27_tmp *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_B.D14_tmp_p +
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7] *
    Hardware_P.ArmConstants.l1_dim * Hardware_B.s) * Hardware_B.D14_tmp_o);
  Hardware_B.D14_tmp_ch = Hardware_B.D46_tmp_tmp_m * 2.0;
  Hardware_B.D14_tmp_nb = Hardware_B.D46_tmp_o * 2.0;
  Hardware_B.d8 = Hardware_B.D46_tmp_lm * 2.0;
  Hardware_B.d9 = Hardware_P.HexaConstants.Inertia[4] * Hardware_B.D17;
  Hardware_B.D16_tmp_e = Hardware_P.HexaConstants.Inertia[8] * Hardware_B.D17;
  Hardware_B.d11 = Hardware_B.D56_tmp_p * Hardware_B.D17;
  Hardware_B.d13 = Hardware_B.D56_tmp_p4 * Hardware_B.D17;
  Hardware_B.D16_tmp_j = Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_B.D46_tmp_g;
  Hardware_B.d19 = Hardware_P.ArmConstants.Inertia1[4] * Hardware_B.D46_tmp_g;
  Hardware_B.D14_tmp_cz = Hardware_B.D47_tmp_c * Hardware_B.D46_tmp_g;
  Hardware_B.rtb_ginv_tmp_tmp_f = Hardware_B.D47_tmp_k * Hardware_B.D46_tmp_g;
  Hardware_B.rtb_ginv_tmp_l = Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_B.D46_tmp_e;
  Hardware_B.D16_tmp_m = Hardware_P.ArmConstants.Inertia2[4] *
    Hardware_B.D46_tmp_e;
  Hardware_B.D27_tmp = Hardware_B.D47_tmp * Hardware_B.D46_tmp_e;
  Hardware_B.d18 = Hardware_B.D14_tmp_nb * Hardware_P.ArmConstants.Mass1;
  Hardware_B.d20 = Hardware_B.D14_tmp_ch * Hardware_P.ArmConstants.Mass1;
  Hardware_B.d21 = Hardware_B.d8 * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D14_tmp_ch *= Hardware_P.ArmConstants.Mass2;
  Hardware_B.D14_tmp_f = Hardware_B.D46_tmp_mv * 2.0 *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D14_tmp_md = Hardware_B.D56_tmp_pm * Hardware_B.D46_tmp_m;
  Hardware_B.D14_tmp_m3 = Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_B.D56_tmp_da;
  Hardware_B.D14_tmp_tmp_cg = Hardware_P.ArmConstants.Inertia1[4] *
    Hardware_B.D56_tmp_da;
  Hardware_B.D14_tmp_tmp_f = Hardware_B.D47_tmp_c * Hardware_B.D56_tmp_da;
  Hardware_B.D14_tmp_h = Hardware_B.D47_tmp_k * Hardware_B.D56_tmp_da;
  Hardware_B.D15_tmp_tmp_d = Hardware_B.D46_tmp_mj * Hardware_B.D46_tmp_tmp_ad;
  Hardware_B.D15_tmp_tmp_n = Hardware_B.D56_tmp_p2 * Hardware_B.D46_tmp_n;
  Hardware_B.D16_tmp_tmp = Hardware_B.D46_tmp_mj * Hardware_B.D56_tmp_tmp_o;
  Hardware_B.D34_tmp_m = Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_B.D56_tmp_e;
  Hardware_B.D37_tmp = Hardware_P.ArmConstants.Inertia2[4] *
    Hardware_B.D56_tmp_e;
  Hardware_B.D46_tmp_tmp_p = Hardware_B.D47_tmp * Hardware_B.D56_tmp_e;
  Hardware_B.rtb_ginv_tmp_k = 2.0 * Hardware_P.ArmConstants.Inertia1[8] *
    Hardware_B.x_tmp_b;
  Hardware_B.d56 = 2.0 * Hardware_P.ArmConstants.Inertia2[8] *
    Hardware_B.x_tmp_b;
  Hardware_B.d57 = Hardware_B.d18 * Hardware_B.x_tmp_b;
  Hardware_B.d58 = Hardware_B.d21 * Hardware_B.x_tmp_b;
  Hardware_B.d59 = Hardware_B.D14_tmp_f * Hardware_B.x_tmp_b;
  Hardware_B.d60 = Hardware_B.D56_tmp_n * Hardware_B.D46_tmp_p;
  Hardware_B.d61 = Hardware_P.ArmConstants.Inertia1[0] * Hardware_B.D56_tmp_bj;
  Hardware_B.d62 = Hardware_P.ArmConstants.Inertia1[4] * Hardware_B.D56_tmp_bj;
  Hardware_B.d63 = Hardware_B.D47_tmp_c * Hardware_B.D56_tmp_bj;
  Hardware_B.d64 = Hardware_B.D47_tmp_k * Hardware_B.D56_tmp_bj;
  Hardware_B.d65 = Hardware_B.D46_tmp_mj * Hardware_B.D46_tmp_tmp_pc;
  Hardware_B.d66 = Hardware_B.D56_tmp_k * Hardware_B.D46_tmp_l;
  Hardware_B.d67 = Hardware_B.D46_tmp_mj * Hardware_B.D56_tmp_tmp_c;
  Hardware_B.d68 = Hardware_P.ArmConstants.Inertia2[0] * Hardware_B.D56_tmp_j;
  Hardware_B.d69 = Hardware_P.ArmConstants.Inertia2[4] * Hardware_B.D56_tmp_j;
  Hardware_B.d70 = Hardware_B.D47_tmp * Hardware_B.D56_tmp_j;
  Hardware_B.d71 = Hardware_B.D56_tmp_n3 * Hardware_B.D46_tmp_j;
  Hardware_B.d72 = Hardware_B.D25 * Hardware_B.D56_tmp_g;
  Hardware_B.d73 = Hardware_B.D56_tmp_oy * Hardware_B.D46_tmp_ld;
  Hardware_B.d74 = Hardware_B.D15 * Hardware_B.D56_tmp_dh;
  Hardware_B.d75 = Hardware_B.D56_tmp_gg * Hardware_B.D46_tmp_lx;
  Hardware_B.d76 = Hardware_B.D25 * Hardware_B.D56_tmp_b;
  Hardware_B.d77 = Hardware_B.D56_tmp_c * Hardware_B.D46_tmp_nu;
  Hardware_B.d78 = Hardware_B.D15 * Hardware_B.D56_tmp_bs;
  Hardware_B.tmp_tmp_l = Hardware_B.D46_tmp_tmp_m * Hardware_B.D14_tmp_m +
    (Hardware_P.HexaConstants.Inertia[4] - Hardware_P.HexaConstants.Inertia[8]);
  Hardware_B.D14_tmp_m =
    ((((((((((((((((((((((((((((((((((((((((((((((((((((Hardware_B.tmp_tmp_l *
    Hardware_B.D56_tmp_tmp_hc + Hardware_B.rtb_ginv_tmp_tmp_n *
    Hardware_B.D46_tmp_tmp_m4) + Hardware_B.D14_tmp_md) + Hardware_B.D46_tmp_mc *
    Hardware_B.D27) + Hardware_B.D46_tmp_h3 * Hardware_B.D27) -
    Hardware_B.D14_tmp_m3) + Hardware_B.D14_tmp_tmp_cg) +
    Hardware_B.D14_tmp_tmp_f) + Hardware_B.D14_tmp_h) + Hardware_B.D15_tmp_tmp_d)
    + Hardware_B.D46_tmp_pc * Hardware_B.D46_tmp_tmp_k) +
    Hardware_B.D15_tmp_tmp_n) + Hardware_B.D46_tmp_pc * Hardware_B.D56_tmp_tmp_p)
    + Hardware_B.D16_tmp_tmp) - Hardware_B.D34_tmp_m) + Hardware_B.D37_tmp) +
    Hardware_B.D46_tmp_tmp_p) + Hardware_B.rtb_ginv_tmp_k) + Hardware_B.d56) +
    2.0 * Hardware_P.HexaConstants.Inertia[0] * Hardware_B.x_tmp_b) +
    Hardware_B.d57) + Hardware_B.d20 * Hardware_B.x_tmp_b) + Hardware_B.d58) +
    Hardware_B.D14_tmp_ch * Hardware_B.x_tmp_b) + Hardware_B.d59) +
    Hardware_P.HexaConstants.Inertia[4] * Hardware_B.D56_tmp_tmp_m) -
    Hardware_P.HexaConstants.Inertia[8] * Hardware_B.D56_tmp_tmp_m) +
    Hardware_B.D56_tmp_p * Hardware_B.D56_tmp_tmp_m) + Hardware_B.D56_tmp_p4 *
    Hardware_B.D56_tmp_tmp_m) + Hardware_B.D46_tmp_mc * Hardware_B.D46_tmp_tmp_c)
    + Hardware_B.D46_tmp_h3 * Hardware_B.D46_tmp_tmp_c) + Hardware_B.d60) +
    Hardware_B.D46_tmp_mc * Hardware_B.D56_tmp_tmp_fb) + Hardware_B.D46_tmp_h3 *
    Hardware_B.D56_tmp_tmp_fb) - Hardware_B.d61) + Hardware_B.d62) +
                     Hardware_B.d63) + Hardware_B.d64) + Hardware_B.d65) +
                  Hardware_B.D46_tmp_pc * Hardware_B.D46_tmp_tmp_b) +
                 Hardware_B.d66) + Hardware_B.D46_tmp_pc *
                Hardware_B.D56_tmp_tmp_h) + Hardware_B.d67) - Hardware_B.d68) +
             Hardware_B.d69) + Hardware_B.d70) + Hardware_B.d71) +
          Hardware_B.d72) + Hardware_B.d73) + Hardware_B.d74) + Hardware_B.d75)
      + Hardware_B.d76) + Hardware_B.d77) + Hardware_B.d78;
  Hardware_B.rtb_ginv_tmp_tmp_n = Hardware_B.D56_tmp_l *
    Hardware_B.rtb_ginv_tmp_i + Hardware_B.D56_tmp_h * Hardware_B.D46_tmp_tmp_a;
  Hardware_B.d177 = Hardware_B.D46_tmp_mj * Hardware_B.D28;
  Hardware_B.dv[35] = -(((((((((((((((((Hardware_B.rtb_ginv_tmp_tmp_n +
    Hardware_B.d9) - Hardware_B.D16_tmp_e) + Hardware_B.d11) + Hardware_B.d13) -
    Hardware_B.D16_tmp_j) + Hardware_B.d19) + Hardware_B.D14_tmp_cz) +
    Hardware_B.rtb_ginv_tmp_tmp_f) + Hardware_B.D46_tmp_mc * Hardware_B.D18) +
    Hardware_B.D46_tmp_h3 * Hardware_B.D18) - Hardware_B.rtb_ginv_tmp_l) +
    Hardware_B.D16_tmp_m) + Hardware_B.D27_tmp) + Hardware_B.D46_tmp_pc *
    Hardware_B.D56_tmp_tmp_oc) + Hardware_B.d177) * Hardware_B.d12 +
    Hardware_B.D14_tmp_m * -Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
                        0.25);
  Hardware_B.d22 = -2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.d23 = Hardware_B.d22 * Hardware_B.D46_tmp_tmp_m;
  Hardware_B.d24 = -4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.tmp_tmp_n = -4.0 * Hardware_P.ArmConstants.MC1;
  Hardware_B.d25 = Hardware_B.tmp_tmp_n *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.tmp_tmp_d = Hardware_B.d24 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_f = -4.0 * Hardware_P.ArmConstants.MC2;
  Hardware_B.tmp_tmp_j = Hardware_B.tmp_tmp_f *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.d26 = Hardware_B.tmp_tmp_j *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_j = Hardware_B.tmp_tmp_j * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d27 = Hardware_B.d24 * Hardware_B.D46_tmp_tmp_m;
  Hardware_B.d28 = Hardware_B.d22 * Hardware_P.HexaConstants.Inertia[4];
  Hardware_B.d29 = Hardware_B.d12 * Hardware_P.HexaConstants.Inertia[8];
  Hardware_B.d30 = Hardware_B.d23 * Hardware_P.ArmConstants.Mass1;
  Hardware_B.d23 *= Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_a = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia1[3];
  Hardware_B.tmp_tmp_il = Hardware_B.d12 * Hardware_P.ArmConstants.Inertia1[0];
  Hardware_B.tmp_tmp_fa = Hardware_B.d22 * Hardware_P.ArmConstants.Inertia1[4];
  Hardware_B.tmp_tmp_ji = Hardware_B.D46_tmp_tmp_cj *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.tmp_tmp_oo = Hardware_B.d22 * Hardware_B.D46_tmp_mv *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d31 = 4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.tmp_tmp_fr = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia2
    [3];
  Hardware_B.tmp_tmp_oy = Hardware_B.d12 * Hardware_P.ArmConstants.Inertia2[0];
  Hardware_B.tmp_tmp_ln = Hardware_B.d22 * Hardware_P.ArmConstants.Inertia2[4];
  Hardware_B.tmp_tmp_lu = Hardware_B.D46_tmp_tmp_m1 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d32 = Hardware_B.d14 * Hardware_B.D46_tmp_tmp_m;
  Hardware_B.d33 = Hardware_B.tmp_tmp_f *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d34 = Hardware_B.D46_tmp_c *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d35 = Hardware_B.D46_tmp_tmp_m *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d36 = Hardware_P.HexaConstants.Inertia[4] *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d37 = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.HexaConstants.Inertia[8];
  Hardware_B.d38 = Hardware_B.d35 * Hardware_P.ArmConstants.Mass1;
  Hardware_B.d35 *= Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_gf = Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.tmp_tmp_d4 = Hardware_P.ArmConstants.Inertia1[4] *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.tmp_tmp_dv = Hardware_B.D46_tmp_o *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.d39 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia1[3];
  Hardware_B.tmp_tmp_jo = Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.tmp_tmp_f1 = Hardware_P.ArmConstants.Inertia2[4] *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.tmp_tmp_i = Hardware_B.D46_tmp_lm *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d40 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia2[3];
  Hardware_B.d41 = Hardware_B.D46_tmp_nr *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.d42 = Hardware_B.d14 * Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.d43 = Hardware_B.d34 * Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d34 = Hardware_B.d34 * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d44 = Hardware_P.ArmConstants.l1_dim * Hardware_B.s +
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_B.D14_tmp_p;
  Hardware_B.d46 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.d47 = Hardware_B.D46_tmp_mv *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d49 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.d50 = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.d51 = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.d52 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.d53 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.d54 = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.d55 = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.d104 = Hardware_B.d28 * Hardware_B.D56_tmp_tmp_hc;
  Hardware_B.d105 = Hardware_B.d29 * Hardware_B.D56_tmp_tmp_hc;
  Hardware_B.d106 = Hardware_B.d30 * Hardware_B.D56_tmp_tmp_hc;
  Hardware_B.d107 = Hardware_B.d23 * Hardware_B.D56_tmp_tmp_hc;
  Hardware_B.d124 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.d108 = Hardware_B.d124 * Hardware_B.D46_tmp_m;
  Hardware_B.d109 = Hardware_B.tmp_tmp_a * Hardware_B.rtb_ginv_tmp_ox;
  Hardware_B.d110 = Hardware_B.d25 * Hardware_B.D27;
  Hardware_B.d111 = Hardware_B.tmp_tmp_d * Hardware_B.D27;
  Hardware_B.d112 = Hardware_B.tmp_tmp_il * Hardware_B.D56_tmp_da;
  Hardware_B.d113 = Hardware_B.tmp_tmp_fa * Hardware_B.D56_tmp_da;
  Hardware_B.d114 = Hardware_B.tmp_tmp_ji * Hardware_B.D56_tmp_da;
  Hardware_B.d115 = Hardware_B.tmp_tmp_oo * Hardware_B.D56_tmp_da;
  Hardware_B.d125 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.d116 = Hardware_B.d125 * Hardware_B.D46_tmp_n;
  Hardware_B.d117 = Hardware_B.tmp_tmp_fr * Hardware_B.D46_tmp_tmp_i;
  Hardware_B.d118 = Hardware_B.d26 * Hardware_B.D56_tmp_tmp_p;
  Hardware_B.d119 = Hardware_B.tmp_tmp_j * Hardware_B.D56_tmp_tmp_o;
  Hardware_B.d120 = Hardware_B.tmp_tmp_oy * Hardware_B.D56_tmp_e;
  Hardware_B.d121 = Hardware_B.tmp_tmp_ln * Hardware_B.D56_tmp_e;
  Hardware_B.d122 = Hardware_B.tmp_tmp_lu * Hardware_B.D56_tmp_e;
  Hardware_B.D46_tmp_o *= -4.0;
  Hardware_B.d123 = Hardware_B.D46_tmp_lm * -4.0;
  Hardware_B.d126 = Hardware_B.d34 * Hardware_B.D46_tmp_tmp;
  Hardware_B.d127 = -4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d128 = Hardware_B.d41 * Hardware_B.D56_tmp_tmp_f;
  Hardware_B.d129 = Hardware_B.d42 * Hardware_B.D56_tmp_tmp_f;
  Hardware_B.d130 = Hardware_B.d43 * Hardware_B.D56_tmp_tmp_e;
  Hardware_B.d131 = Hardware_B.d37 * Hardware_B.d4;
  Hardware_B.d157 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.d132 = Hardware_B.d157 * Hardware_B.D46_tmp_j;
  Hardware_B.d133 = Hardware_B.tmp_tmp_gf * Hardware_B.D38;
  Hardware_B.d134 = Hardware_B.tmp_tmp_d4 * Hardware_B.D38;
  Hardware_B.d135 = Hardware_B.tmp_tmp_dv * Hardware_B.D38;
  Hardware_B.d136 = Hardware_B.d47 * Hardware_B.D38;
  Hardware_B.d137 = Hardware_B.d39 * Hardware_B.D56_tmp_g;
  Hardware_B.d162 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.d138 = Hardware_B.d162 * Hardware_B.D46_tmp_ld;
  Hardware_B.d139 = Hardware_B.tmp_tmp_jo * Hardware_B.D47_tmp_i;
  Hardware_B.d140 = Hardware_B.tmp_tmp_f1 * Hardware_B.D47_tmp_i;
  Hardware_B.d141 = Hardware_B.tmp_tmp_i * Hardware_B.D47_tmp_i;
  Hardware_B.d142 = Hardware_B.d40 * Hardware_B.D56_tmp_dh;
  Hardware_B.d143 = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia1[4];
  Hardware_B.d144 = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia2[4];
  Hardware_B.d145 = Hardware_B.d14 * Hardware_P.HexaConstants.Inertia[4];
  Hardware_B.d150 = Hardware_B.d36 * Hardware_B.D47;
  Hardware_B.d151 = Hardware_B.d38 * Hardware_B.D47;
  Hardware_B.d152 = Hardware_B.d35 * Hardware_B.D47;
  Hardware_B.d153 = Hardware_B.d36 * Hardware_B.D48_tmp_p;
  Hardware_B.d154 = Hardware_B.d37 * Hardware_B.D48_tmp_p;
  Hardware_B.d155 = Hardware_B.d38 * Hardware_B.D48_tmp_p;
  Hardware_B.d156 = Hardware_B.d35 * Hardware_B.D48_tmp_p;
  Hardware_B.d158 = Hardware_B.tmp_tmp_gf * Hardware_B.D56_tmp_tmp;
  Hardware_B.d159 = Hardware_B.tmp_tmp_d4 * Hardware_B.D56_tmp_tmp;
  Hardware_B.d160 = Hardware_B.tmp_tmp_dv * Hardware_B.D56_tmp_tmp;
  Hardware_B.d163 = Hardware_B.tmp_tmp_jo * Hardware_B.D58;
  Hardware_B.d164 = Hardware_B.tmp_tmp_f1 * Hardware_B.D58;
  Hardware_B.d165 = Hardware_B.tmp_tmp_i * Hardware_B.D58;
  Hardware_B.d167 = Hardware_B.tmp_tmp_j * Hardware_B.D46_tmp_tmp_ad;
  Hardware_B.d168 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia1[8] *
    Hardware_B.x_tmp_b;
  Hardware_B.d169 = Hardware_B.d24 * Hardware_P.ArmConstants.Inertia2[8] *
    Hardware_B.x_tmp_b;
  Hardware_B.d170 = Hardware_B.D46_tmp_o *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp_b;
  Hardware_B.d171 = Hardware_B.d123 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_b;
  Hardware_B.d172 = Hardware_B.d24 * Hardware_B.D46_tmp_mv *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_b;
  Hardware_B.d173 = Hardware_B.tmp_tmp_j * Hardware_B.D46_tmp_tmp_pc;
  Hardware_B.d198 = Hardware_B.D14_tmp_jg * Hardware_P.ArmConstants.Inertia2[3] *
    Hardware_B.D46_tmp_tmp_a;
  Hardware_B.d199 = Hardware_B.d53 * Hardware_B.D68;
  Hardware_B.d178 = ((Hardware_B.D14_tmp_jg * Hardware_P.ArmConstants.Inertia1[3]
                      * Hardware_B.rtb_ginv_tmp_i + Hardware_B.d198) +
                     Hardware_B.d52 * Hardware_B.rtb_ginv_tmp_tmp_o) +
    Hardware_B.d199;
  Hardware_B.d179 = Hardware_B.tmp_tmp_a * Hardware_B.d;
  Hardware_B.d180 = Hardware_B.tmp_tmp_fr * Hardware_B.D46_tmp_tmp_iz;
  Hardware_B.d181 = Hardware_B.d54 * Hardware_B.d1;
  Hardware_B.d182 = Hardware_B.d55 * Hardware_B.d2;
  Hardware_B.d183 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_B.D46_tmp_g;
  Hardware_B.d184 = Hardware_B.d143 * Hardware_B.D46_tmp_g;
  Hardware_B.D46_tmp_tmp_cj = Hardware_B.D46_tmp_tmp_cj *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.D46_tmp_g;
  Hardware_B.d185 = Hardware_B.d14 * Hardware_B.D46_tmp_mv *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.D46_tmp_g;
  Hardware_B.d186 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_B.D46_tmp_e;
  Hardware_B.d187 = Hardware_B.d144 * Hardware_B.D46_tmp_e;
  Hardware_B.D46_tmp_tmp_m1 = Hardware_B.D46_tmp_tmp_m1 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.D46_tmp_e;
  Hardware_B.d188 = Hardware_B.d33 * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.D28;
  Hardware_B.d189 = Hardware_B.d50 * Hardware_B.ab_a;
  Hardware_B.d190 = Hardware_B.d51 * Hardware_B.D67;
  Hardware_B.d191 = 8.0 * Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7];
  Hardware_B.d194 = Hardware_B.d46 * Hardware_B.D15_tmp_tmp;
  Hardware_B.d195 = Hardware_B.d49 * Hardware_B.D15_tmp_tmp_o;
  Hardware_B.d196 = Hardware_B.d34 * Hardware_B.D46_tmp_tmp_f;
  Hardware_B.dv[43] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    ((((((((((((((((((((((((((((((((((((((((Hardware_B.d178 + Hardware_B.d104) +
    Hardware_B.d105) + Hardware_B.d106) + Hardware_B.d107) + Hardware_B.d25 *
    Hardware_B.D46_tmp_tmp_m4) + Hardware_B.tmp_tmp_d *
    Hardware_B.D46_tmp_tmp_m4) + Hardware_B.d108) + Hardware_B.d109) +
    Hardware_B.d110) + Hardware_B.d111) + Hardware_B.d112) + Hardware_B.d113) +
    Hardware_B.d114) + Hardware_B.d115) + Hardware_B.d167) + Hardware_B.d26 *
    Hardware_B.D46_tmp_tmp_k) + Hardware_B.d116) + Hardware_B.d117) +
    Hardware_B.d118) + Hardware_B.d119) + Hardware_B.d120) + Hardware_B.d121) +
    Hardware_B.d122) + Hardware_B.d168) + Hardware_B.d169) + Hardware_B.d24 *
    Hardware_P.HexaConstants.Inertia[0] * Hardware_B.x_tmp_b) + Hardware_B.d170)
    + Hardware_B.d27 * Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp_b) +
    Hardware_B.d171) + Hardware_B.d27 * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.x_tmp_b) + Hardware_B.d172) + Hardware_B.d28 *
    Hardware_B.D56_tmp_tmp_m) + Hardware_B.d29 * Hardware_B.D56_tmp_tmp_m) +
    Hardware_B.d30 * Hardware_B.D56_tmp_tmp_m) + Hardware_B.d23 *
    Hardware_B.D56_tmp_tmp_m) + Hardware_B.d25 * Hardware_B.D46_tmp_tmp_c) +
    Hardware_B.tmp_tmp_d * Hardware_B.D46_tmp_tmp_c) + Hardware_B.d31 *
    Hardware_P.ArmConstants.Inertia1[7] * Hardware_B.D46_tmp_p) +
    Hardware_B.d179) + Hardware_B.d25 * Hardware_B.D56_tmp_tmp_fb) +
    Hardware_B.tmp_tmp_d * Hardware_B.D56_tmp_tmp_fb) + Hardware_B.tmp_tmp_il *
    Hardware_B.D56_tmp_bj) + Hardware_B.tmp_tmp_fa * Hardware_B.D56_tmp_bj) +
    Hardware_B.tmp_tmp_ji * Hardware_B.D56_tmp_bj) + Hardware_B.tmp_tmp_oo *
    Hardware_B.D56_tmp_bj) + Hardware_B.d173) + Hardware_B.d26 *
    Hardware_B.D46_tmp_tmp_b) + Hardware_B.d31 *
    Hardware_P.ArmConstants.Inertia2[7] * Hardware_B.D46_tmp_l) +
    Hardware_B.d180) + Hardware_B.d26 * Hardware_B.D56_tmp_tmp_h) +
    Hardware_B.tmp_tmp_j * Hardware_B.D56_tmp_tmp_c) + Hardware_B.tmp_tmp_oy *
    Hardware_B.D56_tmp_j) + Hardware_B.tmp_tmp_ln * Hardware_B.D56_tmp_j) +
    Hardware_B.tmp_tmp_lu * Hardware_B.D56_tmp_j) + Hardware_B.d181) +
    Hardware_B.d182) + Hardware_B.d145 * Hardware_B.D17) + Hardware_B.D16_tmp *
    Hardware_P.HexaConstants.Inertia[8] * Hardware_B.D17) + Hardware_B.d32 *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.D17) + Hardware_B.d32 *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.D17) + Hardware_B.d183) +
    Hardware_B.d184) + Hardware_B.D46_tmp_tmp_cj) + Hardware_B.d185) +
    Hardware_B.tmp_tmp_n * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1 *
    Hardware_B.D18) + Hardware_B.d127 * Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D18) + Hardware_B.d186) + Hardware_B.d187) +
    Hardware_B.D46_tmp_tmp_m1) + Hardware_B.d33 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D56_tmp_tmp_oc) + Hardware_B.d188) + Hardware_B.d126) +
    Hardware_B.d189) + Hardware_B.d128) + Hardware_B.d129) + Hardware_B.d190) +
    Hardware_B.d130) + Hardware_B.d131) + Hardware_B.d132) + Hardware_B.d133) -
    Hardware_B.d134) - Hardware_B.d135) - Hardware_B.d136) + Hardware_B.d137) +
    Hardware_B.d138) + Hardware_B.d139) - Hardware_B.d140) - Hardware_B.d141) +
    Hardware_B.d142) + Hardware_B.d191 * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.d44 * Hardware_B.x_tmp_cx) + 8.0 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_B.D14_tmp_j *
    Hardware_B.x_tmp_cx) + Hardware_B.d150) + Hardware_B.d151) + Hardware_B.d152)
    - Hardware_B.d153) + Hardware_B.d154) - Hardware_B.d155) - Hardware_B.d156)
                       + Hardware_B.d31 * Hardware_P.ArmConstants.Inertia1[6] *
                       Hardware_B.D46_tmp_lx) + Hardware_B.d158) -
                     Hardware_B.d159) - Hardware_B.d160) + Hardware_B.D46_tmp_mv
                   * -Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
                   Hardware_P.ArmConstants.Mass2 * Hardware_B.D56_tmp_tmp) +
                  Hardware_B.d39 * Hardware_B.D56_tmp_b) + Hardware_B.d31 *
                 Hardware_P.ArmConstants.Inertia2[6] * Hardware_B.D46_tmp_nu) +
                Hardware_B.d163) - Hardware_B.d164) - Hardware_B.d165) +
             Hardware_B.d40 * Hardware_B.D56_tmp_bs) + Hardware_B.d194) +
           Hardware_B.d195) + Hardware_B.d41 * Hardware_B.y_a) + Hardware_B.d42 *
         Hardware_B.y_a) + Hardware_B.d43 * Hardware_B.D48_tmp_tmp) +
       Hardware_B.d196) * 0.125);
  Hardware_B.d24 = Hardware_B.D14_tmp_j *
    Hardware_P.ArmConstants.Hexa_to_joint_L;
  Hardware_B.d27 = -Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7];
  Hardware_B.dv[51] = -(Hardware_B.d27 * Hardware_P.ArmConstants.Mass2 *
                        Hardware_B.d44 - Hardware_B.d24 * Hardware_B.d15);
  Hardware_B.dv[59] = -(-Hardware_P.ArmConstants.MC2 *
                        Hardware_P.ArmConstants.Mass2 * Hardware_B.d44 *
                        Hardware_B.d17);
  Hardware_B.d45 = Hardware_B.d45 * Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.d32 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.d33 = Hardware_B.d48 * Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d48 = Hardware_B.d48 * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d39 = Hardware_B.D16_tmp * Hardware_B.D46_tmp_tmp_m;
  Hardware_B.d40 = -4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3];
  Hardware_B.D14_tmp_j = Hardware_B.d31 * Hardware_P.ArmConstants.Inertia2[3];
  Hardware_B.tmp_tmp_h = Hardware_B.D14_tmp_j * Hardware_B.D46_tmp_tmp_a;
  Hardware_B.d99 = 4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3];
  Hardware_B.d161 = Hardware_B.d31 * Hardware_P.ArmConstants.Inertia1[3];
  Hardware_B.d174 = Hardware_B.d99 * Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.d175 = 4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7];
  Hardware_B.d176 = 4.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6];
  Hardware_B.d10 = ((((Hardware_B.d10 * 4.0 * Hardware_P.ArmConstants.Inertia1[6]
                       * Hardware_B.D15_tmp + Hardware_B.d161 *
                       Hardware_B.rtb_ginv_tmp_i) + Hardware_B.d174 *
                      Hardware_B.D15_tmp_g) + Hardware_B.d176 *
                     Hardware_P.ArmConstants.Inertia2[6] * Hardware_B.D15_tmp_g)
                    + Hardware_B.d175 * Hardware_P.ArmConstants.Inertia2[6] *
                    Hardware_B.D15_tmp_g) + Hardware_B.tmp_tmp_h;
  Hardware_B.tmp_tmp_o = Hardware_B.d46 * Hardware_B.D46_tmp_m;
  Hardware_B.tmp_tmp_c = Hardware_B.tmp_tmp_gf * Hardware_B.D56_tmp_da;
  Hardware_B.tmp_tmp_b = Hardware_B.tmp_tmp_d4 * Hardware_B.D56_tmp_da;
  Hardware_B.tmp_tmp_e = Hardware_B.tmp_tmp_dv * Hardware_B.D56_tmp_da;
  Hardware_B.tmp_tmp_ik = Hardware_B.d47 * Hardware_B.D56_tmp_da;
  Hardware_B.tmp_tmp_g = Hardware_B.d48 * Hardware_B.D46_tmp_tmp_ad;
  Hardware_B.tmp_tmp_nn = Hardware_B.d49 * Hardware_B.D46_tmp_n;
  Hardware_B.tmp_tmp_ce = Hardware_B.d48 * Hardware_B.D56_tmp_tmp_o;
  Hardware_B.tmp_tmp_nc = Hardware_B.tmp_tmp_jo * Hardware_B.D56_tmp_e;
  Hardware_B.tmp_tmp_p = Hardware_B.tmp_tmp_f1 * Hardware_B.D56_tmp_e;
  Hardware_B.tmp_tmp_dk = Hardware_B.tmp_tmp_i * Hardware_B.D56_tmp_e;
  Hardware_B.tmp_tmp_oi = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia1
    [8] * Hardware_B.x_tmp_b;
  Hardware_B.d79 = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia2[8] *
    Hardware_B.x_tmp_b;
  Hardware_B.d146 = Hardware_B.D14_tmp_nb *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.d80 = Hardware_B.d146 * Hardware_B.x_tmp_b;
  Hardware_B.d148 = Hardware_B.d8 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]
    * Hardware_P.ArmConstants.Mass2;
  Hardware_B.d81 = Hardware_B.d148 * Hardware_B.x_tmp_b;
  Hardware_B.d149 = Hardware_B.D16_tmp * Hardware_B.D46_tmp_mv *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d82 = Hardware_B.d149 * Hardware_B.x_tmp_b;
  Hardware_B.d83 = Hardware_B.d50 * Hardware_B.D46_tmp_p;
  Hardware_B.tmp_tmp_gf *= Hardware_B.D56_tmp_bj;
  Hardware_B.tmp_tmp_d4 *= Hardware_B.D56_tmp_bj;
  Hardware_B.tmp_tmp_dv *= Hardware_B.D56_tmp_bj;
  Hardware_B.d84 = Hardware_B.d47 * Hardware_B.D56_tmp_bj;
  Hardware_B.d85 = Hardware_B.d48 * Hardware_B.D46_tmp_tmp_pc;
  Hardware_B.d86 = Hardware_B.d51 * Hardware_B.D46_tmp_l;
  Hardware_B.d87 = Hardware_B.d48 * Hardware_B.D56_tmp_tmp_c;
  Hardware_B.tmp_tmp_jo *= Hardware_B.D56_tmp_j;
  Hardware_B.tmp_tmp_f1 *= Hardware_B.D56_tmp_j;
  Hardware_B.tmp_tmp_i *= Hardware_B.D56_tmp_j;
  Hardware_B.d88 = Hardware_B.d40 * Hardware_P.ArmConstants.Inertia1[7] *
    Hardware_B.D17_tmp_p;
  Hardware_B.d89 = Hardware_B.D27_tmp_a * Hardware_P.ArmConstants.Inertia1[7] *
    Hardware_B.D17_tmp_p;
  Hardware_B.tmp_tmp_il *= Hardware_B.D46_tmp_g;
  Hardware_B.tmp_tmp_fa *= Hardware_B.D46_tmp_g;
  Hardware_B.tmp_tmp_ji *= Hardware_B.D46_tmp_g;
  Hardware_B.tmp_tmp_oo *= Hardware_B.D46_tmp_g;
  Hardware_B.d90 = Hardware_B.d40 * Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D17_tmp_i;
  Hardware_B.d91 = Hardware_B.D27_tmp_a * Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D17_tmp_i;
  Hardware_B.d92 = Hardware_B.D14_tmp * Hardware_P.ArmConstants.Inertia2[7] *
    Hardware_B.D17_tmp_i;
  Hardware_B.tmp_tmp_oy *= Hardware_B.D46_tmp_e;
  Hardware_B.tmp_tmp_ln *= Hardware_B.D46_tmp_e;
  Hardware_B.tmp_tmp_lu *= Hardware_B.D46_tmp_e;
  Hardware_B.tmp_tmp_j *= Hardware_B.D28;
  Hardware_B.d93 = Hardware_B.d52 * Hardware_B.D46_tmp_j;
  Hardware_B.d94 = Hardware_B.tmp_tmp_a * Hardware_B.D56_tmp_g;
  Hardware_B.d95 = Hardware_B.d53 * Hardware_B.D46_tmp_ld;
  Hardware_B.d96 = Hardware_B.tmp_tmp_fr * Hardware_B.D56_tmp_dh;
  Hardware_B.d97 = Hardware_B.d54 * Hardware_B.D46_tmp_lx;
  Hardware_B.tmp_tmp_a *= Hardware_B.D56_tmp_b;
  Hardware_B.d98 = Hardware_B.d55 * Hardware_B.D46_tmp_nu;
  Hardware_B.tmp_tmp_fr *= Hardware_B.D56_tmp_bs;
  Hardware_B.d147 = Hardware_B.d39 * Hardware_P.ArmConstants.Mass1;
  Hardware_B.d39 *= Hardware_P.ArmConstants.Mass2;
  Hardware_B.dv[28] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((Hardware_B.d36 * Hardware_B.D56_tmp_tmp_hc + Hardware_B.d10) -
    Hardware_B.d37 * Hardware_B.D56_tmp_tmp_hc) + Hardware_B.d38 *
    Hardware_B.D56_tmp_tmp_hc) + Hardware_B.d35 * Hardware_B.D56_tmp_tmp_hc) +
    Hardware_B.d45 * Hardware_B.D46_tmp_tmp_m4) + Hardware_B.d32 *
    Hardware_B.D46_tmp_tmp_m4) + Hardware_B.tmp_tmp_o) + Hardware_B.d45 *
    Hardware_B.D27) + Hardware_B.d32 * Hardware_B.D27) - Hardware_B.tmp_tmp_c) +
    Hardware_B.tmp_tmp_b) + Hardware_B.tmp_tmp_e) + Hardware_B.tmp_tmp_ik) +
    Hardware_B.tmp_tmp_g) + Hardware_B.d33 * Hardware_B.D46_tmp_tmp_k) +
    Hardware_B.tmp_tmp_nn) + Hardware_B.d33 * Hardware_B.D56_tmp_tmp_p) +
    Hardware_B.tmp_tmp_ce) - Hardware_B.tmp_tmp_nc) + Hardware_B.tmp_tmp_p) +
    Hardware_B.tmp_tmp_dk) + Hardware_B.tmp_tmp_oi) + Hardware_B.d79) +
    Hardware_B.D16_tmp * Hardware_P.HexaConstants.Inertia[0] *
    Hardware_B.x_tmp_b) + Hardware_B.d80) + Hardware_B.d147 * Hardware_B.x_tmp_b)
    + Hardware_B.d81) + Hardware_B.d39 * Hardware_B.x_tmp_b) + Hardware_B.d82) +
    Hardware_B.d36 * Hardware_B.D56_tmp_tmp_m) - Hardware_B.d37 *
    Hardware_B.D56_tmp_tmp_m) + Hardware_B.d38 * Hardware_B.D56_tmp_tmp_m) +
    Hardware_B.d35 * Hardware_B.D56_tmp_tmp_m) + Hardware_B.d45 *
    Hardware_B.D46_tmp_tmp_c) + Hardware_B.d32 * Hardware_B.D46_tmp_tmp_c) +
    Hardware_B.d83) + Hardware_B.d45 * Hardware_B.D56_tmp_tmp_fb) +
    Hardware_B.d32 * Hardware_B.D56_tmp_tmp_fb) - Hardware_B.tmp_tmp_gf) +
    Hardware_B.tmp_tmp_d4) + Hardware_B.tmp_tmp_dv) + Hardware_B.d84) +
    Hardware_B.d85) + Hardware_B.d33 * Hardware_B.D46_tmp_tmp_b) +
    Hardware_B.d86) + Hardware_B.d33 * Hardware_B.D56_tmp_tmp_h) +
    Hardware_B.d87) - Hardware_B.tmp_tmp_jo) + Hardware_B.tmp_tmp_f1) +
    Hardware_B.tmp_tmp_i) + Hardware_B.d28 * Hardware_B.D17) + Hardware_B.d29 *
    Hardware_B.D17) + Hardware_B.d30 * Hardware_B.D17) + Hardware_B.d23 *
    Hardware_B.D17) + Hardware_B.d88) + Hardware_B.d89) + Hardware_B.tmp_tmp_il)
    + Hardware_B.tmp_tmp_fa) + Hardware_B.tmp_tmp_ji) + Hardware_B.tmp_tmp_oo) +
                        Hardware_B.d25 * Hardware_B.D18) + Hardware_B.tmp_tmp_d *
                       Hardware_B.D18) + Hardware_B.d90) + Hardware_B.d91) +
                    Hardware_B.d92) + Hardware_B.tmp_tmp_oy) +
                  Hardware_B.tmp_tmp_ln) + Hardware_B.tmp_tmp_lu) +
                Hardware_B.d26 * Hardware_B.D56_tmp_tmp_oc) +
               Hardware_B.tmp_tmp_j) + Hardware_B.d93) + Hardware_B.d94) +
            Hardware_B.d95) + Hardware_B.d96) + Hardware_B.d97) +
         Hardware_B.tmp_tmp_a) + Hardware_B.d98) + Hardware_B.tmp_tmp_fr) * 0.25);
  Hardware_B.d23 = Hardware_B.D25 * Hardware_B.rtb_ginv_tmp_i + Hardware_B.D15 *
    Hardware_B.D46_tmp_tmp_a;
  Hardware_B.d25 = Hardware_B.D46_tmp_tmp_pr * Hardware_B.D28;
  Hardware_B.tmp_tmp_d = 2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7];
  Hardware_B.d26 = -Hardware_P.ArmConstants.MC1 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.d28 = Hardware_B.D24_tmp * Hardware_B.smax;
  Hardware_B.d29 = Hardware_B.D24_tmp_a * Hardware_B.D18;
  Hardware_B.d30 = Hardware_B.D47_tmp_tmp * Hardware_B.D14_tmp_p;
  Hardware_B.d35 = Hardware_B.D47_tmp_tmp * Hardware_B.D56_tmp_tmp_oc;
  Hardware_B.d36 = (Hardware_B.D47_tmp_tmp * Hardware_B.x_tmp_k +
                    Hardware_B.D48_tmp * Hardware_B.D15_tmp) +
    (Hardware_B.D47_tmp + Hardware_B.D34) * Hardware_B.D15_tmp_g;
  Hardware_B.dv[36] = -((((((((((((((((((Hardware_B.d23 - Hardware_B.d9) +
    Hardware_B.D16_tmp_e) - Hardware_B.d11) - Hardware_B.d13) +
    Hardware_B.D16_tmp_j) - Hardware_B.d19) - Hardware_B.D14_tmp_cz) -
    Hardware_B.rtb_ginv_tmp_tmp_f) + Hardware_B.D46_tmp_jp * Hardware_B.D18) +
    Hardware_B.D46_tmp_k * Hardware_B.D18) + Hardware_B.rtb_ginv_tmp_l) -
    Hardware_B.D16_tmp_m) - Hardware_B.D27_tmp) + Hardware_B.D46_tmp_mx *
    Hardware_B.D56_tmp_tmp_oc) + Hardware_B.d25) *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] + (-2.0 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7] * Hardware_B.d36 *
    Hardware_B.D17_tmp_i + Hardware_B.tmp_tmp_d *
    Hardware_P.ArmConstants.Inertia2[3] * Hardware_B.D46_tmp_tmp_a)) +
    (((((((((((((-Hardware_P.ArmConstants.Hexa_to_joint_L *
                 Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
                 Hardware_B.smax + (Hardware_B.d23 - Hardware_B.d28)) +
                Hardware_B.D16_tmp_j) - Hardware_B.d19) - Hardware_B.D14_tmp_cz)
             - Hardware_B.rtb_ginv_tmp_tmp_f) + Hardware_B.d26 * Hardware_B.D18)
           - Hardware_B.d29) - Hardware_B.d30) + Hardware_B.rtb_ginv_tmp_l) -
        Hardware_B.D16_tmp_m) - Hardware_B.D27_tmp) - Hardware_B.d35) +
     Hardware_B.d25) * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6]) * 0.5);
  Hardware_B.d9 = 4.0 * Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.D16_tmp_e = 4.0 * Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.d11 = -4.0 * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.d13 = -4.0 * Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.d23 = Hardware_B.D47_tmp_tmp * Hardware_B.D46_tmp_tmp_k;
  Hardware_B.d25 = Hardware_B.D47_tmp_tmp * Hardware_B.D56_tmp_tmp_p;
  Hardware_B.d37 = Hardware_B.D47_tmp_tmp * Hardware_B.D46_tmp_tmp_b;
  Hardware_B.d38 = Hardware_B.D47_tmp_tmp * Hardware_B.D56_tmp_tmp_h;
  Hardware_B.d100 = Hardware_B.D47_tmp_d * Hardware_B.D46_tmp_tmp_m4;
  Hardware_B.D47_tmp_d = Hardware_B.D24_tmp * Hardware_B.D46_tmp_tmp_c;
  Hardware_B.d101 = Hardware_B.D24_tmp_a * Hardware_B.D46_tmp_tmp_c;
  Hardware_B.d102 = Hardware_B.D48_tmp * Hardware_B.D46_tmp_tmp_ad +
    Hardware_B.d23;
  Hardware_B.d103 = Hardware_B.D48_tmp * Hardware_B.D46_tmp_tmp_pc;
  Hardware_B.D14_tmp_md = ((Hardware_B.d100 + Hardware_B.D14_tmp_md) +
    Hardware_B.D24_tmp * Hardware_B.D27) + Hardware_B.D24_tmp_a * Hardware_B.D27;
  Hardware_B.d192 = Hardware_B.D24_tmp * Hardware_B.D56_tmp_tmp_fb;
  Hardware_B.d193 = Hardware_B.D24_tmp_a * Hardware_B.D56_tmp_tmp_fb;
  Hardware_B.D14_tmp_m3 =
    (((((((((((((((((((((((((((((((((((((((((Hardware_B.D14_tmp_md -
    Hardware_B.D14_tmp_m3) + Hardware_B.D14_tmp_tmp_cg) +
    Hardware_B.D14_tmp_tmp_f) + Hardware_B.D14_tmp_h) + Hardware_B.D15_tmp_tmp_d)
    + Hardware_B.d23) + Hardware_B.D15_tmp_tmp_n) + Hardware_B.d25) +
    Hardware_B.D16_tmp_tmp) - Hardware_B.D34_tmp_m) + Hardware_B.D37_tmp) +
    Hardware_B.D46_tmp_tmp_p) + Hardware_B.rtb_ginv_tmp_k) + Hardware_B.d56) +
    Hardware_B.d57) + Hardware_B.d58) + Hardware_B.d59) + Hardware_B.D47_tmp_d)
    + Hardware_B.d101) + Hardware_B.d60) + Hardware_B.d192) + Hardware_B.d193) -
                       Hardware_B.d61) + Hardware_B.d62) + Hardware_B.d63) +
                    Hardware_B.d64) + Hardware_B.d65) + Hardware_B.d37) +
                 Hardware_B.d66) + Hardware_B.d38) + Hardware_B.d67) -
              Hardware_B.d68) + Hardware_B.d69) + Hardware_B.d70) +
           Hardware_B.d71) + Hardware_B.d72) + Hardware_B.d73) + Hardware_B.d74)
       + Hardware_B.d75) + Hardware_B.d76) + Hardware_B.d77) + Hardware_B.d78;
  Hardware_B.d197 = (((((((((((((((((((Hardware_B.d102 +
    Hardware_B.D15_tmp_tmp_n) + Hardware_B.d25) + Hardware_B.D48_tmp *
    Hardware_B.D56_tmp_tmp_o) - Hardware_B.D34_tmp_m) + Hardware_B.D37_tmp) +
    Hardware_B.D46_tmp_tmp_p) + Hardware_B.d56) + Hardware_B.d58) +
    Hardware_B.d103) + Hardware_B.d37) + Hardware_B.d66) + Hardware_B.d38) +
    Hardware_B.D48_tmp * Hardware_B.D56_tmp_tmp_c) - Hardware_B.d68) +
    Hardware_B.d69) + Hardware_B.d70) + Hardware_B.d73) + Hardware_B.d74) +
                     Hardware_B.d77) + Hardware_B.d78;
  Hardware_B.dv[44] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((Hardware_B.d9
    * Hardware_B.rtb_ginv_tmp_tmp_o + Hardware_B.D16_tmp_e * Hardware_B.D68) +
    Hardware_B.D25 * Hardware_B.rtb_ginv_tmp_ox) + Hardware_B.D15 *
    Hardware_B.D46_tmp_tmp_i) + Hardware_B.D56_tmp_l * Hardware_B.d) +
    Hardware_B.D56_tmp_h * Hardware_B.D46_tmp_tmp_iz) + Hardware_B.d9 *
    Hardware_B.d1) + Hardware_B.D16_tmp_e * Hardware_B.d2) +
    Hardware_B.D46_tmp_tmp_pr * Hardware_B.D46_tmp_tmp) + Hardware_B.D46_tmp_jp *
    Hardware_B.d3) + Hardware_B.D46_tmp_k * Hardware_B.d3) + Hardware_B.d11 *
    Hardware_B.ab_a) + Hardware_B.D46_tmp_jp * Hardware_B.D56_tmp_tmp_f) +
    Hardware_B.D46_tmp_k * Hardware_B.D56_tmp_tmp_f) + Hardware_B.D46_tmp_tmp_pr
    * Hardware_B.d6) + Hardware_B.D46_tmp_mx * Hardware_B.D37) + Hardware_B.d13 *
    Hardware_B.D67) + Hardware_B.D46_tmp_mx * Hardware_B.D56_tmp_tmp_e) +
    Hardware_P.HexaConstants.Inertia[8] * Hardware_B.d4) +
    Hardware_P.ArmConstants.Inertia1[0] * Hardware_B.D38) -
    Hardware_P.ArmConstants.Inertia1[4] * Hardware_B.D38) - Hardware_B.D47_tmp_c
    * Hardware_B.D38) - Hardware_B.D47_tmp_k * Hardware_B.D38) +
    Hardware_P.ArmConstants.Inertia2[0] * Hardware_B.D47_tmp_i) -
    Hardware_P.ArmConstants.Inertia2[4] * Hardware_B.D47_tmp_i) +
    -Hardware_B.D46_tmp_lm * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D47_tmp_i) + -2.0 * Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_B.D46_tmp_d) + -2.0 * Hardware_P.ArmConstants.Inertia1[4] *
    Hardware_B.D46_tmp_d) + 4.0 * Hardware_P.ArmConstants.Inertia1[8] *
    Hardware_B.D46_tmp_d) + -2.0 * Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_B.D46_tmp_d) + -2.0 * Hardware_P.ArmConstants.Inertia2[4] *
    Hardware_B.D46_tmp_d) + 4.0 * Hardware_P.ArmConstants.Inertia2[8] *
    Hardware_B.D46_tmp_d) + 4.0 * Hardware_P.HexaConstants.Inertia[0] *
    Hardware_B.D46_tmp_d) + -2.0 * Hardware_P.HexaConstants.Inertia[4] *
    Hardware_B.D46_tmp_d) + -2.0 * Hardware_P.HexaConstants.Inertia[8] *
    Hardware_B.D46_tmp_d) + Hardware_B.d18 * Hardware_B.D46_tmp_d) +
    Hardware_B.d20 * Hardware_B.D46_tmp_d) + Hardware_B.d21 *
    Hardware_B.D46_tmp_d) + Hardware_B.D14_tmp_ch * Hardware_B.D46_tmp_d) +
    Hardware_B.D14_tmp_f * Hardware_B.D46_tmp_d) +
    Hardware_P.HexaConstants.Inertia[4] * Hardware_B.D47) + Hardware_B.D56_tmp_p
    * Hardware_B.D47) + Hardware_B.D56_tmp_p4 * Hardware_B.D47) +
    Hardware_P.HexaConstants.Inertia[4] * Hardware_B.D48_tmp_p) -
    Hardware_P.HexaConstants.Inertia[8] * Hardware_B.D48_tmp_p) +
    Hardware_B.D56_tmp_p * Hardware_B.D48_tmp_p) + Hardware_B.D56_tmp_p4 *
    Hardware_B.D48_tmp_p) - Hardware_P.ArmConstants.Inertia1[0] *
                        Hardware_B.D56_tmp_tmp) +
                       Hardware_P.ArmConstants.Inertia1[4] *
                       Hardware_B.D56_tmp_tmp) + Hardware_B.D47_tmp_c *
                      Hardware_B.D56_tmp_tmp) + Hardware_B.D47_tmp_k *
                     Hardware_B.D56_tmp_tmp) - Hardware_P.ArmConstants.Inertia2
                    [0] * Hardware_B.D58) + Hardware_P.ArmConstants.Inertia2[4] *
                   Hardware_B.D58) + Hardware_B.D47_tmp * Hardware_B.D58) +
                 Hardware_B.D46_tmp_mc * Hardware_B.d5) + Hardware_B.D46_tmp_h3 *
                Hardware_B.d5) + Hardware_B.d11 * Hardware_B.D15_tmp_tmp) +
              Hardware_B.D46_tmp_mj * Hardware_B.d7) + Hardware_B.D46_tmp_pc *
             Hardware_B.D14_tmp_tmp) + Hardware_B.d13 * Hardware_B.D15_tmp_tmp_o)
           + Hardware_B.D46_tmp_mc * Hardware_B.y_a) + Hardware_B.D46_tmp_h3 *
          Hardware_B.y_a) + Hardware_B.D46_tmp_pc * Hardware_B.D48_tmp_tmp) +
        Hardware_B.D46_tmp_mj * Hardware_B.D46_tmp_tmp_f) * (-0.5 *
        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) + ((Hardware_B.D14_tmp_m3
         * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] + Hardware_B.d197 *
         Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7]) + Hardware_B.D14_tmp_m *
        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3])) * 0.25);
  Hardware_B.D38 = Hardware_P.ArmConstants.MC1 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D47 = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D48_tmp_p = Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.D58 = Hardware_B.D48_tmp_p *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.d4 = Hardware_B.D46_tmp_nr *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D14_tmp_ch = Hardware_B.d22 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d9 = Hardware_B.D46_tmp_c *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.D16_tmp_e = Hardware_B.d9 * Hardware_P.ArmConstants.Hexa_to_joint_L
    * Hardware_P.ArmConstants.Mass2;
  Hardware_B.d11 = Hardware_B.D58 * Hardware_B.D46_tmp_tmp_k;
  Hardware_B.d13 = Hardware_B.D58 * Hardware_B.D56_tmp_tmp_p;
  Hardware_B.d18 = Hardware_B.D58 * Hardware_B.D46_tmp_tmp_b;
  Hardware_B.d20 = Hardware_B.D58 * Hardware_B.D56_tmp_tmp_h;
  Hardware_B.d21 = Hardware_B.D16_tmp_e * Hardware_B.D14_tmp_p;
  Hardware_B.D14_tmp_f = Hardware_B.D16_tmp_e * Hardware_B.D56_tmp_tmp_oc;
  Hardware_B.dv[52] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((Hardware_B.D38
    * Hardware_B.D46_tmp_tmp_m4 + Hardware_B.d10) + Hardware_B.D47 *
    Hardware_B.D46_tmp_tmp_m4) + Hardware_B.tmp_tmp_o) + Hardware_B.D38 *
    Hardware_B.D27) + Hardware_B.D47 * Hardware_B.D27) - Hardware_B.tmp_tmp_c) +
    Hardware_B.tmp_tmp_b) + Hardware_B.tmp_tmp_e) + Hardware_B.tmp_tmp_ik) +
    Hardware_B.tmp_tmp_g) + Hardware_B.d11) + Hardware_B.tmp_tmp_nn) +
    Hardware_B.d13) + Hardware_B.tmp_tmp_ce) - Hardware_B.tmp_tmp_nc) +
    Hardware_B.tmp_tmp_p) + Hardware_B.tmp_tmp_dk) + Hardware_B.tmp_tmp_oi) +
    Hardware_B.d79) + Hardware_B.d80) + Hardware_B.d81) + Hardware_B.d82) +
    Hardware_B.D38 * Hardware_B.D46_tmp_tmp_c) + Hardware_B.D47 *
    Hardware_B.D46_tmp_tmp_c) + Hardware_B.d83) + Hardware_B.D38 *
    Hardware_B.D56_tmp_tmp_fb) + Hardware_B.D47 * Hardware_B.D56_tmp_tmp_fb) -
    Hardware_B.tmp_tmp_gf) + Hardware_B.tmp_tmp_d4) + Hardware_B.tmp_tmp_dv) +
    Hardware_B.d84) + Hardware_B.d85) + Hardware_B.d18) + Hardware_B.d86) +
    Hardware_B.d20) + Hardware_B.d87) - Hardware_B.tmp_tmp_jo) +
    Hardware_B.tmp_tmp_f1) + Hardware_B.tmp_tmp_i) + Hardware_B.d4 *
    Hardware_B.smax) + Hardware_B.D14_tmp_ch * Hardware_B.smax) + Hardware_B.d88)
    + Hardware_B.d89) + Hardware_B.tmp_tmp_il) + Hardware_B.tmp_tmp_fa) +
    Hardware_B.tmp_tmp_ji) + Hardware_B.tmp_tmp_oo) + Hardware_B.d4 *
    Hardware_B.D18) + Hardware_B.D14_tmp_ch * Hardware_B.D18) + Hardware_B.d21)
                      + Hardware_B.d90) + Hardware_B.d91) + Hardware_B.d92) +
                   Hardware_B.tmp_tmp_oy) + Hardware_B.tmp_tmp_ln) +
                 Hardware_B.tmp_tmp_lu) + Hardware_B.D14_tmp_f) +
               Hardware_B.tmp_tmp_j) + Hardware_B.d93) + Hardware_B.d94) +
            Hardware_B.d95) + Hardware_B.d96) + Hardware_B.d97) +
         Hardware_B.tmp_tmp_a) + Hardware_B.d98) + Hardware_B.tmp_tmp_fr) * 0.25);
  Hardware_B.D48_tmp_p = Hardware_B.D48_tmp_p * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.d9 = Hardware_B.d9 * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.dv[60] = -((((((((((((((((((((((((((((((((((Hardware_B.d16 * 4.0 *
    Hardware_P.ArmConstants.Inertia2[6] * Hardware_B.D15_tmp_g +
    Hardware_B.tmp_tmp_h) + Hardware_B.D48_tmp_p * Hardware_B.D46_tmp_tmp_ad) +
    Hardware_B.d11) + Hardware_B.tmp_tmp_nn) + Hardware_B.d13) +
    Hardware_B.D48_tmp_p * Hardware_B.D56_tmp_tmp_o) - Hardware_B.tmp_tmp_nc) +
    Hardware_B.tmp_tmp_p) + Hardware_B.tmp_tmp_dk) + Hardware_B.d79) +
    Hardware_B.d81) + Hardware_B.D48_tmp_p * Hardware_B.D46_tmp_tmp_pc) +
    Hardware_B.d18) + Hardware_B.d86) + Hardware_B.d20) + Hardware_B.D48_tmp_p *
    Hardware_B.D56_tmp_tmp_c) - Hardware_B.tmp_tmp_jo) + Hardware_B.tmp_tmp_f1)
    + Hardware_B.tmp_tmp_i) + Hardware_B.d9 * Hardware_B.s) + Hardware_B.d21) +
    Hardware_B.d90) + Hardware_B.d91) + Hardware_B.d92) + Hardware_B.tmp_tmp_oy)
    + Hardware_B.tmp_tmp_ln) + Hardware_B.tmp_tmp_lu) + Hardware_B.D14_tmp_f) +
    Hardware_B.d9 * Hardware_B.D28) + Hardware_B.d95) + Hardware_B.d96) +
    Hardware_B.d98) + Hardware_B.tmp_tmp_fr) * 0.25);
  Hardware_B.d10 = Hardware_P.ArmConstants.Inertia2[7] * Hardware_B.D46_tmp_n;
  Hardware_B.d11 = Hardware_P.ArmConstants.Inertia2[7] * Hardware_B.D46_tmp_l;
  Hardware_B.d13 = Hardware_P.ArmConstants.Inertia2[6] * Hardware_B.D46_tmp_ld;
  Hardware_B.d16 = Hardware_P.ArmConstants.Inertia2[6] * Hardware_B.D46_tmp_nu;
  Hardware_B.d18 = Hardware_B.D56_tmp_h * Hardware_B.D46_tmp_e;
  Hardware_B.d20 = Hardware_B.D46_tmp_tmp_pr * Hardware_B.D46_tmp_ol;
  Hardware_B.d21 = Hardware_B.D56_tmp_l * Hardware_B.D46_tmp_g;
  Hardware_B.D14_tmp_f = Hardware_P.ArmConstants.Inertia2[0] *
    Hardware_B.D56_tmp_bs;
  Hardware_B.D14_tmp_m = (Hardware_B.d102 + Hardware_B.d10) - Hardware_B.d103;
  Hardware_B.d10 = (((((((((((Hardware_P.ArmConstants.Inertia1[7] *
    Hardware_B.D46_tmp_m + Hardware_B.d100) + Hardware_B.d23) + Hardware_B.d10)
    - Hardware_B.D47_tmp_d) - Hardware_B.d101) +
    Hardware_P.ArmConstants.Inertia1[7] * Hardware_B.D46_tmp_p) - Hardware_B.d37)
                       + Hardware_B.d11) + Hardware_P.ArmConstants.Inertia1[6] *
                      Hardware_B.D46_tmp_j) + Hardware_B.d13) +
                    Hardware_P.ArmConstants.Inertia1[6] * Hardware_B.D46_tmp_lx)
    + Hardware_B.d16;
  Hardware_B.dv[29] = -(((((((((((((((((((((Hardware_B.rtb_ginv_tmp_cx -
    Hardware_B.tmp_tmp_l * Hardware_B.rtb_ginv_tmp_n) +
    Hardware_B.rtb_ginv_tmp_f) + Hardware_P.ArmConstants.Inertia1[0] *
    Hardware_B.rtb_ginv_tmp_i) - Hardware_B.rtb_ginv_tmp_if) -
    Hardware_B.rtb_ginv_tmp_d) - Hardware_B.rtb_ginv_tmp_g) +
    Hardware_B.D46_tmp_jp * Hardware_B.D46_tmp_h) + Hardware_B.D46_tmp_k *
    Hardware_B.D46_tmp_h) + Hardware_B.D47_tmp_p) + Hardware_B.rtb_ginv_tmp_ie)
    + Hardware_B.D14) - Hardware_B.D24) - Hardware_B.D35) +
    Hardware_B.D46_tmp_mx * Hardware_B.rtb_ginv_tmp) + Hardware_B.d20) +
    Hardware_B.d21) + Hardware_B.d18) * Hardware_B.d22 + Hardware_B.D45 *
    Hardware_B.d99) + (((Hardware_B.D56_tmp - Hardware_B.D14_tmp_f) +
                        Hardware_B.D56_tmp_g4) + Hardware_B.D56_tmp_c3) *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) * Hardware_B.x_tmp_b +
    (((((-Hardware_P.ArmConstants.MC2 * Hardware_P.ArmConstants.Hexa_to_joint_L *
         Hardware_P.ArmConstants.Mass2 * Hardware_B.D46_tmp_tmp_b +
         Hardware_B.D14_tmp_m) + Hardware_B.d11) + Hardware_B.d13) +
      Hardware_B.d16) * Hardware_B.tmp_tmp_d + Hardware_B.d10 *
     Hardware_B.tmp_tmp)) * 0.25);
  Hardware_B.tmp_tmp = 2.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3];
  Hardware_B.tmp_tmp_l = Hardware_B.tmp_tmp * Hardware_B.D46_tmp_tmp_m;
  Hardware_B.D15_tmp_g = Hardware_B.tmp_tmp_f *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3];
  Hardware_B.D45 = 4.0 * Hardware_P.ArmConstants.MC2;
  Hardware_B.D46_tmp_c = Hardware_B.D45 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3];
  Hardware_B.tmp_tmp_f = Hardware_B.d40 * Hardware_B.D46_tmp_tmp_m;
  Hardware_B.tmp_tmp_d = Hardware_B.tmp_tmp * Hardware_P.HexaConstants.Inertia[4];
  Hardware_B.tmp_tmp_j = Hardware_B.tmp_tmp_dd *
    Hardware_P.HexaConstants.Inertia[8];
  Hardware_B.tmp_tmp_i = Hardware_B.tmp_tmp_l * Hardware_P.ArmConstants.Mass1;
  Hardware_B.tmp_tmp_l *= Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_h = Hardware_B.d12 * Hardware_B.D46_tmp_tmp_m;
  Hardware_B.D46_tmp_lm = Hardware_B.tmp_tmp_n *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D46_tmp_mj = Hardware_B.d40 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_mc = 4.0 * Hardware_P.ArmConstants.MC1;
  Hardware_B.D46_tmp_h3 = Hardware_B.D46_tmp_mc *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D46_tmp_pc = Hardware_B.d99 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_n = Hardware_B.tmp_tmp_dd *
    Hardware_P.ArmConstants.Inertia1[0];
  Hardware_B.tmp_tmp_o = Hardware_B.tmp_tmp * Hardware_P.ArmConstants.Inertia1[4];
  Hardware_B.tmp_tmp_c = Hardware_B.D14_tmp_nb *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.tmp_tmp_b = Hardware_B.tmp_tmp * Hardware_B.D46_tmp_mv *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_nr = Hardware_B.D15_tmp_g * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D15_tmp_g = Hardware_B.D15_tmp_g *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D47_tmp = Hardware_B.D46_tmp_c *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.D46_tmp_c = Hardware_B.D46_tmp_c * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_e = Hardware_B.D45 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.tmp_tmp_dd *= Hardware_P.ArmConstants.Inertia2[0];
  Hardware_B.tmp_tmp *= Hardware_P.ArmConstants.Inertia2[4];
  Hardware_B.tmp_tmp_ik = Hardware_B.d8 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp_g = Hardware_B.D14_tmp_jg *
    Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.tmp_tmp_nn = Hardware_B.D14_tmp_jg *
    Hardware_P.ArmConstants.Inertia2[6];
  Hardware_B.tmp_tmp_ce = Hardware_B.D47_tmp_tmp * Hardware_B.rtb_ginv_tmp;
  Hardware_B.tmp_tmp_nc = Hardware_B.d99 * Hardware_P.ArmConstants.Inertia1[3];
  Hardware_B.tmp_tmp_p = Hardware_B.d99 * Hardware_P.ArmConstants.Inertia2[3];
  Hardware_B.tmp_tmp_dk = Hardware_B.d127 * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.tmp_tmp_oi = Hardware_B.d127 * Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.D47_tmp_tmp = Hardware_P.ArmConstants.Inertia1[0] -
    Hardware_P.ArmConstants.Inertia1[4];
  Hardware_B.D56_tmp = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia1[3];
  Hardware_B.D56_tmp_h = Hardware_B.d22 * Hardware_P.ArmConstants.Inertia1[0];
  Hardware_B.D56_tmp_p = Hardware_B.d12 * Hardware_P.ArmConstants.Inertia1[4];
  Hardware_B.D56_tmp_p4 = Hardware_B.D14_tmp_nb *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass1;
  Hardware_B.rtb_ginv_tmp = Hardware_B.d12 * Hardware_B.D46_tmp_mv *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.rtb_ginv_tmp_n = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia2
    [3];
  Hardware_B.rtb_ginv_tmp_f = Hardware_B.tmp_tmp_e *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2;
  Hardware_B.rtb_ginv_tmp_ie = Hardware_B.d22 *
    Hardware_P.ArmConstants.Inertia2[0];
  Hardware_B.rtb_ginv_tmp_cx = Hardware_B.d12 *
    Hardware_P.ArmConstants.Inertia2[4];
  Hardware_B.rtb_ginv_tmp_if = Hardware_B.d8 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.rtb_ginv_tmp_d = Hardware_B.D46_tmp_lm * Hardware_B.D46_tmp_tmp_c;
  Hardware_B.rtb_ginv_tmp_g = Hardware_B.D46_tmp_mj * Hardware_B.D46_tmp_tmp_c;
  Hardware_B.tmp_tmp_a = Hardware_B.D56_tmp * Hardware_B.d;
  Hardware_B.tmp_tmp_il = Hardware_B.D56_tmp_h * Hardware_B.D56_tmp_bj;
  Hardware_B.tmp_tmp_fa = Hardware_B.D56_tmp_p * Hardware_B.D56_tmp_bj;
  Hardware_B.tmp_tmp_ji = Hardware_B.D56_tmp_p4 * Hardware_B.D56_tmp_bj;
  Hardware_B.tmp_tmp_oo = Hardware_B.rtb_ginv_tmp * Hardware_B.D56_tmp_bj;
  Hardware_B.tmp_tmp_fr = Hardware_B.D15_tmp_g * Hardware_B.D46_tmp_tmp_b;
  Hardware_B.tmp_tmp_oy = Hardware_B.rtb_ginv_tmp_n * Hardware_B.D46_tmp_tmp_iz;
  Hardware_B.tmp_tmp_ln = Hardware_B.rtb_ginv_tmp_f * Hardware_B.D56_tmp_tmp_c;
  Hardware_B.tmp_tmp_lu = Hardware_B.rtb_ginv_tmp_ie * Hardware_B.D56_tmp_j;
  Hardware_B.tmp_tmp_gf = Hardware_B.rtb_ginv_tmp_cx * Hardware_B.D56_tmp_j;
  Hardware_B.tmp_tmp_d4 = Hardware_B.rtb_ginv_tmp_if * Hardware_B.D56_tmp_j;
  Hardware_B.tmp_tmp_dv = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia1[0];
  Hardware_B.tmp_tmp_jo = Hardware_B.d14 * Hardware_P.ArmConstants.Inertia2[0];
  Hardware_B.tmp_tmp_f1 = Hardware_B.D46_tmp_nr * Hardware_B.D46_tmp_tmp_pc;
  Hardware_B.D46_tmp_lm *= Hardware_B.D46_tmp_tmp_m4;
  Hardware_B.D46_tmp_mj *= Hardware_B.D46_tmp_tmp_m4;
  Hardware_B.D15_tmp_g *= Hardware_B.D46_tmp_tmp_k;
  Hardware_B.D46_tmp_nr *= Hardware_B.D46_tmp_tmp_ad;
  Hardware_B.D46_tmp_tmp_iz = Hardware_B.d47 * Hardware_B.D56_tmp_tmp;
  Hardware_B.d = Hardware_B.d161 * Hardware_B.D56_tmp_b;
  Hardware_B.D14_tmp_nb = Hardware_B.D14_tmp_j * Hardware_B.D56_tmp_bs;
  Hardware_B.d8 = Hardware_B.d48 * Hardware_B.D46_tmp_tmp_f;
  tmp =
    (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((((((((((((((((Hardware_B.tmp_tmp_g *
    Hardware_B.rtb_ginv_tmp_tmp_o + Hardware_B.tmp_tmp_nn * Hardware_B.D68) +
    Hardware_B.tmp_tmp_d * Hardware_B.D56_tmp_tmp_hc) + Hardware_B.d104) +
    Hardware_B.tmp_tmp_j * Hardware_B.D56_tmp_tmp_hc) + Hardware_B.d105) +
    Hardware_B.tmp_tmp_i * Hardware_B.D56_tmp_tmp_hc) + Hardware_B.d106) +
    Hardware_B.tmp_tmp_l * Hardware_B.D56_tmp_tmp_hc) + Hardware_B.d107) +
    Hardware_B.D46_tmp_lm) + Hardware_B.D46_tmp_mj) + Hardware_B.d108) +
    Hardware_B.d109) + Hardware_B.D46_tmp_h3 * Hardware_B.D27) + Hardware_B.d110)
    + Hardware_B.D46_tmp_pc * Hardware_B.D27) + Hardware_B.d111) +
    Hardware_B.tmp_tmp_n * Hardware_B.D56_tmp_da) + Hardware_B.d112) +
    Hardware_B.tmp_tmp_o * Hardware_B.D56_tmp_da) + Hardware_B.d113) +
    Hardware_B.tmp_tmp_c * Hardware_B.D56_tmp_da) + Hardware_B.d114) +
    Hardware_B.tmp_tmp_b * Hardware_B.D56_tmp_da) + Hardware_B.d115) +
    Hardware_B.D46_tmp_nr) + Hardware_B.D15_tmp_g) + Hardware_B.d116) +
    Hardware_B.d117) + Hardware_B.D47_tmp * Hardware_B.D56_tmp_tmp_p) +
    Hardware_B.d118) + Hardware_B.D46_tmp_c * Hardware_B.D56_tmp_tmp_o) +
    Hardware_B.d119) + Hardware_B.tmp_tmp_dd * Hardware_B.D56_tmp_e) +
    Hardware_B.d120) + Hardware_B.tmp_tmp * Hardware_B.D56_tmp_e) +
    Hardware_B.d121) + Hardware_B.tmp_tmp_ik * Hardware_B.D56_tmp_e) +
    Hardware_B.d122) + Hardware_B.d40 * Hardware_P.ArmConstants.Inertia1[8] *
    Hardware_B.x_tmp_b) + Hardware_B.d40 * Hardware_P.ArmConstants.Inertia2[8] *
    Hardware_B.x_tmp_b) + Hardware_B.d40 * Hardware_P.HexaConstants.Inertia[0] *
    Hardware_B.x_tmp_b) + Hardware_B.D46_tmp_o *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp_b) + Hardware_B.tmp_tmp_f *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.x_tmp_b) + Hardware_B.d123 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_b) + Hardware_B.tmp_tmp_f *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_b) + Hardware_B.d40 *
    Hardware_B.D46_tmp_mv * Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_b)
    + Hardware_B.tmp_tmp_d * Hardware_B.D56_tmp_tmp_m) + Hardware_B.d12 *
    Hardware_P.HexaConstants.Inertia[4] * Hardware_B.D56_tmp_tmp_m) +
    Hardware_B.tmp_tmp_j * Hardware_B.D56_tmp_tmp_m) + Hardware_B.d22 *
    Hardware_P.HexaConstants.Inertia[8] * Hardware_B.D56_tmp_tmp_m) +
    Hardware_B.tmp_tmp_i * Hardware_B.D56_tmp_tmp_m) + Hardware_B.tmp_tmp_h *
    Hardware_P.ArmConstants.Mass1 * Hardware_B.D56_tmp_tmp_m) +
    Hardware_B.tmp_tmp_l * Hardware_B.D56_tmp_tmp_m) + Hardware_B.tmp_tmp_h *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.D56_tmp_tmp_m) +
    Hardware_B.rtb_ginv_tmp_d) + Hardware_B.rtb_ginv_tmp_g) + Hardware_B.d124 *
    Hardware_B.D46_tmp_p) + Hardware_B.tmp_tmp_a) + Hardware_B.D46_tmp_h3 *
    Hardware_B.D56_tmp_tmp_fb) + Hardware_B.D46_tmp_mc *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1 *
    Hardware_B.D56_tmp_tmp_fb) + Hardware_B.D46_tmp_pc *
    Hardware_B.D56_tmp_tmp_fb) + Hardware_B.d31 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.D56_tmp_tmp_fb) +
    Hardware_B.tmp_tmp_n * Hardware_B.D56_tmp_bj) + Hardware_B.tmp_tmp_il) +
    Hardware_B.tmp_tmp_o * Hardware_B.D56_tmp_bj) + Hardware_B.tmp_tmp_fa) +
    Hardware_B.tmp_tmp_c * Hardware_B.D56_tmp_bj) + Hardware_B.tmp_tmp_ji) +
    Hardware_B.tmp_tmp_b * Hardware_B.D56_tmp_bj) + Hardware_B.tmp_tmp_oo) +
    Hardware_B.tmp_tmp_f1) + Hardware_B.tmp_tmp_fr) + Hardware_B.d125 *
    Hardware_B.D46_tmp_l) + Hardware_B.tmp_tmp_oy) + Hardware_B.D47_tmp *
    Hardware_B.D56_tmp_tmp_h) + Hardware_B.tmp_tmp_e *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D56_tmp_tmp_h) + Hardware_B.D46_tmp_c * Hardware_B.D56_tmp_tmp_c)
    + Hardware_B.tmp_tmp_ln) + Hardware_B.tmp_tmp_dd * Hardware_B.D56_tmp_j) +
    Hardware_B.tmp_tmp_lu) + Hardware_B.tmp_tmp * Hardware_B.D56_tmp_j) +
    Hardware_B.tmp_tmp_gf) + Hardware_B.tmp_tmp_ik * Hardware_B.D56_tmp_j) +
    Hardware_B.tmp_tmp_d4) + Hardware_B.tmp_tmp_g * Hardware_B.d1) +
    Hardware_B.tmp_tmp_nn * Hardware_B.d2) + ((((((Hardware_B.D48 +
    Hardware_B.D14) - Hardware_B.D24) - Hardware_B.D35) - Hardware_B.tmp_tmp_ce)
    - Hardware_B.D48_tmp * Hardware_B.D46_tmp_ol) + Hardware_B.d18) *
    (Hardware_B.D14_tmp * Hardware_B.x_tmp_b)) +
    ((((((((((((((Hardware_B.D47_tmp_tmp - Hardware_B.D47_tmp_c) -
    Hardware_B.D47_tmp_k) * Hardware_B.rtb_ginv_tmp_i + Hardware_B.D47_tmp_l0) +
    Hardware_B.d26 * Hardware_B.D46_tmp_h) - Hardware_B.D24_tmp_a *
    Hardware_B.D46_tmp_h) + Hardware_B.D47_tmp_p) + Hardware_B.D46_tmp_gx) +
    Hardware_B.D14) - Hardware_B.D24) - Hardware_B.D35) - Hardware_B.tmp_tmp_ce)
    + Hardware_B.d20) + Hardware_B.d21) + Hardware_B.d18) *
    (Hardware_B.D27_tmp_a * Hardware_B.x_tmp_b)) + Hardware_B.d126) +
    Hardware_B.d41 * Hardware_B.d3) + Hardware_B.d42 * Hardware_B.d3) +
    Hardware_B.tmp_tmp_dk * Hardware_B.ab_a) + Hardware_B.d128) +
    Hardware_B.d129) + Hardware_B.d34 * Hardware_B.d6) + Hardware_B.d43 *
    Hardware_B.D37) + Hardware_B.tmp_tmp_oi * Hardware_B.D67) + Hardware_B.d130)
    + Hardware_B.d131) + Hardware_B.d132) + Hardware_B.d133) - Hardware_B.d134)
    - Hardware_B.d135) - Hardware_B.d136) + Hardware_B.tmp_tmp_nc *
    Hardware_B.D56_tmp_g) + Hardware_B.d137) + Hardware_B.d138) +
                      Hardware_B.d139) - Hardware_B.d140) - Hardware_B.d141) +
                   Hardware_B.tmp_tmp_p * Hardware_B.D56_tmp_dh) +
                  Hardware_B.d142) + Hardware_B.tmp_tmp_dv *
                 Hardware_B.D46_tmp_d) + Hardware_B.d143 * Hardware_B.D46_tmp_d)
               + Hardware_B.D14_tmp_jg * Hardware_P.ArmConstants.Inertia1[8] *
               Hardware_B.D46_tmp_d) + Hardware_B.tmp_tmp_jo *
              Hardware_B.D46_tmp_d) + Hardware_B.d144 * Hardware_B.D46_tmp_d) +
            Hardware_B.D14_tmp_jg * Hardware_P.ArmConstants.Inertia2[8] *
            Hardware_B.D46_tmp_d) + Hardware_B.D14_tmp_jg *
           Hardware_P.HexaConstants.Inertia[0] * Hardware_B.D46_tmp_d) +
          Hardware_B.d145 * Hardware_B.D46_tmp_d) + Hardware_B.d14 *
         Hardware_P.HexaConstants.Inertia[8] * Hardware_B.D46_tmp_d) +
        Hardware_B.d146 * Hardware_B.D46_tmp_d) + Hardware_B.d147 *
       Hardware_B.D46_tmp_d) + Hardware_B.d148 * Hardware_B.D46_tmp_d) +
     Hardware_B.d39 * Hardware_B.D46_tmp_d) + Hardware_B.d149 *
    Hardware_B.D46_tmp_d;
  Hardware_B.dv[37] = -(((((((((((((((((((((((((((((((tmp + Hardware_B.d150) +
    Hardware_B.d151) + Hardware_B.d152) + Hardware_B.d153) - Hardware_B.d154) +
    Hardware_B.d155) + Hardware_B.d156) + Hardware_B.d157 *
    Hardware_B.D46_tmp_lx) - Hardware_B.d158) + Hardware_B.d159) +
    Hardware_B.d160) + Hardware_B.D46_tmp_tmp_iz) + Hardware_B.tmp_tmp_nc *
    Hardware_B.D56_tmp_b) + Hardware_B.d) + Hardware_B.d162 *
    Hardware_B.D46_tmp_nu) - Hardware_B.d163) + Hardware_B.d164) +
    Hardware_B.d165) + Hardware_B.tmp_tmp_p * Hardware_B.D56_tmp_bs) +
    Hardware_B.D14_tmp_nb) + Hardware_B.d45 * Hardware_B.d5) + Hardware_B.d32 *
    Hardware_B.d5) + Hardware_B.tmp_tmp_dk * Hardware_B.D15_tmp_tmp) +
    Hardware_B.d48 * Hardware_B.d7) + Hardware_B.d33 * Hardware_B.D14_tmp_tmp) +
    Hardware_B.tmp_tmp_oi * Hardware_B.D15_tmp_tmp_o) + Hardware_B.d45 *
    Hardware_B.y_a) + Hardware_B.d32 * Hardware_B.y_a) + Hardware_B.d33 *
    Hardware_B.D48_tmp_tmp) + Hardware_B.d8) * 0.125);
  Hardware_B.D56_tmp_tmp_m = Hardware_B.D46_tmp_g2 *
    Hardware_B.rtb_ginv_tmp_tmp_m;
  Hardware_B.D56_tmp_tmp_hc = -2.0 * Hardware_B.rtb_ginv_tmp_tmp_m *
    Hardware_B.x_tmp;
  Hardware_B.rtb_ginv_tmp_tmp_m = Hardware_P.ArmConstants.MC1 *
    Hardware_B.D15_tmp + Hardware_B.D24_tmp_jr;
  Hardware_B.tmp_tmp = Hardware_P.ArmConstants.Hexa_to_joint_L *
    Hardware_B.x_tmp;
  Hardware_B.D14_tmp_jg = -2.0 * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D27_tmp_a = -2.0 * Hardware_P.ArmConstants.Mass2;
  Hardware_B.d14 = 4.0 * Hardware_B.x_tmp_k;
  Hardware_B.D14_tmp = ((Hardware_P.ArmConstants.l1_dim * Hardware_B.D17_tmp_p +
    Hardware_B.tmp_tmp) + Hardware_P.ArmConstants.MC2 * Hardware_B.D17_tmp_i) *
    Hardware_B.DigitalClock - Hardware_B.D24_tmp_c * Hardware_B.x_tmp_c *
    Hardware_B.x_tmp_cx;
  Hardware_B.d18 = 4.0 * Hardware_P.ArmConstants.Mass2;
  Hardware_B.d20 = Hardware_B.D16 * -2.0;
  Hardware_B.d21 = Hardware_B.D25 * Hardware_B.D56_tmp_tmp_tmp +
    Hardware_B.D47_tmp_tmp * Hardware_B.D46_tmp_a;
  Hardware_B.tmp_tmp_dd = Hardware_B.d14 * Hardware_B.D17_tmp_a *
    Hardware_B.x_tmp * (Hardware_B.rtb_ginv_tmp_tmp_c +
                        Hardware_B.rtb_ginv_tmp_tmp_p);
  Hardware_B.tmp_tmp_l = (Hardware_B.D45_tmp_a * 2.0 * Hardware_B.D46_tmp_h2 +
    4.0 * Hardware_P.ArmConstants.Inertia2[3] * Hardware_B.D46_tmp_ex) *
    Hardware_B.rtb_ginv_tmp_da;
  Hardware_B.tmp_tmp_n = (Hardware_B.D34 * 2.0 * Hardware_B.D46_tmp_h2 + -4.0 *
    Hardware_P.ArmConstants.Inertia2[3] * Hardware_B.D46_tmp_ex) *
    Hardware_B.rtb_ginv_tmp_pi;
  Hardware_B.tmp_tmp_d = Hardware_B.D14_tmp * Hardware_B.d18;
  Hardware_B.tmp_tmp = (Hardware_P.ArmConstants.MC1 * Hardware_B.D17_tmp_p +
                        Hardware_B.tmp_tmp) * Hardware_B.DigitalClock;
  Hardware_B.tmp_tmp_f = Hardware_B.D46_tmp_ch * Hardware_B.D14_tmp_i *
    Hardware_B.D46_tmp_d;
  Hardware_B.tmp_tmp_j = Hardware_B.D46_tmp_ax * Hardware_B.d166 *
    Hardware_B.D46_tmp_d;
  Hardware_B.dv[45] = -((((((((((((((((((((Hardware_B.D47_tmp_tmp *
    Hardware_B.D14_tmp_c * Hardware_B.smax + Hardware_P.ArmConstants.Inertia1[3]
    * Hardware_B.D56_tmp_tmp_tmp) * (Hardware_B.d14 * Hardware_B.x_tmp_b *
    Hardware_B.x_tmp) * Hardware_B.x_tmp_cx + (((Hardware_B.D56_tmp_tmp_m *
    Hardware_B.D46_tmp_fi + Hardware_B.D56_tmp_tmp_hc * Hardware_B.D46_tmp_ei) +
    Hardware_B.D56_tmp_tmp_m * Hardware_B.D46_tmp_ch) +
    Hardware_B.D56_tmp_tmp_hc * Hardware_B.D46_tmp_ax)) + ((Hardware_B.D56_tmp_l
    * Hardware_B.D14_tmp_c * Hardware_B.smax + Hardware_B.D46_tmp_b) +
    Hardware_B.D46_tmp_ln) * (Hardware_B.d20 * Hardware_B.x_tmp_b) *
    Hardware_B.x_tmp_cx) + -2.0 * Hardware_B.x_tmp_b * Hardware_B.D56 *
    Hardware_B.D26 * Hardware_B.x_tmp_cx) - Hardware_B.D16 * Hardware_B.x_tmp_b *
    Hardware_B.D46 * Hardware_B.x_tmp_cx) - Hardware_B.D56 * Hardware_B.x_tmp_b *
    Hardware_B.D47_tmp_l * Hardware_B.x_tmp_cx) + Hardware_B.D46_tmp_g2 *
    Hardware_B.x_tmp_b * Hardware_B.x_tmp * (Hardware_B.D15 *
    Hardware_B.D46_tmp_ex + Hardware_B.D45_tmp_a * Hardware_B.D46_tmp_h2) *
    Hardware_B.x_tmp_cx) + Hardware_B.rtb_ginv_tmp_tmp_m * Hardware_B.D14_tmp_jg
    * Hardware_B.x_tmp_b * Hardware_B.x_tmp_c * (Hardware_B.tmp_tmp -
    Hardware_B.rtb_ginv_tmp_tmp_m * Hardware_B.x_tmp_c * Hardware_B.x_tmp_cx)) +
    Hardware_B.D24_tmp_c * Hardware_B.D27_tmp_a * Hardware_B.x_tmp_b *
    Hardware_B.x_tmp_c * Hardware_B.D14_tmp) + Hardware_B.D14_tmp_jg *
    Hardware_B.DigitalClock * Hardware_B.rtb_ginv_tmp_tmp_m * Hardware_B.x_tmp_b
    * Hardware_B.D45_tmp) + Hardware_B.D27_tmp_a * Hardware_B.DigitalClock *
    Hardware_B.D24_tmp_c * Hardware_B.x_tmp_b * Hardware_B.D24_tmp_j) +
    Hardware_P.ArmConstants.Inertia1[8] * Hardware_B.D46_tmp_d) +
    Hardware_P.ArmConstants.Inertia2[8] * Hardware_B.D46_tmp_d) +
    Hardware_P.HexaConstants.Inertia[0] * Hardware_B.D46_tmp_d) -
    Hardware_B.rtb_ginv_tmp_h * Hardware_B.D46_tmp_d) - Hardware_B.D56 *
    Hardware_P.HexaConstants.Inertia[4] * Hardware_B.D46_tmp_d) * Hardware_B.d12
    + ((((((Hardware_B.tmp_tmp_l + Hardware_B.tmp_tmp_dd) + Hardware_B.tmp_tmp_n)
          + Hardware_B.D18_tmp * Hardware_B.d18 * Hardware_B.D24_tmp_j) +
         Hardware_B.tmp_tmp_d * Hardware_B.D17_tmp) + Hardware_B.tmp_tmp_f) +
       Hardware_B.tmp_tmp_j) * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[7]) +
    (((((((((((((Hardware_B.D17_tmp_a * -2.0 * Hardware_B.D17 *
                 (Hardware_B.D47_tmp_tmp * Hardware_B.D56_tmp_tmp_tmp +
                  Hardware_B.D56_tmp_l * Hardware_B.D46_tmp_a) + Hardware_B.d20 *
                 Hardware_B.D17_tmp_a * Hardware_B.d21) + Hardware_B.D17_tmp_a *
                2.0 * Hardware_B.D56 * Hardware_B.d21) + Hardware_B.tmp_tmp_dd)
              + Hardware_B.tmp_tmp_l) + Hardware_B.tmp_tmp_n) +
            (Hardware_B.rtb_ginv_tmp_c * Hardware_B.D17_tmp_e +
             Hardware_B.rtb_ginv_tmp_p * Hardware_B.D17_tmp_a4) * Hardware_B.d18
            * Hardware_B.D24_tmp_j) + (Hardware_B.D14_tmp_tmp_c *
    -Hardware_B.D17_tmp_e + Hardware_B.rtb_ginv_tmp_o * Hardware_B.D17_tmp_a4) *
           Hardware_B.tmp_tmp_d) + Hardware_B.D46_tmp_mc *
          Hardware_P.ArmConstants.Mass1 * Hardware_B.D45_tmp *
          (Hardware_B.D17_tmp_o * Hardware_B.x_tmp + Hardware_B.D17_tmp_j *
           Hardware_B.x_tmp_k)) + ((Hardware_B.D14_tmp_c * Hardware_B.x_tmp_c *
    Hardware_B.x_tmp_cx + -Hardware_B.DigitalClock * Hardware_B.smax) *
    (Hardware_P.ArmConstants.MC1 * Hardware_B.x_tmp) + (Hardware_B.D17_tmp_tmp *
    Hardware_B.x_tmp_cx + Hardware_B.D17_tmp_tmp_p) *
    (Hardware_P.ArmConstants.MC1 * Hardware_B.x_tmp_k)) *
         ((-Hardware_B.rtb_ginv_tmp_tmp_m * Hardware_B.x_tmp_c *
           Hardware_B.x_tmp_cx + Hardware_B.tmp_tmp) * (4.0 *
    Hardware_P.ArmConstants.Mass1))) + Hardware_B.D46_tmp_fi *
        Hardware_B.D14_tmp_i * Hardware_B.D46_tmp_d) + Hardware_B.D46_tmp_ei *
       Hardware_B.d166 * Hardware_B.D46_tmp_d) + Hardware_B.tmp_tmp_f) +
     Hardware_B.tmp_tmp_j) * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6]) -
    (((((((((((((((((((((((((((((((((((((((((Hardware_B.D56_tmp_n3 *
    Hardware_B.D46_tmp_m + Hardware_B.D25 * Hardware_B.D56_tmp_da) +
    Hardware_B.D56_tmp_oy * Hardware_B.D46_tmp_n) + Hardware_B.D15 *
    Hardware_B.D56_tmp_e) + Hardware_B.D56_tmp_gg * Hardware_B.D46_tmp_p) +
    Hardware_B.D25 * Hardware_B.D56_tmp_bj) + Hardware_B.D56_tmp_c *
    Hardware_B.D46_tmp_l) + Hardware_B.D15 * Hardware_B.D56_tmp_j) -
    Hardware_B.D56_tmp_tmp_ob) + Hardware_B.D56_tmp_tmp_l) -
    Hardware_B.D56_tmp_tmp_k) - Hardware_B.D56_tmp_tmp_j) + Hardware_B.D56_tmp_n
    * Hardware_B.D46_tmp_j) + Hardware_B.D46_tmp_jp * Hardware_B.D56_tmp_d) +
    Hardware_B.D46_tmp_k * Hardware_B.D56_tmp_d) + Hardware_B.D56_tmp_tmp_fz) -
    Hardware_B.D56_tmp_tmp_cm) - Hardware_B.D56_tmp_tmp_fq) -
    Hardware_B.D56_tmp_tmp_n) + Hardware_B.D56_tmp_k * Hardware_B.D46_tmp_ld) +
    Hardware_B.D46_tmp_mx * Hardware_B.D56_tmp_f) + Hardware_B.D46_tmp_tmp_pr *
    Hardware_B.D56_tmp_a) + Hardware_B.D56_tmp_tmp_i) -
    Hardware_B.D56_tmp_tmp_l4) - Hardware_B.D56_tmp_tmp_i3) -
                     Hardware_B.D56_tmp_tmp_k1) + Hardware_B.D56_tmp_tmp_fc) -
                   Hardware_B.D56_tmp_tmp_a) + -Hardware_B.D46_tmp_tmp_m *
                  Hardware_P.ArmConstants.Mass2 * Hardware_B.D56_tmp_dy) +
                 Hardware_B.D56_tmp_pm * Hardware_B.D46_tmp_lx) +
                Hardware_B.D46_tmp_jp * Hardware_B.D56_tmp_o) +
               Hardware_B.D46_tmp_k * Hardware_B.D56_tmp_o) +
              Hardware_B.D56_tmp_tmp_d) - Hardware_B.D56_tmp_tmp_ey) -
            Hardware_B.D56_tmp_tmp_eh) - Hardware_B.D56_tmp_tmp_b) +
          Hardware_B.D56_tmp_p2 * Hardware_B.D46_tmp_nu) + Hardware_B.D46_tmp_mx
         * Hardware_B.D56_tmp_ju) + Hardware_B.D46_tmp_tmp_pr *
        Hardware_B.D56_tmp_jz) + Hardware_B.D14_tmp_f) - Hardware_B.D56_tmp_g4)
     - Hardware_B.D56_tmp_c3) * Hardware_B.D16_tmp_m0) * 0.25);
  Hardware_B.D17 = Hardware_B.d99 * Hardware_P.ArmConstants.Inertia1[7];
  Hardware_B.D56_tmp_tmp_m = Hardware_B.D46_tmp_tmp_g *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1;
  Hardware_B.D56_tmp_tmp_hc = Hardware_B.d12 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.rtb_ginv_tmp_tmp_m = Hardware_B.d99 *
    Hardware_P.ArmConstants.Inertia2[7];
  Hardware_B.d166 = Hardware_B.D46_tmp_f *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4];
  Hardware_B.D16_tmp_m0 = Hardware_B.d166 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2;
  Hardware_B.tmp_tmp = Hardware_B.d99 * Hardware_P.ArmConstants.Inertia1[6];
  Hardware_B.D14_tmp_i = Hardware_B.d127 * Hardware_P.ArmConstants.Inertia2[3] *
    Hardware_B.D46_tmp_tmp_a;
  Hardware_B.D68 *= Hardware_B.d55;
  Hardware_B.D14_tmp_jg = Hardware_B.D47_tmp * Hardware_B.D46_tmp_tmp_k;
  Hardware_B.D46_tmp_tmp_k *= Hardware_B.D16_tmp_e;
  Hardware_B.D27_tmp_a = Hardware_B.rtb_ginv_tmp_tmp_m * Hardware_B.D46_tmp_n;
  Hardware_B.D46_tmp_tmp_i *= Hardware_B.rtb_ginv_tmp_n;
  Hardware_B.D56_tmp_tmp_p *= Hardware_B.D16_tmp_m0;
  Hardware_B.d14 = Hardware_B.rtb_ginv_tmp_ie * Hardware_B.D56_tmp_e;
  Hardware_B.D14_tmp = Hardware_B.rtb_ginv_tmp_cx * Hardware_B.D56_tmp_e;
  Hardware_B.d18 = Hardware_B.rtb_ginv_tmp_if * Hardware_B.D56_tmp_e;
  Hardware_B.D16_tmp_e *= Hardware_B.D46_tmp_tmp_b;
  Hardware_B.rtb_ginv_tmp_tmp_m *= Hardware_B.D46_tmp_l;
  Hardware_B.D56_tmp_tmp_h *= Hardware_B.D16_tmp_m0;
  Hardware_B.d2 *= Hardware_B.d53;
  Hardware_B.D16_tmp_m0 = -6.0 * Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.d20 = Hardware_B.D16_tmp_m0 *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D14_tmp_p;
  Hardware_B.d21 = Hardware_B.tmp_tmp_jo * Hardware_B.D46_tmp_e;
  Hardware_B.tmp_tmp_dd = Hardware_B.D16_tmp * Hardware_P.ArmConstants.Inertia2
    [4] * Hardware_B.D46_tmp_e;
  Hardware_B.D14_tmp_f = Hardware_B.d148 * Hardware_B.D46_tmp_e;
  Hardware_B.tmp_tmp_l = Hardware_B.d33 * Hardware_B.D56_tmp_tmp_oc;
  Hardware_B.D37 *= Hardware_B.D58;
  Hardware_B.D67 *= Hardware_B.d49;
  Hardware_B.D56_tmp_tmp_e *= Hardware_B.D58;
  Hardware_B.tmp_tmp_n = Hardware_B.d174 * Hardware_B.D46_tmp_ld;
  Hardware_B.tmp_tmp_d = Hardware_B.D14_tmp_j * Hardware_B.D56_tmp_dh;
  Hardware_B.tmp_tmp_f = Hardware_B.d174 * Hardware_B.D46_tmp_nu;
  Hardware_B.d11 = (((Hardware_B.D14_tmp_m - Hardware_B.d37) + Hardware_B.d11) +
                    Hardware_B.d13) + Hardware_B.d16;
  Hardware_B.d13 = Hardware_B.d11 * Hardware_B.d175;
  Hardware_B.D14_tmp_tmp *= Hardware_B.D58;
  Hardware_B.D15_tmp_tmp_o *= Hardware_B.d51;
  Hardware_B.D58 *= Hardware_B.D48_tmp_tmp;
  Hardware_B.d16 = Hardware_B.D38 * Hardware_B.d3;
  Hardware_B.d3 *= Hardware_B.D47;
  Hardware_B.D14_tmp_m = Hardware_B.D38 * Hardware_B.D56_tmp_tmp_f;
  Hardware_B.D56_tmp_tmp_f *= Hardware_B.D47;
  Hardware_B.tmp_tmp_j = Hardware_B.D38 * Hardware_B.d5;
  Hardware_B.d5 *= Hardware_B.D47;
  Hardware_B.D38 *= Hardware_B.y_a;
  Hardware_B.D47 *= Hardware_B.y_a;
  Hardware_B.dv[53] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((Hardware_B.d127 *
    Hardware_P.ArmConstants.Inertia1[3] * Hardware_B.rtb_ginv_tmp_i +
    Hardware_B.D14_tmp_i) + Hardware_B.d54 * Hardware_B.rtb_ginv_tmp_tmp_o) +
    Hardware_B.D68) + Hardware_B.D46_tmp_h3 * Hardware_B.D46_tmp_tmp_m4) +
    Hardware_B.d4 * Hardware_B.D46_tmp_tmp_m4) + Hardware_B.D46_tmp_pc *
    Hardware_B.D46_tmp_tmp_m4) + Hardware_B.D14_tmp_ch *
    Hardware_B.D46_tmp_tmp_m4) + Hardware_B.D17 * Hardware_B.D46_tmp_m) +
    Hardware_B.D56_tmp * Hardware_B.rtb_ginv_tmp_ox) + Hardware_B.D56_tmp_tmp_m *
    Hardware_B.D27) + Hardware_B.D56_tmp_tmp_hc * Hardware_B.D27) +
    Hardware_B.D56_tmp_h * Hardware_B.D56_tmp_da) + Hardware_B.D56_tmp_p *
    Hardware_B.D56_tmp_da) + Hardware_B.D56_tmp_p4 * Hardware_B.D56_tmp_da) +
    Hardware_B.rtb_ginv_tmp * Hardware_B.D56_tmp_da) + Hardware_B.d167) +
    Hardware_B.D14_tmp_jg) + Hardware_B.D46_tmp_tmp_k) + Hardware_B.D27_tmp_a) +
    Hardware_B.D46_tmp_tmp_i) + Hardware_B.D56_tmp_tmp_p) +
    Hardware_B.rtb_ginv_tmp_f * Hardware_B.D56_tmp_tmp_o) + Hardware_B.d14) +
    Hardware_B.D14_tmp) + Hardware_B.d18) + Hardware_B.d168) + Hardware_B.d169)
    + Hardware_B.d170) + Hardware_B.d171) + Hardware_B.d172) +
    Hardware_B.rtb_ginv_tmp_d) + Hardware_B.d4 * Hardware_B.D46_tmp_tmp_c) +
    Hardware_B.rtb_ginv_tmp_g) + Hardware_B.D14_tmp_ch *
    Hardware_B.D46_tmp_tmp_c) + Hardware_B.D17 * Hardware_B.D46_tmp_p) +
    Hardware_B.tmp_tmp_a) + Hardware_B.D56_tmp_tmp_m * Hardware_B.D56_tmp_tmp_fb)
    + Hardware_B.D56_tmp_tmp_hc * Hardware_B.D56_tmp_tmp_fb) +
    Hardware_B.tmp_tmp_il) + Hardware_B.tmp_tmp_fa) + Hardware_B.tmp_tmp_ji) +
    Hardware_B.tmp_tmp_oo) + Hardware_B.d173) + Hardware_B.tmp_tmp_fr) +
    Hardware_B.D16_tmp_e) + Hardware_B.rtb_ginv_tmp_tmp_m) +
    Hardware_B.tmp_tmp_oy) + Hardware_B.D56_tmp_tmp_h) + Hardware_B.tmp_tmp_ln)
    + Hardware_B.tmp_tmp_lu) + Hardware_B.tmp_tmp_gf) + Hardware_B.tmp_tmp_d4) +
    Hardware_B.d52 * Hardware_B.d1) + Hardware_B.d2) + -6.0 *
    Hardware_P.ArmConstants.MC1 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1 *
    Hardware_B.smax) + -6.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.smax) + Hardware_B.tmp_tmp_dv *
    Hardware_B.D46_tmp_g) + Hardware_B.D16_tmp *
    Hardware_P.ArmConstants.Inertia1[4] * Hardware_B.D46_tmp_g) +
    Hardware_B.d146 * Hardware_B.D46_tmp_g) + Hardware_B.d149 *
    Hardware_B.D46_tmp_g) + Hardware_B.d45 * Hardware_B.D18) + Hardware_B.d32 *
    Hardware_B.D18) + Hardware_B.d20) + Hardware_B.d21) + Hardware_B.tmp_tmp_dd)
    + Hardware_B.D14_tmp_f) + Hardware_B.tmp_tmp_l) + Hardware_B.D45 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D28) + Hardware_B.d48 * Hardware_B.D46_tmp_tmp) + Hardware_B.d16)
    + Hardware_B.d3) + Hardware_B.d46 * Hardware_B.ab_a) + Hardware_B.D14_tmp_m)
    + Hardware_B.D56_tmp_tmp_f) + Hardware_B.D37) + Hardware_B.D67) +
    Hardware_B.D56_tmp_tmp_e) + Hardware_B.tmp_tmp * Hardware_B.D46_tmp_j) -
    Hardware_B.d133) + Hardware_B.d134) + Hardware_B.d135) + Hardware_B.d136) +
    Hardware_B.d161 * Hardware_B.D56_tmp_g) + Hardware_B.tmp_tmp_n) +
    -Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Inertia2[0] * Hardware_B.D47_tmp_i) +
    Hardware_B.d140) + Hardware_B.d141) + Hardware_B.tmp_tmp_d) +
    Hardware_B.tmp_tmp * Hardware_B.D46_tmp_lx) +
    -Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Inertia1[0] * Hardware_B.D56_tmp_tmp) +
    Hardware_B.d159) + Hardware_B.d160) + Hardware_B.D46_tmp_tmp_iz) +
                       Hardware_B.d) + Hardware_B.tmp_tmp_f) + Hardware_B.d13) +
                    Hardware_B.d10 * Hardware_B.d176) - Hardware_B.d163) +
                  Hardware_B.d164) + Hardware_B.d165) + Hardware_B.D14_tmp_nb) +
               Hardware_B.tmp_tmp_j) + Hardware_B.d5) + Hardware_B.d50 *
             Hardware_B.D15_tmp_tmp) + Hardware_B.D14_tmp_tmp) +
           Hardware_B.D15_tmp_tmp_o) + Hardware_B.D38) + Hardware_B.D47) +
        Hardware_B.D58) + Hardware_B.d8) * 0.125);
  Hardware_B.D17 = Hardware_B.d166 * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2;
  Hardware_B.D27 = Hardware_B.D48_tmp_p * Hardware_B.D46_tmp_tmp;
  Hardware_B.D56_tmp_tmp_m = Hardware_B.D48_tmp_p * Hardware_B.d6;
  Hardware_B.D56_tmp_tmp_fb = Hardware_B.D48_tmp_p * Hardware_B.d7;
  Hardware_B.D56_tmp_tmp_hc = Hardware_B.D48_tmp_p * Hardware_B.D46_tmp_tmp_f;
  Hardware_B.dv[61] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((Hardware_B.D46_tmp_c
    * Hardware_B.D46_tmp_tmp_ad + (Hardware_B.D14_tmp_i + Hardware_B.D68)) +
    Hardware_B.d9 * Hardware_B.D46_tmp_tmp_ad) + Hardware_B.D14_tmp_jg) +
    Hardware_B.D46_tmp_tmp_k) + Hardware_B.D27_tmp_a) + Hardware_B.D46_tmp_tmp_i)
    + Hardware_B.D56_tmp_tmp_p) + Hardware_B.D17 * Hardware_B.D56_tmp_tmp_o) +
    Hardware_B.d14) + Hardware_B.D14_tmp) + Hardware_B.d18) + Hardware_B.d169) +
    Hardware_B.d171) + Hardware_B.tmp_tmp_f1) + Hardware_B.d9 *
    Hardware_B.D46_tmp_tmp_pc) + Hardware_B.tmp_tmp_fr) + Hardware_B.D16_tmp_e)
    + Hardware_B.rtb_ginv_tmp_tmp_m) + Hardware_B.tmp_tmp_oy) +
    Hardware_B.D56_tmp_tmp_h) + Hardware_B.D17 * Hardware_B.D56_tmp_tmp_c) +
    Hardware_B.tmp_tmp_lu) + Hardware_B.tmp_tmp_gf) + Hardware_B.tmp_tmp_d4) +
    Hardware_B.d2) + Hardware_B.D16_tmp_m0 * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.s) + Hardware_B.d20) +
    Hardware_B.d21) + Hardware_B.tmp_tmp_dd) + Hardware_B.D14_tmp_f) +
    Hardware_B.tmp_tmp_l) + Hardware_B.d48 * Hardware_B.D28) + Hardware_B.D27) +
    Hardware_B.D56_tmp_tmp_m) + Hardware_B.D37) + Hardware_B.D67) +
                        Hardware_B.D56_tmp_tmp_e) + Hardware_B.tmp_tmp_n) -
                      Hardware_B.d139) + Hardware_B.d140) + Hardware_B.d141) +
                   Hardware_B.tmp_tmp_d) + Hardware_B.tmp_tmp_f) +
                 Hardware_B.d11 * Hardware_B.d176) + Hardware_B.d13) -
               Hardware_B.d163) + Hardware_B.d164) + Hardware_B.d165) +
            Hardware_B.D14_tmp_nb) + Hardware_B.D56_tmp_tmp_fb) +
          Hardware_B.D14_tmp_tmp) + Hardware_B.D15_tmp_tmp_o) + Hardware_B.D58)
       + Hardware_B.D56_tmp_tmp_hc) * 0.125);
  Hardware_B.D17 = Hardware_B.d27 * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.s;
  Hardware_B.D46_tmp_tmp_m4 = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[3] -
    Hardware_B.rtb_ginv_tmp_tmp;
  Hardware_B.dv[30] = -(Hardware_B.d24 * Hardware_B.D46_tmp_tmp_m4 +
                        Hardware_B.D17);
  Hardware_B.dv[38] = -((((((((((((((((Hardware_B.rtb_ginv_tmp_tmp_n +
    Hardware_B.d28) + Hardware_B.D24_tmp_a * Hardware_B.smax) -
    Hardware_B.D16_tmp_j) + Hardware_B.d19) + Hardware_B.D14_tmp_cz) +
    Hardware_B.rtb_ginv_tmp_tmp_f) + Hardware_B.D24_tmp * Hardware_B.D18) +
    Hardware_B.d29) + Hardware_B.d30) - Hardware_B.rtb_ginv_tmp_l) +
    Hardware_B.D16_tmp_m) + Hardware_B.D27_tmp) + Hardware_B.d35) +
    Hardware_B.d177) * Hardware_B.d12 - Hardware_B.D14_tmp_m3 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]) * 0.25);
  Hardware_B.D46_tmp_tmp_ad = Hardware_B.D47_tmp * Hardware_B.D46_tmp_tmp_b;
  Hardware_B.D46_tmp_tmp_k = 6.0 * Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5];
  Hardware_B.D56_tmp_tmp_p = Hardware_B.D46_tmp_tmp_k *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D14_tmp_p;
  Hardware_B.D56_tmp_tmp_o = Hardware_B.d43 * Hardware_B.D56_tmp_tmp_oc;
  Hardware_B.dv[46] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((Hardware_B.d178
    + Hardware_B.D46_tmp_lm) + Hardware_B.D46_tmp_mj) + Hardware_B.d109) +
    Hardware_B.D15_tmp_g) + Hardware_B.d117) + Hardware_B.D46_tmp_h3 *
    Hardware_B.D46_tmp_tmp_c) + Hardware_B.D46_tmp_pc * Hardware_B.D46_tmp_tmp_c)
    + Hardware_B.d179) + Hardware_B.D46_tmp_tmp_ad) + Hardware_B.d180) +
    Hardware_B.d181) + Hardware_B.d182) + 6.0 * Hardware_P.ArmConstants.MC1 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass1 *
    Hardware_B.smax) + 6.0 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.smax) + Hardware_B.d183) +
    Hardware_B.d184) + Hardware_B.D46_tmp_tmp_cj) + Hardware_B.d185) +
    Hardware_B.d41 * Hardware_B.D18) + Hardware_B.d42 * Hardware_B.D18) +
    Hardware_B.D56_tmp_tmp_p) + Hardware_B.d186) + Hardware_B.d187) +
    Hardware_B.D46_tmp_tmp_m1) + Hardware_B.D56_tmp_tmp_o) + Hardware_B.d188) +
    Hardware_B.d126) - Hardware_B.d16) - Hardware_B.d3) + Hardware_B.d189) -
    Hardware_B.D14_tmp_m) - Hardware_B.D56_tmp_tmp_f) - Hardware_B.D37) +
    Hardware_B.d190) - Hardware_B.D56_tmp_tmp_e) + Hardware_B.d133) -
    Hardware_B.d134) - Hardware_B.d135) - Hardware_B.d136) + Hardware_B.d139) -
    Hardware_B.d140) - Hardware_B.d141) + Hardware_B.d191 *
                        Hardware_P.ArmConstants.l1_dim *
                        Hardware_P.ArmConstants.Mass2 * Hardware_B.s *
                        Hardware_B.x_tmp_cx) + Hardware_B.d158) -
                      Hardware_B.d159) - Hardware_B.d160) -
                    Hardware_B.D46_tmp_tmp_iz) + Hardware_B.d163) -
                  Hardware_B.d164) - Hardware_B.d165) +
                ((((((((((((((((((((((((((((((((((((((((((-Hardware_P.ArmConstants.Inertia1
    [0] * Hardware_B.D56_tmp_da + Hardware_B.D14_tmp_md) +
    Hardware_B.D14_tmp_tmp_cg) + Hardware_B.D14_tmp_tmp_f) +
    Hardware_B.D14_tmp_h) + Hardware_B.D15_tmp_tmp_d) + Hardware_B.d23) +
    Hardware_B.D15_tmp_tmp_n) + Hardware_B.d25) + Hardware_B.D16_tmp_tmp) -
    Hardware_B.D34_tmp_m) + Hardware_B.D37_tmp) + Hardware_B.D46_tmp_tmp_p) +
    Hardware_B.rtb_ginv_tmp_k) + Hardware_B.d56) + Hardware_B.d57) +
    Hardware_B.d58) + Hardware_B.d59) + Hardware_B.D47_tmp_d) + Hardware_B.d101)
    + Hardware_B.d60) + Hardware_B.d192) + Hardware_B.d193) - Hardware_B.d61) +
    Hardware_B.d62) + Hardware_B.d63) + Hardware_B.d64) + Hardware_B.d65) +
    Hardware_B.d37) + Hardware_B.d66) + Hardware_B.d38) + Hardware_B.d67) -
    Hardware_B.d68) + Hardware_B.d69) + Hardware_B.d70) + Hardware_B.d71) +
                       Hardware_B.d72) + Hardware_B.d73) + Hardware_B.d74) +
                    Hardware_B.d75) + Hardware_B.d76) + Hardware_B.d77) +
                 Hardware_B.d78) * Hardware_B.d22) - Hardware_B.tmp_tmp_j) -
              Hardware_B.d5) + Hardware_B.d194) - Hardware_B.D14_tmp_tmp) +
           Hardware_B.d195) - Hardware_B.D38) - Hardware_B.D47) - Hardware_B.D58)
       + Hardware_B.d196) * 0.125);
  Hardware_B.dv[54] = -Hardware_B.D17;
  Hardware_B.dv[62] = -(Hardware_B.D46_tmp * Hardware_B.s * Hardware_B.d17);
  Hardware_B.dv[31] = -((Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    Hardware_P.ArmConstants.l1_dim * Hardware_B.s + Hardware_B.d44 *
    Hardware_B.D46_tmp_tmp_m4) * Hardware_B.D14_tmp_o);
  Hardware_B.dv[39] = -((Hardware_B.d36 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] * Hardware_B.D17_tmp_i +
    -Hardware_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    Hardware_P.ArmConstants.Inertia2[3] * Hardware_B.D46_tmp_tmp_a) + -0.25 *
                        Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5] *
                        Hardware_B.d197);
  Hardware_B.dv[47] = -((((((((((((((((((((((((((((((((((Hardware_B.d198 +
    Hardware_B.d199) + Hardware_B.D46_tmp_nr) + Hardware_B.D15_tmp_g) +
    Hardware_B.d117) + Hardware_B.D46_tmp_c * Hardware_B.D46_tmp_tmp_pc) +
    Hardware_B.D46_tmp_tmp_ad) + Hardware_B.d180) + Hardware_B.d182) +
    Hardware_B.D46_tmp_tmp_k * Hardware_P.ArmConstants.l1_dim *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.s) + Hardware_B.D56_tmp_tmp_p) +
    Hardware_B.d186) + Hardware_B.d187) + Hardware_B.D46_tmp_tmp_m1) +
    Hardware_B.D56_tmp_tmp_o) + Hardware_B.d34 * Hardware_B.D28) -
    Hardware_B.D27) - Hardware_B.D56_tmp_tmp_m) - Hardware_B.D37) +
    Hardware_B.d190) - Hardware_B.D56_tmp_tmp_e) + Hardware_B.d139) -
    Hardware_B.d140) - Hardware_B.d141) + -8.0 * Hardware_P.ArmConstants.MC2 *
    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    Hardware_P.ArmConstants.l1_dim * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.s * Hardware_B.x_tmp_cx) + Hardware_B.d163) - Hardware_B.d164) -
    Hardware_B.d165) + Hardware_B.d197 * Hardware_B.d22) -
    Hardware_B.D56_tmp_tmp_fb) - Hardware_B.D14_tmp_tmp) + Hardware_B.d195) +
    -Hardware_P.ArmConstants.MC2 * Hardware_DW.DiscreteTimeIntegrator1_DSTATE[5]
    * Hardware_P.ArmConstants.Hexa_to_joint_L * Hardware_P.ArmConstants.Mass2 *
    Hardware_B.D48_tmp_tmp) - Hardware_B.D56_tmp_tmp_hc) * 0.125);
  Hardware_B.dv[55] = -(Hardware_B.D48_tmp * Hardware_B.s * Hardware_B.d15);
  Hardware_B.dv[63] = -0.0;
  memset(&Hardware_B.dv[0], 0, 24U * sizeof(real_T));
  memset(&Hardware_B.e_hat[0], 0, sizeof(real_T) << 3U);
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    Hardware_B.D17 = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[Hardware_B.c_j];
    for (Hardware_B.jj = 0; Hardware_B.jj < 8; Hardware_B.jj++) {
      Hardware_B.e_hat[Hardware_B.jj] += Hardware_B.dv[(Hardware_B.c_j << 3) +
        Hardware_B.jj] * Hardware_B.D17;
    }
  }

  Hardware_B.rtb_Product3_tmp[0] = 0.0;
  Hardware_B.rtb_Product3_tmp[1] = 0.0;
  Hardware_B.rtb_Product3_tmp[2] = Hardware_B.D46_tmp_bb * 9.80665;
  Hardware_B.D17 = -9.80665 * Hardware_B.x_tmp_b;
  Hardware_B.rtb_Product3_tmp[3] = ((Hardware_B.D14_tmp_js * Hardware_B.x_tmp -
    Hardware_B.D34_tmp) - Hardware_B.D34_tmp_o) * Hardware_B.D17;
  Hardware_B.rtb_Product3_tmp[4] = Hardware_B.D15_tmp_a * 9.80665 *
    Hardware_B.x_tmp_cx;
  Hardware_B.rtb_Product3_tmp[5] = 0.0;
  Hardware_B.rtb_Product3_tmp[6] = (-Hardware_B.D14_tmp_n * Hardware_B.D17_tmp_p
    - Hardware_B.D34_tmp_o) * Hardware_B.D17;
  Hardware_B.rtb_Product3_tmp[7] = Hardware_P.ArmConstants.MC2 * 9.80665 *
    Hardware_P.ArmConstants.Mass2 * Hardware_B.x_tmp_b * Hardware_B.D17_tmp_i;
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    // MATLAB Function: '<S9>/MATLAB Function1'
    Hardware_B.fx[Hardware_B.c_j] = Hardware_B.e_hat[Hardware_B.c_j] -
      Hardware_B.rtb_Product3_tmp[Hardware_B.c_j];
  }

  // MATLAB Function: '<S9>/MATLAB Function1'
  Hardware_mldivide_o(Hardware_B.ginv, Hardware_B.fx);

  // DigitalClock: '<S3>/Digital Clock'
  Hardware_B.DigitalClock = (((&Hardware_M)->Timing.clockTick0) * 0.01);

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  propChange = true;
  Hardware_B.c_j = 0;
  exitg1 = false;
  while (!exitg1 && (Hardware_B.c_j < 144)) {
    if (!(Hardware_DW.obj.Waypoints[Hardware_B.c_j] ==
          Hardware_P.Trajectory.Waypoints[Hardware_B.c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      Hardware_B.c_j++;
    }
  }

  if (!propChange) {
    if (Hardware_DW.obj.isInitialized == 1) {
      Hardware_DW.obj.TunablePropsChanged = true;
      Hardware_DW.obj.tunablePropertyChanged[0] = true;
    }

    memcpy(&Hardware_DW.obj.Waypoints[0], &Hardware_P.Trajectory.Waypoints[0],
           144U * sizeof(real_T));
  }

  propChange = true;
  Hardware_B.c_j = 0;
  exitg1 = false;
  while (!exitg1 && (Hardware_B.c_j < 18)) {
    if (!(Hardware_DW.obj.TimePoints[Hardware_B.c_j] ==
          Hardware_P.Trajectory.Tstamps[Hardware_B.c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      Hardware_B.c_j++;
    }
  }

  if (!propChange) {
    if (Hardware_DW.obj.isInitialized == 1) {
      Hardware_DW.obj.TunablePropsChanged = true;
      Hardware_DW.obj.tunablePropertyChanged[1] = true;
    }

    memcpy(&Hardware_DW.obj.TimePoints[0], &Hardware_P.Trajectory.Tstamps[0],
           18U * sizeof(real_T));
  }

  propChange = true;
  Hardware_B.c_j = 0;
  exitg1 = false;
  while (!exitg1 && (Hardware_B.c_j < 144)) {
    if (!(Hardware_DW.obj.VelocityBoundaryCondition[Hardware_B.c_j] ==
          Hardware_P.PolynomialTrajectory_VelocityBo[Hardware_B.c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      Hardware_B.c_j++;
    }
  }

  if (!propChange) {
    if (Hardware_DW.obj.isInitialized == 1) {
      Hardware_DW.obj.TunablePropsChanged = true;
      Hardware_DW.obj.tunablePropertyChanged[3] = true;
    }

    memcpy(&Hardware_DW.obj.VelocityBoundaryCondition[0],
           &Hardware_P.PolynomialTrajectory_VelocityBo[0], 144U * sizeof(real_T));
  }

  if (Hardware_DW.obj.TunablePropsChanged) {
    Hardware_DW.obj.TunablePropsChanged = false;
    if (Hardware_DW.obj.tunablePropertyChanged[0] ||
        Hardware_DW.obj.tunablePropertyChanged[1] ||
        Hardware_DW.obj.tunablePropertyChanged[2]) {
      propChange = true;
    } else {
      propChange = false;
    }

    if (!propChange) {
      if (Hardware_DW.obj.tunablePropertyChanged[3] ||
          Hardware_DW.obj.tunablePropertyChanged[4]) {
        propChange = true;
      } else {
        propChange = false;
      }
    }

    Hardware_DW.obj.PPFormUpdatedNeeded = propChange;
    if (Hardware_DW.obj.PPFormUpdatedNeeded) {
      PolyTrajSys_regeneratePPFormFro(&Hardware_DW.obj,
        Hardware_DW.obj.Waypoints, Hardware_DW.obj.TimePoints);
    }

    for (Hardware_B.c_j = 0; Hardware_B.c_j < 5; Hardware_B.c_j++) {
      Hardware_DW.obj.tunablePropertyChanged[Hardware_B.c_j] = false;
    }
  }

  Hardware_B.x_tmp_c = Hardware_B.DigitalClock;
  Hardware_B.x_tmp = Hardware_DW.obj.PPStruct.breaks[18];
  if (Hardware_B.DigitalClock == Hardware_DW.obj.PPStruct.breaks[18]) {
    for (i = 0; i < 1; i++) {
      Hardware_B.x_tmp_c = Hardware_B.x_tmp - 2.220446049250313E-15;
    }
  }

  Hardware_ppval(Hardware_DW.obj.PPDDStruct.breaks,
                 Hardware_DW.obj.PPDDStruct.coefs, Hardware_B.x_tmp_c,
                 Hardware_B.e_hat);
  Hardware_ppval(Hardware_DW.obj.PPStruct.breaks, Hardware_DW.obj.PPStruct.coefs,
                 Hardware_B.DigitalClock, Hardware_B.rtb_Product3_tmp);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kp'

  Hardware_B.dv[0] = Hardware_P.PID.Kp[0];
  Hardware_B.dv[8] = 0.0;
  Hardware_B.dv[16] = 0.0;
  Hardware_B.dv[24] = 0.0;
  Hardware_B.dv[32] = 0.0;
  Hardware_B.dv[40] = 0.0;
  Hardware_B.dv[48] = 0.0;
  Hardware_B.dv[56] = 0.0;
  Hardware_B.dv[1] = 0.0;
  Hardware_B.dv[9] = Hardware_P.PID.Kp[1];
  Hardware_B.dv[17] = 0.0;
  Hardware_B.dv[25] = 0.0;
  Hardware_B.dv[33] = 0.0;
  Hardware_B.dv[41] = 0.0;
  Hardware_B.dv[49] = 0.0;
  Hardware_B.dv[57] = 0.0;
  Hardware_B.dv[2] = 0.0;
  Hardware_B.dv[10] = 0.0;
  Hardware_B.dv[18] = Hardware_P.PID.Kp[2];
  Hardware_B.dv[26] = 0.0;
  Hardware_B.dv[34] = 0.0;
  Hardware_B.dv[42] = 0.0;
  Hardware_B.dv[50] = 0.0;
  Hardware_B.dv[58] = 0.0;
  Hardware_B.dv[3] = 0.0;
  Hardware_B.dv[11] = 0.0;
  Hardware_B.dv[19] = 0.0;
  Hardware_B.dv[27] = Hardware_P.PID.Kp[3];
  Hardware_B.dv[35] = 0.0;
  Hardware_B.dv[43] = 0.0;
  Hardware_B.dv[51] = 0.0;
  Hardware_B.dv[59] = 0.0;
  Hardware_B.dv[4] = 0.0;
  Hardware_B.dv[12] = 0.0;
  Hardware_B.dv[20] = 0.0;
  Hardware_B.dv[28] = 0.0;
  Hardware_B.dv[36] = Hardware_P.PID.Kp[4];
  Hardware_B.dv[44] = 0.0;
  Hardware_B.dv[52] = 0.0;
  Hardware_B.dv[60] = 0.0;
  Hardware_B.dv[5] = 0.0;
  Hardware_B.dv[13] = 0.0;
  Hardware_B.dv[21] = 0.0;
  Hardware_B.dv[29] = 0.0;
  Hardware_B.dv[37] = 0.0;
  Hardware_B.dv[45] = Hardware_P.PID.Kp[5];
  Hardware_B.dv[53] = 0.0;
  Hardware_B.dv[61] = 0.0;
  Hardware_B.dv[6] = 0.0;
  Hardware_B.dv[14] = 0.0;
  Hardware_B.dv[22] = 0.0;
  Hardware_B.dv[30] = 0.0;
  Hardware_B.dv[38] = 0.0;
  Hardware_B.dv[46] = 0.0;
  Hardware_B.dv[54] = Hardware_P.PID.Kp[6];
  Hardware_B.dv[62] = 0.0;
  Hardware_B.dv[7] = 0.0;
  Hardware_B.dv[15] = 0.0;
  Hardware_B.dv[23] = 0.0;
  Hardware_B.dv[31] = 0.0;
  Hardware_B.dv[39] = 0.0;
  Hardware_B.dv[47] = 0.0;
  Hardware_B.dv[55] = 0.0;
  Hardware_B.dv[63] = Hardware_P.PID.Kp[7];

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  Hardware_ppval(Hardware_DW.obj.PPDStruct.breaks,
                 Hardware_DW.obj.PPDStruct.coefs, Hardware_B.x_tmp_c,
                 Hardware_B.Product4);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kd'

  Hardware_B.dv1[0] = Hardware_P.PID.Kd[0];
  Hardware_B.dv1[8] = 0.0;
  Hardware_B.dv1[16] = 0.0;
  Hardware_B.dv1[24] = 0.0;
  Hardware_B.dv1[32] = 0.0;
  Hardware_B.dv1[40] = 0.0;
  Hardware_B.dv1[48] = 0.0;
  Hardware_B.dv1[56] = 0.0;
  Hardware_B.dv1[1] = 0.0;
  Hardware_B.dv1[9] = Hardware_P.PID.Kd[1];
  Hardware_B.dv1[17] = 0.0;
  Hardware_B.dv1[25] = 0.0;
  Hardware_B.dv1[33] = 0.0;
  Hardware_B.dv1[41] = 0.0;
  Hardware_B.dv1[49] = 0.0;
  Hardware_B.dv1[57] = 0.0;
  Hardware_B.dv1[2] = 0.0;
  Hardware_B.dv1[10] = 0.0;
  Hardware_B.dv1[18] = Hardware_P.PID.Kd[2];
  Hardware_B.dv1[26] = 0.0;
  Hardware_B.dv1[34] = 0.0;
  Hardware_B.dv1[42] = 0.0;
  Hardware_B.dv1[50] = 0.0;
  Hardware_B.dv1[58] = 0.0;
  Hardware_B.dv1[3] = 0.0;
  Hardware_B.dv1[11] = 0.0;
  Hardware_B.dv1[19] = 0.0;
  Hardware_B.dv1[27] = Hardware_P.PID.Kd[3];
  Hardware_B.dv1[35] = 0.0;
  Hardware_B.dv1[43] = 0.0;
  Hardware_B.dv1[51] = 0.0;
  Hardware_B.dv1[59] = 0.0;
  Hardware_B.dv1[4] = 0.0;
  Hardware_B.dv1[12] = 0.0;
  Hardware_B.dv1[20] = 0.0;
  Hardware_B.dv1[28] = 0.0;
  Hardware_B.dv1[36] = Hardware_P.PID.Kd[4];
  Hardware_B.dv1[44] = 0.0;
  Hardware_B.dv1[52] = 0.0;
  Hardware_B.dv1[60] = 0.0;
  Hardware_B.dv1[5] = 0.0;
  Hardware_B.dv1[13] = 0.0;
  Hardware_B.dv1[21] = 0.0;
  Hardware_B.dv1[29] = 0.0;
  Hardware_B.dv1[37] = 0.0;
  Hardware_B.dv1[45] = Hardware_P.PID.Kd[5];
  Hardware_B.dv1[53] = 0.0;
  Hardware_B.dv1[61] = 0.0;
  Hardware_B.dv1[6] = 0.0;
  Hardware_B.dv1[14] = 0.0;
  Hardware_B.dv1[22] = 0.0;
  Hardware_B.dv1[30] = 0.0;
  Hardware_B.dv1[38] = 0.0;
  Hardware_B.dv1[46] = 0.0;
  Hardware_B.dv1[54] = Hardware_P.PID.Kd[6];
  Hardware_B.dv1[62] = 0.0;
  Hardware_B.dv1[7] = 0.0;
  Hardware_B.dv1[15] = 0.0;
  Hardware_B.dv1[23] = 0.0;
  Hardware_B.dv1[31] = 0.0;
  Hardware_B.dv1[39] = 0.0;
  Hardware_B.dv1[47] = 0.0;
  Hardware_B.dv1[55] = 0.0;
  Hardware_B.dv1[63] = Hardware_P.PID.Kd[7];
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    // Sum: '<S13>/Minus' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    Hardware_B.uv[Hardware_B.c_j] = Hardware_B.rtb_Product3_tmp[Hardware_B.c_j]
      - Hardware_DW.DiscreteTimeIntegrator_DSTATE[Hardware_B.c_j];

    // Sum: '<S13>/Minus1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'

    Hardware_B.dv2[Hardware_B.c_j] = Hardware_B.Product4[Hardware_B.c_j] -
      Hardware_DW.DiscreteTimeIntegrator1_DSTATE[Hardware_B.c_j];

    // MATLAB Function: '<S11>/PD Controller'
    Hardware_B.Product3[Hardware_B.c_j] = 0.0;
  }

  // MATLAB Function: '<S11>/PD Controller'
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    Hardware_B.D17 = Hardware_B.uv[Hardware_B.c_j];
    for (Hardware_B.jj = 0; Hardware_B.jj < 8; Hardware_B.jj++) {
      Hardware_B.Product3[Hardware_B.jj] += Hardware_B.dv[(Hardware_B.c_j << 3)
        + Hardware_B.jj] * Hardware_B.D17;
    }
  }

  memset(&Hardware_B.rtb_Product3_tmp[0], 0, sizeof(real_T) << 3U);
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    Hardware_B.D17 = Hardware_B.dv2[Hardware_B.c_j];
    for (Hardware_B.jj = 0; Hardware_B.jj < 8; Hardware_B.jj++) {
      Hardware_B.rtb_Product3_tmp[Hardware_B.jj] += Hardware_B.dv1
        [(Hardware_B.c_j << 3) + Hardware_B.jj] * Hardware_B.D17;
    }
  }

  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    // Sum: '<S11>/Add1' incorporates:
    //   MATLAB Function: '<S11>/PD Controller'
    //   Sum: '<S11>/Sum'

    Hardware_B.uv[Hardware_B.c_j] = ((Hardware_B.Product3[Hardware_B.c_j] +
      Hardware_B.rtb_Product3_tmp[Hardware_B.c_j]) +
      Hardware_B.e_hat[Hardware_B.c_j]) - Hardware_B.fx[Hardware_B.c_j];

    // Product: '<S11>/Matrix Multiply'
    Hardware_B.fx[Hardware_B.c_j] = 0.0;
  }

  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    // Product: '<S11>/Matrix Multiply'
    Hardware_B.D17 = Hardware_B.uv[Hardware_B.c_j];
    for (Hardware_B.jj = 0; Hardware_B.jj < 8; Hardware_B.jj++) {
      Hardware_B.fx[Hardware_B.jj] += Hardware_B.ginv[(Hardware_B.c_j << 3) +
        Hardware_B.jj] * Hardware_B.D17;
    }

    // Product: '<S2>/Matrix Multiply' incorporates:
    //   Outport: '<Root>/ForcesAndTorque'

    Hardware_Y.ForcesAndTorque[Hardware_B.c_j] = 0.0;
  }

  for (i = 0; i < 8; i++) {
    // Product: '<S2>/Matrix Multiply' incorporates:
    //   Outport: '<Root>/ForcesAndTorque'

    Hardware_B.D17 = Hardware_B.fx[i];
    for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
      Hardware_Y.ForcesAndTorque[Hardware_B.c_j] += Hardware_B.BMinv[(i << 3) +
        Hardware_B.c_j] * Hardware_B.D17;
    }

    // Sum: '<S4>/Sum1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
    //   Inport: '<Root>/<Positions>'

    Hardware_B.e_hat[i] = Hardware_U.Positions[i] -
      Hardware_DW.DiscreteTimeIntegrator_DSTATE[i];
  }

  // MATLAB Function: '<S4>/U power x2' incorporates:
  //   Constant: '<S4>/Q3'

  Hardware_Upowerx1(Hardware_B.e_hat, Hardware_P.Differentiator.w1,
                    Hardware_B.fx);
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    // Signum: '<S4>/Sign' incorporates:
    //   Sum: '<S4>/Sum1'

    Hardware_B.DigitalClock = Hardware_B.e_hat[Hardware_B.c_j];
    if (rtIsNaN(Hardware_B.DigitalClock)) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      Hardware_B.DigitalClock = (rtNaN);
    } else if (Hardware_B.DigitalClock < 0.0) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      Hardware_B.DigitalClock = -1.0;
    } else {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      Hardware_B.DigitalClock = (Hardware_B.DigitalClock > 0.0);
    }

    Hardware_B.rtb_Product3_tmp[Hardware_B.c_j] = Hardware_B.DigitalClock;

    // Product: '<S4>/Product3' incorporates:
    //   Constant: '<S4>/G1'
    //   Signum: '<S4>/Sign'

    Hardware_B.Product3[Hardware_B.c_j] =
      Hardware_P.Differentiator.G1[Hardware_B.c_j] * Hardware_B.DigitalClock *
      Hardware_B.fx[Hardware_B.c_j];
  }

  // MATLAB Function: '<S4>/U power x1' incorporates:
  //   Constant: '<S4>/Q5'

  Hardware_Upowerx1(Hardware_B.e_hat, Hardware_P.Differentiator.p1,
                    Hardware_B.uv);

  // Product: '<S4>/Product4' incorporates:
  //   Constant: '<S4>/Q1'
  //   Signum: '<S4>/Sign1'

  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    Hardware_B.Product4[Hardware_B.c_j] =
      Hardware_P.Differentiator.Q1[Hardware_B.c_j] *
      Hardware_B.rtb_Product3_tmp[Hardware_B.c_j] * Hardware_B.uv[Hardware_B.c_j];
  }

  // End of Product: '<S4>/Product4'

  // MATLAB Function: '<S4>/U power x3' incorporates:
  //   Constant: '<S4>/Q4'

  Hardware_Upowerx1(Hardware_B.e_hat, Hardware_P.Differentiator.w2,
                    Hardware_B.uv);

  // MATLAB Function: '<S4>/U power x4' incorporates:
  //   Constant: '<S4>/Q6'

  Hardware_Upowerx1(Hardware_B.e_hat, Hardware_P.Differentiator.p2,
                    Hardware_B.fx);
  for (Hardware_B.c_j = 0; Hardware_B.c_j < 8; Hardware_B.c_j++) {
    // DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    Hardware_B.x_tmp = Hardware_DW.DiscreteTimeIntegrator1_DSTATE[Hardware_B.c_j];

    // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
    //   Product: '<S4>/Product3'
    //   Product: '<S4>/Product4'
    //   Sum: '<S4>/Sum3'

    Hardware_DW.DiscreteTimeIntegrator_DSTATE[Hardware_B.c_j] +=
      ((Hardware_B.Product3[Hardware_B.c_j] + Hardware_B.x_tmp) +
       Hardware_B.Product4[Hardware_B.c_j]) *
      Hardware_P.DiscreteTimeIntegrator_gainval;

    // Signum: '<S4>/Sign2' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'

    Hardware_B.DigitalClock = Hardware_B.rtb_Product3_tmp[Hardware_B.c_j];

    // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' incorporates:
    //   Constant: '<S4>/G2'
    //   Constant: '<S4>/Q2'
    //   Product: '<S4>/Product5'
    //   Product: '<S4>/Product6'
    //   Signum: '<S4>/Sign2'
    //   Signum: '<S4>/Sign3'
    //   Sum: '<S4>/Sum4'

    Hardware_DW.DiscreteTimeIntegrator1_DSTATE[Hardware_B.c_j] =
      (Hardware_P.Differentiator.G2[Hardware_B.c_j] * Hardware_B.DigitalClock *
       Hardware_B.uv[Hardware_B.c_j] +
       Hardware_P.Differentiator.Q2[Hardware_B.c_j] * Hardware_B.DigitalClock *
       Hardware_B.fx[Hardware_B.c_j]) *
      Hardware_P.DiscreteTimeIntegrator1_gainval + Hardware_B.x_tmp;
  }

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  (&Hardware_M)->Timing.clockTick0++;
}

// Model initialize function
void Hardware::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' 
      Hardware_DW.DiscreteTimeIntegrator_DSTATE[i] =
        Hardware_P.DiscreteTimeIntegrator_IC;

      // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' 
      Hardware_DW.DiscreteTimeIntegrator1_DSTATE[i] =
        Hardware_P.DiscreteTimeIntegrator1_IC;
    }

    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memset(&Hardware_DW.obj.AccelerationBoundaryCondition[0], 0, 10U * sizeof
           (real_T));
    for (i = 0; i < 5; i++) {
      Hardware_DW.obj.tunablePropertyChanged[i] = false;
    }

    memcpy(&Hardware_DW.obj.Waypoints[0], &Hardware_P.Trajectory.Waypoints[0],
           144U * sizeof(real_T));
    memcpy(&Hardware_DW.obj.TimePoints[0], &Hardware_P.Trajectory.Tstamps[0],
           18U * sizeof(real_T));
    memcpy(&Hardware_DW.obj.VelocityBoundaryCondition[0],
           &Hardware_P.PolynomialTrajectory_VelocityBo[0], 144U * sizeof(real_T));
    Hardware_DW.obj.isInitialized = 1;
    PolyTrajSys_regeneratePPFormFro(&Hardware_DW.obj, Hardware_DW.obj.Waypoints,
      Hardware_DW.obj.TimePoints);
    Hardware_DW.obj.TunablePropsChanged = false;

    // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  }
}

// Model terminate function
void Hardware::terminate()
{
  // (no terminate code required)
}

const char_T* Hardware::RT_MODEL_Hardware_T::getErrorStatus() const
{
  return (errorStatus);
}

void Hardware::RT_MODEL_Hardware_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

// Constructor
Hardware::Hardware() :
  Hardware_U(),
  Hardware_Y(),
  Hardware_B(),
  Hardware_DW(),
  Hardware_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
Hardware::~Hardware()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
Hardware::RT_MODEL_Hardware_T * Hardware::getRTM()
{
  return (&Hardware_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
