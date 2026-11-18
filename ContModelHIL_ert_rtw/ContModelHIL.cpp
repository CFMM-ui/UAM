//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ContModelHIL.cpp
//
// Code generated for Simulink model 'ContModelHIL'.
//
// Model version                  : 1.111
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Tue Nov 17 11:15:51 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "ContModelHIL.h"
#include "MW_PX4_Actuators.h"
#include "rtwtypes.h"
#include "ContModelHIL_types.h"
#include <math.h>

extern "C"
{

#include "rt_nonfinite.h"

}

#include "ContModelHIL_private.h"
#include <string.h>

// Block signals (default storage)
B_ContModelHIL_T ContModelHIL_B;

// Block states (default storage)
DW_ContModelHIL_T ContModelHIL_DW;

// Real-time model
RT_MODEL_ContModelHIL_T ContModelHIL_M_ = RT_MODEL_ContModelHIL_T();
RT_MODEL_ContModelHIL_T *const ContModelHIL_M = &ContModelHIL_M_;

// Forward declaration for local functions
static void ContModelHIL_xzgetrf(real_T A[64], int32_T ipiv[8], int32_T *info);
static void ContModelHIL_inv(const real_T x[64], real_T y[64]);
static void ContModelHIL_mldivide_p(const real_T A[64], real_T B[8]);
static void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
  const real_T waypoints[32], const real_T timeData[4]);
