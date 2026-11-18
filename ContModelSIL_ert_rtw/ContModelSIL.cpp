//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ContModelSIL.cpp
//
// Code generated for Simulink model 'ContModelSIL'.
//
// Model version                  : 1.107
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Sat Nov 14 00:21:48 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "ContModelSIL.h"
#include "MW_PX4_Actuators.h"
#include "rtwtypes.h"
#include "ContModelSIL_types.h"
#include <math.h>
#include "ContModelSIL_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>

// Block signals (default storage)
B_ContModelSIL_T ContModelSIL_B;

// Block states (default storage)
DW_ContModelSIL_T ContModelSIL_DW;

// Real-time model
RT_MODEL_ContModelSIL_T ContModelSIL_M_ = RT_MODEL_ContModelSIL_T();
RT_MODEL_ContModelSIL_T *const ContModelSIL_M = &ContModelSIL_M_;

// Forward declaration for local functions
static void ContModelSIL_xzgetrf(real_T A[64], int32_T ipiv[8], int32_T *info);
static void ContModelSIL_inv(const real_T x[64], real_T y[64]);
static void ContModelSIL_mldivide_p(const real_T A[64], real_T B[8]);
static void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
  const real_T waypoints[32], const real_T timeData[4]);
static void ContModelSIL_ppval(const real_T pp_breaks[6], const real_T pp_coefs
  [160], real_T x, real_T v[8]);
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