static void ContModelHIL_ppval(const real_T pp_breaks[6], const real_T pp_coefs
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
static void ContModelHIL_xzgetrf(real_T A[64], int32_T ipiv[8], int32_T *info)
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
    ContModelHIL_B.smax = fabs(A[jj]);
    for (int32_T k = 2; k < n; k++) {
      ContModelHIL_B.s = fabs(A[(jj + k) - 1]);
      if (ContModelHIL_B.s > ContModelHIL_B.smax) {
        a = k - 1;
        ContModelHIL_B.smax = ContModelHIL_B.s;
      }
    }

    if (A[jj + a] != 0.0) {
      if (a != 0) {
        a += j;
        ipiv[j] = a + 1;
        for (int32_T k = 0; k < 8; k++) {
          n = k << 3;
          jA = n + j;
          ContModelHIL_B.smax = A[jA];
          n += a;
          A[jA] = A[n];
          A[n] = ContModelHIL_B.smax;
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
      ContModelHIL_B.smax = A[((k << 3) + jj) + 8];
      if (ContModelHIL_B.smax != 0.0) {
        int32_T c;
        c = (jA - j) + 6;
        for (n = jA; n <= c; n++) {
          A[n - 1] += A[((jj + n) - jA) + 1] * -ContModelHIL_B.smax;
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
static void ContModelHIL_inv(const real_T x[64], real_T y[64])
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
    ContModelHIL_B.b_x[info] = x[info];
  }

  ContModelHIL_xzgetrf(ContModelHIL_B.b_x, ContModelHIL_B.ipiv, &info);
  for (info = 0; info < 8; info++) {
    ContModelHIL_B.p[info] = static_cast<int8_T>(info + 1);
  }

  for (info = 0; info < 7; info++) {
    ipiv = ContModelHIL_B.ipiv[info];
    if (ipiv > info + 1) {
      pipk = ContModelHIL_B.p[ipiv - 1];
      ContModelHIL_B.p[ipiv - 1] = ContModelHIL_B.p[info];
      ContModelHIL_B.p[info] = static_cast<int8_T>(pipk);
    }
  }

  for (pipk = 0; pipk < 8; pipk++) {
    ipiv = (ContModelHIL_B.p[pipk] - 1) << 3;
    y[pipk + ipiv] = 1.0;
    for (jBcol = pipk + 1; jBcol < 9; jBcol++) {
      info = (ipiv + jBcol) - 1;
      if (y[info] != 0.0) {
        for (i = jBcol + 1; i < 9; i++) {
          kAcol = (ipiv + i) - 1;
          y[kAcol] -= ContModelHIL_B.b_x[(((jBcol - 1) << 3) + i) - 1] * y[info];
        }
      }
    }
  }

  for (pipk = 0; pipk < 8; pipk++) {
    jBcol = pipk << 3;
    for (i = 7; i >= 0; i--) {
      kAcol = i << 3;
      info = i + jBcol;
      ContModelHIL_B.d186 = y[info];
      if (ContModelHIL_B.d186 != 0.0) {
        y[info] = ContModelHIL_B.d186 / ContModelHIL_B.b_x[i + kAcol];
        for (b_i = 0; b_i < i; b_i++) {
          ipiv = b_i + jBcol;
          y[ipiv] -= ContModelHIL_B.b_x[b_i + kAcol] * y[info];
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
static void ContModelHIL_mldivide_p(const real_T A[64], real_T B[8])
{
  real_T temp;
  int32_T info;
  int32_T ipiv;
  int32_T kAcol;
  memcpy(&ContModelHIL_B.b_A[0], &A[0], sizeof(real_T) << 6U);
  ContModelHIL_xzgetrf(ContModelHIL_B.b_A, ContModelHIL_B.ipiv_c, &info);
  for (info = 0; info < 7; info++) {
    ipiv = ContModelHIL_B.ipiv_c[info];
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
        B[ipiv - 1] -= ContModelHIL_B.b_A[(ipiv + kAcol) - 1] * B[info];
      }
    }
  }

  for (info = 7; info >= 0; info--) {
    kAcol = info << 3;
    temp = B[info];
    if (temp != 0.0) {
      B[info] = temp / ContModelHIL_B.b_A[info + kAcol];
      for (ipiv = 0; ipiv < info; ipiv++) {
        B[ipiv] -= ContModelHIL_B.b_A[ipiv + kAcol] * B[info];
      }
    }
  }
}

static void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
  const real_T waypoints[32], const real_T timeData[4])
{
  real_T coefMat_tmp;
  real_T waypoints_idx_0;
  real_T waypoints_idx_1;
  int32_T b_coeffVec_tmp;
  int32_T b_i;
  int32_T b_j;
  static const int8_T tmp[4] = { 0, 0, 0, 1 };

  memset(&ContModelHIL_B.coefMat[0], 0, 96U * sizeof(real_T));
  for (b_i = 0; b_i < 3; b_i++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    ContModelHIL_B.finalTime = timeData[b_i + 1] - timeData[b_i];
    for (b_j = 0; b_j < 8; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      b_coeffVec_tmp = (b_i << 3) + b_j;
      ContModelHIL_B.b_coeffVec[0] = waypoints[b_coeffVec_tmp];
      ContModelHIL_B.b_coeffVec[1] = obj->
        VelocityBoundaryCondition[b_coeffVec_tmp];
      b_coeffVec_tmp = ((b_i + 1) << 3) + b_j;
      waypoints_idx_0 = waypoints[b_coeffVec_tmp] - (ContModelHIL_B.finalTime *
        ContModelHIL_B.b_coeffVec[1] + ContModelHIL_B.b_coeffVec[0]);
      waypoints_idx_1 = obj->VelocityBoundaryCondition[b_coeffVec_tmp] - (0.0 *
        ContModelHIL_B.b_coeffVec[0] + ContModelHIL_B.b_coeffVec[1]);
      ContModelHIL_B.b_coeffVec[3] = ContModelHIL_B.b_coeffVec[0];
      b_coeffVec_tmp = ((b_i << 3) + b_j) + 1;
      coefMat_tmp = ContModelHIL_B.finalTime * ContModelHIL_B.finalTime;
      ContModelHIL_B.coefMat[b_coeffVec_tmp - 1] = 1.0 / coefMat_tmp *
        waypoints_idx_1 + -2.0 / rt_powd_snf(ContModelHIL_B.finalTime, 3.0) *
        waypoints_idx_0;
      ContModelHIL_B.coefMat[b_coeffVec_tmp + 23] = 3.0 / coefMat_tmp *
        waypoints_idx_0 + -1.0 / ContModelHIL_B.finalTime * waypoints_idx_1;
      ContModelHIL_B.coefMat[b_coeffVec_tmp + 47] = ContModelHIL_B.b_coeffVec[1];
      ContModelHIL_B.coefMat[b_coeffVec_tmp + 71] = ContModelHIL_B.b_coeffVec[3];
    }
  }

  memset(&ContModelHIL_B.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&ContModelHIL_B.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    b_i = tmp[b_j];
    for (b_coeffVec_tmp = 0; b_coeffVec_tmp < 8; b_coeffVec_tmp++) {
      ContModelHIL_B.coeffMat[b_coeffVec_tmp + 24] += ContModelHIL_B.coefMat[24 *
        b_j + b_coeffVec_tmp] * static_cast<real_T>(b_i);
    }
  }

  memset(&ContModelHIL_B.coefsWithFlatStart[0], 0, sizeof(real_T) << 7U);
  memcpy(&ContModelHIL_B.coefsWithFlatStart[0], &ContModelHIL_B.coeffMat[0],
         sizeof(real_T) << 3U);
  memcpy(&ContModelHIL_B.coefsWithFlatStart[32], &ContModelHIL_B.coeffMat[8],
         sizeof(real_T) << 3U);
  memcpy(&ContModelHIL_B.coefsWithFlatStart[64], &ContModelHIL_B.coeffMat[16],
         sizeof(real_T) << 3U);
  memcpy(&ContModelHIL_B.coefsWithFlatStart[96], &ContModelHIL_B.coeffMat[24],
         sizeof(real_T) << 3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&ContModelHIL_B.coefsWithFlatStart[8], &ContModelHIL_B.coefMat[0], 24U *
         sizeof(real_T));
  memcpy(&ContModelHIL_B.coefsWithFlatStart[40], &ContModelHIL_B.coefMat[24],
         24U * sizeof(real_T));
  memcpy(&ContModelHIL_B.coefsWithFlatStart[72], &ContModelHIL_B.coefMat[48],
         24U * sizeof(real_T));
  memcpy(&ContModelHIL_B.coefsWithFlatStart[104], &ContModelHIL_B.coefMat[72],
         24U * sizeof(real_T));
  ContModelHIL_B.breaksWithFlatStart[0] = timeData[0] - 1.0;
  ContModelHIL_B.breaksWithFlatStart[1] = timeData[0];
  ContModelHIL_B.breaksWithFlatStart[2] = timeData[1];
  ContModelHIL_B.breaksWithFlatStart[3] = timeData[2];
  ContModelHIL_B.breaksWithFlatStart[4] = timeData[3];
  ContModelHIL_B.finalTime = timeData[3] - timeData[2];
  ContModelHIL_B.b_coeffVec[0] = rt_powd_snf(ContModelHIL_B.finalTime, 3.0);
  ContModelHIL_B.b_coeffVec[1] = rt_powd_snf(ContModelHIL_B.finalTime, 2.0);
  ContModelHIL_B.b_coeffVec[2] = rt_powd_snf(ContModelHIL_B.finalTime, 1.0);
  ContModelHIL_B.b_coeffVec[3] = rt_powd_snf(ContModelHIL_B.finalTime, 0.0);
  memset(&ContModelHIL_B.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&ContModelHIL_B.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    ContModelHIL_B.finalTime = ContModelHIL_B.b_coeffVec[b_j];
    for (b_i = 0; b_i < 8; b_i++) {
      ContModelHIL_B.coeffMat[b_i + 24] += ContModelHIL_B.coefsWithFlatStart
        [((b_j << 5) + b_i) + 24] * ContModelHIL_B.finalTime;
    }
  }

  memset(&obj->PPDStruct.coefs[0], 0, 160U * sizeof(real_T));
  for (b_j = 0; b_j < 4; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memcpy(&obj->PPDStruct.coefs[b_j * 40],
           &ContModelHIL_B.coefsWithFlatStart[b_j << 5], sizeof(real_T) << 5U);
    memcpy(&obj->PPDStruct.coefs[b_j * 40 + 32], &ContModelHIL_B.coeffMat[b_j <<
           3], sizeof(real_T) << 3U);
  }

  for (b_j = 0; b_j < 5; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    obj->PPStruct.breaks[b_j] = ContModelHIL_B.breaksWithFlatStart[b_j];
  }

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  obj->PPStruct.breaks[5] = timeData[3] + 1.0;
  for (b_j = 0; b_j < 160; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    obj->PPStruct.coefs[b_j] = obj->PPDStruct.coefs[b_j];
    obj->PPDStruct.coefs[b_j] = 0.0;
  }

  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 40; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      obj->PPDStruct.coefs[b_j + 40 * (b_i + 1)] = obj->PPStruct.coefs[b_i * 40
        + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  memset(&obj->PPDDStruct.coefs[0], 0, 160U * sizeof(real_T));
  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 40; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      obj->PPDDStruct.coefs[b_j + 40 * (b_i + 1)] = obj->PPDStruct.coefs[b_i *
        40 + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  for (b_j = 0; b_j < 6; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    obj->PPDStruct.breaks[b_j] = obj->PPStruct.breaks[b_j];
    obj->PPDDStruct.breaks[b_j] = obj->PPStruct.breaks[b_j];
  }

  obj->PPFormUpdatedNeeded = false;
}

static void ContModelHIL_ppval(const real_T pp_breaks[6], const real_T pp_coefs
  [160], real_T x, real_T v[8])
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

  // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
}

// Model step function
void ContModelHIL_step(void)
{
  real_T tmp;
  int32_T i;
  uint8_T b_varargout_1;
  boolean_T exitg1;
  boolean_T propChange;
  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    // Delay: '<S4>/Delay7' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator3'

    ContModelHIL_B.u = ContModelHIL_DW.Delay7_DSTATE[ContModelHIL_B.i];

    // Delay: '<S4>/Delay9' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator3'

    ContModelHIL_B.DigitalClock = ContModelHIL_DW.Delay9_DSTATE[ContModelHIL_B.i];

    // Delay: '<S4>/Delay8' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator3'

    ContModelHIL_B.u_i = ContModelHIL_DW.Delay8_DSTATE[ContModelHIL_B.i];

    // Signum: '<S4>/Sign7'
    if (rtIsNaN(ContModelHIL_B.u)) {
      ContModelHIL_B.D17 = (rtNaN);
    } else if (ContModelHIL_B.u < 0.0) {
      ContModelHIL_B.D17 = -1.0;
    } else {
      ContModelHIL_B.D17 = (ContModelHIL_B.u > 0.0);
    }

    // Signum: '<S4>/Sign8'
    if (rtIsNaN(ContModelHIL_B.DigitalClock)) {
      ContModelHIL_B.D18 = (rtNaN);
    } else if (ContModelHIL_B.DigitalClock < 0.0) {
      ContModelHIL_B.D18 = -1.0;
    } else {
      ContModelHIL_B.D18 = (ContModelHIL_B.DigitalClock > 0.0);
    }

    // Signum: '<S4>/Sign9'
    if (rtIsNaN(ContModelHIL_B.u_i)) {
      ContModelHIL_B.D27 = (rtNaN);
    } else if (ContModelHIL_B.u_i < 0.0) {
      ContModelHIL_B.D27 = -1.0;
    } else {
      ContModelHIL_B.D27 = (ContModelHIL_B.u_i > 0.0);
    }

    // DiscreteIntegrator: '<S4>/Discrete-Time Integrator3' incorporates:
    //   Abs: '<S4>/Abs8'
    //   Abs: '<S4>/Abs9'
    //   Constant: '<S4>/Constant10'
    //   Constant: '<S4>/Constant11'
    //   Constant: '<S4>/Constant12'
    //   Constant: '<S4>/Constant3'
    //   Constant: '<S4>/Constant5'
    //   Delay: '<S4>/Delay7'
    //   Delay: '<S4>/Delay9'
    //   Math: '<S4>/Power7'
    //   Math: '<S4>/Power8'
    //   Product: '<S4>/Product11'
    //   Product: '<S4>/Product12'
    //   Product: '<S4>/Product13'
    //   Signum: '<S4>/Sign7'
    //   Signum: '<S4>/Sign8'
    //   Signum: '<S4>/Sign9'
    //   Sum: '<S4>/Sum13'

    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE =
      ((ContModelHIL_P.Observer.E3[ContModelHIL_B.i] * ContModelHIL_B.D17 *
        rt_powd_snf(fabs(ContModelHIL_DW.Delay7_DSTATE[ContModelHIL_B.i]),
                    ContModelHIL_P.Observer.alpha[ContModelHIL_B.i]) +
        ContModelHIL_P.Observer.MU3[ContModelHIL_B.i] * ContModelHIL_B.D18 *
        rt_powd_snf(fabs(ContModelHIL_DW.Delay9_DSTATE[ContModelHIL_B.i]),
                    ContModelHIL_P.Observer.beta[ContModelHIL_B.i])) +
       ContModelHIL_P.Observer.E4[ContModelHIL_B.i] * ContModelHIL_B.D27) *
      ContModelHIL_P.DiscreteTimeIntegrator3_gainval +
      ContModelHIL_DW.DiscreteTimeIntegrator3_DSTATE[ContModelHIL_B.i];
    ContModelHIL_DW.DiscreteTimeIntegrator3_DSTATE[ContModelHIL_B.i] =
      ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;

    // Sum: '<S4>/Sum11' incorporates:
    //   Delay: '<S4>/Delay4'
    //   Delay: '<S4>/Delay5'
    //   Product: '<S4>/Matrix Multiply'

    ContModelHIL_B.D17 = 0.0;
    for (i = 0; i < 8; i++) {
      ContModelHIL_B.D17 += ContModelHIL_DW.Delay5_DSTATE[(i << 3) +
        ContModelHIL_B.i] * ContModelHIL_DW.Delay4_DSTATE[i];
    }

    // Sum: '<S4>/Sum9' incorporates:
    //   Constant: '<S4>/Constant11'
    //   Product: '<S4>/Matrix Multiply'

    ContModelHIL_B.u_i = ContModelHIL_P.Observer.alpha[ContModelHIL_B.i];

    // Sum: '<S4>/Sum10' incorporates:
    //   Constant: '<S4>/Constant12'
    //   Product: '<S4>/Matrix Multiply'

    ContModelHIL_B.Observer_beta = ContModelHIL_P.Observer.beta[ContModelHIL_B.i];

    // Delay: '<S4>/Delay3' incorporates:
    //   Product: '<S4>/Matrix Multiply'

    ContModelHIL_B.u = ContModelHIL_DW.Delay3_DSTATE[ContModelHIL_B.i];

    // Delay: '<S4>/Delay6' incorporates:
    //   Product: '<S4>/Matrix Multiply'

    ContModelHIL_B.DigitalClock = ContModelHIL_DW.Delay6_DSTATE[ContModelHIL_B.i];

    // Signum: '<S4>/Sign5'
    if (rtIsNaN(ContModelHIL_B.u)) {
      ContModelHIL_B.D18 = (rtNaN);
    } else if (ContModelHIL_B.u < 0.0) {
      ContModelHIL_B.D18 = -1.0;
    } else {
      ContModelHIL_B.D18 = (ContModelHIL_B.u > 0.0);
    }

    // Signum: '<S4>/Sign6'
    if (rtIsNaN(ContModelHIL_B.DigitalClock)) {
      ContModelHIL_B.D27 = (rtNaN);
    } else if (ContModelHIL_B.DigitalClock < 0.0) {
      ContModelHIL_B.D27 = -1.0;
    } else {
      ContModelHIL_B.D27 = (ContModelHIL_B.DigitalClock > 0.0);
    }

    // DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' incorporates:
    //   Abs: '<S4>/Abs6'
    //   Abs: '<S4>/Abs7'
    //   Constant: '<S4>/Constant'
    //   Constant: '<S4>/Constant11'
    //   Constant: '<S4>/Constant12'
    //   Constant: '<S4>/Constant6'
    //   Constant: '<S4>/Constant7'
    //   Constant: '<S4>/Constant9'
    //   Delay: '<S4>/Delay3'
    //   Delay: '<S4>/Delay6'
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator3'
    //   Gain: '<S4>/Gain5'
    //   Gain: '<S4>/Gain6'
    //   Math: '<S4>/Power5'
    //   Math: '<S4>/Power6'
    //   Product: '<S4>/Matrix Multiply'
    //   Product: '<S4>/Product8'
    //   Product: '<S4>/Product9'
    //   Signum: '<S4>/Sign5'
    //   Signum: '<S4>/Sign6'
    //   Sum: '<S4>/Sum10'
    //   Sum: '<S4>/Sum11'
    //   Sum: '<S4>/Sum9'

    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE = (((rt_powd_snf(fabs
      (ContModelHIL_DW.Delay3_DSTATE[ContModelHIL_B.i]), (ContModelHIL_B.u_i +
      ContModelHIL_P.Constant6_Value[ContModelHIL_B.i]) *
      ContModelHIL_P.Gain5_Gain) * (ContModelHIL_P.Observer.E2[ContModelHIL_B.i]
      * ContModelHIL_B.D18) + ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE) +
      ContModelHIL_B.D17) + rt_powd_snf(fabs
      (ContModelHIL_DW.Delay6_DSTATE[ContModelHIL_B.i]),
      (ContModelHIL_B.Observer_beta +
       ContModelHIL_P.Constant7_Value[ContModelHIL_B.i]) *
      ContModelHIL_P.Gain6_Gain) * (ContModelHIL_P.Observer.MU2[ContModelHIL_B.i]
      * ContModelHIL_B.D27)) * ContModelHIL_P.DiscreteTimeIntegrator1_gainval +
      ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[ContModelHIL_B.i];
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[ContModelHIL_B.i] =
      ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;

    // Delay: '<S4>/Delay2' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    ContModelHIL_B.u = ContModelHIL_DW.Delay2_DSTATE[ContModelHIL_B.i];

    // Delay: '<S4>/Delay1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    ContModelHIL_B.DigitalClock = ContModelHIL_DW.Delay1_DSTATE[ContModelHIL_B.i];

    // Signum: '<S4>/Sign3'
    if (rtIsNaN(ContModelHIL_B.u)) {
      ContModelHIL_B.D17 = (rtNaN);
    } else if (ContModelHIL_B.u < 0.0) {
      ContModelHIL_B.D17 = -1.0;
    } else {
      ContModelHIL_B.D17 = (ContModelHIL_B.u > 0.0);
    }

    // Signum: '<S4>/Sign4'
    if (rtIsNaN(ContModelHIL_B.DigitalClock)) {
      ContModelHIL_B.D18 = (rtNaN);
    } else if (ContModelHIL_B.DigitalClock < 0.0) {
      ContModelHIL_B.D18 = -1.0;
    } else {
      ContModelHIL_B.D18 = (ContModelHIL_B.DigitalClock > 0.0);
    }

    // DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
    //   Abs: '<S4>/Abs4'
    //   Abs: '<S4>/Abs5'
    //   Constant: '<S4>/Constant1'
    //   Constant: '<S4>/Constant11'
    //   Constant: '<S4>/Constant12'
    //   Constant: '<S4>/Constant2'
    //   Constant: '<S4>/Constant4'
    //   Constant: '<S4>/Constant8'
    //   Delay: '<S4>/Delay1'
    //   Delay: '<S4>/Delay2'
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
    //   Gain: '<S4>/Gain3'
    //   Gain: '<S4>/Gain4'
    //   Math: '<S4>/Power3'
    //   Math: '<S4>/Power4'
    //   Product: '<S4>/Product6'
    //   Product: '<S4>/Product7'
    //   Signum: '<S4>/Sign3'
    //   Signum: '<S4>/Sign4'
    //   Sum: '<S4>/Sum5'
    //   Sum: '<S4>/Sum6'
    //   Sum: '<S4>/Sum7'

    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[ContModelHIL_B.i] +=
      ((rt_powd_snf(fabs(ContModelHIL_DW.Delay2_DSTATE[ContModelHIL_B.i]),
                    (ContModelHIL_B.u_i +
                     ContModelHIL_P.Constant2_Value[ContModelHIL_B.i]) *
                    ContModelHIL_P.Gain3_Gain) *
        (ContModelHIL_P.Observer.E1[ContModelHIL_B.i] * ContModelHIL_B.D17) +
        ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE) + rt_powd_snf(fabs
        (ContModelHIL_DW.Delay1_DSTATE[ContModelHIL_B.i]),
        (ContModelHIL_B.Observer_beta +
         ContModelHIL_P.Constant4_Value[ContModelHIL_B.i]) *
        ContModelHIL_P.Gain4_Gain) *
       (ContModelHIL_P.Observer.MU1[ContModelHIL_B.i] * ContModelHIL_B.D18)) *
      ContModelHIL_P.DiscreteTimeIntegrator_gainval;
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Delay: '<S4>/Delay5'

  ContModelHIL_B.DigitalClock = sin
    (ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[5]);
  ContModelHIL_B.u_i = sin(ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelHIL_B.Observer_beta = cos
    (ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[5]);
  ContModelHIL_B.u = sin(ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]);
  ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE = sin
    (ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3]);
  ContModelHIL_B.D14_tmp = cos(ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3]);
  ContModelHIL_B.D14_tmp_k = cos(ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelHIL_B.D14_tmp_c = sin(ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelHIL_B.D14_tmp_tmp = ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]
    + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelHIL_B.D14_tmp_b = sin(ContModelHIL_B.D14_tmp_tmp);
  ContModelHIL_B.D14_tmp_p = cos(ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelHIL_B.D14_tmp_cv = cos(ContModelHIL_B.D14_tmp_tmp);
  ContModelHIL_B.D14_tmp_o = 0.01400542 * ContModelHIL_B.D14_tmp_k +
    0.040588879999999994;
  ContModelHIL_B.D14_tmp_n = 0.01400542 * ContModelHIL_B.D14_tmp_cv;
  ContModelHIL_B.D14_tmp_tmp_i = 0.040588879999999994 * ContModelHIL_B.u_i;
  ContModelHIL_B.D14_tmp_tmp_o = 0.01400542 * ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.D14_tmp_m = ContModelHIL_B.D14_tmp_tmp_i +
    ContModelHIL_B.D14_tmp_tmp_o;
  ContModelHIL_B.D14_tmp_cz = ContModelHIL_B.D14_tmp_m *
    ContModelHIL_B.DigitalClock;
  ContModelHIL_B.D14_tmp_d = ContModelHIL_B.D14_tmp_o *
    ContModelHIL_B.Observer_beta;
  ContModelHIL_B.D14_tmp_a = 0.01400542 * ContModelHIL_B.DigitalClock;
  ContModelHIL_B.D14_tmp_pb = 0.01400542 * ContModelHIL_B.Observer_beta *
    ContModelHIL_B.D14_tmp_c * ContModelHIL_B.u;
  ContModelHIL_B.D14_tmp_o3 = (-ContModelHIL_B.D14_tmp_o *
    ContModelHIL_B.DigitalClock + ContModelHIL_B.D14_tmp_pb) *
    ContModelHIL_B.D14_tmp;
  ContModelHIL_B.D14 = (((ContModelHIL_B.D14_tmp_a * ContModelHIL_B.u_i *
    ContModelHIL_B.D14_tmp_c + -0.023689199999999997 *
    ContModelHIL_B.DigitalClock) + ContModelHIL_B.D14_tmp_d * ContModelHIL_B.u_i
    * ContModelHIL_B.u) * ContModelHIL_B.D14_tmp + ((ContModelHIL_B.D14_tmp_n +
    0.023689199999999997) * ContModelHIL_B.Observer_beta * ContModelHIL_B.u +
    ContModelHIL_B.D14_tmp_cz) * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE)
    + (0.040588879999999994 * ContModelHIL_B.Observer_beta *
       ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.u +
       ContModelHIL_B.D14_tmp_o3) * ContModelHIL_B.D14_tmp_p;
  ContModelHIL_B.D15_tmp = cos(ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]);
  ContModelHIL_B.D15_tmp_tmp = ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelHIL_B.D15_tmp_f = cos(ContModelHIL_B.D15_tmp_tmp);
  ContModelHIL_B.D15_tmp_tmp_a = ContModelHIL_B.D15_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelHIL_B.D15_tmp_g = cos(ContModelHIL_B.D15_tmp_tmp_a);
  ContModelHIL_B.D15_tmp_tmp_o = 0.040588879999999994 * ContModelHIL_B.D15_tmp_f;
  ContModelHIL_B.D15_tmp_tmp_k = 0.01400542 * ContModelHIL_B.D15_tmp_g;
  ContModelHIL_B.D15_tmp_c = (0.023689199999999997 * ContModelHIL_B.D14_tmp +
    ContModelHIL_B.D15_tmp_tmp_o) + ContModelHIL_B.D15_tmp_tmp_k;
  ContModelHIL_B.D15 = ContModelHIL_B.D15_tmp_c * -ContModelHIL_B.Observer_beta *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D16_tmp_tmp = 0.040588879999999994 * ContModelHIL_B.D14_tmp_p;
  ContModelHIL_B.D16_tmp = (ContModelHIL_B.D16_tmp_tmp + 0.023689199999999997) +
    ContModelHIL_B.D14_tmp_n;
  ContModelHIL_B.D16_tmp_n = ContModelHIL_B.D16_tmp *
    ContModelHIL_B.Observer_beta;
  ContModelHIL_B.D16_tmp_l = ContModelHIL_B.D16_tmp *
    ContModelHIL_B.DigitalClock;
  ContModelHIL_B.D16_tmp_p = ContModelHIL_B.D16_tmp_l * ContModelHIL_B.u;
  ContModelHIL_B.D16_tmp_pt = ContModelHIL_B.D14_tmp_cz * ContModelHIL_B.u +
    ContModelHIL_B.D16_tmp_n;
  ContModelHIL_B.D16 = (ContModelHIL_B.D14_tmp_m * -ContModelHIL_B.Observer_beta
                        + ContModelHIL_B.D16_tmp_p) * ContModelHIL_B.D14_tmp +
    ContModelHIL_B.D16_tmp_pt * -ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.D17_tmp_tmp_a = ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE *
    ContModelHIL_B.DigitalClock;
  ContModelHIL_B.D17_tmp_tmp_e = ContModelHIL_B.D14_tmp *
    ContModelHIL_B.Observer_beta;
  ContModelHIL_B.D17_tmp = ContModelHIL_B.D17_tmp_tmp_e * ContModelHIL_B.u +
    ContModelHIL_B.D17_tmp_tmp_a;
  ContModelHIL_B.D17_tmp_m = 0.09794 * ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.D17_tmp_tmp = ContModelHIL_B.Observer_beta *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.D17_tmp_tmp_f = -ContModelHIL_B.D14_tmp *
    ContModelHIL_B.DigitalClock;
  ContModelHIL_B.D17_tmp_m3 = ContModelHIL_B.D17_tmp_tmp * ContModelHIL_B.u +
    ContModelHIL_B.D17_tmp_tmp_f;
  ContModelHIL_B.D17_tmp_j = 0.09794 * ContModelHIL_B.D14_tmp_cv;
  ContModelHIL_B.D17_tmp_h = 0.17 * ContModelHIL_B.D14_tmp_p;
  ContModelHIL_B.D17_tmp_c = 0.17 * ContModelHIL_B.u_i +
    ContModelHIL_B.D17_tmp_m;
  ContModelHIL_B.D17_tmp_p = ContModelHIL_B.D17_tmp_c * 0.143;
  ContModelHIL_B.D17_tmp_n = ContModelHIL_B.D17_tmp_h + ContModelHIL_B.D17_tmp_j;
  ContModelHIL_B.D17_tmp_tmp_o = ContModelHIL_B.DigitalClock *
    ContModelHIL_B.u_i;
  ContModelHIL_B.D17_tmp_tmp_g = ContModelHIL_B.Observer_beta *
    ContModelHIL_B.D14_tmp_p;
  ContModelHIL_B.D17_tmp_k = ContModelHIL_B.D17_tmp_tmp_g * ContModelHIL_B.u +
    ContModelHIL_B.D17_tmp_tmp_o;
  ContModelHIL_B.D17_tmp_n3 = ContModelHIL_B.Observer_beta * ContModelHIL_B.u_i *
    ContModelHIL_B.u + -ContModelHIL_B.D14_tmp_p * ContModelHIL_B.DigitalClock;
  ContModelHIL_B.D17 = ((0.01627888 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.D17_tmp_k +
    ContModelHIL_B.D17_tmp_p * ContModelHIL_B.D17_tmp) +
                        ContModelHIL_B.D17_tmp_n * 0.143 *
                        ContModelHIL_B.D17_tmp_m3) + 0.01627888 *
    ContModelHIL_B.D14_tmp * ContModelHIL_B.D17_tmp_n3;
  ContModelHIL_B.D18_tmp = ContModelHIL_B.D17_tmp * ContModelHIL_B.D17_tmp_m +
    ContModelHIL_B.D17_tmp_m3 * ContModelHIL_B.D17_tmp_j;
  ContModelHIL_B.D18 = ContModelHIL_B.D18_tmp * 0.143;
  ContModelHIL_B.D24_tmp = 0.11464 * ContModelHIL_B.D14_tmp_p + 0.08312;
  ContModelHIL_B.D24_tmp_p = (ContModelHIL_B.D17_tmp_h + 0.08312) +
    ContModelHIL_B.D17_tmp_j;
  ContModelHIL_B.D24_tmp_f = ContModelHIL_B.D17_tmp_m3 *
    ContModelHIL_B.D17_tmp_c;
  ContModelHIL_B.D17_tmp_h = ContModelHIL_B.D15_tmp * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D24_tmp_d = 0.08312 * ContModelHIL_B.D14_tmp;
  ContModelHIL_B.D24_tmp_n = (0.17 * ContModelHIL_B.D15_tmp_f +
    ContModelHIL_B.D24_tmp_d) + 0.09794 * ContModelHIL_B.D15_tmp_g;
  ContModelHIL_B.D24 = (((ContModelHIL_B.D24_tmp * ContModelHIL_B.DigitalClock *
    ContModelHIL_B.u + -0.11464 * ContModelHIL_B.Observer_beta *
    ContModelHIL_B.u_i) * (0.142 * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE)
    + 0.143 * ContModelHIL_B.Observer_beta * ContModelHIL_B.D24_tmp_n *
    ContModelHIL_B.D17_tmp_h) + (0.11464 * ContModelHIL_B.DigitalClock *
    ContModelHIL_B.u_i * ContModelHIL_B.u + ContModelHIL_B.D24_tmp *
    ContModelHIL_B.Observer_beta) * (0.142 * ContModelHIL_B.D14_tmp)) +
    (ContModelHIL_B.D24_tmp_p * ContModelHIL_B.D17_tmp -
     ContModelHIL_B.D24_tmp_f) * (0.143 * ContModelHIL_B.u);
  ContModelHIL_B.D25 = -ContModelHIL_B.D15_tmp_c * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DigitalClock;
  ContModelHIL_B.D26 = ((ContModelHIL_B.D24_tmp * -0.142 *
    ContModelHIL_B.D17_tmp - ContModelHIL_B.D24_tmp_p * 0.143 *
    ContModelHIL_B.D17_tmp) + 0.01627888 * ContModelHIL_B.u_i *
                        ContModelHIL_B.D17_tmp_m3) + ContModelHIL_B.D17_tmp_p *
    ContModelHIL_B.D17_tmp_m3;
  ContModelHIL_B.D17_tmp_tmp_a = ContModelHIL_B.D17_tmp_tmp_a * ContModelHIL_B.u
    + ContModelHIL_B.D17_tmp_tmp_e;
  ContModelHIL_B.D17_tmp_p = ContModelHIL_B.D14_tmp *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.u;
  ContModelHIL_B.D17_tmp_tmp_e = ContModelHIL_B.D17_tmp_tmp -
    ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.D27_tmp = ContModelHIL_B.D17_tmp_tmp_a *
    ContModelHIL_B.D16_tmp_tmp;
  ContModelHIL_B.D27_tmp_i = ContModelHIL_B.D17_tmp_tmp_a *
    ContModelHIL_B.D14_tmp_n;
  ContModelHIL_B.D27 = (ContModelHIL_B.D17_tmp_tmp_e * -ContModelHIL_B.D14_tmp_m
                        + ContModelHIL_B.D27_tmp) + ContModelHIL_B.D27_tmp_i;
  ContModelHIL_B.D28_tmp = -ContModelHIL_B.Observer_beta *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE + ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.D17_tmp_m = ContModelHIL_B.D28_tmp * ContModelHIL_B.D17_tmp_m +
    ContModelHIL_B.D17_tmp_tmp_a * ContModelHIL_B.D17_tmp_j;
  ContModelHIL_B.D28 = ContModelHIL_B.D17_tmp_m * 0.143;
  ContModelHIL_B.D17_tmp_j = sin(ContModelHIL_B.D15_tmp_tmp);
  ContModelHIL_B.D17_tmp_p = sin(ContModelHIL_B.D15_tmp_tmp_a);
  ContModelHIL_B.D34_tmp = 0.040588879999999994 * ContModelHIL_B.D17_tmp_j;
  ContModelHIL_B.D34_tmp_a = 0.01400542 * ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.D34_tmp_m = (0.023689199999999997 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE + ContModelHIL_B.D34_tmp) +
    ContModelHIL_B.D34_tmp_a;
  ContModelHIL_B.D34 = ContModelHIL_B.D34_tmp_m * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D35 = ContModelHIL_B.D15_tmp_c * ContModelHIL_B.u;
  ContModelHIL_B.D37_tmp = ContModelHIL_B.D34_tmp + ContModelHIL_B.D34_tmp_a;
  ContModelHIL_B.D37 = ContModelHIL_B.D37_tmp * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D38 = 0.01400542 * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.D45_tmp = 0.0 * ContModelHIL_B.D15_tmp_g;
  ContModelHIL_B.D45_tmp_c = 0.0 * ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.D45 = ((0.0 * ContModelHIL_B.D15_tmp_f + ContModelHIL_B.D45_tmp)
                        + 0.0 * ContModelHIL_B.D17_tmp_j) +
    ContModelHIL_B.D45_tmp_c;
  ContModelHIL_B.D46_tmp_tmp_f = ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]
    - ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp = sin(ContModelHIL_B.D46_tmp_tmp_f);
  ContModelHIL_B.D46_tmp_tmp_a = ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]
    + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelHIL_B.D46_tmp_g = sin(ContModelHIL_B.D46_tmp_tmp_a);
  ContModelHIL_B.D46_tmp_tmp = ContModelHIL_B.D15_tmp_tmp -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp_m = cos(ContModelHIL_B.D46_tmp_tmp);
  ContModelHIL_B.D46_tmp_tmp_i = ContModelHIL_B.D15_tmp_tmp_a -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp_n = cos(ContModelHIL_B.D46_tmp_tmp_i);
  ContModelHIL_B.D46_tmp_tmp_l = ContModelHIL_B.D15_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp_p = cos(ContModelHIL_B.D46_tmp_tmp_l);
  ContModelHIL_B.D46_tmp_tmp_o = ContModelHIL_B.D15_tmp_tmp_a +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp_l = cos(ContModelHIL_B.D46_tmp_tmp_o);
  ContModelHIL_B.D46_tmp_j = sin(ContModelHIL_B.D46_tmp_tmp);
  ContModelHIL_B.D46_tmp_ld = sin(ContModelHIL_B.D46_tmp_tmp_i);
  ContModelHIL_B.D46_tmp_lx = sin(ContModelHIL_B.D46_tmp_tmp_l);
  ContModelHIL_B.D46_tmp_nu = sin(ContModelHIL_B.D46_tmp_tmp_o);
  ContModelHIL_B.D46_tmp_tmp_h = ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7]
    - ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp_ln = sin(ContModelHIL_B.D46_tmp_tmp_h);
  ContModelHIL_B.D46_tmp_tmp_e = ContModelHIL_B.D14_tmp_tmp -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp_h = sin(ContModelHIL_B.D46_tmp_tmp_e);
  ContModelHIL_B.D46_tmp_tmp_c = ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]
    + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelHIL_B.D46_tmp_b = sin(ContModelHIL_B.D46_tmp_tmp_c);
  ContModelHIL_B.D46_tmp_tmp_ax = ContModelHIL_B.D14_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp_d = sin(ContModelHIL_B.D46_tmp_tmp_ax);
  ContModelHIL_B.D46_tmp_c = -0.0 * ContModelHIL_B.D46_tmp_m;
  ContModelHIL_B.D46_tmp_o = 0.0 * ContModelHIL_B.D46_tmp_p;
  ContModelHIL_B.D46_tmp_lm = 0.0 * ContModelHIL_B.D46_tmp_l;
  ContModelHIL_B.D46_tmp_mv = 0.0 * ContModelHIL_B.D46_tmp_j;
  ContModelHIL_B.D46_tmp_mj = 0.0 * ContModelHIL_B.D46_tmp_ld;
  ContModelHIL_B.D46_tmp_tmp_m = 0.0 * ContModelHIL_B.D46_tmp_n;
  ContModelHIL_B.D46_tmp_p4 = ((ContModelHIL_B.D46_tmp_c -
    ContModelHIL_B.D46_tmp_tmp_m) - ContModelHIL_B.D46_tmp_o) -
    ContModelHIL_B.D46_tmp_lm;
  ContModelHIL_B.D46_tmp_e = 0.004761842800000001 * ContModelHIL_B.D46_tmp_ln;
  ContModelHIL_B.D46_tmp_o4 = -0.00093002 * ContModelHIL_B.u;
  ContModelHIL_B.D46_tmp_hh = -0.0006068 * ContModelHIL_B.u;
  ContModelHIL_B.D46_tmp_l5 = -0.0037324216063999997 * ContModelHIL_B.u;
  ContModelHIL_B.D46_tmp_h2 = -0.0027433816695999996 * ContModelHIL_B.u;
  ContModelHIL_B.D46_tmp_me = -0.008265400000000001 * ContModelHIL_B.u;
  ContModelHIL_B.D46_tmp_mc = 0.0 * ContModelHIL_B.D46_tmp_lx;
  ContModelHIL_B.D46_tmp_h3 = -0.004761842800000001 * ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.D46_tmp_cs = 0.0 * ContModelHIL_B.D46_tmp_nu;
  ContModelHIL_B.D46 = ((((((((((((((((((((0.0027062010112 *
    ContModelHIL_B.D46_tmp + ContModelHIL_B.D46_tmp_p4) + 0.0040412944 *
    ContModelHIL_B.D46_tmp) + ContModelHIL_B.D46_tmp_mv) +
    ContModelHIL_B.D46_tmp_e) + 0.0023282610207999996 * ContModelHIL_B.D46_tmp_h)
    + ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.D46_tmp_o4) +
    ContModelHIL_B.D46_tmp_hh) + -0.0787496 * ContModelHIL_B.u) +
    ContModelHIL_B.D46_tmp_l5) + -0.0019621373695999996 * ContModelHIL_B.u) +
    ContModelHIL_B.D46_tmp_h2) + -0.0019759552383999996 * ContModelHIL_B.u) +
    ContModelHIL_B.D46_tmp_me) + -0.0027062010112 * ContModelHIL_B.D46_tmp_g) +
    -0.0040412944 * ContModelHIL_B.D46_tmp_g) + ContModelHIL_B.D46_tmp_mc) +
    ContModelHIL_B.D46_tmp_h3) + -0.0023282610207999996 *
    ContModelHIL_B.D46_tmp_d) + ContModelHIL_B.D46_tmp_cs) * 0.5;
  ContModelHIL_B.D47_tmp = 0.0011641305103999998 * ContModelHIL_B.D14_tmp_cv;
  ContModelHIL_B.D47_tmp_p = 0.004761842800000001 * ContModelHIL_B.D14_tmp_k;
  ContModelHIL_B.D47_tmp_g = 0.0033737477055999993 * ContModelHIL_B.D14_tmp_p +
    0.008139011638;
  ContModelHIL_B.D47 = (ContModelHIL_B.D47_tmp_g + ContModelHIL_B.D47_tmp_p) +
    ContModelHIL_B.D47_tmp;
  ContModelHIL_B.D48_tmp = 0.0023809214000000004 * ContModelHIL_B.D14_tmp_k +
    0.0016750908347999997;
  ContModelHIL_B.D48 = ContModelHIL_B.D48_tmp + ContModelHIL_B.D47_tmp;
  ContModelHIL_B.D56_tmp_tmp = 2.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3];
  ContModelHIL_B.D56_tmp_tmp_e = ContModelHIL_B.D56_tmp_tmp -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp = sin(ContModelHIL_B.D56_tmp_tmp_e);
  ContModelHIL_B.D56_tmp_tmp_i = ContModelHIL_B.D56_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelHIL_B.D56_tmp_tmp_ol = ContModelHIL_B.D56_tmp_tmp_i -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_d = sin(ContModelHIL_B.D56_tmp_tmp_ol);
  ContModelHIL_B.D56_tmp_tmp_tmp = 2.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6];
  ContModelHIL_B.D56_tmp_tmp_o = ContModelHIL_B.D56_tmp_tmp +
    ContModelHIL_B.D56_tmp_tmp_tmp;
  ContModelHIL_B.D56_tmp_tmp_iz = ContModelHIL_B.D56_tmp_tmp_o -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_g = sin(ContModelHIL_B.D56_tmp_tmp_iz);
  ContModelHIL_B.D56_tmp_tmp_f = 2.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7] +
    ContModelHIL_B.D56_tmp_tmp_o;
  ContModelHIL_B.D56_tmp_tmp_ff = ContModelHIL_B.D56_tmp_tmp_f -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_dh = sin(ContModelHIL_B.D56_tmp_tmp_ff);
  ContModelHIL_B.D56_tmp_tmp_b = ContModelHIL_B.D56_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_dy = sin(ContModelHIL_B.D56_tmp_tmp_b);
  ContModelHIL_B.D56_tmp_tmp_g2 = ContModelHIL_B.D56_tmp_tmp_i +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_o = sin(ContModelHIL_B.D56_tmp_tmp_g2);
  ContModelHIL_B.D56_tmp_tmp_g = ContModelHIL_B.D56_tmp_tmp_o +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_b = sin(ContModelHIL_B.D56_tmp_tmp_g);
  ContModelHIL_B.D56_tmp_tmp_f += ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE
    [4];
  ContModelHIL_B.D56_tmp_bs = sin(ContModelHIL_B.D56_tmp_tmp_f);
  ContModelHIL_B.D56_tmp_e = cos(ContModelHIL_B.D56_tmp_tmp_iz);
  ContModelHIL_B.D56_tmp_bj = cos(ContModelHIL_B.D56_tmp_tmp_ff);
  ContModelHIL_B.D56_tmp_j = cos(ContModelHIL_B.D56_tmp_tmp_g);
  ContModelHIL_B.D56_tmp_f = cos(ContModelHIL_B.D56_tmp_tmp_f);
  ContModelHIL_B.D56_tmp_tmp_iz = ContModelHIL_B.D56_tmp_tmp_i +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelHIL_B.D56_tmp_tmp_f = ContModelHIL_B.D56_tmp_tmp_iz -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_ju = sin(ContModelHIL_B.D56_tmp_tmp_f);
  ContModelHIL_B.D56_tmp_tmp_o += ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE
    [7];
  ContModelHIL_B.D56_tmp_tmp_ff = ContModelHIL_B.D56_tmp_tmp_o -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_jz = sin(ContModelHIL_B.D56_tmp_tmp_ff);
  ContModelHIL_B.D56_tmp_tmp_g = ContModelHIL_B.D56_tmp_tmp_iz +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_o4 = sin(ContModelHIL_B.D56_tmp_tmp_g);
  ContModelHIL_B.D56_tmp_tmp_o += ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE
    [4];
  ContModelHIL_B.D56_tmp_n = sin(ContModelHIL_B.D56_tmp_tmp_o);
  ContModelHIL_B.D56_tmp_k = -0.0 * ContModelHIL_B.D46_tmp_n;
  ContModelHIL_B.D56_tmp_c = -0.0 * ContModelHIL_B.D46_tmp_lx;
  ContModelHIL_B.D56_tmp_fb = -0.0 * ContModelHIL_B.D46_tmp_nu;
  ContModelHIL_B.D56_tmp_tmp_c = 0.04043155 * ContModelHIL_B.D56_tmp;
  ContModelHIL_B.D56_tmp_tmp_cj = 0.06214814 * ContModelHIL_B.D56_tmp;
  ContModelHIL_B.D56_tmp_tmp_m = 0.0009810686847999998 * ContModelHIL_B.D56_tmp;
  ContModelHIL_B.D56_tmp_tmp_j = 0.0009879776191999998 * ContModelHIL_B.D56_tmp;
  ContModelHIL_B.D56_tmp_tmp_k = 5.484E-5 * ContModelHIL_B.D56_tmp_g;
  ContModelHIL_B.D56_tmp_tmp_mx = 0.00050874 * ContModelHIL_B.D56_tmp_g;
  ContModelHIL_B.D56_tmp_tmp_p = 0.0018662108031999999 *
    ContModelHIL_B.D56_tmp_g;
  ContModelHIL_B.D56_tmp_tmp_d = 0.0041327000000000004 *
    ContModelHIL_B.D56_tmp_g;
  ContModelHIL_B.D56_tmp_tmp_g4 = 8.085E-5 * ContModelHIL_B.D56_tmp_dh;
  ContModelHIL_B.D56_tmp_tmp_c3 = 0.00034964 * ContModelHIL_B.D56_tmp_dh;
  ContModelHIL_B.D56_tmp_tmp_cx = 0.0013716908347999998 *
    ContModelHIL_B.D56_tmp_dh;
  ContModelHIL_B.D56_tmp_tmp_if = 0.04043155 * ContModelHIL_B.D56_tmp_dy;
  ContModelHIL_B.D56_tmp_tmp_dx = 0.06214814 * ContModelHIL_B.D56_tmp_dy;
  ContModelHIL_B.D56_tmp_tmp_g4k = 0.0009810686847999998 *
    ContModelHIL_B.D56_tmp_dy;
  ContModelHIL_B.D56_tmp_tmp_l = 5.484E-5 * ContModelHIL_B.D56_tmp_b;
  ContModelHIL_B.D56_tmp_tmp_f1 = 0.00050874 * ContModelHIL_B.D56_tmp_b;
  ContModelHIL_B.D56_tmp_tmp_db = 0.0018662108031999999 *
    ContModelHIL_B.D56_tmp_b;
  ContModelHIL_B.D56_tmp_tmp_jr = 0.0041327000000000004 *
    ContModelHIL_B.D56_tmp_b;
  ContModelHIL_B.D56_tmp = (((((((((((((((((((((((((((((((((((((-0.0 *
    ContModelHIL_B.D56_tmp_e + ContModelHIL_B.D46_tmp_c) +
    ContModelHIL_B.D56_tmp_k) + -0.0 * ContModelHIL_B.D56_tmp_bj) +
    ContModelHIL_B.D46_tmp_o) + -0.0 * ContModelHIL_B.D56_tmp_j) +
    ContModelHIL_B.D46_tmp_lm) + -0.0 * ContModelHIL_B.D56_tmp_f) +
    ContModelHIL_B.D56_tmp_tmp_c) - ContModelHIL_B.D56_tmp_tmp_cj) +
    ContModelHIL_B.D56_tmp_tmp_m) + ContModelHIL_B.D56_tmp_tmp_j) +
    ContModelHIL_B.D46_tmp_mv) + 0.0027062010112 * ContModelHIL_B.D56_tmp_d) +
    0.0040412944 * ContModelHIL_B.D56_tmp_d) - ContModelHIL_B.D56_tmp_tmp_k) +
    ContModelHIL_B.D56_tmp_tmp_mx) + ContModelHIL_B.D56_tmp_tmp_p) +
    ContModelHIL_B.D56_tmp_tmp_d) + ContModelHIL_B.D46_tmp_mj) +
    0.0023282610207999996 * ContModelHIL_B.D56_tmp_ju) + 0.004761842800000001 *
    ContModelHIL_B.D56_tmp_jz) - ContModelHIL_B.D56_tmp_tmp_g4) +
    ContModelHIL_B.D56_tmp_tmp_c3) + ContModelHIL_B.D56_tmp_tmp_cx) +
    ContModelHIL_B.D56_tmp_tmp_if) - ContModelHIL_B.D56_tmp_tmp_dx) +
    ContModelHIL_B.D56_tmp_tmp_g4k) + 0.0009879776191999998 *
    ContModelHIL_B.D56_tmp_dy) + ContModelHIL_B.D56_tmp_c) + 0.0027062010112 *
    ContModelHIL_B.D56_tmp_o) + 0.0040412944 * ContModelHIL_B.D56_tmp_o) -
    ContModelHIL_B.D56_tmp_tmp_l) + ContModelHIL_B.D56_tmp_tmp_f1) +
    ContModelHIL_B.D56_tmp_tmp_db) + ContModelHIL_B.D56_tmp_tmp_jr) +
    ContModelHIL_B.D56_tmp_fb) + 0.0023282610207999996 *
    ContModelHIL_B.D56_tmp_o4) + 0.004761842800000001 * ContModelHIL_B.D56_tmp_n;
  ContModelHIL_B.D46_tmp_c = 0.00034964 * ContModelHIL_B.D56_tmp_bs;
  ContModelHIL_B.D56_tmp_h = 0.0013716908347999998 * ContModelHIL_B.D56_tmp_bs;
  ContModelHIL_B.D56 = (((-8.085E-5 * ContModelHIL_B.D56_tmp_bs +
    ContModelHIL_B.D56_tmp) + ContModelHIL_B.D46_tmp_c) +
                        ContModelHIL_B.D56_tmp_h) * 0.25;
  ContModelHIL_B.D58 = ContModelHIL_B.D45_tmp + ContModelHIL_B.D45_tmp_c;
  ContModelHIL_B.D45_tmp_c = 0.11464 * ContModelHIL_B.u_i;
  ContModelHIL_B.D45_tmp = ContModelHIL_B.D17_tmp * -ContModelHIL_B.D24_tmp +
    ContModelHIL_B.D17_tmp_m3 * ContModelHIL_B.D45_tmp_c;
  ContModelHIL_B.D24_tmp_f += -ContModelHIL_B.D24_tmp_p * ContModelHIL_B.D17_tmp;
  ContModelHIL_B.y_a = ContModelHIL_B.D17_tmp_tmp_e * ContModelHIL_B.D24_tmp +
    ContModelHIL_B.D17_tmp_tmp_a * ContModelHIL_B.D45_tmp_c;
  ContModelHIL_B.ab_a = ContModelHIL_B.D24_tmp_p * ContModelHIL_B.D17_tmp_tmp_e
    + ContModelHIL_B.D17_tmp_tmp_a * ContModelHIL_B.D17_tmp_c;
  ContModelHIL_B.D24_tmp = 0.0011641305103999998 * ContModelHIL_B.D46_tmp_h;
  ContModelHIL_B.D24_tmp_p = 0.0011641305103999998 * ContModelHIL_B.D46_tmp_d;
  ContModelHIL_B.D67 = (((((((((((((((((0.0013531005056 * ContModelHIL_B.D46_tmp
    + ContModelHIL_B.D46_tmp_p4) + 0.0020206472 * ContModelHIL_B.D46_tmp) +
    ContModelHIL_B.D46_tmp_mv) + ContModelHIL_B.D46_tmp_e) +
    ContModelHIL_B.D24_tmp) + ContModelHIL_B.D46_tmp_mj) +
    ContModelHIL_B.D46_tmp_o4) + ContModelHIL_B.D46_tmp_hh) +
    ContModelHIL_B.D46_tmp_l5) + ContModelHIL_B.D46_tmp_h2) +
    ContModelHIL_B.D46_tmp_me) - 0.0013531005056 * ContModelHIL_B.D46_tmp_g) -
    0.0020206472 * ContModelHIL_B.D46_tmp_g) + ContModelHIL_B.D46_tmp_mc) +
    ContModelHIL_B.D46_tmp_h3) - ContModelHIL_B.D24_tmp_p) +
                        ContModelHIL_B.D46_tmp_cs) * 0.5;
  ContModelHIL_B.D68 = (((((((((ContModelHIL_B.D56_tmp_k -
    ContModelHIL_B.D46_tmp_lm) + 0.0023809214000000004 *
    ContModelHIL_B.D46_tmp_ln) + ContModelHIL_B.D24_tmp) +
    ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.D46_tmp_hh) +
    ContModelHIL_B.D46_tmp_h2) + -0.0023809214000000004 *
    ContModelHIL_B.D46_tmp_b) - ContModelHIL_B.D24_tmp_p) +
                        ContModelHIL_B.D46_tmp_cs) * 0.5;
  ContModelHIL_B.rtb_ginv_tmp = cos(ContModelHIL_B.D56_tmp_tmp);
  ContModelHIL_B.rtb_ginv_tmp_tmp_p = ContModelHIL_B.D15_tmp_tmp * 2.0;
  ContModelHIL_B.D24_tmp = cos(ContModelHIL_B.rtb_ginv_tmp_tmp_p);
  ContModelHIL_B.D24_tmp_p = cos(ContModelHIL_B.D56_tmp_tmp_i);
  ContModelHIL_B.D46_tmp_ln = ContModelHIL_B.D15_tmp_tmp_a * 2.0;
  ContModelHIL_B.D46_tmp_b = cos(ContModelHIL_B.D46_tmp_ln);
  ContModelHIL_B.D46_tmp_hh = sin(ContModelHIL_B.D56_tmp_tmp_tmp);
  ContModelHIL_B.rtb_ginv_tmp_tmp = ContModelHIL_B.D14_tmp_tmp * 2.0;
  ContModelHIL_B.D46_tmp_h2 = cos(ContModelHIL_B.rtb_ginv_tmp_tmp);
  ContModelHIL_B.D56_tmp_k = sin(ContModelHIL_B.rtb_ginv_tmp_tmp);
  ContModelHIL_B.rtb_ginv_tmp_tmp = 2.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D46_tmp = sin(ContModelHIL_B.rtb_ginv_tmp_tmp);
  ContModelHIL_B.D46_tmp_g = sin(ContModelHIL_B.rtb_ginv_tmp_tmp_p);
  ContModelHIL_B.D46_tmp_p4 = sin(ContModelHIL_B.D46_tmp_ln);
  ContModelHIL_B.rtb_ginv_tmp_a = cos(ContModelHIL_B.D56_tmp_tmp_iz);
  ContModelHIL_B.rtb_ginv_tmp_tmp_p +=
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelHIL_B.D46_tmp_e = cos(ContModelHIL_B.rtb_ginv_tmp_tmp_p);
  ContModelHIL_B.D56_tmp_tmp_tmp = cos(ContModelHIL_B.D56_tmp_tmp_tmp);
  ContModelHIL_B.ginv[0] = 2.1037999999999997;
  ContModelHIL_B.ginv[8] = 0.0;
  ContModelHIL_B.ginv[16] = 0.0;
  ContModelHIL_B.ginv[24] = ContModelHIL_B.D14;
  ContModelHIL_B.ginv[32] = ContModelHIL_B.D15;
  ContModelHIL_B.ginv[40] = ContModelHIL_B.D16;
  ContModelHIL_B.ginv[48] = ContModelHIL_B.D17;
  ContModelHIL_B.ginv[56] = ContModelHIL_B.D18;
  ContModelHIL_B.ginv[1] = 0.0;
  ContModelHIL_B.ginv[9] = 2.1037999999999997;
  ContModelHIL_B.ginv[17] = 0.0;
  ContModelHIL_B.ginv[25] = ContModelHIL_B.D24;
  ContModelHIL_B.ginv[33] = ContModelHIL_B.D25;
  ContModelHIL_B.ginv[41] = ContModelHIL_B.D26;
  ContModelHIL_B.ginv[49] = ContModelHIL_B.D27;
  ContModelHIL_B.ginv[57] = ContModelHIL_B.D28;
  ContModelHIL_B.ginv[2] = 0.0;
  ContModelHIL_B.ginv[10] = 0.0;
  ContModelHIL_B.ginv[18] = 2.1037999999999997;
  ContModelHIL_B.ginv[26] = ContModelHIL_B.D34;
  ContModelHIL_B.ginv[34] = ContModelHIL_B.D35;
  ContModelHIL_B.ginv[42] = 0.0;
  ContModelHIL_B.ginv[50] = ContModelHIL_B.D37;
  ContModelHIL_B.ginv[58] = ContModelHIL_B.D38;
  ContModelHIL_B.ginv[3] = ContModelHIL_B.D14;
  ContModelHIL_B.ginv[11] = ContModelHIL_B.D24;
  ContModelHIL_B.ginv[19] = ContModelHIL_B.D34;
  ContModelHIL_B.rtb_ginv_tmp_p = 0.006747495411199999 *
    ContModelHIL_B.D14_tmp_p;
  ContModelHIL_B.rtb_ginv_tmp_ap = 0.0023282610207999996 *
    ContModelHIL_B.D14_tmp_cv;
  ContModelHIL_B.ginv[27] = ((ContModelHIL_B.rtb_ginv_tmp_p +
    0.049482857942000004) + ContModelHIL_B.D47_tmp_p) +
    ContModelHIL_B.rtb_ginv_tmp_ap;
  ContModelHIL_B.ginv[35] = ContModelHIL_B.D45;
  ContModelHIL_B.ginv[43] = ContModelHIL_B.D46;
  ContModelHIL_B.ginv[51] = ContModelHIL_B.D47;
  ContModelHIL_B.ginv[59] = ContModelHIL_B.D48;
  ContModelHIL_B.ginv[4] = ContModelHIL_B.D15;
  ContModelHIL_B.ginv[12] = ContModelHIL_B.D25;
  ContModelHIL_B.ginv[20] = ContModelHIL_B.D35;
  ContModelHIL_B.ginv[28] = ContModelHIL_B.D45;
  ContModelHIL_B.rtb_ginv_tmp_m = 0.00050874 * ContModelHIL_B.D24_tmp;
  ContModelHIL_B.rtb_ginv_tmp_ad = 0.0018662108031999999 *
    ContModelHIL_B.D24_tmp;
  ContModelHIL_B.rtb_ginv_tmp_k = 0.0041327000000000004 * ContModelHIL_B.D24_tmp;
  ContModelHIL_B.D15 = 8.085E-5 * ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.D25 = 0.00034964 * ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.D14 = 0.0013716908347999998 * ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.ginv[36] = ((((((((((((((((((((0.04043155 *
    ContModelHIL_B.rtb_ginv_tmp + 0.11291340794199999) - 0.06214814 *
    ContModelHIL_B.rtb_ginv_tmp) + 0.0009810686847999998 *
    ContModelHIL_B.rtb_ginv_tmp) + 0.0009879776191999998 *
    ContModelHIL_B.rtb_ginv_tmp) + ContModelHIL_B.rtb_ginv_tmp_p) + -5.484E-5 *
    ContModelHIL_B.D24_tmp) + ContModelHIL_B.rtb_ginv_tmp_m) +
    ContModelHIL_B.rtb_ginv_tmp_ad) + ContModelHIL_B.rtb_ginv_tmp_k) +
    0.0027062010112 * ContModelHIL_B.D24_tmp_p) + 0.0040412944 *
    ContModelHIL_B.D24_tmp_p) + ContModelHIL_B.D47_tmp_p) +
    ContModelHIL_B.rtb_ginv_tmp_ap) - ContModelHIL_B.D15) + ContModelHIL_B.D25)
    + ContModelHIL_B.D14) + 0.0023282610207999996 *
    ContModelHIL_B.rtb_ginv_tmp_a) + 0.004761842800000001 *
    ContModelHIL_B.D46_tmp_e) + 0.0 * ContModelHIL_B.D46_tmp_g) + 0.0 *
    ContModelHIL_B.D46_tmp_p4) * 0.5;
  ContModelHIL_B.ginv[44] = ContModelHIL_B.D56;
  ContModelHIL_B.ginv[52] = ContModelHIL_B.D45;
  ContModelHIL_B.ginv[60] = ContModelHIL_B.D58;
  ContModelHIL_B.ginv[5] = ContModelHIL_B.D16;
  ContModelHIL_B.ginv[13] = ContModelHIL_B.D26;
  ContModelHIL_B.ginv[21] = 0.0;
  ContModelHIL_B.ginv[29] = ContModelHIL_B.D46;
  ContModelHIL_B.ginv[37] = ContModelHIL_B.D56;
  ContModelHIL_B.D16 = ContModelHIL_B.D14_tmp * ContModelHIL_B.D14_tmp;
  ContModelHIL_B.D26 = ContModelHIL_B.D14_tmp_p * ContModelHIL_B.D14_tmp_p;
  ContModelHIL_B.D46 = ContModelHIL_B.u_i * ContModelHIL_B.u_i;
  ContModelHIL_B.D56 = ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.D46_tmp_ln = 2.0 * ContModelHIL_B.D14_tmp;
  ContModelHIL_B.rtb_ginv_tmp_j = ContModelHIL_B.D46_tmp_ln *
    ContModelHIL_B.D17_tmp_h * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.rtb_ginv_tmp_e = ContModelHIL_B.u * ContModelHIL_B.u;
  ContModelHIL_B.D24 = 0.0 * ContModelHIL_B.D14_tmp_p;
  ContModelHIL_B.D35 = 0.0 * ContModelHIL_B.u_i;
  ContModelHIL_B.D34 = 0.0 * ContModelHIL_B.D14_tmp_cv;
  ContModelHIL_B.D46_tmp_o4 = 0.0 * ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.D46_tmp_l5 = ContModelHIL_B.D24 - ContModelHIL_B.D35;
  ContModelHIL_B.D24 += ContModelHIL_B.D35;
  ContModelHIL_B.D35 = ContModelHIL_B.D34 - ContModelHIL_B.D46_tmp_o4;
  ContModelHIL_B.D34 += ContModelHIL_B.D46_tmp_o4;
  ContModelHIL_B.D46_tmp_o4 = ContModelHIL_B.D26 * 5.484E-5;
  ContModelHIL_B.D46_tmp_me = ContModelHIL_B.D46 * 0.00050874;
  ContModelHIL_B.D26 = (ContModelHIL_B.D26 * 0.00050874 + ContModelHIL_B.D46 *
                        5.484E-5) + 0.0 * ContModelHIL_B.D46_tmp_hh;
  ContModelHIL_B.D46 = (-0.00026879000000000003 * ContModelHIL_B.D46_tmp_h2 +
                        0.00043049) + -0.0 * ContModelHIL_B.D56_tmp_k;
  ContModelHIL_B.D46_tmp_h3 = 0.00026879000000000003 * ContModelHIL_B.D46_tmp_h2;
  ContModelHIL_B.D46_tmp_d = 0.0 * ContModelHIL_B.D56_tmp_k;
  ContModelHIL_B.D46_tmp_h = (ContModelHIL_B.D46_tmp_h3 + 0.00043049) +
    ContModelHIL_B.D46_tmp_d;
  ContModelHIL_B.D45_tmp_c = ContModelHIL_B.D16 * 0.06214814;
  ContModelHIL_B.rtb_ginv_tmp_c = ContModelHIL_B.D17_tmp_h * ContModelHIL_B.D56;
  ContModelHIL_B.rtb_ginv_tmp_f = ContModelHIL_B.D16 * ContModelHIL_B.D17_tmp_h;
  ContModelHIL_B.rtb_ginv_tmp_pm = -0.0 * ContModelHIL_B.D46_tmp_h2;
  ContModelHIL_B.rtb_ginv_tmp_p2 = -0.0 * ContModelHIL_B.D46_tmp_hh;
  ContModelHIL_B.ginv[45] = (((((((((((((((((0.00045390000000000003 *
    ContModelHIL_B.D14_tmp_p * ContModelHIL_B.u_i + -0.0 *
    ContModelHIL_B.D56_tmp_tmp_tmp) * ContModelHIL_B.rtb_ginv_tmp_j +
    (ContModelHIL_B.D17_tmp_h * 0.04043155 * ContModelHIL_B.D56 +
     ContModelHIL_B.D45_tmp_c * ContModelHIL_B.D17_tmp_h)) +
    ((ContModelHIL_B.D46_tmp_o4 + ContModelHIL_B.D46_tmp_me) +
     ContModelHIL_B.rtb_ginv_tmp_p2) * ContModelHIL_B.rtb_ginv_tmp_f) +
    ContModelHIL_B.D26 * ContModelHIL_B.rtb_ginv_tmp_c) + ContModelHIL_B.D16 *
    0.5 * ContModelHIL_B.D17_tmp_h * ContModelHIL_B.D46) +
    ContModelHIL_B.D17_tmp_h * 0.5 * ContModelHIL_B.D56 *
    ContModelHIL_B.D46_tmp_h) + (0.00013439500000000002 *
    ContModelHIL_B.D56_tmp_k + ContModelHIL_B.rtb_ginv_tmp_pm) *
    ContModelHIL_B.rtb_ginv_tmp_j) + ContModelHIL_B.rtb_ginv_tmp_e * 0.00046501)
    + ContModelHIL_B.rtb_ginv_tmp_e * 0.0003034) + ContModelHIL_B.rtb_ginv_tmp_e
    * 0.0393748) + ContModelHIL_B.D45_tmp * ContModelHIL_B.D45_tmp * 0.142) +
    ContModelHIL_B.D24_tmp_f * ContModelHIL_B.D24_tmp_f * 0.143) +
    ContModelHIL_B.y_a * ContModelHIL_B.y_a * 0.142) + ContModelHIL_B.ab_a *
    ContModelHIL_B.ab_a * 0.143) + ContModelHIL_B.D46_tmp_l5 *
    ContModelHIL_B.D14_tmp * ContModelHIL_B.D46_tmp) - ContModelHIL_B.D24 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.D46_tmp) +
    ContModelHIL_B.D35 * ContModelHIL_B.D14_tmp * ContModelHIL_B.D46_tmp) -
    ContModelHIL_B.D34 * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE *
    ContModelHIL_B.D46_tmp;
  ContModelHIL_B.ginv[53] = ContModelHIL_B.D67;
  ContModelHIL_B.ginv[61] = ContModelHIL_B.D68;
  ContModelHIL_B.ginv[6] = ContModelHIL_B.D17;
  ContModelHIL_B.ginv[14] = ContModelHIL_B.D27;
  ContModelHIL_B.ginv[22] = ContModelHIL_B.D37;
  ContModelHIL_B.ginv[30] = ContModelHIL_B.D47;
  ContModelHIL_B.ginv[38] = ContModelHIL_B.D45;
  ContModelHIL_B.ginv[46] = ContModelHIL_B.D67;
  ContModelHIL_B.ginv[54] = ContModelHIL_B.D47_tmp_p + 0.008139011638;
  ContModelHIL_B.ginv[62] = ContModelHIL_B.D48_tmp;
  ContModelHIL_B.ginv[7] = ContModelHIL_B.D18;
  ContModelHIL_B.ginv[15] = ContModelHIL_B.D28;
  ContModelHIL_B.ginv[23] = ContModelHIL_B.D38;
  ContModelHIL_B.ginv[31] = ContModelHIL_B.D48;
  ContModelHIL_B.ginv[39] = ContModelHIL_B.D58;
  ContModelHIL_B.ginv[47] = ContModelHIL_B.D68;
  ContModelHIL_B.ginv[55] = ContModelHIL_B.D48_tmp;
  ContModelHIL_B.ginv[63] = 0.0016750908347999997;
  ContModelHIL_inv(ContModelHIL_B.ginv, ContModelHIL_DW.Delay5_DSTATE);
  ContModelHIL_B.D17 = sin(ContModelHIL_B.D56_tmp_tmp);
  ContModelHIL_B.D18 = sin(ContModelHIL_B.D56_tmp_tmp_i);
  ContModelHIL_B.D27 = cos(ContModelHIL_B.D56_tmp_tmp_ol);
  ContModelHIL_B.D56_tmp_tmp_b = cos(ContModelHIL_B.D56_tmp_tmp_b);
  ContModelHIL_B.D46_tmp_tmp_a = cos(ContModelHIL_B.D46_tmp_tmp_a);
  ContModelHIL_B.D56_tmp_tmp_g2 = cos(ContModelHIL_B.D56_tmp_tmp_g2);
  ContModelHIL_B.D56_tmp_tmp_e = cos(ContModelHIL_B.D56_tmp_tmp_e);
  ContModelHIL_B.D46_tmp_tmp_f = cos(ContModelHIL_B.D46_tmp_tmp_f);
  ContModelHIL_B.D46_tmp_tmp_h = cos(ContModelHIL_B.D46_tmp_tmp_h);
  ContModelHIL_B.D46_tmp_tmp_e = cos(ContModelHIL_B.D46_tmp_tmp_e);
  ContModelHIL_B.D56_tmp_tmp_f = cos(ContModelHIL_B.D56_tmp_tmp_f);
  ContModelHIL_B.D56_tmp_tmp_ff = cos(ContModelHIL_B.D56_tmp_tmp_ff);
  ContModelHIL_B.D46_tmp_tmp_c = cos(ContModelHIL_B.D46_tmp_tmp_c);
  ContModelHIL_B.D46_tmp_tmp_ax = cos(ContModelHIL_B.D46_tmp_tmp_ax);
  ContModelHIL_B.D56_tmp_tmp_g = cos(ContModelHIL_B.D56_tmp_tmp_g);
  ContModelHIL_B.D56_tmp_tmp_o = cos(ContModelHIL_B.D56_tmp_tmp_o);
  ContModelHIL_B.D56_tmp_tmp_ol = sin(ContModelHIL_B.D56_tmp_tmp_iz);
  ContModelHIL_B.D28 = sin(ContModelHIL_B.rtb_ginv_tmp_tmp_p);
  ContModelHIL_B.D37 = -2.0 * ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4];
  ContModelHIL_B.D56_tmp_tmp_i = sin(ContModelHIL_B.D56_tmp_tmp_i +
    ContModelHIL_B.D37);
  ContModelHIL_B.D46_tmp_tmp *= 2.0;
  ContModelHIL_B.D38 = sin(ContModelHIL_B.D46_tmp_tmp);
  ContModelHIL_B.D46_tmp_tmp_i *= 2.0;
  ContModelHIL_B.D47 = sin(ContModelHIL_B.D46_tmp_tmp_i);
  ContModelHIL_B.D48_tmp = sin((-ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  ContModelHIL_B.D56_tmp_tmp = (ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0;
  ContModelHIL_B.D58 = sin(ContModelHIL_B.D56_tmp_tmp);
  ContModelHIL_B.D46_tmp_tmp_l *= 2.0;
  ContModelHIL_B.y_a = sin(ContModelHIL_B.D46_tmp_tmp_l);
  ContModelHIL_B.D46_tmp_tmp_o *= 2.0;
  ContModelHIL_B.ab_a = sin(ContModelHIL_B.D46_tmp_tmp_o);
  ContModelHIL_B.rtb_ginv_tmp_tmp_p = sin(ContModelHIL_B.D56_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelHIL_B.D67 = ContModelHIL_B.D15_tmp_tmp + ContModelHIL_B.D37;
  ContModelHIL_B.D68 = cos(ContModelHIL_B.D67);
  ContModelHIL_B.rtb_ginv_tmp_j = ContModelHIL_B.D15_tmp_tmp_a +
    ContModelHIL_B.D37;
  ContModelHIL_B.d = cos(ContModelHIL_B.rtb_ginv_tmp_j);
  ContModelHIL_B.d1 = cos(ContModelHIL_B.D46_tmp_tmp);
  ContModelHIL_B.D46_tmp_tmp_i = cos(ContModelHIL_B.D46_tmp_tmp_i);
  ContModelHIL_B.d2 = cos(ContModelHIL_B.D46_tmp_tmp_l);
  ContModelHIL_B.D46_tmp_tmp_o = cos(ContModelHIL_B.D46_tmp_tmp_o);
  ContModelHIL_B.D15_tmp_tmp += ContModelHIL_B.rtb_ginv_tmp_tmp;
  ContModelHIL_B.d3 = cos(ContModelHIL_B.D15_tmp_tmp);
  ContModelHIL_B.D15_tmp_tmp_a += ContModelHIL_B.rtb_ginv_tmp_tmp;
  ContModelHIL_B.d4 = cos(ContModelHIL_B.D15_tmp_tmp_a);
  ContModelHIL_B.D46_tmp_tmp = sin(ContModelHIL_B.D46_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelHIL_B.d5 = sin(ContModelHIL_B.D37 +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelHIL_B.D67 = sin(ContModelHIL_B.D67);
  ContModelHIL_B.rtb_ginv_tmp_j = sin(ContModelHIL_B.rtb_ginv_tmp_j);
  ContModelHIL_B.D56_tmp_tmp_iz = sin(ContModelHIL_B.D56_tmp_tmp_iz +
    ContModelHIL_B.D37);
  ContModelHIL_B.d6 = sin((ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3] -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  ContModelHIL_B.d7 = sin(ContModelHIL_B.rtb_ginv_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]);
  ContModelHIL_B.D15_tmp_tmp = sin(ContModelHIL_B.D15_tmp_tmp);
  ContModelHIL_B.D15_tmp_tmp_a = sin(ContModelHIL_B.D15_tmp_tmp_a);
  ContModelHIL_B.D56_tmp_tmp = sin(ContModelHIL_B.D56_tmp_tmp +
    ContModelHIL_B.D14_tmp_tmp);
  ContModelHIL_B.D46_tmp_tmp_l = sin(ContModelHIL_B.D46_tmp_tmp_l +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelHIL_B.d8 = sin(ContModelHIL_B.D37 +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelHIL_B.D37 = sin(ContModelHIL_B.D14_tmp_tmp + ContModelHIL_B.D37);
  ContModelHIL_B.d9 = sin(ContModelHIL_B.rtb_ginv_tmp_tmp +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7]);
  ContModelHIL_B.D14_tmp_tmp = sin(ContModelHIL_B.D14_tmp_tmp +
    ContModelHIL_B.rtb_ginv_tmp_tmp);
  ContModelHIL_B.rtb_ginv_tmp_tmp = cos(ContModelHIL_B.rtb_ginv_tmp_tmp);
  ContModelHIL_B.D14_tmp_d = ContModelHIL_B.D14_tmp_d * ContModelHIL_B.u +
    ContModelHIL_B.D14_tmp_a * ContModelHIL_B.D14_tmp_c;
  ContModelHIL_B.D14_tmp_a = ContModelHIL_B.D14_tmp_m *
    ContModelHIL_B.Observer_beta;
  ContModelHIL_B.d10 = 2.0 * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.d11 = 0.09794 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [7] * 0.143;
  ContModelHIL_B.D16_tmp_n = ContModelHIL_B.D16_tmp_n * ContModelHIL_B.u +
    ContModelHIL_B.D14_tmp_cz;
  ContModelHIL_B.d12 = ContModelHIL_B.D16_tmp_n * ContModelHIL_B.D46_tmp_ln;
  ContModelHIL_B.d13 = ContModelHIL_B.D14_tmp_a * ContModelHIL_B.u;
  ContModelHIL_B.d14 = 2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.d15 = -2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelHIL_B.d149 = -2.0 * ContModelHIL_B.D14_tmp;
  ContModelHIL_B.D14_tmp_a = (ContModelHIL_B.D14_tmp_a -
    ContModelHIL_B.D16_tmp_p) * ContModelHIL_B.d10 + ContModelHIL_B.D16_tmp_pt *
    ContModelHIL_B.d149;
  ContModelHIL_B.D16_tmp_p = ((ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    - ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[5]) +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]) +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelHIL_B.D16_tmp_pt = ((ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[3]
    + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[5]) +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[6]) +
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[7];
  ContModelHIL_B.d20 = 2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelHIL_B.d22 = 2.0 * ContModelHIL_B.Observer_beta;
  ContModelHIL_B.dv[24] = -(((((((ContModelHIL_B.D14_tmp_o *
    ContModelHIL_B.DigitalClock - ContModelHIL_B.D14_tmp_pb) *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE + ContModelHIL_B.D14_tmp_d *
    ContModelHIL_B.D14_tmp) * (ContModelHIL_B.d20 * ContModelHIL_B.D14_tmp_p) +
    ((ContModelHIL_B.d22 * ContModelHIL_B.D15_tmp_g * ContModelHIL_B.u + (cos
    (ContModelHIL_B.D16_tmp_p) - cos(ContModelHIL_B.D16_tmp_pt))) *
     ContModelHIL_B.d11 + ContModelHIL_B.d14 * ContModelHIL_B.Observer_beta *
     ContModelHIL_B.D15_tmp * ContModelHIL_B.D34_tmp_m)) +
    (ContModelHIL_B.D14_tmp_d * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE +
     ContModelHIL_B.D14_tmp_o3) * (ContModelHIL_B.d15 * ContModelHIL_B.u_i)) +
    ((ContModelHIL_B.D16_tmp_l - ContModelHIL_B.d13) * ContModelHIL_B.d10 +
     ContModelHIL_B.d12) * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) +
    ContModelHIL_B.D14_tmp_a * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5])
    * 0.5);
  ContModelHIL_B.dv[32] = -((((ContModelHIL_B.D15_tmp_c *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DigitalClock + ContModelHIL_B.d11 *
    ContModelHIL_B.Observer_beta * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.D17_tmp_p) + ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6]
    * ContModelHIL_B.Observer_beta * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.D37_tmp) + ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    ContModelHIL_B.Observer_beta * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.D34_tmp_m) + ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4]
    * ContModelHIL_B.Observer_beta * ContModelHIL_B.D15_tmp_c * ContModelHIL_B.u);
  ContModelHIL_B.D14_tmp_d = -0.19588 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7] * 0.143;
  ContModelHIL_B.D14_tmp_o = -ContModelHIL_B.D16_tmp *
    ContModelHIL_B.DigitalClock + ContModelHIL_B.d13;
  ContModelHIL_B.D14_tmp_pb = -2.0 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.dv[40] = -(((((((ContModelHIL_B.D17_tmp_tmp_f *
    ContModelHIL_B.u + ContModelHIL_B.D17_tmp_tmp) * -ContModelHIL_B.D14_tmp_m +
    ContModelHIL_B.D27_tmp) + ContModelHIL_B.D27_tmp_i) * ContModelHIL_B.d15 +
    (ContModelHIL_B.D15_tmp_c * ContModelHIL_B.d14 * ContModelHIL_B.D15_tmp *
     ContModelHIL_B.DigitalClock + (ContModelHIL_B.D28_tmp *
    ContModelHIL_B.D14_tmp_b + ContModelHIL_B.D17_tmp_tmp_a *
    ContModelHIL_B.D14_tmp_cv) * ContModelHIL_B.D14_tmp_d)) +
    (ContModelHIL_B.D14_tmp_o * ContModelHIL_B.D14_tmp_pb + ContModelHIL_B.d12) *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) +
    ContModelHIL_B.D14_tmp_a * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3])
    * 0.5);
  ContModelHIL_B.D14_tmp_a = 0.09794 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143;
  ContModelHIL_B.d12 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] +
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelHIL_B.D17_tmp_tmp = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]
    * ContModelHIL_B.u;
  ContModelHIL_B.D17_tmp_tmp_f = 0.11464 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142 *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D14_tmp_o3 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    0.17 * 0.143 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D16_tmp = ContModelHIL_B.D14_tmp_a * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D16_tmp_l = 2.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.D27_tmp = 0.09794 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143;
  ContModelHIL_B.D27_tmp_i = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] +
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelHIL_B.D28_tmp = ContModelHIL_B.D27_tmp_i * 2.0 +
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelHIL_B.d16 = -2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.D14_tmp_k *= ContModelHIL_B.D27_tmp;
  ContModelHIL_B.d17 = ContModelHIL_B.d12 - ContModelHIL_B.D17_tmp_tmp;
  ContModelHIL_B.d18 = ContModelHIL_B.d12 +
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelHIL_B.d19 = ContModelHIL_B.d18 - ContModelHIL_B.D17_tmp_tmp;
  ContModelHIL_B.d21 = ContModelHIL_B.d16 * 0.040588879999999994;
  ContModelHIL_B.d23 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    0.040588879999999994;
  ContModelHIL_B.d24 = ContModelHIL_B.d16 * ContModelHIL_B.u +
    ContModelHIL_B.D28_tmp;
  ContModelHIL_B.d52 = 0.22928 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5];
  ContModelHIL_B.d54 = 0.19588 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5];
  ContModelHIL_B.d91 = -2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelHIL_B.dv[48] = -(((((((((((((((((ContModelHIL_B.D14_tmp_a *
    ContModelHIL_B.D14_tmp_cv * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE + ContModelHIL_B.d23 *
    ContModelHIL_B.D14_tmp_p * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE) + ContModelHIL_B.d52 * 0.142 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.u_i) +
    ContModelHIL_B.D16_tmp_l * 0.17 * 0.143 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.u_i) +
    ContModelHIL_B.D17_tmp_tmp_f * ContModelHIL_B.D17_tmp_j) +
    ContModelHIL_B.D14_tmp_o3 * ContModelHIL_B.D17_tmp_j) + ContModelHIL_B.d54 *
    0.143 * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE *
    ContModelHIL_B.D14_tmp_b) + ContModelHIL_B.D16_tmp *
    ContModelHIL_B.D17_tmp_p) + -0.22928 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.142 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.u_i *
    ContModelHIL_B.u) + -0.22928 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.142 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.u_i *
    ContModelHIL_B.u) + ContModelHIL_B.d91 * 0.17 * 0.143 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.u_i *
    ContModelHIL_B.u) + ContModelHIL_B.d15 * 0.17 * 0.143 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.u_i *
    ContModelHIL_B.u) + -0.19588 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.D14_tmp_b *
    ContModelHIL_B.u) + -0.19588 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.143 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.D14_tmp_b *
    ContModelHIL_B.u) + ContModelHIL_B.D14_tmp_d *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * ContModelHIL_B.D14_tmp_b *
    ContModelHIL_B.u) * ContModelHIL_B.Observer_beta + (ContModelHIL_B.d19 *
    ContModelHIL_B.D14_tmp_n + ContModelHIL_B.d17 * ContModelHIL_B.D16_tmp_tmp) *
    (ContModelHIL_B.d10 * ContModelHIL_B.DigitalClock)) + ((((ContModelHIL_B.d12
    * 2.0 * 0.040588879999999994 + ContModelHIL_B.D14_tmp_k) * ContModelHIL_B.u
    + ContModelHIL_B.d21) * ContModelHIL_B.D14_tmp_p +
    ((((ContModelHIL_B.D17_tmp_tmp_f * ContModelHIL_B.u_i +
        ContModelHIL_B.D14_tmp_o3 * ContModelHIL_B.u_i) + ContModelHIL_B.D16_tmp
       * ContModelHIL_B.D14_tmp_b) - ContModelHIL_B.D27_tmp * ContModelHIL_B.u_i
      * ContModelHIL_B.D14_tmp_c * ContModelHIL_B.u) - (ContModelHIL_B.D16_tmp_l
    - ContModelHIL_B.D28_tmp * ContModelHIL_B.u) * ContModelHIL_B.D14_tmp_n)) *
    ContModelHIL_B.Observer_beta +
    ((ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
      ContModelHIL_B.D14_tmp_p * ContModelHIL_B.D14_tmp_c + ContModelHIL_B.d24 *
      ContModelHIL_B.D14_tmp_b) * 0.01400542 + (ContModelHIL_B.d17 *
    0.08117775999999999 + ContModelHIL_B.D14_tmp_k) * ContModelHIL_B.u_i) *
    ContModelHIL_B.DigitalClock) * ContModelHIL_B.D14_tmp) * 0.5);
  ContModelHIL_B.D14_tmp_d = ContModelHIL_B.d18 * ContModelHIL_B.u;
  ContModelHIL_B.d15 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D17_tmp_tmp_f = 2.0 * ContModelHIL_B.D14_tmp_cv;
  ContModelHIL_B.D14_tmp_o3 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]
    - ContModelHIL_B.D14_tmp_d;
  ContModelHIL_B.dv[56] = -(((((ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4]
    * ContModelHIL_B.D14_tmp_cv * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE + ContModelHIL_B.d15 *
    ContModelHIL_B.D17_tmp_p) + ContModelHIL_B.d10 * ContModelHIL_B.D14_tmp_b *
    ContModelHIL_B.D14_tmp_o3) * ContModelHIL_B.Observer_beta +
    ContModelHIL_B.D17_tmp_tmp_f * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE
    * ContModelHIL_B.DigitalClock * ContModelHIL_B.d19) +
    (((ContModelHIL_B.D14_tmp_d -
       ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
      ContModelHIL_B.D17_tmp_tmp_f + ContModelHIL_B.d15 *
      ContModelHIL_B.D14_tmp_b) * ContModelHIL_B.Observer_beta + 2.0 *
     ContModelHIL_B.DigitalClock * ContModelHIL_B.D14_tmp_b * ContModelHIL_B.d19)
    * ContModelHIL_B.D14_tmp) * 0.00700271);
  ContModelHIL_B.D14_tmp_d = ContModelHIL_B.D15_tmp_tmp_o +
    ContModelHIL_B.D15_tmp_tmp_k;
  ContModelHIL_B.d10 = ContModelHIL_B.d15 * ContModelHIL_B.DigitalClock;
  ContModelHIL_B.d15 = ContModelHIL_B.D14_tmp_d *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelHIL_B.dv[25] = -(((((((((cos(ContModelHIL_B.D16_tmp_p -
    ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]) - cos
    (ContModelHIL_B.D16_tmp_pt - ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]))
    - cos(ContModelHIL_B.D16_tmp_p +
          ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4])) + cos
    (ContModelHIL_B.D16_tmp_pt + ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[4]))
    + sin(ContModelHIL_B.D16_tmp_p) * 2.0) + sin(ContModelHIL_B.D16_tmp_pt) *
    2.0) * (-0.024485 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7] *
            0.143) + (-ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
                      ContModelHIL_B.Observer_beta * ContModelHIL_B.D37_tmp +
                      ContModelHIL_B.D34_tmp_m * ContModelHIL_B.d10)) +
    ContModelHIL_B.d15 * ContModelHIL_B.DigitalClock * ContModelHIL_B.u) +
    (ContModelHIL_B.D15_tmp_c * ContModelHIL_B.DigitalClock * ContModelHIL_B.u +
     ContModelHIL_B.D34_tmp_m * -ContModelHIL_B.Observer_beta) *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) +
    (ContModelHIL_B.D16_tmp_n * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE +
     ContModelHIL_B.D14_tmp_o * ContModelHIL_B.D14_tmp) *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]);
  ContModelHIL_B.D16_tmp_n = ContModelHIL_B.D15_tmp_c *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.D16_tmp_p = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.dv[33] = -((((-ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]
    * ContModelHIL_B.Observer_beta * ContModelHIL_B.D15_tmp_c *
    ContModelHIL_B.D15_tmp + ContModelHIL_B.d11 * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.D17_tmp_p) +
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.D37_tmp) +
    ContModelHIL_B.D16_tmp_p * ContModelHIL_B.DigitalClock *
    ContModelHIL_B.D34_tmp_m) + ContModelHIL_B.D16_tmp_n *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.u);
  ContModelHIL_B.D16_tmp_pt = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]
    - ContModelHIL_B.d12 * ContModelHIL_B.u;
  ContModelHIL_B.D14_tmp_o = (((ContModelHIL_B.d20 +
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) * 0.17 * 0.143 +
    ContModelHIL_B.d12 * 0.22928 * 0.142) + ContModelHIL_B.d21 *
    ContModelHIL_B.u) + ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.17
    * 0.143 * ContModelHIL_B.rtb_ginv_tmp_e;
  ContModelHIL_B.D17_tmp_tmp_f = 4.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.D16_tmp = -4.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelHIL_B.D28_tmp = -4.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelHIL_B.dv[41] = -((((((((((-3.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] + ContModelHIL_B.D16_tmp)
    + ContModelHIL_B.D28_tmp) + ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3]
    * ContModelHIL_B.rtb_ginv_tmp_tmp) + ContModelHIL_B.D17_tmp_tmp_f *
    ContModelHIL_B.u) * (-0.00700271 * ContModelHIL_B.D14_tmp_cv) +
    (-ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * ContModelHIL_B.u +
     ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3]) * 0.047378399999999994)
    + ContModelHIL_B.D14_tmp_o * ContModelHIL_B.D14_tmp_p) *
    ContModelHIL_B.DigitalClock +
    ((ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.08312 * 0.285 *
      ContModelHIL_B.D15_tmp + ContModelHIL_B.D16_tmp_pt *
      ContModelHIL_B.D14_tmp_tmp_i) + ContModelHIL_B.D14_tmp_o3 *
     ContModelHIL_B.D14_tmp_tmp_o) * ContModelHIL_B.d22) *
    -ContModelHIL_B.D14_tmp +
    ((((-ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * ContModelHIL_B.u +
        ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) *
       0.023689199999999997 + ContModelHIL_B.D16_tmp_pt *
       ContModelHIL_B.D16_tmp_tmp) + ContModelHIL_B.D14_tmp_o3 *
      ContModelHIL_B.D14_tmp_n) * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE
     + (ContModelHIL_B.D14_tmp_a * ContModelHIL_B.D15_tmp_g *
        ContModelHIL_B.D15_tmp + ContModelHIL_B.d23 * ContModelHIL_B.D15_tmp_f *
        ContModelHIL_B.D15_tmp)) * (-2.0 * ContModelHIL_B.Observer_beta)) +
    (((ContModelHIL_B.rtb_ginv_tmp_e *
       ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] + ContModelHIL_B.d24) *
      ContModelHIL_B.D14_tmp_tmp_o + ContModelHIL_B.D14_tmp_o *
      ContModelHIL_B.u_i) * ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE +
     (-ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.17 * 0.143 *
      ContModelHIL_B.D15_tmp_f * ContModelHIL_B.D17_tmp_h -
      ContModelHIL_B.D27_tmp * ContModelHIL_B.D15_tmp_g *
      ContModelHIL_B.D17_tmp_h)) * ContModelHIL_B.DigitalClock) * 0.5);
  ContModelHIL_B.D14_tmp_a = ContModelHIL_B.D16_tmp_tmp +
    ContModelHIL_B.D14_tmp_n;
  ContModelHIL_B.dv[49] = -((((ContModelHIL_B.D14_tmp_d *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.u +
    (-ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] *
     ContModelHIL_B.Observer_beta * ContModelHIL_B.D37_tmp + ContModelHIL_B.d10 *
     ContModelHIL_B.D37_tmp)) - (ContModelHIL_B.Observer_beta *
    ContModelHIL_B.D17_tmp_p - ContModelHIL_B.D15_tmp_g *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.u) * ContModelHIL_B.d11) +
    (ContModelHIL_B.D14_tmp_d * ContModelHIL_B.DigitalClock * ContModelHIL_B.u +
     ContModelHIL_B.D37_tmp * -ContModelHIL_B.Observer_beta) *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6]) +
    ((ContModelHIL_B.D14_tmp_a * ContModelHIL_B.Observer_beta * ContModelHIL_B.u
      + ContModelHIL_B.D14_tmp_cz) *
     ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE + (-ContModelHIL_B.D14_tmp_a *
    ContModelHIL_B.DigitalClock + ContModelHIL_B.d13) * ContModelHIL_B.D14_tmp) *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]);
  ContModelHIL_B.dv[57] = -(((((ContModelHIL_B.d18 -
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4]) *
    ContModelHIL_B.D46_tmp_ld + ContModelHIL_B.D16_tmp_l *
    ContModelHIL_B.D15_tmp_g) - (ContModelHIL_B.d18 +
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4]) *
    ContModelHIL_B.D46_tmp_nu) * ContModelHIL_B.DigitalClock +
    ContModelHIL_B.d22 * ContModelHIL_B.D17_tmp_p * ContModelHIL_B.d19) *
    -0.00700271);
  ContModelHIL_B.dv[26] = -(((ContModelHIL_B.d11 * ContModelHIL_B.D15_tmp_g *
    ContModelHIL_B.D15_tmp + ContModelHIL_B.d15 * ContModelHIL_B.D15_tmp) +
    ContModelHIL_B.D15_tmp_c * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3]
    * ContModelHIL_B.D15_tmp) - ContModelHIL_B.D34_tmp_m *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * ContModelHIL_B.u);
  ContModelHIL_B.dv[34] = -(((ContModelHIL_B.D16_tmp_n * ContModelHIL_B.D15_tmp
    - ContModelHIL_B.d11 * ContModelHIL_B.D17_tmp_p * ContModelHIL_B.u) +
    ContModelHIL_B.D37_tmp * -ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    ContModelHIL_B.u) - ContModelHIL_B.D34_tmp_m *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * ContModelHIL_B.u);
  ContModelHIL_B.dv[42] = -0.0;
  ContModelHIL_B.dv[50] = -((ContModelHIL_B.d18 * 0.09794 * 0.143 *
    ContModelHIL_B.D15_tmp_g * ContModelHIL_B.D15_tmp + ContModelHIL_B.d12 *
    0.040588879999999994 * ContModelHIL_B.D15_tmp_f * ContModelHIL_B.D15_tmp) -
    ContModelHIL_B.D37_tmp * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    ContModelHIL_B.u);
  ContModelHIL_B.dv[58] = -((ContModelHIL_B.d18 * ContModelHIL_B.D15_tmp_g *
    ContModelHIL_B.D15_tmp - ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] *
    ContModelHIL_B.D17_tmp_p * ContModelHIL_B.u) * 0.01400542);
  ContModelHIL_B.dv[27] = -(-ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    0.08312 * 0.040588879999999994 * ContModelHIL_B.u_i -
    (ContModelHIL_B.D27_tmp_i * 0.08312 * ContModelHIL_B.D14_tmp_b +
     ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7] * 0.17 *
     ContModelHIL_B.D14_tmp_c) * 0.01400542);
  ContModelHIL_B.D14_tmp_d = 0.04043155 * ContModelHIL_B.D17;
  ContModelHIL_B.D14_tmp_a = 0.06214814 * ContModelHIL_B.D17;
  ContModelHIL_B.d10 = 0.0009810686847999998 * ContModelHIL_B.D17;
  ContModelHIL_B.d11 = 0.0009879776191999998 * ContModelHIL_B.D17;
  ContModelHIL_B.D16_tmp_n = 5.484E-5 * ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d13 = 0.00050874 * ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d15 = 0.0018662108031999999 * ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.D16_tmp_pt = 0.0041327000000000004 * ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d22 = 8.085E-5 * ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.D14_tmp_o = 0.00034964 * ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.D14_tmp_o3 = 0.0013716908347999998 * ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.D27_tmp = 0.0 * ContModelHIL_B.D46_tmp_m;
  ContModelHIL_B.D27_tmp_i = 5.484E-5 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.D14_tmp_k = 0.00050874 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.d21 = 0.0018662108031999999 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.d23 = 0.0041327000000000004 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.d24 = 0.004761842800000001 * ContModelHIL_B.D46_tmp_tmp_h;
  ContModelHIL_B.D14_tmp_cv = 0.004761842800000001 *
    ContModelHIL_B.D56_tmp_tmp_ff;
  ContModelHIL_B.D14_tmp_n = 8.085E-5 * ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.D14_tmp_tmp_i = 0.00034964 * ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.D14_tmp_tmp_o = 0.0013716908347999998 *
    ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.D14_tmp_cz = 0.00093002 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D15_tmp_tmp_o = 0.0006068 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D15_tmp_tmp_k = 0.0037324216063999997 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D16_tmp_tmp = 0.0027433816695999996 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D34_tmp_m = 0.008265400000000001 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.D37_tmp = -0.0 * ContModelHIL_B.D46_tmp_p;
  ContModelHIL_B.rtb_ginv_tmp_e = 5.484E-5 * ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.d56 = 0.00050874 * ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.d57 = 0.0018662108031999999 * ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.d58 = 0.0041327000000000004 * ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.d59 = 0.004761842800000001 * ContModelHIL_B.D46_tmp_tmp_c;
  ContModelHIL_B.d60 = -0.0 * ContModelHIL_B.D46_tmp_l;
  ContModelHIL_B.d61 = 0.004761842800000001 * ContModelHIL_B.D56_tmp_tmp_o;
  ContModelHIL_B.d62 = 8.085E-5 * ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.d63 = 0.00034964 * ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.d64 = 0.0013716908347999998 * ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.d65 = 0.0 * ContModelHIL_B.D56_tmp_g;
  ContModelHIL_B.d66 = 0.0 * ContModelHIL_B.D56_tmp_dh;
  ContModelHIL_B.d67 = 0.0 * ContModelHIL_B.D56_tmp_b;
  ContModelHIL_B.d68 = 0.0 * ContModelHIL_B.D56_tmp_bs;
  ContModelHIL_B.d55 =
    ((((((((((((((((((((((((((((((((((((((((((((((((((((-0.019747543696 *
    ContModelHIL_B.D56_tmp_tmp_e + 0.006747495411199999 *
    ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.D27_tmp) + 0.0027062010112 *
    ContModelHIL_B.D27) + 0.0040412944 * ContModelHIL_B.D27) -
    ContModelHIL_B.D27_tmp_i) + ContModelHIL_B.D14_tmp_k) + ContModelHIL_B.d21)
    + ContModelHIL_B.d23) + ContModelHIL_B.d24) + 0.0023282610207999996 *
    ContModelHIL_B.D46_tmp_tmp_e) + ContModelHIL_B.D46_tmp_tmp_m) +
    0.0023282610207999996 * ContModelHIL_B.D56_tmp_tmp_f) +
    ContModelHIL_B.D14_tmp_cv) - ContModelHIL_B.D14_tmp_n) +
    ContModelHIL_B.D14_tmp_tmp_i) + ContModelHIL_B.D14_tmp_tmp_o) +
    ContModelHIL_B.D14_tmp_cz) + ContModelHIL_B.D15_tmp_tmp_o) + 0.0787496 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.D15_tmp_tmp_k) +
    0.0019621373695999996 * ContModelHIL_B.D15_tmp) + ContModelHIL_B.D16_tmp_tmp)
    + 0.0019759552383999996 * ContModelHIL_B.D15_tmp) + ContModelHIL_B.D34_tmp_m)
    + 0.04043155 * ContModelHIL_B.D56_tmp_tmp_b) - 0.06214814 *
    ContModelHIL_B.D56_tmp_tmp_b) + 0.0009810686847999998 *
    ContModelHIL_B.D56_tmp_tmp_b) + 0.0009879776191999998 *
    ContModelHIL_B.D56_tmp_tmp_b) + 0.0027062010112 *
    ContModelHIL_B.D46_tmp_tmp_a) + 0.0040412944 * ContModelHIL_B.D46_tmp_tmp_a)
    + ContModelHIL_B.D37_tmp) + 0.0027062010112 * ContModelHIL_B.D56_tmp_tmp_g2)
    + 0.0040412944 * ContModelHIL_B.D56_tmp_tmp_g2) -
                       ContModelHIL_B.rtb_ginv_tmp_e) + ContModelHIL_B.d56) +
                     ContModelHIL_B.d57) + ContModelHIL_B.d58) +
                   ContModelHIL_B.d59) + 0.0023282610207999996 *
                  ContModelHIL_B.D46_tmp_tmp_ax) + ContModelHIL_B.d60) +
                0.0023282610207999996 * ContModelHIL_B.D56_tmp_tmp_g) +
               ContModelHIL_B.d61) - ContModelHIL_B.d62) + ContModelHIL_B.d63) +
            ContModelHIL_B.d64) + ContModelHIL_B.D46_tmp_mv) +
          ContModelHIL_B.d65) + ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.d66)
       + ContModelHIL_B.D56_tmp_c) + ContModelHIL_B.d67) +
     ContModelHIL_B.D56_tmp_fb) + ContModelHIL_B.d68;
  ContModelHIL_B.d159 = -0.0 * ContModelHIL_B.D24_tmp + -0.0 *
    ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.d160 = 0.004761842800000001 * ContModelHIL_B.D28;
  ContModelHIL_B.dv[35] = -(((((((((((((((((ContModelHIL_B.d159 +
    ContModelHIL_B.D14_tmp_d) - ContModelHIL_B.D14_tmp_a) + ContModelHIL_B.d10)
    + ContModelHIL_B.d11) - ContModelHIL_B.D16_tmp_n) + ContModelHIL_B.d13) +
    ContModelHIL_B.d15) + ContModelHIL_B.D16_tmp_pt) + 0.0027062010112 *
    ContModelHIL_B.D18) + 0.0040412944 * ContModelHIL_B.D18) -
    ContModelHIL_B.d22) + ContModelHIL_B.D14_tmp_o) + ContModelHIL_B.D14_tmp_o3)
    + 0.0023282610207999996 * ContModelHIL_B.D56_tmp_tmp_ol) +
    ContModelHIL_B.d160) * ContModelHIL_B.d14 + ContModelHIL_B.d55 *
    -ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) * 0.25);
  ContModelHIL_B.d25 = ContModelHIL_B.D17_tmp_tmp_f * 0.0;
  ContModelHIL_B.d26 = ContModelHIL_B.D16_tmp_l * 0.0;
  ContModelHIL_B.d27 = -2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.d28 = ContModelHIL_B.d27 * 0.0069089343999999995;
  ContModelHIL_B.d29 = -4.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.d30 = -0.45856 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.08312 * 0.142;
  ContModelHIL_B.tmp_tmp = ContModelHIL_B.d29 * 0.08312 * 0.17 * 0.143;
  ContModelHIL_B.d31 = -0.39176 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.d32 = ContModelHIL_B.d29 * 0.0;
  ContModelHIL_B.d33 = ContModelHIL_B.d31 * 0.08312 * 0.143;
  ContModelHIL_B.d31 = ContModelHIL_B.d31 * 0.17 * 0.143;
  ContModelHIL_B.d34 = ContModelHIL_B.d29 * 0.0069089343999999995;
  ContModelHIL_B.d35 = ContModelHIL_B.d27 * 0.04043155;
  ContModelHIL_B.d36 = ContModelHIL_B.d14 * 0.06214814;
  ContModelHIL_B.d37 = ContModelHIL_B.d28 * 0.142;
  ContModelHIL_B.d28 *= 0.143;
  ContModelHIL_B.d38 = ContModelHIL_B.d14 * 5.484E-5;
  ContModelHIL_B.d39 = ContModelHIL_B.d27 * 0.00050874;
  ContModelHIL_B.d40 = -0.0262846592 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142;
  ContModelHIL_B.tmp_tmp_p = ContModelHIL_B.d27 * 0.028900000000000006 * 0.143;
  ContModelHIL_B.d111 = 4.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.d41 = ContModelHIL_B.d111 * 0.0;
  ContModelHIL_B.tmp_tmp_b = ContModelHIL_B.d14 * 8.085E-5;
  ContModelHIL_B.tmp_tmp_c = ContModelHIL_B.d27 * 0.00034964;
  ContModelHIL_B.tmp_tmp_n = -0.0191844872 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143;
  ContModelHIL_B.d42 = ContModelHIL_B.d16 * 0.0;
  ContModelHIL_B.d43 = ContModelHIL_B.d16 * 0.0069089343999999995;
  ContModelHIL_B.d44 = -0.39176 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.d45 = -0.19588 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.d46 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.0069089343999999995;
  ContModelHIL_B.d47 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.04043155;
  ContModelHIL_B.tmp_tmp_nm = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.06214814;
  ContModelHIL_B.tmp_tmp_er = ContModelHIL_B.d46 * 0.142;
  ContModelHIL_B.d46 *= 0.143;
  ContModelHIL_B.tmp_tmp_d = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    5.484E-5;
  ContModelHIL_B.tmp_tmp_ik = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.00050874;
  ContModelHIL_B.tmp_tmp_g = 0.0131423296 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.142;
  ContModelHIL_B.tmp_tmp_nn = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    8.085E-5;
  ContModelHIL_B.tmp_tmp_l = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.00034964;
  ContModelHIL_B.tmp_tmp_ce = 0.0095922436 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.143;
  ContModelHIL_B.d48 = -0.22928 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142;
  ContModelHIL_B.d49 = ContModelHIL_B.d16 * 0.08312 * 0.17 * 0.143;
  ContModelHIL_B.d50 = ContModelHIL_B.d45 * 0.08312 * 0.143;
  ContModelHIL_B.d45 = ContModelHIL_B.d45 * 0.17 * 0.143;
  ContModelHIL_B.d51 = 0.17 * ContModelHIL_B.D14_tmp_c + 0.08312 *
    ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.d53 = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.028900000000000006 * 0.143;
  ContModelHIL_B.d90 = ContModelHIL_B.d35 * ContModelHIL_B.D56_tmp_tmp_e;
  ContModelHIL_B.d92 = ContModelHIL_B.d36 * ContModelHIL_B.D56_tmp_tmp_e;
  ContModelHIL_B.d93 = ContModelHIL_B.d37 * ContModelHIL_B.D56_tmp_tmp_e;
  ContModelHIL_B.d94 = ContModelHIL_B.d28 * ContModelHIL_B.D56_tmp_tmp_e;
  ContModelHIL_B.d96 = ContModelHIL_B.d32 * ContModelHIL_B.D46_tmp_m;
  ContModelHIL_B.d97 = ContModelHIL_B.d26 * ContModelHIL_B.d1;
  ContModelHIL_B.d98 = ContModelHIL_B.d30 * ContModelHIL_B.D27;
  ContModelHIL_B.d99 = ContModelHIL_B.tmp_tmp * ContModelHIL_B.D27;
  ContModelHIL_B.d100 = ContModelHIL_B.d38 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.d101 = ContModelHIL_B.d39 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.d102 = ContModelHIL_B.d40 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.d103 = ContModelHIL_B.tmp_tmp_p * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.d104 = ContModelHIL_B.d32 * ContModelHIL_B.D46_tmp_n;
  ContModelHIL_B.d105 = ContModelHIL_B.d26 * ContModelHIL_B.D46_tmp_tmp_i;
  ContModelHIL_B.d106 = ContModelHIL_B.d33 * ContModelHIL_B.D56_tmp_tmp_f;
  ContModelHIL_B.d107 = ContModelHIL_B.d31 * ContModelHIL_B.D56_tmp_tmp_ff;
  ContModelHIL_B.d108 = ContModelHIL_B.tmp_tmp_b * ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.d109 = ContModelHIL_B.tmp_tmp_c * ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.d110 = ContModelHIL_B.tmp_tmp_n * ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.d112 = ContModelHIL_B.d45 * ContModelHIL_B.D46_tmp_tmp;
  ContModelHIL_B.tmp_tmp_i3 = -4.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.d113 = ContModelHIL_B.d48 * ContModelHIL_B.D56_tmp_tmp_i;
  ContModelHIL_B.d114 = ContModelHIL_B.d49 * ContModelHIL_B.D56_tmp_tmp_i;
  ContModelHIL_B.d115 = ContModelHIL_B.d50 * ContModelHIL_B.D56_tmp_tmp_iz;
  ContModelHIL_B.d116 = ContModelHIL_B.tmp_tmp_nm * ContModelHIL_B.d6;
  ContModelHIL_B.d117 = ContModelHIL_B.d32 * ContModelHIL_B.D46_tmp_j;
  ContModelHIL_B.d118 = ContModelHIL_B.tmp_tmp_d * ContModelHIL_B.D38;
  ContModelHIL_B.d119 = ContModelHIL_B.tmp_tmp_ik * ContModelHIL_B.D38;
  ContModelHIL_B.d120 = ContModelHIL_B.tmp_tmp_g * ContModelHIL_B.D38;
  ContModelHIL_B.d121 = ContModelHIL_B.d53 * ContModelHIL_B.D38;
  ContModelHIL_B.d123 = ContModelHIL_B.d32 * ContModelHIL_B.D56_tmp_g;
  ContModelHIL_B.d124 = ContModelHIL_B.d32 * ContModelHIL_B.D46_tmp_ld;
  ContModelHIL_B.d125 = ContModelHIL_B.tmp_tmp_nn * ContModelHIL_B.D47;
  ContModelHIL_B.d126 = ContModelHIL_B.tmp_tmp_l * ContModelHIL_B.D47;
  ContModelHIL_B.d127 = ContModelHIL_B.tmp_tmp_ce * ContModelHIL_B.D47;
  ContModelHIL_B.d128 = ContModelHIL_B.d32 * ContModelHIL_B.D56_tmp_dh;
  ContModelHIL_B.d129 = ContModelHIL_B.d16 * 0.00050874;
  ContModelHIL_B.d130 = ContModelHIL_B.d16 * 0.00034964;
  ContModelHIL_B.d131 = ContModelHIL_B.d16 * 0.04043155;
  ContModelHIL_B.d136 = ContModelHIL_B.d47 * ContModelHIL_B.D48_tmp;
  ContModelHIL_B.d137 = ContModelHIL_B.tmp_tmp_er * ContModelHIL_B.D48_tmp;
  ContModelHIL_B.d138 = ContModelHIL_B.d46 * ContModelHIL_B.D48_tmp;
  ContModelHIL_B.d139 = ContModelHIL_B.d47 * ContModelHIL_B.D58;
  ContModelHIL_B.d140 = ContModelHIL_B.tmp_tmp_nm * ContModelHIL_B.D58;
  ContModelHIL_B.d141 = ContModelHIL_B.tmp_tmp_er * ContModelHIL_B.D58;
  ContModelHIL_B.d142 = ContModelHIL_B.d46 * ContModelHIL_B.D58;
  ContModelHIL_B.d143 = ContModelHIL_B.tmp_tmp_d * ContModelHIL_B.y_a;
  ContModelHIL_B.d144 = ContModelHIL_B.tmp_tmp_ik * ContModelHIL_B.y_a;
  ContModelHIL_B.d145 = ContModelHIL_B.tmp_tmp_g * ContModelHIL_B.y_a;
  ContModelHIL_B.d146 = ContModelHIL_B.tmp_tmp_nn * ContModelHIL_B.ab_a;
  ContModelHIL_B.d147 = ContModelHIL_B.tmp_tmp_l * ContModelHIL_B.ab_a;
  ContModelHIL_B.d148 = ContModelHIL_B.tmp_tmp_ce * ContModelHIL_B.ab_a;
  ContModelHIL_B.d150 = ContModelHIL_B.d31 * ContModelHIL_B.D46_tmp_tmp_h;
  ContModelHIL_B.d151 = ContModelHIL_B.d29 * 0.00046501 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d152 = ContModelHIL_B.d29 * 0.0003034 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d153 = -0.0525693184 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142 *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d154 = -0.0383689744 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143 *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d155 = ContModelHIL_B.d29 * 0.028900000000000006 * 0.143 *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d156 = ContModelHIL_B.d31 * ContModelHIL_B.D46_tmp_tmp_c;
  ContModelHIL_B.d184 = ContModelHIL_B.d25 * ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.d185 = ContModelHIL_B.d26 * ContModelHIL_B.d;
  ContModelHIL_B.d161 = ((ContModelHIL_B.d25 * ContModelHIL_B.D24_tmp +
    ContModelHIL_B.d184) + ContModelHIL_B.d26 * ContModelHIL_B.D68) +
    ContModelHIL_B.d185;
  ContModelHIL_B.d162 = ContModelHIL_B.d26 * ContModelHIL_B.d2;
  ContModelHIL_B.d163 = ContModelHIL_B.d26 * ContModelHIL_B.D46_tmp_tmp_o;
  ContModelHIL_B.d164 = ContModelHIL_B.d42 * ContModelHIL_B.d3;
  ContModelHIL_B.d165 = ContModelHIL_B.d42 * ContModelHIL_B.d4;
  ContModelHIL_B.d166 = ContModelHIL_B.D16_tmp_l * 5.484E-5 *
    ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d167 = ContModelHIL_B.d129 * ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d168 = -0.0262846592 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.142 *
    ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d169 = ContModelHIL_B.d16 * 0.028900000000000006 * 0.143 *
    ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d170 = ContModelHIL_B.D16_tmp_l * 8.085E-5 *
    ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.d171 = ContModelHIL_B.d130 * ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.d172 = -0.0191844872 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.143 *
    ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.d173 = ContModelHIL_B.d44 * 0.17 * 0.143 * ContModelHIL_B.D28;
  ContModelHIL_B.d174 = ContModelHIL_B.d42 * ContModelHIL_B.D67;
  ContModelHIL_B.d175 = ContModelHIL_B.d42 * ContModelHIL_B.rtb_ginv_tmp_j;
  ContModelHIL_B.d176 = 0.78352 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelHIL_B.d180 = ContModelHIL_B.d26 * ContModelHIL_B.D15_tmp_tmp;
  ContModelHIL_B.d181 = ContModelHIL_B.d26 * ContModelHIL_B.D15_tmp_tmp_a;
  ContModelHIL_B.d182 = ContModelHIL_B.d45 * ContModelHIL_B.D46_tmp_tmp_l;
  ContModelHIL_B.dv[43] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    ((((((((((((((((((((((((((((((((((((((((ContModelHIL_B.d161 +
    ContModelHIL_B.d90) + ContModelHIL_B.d92) + ContModelHIL_B.d93) +
    ContModelHIL_B.d94) + ContModelHIL_B.d30 * ContModelHIL_B.D46_tmp_tmp_f) +
    ContModelHIL_B.tmp_tmp * ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.d96)
    + ContModelHIL_B.d97) + ContModelHIL_B.d98) + ContModelHIL_B.d99) +
    ContModelHIL_B.d100) + ContModelHIL_B.d101) + ContModelHIL_B.d102) +
    ContModelHIL_B.d103) + ContModelHIL_B.d150) + ContModelHIL_B.d33 *
    ContModelHIL_B.D46_tmp_tmp_e) + ContModelHIL_B.d104) + ContModelHIL_B.d105)
    + ContModelHIL_B.d106) + ContModelHIL_B.d107) + ContModelHIL_B.d108) +
    ContModelHIL_B.d109) + ContModelHIL_B.d110) + ContModelHIL_B.d151) +
    ContModelHIL_B.d152) + ContModelHIL_B.d29 * 0.0393748 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.d153) + ContModelHIL_B.d34 * 0.142 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.d154) + ContModelHIL_B.d34 * 0.143 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.d155) + ContModelHIL_B.d35 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d36 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d37 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d28 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d30 *
    ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.tmp_tmp *
    ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.d41 *
    ContModelHIL_B.D46_tmp_p) + ContModelHIL_B.d162) + ContModelHIL_B.d30 *
    ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.tmp_tmp *
    ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.d38 *
    ContModelHIL_B.D56_tmp_j) + ContModelHIL_B.d39 * ContModelHIL_B.D56_tmp_j) +
    ContModelHIL_B.d40 * ContModelHIL_B.D56_tmp_j) + ContModelHIL_B.tmp_tmp_p *
    ContModelHIL_B.D56_tmp_j) + ContModelHIL_B.d156) + ContModelHIL_B.d33 *
    ContModelHIL_B.D46_tmp_tmp_ax) + ContModelHIL_B.d41 *
    ContModelHIL_B.D46_tmp_l) + ContModelHIL_B.d163) + ContModelHIL_B.d33 *
    ContModelHIL_B.D56_tmp_tmp_g) + ContModelHIL_B.d31 *
    ContModelHIL_B.D56_tmp_tmp_o) + ContModelHIL_B.tmp_tmp_b *
    ContModelHIL_B.D56_tmp_f) + ContModelHIL_B.tmp_tmp_c *
    ContModelHIL_B.D56_tmp_f) + ContModelHIL_B.tmp_tmp_n *
    ContModelHIL_B.D56_tmp_f) + ContModelHIL_B.d164) + ContModelHIL_B.d165) +
    ContModelHIL_B.d131 * ContModelHIL_B.D17) + ContModelHIL_B.D16_tmp_l *
    0.06214814 * ContModelHIL_B.D17) + ContModelHIL_B.d43 * 0.142 *
    ContModelHIL_B.D17) + ContModelHIL_B.d43 * 0.143 * ContModelHIL_B.D17) +
    ContModelHIL_B.d166) + ContModelHIL_B.d167) + ContModelHIL_B.d168) +
    ContModelHIL_B.d169) + -0.45856 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142 *
    ContModelHIL_B.D18) + ContModelHIL_B.tmp_tmp_i3 * 0.08312 * 0.17 * 0.143 *
    ContModelHIL_B.D18) + ContModelHIL_B.d170) + ContModelHIL_B.d171) +
    ContModelHIL_B.d172) + ContModelHIL_B.d44 * 0.08312 * 0.143 *
    ContModelHIL_B.D56_tmp_tmp_ol) + ContModelHIL_B.d173) + ContModelHIL_B.d112)
    + ContModelHIL_B.d174) + ContModelHIL_B.d113) + ContModelHIL_B.d114) +
    ContModelHIL_B.d175) + ContModelHIL_B.d115) + ContModelHIL_B.d116) +
    ContModelHIL_B.d117) + ContModelHIL_B.d118) - ContModelHIL_B.d119) -
    ContModelHIL_B.d120) - ContModelHIL_B.d121) + ContModelHIL_B.d123) +
    ContModelHIL_B.d124) + ContModelHIL_B.d125) - ContModelHIL_B.d126) -
    ContModelHIL_B.d127) + ContModelHIL_B.d128) + ContModelHIL_B.d176 * 0.143 *
    ContModelHIL_B.d51 * ContModelHIL_B.u) + 8.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.08312 *
    ContModelHIL_B.D14_tmp_m * ContModelHIL_B.u) + ContModelHIL_B.d136) +
    ContModelHIL_B.d137) + ContModelHIL_B.d138) - ContModelHIL_B.d139) +
    ContModelHIL_B.d140) - ContModelHIL_B.d141) - ContModelHIL_B.d142) +
                       ContModelHIL_B.d41 * ContModelHIL_B.D46_tmp_lx) +
                      ContModelHIL_B.d143) - ContModelHIL_B.d144) -
                    ContModelHIL_B.d145) +
                   -ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
                   0.028900000000000006 * 0.143 * ContModelHIL_B.y_a) +
                  ContModelHIL_B.d32 * ContModelHIL_B.D56_tmp_b) +
                 ContModelHIL_B.d41 * ContModelHIL_B.D46_tmp_nu) +
                ContModelHIL_B.d146) - ContModelHIL_B.d147) -
              ContModelHIL_B.d148) + ContModelHIL_B.d32 *
             ContModelHIL_B.D56_tmp_bs) + ContModelHIL_B.d180) +
           ContModelHIL_B.d181) + ContModelHIL_B.d48 *
          ContModelHIL_B.rtb_ginv_tmp_tmp_p) + ContModelHIL_B.d49 *
         ContModelHIL_B.rtb_ginv_tmp_tmp_p) + ContModelHIL_B.d50 *
        ContModelHIL_B.D56_tmp_tmp) + ContModelHIL_B.d182) * 0.125);
  ContModelHIL_B.d29 = -0.09794 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelHIL_B.d34 = ContModelHIL_B.D14_tmp_m * 0.08312;
  ContModelHIL_B.dv[51] = -(ContModelHIL_B.d29 * 0.143 * ContModelHIL_B.d51 -
    ContModelHIL_B.d34 * ContModelHIL_B.d17);
  ContModelHIL_B.dv[59] = -(ContModelHIL_B.d51 * -0.01400542 *
    ContModelHIL_B.d19);
  ContModelHIL_B.d52 = ContModelHIL_B.d52 * 0.08312 * 0.142;
  ContModelHIL_B.d43 = ContModelHIL_B.D16_tmp_l * 0.08312 * 0.17 * 0.143;
  ContModelHIL_B.d44 = ContModelHIL_B.d54 * 0.08312 * 0.143;
  ContModelHIL_B.d54 = ContModelHIL_B.d54 * 0.17 * 0.143;
  ContModelHIL_B.D14_tmp_m = ContModelHIL_B.D16_tmp_l * 0.0069089343999999995;
  ContModelHIL_B.d95 = -4.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelHIL_B.tmp_tmp_nc = ContModelHIL_B.d95 * 0.0;
  ContModelHIL_B.tmp_tmp_ph = ContModelHIL_B.D16_tmp * 0.0;
  ContModelHIL_B.tmp_tmp_dk = ContModelHIL_B.d41 * ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.tmp_tmp_h = 4.0 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelHIL_B.d122 = ContModelHIL_B.tmp_tmp_h * 0.0;
  ContModelHIL_B.d157 = 4.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7];
  ContModelHIL_B.d158 = 4.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6];
  ContModelHIL_B.d12 = ((((ContModelHIL_B.d12 * 4.0 * 0.0 *
    ContModelHIL_B.D15_tmp_f + ContModelHIL_B.d41 * ContModelHIL_B.D24_tmp) +
    ContModelHIL_B.d122 * ContModelHIL_B.D15_tmp_g) + ContModelHIL_B.d158 * 0.0 *
    ContModelHIL_B.D15_tmp_g) + ContModelHIL_B.d157 * 0.0 *
                        ContModelHIL_B.D15_tmp_g) + ContModelHIL_B.tmp_tmp_dk;
  ContModelHIL_B.tmp_tmp_oi = ContModelHIL_B.d26 * ContModelHIL_B.D46_tmp_m;
  ContModelHIL_B.tmp_tmp_jr = ContModelHIL_B.tmp_tmp_d *
    ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.tmp_tmp_c2 = ContModelHIL_B.tmp_tmp_ik *
    ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.tmp_tmp_hp = ContModelHIL_B.tmp_tmp_g *
    ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.tmp_tmp_c5 = ContModelHIL_B.d53 * ContModelHIL_B.D56_tmp_e;
  ContModelHIL_B.tmp_tmp_i = ContModelHIL_B.d54 * ContModelHIL_B.D46_tmp_tmp_h;
  ContModelHIL_B.tmp_tmp_m = ContModelHIL_B.d26 * ContModelHIL_B.D46_tmp_n;
  ContModelHIL_B.tmp_tmp_o = ContModelHIL_B.d54 * ContModelHIL_B.D56_tmp_tmp_ff;
  ContModelHIL_B.tmp_tmp_ch = ContModelHIL_B.tmp_tmp_nn *
    ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.tmp_tmp_bd = ContModelHIL_B.tmp_tmp_l *
    ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.tmp_tmp_da = ContModelHIL_B.tmp_tmp_ce *
    ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.tmp_tmp_j = ContModelHIL_B.D16_tmp_l * 0.00046501 *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.tmp_tmp_e = ContModelHIL_B.D16_tmp_l * 0.0003034 *
    ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d132 = 0.0262846592 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.142;
  ContModelHIL_B.tmp_tmp_mv = ContModelHIL_B.d132 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d134 = 0.0191844872 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.143;
  ContModelHIL_B.tmp_tmp_m0 = ContModelHIL_B.d134 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.d135 = ContModelHIL_B.D16_tmp_l * 0.028900000000000006 * 0.143;
  ContModelHIL_B.tmp_tmp_jg = ContModelHIL_B.d135 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.tmp_tmp_f = ContModelHIL_B.d42 * ContModelHIL_B.D46_tmp_p;
  ContModelHIL_B.tmp_tmp_d *= ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_ik *= ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_g *= ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_a = ContModelHIL_B.d53 * ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_nr = ContModelHIL_B.d54 * ContModelHIL_B.D46_tmp_tmp_c;
  ContModelHIL_B.d69 = ContModelHIL_B.d42 * ContModelHIL_B.D46_tmp_l;
  ContModelHIL_B.d70 = ContModelHIL_B.d54 * ContModelHIL_B.D56_tmp_tmp_o;
  ContModelHIL_B.tmp_tmp_nn *= ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.tmp_tmp_l *= ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.tmp_tmp_ce *= ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.d71 = ContModelHIL_B.tmp_tmp_nc * ContModelHIL_B.D17_tmp_j;
  ContModelHIL_B.d72 = ContModelHIL_B.tmp_tmp_ph * ContModelHIL_B.D17_tmp_j;
  ContModelHIL_B.d38 *= ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d39 *= ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d40 *= ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.tmp_tmp_p *= ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.tmp_tmp_nc *= ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.tmp_tmp_ph *= ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.d73 = ContModelHIL_B.D28_tmp * 0.0 * ContModelHIL_B.D17_tmp_p;
  ContModelHIL_B.tmp_tmp_b *= ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.tmp_tmp_c *= ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.tmp_tmp_n *= ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.d31 *= ContModelHIL_B.D28;
  ContModelHIL_B.d75 = ContModelHIL_B.d26 * ContModelHIL_B.D46_tmp_j;
  ContModelHIL_B.d76 = ContModelHIL_B.d26 * ContModelHIL_B.D56_tmp_g;
  ContModelHIL_B.d77 = ContModelHIL_B.d26 * ContModelHIL_B.D46_tmp_ld;
  ContModelHIL_B.d78 = ContModelHIL_B.d26 * ContModelHIL_B.D56_tmp_dh;
  ContModelHIL_B.d79 = ContModelHIL_B.d42 * ContModelHIL_B.D46_tmp_lx;
  ContModelHIL_B.d80 = ContModelHIL_B.d26 * ContModelHIL_B.D56_tmp_b;
  ContModelHIL_B.d81 = ContModelHIL_B.d42 * ContModelHIL_B.D46_tmp_nu;
  ContModelHIL_B.d82 = ContModelHIL_B.d26 * ContModelHIL_B.D56_tmp_bs;
  ContModelHIL_B.d133 = ContModelHIL_B.D14_tmp_m * 0.142;
  ContModelHIL_B.D14_tmp_m *= 0.143;
  ContModelHIL_B.dv[28] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((ContModelHIL_B.d47 * ContModelHIL_B.D56_tmp_tmp_e + ContModelHIL_B.d12) -
    ContModelHIL_B.tmp_tmp_nm * ContModelHIL_B.D56_tmp_tmp_e) +
    ContModelHIL_B.tmp_tmp_er * ContModelHIL_B.D56_tmp_tmp_e) +
    ContModelHIL_B.d46 * ContModelHIL_B.D56_tmp_tmp_e) + ContModelHIL_B.d52 *
    ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.d43 *
    ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.tmp_tmp_oi) +
    ContModelHIL_B.d52 * ContModelHIL_B.D27) + ContModelHIL_B.d43 *
    ContModelHIL_B.D27) - ContModelHIL_B.tmp_tmp_jr) + ContModelHIL_B.tmp_tmp_c2)
    + ContModelHIL_B.tmp_tmp_hp) + ContModelHIL_B.tmp_tmp_c5) +
    ContModelHIL_B.tmp_tmp_i) + ContModelHIL_B.d44 *
    ContModelHIL_B.D46_tmp_tmp_e) + ContModelHIL_B.tmp_tmp_m) +
    ContModelHIL_B.d44 * ContModelHIL_B.D56_tmp_tmp_f) +
    ContModelHIL_B.tmp_tmp_o) - ContModelHIL_B.tmp_tmp_ch) +
    ContModelHIL_B.tmp_tmp_bd) + ContModelHIL_B.tmp_tmp_da) +
    ContModelHIL_B.tmp_tmp_j) + ContModelHIL_B.tmp_tmp_e) +
    ContModelHIL_B.D16_tmp_l * 0.0393748 * ContModelHIL_B.D15_tmp) +
    ContModelHIL_B.tmp_tmp_mv) + ContModelHIL_B.d133 * ContModelHIL_B.D15_tmp) +
    ContModelHIL_B.tmp_tmp_m0) + ContModelHIL_B.D14_tmp_m *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.tmp_tmp_jg) + ContModelHIL_B.d47 *
    ContModelHIL_B.D56_tmp_tmp_b) - ContModelHIL_B.tmp_tmp_nm *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.tmp_tmp_er *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d46 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d52 *
    ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.d43 *
    ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.tmp_tmp_f) +
    ContModelHIL_B.d52 * ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.d43 *
    ContModelHIL_B.D56_tmp_tmp_g2) - ContModelHIL_B.tmp_tmp_d) +
    ContModelHIL_B.tmp_tmp_ik) + ContModelHIL_B.tmp_tmp_g) +
    ContModelHIL_B.tmp_tmp_a) + ContModelHIL_B.tmp_tmp_nr) + ContModelHIL_B.d44 *
    ContModelHIL_B.D46_tmp_tmp_ax) + ContModelHIL_B.d69) + ContModelHIL_B.d44 *
    ContModelHIL_B.D56_tmp_tmp_g) + ContModelHIL_B.d70) -
    ContModelHIL_B.tmp_tmp_nn) + ContModelHIL_B.tmp_tmp_l) +
    ContModelHIL_B.tmp_tmp_ce) + ContModelHIL_B.d35 * ContModelHIL_B.D17) +
    ContModelHIL_B.d36 * ContModelHIL_B.D17) + ContModelHIL_B.d37 *
    ContModelHIL_B.D17) + ContModelHIL_B.d28 * ContModelHIL_B.D17) +
    ContModelHIL_B.d71) + ContModelHIL_B.d72) + ContModelHIL_B.d38) +
    ContModelHIL_B.d39) + ContModelHIL_B.d40) + ContModelHIL_B.tmp_tmp_p) +
                        ContModelHIL_B.d30 * ContModelHIL_B.D18) +
                       ContModelHIL_B.tmp_tmp * ContModelHIL_B.D18) +
                      ContModelHIL_B.tmp_tmp_nc) + ContModelHIL_B.tmp_tmp_ph) +
                    ContModelHIL_B.d73) + ContModelHIL_B.tmp_tmp_b) +
                  ContModelHIL_B.tmp_tmp_c) + ContModelHIL_B.tmp_tmp_n) +
                ContModelHIL_B.d33 * ContModelHIL_B.D56_tmp_tmp_ol) +
               ContModelHIL_B.d31) + ContModelHIL_B.d75) + ContModelHIL_B.d76) +
            ContModelHIL_B.d77) + ContModelHIL_B.d78) + ContModelHIL_B.d79) +
         ContModelHIL_B.d80) + ContModelHIL_B.d81) + ContModelHIL_B.d82) * 0.25);
  ContModelHIL_B.d28 = 0.0 * ContModelHIL_B.D24_tmp + 0.0 *
    ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.d30 = -0.004761842800000001 * ContModelHIL_B.D28;
  ContModelHIL_B.tmp_tmp = 2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [7];
  ContModelHIL_B.d33 = 0.0013531005056 * ContModelHIL_B.u_i;
  ContModelHIL_B.d35 = 0.0020206472 * ContModelHIL_B.D18;
  ContModelHIL_B.d36 = 0.0011641305103999998 * ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.d37 = 0.0011641305103999998 * ContModelHIL_B.D56_tmp_tmp_ol;
  ContModelHIL_B.d46 = (0.0011641305103999998 * ContModelHIL_B.D14_tmp +
                        0.0023809214000000004 * ContModelHIL_B.D15_tmp_f) +
    0.0016404808348 * ContModelHIL_B.D15_tmp_g;
  ContModelHIL_B.dv[36] = -((((((((((((((((((ContModelHIL_B.d28 -
    ContModelHIL_B.D14_tmp_d) + ContModelHIL_B.D14_tmp_a) - ContModelHIL_B.d10)
    - ContModelHIL_B.d11) + ContModelHIL_B.D16_tmp_n) - ContModelHIL_B.d13) -
    ContModelHIL_B.d15) - ContModelHIL_B.D16_tmp_pt) + -0.0027062010112 *
    ContModelHIL_B.D18) + -0.0040412944 * ContModelHIL_B.D18) +
    ContModelHIL_B.d22) - ContModelHIL_B.D14_tmp_o) - ContModelHIL_B.D14_tmp_o3)
    + -0.0023282610207999996 * ContModelHIL_B.D56_tmp_tmp_ol) +
    ContModelHIL_B.d30) * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] +
    (-2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7] *
     ContModelHIL_B.d46 * ContModelHIL_B.D17_tmp_p + ContModelHIL_B.tmp_tmp *
     0.0 * ContModelHIL_B.D46_tmp_b)) + ((((((((((((((ContModelHIL_B.d28 -
    ContModelHIL_B.d33) + -0.0020206472 * ContModelHIL_B.u_i) +
    ContModelHIL_B.D16_tmp_n) - ContModelHIL_B.d13) - ContModelHIL_B.d15) -
    ContModelHIL_B.D16_tmp_pt) + -0.0013531005056 * ContModelHIL_B.D18) -
    ContModelHIL_B.d35) - ContModelHIL_B.d36) + ContModelHIL_B.d22) -
    ContModelHIL_B.D14_tmp_o) - ContModelHIL_B.D14_tmp_o3) - ContModelHIL_B.d37)
    + ContModelHIL_B.d30) * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6]) *
    0.5);
  ContModelHIL_B.D14_tmp_d = 0.0011641305103999998 *
    ContModelHIL_B.D46_tmp_tmp_e;
  ContModelHIL_B.D14_tmp_a = 0.0011641305103999998 *
    ContModelHIL_B.D56_tmp_tmp_f;
  ContModelHIL_B.d10 = 0.0011641305103999998 * ContModelHIL_B.D46_tmp_tmp_ax;
  ContModelHIL_B.d11 = 0.0011641305103999998 * ContModelHIL_B.D56_tmp_tmp_g;
  ContModelHIL_B.d28 = 0.0033737477055999993 * ContModelHIL_B.D46_tmp_tmp_f +
    ContModelHIL_B.D27_tmp;
  ContModelHIL_B.d30 = 0.0013531005056 * ContModelHIL_B.D46_tmp_tmp_a;
  ContModelHIL_B.d47 = 0.0020206472 * ContModelHIL_B.D46_tmp_tmp_a;
  ContModelHIL_B.tmp_tmp_nm = (0.0023809214000000004 *
    ContModelHIL_B.D46_tmp_tmp_h + ContModelHIL_B.D14_tmp_d) +
    ContModelHIL_B.D46_tmp_tmp_m;
  ContModelHIL_B.tmp_tmp_er = 0.0023809214000000004 *
    ContModelHIL_B.D46_tmp_tmp_c;
  ContModelHIL_B.d177 = (0.0013531005056 * ContModelHIL_B.D27 +
    ContModelHIL_B.d28) + 0.0020206472 * ContModelHIL_B.D27;
  ContModelHIL_B.d178 = 0.0013531005056 * ContModelHIL_B.D56_tmp_tmp_g2;
  ContModelHIL_B.d179 = 0.0020206472 * ContModelHIL_B.D56_tmp_tmp_g2;
  ContModelHIL_B.D27_tmp_i =
    (((((((((((((((((((((((((((((((((((((((((ContModelHIL_B.d177 -
    ContModelHIL_B.D27_tmp_i) + ContModelHIL_B.D14_tmp_k) + ContModelHIL_B.d21)
    + ContModelHIL_B.d23) + ContModelHIL_B.d24) + ContModelHIL_B.D14_tmp_d) +
    ContModelHIL_B.D46_tmp_tmp_m) + ContModelHIL_B.D14_tmp_a) +
    ContModelHIL_B.D14_tmp_cv) - ContModelHIL_B.D14_tmp_n) +
    ContModelHIL_B.D14_tmp_tmp_i) + ContModelHIL_B.D14_tmp_tmp_o) +
    ContModelHIL_B.D14_tmp_cz) + ContModelHIL_B.D15_tmp_tmp_o) +
    ContModelHIL_B.D15_tmp_tmp_k) + ContModelHIL_B.D16_tmp_tmp) +
    ContModelHIL_B.D34_tmp_m) + ContModelHIL_B.d30) + ContModelHIL_B.d47) +
    ContModelHIL_B.D37_tmp) + ContModelHIL_B.d178) + ContModelHIL_B.d179) -
                       ContModelHIL_B.rtb_ginv_tmp_e) + ContModelHIL_B.d56) +
                     ContModelHIL_B.d57) + ContModelHIL_B.d58) +
                   ContModelHIL_B.d59) + ContModelHIL_B.d10) +
                 ContModelHIL_B.d60) + ContModelHIL_B.d11) + ContModelHIL_B.d61)
              - ContModelHIL_B.d62) + ContModelHIL_B.d63) + ContModelHIL_B.d64)
           + ContModelHIL_B.D46_tmp_mv) + ContModelHIL_B.d65) +
         ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.d66) +
       ContModelHIL_B.D56_tmp_c) + ContModelHIL_B.d67) +
     ContModelHIL_B.D56_tmp_fb) + ContModelHIL_B.d68;
  ContModelHIL_B.d183 = ((((((((((((((((((ContModelHIL_B.tmp_tmp_nm +
    ContModelHIL_B.D14_tmp_a) + 0.0023809214000000004 *
    ContModelHIL_B.D56_tmp_tmp_ff) - ContModelHIL_B.D14_tmp_n) +
    ContModelHIL_B.D14_tmp_tmp_i) + ContModelHIL_B.D14_tmp_tmp_o) +
    ContModelHIL_B.D15_tmp_tmp_o) + ContModelHIL_B.D16_tmp_tmp) +
    ContModelHIL_B.tmp_tmp_er) + ContModelHIL_B.d10) + ContModelHIL_B.d60) +
    ContModelHIL_B.d11) + 0.0023809214000000004 * ContModelHIL_B.D56_tmp_tmp_o)
    - ContModelHIL_B.d62) + ContModelHIL_B.d63) + ContModelHIL_B.d64) +
    ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.d66) + ContModelHIL_B.D56_tmp_fb)
    + ContModelHIL_B.d68;
  ContModelHIL_B.dv[44] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((0.0 *
    ContModelHIL_B.D68 + 0.0 * ContModelHIL_B.d) + 0.0 * ContModelHIL_B.d1) +
    0.0 * ContModelHIL_B.D46_tmp_tmp_i) + -0.0 * ContModelHIL_B.d2) + -0.0 *
    ContModelHIL_B.D46_tmp_tmp_o) + 0.0 * ContModelHIL_B.d3) + 0.0 *
    ContModelHIL_B.d4) + -0.004761842800000001 * ContModelHIL_B.D46_tmp_tmp) +
    -0.0027062010112 * ContModelHIL_B.d5) + -0.0040412944 * ContModelHIL_B.d5) +
    -0.0 * ContModelHIL_B.D67) + -0.0027062010112 * ContModelHIL_B.D56_tmp_tmp_i)
    + -0.0040412944 * ContModelHIL_B.D56_tmp_tmp_i) + -0.004761842800000001 *
    ContModelHIL_B.d8) + -0.0023282610207999996 * ContModelHIL_B.D37) + -0.0 *
    ContModelHIL_B.rtb_ginv_tmp_j) + -0.0023282610207999996 *
    ContModelHIL_B.D56_tmp_tmp_iz) + 0.06214814 * ContModelHIL_B.d6) + 5.484E-5 *
    ContModelHIL_B.D38) - 0.00050874 * ContModelHIL_B.D38) -
    0.0018662108031999999 * ContModelHIL_B.D38) - 0.0041327000000000004 *
    ContModelHIL_B.D38) + 8.085E-5 * ContModelHIL_B.D47) - 0.00034964 *
    ContModelHIL_B.D47) + -0.0013716908347999998 * ContModelHIL_B.D47) +
    -0.00010968 * ContModelHIL_B.D46_tmp) + -0.00101748 * ContModelHIL_B.D46_tmp)
    + 0.00186004 * ContModelHIL_B.D46_tmp) + -0.0001617 * ContModelHIL_B.D46_tmp)
    + -0.00069928 * ContModelHIL_B.D46_tmp) + 0.0012136 * ContModelHIL_B.D46_tmp)
    + 0.1574992 * ContModelHIL_B.D46_tmp) + -0.0808631 * ContModelHIL_B.D46_tmp)
    + -0.12429628 * ContModelHIL_B.D46_tmp) + 0.0037324216063999997 *
    ContModelHIL_B.D46_tmp) + 0.0019621373695999996 * ContModelHIL_B.D46_tmp) +
    0.0027433816695999996 * ContModelHIL_B.D46_tmp) + 0.0019759552383999996 *
    ContModelHIL_B.D46_tmp) + 0.008265400000000001 * ContModelHIL_B.D46_tmp) +
    0.04043155 * ContModelHIL_B.D48_tmp) + 0.0009810686847999998 *
    ContModelHIL_B.D48_tmp) + 0.0009879776191999998 * ContModelHIL_B.D48_tmp) +
    0.04043155 * ContModelHIL_B.D58) - 0.06214814 * ContModelHIL_B.D58) +
    0.0009810686847999998 * ContModelHIL_B.D58) + 0.0009879776191999998 *
    ContModelHIL_B.D58) - 5.484E-5 * ContModelHIL_B.y_a) + 0.00050874 *
                       ContModelHIL_B.y_a) + 0.0018662108031999999 *
                      ContModelHIL_B.y_a) + 0.0041327000000000004 *
                     ContModelHIL_B.y_a) - 8.085E-5 * ContModelHIL_B.ab_a) +
                   0.00034964 * ContModelHIL_B.ab_a) + 0.0013716908347999998 *
                  ContModelHIL_B.ab_a) + 0.0027062010112 * ContModelHIL_B.d7) +
                0.0040412944 * ContModelHIL_B.d7) + -0.0 *
               ContModelHIL_B.D15_tmp_tmp) + 0.004761842800000001 *
              ContModelHIL_B.d9) + 0.0023282610207999996 *
             ContModelHIL_B.D14_tmp_tmp) + -0.0 * ContModelHIL_B.D15_tmp_tmp_a)
           + 0.0027062010112 * ContModelHIL_B.rtb_ginv_tmp_tmp_p) + 0.0040412944
          * ContModelHIL_B.rtb_ginv_tmp_tmp_p) + 0.0023282610207999996 *
         ContModelHIL_B.D56_tmp_tmp) + 0.004761842800000001 *
        ContModelHIL_B.D46_tmp_tmp_l) * (-0.5 *
        ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) +
       ((ContModelHIL_B.D27_tmp_i *
         ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] + ContModelHIL_B.d183
         * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7]) +
        ContModelHIL_B.d55 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3]))
      * 0.25);
  ContModelHIL_B.D38 = 0.11464 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5] * 0.08312 * 0.142;
  ContModelHIL_B.D48_tmp = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] *
    0.08312 * 0.17 * 0.143;
  ContModelHIL_B.D58 = 0.09794 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5];
  ContModelHIL_B.ab_a = ContModelHIL_B.D58 * 0.08312 * 0.143;
  ContModelHIL_B.d6 = -0.22928 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [4] * 0.08312 * 0.142;
  ContModelHIL_B.d55 = ContModelHIL_B.d27 * 0.08312 * 0.17 * 0.143;
  ContModelHIL_B.d87 = -0.19588 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.d74 = ContModelHIL_B.d87 * 0.08312 * 0.143;
  ContModelHIL_B.d83 = ContModelHIL_B.ab_a * ContModelHIL_B.D46_tmp_tmp_e;
  ContModelHIL_B.d84 = ContModelHIL_B.ab_a * ContModelHIL_B.D56_tmp_tmp_f;
  ContModelHIL_B.d85 = ContModelHIL_B.ab_a * ContModelHIL_B.D46_tmp_tmp_ax;
  ContModelHIL_B.d86 = ContModelHIL_B.ab_a * ContModelHIL_B.D56_tmp_tmp_g;
  ContModelHIL_B.d88 = ContModelHIL_B.d74 * ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.d89 = ContModelHIL_B.d74 * ContModelHIL_B.D56_tmp_tmp_ol;
  ContModelHIL_B.dv[52] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((ContModelHIL_B.D38
    * ContModelHIL_B.D46_tmp_tmp_f + ContModelHIL_B.d12) +
    ContModelHIL_B.D48_tmp * ContModelHIL_B.D46_tmp_tmp_f) +
    ContModelHIL_B.tmp_tmp_oi) + ContModelHIL_B.D38 * ContModelHIL_B.D27) +
    ContModelHIL_B.D48_tmp * ContModelHIL_B.D27) - ContModelHIL_B.tmp_tmp_jr) +
    ContModelHIL_B.tmp_tmp_c2) + ContModelHIL_B.tmp_tmp_hp) +
    ContModelHIL_B.tmp_tmp_c5) + ContModelHIL_B.tmp_tmp_i) + ContModelHIL_B.d83)
    + ContModelHIL_B.tmp_tmp_m) + ContModelHIL_B.d84) + ContModelHIL_B.tmp_tmp_o)
    - ContModelHIL_B.tmp_tmp_ch) + ContModelHIL_B.tmp_tmp_bd) +
    ContModelHIL_B.tmp_tmp_da) + ContModelHIL_B.tmp_tmp_j) +
    ContModelHIL_B.tmp_tmp_e) + ContModelHIL_B.tmp_tmp_mv) +
    ContModelHIL_B.tmp_tmp_m0) + ContModelHIL_B.tmp_tmp_jg) + ContModelHIL_B.D38
    * ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.D48_tmp *
    ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.tmp_tmp_f) +
    ContModelHIL_B.D38 * ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.D48_tmp
    * ContModelHIL_B.D56_tmp_tmp_g2) - ContModelHIL_B.tmp_tmp_d) +
    ContModelHIL_B.tmp_tmp_ik) + ContModelHIL_B.tmp_tmp_g) +
    ContModelHIL_B.tmp_tmp_a) + ContModelHIL_B.tmp_tmp_nr) + ContModelHIL_B.d85)
    + ContModelHIL_B.d69) + ContModelHIL_B.d86) + ContModelHIL_B.d70) -
    ContModelHIL_B.tmp_tmp_nn) + ContModelHIL_B.tmp_tmp_l) +
    ContModelHIL_B.tmp_tmp_ce) + ContModelHIL_B.d6 * ContModelHIL_B.u_i) +
    ContModelHIL_B.d55 * ContModelHIL_B.u_i) + ContModelHIL_B.d71) +
    ContModelHIL_B.d72) + ContModelHIL_B.d38) + ContModelHIL_B.d39) +
    ContModelHIL_B.d40) + ContModelHIL_B.tmp_tmp_p) + ContModelHIL_B.d6 *
    ContModelHIL_B.D18) + ContModelHIL_B.d55 * ContModelHIL_B.D18) +
                       ContModelHIL_B.d88) + ContModelHIL_B.tmp_tmp_nc) +
                     ContModelHIL_B.tmp_tmp_ph) + ContModelHIL_B.d73) +
                   ContModelHIL_B.tmp_tmp_b) + ContModelHIL_B.tmp_tmp_c) +
                 ContModelHIL_B.tmp_tmp_n) + ContModelHIL_B.d89) +
               ContModelHIL_B.d31) + ContModelHIL_B.d75) + ContModelHIL_B.d76) +
            ContModelHIL_B.d77) + ContModelHIL_B.d78) + ContModelHIL_B.d79) +
         ContModelHIL_B.d80) + ContModelHIL_B.d81) + ContModelHIL_B.d82) * 0.25);
  ContModelHIL_B.D58 = ContModelHIL_B.D58 * 0.17 * 0.143;
  ContModelHIL_B.d12 = ContModelHIL_B.d87 * 0.17 * 0.143;
  ContModelHIL_B.dv[60] = -((((((((((((((((((((((((((((((((((ContModelHIL_B.d18 *
    4.0 * 0.0 * ContModelHIL_B.D15_tmp_g + ContModelHIL_B.tmp_tmp_dk) +
    ContModelHIL_B.D58 * ContModelHIL_B.D46_tmp_tmp_h) + ContModelHIL_B.d83) +
    ContModelHIL_B.tmp_tmp_m) + ContModelHIL_B.d84) + ContModelHIL_B.D58 *
    ContModelHIL_B.D56_tmp_tmp_ff) - ContModelHIL_B.tmp_tmp_ch) +
    ContModelHIL_B.tmp_tmp_bd) + ContModelHIL_B.tmp_tmp_da) +
    ContModelHIL_B.tmp_tmp_e) + ContModelHIL_B.tmp_tmp_m0) + ContModelHIL_B.D58 *
    ContModelHIL_B.D46_tmp_tmp_c) + ContModelHIL_B.d85) + ContModelHIL_B.d69) +
    ContModelHIL_B.d86) + ContModelHIL_B.D58 * ContModelHIL_B.D56_tmp_tmp_o) -
    ContModelHIL_B.tmp_tmp_nn) + ContModelHIL_B.tmp_tmp_l) +
    ContModelHIL_B.tmp_tmp_ce) + ContModelHIL_B.d12 * ContModelHIL_B.D14_tmp_c)
    + ContModelHIL_B.d88) + ContModelHIL_B.tmp_tmp_nc) +
    ContModelHIL_B.tmp_tmp_ph) + ContModelHIL_B.d73) + ContModelHIL_B.tmp_tmp_b)
    + ContModelHIL_B.tmp_tmp_c) + ContModelHIL_B.tmp_tmp_n) + ContModelHIL_B.d89)
    + ContModelHIL_B.d12 * ContModelHIL_B.D28) + ContModelHIL_B.d77) +
    ContModelHIL_B.d78) + ContModelHIL_B.d81) + ContModelHIL_B.d82) * 0.25);
  ContModelHIL_B.d18 = -0.0 * ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.d31 = -0.004761842800000001 * ContModelHIL_B.D46_tmp_e;
  ContModelHIL_B.d38 = -0.0 * ContModelHIL_B.D46_tmp_g;
  ContModelHIL_B.d39 = 8.085E-5 * ContModelHIL_B.D56_tmp_bs;
  ContModelHIL_B.d40 = ContModelHIL_B.tmp_tmp_nm - ContModelHIL_B.tmp_tmp_er;
  ContModelHIL_B.d28 = ((((((((((ContModelHIL_B.d28 + ContModelHIL_B.D14_tmp_d)
    + ContModelHIL_B.D46_tmp_tmp_m) - ContModelHIL_B.d30) - ContModelHIL_B.d47)
    + ContModelHIL_B.D46_tmp_o) - ContModelHIL_B.d10) +
    ContModelHIL_B.D46_tmp_lm) + ContModelHIL_B.D46_tmp_mv) +
    ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.D46_tmp_mc) +
    ContModelHIL_B.D46_tmp_cs;
  ContModelHIL_B.dv[29] = -(((((((((((((((((((((0.049482857942000004 -
    -0.019747543696 * ContModelHIL_B.rtb_ginv_tmp) +
    ContModelHIL_B.rtb_ginv_tmp_p) + 5.484E-5 * ContModelHIL_B.D24_tmp) -
    ContModelHIL_B.rtb_ginv_tmp_m) - ContModelHIL_B.rtb_ginv_tmp_ad) -
    ContModelHIL_B.rtb_ginv_tmp_k) + -0.0027062010112 * ContModelHIL_B.D24_tmp_p)
    + -0.0040412944 * ContModelHIL_B.D24_tmp_p) + ContModelHIL_B.D47_tmp_p) +
    ContModelHIL_B.rtb_ginv_tmp_ap) + ContModelHIL_B.D15) - ContModelHIL_B.D25)
    - ContModelHIL_B.D14) + -0.0023282610207999996 *
    ContModelHIL_B.rtb_ginv_tmp_a) + ContModelHIL_B.d31) + ContModelHIL_B.d38) +
    ContModelHIL_B.d18) * ContModelHIL_B.d27 + ContModelHIL_B.D45 *
    ContModelHIL_B.tmp_tmp_h) + (((ContModelHIL_B.D56_tmp - ContModelHIL_B.d39)
    + ContModelHIL_B.D46_tmp_c) + ContModelHIL_B.D56_tmp_h) *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) * ContModelHIL_B.D15_tmp
    + (((((-0.0011641305103999998 * ContModelHIL_B.D46_tmp_tmp_ax +
           ContModelHIL_B.d40) + ContModelHIL_B.D46_tmp_lm) +
         ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.D46_tmp_cs) *
       ContModelHIL_B.tmp_tmp + ContModelHIL_B.d28 * ContModelHIL_B.d20)) * 0.25);
  ContModelHIL_B.tmp_tmp = 2.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [3];
  ContModelHIL_B.tmp_tmp_p = ContModelHIL_B.tmp_tmp * 0.0069089343999999995;
  ContModelHIL_B.D15_tmp_g = -0.39176 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3];
  ContModelHIL_B.D45 = 0.39176 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [3];
  ContModelHIL_B.tmp_tmp_b = ContModelHIL_B.d95 * 0.0069089343999999995;
  ContModelHIL_B.tmp_tmp_c = ContModelHIL_B.tmp_tmp * 0.04043155;
  ContModelHIL_B.tmp_tmp_n = ContModelHIL_B.d91 * 0.06214814;
  ContModelHIL_B.tmp_tmp_i = ContModelHIL_B.tmp_tmp_p * 0.142;
  ContModelHIL_B.tmp_tmp_p *= 0.143;
  ContModelHIL_B.tmp_tmp_m = ContModelHIL_B.d14 * 0.0069089343999999995;
  ContModelHIL_B.D46_tmp_o = -0.45856 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.08312 * 0.142;
  ContModelHIL_B.D56_tmp = ContModelHIL_B.d95 * 0.08312 * 0.17 * 0.143;
  ContModelHIL_B.rtb_ginv_tmp = 0.45856 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.08312 * 0.142;
  ContModelHIL_B.rtb_ginv_tmp_p = ContModelHIL_B.tmp_tmp_h * 0.08312 * 0.17 *
    0.143;
  ContModelHIL_B.tmp_tmp_j = ContModelHIL_B.d91 * 5.484E-5;
  ContModelHIL_B.tmp_tmp_e = ContModelHIL_B.tmp_tmp * 0.00050874;
  ContModelHIL_B.tmp_tmp_mv = 0.0262846592 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.142;
  ContModelHIL_B.tmp_tmp_m0 = ContModelHIL_B.tmp_tmp * 0.028900000000000006 *
    0.143;
  ContModelHIL_B.rtb_ginv_tmp_ap = ContModelHIL_B.D15_tmp_g * 0.17 * 0.143;
  ContModelHIL_B.D15_tmp_g = ContModelHIL_B.D15_tmp_g * 0.08312 * 0.143;
  ContModelHIL_B.rtb_ginv_tmp_m = ContModelHIL_B.D45 * 0.08312 * 0.143;
  ContModelHIL_B.D45 = ContModelHIL_B.D45 * 0.17 * 0.143;
  ContModelHIL_B.tmp_tmp_jg = 0.39176 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.tmp_tmp_f = ContModelHIL_B.d91 * 8.085E-5;
  ContModelHIL_B.tmp_tmp *= 0.00034964;
  ContModelHIL_B.tmp_tmp_a = 0.0191844872 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143;
  ContModelHIL_B.tmp_tmp_nr = 0.0011641305103999998 *
    ContModelHIL_B.rtb_ginv_tmp_a;
  ContModelHIL_B.rtb_ginv_tmp_a = ContModelHIL_B.tmp_tmp_i3 * 0.0;
  ContModelHIL_B.rtb_ginv_tmp_ad = ContModelHIL_B.d27 * 5.484E-5;
  ContModelHIL_B.rtb_ginv_tmp_k = ContModelHIL_B.d14 * 0.00050874;
  ContModelHIL_B.tmp_tmp_i3 = 0.0262846592 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.142;
  ContModelHIL_B.tmp_tmp_h = ContModelHIL_B.d14 * 0.028900000000000006 * 0.143;
  ContModelHIL_B.tmp_tmp_nm = ContModelHIL_B.tmp_tmp_jg * 0.17 * 0.143;
  ContModelHIL_B.tmp_tmp_o = ContModelHIL_B.d27 * 8.085E-5;
  ContModelHIL_B.tmp_tmp_ch = ContModelHIL_B.d14 * 0.00034964;
  ContModelHIL_B.tmp_tmp_bd = 0.0191844872 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.143;
  ContModelHIL_B.tmp_tmp_er = ContModelHIL_B.D46_tmp_o *
    ContModelHIL_B.D46_tmp_tmp_a;
  ContModelHIL_B.tmp_tmp_d = ContModelHIL_B.D56_tmp *
    ContModelHIL_B.D46_tmp_tmp_a;
  ContModelHIL_B.tmp_tmp_ik = ContModelHIL_B.d42 * ContModelHIL_B.d2;
  ContModelHIL_B.tmp_tmp_g = ContModelHIL_B.rtb_ginv_tmp_ad *
    ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_nn = ContModelHIL_B.rtb_ginv_tmp_k *
    ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_l = ContModelHIL_B.tmp_tmp_i3 *
    ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_ce = ContModelHIL_B.tmp_tmp_h *
    ContModelHIL_B.D56_tmp_j;
  ContModelHIL_B.tmp_tmp_nc = ContModelHIL_B.D15_tmp_g *
    ContModelHIL_B.D46_tmp_tmp_ax;
  ContModelHIL_B.tmp_tmp_ph = ContModelHIL_B.d42 * ContModelHIL_B.D46_tmp_tmp_o;
  ContModelHIL_B.tmp_tmp_dk = ContModelHIL_B.tmp_tmp_nm *
    ContModelHIL_B.D56_tmp_tmp_o;
  ContModelHIL_B.tmp_tmp_oi = ContModelHIL_B.tmp_tmp_o *
    ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.tmp_tmp_jr = ContModelHIL_B.tmp_tmp_ch *
    ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.tmp_tmp_c2 = ContModelHIL_B.tmp_tmp_bd *
    ContModelHIL_B.D56_tmp_f;
  ContModelHIL_B.tmp_tmp_hp = ContModelHIL_B.d16 * 5.484E-5;
  ContModelHIL_B.tmp_tmp_da = ContModelHIL_B.d16 * 8.085E-5;
  ContModelHIL_B.tmp_tmp_c5 = ContModelHIL_B.rtb_ginv_tmp_ap *
    ContModelHIL_B.D46_tmp_tmp_c;
  ContModelHIL_B.D46_tmp_o *= ContModelHIL_B.D46_tmp_tmp_f;
  ContModelHIL_B.D56_tmp *= ContModelHIL_B.D46_tmp_tmp_f;
  ContModelHIL_B.D15_tmp_g *= ContModelHIL_B.D46_tmp_tmp_e;
  ContModelHIL_B.rtb_ginv_tmp_ap *= ContModelHIL_B.D46_tmp_tmp_h;
  ContModelHIL_B.D46_tmp_tmp_o = ContModelHIL_B.d53 * ContModelHIL_B.y_a;
  ContModelHIL_B.d2 = ContModelHIL_B.d41 * ContModelHIL_B.D56_tmp_b;
  ContModelHIL_B.d20 = ContModelHIL_B.d41 * ContModelHIL_B.D56_tmp_bs;
  ContModelHIL_B.d91 = ContModelHIL_B.d54 * ContModelHIL_B.D46_tmp_tmp_l;
  tmp =
    (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((((((((((((((((ContModelHIL_B.d25 *
    ContModelHIL_B.D68 + ContModelHIL_B.d25 * ContModelHIL_B.d) +
    ContModelHIL_B.tmp_tmp_c * ContModelHIL_B.D56_tmp_tmp_e) +
    ContModelHIL_B.d90) + ContModelHIL_B.tmp_tmp_n *
    ContModelHIL_B.D56_tmp_tmp_e) + ContModelHIL_B.d92) +
    ContModelHIL_B.tmp_tmp_i * ContModelHIL_B.D56_tmp_tmp_e) +
    ContModelHIL_B.d93) + ContModelHIL_B.tmp_tmp_p *
    ContModelHIL_B.D56_tmp_tmp_e) + ContModelHIL_B.d94) +
    ContModelHIL_B.D46_tmp_o) + ContModelHIL_B.D56_tmp) + ContModelHIL_B.d96) +
    ContModelHIL_B.d97) + ContModelHIL_B.rtb_ginv_tmp * ContModelHIL_B.D27) +
    ContModelHIL_B.d98) + ContModelHIL_B.rtb_ginv_tmp_p * ContModelHIL_B.D27) +
    ContModelHIL_B.d99) + ContModelHIL_B.tmp_tmp_j * ContModelHIL_B.D56_tmp_e) +
    ContModelHIL_B.d100) + ContModelHIL_B.tmp_tmp_e * ContModelHIL_B.D56_tmp_e)
    + ContModelHIL_B.d101) + ContModelHIL_B.tmp_tmp_mv *
    ContModelHIL_B.D56_tmp_e) + ContModelHIL_B.d102) + ContModelHIL_B.tmp_tmp_m0
    * ContModelHIL_B.D56_tmp_e) + ContModelHIL_B.d103) +
    ContModelHIL_B.rtb_ginv_tmp_ap) + ContModelHIL_B.D15_tmp_g) +
    ContModelHIL_B.d104) + ContModelHIL_B.d105) + ContModelHIL_B.rtb_ginv_tmp_m *
    ContModelHIL_B.D56_tmp_tmp_f) + ContModelHIL_B.d106) + ContModelHIL_B.D45 *
    ContModelHIL_B.D56_tmp_tmp_ff) + ContModelHIL_B.d107) +
    ContModelHIL_B.tmp_tmp_f * ContModelHIL_B.D56_tmp_bj) + ContModelHIL_B.d108)
    + ContModelHIL_B.tmp_tmp * ContModelHIL_B.D56_tmp_bj) + ContModelHIL_B.d109)
    + ContModelHIL_B.tmp_tmp_a * ContModelHIL_B.D56_tmp_bj) +
    ContModelHIL_B.d110) + ContModelHIL_B.d95 * 0.00046501 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.d95 * 0.0003034 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.d95 * 0.0393748 *
    ContModelHIL_B.D15_tmp) + -0.0525693184 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.142 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.tmp_tmp_b * 0.142 *
    ContModelHIL_B.D15_tmp) + -0.0383689744 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[3] * 0.143 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.tmp_tmp_b * 0.143 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.d95 * 0.028900000000000006 * 0.143 *
    ContModelHIL_B.D15_tmp) + ContModelHIL_B.tmp_tmp_c *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d14 * 0.04043155 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.tmp_tmp_n *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.d27 * 0.06214814 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.tmp_tmp_i *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.tmp_tmp_m * 0.142 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.tmp_tmp_p *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.tmp_tmp_m * 0.143 *
    ContModelHIL_B.D56_tmp_tmp_b) + ContModelHIL_B.tmp_tmp_er) +
    ContModelHIL_B.tmp_tmp_d) + ContModelHIL_B.d32 * ContModelHIL_B.D46_tmp_p) +
    ContModelHIL_B.tmp_tmp_ik) + ContModelHIL_B.rtb_ginv_tmp *
    ContModelHIL_B.D56_tmp_tmp_g2) + 0.45856 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.08312 * 0.142 *
    ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.rtb_ginv_tmp_p *
    ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.d111 * 0.08312 * 0.17 *
    0.143 * ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.tmp_tmp_j *
    ContModelHIL_B.D56_tmp_j) + ContModelHIL_B.tmp_tmp_g) +
    ContModelHIL_B.tmp_tmp_e * ContModelHIL_B.D56_tmp_j) +
    ContModelHIL_B.tmp_tmp_nn) + ContModelHIL_B.tmp_tmp_mv *
    ContModelHIL_B.D56_tmp_j) + ContModelHIL_B.tmp_tmp_l) +
    ContModelHIL_B.tmp_tmp_m0 * ContModelHIL_B.D56_tmp_j) +
    ContModelHIL_B.tmp_tmp_ce) + ContModelHIL_B.tmp_tmp_c5) +
    ContModelHIL_B.tmp_tmp_nc) + ContModelHIL_B.d32 * ContModelHIL_B.D46_tmp_l)
    + ContModelHIL_B.tmp_tmp_ph) + ContModelHIL_B.rtb_ginv_tmp_m *
    ContModelHIL_B.D56_tmp_tmp_g) + ContModelHIL_B.tmp_tmp_jg * 0.08312 * 0.143 *
    ContModelHIL_B.D56_tmp_tmp_g) + ContModelHIL_B.D45 *
    ContModelHIL_B.D56_tmp_tmp_o) + ContModelHIL_B.tmp_tmp_dk) +
    ContModelHIL_B.tmp_tmp_f * ContModelHIL_B.D56_tmp_f) +
    ContModelHIL_B.tmp_tmp_oi) + ContModelHIL_B.tmp_tmp *
    ContModelHIL_B.D56_tmp_f) + ContModelHIL_B.tmp_tmp_jr) +
    ContModelHIL_B.tmp_tmp_a * ContModelHIL_B.D56_tmp_f) +
    ContModelHIL_B.tmp_tmp_c2) + ContModelHIL_B.d25 * ContModelHIL_B.d3) +
    ContModelHIL_B.d25 * ContModelHIL_B.d4) + ((((((ContModelHIL_B.D48 +
    ContModelHIL_B.D15) - ContModelHIL_B.D25) - ContModelHIL_B.D14) -
    ContModelHIL_B.tmp_tmp_nr) - 0.0023809214000000004 *
    ContModelHIL_B.D46_tmp_e) + ContModelHIL_B.d18) * (ContModelHIL_B.D28_tmp *
    ContModelHIL_B.D15_tmp)) + ((((((((((((-0.0064528108032 *
    ContModelHIL_B.D24_tmp + ContModelHIL_B.D47_tmp_g) + -0.0013531005056 *
    ContModelHIL_B.D24_tmp_p) - 0.0020206472 * ContModelHIL_B.D24_tmp_p) +
    ContModelHIL_B.D47_tmp_p) + ContModelHIL_B.D47_tmp) + ContModelHIL_B.D15) -
    ContModelHIL_B.D25) - ContModelHIL_B.D14) - ContModelHIL_B.tmp_tmp_nr) +
    ContModelHIL_B.d31) + ContModelHIL_B.d38) + ContModelHIL_B.d18) *
    (ContModelHIL_B.D16_tmp * ContModelHIL_B.D15_tmp)) + ContModelHIL_B.d112) +
    ContModelHIL_B.d48 * ContModelHIL_B.d5) + ContModelHIL_B.d49 *
    ContModelHIL_B.d5) + ContModelHIL_B.rtb_ginv_tmp_a * ContModelHIL_B.D67) +
    ContModelHIL_B.d113) + ContModelHIL_B.d114) + ContModelHIL_B.d45 *
    ContModelHIL_B.d8) + ContModelHIL_B.d50 * ContModelHIL_B.D37) +
    ContModelHIL_B.rtb_ginv_tmp_a * ContModelHIL_B.rtb_ginv_tmp_j) +
    ContModelHIL_B.d115) + ContModelHIL_B.d116) + ContModelHIL_B.d117) +
    ContModelHIL_B.d118) - ContModelHIL_B.d119) - ContModelHIL_B.d120) -
    ContModelHIL_B.d121) + ContModelHIL_B.d122 * ContModelHIL_B.D56_tmp_g) +
    ContModelHIL_B.d123) + ContModelHIL_B.d124) + ContModelHIL_B.d125) -
                     ContModelHIL_B.d126) - ContModelHIL_B.d127) +
                   ContModelHIL_B.d122 * ContModelHIL_B.D56_tmp_dh) +
                  ContModelHIL_B.d128) + ContModelHIL_B.tmp_tmp_hp *
                 ContModelHIL_B.D46_tmp) + ContModelHIL_B.d129 *
                ContModelHIL_B.D46_tmp) + ContModelHIL_B.D17_tmp_tmp_f *
               0.00046501 * ContModelHIL_B.D46_tmp) + ContModelHIL_B.tmp_tmp_da *
              ContModelHIL_B.D46_tmp) + ContModelHIL_B.d130 *
             ContModelHIL_B.D46_tmp) + ContModelHIL_B.D17_tmp_tmp_f * 0.0003034 *
            ContModelHIL_B.D46_tmp) + ContModelHIL_B.D17_tmp_tmp_f * 0.0393748 *
           ContModelHIL_B.D46_tmp) + ContModelHIL_B.d131 *
          ContModelHIL_B.D46_tmp) + ContModelHIL_B.d16 * 0.06214814 *
         ContModelHIL_B.D46_tmp) + ContModelHIL_B.d132 * ContModelHIL_B.D46_tmp)
       + ContModelHIL_B.d133 * ContModelHIL_B.D46_tmp) + ContModelHIL_B.d134 *
      ContModelHIL_B.D46_tmp) + ContModelHIL_B.D14_tmp_m *
     ContModelHIL_B.D46_tmp) + ContModelHIL_B.d135 * ContModelHIL_B.D46_tmp;
  ContModelHIL_B.dv[37] = -(((((((((((((((((((((((((((((((tmp +
    ContModelHIL_B.d136) + ContModelHIL_B.d137) + ContModelHIL_B.d138) +
    ContModelHIL_B.d139) - ContModelHIL_B.d140) + ContModelHIL_B.d141) +
    ContModelHIL_B.d142) + ContModelHIL_B.d32 * ContModelHIL_B.D46_tmp_lx) -
    ContModelHIL_B.d143) + ContModelHIL_B.d144) + ContModelHIL_B.d145) +
    ContModelHIL_B.D46_tmp_tmp_o) + ContModelHIL_B.d122 *
    ContModelHIL_B.D56_tmp_b) + ContModelHIL_B.d2) + ContModelHIL_B.d32 *
    ContModelHIL_B.D46_tmp_nu) - ContModelHIL_B.d146) + ContModelHIL_B.d147) +
    ContModelHIL_B.d148) + ContModelHIL_B.d122 * ContModelHIL_B.D56_tmp_bs) +
    ContModelHIL_B.d20) + ContModelHIL_B.d52 * ContModelHIL_B.d7) +
    ContModelHIL_B.d43 * ContModelHIL_B.d7) + ContModelHIL_B.rtb_ginv_tmp_a *
    ContModelHIL_B.D15_tmp_tmp) + ContModelHIL_B.d54 * ContModelHIL_B.d9) +
    ContModelHIL_B.d44 * ContModelHIL_B.D14_tmp_tmp) +
    ContModelHIL_B.rtb_ginv_tmp_a * ContModelHIL_B.D15_tmp_tmp_a) +
    ContModelHIL_B.d52 * ContModelHIL_B.rtb_ginv_tmp_tmp_p) + ContModelHIL_B.d43
    * ContModelHIL_B.rtb_ginv_tmp_tmp_p) + ContModelHIL_B.d44 *
    ContModelHIL_B.D56_tmp_tmp) + ContModelHIL_B.d91) * 0.125);
  ContModelHIL_B.D56_tmp_tmp_b = ContModelHIL_B.D46_tmp_ln *
    ContModelHIL_B.rtb_ginv_tmp_tmp;
  ContModelHIL_B.D56_tmp_tmp_e = -2.0 * ContModelHIL_B.rtb_ginv_tmp_tmp *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.rtb_ginv_tmp_tmp = 0.11464 * ContModelHIL_B.D15_tmp_f +
    ContModelHIL_B.D24_tmp_d;
  ContModelHIL_B.D17_tmp_tmp_f = 0.08312 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE;
  ContModelHIL_B.D16_tmp = 4.0 * ContModelHIL_B.D14_tmp;
  ContModelHIL_B.D28_tmp = 0.0 * ContModelHIL_B.D46_tmp_h2;
  ContModelHIL_B.d16 = ((0.17 * ContModelHIL_B.D17_tmp_j +
    ContModelHIL_B.D17_tmp_tmp_f) + 0.09794 * ContModelHIL_B.D17_tmp_p) *
    ContModelHIL_B.Observer_beta - ContModelHIL_B.D24_tmp_n *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.u;
  ContModelHIL_B.d18 = ContModelHIL_B.D16 * -2.0;
  ContModelHIL_B.d25 = 0.0 * ContModelHIL_B.D56_tmp_tmp_tmp;
  ContModelHIL_B.tmp_tmp = -0.00045390000000000003 * ContModelHIL_B.D46_tmp_hh +
    ContModelHIL_B.d25;
  ContModelHIL_B.d31 = ContModelHIL_B.D16_tmp * ContModelHIL_B.D17_tmp_h *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * (ContModelHIL_B.D46_tmp_h3 +
    ContModelHIL_B.D46_tmp_d);
  ContModelHIL_B.d32 = (-0.0005375800000000001 * ContModelHIL_B.D56_tmp_k +
                        ContModelHIL_B.D28_tmp) * ContModelHIL_B.rtb_ginv_tmp_c;
  ContModelHIL_B.d38 = (0.0005375800000000001 * ContModelHIL_B.D56_tmp_k +
                        ContModelHIL_B.rtb_ginv_tmp_pm) *
    ContModelHIL_B.rtb_ginv_tmp_f;
  ContModelHIL_B.tmp_tmp_p = ContModelHIL_B.d16 * 0.572;
  ContModelHIL_B.D17_tmp_tmp_f = (0.11464 * ContModelHIL_B.D17_tmp_j +
    ContModelHIL_B.D17_tmp_tmp_f) * ContModelHIL_B.Observer_beta;
  ContModelHIL_B.d111 = ContModelHIL_B.D35 * ContModelHIL_B.D14_tmp_pb *
    ContModelHIL_B.D46_tmp;
  ContModelHIL_B.tmp_tmp_b = ContModelHIL_B.D34 * ContModelHIL_B.d149 *
    ContModelHIL_B.D46_tmp;
  ContModelHIL_B.dv[45] = -((((((((((((((((((((-0.00045390000000000003 *
    ContModelHIL_B.D14_tmp_p * ContModelHIL_B.u_i + ContModelHIL_B.d25) *
    (ContModelHIL_B.D16_tmp * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE) * ContModelHIL_B.u +
    (((ContModelHIL_B.D56_tmp_tmp_b * ContModelHIL_B.D46_tmp_l5 +
    ContModelHIL_B.D56_tmp_tmp_e * ContModelHIL_B.D24) +
    ContModelHIL_B.D56_tmp_tmp_b * ContModelHIL_B.D35) +
    ContModelHIL_B.D56_tmp_tmp_e * ContModelHIL_B.D34)) + ((-0.0 *
    ContModelHIL_B.D14_tmp_p * ContModelHIL_B.u_i + ContModelHIL_B.D46_tmp_o4) +
    ContModelHIL_B.D46_tmp_me) * (ContModelHIL_B.d18 * ContModelHIL_B.D15_tmp) *
    ContModelHIL_B.u) + -2.0 * ContModelHIL_B.D15_tmp * ContModelHIL_B.D56 *
    ContModelHIL_B.D26 * ContModelHIL_B.u) - ContModelHIL_B.D16 *
    ContModelHIL_B.D15_tmp * ContModelHIL_B.D46 * ContModelHIL_B.u) -
    ContModelHIL_B.D56 * ContModelHIL_B.D15_tmp * ContModelHIL_B.D46_tmp_h *
    ContModelHIL_B.u) + ContModelHIL_B.D46_tmp_ln * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE * (-0.00026879000000000003 *
    ContModelHIL_B.D56_tmp_k + ContModelHIL_B.D28_tmp) * ContModelHIL_B.u) +
    ContModelHIL_B.rtb_ginv_tmp_tmp * -0.284 * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.DigitalClock * (ContModelHIL_B.D17_tmp_tmp_f -
    ContModelHIL_B.rtb_ginv_tmp_tmp * ContModelHIL_B.DigitalClock *
    ContModelHIL_B.u)) + ContModelHIL_B.D24_tmp_n * -0.286 *
    ContModelHIL_B.D15_tmp * ContModelHIL_B.DigitalClock * ContModelHIL_B.d16) +
    -0.284 * ContModelHIL_B.Observer_beta * ContModelHIL_B.rtb_ginv_tmp_tmp *
    ContModelHIL_B.D15_tmp * ContModelHIL_B.D45_tmp) + -0.286 *
    ContModelHIL_B.Observer_beta * ContModelHIL_B.D24_tmp_n *
    ContModelHIL_B.D15_tmp * ContModelHIL_B.D24_tmp_f) + 0.00046501 *
    ContModelHIL_B.D46_tmp) + 0.0003034 * ContModelHIL_B.D46_tmp) + 0.0393748 *
    ContModelHIL_B.D46_tmp) - ContModelHIL_B.D45_tmp_c * ContModelHIL_B.D46_tmp)
    - ContModelHIL_B.D56 * 0.04043155 * ContModelHIL_B.D46_tmp) *
    ContModelHIL_B.d14 + ((((ContModelHIL_B.D18_tmp * 0.572 *
    ContModelHIL_B.D24_tmp_f + ((ContModelHIL_B.d31 + ContModelHIL_B.d32) +
    ContModelHIL_B.d38)) + ContModelHIL_B.tmp_tmp_p * ContModelHIL_B.D17_tmp_m)
    + ContModelHIL_B.d111) + ContModelHIL_B.tmp_tmp_b) *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[7]) +
    (((((((((((((ContModelHIL_B.D17_tmp_h * -2.0 * ContModelHIL_B.D17 *
                 (-0.00045390000000000003 * ContModelHIL_B.D56_tmp_tmp_tmp +
                  ContModelHIL_B.rtb_ginv_tmp_p2) + ContModelHIL_B.d18 *
                 ContModelHIL_B.D17_tmp_h * ContModelHIL_B.tmp_tmp) +
                ContModelHIL_B.D17_tmp_h * 2.0 * ContModelHIL_B.D56 *
                ContModelHIL_B.tmp_tmp) + ContModelHIL_B.d31) +
              ContModelHIL_B.d32) + ContModelHIL_B.d38) +
            (ContModelHIL_B.D17_tmp * ContModelHIL_B.D17_tmp_c +
             ContModelHIL_B.D17_tmp_m3 * ContModelHIL_B.D17_tmp_n) * 0.572 *
            ContModelHIL_B.D24_tmp_f) + (ContModelHIL_B.D17_tmp_tmp_e *
    -ContModelHIL_B.D17_tmp_c + ContModelHIL_B.D17_tmp_tmp_a *
    ContModelHIL_B.D17_tmp_n) * ContModelHIL_B.tmp_tmp_p) +
          (ContModelHIL_B.D17_tmp_k *
           ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE +
           ContModelHIL_B.D17_tmp_n3 * ContModelHIL_B.D14_tmp) *
          (ContModelHIL_B.D45_tmp * 0.06511552)) + ((ContModelHIL_B.D14_tmp_p *
    ContModelHIL_B.DigitalClock * ContModelHIL_B.u +
    -ContModelHIL_B.Observer_beta * ContModelHIL_B.u_i) * (0.11464 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE) +
    (ContModelHIL_B.D17_tmp_tmp_o * ContModelHIL_B.u +
     ContModelHIL_B.D17_tmp_tmp_g) * (0.11464 * ContModelHIL_B.D14_tmp)) *
         ((-ContModelHIL_B.rtb_ginv_tmp_tmp * ContModelHIL_B.DigitalClock *
           ContModelHIL_B.u + ContModelHIL_B.D17_tmp_tmp_f) * 0.568)) +
        ContModelHIL_B.D46_tmp_l5 * ContModelHIL_B.D14_tmp_pb *
        ContModelHIL_B.D46_tmp) + ContModelHIL_B.D24 * ContModelHIL_B.d149 *
       ContModelHIL_B.D46_tmp) + ContModelHIL_B.d111) + ContModelHIL_B.tmp_tmp_b)
    * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6]) -
    (((((((((((((((((((((((((((((((((((((((((0.0 * ContModelHIL_B.D56_tmp_e +
    ContModelHIL_B.D27_tmp) + ContModelHIL_B.D46_tmp_tmp_m) + 0.0 *
    ContModelHIL_B.D56_tmp_bj) + ContModelHIL_B.D37_tmp) + 0.0 *
    ContModelHIL_B.D56_tmp_j) + ContModelHIL_B.d60) + 0.0 *
    ContModelHIL_B.D56_tmp_f) - ContModelHIL_B.D56_tmp_tmp_c) +
    ContModelHIL_B.D56_tmp_tmp_cj) - ContModelHIL_B.D56_tmp_tmp_m) -
    ContModelHIL_B.D56_tmp_tmp_j) + -0.0 * ContModelHIL_B.D46_tmp_j) +
    -0.0027062010112 * ContModelHIL_B.D56_tmp_d) + -0.0040412944 *
    ContModelHIL_B.D56_tmp_d) + ContModelHIL_B.D56_tmp_tmp_k) -
    ContModelHIL_B.D56_tmp_tmp_mx) - ContModelHIL_B.D56_tmp_tmp_p) -
    ContModelHIL_B.D56_tmp_tmp_d) + -0.0 * ContModelHIL_B.D46_tmp_ld) +
    -0.0023282610207999996 * ContModelHIL_B.D56_tmp_ju) + -0.004761842800000001 *
    ContModelHIL_B.D56_tmp_jz) + ContModelHIL_B.D56_tmp_tmp_g4) -
    ContModelHIL_B.D56_tmp_tmp_c3) - ContModelHIL_B.D56_tmp_tmp_cx) -
                     ContModelHIL_B.D56_tmp_tmp_if) +
                    ContModelHIL_B.D56_tmp_tmp_dx) -
                   ContModelHIL_B.D56_tmp_tmp_g4k) + -0.0009879776191999998 *
                  ContModelHIL_B.D56_tmp_dy) + ContModelHIL_B.D46_tmp_mc) +
                -0.0027062010112 * ContModelHIL_B.D56_tmp_o) + -0.0040412944 *
               ContModelHIL_B.D56_tmp_o) + ContModelHIL_B.D56_tmp_tmp_l) -
             ContModelHIL_B.D56_tmp_tmp_f1) - ContModelHIL_B.D56_tmp_tmp_db) -
           ContModelHIL_B.D56_tmp_tmp_jr) + ContModelHIL_B.D46_tmp_cs) +
         -0.0023282610207999996 * ContModelHIL_B.D56_tmp_o4) +
        -0.004761842800000001 * ContModelHIL_B.D56_tmp_n) + ContModelHIL_B.d39)
      - ContModelHIL_B.D46_tmp_c) - ContModelHIL_B.D56_tmp_h) *
    ContModelHIL_B.D16_tmp_p) * 0.25);
  ContModelHIL_B.D17 = 0.22928 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [4] * 0.08312 * 0.142;
  ContModelHIL_B.D56_tmp_tmp_b = ContModelHIL_B.d14 * 0.08312 * 0.17 * 0.143;
  ContModelHIL_B.D56_tmp_tmp_e = 0.19588 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4];
  ContModelHIL_B.rtb_ginv_tmp_tmp = ContModelHIL_B.D56_tmp_tmp_e * 0.08312 *
    0.143;
  ContModelHIL_B.d149 = ContModelHIL_B.rtb_ginv_tmp_a * ContModelHIL_B.D46_tmp_b;
  ContModelHIL_B.d *= ContModelHIL_B.d42;
  ContModelHIL_B.D16_tmp_p = ContModelHIL_B.rtb_ginv_tmp_m *
    ContModelHIL_B.D46_tmp_tmp_e;
  ContModelHIL_B.D46_tmp_tmp_e *= ContModelHIL_B.d74;
  ContModelHIL_B.D14_tmp_pb = ContModelHIL_B.d122 * ContModelHIL_B.D46_tmp_n;
  ContModelHIL_B.D46_tmp_tmp_i *= ContModelHIL_B.d42;
  ContModelHIL_B.D56_tmp_tmp_f *= ContModelHIL_B.rtb_ginv_tmp_tmp;
  ContModelHIL_B.D17_tmp_tmp_f = ContModelHIL_B.tmp_tmp_o *
    ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.D16_tmp = ContModelHIL_B.tmp_tmp_ch * ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.D27_tmp = ContModelHIL_B.tmp_tmp_bd * ContModelHIL_B.D56_tmp_bj;
  ContModelHIL_B.D28_tmp = ContModelHIL_B.d74 * ContModelHIL_B.D46_tmp_tmp_ax;
  ContModelHIL_B.d16 = ContModelHIL_B.d122 * ContModelHIL_B.D46_tmp_l;
  ContModelHIL_B.D56_tmp_tmp_g *= ContModelHIL_B.rtb_ginv_tmp_tmp;
  ContModelHIL_B.d4 *= ContModelHIL_B.d26;
  ContModelHIL_B.rtb_ginv_tmp_tmp = -0.5876399999999999 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.d18 = ContModelHIL_B.rtb_ginv_tmp_tmp * 0.08312 * 0.143 *
    ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.d25 = ContModelHIL_B.tmp_tmp_da * ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.tmp_tmp = ContModelHIL_B.D16_tmp_l * 0.00034964 *
    ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.d31 = ContModelHIL_B.d134 * ContModelHIL_B.D46_tmp_p4;
  ContModelHIL_B.d32 = ContModelHIL_B.d44 * ContModelHIL_B.D56_tmp_tmp_ol;
  ContModelHIL_B.D37 *= ContModelHIL_B.ab_a;
  ContModelHIL_B.rtb_ginv_tmp_j *= ContModelHIL_B.d26;
  ContModelHIL_B.D56_tmp_tmp_iz *= ContModelHIL_B.ab_a;
  ContModelHIL_B.d38 = ContModelHIL_B.d122 * ContModelHIL_B.D46_tmp_ld;
  ContModelHIL_B.d39 = ContModelHIL_B.d41 * ContModelHIL_B.D56_tmp_dh;
  ContModelHIL_B.tmp_tmp_p = ContModelHIL_B.d122 * ContModelHIL_B.D46_tmp_nu;
  ContModelHIL_B.d40 = (((ContModelHIL_B.d40 - ContModelHIL_B.d10) +
    ContModelHIL_B.D46_tmp_lm) + ContModelHIL_B.D46_tmp_mj) +
    ContModelHIL_B.D46_tmp_cs;
  ContModelHIL_B.d111 = ContModelHIL_B.d40 * ContModelHIL_B.d157;
  ContModelHIL_B.D14_tmp_tmp *= ContModelHIL_B.ab_a;
  ContModelHIL_B.D15_tmp_tmp_a *= ContModelHIL_B.d42;
  ContModelHIL_B.ab_a *= ContModelHIL_B.D56_tmp_tmp;
  ContModelHIL_B.tmp_tmp_b = ContModelHIL_B.D38 * ContModelHIL_B.d5;
  ContModelHIL_B.d5 *= ContModelHIL_B.D48_tmp;
  ContModelHIL_B.tmp_tmp_c = ContModelHIL_B.D38 * ContModelHIL_B.D56_tmp_tmp_i;
  ContModelHIL_B.D56_tmp_tmp_i *= ContModelHIL_B.D48_tmp;
  ContModelHIL_B.tmp_tmp_n = ContModelHIL_B.D38 * ContModelHIL_B.d7;
  ContModelHIL_B.d7 *= ContModelHIL_B.D48_tmp;
  ContModelHIL_B.D38 *= ContModelHIL_B.rtb_ginv_tmp_tmp_p;
  ContModelHIL_B.D48_tmp *= ContModelHIL_B.rtb_ginv_tmp_tmp_p;
  ContModelHIL_B.dv[53] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((ContModelHIL_B.rtb_ginv_tmp_a *
    ContModelHIL_B.D24_tmp + ContModelHIL_B.d149) + ContModelHIL_B.d42 *
    ContModelHIL_B.D68) + ContModelHIL_B.d) + ContModelHIL_B.rtb_ginv_tmp *
    ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.d6 *
    ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.rtb_ginv_tmp_p *
    ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.d55 *
    ContModelHIL_B.D46_tmp_tmp_f) + ContModelHIL_B.d122 *
    ContModelHIL_B.D46_tmp_m) + ContModelHIL_B.d42 * ContModelHIL_B.d1) +
    ContModelHIL_B.D17 * ContModelHIL_B.D27) + ContModelHIL_B.D56_tmp_tmp_b *
    ContModelHIL_B.D27) + ContModelHIL_B.rtb_ginv_tmp_ad *
    ContModelHIL_B.D56_tmp_e) + ContModelHIL_B.rtb_ginv_tmp_k *
    ContModelHIL_B.D56_tmp_e) + ContModelHIL_B.tmp_tmp_i3 *
    ContModelHIL_B.D56_tmp_e) + ContModelHIL_B.tmp_tmp_h *
    ContModelHIL_B.D56_tmp_e) + ContModelHIL_B.d150) + ContModelHIL_B.D16_tmp_p)
    + ContModelHIL_B.D46_tmp_tmp_e) + ContModelHIL_B.D14_tmp_pb) +
    ContModelHIL_B.D46_tmp_tmp_i) + ContModelHIL_B.D56_tmp_tmp_f) +
    ContModelHIL_B.tmp_tmp_nm * ContModelHIL_B.D56_tmp_tmp_ff) +
    ContModelHIL_B.D17_tmp_tmp_f) + ContModelHIL_B.D16_tmp) +
    ContModelHIL_B.D27_tmp) + ContModelHIL_B.d151) + ContModelHIL_B.d152) +
    ContModelHIL_B.d153) + ContModelHIL_B.d154) + ContModelHIL_B.d155) +
    ContModelHIL_B.tmp_tmp_er) + ContModelHIL_B.d6 *
    ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.tmp_tmp_d) +
    ContModelHIL_B.d55 * ContModelHIL_B.D46_tmp_tmp_a) + ContModelHIL_B.d122 *
    ContModelHIL_B.D46_tmp_p) + ContModelHIL_B.tmp_tmp_ik) + ContModelHIL_B.D17 *
    ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.D56_tmp_tmp_b *
    ContModelHIL_B.D56_tmp_tmp_g2) + ContModelHIL_B.tmp_tmp_g) +
    ContModelHIL_B.tmp_tmp_nn) + ContModelHIL_B.tmp_tmp_l) +
    ContModelHIL_B.tmp_tmp_ce) + ContModelHIL_B.d156) +
    ContModelHIL_B.tmp_tmp_nc) + ContModelHIL_B.D28_tmp) + ContModelHIL_B.d16) +
    ContModelHIL_B.tmp_tmp_ph) + ContModelHIL_B.D56_tmp_tmp_g) +
    ContModelHIL_B.tmp_tmp_dk) + ContModelHIL_B.tmp_tmp_oi) +
    ContModelHIL_B.tmp_tmp_jr) + ContModelHIL_B.tmp_tmp_c2) + ContModelHIL_B.d26
    * ContModelHIL_B.d3) + ContModelHIL_B.d4) + -0.68784 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142 *
    ContModelHIL_B.u_i) + -6.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [5] * 0.08312 * 0.17 * 0.143 * ContModelHIL_B.u_i) +
    ContModelHIL_B.tmp_tmp_hp * ContModelHIL_B.D46_tmp_g) +
    ContModelHIL_B.D16_tmp_l * 0.00050874 * ContModelHIL_B.D46_tmp_g) +
    ContModelHIL_B.d132 * ContModelHIL_B.D46_tmp_g) + ContModelHIL_B.d135 *
    ContModelHIL_B.D46_tmp_g) + ContModelHIL_B.d52 * ContModelHIL_B.D18) +
    ContModelHIL_B.d43 * ContModelHIL_B.D18) + ContModelHIL_B.d18) +
    ContModelHIL_B.d25) + ContModelHIL_B.tmp_tmp) + ContModelHIL_B.d31) +
    ContModelHIL_B.d32) + 0.39176 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.17 * 0.143 *
    ContModelHIL_B.D28) + ContModelHIL_B.d54 * ContModelHIL_B.D46_tmp_tmp) +
    ContModelHIL_B.tmp_tmp_b) + ContModelHIL_B.d5) + ContModelHIL_B.d26 *
    ContModelHIL_B.D67) + ContModelHIL_B.tmp_tmp_c) +
    ContModelHIL_B.D56_tmp_tmp_i) + ContModelHIL_B.D37) +
    ContModelHIL_B.rtb_ginv_tmp_j) + ContModelHIL_B.D56_tmp_tmp_iz) +
    ContModelHIL_B.d122 * ContModelHIL_B.D46_tmp_j) - ContModelHIL_B.d118) +
    ContModelHIL_B.d119) + ContModelHIL_B.d120) + ContModelHIL_B.d121) +
    ContModelHIL_B.d41 * ContModelHIL_B.D56_tmp_g) + ContModelHIL_B.d38) +
    -ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 8.085E-5 *
    ContModelHIL_B.D47) + ContModelHIL_B.d126) + ContModelHIL_B.d127) +
    ContModelHIL_B.d39) + ContModelHIL_B.d122 * ContModelHIL_B.D46_tmp_lx) +
    -ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 5.484E-5 *
    ContModelHIL_B.y_a) + ContModelHIL_B.d144) + ContModelHIL_B.d145) +
                        ContModelHIL_B.D46_tmp_tmp_o) + ContModelHIL_B.d2) +
                      ContModelHIL_B.tmp_tmp_p) + ContModelHIL_B.d111) +
                    ContModelHIL_B.d28 * ContModelHIL_B.d158) -
                   ContModelHIL_B.d146) + ContModelHIL_B.d147) +
                 ContModelHIL_B.d148) + ContModelHIL_B.d20) +
               ContModelHIL_B.tmp_tmp_n) + ContModelHIL_B.d7) +
             ContModelHIL_B.d42 * ContModelHIL_B.D15_tmp_tmp) +
            ContModelHIL_B.D14_tmp_tmp) + ContModelHIL_B.D15_tmp_tmp_a) +
          ContModelHIL_B.D38) + ContModelHIL_B.D48_tmp) + ContModelHIL_B.ab_a) +
       ContModelHIL_B.d91) * 0.125);
  ContModelHIL_B.D17 = ContModelHIL_B.D56_tmp_tmp_e * 0.17 * 0.143;
  ContModelHIL_B.D27 = ContModelHIL_B.D58 * ContModelHIL_B.D46_tmp_tmp;
  ContModelHIL_B.D56_tmp_tmp_b = ContModelHIL_B.D58 * ContModelHIL_B.d8;
  ContModelHIL_B.D56_tmp_tmp_g2 = ContModelHIL_B.D58 * ContModelHIL_B.d9;
  ContModelHIL_B.D56_tmp_tmp_e = ContModelHIL_B.D58 *
    ContModelHIL_B.D46_tmp_tmp_l;
  ContModelHIL_B.dv[61] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((ContModelHIL_B.d149
    + ContModelHIL_B.d) + ContModelHIL_B.D45 * ContModelHIL_B.D46_tmp_tmp_h) +
    ContModelHIL_B.d12 * ContModelHIL_B.D46_tmp_tmp_h) +
    ContModelHIL_B.D16_tmp_p) + ContModelHIL_B.D46_tmp_tmp_e) +
    ContModelHIL_B.D14_tmp_pb) + ContModelHIL_B.D46_tmp_tmp_i) +
    ContModelHIL_B.D56_tmp_tmp_f) + ContModelHIL_B.D17 *
    ContModelHIL_B.D56_tmp_tmp_ff) + ContModelHIL_B.D17_tmp_tmp_f) +
    ContModelHIL_B.D16_tmp) + ContModelHIL_B.D27_tmp) + ContModelHIL_B.d152) +
    ContModelHIL_B.d154) + ContModelHIL_B.tmp_tmp_c5) + ContModelHIL_B.d12 *
    ContModelHIL_B.D46_tmp_tmp_c) + ContModelHIL_B.tmp_tmp_nc) +
    ContModelHIL_B.D28_tmp) + ContModelHIL_B.d16) + ContModelHIL_B.tmp_tmp_ph) +
    ContModelHIL_B.D56_tmp_tmp_g) + ContModelHIL_B.D17 *
    ContModelHIL_B.D56_tmp_tmp_o) + ContModelHIL_B.tmp_tmp_oi) +
    ContModelHIL_B.tmp_tmp_jr) + ContModelHIL_B.tmp_tmp_c2) + ContModelHIL_B.d4)
    + ContModelHIL_B.rtb_ginv_tmp_tmp * 0.17 * 0.143 * ContModelHIL_B.D14_tmp_c)
    + ContModelHIL_B.d18) + ContModelHIL_B.d25) + ContModelHIL_B.tmp_tmp) +
    ContModelHIL_B.d31) + ContModelHIL_B.d32) + ContModelHIL_B.d54 *
    ContModelHIL_B.D28) + ContModelHIL_B.D27) + ContModelHIL_B.D56_tmp_tmp_b) +
    ContModelHIL_B.D37) + ContModelHIL_B.rtb_ginv_tmp_j) +
                        ContModelHIL_B.D56_tmp_tmp_iz) + ContModelHIL_B.d38) -
                      ContModelHIL_B.d125) + ContModelHIL_B.d126) +
                    ContModelHIL_B.d127) + ContModelHIL_B.d39) +
                  ContModelHIL_B.tmp_tmp_p) + ContModelHIL_B.d40 *
                 ContModelHIL_B.d158) + ContModelHIL_B.d111) -
               ContModelHIL_B.d146) + ContModelHIL_B.d147) + ContModelHIL_B.d148)
            + ContModelHIL_B.d20) + ContModelHIL_B.D56_tmp_tmp_g2) +
          ContModelHIL_B.D14_tmp_tmp) + ContModelHIL_B.D15_tmp_tmp_a) +
        ContModelHIL_B.ab_a) + ContModelHIL_B.D56_tmp_tmp_e) * 0.125);
  ContModelHIL_B.D17 = ContModelHIL_B.d29 * 0.17 * 0.143 *
    ContModelHIL_B.D14_tmp_c;
  ContModelHIL_B.D46_tmp_tmp_f = ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE
    [3] - ContModelHIL_B.D17_tmp_tmp;
  ContModelHIL_B.dv[30] = -(ContModelHIL_B.d34 * ContModelHIL_B.D46_tmp_tmp_f +
    ContModelHIL_B.D17);
  ContModelHIL_B.dv[38] = -((((((((((((((((ContModelHIL_B.d159 +
    ContModelHIL_B.d33) + 0.0020206472 * ContModelHIL_B.u_i) -
    ContModelHIL_B.D16_tmp_n) + ContModelHIL_B.d13) + ContModelHIL_B.d15) +
    ContModelHIL_B.D16_tmp_pt) + 0.0013531005056 * ContModelHIL_B.D18) +
    ContModelHIL_B.d35) + ContModelHIL_B.d36) - ContModelHIL_B.d22) +
    ContModelHIL_B.D14_tmp_o) + ContModelHIL_B.D14_tmp_o3) + ContModelHIL_B.d37)
    + ContModelHIL_B.d160) * ContModelHIL_B.d14 - ContModelHIL_B.D27_tmp_i *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]) * 0.25);
  ContModelHIL_B.D46_tmp_tmp_h = ContModelHIL_B.rtb_ginv_tmp_m *
    ContModelHIL_B.D46_tmp_tmp_ax;
  ContModelHIL_B.D46_tmp_tmp_e = 0.5876399999999999 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5];
  ContModelHIL_B.D56_tmp_tmp_f = ContModelHIL_B.D46_tmp_tmp_e * 0.08312 * 0.143 *
    ContModelHIL_B.D14_tmp_b;
  ContModelHIL_B.D56_tmp_tmp_ff = ContModelHIL_B.d50 *
    ContModelHIL_B.D56_tmp_tmp_ol;
  ContModelHIL_B.dv[46] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((ContModelHIL_B.d161
    + ContModelHIL_B.D46_tmp_o) + ContModelHIL_B.D56_tmp) + ContModelHIL_B.d97)
    + ContModelHIL_B.D15_tmp_g) + ContModelHIL_B.d105) +
    ContModelHIL_B.rtb_ginv_tmp * ContModelHIL_B.D46_tmp_tmp_a) +
    ContModelHIL_B.rtb_ginv_tmp_p * ContModelHIL_B.D46_tmp_tmp_a) +
    ContModelHIL_B.d162) + ContModelHIL_B.D46_tmp_tmp_h) + ContModelHIL_B.d163)
    + ContModelHIL_B.d164) + ContModelHIL_B.d165) + 0.68784 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.142 *
    ContModelHIL_B.u_i) + 6.0 * ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5]
    * 0.08312 * 0.17 * 0.143 * ContModelHIL_B.u_i) + ContModelHIL_B.d166) +
    ContModelHIL_B.d167) + ContModelHIL_B.d168) + ContModelHIL_B.d169) +
    ContModelHIL_B.d48 * ContModelHIL_B.D18) + ContModelHIL_B.d49 *
    ContModelHIL_B.D18) + ContModelHIL_B.D56_tmp_tmp_f) + ContModelHIL_B.d170) +
    ContModelHIL_B.d171) + ContModelHIL_B.d172) + ContModelHIL_B.D56_tmp_tmp_ff)
    + ContModelHIL_B.d173) + ContModelHIL_B.d112) - ContModelHIL_B.tmp_tmp_b) -
    ContModelHIL_B.d5) + ContModelHIL_B.d174) - ContModelHIL_B.tmp_tmp_c) -
    ContModelHIL_B.D56_tmp_tmp_i) - ContModelHIL_B.D37) + ContModelHIL_B.d175) -
    ContModelHIL_B.D56_tmp_tmp_iz) + ContModelHIL_B.d118) - ContModelHIL_B.d119)
    - ContModelHIL_B.d120) - ContModelHIL_B.d121) + ContModelHIL_B.d125) -
    ContModelHIL_B.d126) - ContModelHIL_B.d127) + ContModelHIL_B.d176 * 0.17 *
                        0.143 * ContModelHIL_B.D14_tmp_c * ContModelHIL_B.u) +
                       ContModelHIL_B.d143) - ContModelHIL_B.d144) -
                     ContModelHIL_B.d145) - ContModelHIL_B.D46_tmp_tmp_o) +
                   ContModelHIL_B.d146) - ContModelHIL_B.d147) -
                 ContModelHIL_B.d148) +
                ((((((((((((((((((((((((((((((((((((((((((-5.484E-5 *
    ContModelHIL_B.D56_tmp_e + ContModelHIL_B.d177) + ContModelHIL_B.D14_tmp_k)
    + ContModelHIL_B.d21) + ContModelHIL_B.d23) + ContModelHIL_B.d24) +
    ContModelHIL_B.D14_tmp_d) + ContModelHIL_B.D46_tmp_tmp_m) +
    ContModelHIL_B.D14_tmp_a) + ContModelHIL_B.D14_tmp_cv) -
    ContModelHIL_B.D14_tmp_n) + ContModelHIL_B.D14_tmp_tmp_i) +
    ContModelHIL_B.D14_tmp_tmp_o) + ContModelHIL_B.D14_tmp_cz) +
    ContModelHIL_B.D15_tmp_tmp_o) + ContModelHIL_B.D15_tmp_tmp_k) +
    ContModelHIL_B.D16_tmp_tmp) + ContModelHIL_B.D34_tmp_m) + ContModelHIL_B.d30)
    + ContModelHIL_B.d47) + ContModelHIL_B.D37_tmp) + ContModelHIL_B.d178) +
    ContModelHIL_B.d179) - ContModelHIL_B.rtb_ginv_tmp_e) + ContModelHIL_B.d56)
    + ContModelHIL_B.d57) + ContModelHIL_B.d58) + ContModelHIL_B.d59) +
    ContModelHIL_B.d10) + ContModelHIL_B.d60) + ContModelHIL_B.d11) +
    ContModelHIL_B.d61) - ContModelHIL_B.d62) + ContModelHIL_B.d63) +
    ContModelHIL_B.d64) + ContModelHIL_B.D46_tmp_mv) + ContModelHIL_B.d65) +
                      ContModelHIL_B.D46_tmp_mj) + ContModelHIL_B.d66) +
                    ContModelHIL_B.D56_tmp_c) + ContModelHIL_B.d67) +
                  ContModelHIL_B.D56_tmp_fb) + ContModelHIL_B.d68) *
                ContModelHIL_B.d27) - ContModelHIL_B.tmp_tmp_n) -
              ContModelHIL_B.d7) + ContModelHIL_B.d180) -
            ContModelHIL_B.D14_tmp_tmp) + ContModelHIL_B.d181) -
          ContModelHIL_B.D38) - ContModelHIL_B.D48_tmp) - ContModelHIL_B.ab_a) +
       ContModelHIL_B.d182) * 0.125);
  ContModelHIL_B.dv[54] = -ContModelHIL_B.D17;
  ContModelHIL_B.dv[62] = -(-0.0023809214000000004 * ContModelHIL_B.D14_tmp_c *
    ContModelHIL_B.d19);
  ContModelHIL_B.dv[31] = -((ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] *
    0.17 * ContModelHIL_B.D14_tmp_c + ContModelHIL_B.d51 *
    ContModelHIL_B.D46_tmp_tmp_f) * 0.01400542);
  ContModelHIL_B.dv[39] = -((ContModelHIL_B.d46 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * ContModelHIL_B.D17_tmp_p
    + -ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[4] * 0.0 *
    ContModelHIL_B.D46_tmp_b) + -0.25 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * ContModelHIL_B.d183);
  ContModelHIL_B.dv[47] = -((((((((((((((((((((((((((((((((((ContModelHIL_B.d184
    + ContModelHIL_B.d185) + ContModelHIL_B.rtb_ginv_tmp_ap) +
    ContModelHIL_B.D15_tmp_g) + ContModelHIL_B.d105) + ContModelHIL_B.D45 *
    ContModelHIL_B.D46_tmp_tmp_c) + ContModelHIL_B.D46_tmp_tmp_h) +
    ContModelHIL_B.d163) + ContModelHIL_B.d165) + ContModelHIL_B.D46_tmp_tmp_e *
    0.17 * 0.143 * ContModelHIL_B.D14_tmp_c) + ContModelHIL_B.D56_tmp_tmp_f) +
    ContModelHIL_B.d170) + ContModelHIL_B.d171) + ContModelHIL_B.d172) +
    ContModelHIL_B.D56_tmp_tmp_ff) + ContModelHIL_B.d45 * ContModelHIL_B.D28) -
    ContModelHIL_B.D27) - ContModelHIL_B.D56_tmp_tmp_b) - ContModelHIL_B.D37) +
    ContModelHIL_B.d175) - ContModelHIL_B.D56_tmp_tmp_iz) + ContModelHIL_B.d125)
    - ContModelHIL_B.d126) - ContModelHIL_B.d127) + -0.78352 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[6] * 0.17 * 0.143 *
    ContModelHIL_B.D14_tmp_c * ContModelHIL_B.u) + ContModelHIL_B.d146) -
    ContModelHIL_B.d147) - ContModelHIL_B.d148) + ContModelHIL_B.d183 *
    ContModelHIL_B.d27) - ContModelHIL_B.D56_tmp_tmp_g2) -
    ContModelHIL_B.D14_tmp_tmp) + ContModelHIL_B.d181) + -0.09794 *
    ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[5] * 0.08312 * 0.143 *
    ContModelHIL_B.D56_tmp_tmp) - ContModelHIL_B.D56_tmp_tmp_e) * 0.125);
  ContModelHIL_B.dv[55] = -(0.0023809214000000004 * ContModelHIL_B.D14_tmp_c *
    ContModelHIL_B.d17);
  ContModelHIL_B.dv[63] = -0.0;
  memset(&ContModelHIL_B.dv[0], 0, 24U * sizeof(real_T));
  memset(&ContModelHIL_B.dv1[0], 0, sizeof(real_T) << 3U);
  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_B.D17 =
      ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[ContModelHIL_B.i];
    for (i = 0; i < 8; i++) {
      ContModelHIL_B.dv1[i] += ContModelHIL_B.dv[(ContModelHIL_B.i << 3) + i] *
        ContModelHIL_B.D17;
    }
  }

  ContModelHIL_B.dv2[0] = 0.0;
  ContModelHIL_B.dv2[1] = 0.0;
  ContModelHIL_B.dv2[2] = 20.631230269999996;
  ContModelHIL_B.D17 = -9.80665 * ContModelHIL_B.D15_tmp;
  ContModelHIL_B.dv2[3] = ((-0.023689199999999997 *
    ContModelHIL_B.DiscreteTimeIntegrator3_DSTATE - ContModelHIL_B.D34_tmp) -
    ContModelHIL_B.D34_tmp_a) * ContModelHIL_B.D17;
  ContModelHIL_B.dv2[4] = ContModelHIL_B.D15_tmp_c * 9.80665 * ContModelHIL_B.u;
  ContModelHIL_B.dv2[5] = 0.0;
  ContModelHIL_B.dv2[6] = (-0.040588879999999994 * ContModelHIL_B.D17_tmp_j -
    ContModelHIL_B.D34_tmp_a) * ContModelHIL_B.D17;
  ContModelHIL_B.dv2[7] = 0.137346252043 * ContModelHIL_B.D15_tmp *
    ContModelHIL_B.D17_tmp_p;

  // Product: '<S1>/Matrix Multiply' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_B.fx[ContModelHIL_B.i] = ContModelHIL_B.dv1[ContModelHIL_B.i] -
      ContModelHIL_B.dv2[ContModelHIL_B.i];
    ContModelHIL_DW.Delay4_DSTATE[ContModelHIL_B.i] = 0.0;
  }

  // MATLAB Function: '<S1>/MATLAB Function1'
  ContModelHIL_mldivide_p(ContModelHIL_B.ginv, ContModelHIL_B.fx);

  // Product: '<S1>/Matrix Multiply' incorporates:
  //   Delay: '<S1>/Delay'

  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_B.D17 = ContModelHIL_DW.Delay_DSTATE[ContModelHIL_B.i];
    for (i = 0; i < 8; i++) {
      ContModelHIL_DW.Delay4_DSTATE[i] += ContModelHIL_B.ginv[(ContModelHIL_B.i <<
        3) + i] * ContModelHIL_B.D17;
    }
  }

  // Product: '<S1>/Divide' incorporates:
  //   Constant: '<S1>/Constant'
  //   Delay: '<S4>/Delay'
  //   Product: '<S1>/Matrix Multiply'

  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_B.Delay[ContModelHIL_B.i] =
      ContModelHIL_DW.Delay4_DSTATE[ContModelHIL_B.i] /
      ContModelHIL_P.Constant_Value_l;
  }

  // End of Product: '<S1>/Divide'

  // DigitalClock: '<S3>/Digital Clock'
  ContModelHIL_B.DigitalClock = ((ContModelHIL_M->Timing.clockTick0) * 0.01);

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  propChange = true;
  ContModelHIL_B.i = 0;
  exitg1 = false;
  while (!exitg1 && (ContModelHIL_B.i < 32)) {
    if (!(ContModelHIL_DW.obj.Waypoints[ContModelHIL_B.i] ==
          ContModelHIL_P.Trajectory.Waypoints[ContModelHIL_B.i])) {
      propChange = false;
      exitg1 = true;
    } else {
      ContModelHIL_B.i++;
    }
  }

  if (!propChange) {
    if (ContModelHIL_DW.obj.isInitialized == 1) {
      ContModelHIL_DW.obj.TunablePropsChanged = true;
      ContModelHIL_DW.obj.tunablePropertyChanged[0] = true;
    }

    memcpy(&ContModelHIL_DW.obj.Waypoints[0],
           &ContModelHIL_P.Trajectory.Waypoints[0], sizeof(real_T) << 5U);
  }

  propChange = true;
  ContModelHIL_B.i = 0;
  exitg1 = false;
  while (!exitg1 && (ContModelHIL_B.i < 4)) {
    if (!(ContModelHIL_DW.obj.TimePoints[ContModelHIL_B.i] ==
          ContModelHIL_P.Trajectory.Tstamps[ContModelHIL_B.i])) {
      propChange = false;
      exitg1 = true;
    } else {
      ContModelHIL_B.i++;
    }
  }

  if (!propChange) {
    if (ContModelHIL_DW.obj.isInitialized == 1) {
      ContModelHIL_DW.obj.TunablePropsChanged = true;
      ContModelHIL_DW.obj.tunablePropertyChanged[1] = true;
    }

    ContModelHIL_DW.obj.TimePoints[0] = ContModelHIL_P.Trajectory.Tstamps[0];
    ContModelHIL_DW.obj.TimePoints[1] = ContModelHIL_P.Trajectory.Tstamps[1];
    ContModelHIL_DW.obj.TimePoints[2] = ContModelHIL_P.Trajectory.Tstamps[2];
    ContModelHIL_DW.obj.TimePoints[3] = ContModelHIL_P.Trajectory.Tstamps[3];
  }

  propChange = true;
  ContModelHIL_B.i = 0;
  exitg1 = false;
  while (!exitg1 && (ContModelHIL_B.i < 32)) {
    if (!(ContModelHIL_DW.obj.VelocityBoundaryCondition[ContModelHIL_B.i] ==
          ContModelHIL_P.PolynomialTrajectory_VelocityBo[ContModelHIL_B.i])) {
      propChange = false;
      exitg1 = true;
    } else {
      ContModelHIL_B.i++;
    }
  }

  if (!propChange) {
    if (ContModelHIL_DW.obj.isInitialized == 1) {
      ContModelHIL_DW.obj.TunablePropsChanged = true;
      ContModelHIL_DW.obj.tunablePropertyChanged[3] = true;
    }

    memcpy(&ContModelHIL_DW.obj.VelocityBoundaryCondition[0],
           &ContModelHIL_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) <<
           5U);
  }

  if (ContModelHIL_DW.obj.TunablePropsChanged) {
    ContModelHIL_DW.obj.TunablePropsChanged = false;
    if (ContModelHIL_DW.obj.tunablePropertyChanged[0] ||
        ContModelHIL_DW.obj.tunablePropertyChanged[1] ||
        ContModelHIL_DW.obj.tunablePropertyChanged[2]) {
      propChange = true;
    } else {
      propChange = false;
    }

    if (!propChange) {
      if (ContModelHIL_DW.obj.tunablePropertyChanged[3] ||
          ContModelHIL_DW.obj.tunablePropertyChanged[4]) {
        propChange = true;
      } else {
        propChange = false;
      }
    }

    ContModelHIL_DW.obj.PPFormUpdatedNeeded = propChange;
    if (ContModelHIL_DW.obj.PPFormUpdatedNeeded) {
      PolyTrajSys_regeneratePPFormFro(&ContModelHIL_DW.obj,
        ContModelHIL_DW.obj.Waypoints, ContModelHIL_DW.obj.TimePoints);
    }

    for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 5; ContModelHIL_B.i++) {
      ContModelHIL_DW.obj.tunablePropertyChanged[ContModelHIL_B.i] = false;
    }
  }

  // MATLABSystem: '<S2>/SourceBlock' incorporates:
  //   Constant: '<S2>/Constant'

  ContModelHIL_B.r = ContModelHIL_P.Constant_Value;

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  ContModelHIL_B.u = ContModelHIL_B.DigitalClock;
  ContModelHIL_B.u_i = ContModelHIL_DW.obj.PPStruct.breaks[4];
  if (ContModelHIL_B.DigitalClock == ContModelHIL_DW.obj.PPStruct.breaks[4]) {
    for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 1; ContModelHIL_B.i++) {
      ContModelHIL_B.u = ContModelHIL_B.u_i - 2.220446049250313E-15;
    }
  }

  ContModelHIL_ppval(ContModelHIL_DW.obj.PPStruct.breaks,
                     ContModelHIL_DW.obj.PPStruct.coefs,
                     ContModelHIL_B.DigitalClock, ContModelHIL_B.dv1);

  // MATLAB Function: '<S6>/PD Controller' incorporates:
  //   Constant: '<S6>/Kp'

  ContModelHIL_B.dv[0] = ContModelHIL_P.PID.Kp[0];
  ContModelHIL_B.dv[8] = 0.0;
  ContModelHIL_B.dv[16] = 0.0;
  ContModelHIL_B.dv[24] = 0.0;
  ContModelHIL_B.dv[32] = 0.0;
  ContModelHIL_B.dv[40] = 0.0;
  ContModelHIL_B.dv[48] = 0.0;
  ContModelHIL_B.dv[56] = 0.0;
  ContModelHIL_B.dv[1] = 0.0;
  ContModelHIL_B.dv[9] = ContModelHIL_P.PID.Kp[1];
  ContModelHIL_B.dv[17] = 0.0;
  ContModelHIL_B.dv[25] = 0.0;
  ContModelHIL_B.dv[33] = 0.0;
  ContModelHIL_B.dv[41] = 0.0;
  ContModelHIL_B.dv[49] = 0.0;
  ContModelHIL_B.dv[57] = 0.0;
  ContModelHIL_B.dv[2] = 0.0;
  ContModelHIL_B.dv[10] = 0.0;
  ContModelHIL_B.dv[18] = ContModelHIL_P.PID.Kp[2];
  ContModelHIL_B.dv[26] = 0.0;
  ContModelHIL_B.dv[34] = 0.0;
  ContModelHIL_B.dv[42] = 0.0;
  ContModelHIL_B.dv[50] = 0.0;
  ContModelHIL_B.dv[58] = 0.0;
  ContModelHIL_B.dv[3] = 0.0;
  ContModelHIL_B.dv[11] = 0.0;
  ContModelHIL_B.dv[19] = 0.0;
  ContModelHIL_B.dv[27] = ContModelHIL_P.PID.Kp[3];
  ContModelHIL_B.dv[35] = 0.0;
  ContModelHIL_B.dv[43] = 0.0;
  ContModelHIL_B.dv[51] = 0.0;
  ContModelHIL_B.dv[59] = 0.0;
  ContModelHIL_B.dv[4] = 0.0;
  ContModelHIL_B.dv[12] = 0.0;
  ContModelHIL_B.dv[20] = 0.0;
  ContModelHIL_B.dv[28] = 0.0;
  ContModelHIL_B.dv[36] = ContModelHIL_P.PID.Kp[4];
  ContModelHIL_B.dv[44] = 0.0;
  ContModelHIL_B.dv[52] = 0.0;
  ContModelHIL_B.dv[60] = 0.0;
  ContModelHIL_B.dv[5] = 0.0;
  ContModelHIL_B.dv[13] = 0.0;
  ContModelHIL_B.dv[21] = 0.0;
  ContModelHIL_B.dv[29] = 0.0;
  ContModelHIL_B.dv[37] = 0.0;
  ContModelHIL_B.dv[45] = ContModelHIL_P.PID.Kp[5];
  ContModelHIL_B.dv[53] = 0.0;
  ContModelHIL_B.dv[61] = 0.0;
  ContModelHIL_B.dv[6] = 0.0;
  ContModelHIL_B.dv[14] = 0.0;
  ContModelHIL_B.dv[22] = 0.0;
  ContModelHIL_B.dv[30] = 0.0;
  ContModelHIL_B.dv[38] = 0.0;
  ContModelHIL_B.dv[46] = 0.0;
  ContModelHIL_B.dv[54] = ContModelHIL_P.PID.Kp[6];
  ContModelHIL_B.dv[62] = 0.0;
  ContModelHIL_B.dv[7] = 0.0;
  ContModelHIL_B.dv[15] = 0.0;
  ContModelHIL_B.dv[23] = 0.0;
  ContModelHIL_B.dv[31] = 0.0;
  ContModelHIL_B.dv[39] = 0.0;
  ContModelHIL_B.dv[47] = 0.0;
  ContModelHIL_B.dv[55] = 0.0;
  ContModelHIL_B.dv[63] = ContModelHIL_P.PID.Kp[7];

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  ContModelHIL_ppval(ContModelHIL_DW.obj.PPDStruct.breaks,
                     ContModelHIL_DW.obj.PPDStruct.coefs, ContModelHIL_B.u,
                     ContModelHIL_B.dv3);

  // MATLAB Function: '<S6>/PD Controller' incorporates:
  //   Constant: '<S6>/Kd'

  ContModelHIL_B.ginv[0] = ContModelHIL_P.PID.Kd[0];
  ContModelHIL_B.ginv[8] = 0.0;
  ContModelHIL_B.ginv[16] = 0.0;
  ContModelHIL_B.ginv[24] = 0.0;
  ContModelHIL_B.ginv[32] = 0.0;
  ContModelHIL_B.ginv[40] = 0.0;
  ContModelHIL_B.ginv[48] = 0.0;
  ContModelHIL_B.ginv[56] = 0.0;
  ContModelHIL_B.ginv[1] = 0.0;
  ContModelHIL_B.ginv[9] = ContModelHIL_P.PID.Kd[1];
  ContModelHIL_B.ginv[17] = 0.0;
  ContModelHIL_B.ginv[25] = 0.0;
  ContModelHIL_B.ginv[33] = 0.0;
  ContModelHIL_B.ginv[41] = 0.0;
  ContModelHIL_B.ginv[49] = 0.0;
  ContModelHIL_B.ginv[57] = 0.0;
  ContModelHIL_B.ginv[2] = 0.0;
  ContModelHIL_B.ginv[10] = 0.0;
  ContModelHIL_B.ginv[18] = ContModelHIL_P.PID.Kd[2];
  ContModelHIL_B.ginv[26] = 0.0;
  ContModelHIL_B.ginv[34] = 0.0;
  ContModelHIL_B.ginv[42] = 0.0;
  ContModelHIL_B.ginv[50] = 0.0;
  ContModelHIL_B.ginv[58] = 0.0;
  ContModelHIL_B.ginv[3] = 0.0;
  ContModelHIL_B.ginv[11] = 0.0;
  ContModelHIL_B.ginv[19] = 0.0;
  ContModelHIL_B.ginv[27] = ContModelHIL_P.PID.Kd[3];
  ContModelHIL_B.ginv[35] = 0.0;
  ContModelHIL_B.ginv[43] = 0.0;
  ContModelHIL_B.ginv[51] = 0.0;
  ContModelHIL_B.ginv[59] = 0.0;
  ContModelHIL_B.ginv[4] = 0.0;
  ContModelHIL_B.ginv[12] = 0.0;
  ContModelHIL_B.ginv[20] = 0.0;
  ContModelHIL_B.ginv[28] = 0.0;
  ContModelHIL_B.ginv[36] = ContModelHIL_P.PID.Kd[4];
  ContModelHIL_B.ginv[44] = 0.0;
  ContModelHIL_B.ginv[52] = 0.0;
  ContModelHIL_B.ginv[60] = 0.0;
  ContModelHIL_B.ginv[5] = 0.0;
  ContModelHIL_B.ginv[13] = 0.0;
  ContModelHIL_B.ginv[21] = 0.0;
  ContModelHIL_B.ginv[29] = 0.0;
  ContModelHIL_B.ginv[37] = 0.0;
  ContModelHIL_B.ginv[45] = ContModelHIL_P.PID.Kd[5];
  ContModelHIL_B.ginv[53] = 0.0;
  ContModelHIL_B.ginv[61] = 0.0;
  ContModelHIL_B.ginv[6] = 0.0;
  ContModelHIL_B.ginv[14] = 0.0;
  ContModelHIL_B.ginv[22] = 0.0;
  ContModelHIL_B.ginv[30] = 0.0;
  ContModelHIL_B.ginv[38] = 0.0;
  ContModelHIL_B.ginv[46] = 0.0;
  ContModelHIL_B.ginv[54] = ContModelHIL_P.PID.Kd[6];
  ContModelHIL_B.ginv[62] = 0.0;
  ContModelHIL_B.ginv[7] = 0.0;
  ContModelHIL_B.ginv[15] = 0.0;
  ContModelHIL_B.ginv[23] = 0.0;
  ContModelHIL_B.ginv[31] = 0.0;
  ContModelHIL_B.ginv[39] = 0.0;
  ContModelHIL_B.ginv[47] = 0.0;
  ContModelHIL_B.ginv[55] = 0.0;
  ContModelHIL_B.ginv[63] = ContModelHIL_P.PID.Kd[7];
  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    // Sum: '<S7>/Minus' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    ContModelHIL_B.dv2[ContModelHIL_B.i] = ContModelHIL_B.dv1[ContModelHIL_B.i]
      - ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[ContModelHIL_B.i];

    // Sum: '<S7>/Minus1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'

    ContModelHIL_B.dv4[ContModelHIL_B.i] = ContModelHIL_B.dv3[ContModelHIL_B.i]
      - ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[ContModelHIL_B.i];

    // MATLAB Function: '<S6>/PD Controller'
    ContModelHIL_B.dv5[ContModelHIL_B.i] = 0.0;
  }

  // MATLAB Function: '<S6>/PD Controller'
  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_B.D17 = ContModelHIL_B.dv2[ContModelHIL_B.i];
    for (i = 0; i < 8; i++) {
      ContModelHIL_B.dv5[i] += ContModelHIL_B.dv[(ContModelHIL_B.i << 3) + i] *
        ContModelHIL_B.D17;
    }
  }

  memset(&ContModelHIL_B.dv1[0], 0, sizeof(real_T) << 3U);
  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_B.D17 = ContModelHIL_B.dv4[ContModelHIL_B.i];
    for (i = 0; i < 8; i++) {
      ContModelHIL_B.dv1[i] += ContModelHIL_B.ginv[(ContModelHIL_B.i << 3) + i] *
        ContModelHIL_B.D17;
    }
  }

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  ContModelHIL_ppval(ContModelHIL_DW.obj.PPDDStruct.breaks,
                     ContModelHIL_DW.obj.PPDDStruct.coefs, ContModelHIL_B.u,
                     ContModelHIL_B.dv2);

  // Sum: '<S1>/Add1' incorporates:
  //   Delay: '<S1>/Delay'
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator3'
  //   MATLAB Function: '<S6>/PD Controller'

  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_DW.Delay_DSTATE[ContModelHIL_B.i] =
      (((ContModelHIL_B.dv5[ContModelHIL_B.i] +
         ContModelHIL_B.dv1[ContModelHIL_B.i]) +
        ContModelHIL_B.dv2[ContModelHIL_B.i]) -
       ContModelHIL_DW.DiscreteTimeIntegrator3_DSTATE[ContModelHIL_B.i]) -
      ContModelHIL_B.fx[ContModelHIL_B.i];
  }

  // End of Sum: '<S1>/Add1'

  // MATLABSystem: '<Root>/PX4 Actuator Write' incorporates:
  //   Constant: '<Root>/Constant'
  //   DataTypeConversion: '<Root>/Data Type Conversion10'
  //   DataTypeConversion: '<Root>/Data Type Conversion11'
  //   DataTypeConversion: '<Root>/Data Type Conversion12'
  //   DataTypeConversion: '<Root>/Data Type Conversion13'
  //   DataTypeConversion: '<Root>/Data Type Conversion14'
  //   DataTypeConversion: '<Root>/Data Type Conversion15'
  //   DataTypeConversion: '<Root>/Data Type Conversion8'
  //   DataTypeConversion: '<Root>/Data Type Conversion9'

  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 12; ContModelHIL_B.i++) {
    ContModelHIL_B.motorValues[ContModelHIL_B.i] = (rtNaNF);
  }

  for (ContModelHIL_B.i = 0; ContModelHIL_B.i < 8; ContModelHIL_B.i++) {
    ContModelHIL_B.servoValues[ContModelHIL_B.i] = (rtNaNF);
  }

  ContModelHIL_B.motorValues[0] = static_cast<real32_T>(ContModelHIL_B.Delay[0]);
  ContModelHIL_B.motorValues[1] = static_cast<real32_T>(ContModelHIL_B.Delay[1]);
  ContModelHIL_B.motorValues[2] = static_cast<real32_T>(ContModelHIL_B.Delay[2]);
  ContModelHIL_B.motorValues[3] = static_cast<real32_T>(ContModelHIL_B.Delay[3]);
  ContModelHIL_B.motorValues[4] = static_cast<real32_T>(ContModelHIL_B.Delay[4]);
  ContModelHIL_B.motorValues[5] = static_cast<real32_T>(ContModelHIL_B.Delay[5]);
  ContModelHIL_B.motorValues[6] = static_cast<real32_T>(ContModelHIL_B.Delay[6]);
  ContModelHIL_B.motorValues[7] = static_cast<real32_T>(ContModelHIL_B.Delay[7]);
  MW_actuators_set(ContModelHIL_P.Constant_Value_h, &ContModelHIL_B.motorValues
                   [0], &ContModelHIL_B.servoValues[0]);

  // End of MATLABSystem: '<Root>/PX4 Actuator Write'

  // MATLABSystem: '<S2>/SourceBlock'
  b_varargout_1 = uORB_read_topic_exists(ContModelHIL_DW.obj_h.orbMetadataObj, 0);
  if (b_varargout_1 != 2) {
    b_varargout_1 = uORB_read_step(ContModelHIL_DW.obj_h.orbMetadataObj,
      &ContModelHIL_DW.obj_h.eventStructObj, &ContModelHIL_B.r, false, 1.0);
  }

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S10>/Enable'

  // RelationalOperator: '<S9>/Compare' incorporates:
  //   Constant: '<S9>/Constant'
  //   MATLABSystem: '<S2>/SourceBlock'
  //
  if (b_varargout_1 == ContModelHIL_P.CompareToConstant_const) {
    // SignalConversion generated from: '<S10>/In1'
    ContModelHIL_B.In1 = ContModelHIL_B.r;
  }

  // End of RelationalOperator: '<S9>/Compare'
  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // Sum: '<S4>/Sum8' incorporates:
  //   Delay: '<S4>/Delay'

  ContModelHIL_DW.Delay3_DSTATE[0] = ContModelHIL_B.In1.x -
    ContModelHIL_DW.Delay_DSTATE_a[0];
  ContModelHIL_DW.Delay3_DSTATE[1] = ContModelHIL_B.In1.y -
    ContModelHIL_DW.Delay_DSTATE_a[1];
  ContModelHIL_DW.Delay3_DSTATE[2] = ContModelHIL_B.In1.z -
    ContModelHIL_DW.Delay_DSTATE_a[2];
  ContModelHIL_DW.Delay3_DSTATE[3] = ContModelHIL_B.In1.roll -
    ContModelHIL_DW.Delay_DSTATE_a[3];
  ContModelHIL_DW.Delay3_DSTATE[4] = ContModelHIL_B.In1.pitch -
    ContModelHIL_DW.Delay_DSTATE_a[4];
  ContModelHIL_DW.Delay3_DSTATE[5] = ContModelHIL_B.In1.yaw -
    ContModelHIL_DW.Delay_DSTATE_a[5];
  ContModelHIL_DW.Delay3_DSTATE[6] = ContModelHIL_B.In1.linkone -
    ContModelHIL_DW.Delay_DSTATE_a[6];
  ContModelHIL_DW.Delay3_DSTATE[7] = ContModelHIL_B.In1.linktwo -
    ContModelHIL_DW.Delay_DSTATE_a[7];

  // Update for Delay: '<S4>/Delay7' incorporates:
  //   Sum: '<S4>/Sum8'

  memcpy(&ContModelHIL_DW.Delay7_DSTATE[0], &ContModelHIL_DW.Delay3_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S4>/Delay9' incorporates:
  //   Sum: '<S4>/Sum8'

  memcpy(&ContModelHIL_DW.Delay9_DSTATE[0], &ContModelHIL_DW.Delay3_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S4>/Delay8' incorporates:
  //   Sum: '<S4>/Sum8'

  memcpy(&ContModelHIL_DW.Delay8_DSTATE[0], &ContModelHIL_DW.Delay3_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S4>/Delay6' incorporates:
  //   Sum: '<S4>/Sum8'

  memcpy(&ContModelHIL_DW.Delay6_DSTATE[0], &ContModelHIL_DW.Delay3_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S4>/Delay2' incorporates:
  //   Sum: '<S4>/Sum8'

  memcpy(&ContModelHIL_DW.Delay2_DSTATE[0], &ContModelHIL_DW.Delay3_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S4>/Delay1' incorporates:
  //   Sum: '<S4>/Sum8'

  memcpy(&ContModelHIL_DW.Delay1_DSTATE[0], &ContModelHIL_DW.Delay3_DSTATE[0],
         sizeof(real_T) << 3U);

  // Update for Delay: '<S4>/Delay' incorporates:
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

  memcpy(&ContModelHIL_DW.Delay_DSTATE_a[0],
         &ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[0], sizeof(real_T) << 3U);

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  ContModelHIL_M->Timing.clockTick0++;
}

// Model initialize function
void ContModelHIL_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;
    static const boolean_T tmp[12] = { true, true, true, true, true, true, true,
      true, false, false, false, false };

    // InitializeConditions for Delay: '<S4>/Delay5'
    for (i = 0; i < 64; i++) {
      ContModelHIL_DW.Delay5_DSTATE[i] = ContModelHIL_P.Delay5_InitialCondition;
    }

    // End of InitializeConditions for Delay: '<S4>/Delay5'
    for (i = 0; i < 8; i++) {
      // InitializeConditions for Delay: '<S4>/Delay3'
      ContModelHIL_DW.Delay3_DSTATE[i] = ContModelHIL_P.Delay3_InitialCondition;

      // InitializeConditions for Delay: '<S4>/Delay7'
      ContModelHIL_DW.Delay7_DSTATE[i] = ContModelHIL_P.Delay7_InitialCondition;

      // InitializeConditions for Delay: '<S4>/Delay9'
      ContModelHIL_DW.Delay9_DSTATE[i] = ContModelHIL_P.Delay9_InitialCondition;

      // InitializeConditions for Delay: '<S4>/Delay8'
      ContModelHIL_DW.Delay8_DSTATE[i] = ContModelHIL_P.Delay8_InitialCondition;

      // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator3' 
      ContModelHIL_DW.DiscreteTimeIntegrator3_DSTATE[i] =
        ContModelHIL_P.DiscreteTimeIntegrator3_IC[i];

      // InitializeConditions for Delay: '<S4>/Delay4'
      ContModelHIL_DW.Delay4_DSTATE[i] = ContModelHIL_P.Delay4_InitialCondition;

      // InitializeConditions for Delay: '<S4>/Delay6'
      ContModelHIL_DW.Delay6_DSTATE[i] = ContModelHIL_P.Delay6_InitialCondition;

      // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' 
      ContModelHIL_DW.DiscreteTimeIntegrator1_DSTATE[i] =
        ContModelHIL_P.DiscreteTimeIntegrator1_IC[i];

      // InitializeConditions for Delay: '<S4>/Delay2'
      ContModelHIL_DW.Delay2_DSTATE[i] = ContModelHIL_P.Delay2_InitialCondition;

      // InitializeConditions for Delay: '<S4>/Delay1'
      ContModelHIL_DW.Delay1_DSTATE[i] = ContModelHIL_P.Delay1_InitialCondition;

      // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' 
      ContModelHIL_DW.DiscreteTimeIntegrator_DSTATE[i] =
        ContModelHIL_P.DiscreteTimeIntegrator_IC[i];

      // InitializeConditions for Delay: '<S1>/Delay'
      ContModelHIL_DW.Delay_DSTATE[i] = ContModelHIL_P.Delay_InitialCondition;

      // InitializeConditions for Delay: '<S4>/Delay'
      ContModelHIL_DW.Delay_DSTATE_a[i] =
        ContModelHIL_P.Delay_InitialCondition_b;
    }

    // SystemInitialize for Enabled SubSystem: '<S2>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S10>/In1' incorporates:
    //   Outport: '<S10>/Out1'

    ContModelHIL_B.In1 = ContModelHIL_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S2>/Enabled Subsystem'

    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memset(&ContModelHIL_DW.obj.AccelerationBoundaryCondition[0], 0, 10U *
           sizeof(real_T));
    for (i = 0; i < 5; i++) {
      ContModelHIL_DW.obj.tunablePropertyChanged[i] = false;
    }

    ContModelHIL_DW.obj.TimePoints[0] = ContModelHIL_P.Trajectory.Tstamps[0];
    ContModelHIL_DW.obj.TimePoints[1] = ContModelHIL_P.Trajectory.Tstamps[1];
    ContModelHIL_DW.obj.TimePoints[2] = ContModelHIL_P.Trajectory.Tstamps[2];
    ContModelHIL_DW.obj.TimePoints[3] = ContModelHIL_P.Trajectory.Tstamps[3];
    memcpy(&ContModelHIL_DW.obj.Waypoints[0],
           &ContModelHIL_P.Trajectory.Waypoints[0], sizeof(real_T) << 5U);
    memcpy(&ContModelHIL_DW.obj.VelocityBoundaryCondition[0],
           &ContModelHIL_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) <<
           5U);
    ContModelHIL_DW.obj.isInitialized = 1;
    PolyTrajSys_regeneratePPFormFro(&ContModelHIL_DW.obj,
      ContModelHIL_DW.obj.Waypoints, ContModelHIL_DW.obj.TimePoints);
    ContModelHIL_DW.obj.TunablePropsChanged = false;

    // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'

    // Start for MATLABSystem: '<Root>/PX4 Actuator Write'
    ContModelHIL_DW.obj_a.matlabCodegenIsDeleted = false;
    ContModelHIL_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      ContModelHIL_DW.obj_a.ValidMotorIdx[i] = tmp[i];
    }

    for (i = 0; i < 8; i++) {
      ContModelHIL_DW.obj_a.ValidServoIdx[i] = false;
    }

    MW_actuators_init();
    ContModelHIL_DW.obj_a.isSetupComplete = true;

    // End of Start for MATLABSystem: '<Root>/PX4 Actuator Write'

    // Start for MATLABSystem: '<S2>/SourceBlock'
    ContModelHIL_DW.obj_h.matlabCodegenIsDeleted = false;
    ContModelHIL_DW.obj_h.isSetupComplete = false;
    ContModelHIL_DW.obj_h.isInitialized = 1;
    ContModelHIL_DW.obj_h.orbMetadataObj = ORB_ID(uam_states);
    uORB_read_initialize(ContModelHIL_DW.obj_h.orbMetadataObj,
                         &ContModelHIL_DW.obj_h.eventStructObj);
    ContModelHIL_DW.obj_h.isSetupComplete = true;
  }
}