// Function for MATLAB Function: '<S1>/MATLAB Function1'
static void ContModelSIL_xzgetrf(real_T A[64], int32_T ipiv[8], int32_T *info)
{
  int32_T n;
  for (n = 0; n < 8; n++) {
    ipiv[n] = n + 1;
  }

  *info = 0;
  for (int32_T j = 0; j < 7; j++) {
    int32_T a;
    int32_T jA;
    int32_T jj;
    jj = j * 9;
    n = 9 - j;
    a = 0;
    ContModelSIL_B.smax_p = fabs(A[jj]);
    for (int32_T k = 2; k < n; k++) {
      ContModelSIL_B.s_a = fabs(A[(jj + k) - 1]);
      if (ContModelSIL_B.s_a > ContModelSIL_B.smax_p) {
        a = k - 1;
        ContModelSIL_B.smax_p = ContModelSIL_B.s_a;
      }
    }

    if (A[jj + a] != 0.0) {
      if (a != 0) {
        a += j;
        ipiv[j] = a + 1;
        for (int32_T k = 0; k < 8; k++) {
          n = k << 3;
          jA = n + j;
          ContModelSIL_B.smax_p = A[jA];
          n += a;
          A[jA] = A[n];
          A[n] = ContModelSIL_B.smax_p;
        }
      }

      n = (jj - j) + 8;
      for (int32_T k = jj + 2; k <= n; k++) {
        A[k - 1] /= A[jj];
      }
    } else {
      *info = j + 1;
    }

    a = 6 - j;
    jA = jj + 10;
    for (int32_T k = 0; k <= a; k++) {
      ContModelSIL_B.smax_p = A[((k << 3) + jj) + 8];
      if (ContModelSIL_B.smax_p != 0.0) {
        int32_T c;
        c = (jA - j) + 6;
        for (n = jA; n <= c; n++) {
          A[n - 1] += A[((jj + n) - jA) + 1] * -ContModelSIL_B.smax_p;
        }
      }

      jA += 8;
    }
  }

  if ((*info == 0) && !(A[63] != 0.0)) {
    *info = 8;
  }
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
static void ContModelSIL_inv(const real_T x[64], real_T y[64])
{
  int32_T b_i;
  int32_T i;
  int32_T info;
  int32_T ipiv;
  int32_T jBcol;
  int32_T kAcol;
  int32_T pipk;
  for (info = 0; info < 64; info++) {
    y[info] = 0.0;
    ContModelSIL_B.b_x[info] = x[info];
  }

  ContModelSIL_xzgetrf(ContModelSIL_B.b_x, ContModelSIL_B.ipiv, &info);
  for (info = 0; info < 8; info++) {
    ContModelSIL_B.p_c[info] = static_cast<int8_T>(info + 1);
  }

  for (info = 0; info < 7; info++) {
    ipiv = ContModelSIL_B.ipiv[info];
    if (ipiv > info + 1) {
      pipk = ContModelSIL_B.p_c[ipiv - 1];
      ContModelSIL_B.p_c[ipiv - 1] = ContModelSIL_B.p_c[info];
      ContModelSIL_B.p_c[info] = static_cast<int8_T>(pipk);
    }
  }

  for (pipk = 0; pipk < 8; pipk++) {
    ipiv = (ContModelSIL_B.p_c[pipk] - 1) << 3;
    y[pipk + ipiv] = 1.0;
    for (jBcol = pipk + 1; jBcol < 9; jBcol++) {
      info = (ipiv + jBcol) - 1;
      if (y[info] != 0.0) {
        for (i = jBcol + 1; i < 9; i++) {
          kAcol = (ipiv + i) - 1;
          y[kAcol] -= ContModelSIL_B.b_x[(((jBcol - 1) << 3) + i) - 1] * y[info];
        }
      }
    }
  }

  for (pipk = 0; pipk < 8; pipk++) {
    jBcol = pipk << 3;
    for (i = 7; i >= 0; i--) {
      kAcol = i << 3;
      info = i + jBcol;
      ContModelSIL_B.d186 = y[info];
      if (ContModelSIL_B.d186 != 0.0) {
        y[info] = ContModelSIL_B.d186 / ContModelSIL_B.b_x[i + kAcol];
        for (b_i = 0; b_i < i; b_i++) {
          ipiv = b_i + jBcol;
          y[ipiv] -= ContModelSIL_B.b_x[b_i + kAcol] * y[info];
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
static void ContModelSIL_mldivide_p(const real_T A[64], real_T B[8])
{
  real_T temp;
  int32_T info;
  int32_T ipiv;
  int32_T kAcol;
  memcpy(&ContModelSIL_B.b_A[0], &A[0], sizeof(real_T) << 6U);
  ContModelSIL_xzgetrf(ContModelSIL_B.b_A, ContModelSIL_B.ipiv_c, &info);
  for (info = 0; info < 7; info++) {
    ipiv = ContModelSIL_B.ipiv_c[info];
    if (info + 1 != ipiv) {
      temp = B[info];
      B[info] = B[ipiv - 1];
      B[ipiv - 1] = temp;
    }
  }

  for (info = 0; info < 8; info++) {
    kAcol = info << 3;
    if (B[info] != 0.0) {
      for (ipiv = info + 2; ipiv < 9; ipiv++) {
        B[ipiv - 1] -= ContModelSIL_B.b_A[(ipiv + kAcol) - 1] * B[info];
      }
    }
  }

  for (info = 7; info >= 0; info--) {
    kAcol = info << 3;
    temp = B[info];
    if (temp != 0.0) {
      B[info] = temp / ContModelSIL_B.b_A[info + kAcol];
      for (ipiv = 0; ipiv < info; ipiv++) {
        B[ipiv] -= ContModelSIL_B.b_A[ipiv + kAcol] * B[info];
      }
    }
  }
}

static void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
  const real_T waypoints[32], const real_T timeData[4])
{
  int32_T b_coeffVec_tmp;
  int32_T b_i;
  int32_T b_j;
  static const int8_T tmp[4] = { 0, 0, 0, 1 };

  memset(&ContModelSIL_B.coefMat[0], 0, 96U * sizeof(real_T));
  for (b_i = 0; b_i < 3; b_i++) {
    // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
    ContModelSIL_B.finalTime = timeData[b_i + 1] - timeData[b_i];
    for (b_j = 0; b_j < 8; b_j++) {
      // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
      b_coeffVec_tmp = (b_i << 3) + b_j;
      ContModelSIL_B.b_coeffVec[0] = waypoints[b_coeffVec_tmp];
      ContModelSIL_B.b_coeffVec[1] = obj->
        VelocityBoundaryCondition[b_coeffVec_tmp];
      b_coeffVec_tmp = ((b_i + 1) << 3) + b_j;
      ContModelSIL_B.waypoints_idx_0 = waypoints[b_coeffVec_tmp] -
        (ContModelSIL_B.finalTime * ContModelSIL_B.b_coeffVec[1] +
         ContModelSIL_B.b_coeffVec[0]);
      ContModelSIL_B.waypoints_idx_1 = obj->
        VelocityBoundaryCondition[b_coeffVec_tmp] - (0.0 *
        ContModelSIL_B.b_coeffVec[0] + ContModelSIL_B.b_coeffVec[1]);
      ContModelSIL_B.b_coeffVec[3] = ContModelSIL_B.b_coeffVec[0];
      b_coeffVec_tmp = ((b_i << 3) + b_j) + 1;
      ContModelSIL_B.coefMat_tmp = ContModelSIL_B.finalTime *
        ContModelSIL_B.finalTime;
      ContModelSIL_B.coefMat[b_coeffVec_tmp - 1] = 1.0 /
        ContModelSIL_B.coefMat_tmp * ContModelSIL_B.waypoints_idx_1 + -2.0 /
        rt_powd_snf(ContModelSIL_B.finalTime, 3.0) *
        ContModelSIL_B.waypoints_idx_0;
      ContModelSIL_B.coefMat[b_coeffVec_tmp + 23] = 3.0 /
        ContModelSIL_B.coefMat_tmp * ContModelSIL_B.waypoints_idx_0 + -1.0 /
        ContModelSIL_B.finalTime * ContModelSIL_B.waypoints_idx_1;
      ContModelSIL_B.coefMat[b_coeffVec_tmp + 47] = ContModelSIL_B.b_coeffVec[1];
      ContModelSIL_B.coefMat[b_coeffVec_tmp + 71] = ContModelSIL_B.b_coeffVec[3];
    }
  }

  memset(&ContModelSIL_B.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
  memset(&ContModelSIL_B.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    b_i = tmp[b_j];
    for (b_coeffVec_tmp = 0; b_coeffVec_tmp < 8; b_coeffVec_tmp++) {
      ContModelSIL_B.coeffMat[b_coeffVec_tmp + 24] += ContModelSIL_B.coefMat[24 *
        b_j + b_coeffVec_tmp] * static_cast<real_T>(b_i);
    }
  }

  memset(&ContModelSIL_B.coefsWithFlatStart[0], 0, sizeof(real_T) << 7U);
  memcpy(&ContModelSIL_B.coefsWithFlatStart[0], &ContModelSIL_B.coeffMat[0],
         sizeof(real_T) << 3U);
  memcpy(&ContModelSIL_B.coefsWithFlatStart[32], &ContModelSIL_B.coeffMat[8],
         sizeof(real_T) << 3U);
  memcpy(&ContModelSIL_B.coefsWithFlatStart[64], &ContModelSIL_B.coeffMat[16],
         sizeof(real_T) << 3U);
  memcpy(&ContModelSIL_B.coefsWithFlatStart[96], &ContModelSIL_B.coeffMat[24],
         sizeof(real_T) << 3U);

  // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
  memcpy(&ContModelSIL_B.coefsWithFlatStart[8], &ContModelSIL_B.coefMat[0], 24U *
         sizeof(real_T));
  memcpy(&ContModelSIL_B.coefsWithFlatStart[40], &ContModelSIL_B.coefMat[24],
         24U * sizeof(real_T));
  memcpy(&ContModelSIL_B.coefsWithFlatStart[72], &ContModelSIL_B.coefMat[48],
         24U * sizeof(real_T));
  memcpy(&ContModelSIL_B.coefsWithFlatStart[104], &ContModelSIL_B.coefMat[72],
         24U * sizeof(real_T));
  ContModelSIL_B.breaksWithFlatStart[0] = timeData[0] - 1.0;
  ContModelSIL_B.breaksWithFlatStart[1] = timeData[0];
  ContModelSIL_B.breaksWithFlatStart[2] = timeData[1];
  ContModelSIL_B.breaksWithFlatStart[3] = timeData[2];
  ContModelSIL_B.breaksWithFlatStart[4] = timeData[3];
  ContModelSIL_B.finalTime = timeData[3] - timeData[2];
  ContModelSIL_B.b_coeffVec[0] = rt_powd_snf(ContModelSIL_B.finalTime, 3.0);
  ContModelSIL_B.b_coeffVec[1] = rt_powd_snf(ContModelSIL_B.finalTime, 2.0);
  ContModelSIL_B.b_coeffVec[2] = rt_powd_snf(ContModelSIL_B.finalTime, 1.0);
  ContModelSIL_B.b_coeffVec[3] = rt_powd_snf(ContModelSIL_B.finalTime, 0.0);
  memset(&ContModelSIL_B.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
  memset(&ContModelSIL_B.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    ContModelSIL_B.finalTime = ContModelSIL_B.b_coeffVec[b_j];
    for (b_i = 0; b_i < 8; b_i++) {
      ContModelSIL_B.coeffMat[b_i + 24] += ContModelSIL_B.coefsWithFlatStart
        [((b_j << 5) + b_i) + 24] * ContModelSIL_B.finalTime;
    }
  }

  memset(&obj->PPDStruct.coefs[0], 0, 160U * sizeof(real_T));
  for (b_j = 0; b_j < 4; b_j++) {
    // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
    memcpy(&obj->PPDStruct.coefs[b_j * 40],
           &ContModelSIL_B.coefsWithFlatStart[b_j << 5], sizeof(real_T) << 5U);
    memcpy(&obj->PPDStruct.coefs[b_j * 40 + 32], &ContModelSIL_B.coeffMat[b_j <<
           3], sizeof(real_T) << 3U);
  }

  for (b_j = 0; b_j < 5; b_j++) {
    // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
    obj->PPStruct.breaks[b_j] = ContModelSIL_B.breaksWithFlatStart[b_j];
  }

  // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
  obj->PPStruct.breaks[5] = timeData[3] + 1.0;
  for (b_j = 0; b_j < 160; b_j++) {
    // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
    obj->PPStruct.coefs[b_j] = obj->PPDStruct.coefs[b_j];
    obj->PPDStruct.coefs[b_j] = 0.0;
  }

  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 40; b_j++) {
      // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
      obj->PPDStruct.coefs[b_j + 40 * (b_i + 1)] = obj->PPStruct.coefs[b_i * 40
        + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  memset(&obj->PPDDStruct.coefs[0], 0, 160U * sizeof(real_T));
  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 40; b_j++) {
      // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
      obj->PPDDStruct.coefs[b_j + 40 * (b_i + 1)] = obj->PPDStruct.coefs[b_i *
        40 + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  for (b_j = 0; b_j < 6; b_j++) {
    // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
    obj->PPDStruct.breaks[b_j] = obj->PPStruct.breaks[b_j];
    obj->PPDDStruct.breaks[b_j] = obj->PPStruct.breaks[b_j];
  }

  obj->PPFormUpdatedNeeded = false;
}

static void ContModelSIL_ppval(const real_T pp_breaks[6], const real_T pp_coefs
  [160], real_T x, real_T v[8])
{
  // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
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
    high_i = 6;
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
      high_i = ((low_i + 1) * 40 + low_ip1) - 1;
      for (mid_i = 0; mid_i < 8; mid_i++) {
        v[mid_i] = pp_coefs[(high_i + mid_i) + 1] + xloc * v[mid_i];
      }
    }
  }

  // End of Start for MATLABSystem: '<S6>/Polynomial Trajectory'
}

// Model step function
void ContModelSIL_step(void)
{
  real_T tmp;
  int32_T i;
  int8_T ipiv;
  uint8_T b_varargout_1;
  boolean_T exitg1;
  boolean_T propChange;
  for (i = 0; i < 8; i++) {
    // Signum: '<S8>/Sign3' incorporates:
    //   Delay: '<S8>/Delay2'
    //   Product: '<S7>/Product7'

    ContModelSIL_B.DigitalClock = ContModelSIL_DW.Delay2_DSTATE[i];

    // Abs: '<S8>/Abs4' incorporates:
    //   Delay: '<S8>/Delay2'
    //   Product: '<S7>/Product7'

    ContModelSIL_DW.Delay2_DSTATE[i] = fabs(ContModelSIL_DW.Delay2_DSTATE[i]);

    // Sum: '<S8>/Sum5' incorporates:
    //   Constant: '<S8>/Constant11'
    //   Math: '<S8>/Power3'
    //   Product: '<S7>/Product7'

    ContModelSIL_B.Observer_alpha = ContModelSIL_P.Observer.alpha[i];

    // Math: '<S8>/Power3' incorporates:
    //   Constant: '<S8>/Constant11'
    //   Constant: '<S8>/Constant2'
    //   Delay: '<S8>/Delay2'
    //   Gain: '<S8>/Gain3'
    //   Product: '<S7>/Product7'
    //   Sum: '<S8>/Sum5'

    ContModelSIL_DW.Delay2_DSTATE[i] = rt_powd_snf
      (ContModelSIL_DW.Delay2_DSTATE[i], (ContModelSIL_B.Observer_alpha +
        ContModelSIL_P.Constant2_Value[i]) * ContModelSIL_P.Gain3_Gain);

    // Signum: '<S8>/Sign3'
    if (rtIsNaN(ContModelSIL_B.DigitalClock)) {
      ContModelSIL_B.D17 = (rtNaN);
    } else if (ContModelSIL_B.DigitalClock < 0.0) {
      ContModelSIL_B.D17 = -1.0;
    } else {
      ContModelSIL_B.D17 = (ContModelSIL_B.DigitalClock > 0.0);
    }

    // Product: '<S8>/Product6' incorporates:
    //   Constant: '<S8>/Constant1'
    //   Delay: '<S8>/Delay2'
    //   Product: '<S7>/Product7'
    //   Signum: '<S8>/Sign3'

    ContModelSIL_B.Sign3[i] = ContModelSIL_P.Observer.E1[i] * ContModelSIL_B.D17
      * ContModelSIL_DW.Delay2_DSTATE[i];

    // Gain: '<S8>/Gain5' incorporates:
    //   Constant: '<S8>/Constant11'
    //   Constant: '<S8>/Constant6'
    //   Delay: '<S8>/Delay2'
    //   Sum: '<S8>/Sum9'

    ContModelSIL_DW.Delay2_DSTATE[i] = (ContModelSIL_B.Observer_alpha +
      ContModelSIL_P.Constant6_Value[i]) * ContModelSIL_P.Gain5_Gain;

    // Delay: '<S8>/Delay3'
    ContModelSIL_B.DigitalClock = ContModelSIL_DW.Delay3_DSTATE[i];

    // Signum: '<S8>/Sign5'
    if (rtIsNaN(ContModelSIL_B.DigitalClock)) {
      ContModelSIL_B.D17 = (rtNaN);
    } else if (ContModelSIL_B.DigitalClock < 0.0) {
      ContModelSIL_B.D17 = -1.0;
    } else {
      ContModelSIL_B.D17 = (ContModelSIL_B.DigitalClock > 0.0);
    }

    // Product: '<S8>/Product8' incorporates:
    //   Abs: '<S8>/Abs6'
    //   Constant: '<S8>/Constant'
    //   Delay: '<S8>/Delay2'
    //   Delay: '<S8>/Delay3'
    //   Math: '<S8>/Power5'
    //   Signum: '<S8>/Sign5'

    ContModelSIL_B.Product8[i] = ContModelSIL_P.Observer.E2[i] *
      ContModelSIL_B.D17 * rt_powd_snf(fabs(ContModelSIL_DW.Delay3_DSTATE[i]),
      ContModelSIL_DW.Delay2_DSTATE[i]);

    // Delay: '<S8>/Delay7' incorporates:
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator3'

    ContModelSIL_B.DigitalClock = ContModelSIL_DW.Delay7_DSTATE[i];

    // Delay: '<S8>/Delay9' incorporates:
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator3'

    ContModelSIL_B.u = ContModelSIL_DW.Delay9_DSTATE[i];

    // Delay: '<S8>/Delay8' incorporates:
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator3'

    ContModelSIL_B.Observer_alpha = ContModelSIL_DW.Delay8_DSTATE[i];

    // Signum: '<S8>/Sign7'
    if (rtIsNaN(ContModelSIL_B.DigitalClock)) {
      ContModelSIL_B.D17 = (rtNaN);
    } else if (ContModelSIL_B.DigitalClock < 0.0) {
      ContModelSIL_B.D17 = -1.0;
    } else {
      ContModelSIL_B.D17 = (ContModelSIL_B.DigitalClock > 0.0);
    }

    // Signum: '<S8>/Sign8'
    if (rtIsNaN(ContModelSIL_B.u)) {
      ContModelSIL_B.D18 = (rtNaN);
    } else if (ContModelSIL_B.u < 0.0) {
      ContModelSIL_B.D18 = -1.0;
    } else {
      ContModelSIL_B.D18 = (ContModelSIL_B.u > 0.0);
    }

    // Signum: '<S8>/Sign9'
    if (rtIsNaN(ContModelSIL_B.Observer_alpha)) {
      ContModelSIL_B.D27 = (rtNaN);
    } else if (ContModelSIL_B.Observer_alpha < 0.0) {
      ContModelSIL_B.D27 = -1.0;
    } else {
      ContModelSIL_B.D27 = (ContModelSIL_B.Observer_alpha > 0.0);
    }

    // DiscreteIntegrator: '<S8>/Discrete-Time Integrator3' incorporates:
    //   Abs: '<S8>/Abs8'
    //   Abs: '<S8>/Abs9'
    //   Constant: '<S8>/Constant10'
    //   Constant: '<S8>/Constant11'
    //   Constant: '<S8>/Constant12'
    //   Constant: '<S8>/Constant3'
    //   Constant: '<S8>/Constant5'
    //   Delay: '<S8>/Delay7'
    //   Delay: '<S8>/Delay9'
    //   Math: '<S8>/Power7'
    //   Math: '<S8>/Power8'
    //   Product: '<S8>/Product11'
    //   Product: '<S8>/Product12'
    //   Product: '<S8>/Product13'
    //   Signum: '<S8>/Sign7'
    //   Signum: '<S8>/Sign8'
    //   Signum: '<S8>/Sign9'
    //   Sum: '<S8>/Sum13'

    ContModelSIL_DW.DiscreteTimeIntegrator3_DSTATE[i] +=
      ((ContModelSIL_P.Observer.E3[i] * ContModelSIL_B.D17 * rt_powd_snf(fabs
         (ContModelSIL_DW.Delay7_DSTATE[i]), ContModelSIL_P.Observer.alpha[i]) +
        ContModelSIL_P.Observer.MU3[i] * ContModelSIL_B.D18 * rt_powd_snf(fabs
         (ContModelSIL_DW.Delay9_DSTATE[i]), ContModelSIL_P.Observer.beta[i])) +
       ContModelSIL_P.Observer.E4[i] * ContModelSIL_B.D27) *
      ContModelSIL_P.DiscreteTimeIntegrator3_gainval;

    // Product: '<S8>/Matrix Multiply' incorporates:
    //   Delay: '<S8>/Delay2'
    //   Product: '<S7>/Product7'

    ContModelSIL_DW.Delay2_DSTATE[i] = 0.0;
  }

  // Product: '<S8>/Matrix Multiply' incorporates:
  //   Delay: '<S8>/Delay2'
  //   Delay: '<S8>/Delay4'
  //   Delay: '<S8>/Delay5'
  //   Product: '<S7>/Product7'

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.D17 = ContModelSIL_DW.Delay4_DSTATE[ContModelSIL_B.c_j];
    for (ContModelSIL_B.jj = 0; ContModelSIL_B.jj < 8; ContModelSIL_B.jj++) {
      ContModelSIL_DW.Delay2_DSTATE[ContModelSIL_B.jj] +=
        ContModelSIL_DW.Delay5_DSTATE[(ContModelSIL_B.c_j << 3) +
        ContModelSIL_B.jj] * ContModelSIL_B.D17;
    }
  }

  for (i = 0; i < 8; i++) {
    // Sum: '<S8>/Sum10' incorporates:
    //   Constant: '<S8>/Constant12'
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator1'

    ContModelSIL_B.Observer_alpha = ContModelSIL_P.Observer.beta[i];

    // Delay: '<S8>/Delay6' incorporates:
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator1'

    ContModelSIL_B.DigitalClock = ContModelSIL_DW.Delay6_DSTATE[i];

    // Signum: '<S8>/Sign6'
    if (rtIsNaN(ContModelSIL_B.DigitalClock)) {
      ContModelSIL_B.D17 = (rtNaN);
    } else if (ContModelSIL_B.DigitalClock < 0.0) {
      ContModelSIL_B.D17 = -1.0;
    } else {
      ContModelSIL_B.D17 = (ContModelSIL_B.DigitalClock > 0.0);
    }

    // DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' incorporates:
    //   Abs: '<S8>/Abs7'
    //   Constant: '<S8>/Constant12'
    //   Constant: '<S8>/Constant7'
    //   Constant: '<S8>/Constant9'
    //   Delay: '<S8>/Delay2'
    //   Delay: '<S8>/Delay6'
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator3'
    //   Gain: '<S8>/Gain6'
    //   Math: '<S8>/Power6'
    //   Product: '<S7>/Product7'
    //   Product: '<S8>/Product8'
    //   Product: '<S8>/Product9'
    //   Signum: '<S8>/Sign6'
    //   Sum: '<S8>/Sum10'
    //   Sum: '<S8>/Sum11'

    ContModelSIL_B.u = (rt_powd_snf(fabs(ContModelSIL_DW.Delay6_DSTATE[i]),
      (ContModelSIL_B.Observer_alpha + ContModelSIL_P.Constant7_Value[i]) *
      ContModelSIL_P.Gain6_Gain) * (ContModelSIL_P.Observer.MU2[i] *
      ContModelSIL_B.D17) + ((ContModelSIL_B.Product8[i] +
      ContModelSIL_DW.DiscreteTimeIntegrator3_DSTATE[i]) +
      ContModelSIL_DW.Delay2_DSTATE[i])) *
      ContModelSIL_P.DiscreteTimeIntegrator1_gainval +
      ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[i];
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[i] = ContModelSIL_B.u;

    // Gain: '<S8>/Gain4' incorporates:
    //   Constant: '<S8>/Constant12'
    //   Constant: '<S8>/Constant4'
    //   Delay: '<S8>/Delay2'
    //   Sum: '<S8>/Sum6'

    ContModelSIL_DW.Delay2_DSTATE[i] = (ContModelSIL_B.Observer_alpha +
      ContModelSIL_P.Constant4_Value[i]) * ContModelSIL_P.Gain4_Gain;

    // Delay: '<S8>/Delay1' incorporates:
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator'

    ContModelSIL_B.DigitalClock = ContModelSIL_DW.Delay1_DSTATE[i];

    // Signum: '<S8>/Sign4'
    if (rtIsNaN(ContModelSIL_B.DigitalClock)) {
      ContModelSIL_B.D17 = (rtNaN);
    } else if (ContModelSIL_B.DigitalClock < 0.0) {
      ContModelSIL_B.D17 = -1.0;
    } else {
      ContModelSIL_B.D17 = (ContModelSIL_B.DigitalClock > 0.0);
    }

    // DiscreteIntegrator: '<S8>/Discrete-Time Integrator' incorporates:
    //   Abs: '<S8>/Abs5'
    //   Constant: '<S8>/Constant8'
    //   Delay: '<S8>/Delay1'
    //   Delay: '<S8>/Delay2'
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator1'
    //   Math: '<S8>/Power4'
    //   Product: '<S8>/Product6'
    //   Product: '<S8>/Product7'
    //   Signum: '<S8>/Sign4'
    //   Sum: '<S8>/Sum7'

    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[i] +=
      (ContModelSIL_P.Observer.MU1[i] * ContModelSIL_B.D17 * rt_powd_snf(fabs
        (ContModelSIL_DW.Delay1_DSTATE[i]), ContModelSIL_DW.Delay2_DSTATE[i]) +
       (ContModelSIL_B.Sign3[i] + ContModelSIL_B.u)) *
      ContModelSIL_P.DiscreteTimeIntegrator_gainval;
  }

  // MATLAB Function: '<S11>/GetBInvMatrix' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  ContModelSIL_B.DigitalClock = cos
    (ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[5]);
  ContModelSIL_B.Observer_alpha = sin
    (ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3]);
  ContModelSIL_B.u = sin(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[5]);
  ContModelSIL_B.x_tmp = cos(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3]);
  ContModelSIL_B.x_tmp_b = sin(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]);
  ContModelSIL_B.x_tmp_p = cos(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]);
  ContModelSIL_B.smax = tan(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]);
  memset(&ContModelSIL_B.ginv[0], 0, sizeof(real_T) << 6U);
  memset(&ContModelSIL_B.BMinv[0], 0, sizeof(real_T) << 6U);
  ContModelSIL_B.ginv[0] = ContModelSIL_B.DigitalClock * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.rtb_ginv_tmp_tmp = ContModelSIL_B.DigitalClock *
    ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.rtb_ginv_tmp_tmp_o = -ContModelSIL_B.x_tmp * ContModelSIL_B.u;
  ContModelSIL_B.rtb_ginv_tmp_h = ContModelSIL_B.rtb_ginv_tmp_tmp *
    ContModelSIL_B.x_tmp_b + ContModelSIL_B.rtb_ginv_tmp_tmp_o;
  ContModelSIL_B.ginv[8] = ContModelSIL_B.rtb_ginv_tmp_h;
  ContModelSIL_B.rtb_ginv_tmp_i = ContModelSIL_B.Observer_alpha *
    ContModelSIL_B.u;
  ContModelSIL_B.rtb_ginv_tmp_o = ContModelSIL_B.x_tmp *
    ContModelSIL_B.DigitalClock;
  ContModelSIL_B.rtb_ginv_tmp_j = ContModelSIL_B.rtb_ginv_tmp_o *
    ContModelSIL_B.x_tmp_b + ContModelSIL_B.rtb_ginv_tmp_i;
  ContModelSIL_B.ginv[16] = ContModelSIL_B.rtb_ginv_tmp_j;
  ContModelSIL_B.ginv[24] = 0.0;
  ContModelSIL_B.ginv[32] = 0.0;
  ContModelSIL_B.ginv[40] = 0.0;
  ContModelSIL_B.ginv[1] = ContModelSIL_B.x_tmp_p * ContModelSIL_B.u;
  ContModelSIL_B.rtb_ginv_tmp_i = ContModelSIL_B.rtb_ginv_tmp_i *
    ContModelSIL_B.x_tmp_b + ContModelSIL_B.rtb_ginv_tmp_o;
  ContModelSIL_B.ginv[9] = ContModelSIL_B.rtb_ginv_tmp_i;
  ContModelSIL_B.rtb_ginv_tmp_o = ContModelSIL_B.x_tmp * ContModelSIL_B.u *
    ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.rtb_ginv_tmp_e = -ContModelSIL_B.DigitalClock *
    ContModelSIL_B.Observer_alpha + ContModelSIL_B.rtb_ginv_tmp_o;
  ContModelSIL_B.ginv[17] = ContModelSIL_B.rtb_ginv_tmp_e;
  ContModelSIL_B.ginv[25] = 0.0;
  ContModelSIL_B.ginv[33] = 0.0;
  ContModelSIL_B.ginv[41] = 0.0;
  ContModelSIL_B.ginv[2] = -ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.ginv[10] = ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.ginv[18] = ContModelSIL_B.x_tmp * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.ginv[26] = 0.0;
  ContModelSIL_B.ginv[34] = 0.0;
  ContModelSIL_B.ginv[42] = 0.0;
  ContModelSIL_B.ginv[3] = 0.0;
  ContModelSIL_B.ginv[11] = 0.0;
  ContModelSIL_B.ginv[19] = 0.0;
  ContModelSIL_B.ginv[27] = 1.0;
  ContModelSIL_B.ginv[35] = ContModelSIL_B.Observer_alpha * ContModelSIL_B.smax;
  ContModelSIL_B.ginv[43] = ContModelSIL_B.x_tmp * ContModelSIL_B.smax;
  ContModelSIL_B.ginv[4] = 0.0;
  ContModelSIL_B.ginv[12] = 0.0;
  ContModelSIL_B.ginv[20] = 0.0;
  ContModelSIL_B.ginv[28] = 0.0;
  ContModelSIL_B.ginv[36] = ContModelSIL_B.x_tmp;
  ContModelSIL_B.ginv[44] = -ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.ginv[5] = 0.0;
  ContModelSIL_B.ginv[13] = 0.0;
  ContModelSIL_B.ginv[21] = 0.0;
  ContModelSIL_B.ginv[29] = 0.0;
  ContModelSIL_B.rtb_ginv_tmp_n = 1.0 / ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.ginv[37] = ContModelSIL_B.rtb_ginv_tmp_n *
    ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.ginv[45] = ContModelSIL_B.rtb_ginv_tmp_n * ContModelSIL_B.x_tmp;
  ContModelSIL_B.ginv[54] = 1.0;
  ContModelSIL_B.ginv[55] = 0.0;
  ContModelSIL_B.ginv[62] = 0.0;
  ContModelSIL_B.ginv[63] = 1.0;
  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.ipiv_k[ContModelSIL_B.c_j] = static_cast<int8_T>
      (ContModelSIL_B.c_j + 1);
  }

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 7; ContModelSIL_B.c_j++) {
    ContModelSIL_B.jj = ContModelSIL_B.c_j * 9;
    i = 9 - ContModelSIL_B.c_j;
    ContModelSIL_B.jA = 0;
    ContModelSIL_B.smax = fabs(ContModelSIL_B.ginv[ContModelSIL_B.jj]);
    for (ContModelSIL_B.d_k = 2; ContModelSIL_B.d_k < i; ContModelSIL_B.d_k++) {
      ContModelSIL_B.s = fabs(ContModelSIL_B.ginv[(ContModelSIL_B.jj +
        ContModelSIL_B.d_k) - 1]);
      if (ContModelSIL_B.s > ContModelSIL_B.smax) {
        ContModelSIL_B.jA = ContModelSIL_B.d_k - 1;
        ContModelSIL_B.smax = ContModelSIL_B.s;
      }
    }

    if (ContModelSIL_B.ginv[ContModelSIL_B.jj + ContModelSIL_B.jA] != 0.0) {
      if (ContModelSIL_B.jA != 0) {
        i = ContModelSIL_B.c_j + ContModelSIL_B.jA;
        ContModelSIL_B.ipiv_k[ContModelSIL_B.c_j] = static_cast<int8_T>(i + 1);
        for (ContModelSIL_B.jA = 0; ContModelSIL_B.jA < 8; ContModelSIL_B.jA++)
        {
          ContModelSIL_B.kAcol = ContModelSIL_B.jA << 3;
          ContModelSIL_B.d_k = ContModelSIL_B.kAcol + ContModelSIL_B.c_j;
          ContModelSIL_B.smax = ContModelSIL_B.ginv[ContModelSIL_B.d_k];
          ContModelSIL_B.kAcol += i;
          ContModelSIL_B.ginv[ContModelSIL_B.d_k] =
            ContModelSIL_B.ginv[ContModelSIL_B.kAcol];
          ContModelSIL_B.ginv[ContModelSIL_B.kAcol] = ContModelSIL_B.smax;
        }
      }

      i = (ContModelSIL_B.jj - ContModelSIL_B.c_j) + 8;
      for (ContModelSIL_B.jA = ContModelSIL_B.jj + 2; ContModelSIL_B.jA <= i;
           ContModelSIL_B.jA++) {
        ContModelSIL_B.ginv[ContModelSIL_B.jA - 1] /=
          ContModelSIL_B.ginv[ContModelSIL_B.jj];
      }
    }

    i = 6 - ContModelSIL_B.c_j;
    ContModelSIL_B.jA = ContModelSIL_B.jj + 10;
    for (ContModelSIL_B.d_k = 0; ContModelSIL_B.d_k <= i; ContModelSIL_B.d_k++)
    {
      ContModelSIL_B.D17 = ContModelSIL_B.ginv[((ContModelSIL_B.d_k << 3) +
        ContModelSIL_B.jj) + 8];
      if (ContModelSIL_B.D17 != 0.0) {
        ContModelSIL_B.kAcol = (ContModelSIL_B.jA - ContModelSIL_B.c_j) + 6;
        for (ContModelSIL_B.ijA = ContModelSIL_B.jA; ContModelSIL_B.ijA <=
             ContModelSIL_B.kAcol; ContModelSIL_B.ijA++) {
          ContModelSIL_B.ginv[ContModelSIL_B.ijA - 1] += ContModelSIL_B.ginv
            [((ContModelSIL_B.jj + ContModelSIL_B.ijA) - ContModelSIL_B.jA) + 1]
            * -ContModelSIL_B.D17;
        }
      }

      ContModelSIL_B.jA += 8;
    }
  }

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.p[ContModelSIL_B.c_j] = static_cast<int8_T>
      (ContModelSIL_B.c_j + 1);
  }

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 7; ContModelSIL_B.c_j++) {
    ipiv = ContModelSIL_B.ipiv_k[ContModelSIL_B.c_j];
    if (ipiv > ContModelSIL_B.c_j + 1) {
      ContModelSIL_B.jj = ContModelSIL_B.p[ipiv - 1];
      ContModelSIL_B.p[ipiv - 1] = ContModelSIL_B.p[ContModelSIL_B.c_j];
      ContModelSIL_B.p[ContModelSIL_B.c_j] = static_cast<int8_T>
        (ContModelSIL_B.jj);
    }
  }

  for (ContModelSIL_B.jA = 0; ContModelSIL_B.jA < 8; ContModelSIL_B.jA++) {
    ContModelSIL_B.jj = (ContModelSIL_B.p[ContModelSIL_B.jA] - 1) << 3;
    ContModelSIL_B.BMinv[ContModelSIL_B.jA + ContModelSIL_B.jj] = 1.0;
    for (ContModelSIL_B.d_k = ContModelSIL_B.jA + 1; ContModelSIL_B.d_k < 9;
         ContModelSIL_B.d_k++) {
      ContModelSIL_B.c_j = (ContModelSIL_B.jj + ContModelSIL_B.d_k) - 1;
      if (ContModelSIL_B.BMinv[ContModelSIL_B.c_j] != 0.0) {
        for (i = ContModelSIL_B.d_k + 1; i < 9; i++) {
          ContModelSIL_B.kAcol = (ContModelSIL_B.jj + i) - 1;
          ContModelSIL_B.BMinv[ContModelSIL_B.kAcol] -= ContModelSIL_B.ginv
            [(((ContModelSIL_B.d_k - 1) << 3) + i) - 1] *
            ContModelSIL_B.BMinv[ContModelSIL_B.c_j];
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    ContModelSIL_B.jA = i << 3;
    for (ContModelSIL_B.d_k = 7; ContModelSIL_B.d_k >= 0; ContModelSIL_B.d_k--)
    {
      ContModelSIL_B.kAcol = ContModelSIL_B.d_k << 3;
      ContModelSIL_B.c_j = ContModelSIL_B.d_k + ContModelSIL_B.jA;
      ContModelSIL_B.D17 = ContModelSIL_B.BMinv[ContModelSIL_B.c_j];
      if (ContModelSIL_B.D17 != 0.0) {
        ContModelSIL_B.BMinv[ContModelSIL_B.c_j] = ContModelSIL_B.D17 /
          ContModelSIL_B.ginv[ContModelSIL_B.d_k + ContModelSIL_B.kAcol];
        for (ContModelSIL_B.ijA = 0; ContModelSIL_B.ijA < ContModelSIL_B.d_k;
             ContModelSIL_B.ijA++) {
          ContModelSIL_B.jj = ContModelSIL_B.ijA + ContModelSIL_B.jA;
          ContModelSIL_B.BMinv[ContModelSIL_B.jj] -=
            ContModelSIL_B.ginv[ContModelSIL_B.ijA + ContModelSIL_B.kAcol] *
            ContModelSIL_B.BMinv[ContModelSIL_B.c_j];
        }
      }
    }
  }

  // End of MATLAB Function: '<S11>/GetBInvMatrix'

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Delay: '<S8>/Delay5'

  ContModelSIL_B.smax = sin(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelSIL_B.D14_tmp = cos(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelSIL_B.s = sin(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelSIL_B.D14_tmp_tmp = ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]
    + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelSIL_B.D14_tmp_c = sin(ContModelSIL_B.D14_tmp_tmp);
  ContModelSIL_B.D14_tmp_f = cos(ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelSIL_B.D14_tmp_g = cos(ContModelSIL_B.D14_tmp_tmp);
  ContModelSIL_B.D14_tmp_m = 0.01400542 * ContModelSIL_B.D14_tmp +
    0.040588879999999994;
  ContModelSIL_B.D14_tmp_cz = 0.01400542 * ContModelSIL_B.D14_tmp_g;
  ContModelSIL_B.D14_tmp_tmp_m = 0.040588879999999994 * ContModelSIL_B.smax;
  ContModelSIL_B.D14_tmp_tmp_c = 0.01400542 * ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.D14_tmp_md = ContModelSIL_B.D14_tmp_tmp_m +
    ContModelSIL_B.D14_tmp_tmp_c;
  ContModelSIL_B.D14_tmp_m3 = ContModelSIL_B.D14_tmp_md * ContModelSIL_B.u;
  ContModelSIL_B.D14_tmp_p = ContModelSIL_B.D14_tmp_m *
    ContModelSIL_B.DigitalClock;
  ContModelSIL_B.D14_tmp_ms = 0.01400542 * ContModelSIL_B.u;
  ContModelSIL_B.D14_tmp_o = 0.01400542 * ContModelSIL_B.DigitalClock *
    ContModelSIL_B.s * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D14_tmp_l = (-ContModelSIL_B.D14_tmp_m * ContModelSIL_B.u +
    ContModelSIL_B.D14_tmp_o) * ContModelSIL_B.x_tmp;
  ContModelSIL_B.D14 = (((ContModelSIL_B.D14_tmp_ms * ContModelSIL_B.smax *
    ContModelSIL_B.s + -0.023689199999999997 * ContModelSIL_B.u) +
    ContModelSIL_B.D14_tmp_p * ContModelSIL_B.smax * ContModelSIL_B.x_tmp_b) *
                        ContModelSIL_B.x_tmp + ((ContModelSIL_B.D14_tmp_cz +
    0.023689199999999997) * ContModelSIL_B.DigitalClock * ContModelSIL_B.x_tmp_b
    + ContModelSIL_B.D14_tmp_m3) * ContModelSIL_B.Observer_alpha) +
    (0.040588879999999994 * ContModelSIL_B.DigitalClock *
     ContModelSIL_B.Observer_alpha * ContModelSIL_B.x_tmp_b +
     ContModelSIL_B.D14_tmp_l) * ContModelSIL_B.D14_tmp_f;
  ContModelSIL_B.D15_tmp_tmp = ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelSIL_B.D15_tmp = cos(ContModelSIL_B.D15_tmp_tmp);
  ContModelSIL_B.D15_tmp_tmp_a = ContModelSIL_B.D15_tmp_tmp +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelSIL_B.D15_tmp_g = cos(ContModelSIL_B.D15_tmp_tmp_a);
  ContModelSIL_B.D15_tmp_tmp_i = 0.040588879999999994 * ContModelSIL_B.D15_tmp;
  ContModelSIL_B.D15_tmp_tmp_o = 0.01400542 * ContModelSIL_B.D15_tmp_g;
  ContModelSIL_B.D15_tmp_p = (0.023689199999999997 * ContModelSIL_B.x_tmp +
    ContModelSIL_B.D15_tmp_tmp_i) + ContModelSIL_B.D15_tmp_tmp_o;
  ContModelSIL_B.D15 = ContModelSIL_B.D15_tmp_p * -ContModelSIL_B.DigitalClock *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D16_tmp_tmp = 0.040588879999999994 * ContModelSIL_B.D14_tmp_f;
  ContModelSIL_B.D16_tmp = (ContModelSIL_B.D16_tmp_tmp + 0.023689199999999997) +
    ContModelSIL_B.D14_tmp_cz;
  ContModelSIL_B.D16_tmp_p = ContModelSIL_B.D16_tmp *
    ContModelSIL_B.DigitalClock;
  ContModelSIL_B.D16_tmp_pt = ContModelSIL_B.D16_tmp * ContModelSIL_B.u;
  ContModelSIL_B.D16_tmp_f = ContModelSIL_B.D16_tmp_pt * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D16_tmp_i = ContModelSIL_B.D14_tmp_m3 * ContModelSIL_B.x_tmp_b
    + ContModelSIL_B.D16_tmp_p;
  ContModelSIL_B.D16 = (ContModelSIL_B.D14_tmp_md * -ContModelSIL_B.DigitalClock
                        + ContModelSIL_B.D16_tmp_f) * ContModelSIL_B.x_tmp +
    ContModelSIL_B.D16_tmp_i * -ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.D17_tmp = 0.09794 * ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.D17_tmp_c = 0.09794 * ContModelSIL_B.D14_tmp_g;
  ContModelSIL_B.D17_tmp_ct = 0.17 * ContModelSIL_B.D14_tmp_f;
  ContModelSIL_B.D17_tmp_p = 0.17 * ContModelSIL_B.smax + ContModelSIL_B.D17_tmp;
  ContModelSIL_B.D17_tmp_a = ContModelSIL_B.D17_tmp_p * 0.143;
  ContModelSIL_B.D17_tmp_n = ContModelSIL_B.D17_tmp_ct +
    ContModelSIL_B.D17_tmp_c;
  ContModelSIL_B.D17_tmp_tmp = ContModelSIL_B.u * ContModelSIL_B.smax;
  ContModelSIL_B.D17_tmp_tmp_c = ContModelSIL_B.DigitalClock *
    ContModelSIL_B.D14_tmp_f;
  ContModelSIL_B.D17_tmp_o = ContModelSIL_B.D17_tmp_tmp_c *
    ContModelSIL_B.x_tmp_b + ContModelSIL_B.D17_tmp_tmp;
  ContModelSIL_B.D17_tmp_g = ContModelSIL_B.DigitalClock * ContModelSIL_B.smax *
    ContModelSIL_B.x_tmp_b + -ContModelSIL_B.D14_tmp_f * ContModelSIL_B.u;
  ContModelSIL_B.D17 = ((0.01627888 * ContModelSIL_B.Observer_alpha *
    ContModelSIL_B.D17_tmp_o + ContModelSIL_B.D17_tmp_a *
    ContModelSIL_B.rtb_ginv_tmp_j) + ContModelSIL_B.D17_tmp_n * 0.143 *
                        ContModelSIL_B.rtb_ginv_tmp_h) + 0.01627888 *
    ContModelSIL_B.x_tmp * ContModelSIL_B.D17_tmp_g;
  ContModelSIL_B.D18_tmp = ContModelSIL_B.rtb_ginv_tmp_j *
    ContModelSIL_B.D17_tmp + ContModelSIL_B.rtb_ginv_tmp_h *
    ContModelSIL_B.D17_tmp_c;
  ContModelSIL_B.D18 = ContModelSIL_B.D18_tmp * 0.143;
  ContModelSIL_B.rtb_ginv_tmp_n = 0.11464 * ContModelSIL_B.D14_tmp_f + 0.08312;
  ContModelSIL_B.D24_tmp = (ContModelSIL_B.D17_tmp_ct + 0.08312) +
    ContModelSIL_B.D17_tmp_c;
  ContModelSIL_B.D24_tmp_p = ContModelSIL_B.rtb_ginv_tmp_h *
    ContModelSIL_B.D17_tmp_p;
  ContModelSIL_B.D17_tmp_ct = ContModelSIL_B.x_tmp_p * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D24_tmp_c = 0.08312 * ContModelSIL_B.x_tmp;
  ContModelSIL_B.D24_tmp_f = (0.17 * ContModelSIL_B.D15_tmp +
    ContModelSIL_B.D24_tmp_c) + 0.09794 * ContModelSIL_B.D15_tmp_g;
  ContModelSIL_B.D24 = (((ContModelSIL_B.rtb_ginv_tmp_n * ContModelSIL_B.u *
    ContModelSIL_B.x_tmp_b + -0.11464 * ContModelSIL_B.DigitalClock *
    ContModelSIL_B.smax) * (0.142 * ContModelSIL_B.Observer_alpha) + 0.143 *
    ContModelSIL_B.DigitalClock * ContModelSIL_B.D24_tmp_f *
    ContModelSIL_B.D17_tmp_ct) + (0.11464 * ContModelSIL_B.u *
    ContModelSIL_B.smax * ContModelSIL_B.x_tmp_b + ContModelSIL_B.rtb_ginv_tmp_n
    * ContModelSIL_B.DigitalClock) * (0.142 * ContModelSIL_B.x_tmp)) +
    (ContModelSIL_B.D24_tmp * ContModelSIL_B.rtb_ginv_tmp_j -
     ContModelSIL_B.D24_tmp_p) * (0.143 * ContModelSIL_B.x_tmp_b);
  ContModelSIL_B.D25 = -ContModelSIL_B.D15_tmp_p * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.u;
  ContModelSIL_B.D26 = ((ContModelSIL_B.rtb_ginv_tmp_n * -0.142 *
    ContModelSIL_B.rtb_ginv_tmp_j - ContModelSIL_B.D24_tmp * 0.143 *
    ContModelSIL_B.rtb_ginv_tmp_j) + 0.01627888 * ContModelSIL_B.smax *
                        ContModelSIL_B.rtb_ginv_tmp_h) +
    ContModelSIL_B.D17_tmp_a * ContModelSIL_B.rtb_ginv_tmp_h;
  ContModelSIL_B.D17_tmp_a = ContModelSIL_B.rtb_ginv_tmp_tmp -
    ContModelSIL_B.rtb_ginv_tmp_o;
  ContModelSIL_B.D27_tmp = ContModelSIL_B.rtb_ginv_tmp_i *
    ContModelSIL_B.D16_tmp_tmp;
  ContModelSIL_B.D27_tmp_k = ContModelSIL_B.rtb_ginv_tmp_i *
    ContModelSIL_B.D14_tmp_cz;
  ContModelSIL_B.D27 = (ContModelSIL_B.D17_tmp_a * -ContModelSIL_B.D14_tmp_md +
                        ContModelSIL_B.D27_tmp) + ContModelSIL_B.D27_tmp_k;
  ContModelSIL_B.D17_tmp = ContModelSIL_B.rtb_ginv_tmp_e *
    ContModelSIL_B.D17_tmp + ContModelSIL_B.rtb_ginv_tmp_i *
    ContModelSIL_B.D17_tmp_c;
  ContModelSIL_B.D28 = ContModelSIL_B.D17_tmp * 0.143;
  ContModelSIL_B.D17_tmp_c = sin(ContModelSIL_B.D15_tmp_tmp);
  ContModelSIL_B.D34_tmp = sin(ContModelSIL_B.D15_tmp_tmp_a);
  ContModelSIL_B.D34_tmp_a = 0.040588879999999994 * ContModelSIL_B.D17_tmp_c;
  ContModelSIL_B.D34_tmp_i = 0.01400542 * ContModelSIL_B.D34_tmp;
  ContModelSIL_B.D34_tmp_n = (0.023689199999999997 *
    ContModelSIL_B.Observer_alpha + ContModelSIL_B.D34_tmp_a) +
    ContModelSIL_B.D34_tmp_i;
  ContModelSIL_B.D34 = ContModelSIL_B.D34_tmp_n * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D35 = ContModelSIL_B.D15_tmp_p * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D37_tmp = ContModelSIL_B.D34_tmp_a + ContModelSIL_B.D34_tmp_i;
  ContModelSIL_B.D37 = ContModelSIL_B.D37_tmp * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D38 = 0.01400542 * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.D34_tmp;
  ContModelSIL_B.D45_tmp = 0.0 * ContModelSIL_B.D15_tmp_g;
  ContModelSIL_B.D45_tmp_f = 0.0 * ContModelSIL_B.D34_tmp;
  ContModelSIL_B.D45 = ((0.0 * ContModelSIL_B.D15_tmp + ContModelSIL_B.D45_tmp)
                        + 0.0 * ContModelSIL_B.D17_tmp_c) +
    ContModelSIL_B.D45_tmp_f;
  ContModelSIL_B.D46_tmp_tmp_ei = ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE
    [6] - ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp = sin(ContModelSIL_B.D46_tmp_tmp_ei);
  ContModelSIL_B.D46_tmp_tmp_e = ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]
    + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelSIL_B.D46_tmp_m = sin(ContModelSIL_B.D46_tmp_tmp_e);
  ContModelSIL_B.D46_tmp_tmp = ContModelSIL_B.D15_tmp_tmp -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp_n = cos(ContModelSIL_B.D46_tmp_tmp);
  ContModelSIL_B.D46_tmp_tmp_l = ContModelSIL_B.D15_tmp_tmp_a -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp_p = cos(ContModelSIL_B.D46_tmp_tmp_l);
  ContModelSIL_B.D46_tmp_tmp_o = ContModelSIL_B.D15_tmp_tmp +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp_l = cos(ContModelSIL_B.D46_tmp_tmp_o);
  ContModelSIL_B.D46_tmp_tmp_o2 = ContModelSIL_B.D15_tmp_tmp_a +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp_j = cos(ContModelSIL_B.D46_tmp_tmp_o2);
  ContModelSIL_B.D46_tmp_d = sin(ContModelSIL_B.D46_tmp_tmp);
  ContModelSIL_B.D46_tmp_dh = sin(ContModelSIL_B.D46_tmp_tmp_l);
  ContModelSIL_B.D46_tmp_o = sin(ContModelSIL_B.D46_tmp_tmp_o);
  ContModelSIL_B.D46_tmp_b = sin(ContModelSIL_B.D46_tmp_tmp_o2);
  ContModelSIL_B.D46_tmp_tmp_c = ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7]
    - ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp_h = sin(ContModelSIL_B.D46_tmp_tmp_c);
  ContModelSIL_B.D46_tmp_tmp_a = ContModelSIL_B.D14_tmp_tmp -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp_bn = sin(ContModelSIL_B.D46_tmp_tmp_a);
  ContModelSIL_B.D46_tmp_tmp_d = ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]
    + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelSIL_B.D46_tmp_da = sin(ContModelSIL_B.D46_tmp_tmp_d);
  ContModelSIL_B.D46_tmp_tmp_af = ContModelSIL_B.D14_tmp_tmp +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp_e = sin(ContModelSIL_B.D46_tmp_tmp_af);
  ContModelSIL_B.D46_tmp_o3 = -0.0 * ContModelSIL_B.D46_tmp_n;
  ContModelSIL_B.D46_tmp_lm = 0.0 * ContModelSIL_B.D46_tmp_l;
  ContModelSIL_B.D46_tmp_mv = 0.0 * ContModelSIL_B.D46_tmp_j;
  ContModelSIL_B.D46_tmp_mj = 0.0 * ContModelSIL_B.D46_tmp_d;
  ContModelSIL_B.D46_tmp_c = 0.0 * ContModelSIL_B.D46_tmp_dh;
  ContModelSIL_B.D46_tmp_tmp_f = 0.0 * ContModelSIL_B.D46_tmp_p;
  ContModelSIL_B.D46_tmp_e1 = ((ContModelSIL_B.D46_tmp_o3 -
    ContModelSIL_B.D46_tmp_tmp_f) - ContModelSIL_B.D46_tmp_lm) -
    ContModelSIL_B.D46_tmp_mv;
  ContModelSIL_B.D46_tmp_o4 = 0.004761842800000001 * ContModelSIL_B.D46_tmp_h;
  ContModelSIL_B.D46_tmp_hh = -0.00093002 * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D46_tmp_l5 = -0.0006068 * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D46_tmp_h2 = -0.0037324216063999997 * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D46_tmp_me = -0.0027433816695999996 * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D46_tmp_mc = -0.008265400000000001 * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D46_tmp_h3 = 0.0 * ContModelSIL_B.D46_tmp_o;
  ContModelSIL_B.D46_tmp_cs = -0.004761842800000001 * ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.D46_tmp_k = 0.0 * ContModelSIL_B.D46_tmp_b;
  ContModelSIL_B.D46 = ((((((((((((((((((((0.0027062010112 *
    ContModelSIL_B.D46_tmp + ContModelSIL_B.D46_tmp_e1) + 0.0040412944 *
    ContModelSIL_B.D46_tmp) + ContModelSIL_B.D46_tmp_mj) +
    ContModelSIL_B.D46_tmp_o4) + 0.0023282610207999996 *
    ContModelSIL_B.D46_tmp_bn) + ContModelSIL_B.D46_tmp_c) +
    ContModelSIL_B.D46_tmp_hh) + ContModelSIL_B.D46_tmp_l5) + -0.0787496 *
    ContModelSIL_B.x_tmp_b) + ContModelSIL_B.D46_tmp_h2) +
    -0.0019621373695999996 * ContModelSIL_B.x_tmp_b) + ContModelSIL_B.D46_tmp_me)
    + -0.0019759552383999996 * ContModelSIL_B.x_tmp_b) +
    ContModelSIL_B.D46_tmp_mc) + -0.0027062010112 * ContModelSIL_B.D46_tmp_m) +
    -0.0040412944 * ContModelSIL_B.D46_tmp_m) + ContModelSIL_B.D46_tmp_h3) +
    ContModelSIL_B.D46_tmp_cs) + -0.0023282610207999996 *
    ContModelSIL_B.D46_tmp_e) + ContModelSIL_B.D46_tmp_k) * 0.5;
  ContModelSIL_B.D47_tmp = 0.0011641305103999998 * ContModelSIL_B.D14_tmp_g;
  ContModelSIL_B.D47_tmp_a = 0.004761842800000001 * ContModelSIL_B.D14_tmp;
  ContModelSIL_B.D47_tmp_d = 0.0033737477055999993 * ContModelSIL_B.D14_tmp_f +
    0.008139011638;
  ContModelSIL_B.D47 = (ContModelSIL_B.D47_tmp_d + ContModelSIL_B.D47_tmp_a) +
    ContModelSIL_B.D47_tmp;
  ContModelSIL_B.D48_tmp = 0.0023809214000000004 * ContModelSIL_B.D14_tmp +
    0.0016750908347999997;
  ContModelSIL_B.D48 = ContModelSIL_B.D48_tmp + ContModelSIL_B.D47_tmp;
  ContModelSIL_B.D56_tmp_tmp = 2.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3];
  ContModelSIL_B.D56_tmp_tmp_h = ContModelSIL_B.D56_tmp_tmp -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp = sin(ContModelSIL_B.D56_tmp_tmp_h);
  ContModelSIL_B.D56_tmp_tmp_f = ContModelSIL_B.D56_tmp_tmp +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelSIL_B.D56_tmp_tmp_a = ContModelSIL_B.D56_tmp_tmp_f -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_g = sin(ContModelSIL_B.D56_tmp_tmp_a);
  ContModelSIL_B.D56_tmp_tmp_tmp = 2.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelSIL_B.D56_tmp_tmp_i = ContModelSIL_B.D56_tmp_tmp +
    ContModelSIL_B.D56_tmp_tmp_tmp;
  ContModelSIL_B.D56_tmp_tmp_ff = ContModelSIL_B.D56_tmp_tmp_i -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_l = sin(ContModelSIL_B.D56_tmp_tmp_ff);
  ContModelSIL_B.D56_tmp_tmp_iz = 2.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7] +
    ContModelSIL_B.D56_tmp_tmp_i;
  ContModelSIL_B.D56_tmp_tmp_g = ContModelSIL_B.D56_tmp_tmp_iz -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_d = sin(ContModelSIL_B.D56_tmp_tmp_g);
  ContModelSIL_B.D56_tmp_tmp_g2 = ContModelSIL_B.D56_tmp_tmp +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_lx = sin(ContModelSIL_B.D56_tmp_tmp_g2);
  ContModelSIL_B.D56_tmp_tmp_fi = ContModelSIL_B.D56_tmp_tmp_f +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_b = sin(ContModelSIL_B.D56_tmp_tmp_fi);
  ContModelSIL_B.D56_tmp_tmp_c = ContModelSIL_B.D56_tmp_tmp_i +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_n = sin(ContModelSIL_B.D56_tmp_tmp_c);
  ContModelSIL_B.D56_tmp_tmp_iz +=
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_ln = sin(ContModelSIL_B.D56_tmp_tmp_iz);
  ContModelSIL_B.D56_tmp_bj = cos(ContModelSIL_B.D56_tmp_tmp_ff);
  ContModelSIL_B.D56_tmp_j = cos(ContModelSIL_B.D56_tmp_tmp_g);
  ContModelSIL_B.D56_tmp_f = cos(ContModelSIL_B.D56_tmp_tmp_c);
  ContModelSIL_B.D56_tmp_a = cos(ContModelSIL_B.D56_tmp_tmp_iz);
  ContModelSIL_B.D56_tmp_tmp_ff = ContModelSIL_B.D56_tmp_tmp_f +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelSIL_B.D56_tmp_tmp_iz = ContModelSIL_B.D56_tmp_tmp_ff -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_ju = sin(ContModelSIL_B.D56_tmp_tmp_iz);
  ContModelSIL_B.D56_tmp_tmp_i += ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE
    [7];
  ContModelSIL_B.D56_tmp_tmp_g = ContModelSIL_B.D56_tmp_tmp_i -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_jz = sin(ContModelSIL_B.D56_tmp_tmp_g);
  ContModelSIL_B.D56_tmp_tmp_c = ContModelSIL_B.D56_tmp_tmp_ff +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_o = sin(ContModelSIL_B.D56_tmp_tmp_c);
  ContModelSIL_B.D56_tmp_tmp_i += ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE
    [4];
  ContModelSIL_B.D56_tmp_ny = sin(ContModelSIL_B.D56_tmp_tmp_i);
  ContModelSIL_B.D56_tmp_p = -0.0 * ContModelSIL_B.D46_tmp_p;
  ContModelSIL_B.D56_tmp_h = -0.0 * ContModelSIL_B.D46_tmp_o;
  ContModelSIL_B.D56_tmp_m = -0.0 * ContModelSIL_B.D46_tmp_b;
  ContModelSIL_B.D56_tmp_tmp_cj = 0.04043155 * ContModelSIL_B.D56_tmp;
  ContModelSIL_B.D56_tmp_tmp_m = 0.06214814 * ContModelSIL_B.D56_tmp;
  ContModelSIL_B.D56_tmp_tmp_j = 0.0009810686847999998 * ContModelSIL_B.D56_tmp;
  ContModelSIL_B.D56_tmp_tmp_k = 0.0009879776191999998 * ContModelSIL_B.D56_tmp;
  ContModelSIL_B.D56_tmp_tmp_mx = 5.484E-5 * ContModelSIL_B.D56_tmp_l;
  ContModelSIL_B.D56_tmp_tmp_p = 0.00050874 * ContModelSIL_B.D56_tmp_l;
  ContModelSIL_B.D56_tmp_tmp_d = 0.0018662108031999999 *
    ContModelSIL_B.D56_tmp_l;
  ContModelSIL_B.D56_tmp_tmp_g4 = 0.0041327000000000004 *
    ContModelSIL_B.D56_tmp_l;
  ContModelSIL_B.D56_tmp_tmp_c3 = 8.085E-5 * ContModelSIL_B.D56_tmp_d;
  ContModelSIL_B.D56_tmp_tmp_cx = 0.00034964 * ContModelSIL_B.D56_tmp_d;
  ContModelSIL_B.D56_tmp_tmp_if = 0.0013716908347999998 *
    ContModelSIL_B.D56_tmp_d;
  ContModelSIL_B.D56_tmp_tmp_dx = 0.04043155 * ContModelSIL_B.D56_tmp_lx;
  ContModelSIL_B.D56_tmp_tmp_g4k = 0.06214814 * ContModelSIL_B.D56_tmp_lx;
  ContModelSIL_B.D56_tmp_tmp_l = 0.0009810686847999998 *
    ContModelSIL_B.D56_tmp_lx;
  ContModelSIL_B.D56_tmp_tmp_f1 = 5.484E-5 * ContModelSIL_B.D56_tmp_n;
  ContModelSIL_B.D56_tmp_tmp_db = 0.00050874 * ContModelSIL_B.D56_tmp_n;
  ContModelSIL_B.D56_tmp_tmp_jr = 0.0018662108031999999 *
    ContModelSIL_B.D56_tmp_n;
  ContModelSIL_B.D56_tmp_tmp_i3 = 0.0041327000000000004 *
    ContModelSIL_B.D56_tmp_n;
  ContModelSIL_B.D56_tmp = (((((((((((((((((((((((((((((((((((((-0.0 *
    ContModelSIL_B.D56_tmp_bj + ContModelSIL_B.D46_tmp_o3) +
    ContModelSIL_B.D56_tmp_p) + -0.0 * ContModelSIL_B.D56_tmp_j) +
    ContModelSIL_B.D46_tmp_lm) + -0.0 * ContModelSIL_B.D56_tmp_f) +
    ContModelSIL_B.D46_tmp_mv) + -0.0 * ContModelSIL_B.D56_tmp_a) +
    ContModelSIL_B.D56_tmp_tmp_cj) - ContModelSIL_B.D56_tmp_tmp_m) +
    ContModelSIL_B.D56_tmp_tmp_j) + ContModelSIL_B.D56_tmp_tmp_k) +
    ContModelSIL_B.D46_tmp_mj) + 0.0027062010112 * ContModelSIL_B.D56_tmp_g) +
    0.0040412944 * ContModelSIL_B.D56_tmp_g) - ContModelSIL_B.D56_tmp_tmp_mx) +
    ContModelSIL_B.D56_tmp_tmp_p) + ContModelSIL_B.D56_tmp_tmp_d) +
    ContModelSIL_B.D56_tmp_tmp_g4) + ContModelSIL_B.D46_tmp_c) +
    0.0023282610207999996 * ContModelSIL_B.D56_tmp_ju) + 0.004761842800000001 *
    ContModelSIL_B.D56_tmp_jz) - ContModelSIL_B.D56_tmp_tmp_c3) +
    ContModelSIL_B.D56_tmp_tmp_cx) + ContModelSIL_B.D56_tmp_tmp_if) +
    ContModelSIL_B.D56_tmp_tmp_dx) - ContModelSIL_B.D56_tmp_tmp_g4k) +
    ContModelSIL_B.D56_tmp_tmp_l) + 0.0009879776191999998 *
    ContModelSIL_B.D56_tmp_lx) + ContModelSIL_B.D56_tmp_h) + 0.0027062010112 *
    ContModelSIL_B.D56_tmp_b) + 0.0040412944 * ContModelSIL_B.D56_tmp_b) -
    ContModelSIL_B.D56_tmp_tmp_f1) + ContModelSIL_B.D56_tmp_tmp_db) +
    ContModelSIL_B.D56_tmp_tmp_jr) + ContModelSIL_B.D56_tmp_tmp_i3) +
    ContModelSIL_B.D56_tmp_m) + 0.0023282610207999996 * ContModelSIL_B.D56_tmp_o)
    + 0.004761842800000001 * ContModelSIL_B.D56_tmp_ny;
  ContModelSIL_B.D46_tmp_o3 = 0.00034964 * ContModelSIL_B.D56_tmp_ln;
  ContModelSIL_B.D56_tmp_ad = 0.0013716908347999998 * ContModelSIL_B.D56_tmp_ln;
  ContModelSIL_B.D56 = (((-8.085E-5 * ContModelSIL_B.D56_tmp_ln +
    ContModelSIL_B.D56_tmp) + ContModelSIL_B.D46_tmp_o3) +
                        ContModelSIL_B.D56_tmp_ad) * 0.25;
  ContModelSIL_B.D58 = ContModelSIL_B.D45_tmp + ContModelSIL_B.D45_tmp_f;
  ContModelSIL_B.D45_tmp_f = 0.11464 * ContModelSIL_B.smax;
  ContModelSIL_B.D45_tmp = ContModelSIL_B.rtb_ginv_tmp_j *
    -ContModelSIL_B.rtb_ginv_tmp_n + ContModelSIL_B.rtb_ginv_tmp_h *
    ContModelSIL_B.D45_tmp_f;
  ContModelSIL_B.D24_tmp_p += -ContModelSIL_B.D24_tmp *
    ContModelSIL_B.rtb_ginv_tmp_j;
  ContModelSIL_B.y_a = ContModelSIL_B.D17_tmp_a * ContModelSIL_B.rtb_ginv_tmp_n
    + ContModelSIL_B.rtb_ginv_tmp_i * ContModelSIL_B.D45_tmp_f;
  ContModelSIL_B.ab_a = ContModelSIL_B.D24_tmp * ContModelSIL_B.D17_tmp_a +
    ContModelSIL_B.rtb_ginv_tmp_i * ContModelSIL_B.D17_tmp_p;
  ContModelSIL_B.rtb_ginv_tmp_n = 0.0011641305103999998 *
    ContModelSIL_B.D46_tmp_bn;
  ContModelSIL_B.D24_tmp = 0.0011641305103999998 * ContModelSIL_B.D46_tmp_e;
  ContModelSIL_B.D67 = (((((((((((((((((0.0013531005056 * ContModelSIL_B.D46_tmp
    + ContModelSIL_B.D46_tmp_e1) + 0.0020206472 * ContModelSIL_B.D46_tmp) +
    ContModelSIL_B.D46_tmp_mj) + ContModelSIL_B.D46_tmp_o4) +
    ContModelSIL_B.rtb_ginv_tmp_n) + ContModelSIL_B.D46_tmp_c) +
    ContModelSIL_B.D46_tmp_hh) + ContModelSIL_B.D46_tmp_l5) +
    ContModelSIL_B.D46_tmp_h2) + ContModelSIL_B.D46_tmp_me) +
    ContModelSIL_B.D46_tmp_mc) - 0.0013531005056 * ContModelSIL_B.D46_tmp_m) -
    0.0020206472 * ContModelSIL_B.D46_tmp_m) + ContModelSIL_B.D46_tmp_h3) +
    ContModelSIL_B.D46_tmp_cs) - ContModelSIL_B.D24_tmp) +
                        ContModelSIL_B.D46_tmp_k) * 0.5;
  ContModelSIL_B.D68 = (((((((((ContModelSIL_B.D56_tmp_p -
    ContModelSIL_B.D46_tmp_mv) + 0.0023809214000000004 *
    ContModelSIL_B.D46_tmp_h) + ContModelSIL_B.rtb_ginv_tmp_n) +
    ContModelSIL_B.D46_tmp_c) + ContModelSIL_B.D46_tmp_l5) +
    ContModelSIL_B.D46_tmp_me) + -0.0023809214000000004 *
    ContModelSIL_B.D46_tmp_da) - ContModelSIL_B.D24_tmp) +
                        ContModelSIL_B.D46_tmp_k) * 0.5;
  ContModelSIL_B.rtb_ginv_tmp_o = cos(ContModelSIL_B.D56_tmp_tmp);
  ContModelSIL_B.rtb_ginv_tmp_tmp_p4 = ContModelSIL_B.D15_tmp_tmp * 2.0;
  ContModelSIL_B.rtb_ginv_tmp_n = cos(ContModelSIL_B.rtb_ginv_tmp_tmp_p4);
  ContModelSIL_B.D24_tmp = cos(ContModelSIL_B.D56_tmp_tmp_f);
  ContModelSIL_B.D46_tmp_h = ContModelSIL_B.D15_tmp_tmp_a * 2.0;
  ContModelSIL_B.D46_tmp_da = cos(ContModelSIL_B.D46_tmp_h);
  ContModelSIL_B.D46_tmp_l5 = sin(ContModelSIL_B.D56_tmp_tmp_tmp);
  ContModelSIL_B.rtb_ginv_tmp_tmp_p = ContModelSIL_B.D14_tmp_tmp * 2.0;
  ContModelSIL_B.D46_tmp_me = cos(ContModelSIL_B.rtb_ginv_tmp_tmp_p);
  ContModelSIL_B.D56_tmp_p = sin(ContModelSIL_B.rtb_ginv_tmp_tmp_p);
  ContModelSIL_B.rtb_ginv_tmp_tmp_p = 2.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D46_tmp = sin(ContModelSIL_B.rtb_ginv_tmp_tmp_p);
  ContModelSIL_B.D46_tmp_m = sin(ContModelSIL_B.rtb_ginv_tmp_tmp_p4);
  ContModelSIL_B.D46_tmp_e1 = sin(ContModelSIL_B.D46_tmp_h);
  ContModelSIL_B.rtb_ginv_tmp = cos(ContModelSIL_B.D56_tmp_tmp_ff);
  ContModelSIL_B.rtb_ginv_tmp_tmp_p4 +=
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelSIL_B.D46_tmp_o4 = cos(ContModelSIL_B.rtb_ginv_tmp_tmp_p4);
  ContModelSIL_B.D56_tmp_tmp_tmp = cos(ContModelSIL_B.D56_tmp_tmp_tmp);
  ContModelSIL_B.ginv[0] = 2.1037999999999997;
  ContModelSIL_B.ginv[8] = 0.0;
  ContModelSIL_B.ginv[16] = 0.0;
  ContModelSIL_B.ginv[24] = ContModelSIL_B.D14;
  ContModelSIL_B.ginv[32] = ContModelSIL_B.D15;
  ContModelSIL_B.ginv[40] = ContModelSIL_B.D16;
  ContModelSIL_B.ginv[48] = ContModelSIL_B.D17;
  ContModelSIL_B.ginv[56] = ContModelSIL_B.D18;
  ContModelSIL_B.ginv[1] = 0.0;
  ContModelSIL_B.ginv[9] = 2.1037999999999997;
  ContModelSIL_B.ginv[17] = 0.0;
  ContModelSIL_B.ginv[25] = ContModelSIL_B.D24;
  ContModelSIL_B.ginv[33] = ContModelSIL_B.D25;
  ContModelSIL_B.ginv[41] = ContModelSIL_B.D26;
  ContModelSIL_B.ginv[49] = ContModelSIL_B.D27;
  ContModelSIL_B.ginv[57] = ContModelSIL_B.D28;
  ContModelSIL_B.ginv[2] = 0.0;
  ContModelSIL_B.ginv[10] = 0.0;
  ContModelSIL_B.ginv[18] = 2.1037999999999997;
  ContModelSIL_B.ginv[26] = ContModelSIL_B.D34;
  ContModelSIL_B.ginv[34] = ContModelSIL_B.D35;
  ContModelSIL_B.ginv[42] = 0.0;
  ContModelSIL_B.ginv[50] = ContModelSIL_B.D37;
  ContModelSIL_B.ginv[58] = ContModelSIL_B.D38;
  ContModelSIL_B.ginv[3] = ContModelSIL_B.D14;
  ContModelSIL_B.ginv[11] = ContModelSIL_B.D24;
  ContModelSIL_B.ginv[19] = ContModelSIL_B.D34;
  ContModelSIL_B.rtb_ginv_tmp_jd = 0.006747495411199999 *
    ContModelSIL_B.D14_tmp_f;
  ContModelSIL_B.rtb_ginv_tmp_ek = 0.0023282610207999996 *
    ContModelSIL_B.D14_tmp_g;
  ContModelSIL_B.ginv[27] = ((ContModelSIL_B.rtb_ginv_tmp_jd +
    0.049482857942000004) + ContModelSIL_B.D47_tmp_a) +
    ContModelSIL_B.rtb_ginv_tmp_ek;
  ContModelSIL_B.ginv[35] = ContModelSIL_B.D45;
  ContModelSIL_B.ginv[43] = ContModelSIL_B.D46;
  ContModelSIL_B.ginv[51] = ContModelSIL_B.D47;
  ContModelSIL_B.ginv[59] = ContModelSIL_B.D48;
  ContModelSIL_B.ginv[4] = ContModelSIL_B.D15;
  ContModelSIL_B.ginv[12] = ContModelSIL_B.D25;
  ContModelSIL_B.ginv[20] = ContModelSIL_B.D35;
  ContModelSIL_B.ginv[28] = ContModelSIL_B.D45;
  ContModelSIL_B.rtb_ginv_tmp_k = 0.00050874 * ContModelSIL_B.rtb_ginv_tmp_n;
  ContModelSIL_B.rtb_ginv_tmp_p = 0.0018662108031999999 *
    ContModelSIL_B.rtb_ginv_tmp_n;
  ContModelSIL_B.rtb_ginv_tmp_bp = 0.0041327000000000004 *
    ContModelSIL_B.rtb_ginv_tmp_n;
  ContModelSIL_B.D15 = 8.085E-5 * ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.D25 = 0.00034964 * ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.D14 = 0.0013716908347999998 * ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.ginv[36] = ((((((((((((((((((((0.04043155 *
    ContModelSIL_B.rtb_ginv_tmp_o + 0.11291340794199999) - 0.06214814 *
    ContModelSIL_B.rtb_ginv_tmp_o) + 0.0009810686847999998 *
    ContModelSIL_B.rtb_ginv_tmp_o) + 0.0009879776191999998 *
    ContModelSIL_B.rtb_ginv_tmp_o) + ContModelSIL_B.rtb_ginv_tmp_jd) + -5.484E-5
    * ContModelSIL_B.rtb_ginv_tmp_n) + ContModelSIL_B.rtb_ginv_tmp_k) +
    ContModelSIL_B.rtb_ginv_tmp_p) + ContModelSIL_B.rtb_ginv_tmp_bp) +
    0.0027062010112 * ContModelSIL_B.D24_tmp) + 0.0040412944 *
    ContModelSIL_B.D24_tmp) + ContModelSIL_B.D47_tmp_a) +
    ContModelSIL_B.rtb_ginv_tmp_ek) - ContModelSIL_B.D15) + ContModelSIL_B.D25)
    + ContModelSIL_B.D14) + 0.0023282610207999996 * ContModelSIL_B.rtb_ginv_tmp)
    + 0.004761842800000001 * ContModelSIL_B.D46_tmp_o4) + 0.0 *
    ContModelSIL_B.D46_tmp_m) + 0.0 * ContModelSIL_B.D46_tmp_e1) * 0.5;
  ContModelSIL_B.ginv[44] = ContModelSIL_B.D56;
  ContModelSIL_B.ginv[52] = ContModelSIL_B.D45;
  ContModelSIL_B.ginv[60] = ContModelSIL_B.D58;
  ContModelSIL_B.ginv[5] = ContModelSIL_B.D16;
  ContModelSIL_B.ginv[13] = ContModelSIL_B.D26;
  ContModelSIL_B.ginv[21] = 0.0;
  ContModelSIL_B.ginv[29] = ContModelSIL_B.D46;
  ContModelSIL_B.ginv[37] = ContModelSIL_B.D56;
  ContModelSIL_B.D16 = ContModelSIL_B.x_tmp * ContModelSIL_B.x_tmp;
  ContModelSIL_B.D26 = ContModelSIL_B.D14_tmp_f * ContModelSIL_B.D14_tmp_f;
  ContModelSIL_B.D46 = ContModelSIL_B.smax * ContModelSIL_B.smax;
  ContModelSIL_B.D56 = ContModelSIL_B.Observer_alpha *
    ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.D46_tmp_h = 2.0 * ContModelSIL_B.x_tmp;
  ContModelSIL_B.rtb_ginv_tmp_ol = ContModelSIL_B.D46_tmp_h *
    ContModelSIL_B.D17_tmp_ct * ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.rtb_ginv_tmp_b = ContModelSIL_B.x_tmp_b *
    ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D24 = 0.0 * ContModelSIL_B.D14_tmp_f;
  ContModelSIL_B.D35 = 0.0 * ContModelSIL_B.smax;
  ContModelSIL_B.D34 = 0.0 * ContModelSIL_B.D14_tmp_g;
  ContModelSIL_B.D46_tmp_hh = 0.0 * ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.D46_tmp_h2 = ContModelSIL_B.D24 - ContModelSIL_B.D35;
  ContModelSIL_B.D24 += ContModelSIL_B.D35;
  ContModelSIL_B.D35 = ContModelSIL_B.D34 - ContModelSIL_B.D46_tmp_hh;
  ContModelSIL_B.D34 += ContModelSIL_B.D46_tmp_hh;
  ContModelSIL_B.D46_tmp_hh = ContModelSIL_B.D26 * 5.484E-5;
  ContModelSIL_B.D46_tmp_mc = ContModelSIL_B.D46 * 0.00050874;
  ContModelSIL_B.D26 = (ContModelSIL_B.D26 * 0.00050874 + ContModelSIL_B.D46 *
                        5.484E-5) + 0.0 * ContModelSIL_B.D46_tmp_l5;
  ContModelSIL_B.D46 = (-0.00026879000000000003 * ContModelSIL_B.D46_tmp_me +
                        0.00043049) + -0.0 * ContModelSIL_B.D56_tmp_p;
  ContModelSIL_B.D46_tmp_cs = 0.00026879000000000003 * ContModelSIL_B.D46_tmp_me;
  ContModelSIL_B.D46_tmp_e = 0.0 * ContModelSIL_B.D56_tmp_p;
  ContModelSIL_B.D46_tmp_bn = (ContModelSIL_B.D46_tmp_cs + 0.00043049) +
    ContModelSIL_B.D46_tmp_e;
  ContModelSIL_B.D45_tmp_f = ContModelSIL_B.D16 * 0.06214814;
  ContModelSIL_B.rtb_ginv_tmp_pm = ContModelSIL_B.D17_tmp_ct *
    ContModelSIL_B.D56;
  ContModelSIL_B.rtb_ginv_tmp_p2 = ContModelSIL_B.D16 *
    ContModelSIL_B.D17_tmp_ct;
  ContModelSIL_B.rtb_ginv_tmp_nj = -0.0 * ContModelSIL_B.D46_tmp_me;
  ContModelSIL_B.rtb_ginv_tmp_kt = -0.0 * ContModelSIL_B.D46_tmp_l5;
  ContModelSIL_B.ginv[45] = (((((((((((((((((0.00045390000000000003 *
    ContModelSIL_B.D14_tmp_f * ContModelSIL_B.smax + -0.0 *
    ContModelSIL_B.D56_tmp_tmp_tmp) * ContModelSIL_B.rtb_ginv_tmp_ol +
    (ContModelSIL_B.D17_tmp_ct * 0.04043155 * ContModelSIL_B.D56 +
     ContModelSIL_B.D45_tmp_f * ContModelSIL_B.D17_tmp_ct)) +
    ((ContModelSIL_B.D46_tmp_hh + ContModelSIL_B.D46_tmp_mc) +
     ContModelSIL_B.rtb_ginv_tmp_kt) * ContModelSIL_B.rtb_ginv_tmp_p2) +
    ContModelSIL_B.D26 * ContModelSIL_B.rtb_ginv_tmp_pm) + ContModelSIL_B.D16 *
    0.5 * ContModelSIL_B.D17_tmp_ct * ContModelSIL_B.D46) +
    ContModelSIL_B.D17_tmp_ct * 0.5 * ContModelSIL_B.D56 *
    ContModelSIL_B.D46_tmp_bn) + (0.00013439500000000002 *
    ContModelSIL_B.D56_tmp_p + ContModelSIL_B.rtb_ginv_tmp_nj) *
    ContModelSIL_B.rtb_ginv_tmp_ol) + ContModelSIL_B.rtb_ginv_tmp_b * 0.00046501)
    + ContModelSIL_B.rtb_ginv_tmp_b * 0.0003034) + ContModelSIL_B.rtb_ginv_tmp_b
    * 0.0393748) + ContModelSIL_B.D45_tmp * ContModelSIL_B.D45_tmp * 0.142) +
    ContModelSIL_B.D24_tmp_p * ContModelSIL_B.D24_tmp_p * 0.143) +
    ContModelSIL_B.y_a * ContModelSIL_B.y_a * 0.142) + ContModelSIL_B.ab_a *
    ContModelSIL_B.ab_a * 0.143) + ContModelSIL_B.D46_tmp_h2 *
    ContModelSIL_B.x_tmp * ContModelSIL_B.D46_tmp) - ContModelSIL_B.D24 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.D46_tmp) + ContModelSIL_B.D35
    * ContModelSIL_B.x_tmp * ContModelSIL_B.D46_tmp) - ContModelSIL_B.D34 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.D46_tmp;
  ContModelSIL_B.ginv[53] = ContModelSIL_B.D67;
  ContModelSIL_B.ginv[61] = ContModelSIL_B.D68;
  ContModelSIL_B.ginv[6] = ContModelSIL_B.D17;
  ContModelSIL_B.ginv[14] = ContModelSIL_B.D27;
  ContModelSIL_B.ginv[22] = ContModelSIL_B.D37;
  ContModelSIL_B.ginv[30] = ContModelSIL_B.D47;
  ContModelSIL_B.ginv[38] = ContModelSIL_B.D45;
  ContModelSIL_B.ginv[46] = ContModelSIL_B.D67;
  ContModelSIL_B.ginv[54] = ContModelSIL_B.D47_tmp_a + 0.008139011638;
  ContModelSIL_B.ginv[62] = ContModelSIL_B.D48_tmp;
  ContModelSIL_B.ginv[7] = ContModelSIL_B.D18;
  ContModelSIL_B.ginv[15] = ContModelSIL_B.D28;
  ContModelSIL_B.ginv[23] = ContModelSIL_B.D38;
  ContModelSIL_B.ginv[31] = ContModelSIL_B.D48;
  ContModelSIL_B.ginv[39] = ContModelSIL_B.D58;
  ContModelSIL_B.ginv[47] = ContModelSIL_B.D68;
  ContModelSIL_B.ginv[55] = ContModelSIL_B.D48_tmp;
  ContModelSIL_B.ginv[63] = 0.0016750908347999997;
  ContModelSIL_inv(ContModelSIL_B.ginv, ContModelSIL_DW.Delay5_DSTATE);
  ContModelSIL_B.D17 = sin(ContModelSIL_B.D56_tmp_tmp);
  ContModelSIL_B.D18 = sin(ContModelSIL_B.D56_tmp_tmp_f);
  ContModelSIL_B.D27 = cos(ContModelSIL_B.D56_tmp_tmp_a);
  ContModelSIL_B.D56_tmp_tmp_g2 = cos(ContModelSIL_B.D56_tmp_tmp_g2);
  ContModelSIL_B.D46_tmp_tmp_e = cos(ContModelSIL_B.D46_tmp_tmp_e);
  ContModelSIL_B.D56_tmp_tmp_fi = cos(ContModelSIL_B.D56_tmp_tmp_fi);
  ContModelSIL_B.D56_tmp_tmp_h = cos(ContModelSIL_B.D56_tmp_tmp_h);
  ContModelSIL_B.D46_tmp_tmp_ei = cos(ContModelSIL_B.D46_tmp_tmp_ei);
  ContModelSIL_B.D46_tmp_tmp_c = cos(ContModelSIL_B.D46_tmp_tmp_c);
  ContModelSIL_B.D46_tmp_tmp_a = cos(ContModelSIL_B.D46_tmp_tmp_a);
  ContModelSIL_B.D56_tmp_tmp_iz = cos(ContModelSIL_B.D56_tmp_tmp_iz);
  ContModelSIL_B.D56_tmp_tmp_g = cos(ContModelSIL_B.D56_tmp_tmp_g);
  ContModelSIL_B.D46_tmp_tmp_d = cos(ContModelSIL_B.D46_tmp_tmp_d);
  ContModelSIL_B.D46_tmp_tmp_af = cos(ContModelSIL_B.D46_tmp_tmp_af);
  ContModelSIL_B.D56_tmp_tmp_c = cos(ContModelSIL_B.D56_tmp_tmp_c);
  ContModelSIL_B.D56_tmp_tmp_i = cos(ContModelSIL_B.D56_tmp_tmp_i);
  ContModelSIL_B.D56_tmp_tmp_a = sin(ContModelSIL_B.D56_tmp_tmp_ff);
  ContModelSIL_B.D28 = sin(ContModelSIL_B.rtb_ginv_tmp_tmp_p4);
  ContModelSIL_B.D37 = -2.0 * ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelSIL_B.D56_tmp_tmp_f = sin(ContModelSIL_B.D56_tmp_tmp_f +
    ContModelSIL_B.D37);
  ContModelSIL_B.D46_tmp_tmp *= 2.0;
  ContModelSIL_B.D38 = sin(ContModelSIL_B.D46_tmp_tmp);
  ContModelSIL_B.D46_tmp_tmp_l *= 2.0;
  ContModelSIL_B.D47 = sin(ContModelSIL_B.D46_tmp_tmp_l);
  ContModelSIL_B.D48_tmp = sin((-ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  ContModelSIL_B.D56_tmp_tmp = (ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0;
  ContModelSIL_B.D58 = sin(ContModelSIL_B.D56_tmp_tmp);
  ContModelSIL_B.D46_tmp_tmp_o *= 2.0;
  ContModelSIL_B.y_a = sin(ContModelSIL_B.D46_tmp_tmp_o);
  ContModelSIL_B.D46_tmp_tmp_o2 *= 2.0;
  ContModelSIL_B.ab_a = sin(ContModelSIL_B.D46_tmp_tmp_o2);
  ContModelSIL_B.rtb_ginv_tmp_tmp_p4 = sin(ContModelSIL_B.D56_tmp_tmp +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelSIL_B.D67 = ContModelSIL_B.D15_tmp_tmp + ContModelSIL_B.D37;
  ContModelSIL_B.D68 = cos(ContModelSIL_B.D67);
  ContModelSIL_B.rtb_ginv_tmp_ol = ContModelSIL_B.D15_tmp_tmp_a +
    ContModelSIL_B.D37;
  ContModelSIL_B.d = cos(ContModelSIL_B.rtb_ginv_tmp_ol);
  ContModelSIL_B.d1 = cos(ContModelSIL_B.D46_tmp_tmp);
  ContModelSIL_B.D46_tmp_tmp_l = cos(ContModelSIL_B.D46_tmp_tmp_l);
  ContModelSIL_B.d2 = cos(ContModelSIL_B.D46_tmp_tmp_o);
  ContModelSIL_B.D46_tmp_tmp_o2 = cos(ContModelSIL_B.D46_tmp_tmp_o2);
  ContModelSIL_B.D15_tmp_tmp += ContModelSIL_B.rtb_ginv_tmp_tmp_p;
  ContModelSIL_B.d3 = cos(ContModelSIL_B.D15_tmp_tmp);
  ContModelSIL_B.D15_tmp_tmp_a += ContModelSIL_B.rtb_ginv_tmp_tmp_p;
  ContModelSIL_B.d4 = cos(ContModelSIL_B.D15_tmp_tmp_a);
  ContModelSIL_B.D46_tmp_tmp = sin(ContModelSIL_B.D46_tmp_tmp +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelSIL_B.d5 = sin(ContModelSIL_B.D37 +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelSIL_B.D67 = sin(ContModelSIL_B.D67);
  ContModelSIL_B.rtb_ginv_tmp_ol = sin(ContModelSIL_B.rtb_ginv_tmp_ol);
  ContModelSIL_B.D56_tmp_tmp_ff = sin(ContModelSIL_B.D56_tmp_tmp_ff +
    ContModelSIL_B.D37);
  ContModelSIL_B.d6 = sin((ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3] -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  ContModelSIL_B.d7 = sin(ContModelSIL_B.rtb_ginv_tmp_tmp_p +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelSIL_B.D15_tmp_tmp = sin(ContModelSIL_B.D15_tmp_tmp);
  ContModelSIL_B.D15_tmp_tmp_a = sin(ContModelSIL_B.D15_tmp_tmp_a);
  ContModelSIL_B.D56_tmp_tmp = sin(ContModelSIL_B.D56_tmp_tmp +
    ContModelSIL_B.D14_tmp_tmp);
  ContModelSIL_B.D46_tmp_tmp_o = sin(ContModelSIL_B.D46_tmp_tmp_o +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelSIL_B.d8 = sin(ContModelSIL_B.D37 +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelSIL_B.D37 = sin(ContModelSIL_B.D14_tmp_tmp + ContModelSIL_B.D37);
  ContModelSIL_B.d9 = sin(ContModelSIL_B.rtb_ginv_tmp_tmp_p +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelSIL_B.D14_tmp_tmp = sin(ContModelSIL_B.D14_tmp_tmp +
    ContModelSIL_B.rtb_ginv_tmp_tmp_p);
  ContModelSIL_B.rtb_ginv_tmp_tmp_p = cos(ContModelSIL_B.rtb_ginv_tmp_tmp_p);
  ContModelSIL_B.D14_tmp_p = ContModelSIL_B.D14_tmp_p * ContModelSIL_B.x_tmp_b +
    ContModelSIL_B.D14_tmp_ms * ContModelSIL_B.s;
  ContModelSIL_B.D14_tmp_ms = ContModelSIL_B.D14_tmp_md *
    ContModelSIL_B.DigitalClock;
  ContModelSIL_B.d10 = 2.0 * ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.d11 = 0.09794 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [7] * 0.143;
  ContModelSIL_B.D16_tmp_p = ContModelSIL_B.D16_tmp_p * ContModelSIL_B.x_tmp_b +
    ContModelSIL_B.D14_tmp_m3;
  ContModelSIL_B.d12 = ContModelSIL_B.D16_tmp_p * ContModelSIL_B.D46_tmp_h;
  ContModelSIL_B.d13 = ContModelSIL_B.D14_tmp_ms * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.d14 = 2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.d15 = -2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelSIL_B.d149 = -2.0 * ContModelSIL_B.x_tmp;
  ContModelSIL_B.D14_tmp_ms = (ContModelSIL_B.D14_tmp_ms -
    ContModelSIL_B.D16_tmp_f) * ContModelSIL_B.d10 + ContModelSIL_B.D16_tmp_i *
    ContModelSIL_B.d149;
  ContModelSIL_B.D16_tmp_f = ((ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    - ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[5]) +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]) +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelSIL_B.D16_tmp_i = ((ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[5]) +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[6]) +
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelSIL_B.d20 = 2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelSIL_B.d22 = 2.0 * ContModelSIL_B.DigitalClock;
  ContModelSIL_B.dv[24] = -(((((((ContModelSIL_B.D14_tmp_m * ContModelSIL_B.u -
    ContModelSIL_B.D14_tmp_o) * ContModelSIL_B.Observer_alpha +
    ContModelSIL_B.D14_tmp_p * ContModelSIL_B.x_tmp) * (ContModelSIL_B.d20 *
    ContModelSIL_B.D14_tmp_f) + ((ContModelSIL_B.d22 * ContModelSIL_B.D15_tmp_g *
    ContModelSIL_B.x_tmp_b + (cos(ContModelSIL_B.D16_tmp_f) - cos
    (ContModelSIL_B.D16_tmp_i))) * ContModelSIL_B.d11 + ContModelSIL_B.d14 *
    ContModelSIL_B.DigitalClock * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.D34_tmp_n)) + (ContModelSIL_B.D14_tmp_p *
    ContModelSIL_B.Observer_alpha + ContModelSIL_B.D14_tmp_l) *
    (ContModelSIL_B.d15 * ContModelSIL_B.smax)) + ((ContModelSIL_B.D16_tmp_pt -
    ContModelSIL_B.d13) * ContModelSIL_B.d10 + ContModelSIL_B.d12) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) +
    ContModelSIL_B.D14_tmp_ms * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5])
    * 0.5);
  ContModelSIL_B.dv[32] = -((((ContModelSIL_B.D15_tmp_p *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.u + ContModelSIL_B.d11 * ContModelSIL_B.DigitalClock *
    ContModelSIL_B.x_tmp_p * ContModelSIL_B.D34_tmp) +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    ContModelSIL_B.DigitalClock * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.D37_tmp) + ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    ContModelSIL_B.DigitalClock * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.D34_tmp_n) + ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4]
    * ContModelSIL_B.DigitalClock * ContModelSIL_B.D15_tmp_p *
    ContModelSIL_B.x_tmp_b);
  ContModelSIL_B.D14_tmp_p = -0.19588 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7] * 0.143;
  ContModelSIL_B.D14_tmp_m = -ContModelSIL_B.D16_tmp * ContModelSIL_B.u +
    ContModelSIL_B.d13;
  ContModelSIL_B.D14_tmp_o = -2.0 * ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.dv[40] = -(((((((ContModelSIL_B.rtb_ginv_tmp_tmp_o *
    ContModelSIL_B.x_tmp_b + ContModelSIL_B.rtb_ginv_tmp_tmp) *
    -ContModelSIL_B.D14_tmp_md + ContModelSIL_B.D27_tmp) +
    ContModelSIL_B.D27_tmp_k) * ContModelSIL_B.d15 + (ContModelSIL_B.D15_tmp_p *
    ContModelSIL_B.d14 * ContModelSIL_B.x_tmp_p * ContModelSIL_B.u +
    (ContModelSIL_B.rtb_ginv_tmp_e * ContModelSIL_B.D14_tmp_c +
     ContModelSIL_B.rtb_ginv_tmp_i * ContModelSIL_B.D14_tmp_g) *
    ContModelSIL_B.D14_tmp_p)) + (ContModelSIL_B.D14_tmp_m *
    ContModelSIL_B.D14_tmp_o + ContModelSIL_B.d12) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) +
    ContModelSIL_B.D14_tmp_ms * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3])
    * 0.5);
  ContModelSIL_B.D14_tmp_ms = 0.09794 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143;
  ContModelSIL_B.d12 = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelSIL_B.rtb_ginv_tmp_tmp =
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.rtb_ginv_tmp_tmp_o = 0.11464 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142 *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.rtb_ginv_tmp_e =
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.17 * 0.143 *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D14_tmp_l = ContModelSIL_B.D14_tmp_ms * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D16_tmp = 2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5];
  ContModelSIL_B.D16_tmp_pt = 0.09794 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143;
  ContModelSIL_B.D27_tmp = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelSIL_B.D27_tmp_k = ContModelSIL_B.D27_tmp * 2.0 +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelSIL_B.d16 = -2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelSIL_B.D14_tmp *= ContModelSIL_B.D16_tmp_pt;
  ContModelSIL_B.d17 = ContModelSIL_B.d12 - ContModelSIL_B.rtb_ginv_tmp_tmp;
  ContModelSIL_B.d18 = ContModelSIL_B.d12 +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelSIL_B.d19 = ContModelSIL_B.d18 - ContModelSIL_B.rtb_ginv_tmp_tmp;
  ContModelSIL_B.d21 = ContModelSIL_B.d16 * 0.040588879999999994;
  ContModelSIL_B.d23 = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    0.040588879999999994;
  ContModelSIL_B.d24 = ContModelSIL_B.d16 * ContModelSIL_B.x_tmp_b +
    ContModelSIL_B.D27_tmp_k;
  ContModelSIL_B.d52 = 0.22928 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5];
  ContModelSIL_B.d54 = 0.19588 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5];
  ContModelSIL_B.d91 = -2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelSIL_B.dv[48] = -(((((((((((((((((ContModelSIL_B.D14_tmp_ms *
    ContModelSIL_B.D14_tmp_g * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.Observer_alpha + ContModelSIL_B.d23 *
    ContModelSIL_B.D14_tmp_f * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.Observer_alpha) + ContModelSIL_B.d52 * 0.142 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.smax) +
    ContModelSIL_B.D16_tmp * 0.17 * 0.143 * ContModelSIL_B.Observer_alpha *
    ContModelSIL_B.smax) + ContModelSIL_B.rtb_ginv_tmp_tmp_o *
    ContModelSIL_B.D17_tmp_c) + ContModelSIL_B.rtb_ginv_tmp_e *
    ContModelSIL_B.D17_tmp_c) + ContModelSIL_B.d54 * 0.143 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.D14_tmp_c) +
    ContModelSIL_B.D14_tmp_l * ContModelSIL_B.D34_tmp) + -0.22928 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.142 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.smax * ContModelSIL_B.x_tmp_b)
    + -0.22928 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.142 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.smax * ContModelSIL_B.x_tmp_b)
    + ContModelSIL_B.d91 * 0.17 * 0.143 * ContModelSIL_B.Observer_alpha *
    ContModelSIL_B.smax * ContModelSIL_B.x_tmp_b) + ContModelSIL_B.d15 * 0.17 *
    0.143 * ContModelSIL_B.Observer_alpha * ContModelSIL_B.smax *
    ContModelSIL_B.x_tmp_b) + -0.19588 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.D14_tmp_c *
    ContModelSIL_B.x_tmp_b) + -0.19588 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.143 *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.D14_tmp_c *
    ContModelSIL_B.x_tmp_b) + ContModelSIL_B.D14_tmp_p *
    ContModelSIL_B.Observer_alpha * ContModelSIL_B.D14_tmp_c *
    ContModelSIL_B.x_tmp_b) * ContModelSIL_B.DigitalClock + (ContModelSIL_B.d19 *
    ContModelSIL_B.D14_tmp_cz + ContModelSIL_B.d17 * ContModelSIL_B.D16_tmp_tmp)
    * (ContModelSIL_B.d10 * ContModelSIL_B.u)) + ((((ContModelSIL_B.d12 * 2.0 *
    0.040588879999999994 + ContModelSIL_B.D14_tmp) * ContModelSIL_B.x_tmp_b +
    ContModelSIL_B.d21) * ContModelSIL_B.D14_tmp_f +
    ((((ContModelSIL_B.rtb_ginv_tmp_tmp_o * ContModelSIL_B.smax +
        ContModelSIL_B.rtb_ginv_tmp_e * ContModelSIL_B.smax) +
       ContModelSIL_B.D14_tmp_l * ContModelSIL_B.D14_tmp_c) -
      ContModelSIL_B.D16_tmp_pt * ContModelSIL_B.smax * ContModelSIL_B.s *
      ContModelSIL_B.x_tmp_b) - (ContModelSIL_B.D16_tmp -
    ContModelSIL_B.D27_tmp_k * ContModelSIL_B.x_tmp_b) *
     ContModelSIL_B.D14_tmp_cz)) * ContModelSIL_B.DigitalClock +
    ((ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
      ContModelSIL_B.D14_tmp_f * ContModelSIL_B.s + ContModelSIL_B.d24 *
      ContModelSIL_B.D14_tmp_c) * 0.01400542 + (ContModelSIL_B.d17 *
    0.08117775999999999 + ContModelSIL_B.D14_tmp) * ContModelSIL_B.smax) *
    ContModelSIL_B.u) * ContModelSIL_B.x_tmp) * 0.5);
  ContModelSIL_B.D14_tmp_p = ContModelSIL_B.d18 * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.d15 = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.rtb_ginv_tmp_tmp_o = 2.0 * ContModelSIL_B.D14_tmp_g;
  ContModelSIL_B.rtb_ginv_tmp_e =
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] - ContModelSIL_B.D14_tmp_p;
  ContModelSIL_B.dv[56] = -(((((ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4]
    * ContModelSIL_B.D14_tmp_g * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.Observer_alpha + ContModelSIL_B.d15 * ContModelSIL_B.D34_tmp)
    + ContModelSIL_B.d10 * ContModelSIL_B.D14_tmp_c *
    ContModelSIL_B.rtb_ginv_tmp_e) * ContModelSIL_B.DigitalClock +
    ContModelSIL_B.rtb_ginv_tmp_tmp_o * ContModelSIL_B.Observer_alpha *
    ContModelSIL_B.u * ContModelSIL_B.d19) + (((ContModelSIL_B.D14_tmp_p -
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
    ContModelSIL_B.rtb_ginv_tmp_tmp_o + ContModelSIL_B.d15 *
    ContModelSIL_B.D14_tmp_c) * ContModelSIL_B.DigitalClock + 2.0 *
    ContModelSIL_B.u * ContModelSIL_B.D14_tmp_c * ContModelSIL_B.d19) *
    ContModelSIL_B.x_tmp) * 0.00700271);
  ContModelSIL_B.D14_tmp_p = ContModelSIL_B.D15_tmp_tmp_i +
    ContModelSIL_B.D15_tmp_tmp_o;
  ContModelSIL_B.d10 = ContModelSIL_B.d15 * ContModelSIL_B.u;
  ContModelSIL_B.d15 = ContModelSIL_B.D14_tmp_p *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelSIL_B.dv[25] = -(((((((((cos(ContModelSIL_B.D16_tmp_f -
    ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]) - cos
    (ContModelSIL_B.D16_tmp_i - ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]))
    - cos(ContModelSIL_B.D16_tmp_f +
          ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4])) + cos
    (ContModelSIL_B.D16_tmp_i + ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[4]))
    + sin(ContModelSIL_B.D16_tmp_f) * 2.0) + sin(ContModelSIL_B.D16_tmp_i) * 2.0)
    * (-0.024485 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7] * 0.143) +
    (-ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
     ContModelSIL_B.DigitalClock * ContModelSIL_B.D37_tmp +
     ContModelSIL_B.D34_tmp_n * ContModelSIL_B.d10)) + ContModelSIL_B.d15 *
    ContModelSIL_B.u * ContModelSIL_B.x_tmp_b) + (ContModelSIL_B.D15_tmp_p *
    ContModelSIL_B.u * ContModelSIL_B.x_tmp_b + ContModelSIL_B.D34_tmp_n *
    -ContModelSIL_B.DigitalClock) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) +
    (ContModelSIL_B.D16_tmp_p * ContModelSIL_B.Observer_alpha +
     ContModelSIL_B.D14_tmp_m * ContModelSIL_B.x_tmp) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]);
  ContModelSIL_B.D16_tmp_p = ContModelSIL_B.D15_tmp_p *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.D16_tmp_f = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.dv[33] = -((((-ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]
    * ContModelSIL_B.DigitalClock * ContModelSIL_B.D15_tmp_p *
    ContModelSIL_B.x_tmp_p + ContModelSIL_B.d11 * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.u * ContModelSIL_B.D34_tmp) +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.u * ContModelSIL_B.D37_tmp) + ContModelSIL_B.D16_tmp_f *
    ContModelSIL_B.u * ContModelSIL_B.D34_tmp_n) + ContModelSIL_B.D16_tmp_p *
    ContModelSIL_B.u * ContModelSIL_B.x_tmp_b);
  ContModelSIL_B.D16_tmp_i = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] -
    ContModelSIL_B.d12 * ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.D14_tmp_m = (((ContModelSIL_B.d20 +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) * 0.17 * 0.143 +
    ContModelSIL_B.d12 * 0.22928 * 0.142) + ContModelSIL_B.d21 *
    ContModelSIL_B.x_tmp_b) + ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    0.17 * 0.143 * ContModelSIL_B.rtb_ginv_tmp_b;
  ContModelSIL_B.rtb_ginv_tmp_tmp_o = 4.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelSIL_B.D14_tmp_l = -4.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelSIL_B.D27_tmp_k = -4.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelSIL_B.dv[41] = -((((((((((-3.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] + ContModelSIL_B.D14_tmp_l)
    + ContModelSIL_B.D27_tmp_k) +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    ContModelSIL_B.rtb_ginv_tmp_tmp_p) + ContModelSIL_B.rtb_ginv_tmp_tmp_o *
    ContModelSIL_B.x_tmp_b) * (-0.00700271 * ContModelSIL_B.D14_tmp_g) +
    (-ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * ContModelSIL_B.x_tmp_b
     + ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) * 0.047378399999999994)
    + ContModelSIL_B.D14_tmp_m * ContModelSIL_B.D14_tmp_f) * ContModelSIL_B.u +
    ((ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.08312 * 0.285 *
      ContModelSIL_B.x_tmp_p + ContModelSIL_B.D16_tmp_i *
      ContModelSIL_B.D14_tmp_tmp_m) + ContModelSIL_B.rtb_ginv_tmp_e *
     ContModelSIL_B.D14_tmp_tmp_c) * ContModelSIL_B.d22) * -ContModelSIL_B.x_tmp
    + ((((-ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
          ContModelSIL_B.x_tmp_b +
          ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
         0.023689199999999997 + ContModelSIL_B.D16_tmp_i *
         ContModelSIL_B.D16_tmp_tmp) + ContModelSIL_B.rtb_ginv_tmp_e *
        ContModelSIL_B.D14_tmp_cz) * ContModelSIL_B.Observer_alpha +
       (ContModelSIL_B.D14_tmp_ms * ContModelSIL_B.D15_tmp_g *
        ContModelSIL_B.x_tmp_p + ContModelSIL_B.d23 * ContModelSIL_B.D15_tmp *
        ContModelSIL_B.x_tmp_p)) * (-2.0 * ContModelSIL_B.DigitalClock)) +
    (((ContModelSIL_B.rtb_ginv_tmp_b *
       ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] + ContModelSIL_B.d24) *
      ContModelSIL_B.D14_tmp_tmp_c + ContModelSIL_B.D14_tmp_m *
      ContModelSIL_B.smax) * ContModelSIL_B.Observer_alpha +
     (-ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.17 * 0.143 *
      ContModelSIL_B.D15_tmp * ContModelSIL_B.D17_tmp_ct -
      ContModelSIL_B.D16_tmp_pt * ContModelSIL_B.D15_tmp_g *
      ContModelSIL_B.D17_tmp_ct)) * ContModelSIL_B.u) * 0.5);
  ContModelSIL_B.D14_tmp_ms = ContModelSIL_B.D16_tmp_tmp +
    ContModelSIL_B.D14_tmp_cz;
  ContModelSIL_B.dv[49] = -((((ContModelSIL_B.D14_tmp_p *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * ContModelSIL_B.u *
    ContModelSIL_B.x_tmp_b + (-ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3]
    * ContModelSIL_B.DigitalClock * ContModelSIL_B.D37_tmp + ContModelSIL_B.d10 *
    ContModelSIL_B.D37_tmp)) - (ContModelSIL_B.DigitalClock *
    ContModelSIL_B.D34_tmp - ContModelSIL_B.D15_tmp_g * ContModelSIL_B.u *
    ContModelSIL_B.x_tmp_b) * ContModelSIL_B.d11) + (ContModelSIL_B.D14_tmp_p *
    ContModelSIL_B.u * ContModelSIL_B.x_tmp_b + ContModelSIL_B.D37_tmp *
    -ContModelSIL_B.DigitalClock) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6]) +
    ((ContModelSIL_B.D14_tmp_ms * ContModelSIL_B.DigitalClock *
      ContModelSIL_B.x_tmp_b + ContModelSIL_B.D14_tmp_m3) *
     ContModelSIL_B.Observer_alpha + (-ContModelSIL_B.D14_tmp_ms *
    ContModelSIL_B.u + ContModelSIL_B.d13) * ContModelSIL_B.x_tmp) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]);
  ContModelSIL_B.dv[57] = -(((((ContModelSIL_B.d18 -
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4]) *
    ContModelSIL_B.D46_tmp_dh + ContModelSIL_B.D16_tmp *
    ContModelSIL_B.D15_tmp_g) - (ContModelSIL_B.d18 +
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4]) *
    ContModelSIL_B.D46_tmp_b) * ContModelSIL_B.u + ContModelSIL_B.d22 *
    ContModelSIL_B.D34_tmp * ContModelSIL_B.d19) * -0.00700271);
  ContModelSIL_B.dv[26] = -(((ContModelSIL_B.d11 * ContModelSIL_B.D15_tmp_g *
    ContModelSIL_B.x_tmp_p + ContModelSIL_B.d15 * ContModelSIL_B.x_tmp_p) +
    ContModelSIL_B.D15_tmp_p * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3]
    * ContModelSIL_B.x_tmp_p) - ContModelSIL_B.D34_tmp_n *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * ContModelSIL_B.x_tmp_b);
  ContModelSIL_B.dv[34] = -(((ContModelSIL_B.D16_tmp_p * ContModelSIL_B.x_tmp_p
    - ContModelSIL_B.d11 * ContModelSIL_B.D34_tmp * ContModelSIL_B.x_tmp_b) +
    ContModelSIL_B.D37_tmp * -ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    ContModelSIL_B.x_tmp_b) - ContModelSIL_B.D34_tmp_n *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * ContModelSIL_B.x_tmp_b);
  ContModelSIL_B.dv[42] = -0.0;
  ContModelSIL_B.dv[50] = -((ContModelSIL_B.d18 * 0.09794 * 0.143 *
    ContModelSIL_B.D15_tmp_g * ContModelSIL_B.x_tmp_p + ContModelSIL_B.d12 *
    0.040588879999999994 * ContModelSIL_B.D15_tmp * ContModelSIL_B.x_tmp_p) -
    ContModelSIL_B.D37_tmp * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    ContModelSIL_B.x_tmp_b);
  ContModelSIL_B.dv[58] = -((ContModelSIL_B.d18 * ContModelSIL_B.D15_tmp_g *
    ContModelSIL_B.x_tmp_p - ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    ContModelSIL_B.D34_tmp * ContModelSIL_B.x_tmp_b) * 0.01400542);
  ContModelSIL_B.dv[27] = -(-ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    0.08312 * 0.040588879999999994 * ContModelSIL_B.smax -
    (ContModelSIL_B.D27_tmp * 0.08312 * ContModelSIL_B.D14_tmp_c +
     ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7] * 0.17 * ContModelSIL_B.s)
    * 0.01400542);
  ContModelSIL_B.D14_tmp_p = 0.04043155 * ContModelSIL_B.D17;
  ContModelSIL_B.D14_tmp_ms = 0.06214814 * ContModelSIL_B.D17;
  ContModelSIL_B.d10 = 0.0009810686847999998 * ContModelSIL_B.D17;
  ContModelSIL_B.d11 = 0.0009879776191999998 * ContModelSIL_B.D17;
  ContModelSIL_B.D16_tmp_p = 5.484E-5 * ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d13 = 0.00050874 * ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d15 = 0.0018662108031999999 * ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.D16_tmp_i = 0.0041327000000000004 * ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d22 = 8.085E-5 * ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.D14_tmp_m = 0.00034964 * ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.rtb_ginv_tmp_e = 0.0013716908347999998 *
    ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.D16_tmp_pt = 0.0 * ContModelSIL_B.D46_tmp_n;
  ContModelSIL_B.D27_tmp = 5.484E-5 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.D14_tmp = 0.00050874 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.d21 = 0.0018662108031999999 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.d23 = 0.0041327000000000004 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.d24 = 0.004761842800000001 * ContModelSIL_B.D46_tmp_tmp_c;
  ContModelSIL_B.D14_tmp_g = 0.004761842800000001 * ContModelSIL_B.D56_tmp_tmp_g;
  ContModelSIL_B.D14_tmp_cz = 8.085E-5 * ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.D14_tmp_tmp_m = 0.00034964 * ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.D14_tmp_tmp_c = 0.0013716908347999998 *
    ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.D14_tmp_m3 = 0.00093002 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D15_tmp_tmp_i = 0.0006068 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D15_tmp_tmp_o = 0.0037324216063999997 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D16_tmp_tmp = 0.0027433816695999996 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D34_tmp_n = 0.008265400000000001 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.D37_tmp = -0.0 * ContModelSIL_B.D46_tmp_l;
  ContModelSIL_B.rtb_ginv_tmp_b = 5.484E-5 * ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.d56 = 0.00050874 * ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.d57 = 0.0018662108031999999 * ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.d58 = 0.0041327000000000004 * ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.d59 = 0.004761842800000001 * ContModelSIL_B.D46_tmp_tmp_d;
  ContModelSIL_B.d60 = -0.0 * ContModelSIL_B.D46_tmp_j;
  ContModelSIL_B.d61 = 0.004761842800000001 * ContModelSIL_B.D56_tmp_tmp_i;
  ContModelSIL_B.d62 = 8.085E-5 * ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.d63 = 0.00034964 * ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.d64 = 0.0013716908347999998 * ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.d65 = 0.0 * ContModelSIL_B.D56_tmp_l;
  ContModelSIL_B.d66 = 0.0 * ContModelSIL_B.D56_tmp_d;
  ContModelSIL_B.d67 = 0.0 * ContModelSIL_B.D56_tmp_n;
  ContModelSIL_B.d68 = 0.0 * ContModelSIL_B.D56_tmp_ln;
  ContModelSIL_B.d55 =
    ((((((((((((((((((((((((((((((((((((((((((((((((((((-0.019747543696 *
    ContModelSIL_B.D56_tmp_tmp_h + 0.006747495411199999 *
    ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.D16_tmp_pt) +
    0.0027062010112 * ContModelSIL_B.D27) + 0.0040412944 * ContModelSIL_B.D27) -
    ContModelSIL_B.D27_tmp) + ContModelSIL_B.D14_tmp) + ContModelSIL_B.d21) +
    ContModelSIL_B.d23) + ContModelSIL_B.d24) + 0.0023282610207999996 *
    ContModelSIL_B.D46_tmp_tmp_a) + ContModelSIL_B.D46_tmp_tmp_f) +
    0.0023282610207999996 * ContModelSIL_B.D56_tmp_tmp_iz) +
    ContModelSIL_B.D14_tmp_g) - ContModelSIL_B.D14_tmp_cz) +
    ContModelSIL_B.D14_tmp_tmp_m) + ContModelSIL_B.D14_tmp_tmp_c) +
    ContModelSIL_B.D14_tmp_m3) + ContModelSIL_B.D15_tmp_tmp_i) + 0.0787496 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.D15_tmp_tmp_o) +
    0.0019621373695999996 * ContModelSIL_B.x_tmp_p) + ContModelSIL_B.D16_tmp_tmp)
    + 0.0019759552383999996 * ContModelSIL_B.x_tmp_p) + ContModelSIL_B.D34_tmp_n)
    + 0.04043155 * ContModelSIL_B.D56_tmp_tmp_g2) - 0.06214814 *
    ContModelSIL_B.D56_tmp_tmp_g2) + 0.0009810686847999998 *
    ContModelSIL_B.D56_tmp_tmp_g2) + 0.0009879776191999998 *
    ContModelSIL_B.D56_tmp_tmp_g2) + 0.0027062010112 *
    ContModelSIL_B.D46_tmp_tmp_e) + 0.0040412944 * ContModelSIL_B.D46_tmp_tmp_e)
    + ContModelSIL_B.D37_tmp) + 0.0027062010112 * ContModelSIL_B.D56_tmp_tmp_fi)
    + 0.0040412944 * ContModelSIL_B.D56_tmp_tmp_fi) -
                       ContModelSIL_B.rtb_ginv_tmp_b) + ContModelSIL_B.d56) +
                     ContModelSIL_B.d57) + ContModelSIL_B.d58) +
                   ContModelSIL_B.d59) + 0.0023282610207999996 *
                  ContModelSIL_B.D46_tmp_tmp_af) + ContModelSIL_B.d60) +
                0.0023282610207999996 * ContModelSIL_B.D56_tmp_tmp_c) +
               ContModelSIL_B.d61) - ContModelSIL_B.d62) + ContModelSIL_B.d63) +
            ContModelSIL_B.d64) + ContModelSIL_B.D46_tmp_mj) +
          ContModelSIL_B.d65) + ContModelSIL_B.D46_tmp_c) + ContModelSIL_B.d66)
       + ContModelSIL_B.D56_tmp_h) + ContModelSIL_B.d67) +
     ContModelSIL_B.D56_tmp_m) + ContModelSIL_B.d68;
  ContModelSIL_B.d159 = -0.0 * ContModelSIL_B.rtb_ginv_tmp_n + -0.0 *
    ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.d160 = 0.004761842800000001 * ContModelSIL_B.D28;
  ContModelSIL_B.dv[35] = -(((((((((((((((((ContModelSIL_B.d159 +
    ContModelSIL_B.D14_tmp_p) - ContModelSIL_B.D14_tmp_ms) + ContModelSIL_B.d10)
    + ContModelSIL_B.d11) - ContModelSIL_B.D16_tmp_p) + ContModelSIL_B.d13) +
    ContModelSIL_B.d15) + ContModelSIL_B.D16_tmp_i) + 0.0027062010112 *
    ContModelSIL_B.D18) + 0.0040412944 * ContModelSIL_B.D18) -
    ContModelSIL_B.d22) + ContModelSIL_B.D14_tmp_m) +
    ContModelSIL_B.rtb_ginv_tmp_e) + 0.0023282610207999996 *
    ContModelSIL_B.D56_tmp_tmp_a) + ContModelSIL_B.d160) * ContModelSIL_B.d14 +
    ContModelSIL_B.d55 * -ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
    0.25);
  ContModelSIL_B.d25 = ContModelSIL_B.rtb_ginv_tmp_tmp_o * 0.0;
  ContModelSIL_B.d26 = ContModelSIL_B.D16_tmp * 0.0;
  ContModelSIL_B.d27 = -2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.d28 = ContModelSIL_B.d27 * 0.0069089343999999995;
  ContModelSIL_B.d29 = -4.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.d30 = -0.45856 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.08312 * 0.142;
  ContModelSIL_B.tmp_tmp = ContModelSIL_B.d29 * 0.08312 * 0.17 * 0.143;
  ContModelSIL_B.d31 = -0.39176 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.d32 = ContModelSIL_B.d29 * 0.0;
  ContModelSIL_B.d33 = ContModelSIL_B.d31 * 0.08312 * 0.143;
  ContModelSIL_B.d31 = ContModelSIL_B.d31 * 0.17 * 0.143;
  ContModelSIL_B.d34 = ContModelSIL_B.d29 * 0.0069089343999999995;
  ContModelSIL_B.d35 = ContModelSIL_B.d27 * 0.04043155;
  ContModelSIL_B.d36 = ContModelSIL_B.d14 * 0.06214814;
  ContModelSIL_B.d37 = ContModelSIL_B.d28 * 0.142;
  ContModelSIL_B.d28 *= 0.143;
  ContModelSIL_B.d38 = ContModelSIL_B.d14 * 5.484E-5;
  ContModelSIL_B.d39 = ContModelSIL_B.d27 * 0.00050874;
  ContModelSIL_B.d40 = -0.0262846592 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142;
  ContModelSIL_B.tmp_tmp_c = ContModelSIL_B.d27 * 0.028900000000000006 * 0.143;
  ContModelSIL_B.d111 = 4.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.d41 = ContModelSIL_B.d111 * 0.0;
  ContModelSIL_B.tmp_tmp_n = ContModelSIL_B.d14 * 8.085E-5;
  ContModelSIL_B.tmp_tmp_i = ContModelSIL_B.d27 * 0.00034964;
  ContModelSIL_B.tmp_tmp_m = -0.0191844872 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143;
  ContModelSIL_B.d42 = ContModelSIL_B.d16 * 0.0;
  ContModelSIL_B.d43 = ContModelSIL_B.d16 * 0.0069089343999999995;
  ContModelSIL_B.d44 = -0.39176 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelSIL_B.d45 = -0.19588 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelSIL_B.d46 = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.0069089343999999995;
  ContModelSIL_B.d47 = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.04043155;
  ContModelSIL_B.tmp_tmp_o = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.06214814;
  ContModelSIL_B.tmp_tmp_d = ContModelSIL_B.d46 * 0.142;
  ContModelSIL_B.d46 *= 0.143;
  ContModelSIL_B.tmp_tmp_ik = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    5.484E-5;
  ContModelSIL_B.tmp_tmp_gs = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.00050874;
  ContModelSIL_B.tmp_tmp_nn = 0.0131423296 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.142;
  ContModelSIL_B.tmp_tmp_l = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    8.085E-5;
  ContModelSIL_B.tmp_tmp_ce = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.00034964;
  ContModelSIL_B.tmp_tmp_nc = 0.0095922436 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.143;
  ContModelSIL_B.d48 = -0.22928 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142;
  ContModelSIL_B.d49 = ContModelSIL_B.d16 * 0.08312 * 0.17 * 0.143;
  ContModelSIL_B.d50 = ContModelSIL_B.d45 * 0.08312 * 0.143;
  ContModelSIL_B.d45 = ContModelSIL_B.d45 * 0.17 * 0.143;
  ContModelSIL_B.d51 = 0.17 * ContModelSIL_B.s + 0.08312 *
    ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.d53 = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.028900000000000006 * 0.143;
  ContModelSIL_B.d90 = ContModelSIL_B.d35 * ContModelSIL_B.D56_tmp_tmp_h;
  ContModelSIL_B.d92 = ContModelSIL_B.d36 * ContModelSIL_B.D56_tmp_tmp_h;
  ContModelSIL_B.d93 = ContModelSIL_B.d37 * ContModelSIL_B.D56_tmp_tmp_h;
  ContModelSIL_B.d94 = ContModelSIL_B.d28 * ContModelSIL_B.D56_tmp_tmp_h;
  ContModelSIL_B.d96 = ContModelSIL_B.d32 * ContModelSIL_B.D46_tmp_n;
  ContModelSIL_B.d97 = ContModelSIL_B.d26 * ContModelSIL_B.d1;
  ContModelSIL_B.d98 = ContModelSIL_B.d30 * ContModelSIL_B.D27;
  ContModelSIL_B.d99 = ContModelSIL_B.tmp_tmp * ContModelSIL_B.D27;
  ContModelSIL_B.d100 = ContModelSIL_B.d38 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.d101 = ContModelSIL_B.d39 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.d102 = ContModelSIL_B.d40 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.d103 = ContModelSIL_B.tmp_tmp_c * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.d104 = ContModelSIL_B.d32 * ContModelSIL_B.D46_tmp_p;
  ContModelSIL_B.d105 = ContModelSIL_B.d26 * ContModelSIL_B.D46_tmp_tmp_l;
  ContModelSIL_B.d106 = ContModelSIL_B.d33 * ContModelSIL_B.D56_tmp_tmp_iz;
  ContModelSIL_B.d107 = ContModelSIL_B.d31 * ContModelSIL_B.D56_tmp_tmp_g;
  ContModelSIL_B.d108 = ContModelSIL_B.tmp_tmp_n * ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.d109 = ContModelSIL_B.tmp_tmp_i * ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.d110 = ContModelSIL_B.tmp_tmp_m * ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.d112 = ContModelSIL_B.d45 * ContModelSIL_B.D46_tmp_tmp;
  ContModelSIL_B.tmp_tmp_h = -4.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelSIL_B.d113 = ContModelSIL_B.d48 * ContModelSIL_B.D56_tmp_tmp_f;
  ContModelSIL_B.d114 = ContModelSIL_B.d49 * ContModelSIL_B.D56_tmp_tmp_f;
  ContModelSIL_B.d115 = ContModelSIL_B.d50 * ContModelSIL_B.D56_tmp_tmp_ff;
  ContModelSIL_B.d116 = ContModelSIL_B.tmp_tmp_o * ContModelSIL_B.d6;
  ContModelSIL_B.d117 = ContModelSIL_B.d32 * ContModelSIL_B.D46_tmp_d;
  ContModelSIL_B.d118 = ContModelSIL_B.tmp_tmp_ik * ContModelSIL_B.D38;
  ContModelSIL_B.d119 = ContModelSIL_B.tmp_tmp_gs * ContModelSIL_B.D38;
  ContModelSIL_B.d120 = ContModelSIL_B.tmp_tmp_nn * ContModelSIL_B.D38;
  ContModelSIL_B.d121 = ContModelSIL_B.d53 * ContModelSIL_B.D38;
  ContModelSIL_B.d123 = ContModelSIL_B.d32 * ContModelSIL_B.D56_tmp_l;
  ContModelSIL_B.d124 = ContModelSIL_B.d32 * ContModelSIL_B.D46_tmp_dh;
  ContModelSIL_B.d125 = ContModelSIL_B.tmp_tmp_l * ContModelSIL_B.D47;
  ContModelSIL_B.d126 = ContModelSIL_B.tmp_tmp_ce * ContModelSIL_B.D47;
  ContModelSIL_B.d127 = ContModelSIL_B.tmp_tmp_nc * ContModelSIL_B.D47;
  ContModelSIL_B.d128 = ContModelSIL_B.d32 * ContModelSIL_B.D56_tmp_d;
  ContModelSIL_B.d129 = ContModelSIL_B.d16 * 0.00050874;
  ContModelSIL_B.d130 = ContModelSIL_B.d16 * 0.00034964;
  ContModelSIL_B.d131 = ContModelSIL_B.d16 * 0.04043155;
  ContModelSIL_B.d136 = ContModelSIL_B.d47 * ContModelSIL_B.D48_tmp;
  ContModelSIL_B.d137 = ContModelSIL_B.tmp_tmp_d * ContModelSIL_B.D48_tmp;
  ContModelSIL_B.d138 = ContModelSIL_B.d46 * ContModelSIL_B.D48_tmp;
  ContModelSIL_B.d139 = ContModelSIL_B.d47 * ContModelSIL_B.D58;
  ContModelSIL_B.d140 = ContModelSIL_B.tmp_tmp_o * ContModelSIL_B.D58;
  ContModelSIL_B.d141 = ContModelSIL_B.tmp_tmp_d * ContModelSIL_B.D58;
  ContModelSIL_B.d142 = ContModelSIL_B.d46 * ContModelSIL_B.D58;
  ContModelSIL_B.d143 = ContModelSIL_B.tmp_tmp_ik * ContModelSIL_B.y_a;
  ContModelSIL_B.d144 = ContModelSIL_B.tmp_tmp_gs * ContModelSIL_B.y_a;
  ContModelSIL_B.d145 = ContModelSIL_B.tmp_tmp_nn * ContModelSIL_B.y_a;
  ContModelSIL_B.d146 = ContModelSIL_B.tmp_tmp_l * ContModelSIL_B.ab_a;
  ContModelSIL_B.d147 = ContModelSIL_B.tmp_tmp_ce * ContModelSIL_B.ab_a;
  ContModelSIL_B.d148 = ContModelSIL_B.tmp_tmp_nc * ContModelSIL_B.ab_a;
  ContModelSIL_B.d150 = ContModelSIL_B.d31 * ContModelSIL_B.D46_tmp_tmp_c;
  ContModelSIL_B.d151 = ContModelSIL_B.d29 * 0.00046501 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d152 = ContModelSIL_B.d29 * 0.0003034 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d153 = -0.0525693184 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142 *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d154 = -0.0383689744 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143 *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d155 = ContModelSIL_B.d29 * 0.028900000000000006 * 0.143 *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d156 = ContModelSIL_B.d31 * ContModelSIL_B.D46_tmp_tmp_d;
  ContModelSIL_B.d184 = ContModelSIL_B.d25 * ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.d185 = ContModelSIL_B.d26 * ContModelSIL_B.d;
  ContModelSIL_B.d161 = ((ContModelSIL_B.d25 * ContModelSIL_B.rtb_ginv_tmp_n +
    ContModelSIL_B.d184) + ContModelSIL_B.d26 * ContModelSIL_B.D68) +
    ContModelSIL_B.d185;
  ContModelSIL_B.d162 = ContModelSIL_B.d26 * ContModelSIL_B.d2;
  ContModelSIL_B.d163 = ContModelSIL_B.d26 * ContModelSIL_B.D46_tmp_tmp_o2;
  ContModelSIL_B.d164 = ContModelSIL_B.d42 * ContModelSIL_B.d3;
  ContModelSIL_B.d165 = ContModelSIL_B.d42 * ContModelSIL_B.d4;
  ContModelSIL_B.d166 = ContModelSIL_B.D16_tmp * 5.484E-5 *
    ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d167 = ContModelSIL_B.d129 * ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d168 = -0.0262846592 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.142 *
    ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d169 = ContModelSIL_B.d16 * 0.028900000000000006 * 0.143 *
    ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d170 = ContModelSIL_B.D16_tmp * 8.085E-5 *
    ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.d171 = ContModelSIL_B.d130 * ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.d172 = -0.0191844872 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.143 *
    ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.d173 = ContModelSIL_B.d44 * 0.17 * 0.143 * ContModelSIL_B.D28;
  ContModelSIL_B.d174 = ContModelSIL_B.d42 * ContModelSIL_B.D67;
  ContModelSIL_B.d175 = ContModelSIL_B.d42 * ContModelSIL_B.rtb_ginv_tmp_ol;
  ContModelSIL_B.d176 = 0.78352 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelSIL_B.d180 = ContModelSIL_B.d26 * ContModelSIL_B.D15_tmp_tmp;
  ContModelSIL_B.d181 = ContModelSIL_B.d26 * ContModelSIL_B.D15_tmp_tmp_a;
  ContModelSIL_B.d182 = ContModelSIL_B.d45 * ContModelSIL_B.D46_tmp_tmp_o;
  ContModelSIL_B.dv[43] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    ((((((((((((((((((((((((((((((((((((((((ContModelSIL_B.d161 +
    ContModelSIL_B.d90) + ContModelSIL_B.d92) + ContModelSIL_B.d93) +
    ContModelSIL_B.d94) + ContModelSIL_B.d30 * ContModelSIL_B.D46_tmp_tmp_ei) +
    ContModelSIL_B.tmp_tmp * ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.d96)
    + ContModelSIL_B.d97) + ContModelSIL_B.d98) + ContModelSIL_B.d99) +
    ContModelSIL_B.d100) + ContModelSIL_B.d101) + ContModelSIL_B.d102) +
    ContModelSIL_B.d103) + ContModelSIL_B.d150) + ContModelSIL_B.d33 *
    ContModelSIL_B.D46_tmp_tmp_a) + ContModelSIL_B.d104) + ContModelSIL_B.d105)
    + ContModelSIL_B.d106) + ContModelSIL_B.d107) + ContModelSIL_B.d108) +
    ContModelSIL_B.d109) + ContModelSIL_B.d110) + ContModelSIL_B.d151) +
    ContModelSIL_B.d152) + ContModelSIL_B.d29 * 0.0393748 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.d153) + ContModelSIL_B.d34 * 0.142 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.d154) + ContModelSIL_B.d34 * 0.143 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.d155) + ContModelSIL_B.d35 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d36 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d37 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d28 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d30 *
    ContModelSIL_B.D46_tmp_tmp_e) + ContModelSIL_B.tmp_tmp *
    ContModelSIL_B.D46_tmp_tmp_e) + ContModelSIL_B.d41 *
    ContModelSIL_B.D46_tmp_l) + ContModelSIL_B.d162) + ContModelSIL_B.d30 *
    ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.tmp_tmp *
    ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.d38 *
    ContModelSIL_B.D56_tmp_f) + ContModelSIL_B.d39 * ContModelSIL_B.D56_tmp_f) +
    ContModelSIL_B.d40 * ContModelSIL_B.D56_tmp_f) + ContModelSIL_B.tmp_tmp_c *
    ContModelSIL_B.D56_tmp_f) + ContModelSIL_B.d156) + ContModelSIL_B.d33 *
    ContModelSIL_B.D46_tmp_tmp_af) + ContModelSIL_B.d41 *
    ContModelSIL_B.D46_tmp_j) + ContModelSIL_B.d163) + ContModelSIL_B.d33 *
    ContModelSIL_B.D56_tmp_tmp_c) + ContModelSIL_B.d31 *
    ContModelSIL_B.D56_tmp_tmp_i) + ContModelSIL_B.tmp_tmp_n *
    ContModelSIL_B.D56_tmp_a) + ContModelSIL_B.tmp_tmp_i *
    ContModelSIL_B.D56_tmp_a) + ContModelSIL_B.tmp_tmp_m *
    ContModelSIL_B.D56_tmp_a) + ContModelSIL_B.d164) + ContModelSIL_B.d165) +
    ContModelSIL_B.d131 * ContModelSIL_B.D17) + ContModelSIL_B.D16_tmp *
    0.06214814 * ContModelSIL_B.D17) + ContModelSIL_B.d43 * 0.142 *
    ContModelSIL_B.D17) + ContModelSIL_B.d43 * 0.143 * ContModelSIL_B.D17) +
    ContModelSIL_B.d166) + ContModelSIL_B.d167) + ContModelSIL_B.d168) +
    ContModelSIL_B.d169) + -0.45856 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142 *
    ContModelSIL_B.D18) + ContModelSIL_B.tmp_tmp_h * 0.08312 * 0.17 * 0.143 *
    ContModelSIL_B.D18) + ContModelSIL_B.d170) + ContModelSIL_B.d171) +
    ContModelSIL_B.d172) + ContModelSIL_B.d44 * 0.08312 * 0.143 *
    ContModelSIL_B.D56_tmp_tmp_a) + ContModelSIL_B.d173) + ContModelSIL_B.d112)
    + ContModelSIL_B.d174) + ContModelSIL_B.d113) + ContModelSIL_B.d114) +
    ContModelSIL_B.d175) + ContModelSIL_B.d115) + ContModelSIL_B.d116) +
    ContModelSIL_B.d117) + ContModelSIL_B.d118) - ContModelSIL_B.d119) -
    ContModelSIL_B.d120) - ContModelSIL_B.d121) + ContModelSIL_B.d123) +
    ContModelSIL_B.d124) + ContModelSIL_B.d125) - ContModelSIL_B.d126) -
    ContModelSIL_B.d127) + ContModelSIL_B.d128) + ContModelSIL_B.d176 * 0.143 *
    ContModelSIL_B.d51 * ContModelSIL_B.x_tmp_b) + 8.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.08312 *
    ContModelSIL_B.D14_tmp_md * ContModelSIL_B.x_tmp_b) + ContModelSIL_B.d136) +
    ContModelSIL_B.d137) + ContModelSIL_B.d138) - ContModelSIL_B.d139) +
    ContModelSIL_B.d140) - ContModelSIL_B.d141) - ContModelSIL_B.d142) +
                       ContModelSIL_B.d41 * ContModelSIL_B.D46_tmp_o) +
                      ContModelSIL_B.d143) - ContModelSIL_B.d144) -
                    ContModelSIL_B.d145) +
                   -ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
                   0.028900000000000006 * 0.143 * ContModelSIL_B.y_a) +
                  ContModelSIL_B.d32 * ContModelSIL_B.D56_tmp_n) +
                 ContModelSIL_B.d41 * ContModelSIL_B.D46_tmp_b) +
                ContModelSIL_B.d146) - ContModelSIL_B.d147) -
              ContModelSIL_B.d148) + ContModelSIL_B.d32 *
             ContModelSIL_B.D56_tmp_ln) + ContModelSIL_B.d180) +
           ContModelSIL_B.d181) + ContModelSIL_B.d48 *
          ContModelSIL_B.rtb_ginv_tmp_tmp_p4) + ContModelSIL_B.d49 *
         ContModelSIL_B.rtb_ginv_tmp_tmp_p4) + ContModelSIL_B.d50 *
        ContModelSIL_B.D56_tmp_tmp) + ContModelSIL_B.d182) * 0.125);
  ContModelSIL_B.d29 = -0.09794 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelSIL_B.d34 = ContModelSIL_B.D14_tmp_md * 0.08312;
  ContModelSIL_B.dv[51] = -(ContModelSIL_B.d29 * 0.143 * ContModelSIL_B.d51 -
    ContModelSIL_B.d34 * ContModelSIL_B.d17);
  ContModelSIL_B.dv[59] = -(ContModelSIL_B.d51 * -0.01400542 *
    ContModelSIL_B.d19);
  ContModelSIL_B.d52 = ContModelSIL_B.d52 * 0.08312 * 0.142;
  ContModelSIL_B.d43 = ContModelSIL_B.D16_tmp * 0.08312 * 0.17 * 0.143;
  ContModelSIL_B.d44 = ContModelSIL_B.d54 * 0.08312 * 0.143;
  ContModelSIL_B.d54 = ContModelSIL_B.d54 * 0.17 * 0.143;
  ContModelSIL_B.D14_tmp_md = ContModelSIL_B.D16_tmp * 0.0069089343999999995;
  ContModelSIL_B.d95 = -4.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelSIL_B.tmp_tmp_p = ContModelSIL_B.d95 * 0.0;
  ContModelSIL_B.tmp_tmp_dk = ContModelSIL_B.D14_tmp_l * 0.0;
  ContModelSIL_B.tmp_tmp_oi = ContModelSIL_B.d41 * ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.tmp_tmp_nm = 4.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelSIL_B.d122 = ContModelSIL_B.tmp_tmp_nm * 0.0;
  ContModelSIL_B.d157 = 4.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelSIL_B.d158 = 4.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelSIL_B.d12 = ((((ContModelSIL_B.d12 * 4.0 * 0.0 *
    ContModelSIL_B.D15_tmp + ContModelSIL_B.d41 * ContModelSIL_B.rtb_ginv_tmp_n)
    + ContModelSIL_B.d122 * ContModelSIL_B.D15_tmp_g) + ContModelSIL_B.d158 *
    0.0 * ContModelSIL_B.D15_tmp_g) + ContModelSIL_B.d157 * 0.0 *
                        ContModelSIL_B.D15_tmp_g) + ContModelSIL_B.tmp_tmp_oi;
  ContModelSIL_B.tmp_tmp_jr = ContModelSIL_B.d26 * ContModelSIL_B.D46_tmp_n;
  ContModelSIL_B.tmp_tmp_c2 = ContModelSIL_B.tmp_tmp_ik *
    ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.tmp_tmp_hp = ContModelSIL_B.tmp_tmp_gs *
    ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.tmp_tmp_da = ContModelSIL_B.tmp_tmp_nn *
    ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.tmp_tmp_pw = ContModelSIL_B.d53 * ContModelSIL_B.D56_tmp_bj;
  ContModelSIL_B.tmp_tmp_j = ContModelSIL_B.d54 * ContModelSIL_B.D46_tmp_tmp_c;
  ContModelSIL_B.tmp_tmp_e = ContModelSIL_B.d26 * ContModelSIL_B.D46_tmp_p;
  ContModelSIL_B.tmp_tmp_ch = ContModelSIL_B.d54 * ContModelSIL_B.D56_tmp_tmp_g;
  ContModelSIL_B.tmp_tmp_b = ContModelSIL_B.tmp_tmp_l * ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.tmp_tmp_er = ContModelSIL_B.tmp_tmp_ce *
    ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.tmp_tmp_c5 = ContModelSIL_B.tmp_tmp_nc *
    ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.tmp_tmp_mv = ContModelSIL_B.D16_tmp * 0.00046501 *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.tmp_tmp_m0 = ContModelSIL_B.D16_tmp * 0.0003034 *
    ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d132 = 0.0262846592 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.142;
  ContModelSIL_B.tmp_tmp_jg = ContModelSIL_B.d132 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d134 = 0.0191844872 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.143;
  ContModelSIL_B.tmp_tmp_f = ContModelSIL_B.d134 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.d135 = ContModelSIL_B.D16_tmp * 0.028900000000000006 * 0.143;
  ContModelSIL_B.tmp_tmp_a = ContModelSIL_B.d135 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.tmp_tmp_g = ContModelSIL_B.d42 * ContModelSIL_B.D46_tmp_l;
  ContModelSIL_B.tmp_tmp_ik *= ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_gs *= ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_nn *= ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_nr = ContModelSIL_B.d53 * ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_na = ContModelSIL_B.d54 * ContModelSIL_B.D46_tmp_tmp_d;
  ContModelSIL_B.d69 = ContModelSIL_B.d42 * ContModelSIL_B.D46_tmp_j;
  ContModelSIL_B.d70 = ContModelSIL_B.d54 * ContModelSIL_B.D56_tmp_tmp_i;
  ContModelSIL_B.tmp_tmp_l *= ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.tmp_tmp_ce *= ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.tmp_tmp_nc *= ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.d71 = ContModelSIL_B.tmp_tmp_p * ContModelSIL_B.D17_tmp_c;
  ContModelSIL_B.d72 = ContModelSIL_B.tmp_tmp_dk * ContModelSIL_B.D17_tmp_c;
  ContModelSIL_B.d38 *= ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d39 *= ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d40 *= ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.tmp_tmp_c *= ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.tmp_tmp_p *= ContModelSIL_B.D34_tmp;
  ContModelSIL_B.tmp_tmp_dk *= ContModelSIL_B.D34_tmp;
  ContModelSIL_B.d73 = ContModelSIL_B.D27_tmp_k * 0.0 * ContModelSIL_B.D34_tmp;
  ContModelSIL_B.tmp_tmp_n *= ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.tmp_tmp_i *= ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.tmp_tmp_m *= ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.d31 *= ContModelSIL_B.D28;
  ContModelSIL_B.d75 = ContModelSIL_B.d26 * ContModelSIL_B.D46_tmp_d;
  ContModelSIL_B.d76 = ContModelSIL_B.d26 * ContModelSIL_B.D56_tmp_l;
  ContModelSIL_B.d77 = ContModelSIL_B.d26 * ContModelSIL_B.D46_tmp_dh;
  ContModelSIL_B.d78 = ContModelSIL_B.d26 * ContModelSIL_B.D56_tmp_d;
  ContModelSIL_B.d79 = ContModelSIL_B.d42 * ContModelSIL_B.D46_tmp_o;
  ContModelSIL_B.d80 = ContModelSIL_B.d26 * ContModelSIL_B.D56_tmp_n;
  ContModelSIL_B.d81 = ContModelSIL_B.d42 * ContModelSIL_B.D46_tmp_b;
  ContModelSIL_B.d82 = ContModelSIL_B.d26 * ContModelSIL_B.D56_tmp_ln;
  ContModelSIL_B.d133 = ContModelSIL_B.D14_tmp_md * 0.142;
  ContModelSIL_B.D14_tmp_md *= 0.143;
  ContModelSIL_B.dv[28] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((ContModelSIL_B.d47 * ContModelSIL_B.D56_tmp_tmp_h + ContModelSIL_B.d12) -
    ContModelSIL_B.tmp_tmp_o * ContModelSIL_B.D56_tmp_tmp_h) +
    ContModelSIL_B.tmp_tmp_d * ContModelSIL_B.D56_tmp_tmp_h) +
    ContModelSIL_B.d46 * ContModelSIL_B.D56_tmp_tmp_h) + ContModelSIL_B.d52 *
    ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.d43 *
    ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.tmp_tmp_jr) +
    ContModelSIL_B.d52 * ContModelSIL_B.D27) + ContModelSIL_B.d43 *
    ContModelSIL_B.D27) - ContModelSIL_B.tmp_tmp_c2) + ContModelSIL_B.tmp_tmp_hp)
    + ContModelSIL_B.tmp_tmp_da) + ContModelSIL_B.tmp_tmp_pw) +
    ContModelSIL_B.tmp_tmp_j) + ContModelSIL_B.d44 *
    ContModelSIL_B.D46_tmp_tmp_a) + ContModelSIL_B.tmp_tmp_e) +
    ContModelSIL_B.d44 * ContModelSIL_B.D56_tmp_tmp_iz) +
    ContModelSIL_B.tmp_tmp_ch) - ContModelSIL_B.tmp_tmp_b) +
    ContModelSIL_B.tmp_tmp_er) + ContModelSIL_B.tmp_tmp_c5) +
    ContModelSIL_B.tmp_tmp_mv) + ContModelSIL_B.tmp_tmp_m0) +
    ContModelSIL_B.D16_tmp * 0.0393748 * ContModelSIL_B.x_tmp_p) +
    ContModelSIL_B.tmp_tmp_jg) + ContModelSIL_B.d133 * ContModelSIL_B.x_tmp_p) +
    ContModelSIL_B.tmp_tmp_f) + ContModelSIL_B.D14_tmp_md *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.tmp_tmp_a) + ContModelSIL_B.d47 *
    ContModelSIL_B.D56_tmp_tmp_g2) - ContModelSIL_B.tmp_tmp_o *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.tmp_tmp_d *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d46 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d52 *
    ContModelSIL_B.D46_tmp_tmp_e) + ContModelSIL_B.d43 *
    ContModelSIL_B.D46_tmp_tmp_e) + ContModelSIL_B.tmp_tmp_g) +
    ContModelSIL_B.d52 * ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.d43 *
    ContModelSIL_B.D56_tmp_tmp_fi) - ContModelSIL_B.tmp_tmp_ik) +
    ContModelSIL_B.tmp_tmp_gs) + ContModelSIL_B.tmp_tmp_nn) +
    ContModelSIL_B.tmp_tmp_nr) + ContModelSIL_B.tmp_tmp_na) + ContModelSIL_B.d44
    * ContModelSIL_B.D46_tmp_tmp_af) + ContModelSIL_B.d69) + ContModelSIL_B.d44 *
    ContModelSIL_B.D56_tmp_tmp_c) + ContModelSIL_B.d70) -
    ContModelSIL_B.tmp_tmp_l) + ContModelSIL_B.tmp_tmp_ce) +
    ContModelSIL_B.tmp_tmp_nc) + ContModelSIL_B.d35 * ContModelSIL_B.D17) +
    ContModelSIL_B.d36 * ContModelSIL_B.D17) + ContModelSIL_B.d37 *
    ContModelSIL_B.D17) + ContModelSIL_B.d28 * ContModelSIL_B.D17) +
    ContModelSIL_B.d71) + ContModelSIL_B.d72) + ContModelSIL_B.d38) +
    ContModelSIL_B.d39) + ContModelSIL_B.d40) + ContModelSIL_B.tmp_tmp_c) +
                        ContModelSIL_B.d30 * ContModelSIL_B.D18) +
                       ContModelSIL_B.tmp_tmp * ContModelSIL_B.D18) +
                      ContModelSIL_B.tmp_tmp_p) + ContModelSIL_B.tmp_tmp_dk) +
                    ContModelSIL_B.d73) + ContModelSIL_B.tmp_tmp_n) +
                  ContModelSIL_B.tmp_tmp_i) + ContModelSIL_B.tmp_tmp_m) +
                ContModelSIL_B.d33 * ContModelSIL_B.D56_tmp_tmp_a) +
               ContModelSIL_B.d31) + ContModelSIL_B.d75) + ContModelSIL_B.d76) +
            ContModelSIL_B.d77) + ContModelSIL_B.d78) + ContModelSIL_B.d79) +
         ContModelSIL_B.d80) + ContModelSIL_B.d81) + ContModelSIL_B.d82) * 0.25);
  ContModelSIL_B.d28 = 0.0 * ContModelSIL_B.rtb_ginv_tmp_n + 0.0 *
    ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.d30 = -0.004761842800000001 * ContModelSIL_B.D28;
  ContModelSIL_B.tmp_tmp = 2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [7];
  ContModelSIL_B.d33 = 0.0013531005056 * ContModelSIL_B.smax;
  ContModelSIL_B.d35 = 0.0020206472 * ContModelSIL_B.D18;
  ContModelSIL_B.d36 = 0.0011641305103999998 * ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.d37 = 0.0011641305103999998 * ContModelSIL_B.D56_tmp_tmp_a;
  ContModelSIL_B.d46 = (0.0011641305103999998 * ContModelSIL_B.x_tmp +
                        0.0023809214000000004 * ContModelSIL_B.D15_tmp) +
    0.0016404808348 * ContModelSIL_B.D15_tmp_g;
  ContModelSIL_B.dv[36] = -((((((((((((((((((ContModelSIL_B.d28 -
    ContModelSIL_B.D14_tmp_p) + ContModelSIL_B.D14_tmp_ms) - ContModelSIL_B.d10)
    - ContModelSIL_B.d11) + ContModelSIL_B.D16_tmp_p) - ContModelSIL_B.d13) -
    ContModelSIL_B.d15) - ContModelSIL_B.D16_tmp_i) + -0.0027062010112 *
    ContModelSIL_B.D18) + -0.0040412944 * ContModelSIL_B.D18) +
    ContModelSIL_B.d22) - ContModelSIL_B.D14_tmp_m) -
    ContModelSIL_B.rtb_ginv_tmp_e) + -0.0023282610207999996 *
    ContModelSIL_B.D56_tmp_tmp_a) + ContModelSIL_B.d30) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] + (-2.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7] * ContModelSIL_B.d46 *
    ContModelSIL_B.D34_tmp + ContModelSIL_B.tmp_tmp * 0.0 *
    ContModelSIL_B.D46_tmp_da)) + ((((((((((((((ContModelSIL_B.d28 -
    ContModelSIL_B.d33) + -0.0020206472 * ContModelSIL_B.smax) +
    ContModelSIL_B.D16_tmp_p) - ContModelSIL_B.d13) - ContModelSIL_B.d15) -
    ContModelSIL_B.D16_tmp_i) + -0.0013531005056 * ContModelSIL_B.D18) -
    ContModelSIL_B.d35) - ContModelSIL_B.d36) + ContModelSIL_B.d22) -
    ContModelSIL_B.D14_tmp_m) - ContModelSIL_B.rtb_ginv_tmp_e) -
    ContModelSIL_B.d37) + ContModelSIL_B.d30) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6]) * 0.5);
  ContModelSIL_B.D14_tmp_p = 0.0011641305103999998 *
    ContModelSIL_B.D46_tmp_tmp_a;
  ContModelSIL_B.D14_tmp_ms = 0.0011641305103999998 *
    ContModelSIL_B.D56_tmp_tmp_iz;
  ContModelSIL_B.d10 = 0.0011641305103999998 * ContModelSIL_B.D46_tmp_tmp_af;
  ContModelSIL_B.d11 = 0.0011641305103999998 * ContModelSIL_B.D56_tmp_tmp_c;
  ContModelSIL_B.d28 = 0.0033737477055999993 * ContModelSIL_B.D46_tmp_tmp_ei +
    ContModelSIL_B.D16_tmp_pt;
  ContModelSIL_B.d30 = 0.0013531005056 * ContModelSIL_B.D46_tmp_tmp_e;
  ContModelSIL_B.d47 = 0.0020206472 * ContModelSIL_B.D46_tmp_tmp_e;
  ContModelSIL_B.tmp_tmp_o = (0.0023809214000000004 *
    ContModelSIL_B.D46_tmp_tmp_c + ContModelSIL_B.D14_tmp_p) +
    ContModelSIL_B.D46_tmp_tmp_f;
  ContModelSIL_B.tmp_tmp_d = 0.0023809214000000004 *
    ContModelSIL_B.D46_tmp_tmp_d;
  ContModelSIL_B.d177 = (0.0013531005056 * ContModelSIL_B.D27 +
    ContModelSIL_B.d28) + 0.0020206472 * ContModelSIL_B.D27;
  ContModelSIL_B.d178 = 0.0013531005056 * ContModelSIL_B.D56_tmp_tmp_fi;
  ContModelSIL_B.d179 = 0.0020206472 * ContModelSIL_B.D56_tmp_tmp_fi;
  ContModelSIL_B.D27_tmp =
    (((((((((((((((((((((((((((((((((((((((((ContModelSIL_B.d177 -
    ContModelSIL_B.D27_tmp) + ContModelSIL_B.D14_tmp) + ContModelSIL_B.d21) +
    ContModelSIL_B.d23) + ContModelSIL_B.d24) + ContModelSIL_B.D14_tmp_p) +
    ContModelSIL_B.D46_tmp_tmp_f) + ContModelSIL_B.D14_tmp_ms) +
    ContModelSIL_B.D14_tmp_g) - ContModelSIL_B.D14_tmp_cz) +
    ContModelSIL_B.D14_tmp_tmp_m) + ContModelSIL_B.D14_tmp_tmp_c) +
    ContModelSIL_B.D14_tmp_m3) + ContModelSIL_B.D15_tmp_tmp_i) +
    ContModelSIL_B.D15_tmp_tmp_o) + ContModelSIL_B.D16_tmp_tmp) +
    ContModelSIL_B.D34_tmp_n) + ContModelSIL_B.d30) + ContModelSIL_B.d47) +
    ContModelSIL_B.D37_tmp) + ContModelSIL_B.d178) + ContModelSIL_B.d179) -
                       ContModelSIL_B.rtb_ginv_tmp_b) + ContModelSIL_B.d56) +
                     ContModelSIL_B.d57) + ContModelSIL_B.d58) +
                   ContModelSIL_B.d59) + ContModelSIL_B.d10) +
                 ContModelSIL_B.d60) + ContModelSIL_B.d11) + ContModelSIL_B.d61)
              - ContModelSIL_B.d62) + ContModelSIL_B.d63) + ContModelSIL_B.d64)
           + ContModelSIL_B.D46_tmp_mj) + ContModelSIL_B.d65) +
         ContModelSIL_B.D46_tmp_c) + ContModelSIL_B.d66) +
       ContModelSIL_B.D56_tmp_h) + ContModelSIL_B.d67) +
     ContModelSIL_B.D56_tmp_m) + ContModelSIL_B.d68;
  ContModelSIL_B.d183 = ((((((((((((((((((ContModelSIL_B.tmp_tmp_o +
    ContModelSIL_B.D14_tmp_ms) + 0.0023809214000000004 *
    ContModelSIL_B.D56_tmp_tmp_g) - ContModelSIL_B.D14_tmp_cz) +
    ContModelSIL_B.D14_tmp_tmp_m) + ContModelSIL_B.D14_tmp_tmp_c) +
    ContModelSIL_B.D15_tmp_tmp_i) + ContModelSIL_B.D16_tmp_tmp) +
    ContModelSIL_B.tmp_tmp_d) + ContModelSIL_B.d10) + ContModelSIL_B.d60) +
    ContModelSIL_B.d11) + 0.0023809214000000004 * ContModelSIL_B.D56_tmp_tmp_i)
    - ContModelSIL_B.d62) + ContModelSIL_B.d63) + ContModelSIL_B.d64) +
    ContModelSIL_B.D46_tmp_c) + ContModelSIL_B.d66) + ContModelSIL_B.D56_tmp_m)
    + ContModelSIL_B.d68;
  ContModelSIL_B.dv[44] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((0.0 *
    ContModelSIL_B.D68 + 0.0 * ContModelSIL_B.d) + 0.0 * ContModelSIL_B.d1) +
    0.0 * ContModelSIL_B.D46_tmp_tmp_l) + -0.0 * ContModelSIL_B.d2) + -0.0 *
    ContModelSIL_B.D46_tmp_tmp_o2) + 0.0 * ContModelSIL_B.d3) + 0.0 *
    ContModelSIL_B.d4) + -0.004761842800000001 * ContModelSIL_B.D46_tmp_tmp) +
    -0.0027062010112 * ContModelSIL_B.d5) + -0.0040412944 * ContModelSIL_B.d5) +
    -0.0 * ContModelSIL_B.D67) + -0.0027062010112 * ContModelSIL_B.D56_tmp_tmp_f)
    + -0.0040412944 * ContModelSIL_B.D56_tmp_tmp_f) + -0.004761842800000001 *
    ContModelSIL_B.d8) + -0.0023282610207999996 * ContModelSIL_B.D37) + -0.0 *
    ContModelSIL_B.rtb_ginv_tmp_ol) + -0.0023282610207999996 *
    ContModelSIL_B.D56_tmp_tmp_ff) + 0.06214814 * ContModelSIL_B.d6) + 5.484E-5 *
    ContModelSIL_B.D38) - 0.00050874 * ContModelSIL_B.D38) -
    0.0018662108031999999 * ContModelSIL_B.D38) - 0.0041327000000000004 *
    ContModelSIL_B.D38) + 8.085E-5 * ContModelSIL_B.D47) - 0.00034964 *
    ContModelSIL_B.D47) + -0.0013716908347999998 * ContModelSIL_B.D47) +
    -0.00010968 * ContModelSIL_B.D46_tmp) + -0.00101748 * ContModelSIL_B.D46_tmp)
    + 0.00186004 * ContModelSIL_B.D46_tmp) + -0.0001617 * ContModelSIL_B.D46_tmp)
    + -0.00069928 * ContModelSIL_B.D46_tmp) + 0.0012136 * ContModelSIL_B.D46_tmp)
    + 0.1574992 * ContModelSIL_B.D46_tmp) + -0.0808631 * ContModelSIL_B.D46_tmp)
    + -0.12429628 * ContModelSIL_B.D46_tmp) + 0.0037324216063999997 *
    ContModelSIL_B.D46_tmp) + 0.0019621373695999996 * ContModelSIL_B.D46_tmp) +
    0.0027433816695999996 * ContModelSIL_B.D46_tmp) + 0.0019759552383999996 *
    ContModelSIL_B.D46_tmp) + 0.008265400000000001 * ContModelSIL_B.D46_tmp) +
    0.04043155 * ContModelSIL_B.D48_tmp) + 0.0009810686847999998 *
    ContModelSIL_B.D48_tmp) + 0.0009879776191999998 * ContModelSIL_B.D48_tmp) +
    0.04043155 * ContModelSIL_B.D58) - 0.06214814 * ContModelSIL_B.D58) +
    0.0009810686847999998 * ContModelSIL_B.D58) + 0.0009879776191999998 *
    ContModelSIL_B.D58) - 5.484E-5 * ContModelSIL_B.y_a) + 0.00050874 *
                       ContModelSIL_B.y_a) + 0.0018662108031999999 *
                      ContModelSIL_B.y_a) + 0.0041327000000000004 *
                     ContModelSIL_B.y_a) - 8.085E-5 * ContModelSIL_B.ab_a) +
                   0.00034964 * ContModelSIL_B.ab_a) + 0.0013716908347999998 *
                  ContModelSIL_B.ab_a) + 0.0027062010112 * ContModelSIL_B.d7) +
                0.0040412944 * ContModelSIL_B.d7) + -0.0 *
               ContModelSIL_B.D15_tmp_tmp) + 0.004761842800000001 *
              ContModelSIL_B.d9) + 0.0023282610207999996 *
             ContModelSIL_B.D14_tmp_tmp) + -0.0 * ContModelSIL_B.D15_tmp_tmp_a)
           + 0.0027062010112 * ContModelSIL_B.rtb_ginv_tmp_tmp_p4) +
          0.0040412944 * ContModelSIL_B.rtb_ginv_tmp_tmp_p4) +
         0.0023282610207999996 * ContModelSIL_B.D56_tmp_tmp) +
        0.004761842800000001 * ContModelSIL_B.D46_tmp_tmp_o) * (-0.5 *
        ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) +
       ((ContModelSIL_B.D27_tmp *
         ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] + ContModelSIL_B.d183
         * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7]) +
        ContModelSIL_B.d55 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3]))
      * 0.25);
  ContModelSIL_B.D38 = 0.11464 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5] * 0.08312 * 0.142;
  ContModelSIL_B.D48_tmp = ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.08312 * 0.17 * 0.143;
  ContModelSIL_B.D58 = 0.09794 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5];
  ContModelSIL_B.ab_a = ContModelSIL_B.D58 * 0.08312 * 0.143;
  ContModelSIL_B.d6 = -0.22928 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [4] * 0.08312 * 0.142;
  ContModelSIL_B.d55 = ContModelSIL_B.d27 * 0.08312 * 0.17 * 0.143;
  ContModelSIL_B.d87 = -0.19588 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.d74 = ContModelSIL_B.d87 * 0.08312 * 0.143;
  ContModelSIL_B.d83 = ContModelSIL_B.ab_a * ContModelSIL_B.D46_tmp_tmp_a;
  ContModelSIL_B.d84 = ContModelSIL_B.ab_a * ContModelSIL_B.D56_tmp_tmp_iz;
  ContModelSIL_B.d85 = ContModelSIL_B.ab_a * ContModelSIL_B.D46_tmp_tmp_af;
  ContModelSIL_B.d86 = ContModelSIL_B.ab_a * ContModelSIL_B.D56_tmp_tmp_c;
  ContModelSIL_B.d88 = ContModelSIL_B.d74 * ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.d89 = ContModelSIL_B.d74 * ContModelSIL_B.D56_tmp_tmp_a;
  ContModelSIL_B.dv[52] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((ContModelSIL_B.D38
    * ContModelSIL_B.D46_tmp_tmp_ei + ContModelSIL_B.d12) +
    ContModelSIL_B.D48_tmp * ContModelSIL_B.D46_tmp_tmp_ei) +
    ContModelSIL_B.tmp_tmp_jr) + ContModelSIL_B.D38 * ContModelSIL_B.D27) +
    ContModelSIL_B.D48_tmp * ContModelSIL_B.D27) - ContModelSIL_B.tmp_tmp_c2) +
    ContModelSIL_B.tmp_tmp_hp) + ContModelSIL_B.tmp_tmp_da) +
    ContModelSIL_B.tmp_tmp_pw) + ContModelSIL_B.tmp_tmp_j) + ContModelSIL_B.d83)
    + ContModelSIL_B.tmp_tmp_e) + ContModelSIL_B.d84) +
    ContModelSIL_B.tmp_tmp_ch) - ContModelSIL_B.tmp_tmp_b) +
    ContModelSIL_B.tmp_tmp_er) + ContModelSIL_B.tmp_tmp_c5) +
    ContModelSIL_B.tmp_tmp_mv) + ContModelSIL_B.tmp_tmp_m0) +
    ContModelSIL_B.tmp_tmp_jg) + ContModelSIL_B.tmp_tmp_f) +
    ContModelSIL_B.tmp_tmp_a) + ContModelSIL_B.D38 *
    ContModelSIL_B.D46_tmp_tmp_e) + ContModelSIL_B.D48_tmp *
    ContModelSIL_B.D46_tmp_tmp_e) + ContModelSIL_B.tmp_tmp_g) +
    ContModelSIL_B.D38 * ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.D48_tmp
    * ContModelSIL_B.D56_tmp_tmp_fi) - ContModelSIL_B.tmp_tmp_ik) +
    ContModelSIL_B.tmp_tmp_gs) + ContModelSIL_B.tmp_tmp_nn) +
    ContModelSIL_B.tmp_tmp_nr) + ContModelSIL_B.tmp_tmp_na) + ContModelSIL_B.d85)
    + ContModelSIL_B.d69) + ContModelSIL_B.d86) + ContModelSIL_B.d70) -
    ContModelSIL_B.tmp_tmp_l) + ContModelSIL_B.tmp_tmp_ce) +
    ContModelSIL_B.tmp_tmp_nc) + ContModelSIL_B.d6 * ContModelSIL_B.smax) +
    ContModelSIL_B.d55 * ContModelSIL_B.smax) + ContModelSIL_B.d71) +
    ContModelSIL_B.d72) + ContModelSIL_B.d38) + ContModelSIL_B.d39) +
    ContModelSIL_B.d40) + ContModelSIL_B.tmp_tmp_c) + ContModelSIL_B.d6 *
    ContModelSIL_B.D18) + ContModelSIL_B.d55 * ContModelSIL_B.D18) +
                       ContModelSIL_B.d88) + ContModelSIL_B.tmp_tmp_p) +
                     ContModelSIL_B.tmp_tmp_dk) + ContModelSIL_B.d73) +
                   ContModelSIL_B.tmp_tmp_n) + ContModelSIL_B.tmp_tmp_i) +
                 ContModelSIL_B.tmp_tmp_m) + ContModelSIL_B.d89) +
               ContModelSIL_B.d31) + ContModelSIL_B.d75) + ContModelSIL_B.d76) +
            ContModelSIL_B.d77) + ContModelSIL_B.d78) + ContModelSIL_B.d79) +
         ContModelSIL_B.d80) + ContModelSIL_B.d81) + ContModelSIL_B.d82) * 0.25);
  ContModelSIL_B.D58 = ContModelSIL_B.D58 * 0.17 * 0.143;
  ContModelSIL_B.d12 = ContModelSIL_B.d87 * 0.17 * 0.143;
  ContModelSIL_B.dv[60] = -((((((((((((((((((((((((((((((((((ContModelSIL_B.d18 *
    4.0 * 0.0 * ContModelSIL_B.D15_tmp_g + ContModelSIL_B.tmp_tmp_oi) +
    ContModelSIL_B.D58 * ContModelSIL_B.D46_tmp_tmp_c) + ContModelSIL_B.d83) +
    ContModelSIL_B.tmp_tmp_e) + ContModelSIL_B.d84) + ContModelSIL_B.D58 *
    ContModelSIL_B.D56_tmp_tmp_g) - ContModelSIL_B.tmp_tmp_b) +
    ContModelSIL_B.tmp_tmp_er) + ContModelSIL_B.tmp_tmp_c5) +
    ContModelSIL_B.tmp_tmp_m0) + ContModelSIL_B.tmp_tmp_f) + ContModelSIL_B.D58 *
    ContModelSIL_B.D46_tmp_tmp_d) + ContModelSIL_B.d85) + ContModelSIL_B.d69) +
    ContModelSIL_B.d86) + ContModelSIL_B.D58 * ContModelSIL_B.D56_tmp_tmp_i) -
    ContModelSIL_B.tmp_tmp_l) + ContModelSIL_B.tmp_tmp_ce) +
    ContModelSIL_B.tmp_tmp_nc) + ContModelSIL_B.d12 * ContModelSIL_B.s) +
    ContModelSIL_B.d88) + ContModelSIL_B.tmp_tmp_p) + ContModelSIL_B.tmp_tmp_dk)
    + ContModelSIL_B.d73) + ContModelSIL_B.tmp_tmp_n) + ContModelSIL_B.tmp_tmp_i)
    + ContModelSIL_B.tmp_tmp_m) + ContModelSIL_B.d89) + ContModelSIL_B.d12 *
    ContModelSIL_B.D28) + ContModelSIL_B.d77) + ContModelSIL_B.d78) +
    ContModelSIL_B.d81) + ContModelSIL_B.d82) * 0.25);
  ContModelSIL_B.d18 = -0.0 * ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.d31 = -0.004761842800000001 * ContModelSIL_B.D46_tmp_o4;
  ContModelSIL_B.d38 = -0.0 * ContModelSIL_B.D46_tmp_m;
  ContModelSIL_B.d39 = 8.085E-5 * ContModelSIL_B.D56_tmp_ln;
  ContModelSIL_B.d40 = ContModelSIL_B.tmp_tmp_o - ContModelSIL_B.tmp_tmp_d;
  ContModelSIL_B.d28 = ((((((((((ContModelSIL_B.d28 + ContModelSIL_B.D14_tmp_p)
    + ContModelSIL_B.D46_tmp_tmp_f) - ContModelSIL_B.d30) - ContModelSIL_B.d47)
    + ContModelSIL_B.D46_tmp_lm) - ContModelSIL_B.d10) +
    ContModelSIL_B.D46_tmp_mv) + ContModelSIL_B.D46_tmp_mj) +
    ContModelSIL_B.D46_tmp_c) + ContModelSIL_B.D46_tmp_h3) +
    ContModelSIL_B.D46_tmp_k;
  ContModelSIL_B.dv[29] = -(((((((((((((((((((((0.049482857942000004 -
    -0.019747543696 * ContModelSIL_B.rtb_ginv_tmp_o) +
    ContModelSIL_B.rtb_ginv_tmp_jd) + 5.484E-5 * ContModelSIL_B.rtb_ginv_tmp_n)
    - ContModelSIL_B.rtb_ginv_tmp_k) - ContModelSIL_B.rtb_ginv_tmp_p) -
    ContModelSIL_B.rtb_ginv_tmp_bp) + -0.0027062010112 * ContModelSIL_B.D24_tmp)
    + -0.0040412944 * ContModelSIL_B.D24_tmp) + ContModelSIL_B.D47_tmp_a) +
    ContModelSIL_B.rtb_ginv_tmp_ek) + ContModelSIL_B.D15) - ContModelSIL_B.D25)
    - ContModelSIL_B.D14) + -0.0023282610207999996 * ContModelSIL_B.rtb_ginv_tmp)
    + ContModelSIL_B.d31) + ContModelSIL_B.d38) + ContModelSIL_B.d18) *
    ContModelSIL_B.d27 + ContModelSIL_B.D45 * ContModelSIL_B.tmp_tmp_nm) +
    (((ContModelSIL_B.D56_tmp - ContModelSIL_B.d39) + ContModelSIL_B.D46_tmp_o3)
     + ContModelSIL_B.D56_tmp_ad) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) * ContModelSIL_B.x_tmp_p
    + (((((-0.0011641305103999998 * ContModelSIL_B.D46_tmp_tmp_af +
           ContModelSIL_B.d40) + ContModelSIL_B.D46_tmp_mv) +
         ContModelSIL_B.D46_tmp_c) + ContModelSIL_B.D46_tmp_k) *
       ContModelSIL_B.tmp_tmp + ContModelSIL_B.d28 * ContModelSIL_B.d20)) * 0.25);
  ContModelSIL_B.tmp_tmp = 2.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [3];
  ContModelSIL_B.tmp_tmp_c = ContModelSIL_B.tmp_tmp * 0.0069089343999999995;
  ContModelSIL_B.D15_tmp_g = -0.39176 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelSIL_B.D45 = 0.39176 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [3];
  ContModelSIL_B.tmp_tmp_n = ContModelSIL_B.d95 * 0.0069089343999999995;
  ContModelSIL_B.tmp_tmp_i = ContModelSIL_B.tmp_tmp * 0.04043155;
  ContModelSIL_B.tmp_tmp_m = ContModelSIL_B.d91 * 0.06214814;
  ContModelSIL_B.tmp_tmp_j = ContModelSIL_B.tmp_tmp_c * 0.142;
  ContModelSIL_B.tmp_tmp_c *= 0.143;
  ContModelSIL_B.tmp_tmp_e = ContModelSIL_B.d14 * 0.0069089343999999995;
  ContModelSIL_B.D46_tmp_lm = -0.45856 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.08312 * 0.142;
  ContModelSIL_B.D56_tmp = ContModelSIL_B.d95 * 0.08312 * 0.17 * 0.143;
  ContModelSIL_B.rtb_ginv_tmp_o = 0.45856 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.08312 * 0.142;
  ContModelSIL_B.rtb_ginv_tmp_jd = ContModelSIL_B.tmp_tmp_nm * 0.08312 * 0.17 *
    0.143;
  ContModelSIL_B.tmp_tmp_mv = ContModelSIL_B.d91 * 5.484E-5;
  ContModelSIL_B.tmp_tmp_m0 = ContModelSIL_B.tmp_tmp * 0.00050874;
  ContModelSIL_B.tmp_tmp_jg = 0.0262846592 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.142;
  ContModelSIL_B.tmp_tmp_f = ContModelSIL_B.tmp_tmp * 0.028900000000000006 *
    0.143;
  ContModelSIL_B.rtb_ginv_tmp_ek = ContModelSIL_B.D15_tmp_g * 0.17 * 0.143;
  ContModelSIL_B.D15_tmp_g = ContModelSIL_B.D15_tmp_g * 0.08312 * 0.143;
  ContModelSIL_B.rtb_ginv_tmp_k = ContModelSIL_B.D45 * 0.08312 * 0.143;
  ContModelSIL_B.D45 = ContModelSIL_B.D45 * 0.17 * 0.143;
  ContModelSIL_B.tmp_tmp_a = 0.39176 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.tmp_tmp_g = ContModelSIL_B.d91 * 8.085E-5;
  ContModelSIL_B.tmp_tmp *= 0.00034964;
  ContModelSIL_B.tmp_tmp_nr = 0.0191844872 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143;
  ContModelSIL_B.tmp_tmp_na = 0.0011641305103999998 *
    ContModelSIL_B.rtb_ginv_tmp;
  ContModelSIL_B.rtb_ginv_tmp = ContModelSIL_B.tmp_tmp_h * 0.0;
  ContModelSIL_B.rtb_ginv_tmp_p = ContModelSIL_B.d27 * 5.484E-5;
  ContModelSIL_B.rtb_ginv_tmp_bp = ContModelSIL_B.d14 * 0.00050874;
  ContModelSIL_B.tmp_tmp_h = 0.0262846592 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142;
  ContModelSIL_B.tmp_tmp_nm = ContModelSIL_B.d14 * 0.028900000000000006 * 0.143;
  ContModelSIL_B.tmp_tmp_o = ContModelSIL_B.tmp_tmp_a * 0.17 * 0.143;
  ContModelSIL_B.tmp_tmp_ch = ContModelSIL_B.d27 * 8.085E-5;
  ContModelSIL_B.tmp_tmp_b = ContModelSIL_B.d14 * 0.00034964;
  ContModelSIL_B.tmp_tmp_er = 0.0191844872 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143;
  ContModelSIL_B.tmp_tmp_d = ContModelSIL_B.D46_tmp_lm *
    ContModelSIL_B.D46_tmp_tmp_e;
  ContModelSIL_B.tmp_tmp_ik = ContModelSIL_B.D56_tmp *
    ContModelSIL_B.D46_tmp_tmp_e;
  ContModelSIL_B.tmp_tmp_gs = ContModelSIL_B.d42 * ContModelSIL_B.d2;
  ContModelSIL_B.tmp_tmp_nn = ContModelSIL_B.rtb_ginv_tmp_p *
    ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_l = ContModelSIL_B.rtb_ginv_tmp_bp *
    ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_ce = ContModelSIL_B.tmp_tmp_h *
    ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_nc = ContModelSIL_B.tmp_tmp_nm *
    ContModelSIL_B.D56_tmp_f;
  ContModelSIL_B.tmp_tmp_p = ContModelSIL_B.D15_tmp_g *
    ContModelSIL_B.D46_tmp_tmp_af;
  ContModelSIL_B.tmp_tmp_dk = ContModelSIL_B.d42 * ContModelSIL_B.D46_tmp_tmp_o2;
  ContModelSIL_B.tmp_tmp_oi = ContModelSIL_B.tmp_tmp_o *
    ContModelSIL_B.D56_tmp_tmp_i;
  ContModelSIL_B.tmp_tmp_jr = ContModelSIL_B.tmp_tmp_ch *
    ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.tmp_tmp_c2 = ContModelSIL_B.tmp_tmp_b *
    ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.tmp_tmp_hp = ContModelSIL_B.tmp_tmp_er *
    ContModelSIL_B.D56_tmp_a;
  ContModelSIL_B.tmp_tmp_da = ContModelSIL_B.d16 * 5.484E-5;
  ContModelSIL_B.tmp_tmp_c5 = ContModelSIL_B.d16 * 8.085E-5;
  ContModelSIL_B.tmp_tmp_pw = ContModelSIL_B.rtb_ginv_tmp_ek *
    ContModelSIL_B.D46_tmp_tmp_d;
  ContModelSIL_B.D46_tmp_lm *= ContModelSIL_B.D46_tmp_tmp_ei;
  ContModelSIL_B.D56_tmp *= ContModelSIL_B.D46_tmp_tmp_ei;
  ContModelSIL_B.D15_tmp_g *= ContModelSIL_B.D46_tmp_tmp_a;
  ContModelSIL_B.rtb_ginv_tmp_ek *= ContModelSIL_B.D46_tmp_tmp_c;
  ContModelSIL_B.D46_tmp_tmp_o2 = ContModelSIL_B.d53 * ContModelSIL_B.y_a;
  ContModelSIL_B.d2 = ContModelSIL_B.d41 * ContModelSIL_B.D56_tmp_n;
  ContModelSIL_B.d20 = ContModelSIL_B.d41 * ContModelSIL_B.D56_tmp_ln;
  ContModelSIL_B.d91 = ContModelSIL_B.d54 * ContModelSIL_B.D46_tmp_tmp_o;
  tmp =
    (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((((((((((((((((ContModelSIL_B.d25 *
    ContModelSIL_B.D68 + ContModelSIL_B.d25 * ContModelSIL_B.d) +
    ContModelSIL_B.tmp_tmp_i * ContModelSIL_B.D56_tmp_tmp_h) +
    ContModelSIL_B.d90) + ContModelSIL_B.tmp_tmp_m *
    ContModelSIL_B.D56_tmp_tmp_h) + ContModelSIL_B.d92) +
    ContModelSIL_B.tmp_tmp_j * ContModelSIL_B.D56_tmp_tmp_h) +
    ContModelSIL_B.d93) + ContModelSIL_B.tmp_tmp_c *
    ContModelSIL_B.D56_tmp_tmp_h) + ContModelSIL_B.d94) +
    ContModelSIL_B.D46_tmp_lm) + ContModelSIL_B.D56_tmp) + ContModelSIL_B.d96) +
    ContModelSIL_B.d97) + ContModelSIL_B.rtb_ginv_tmp_o * ContModelSIL_B.D27) +
    ContModelSIL_B.d98) + ContModelSIL_B.rtb_ginv_tmp_jd * ContModelSIL_B.D27) +
    ContModelSIL_B.d99) + ContModelSIL_B.tmp_tmp_mv * ContModelSIL_B.D56_tmp_bj)
    + ContModelSIL_B.d100) + ContModelSIL_B.tmp_tmp_m0 *
    ContModelSIL_B.D56_tmp_bj) + ContModelSIL_B.d101) +
    ContModelSIL_B.tmp_tmp_jg * ContModelSIL_B.D56_tmp_bj) + ContModelSIL_B.d102)
    + ContModelSIL_B.tmp_tmp_f * ContModelSIL_B.D56_tmp_bj) +
    ContModelSIL_B.d103) + ContModelSIL_B.rtb_ginv_tmp_ek) +
    ContModelSIL_B.D15_tmp_g) + ContModelSIL_B.d104) + ContModelSIL_B.d105) +
    ContModelSIL_B.rtb_ginv_tmp_k * ContModelSIL_B.D56_tmp_tmp_iz) +
    ContModelSIL_B.d106) + ContModelSIL_B.D45 * ContModelSIL_B.D56_tmp_tmp_g) +
    ContModelSIL_B.d107) + ContModelSIL_B.tmp_tmp_g * ContModelSIL_B.D56_tmp_j)
    + ContModelSIL_B.d108) + ContModelSIL_B.tmp_tmp * ContModelSIL_B.D56_tmp_j)
    + ContModelSIL_B.d109) + ContModelSIL_B.tmp_tmp_nr *
    ContModelSIL_B.D56_tmp_j) + ContModelSIL_B.d110) + ContModelSIL_B.d95 *
    0.00046501 * ContModelSIL_B.x_tmp_p) + ContModelSIL_B.d95 * 0.0003034 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.d95 * 0.0393748 *
    ContModelSIL_B.x_tmp_p) + -0.0525693184 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.142 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.tmp_tmp_n * 0.142 *
    ContModelSIL_B.x_tmp_p) + -0.0383689744 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.tmp_tmp_n * 0.143 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.d95 * 0.028900000000000006 * 0.143 *
    ContModelSIL_B.x_tmp_p) + ContModelSIL_B.tmp_tmp_i *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d14 * 0.04043155 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.tmp_tmp_m *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.d27 * 0.06214814 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.tmp_tmp_j *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.tmp_tmp_e * 0.142 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.tmp_tmp_c *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.tmp_tmp_e * 0.143 *
    ContModelSIL_B.D56_tmp_tmp_g2) + ContModelSIL_B.tmp_tmp_d) +
    ContModelSIL_B.tmp_tmp_ik) + ContModelSIL_B.d32 * ContModelSIL_B.D46_tmp_l)
    + ContModelSIL_B.tmp_tmp_gs) + ContModelSIL_B.rtb_ginv_tmp_o *
    ContModelSIL_B.D56_tmp_tmp_fi) + 0.45856 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.08312 * 0.142 *
    ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.rtb_ginv_tmp_jd *
    ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.d111 * 0.08312 * 0.17 *
    0.143 * ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.tmp_tmp_mv *
    ContModelSIL_B.D56_tmp_f) + ContModelSIL_B.tmp_tmp_nn) +
    ContModelSIL_B.tmp_tmp_m0 * ContModelSIL_B.D56_tmp_f) +
    ContModelSIL_B.tmp_tmp_l) + ContModelSIL_B.tmp_tmp_jg *
    ContModelSIL_B.D56_tmp_f) + ContModelSIL_B.tmp_tmp_ce) +
    ContModelSIL_B.tmp_tmp_f * ContModelSIL_B.D56_tmp_f) +
    ContModelSIL_B.tmp_tmp_nc) + ContModelSIL_B.tmp_tmp_pw) +
    ContModelSIL_B.tmp_tmp_p) + ContModelSIL_B.d32 * ContModelSIL_B.D46_tmp_j) +
    ContModelSIL_B.tmp_tmp_dk) + ContModelSIL_B.rtb_ginv_tmp_k *
    ContModelSIL_B.D56_tmp_tmp_c) + ContModelSIL_B.tmp_tmp_a * 0.08312 * 0.143 *
    ContModelSIL_B.D56_tmp_tmp_c) + ContModelSIL_B.D45 *
    ContModelSIL_B.D56_tmp_tmp_i) + ContModelSIL_B.tmp_tmp_oi) +
    ContModelSIL_B.tmp_tmp_g * ContModelSIL_B.D56_tmp_a) +
    ContModelSIL_B.tmp_tmp_jr) + ContModelSIL_B.tmp_tmp *
    ContModelSIL_B.D56_tmp_a) + ContModelSIL_B.tmp_tmp_c2) +
    ContModelSIL_B.tmp_tmp_nr * ContModelSIL_B.D56_tmp_a) +
    ContModelSIL_B.tmp_tmp_hp) + ContModelSIL_B.d25 * ContModelSIL_B.d3) +
    ContModelSIL_B.d25 * ContModelSIL_B.d4) + ((((((ContModelSIL_B.D48 +
    ContModelSIL_B.D15) - ContModelSIL_B.D25) - ContModelSIL_B.D14) -
    ContModelSIL_B.tmp_tmp_na) - 0.0023809214000000004 *
    ContModelSIL_B.D46_tmp_o4) + ContModelSIL_B.d18) * (ContModelSIL_B.D27_tmp_k
    * ContModelSIL_B.x_tmp_p)) + ((((((((((((-0.0064528108032 *
    ContModelSIL_B.rtb_ginv_tmp_n + ContModelSIL_B.D47_tmp_d) + -0.0013531005056
    * ContModelSIL_B.D24_tmp) - 0.0020206472 * ContModelSIL_B.D24_tmp) +
    ContModelSIL_B.D47_tmp_a) + ContModelSIL_B.D47_tmp) + ContModelSIL_B.D15) -
    ContModelSIL_B.D25) - ContModelSIL_B.D14) - ContModelSIL_B.tmp_tmp_na) +
    ContModelSIL_B.d31) + ContModelSIL_B.d38) + ContModelSIL_B.d18) *
    (ContModelSIL_B.D14_tmp_l * ContModelSIL_B.x_tmp_p)) + ContModelSIL_B.d112)
    + ContModelSIL_B.d48 * ContModelSIL_B.d5) + ContModelSIL_B.d49 *
    ContModelSIL_B.d5) + ContModelSIL_B.rtb_ginv_tmp * ContModelSIL_B.D67) +
    ContModelSIL_B.d113) + ContModelSIL_B.d114) + ContModelSIL_B.d45 *
    ContModelSIL_B.d8) + ContModelSIL_B.d50 * ContModelSIL_B.D37) +
    ContModelSIL_B.rtb_ginv_tmp * ContModelSIL_B.rtb_ginv_tmp_ol) +
    ContModelSIL_B.d115) + ContModelSIL_B.d116) + ContModelSIL_B.d117) +
    ContModelSIL_B.d118) - ContModelSIL_B.d119) - ContModelSIL_B.d120) -
    ContModelSIL_B.d121) + ContModelSIL_B.d122 * ContModelSIL_B.D56_tmp_l) +
    ContModelSIL_B.d123) + ContModelSIL_B.d124) + ContModelSIL_B.d125) -
                     ContModelSIL_B.d126) - ContModelSIL_B.d127) +
                   ContModelSIL_B.d122 * ContModelSIL_B.D56_tmp_d) +
                  ContModelSIL_B.d128) + ContModelSIL_B.tmp_tmp_da *
                 ContModelSIL_B.D46_tmp) + ContModelSIL_B.d129 *
                ContModelSIL_B.D46_tmp) + ContModelSIL_B.rtb_ginv_tmp_tmp_o *
               0.00046501 * ContModelSIL_B.D46_tmp) + ContModelSIL_B.tmp_tmp_c5 *
              ContModelSIL_B.D46_tmp) + ContModelSIL_B.d130 *
             ContModelSIL_B.D46_tmp) + ContModelSIL_B.rtb_ginv_tmp_tmp_o *
            0.0003034 * ContModelSIL_B.D46_tmp) +
           ContModelSIL_B.rtb_ginv_tmp_tmp_o * 0.0393748 *
           ContModelSIL_B.D46_tmp) + ContModelSIL_B.d131 *
          ContModelSIL_B.D46_tmp) + ContModelSIL_B.d16 * 0.06214814 *
         ContModelSIL_B.D46_tmp) + ContModelSIL_B.d132 * ContModelSIL_B.D46_tmp)
       + ContModelSIL_B.d133 * ContModelSIL_B.D46_tmp) + ContModelSIL_B.d134 *
      ContModelSIL_B.D46_tmp) + ContModelSIL_B.D14_tmp_md *
     ContModelSIL_B.D46_tmp) + ContModelSIL_B.d135 * ContModelSIL_B.D46_tmp;
  ContModelSIL_B.dv[37] = -(((((((((((((((((((((((((((((((tmp +
    ContModelSIL_B.d136) + ContModelSIL_B.d137) + ContModelSIL_B.d138) +
    ContModelSIL_B.d139) - ContModelSIL_B.d140) + ContModelSIL_B.d141) +
    ContModelSIL_B.d142) + ContModelSIL_B.d32 * ContModelSIL_B.D46_tmp_o) -
    ContModelSIL_B.d143) + ContModelSIL_B.d144) + ContModelSIL_B.d145) +
    ContModelSIL_B.D46_tmp_tmp_o2) + ContModelSIL_B.d122 *
    ContModelSIL_B.D56_tmp_n) + ContModelSIL_B.d2) + ContModelSIL_B.d32 *
    ContModelSIL_B.D46_tmp_b) - ContModelSIL_B.d146) + ContModelSIL_B.d147) +
    ContModelSIL_B.d148) + ContModelSIL_B.d122 * ContModelSIL_B.D56_tmp_ln) +
    ContModelSIL_B.d20) + ContModelSIL_B.d52 * ContModelSIL_B.d7) +
    ContModelSIL_B.d43 * ContModelSIL_B.d7) + ContModelSIL_B.rtb_ginv_tmp *
    ContModelSIL_B.D15_tmp_tmp) + ContModelSIL_B.d54 * ContModelSIL_B.d9) +
    ContModelSIL_B.d44 * ContModelSIL_B.D14_tmp_tmp) +
    ContModelSIL_B.rtb_ginv_tmp * ContModelSIL_B.D15_tmp_tmp_a) +
    ContModelSIL_B.d52 * ContModelSIL_B.rtb_ginv_tmp_tmp_p4) +
    ContModelSIL_B.d43 * ContModelSIL_B.rtb_ginv_tmp_tmp_p4) +
    ContModelSIL_B.d44 * ContModelSIL_B.D56_tmp_tmp) + ContModelSIL_B.d91) *
    0.125);
  ContModelSIL_B.D56_tmp_tmp_g2 = ContModelSIL_B.D46_tmp_h *
    ContModelSIL_B.rtb_ginv_tmp_tmp_p;
  ContModelSIL_B.D56_tmp_tmp_h = -2.0 * ContModelSIL_B.rtb_ginv_tmp_tmp_p *
    ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.rtb_ginv_tmp_tmp_p = 0.11464 * ContModelSIL_B.D15_tmp +
    ContModelSIL_B.D24_tmp_c;
  ContModelSIL_B.rtb_ginv_tmp_tmp_o = 0.08312 * ContModelSIL_B.Observer_alpha;
  ContModelSIL_B.D14_tmp_l = 4.0 * ContModelSIL_B.x_tmp;
  ContModelSIL_B.D27_tmp_k = 0.0 * ContModelSIL_B.D46_tmp_me;
  ContModelSIL_B.d16 = ((0.17 * ContModelSIL_B.D17_tmp_c +
    ContModelSIL_B.rtb_ginv_tmp_tmp_o) + 0.09794 * ContModelSIL_B.D34_tmp) *
    ContModelSIL_B.DigitalClock - ContModelSIL_B.D24_tmp_f * ContModelSIL_B.u *
    ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.d18 = ContModelSIL_B.D16 * -2.0;
  ContModelSIL_B.d25 = 0.0 * ContModelSIL_B.D56_tmp_tmp_tmp;
  ContModelSIL_B.tmp_tmp = -0.00045390000000000003 * ContModelSIL_B.D46_tmp_l5 +
    ContModelSIL_B.d25;
  ContModelSIL_B.d31 = ContModelSIL_B.D14_tmp_l * ContModelSIL_B.D17_tmp_ct *
    ContModelSIL_B.Observer_alpha * (ContModelSIL_B.D46_tmp_cs +
    ContModelSIL_B.D46_tmp_e);
  ContModelSIL_B.d32 = (-0.0005375800000000001 * ContModelSIL_B.D56_tmp_p +
                        ContModelSIL_B.D27_tmp_k) *
    ContModelSIL_B.rtb_ginv_tmp_pm;
  ContModelSIL_B.d38 = (0.0005375800000000001 * ContModelSIL_B.D56_tmp_p +
                        ContModelSIL_B.rtb_ginv_tmp_nj) *
    ContModelSIL_B.rtb_ginv_tmp_p2;
  ContModelSIL_B.tmp_tmp_c = ContModelSIL_B.d16 * 0.572;
  ContModelSIL_B.rtb_ginv_tmp_tmp_o = (0.11464 * ContModelSIL_B.D17_tmp_c +
    ContModelSIL_B.rtb_ginv_tmp_tmp_o) * ContModelSIL_B.DigitalClock;
  ContModelSIL_B.d111 = ContModelSIL_B.D35 * ContModelSIL_B.D14_tmp_o *
    ContModelSIL_B.D46_tmp;
  ContModelSIL_B.tmp_tmp_n = ContModelSIL_B.D34 * ContModelSIL_B.d149 *
    ContModelSIL_B.D46_tmp;
  ContModelSIL_B.dv[45] = -((((((((((((((((((((-0.00045390000000000003 *
    ContModelSIL_B.D14_tmp_f * ContModelSIL_B.smax + ContModelSIL_B.d25) *
    (ContModelSIL_B.D14_tmp_l * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.Observer_alpha) * ContModelSIL_B.x_tmp_b +
    (((ContModelSIL_B.D56_tmp_tmp_g2 * ContModelSIL_B.D46_tmp_h2 +
    ContModelSIL_B.D56_tmp_tmp_h * ContModelSIL_B.D24) +
    ContModelSIL_B.D56_tmp_tmp_g2 * ContModelSIL_B.D35) +
    ContModelSIL_B.D56_tmp_tmp_h * ContModelSIL_B.D34)) + ((-0.0 *
    ContModelSIL_B.D14_tmp_f * ContModelSIL_B.smax + ContModelSIL_B.D46_tmp_hh)
    + ContModelSIL_B.D46_tmp_mc) * (ContModelSIL_B.d18 * ContModelSIL_B.x_tmp_p)
    * ContModelSIL_B.x_tmp_b) + -2.0 * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.D56 * ContModelSIL_B.D26 * ContModelSIL_B.x_tmp_b) -
    ContModelSIL_B.D16 * ContModelSIL_B.x_tmp_p * ContModelSIL_B.D46 *
    ContModelSIL_B.x_tmp_b) - ContModelSIL_B.D56 * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.D46_tmp_bn * ContModelSIL_B.x_tmp_b) +
    ContModelSIL_B.D46_tmp_h * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.Observer_alpha * (-0.00026879000000000003 *
    ContModelSIL_B.D56_tmp_p + ContModelSIL_B.D27_tmp_k) *
    ContModelSIL_B.x_tmp_b) + ContModelSIL_B.rtb_ginv_tmp_tmp_p * -0.284 *
    ContModelSIL_B.x_tmp_p * ContModelSIL_B.u *
    (ContModelSIL_B.rtb_ginv_tmp_tmp_o - ContModelSIL_B.rtb_ginv_tmp_tmp_p *
     ContModelSIL_B.u * ContModelSIL_B.x_tmp_b)) + ContModelSIL_B.D24_tmp_f *
    -0.286 * ContModelSIL_B.x_tmp_p * ContModelSIL_B.u * ContModelSIL_B.d16) +
    -0.284 * ContModelSIL_B.DigitalClock * ContModelSIL_B.rtb_ginv_tmp_tmp_p *
    ContModelSIL_B.x_tmp_p * ContModelSIL_B.D45_tmp) + -0.286 *
    ContModelSIL_B.DigitalClock * ContModelSIL_B.D24_tmp_f *
    ContModelSIL_B.x_tmp_p * ContModelSIL_B.D24_tmp_p) + 0.00046501 *
    ContModelSIL_B.D46_tmp) + 0.0003034 * ContModelSIL_B.D46_tmp) + 0.0393748 *
    ContModelSIL_B.D46_tmp) - ContModelSIL_B.D45_tmp_f * ContModelSIL_B.D46_tmp)
    - ContModelSIL_B.D56 * 0.04043155 * ContModelSIL_B.D46_tmp) *
    ContModelSIL_B.d14 + ((((ContModelSIL_B.D18_tmp * 0.572 *
    ContModelSIL_B.D24_tmp_p + ((ContModelSIL_B.d31 + ContModelSIL_B.d32) +
    ContModelSIL_B.d38)) + ContModelSIL_B.tmp_tmp_c * ContModelSIL_B.D17_tmp) +
    ContModelSIL_B.d111) + ContModelSIL_B.tmp_tmp_n) *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[7]) +
    (((((((((((((ContModelSIL_B.D17_tmp_ct * -2.0 * ContModelSIL_B.D17 *
                 (-0.00045390000000000003 * ContModelSIL_B.D56_tmp_tmp_tmp +
                  ContModelSIL_B.rtb_ginv_tmp_kt) + ContModelSIL_B.d18 *
                 ContModelSIL_B.D17_tmp_ct * ContModelSIL_B.tmp_tmp) +
                ContModelSIL_B.D17_tmp_ct * 2.0 * ContModelSIL_B.D56 *
                ContModelSIL_B.tmp_tmp) + ContModelSIL_B.d31) +
              ContModelSIL_B.d32) + ContModelSIL_B.d38) +
            (ContModelSIL_B.rtb_ginv_tmp_j * ContModelSIL_B.D17_tmp_p +
             ContModelSIL_B.rtb_ginv_tmp_h * ContModelSIL_B.D17_tmp_n) * 0.572 *
            ContModelSIL_B.D24_tmp_p) + (ContModelSIL_B.D17_tmp_a *
    -ContModelSIL_B.D17_tmp_p + ContModelSIL_B.rtb_ginv_tmp_i *
    ContModelSIL_B.D17_tmp_n) * ContModelSIL_B.tmp_tmp_c) +
          (ContModelSIL_B.D17_tmp_o * ContModelSIL_B.Observer_alpha +
           ContModelSIL_B.D17_tmp_g * ContModelSIL_B.x_tmp) *
          (ContModelSIL_B.D45_tmp * 0.06511552)) + ((ContModelSIL_B.D14_tmp_f *
    ContModelSIL_B.u * ContModelSIL_B.x_tmp_b + -ContModelSIL_B.DigitalClock *
    ContModelSIL_B.smax) * (0.11464 * ContModelSIL_B.Observer_alpha) +
    (ContModelSIL_B.D17_tmp_tmp * ContModelSIL_B.x_tmp_b +
     ContModelSIL_B.D17_tmp_tmp_c) * (0.11464 * ContModelSIL_B.x_tmp)) *
         ((-ContModelSIL_B.rtb_ginv_tmp_tmp_p * ContModelSIL_B.u *
           ContModelSIL_B.x_tmp_b + ContModelSIL_B.rtb_ginv_tmp_tmp_o) * 0.568))
        + ContModelSIL_B.D46_tmp_h2 * ContModelSIL_B.D14_tmp_o *
        ContModelSIL_B.D46_tmp) + ContModelSIL_B.D24 * ContModelSIL_B.d149 *
       ContModelSIL_B.D46_tmp) + ContModelSIL_B.d111) + ContModelSIL_B.tmp_tmp_n)
    * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6]) -
    (((((((((((((((((((((((((((((((((((((((((0.0 * ContModelSIL_B.D56_tmp_bj +
    ContModelSIL_B.D16_tmp_pt) + ContModelSIL_B.D46_tmp_tmp_f) + 0.0 *
    ContModelSIL_B.D56_tmp_j) + ContModelSIL_B.D37_tmp) + 0.0 *
    ContModelSIL_B.D56_tmp_f) + ContModelSIL_B.d60) + 0.0 *
    ContModelSIL_B.D56_tmp_a) - ContModelSIL_B.D56_tmp_tmp_cj) +
    ContModelSIL_B.D56_tmp_tmp_m) - ContModelSIL_B.D56_tmp_tmp_j) -
    ContModelSIL_B.D56_tmp_tmp_k) + -0.0 * ContModelSIL_B.D46_tmp_d) +
    -0.0027062010112 * ContModelSIL_B.D56_tmp_g) + -0.0040412944 *
    ContModelSIL_B.D56_tmp_g) + ContModelSIL_B.D56_tmp_tmp_mx) -
    ContModelSIL_B.D56_tmp_tmp_p) - ContModelSIL_B.D56_tmp_tmp_d) -
    ContModelSIL_B.D56_tmp_tmp_g4) + -0.0 * ContModelSIL_B.D46_tmp_dh) +
    -0.0023282610207999996 * ContModelSIL_B.D56_tmp_ju) + -0.004761842800000001 *
    ContModelSIL_B.D56_tmp_jz) + ContModelSIL_B.D56_tmp_tmp_c3) -
    ContModelSIL_B.D56_tmp_tmp_cx) - ContModelSIL_B.D56_tmp_tmp_if) -
                     ContModelSIL_B.D56_tmp_tmp_dx) +
                    ContModelSIL_B.D56_tmp_tmp_g4k) -
                   ContModelSIL_B.D56_tmp_tmp_l) + -0.0009879776191999998 *
                  ContModelSIL_B.D56_tmp_lx) + ContModelSIL_B.D46_tmp_h3) +
                -0.0027062010112 * ContModelSIL_B.D56_tmp_b) + -0.0040412944 *
               ContModelSIL_B.D56_tmp_b) + ContModelSIL_B.D56_tmp_tmp_f1) -
             ContModelSIL_B.D56_tmp_tmp_db) - ContModelSIL_B.D56_tmp_tmp_jr) -
           ContModelSIL_B.D56_tmp_tmp_i3) + ContModelSIL_B.D46_tmp_k) +
         -0.0023282610207999996 * ContModelSIL_B.D56_tmp_o) +
        -0.004761842800000001 * ContModelSIL_B.D56_tmp_ny) + ContModelSIL_B.d39)
      - ContModelSIL_B.D46_tmp_o3) - ContModelSIL_B.D56_tmp_ad) *
    ContModelSIL_B.D16_tmp_f) * 0.25);
  ContModelSIL_B.D17 = 0.22928 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [4] * 0.08312 * 0.142;
  ContModelSIL_B.D56_tmp_tmp_g2 = ContModelSIL_B.d14 * 0.08312 * 0.17 * 0.143;
  ContModelSIL_B.D56_tmp_tmp_h = 0.19588 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelSIL_B.rtb_ginv_tmp_tmp_p = ContModelSIL_B.D56_tmp_tmp_h * 0.08312 *
    0.143;
  ContModelSIL_B.d149 = ContModelSIL_B.rtb_ginv_tmp * ContModelSIL_B.D46_tmp_da;
  ContModelSIL_B.d *= ContModelSIL_B.d42;
  ContModelSIL_B.D16_tmp_f = ContModelSIL_B.rtb_ginv_tmp_k *
    ContModelSIL_B.D46_tmp_tmp_a;
  ContModelSIL_B.D46_tmp_tmp_a *= ContModelSIL_B.d74;
  ContModelSIL_B.D14_tmp_o = ContModelSIL_B.d122 * ContModelSIL_B.D46_tmp_p;
  ContModelSIL_B.D46_tmp_tmp_l *= ContModelSIL_B.d42;
  ContModelSIL_B.D56_tmp_tmp_iz *= ContModelSIL_B.rtb_ginv_tmp_tmp_p;
  ContModelSIL_B.rtb_ginv_tmp_tmp_o = ContModelSIL_B.tmp_tmp_ch *
    ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.D14_tmp_l = ContModelSIL_B.tmp_tmp_b * ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.D16_tmp_pt = ContModelSIL_B.tmp_tmp_er *
    ContModelSIL_B.D56_tmp_j;
  ContModelSIL_B.D27_tmp_k = ContModelSIL_B.d74 * ContModelSIL_B.D46_tmp_tmp_af;
  ContModelSIL_B.d16 = ContModelSIL_B.d122 * ContModelSIL_B.D46_tmp_j;
  ContModelSIL_B.D56_tmp_tmp_c *= ContModelSIL_B.rtb_ginv_tmp_tmp_p;
  ContModelSIL_B.d4 *= ContModelSIL_B.d26;
  ContModelSIL_B.rtb_ginv_tmp_tmp_p = -0.5876399999999999 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelSIL_B.d18 = ContModelSIL_B.rtb_ginv_tmp_tmp_p * 0.08312 * 0.143 *
    ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.d25 = ContModelSIL_B.tmp_tmp_c5 * ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.tmp_tmp = ContModelSIL_B.D16_tmp * 0.00034964 *
    ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.d31 = ContModelSIL_B.d134 * ContModelSIL_B.D46_tmp_e1;
  ContModelSIL_B.d32 = ContModelSIL_B.d44 * ContModelSIL_B.D56_tmp_tmp_a;
  ContModelSIL_B.D37 *= ContModelSIL_B.ab_a;
  ContModelSIL_B.rtb_ginv_tmp_ol *= ContModelSIL_B.d26;
  ContModelSIL_B.D56_tmp_tmp_ff *= ContModelSIL_B.ab_a;
  ContModelSIL_B.d38 = ContModelSIL_B.d122 * ContModelSIL_B.D46_tmp_dh;
  ContModelSIL_B.d39 = ContModelSIL_B.d41 * ContModelSIL_B.D56_tmp_d;
  ContModelSIL_B.tmp_tmp_c = ContModelSIL_B.d122 * ContModelSIL_B.D46_tmp_b;
  ContModelSIL_B.d40 = (((ContModelSIL_B.d40 - ContModelSIL_B.d10) +
    ContModelSIL_B.D46_tmp_mv) + ContModelSIL_B.D46_tmp_c) +
    ContModelSIL_B.D46_tmp_k;
  ContModelSIL_B.d111 = ContModelSIL_B.d40 * ContModelSIL_B.d157;
  ContModelSIL_B.D14_tmp_tmp *= ContModelSIL_B.ab_a;
  ContModelSIL_B.D15_tmp_tmp_a *= ContModelSIL_B.d42;
  ContModelSIL_B.ab_a *= ContModelSIL_B.D56_tmp_tmp;
  ContModelSIL_B.tmp_tmp_n = ContModelSIL_B.D38 * ContModelSIL_B.d5;
  ContModelSIL_B.d5 *= ContModelSIL_B.D48_tmp;
  ContModelSIL_B.tmp_tmp_i = ContModelSIL_B.D38 * ContModelSIL_B.D56_tmp_tmp_f;
  ContModelSIL_B.D56_tmp_tmp_f *= ContModelSIL_B.D48_tmp;
  ContModelSIL_B.tmp_tmp_m = ContModelSIL_B.D38 * ContModelSIL_B.d7;
  ContModelSIL_B.d7 *= ContModelSIL_B.D48_tmp;
  ContModelSIL_B.D38 *= ContModelSIL_B.rtb_ginv_tmp_tmp_p4;
  ContModelSIL_B.D48_tmp *= ContModelSIL_B.rtb_ginv_tmp_tmp_p4;
  ContModelSIL_B.dv[53] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((ContModelSIL_B.rtb_ginv_tmp *
    ContModelSIL_B.rtb_ginv_tmp_n + ContModelSIL_B.d149) + ContModelSIL_B.d42 *
    ContModelSIL_B.D68) + ContModelSIL_B.d) + ContModelSIL_B.rtb_ginv_tmp_o *
    ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.d6 *
    ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.rtb_ginv_tmp_jd *
    ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.d55 *
    ContModelSIL_B.D46_tmp_tmp_ei) + ContModelSIL_B.d122 *
    ContModelSIL_B.D46_tmp_n) + ContModelSIL_B.d42 * ContModelSIL_B.d1) +
    ContModelSIL_B.D17 * ContModelSIL_B.D27) + ContModelSIL_B.D56_tmp_tmp_g2 *
    ContModelSIL_B.D27) + ContModelSIL_B.rtb_ginv_tmp_p *
    ContModelSIL_B.D56_tmp_bj) + ContModelSIL_B.rtb_ginv_tmp_bp *
    ContModelSIL_B.D56_tmp_bj) + ContModelSIL_B.tmp_tmp_h *
    ContModelSIL_B.D56_tmp_bj) + ContModelSIL_B.tmp_tmp_nm *
    ContModelSIL_B.D56_tmp_bj) + ContModelSIL_B.d150) + ContModelSIL_B.D16_tmp_f)
    + ContModelSIL_B.D46_tmp_tmp_a) + ContModelSIL_B.D14_tmp_o) +
    ContModelSIL_B.D46_tmp_tmp_l) + ContModelSIL_B.D56_tmp_tmp_iz) +
    ContModelSIL_B.tmp_tmp_o * ContModelSIL_B.D56_tmp_tmp_g) +
    ContModelSIL_B.rtb_ginv_tmp_tmp_o) + ContModelSIL_B.D14_tmp_l) +
    ContModelSIL_B.D16_tmp_pt) + ContModelSIL_B.d151) + ContModelSIL_B.d152) +
    ContModelSIL_B.d153) + ContModelSIL_B.d154) + ContModelSIL_B.d155) +
    ContModelSIL_B.tmp_tmp_d) + ContModelSIL_B.d6 * ContModelSIL_B.D46_tmp_tmp_e)
    + ContModelSIL_B.tmp_tmp_ik) + ContModelSIL_B.d55 *
    ContModelSIL_B.D46_tmp_tmp_e) + ContModelSIL_B.d122 *
    ContModelSIL_B.D46_tmp_l) + ContModelSIL_B.tmp_tmp_gs) + ContModelSIL_B.D17 *
    ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.D56_tmp_tmp_g2 *
    ContModelSIL_B.D56_tmp_tmp_fi) + ContModelSIL_B.tmp_tmp_nn) +
    ContModelSIL_B.tmp_tmp_l) + ContModelSIL_B.tmp_tmp_ce) +
    ContModelSIL_B.tmp_tmp_nc) + ContModelSIL_B.d156) + ContModelSIL_B.tmp_tmp_p)
    + ContModelSIL_B.D27_tmp_k) + ContModelSIL_B.d16) +
    ContModelSIL_B.tmp_tmp_dk) + ContModelSIL_B.D56_tmp_tmp_c) +
    ContModelSIL_B.tmp_tmp_oi) + ContModelSIL_B.tmp_tmp_jr) +
    ContModelSIL_B.tmp_tmp_c2) + ContModelSIL_B.tmp_tmp_hp) + ContModelSIL_B.d26
    * ContModelSIL_B.d3) + ContModelSIL_B.d4) + -0.68784 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142 *
    ContModelSIL_B.smax) + -6.0 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.17 * 0.143 *
    ContModelSIL_B.smax) + ContModelSIL_B.tmp_tmp_da * ContModelSIL_B.D46_tmp_m)
    + ContModelSIL_B.D16_tmp * 0.00050874 * ContModelSIL_B.D46_tmp_m) +
    ContModelSIL_B.d132 * ContModelSIL_B.D46_tmp_m) + ContModelSIL_B.d135 *
    ContModelSIL_B.D46_tmp_m) + ContModelSIL_B.d52 * ContModelSIL_B.D18) +
    ContModelSIL_B.d43 * ContModelSIL_B.D18) + ContModelSIL_B.d18) +
    ContModelSIL_B.d25) + ContModelSIL_B.tmp_tmp) + ContModelSIL_B.d31) +
    ContModelSIL_B.d32) + 0.39176 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.17 * 0.143 *
    ContModelSIL_B.D28) + ContModelSIL_B.d54 * ContModelSIL_B.D46_tmp_tmp) +
    ContModelSIL_B.tmp_tmp_n) + ContModelSIL_B.d5) + ContModelSIL_B.d26 *
    ContModelSIL_B.D67) + ContModelSIL_B.tmp_tmp_i) +
    ContModelSIL_B.D56_tmp_tmp_f) + ContModelSIL_B.D37) +
    ContModelSIL_B.rtb_ginv_tmp_ol) + ContModelSIL_B.D56_tmp_tmp_ff) +
    ContModelSIL_B.d122 * ContModelSIL_B.D46_tmp_d) - ContModelSIL_B.d118) +
    ContModelSIL_B.d119) + ContModelSIL_B.d120) + ContModelSIL_B.d121) +
    ContModelSIL_B.d41 * ContModelSIL_B.D56_tmp_l) + ContModelSIL_B.d38) +
    -ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 8.085E-5 *
    ContModelSIL_B.D47) + ContModelSIL_B.d126) + ContModelSIL_B.d127) +
    ContModelSIL_B.d39) + ContModelSIL_B.d122 * ContModelSIL_B.D46_tmp_o) +
    -ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 5.484E-5 *
    ContModelSIL_B.y_a) + ContModelSIL_B.d144) + ContModelSIL_B.d145) +
                        ContModelSIL_B.D46_tmp_tmp_o2) + ContModelSIL_B.d2) +
                      ContModelSIL_B.tmp_tmp_c) + ContModelSIL_B.d111) +
                    ContModelSIL_B.d28 * ContModelSIL_B.d158) -
                   ContModelSIL_B.d146) + ContModelSIL_B.d147) +
                 ContModelSIL_B.d148) + ContModelSIL_B.d20) +
               ContModelSIL_B.tmp_tmp_m) + ContModelSIL_B.d7) +
             ContModelSIL_B.d42 * ContModelSIL_B.D15_tmp_tmp) +
            ContModelSIL_B.D14_tmp_tmp) + ContModelSIL_B.D15_tmp_tmp_a) +
          ContModelSIL_B.D38) + ContModelSIL_B.D48_tmp) + ContModelSIL_B.ab_a) +
       ContModelSIL_B.d91) * 0.125);
  ContModelSIL_B.D17 = ContModelSIL_B.D56_tmp_tmp_h * 0.17 * 0.143;
  ContModelSIL_B.D27 = ContModelSIL_B.D58 * ContModelSIL_B.D46_tmp_tmp;
  ContModelSIL_B.D56_tmp_tmp_g2 = ContModelSIL_B.D58 * ContModelSIL_B.d8;
  ContModelSIL_B.D56_tmp_tmp_fi = ContModelSIL_B.D58 * ContModelSIL_B.d9;
  ContModelSIL_B.D56_tmp_tmp_h = ContModelSIL_B.D58 *
    ContModelSIL_B.D46_tmp_tmp_o;
  ContModelSIL_B.dv[61] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((ContModelSIL_B.d149
    + ContModelSIL_B.d) + ContModelSIL_B.D45 * ContModelSIL_B.D46_tmp_tmp_c) +
    ContModelSIL_B.d12 * ContModelSIL_B.D46_tmp_tmp_c) +
    ContModelSIL_B.D16_tmp_f) + ContModelSIL_B.D46_tmp_tmp_a) +
    ContModelSIL_B.D14_tmp_o) + ContModelSIL_B.D46_tmp_tmp_l) +
    ContModelSIL_B.D56_tmp_tmp_iz) + ContModelSIL_B.D17 *
    ContModelSIL_B.D56_tmp_tmp_g) + ContModelSIL_B.rtb_ginv_tmp_tmp_o) +
    ContModelSIL_B.D14_tmp_l) + ContModelSIL_B.D16_tmp_pt) + ContModelSIL_B.d152)
    + ContModelSIL_B.d154) + ContModelSIL_B.tmp_tmp_pw) + ContModelSIL_B.d12 *
    ContModelSIL_B.D46_tmp_tmp_d) + ContModelSIL_B.tmp_tmp_p) +
    ContModelSIL_B.D27_tmp_k) + ContModelSIL_B.d16) + ContModelSIL_B.tmp_tmp_dk)
    + ContModelSIL_B.D56_tmp_tmp_c) + ContModelSIL_B.D17 *
    ContModelSIL_B.D56_tmp_tmp_i) + ContModelSIL_B.tmp_tmp_jr) +
    ContModelSIL_B.tmp_tmp_c2) + ContModelSIL_B.tmp_tmp_hp) + ContModelSIL_B.d4)
    + ContModelSIL_B.rtb_ginv_tmp_tmp_p * 0.17 * 0.143 * ContModelSIL_B.s) +
    ContModelSIL_B.d18) + ContModelSIL_B.d25) + ContModelSIL_B.tmp_tmp) +
    ContModelSIL_B.d31) + ContModelSIL_B.d32) + ContModelSIL_B.d54 *
    ContModelSIL_B.D28) + ContModelSIL_B.D27) + ContModelSIL_B.D56_tmp_tmp_g2) +
    ContModelSIL_B.D37) + ContModelSIL_B.rtb_ginv_tmp_ol) +
                        ContModelSIL_B.D56_tmp_tmp_ff) + ContModelSIL_B.d38) -
                      ContModelSIL_B.d125) + ContModelSIL_B.d126) +
                    ContModelSIL_B.d127) + ContModelSIL_B.d39) +
                  ContModelSIL_B.tmp_tmp_c) + ContModelSIL_B.d40 *
                 ContModelSIL_B.d158) + ContModelSIL_B.d111) -
               ContModelSIL_B.d146) + ContModelSIL_B.d147) + ContModelSIL_B.d148)
            + ContModelSIL_B.d20) + ContModelSIL_B.D56_tmp_tmp_fi) +
          ContModelSIL_B.D14_tmp_tmp) + ContModelSIL_B.D15_tmp_tmp_a) +
        ContModelSIL_B.ab_a) + ContModelSIL_B.D56_tmp_tmp_h) * 0.125);
  ContModelSIL_B.D17 = ContModelSIL_B.d29 * 0.17 * 0.143 * ContModelSIL_B.s;
  ContModelSIL_B.D46_tmp_tmp_ei =
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[3] -
    ContModelSIL_B.rtb_ginv_tmp_tmp;
  ContModelSIL_B.dv[30] = -(ContModelSIL_B.d34 * ContModelSIL_B.D46_tmp_tmp_ei +
    ContModelSIL_B.D17);
  ContModelSIL_B.dv[38] = -((((((((((((((((ContModelSIL_B.d159 +
    ContModelSIL_B.d33) + 0.0020206472 * ContModelSIL_B.smax) -
    ContModelSIL_B.D16_tmp_p) + ContModelSIL_B.d13) + ContModelSIL_B.d15) +
    ContModelSIL_B.D16_tmp_i) + 0.0013531005056 * ContModelSIL_B.D18) +
    ContModelSIL_B.d35) + ContModelSIL_B.d36) - ContModelSIL_B.d22) +
    ContModelSIL_B.D14_tmp_m) + ContModelSIL_B.rtb_ginv_tmp_e) +
    ContModelSIL_B.d37) + ContModelSIL_B.d160) * ContModelSIL_B.d14 -
    ContModelSIL_B.D27_tmp * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
    0.25);
  ContModelSIL_B.D46_tmp_tmp_c = ContModelSIL_B.rtb_ginv_tmp_k *
    ContModelSIL_B.D46_tmp_tmp_af;
  ContModelSIL_B.D46_tmp_tmp_a = 0.5876399999999999 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelSIL_B.D56_tmp_tmp_iz = ContModelSIL_B.D46_tmp_tmp_a * 0.08312 * 0.143
    * ContModelSIL_B.D14_tmp_c;
  ContModelSIL_B.D56_tmp_tmp_g = ContModelSIL_B.d50 *
    ContModelSIL_B.D56_tmp_tmp_a;
  ContModelSIL_B.dv[46] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((ContModelSIL_B.d161
    + ContModelSIL_B.D46_tmp_lm) + ContModelSIL_B.D56_tmp) + ContModelSIL_B.d97)
    + ContModelSIL_B.D15_tmp_g) + ContModelSIL_B.d105) +
    ContModelSIL_B.rtb_ginv_tmp_o * ContModelSIL_B.D46_tmp_tmp_e) +
    ContModelSIL_B.rtb_ginv_tmp_jd * ContModelSIL_B.D46_tmp_tmp_e) +
    ContModelSIL_B.d162) + ContModelSIL_B.D46_tmp_tmp_c) + ContModelSIL_B.d163)
    + ContModelSIL_B.d164) + ContModelSIL_B.d165) + 0.68784 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142 *
    ContModelSIL_B.smax) + 6.0 * ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5] * 0.08312 * 0.17 * 0.143 * ContModelSIL_B.smax) + ContModelSIL_B.d166) +
    ContModelSIL_B.d167) + ContModelSIL_B.d168) + ContModelSIL_B.d169) +
    ContModelSIL_B.d48 * ContModelSIL_B.D18) + ContModelSIL_B.d49 *
    ContModelSIL_B.D18) + ContModelSIL_B.D56_tmp_tmp_iz) + ContModelSIL_B.d170)
    + ContModelSIL_B.d171) + ContModelSIL_B.d172) + ContModelSIL_B.D56_tmp_tmp_g)
    + ContModelSIL_B.d173) + ContModelSIL_B.d112) - ContModelSIL_B.tmp_tmp_n) -
    ContModelSIL_B.d5) + ContModelSIL_B.d174) - ContModelSIL_B.tmp_tmp_i) -
    ContModelSIL_B.D56_tmp_tmp_f) - ContModelSIL_B.D37) + ContModelSIL_B.d175) -
    ContModelSIL_B.D56_tmp_tmp_ff) + ContModelSIL_B.d118) - ContModelSIL_B.d119)
    - ContModelSIL_B.d120) - ContModelSIL_B.d121) + ContModelSIL_B.d125) -
    ContModelSIL_B.d126) - ContModelSIL_B.d127) + ContModelSIL_B.d176 * 0.17 *
                        0.143 * ContModelSIL_B.s * ContModelSIL_B.x_tmp_b) +
                       ContModelSIL_B.d143) - ContModelSIL_B.d144) -
                     ContModelSIL_B.d145) - ContModelSIL_B.D46_tmp_tmp_o2) +
                   ContModelSIL_B.d146) - ContModelSIL_B.d147) -
                 ContModelSIL_B.d148) +
                ((((((((((((((((((((((((((((((((((((((((((-5.484E-5 *
    ContModelSIL_B.D56_tmp_bj + ContModelSIL_B.d177) + ContModelSIL_B.D14_tmp) +
    ContModelSIL_B.d21) + ContModelSIL_B.d23) + ContModelSIL_B.d24) +
    ContModelSIL_B.D14_tmp_p) + ContModelSIL_B.D46_tmp_tmp_f) +
    ContModelSIL_B.D14_tmp_ms) + ContModelSIL_B.D14_tmp_g) -
    ContModelSIL_B.D14_tmp_cz) + ContModelSIL_B.D14_tmp_tmp_m) +
    ContModelSIL_B.D14_tmp_tmp_c) + ContModelSIL_B.D14_tmp_m3) +
    ContModelSIL_B.D15_tmp_tmp_i) + ContModelSIL_B.D15_tmp_tmp_o) +
    ContModelSIL_B.D16_tmp_tmp) + ContModelSIL_B.D34_tmp_n) + ContModelSIL_B.d30)
    + ContModelSIL_B.d47) + ContModelSIL_B.D37_tmp) + ContModelSIL_B.d178) +
    ContModelSIL_B.d179) - ContModelSIL_B.rtb_ginv_tmp_b) + ContModelSIL_B.d56)
    + ContModelSIL_B.d57) + ContModelSIL_B.d58) + ContModelSIL_B.d59) +
    ContModelSIL_B.d10) + ContModelSIL_B.d60) + ContModelSIL_B.d11) +
    ContModelSIL_B.d61) - ContModelSIL_B.d62) + ContModelSIL_B.d63) +
    ContModelSIL_B.d64) + ContModelSIL_B.D46_tmp_mj) + ContModelSIL_B.d65) +
                      ContModelSIL_B.D46_tmp_c) + ContModelSIL_B.d66) +
                    ContModelSIL_B.D56_tmp_h) + ContModelSIL_B.d67) +
                  ContModelSIL_B.D56_tmp_m) + ContModelSIL_B.d68) *
                ContModelSIL_B.d27) - ContModelSIL_B.tmp_tmp_m) -
              ContModelSIL_B.d7) + ContModelSIL_B.d180) -
            ContModelSIL_B.D14_tmp_tmp) + ContModelSIL_B.d181) -
          ContModelSIL_B.D38) - ContModelSIL_B.D48_tmp) - ContModelSIL_B.ab_a) +
       ContModelSIL_B.d182) * 0.125);
  ContModelSIL_B.dv[54] = -ContModelSIL_B.D17;
  ContModelSIL_B.dv[62] = -(-0.0023809214000000004 * ContModelSIL_B.s *
    ContModelSIL_B.d19);
  ContModelSIL_B.dv[31] = -((ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    0.17 * ContModelSIL_B.s + ContModelSIL_B.d51 * ContModelSIL_B.D46_tmp_tmp_ei)
    * 0.01400542);
  ContModelSIL_B.dv[39] = -((ContModelSIL_B.d46 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * ContModelSIL_B.D34_tmp +
    -ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.0 *
    ContModelSIL_B.D46_tmp_da) + -0.25 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * ContModelSIL_B.d183);
  ContModelSIL_B.dv[47] = -((((((((((((((((((((((((((((((((((ContModelSIL_B.d184
    + ContModelSIL_B.d185) + ContModelSIL_B.rtb_ginv_tmp_ek) +
    ContModelSIL_B.D15_tmp_g) + ContModelSIL_B.d105) + ContModelSIL_B.D45 *
    ContModelSIL_B.D46_tmp_tmp_d) + ContModelSIL_B.D46_tmp_tmp_c) +
    ContModelSIL_B.d163) + ContModelSIL_B.d165) + ContModelSIL_B.D46_tmp_tmp_a *
    0.17 * 0.143 * ContModelSIL_B.s) + ContModelSIL_B.D56_tmp_tmp_iz) +
    ContModelSIL_B.d170) + ContModelSIL_B.d171) + ContModelSIL_B.d172) +
    ContModelSIL_B.D56_tmp_tmp_g) + ContModelSIL_B.d45 * ContModelSIL_B.D28) -
    ContModelSIL_B.D27) - ContModelSIL_B.D56_tmp_tmp_g2) - ContModelSIL_B.D37) +
    ContModelSIL_B.d175) - ContModelSIL_B.D56_tmp_tmp_ff) + ContModelSIL_B.d125)
    - ContModelSIL_B.d126) - ContModelSIL_B.d127) + -0.78352 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.17 * 0.143 *
    ContModelSIL_B.s * ContModelSIL_B.x_tmp_b) + ContModelSIL_B.d146) -
    ContModelSIL_B.d147) - ContModelSIL_B.d148) + ContModelSIL_B.d183 *
    ContModelSIL_B.d27) - ContModelSIL_B.D56_tmp_tmp_fi) -
    ContModelSIL_B.D14_tmp_tmp) + ContModelSIL_B.d181) + -0.09794 *
    ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.143 *
    ContModelSIL_B.D56_tmp_tmp) - ContModelSIL_B.D56_tmp_tmp_h) * 0.125);
  ContModelSIL_B.dv[55] = -(0.0023809214000000004 * ContModelSIL_B.s *
    ContModelSIL_B.d17);
  ContModelSIL_B.dv[63] = -0.0;
  memset(&ContModelSIL_B.dv[0], 0, 24U * sizeof(real_T));
  memset(&ContModelSIL_B.dv1[0], 0, sizeof(real_T) << 3U);
  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.D17 =
      ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[ContModelSIL_B.c_j];
    for (ContModelSIL_B.jj = 0; ContModelSIL_B.jj < 8; ContModelSIL_B.jj++) {
      ContModelSIL_B.dv1[ContModelSIL_B.jj] += ContModelSIL_B.dv
        [(ContModelSIL_B.c_j << 3) + ContModelSIL_B.jj] * ContModelSIL_B.D17;
    }
  }

  ContModelSIL_B.dv2[0] = 0.0;
  ContModelSIL_B.dv2[1] = 0.0;
  ContModelSIL_B.dv2[2] = 20.631230269999996;
  ContModelSIL_B.D17 = -9.80665 * ContModelSIL_B.x_tmp_p;
  ContModelSIL_B.dv2[3] = ((-0.023689199999999997 *
    ContModelSIL_B.Observer_alpha - ContModelSIL_B.D34_tmp_a) -
    ContModelSIL_B.D34_tmp_i) * ContModelSIL_B.D17;
  ContModelSIL_B.dv2[4] = ContModelSIL_B.D15_tmp_p * 9.80665 *
    ContModelSIL_B.x_tmp_b;
  ContModelSIL_B.dv2[5] = 0.0;
  ContModelSIL_B.dv2[6] = (-0.040588879999999994 * ContModelSIL_B.D17_tmp_c -
    ContModelSIL_B.D34_tmp_i) * ContModelSIL_B.D17;
  ContModelSIL_B.dv2[7] = 0.137346252043 * ContModelSIL_B.x_tmp_p *
    ContModelSIL_B.D34_tmp;

  // Product: '<S1>/Matrix Multiply' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.Sign3[ContModelSIL_B.c_j] =
      ContModelSIL_B.dv1[ContModelSIL_B.c_j] -
      ContModelSIL_B.dv2[ContModelSIL_B.c_j];
    ContModelSIL_DW.Delay4_DSTATE[ContModelSIL_B.c_j] = 0.0;
  }

  // MATLAB Function: '<S1>/MATLAB Function1'
  ContModelSIL_mldivide_p(ContModelSIL_B.ginv, ContModelSIL_B.Sign3);
  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    // Product: '<S1>/Matrix Multiply' incorporates:
    //   Delay: '<S1>/Delay'

    ContModelSIL_B.D17 = ContModelSIL_DW.Delay_DSTATE[ContModelSIL_B.c_j];
    for (ContModelSIL_B.jj = 0; ContModelSIL_B.jj < 8; ContModelSIL_B.jj++) {
      ContModelSIL_DW.Delay4_DSTATE[ContModelSIL_B.jj] += ContModelSIL_B.ginv
        [(ContModelSIL_B.c_j << 3) + ContModelSIL_B.jj] * ContModelSIL_B.D17;
    }

    // Product: '<S11>/Matrix Multiply1' incorporates:
    //   Delay: '<S8>/Delay'

    ContModelSIL_B.Product8[ContModelSIL_B.c_j] = 0.0;
  }

  // Product: '<S11>/Matrix Multiply1' incorporates:
  //   Delay: '<S8>/Delay'
  //   Product: '<S1>/Matrix Multiply'

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.D17 = ContModelSIL_DW.Delay4_DSTATE[ContModelSIL_B.c_j];
    for (ContModelSIL_B.jj = 0; ContModelSIL_B.jj < 8; ContModelSIL_B.jj++) {
      ContModelSIL_B.Product8[ContModelSIL_B.jj] += ContModelSIL_B.BMinv
        [(ContModelSIL_B.c_j << 3) + ContModelSIL_B.jj] * ContModelSIL_B.D17;
    }
  }

  // DigitalClock: '<S6>/Digital Clock'
  ContModelSIL_B.DigitalClock = ((ContModelSIL_M->Timing.clockTick0) * 0.01);

  // MATLABSystem: '<S6>/Polynomial Trajectory'
  propChange = true;
  ContModelSIL_B.c_j = 0;
  exitg1 = false;
  while (!exitg1 && (ContModelSIL_B.c_j < 32)) {
    if (!(ContModelSIL_DW.obj.Waypoints[ContModelSIL_B.c_j] ==
          ContModelSIL_P.Trajectory.Waypoints[ContModelSIL_B.c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      ContModelSIL_B.c_j++;
    }
  }

  if (!propChange) {
    if (ContModelSIL_DW.obj.isInitialized == 1) {
      ContModelSIL_DW.obj.TunablePropsChanged = true;
      ContModelSIL_DW.obj.tunablePropertyChanged[0] = true;
    }

    memcpy(&ContModelSIL_DW.obj.Waypoints[0],
           &ContModelSIL_P.Trajectory.Waypoints[0], sizeof(real_T) << 5U);
  }

  propChange = true;
  ContModelSIL_B.c_j = 0;
  exitg1 = false;
  while (!exitg1 && (ContModelSIL_B.c_j < 4)) {
    if (!(ContModelSIL_DW.obj.TimePoints[ContModelSIL_B.c_j] ==
          ContModelSIL_P.Trajectory.Tstamps[ContModelSIL_B.c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      ContModelSIL_B.c_j++;
    }
  }

  if (!propChange) {
    if (ContModelSIL_DW.obj.isInitialized == 1) {
      ContModelSIL_DW.obj.TunablePropsChanged = true;
      ContModelSIL_DW.obj.tunablePropertyChanged[1] = true;
    }

    ContModelSIL_DW.obj.TimePoints[0] = ContModelSIL_P.Trajectory.Tstamps[0];
    ContModelSIL_DW.obj.TimePoints[1] = ContModelSIL_P.Trajectory.Tstamps[1];
    ContModelSIL_DW.obj.TimePoints[2] = ContModelSIL_P.Trajectory.Tstamps[2];
    ContModelSIL_DW.obj.TimePoints[3] = ContModelSIL_P.Trajectory.Tstamps[3];
  }

  propChange = true;
  ContModelSIL_B.c_j = 0;
  exitg1 = false;
  while (!exitg1 && (ContModelSIL_B.c_j < 32)) {
    if (!(ContModelSIL_DW.obj.VelocityBoundaryCondition[ContModelSIL_B.c_j] ==
          ContModelSIL_P.PolynomialTrajectory_VelocityBo[ContModelSIL_B.c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      ContModelSIL_B.c_j++;
    }
  }

  if (!propChange) {
    if (ContModelSIL_DW.obj.isInitialized == 1) {
      ContModelSIL_DW.obj.TunablePropsChanged = true;
      ContModelSIL_DW.obj.tunablePropertyChanged[3] = true;
    }

    memcpy(&ContModelSIL_DW.obj.VelocityBoundaryCondition[0],
           &ContModelSIL_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) <<
           5U);
  }

  if (ContModelSIL_DW.obj.TunablePropsChanged) {
    ContModelSIL_DW.obj.TunablePropsChanged = false;
    if (ContModelSIL_DW.obj.tunablePropertyChanged[0] ||
        ContModelSIL_DW.obj.tunablePropertyChanged[1] ||
        ContModelSIL_DW.obj.tunablePropertyChanged[2]) {
      propChange = true;
    } else {
      propChange = false;
    }

    if (!propChange) {
      if (ContModelSIL_DW.obj.tunablePropertyChanged[3] ||
          ContModelSIL_DW.obj.tunablePropertyChanged[4]) {
        propChange = true;
      } else {
        propChange = false;
      }
    }

    ContModelSIL_DW.obj.PPFormUpdatedNeeded = propChange;
    if (ContModelSIL_DW.obj.PPFormUpdatedNeeded) {
      PolyTrajSys_regeneratePPFormFro(&ContModelSIL_DW.obj,
        ContModelSIL_DW.obj.Waypoints, ContModelSIL_DW.obj.TimePoints);
    }

    for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 5; ContModelSIL_B.c_j++) {
      ContModelSIL_DW.obj.tunablePropertyChanged[ContModelSIL_B.c_j] = false;
    }
  }

  // MATLABSystem: '<S4>/SourceBlock' incorporates:
  //   Constant: '<S4>/Constant'

  ContModelSIL_B.r1 = ContModelSIL_P.Constant_Value_p;

  // MATLABSystem: '<S5>/SourceBlock' incorporates:
  //   Constant: '<S5>/Constant'

  ContModelSIL_B.r = ContModelSIL_P.Constant_Value;

  // MATLABSystem: '<S6>/Polynomial Trajectory'
  ContModelSIL_B.u = ContModelSIL_B.DigitalClock;
  ContModelSIL_B.Observer_alpha = ContModelSIL_DW.obj.PPStruct.breaks[4];
  if (ContModelSIL_B.DigitalClock == ContModelSIL_DW.obj.PPStruct.breaks[4]) {
    for (i = 0; i < 1; i++) {
      ContModelSIL_B.u = ContModelSIL_B.Observer_alpha - 2.220446049250313E-15;
    }
  }

  ContModelSIL_ppval(ContModelSIL_DW.obj.PPStruct.breaks,
                     ContModelSIL_DW.obj.PPStruct.coefs,
                     ContModelSIL_B.DigitalClock, ContModelSIL_B.dv1);

  // MATLAB Function: '<S10>/PD Controller' incorporates:
  //   Constant: '<S10>/Kp'

  ContModelSIL_B.dv[0] = ContModelSIL_P.PID.Kp[0];
  ContModelSIL_B.dv[8] = 0.0;
  ContModelSIL_B.dv[16] = 0.0;
  ContModelSIL_B.dv[24] = 0.0;
  ContModelSIL_B.dv[32] = 0.0;
  ContModelSIL_B.dv[40] = 0.0;
  ContModelSIL_B.dv[48] = 0.0;
  ContModelSIL_B.dv[56] = 0.0;
  ContModelSIL_B.dv[1] = 0.0;
  ContModelSIL_B.dv[9] = ContModelSIL_P.PID.Kp[1];
  ContModelSIL_B.dv[17] = 0.0;
  ContModelSIL_B.dv[25] = 0.0;
  ContModelSIL_B.dv[33] = 0.0;
  ContModelSIL_B.dv[41] = 0.0;
  ContModelSIL_B.dv[49] = 0.0;
  ContModelSIL_B.dv[57] = 0.0;
  ContModelSIL_B.dv[2] = 0.0;
  ContModelSIL_B.dv[10] = 0.0;
  ContModelSIL_B.dv[18] = ContModelSIL_P.PID.Kp[2];
  ContModelSIL_B.dv[26] = 0.0;
  ContModelSIL_B.dv[34] = 0.0;
  ContModelSIL_B.dv[42] = 0.0;
  ContModelSIL_B.dv[50] = 0.0;
  ContModelSIL_B.dv[58] = 0.0;
  ContModelSIL_B.dv[3] = 0.0;
  ContModelSIL_B.dv[11] = 0.0;
  ContModelSIL_B.dv[19] = 0.0;
  ContModelSIL_B.dv[27] = ContModelSIL_P.PID.Kp[3];
  ContModelSIL_B.dv[35] = 0.0;
  ContModelSIL_B.dv[43] = 0.0;
  ContModelSIL_B.dv[51] = 0.0;
  ContModelSIL_B.dv[59] = 0.0;
  ContModelSIL_B.dv[4] = 0.0;
  ContModelSIL_B.dv[12] = 0.0;
  ContModelSIL_B.dv[20] = 0.0;
  ContModelSIL_B.dv[28] = 0.0;
  ContModelSIL_B.dv[36] = ContModelSIL_P.PID.Kp[4];
  ContModelSIL_B.dv[44] = 0.0;
  ContModelSIL_B.dv[52] = 0.0;
  ContModelSIL_B.dv[60] = 0.0;
  ContModelSIL_B.dv[5] = 0.0;
  ContModelSIL_B.dv[13] = 0.0;
  ContModelSIL_B.dv[21] = 0.0;
  ContModelSIL_B.dv[29] = 0.0;
  ContModelSIL_B.dv[37] = 0.0;
  ContModelSIL_B.dv[45] = ContModelSIL_P.PID.Kp[5];
  ContModelSIL_B.dv[53] = 0.0;
  ContModelSIL_B.dv[61] = 0.0;
  ContModelSIL_B.dv[6] = 0.0;
  ContModelSIL_B.dv[14] = 0.0;
  ContModelSIL_B.dv[22] = 0.0;
  ContModelSIL_B.dv[30] = 0.0;
  ContModelSIL_B.dv[38] = 0.0;
  ContModelSIL_B.dv[46] = 0.0;
  ContModelSIL_B.dv[54] = ContModelSIL_P.PID.Kp[6];
  ContModelSIL_B.dv[62] = 0.0;
  ContModelSIL_B.dv[7] = 0.0;
  ContModelSIL_B.dv[15] = 0.0;
  ContModelSIL_B.dv[23] = 0.0;
  ContModelSIL_B.dv[31] = 0.0;
  ContModelSIL_B.dv[39] = 0.0;
  ContModelSIL_B.dv[47] = 0.0;
  ContModelSIL_B.dv[55] = 0.0;
  ContModelSIL_B.dv[63] = ContModelSIL_P.PID.Kp[7];

  // MATLABSystem: '<S6>/Polynomial Trajectory'
  ContModelSIL_ppval(ContModelSIL_DW.obj.PPDStruct.breaks,
                     ContModelSIL_DW.obj.PPDStruct.coefs, ContModelSIL_B.u,
                     ContModelSIL_B.dv3);

  // MATLAB Function: '<S10>/PD Controller' incorporates:
  //   Constant: '<S10>/Kd'

  ContModelSIL_B.ginv[0] = ContModelSIL_P.PID.Kd[0];
  ContModelSIL_B.ginv[8] = 0.0;
  ContModelSIL_B.ginv[16] = 0.0;
  ContModelSIL_B.ginv[24] = 0.0;
  ContModelSIL_B.ginv[32] = 0.0;
  ContModelSIL_B.ginv[40] = 0.0;
  ContModelSIL_B.ginv[48] = 0.0;
  ContModelSIL_B.ginv[56] = 0.0;
  ContModelSIL_B.ginv[1] = 0.0;
  ContModelSIL_B.ginv[9] = ContModelSIL_P.PID.Kd[1];
  ContModelSIL_B.ginv[17] = 0.0;
  ContModelSIL_B.ginv[25] = 0.0;
  ContModelSIL_B.ginv[33] = 0.0;
  ContModelSIL_B.ginv[41] = 0.0;
  ContModelSIL_B.ginv[49] = 0.0;
  ContModelSIL_B.ginv[57] = 0.0;
  ContModelSIL_B.ginv[2] = 0.0;
  ContModelSIL_B.ginv[10] = 0.0;
  ContModelSIL_B.ginv[18] = ContModelSIL_P.PID.Kd[2];
  ContModelSIL_B.ginv[26] = 0.0;
  ContModelSIL_B.ginv[34] = 0.0;
  ContModelSIL_B.ginv[42] = 0.0;
  ContModelSIL_B.ginv[50] = 0.0;
  ContModelSIL_B.ginv[58] = 0.0;
  ContModelSIL_B.ginv[3] = 0.0;
  ContModelSIL_B.ginv[11] = 0.0;
  ContModelSIL_B.ginv[19] = 0.0;
  ContModelSIL_B.ginv[27] = ContModelSIL_P.PID.Kd[3];
  ContModelSIL_B.ginv[35] = 0.0;
  ContModelSIL_B.ginv[43] = 0.0;
  ContModelSIL_B.ginv[51] = 0.0;
  ContModelSIL_B.ginv[59] = 0.0;
  ContModelSIL_B.ginv[4] = 0.0;
  ContModelSIL_B.ginv[12] = 0.0;
  ContModelSIL_B.ginv[20] = 0.0;
  ContModelSIL_B.ginv[28] = 0.0;
  ContModelSIL_B.ginv[36] = ContModelSIL_P.PID.Kd[4];
  ContModelSIL_B.ginv[44] = 0.0;
  ContModelSIL_B.ginv[52] = 0.0;
  ContModelSIL_B.ginv[60] = 0.0;
  ContModelSIL_B.ginv[5] = 0.0;
  ContModelSIL_B.ginv[13] = 0.0;
  ContModelSIL_B.ginv[21] = 0.0;
  ContModelSIL_B.ginv[29] = 0.0;
  ContModelSIL_B.ginv[37] = 0.0;
  ContModelSIL_B.ginv[45] = ContModelSIL_P.PID.Kd[5];
  ContModelSIL_B.ginv[53] = 0.0;
  ContModelSIL_B.ginv[61] = 0.0;
  ContModelSIL_B.ginv[6] = 0.0;
  ContModelSIL_B.ginv[14] = 0.0;
  ContModelSIL_B.ginv[22] = 0.0;
  ContModelSIL_B.ginv[30] = 0.0;
  ContModelSIL_B.ginv[38] = 0.0;
  ContModelSIL_B.ginv[46] = 0.0;
  ContModelSIL_B.ginv[54] = ContModelSIL_P.PID.Kd[6];
  ContModelSIL_B.ginv[62] = 0.0;
  ContModelSIL_B.ginv[7] = 0.0;
  ContModelSIL_B.ginv[15] = 0.0;
  ContModelSIL_B.ginv[23] = 0.0;
  ContModelSIL_B.ginv[31] = 0.0;
  ContModelSIL_B.ginv[39] = 0.0;
  ContModelSIL_B.ginv[47] = 0.0;
  ContModelSIL_B.ginv[55] = 0.0;
  ContModelSIL_B.ginv[63] = ContModelSIL_P.PID.Kd[7];
  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    // Sum: '<S12>/Minus' incorporates:
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator'

    ContModelSIL_B.dv2[ContModelSIL_B.c_j] =
      ContModelSIL_B.dv1[ContModelSIL_B.c_j] -
      ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[ContModelSIL_B.c_j];

    // Sum: '<S12>/Minus1' incorporates:
    //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator1'

    ContModelSIL_B.dv4[ContModelSIL_B.c_j] =
      ContModelSIL_B.dv3[ContModelSIL_B.c_j] -
      ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[ContModelSIL_B.c_j];

    // MATLAB Function: '<S10>/PD Controller'
    ContModelSIL_B.dv5[ContModelSIL_B.c_j] = 0.0;
  }

  // MATLAB Function: '<S10>/PD Controller'
  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.D17 = ContModelSIL_B.dv2[ContModelSIL_B.c_j];
    for (ContModelSIL_B.jj = 0; ContModelSIL_B.jj < 8; ContModelSIL_B.jj++) {
      ContModelSIL_B.dv5[ContModelSIL_B.jj] += ContModelSIL_B.dv
        [(ContModelSIL_B.c_j << 3) + ContModelSIL_B.jj] * ContModelSIL_B.D17;
    }
  }

  memset(&ContModelSIL_B.dv1[0], 0, sizeof(real_T) << 3U);
  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.D17 = ContModelSIL_B.dv4[ContModelSIL_B.c_j];
    for (ContModelSIL_B.jj = 0; ContModelSIL_B.jj < 8; ContModelSIL_B.jj++) {
      ContModelSIL_B.dv1[ContModelSIL_B.jj] += ContModelSIL_B.ginv
        [(ContModelSIL_B.c_j << 3) + ContModelSIL_B.jj] * ContModelSIL_B.D17;
    }
  }

  // MATLABSystem: '<S6>/Polynomial Trajectory'
  ContModelSIL_ppval(ContModelSIL_DW.obj.PPDDStruct.breaks,
                     ContModelSIL_DW.obj.PPDDStruct.coefs, ContModelSIL_B.u,
                     ContModelSIL_B.dv2);

  // Sum: '<S1>/Add1' incorporates:
  //   Delay: '<S1>/Delay'
  //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator3'
  //   MATLAB Function: '<S10>/PD Controller'

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_DW.Delay_DSTATE[ContModelSIL_B.c_j] =
      (((ContModelSIL_B.dv5[ContModelSIL_B.c_j] +
         ContModelSIL_B.dv1[ContModelSIL_B.c_j]) +
        ContModelSIL_B.dv2[ContModelSIL_B.c_j]) -
       ContModelSIL_DW.DiscreteTimeIntegrator3_DSTATE[ContModelSIL_B.c_j]) -
      ContModelSIL_B.Sign3[ContModelSIL_B.c_j];
  }

  // End of Sum: '<S1>/Add1'

  // Product: '<S7>/Product7' incorporates:
  //   Constant: '<S7>/Constant'
  //   Delay: '<S8>/Delay2'

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 6; ContModelSIL_B.c_j++) {
    ContModelSIL_B.dv6[ContModelSIL_B.c_j] = 0.0;
  }

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 6; ContModelSIL_B.c_j++) {
    ContModelSIL_B.D17 = ContModelSIL_B.Product8[ContModelSIL_B.c_j];
    for (ContModelSIL_B.jj = 0; ContModelSIL_B.jj < 6; ContModelSIL_B.jj++) {
      ContModelSIL_B.dv6[ContModelSIL_B.jj] += ContModelSIL_P.Constant_Value_e[6
        * ContModelSIL_B.c_j + ContModelSIL_B.jj] * ContModelSIL_B.D17;
    }
  }

  for (i = 0; i < 6; i++) {
    ContModelSIL_B.DigitalClock = ContModelSIL_B.dv6[i];

    // Saturate: '<S7>/Rotation Saturation1' incorporates:
    //   Delay: '<S8>/Delay2'

    if (ContModelSIL_B.DigitalClock >
        ContModelSIL_P.RotationSaturation1_UpperSat) {
      ContModelSIL_B.DigitalClock = ContModelSIL_P.RotationSaturation1_UpperSat;
    } else if (ContModelSIL_B.DigitalClock <
               ContModelSIL_P.RotationSaturation1_LowerSat) {
      ContModelSIL_B.DigitalClock = ContModelSIL_P.RotationSaturation1_LowerSat;
    }

    // MATLAB Function: '<Root>/MATLAB Function2' incorporates:
    //   Saturate: '<S7>/Rotation Saturation1'

    ContModelSIL_B.DS[i] = ContModelSIL_B.DigitalClock / 877000.0;
  }

  // End of Product: '<S7>/Product7'

  // MATLABSystem: '<S4>/SourceBlock'
  b_varargout_1 = uORB_read_topic_exists(ContModelSIL_DW.obj_d.orbMetadataObj, 0);
  if (b_varargout_1 != 2) {
    b_varargout_1 = uORB_read_step(ContModelSIL_DW.obj_d.orbMetadataObj,
      &ContModelSIL_DW.obj_d.eventStructObj, &ContModelSIL_B.r1, false, 1.0);
  }

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S16>/Enable'

  // RelationalOperator: '<S15>/Compare' incorporates:
  //   Constant: '<S15>/Constant'
  //   MATLABSystem: '<S4>/SourceBlock'
  //
  if (b_varargout_1 == ContModelSIL_P.CompareToConstant_const) {
    // SignalConversion generated from: '<S16>/In1'
    ContModelSIL_B.In1_h = ContModelSIL_B.r1;
  }

  // End of RelationalOperator: '<S15>/Compare'
  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'

  // MATLABSystem: '<Root>/PX4 Actuator Write' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion10'
  //   DataTypeConversion: '<Root>/Data Type Conversion11'
  //   DataTypeConversion: '<Root>/Data Type Conversion12'
  //   DataTypeConversion: '<Root>/Data Type Conversion13'
  //   DataTypeConversion: '<Root>/Data Type Conversion14'
  //   DataTypeConversion: '<Root>/Data Type Conversion15'

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 12; ContModelSIL_B.c_j++) {
    ContModelSIL_B.motorValues[ContModelSIL_B.c_j] = (rtNaNF);
  }

  for (ContModelSIL_B.c_j = 0; ContModelSIL_B.c_j < 8; ContModelSIL_B.c_j++) {
    ContModelSIL_B.servoValues[ContModelSIL_B.c_j] = (rtNaNF);
  }

  ContModelSIL_B.motorValues[0] = static_cast<real32_T>(ContModelSIL_B.DS[0]);
  ContModelSIL_B.motorValues[1] = static_cast<real32_T>(ContModelSIL_B.DS[1]);
  ContModelSIL_B.motorValues[2] = static_cast<real32_T>(ContModelSIL_B.DS[2]);
  ContModelSIL_B.motorValues[3] = static_cast<real32_T>(ContModelSIL_B.DS[3]);
  ContModelSIL_B.motorValues[4] = static_cast<real32_T>(ContModelSIL_B.DS[4]);
  ContModelSIL_B.motorValues[5] = static_cast<real32_T>(ContModelSIL_B.DS[5]);

  // Saturate: '<S1>/Torque Saturation1'
  if (ContModelSIL_B.Product8[6] > ContModelSIL_P.ArmConstants.Servos.T1max) {
    ContModelSIL_B.D17 = ContModelSIL_P.ArmConstants.Servos.T1max;
  } else if (ContModelSIL_B.Product8[6] <
             -ContModelSIL_P.ArmConstants.Servos.T1max) {
    ContModelSIL_B.D17 = -ContModelSIL_P.ArmConstants.Servos.T1max;
  } else {
    ContModelSIL_B.D17 = ContModelSIL_B.Product8[6];
  }

  // MATLABSystem: '<Root>/PX4 Actuator Write' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion9'
  //   MATLAB Function: '<Root>/MATLAB Function1'
  //   Saturate: '<S1>/Torque Saturation1'

  ContModelSIL_B.servoValues[0] = static_cast<real32_T>(ContModelSIL_B.D17 / 2.5);

  // Saturate: '<S1>/Torque Saturation1'
  if (ContModelSIL_B.Product8[7] > ContModelSIL_P.ArmConstants.Servos.T1max) {
    ContModelSIL_B.D17 = ContModelSIL_P.ArmConstants.Servos.T1max;
  } else if (ContModelSIL_B.Product8[7] <
             -ContModelSIL_P.ArmConstants.Servos.T1max) {
    ContModelSIL_B.D17 = -ContModelSIL_P.ArmConstants.Servos.T1max;
  } else {
    ContModelSIL_B.D17 = ContModelSIL_B.Product8[7];
  }

  // MATLABSystem: '<Root>/PX4 Actuator Write' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion8'
  //   MATLAB Function: '<Root>/MATLAB Function1'
  //   Saturate: '<S1>/Torque Saturation1'

  ContModelSIL_B.servoValues[1] = static_cast<real32_T>(ContModelSIL_B.D17 / 2.5);
  MW_actuators_set(ContModelSIL_B.In1_h.armed, &ContModelSIL_B.motorValues[0],
                   &ContModelSIL_B.servoValues[0]);

  // MATLABSystem: '<S5>/SourceBlock'
  b_varargout_1 = uORB_read_topic_exists(ContModelSIL_DW.obj_h.orbMetadataObj, 0);
  if (b_varargout_1 != 2) {
    b_varargout_1 = uORB_read_step(ContModelSIL_DW.obj_h.orbMetadataObj,
      &ContModelSIL_DW.obj_h.eventStructObj, &ContModelSIL_B.r, false, 1.0);
  }

  // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S18>/Enable'

  // RelationalOperator: '<S17>/Compare' incorporates:
  //   Constant: '<S17>/Constant'
  //   MATLABSystem: '<S5>/SourceBlock'
  //
  if (b_varargout_1 == ContModelSIL_P.CompareToConstant_const_o) {
    // SignalConversion generated from: '<S18>/In1'
    ContModelSIL_B.In1 = ContModelSIL_B.r;
  }

  // End of RelationalOperator: '<S17>/Compare'
  // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'

  // Sum: '<S8>/Sum8' incorporates:
  //   Delay: '<S8>/Delay'

  ContModelSIL_DW.Delay2_DSTATE[0] = ContModelSIL_B.In1.x -
    ContModelSIL_DW.Delay_DSTATE_a[0];
  ContModelSIL_DW.Delay2_DSTATE[1] = ContModelSIL_B.In1.y -
    ContModelSIL_DW.Delay_DSTATE_a[1];
  ContModelSIL_DW.Delay2_DSTATE[2] = ContModelSIL_B.In1.z -
    ContModelSIL_DW.Delay_DSTATE_a[2];
  ContModelSIL_DW.Delay2_DSTATE[3] = ContModelSIL_B.In1.roll -
    ContModelSIL_DW.Delay_DSTATE_a[3];
  ContModelSIL_DW.Delay2_DSTATE[4] = ContModelSIL_B.In1.pitch -
    ContModelSIL_DW.Delay_DSTATE_a[4];
  ContModelSIL_DW.Delay2_DSTATE[5] = ContModelSIL_B.In1.yaw -
    ContModelSIL_DW.Delay_DSTATE_a[5];
  ContModelSIL_DW.Delay2_DSTATE[6] = ContModelSIL_B.In1.linkone -
    ContModelSIL_DW.Delay_DSTATE_a[6];
  ContModelSIL_DW.Delay2_DSTATE[7] = ContModelSIL_B.In1.linktwo -
    ContModelSIL_DW.Delay_DSTATE_a[7];

  // Update for Delay: '<S8>/Delay3' incorporates:
  //   Sum: '<S8>/Sum8'

  memcpy(&ContModelSIL_DW.Delay3_DSTATE[0], &ContModelSIL_DW.Delay2_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S8>/Delay7' incorporates:
  //   Sum: '<S8>/Sum8'

  memcpy(&ContModelSIL_DW.Delay7_DSTATE[0], &ContModelSIL_DW.Delay2_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S8>/Delay9' incorporates:
  //   Sum: '<S8>/Sum8'

  memcpy(&ContModelSIL_DW.Delay9_DSTATE[0], &ContModelSIL_DW.Delay2_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S8>/Delay8' incorporates:
  //   Sum: '<S8>/Sum8'

  memcpy(&ContModelSIL_DW.Delay8_DSTATE[0], &ContModelSIL_DW.Delay2_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S8>/Delay6' incorporates:
  //   Sum: '<S8>/Sum8'

  memcpy(&ContModelSIL_DW.Delay6_DSTATE[0], &ContModelSIL_DW.Delay2_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S8>/Delay1' incorporates:
  //   Sum: '<S8>/Sum8'

  memcpy(&ContModelSIL_DW.Delay1_DSTATE[0], &ContModelSIL_DW.Delay2_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S8>/Delay' incorporates:
  //   DiscreteIntegrator: '<S8>/Discrete-Time Integrator'

  memcpy(&ContModelSIL_DW.Delay_DSTATE_a[0],
         &ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[0], sizeof(real_T) << 3U);

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  ContModelSIL_M->Timing.clockTick0++;
}

// Model initialize function
void ContModelSIL_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;
    static const boolean_T tmp[12] = { true, true, true, true, true, true, false,
      false, false, false, false, false };

    static const boolean_T tmp_0[8] = { true, true, false, false, false, false,
      false, false };

    // InitializeConditions for Delay: '<S8>/Delay5'
    for (i = 0; i < 64; i++) {
      ContModelSIL_DW.Delay5_DSTATE[i] = ContModelSIL_P.Delay5_InitialCondition;
    }

    // End of InitializeConditions for Delay: '<S8>/Delay5'
    for (i = 0; i < 8; i++) {
      // InitializeConditions for Delay: '<S8>/Delay2'
      ContModelSIL_DW.Delay2_DSTATE[i] = ContModelSIL_P.Delay2_InitialCondition;

      // InitializeConditions for Delay: '<S8>/Delay3'
      ContModelSIL_DW.Delay3_DSTATE[i] = ContModelSIL_P.Delay3_InitialCondition;

      // InitializeConditions for Delay: '<S8>/Delay7'
      ContModelSIL_DW.Delay7_DSTATE[i] = ContModelSIL_P.Delay7_InitialCondition;

      // InitializeConditions for Delay: '<S8>/Delay9'
      ContModelSIL_DW.Delay9_DSTATE[i] = ContModelSIL_P.Delay9_InitialCondition;

      // InitializeConditions for Delay: '<S8>/Delay8'
      ContModelSIL_DW.Delay8_DSTATE[i] = ContModelSIL_P.Delay8_InitialCondition;

      // InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator3' 
      ContModelSIL_DW.DiscreteTimeIntegrator3_DSTATE[i] =
        ContModelSIL_P.DiscreteTimeIntegrator3_IC[i];

      // InitializeConditions for Delay: '<S8>/Delay4'
      ContModelSIL_DW.Delay4_DSTATE[i] = ContModelSIL_P.Delay4_InitialCondition;

      // InitializeConditions for Delay: '<S8>/Delay6'
      ContModelSIL_DW.Delay6_DSTATE[i] = ContModelSIL_P.Delay6_InitialCondition;

      // InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator1' 
      ContModelSIL_DW.DiscreteTimeIntegrator1_DSTATE[i] =
        ContModelSIL_P.DiscreteTimeIntegrator1_IC[i];

      // InitializeConditions for Delay: '<S8>/Delay1'
      ContModelSIL_DW.Delay1_DSTATE[i] = ContModelSIL_P.Delay1_InitialCondition;

      // InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' 
      ContModelSIL_DW.DiscreteTimeIntegrator_DSTATE[i] =
        ContModelSIL_P.DiscreteTimeIntegrator_IC[i];

      // InitializeConditions for Delay: '<S1>/Delay'
      ContModelSIL_DW.Delay_DSTATE[i] = ContModelSIL_P.Delay_InitialCondition;

      // InitializeConditions for Delay: '<S8>/Delay'
      ContModelSIL_DW.Delay_DSTATE_a[i] =
        ContModelSIL_P.Delay_InitialCondition_b;
    }

    // SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S16>/In1' incorporates:
    //   Outport: '<S16>/Out1'

    ContModelSIL_B.In1_h = ContModelSIL_P.Out1_Y0_o;

    // End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem'

    // SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S18>/In1' incorporates:
    //   Outport: '<S18>/Out1'

    ContModelSIL_B.In1 = ContModelSIL_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem'

    // Start for MATLABSystem: '<S6>/Polynomial Trajectory'
    memset(&ContModelSIL_DW.obj.AccelerationBoundaryCondition[0], 0, 10U *
           sizeof(real_T));
    for (i = 0; i < 5; i++) {
      ContModelSIL_DW.obj.tunablePropertyChanged[i] = false;
    }

    ContModelSIL_DW.obj.TimePoints[0] = ContModelSIL_P.Trajectory.Tstamps[0];
    ContModelSIL_DW.obj.TimePoints[1] = ContModelSIL_P.Trajectory.Tstamps[1];
    ContModelSIL_DW.obj.TimePoints[2] = ContModelSIL_P.Trajectory.Tstamps[2];
    ContModelSIL_DW.obj.TimePoints[3] = ContModelSIL_P.Trajectory.Tstamps[3];
    memcpy(&ContModelSIL_DW.obj.Waypoints[0],
           &ContModelSIL_P.Trajectory.Waypoints[0], sizeof(real_T) << 5U);
    memcpy(&ContModelSIL_DW.obj.VelocityBoundaryCondition[0],
           &ContModelSIL_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) <<
           5U);
    ContModelSIL_DW.obj.isInitialized = 1;
    PolyTrajSys_regeneratePPFormFro(&ContModelSIL_DW.obj,
      ContModelSIL_DW.obj.Waypoints, ContModelSIL_DW.obj.TimePoints);
    ContModelSIL_DW.obj.TunablePropsChanged = false;

    // End of Start for MATLABSystem: '<S6>/Polynomial Trajectory'

    // Start for MATLABSystem: '<S4>/SourceBlock'
    ContModelSIL_DW.obj_d.matlabCodegenIsDeleted = false;
    ContModelSIL_DW.obj_d.isSetupComplete = false;
    ContModelSIL_DW.obj_d.isInitialized = 1;
    ContModelSIL_DW.obj_d.orbMetadataObj = ORB_ID(actuator_armed);
    uORB_read_initialize(ContModelSIL_DW.obj_d.orbMetadataObj,
                         &ContModelSIL_DW.obj_d.eventStructObj);
    ContModelSIL_DW.obj_d.isSetupComplete = true;

    // Start for MATLABSystem: '<Root>/PX4 Actuator Write'
    ContModelSIL_DW.obj_a.matlabCodegenIsDeleted = false;
    ContModelSIL_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      ContModelSIL_DW.obj_a.ValidMotorIdx[i] = tmp[i];
    }

    for (i = 0; i < 8; i++) {
      ContModelSIL_DW.obj_a.ValidServoIdx[i] = tmp_0[i];
    }

    MW_actuators_init();
    ContModelSIL_DW.obj_a.isSetupComplete = true;

    // End of Start for MATLABSystem: '<Root>/PX4 Actuator Write'

    // Start for MATLABSystem: '<S5>/SourceBlock'
    ContModelSIL_DW.obj_h.matlabCodegenIsDeleted = false;
    ContModelSIL_DW.obj_h.isSetupComplete = false;
    ContModelSIL_DW.obj_h.isInitialized = 1;
    ContModelSIL_DW.obj_h.orbMetadataObj = ORB_ID(uam_states);
    uORB_read_initialize(ContModelSIL_DW.obj_h.orbMetadataObj,
                         &ContModelSIL_DW.obj_h.eventStructObj);
    ContModelSIL_DW.obj_h.isSetupComplete = true;
  }
}

// Model terminate function
void ContModelSIL_terminate(void)
{
  real32_T servoValues[8];

  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  if (!ContModelSIL_DW.obj_d.matlabCodegenIsDeleted) {
    ContModelSIL_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((ContModelSIL_DW.obj_d.isInitialized == 1) &&
        ContModelSIL_DW.obj_d.isSetupComplete) {
      uORB_read_terminate(&ContModelSIL_DW.obj_d.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S4>/SourceBlock'

  // Terminate for MATLABSystem: '<Root>/PX4 Actuator Write'
  if (!ContModelSIL_DW.obj_a.matlabCodegenIsDeleted) {
    ContModelSIL_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((ContModelSIL_DW.obj_a.isInitialized == 1) &&
        ContModelSIL_DW.obj_a.isSetupComplete) {
      for (int32_T i = 0; i < 12; i++) {
        ContModelSIL_B.motorValues_m[i] = (rtNaNF);
      }

      for (int32_T i = 0; i < 8; i++) {
        servoValues[i] = (rtNaNF);
      }

      for (int32_T i = 0; i < 12; i++) {
        if (ContModelSIL_DW.obj_a.ValidMotorIdx[i]) {
          ContModelSIL_B.motorValues_m[i] = 0.0F;
        }
      }

      for (int32_T i = 0; i < 8; i++) {
        if (ContModelSIL_DW.obj_a.ValidServoIdx[i]) {
          servoValues[i] = 0.0F;
        }
      }

      MW_actuators_set(false, &ContModelSIL_B.motorValues_m[0], &servoValues[0]);
      MW_actuators_terminate();
    }
  }

  // End of Terminate for MATLABSystem: '<Root>/PX4 Actuator Write'

  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!ContModelSIL_DW.obj_h.matlabCodegenIsDeleted) {
    ContModelSIL_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((ContModelSIL_DW.obj_h.isInitialized == 1) &&
        ContModelSIL_DW.obj_h.isSetupComplete) {
      uORB_read_terminate(&ContModelSIL_DW.obj_h.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
}

const char_T* RT_MODEL_ContModelSIL_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_ContModelSIL_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