// Model terminate function
void ContModelHIL_terminate(void)
{
  real32_T servoValues[8];

  // Terminate for MATLABSystem: '<Root>/PX4 Actuator Write'
  if (!ContModelHIL_DW.obj_a.matlabCodegenIsDeleted) {
    ContModelHIL_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((ContModelHIL_DW.obj_a.isInitialized == 1) &&
        ContModelHIL_DW.obj_a.isSetupComplete) {
      for (int32_T i = 0; i < 12; i++) {
        ContModelHIL_B.motorValues_m[i] = (rtNaNF);
      }

      for (int32_T i = 0; i < 8; i++) {
        servoValues[i] = (rtNaNF);
      }

      for (int32_T i = 0; i < 12; i++) {
        if (ContModelHIL_DW.obj_a.ValidMotorIdx[i]) {
          ContModelHIL_B.motorValues_m[i] = 0.0F;
        }
      }

      for (int32_T i = 0; i < 8; i++) {
        if (ContModelHIL_DW.obj_a.ValidServoIdx[i]) {
          servoValues[i] = 0.0F;
        }
      }

      MW_actuators_set(false, &ContModelHIL_B.motorValues_m[0], &servoValues[0]);
      MW_actuators_terminate();
    }
  }

  // End of Terminate for MATLABSystem: '<Root>/PX4 Actuator Write'

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  if (!ContModelHIL_DW.obj_h.matlabCodegenIsDeleted) {
    ContModelHIL_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((ContModelHIL_DW.obj_h.isInitialized == 1) &&
        ContModelHIL_DW.obj_h.isSetupComplete) {
      uORB_read_terminate(&ContModelHIL_DW.obj_h.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SourceBlock'
}

const char_T* RT_MODEL_ContModelHIL_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_ContModelHIL_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
