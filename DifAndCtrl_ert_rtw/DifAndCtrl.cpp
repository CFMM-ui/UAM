//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: DifAndCtrl.cpp
//
// Code generated for Simulink model 'DifAndCtrl'.
//
// Model version                  : 1.70
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Thu Oct 22 18:50:01 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "DifAndCtrl.h"
#include "rtwtypes.h"
#include "DifAndCtrl_types.h"
#include "DifAndCtrl_private.h"
#include <math.h>
#include <string.h>

extern "C"
{

#include "rt_nonfinite.h"

}

// Forward declaration for local functions
static void DifAndCtrl_mldivide_e(const real_T A[64], real_T B[8],
  B_DifAndCtrl_T *DifAndCtrl_B);
static real_T DifAndCtrl_rt_powd_snf(real_T u0, real_T u1, B_DifAndCtrl_T
  *DifAndCtrl_B);
static void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
  const real_T waypoints[16], const real_T timeData[2], B_DifAndCtrl_T
  *DifAndCtrl_B);
static void DifAndCtrl_ppval(const real_T pp_breaks[4], const real_T pp_coefs[96],
  real_T x, real_T v[8]);

//
// This function updates continuous states using the ODE4 fixed-step
// solver algorithm
//
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M, ExtU_DifAndCtrl_T *DifAndCtrl_U,
  ExtY_DifAndCtrl_T *DifAndCtrl_Y)
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = static_cast<ODE4_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 16;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  DifAndCtrl_derivatives(DifAndCtrl_M);

  // f1 = f(t + (h/2), y + (h/2)*f0)
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  DifAndCtrl_step(DifAndCtrl_M, DifAndCtrl_U, DifAndCtrl_Y);
  DifAndCtrl_derivatives(DifAndCtrl_M);

  // f2 = f(t + (h/2), y + (h/2)*f1)
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  DifAndCtrl_step(DifAndCtrl_M, DifAndCtrl_U, DifAndCtrl_Y);
  DifAndCtrl_derivatives(DifAndCtrl_M);

  // f3 = f(t + h, y + h*f2)
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  DifAndCtrl_step(DifAndCtrl_M, DifAndCtrl_U, DifAndCtrl_Y);
  DifAndCtrl_derivatives(DifAndCtrl_M);

  // tnew = t + h
  // ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3)
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
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
void DifAndCtrl_Upowerx1(const real_T rtu_u[8], const real_T rtu_v[8], real_T
  rty_uv[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    rty_uv[i] = rt_powd_snf(fabs(rtu_u[i]), rtu_v[i]);
  }
}

// Function for MATLAB Function: '<S9>/MATLAB Function1'
static void DifAndCtrl_mldivide_e(const real_T A[64], real_T B[8],
  B_DifAndCtrl_T *DifAndCtrl_B)
{
  int32_T a;
  int32_T c;
  int32_T j;
  int32_T jA;
  int32_T jj;
  int32_T kAcol;
  int32_T n;
  int8_T ipiv;
  memcpy(&DifAndCtrl_B->b_A[0], &A[0], sizeof(real_T) << 6U);
  for (j = 0; j < 8; j++) {
    DifAndCtrl_B->ipiv_k[j] = static_cast<int8_T>(j + 1);
  }

  for (j = 0; j < 7; j++) {
    jj = j * 9;
    n = 9 - j;
    a = 0;
    DifAndCtrl_B->smax_a = fabs(DifAndCtrl_B->b_A[jj]);
    for (kAcol = 2; kAcol < n; kAcol++) {
      DifAndCtrl_B->s_f = fabs(DifAndCtrl_B->b_A[(jj + kAcol) - 1]);
      if (DifAndCtrl_B->s_f > DifAndCtrl_B->smax_a) {
        a = kAcol - 1;
        DifAndCtrl_B->smax_a = DifAndCtrl_B->s_f;
      }
    }

    if (DifAndCtrl_B->b_A[jj + a] != 0.0) {
      if (a != 0) {
        n = j + a;
        DifAndCtrl_B->ipiv_k[j] = static_cast<int8_T>(n + 1);
        for (kAcol = 0; kAcol < 8; kAcol++) {
          jA = kAcol << 3;
          a = jA + j;
          DifAndCtrl_B->smax_a = DifAndCtrl_B->b_A[a];
          jA += n;
          DifAndCtrl_B->b_A[a] = DifAndCtrl_B->b_A[jA];
          DifAndCtrl_B->b_A[jA] = DifAndCtrl_B->smax_a;
        }
      }

      n = (jj - j) + 8;
      for (kAcol = jj + 2; kAcol <= n; kAcol++) {
        DifAndCtrl_B->b_A[kAcol - 1] /= DifAndCtrl_B->b_A[jj];
      }
    }

    a = 6 - j;
    jA = jj + 10;
    for (kAcol = 0; kAcol <= a; kAcol++) {
      DifAndCtrl_B->smax_a = DifAndCtrl_B->b_A[((kAcol << 3) + jj) + 8];
      if (DifAndCtrl_B->smax_a != 0.0) {
        c = (jA - j) + 6;
        for (n = jA; n <= c; n++) {
          DifAndCtrl_B->b_A[n - 1] += DifAndCtrl_B->b_A[((jj + n) - jA) + 1] *
            -DifAndCtrl_B->smax_a;
        }
      }

      jA += 8;
    }

    ipiv = DifAndCtrl_B->ipiv_k[j];
    if (j + 1 != ipiv) {
      DifAndCtrl_B->smax_a = B[j];
      B[j] = B[ipiv - 1];
      B[ipiv - 1] = DifAndCtrl_B->smax_a;
    }
  }

  for (j = 0; j < 8; j++) {
    kAcol = j << 3;
    if (B[j] != 0.0) {
      for (jj = j + 2; jj < 9; jj++) {
        B[jj - 1] -= DifAndCtrl_B->b_A[(jj + kAcol) - 1] * B[j];
      }
    }
  }

  for (j = 7; j >= 0; j--) {
    kAcol = j << 3;
    DifAndCtrl_B->smax_a = B[j];
    if (DifAndCtrl_B->smax_a != 0.0) {
      B[j] = DifAndCtrl_B->smax_a / DifAndCtrl_B->b_A[j + kAcol];
      for (jj = 0; jj < j; jj++) {
        B[jj] -= DifAndCtrl_B->b_A[jj + kAcol] * B[j];
      }
    }
  }
}

static real_T DifAndCtrl_rt_powd_snf(real_T u0, real_T u1, B_DifAndCtrl_T
  *DifAndCtrl_B)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    DifAndCtrl_B->d200 = fabs(u0);
    DifAndCtrl_B->d201 = fabs(u1);
    if (rtIsInf(u1)) {
      if (DifAndCtrl_B->d200 == 1.0) {
        y = 1.0;
      } else if (DifAndCtrl_B->d200 > 1.0) {
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
    } else if (DifAndCtrl_B->d201 == 0.0) {
      y = 1.0;
    } else if (DifAndCtrl_B->d201 == 1.0) {
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

static void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
  const real_T waypoints[16], const real_T timeData[2], B_DifAndCtrl_T
  *DifAndCtrl_B)
{
  int32_T b_i;
  int32_T b_j;
  int32_T i;
  static const int8_T tmp[4] = { 0, 0, 0, 1 };

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  DifAndCtrl_B->finalTime = timeData[1] - timeData[0];
  for (b_j = 0; b_j < 8; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    DifAndCtrl_B->obj_PPStruct = waypoints[b_j];
    DifAndCtrl_B->obj_PPStruct_n = obj->VelocityBoundaryCondition[b_j];
    DifAndCtrl_B->waypoints_idx_0 = waypoints[b_j + 8] -
      (DifAndCtrl_B->finalTime * DifAndCtrl_B->obj_PPStruct_n +
       DifAndCtrl_B->obj_PPStruct);
    DifAndCtrl_B->xtmp = obj->VelocityBoundaryCondition[b_j + 8] - (0.0 *
      DifAndCtrl_B->obj_PPStruct + DifAndCtrl_B->obj_PPStruct_n);
    DifAndCtrl_B->obj_PPStruct_tmp = DifAndCtrl_B->finalTime *
      DifAndCtrl_B->finalTime;
    DifAndCtrl_B->obj_PPStruct_k = 3.0 / DifAndCtrl_B->obj_PPStruct_tmp *
      DifAndCtrl_B->waypoints_idx_0 + -1.0 / DifAndCtrl_B->finalTime *
      DifAndCtrl_B->xtmp;
    DifAndCtrl_B->waypoints_idx_0 = 1.0 / DifAndCtrl_B->obj_PPStruct_tmp *
      DifAndCtrl_B->xtmp + -2.0 / DifAndCtrl_rt_powd_snf(DifAndCtrl_B->finalTime,
      3.0, DifAndCtrl_B) * DifAndCtrl_B->waypoints_idx_0;
    obj->PPStruct.breaks[0] = DifAndCtrl_B->waypoints_idx_0;
    obj->PPStruct.breaks[3] = DifAndCtrl_B->obj_PPStruct;
    obj->PPStruct.breaks[1] = DifAndCtrl_B->obj_PPStruct_k;
    obj->PPStruct.breaks[2] = DifAndCtrl_B->obj_PPStruct_n;
    DifAndCtrl_B->coefMat[b_j] = DifAndCtrl_B->waypoints_idx_0;
    DifAndCtrl_B->coefMat[b_j + 8] = DifAndCtrl_B->obj_PPStruct_k;
    DifAndCtrl_B->coefMat[b_j + 16] = DifAndCtrl_B->obj_PPStruct_n;
    DifAndCtrl_B->coefMat[b_j + 24] = DifAndCtrl_B->obj_PPStruct;
  }

  memset(&DifAndCtrl_B->coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&DifAndCtrl_B->coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    b_i = tmp[b_j];
    for (i = 0; i < 8; i++) {
      DifAndCtrl_B->coeffMat[i + 24] += DifAndCtrl_B->coefMat[(b_j << 3) + i] *
        static_cast<real_T>(b_i);
    }
  }

  memset(&DifAndCtrl_B->coefsWithFlatStart[0], 0, sizeof(real_T) << 6U);
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[0], &DifAndCtrl_B->coeffMat[0],
         sizeof(real_T) << 3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[8], &DifAndCtrl_B->coefMat[0], sizeof
         (real_T) << 3U);
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[16], &DifAndCtrl_B->coeffMat[8],
         sizeof(real_T) << 3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[24], &DifAndCtrl_B->coefMat[8],
         sizeof(real_T) << 3U);
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[32], &DifAndCtrl_B->coeffMat[16],
         sizeof(real_T) << 3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[40], &DifAndCtrl_B->coefMat[16],
         sizeof(real_T) << 3U);
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[48], &DifAndCtrl_B->coeffMat[24],
         sizeof(real_T) << 3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&DifAndCtrl_B->coefsWithFlatStart[56], &DifAndCtrl_B->coefMat[24],
         sizeof(real_T) << 3U);
  obj->PPStruct.breaks[0] = DifAndCtrl_rt_powd_snf(DifAndCtrl_B->finalTime, 3.0,
    DifAndCtrl_B);
  obj->PPStruct.breaks[1] = DifAndCtrl_rt_powd_snf(DifAndCtrl_B->finalTime, 2.0,
    DifAndCtrl_B);
  obj->PPStruct.breaks[2] = DifAndCtrl_rt_powd_snf(DifAndCtrl_B->finalTime, 1.0,
    DifAndCtrl_B);
  obj->PPStruct.breaks[3] = DifAndCtrl_rt_powd_snf(DifAndCtrl_B->finalTime, 0.0,
    DifAndCtrl_B);
  memset(&DifAndCtrl_B->coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&DifAndCtrl_B->coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    DifAndCtrl_B->finalTime = obj->PPStruct.breaks[b_j];
    for (b_i = 0; b_i < 8; b_i++) {
      DifAndCtrl_B->coeffMat[b_i + 24] += DifAndCtrl_B->coefsWithFlatStart[((b_j
        << 4) + b_i) + 8] * DifAndCtrl_B->finalTime;
    }
  }

  memset(&obj->PPDStruct.coefs[0], 0, 96U * sizeof(real_T));
  for (b_j = 0; b_j < 4; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memcpy(&obj->PPDStruct.coefs[b_j * 24], &DifAndCtrl_B->
           coefsWithFlatStart[b_j << 4], sizeof(real_T) << 4U);
    memcpy(&obj->PPDStruct.coefs[b_j * 24 + 16], &DifAndCtrl_B->coeffMat[b_j <<
           3], sizeof(real_T) << 3U);
  }

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  obj->PPStruct.breaks[0] = timeData[0] - 1.0;
  obj->PPStruct.breaks[1] = timeData[0];
  obj->PPStruct.breaks[2] = timeData[1];
  obj->PPStruct.breaks[3] = timeData[1] + 1.0;
  for (b_j = 0; b_j < 96; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    obj->PPStruct.coefs[b_j] = obj->PPDStruct.coefs[b_j];
    obj->PPDStruct.coefs[b_j] = 0.0;
  }

  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 24; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      obj->PPDStruct.coefs[b_j + 24 * (b_i + 1)] = obj->PPStruct.coefs[b_i * 24
        + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  memset(&obj->PPDDStruct.coefs[0], 0, 96U * sizeof(real_T));
  for (b_i = 0; b_i < 3; b_i++) {
    for (b_j = 0; b_j < 24; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      obj->PPDDStruct.coefs[b_j + 24 * (b_i + 1)] = obj->PPDStruct.coefs[b_i *
        24 + b_j] * (3.0 - static_cast<real_T>(b_i));
    }
  }

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  obj->PPDStruct.breaks[0] = obj->PPStruct.breaks[0];
  obj->PPDDStruct.breaks[0] = obj->PPStruct.breaks[0];
  obj->PPDStruct.breaks[1] = obj->PPStruct.breaks[1];
  obj->PPDDStruct.breaks[1] = obj->PPStruct.breaks[1];
  obj->PPDStruct.breaks[2] = obj->PPStruct.breaks[2];
  obj->PPDDStruct.breaks[2] = obj->PPStruct.breaks[2];
  obj->PPDStruct.breaks[3] = obj->PPStruct.breaks[3];
  obj->PPDDStruct.breaks[3] = obj->PPStruct.breaks[3];
  obj->PPFormUpdatedNeeded = false;
}

static void DifAndCtrl_ppval(const real_T pp_breaks[4], const real_T pp_coefs[96],
  real_T x, real_T v[8])
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
    high_i = 4;
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
      high_i = ((low_i + 1) * 24 + low_ip1) - 1;
      for (mid_i = 0; mid_i < 8; mid_i++) {
        v[mid_i] = pp_coefs[(high_i + mid_i) + 1] + xloc * v[mid_i];
      }
    }
  }

  // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
}

// Model step function
void DifAndCtrl_step(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M,
                     ExtU_DifAndCtrl_T *DifAndCtrl_U, ExtY_DifAndCtrl_T
                     *DifAndCtrl_Y)
{
  B_DifAndCtrl_T *DifAndCtrl_B = DifAndCtrl_M->blockIO;
  DW_DifAndCtrl_T *DifAndCtrl_DW = DifAndCtrl_M->dwork;
  X_DifAndCtrl_T *DifAndCtrl_X = DifAndCtrl_M->contStates;
  real_T tmp;
  int32_T i;
  int32_T jA;
  int32_T n;
  int8_T ipiv;
  boolean_T exitg1;
  boolean_T propChange;
  if (DifAndCtrl_M->isMajorTimeStep()) {
    // set solver stop time
    rtsiSetSolverStopTime(&DifAndCtrl_M->solverInfo,
                          ((DifAndCtrl_M->Timing.clockTick0+1)*
      DifAndCtrl_M->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (DifAndCtrl_M->isMinorTimeStep()) {
    DifAndCtrl_M->Timing.t[0] = rtsiGetT(&DifAndCtrl_M->solverInfo);
  }

  // MATLAB Function: '<S2>/GetBInvMatrix' incorporates:
  //   Integrator: '<S4>/Integrator'
  //   MATLAB Function: '<S9>/MATLAB Function1'

  DifAndCtrl_B->Clock2 = cos(DifAndCtrl_X->Integrator_CSTATE[5]);
  DifAndCtrl_B->x_tmp = sin(DifAndCtrl_X->Integrator_CSTATE[3]);
  DifAndCtrl_B->x_tmp_c = sin(DifAndCtrl_X->Integrator_CSTATE[5]);
  DifAndCtrl_B->x_tmp_b = cos(DifAndCtrl_X->Integrator_CSTATE[3]);
  DifAndCtrl_B->x_tmp_p = sin(DifAndCtrl_X->Integrator_CSTATE[4]);
  DifAndCtrl_B->x_tmp_cv = cos(DifAndCtrl_X->Integrator_CSTATE[4]);
  DifAndCtrl_B->smax = tan(DifAndCtrl_X->Integrator_CSTATE[4]);
  memset(&DifAndCtrl_B->ginv[0], 0, sizeof(real_T) << 6U);
  memset(&DifAndCtrl_B->BMinv[0], 0, sizeof(real_T) << 6U);
  DifAndCtrl_B->ginv[0] = DifAndCtrl_B->Clock2 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->rtb_ginv_tmp_tmp = DifAndCtrl_B->Clock2 * DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_g = -DifAndCtrl_B->x_tmp_b *
    DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->rtb_ginv_tmp_a = DifAndCtrl_B->rtb_ginv_tmp_tmp *
    DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->rtb_ginv_tmp_tmp_g;
  DifAndCtrl_B->ginv[8] = DifAndCtrl_B->rtb_ginv_tmp_a;
  DifAndCtrl_B->rtb_ginv_tmp_i = DifAndCtrl_B->x_tmp * DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->rtb_ginv_tmp_o = DifAndCtrl_B->x_tmp_b * DifAndCtrl_B->Clock2;
  DifAndCtrl_B->rtb_ginv_tmp_p = DifAndCtrl_B->rtb_ginv_tmp_o *
    DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->rtb_ginv_tmp_i;
  DifAndCtrl_B->ginv[16] = DifAndCtrl_B->rtb_ginv_tmp_p;
  DifAndCtrl_B->ginv[24] = 0.0;
  DifAndCtrl_B->ginv[32] = 0.0;
  DifAndCtrl_B->ginv[40] = 0.0;
  DifAndCtrl_B->ginv[1] = DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->rtb_ginv_tmp_i = DifAndCtrl_B->rtb_ginv_tmp_i *
    DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->rtb_ginv_tmp_o;
  DifAndCtrl_B->ginv[9] = DifAndCtrl_B->rtb_ginv_tmp_i;
  DifAndCtrl_B->rtb_ginv_tmp_o = DifAndCtrl_B->x_tmp_b * DifAndCtrl_B->x_tmp_c *
    DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->rtb_ginv_tmp_o2 = -DifAndCtrl_B->Clock2 * DifAndCtrl_B->x_tmp +
    DifAndCtrl_B->rtb_ginv_tmp_o;
  DifAndCtrl_B->ginv[17] = DifAndCtrl_B->rtb_ginv_tmp_o2;
  DifAndCtrl_B->ginv[25] = 0.0;
  DifAndCtrl_B->ginv[33] = 0.0;
  DifAndCtrl_B->ginv[41] = 0.0;
  DifAndCtrl_B->ginv[2] = -DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->ginv[10] = DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->ginv[18] = DifAndCtrl_B->x_tmp_b * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->ginv[26] = 0.0;
  DifAndCtrl_B->ginv[34] = 0.0;
  DifAndCtrl_B->ginv[42] = 0.0;
  DifAndCtrl_B->ginv[3] = 0.0;
  DifAndCtrl_B->ginv[11] = 0.0;
  DifAndCtrl_B->ginv[19] = 0.0;
  DifAndCtrl_B->ginv[27] = 1.0;
  DifAndCtrl_B->ginv[35] = DifAndCtrl_B->x_tmp * DifAndCtrl_B->smax;
  DifAndCtrl_B->ginv[43] = DifAndCtrl_B->x_tmp_b * DifAndCtrl_B->smax;
  DifAndCtrl_B->ginv[4] = 0.0;
  DifAndCtrl_B->ginv[12] = 0.0;
  DifAndCtrl_B->ginv[20] = 0.0;
  DifAndCtrl_B->ginv[28] = 0.0;
  DifAndCtrl_B->ginv[36] = DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->ginv[44] = -DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->ginv[5] = 0.0;
  DifAndCtrl_B->ginv[13] = 0.0;
  DifAndCtrl_B->ginv[21] = 0.0;
  DifAndCtrl_B->ginv[29] = 0.0;
  DifAndCtrl_B->rtb_ginv_tmp_n = 1.0 / DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->ginv[37] = DifAndCtrl_B->rtb_ginv_tmp_n * DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->ginv[45] = DifAndCtrl_B->rtb_ginv_tmp_n * DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->ginv[54] = 1.0;
  DifAndCtrl_B->ginv[55] = 0.0;
  DifAndCtrl_B->ginv[62] = 0.0;
  DifAndCtrl_B->ginv[63] = 1.0;
  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    DifAndCtrl_B->ipiv[DifAndCtrl_B->c_j] = static_cast<int8_T>
      (DifAndCtrl_B->c_j + 1);
  }

  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 7; DifAndCtrl_B->c_j++) {
    DifAndCtrl_B->jj = DifAndCtrl_B->c_j * 9;
    n = 9 - DifAndCtrl_B->c_j;
    DifAndCtrl_B->a = 0;
    DifAndCtrl_B->smax = fabs(DifAndCtrl_B->ginv[DifAndCtrl_B->jj]);
    for (i = 2; i < n; i++) {
      DifAndCtrl_B->s = fabs(DifAndCtrl_B->ginv[(DifAndCtrl_B->jj + i) - 1]);
      if (DifAndCtrl_B->s > DifAndCtrl_B->smax) {
        DifAndCtrl_B->a = i - 1;
        DifAndCtrl_B->smax = DifAndCtrl_B->s;
      }
    }

    if (DifAndCtrl_B->ginv[DifAndCtrl_B->jj + DifAndCtrl_B->a] != 0.0) {
      if (DifAndCtrl_B->a != 0) {
        n = DifAndCtrl_B->c_j + DifAndCtrl_B->a;
        DifAndCtrl_B->ipiv[DifAndCtrl_B->c_j] = static_cast<int8_T>(n + 1);
        for (i = 0; i < 8; i++) {
          jA = i << 3;
          DifAndCtrl_B->a = jA + DifAndCtrl_B->c_j;
          DifAndCtrl_B->smax = DifAndCtrl_B->ginv[DifAndCtrl_B->a];
          jA += n;
          DifAndCtrl_B->ginv[DifAndCtrl_B->a] = DifAndCtrl_B->ginv[jA];
          DifAndCtrl_B->ginv[jA] = DifAndCtrl_B->smax;
        }
      }

      n = (DifAndCtrl_B->jj - DifAndCtrl_B->c_j) + 8;
      for (i = DifAndCtrl_B->jj + 2; i <= n; i++) {
        DifAndCtrl_B->ginv[i - 1] /= DifAndCtrl_B->ginv[DifAndCtrl_B->jj];
      }
    }

    DifAndCtrl_B->a = 6 - DifAndCtrl_B->c_j;
    jA = DifAndCtrl_B->jj + 10;
    for (i = 0; i <= DifAndCtrl_B->a; i++) {
      DifAndCtrl_B->D17 = DifAndCtrl_B->ginv[((i << 3) + DifAndCtrl_B->jj) + 8];
      if (DifAndCtrl_B->D17 != 0.0) {
        DifAndCtrl_B->kAcol = (jA - DifAndCtrl_B->c_j) + 6;
        for (n = jA; n <= DifAndCtrl_B->kAcol; n++) {
          DifAndCtrl_B->ginv[n - 1] += DifAndCtrl_B->ginv[((DifAndCtrl_B->jj + n)
            - jA) + 1] * -DifAndCtrl_B->D17;
        }
      }

      jA += 8;
    }
  }

  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    DifAndCtrl_B->p[DifAndCtrl_B->c_j] = static_cast<int8_T>(DifAndCtrl_B->c_j +
      1);
  }

  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 7; DifAndCtrl_B->c_j++) {
    ipiv = DifAndCtrl_B->ipiv[DifAndCtrl_B->c_j];
    if (ipiv > DifAndCtrl_B->c_j + 1) {
      DifAndCtrl_B->jj = DifAndCtrl_B->p[ipiv - 1];
      DifAndCtrl_B->p[ipiv - 1] = DifAndCtrl_B->p[DifAndCtrl_B->c_j];
      DifAndCtrl_B->p[DifAndCtrl_B->c_j] = static_cast<int8_T>(DifAndCtrl_B->jj);
    }
  }

  for (n = 0; n < 8; n++) {
    DifAndCtrl_B->jj = (DifAndCtrl_B->p[n] - 1) << 3;
    DifAndCtrl_B->BMinv[n + DifAndCtrl_B->jj] = 1.0;
    for (DifAndCtrl_B->a = n + 1; DifAndCtrl_B->a < 9; DifAndCtrl_B->a++) {
      DifAndCtrl_B->c_j = (DifAndCtrl_B->jj + DifAndCtrl_B->a) - 1;
      if (DifAndCtrl_B->BMinv[DifAndCtrl_B->c_j] != 0.0) {
        for (i = DifAndCtrl_B->a + 1; i < 9; i++) {
          jA = (DifAndCtrl_B->jj + i) - 1;
          DifAndCtrl_B->BMinv[jA] -= DifAndCtrl_B->ginv[(((DifAndCtrl_B->a - 1) <<
            3) + i) - 1] * DifAndCtrl_B->BMinv[DifAndCtrl_B->c_j];
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    jA = i << 3;
    for (n = 7; n >= 0; n--) {
      DifAndCtrl_B->kAcol = n << 3;
      DifAndCtrl_B->c_j = n + jA;
      DifAndCtrl_B->D17 = DifAndCtrl_B->BMinv[DifAndCtrl_B->c_j];
      if (DifAndCtrl_B->D17 != 0.0) {
        DifAndCtrl_B->BMinv[DifAndCtrl_B->c_j] = DifAndCtrl_B->D17 /
          DifAndCtrl_B->ginv[n + DifAndCtrl_B->kAcol];
        for (DifAndCtrl_B->a = 0; DifAndCtrl_B->a < n; DifAndCtrl_B->a++) {
          DifAndCtrl_B->jj = DifAndCtrl_B->a + jA;
          DifAndCtrl_B->BMinv[DifAndCtrl_B->jj] -= DifAndCtrl_B->
            ginv[DifAndCtrl_B->a + DifAndCtrl_B->kAcol] * DifAndCtrl_B->
            BMinv[DifAndCtrl_B->c_j];
        }
      }
    }
  }

  // End of MATLAB Function: '<S2>/GetBInvMatrix'

  // MATLAB Function: '<S9>/MATLAB Function1' incorporates:
  //   Integrator: '<S4>/Integrator'
  //   Integrator: '<S4>/Integrator1'

  DifAndCtrl_B->smax = sin(DifAndCtrl_X->Integrator_CSTATE[6]);
  DifAndCtrl_B->D14_tmp = cos(DifAndCtrl_X->Integrator_CSTATE[7]);
  DifAndCtrl_B->s = sin(DifAndCtrl_X->Integrator_CSTATE[7]);
  DifAndCtrl_B->D14_tmp_tmp = DifAndCtrl_X->Integrator_CSTATE[6] +
    DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->D14_tmp_f = sin(DifAndCtrl_B->D14_tmp_tmp);
  DifAndCtrl_B->D14_tmp_g = cos(DifAndCtrl_X->Integrator_CSTATE[6]);
  DifAndCtrl_B->D14_tmp_g1 = cos(DifAndCtrl_B->D14_tmp_tmp);
  DifAndCtrl_B->D14_tmp_m = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D14_tmp_tmp_p = DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D14_tmp_c = DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 + DifAndCtrl_B->D14_tmp_tmp_p;
  DifAndCtrl_B->D14_tmp_md = DifAndCtrl_P.ArmConstants.Mass1 +
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D14_tmp_m3 = DifAndCtrl_B->D14_tmp_m * DifAndCtrl_B->D14_tmp +
    DifAndCtrl_B->D14_tmp_c;
  DifAndCtrl_B->D14_tmp_j = DifAndCtrl_B->D14_tmp_md *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L;
  DifAndCtrl_B->D14_tmp_h = DifAndCtrl_B->D14_tmp_m * DifAndCtrl_B->D14_tmp_g1;
  DifAndCtrl_B->D14_tmp_tmp_pm = DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->smax;
  DifAndCtrl_B->D14_tmp_tmp_p2 = DifAndCtrl_B->D14_tmp_m *
    DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->D14_tmp_c0 = DifAndCtrl_B->D14_tmp_tmp_pm +
    DifAndCtrl_B->D14_tmp_tmp_p2;
  DifAndCtrl_B->D14_tmp_ct = DifAndCtrl_B->D14_tmp_c0 * DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->D14_tmp_i = DifAndCtrl_B->D14_tmp_m3 * DifAndCtrl_B->Clock2;
  DifAndCtrl_B->D14_tmp_my = DifAndCtrl_B->D14_tmp_m * DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->D14_tmp_jg = DifAndCtrl_B->D14_tmp_m * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->s * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D14_tmp_mv = (-DifAndCtrl_B->D14_tmp_m3 * DifAndCtrl_B->x_tmp_c
    + DifAndCtrl_B->D14_tmp_jg) * DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->D14_tmp_cf = DifAndCtrl_B->D14_tmp_md *
    -DifAndCtrl_P.ArmConstants.Hexa_to_joint_L;
  DifAndCtrl_B->D14 = (((DifAndCtrl_B->D14_tmp_my * DifAndCtrl_B->smax *
    DifAndCtrl_B->s + DifAndCtrl_B->D14_tmp_cf * DifAndCtrl_B->x_tmp_c) +
                        DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->smax *
                        DifAndCtrl_B->x_tmp_p) * DifAndCtrl_B->x_tmp_b +
                       ((DifAndCtrl_B->D14_tmp_j + DifAndCtrl_B->D14_tmp_h) *
                        DifAndCtrl_B->Clock2 * DifAndCtrl_B->x_tmp_p +
                        DifAndCtrl_B->D14_tmp_ct) * DifAndCtrl_B->x_tmp) +
    (DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->Clock2 * DifAndCtrl_B->x_tmp *
     DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->D14_tmp_mv) * DifAndCtrl_B->D14_tmp_g;
  DifAndCtrl_B->D15_tmp_tmp = DifAndCtrl_X->Integrator_CSTATE[3] +
    DifAndCtrl_X->Integrator_CSTATE[6];
  DifAndCtrl_B->D15_tmp = cos(DifAndCtrl_B->D15_tmp_tmp);
  DifAndCtrl_B->D15_tmp_tmp_i = DifAndCtrl_B->D15_tmp_tmp +
    DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->D15_tmp_m = cos(DifAndCtrl_B->D15_tmp_tmp_i);
  DifAndCtrl_B->D15_tmp_tmp_c = DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->D15_tmp;
  DifAndCtrl_B->D15_tmp_tmp_f = DifAndCtrl_B->D14_tmp_m *
    DifAndCtrl_B->D15_tmp_m;
  DifAndCtrl_B->D15_tmp_i = (DifAndCtrl_B->D14_tmp_j * DifAndCtrl_B->x_tmp_b +
    DifAndCtrl_B->D15_tmp_tmp_c) + DifAndCtrl_B->D15_tmp_tmp_f;
  DifAndCtrl_B->D15 = DifAndCtrl_B->D15_tmp_i * -DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->D16_tmp_tmp = DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->D14_tmp_g;
  DifAndCtrl_B->D16_tmp = (DifAndCtrl_B->D16_tmp_tmp + DifAndCtrl_B->D14_tmp_j)
    + DifAndCtrl_B->D14_tmp_h;
  DifAndCtrl_B->D16_tmp_m = DifAndCtrl_B->D16_tmp * DifAndCtrl_B->Clock2;
  DifAndCtrl_B->D16_tmp_j = DifAndCtrl_B->D16_tmp * DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->D16_tmp_f = DifAndCtrl_B->D16_tmp_j * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D16_tmp_a = DifAndCtrl_B->D14_tmp_ct * DifAndCtrl_B->x_tmp_p +
    DifAndCtrl_B->D16_tmp_m;
  DifAndCtrl_B->D16 = (DifAndCtrl_B->D14_tmp_c0 * -DifAndCtrl_B->Clock2 +
                       DifAndCtrl_B->D16_tmp_f) * DifAndCtrl_B->x_tmp_b +
    DifAndCtrl_B->D16_tmp_a * -DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->D17_tmp = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->D17_tmp_e = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_B->D14_tmp_g1;
  DifAndCtrl_B->D17_tmp_a = DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_B->D14_tmp_g;
  DifAndCtrl_B->D17_tmp_as = DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_B->smax + DifAndCtrl_B->D17_tmp;
  DifAndCtrl_B->D17_tmp_o = DifAndCtrl_B->D17_tmp_as *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D17_tmp_j = DifAndCtrl_B->D17_tmp_a + DifAndCtrl_B->D17_tmp_e;
  DifAndCtrl_B->D17_tmp_tmp = DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->smax;
  DifAndCtrl_B->D17_tmp_tmp_l = DifAndCtrl_B->Clock2 * DifAndCtrl_B->D14_tmp_g;
  DifAndCtrl_B->D17_tmp_p = DifAndCtrl_B->D17_tmp_tmp_l * DifAndCtrl_B->x_tmp_p
    + DifAndCtrl_B->D17_tmp_tmp;
  DifAndCtrl_B->D17_tmp_ob = DifAndCtrl_B->Clock2 * DifAndCtrl_B->smax *
    DifAndCtrl_B->x_tmp_p + -DifAndCtrl_B->D14_tmp_g * DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->D17 = ((DifAndCtrl_B->D14_tmp_tmp_p * DifAndCtrl_B->x_tmp *
                        DifAndCtrl_B->D17_tmp_p + DifAndCtrl_B->D17_tmp_o *
                        DifAndCtrl_B->rtb_ginv_tmp_p) + DifAndCtrl_B->D17_tmp_j *
                       DifAndCtrl_P.ArmConstants.Mass2 *
                       DifAndCtrl_B->rtb_ginv_tmp_a) +
    DifAndCtrl_B->D14_tmp_tmp_p * DifAndCtrl_B->x_tmp_b *
    DifAndCtrl_B->D17_tmp_ob;
  DifAndCtrl_B->D18_tmp = DifAndCtrl_B->rtb_ginv_tmp_p * DifAndCtrl_B->D17_tmp +
    DifAndCtrl_B->rtb_ginv_tmp_a * DifAndCtrl_B->D17_tmp_e;
  DifAndCtrl_B->D18 = DifAndCtrl_B->D18_tmp * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D24_tmp = DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_B->D14_tmp_g + DifAndCtrl_P.ArmConstants.Hexa_to_joint_L;
  DifAndCtrl_B->D24_tmp_l = (DifAndCtrl_B->D17_tmp_a +
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L) + DifAndCtrl_B->D17_tmp_e;
  DifAndCtrl_B->D24_tmp_o = DifAndCtrl_B->rtb_ginv_tmp_a *
    DifAndCtrl_B->D17_tmp_as;
  DifAndCtrl_B->D17_tmp_a = DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->D24_tmp_h = DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
    DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->D24_tmp_d = (DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_B->D15_tmp + DifAndCtrl_B->D24_tmp_h) +
    DifAndCtrl_P.ArmConstants.MC2 * DifAndCtrl_B->D15_tmp_m;
  DifAndCtrl_B->D24 = (((DifAndCtrl_B->D24_tmp * DifAndCtrl_B->x_tmp_c *
    DifAndCtrl_B->x_tmp_p + -DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_B->Clock2 * DifAndCtrl_B->smax) *
                        (DifAndCtrl_P.ArmConstants.Mass1 * DifAndCtrl_B->x_tmp)
                        + DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->Clock2
                        * DifAndCtrl_B->D24_tmp_d * DifAndCtrl_B->D17_tmp_a) +
                       (DifAndCtrl_P.ArmConstants.MC1 * DifAndCtrl_B->x_tmp_c *
                        DifAndCtrl_B->smax * DifAndCtrl_B->x_tmp_p +
                        DifAndCtrl_B->D24_tmp * DifAndCtrl_B->Clock2) *
                       (DifAndCtrl_P.ArmConstants.Mass1 * DifAndCtrl_B->x_tmp_b))
    + (DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->rtb_ginv_tmp_p -
       DifAndCtrl_B->D24_tmp_o) * (DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->x_tmp_p);
  DifAndCtrl_B->D25 = -DifAndCtrl_B->D15_tmp_i * DifAndCtrl_B->x_tmp_cv *
    DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->D26 = ((DifAndCtrl_B->D24_tmp * -DifAndCtrl_P.ArmConstants.Mass1
                        * DifAndCtrl_B->rtb_ginv_tmp_p - DifAndCtrl_B->D24_tmp_l
                        * DifAndCtrl_P.ArmConstants.Mass2 *
                        DifAndCtrl_B->rtb_ginv_tmp_p) +
                       DifAndCtrl_B->D14_tmp_tmp_p * DifAndCtrl_B->smax *
                       DifAndCtrl_B->rtb_ginv_tmp_a) + DifAndCtrl_B->D17_tmp_o *
    DifAndCtrl_B->rtb_ginv_tmp_a;
  DifAndCtrl_B->D14_tmp_tmp_p = DifAndCtrl_B->rtb_ginv_tmp_tmp -
    DifAndCtrl_B->rtb_ginv_tmp_o;
  DifAndCtrl_B->D27_tmp = DifAndCtrl_B->D16_tmp_tmp *
    DifAndCtrl_B->rtb_ginv_tmp_i;
  DifAndCtrl_B->D27_tmp_n = DifAndCtrl_B->rtb_ginv_tmp_i *
    DifAndCtrl_B->D14_tmp_h;
  DifAndCtrl_B->D27 = (-DifAndCtrl_B->D14_tmp_c0 * DifAndCtrl_B->D14_tmp_tmp_p +
                       DifAndCtrl_B->D27_tmp) + DifAndCtrl_B->D27_tmp_n;
  DifAndCtrl_B->D17_tmp = DifAndCtrl_B->rtb_ginv_tmp_o2 * DifAndCtrl_B->D17_tmp
    + DifAndCtrl_B->rtb_ginv_tmp_i * DifAndCtrl_B->D17_tmp_e;
  DifAndCtrl_B->D28 = DifAndCtrl_B->D17_tmp * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D17_tmp_e = sin(DifAndCtrl_B->D15_tmp_tmp);
  DifAndCtrl_B->D17_tmp_o = sin(DifAndCtrl_B->D15_tmp_tmp_i);
  DifAndCtrl_B->D34_tmp = DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->D17_tmp_e;
  DifAndCtrl_B->D34_tmp_f = DifAndCtrl_B->D14_tmp_m * DifAndCtrl_B->D17_tmp_o;
  DifAndCtrl_B->D34_tmp_e = (DifAndCtrl_B->D14_tmp_j * DifAndCtrl_B->x_tmp +
    DifAndCtrl_B->D34_tmp) + DifAndCtrl_B->D34_tmp_f;
  DifAndCtrl_B->D34 = DifAndCtrl_B->D34_tmp_e * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->D35 = DifAndCtrl_B->D15_tmp_i * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D37_tmp = DifAndCtrl_B->D34_tmp + DifAndCtrl_B->D34_tmp_f;
  DifAndCtrl_B->D37 = DifAndCtrl_B->D37_tmp * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->D38 = DifAndCtrl_B->D14_tmp_m * DifAndCtrl_B->x_tmp_cv *
    DifAndCtrl_B->D17_tmp_o;
  DifAndCtrl_B->D45_tmp = DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D15_tmp_m;
  DifAndCtrl_B->D45_tmp_e = DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D17_tmp_o;
  DifAndCtrl_B->D45 = ((DifAndCtrl_P.ArmConstants.Inertia1[7] *
                        DifAndCtrl_B->D15_tmp + DifAndCtrl_B->D45_tmp) +
                       DifAndCtrl_P.ArmConstants.Inertia1[6] *
                       DifAndCtrl_B->D17_tmp_e) + DifAndCtrl_B->D45_tmp_e;
  DifAndCtrl_B->D46_tmp_tmp_k = DifAndCtrl_X->Integrator_CSTATE[6] -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp = sin(DifAndCtrl_B->D46_tmp_tmp_k);
  DifAndCtrl_B->D46_tmp_tmp_hc = DifAndCtrl_X->Integrator_CSTATE[4] +
    DifAndCtrl_X->Integrator_CSTATE[6];
  DifAndCtrl_B->D46_tmp_n = sin(DifAndCtrl_B->D46_tmp_tmp_hc);
  DifAndCtrl_B->D46_tmp_tmp = DifAndCtrl_B->D15_tmp_tmp -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp_p = cos(DifAndCtrl_B->D46_tmp_tmp);
  DifAndCtrl_B->D46_tmp_tmp_i = DifAndCtrl_B->D15_tmp_tmp_i -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp_l = cos(DifAndCtrl_B->D46_tmp_tmp_i);
  DifAndCtrl_B->D46_tmp_tmp_f = DifAndCtrl_B->D15_tmp_tmp +
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp_j = cos(DifAndCtrl_B->D46_tmp_tmp_f);
  DifAndCtrl_B->D46_tmp_tmp_g = DifAndCtrl_B->D15_tmp_tmp_i +
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp_d = cos(DifAndCtrl_B->D46_tmp_tmp_g);
  DifAndCtrl_B->D46_tmp_g = sin(DifAndCtrl_B->D46_tmp_tmp);
  DifAndCtrl_B->D46_tmp_dy = sin(DifAndCtrl_B->D46_tmp_tmp_i);
  DifAndCtrl_B->D46_tmp_b = sin(DifAndCtrl_B->D46_tmp_tmp_f);
  DifAndCtrl_B->D46_tmp_ln = sin(DifAndCtrl_B->D46_tmp_tmp_g);
  DifAndCtrl_B->D46_tmp_tmp_p = DifAndCtrl_X->Integrator_CSTATE[7] -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->rtb_ginv_tmp_n = sin(DifAndCtrl_B->D46_tmp_tmp_p);
  DifAndCtrl_B->D46_tmp_tmp_b = DifAndCtrl_B->D14_tmp_tmp -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp_bn = sin(DifAndCtrl_B->D46_tmp_tmp_b);
  DifAndCtrl_B->D46_tmp_tmp_c = DifAndCtrl_X->Integrator_CSTATE[4] +
    DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->D46_tmp_da = sin(DifAndCtrl_B->D46_tmp_tmp_c);
  DifAndCtrl_B->D46_tmp_tmp_n = DifAndCtrl_B->D14_tmp_tmp +
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp_e = sin(DifAndCtrl_B->D46_tmp_tmp_n);
  DifAndCtrl_B->D46_tmp_c = 2.0 * DifAndCtrl_P.ArmConstants.MC2;
  DifAndCtrl_B->D46_tmp_tmp_h = DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L;
  DifAndCtrl_B->D46_tmp_o = DifAndCtrl_B->D46_tmp_tmp_h * -2.0;
  DifAndCtrl_B->D46_tmp_lm = -2.0 * DifAndCtrl_P.ArmConstants.MC2;
  DifAndCtrl_B->D46_tmp_m = DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_P.ArmConstants.MC1;
  DifAndCtrl_B->D46_tmp_mj = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.MC2;
  DifAndCtrl_B->D46_tmp_cn = DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.l1_dim;
  DifAndCtrl_B->D46_tmp_f = DifAndCtrl_B->D46_tmp_c *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_tmp_d = 2.0 * DifAndCtrl_P.ArmConstants.MC1;
  DifAndCtrl_B->D46_tmp_cs = DifAndCtrl_B->D46_tmp_tmp_d *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D46_tmp_tmp_ft = 2.0 * DifAndCtrl_P.ArmConstants.Hexa_to_joint_L;
  DifAndCtrl_B->D46_tmp_k = DifAndCtrl_B->D46_tmp_tmp_ft *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_p4 = DifAndCtrl_B->D46_tmp_c *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_tmp_m = DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D46_tmp_d;
  DifAndCtrl_B->D46_tmp_bb = ((-DifAndCtrl_P.ArmConstants.Inertia1[6] *
    DifAndCtrl_B->D46_tmp_p - DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D46_tmp_l) - DifAndCtrl_P.ArmConstants.Inertia1[6] *
    DifAndCtrl_B->D46_tmp_j) - DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->D46_tmp_a = DifAndCtrl_P.ArmConstants.Inertia1[7] *
    DifAndCtrl_B->D46_tmp_g;
  DifAndCtrl_B->D46_tmp_g2 = DifAndCtrl_B->D46_tmp_f *
    DifAndCtrl_B->rtb_ginv_tmp_n;
  DifAndCtrl_B->D46_tmp_ex = DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D46_tmp_dy;
  DifAndCtrl_B->D46_tmp_fi = -2.0 * DifAndCtrl_P.ArmConstants.Inertia1[8] *
    DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D46_tmp_h = -2.0 * DifAndCtrl_P.ArmConstants.Inertia2[8] *
    DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D46_tmp_tmp_j = DifAndCtrl_B->D46_tmp_m * -2.0;
  DifAndCtrl_B->D46_tmp_ei = DifAndCtrl_B->D46_tmp_tmp_j *
    DifAndCtrl_P.ArmConstants.Mass1 * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D46_tmp_tmp_kn = DifAndCtrl_B->D46_tmp_mj * -2.0;
  DifAndCtrl_B->D46_tmp_ch = DifAndCtrl_B->D46_tmp_tmp_kn *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D46_tmp_ax = DifAndCtrl_B->D46_tmp_cn * -2.0 *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D46_tmp_dau = DifAndCtrl_P.ArmConstants.Inertia1[7] *
    DifAndCtrl_B->D46_tmp_b;
  DifAndCtrl_B->D46_tmp_tmp_g4 = DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_af = DifAndCtrl_B->D46_tmp_tmp_g4 *
    DifAndCtrl_B->D46_tmp_da;
  DifAndCtrl_B->D46_tmp_pb = DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D46_tmp_ln;
  DifAndCtrl_B->D46_tmp_na = -2.0 * DifAndCtrl_P.ArmConstants.MC1;
  DifAndCtrl_B->D46_tmp_mx = DifAndCtrl_B->D46_tmp_na *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D46_tmp_pr = -2.0 * DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_dz = DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46 = ((((((((((((((((((((DifAndCtrl_B->D46_tmp_cs *
    DifAndCtrl_B->D46_tmp + DifAndCtrl_B->D46_tmp_bb) + DifAndCtrl_B->D46_tmp_k *
    DifAndCtrl_B->D46_tmp) + DifAndCtrl_B->D46_tmp_a) + DifAndCtrl_B->D46_tmp_g2)
    + DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->D46_tmp_bn) +
    DifAndCtrl_B->D46_tmp_ex) + DifAndCtrl_B->D46_tmp_fi) +
    DifAndCtrl_B->D46_tmp_h) + -2.0 * DifAndCtrl_P.HexaConstants.Inertia[0] *
    DifAndCtrl_B->x_tmp_p) + DifAndCtrl_B->D46_tmp_ei) + DifAndCtrl_B->D46_tmp_o
    * DifAndCtrl_P.ArmConstants.Mass1 * DifAndCtrl_B->x_tmp_p) +
    DifAndCtrl_B->D46_tmp_ch) + DifAndCtrl_B->D46_tmp_o *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_p) +
    DifAndCtrl_B->D46_tmp_ax) + DifAndCtrl_B->D46_tmp_mx *
    DifAndCtrl_B->D46_tmp_n) + DifAndCtrl_B->D46_tmp_pr *
    DifAndCtrl_B->D46_tmp_n) + DifAndCtrl_B->D46_tmp_dau) +
    DifAndCtrl_B->D46_tmp_af) + DifAndCtrl_B->D46_tmp_dz *
                        DifAndCtrl_B->D46_tmp_e) + DifAndCtrl_B->D46_tmp_pb) *
    0.5;
  DifAndCtrl_B->D47_tmp = DifAndCtrl_B->D46_tmp_mj *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D47_tmp_tmp = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_o = DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D14_tmp_g1;
  DifAndCtrl_B->D47_tmp_p = DifAndCtrl_B->D46_tmp_m *
    DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D47_tmp_px = DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D47_tmp_pt = DifAndCtrl_P.ArmConstants.Inertia1[8] +
    DifAndCtrl_P.ArmConstants.Inertia2[8];
  DifAndCtrl_B->D47_tmp_i = DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D14_tmp;
  DifAndCtrl_B->D47_tmp_m = ((DifAndCtrl_B->D47_tmp_p + DifAndCtrl_B->D47_tmp_pt)
    + DifAndCtrl_B->D47_tmp) + DifAndCtrl_B->D47_tmp_px;
  DifAndCtrl_B->D47_tmp_c = DifAndCtrl_B->D14_tmp_c *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L;
  DifAndCtrl_B->D47_tmp_n = DifAndCtrl_B->D47_tmp_c * DifAndCtrl_B->D14_tmp_g +
    DifAndCtrl_B->D47_tmp_m;
  DifAndCtrl_B->D47 = (DifAndCtrl_B->D47_tmp_n + DifAndCtrl_B->D47_tmp_i) +
    DifAndCtrl_B->D46_tmp_o;
  DifAndCtrl_B->D48_tmp = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D48_tmp_tmp = DifAndCtrl_B->D47_tmp +
    DifAndCtrl_P.ArmConstants.Inertia2[8];
  DifAndCtrl_B->D48_tmp_o = DifAndCtrl_B->D48_tmp * DifAndCtrl_B->D14_tmp +
    DifAndCtrl_B->D48_tmp_tmp;
  DifAndCtrl_B->D48 = DifAndCtrl_B->D48_tmp_o + DifAndCtrl_B->D46_tmp_o;
  DifAndCtrl_B->D56_tmp_tmp = 2.0 * DifAndCtrl_X->Integrator_CSTATE[3];
  DifAndCtrl_B->D56_tmp_tmp_a = DifAndCtrl_B->D56_tmp_tmp -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp = sin(DifAndCtrl_B->D56_tmp_tmp_a);
  DifAndCtrl_B->D56_tmp_tmp_e = DifAndCtrl_B->D56_tmp_tmp +
    DifAndCtrl_X->Integrator_CSTATE[6];
  DifAndCtrl_B->D56_tmp_tmp_c = DifAndCtrl_B->D56_tmp_tmp_e -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_l = sin(DifAndCtrl_B->D56_tmp_tmp_c);
  DifAndCtrl_B->D56_tmp_tmp_tmp = 2.0 * DifAndCtrl_X->Integrator_CSTATE[6];
  DifAndCtrl_B->D56_tmp_tmp_p = DifAndCtrl_B->D56_tmp_tmp +
    DifAndCtrl_B->D56_tmp_tmp_tmp;
  DifAndCtrl_B->D56_tmp_tmp_h = DifAndCtrl_B->D56_tmp_tmp_p -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_d = sin(DifAndCtrl_B->D56_tmp_tmp_h);
  DifAndCtrl_B->D56_tmp_tmp_o = 2.0 * DifAndCtrl_X->Integrator_CSTATE[7] +
    DifAndCtrl_B->D56_tmp_tmp_p;
  DifAndCtrl_B->D56_tmp_tmp_l = DifAndCtrl_B->D56_tmp_tmp_o -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_lx = sin(DifAndCtrl_B->D56_tmp_tmp_l);
  DifAndCtrl_B->D56_tmp_tmp_f = DifAndCtrl_B->D56_tmp_tmp +
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_o = sin(DifAndCtrl_B->D56_tmp_tmp_f);
  DifAndCtrl_B->D56_tmp_tmp_m = DifAndCtrl_B->D56_tmp_tmp_e +
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_n = sin(DifAndCtrl_B->D56_tmp_tmp_m);
  DifAndCtrl_B->D56_tmp_tmp_h2 = DifAndCtrl_B->D56_tmp_tmp_p +
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_b = sin(DifAndCtrl_B->D56_tmp_tmp_h2);
  DifAndCtrl_B->D56_tmp_tmp_o += DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_h = sin(DifAndCtrl_B->D56_tmp_tmp_o);
  DifAndCtrl_B->D56_tmp_bj = cos(DifAndCtrl_B->D56_tmp_tmp_h);
  DifAndCtrl_B->D56_tmp_j = cos(DifAndCtrl_B->D56_tmp_tmp_l);
  DifAndCtrl_B->D56_tmp_f = cos(DifAndCtrl_B->D56_tmp_tmp_h2);
  DifAndCtrl_B->D56_tmp_a = cos(DifAndCtrl_B->D56_tmp_tmp_o);
  DifAndCtrl_B->D56_tmp_tmp_h = DifAndCtrl_B->D56_tmp_tmp_e +
    DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->D56_tmp_tmp_o = DifAndCtrl_B->D56_tmp_tmp_h -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_ju = sin(DifAndCtrl_B->D56_tmp_tmp_o);
  DifAndCtrl_B->D56_tmp_tmp_p += DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->D56_tmp_tmp_l = DifAndCtrl_B->D56_tmp_tmp_p -
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_jz = sin(DifAndCtrl_B->D56_tmp_tmp_l);
  DifAndCtrl_B->D56_tmp_tmp_h2 = DifAndCtrl_B->D56_tmp_tmp_h +
    DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_o4 = sin(DifAndCtrl_B->D56_tmp_tmp_h2);
  DifAndCtrl_B->D56_tmp_tmp_p += DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_ny = sin(DifAndCtrl_B->D56_tmp_tmp_p);
  DifAndCtrl_B->D56_tmp_m = -2.0 * DifAndCtrl_P.ArmConstants.Inertia1[3];
  DifAndCtrl_B->D56_tmp_mc = -2.0 * DifAndCtrl_P.ArmConstants.Inertia2[3];
  DifAndCtrl_B->D56_tmp_ap = DifAndCtrl_B->D46_tmp_tmp_h *
    DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D56_tmp_jd = DifAndCtrl_B->D46_tmp_tmp_h *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D56_tmp_nj = 2.0 * DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->D56_tmp_k = 2.0 * DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->D56_tmp_n3 = -2.0 * DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->D56_tmp_oy = -2.0 * DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->D56_tmp_g = 2.0 * DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->D56_tmp_c = 2.0 * DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->D56_tmp_cj = -2.0 * DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->D56_tmp_m1 = -2.0 * DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->D56_tmp_tmp_k = DifAndCtrl_P.HexaConstants.Inertia[4] *
    DifAndCtrl_B->D56_tmp;
  DifAndCtrl_B->D56_tmp_tmp_j = DifAndCtrl_P.HexaConstants.Inertia[8] *
    DifAndCtrl_B->D56_tmp;
  DifAndCtrl_B->D56_tmp_tmp_fz = DifAndCtrl_B->D56_tmp_ap *
    DifAndCtrl_B->D56_tmp;
  DifAndCtrl_B->D56_tmp_tmp_cm = DifAndCtrl_B->D56_tmp_jd *
    DifAndCtrl_B->D56_tmp;
  DifAndCtrl_B->D56_tmp_tmp_fq = DifAndCtrl_P.ArmConstants.Inertia1[0] *
    DifAndCtrl_B->D56_tmp_d;
  DifAndCtrl_B->D56_tmp_tmp_n = DifAndCtrl_P.ArmConstants.Inertia1[4] *
    DifAndCtrl_B->D56_tmp_d;
  DifAndCtrl_B->D56_tmp_tmp_i = DifAndCtrl_B->D47_tmp_p *
    DifAndCtrl_B->D56_tmp_d;
  DifAndCtrl_B->D56_tmp_tmp_l4 = DifAndCtrl_B->D47_tmp_px *
    DifAndCtrl_B->D56_tmp_d;
  DifAndCtrl_B->D56_tmp_tmp_i3 = DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D56_tmp_lx;
  DifAndCtrl_B->D56_tmp_tmp_k1 = DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_B->D56_tmp_lx;
  DifAndCtrl_B->D56_tmp_tmp_fc = DifAndCtrl_B->D47_tmp *
    DifAndCtrl_B->D56_tmp_lx;
  DifAndCtrl_B->D56_tmp_tmp_al = DifAndCtrl_P.HexaConstants.Inertia[4] *
    DifAndCtrl_B->D56_tmp_o;
  DifAndCtrl_B->D56_tmp_tmp_d = DifAndCtrl_P.HexaConstants.Inertia[8] *
    DifAndCtrl_B->D56_tmp_o;
  DifAndCtrl_B->D56_tmp_tmp_ey = DifAndCtrl_B->D56_tmp_ap *
    DifAndCtrl_B->D56_tmp_o;
  DifAndCtrl_B->D56_tmp_tmp_eh = DifAndCtrl_P.ArmConstants.Inertia1[0] *
    DifAndCtrl_B->D56_tmp_b;
  DifAndCtrl_B->D56_tmp_tmp_b = DifAndCtrl_P.ArmConstants.Inertia1[4] *
    DifAndCtrl_B->D56_tmp_b;
  DifAndCtrl_B->D56_tmp_tmp_a0 = DifAndCtrl_B->D47_tmp_p *
    DifAndCtrl_B->D56_tmp_b;
  DifAndCtrl_B->D56_tmp_tmp_il = DifAndCtrl_B->D47_tmp_px *
    DifAndCtrl_B->D56_tmp_b;
  DifAndCtrl_B->D56_tmp =
    (((((((((((((((((((((((((((((((((((((DifAndCtrl_B->D56_tmp_cj *
    DifAndCtrl_B->D46_tmp_p + DifAndCtrl_B->D56_tmp_m * DifAndCtrl_B->D56_tmp_bj)
    + DifAndCtrl_B->D56_tmp_m1 * DifAndCtrl_B->D46_tmp_l) +
    DifAndCtrl_B->D56_tmp_mc * DifAndCtrl_B->D56_tmp_j) +
    DifAndCtrl_B->D56_tmp_g * DifAndCtrl_B->D46_tmp_j) + DifAndCtrl_B->D56_tmp_m
    * DifAndCtrl_B->D56_tmp_f) + DifAndCtrl_B->D56_tmp_c *
    DifAndCtrl_B->D46_tmp_d) + DifAndCtrl_B->D56_tmp_mc *
    DifAndCtrl_B->D56_tmp_a) + DifAndCtrl_B->D56_tmp_tmp_k) -
    DifAndCtrl_B->D56_tmp_tmp_j) + DifAndCtrl_B->D56_tmp_tmp_fz) +
    DifAndCtrl_B->D56_tmp_tmp_cm) + DifAndCtrl_B->D56_tmp_nj *
    DifAndCtrl_B->D46_tmp_g) + DifAndCtrl_B->D46_tmp_cs *
    DifAndCtrl_B->D56_tmp_l) + DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->D56_tmp_l)
    - DifAndCtrl_B->D56_tmp_tmp_fq) + DifAndCtrl_B->D56_tmp_tmp_n) +
    DifAndCtrl_B->D56_tmp_tmp_i) + DifAndCtrl_B->D56_tmp_tmp_l4) +
                       DifAndCtrl_B->D56_tmp_k * DifAndCtrl_B->D46_tmp_dy) +
                      DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->D56_tmp_ju) +
                     DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D56_tmp_jz) -
                    DifAndCtrl_B->D56_tmp_tmp_i3) + DifAndCtrl_B->D56_tmp_tmp_k1)
                  + DifAndCtrl_B->D56_tmp_tmp_fc) + DifAndCtrl_B->D56_tmp_tmp_al)
                - DifAndCtrl_B->D56_tmp_tmp_d) + DifAndCtrl_B->D56_tmp_tmp_ey) +
              DifAndCtrl_B->D56_tmp_jd * DifAndCtrl_B->D56_tmp_o) +
             DifAndCtrl_B->D56_tmp_n3 * DifAndCtrl_B->D46_tmp_b) +
            DifAndCtrl_B->D46_tmp_cs * DifAndCtrl_B->D56_tmp_n) +
           DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->D56_tmp_n) -
          DifAndCtrl_B->D56_tmp_tmp_eh) + DifAndCtrl_B->D56_tmp_tmp_b) +
        DifAndCtrl_B->D56_tmp_tmp_a0) + DifAndCtrl_B->D56_tmp_tmp_il) +
      DifAndCtrl_B->D56_tmp_oy * DifAndCtrl_B->D46_tmp_ln) +
     DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->D56_tmp_o4) +
    DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D56_tmp_ny;
  DifAndCtrl_B->D56_tmp_cx = DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_B->D56_tmp_h;
  DifAndCtrl_B->D56_tmp_i = DifAndCtrl_B->D47_tmp * DifAndCtrl_B->D56_tmp_h;
  DifAndCtrl_B->D56 = (((-DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D56_tmp_h + DifAndCtrl_B->D56_tmp) + DifAndCtrl_B->D56_tmp_cx)
                       + DifAndCtrl_B->D56_tmp_i) * 0.25;
  DifAndCtrl_B->D58 = DifAndCtrl_B->D45_tmp + DifAndCtrl_B->D45_tmp_e;
  DifAndCtrl_B->D45_tmp_e = DifAndCtrl_P.ArmConstants.MC1 * DifAndCtrl_B->smax;
  DifAndCtrl_B->D45_tmp = DifAndCtrl_B->rtb_ginv_tmp_p * -DifAndCtrl_B->D24_tmp
    + DifAndCtrl_B->rtb_ginv_tmp_a * DifAndCtrl_B->D45_tmp_e;
  DifAndCtrl_B->D24_tmp_o += -DifAndCtrl_B->D24_tmp_l *
    DifAndCtrl_B->rtb_ginv_tmp_p;
  DifAndCtrl_B->y_a = DifAndCtrl_B->D14_tmp_tmp_p * DifAndCtrl_B->D24_tmp +
    DifAndCtrl_B->rtb_ginv_tmp_i * DifAndCtrl_B->D45_tmp_e;
  DifAndCtrl_B->ab_a = DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->D14_tmp_tmp_p +
    DifAndCtrl_B->rtb_ginv_tmp_i * DifAndCtrl_B->D17_tmp_as;
  DifAndCtrl_B->D24_tmp = DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D24_tmp_l = DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_bn *= DifAndCtrl_B->D47_tmp_tmp;
  DifAndCtrl_B->D46_tmp_e *= DifAndCtrl_B->D47_tmp_tmp;
  DifAndCtrl_B->D67 = (((((((((((((((((DifAndCtrl_B->D24_tmp *
    DifAndCtrl_B->D46_tmp + DifAndCtrl_B->D46_tmp_bb) + DifAndCtrl_B->D24_tmp_l *
    DifAndCtrl_B->D46_tmp) + DifAndCtrl_B->D46_tmp_a) + DifAndCtrl_B->D46_tmp_g2)
    + DifAndCtrl_B->D46_tmp_bn) + DifAndCtrl_B->D46_tmp_ex) +
    DifAndCtrl_B->D46_tmp_fi) + DifAndCtrl_B->D46_tmp_h) +
    DifAndCtrl_B->D46_tmp_ei) + DifAndCtrl_B->D46_tmp_ch) +
    DifAndCtrl_B->D46_tmp_ax) - DifAndCtrl_B->D24_tmp * DifAndCtrl_B->D46_tmp_n)
    - DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->D46_tmp_n) +
    DifAndCtrl_B->D46_tmp_dau) + DifAndCtrl_B->D46_tmp_af) -
                        DifAndCtrl_B->D46_tmp_e) + DifAndCtrl_B->D46_tmp_pb) *
    0.5;
  DifAndCtrl_B->D46_tmp = -DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D68 = (((((((((-DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D46_tmp_l - DifAndCtrl_B->D46_tmp_tmp_m) +
    DifAndCtrl_B->D48_tmp * DifAndCtrl_B->rtb_ginv_tmp_n) +
    DifAndCtrl_B->D46_tmp_bn) + DifAndCtrl_B->D46_tmp_ex) +
    DifAndCtrl_B->D46_tmp_h) + DifAndCtrl_B->D46_tmp_ch) + DifAndCtrl_B->D46_tmp
    * DifAndCtrl_B->D46_tmp_da) - DifAndCtrl_B->D46_tmp_e) +
                       DifAndCtrl_B->D46_tmp_pb) * 0.5;
  DifAndCtrl_B->rtb_ginv_tmp_o = cos(DifAndCtrl_B->D56_tmp_tmp);
  DifAndCtrl_B->rtb_ginv_tmp_tmp_l = DifAndCtrl_B->D15_tmp_tmp * 2.0;
  DifAndCtrl_B->rtb_ginv_tmp_n = cos(DifAndCtrl_B->rtb_ginv_tmp_tmp_l);
  DifAndCtrl_B->D46_tmp_da = cos(DifAndCtrl_B->D56_tmp_tmp_e);
  DifAndCtrl_B->rtb_ginv_tmp_tmp_p = DifAndCtrl_B->D15_tmp_tmp_i * 2.0;
  DifAndCtrl_B->D46_tmp_tmp_m = cos(DifAndCtrl_B->rtb_ginv_tmp_tmp_p);
  DifAndCtrl_B->D46_tmp_ex = sin(DifAndCtrl_B->D56_tmp_tmp_tmp);
  DifAndCtrl_B->rtb_ginv_tmp_tmp_n = DifAndCtrl_B->D14_tmp_tmp * 2.0;
  DifAndCtrl_B->D46_tmp_h = cos(DifAndCtrl_B->rtb_ginv_tmp_tmp_n);
  DifAndCtrl_B->D46_tmp_ch = sin(DifAndCtrl_B->rtb_ginv_tmp_tmp_n);
  DifAndCtrl_B->rtb_ginv_tmp_tmp_n = 2.0 * DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D46_tmp_pb = sin(DifAndCtrl_B->rtb_ginv_tmp_tmp_n);
  DifAndCtrl_B->D46_tmp_n = sin(DifAndCtrl_B->rtb_ginv_tmp_tmp_l);
  DifAndCtrl_B->D46_tmp_bb = sin(DifAndCtrl_B->rtb_ginv_tmp_tmp_p);
  DifAndCtrl_B->rtb_ginv_tmp = cos(DifAndCtrl_B->D56_tmp_tmp_h);
  DifAndCtrl_B->rtb_ginv_tmp_tmp_l += DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->D46_tmp_a = cos(DifAndCtrl_B->rtb_ginv_tmp_tmp_l);
  DifAndCtrl_B->D56_tmp_tmp_tmp = cos(DifAndCtrl_B->D56_tmp_tmp_tmp);
  DifAndCtrl_B->D46_tmp_g2 = (DifAndCtrl_P.HexaConstants.Mass +
    DifAndCtrl_P.ArmConstants.Mass1) + DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->ginv[0] = DifAndCtrl_B->D46_tmp_g2;
  DifAndCtrl_B->ginv[8] = 0.0;
  DifAndCtrl_B->ginv[16] = 0.0;
  DifAndCtrl_B->ginv[24] = DifAndCtrl_B->D14;
  DifAndCtrl_B->ginv[32] = DifAndCtrl_B->D15;
  DifAndCtrl_B->ginv[40] = DifAndCtrl_B->D16;
  DifAndCtrl_B->ginv[48] = DifAndCtrl_B->D17;
  DifAndCtrl_B->ginv[56] = DifAndCtrl_B->D18;
  DifAndCtrl_B->ginv[1] = 0.0;
  DifAndCtrl_B->ginv[9] = DifAndCtrl_B->D46_tmp_g2;
  DifAndCtrl_B->ginv[17] = 0.0;
  DifAndCtrl_B->ginv[25] = DifAndCtrl_B->D24;
  DifAndCtrl_B->ginv[33] = DifAndCtrl_B->D25;
  DifAndCtrl_B->ginv[41] = DifAndCtrl_B->D26;
  DifAndCtrl_B->ginv[49] = DifAndCtrl_B->D27;
  DifAndCtrl_B->ginv[57] = DifAndCtrl_B->D28;
  DifAndCtrl_B->ginv[2] = 0.0;
  DifAndCtrl_B->ginv[10] = 0.0;
  DifAndCtrl_B->ginv[18] = DifAndCtrl_B->D46_tmp_g2;
  DifAndCtrl_B->ginv[26] = DifAndCtrl_B->D34;
  DifAndCtrl_B->ginv[34] = DifAndCtrl_B->D35;
  DifAndCtrl_B->ginv[42] = 0.0;
  DifAndCtrl_B->ginv[50] = DifAndCtrl_B->D37;
  DifAndCtrl_B->ginv[58] = DifAndCtrl_B->D38;
  DifAndCtrl_B->ginv[3] = DifAndCtrl_B->D14;
  DifAndCtrl_B->ginv[11] = DifAndCtrl_B->D24;
  DifAndCtrl_B->ginv[19] = DifAndCtrl_B->D34;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_p = DifAndCtrl_B->D14_tmp_c *
    DifAndCtrl_B->D46_tmp_tmp_ft;
  DifAndCtrl_B->rtb_ginv_tmp_ox = DifAndCtrl_B->rtb_ginv_tmp_tmp_p *
    DifAndCtrl_B->D14_tmp_g;
  DifAndCtrl_B->rtb_ginv_tmp_k = DifAndCtrl_B->D46_tmp_p4 *
    DifAndCtrl_B->D14_tmp_g1;
  DifAndCtrl_B->rtb_ginv_tmp_d = (((((DifAndCtrl_B->D47_tmp_pt +
    DifAndCtrl_P.HexaConstants.Inertia[0]) + DifAndCtrl_B->D47_tmp_p) +
    DifAndCtrl_B->D56_tmp_ap) + DifAndCtrl_B->D47_tmp) +
    DifAndCtrl_B->D56_tmp_jd) + DifAndCtrl_B->D47_tmp_px;
  DifAndCtrl_B->ginv[27] = ((DifAndCtrl_B->rtb_ginv_tmp_d +
    DifAndCtrl_B->rtb_ginv_tmp_ox) + DifAndCtrl_B->D47_tmp_i) +
    DifAndCtrl_B->rtb_ginv_tmp_k;
  DifAndCtrl_B->ginv[35] = DifAndCtrl_B->D45;
  DifAndCtrl_B->ginv[43] = DifAndCtrl_B->D46;
  DifAndCtrl_B->ginv[51] = DifAndCtrl_B->D47;
  DifAndCtrl_B->ginv[59] = DifAndCtrl_B->D48;
  DifAndCtrl_B->ginv[4] = DifAndCtrl_B->D15;
  DifAndCtrl_B->ginv[12] = DifAndCtrl_B->D25;
  DifAndCtrl_B->ginv[20] = DifAndCtrl_B->D35;
  DifAndCtrl_B->ginv[28] = DifAndCtrl_B->D45;
  DifAndCtrl_B->D15 = 2.0 * DifAndCtrl_P.ArmConstants.Inertia2[3];
  DifAndCtrl_B->D25 = 2.0 * DifAndCtrl_P.ArmConstants.Inertia1[3];
  DifAndCtrl_B->rtb_ginv_tmp_g = DifAndCtrl_P.ArmConstants.Inertia1[4] *
    DifAndCtrl_B->rtb_ginv_tmp_n;
  DifAndCtrl_B->rtb_ginv_tmp_l = DifAndCtrl_B->D47_tmp_p *
    DifAndCtrl_B->rtb_ginv_tmp_n;
  DifAndCtrl_B->rtb_ginv_tmp_f = DifAndCtrl_B->D47_tmp_px *
    DifAndCtrl_B->rtb_ginv_tmp_n;
  DifAndCtrl_B->D14 = DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->D24 = DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->D35 = DifAndCtrl_B->D47_tmp * DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->ginv[36] =
    ((((((((((((((((((((((((((((((DifAndCtrl_P.ArmConstants.Inertia1[0] +
    DifAndCtrl_P.ArmConstants.Inertia1[4]) + DifAndCtrl_P.ArmConstants.Inertia2
    [0]) + DifAndCtrl_P.ArmConstants.Inertia2[4]) +
    DifAndCtrl_P.HexaConstants.Inertia[4]) + DifAndCtrl_P.HexaConstants.Inertia
    [8]) + DifAndCtrl_B->D47_tmp_p) + DifAndCtrl_B->D56_tmp_ap) +
    DifAndCtrl_B->D47_tmp) + DifAndCtrl_B->D56_tmp_jd) +
    DifAndCtrl_B->D47_tmp_px) + DifAndCtrl_P.HexaConstants.Inertia[4] *
    DifAndCtrl_B->rtb_ginv_tmp_o) - DifAndCtrl_P.HexaConstants.Inertia[8] *
                       DifAndCtrl_B->rtb_ginv_tmp_o) + DifAndCtrl_B->D56_tmp_ap *
                      DifAndCtrl_B->rtb_ginv_tmp_o) + DifAndCtrl_B->D56_tmp_jd *
                     DifAndCtrl_B->rtb_ginv_tmp_o) +
                    DifAndCtrl_B->rtb_ginv_tmp_ox) +
                   -DifAndCtrl_P.ArmConstants.Inertia1[0] *
                   DifAndCtrl_B->rtb_ginv_tmp_n) + DifAndCtrl_B->rtb_ginv_tmp_g)
                 + DifAndCtrl_B->rtb_ginv_tmp_l) + DifAndCtrl_B->rtb_ginv_tmp_f)
               + DifAndCtrl_B->D46_tmp_cs * DifAndCtrl_B->D46_tmp_da) +
              DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->D46_tmp_da) +
             DifAndCtrl_B->D47_tmp_i) + DifAndCtrl_B->rtb_ginv_tmp_k) -
           DifAndCtrl_B->D14) + DifAndCtrl_B->D24) + DifAndCtrl_B->D35) +
        DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->rtb_ginv_tmp) +
       DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D46_tmp_a) + DifAndCtrl_B->D25 *
      DifAndCtrl_B->D46_tmp_n) + DifAndCtrl_B->D15 * DifAndCtrl_B->D46_tmp_bb) *
    0.5;
  DifAndCtrl_B->ginv[44] = DifAndCtrl_B->D56;
  DifAndCtrl_B->ginv[52] = DifAndCtrl_B->D45;
  DifAndCtrl_B->ginv[60] = DifAndCtrl_B->D58;
  DifAndCtrl_B->ginv[5] = DifAndCtrl_B->D16;
  DifAndCtrl_B->ginv[13] = DifAndCtrl_B->D26;
  DifAndCtrl_B->ginv[21] = 0.0;
  DifAndCtrl_B->ginv[29] = DifAndCtrl_B->D46;
  DifAndCtrl_B->ginv[37] = DifAndCtrl_B->D56;
  DifAndCtrl_B->D16 = DifAndCtrl_B->x_tmp_b * DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->D26 = DifAndCtrl_B->D14_tmp_g * DifAndCtrl_B->D14_tmp_g;
  DifAndCtrl_B->D46 = DifAndCtrl_B->smax * DifAndCtrl_B->smax;
  DifAndCtrl_B->D56 = DifAndCtrl_B->x_tmp * DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->D47_tmp_pt = DifAndCtrl_P.ArmConstants.Inertia2[0] +
    DifAndCtrl_P.ArmConstants.Inertia2[4];
  DifAndCtrl_B->D34 = -DifAndCtrl_P.ArmConstants.Inertia2[0] +
    DifAndCtrl_P.ArmConstants.Inertia2[4];
  DifAndCtrl_B->D46_tmp_fi = 2.0 * DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->rtb_ginv_tmp_ie = DifAndCtrl_B->D46_tmp_fi *
    DifAndCtrl_B->D17_tmp_a * DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->rtb_ginv_tmp_oc = DifAndCtrl_B->x_tmp_p * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D46_tmp_ei = DifAndCtrl_P.ArmConstants.Inertia1[6] *
    DifAndCtrl_B->D14_tmp_g - DifAndCtrl_P.ArmConstants.Inertia1[7] *
    DifAndCtrl_B->smax;
  DifAndCtrl_B->D46_tmp_ax = DifAndCtrl_P.ArmConstants.Inertia1[7] *
    DifAndCtrl_B->D14_tmp_g + DifAndCtrl_P.ArmConstants.Inertia1[6] *
    DifAndCtrl_B->smax;
  DifAndCtrl_B->D46_tmp_dau = DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D14_tmp_g1 - DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->D46_tmp_af = DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D14_tmp_g1 + DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->D46_tmp_e = DifAndCtrl_B->D26 *
    DifAndCtrl_P.ArmConstants.Inertia1[0];
  DifAndCtrl_B->D46_tmp_bn = DifAndCtrl_B->D46 *
    DifAndCtrl_P.ArmConstants.Inertia1[4];
  DifAndCtrl_B->D26 = (DifAndCtrl_B->D26 * DifAndCtrl_P.ArmConstants.Inertia1[4]
                       + DifAndCtrl_B->D46 * DifAndCtrl_P.ArmConstants.Inertia1
                       [0]) + DifAndCtrl_P.ArmConstants.Inertia1[3] *
    DifAndCtrl_B->D46_tmp_ex;
  DifAndCtrl_B->D45_tmp_e = DifAndCtrl_P.ArmConstants.Inertia2[0] -
    DifAndCtrl_P.ArmConstants.Inertia2[4];
  DifAndCtrl_B->D46 = (DifAndCtrl_B->D45_tmp_e * DifAndCtrl_B->D46_tmp_h +
                       DifAndCtrl_B->D47_tmp_pt) + DifAndCtrl_B->D56_tmp_mc *
    DifAndCtrl_B->D46_tmp_ch;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_pi = DifAndCtrl_B->D34 *
    DifAndCtrl_B->D46_tmp_h;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_a = DifAndCtrl_B->D15 *
    DifAndCtrl_B->D46_tmp_ch;
  DifAndCtrl_B->D47_tmp_pt = (DifAndCtrl_B->rtb_ginv_tmp_tmp_pi +
    DifAndCtrl_B->D47_tmp_pt) + DifAndCtrl_B->rtb_ginv_tmp_tmp_a;
  DifAndCtrl_B->rtb_ginv_tmp_c = DifAndCtrl_B->D16 *
    DifAndCtrl_P.HexaConstants.Inertia[8];
  DifAndCtrl_B->rtb_ginv_tmp_pw = DifAndCtrl_B->D17_tmp_a * DifAndCtrl_B->D56;
  DifAndCtrl_B->rtb_ginv_tmp_ow = DifAndCtrl_B->D16 * DifAndCtrl_B->D17_tmp_a;
  DifAndCtrl_B->ginv[45] =
    ((((((((((((((((((-DifAndCtrl_P.ArmConstants.Inertia1[0] +
                      DifAndCtrl_P.ArmConstants.Inertia1[4]) *
                     DifAndCtrl_B->D14_tmp_g * DifAndCtrl_B->smax +
                     -DifAndCtrl_P.ArmConstants.Inertia1[3] *
                     DifAndCtrl_B->D56_tmp_tmp_tmp) *
                    DifAndCtrl_B->rtb_ginv_tmp_ie + (DifAndCtrl_B->D17_tmp_a *
    DifAndCtrl_P.HexaConstants.Inertia[4] * DifAndCtrl_B->D56 +
    DifAndCtrl_B->rtb_ginv_tmp_c * DifAndCtrl_B->D17_tmp_a)) +
                   ((DifAndCtrl_B->D46_tmp_e + DifAndCtrl_B->D46_tmp_bn) +
                    -DifAndCtrl_P.ArmConstants.Inertia1[3] *
                    DifAndCtrl_B->D46_tmp_ex) * DifAndCtrl_B->rtb_ginv_tmp_ow) +
                  DifAndCtrl_B->D26 * DifAndCtrl_B->rtb_ginv_tmp_pw) +
                 DifAndCtrl_B->D16 * 0.5 * DifAndCtrl_B->D17_tmp_a *
                 DifAndCtrl_B->D46) + DifAndCtrl_B->D17_tmp_a * 0.5 *
                DifAndCtrl_B->D56 * DifAndCtrl_B->D47_tmp_pt) +
               (DifAndCtrl_B->D34 * 0.5 * DifAndCtrl_B->D46_tmp_ch +
                -DifAndCtrl_P.ArmConstants.Inertia2[3] * DifAndCtrl_B->D46_tmp_h)
               * DifAndCtrl_B->rtb_ginv_tmp_ie) + DifAndCtrl_B->rtb_ginv_tmp_oc *
              DifAndCtrl_P.ArmConstants.Inertia1[8]) +
             DifAndCtrl_B->rtb_ginv_tmp_oc * DifAndCtrl_P.ArmConstants.Inertia2
             [8]) + DifAndCtrl_B->rtb_ginv_tmp_oc *
            DifAndCtrl_P.HexaConstants.Inertia[0]) + DifAndCtrl_B->D45_tmp *
           DifAndCtrl_B->D45_tmp * DifAndCtrl_P.ArmConstants.Mass1) +
          DifAndCtrl_B->D24_tmp_o * DifAndCtrl_B->D24_tmp_o *
          DifAndCtrl_P.ArmConstants.Mass2) + DifAndCtrl_B->y_a *
         DifAndCtrl_B->y_a * DifAndCtrl_P.ArmConstants.Mass1) +
        DifAndCtrl_B->ab_a * DifAndCtrl_B->ab_a *
        DifAndCtrl_P.ArmConstants.Mass2) + DifAndCtrl_B->D46_tmp_ei *
       DifAndCtrl_B->x_tmp_b * DifAndCtrl_B->D46_tmp_pb) -
      DifAndCtrl_B->D46_tmp_ax * DifAndCtrl_B->x_tmp * DifAndCtrl_B->D46_tmp_pb)
     + DifAndCtrl_B->D46_tmp_dau * DifAndCtrl_B->x_tmp_b *
     DifAndCtrl_B->D46_tmp_pb) - DifAndCtrl_B->D46_tmp_af * DifAndCtrl_B->x_tmp *
    DifAndCtrl_B->D46_tmp_pb;
  DifAndCtrl_B->ginv[53] = DifAndCtrl_B->D67;
  DifAndCtrl_B->ginv[61] = DifAndCtrl_B->D68;
  DifAndCtrl_B->ginv[6] = DifAndCtrl_B->D17;
  DifAndCtrl_B->ginv[14] = DifAndCtrl_B->D27;
  DifAndCtrl_B->ginv[22] = DifAndCtrl_B->D37;
  DifAndCtrl_B->ginv[30] = DifAndCtrl_B->D47;
  DifAndCtrl_B->ginv[38] = DifAndCtrl_B->D45;
  DifAndCtrl_B->ginv[46] = DifAndCtrl_B->D67;
  DifAndCtrl_B->ginv[54] = DifAndCtrl_B->D47_tmp_m + DifAndCtrl_B->D47_tmp_i;
  DifAndCtrl_B->ginv[62] = DifAndCtrl_B->D48_tmp_o;
  DifAndCtrl_B->ginv[7] = DifAndCtrl_B->D18;
  DifAndCtrl_B->ginv[15] = DifAndCtrl_B->D28;
  DifAndCtrl_B->ginv[23] = DifAndCtrl_B->D38;
  DifAndCtrl_B->ginv[31] = DifAndCtrl_B->D48;
  DifAndCtrl_B->ginv[39] = DifAndCtrl_B->D58;
  DifAndCtrl_B->ginv[47] = DifAndCtrl_B->D68;
  DifAndCtrl_B->ginv[55] = DifAndCtrl_B->D48_tmp_o;
  DifAndCtrl_B->ginv[63] = DifAndCtrl_B->D48_tmp_tmp;
  DifAndCtrl_B->D17 = sin(DifAndCtrl_B->D56_tmp_tmp);
  DifAndCtrl_B->D18 = sin(DifAndCtrl_B->D56_tmp_tmp_e);
  DifAndCtrl_B->D27 = cos(DifAndCtrl_B->D56_tmp_tmp_c);
  DifAndCtrl_B->D56_tmp_tmp_f = cos(DifAndCtrl_B->D56_tmp_tmp_f);
  DifAndCtrl_B->D46_tmp_tmp_hc = cos(DifAndCtrl_B->D46_tmp_tmp_hc);
  DifAndCtrl_B->D56_tmp_tmp_m = cos(DifAndCtrl_B->D56_tmp_tmp_m);
  DifAndCtrl_B->D56_tmp_tmp_a = cos(DifAndCtrl_B->D56_tmp_tmp_a);
  DifAndCtrl_B->D46_tmp_tmp_k = cos(DifAndCtrl_B->D46_tmp_tmp_k);
  DifAndCtrl_B->D46_tmp_tmp_p = cos(DifAndCtrl_B->D46_tmp_tmp_p);
  DifAndCtrl_B->D46_tmp_tmp_b = cos(DifAndCtrl_B->D46_tmp_tmp_b);
  DifAndCtrl_B->D56_tmp_tmp_o = cos(DifAndCtrl_B->D56_tmp_tmp_o);
  DifAndCtrl_B->D56_tmp_tmp_l = cos(DifAndCtrl_B->D56_tmp_tmp_l);
  DifAndCtrl_B->D46_tmp_tmp_c = cos(DifAndCtrl_B->D46_tmp_tmp_c);
  DifAndCtrl_B->D46_tmp_tmp_n = cos(DifAndCtrl_B->D46_tmp_tmp_n);
  DifAndCtrl_B->D56_tmp_tmp_h2 = cos(DifAndCtrl_B->D56_tmp_tmp_h2);
  DifAndCtrl_B->D56_tmp_tmp_p = cos(DifAndCtrl_B->D56_tmp_tmp_p);
  DifAndCtrl_B->D56_tmp_tmp_c = sin(DifAndCtrl_B->D56_tmp_tmp_h);
  DifAndCtrl_B->D28 = sin(DifAndCtrl_B->rtb_ginv_tmp_tmp_l);
  DifAndCtrl_B->D37 = -2.0 * DifAndCtrl_X->Integrator_CSTATE[4];
  DifAndCtrl_B->D56_tmp_tmp_e = sin(DifAndCtrl_B->D56_tmp_tmp_e +
    DifAndCtrl_B->D37);
  DifAndCtrl_B->D46_tmp_tmp *= 2.0;
  DifAndCtrl_B->D38 = sin(DifAndCtrl_B->D46_tmp_tmp);
  DifAndCtrl_B->D46_tmp_tmp_i *= 2.0;
  DifAndCtrl_B->D47_tmp_m = sin(DifAndCtrl_B->D46_tmp_tmp_i);
  DifAndCtrl_B->D47 = sin((-DifAndCtrl_X->Integrator_CSTATE[3] +
    DifAndCtrl_X->Integrator_CSTATE[4]) * 2.0);
  DifAndCtrl_B->D48_tmp_tmp = (DifAndCtrl_X->Integrator_CSTATE[3] +
    DifAndCtrl_X->Integrator_CSTATE[4]) * 2.0;
  DifAndCtrl_B->D48_tmp_o = sin(DifAndCtrl_B->D48_tmp_tmp);
  DifAndCtrl_B->D46_tmp_tmp_f *= 2.0;
  DifAndCtrl_B->D56_tmp_tmp = sin(DifAndCtrl_B->D46_tmp_tmp_f);
  DifAndCtrl_B->D46_tmp_tmp_g *= 2.0;
  DifAndCtrl_B->D58 = sin(DifAndCtrl_B->D46_tmp_tmp_g);
  DifAndCtrl_B->y_a = sin(DifAndCtrl_B->D48_tmp_tmp +
    DifAndCtrl_X->Integrator_CSTATE[6]);
  DifAndCtrl_B->ab_a = DifAndCtrl_B->D15_tmp_tmp + DifAndCtrl_B->D37;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_l = cos(DifAndCtrl_B->ab_a);
  DifAndCtrl_B->D67 = DifAndCtrl_B->D15_tmp_tmp_i + DifAndCtrl_B->D37;
  DifAndCtrl_B->D68 = cos(DifAndCtrl_B->D67);
  DifAndCtrl_B->rtb_ginv_tmp_ie = cos(DifAndCtrl_B->D46_tmp_tmp);
  DifAndCtrl_B->D46_tmp_tmp_i = cos(DifAndCtrl_B->D46_tmp_tmp_i);
  DifAndCtrl_B->d = cos(DifAndCtrl_B->D46_tmp_tmp_f);
  DifAndCtrl_B->D46_tmp_tmp_g = cos(DifAndCtrl_B->D46_tmp_tmp_g);
  DifAndCtrl_B->D15_tmp_tmp += DifAndCtrl_B->rtb_ginv_tmp_tmp_n;
  DifAndCtrl_B->d1 = cos(DifAndCtrl_B->D15_tmp_tmp);
  DifAndCtrl_B->D15_tmp_tmp_i += DifAndCtrl_B->rtb_ginv_tmp_tmp_n;
  DifAndCtrl_B->d2 = cos(DifAndCtrl_B->D15_tmp_tmp_i);
  DifAndCtrl_B->D46_tmp_tmp = sin(DifAndCtrl_B->D46_tmp_tmp +
    DifAndCtrl_X->Integrator_CSTATE[7]);
  DifAndCtrl_B->d3 = sin(DifAndCtrl_B->D37 + DifAndCtrl_X->Integrator_CSTATE[6]);
  DifAndCtrl_B->ab_a = sin(DifAndCtrl_B->ab_a);
  DifAndCtrl_B->D67 = sin(DifAndCtrl_B->D67);
  DifAndCtrl_B->D56_tmp_tmp_h = sin(DifAndCtrl_B->D56_tmp_tmp_h +
    DifAndCtrl_B->D37);
  DifAndCtrl_B->d4 = sin((DifAndCtrl_X->Integrator_CSTATE[3] -
    DifAndCtrl_X->Integrator_CSTATE[4]) * 2.0);
  DifAndCtrl_B->d5 = sin(DifAndCtrl_B->rtb_ginv_tmp_tmp_n +
    DifAndCtrl_X->Integrator_CSTATE[6]);
  DifAndCtrl_B->D15_tmp_tmp = sin(DifAndCtrl_B->D15_tmp_tmp);
  DifAndCtrl_B->D15_tmp_tmp_i = sin(DifAndCtrl_B->D15_tmp_tmp_i);
  DifAndCtrl_B->D48_tmp_tmp = sin(DifAndCtrl_B->D48_tmp_tmp +
    DifAndCtrl_B->D14_tmp_tmp);
  DifAndCtrl_B->D46_tmp_tmp_f = sin(DifAndCtrl_B->D46_tmp_tmp_f +
    DifAndCtrl_X->Integrator_CSTATE[7]);
  DifAndCtrl_B->d6 = sin(DifAndCtrl_B->D37 + DifAndCtrl_X->Integrator_CSTATE[7]);
  DifAndCtrl_B->D37 = sin(DifAndCtrl_B->D14_tmp_tmp + DifAndCtrl_B->D37);
  DifAndCtrl_B->d7 = sin(DifAndCtrl_B->rtb_ginv_tmp_tmp_n +
    DifAndCtrl_X->Integrator_CSTATE[7]);
  DifAndCtrl_B->D14_tmp_tmp = sin(DifAndCtrl_B->D14_tmp_tmp +
    DifAndCtrl_B->rtb_ginv_tmp_tmp_n);
  DifAndCtrl_B->rtb_ginv_tmp_tmp_n = cos(DifAndCtrl_B->rtb_ginv_tmp_tmp_n);
  DifAndCtrl_B->D14_tmp_i = DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->x_tmp_p +
    DifAndCtrl_B->D14_tmp_my * DifAndCtrl_B->s;
  DifAndCtrl_B->D14_tmp_my = DifAndCtrl_B->D14_tmp_c0 * DifAndCtrl_B->Clock2;
  DifAndCtrl_B->d8 = 2.0 * DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->d9 = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[7] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D16_tmp_m = DifAndCtrl_B->D16_tmp_m * DifAndCtrl_B->x_tmp_p +
    DifAndCtrl_B->D14_tmp_ct;
  DifAndCtrl_B->d10 = DifAndCtrl_B->D16_tmp_m * DifAndCtrl_B->D46_tmp_fi;
  DifAndCtrl_B->d11 = DifAndCtrl_B->D14_tmp_my * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->d12 = 2.0 * DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->d13 = -2.0 * DifAndCtrl_X->Integrator1_CSTATE[6];
  DifAndCtrl_B->d166 = -2.0 * DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->D14_tmp_my = (DifAndCtrl_B->D14_tmp_my - DifAndCtrl_B->D16_tmp_f)
    * DifAndCtrl_B->d8 + DifAndCtrl_B->D16_tmp_a * DifAndCtrl_B->d166;
  DifAndCtrl_B->D16_tmp_f = ((DifAndCtrl_X->Integrator_CSTATE[3] -
    DifAndCtrl_X->Integrator_CSTATE[5]) + DifAndCtrl_X->Integrator_CSTATE[6]) +
    DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->D16_tmp_a = ((DifAndCtrl_X->Integrator_CSTATE[3] +
    DifAndCtrl_X->Integrator_CSTATE[5]) + DifAndCtrl_X->Integrator_CSTATE[6]) +
    DifAndCtrl_X->Integrator_CSTATE[7];
  DifAndCtrl_B->tmp_tmp = 2.0 * DifAndCtrl_X->Integrator1_CSTATE[6];
  DifAndCtrl_B->d19 = 2.0 * DifAndCtrl_B->Clock2;
  DifAndCtrl_B->dv[24] = -(((((((DifAndCtrl_B->D14_tmp_m3 *
    DifAndCtrl_B->x_tmp_c - DifAndCtrl_B->D14_tmp_jg) * DifAndCtrl_B->x_tmp +
    DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->x_tmp_b) * (DifAndCtrl_B->tmp_tmp *
    DifAndCtrl_B->D14_tmp_g) + ((DifAndCtrl_B->d19 * DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_B->x_tmp_p + (cos(DifAndCtrl_B->D16_tmp_f) - cos
    (DifAndCtrl_B->D16_tmp_a))) * DifAndCtrl_B->d9 + DifAndCtrl_B->d12 *
    DifAndCtrl_B->Clock2 * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D34_tmp_e)) +
    (DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->x_tmp + DifAndCtrl_B->D14_tmp_mv) *
    (DifAndCtrl_B->d13 * DifAndCtrl_B->smax)) + ((DifAndCtrl_B->D16_tmp_j -
    DifAndCtrl_B->d11) * DifAndCtrl_B->d8 + DifAndCtrl_B->d10) *
    DifAndCtrl_X->Integrator1_CSTATE[3]) + DifAndCtrl_B->D14_tmp_my *
    DifAndCtrl_X->Integrator1_CSTATE[5]) * 0.5);
  DifAndCtrl_B->dv[32] = -((((DifAndCtrl_B->D15_tmp_i *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_B->x_tmp_cv *
    DifAndCtrl_B->x_tmp_c + DifAndCtrl_B->d9 * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D17_tmp_o) +
    DifAndCtrl_X->Integrator1_CSTATE[6] * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D37_tmp) +
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D34_tmp_e) +
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->D15_tmp_i * DifAndCtrl_B->x_tmp_p);
  DifAndCtrl_B->D14_tmp_i = DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_X->Integrator1_CSTATE[7] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D14_tmp_m3 = -DifAndCtrl_B->D16_tmp * DifAndCtrl_B->x_tmp_c +
    DifAndCtrl_B->d11;
  DifAndCtrl_B->D14_tmp_jg = -2.0 * DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->dv[40] = -(((((((DifAndCtrl_B->rtb_ginv_tmp_tmp_g *
    DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->rtb_ginv_tmp_tmp) *
    -DifAndCtrl_B->D14_tmp_c0 + DifAndCtrl_B->D27_tmp) + DifAndCtrl_B->D27_tmp_n)
    * DifAndCtrl_B->d13 + (DifAndCtrl_B->D15_tmp_i * DifAndCtrl_B->d12 *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp_c +
    (DifAndCtrl_B->rtb_ginv_tmp_o2 * DifAndCtrl_B->D14_tmp_f +
     DifAndCtrl_B->rtb_ginv_tmp_i * DifAndCtrl_B->D14_tmp_g1) *
    DifAndCtrl_B->D14_tmp_i)) + (DifAndCtrl_B->D14_tmp_m3 *
    DifAndCtrl_B->D14_tmp_jg + DifAndCtrl_B->d10) *
    DifAndCtrl_X->Integrator1_CSTATE[5]) + DifAndCtrl_B->D14_tmp_my *
    DifAndCtrl_X->Integrator1_CSTATE[3]) * 0.5);
  DifAndCtrl_B->D14_tmp_my = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d10 = DifAndCtrl_X->Integrator1_CSTATE[3] +
    DifAndCtrl_X->Integrator1_CSTATE[6];
  DifAndCtrl_B->rtb_ginv_tmp_tmp = DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_g = DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->rtb_ginv_tmp_o2 = DifAndCtrl_X->Integrator1_CSTATE[4] *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->D14_tmp_mv = DifAndCtrl_B->D14_tmp_my * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->D16_tmp = 2.0 * DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->D16_tmp_j = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D27_tmp = DifAndCtrl_X->Integrator1_CSTATE[6] +
    DifAndCtrl_X->Integrator1_CSTATE[7];
  DifAndCtrl_B->D27_tmp_n = DifAndCtrl_B->D27_tmp * 2.0 +
    DifAndCtrl_X->Integrator1_CSTATE[3];
  DifAndCtrl_B->d14 = -2.0 * DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->d15 = DifAndCtrl_B->d10 - DifAndCtrl_B->rtb_ginv_tmp_tmp;
  DifAndCtrl_B->D14_tmp *= DifAndCtrl_B->D16_tmp_j;
  DifAndCtrl_B->d16 = DifAndCtrl_B->d10 + DifAndCtrl_X->Integrator1_CSTATE[7];
  DifAndCtrl_B->d17 = DifAndCtrl_B->d16 - DifAndCtrl_B->rtb_ginv_tmp_tmp;
  DifAndCtrl_B->d18 = DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->d14;
  DifAndCtrl_B->d20 = DifAndCtrl_B->D14_tmp_c * DifAndCtrl_X->
    Integrator1_CSTATE[4];
  DifAndCtrl_B->d21 = DifAndCtrl_B->d14 * DifAndCtrl_B->x_tmp_p +
    DifAndCtrl_B->D27_tmp_n;
  DifAndCtrl_B->d45 = DifAndCtrl_B->D46_tmp_tmp_d *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->d48 = DifAndCtrl_B->D46_tmp_c * DifAndCtrl_X->
    Integrator1_CSTATE[5];
  DifAndCtrl_B->tmp_tmp_g = -2.0 * DifAndCtrl_X->Integrator1_CSTATE[3];
  DifAndCtrl_B->dv[48] = -(((((((((((((((((DifAndCtrl_B->d20 *
    DifAndCtrl_B->D14_tmp_g * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp +
    DifAndCtrl_B->D14_tmp_my * DifAndCtrl_B->D14_tmp_g1 * DifAndCtrl_B->x_tmp_cv
    * DifAndCtrl_B->x_tmp) + DifAndCtrl_B->d45 * DifAndCtrl_P.ArmConstants.Mass1
    * DifAndCtrl_B->x_tmp * DifAndCtrl_B->smax) + DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->x_tmp * DifAndCtrl_B->smax) + DifAndCtrl_B->rtb_ginv_tmp_tmp_g
    * DifAndCtrl_B->D17_tmp_e) + DifAndCtrl_B->rtb_ginv_tmp_o2 *
    DifAndCtrl_B->D17_tmp_e) + DifAndCtrl_B->d48 *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp *
    DifAndCtrl_B->D14_tmp_f) + DifAndCtrl_B->D14_tmp_mv *
    DifAndCtrl_B->D17_tmp_o) + DifAndCtrl_B->D46_tmp_na *
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->x_tmp * DifAndCtrl_B->smax * DifAndCtrl_B->x_tmp_p) +
    DifAndCtrl_B->D46_tmp_na * DifAndCtrl_X->Integrator1_CSTATE[6] *
    DifAndCtrl_P.ArmConstants.Mass1 * DifAndCtrl_B->x_tmp * DifAndCtrl_B->smax *
    DifAndCtrl_B->x_tmp_p) + DifAndCtrl_B->tmp_tmp_g *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->x_tmp * DifAndCtrl_B->smax * DifAndCtrl_B->x_tmp_p) +
    DifAndCtrl_B->d13 * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp * DifAndCtrl_B->smax *
    DifAndCtrl_B->x_tmp_p) + DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->x_tmp * DifAndCtrl_B->D14_tmp_f * DifAndCtrl_B->x_tmp_p) +
    DifAndCtrl_B->D46_tmp_lm * DifAndCtrl_X->Integrator1_CSTATE[6] *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp *
    DifAndCtrl_B->D14_tmp_f * DifAndCtrl_B->x_tmp_p) + DifAndCtrl_B->D14_tmp_i *
    DifAndCtrl_B->x_tmp * DifAndCtrl_B->D14_tmp_f * DifAndCtrl_B->x_tmp_p) *
    DifAndCtrl_B->Clock2 + (DifAndCtrl_B->D16_tmp_tmp * DifAndCtrl_B->d15 +
    DifAndCtrl_B->d17 * DifAndCtrl_B->D14_tmp_h) * (DifAndCtrl_B->d8 *
    DifAndCtrl_B->x_tmp_c)) + ((((DifAndCtrl_B->d10 * 2.0 *
    DifAndCtrl_B->D14_tmp_c + DifAndCtrl_B->D14_tmp) * DifAndCtrl_B->x_tmp_p +
    DifAndCtrl_B->d18) * DifAndCtrl_B->D14_tmp_g +
    ((((DifAndCtrl_B->rtb_ginv_tmp_tmp_g * DifAndCtrl_B->smax +
        DifAndCtrl_B->rtb_ginv_tmp_o2 * DifAndCtrl_B->smax) +
       DifAndCtrl_B->D14_tmp_mv * DifAndCtrl_B->D14_tmp_f) -
      DifAndCtrl_B->D16_tmp_j * DifAndCtrl_B->smax * DifAndCtrl_B->s *
      DifAndCtrl_B->x_tmp_p) - (DifAndCtrl_B->D16_tmp - DifAndCtrl_B->D27_tmp_n *
    DifAndCtrl_B->x_tmp_p) * DifAndCtrl_B->D14_tmp_h)) * DifAndCtrl_B->Clock2 +
    ((DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_B->D14_tmp_g *
      DifAndCtrl_B->s + DifAndCtrl_B->d21 * DifAndCtrl_B->D14_tmp_f) *
     DifAndCtrl_B->D14_tmp_m + (DifAndCtrl_B->D14_tmp_c * 2.0 *
    DifAndCtrl_B->d15 + DifAndCtrl_B->D14_tmp) * DifAndCtrl_B->smax) *
    DifAndCtrl_B->x_tmp_c) * DifAndCtrl_B->x_tmp_b) * 0.5);
  DifAndCtrl_B->D14_tmp_i = DifAndCtrl_B->d16 * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->d13 = DifAndCtrl_X->Integrator1_CSTATE[4] *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_g = 2.0 * DifAndCtrl_B->D14_tmp_g1;
  DifAndCtrl_B->rtb_ginv_tmp_o2 = DifAndCtrl_X->Integrator1_CSTATE[5] -
    DifAndCtrl_B->D14_tmp_i;
  DifAndCtrl_B->dv[56] = -(((((DifAndCtrl_X->Integrator1_CSTATE[4] *
    DifAndCtrl_B->D14_tmp_g1 * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp +
    DifAndCtrl_B->d13 * DifAndCtrl_B->D17_tmp_o) + DifAndCtrl_B->d8 *
    DifAndCtrl_B->D14_tmp_f * DifAndCtrl_B->rtb_ginv_tmp_o2) *
    DifAndCtrl_B->Clock2 + DifAndCtrl_B->rtb_ginv_tmp_tmp_g *
    DifAndCtrl_B->x_tmp * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->d17) +
    (((DifAndCtrl_B->D14_tmp_i - DifAndCtrl_X->Integrator1_CSTATE[5]) *
      DifAndCtrl_B->rtb_ginv_tmp_tmp_g + DifAndCtrl_B->d13 *
      DifAndCtrl_B->D14_tmp_f) * DifAndCtrl_B->Clock2 + 2.0 *
     DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->D14_tmp_f * DifAndCtrl_B->d17) *
    DifAndCtrl_B->x_tmp_b) * (0.5 * DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.Mass2));
  DifAndCtrl_B->D14_tmp_i = DifAndCtrl_B->D15_tmp_tmp_c +
    DifAndCtrl_B->D15_tmp_tmp_f;
  DifAndCtrl_B->d8 = DifAndCtrl_B->d13 * DifAndCtrl_B->x_tmp_c;
  DifAndCtrl_B->d13 = DifAndCtrl_B->D14_tmp_i * DifAndCtrl_X->
    Integrator1_CSTATE[6];
  DifAndCtrl_B->dv[25] = -(((((((((cos(DifAndCtrl_B->D16_tmp_f -
    DifAndCtrl_X->Integrator_CSTATE[4]) - cos(DifAndCtrl_B->D16_tmp_a -
    DifAndCtrl_X->Integrator_CSTATE[4])) - cos(DifAndCtrl_B->D16_tmp_f +
    DifAndCtrl_X->Integrator_CSTATE[4])) + cos(DifAndCtrl_B->D16_tmp_a +
    DifAndCtrl_X->Integrator_CSTATE[4])) + sin(DifAndCtrl_B->D16_tmp_f) * 2.0) +
    sin(DifAndCtrl_B->D16_tmp_a) * 2.0) * (-0.25 * DifAndCtrl_P.ArmConstants.MC2
    * DifAndCtrl_X->Integrator1_CSTATE[7] * DifAndCtrl_P.ArmConstants.Mass2) + (
    -DifAndCtrl_X->Integrator1_CSTATE[6] * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->D37_tmp + DifAndCtrl_B->D34_tmp_e * DifAndCtrl_B->d8)) +
    DifAndCtrl_B->d13 * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->x_tmp_p) +
    (DifAndCtrl_B->D15_tmp_i * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->x_tmp_p +
     DifAndCtrl_B->D34_tmp_e * -DifAndCtrl_B->Clock2) *
    DifAndCtrl_X->Integrator1_CSTATE[3]) + (DifAndCtrl_B->D16_tmp_m *
    DifAndCtrl_B->x_tmp + DifAndCtrl_B->D14_tmp_m3 * DifAndCtrl_B->x_tmp_b) *
    DifAndCtrl_X->Integrator1_CSTATE[5]);
  DifAndCtrl_B->D16_tmp_m = DifAndCtrl_B->D15_tmp_i *
    DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->D16_tmp_f = DifAndCtrl_X->Integrator1_CSTATE[3] *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->dv[33] = -((((-DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_B->Clock2 * DifAndCtrl_B->D15_tmp_i * DifAndCtrl_B->x_tmp_cv +
    DifAndCtrl_B->d9 * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp_c *
    DifAndCtrl_B->D17_tmp_o) + DifAndCtrl_X->Integrator1_CSTATE[6] *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->D37_tmp) +
    DifAndCtrl_B->D16_tmp_f * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->D34_tmp_e) +
    DifAndCtrl_B->D16_tmp_m * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->x_tmp_p);
  DifAndCtrl_B->D16_tmp_a = DifAndCtrl_X->Integrator1_CSTATE[5] -
    DifAndCtrl_B->d10 * DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->D14_tmp_m3 = (((DifAndCtrl_B->tmp_tmp +
    DifAndCtrl_X->Integrator1_CSTATE[3]) * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 + DifAndCtrl_B->D46_tmp_tmp_d *
    DifAndCtrl_B->d10 * DifAndCtrl_P.ArmConstants.Mass1) + DifAndCtrl_B->d18 *
    DifAndCtrl_B->x_tmp_p) + DifAndCtrl_X->Integrator1_CSTATE[3] *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->rtb_ginv_tmp_oc;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_g = -0.5 * DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D14_tmp_mv = 4.0 * DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->D27_tmp_n = -4.0 * DifAndCtrl_X->Integrator1_CSTATE[6];
  DifAndCtrl_B->D14_tmp = -4.0 * DifAndCtrl_X->Integrator1_CSTATE[7];
  DifAndCtrl_B->dv[41] = -((((((((((-3.0 * DifAndCtrl_X->Integrator1_CSTATE[3] +
    DifAndCtrl_B->D27_tmp_n) + DifAndCtrl_B->D14_tmp) +
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_B->rtb_ginv_tmp_tmp_n) +
    DifAndCtrl_B->D14_tmp_mv * DifAndCtrl_B->x_tmp_p) *
    (DifAndCtrl_B->rtb_ginv_tmp_tmp_g * DifAndCtrl_B->D14_tmp_g1) +
    (-DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_B->x_tmp_p +
     DifAndCtrl_X->Integrator1_CSTATE[3]) * (DifAndCtrl_B->D46_tmp_tmp_ft *
    DifAndCtrl_B->D14_tmp_md)) + DifAndCtrl_B->D14_tmp_m3 *
    DifAndCtrl_B->D14_tmp_g) * DifAndCtrl_B->x_tmp_c +
    ((DifAndCtrl_X->Integrator1_CSTATE[4] *
      DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_B->D14_tmp_md *
      DifAndCtrl_B->x_tmp_cv + DifAndCtrl_B->D14_tmp_tmp_pm *
      DifAndCtrl_B->D16_tmp_a) + DifAndCtrl_B->rtb_ginv_tmp_o2 *
     DifAndCtrl_B->D14_tmp_tmp_p2) * DifAndCtrl_B->d19) * -DifAndCtrl_B->x_tmp_b
    + ((((-DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_B->x_tmp_p +
          DifAndCtrl_X->Integrator1_CSTATE[5]) * DifAndCtrl_B->D14_tmp_j +
         DifAndCtrl_B->D16_tmp_tmp * DifAndCtrl_B->D16_tmp_a) +
        DifAndCtrl_B->rtb_ginv_tmp_o2 * DifAndCtrl_B->D14_tmp_h) *
       DifAndCtrl_B->x_tmp + (DifAndCtrl_B->d20 * DifAndCtrl_B->D15_tmp *
    DifAndCtrl_B->x_tmp_cv + DifAndCtrl_B->D14_tmp_my * DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_B->x_tmp_cv)) * (-2.0 * DifAndCtrl_B->Clock2)) +
    (((DifAndCtrl_B->rtb_ginv_tmp_oc * DifAndCtrl_X->Integrator1_CSTATE[3] +
       DifAndCtrl_B->d21) * DifAndCtrl_B->D14_tmp_tmp_p2 +
      DifAndCtrl_B->D14_tmp_m3 * DifAndCtrl_B->smax) * DifAndCtrl_B->x_tmp +
     (-DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_P.ArmConstants.l1_dim *
      DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D15_tmp *
      DifAndCtrl_B->D17_tmp_a - DifAndCtrl_B->D16_tmp_j *
      DifAndCtrl_B->D15_tmp_m * DifAndCtrl_B->D17_tmp_a)) *
    DifAndCtrl_B->x_tmp_c) * 0.5);
  DifAndCtrl_B->D14_tmp_my = DifAndCtrl_B->D16_tmp_tmp + DifAndCtrl_B->D14_tmp_h;
  DifAndCtrl_B->dv[49] = -((((DifAndCtrl_B->D14_tmp_i *
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_B->x_tmp_c *
    DifAndCtrl_B->x_tmp_p + (-DifAndCtrl_X->Integrator1_CSTATE[3] *
    DifAndCtrl_B->Clock2 * DifAndCtrl_B->D37_tmp + DifAndCtrl_B->D37_tmp *
    DifAndCtrl_B->d8)) - (DifAndCtrl_B->Clock2 * DifAndCtrl_B->D17_tmp_o -
    DifAndCtrl_B->D15_tmp_m * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->x_tmp_p) *
    DifAndCtrl_B->d9) + (DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->x_tmp_c *
    DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->D37_tmp * -DifAndCtrl_B->Clock2) *
    DifAndCtrl_X->Integrator1_CSTATE[6]) + ((DifAndCtrl_B->D14_tmp_my *
    DifAndCtrl_B->Clock2 * DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->D14_tmp_ct) *
    DifAndCtrl_B->x_tmp + (-DifAndCtrl_B->D14_tmp_my * DifAndCtrl_B->x_tmp_c +
    DifAndCtrl_B->d11) * DifAndCtrl_B->x_tmp_b) *
    DifAndCtrl_X->Integrator1_CSTATE[5]);
  DifAndCtrl_B->dv[57] = -(((((DifAndCtrl_B->d16 -
    DifAndCtrl_X->Integrator1_CSTATE[4]) * DifAndCtrl_B->D46_tmp_dy +
    DifAndCtrl_B->D16_tmp * DifAndCtrl_B->D15_tmp_m) - (DifAndCtrl_B->d16 +
    DifAndCtrl_X->Integrator1_CSTATE[4]) * DifAndCtrl_B->D46_tmp_ln) *
    DifAndCtrl_B->x_tmp_c + DifAndCtrl_B->d19 * DifAndCtrl_B->D17_tmp_o *
    DifAndCtrl_B->d17) * DifAndCtrl_B->rtb_ginv_tmp_tmp_g);
  DifAndCtrl_B->dv[26] = -(((DifAndCtrl_B->d9 * DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_B->x_tmp_cv + DifAndCtrl_B->d13 * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->D15_tmp_i * DifAndCtrl_X->Integrator1_CSTATE[3] *
    DifAndCtrl_B->x_tmp_cv) - DifAndCtrl_B->D34_tmp_e *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_B->x_tmp_p);
  DifAndCtrl_B->dv[34] = -(((DifAndCtrl_B->D16_tmp_m * DifAndCtrl_B->x_tmp_cv -
    DifAndCtrl_B->d9 * DifAndCtrl_B->D17_tmp_o * DifAndCtrl_B->x_tmp_p) +
    DifAndCtrl_B->D37_tmp * -DifAndCtrl_X->Integrator1_CSTATE[6] *
    DifAndCtrl_B->x_tmp_p) - DifAndCtrl_B->D34_tmp_e *
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_B->x_tmp_p);
  DifAndCtrl_B->dv[42] = -0.0;
  DifAndCtrl_B->dv[50] = -((DifAndCtrl_B->d16 * DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_B->x_tmp_cv + DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->d10 *
    DifAndCtrl_B->D15_tmp * DifAndCtrl_B->x_tmp_cv) - DifAndCtrl_B->D37_tmp *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_B->x_tmp_p);
  DifAndCtrl_B->dv[58] = -((DifAndCtrl_B->d16 * DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_B->x_tmp_cv - DifAndCtrl_X->Integrator1_CSTATE[4] *
    DifAndCtrl_B->D17_tmp_o * DifAndCtrl_B->x_tmp_p) * DifAndCtrl_B->D14_tmp_m);
  DifAndCtrl_B->dv[27] = -(-DifAndCtrl_X->Integrator1_CSTATE[6] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_B->D14_tmp_c *
    DifAndCtrl_B->smax - (DifAndCtrl_B->D27_tmp *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_B->D14_tmp_f +
    DifAndCtrl_X->Integrator1_CSTATE[7] * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_B->s) * DifAndCtrl_B->D14_tmp_m);
  DifAndCtrl_B->D14_tmp_i = DifAndCtrl_B->D46_tmp_tmp_h * 2.0;
  DifAndCtrl_B->D14_tmp_my = DifAndCtrl_B->D46_tmp_m * 2.0;
  DifAndCtrl_B->d8 = DifAndCtrl_B->D46_tmp_mj * 2.0;
  DifAndCtrl_B->d9 = DifAndCtrl_P.HexaConstants.Inertia[4] * DifAndCtrl_B->D17;
  DifAndCtrl_B->D16_tmp_m = DifAndCtrl_P.HexaConstants.Inertia[8] *
    DifAndCtrl_B->D17;
  DifAndCtrl_B->d11 = DifAndCtrl_B->D56_tmp_ap * DifAndCtrl_B->D17;
  DifAndCtrl_B->d13 = DifAndCtrl_B->D56_tmp_jd * DifAndCtrl_B->D17;
  DifAndCtrl_B->D16_tmp_a = DifAndCtrl_P.ArmConstants.Inertia1[0] *
    DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->d19 = DifAndCtrl_P.ArmConstants.Inertia1[4] *
    DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->D14_tmp_m3 = DifAndCtrl_B->D47_tmp_p * DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_g = DifAndCtrl_B->D47_tmp_px *
    DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->rtb_ginv_tmp_o2 = DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->D16_tmp_j = DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->D27_tmp = DifAndCtrl_B->D47_tmp * DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->d18 = DifAndCtrl_B->D14_tmp_my * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d20 = DifAndCtrl_B->D14_tmp_i * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d21 = DifAndCtrl_B->d8 * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D14_tmp_i *= DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D14_tmp_g1 = DifAndCtrl_B->D46_tmp_cn * 2.0 *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D14_tmp_j = DifAndCtrl_B->D56_tmp_nj * DifAndCtrl_B->D46_tmp_p;
  DifAndCtrl_B->D14_tmp_h = DifAndCtrl_P.ArmConstants.Inertia1[0] *
    DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->D14_tmp_tmp_pm = DifAndCtrl_P.ArmConstants.Inertia1[4] *
    DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->D14_tmp_tmp_p2 = DifAndCtrl_B->D47_tmp_p *
    DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->D14_tmp_ct = DifAndCtrl_B->D47_tmp_px * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->D15_tmp_tmp_c = DifAndCtrl_B->D46_tmp_f *
    DifAndCtrl_B->D46_tmp_tmp_p;
  DifAndCtrl_B->D15_tmp_tmp_f = DifAndCtrl_B->D56_tmp_k *
    DifAndCtrl_B->D46_tmp_l;
  DifAndCtrl_B->D16_tmp_tmp = DifAndCtrl_B->D46_tmp_f *
    DifAndCtrl_B->D56_tmp_tmp_l;
  DifAndCtrl_B->D34_tmp_e = DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->D37_tmp = DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->D46_tmp_tmp_ft = DifAndCtrl_B->D47_tmp * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->rtb_ginv_tmp_oc = 2.0 * DifAndCtrl_P.ArmConstants.Inertia1[8] *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d56 = 2.0 * DifAndCtrl_P.ArmConstants.Inertia2[8] *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d57 = DifAndCtrl_B->d18 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d58 = DifAndCtrl_B->d21 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d59 = DifAndCtrl_B->D14_tmp_g1 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d60 = DifAndCtrl_B->D56_tmp_n3 * DifAndCtrl_B->D46_tmp_j;
  DifAndCtrl_B->d61 = DifAndCtrl_P.ArmConstants.Inertia1[0] *
    DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->d62 = DifAndCtrl_P.ArmConstants.Inertia1[4] *
    DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->d63 = DifAndCtrl_B->D47_tmp_p * DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->d64 = DifAndCtrl_B->D47_tmp_px * DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->d65 = DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D46_tmp_tmp_c;
  DifAndCtrl_B->d66 = DifAndCtrl_B->D56_tmp_oy * DifAndCtrl_B->D46_tmp_d;
  DifAndCtrl_B->d67 = DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D56_tmp_tmp_p;
  DifAndCtrl_B->d68 = DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->d69 = DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->d70 = DifAndCtrl_B->D47_tmp * DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->d71 = DifAndCtrl_B->D56_tmp_g * DifAndCtrl_B->D46_tmp_g;
  DifAndCtrl_B->d72 = DifAndCtrl_B->D25 * DifAndCtrl_B->D56_tmp_d;
  DifAndCtrl_B->d73 = DifAndCtrl_B->D56_tmp_c * DifAndCtrl_B->D46_tmp_dy;
  DifAndCtrl_B->d74 = DifAndCtrl_B->D15 * DifAndCtrl_B->D56_tmp_lx;
  DifAndCtrl_B->d75 = DifAndCtrl_B->D56_tmp_cj * DifAndCtrl_B->D46_tmp_b;
  DifAndCtrl_B->d76 = DifAndCtrl_B->D25 * DifAndCtrl_B->D56_tmp_b;
  DifAndCtrl_B->d77 = DifAndCtrl_B->D56_tmp_m1 * DifAndCtrl_B->D46_tmp_ln;
  DifAndCtrl_B->d78 = DifAndCtrl_B->D15 * DifAndCtrl_B->D56_tmp_h;
  DifAndCtrl_B->tmp_tmp_d = DifAndCtrl_B->D46_tmp_tmp_h *
    DifAndCtrl_B->D14_tmp_md + (DifAndCtrl_P.HexaConstants.Inertia[4] -
    DifAndCtrl_P.HexaConstants.Inertia[8]);
  DifAndCtrl_B->D14_tmp_md =
    ((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B->tmp_tmp_d *
    DifAndCtrl_B->D56_tmp_tmp_a + DifAndCtrl_B->rtb_ginv_tmp_tmp_p *
    DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->D14_tmp_j) +
    DifAndCtrl_B->D46_tmp_cs * DifAndCtrl_B->D27) + DifAndCtrl_B->D46_tmp_k *
    DifAndCtrl_B->D27) - DifAndCtrl_B->D14_tmp_h) + DifAndCtrl_B->D14_tmp_tmp_pm)
    + DifAndCtrl_B->D14_tmp_tmp_p2) + DifAndCtrl_B->D14_tmp_ct) +
    DifAndCtrl_B->D15_tmp_tmp_c) + DifAndCtrl_B->D46_tmp_p4 *
    DifAndCtrl_B->D46_tmp_tmp_b) + DifAndCtrl_B->D15_tmp_tmp_f) +
    DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->D56_tmp_tmp_o) +
    DifAndCtrl_B->D16_tmp_tmp) - DifAndCtrl_B->D34_tmp_e) +
    DifAndCtrl_B->D37_tmp) + DifAndCtrl_B->D46_tmp_tmp_ft) +
    DifAndCtrl_B->rtb_ginv_tmp_oc) + DifAndCtrl_B->d56) + 2.0 *
    DifAndCtrl_P.HexaConstants.Inertia[0] * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->d57) + DifAndCtrl_B->d20 * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->d58) + DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->d59) + DifAndCtrl_P.HexaConstants.Inertia[4] *
    DifAndCtrl_B->D56_tmp_tmp_f) - DifAndCtrl_P.HexaConstants.Inertia[8] *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->D56_tmp_ap *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->D56_tmp_jd *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->D46_tmp_cs *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->D46_tmp_k *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->d60) +
    DifAndCtrl_B->D46_tmp_cs * DifAndCtrl_B->D56_tmp_tmp_m) +
    DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->D56_tmp_tmp_m) - DifAndCtrl_B->d61)
                      + DifAndCtrl_B->d62) + DifAndCtrl_B->d63) +
                    DifAndCtrl_B->d64) + DifAndCtrl_B->d65) +
                  DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->D46_tmp_tmp_n) +
                 DifAndCtrl_B->d66) + DifAndCtrl_B->D46_tmp_p4 *
                DifAndCtrl_B->D56_tmp_tmp_h2) + DifAndCtrl_B->d67) -
              DifAndCtrl_B->d68) + DifAndCtrl_B->d69) + DifAndCtrl_B->d70) +
           DifAndCtrl_B->d71) + DifAndCtrl_B->d72) + DifAndCtrl_B->d73) +
        DifAndCtrl_B->d74) + DifAndCtrl_B->d75) + DifAndCtrl_B->d76) +
     DifAndCtrl_B->d77) + DifAndCtrl_B->d78;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_p = DifAndCtrl_B->D56_tmp_m *
    DifAndCtrl_B->rtb_ginv_tmp_n + DifAndCtrl_B->D56_tmp_mc *
    DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->d177 = DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D28;
  DifAndCtrl_B->dv[35] = -(((((((((((((((((DifAndCtrl_B->rtb_ginv_tmp_tmp_p +
    DifAndCtrl_B->d9) - DifAndCtrl_B->D16_tmp_m) + DifAndCtrl_B->d11) +
    DifAndCtrl_B->d13) - DifAndCtrl_B->D16_tmp_a) + DifAndCtrl_B->d19) +
    DifAndCtrl_B->D14_tmp_m3) + DifAndCtrl_B->rtb_ginv_tmp_tmp_g) +
    DifAndCtrl_B->D46_tmp_cs * DifAndCtrl_B->D18) + DifAndCtrl_B->D46_tmp_k *
    DifAndCtrl_B->D18) - DifAndCtrl_B->rtb_ginv_tmp_o2) +
    DifAndCtrl_B->D16_tmp_j) + DifAndCtrl_B->D27_tmp) + DifAndCtrl_B->D46_tmp_p4
    * DifAndCtrl_B->D56_tmp_tmp_c) + DifAndCtrl_B->d177) * DifAndCtrl_B->d12 +
    DifAndCtrl_B->D14_tmp_md * -DifAndCtrl_X->Integrator1_CSTATE[5]) * 0.25);
  DifAndCtrl_B->d22 = -2.0 * DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->d23 = DifAndCtrl_B->d22 * DifAndCtrl_B->D46_tmp_tmp_h;
  DifAndCtrl_B->d24 = -4.0 * DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->tmp_tmp_c = -4.0 * DifAndCtrl_P.ArmConstants.MC1;
  DifAndCtrl_B->d25 = DifAndCtrl_B->tmp_tmp_c * DifAndCtrl_X->
    Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
    DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->tmp_tmp_i = DifAndCtrl_B->d24 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_j = -4.0 * DifAndCtrl_P.ArmConstants.MC2;
  DifAndCtrl_B->tmp_tmp_h = DifAndCtrl_B->tmp_tmp_j *
    DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->d26 = DifAndCtrl_B->tmp_tmp_h *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_h = DifAndCtrl_B->tmp_tmp_h *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d27 = DifAndCtrl_B->d24 * DifAndCtrl_B->D46_tmp_tmp_h;
  DifAndCtrl_B->d28 = DifAndCtrl_B->d22 * DifAndCtrl_P.HexaConstants.Inertia[4];
  DifAndCtrl_B->d29 = DifAndCtrl_B->d12 * DifAndCtrl_P.HexaConstants.Inertia[8];
  DifAndCtrl_B->d30 = DifAndCtrl_B->d23 * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d23 *= DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_f = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia1[3];
  DifAndCtrl_B->tmp_tmp_ji = DifAndCtrl_B->d12 *
    DifAndCtrl_P.ArmConstants.Inertia1[0];
  DifAndCtrl_B->tmp_tmp_oo = DifAndCtrl_B->d22 *
    DifAndCtrl_P.ArmConstants.Inertia1[4];
  DifAndCtrl_B->tmp_tmp_fr = DifAndCtrl_B->D46_tmp_tmp_j *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->tmp_tmp_oy = DifAndCtrl_B->d22 * DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d31 = 4.0 * DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->tmp_tmp_ln = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia2[3];
  DifAndCtrl_B->tmp_tmp_lu = DifAndCtrl_B->d12 *
    DifAndCtrl_P.ArmConstants.Inertia2[0];
  DifAndCtrl_B->tmp_tmp_gf = DifAndCtrl_B->d22 *
    DifAndCtrl_P.ArmConstants.Inertia2[4];
  DifAndCtrl_B->tmp_tmp_d4 = DifAndCtrl_B->D46_tmp_tmp_kn *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d32 = DifAndCtrl_B->d14 * DifAndCtrl_B->D46_tmp_tmp_h;
  DifAndCtrl_B->d33 = DifAndCtrl_B->tmp_tmp_j * DifAndCtrl_X->
    Integrator1_CSTATE[5];
  DifAndCtrl_B->d34 = DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->d35 = DifAndCtrl_B->D46_tmp_tmp_h *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->d36 = DifAndCtrl_P.HexaConstants.Inertia[4] *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->d37 = DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.HexaConstants.Inertia[8];
  DifAndCtrl_B->d38 = DifAndCtrl_B->d35 * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d35 *= DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_dv = DifAndCtrl_P.ArmConstants.Inertia1[0] *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->tmp_tmp_jo = DifAndCtrl_P.ArmConstants.Inertia1[4] *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->tmp_tmp_f1 = DifAndCtrl_B->D46_tmp_m *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d39 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia1[3];
  DifAndCtrl_B->tmp_tmp_js = DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->tmp_tmp_ho = DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->tmp_tmp_n = DifAndCtrl_B->D46_tmp_mj *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d40 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia2[3];
  DifAndCtrl_B->d41 = DifAndCtrl_B->D46_tmp_na *
    DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d42 = DifAndCtrl_B->d14 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d43 = DifAndCtrl_B->d34 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d34 = DifAndCtrl_B->d34 * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d44 = DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_B->s +
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->d46 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->d47 = DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d49 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->d50 = DifAndCtrl_B->d14 * DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->d51 = DifAndCtrl_B->d14 * DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->d52 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->d53 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->d54 = DifAndCtrl_B->d14 * DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->d55 = DifAndCtrl_B->d14 * DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->d104 = DifAndCtrl_B->d28 * DifAndCtrl_B->D56_tmp_tmp_a;
  DifAndCtrl_B->d105 = DifAndCtrl_B->d29 * DifAndCtrl_B->D56_tmp_tmp_a;
  DifAndCtrl_B->d106 = DifAndCtrl_B->d30 * DifAndCtrl_B->D56_tmp_tmp_a;
  DifAndCtrl_B->d107 = DifAndCtrl_B->d23 * DifAndCtrl_B->D56_tmp_tmp_a;
  DifAndCtrl_B->d124 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->d108 = DifAndCtrl_B->d124 * DifAndCtrl_B->D46_tmp_p;
  DifAndCtrl_B->d109 = DifAndCtrl_B->tmp_tmp_f * DifAndCtrl_B->rtb_ginv_tmp_ie;
  DifAndCtrl_B->d110 = DifAndCtrl_B->d25 * DifAndCtrl_B->D27;
  DifAndCtrl_B->d111 = DifAndCtrl_B->tmp_tmp_i * DifAndCtrl_B->D27;
  DifAndCtrl_B->d112 = DifAndCtrl_B->tmp_tmp_ji * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->d113 = DifAndCtrl_B->tmp_tmp_oo * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->d114 = DifAndCtrl_B->tmp_tmp_fr * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->d115 = DifAndCtrl_B->tmp_tmp_oy * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->d125 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->d116 = DifAndCtrl_B->d125 * DifAndCtrl_B->D46_tmp_l;
  DifAndCtrl_B->d117 = DifAndCtrl_B->tmp_tmp_ln * DifAndCtrl_B->D46_tmp_tmp_i;
  DifAndCtrl_B->d118 = DifAndCtrl_B->d26 * DifAndCtrl_B->D56_tmp_tmp_o;
  DifAndCtrl_B->d119 = DifAndCtrl_B->tmp_tmp_h * DifAndCtrl_B->D56_tmp_tmp_l;
  DifAndCtrl_B->d120 = DifAndCtrl_B->tmp_tmp_lu * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->d121 = DifAndCtrl_B->tmp_tmp_gf * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->d122 = DifAndCtrl_B->tmp_tmp_d4 * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->D46_tmp_m *= -4.0;
  DifAndCtrl_B->d123 = DifAndCtrl_B->D46_tmp_mj * -4.0;
  DifAndCtrl_B->d126 = DifAndCtrl_B->d34 * DifAndCtrl_B->D46_tmp_tmp;
  DifAndCtrl_B->d127 = -4.0 * DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->d128 = DifAndCtrl_B->d41 * DifAndCtrl_B->D56_tmp_tmp_e;
  DifAndCtrl_B->d129 = DifAndCtrl_B->d42 * DifAndCtrl_B->D56_tmp_tmp_e;
  DifAndCtrl_B->d130 = DifAndCtrl_B->d43 * DifAndCtrl_B->D56_tmp_tmp_h;
  DifAndCtrl_B->d131 = DifAndCtrl_B->d37 * DifAndCtrl_B->d4;
  DifAndCtrl_B->d157 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->d132 = DifAndCtrl_B->d157 * DifAndCtrl_B->D46_tmp_g;
  DifAndCtrl_B->d133 = DifAndCtrl_B->tmp_tmp_dv * DifAndCtrl_B->D38;
  DifAndCtrl_B->d134 = DifAndCtrl_B->tmp_tmp_jo * DifAndCtrl_B->D38;
  DifAndCtrl_B->d135 = DifAndCtrl_B->tmp_tmp_f1 * DifAndCtrl_B->D38;
  DifAndCtrl_B->d136 = DifAndCtrl_B->d47 * DifAndCtrl_B->D38;
  DifAndCtrl_B->d137 = DifAndCtrl_B->d39 * DifAndCtrl_B->D56_tmp_d;
  DifAndCtrl_B->d162 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->d138 = DifAndCtrl_B->d162 * DifAndCtrl_B->D46_tmp_dy;
  DifAndCtrl_B->d139 = DifAndCtrl_B->tmp_tmp_js * DifAndCtrl_B->D47_tmp_m;
  DifAndCtrl_B->d140 = DifAndCtrl_B->tmp_tmp_ho * DifAndCtrl_B->D47_tmp_m;
  DifAndCtrl_B->d141 = DifAndCtrl_B->tmp_tmp_n * DifAndCtrl_B->D47_tmp_m;
  DifAndCtrl_B->d142 = DifAndCtrl_B->d40 * DifAndCtrl_B->D56_tmp_lx;
  DifAndCtrl_B->d143 = DifAndCtrl_B->d14 * DifAndCtrl_P.ArmConstants.Inertia1[4];
  DifAndCtrl_B->d144 = DifAndCtrl_B->d14 * DifAndCtrl_P.ArmConstants.Inertia2[4];
  DifAndCtrl_B->d145 = DifAndCtrl_B->d14 * DifAndCtrl_P.HexaConstants.Inertia[4];
  DifAndCtrl_B->d150 = DifAndCtrl_B->d36 * DifAndCtrl_B->D47;
  DifAndCtrl_B->d151 = DifAndCtrl_B->d38 * DifAndCtrl_B->D47;
  DifAndCtrl_B->d152 = DifAndCtrl_B->d35 * DifAndCtrl_B->D47;
  DifAndCtrl_B->d153 = DifAndCtrl_B->d36 * DifAndCtrl_B->D48_tmp_o;
  DifAndCtrl_B->d154 = DifAndCtrl_B->d37 * DifAndCtrl_B->D48_tmp_o;
  DifAndCtrl_B->d155 = DifAndCtrl_B->d38 * DifAndCtrl_B->D48_tmp_o;
  DifAndCtrl_B->d156 = DifAndCtrl_B->d35 * DifAndCtrl_B->D48_tmp_o;
  DifAndCtrl_B->d158 = DifAndCtrl_B->tmp_tmp_dv * DifAndCtrl_B->D56_tmp_tmp;
  DifAndCtrl_B->d159 = DifAndCtrl_B->tmp_tmp_jo * DifAndCtrl_B->D56_tmp_tmp;
  DifAndCtrl_B->d160 = DifAndCtrl_B->tmp_tmp_f1 * DifAndCtrl_B->D56_tmp_tmp;
  DifAndCtrl_B->d163 = DifAndCtrl_B->tmp_tmp_js * DifAndCtrl_B->D58;
  DifAndCtrl_B->d164 = DifAndCtrl_B->tmp_tmp_ho * DifAndCtrl_B->D58;
  DifAndCtrl_B->d165 = DifAndCtrl_B->tmp_tmp_n * DifAndCtrl_B->D58;
  DifAndCtrl_B->d167 = DifAndCtrl_B->tmp_tmp_h * DifAndCtrl_B->D46_tmp_tmp_p;
  DifAndCtrl_B->d168 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia1[8]
    * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d169 = DifAndCtrl_B->d24 * DifAndCtrl_P.ArmConstants.Inertia2[8]
    * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d170 = DifAndCtrl_B->D46_tmp_m *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d171 = DifAndCtrl_B->d123 * DifAndCtrl_X->Integrator1_CSTATE[4] *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d172 = DifAndCtrl_B->d24 * DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d173 = DifAndCtrl_B->tmp_tmp_h * DifAndCtrl_B->D46_tmp_tmp_c;
  DifAndCtrl_B->d198 = DifAndCtrl_B->D14_tmp_mv *
    DifAndCtrl_P.ArmConstants.Inertia2[3] * DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->d199 = DifAndCtrl_B->d53 * DifAndCtrl_B->D68;
  DifAndCtrl_B->d178 = ((DifAndCtrl_B->D14_tmp_mv *
    DifAndCtrl_P.ArmConstants.Inertia1[3] * DifAndCtrl_B->rtb_ginv_tmp_n +
    DifAndCtrl_B->d198) + DifAndCtrl_B->d52 * DifAndCtrl_B->rtb_ginv_tmp_tmp_l)
    + DifAndCtrl_B->d199;
  DifAndCtrl_B->d179 = DifAndCtrl_B->tmp_tmp_f * DifAndCtrl_B->d;
  DifAndCtrl_B->d180 = DifAndCtrl_B->tmp_tmp_ln * DifAndCtrl_B->D46_tmp_tmp_g;
  DifAndCtrl_B->d181 = DifAndCtrl_B->d54 * DifAndCtrl_B->d1;
  DifAndCtrl_B->d182 = DifAndCtrl_B->d55 * DifAndCtrl_B->d2;
  DifAndCtrl_B->d183 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia1[0] * DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->d184 = DifAndCtrl_B->d143 * DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->D46_tmp_tmp_j = DifAndCtrl_B->D46_tmp_tmp_j *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->d185 = DifAndCtrl_B->d14 * DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->d186 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia2[0] * DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->d187 = DifAndCtrl_B->d144 * DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->D46_tmp_tmp_kn = DifAndCtrl_B->D46_tmp_tmp_kn *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->d188 = DifAndCtrl_B->d33 * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D28;
  DifAndCtrl_B->d189 = DifAndCtrl_B->d50 * DifAndCtrl_B->ab_a;
  DifAndCtrl_B->d190 = DifAndCtrl_B->d51 * DifAndCtrl_B->D67;
  DifAndCtrl_B->d191 = 8.0 * DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[7];
  DifAndCtrl_B->d194 = DifAndCtrl_B->d46 * DifAndCtrl_B->D15_tmp_tmp;
  DifAndCtrl_B->d195 = DifAndCtrl_B->d49 * DifAndCtrl_B->D15_tmp_tmp_i;
  DifAndCtrl_B->d196 = DifAndCtrl_B->d34 * DifAndCtrl_B->D46_tmp_tmp_f;
  DifAndCtrl_B->dv[43] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    ((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B->d178 +
    DifAndCtrl_B->d104) + DifAndCtrl_B->d105) + DifAndCtrl_B->d106) +
    DifAndCtrl_B->d107) + DifAndCtrl_B->d25 * DifAndCtrl_B->D46_tmp_tmp_k) +
    DifAndCtrl_B->tmp_tmp_i * DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->d108)
    + DifAndCtrl_B->d109) + DifAndCtrl_B->d110) + DifAndCtrl_B->d111) +
    DifAndCtrl_B->d112) + DifAndCtrl_B->d113) + DifAndCtrl_B->d114) +
    DifAndCtrl_B->d115) + DifAndCtrl_B->d167) + DifAndCtrl_B->d26 *
    DifAndCtrl_B->D46_tmp_tmp_b) + DifAndCtrl_B->d116) + DifAndCtrl_B->d117) +
    DifAndCtrl_B->d118) + DifAndCtrl_B->d119) + DifAndCtrl_B->d120) +
    DifAndCtrl_B->d121) + DifAndCtrl_B->d122) + DifAndCtrl_B->d168) +
    DifAndCtrl_B->d169) + DifAndCtrl_B->d24 *
    DifAndCtrl_P.HexaConstants.Inertia[0] * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->d170) + DifAndCtrl_B->d27 * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->d171) + DifAndCtrl_B->d27 *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->d172) + DifAndCtrl_B->d28 * DifAndCtrl_B->D56_tmp_tmp_f) +
    DifAndCtrl_B->d29 * DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d30 *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d23 *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d25 *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->tmp_tmp_i *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->d31 *
    DifAndCtrl_P.ArmConstants.Inertia1[7] * DifAndCtrl_B->D46_tmp_j) +
    DifAndCtrl_B->d179) + DifAndCtrl_B->d25 * DifAndCtrl_B->D56_tmp_tmp_m) +
    DifAndCtrl_B->tmp_tmp_i * DifAndCtrl_B->D56_tmp_tmp_m) +
    DifAndCtrl_B->tmp_tmp_ji * DifAndCtrl_B->D56_tmp_f) +
    DifAndCtrl_B->tmp_tmp_oo * DifAndCtrl_B->D56_tmp_f) +
    DifAndCtrl_B->tmp_tmp_fr * DifAndCtrl_B->D56_tmp_f) +
    DifAndCtrl_B->tmp_tmp_oy * DifAndCtrl_B->D56_tmp_f) + DifAndCtrl_B->d173) +
    DifAndCtrl_B->d26 * DifAndCtrl_B->D46_tmp_tmp_n) + DifAndCtrl_B->d31 *
    DifAndCtrl_P.ArmConstants.Inertia2[7] * DifAndCtrl_B->D46_tmp_d) +
    DifAndCtrl_B->d180) + DifAndCtrl_B->d26 * DifAndCtrl_B->D56_tmp_tmp_h2) +
    DifAndCtrl_B->tmp_tmp_h * DifAndCtrl_B->D56_tmp_tmp_p) +
    DifAndCtrl_B->tmp_tmp_lu * DifAndCtrl_B->D56_tmp_a) +
    DifAndCtrl_B->tmp_tmp_gf * DifAndCtrl_B->D56_tmp_a) +
    DifAndCtrl_B->tmp_tmp_d4 * DifAndCtrl_B->D56_tmp_a) + DifAndCtrl_B->d181) +
    DifAndCtrl_B->d182) + DifAndCtrl_B->d145 * DifAndCtrl_B->D17) +
    DifAndCtrl_B->D16_tmp * DifAndCtrl_P.HexaConstants.Inertia[8] *
    DifAndCtrl_B->D17) + DifAndCtrl_B->d32 * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->D17) + DifAndCtrl_B->d32 * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->D17) + DifAndCtrl_B->d183) + DifAndCtrl_B->d184) +
    DifAndCtrl_B->D46_tmp_tmp_j) + DifAndCtrl_B->d185) + DifAndCtrl_B->tmp_tmp_c
    * DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->D18) + DifAndCtrl_B->d127 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D18) + DifAndCtrl_B->d186)
    + DifAndCtrl_B->d187) + DifAndCtrl_B->D46_tmp_tmp_kn) + DifAndCtrl_B->d33 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->D56_tmp_tmp_c) + DifAndCtrl_B->d188) + DifAndCtrl_B->d126) +
    DifAndCtrl_B->d189) + DifAndCtrl_B->d128) + DifAndCtrl_B->d129) +
    DifAndCtrl_B->d190) + DifAndCtrl_B->d130) + DifAndCtrl_B->d131) +
    DifAndCtrl_B->d132) + DifAndCtrl_B->d133) - DifAndCtrl_B->d134) -
    DifAndCtrl_B->d135) - DifAndCtrl_B->d136) + DifAndCtrl_B->d137) +
    DifAndCtrl_B->d138) + DifAndCtrl_B->d139) - DifAndCtrl_B->d140) -
    DifAndCtrl_B->d141) + DifAndCtrl_B->d142) + DifAndCtrl_B->d191 *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->d44 * DifAndCtrl_B->x_tmp_p)
    + 8.0 * DifAndCtrl_X->Integrator1_CSTATE[6] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_B->D14_tmp_c0 *
    DifAndCtrl_B->x_tmp_p) + DifAndCtrl_B->d150) + DifAndCtrl_B->d151) +
    DifAndCtrl_B->d152) - DifAndCtrl_B->d153) + DifAndCtrl_B->d154) -
    DifAndCtrl_B->d155) - DifAndCtrl_B->d156) + DifAndCtrl_B->d31 *
                       DifAndCtrl_P.ArmConstants.Inertia1[6] *
                       DifAndCtrl_B->D46_tmp_b) + DifAndCtrl_B->d158) -
                     DifAndCtrl_B->d159) - DifAndCtrl_B->d160) +
                   DifAndCtrl_B->D46_tmp_cn * -DifAndCtrl_X->Integrator1_CSTATE
                   [5] * DifAndCtrl_P.ArmConstants.Mass2 *
                   DifAndCtrl_B->D56_tmp_tmp) + DifAndCtrl_B->d39 *
                  DifAndCtrl_B->D56_tmp_b) + DifAndCtrl_B->d31 *
                 DifAndCtrl_P.ArmConstants.Inertia2[6] *
                 DifAndCtrl_B->D46_tmp_ln) + DifAndCtrl_B->d163) -
               DifAndCtrl_B->d164) - DifAndCtrl_B->d165) + DifAndCtrl_B->d40 *
             DifAndCtrl_B->D56_tmp_h) + DifAndCtrl_B->d194) + DifAndCtrl_B->d195)
          + DifAndCtrl_B->d41 * DifAndCtrl_B->y_a) + DifAndCtrl_B->d42 *
         DifAndCtrl_B->y_a) + DifAndCtrl_B->d43 * DifAndCtrl_B->D48_tmp_tmp) +
       DifAndCtrl_B->d196) * 0.125);
  DifAndCtrl_B->d24 = DifAndCtrl_B->D14_tmp_c0 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L;
  DifAndCtrl_B->d27 = -DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[7];
  DifAndCtrl_B->dv[51] = -(DifAndCtrl_B->d27 * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->d44 - DifAndCtrl_B->d24 * DifAndCtrl_B->d15);
  DifAndCtrl_B->dv[59] = -(-DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->d44 * DifAndCtrl_B->d17);
  DifAndCtrl_B->d45 = DifAndCtrl_B->d45 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d32 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d33 = DifAndCtrl_B->d48 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d48 = DifAndCtrl_B->d48 * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d39 = DifAndCtrl_B->D16_tmp * DifAndCtrl_B->D46_tmp_tmp_h;
  DifAndCtrl_B->d40 = -4.0 * DifAndCtrl_X->Integrator1_CSTATE[3];
  DifAndCtrl_B->D14_tmp_c0 = DifAndCtrl_B->d31 *
    DifAndCtrl_P.ArmConstants.Inertia2[3];
  DifAndCtrl_B->tmp_tmp_o = DifAndCtrl_B->D14_tmp_c0 *
    DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->d99 = 4.0 * DifAndCtrl_X->Integrator1_CSTATE[3];
  DifAndCtrl_B->d161 = DifAndCtrl_B->d31 * DifAndCtrl_P.ArmConstants.Inertia1[3];
  DifAndCtrl_B->d174 = DifAndCtrl_B->d99 * DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->d175 = 4.0 * DifAndCtrl_X->Integrator1_CSTATE[7];
  DifAndCtrl_B->d176 = 4.0 * DifAndCtrl_X->Integrator1_CSTATE[6];
  DifAndCtrl_B->d10 = ((((DifAndCtrl_B->d10 * 4.0 *
    DifAndCtrl_P.ArmConstants.Inertia1[6] * DifAndCtrl_B->D15_tmp +
    DifAndCtrl_B->d161 * DifAndCtrl_B->rtb_ginv_tmp_n) + DifAndCtrl_B->d174 *
    DifAndCtrl_B->D15_tmp_m) + DifAndCtrl_B->d176 *
                        DifAndCtrl_P.ArmConstants.Inertia2[6] *
                        DifAndCtrl_B->D15_tmp_m) + DifAndCtrl_B->d175 *
                       DifAndCtrl_P.ArmConstants.Inertia2[6] *
                       DifAndCtrl_B->D15_tmp_m) + DifAndCtrl_B->tmp_tmp_o;
  DifAndCtrl_B->tmp_tmp_b = DifAndCtrl_B->d46 * DifAndCtrl_B->D46_tmp_p;
  DifAndCtrl_B->tmp_tmp_e = DifAndCtrl_B->tmp_tmp_dv * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->tmp_tmp_dd = DifAndCtrl_B->tmp_tmp_jo * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->tmp_tmp_ik = DifAndCtrl_B->tmp_tmp_f1 * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->tmp_tmp_nn = DifAndCtrl_B->d47 * DifAndCtrl_B->D56_tmp_bj;
  DifAndCtrl_B->tmp_tmp_l = DifAndCtrl_B->d48 * DifAndCtrl_B->D46_tmp_tmp_p;
  DifAndCtrl_B->tmp_tmp_ce = DifAndCtrl_B->d49 * DifAndCtrl_B->D46_tmp_l;
  DifAndCtrl_B->tmp_tmp_p = DifAndCtrl_B->d48 * DifAndCtrl_B->D56_tmp_tmp_l;
  DifAndCtrl_B->tmp_tmp_dk = DifAndCtrl_B->tmp_tmp_js * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->tmp_tmp_oi = DifAndCtrl_B->tmp_tmp_ho * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->tmp_tmp_jr = DifAndCtrl_B->tmp_tmp_n * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->tmp_tmp_c2 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia1[8] * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d79 = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia2[8] * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d146 = DifAndCtrl_B->D14_tmp_my *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d80 = DifAndCtrl_B->d146 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d148 = DifAndCtrl_B->d8 * DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d81 = DifAndCtrl_B->d148 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d149 = DifAndCtrl_B->D16_tmp * DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d82 = DifAndCtrl_B->d149 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->d83 = DifAndCtrl_B->d50 * DifAndCtrl_B->D46_tmp_j;
  DifAndCtrl_B->tmp_tmp_dv *= DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->tmp_tmp_jo *= DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->tmp_tmp_f1 *= DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->d84 = DifAndCtrl_B->d47 * DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->d85 = DifAndCtrl_B->d48 * DifAndCtrl_B->D46_tmp_tmp_c;
  DifAndCtrl_B->d86 = DifAndCtrl_B->d51 * DifAndCtrl_B->D46_tmp_d;
  DifAndCtrl_B->d87 = DifAndCtrl_B->d48 * DifAndCtrl_B->D56_tmp_tmp_p;
  DifAndCtrl_B->tmp_tmp_js *= DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->tmp_tmp_ho *= DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->tmp_tmp_n *= DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->d88 = DifAndCtrl_B->d40 * DifAndCtrl_P.ArmConstants.Inertia1[7] *
    DifAndCtrl_B->D17_tmp_e;
  DifAndCtrl_B->d89 = DifAndCtrl_B->D27_tmp_n *
    DifAndCtrl_P.ArmConstants.Inertia1[7] * DifAndCtrl_B->D17_tmp_e;
  DifAndCtrl_B->tmp_tmp_ji *= DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->tmp_tmp_oo *= DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->tmp_tmp_fr *= DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->tmp_tmp_oy *= DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->d90 = DifAndCtrl_B->d40 * DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D17_tmp_o;
  DifAndCtrl_B->d91 = DifAndCtrl_B->D27_tmp_n *
    DifAndCtrl_P.ArmConstants.Inertia2[7] * DifAndCtrl_B->D17_tmp_o;
  DifAndCtrl_B->d92 = DifAndCtrl_B->D14_tmp *
    DifAndCtrl_P.ArmConstants.Inertia2[7] * DifAndCtrl_B->D17_tmp_o;
  DifAndCtrl_B->tmp_tmp_lu *= DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->tmp_tmp_gf *= DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->tmp_tmp_d4 *= DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->tmp_tmp_h *= DifAndCtrl_B->D28;
  DifAndCtrl_B->d93 = DifAndCtrl_B->d52 * DifAndCtrl_B->D46_tmp_g;
  DifAndCtrl_B->d94 = DifAndCtrl_B->tmp_tmp_f * DifAndCtrl_B->D56_tmp_d;
  DifAndCtrl_B->d95 = DifAndCtrl_B->d53 * DifAndCtrl_B->D46_tmp_dy;
  DifAndCtrl_B->d96 = DifAndCtrl_B->tmp_tmp_ln * DifAndCtrl_B->D56_tmp_lx;
  DifAndCtrl_B->d97 = DifAndCtrl_B->d54 * DifAndCtrl_B->D46_tmp_b;
  DifAndCtrl_B->tmp_tmp_f *= DifAndCtrl_B->D56_tmp_b;
  DifAndCtrl_B->d98 = DifAndCtrl_B->d55 * DifAndCtrl_B->D46_tmp_ln;
  DifAndCtrl_B->tmp_tmp_ln *= DifAndCtrl_B->D56_tmp_h;
  DifAndCtrl_B->d147 = DifAndCtrl_B->d39 * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d39 *= DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->dv[28] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((DifAndCtrl_B->d36 * DifAndCtrl_B->D56_tmp_tmp_a + DifAndCtrl_B->d10) -
    DifAndCtrl_B->d37 * DifAndCtrl_B->D56_tmp_tmp_a) + DifAndCtrl_B->d38 *
    DifAndCtrl_B->D56_tmp_tmp_a) + DifAndCtrl_B->d35 *
    DifAndCtrl_B->D56_tmp_tmp_a) + DifAndCtrl_B->d45 *
    DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->d32 *
    DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->tmp_tmp_b) + DifAndCtrl_B->d45 *
    DifAndCtrl_B->D27) + DifAndCtrl_B->d32 * DifAndCtrl_B->D27) -
    DifAndCtrl_B->tmp_tmp_e) + DifAndCtrl_B->tmp_tmp_dd) +
    DifAndCtrl_B->tmp_tmp_ik) + DifAndCtrl_B->tmp_tmp_nn) +
    DifAndCtrl_B->tmp_tmp_l) + DifAndCtrl_B->d33 * DifAndCtrl_B->D46_tmp_tmp_b)
    + DifAndCtrl_B->tmp_tmp_ce) + DifAndCtrl_B->d33 *
    DifAndCtrl_B->D56_tmp_tmp_o) + DifAndCtrl_B->tmp_tmp_p) -
    DifAndCtrl_B->tmp_tmp_dk) + DifAndCtrl_B->tmp_tmp_oi) +
    DifAndCtrl_B->tmp_tmp_jr) + DifAndCtrl_B->tmp_tmp_c2) + DifAndCtrl_B->d79) +
    DifAndCtrl_B->D16_tmp * DifAndCtrl_P.HexaConstants.Inertia[0] *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->d80) + DifAndCtrl_B->d147 *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->d81) + DifAndCtrl_B->d39 *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->d82) + DifAndCtrl_B->d36 *
    DifAndCtrl_B->D56_tmp_tmp_f) - DifAndCtrl_B->d37 *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d38 *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d35 *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d45 *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->d32 *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->d83) + DifAndCtrl_B->d45 *
    DifAndCtrl_B->D56_tmp_tmp_m) + DifAndCtrl_B->d32 *
    DifAndCtrl_B->D56_tmp_tmp_m) - DifAndCtrl_B->tmp_tmp_dv) +
    DifAndCtrl_B->tmp_tmp_jo) + DifAndCtrl_B->tmp_tmp_f1) + DifAndCtrl_B->d84) +
    DifAndCtrl_B->d85) + DifAndCtrl_B->d33 * DifAndCtrl_B->D46_tmp_tmp_n) +
    DifAndCtrl_B->d86) + DifAndCtrl_B->d33 * DifAndCtrl_B->D56_tmp_tmp_h2) +
    DifAndCtrl_B->d87) - DifAndCtrl_B->tmp_tmp_js) + DifAndCtrl_B->tmp_tmp_ho) +
    DifAndCtrl_B->tmp_tmp_n) + DifAndCtrl_B->d28 * DifAndCtrl_B->D17) +
    DifAndCtrl_B->d29 * DifAndCtrl_B->D17) + DifAndCtrl_B->d30 *
    DifAndCtrl_B->D17) + DifAndCtrl_B->d23 * DifAndCtrl_B->D17) +
    DifAndCtrl_B->d88) + DifAndCtrl_B->d89) + DifAndCtrl_B->tmp_tmp_ji) +
    DifAndCtrl_B->tmp_tmp_oo) + DifAndCtrl_B->tmp_tmp_fr) +
    DifAndCtrl_B->tmp_tmp_oy) + DifAndCtrl_B->d25 * DifAndCtrl_B->D18) +
                       DifAndCtrl_B->tmp_tmp_i * DifAndCtrl_B->D18) +
                      DifAndCtrl_B->d90) + DifAndCtrl_B->d91) +
                    DifAndCtrl_B->d92) + DifAndCtrl_B->tmp_tmp_lu) +
                  DifAndCtrl_B->tmp_tmp_gf) + DifAndCtrl_B->tmp_tmp_d4) +
                DifAndCtrl_B->d26 * DifAndCtrl_B->D56_tmp_tmp_c) +
               DifAndCtrl_B->tmp_tmp_h) + DifAndCtrl_B->d93) + DifAndCtrl_B->d94)
            + DifAndCtrl_B->d95) + DifAndCtrl_B->d96) + DifAndCtrl_B->d97) +
         DifAndCtrl_B->tmp_tmp_f) + DifAndCtrl_B->d98) +
       DifAndCtrl_B->tmp_tmp_ln) * 0.25);
  DifAndCtrl_B->d23 = DifAndCtrl_B->D25 * DifAndCtrl_B->rtb_ginv_tmp_n +
    DifAndCtrl_B->D15 * DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->d25 = DifAndCtrl_B->D46_tmp_tmp_g4 * DifAndCtrl_B->D28;
  DifAndCtrl_B->tmp_tmp_i = 2.0 * DifAndCtrl_X->Integrator1_CSTATE[7];
  DifAndCtrl_B->d26 = -DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->d28 = DifAndCtrl_B->D24_tmp * DifAndCtrl_B->smax;
  DifAndCtrl_B->d29 = DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->D18;
  DifAndCtrl_B->d30 = DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->d35 = DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D56_tmp_tmp_c;
  DifAndCtrl_B->d36 = (DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->x_tmp_b +
                       DifAndCtrl_B->D48_tmp * DifAndCtrl_B->D15_tmp) +
    (DifAndCtrl_B->D47_tmp + DifAndCtrl_B->D34) * DifAndCtrl_B->D15_tmp_m;
  DifAndCtrl_B->dv[36] = -((((((((((((((((((DifAndCtrl_B->d23 - DifAndCtrl_B->d9)
    + DifAndCtrl_B->D16_tmp_m) - DifAndCtrl_B->d11) - DifAndCtrl_B->d13) +
    DifAndCtrl_B->D16_tmp_a) - DifAndCtrl_B->d19) - DifAndCtrl_B->D14_tmp_m3) -
    DifAndCtrl_B->rtb_ginv_tmp_tmp_g) + DifAndCtrl_B->D46_tmp_mx *
    DifAndCtrl_B->D18) + DifAndCtrl_B->D46_tmp_pr * DifAndCtrl_B->D18) +
    DifAndCtrl_B->rtb_ginv_tmp_o2) - DifAndCtrl_B->D16_tmp_j) -
    DifAndCtrl_B->D27_tmp) + DifAndCtrl_B->D46_tmp_dz *
    DifAndCtrl_B->D56_tmp_tmp_c) + DifAndCtrl_B->d25) *
    DifAndCtrl_X->Integrator1_CSTATE[3] + (-2.0 *
    DifAndCtrl_X->Integrator1_CSTATE[7] * DifAndCtrl_B->d36 *
    DifAndCtrl_B->D17_tmp_o + DifAndCtrl_B->tmp_tmp_i *
    DifAndCtrl_P.ArmConstants.Inertia2[3] * DifAndCtrl_B->D46_tmp_tmp_m)) +
    (((((((((((((-DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
                 DifAndCtrl_P.ArmConstants.l1_dim *
                 DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->smax +
                 (DifAndCtrl_B->d23 - DifAndCtrl_B->d28)) +
                DifAndCtrl_B->D16_tmp_a) - DifAndCtrl_B->d19) -
              DifAndCtrl_B->D14_tmp_m3) - DifAndCtrl_B->rtb_ginv_tmp_tmp_g) +
            DifAndCtrl_B->d26 * DifAndCtrl_B->D18) - DifAndCtrl_B->d29) -
          DifAndCtrl_B->d30) + DifAndCtrl_B->rtb_ginv_tmp_o2) -
        DifAndCtrl_B->D16_tmp_j) - DifAndCtrl_B->D27_tmp) - DifAndCtrl_B->d35) +
     DifAndCtrl_B->d25) * DifAndCtrl_X->Integrator1_CSTATE[6]) * 0.5);
  DifAndCtrl_B->d9 = 4.0 * DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->D16_tmp_m = 4.0 * DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->d11 = -4.0 * DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->d13 = -4.0 * DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->d23 = DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D46_tmp_tmp_b;
  DifAndCtrl_B->d25 = DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D56_tmp_tmp_o;
  DifAndCtrl_B->d37 = DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D46_tmp_tmp_n;
  DifAndCtrl_B->d38 = DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D56_tmp_tmp_h2;
  DifAndCtrl_B->d100 = DifAndCtrl_B->D47_tmp_c * DifAndCtrl_B->D46_tmp_tmp_k;
  DifAndCtrl_B->D47_tmp_c = DifAndCtrl_B->D24_tmp * DifAndCtrl_B->D46_tmp_tmp_hc;
  DifAndCtrl_B->d101 = DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->D46_tmp_tmp_hc;
  DifAndCtrl_B->d102 = DifAndCtrl_B->D48_tmp * DifAndCtrl_B->D46_tmp_tmp_p +
    DifAndCtrl_B->d23;
  DifAndCtrl_B->d103 = DifAndCtrl_B->D48_tmp * DifAndCtrl_B->D46_tmp_tmp_c;
  DifAndCtrl_B->D14_tmp_j = ((DifAndCtrl_B->d100 + DifAndCtrl_B->D14_tmp_j) +
    DifAndCtrl_B->D24_tmp * DifAndCtrl_B->D27) + DifAndCtrl_B->D24_tmp_l *
    DifAndCtrl_B->D27;
  DifAndCtrl_B->d192 = DifAndCtrl_B->D24_tmp * DifAndCtrl_B->D56_tmp_tmp_m;
  DifAndCtrl_B->d193 = DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->D56_tmp_tmp_m;
  DifAndCtrl_B->D14_tmp_h =
    (((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B->D14_tmp_j -
    DifAndCtrl_B->D14_tmp_h) + DifAndCtrl_B->D14_tmp_tmp_pm) +
    DifAndCtrl_B->D14_tmp_tmp_p2) + DifAndCtrl_B->D14_tmp_ct) +
    DifAndCtrl_B->D15_tmp_tmp_c) + DifAndCtrl_B->d23) +
    DifAndCtrl_B->D15_tmp_tmp_f) + DifAndCtrl_B->d25) +
    DifAndCtrl_B->D16_tmp_tmp) - DifAndCtrl_B->D34_tmp_e) +
    DifAndCtrl_B->D37_tmp) + DifAndCtrl_B->D46_tmp_tmp_ft) +
    DifAndCtrl_B->rtb_ginv_tmp_oc) + DifAndCtrl_B->d56) + DifAndCtrl_B->d57) +
    DifAndCtrl_B->d58) + DifAndCtrl_B->d59) + DifAndCtrl_B->D47_tmp_c) +
    DifAndCtrl_B->d101) + DifAndCtrl_B->d60) + DifAndCtrl_B->d192) +
    DifAndCtrl_B->d193) - DifAndCtrl_B->d61) + DifAndCtrl_B->d62) +
                     DifAndCtrl_B->d63) + DifAndCtrl_B->d64) + DifAndCtrl_B->d65)
                  + DifAndCtrl_B->d37) + DifAndCtrl_B->d66) + DifAndCtrl_B->d38)
               + DifAndCtrl_B->d67) - DifAndCtrl_B->d68) + DifAndCtrl_B->d69) +
            DifAndCtrl_B->d70) + DifAndCtrl_B->d71) + DifAndCtrl_B->d72) +
         DifAndCtrl_B->d73) + DifAndCtrl_B->d74) + DifAndCtrl_B->d75) +
      DifAndCtrl_B->d76) + DifAndCtrl_B->d77) + DifAndCtrl_B->d78;
  DifAndCtrl_B->d197 = (((((((((((((((((((DifAndCtrl_B->d102 +
    DifAndCtrl_B->D15_tmp_tmp_f) + DifAndCtrl_B->d25) + DifAndCtrl_B->D48_tmp *
    DifAndCtrl_B->D56_tmp_tmp_l) - DifAndCtrl_B->D34_tmp_e) +
    DifAndCtrl_B->D37_tmp) + DifAndCtrl_B->D46_tmp_tmp_ft) + DifAndCtrl_B->d56)
    + DifAndCtrl_B->d58) + DifAndCtrl_B->d103) + DifAndCtrl_B->d37) +
    DifAndCtrl_B->d66) + DifAndCtrl_B->d38) + DifAndCtrl_B->D48_tmp *
    DifAndCtrl_B->D56_tmp_tmp_p) - DifAndCtrl_B->d68) + DifAndCtrl_B->d69) +
    DifAndCtrl_B->d70) + DifAndCtrl_B->d73) + DifAndCtrl_B->d74) +
                        DifAndCtrl_B->d77) + DifAndCtrl_B->d78;
  DifAndCtrl_B->dv[44] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B
    ->d9 * DifAndCtrl_B->rtb_ginv_tmp_tmp_l + DifAndCtrl_B->D16_tmp_m *
    DifAndCtrl_B->D68) + DifAndCtrl_B->D25 * DifAndCtrl_B->rtb_ginv_tmp_ie) +
    DifAndCtrl_B->D15 * DifAndCtrl_B->D46_tmp_tmp_i) + DifAndCtrl_B->D56_tmp_m *
    DifAndCtrl_B->d) + DifAndCtrl_B->D56_tmp_mc * DifAndCtrl_B->D46_tmp_tmp_g) +
    DifAndCtrl_B->d9 * DifAndCtrl_B->d1) + DifAndCtrl_B->D16_tmp_m *
    DifAndCtrl_B->d2) + DifAndCtrl_B->D46_tmp_tmp_g4 * DifAndCtrl_B->D46_tmp_tmp)
    + DifAndCtrl_B->D46_tmp_mx * DifAndCtrl_B->d3) + DifAndCtrl_B->D46_tmp_pr *
    DifAndCtrl_B->d3) + DifAndCtrl_B->d11 * DifAndCtrl_B->ab_a) +
    DifAndCtrl_B->D46_tmp_mx * DifAndCtrl_B->D56_tmp_tmp_e) +
    DifAndCtrl_B->D46_tmp_pr * DifAndCtrl_B->D56_tmp_tmp_e) +
    DifAndCtrl_B->D46_tmp_tmp_g4 * DifAndCtrl_B->d6) + DifAndCtrl_B->D46_tmp_dz *
    DifAndCtrl_B->D37) + DifAndCtrl_B->d13 * DifAndCtrl_B->D67) +
    DifAndCtrl_B->D46_tmp_dz * DifAndCtrl_B->D56_tmp_tmp_h) +
    DifAndCtrl_P.HexaConstants.Inertia[8] * DifAndCtrl_B->d4) +
    DifAndCtrl_P.ArmConstants.Inertia1[0] * DifAndCtrl_B->D38) -
    DifAndCtrl_P.ArmConstants.Inertia1[4] * DifAndCtrl_B->D38) -
    DifAndCtrl_B->D47_tmp_p * DifAndCtrl_B->D38) - DifAndCtrl_B->D47_tmp_px *
    DifAndCtrl_B->D38) + DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D47_tmp_m) - DifAndCtrl_P.ArmConstants.Inertia2[4] *
    DifAndCtrl_B->D47_tmp_m) + -DifAndCtrl_B->D46_tmp_mj *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D47_tmp_m) + -2.0 *
    DifAndCtrl_P.ArmConstants.Inertia1[0] * DifAndCtrl_B->D46_tmp_pb) + -2.0 *
    DifAndCtrl_P.ArmConstants.Inertia1[4] * DifAndCtrl_B->D46_tmp_pb) + 4.0 *
    DifAndCtrl_P.ArmConstants.Inertia1[8] * DifAndCtrl_B->D46_tmp_pb) + -2.0 *
    DifAndCtrl_P.ArmConstants.Inertia2[0] * DifAndCtrl_B->D46_tmp_pb) + -2.0 *
    DifAndCtrl_P.ArmConstants.Inertia2[4] * DifAndCtrl_B->D46_tmp_pb) + 4.0 *
    DifAndCtrl_P.ArmConstants.Inertia2[8] * DifAndCtrl_B->D46_tmp_pb) + 4.0 *
    DifAndCtrl_P.HexaConstants.Inertia[0] * DifAndCtrl_B->D46_tmp_pb) + -2.0 *
    DifAndCtrl_P.HexaConstants.Inertia[4] * DifAndCtrl_B->D46_tmp_pb) + -2.0 *
    DifAndCtrl_P.HexaConstants.Inertia[8] * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_B->d18 * DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d20 *
    DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d21 * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_B->D14_tmp_g1 * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_P.HexaConstants.Inertia[4] * DifAndCtrl_B->D47) +
    DifAndCtrl_B->D56_tmp_ap * DifAndCtrl_B->D47) + DifAndCtrl_B->D56_tmp_jd *
    DifAndCtrl_B->D47) + DifAndCtrl_P.HexaConstants.Inertia[4] *
    DifAndCtrl_B->D48_tmp_o) - DifAndCtrl_P.HexaConstants.Inertia[8] *
    DifAndCtrl_B->D48_tmp_o) + DifAndCtrl_B->D56_tmp_ap *
    DifAndCtrl_B->D48_tmp_o) + DifAndCtrl_B->D56_tmp_jd *
    DifAndCtrl_B->D48_tmp_o) - DifAndCtrl_P.ArmConstants.Inertia1[0] *
                        DifAndCtrl_B->D56_tmp_tmp) +
                       DifAndCtrl_P.ArmConstants.Inertia1[4] *
                       DifAndCtrl_B->D56_tmp_tmp) + DifAndCtrl_B->D47_tmp_p *
                      DifAndCtrl_B->D56_tmp_tmp) + DifAndCtrl_B->D47_tmp_px *
                     DifAndCtrl_B->D56_tmp_tmp) -
                    DifAndCtrl_P.ArmConstants.Inertia2[0] * DifAndCtrl_B->D58) +
                   DifAndCtrl_P.ArmConstants.Inertia2[4] * DifAndCtrl_B->D58) +
                  DifAndCtrl_B->D47_tmp * DifAndCtrl_B->D58) +
                 DifAndCtrl_B->D46_tmp_cs * DifAndCtrl_B->d5) +
                DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->d5) + DifAndCtrl_B->d11 *
               DifAndCtrl_B->D15_tmp_tmp) + DifAndCtrl_B->D46_tmp_f *
              DifAndCtrl_B->d7) + DifAndCtrl_B->D46_tmp_p4 *
             DifAndCtrl_B->D14_tmp_tmp) + DifAndCtrl_B->d13 *
            DifAndCtrl_B->D15_tmp_tmp_i) + DifAndCtrl_B->D46_tmp_cs *
           DifAndCtrl_B->y_a) + DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->y_a) +
         DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->D48_tmp_tmp) +
        DifAndCtrl_B->D46_tmp_f * DifAndCtrl_B->D46_tmp_tmp_f) * (-0.5 *
        DifAndCtrl_X->Integrator1_CSTATE[5]) + ((DifAndCtrl_B->D14_tmp_h *
         DifAndCtrl_X->Integrator1_CSTATE[6] + DifAndCtrl_B->d197 *
         DifAndCtrl_X->Integrator1_CSTATE[7]) + DifAndCtrl_B->D14_tmp_md *
        DifAndCtrl_X->Integrator1_CSTATE[3])) * 0.25);
  DifAndCtrl_B->D38 = DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D47 = DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D48_tmp_o = DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->D58 = DifAndCtrl_B->D48_tmp_o *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d4 = DifAndCtrl_B->D46_tmp_na * DifAndCtrl_X->
    Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
    DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D14_tmp_i = DifAndCtrl_B->d22 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d9 = DifAndCtrl_B->D46_tmp_lm * DifAndCtrl_X->
    Integrator1_CSTATE[4];
  DifAndCtrl_B->D16_tmp_m = DifAndCtrl_B->d9 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d11 = DifAndCtrl_B->D58 * DifAndCtrl_B->D46_tmp_tmp_b;
  DifAndCtrl_B->d13 = DifAndCtrl_B->D58 * DifAndCtrl_B->D56_tmp_tmp_o;
  DifAndCtrl_B->d18 = DifAndCtrl_B->D58 * DifAndCtrl_B->D46_tmp_tmp_n;
  DifAndCtrl_B->d20 = DifAndCtrl_B->D58 * DifAndCtrl_B->D56_tmp_tmp_h2;
  DifAndCtrl_B->d21 = DifAndCtrl_B->D16_tmp_m * DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->D14_tmp_g1 = DifAndCtrl_B->D16_tmp_m *
    DifAndCtrl_B->D56_tmp_tmp_c;
  DifAndCtrl_B->dv[52] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B
    ->D38 * DifAndCtrl_B->D46_tmp_tmp_k + DifAndCtrl_B->d10) + DifAndCtrl_B->D47
    * DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->tmp_tmp_b) +
    DifAndCtrl_B->D38 * DifAndCtrl_B->D27) + DifAndCtrl_B->D47 *
    DifAndCtrl_B->D27) - DifAndCtrl_B->tmp_tmp_e) + DifAndCtrl_B->tmp_tmp_dd) +
    DifAndCtrl_B->tmp_tmp_ik) + DifAndCtrl_B->tmp_tmp_nn) +
    DifAndCtrl_B->tmp_tmp_l) + DifAndCtrl_B->d11) + DifAndCtrl_B->tmp_tmp_ce) +
    DifAndCtrl_B->d13) + DifAndCtrl_B->tmp_tmp_p) - DifAndCtrl_B->tmp_tmp_dk) +
    DifAndCtrl_B->tmp_tmp_oi) + DifAndCtrl_B->tmp_tmp_jr) +
    DifAndCtrl_B->tmp_tmp_c2) + DifAndCtrl_B->d79) + DifAndCtrl_B->d80) +
    DifAndCtrl_B->d81) + DifAndCtrl_B->d82) + DifAndCtrl_B->D38 *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->D47 *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->d83) + DifAndCtrl_B->D38 *
    DifAndCtrl_B->D56_tmp_tmp_m) + DifAndCtrl_B->D47 *
    DifAndCtrl_B->D56_tmp_tmp_m) - DifAndCtrl_B->tmp_tmp_dv) +
    DifAndCtrl_B->tmp_tmp_jo) + DifAndCtrl_B->tmp_tmp_f1) + DifAndCtrl_B->d84) +
    DifAndCtrl_B->d85) + DifAndCtrl_B->d18) + DifAndCtrl_B->d86) +
    DifAndCtrl_B->d20) + DifAndCtrl_B->d87) - DifAndCtrl_B->tmp_tmp_js) +
    DifAndCtrl_B->tmp_tmp_ho) + DifAndCtrl_B->tmp_tmp_n) + DifAndCtrl_B->d4 *
    DifAndCtrl_B->smax) + DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->smax) +
    DifAndCtrl_B->d88) + DifAndCtrl_B->d89) + DifAndCtrl_B->tmp_tmp_ji) +
    DifAndCtrl_B->tmp_tmp_oo) + DifAndCtrl_B->tmp_tmp_fr) +
    DifAndCtrl_B->tmp_tmp_oy) + DifAndCtrl_B->d4 * DifAndCtrl_B->D18) +
                        DifAndCtrl_B->D14_tmp_i * DifAndCtrl_B->D18) +
                       DifAndCtrl_B->d21) + DifAndCtrl_B->d90) +
                     DifAndCtrl_B->d91) + DifAndCtrl_B->d92) +
                   DifAndCtrl_B->tmp_tmp_lu) + DifAndCtrl_B->tmp_tmp_gf) +
                 DifAndCtrl_B->tmp_tmp_d4) + DifAndCtrl_B->D14_tmp_g1) +
               DifAndCtrl_B->tmp_tmp_h) + DifAndCtrl_B->d93) + DifAndCtrl_B->d94)
            + DifAndCtrl_B->d95) + DifAndCtrl_B->d96) + DifAndCtrl_B->d97) +
         DifAndCtrl_B->tmp_tmp_f) + DifAndCtrl_B->d98) +
       DifAndCtrl_B->tmp_tmp_ln) * 0.25);
  DifAndCtrl_B->D48_tmp_o = DifAndCtrl_B->D48_tmp_o *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d9 = DifAndCtrl_B->d9 * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->dv[60] = -((((((((((((((((((((((((((((((((((DifAndCtrl_B->d16 *
    4.0 * DifAndCtrl_P.ArmConstants.Inertia2[6] * DifAndCtrl_B->D15_tmp_m +
    DifAndCtrl_B->tmp_tmp_o) + DifAndCtrl_B->D48_tmp_o *
    DifAndCtrl_B->D46_tmp_tmp_p) + DifAndCtrl_B->d11) + DifAndCtrl_B->tmp_tmp_ce)
    + DifAndCtrl_B->d13) + DifAndCtrl_B->D48_tmp_o * DifAndCtrl_B->D56_tmp_tmp_l)
    - DifAndCtrl_B->tmp_tmp_dk) + DifAndCtrl_B->tmp_tmp_oi) +
    DifAndCtrl_B->tmp_tmp_jr) + DifAndCtrl_B->d79) + DifAndCtrl_B->d81) +
    DifAndCtrl_B->D48_tmp_o * DifAndCtrl_B->D46_tmp_tmp_c) + DifAndCtrl_B->d18)
    + DifAndCtrl_B->d86) + DifAndCtrl_B->d20) + DifAndCtrl_B->D48_tmp_o *
    DifAndCtrl_B->D56_tmp_tmp_p) - DifAndCtrl_B->tmp_tmp_js) +
    DifAndCtrl_B->tmp_tmp_ho) + DifAndCtrl_B->tmp_tmp_n) + DifAndCtrl_B->d9 *
    DifAndCtrl_B->s) + DifAndCtrl_B->d21) + DifAndCtrl_B->d90) +
    DifAndCtrl_B->d91) + DifAndCtrl_B->d92) + DifAndCtrl_B->tmp_tmp_lu) +
    DifAndCtrl_B->tmp_tmp_gf) + DifAndCtrl_B->tmp_tmp_d4) +
    DifAndCtrl_B->D14_tmp_g1) + DifAndCtrl_B->d9 * DifAndCtrl_B->D28) +
    DifAndCtrl_B->d95) + DifAndCtrl_B->d96) + DifAndCtrl_B->d98) +
    DifAndCtrl_B->tmp_tmp_ln) * 0.25);
  DifAndCtrl_B->d10 = DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D46_tmp_l;
  DifAndCtrl_B->d11 = DifAndCtrl_P.ArmConstants.Inertia2[7] *
    DifAndCtrl_B->D46_tmp_d;
  DifAndCtrl_B->d13 = DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D46_tmp_dy;
  DifAndCtrl_B->d16 = DifAndCtrl_P.ArmConstants.Inertia2[6] *
    DifAndCtrl_B->D46_tmp_ln;
  DifAndCtrl_B->d18 = DifAndCtrl_B->D56_tmp_mc * DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->d20 = DifAndCtrl_B->D46_tmp_tmp_g4 * DifAndCtrl_B->D46_tmp_a;
  DifAndCtrl_B->d21 = DifAndCtrl_B->D56_tmp_m * DifAndCtrl_B->D46_tmp_n;
  DifAndCtrl_B->D14_tmp_g1 = DifAndCtrl_P.ArmConstants.Inertia2[0] *
    DifAndCtrl_B->D56_tmp_h;
  DifAndCtrl_B->D14_tmp_md = (DifAndCtrl_B->d102 + DifAndCtrl_B->d10) -
    DifAndCtrl_B->d103;
  DifAndCtrl_B->d10 = (((((((((((DifAndCtrl_P.ArmConstants.Inertia1[7] *
    DifAndCtrl_B->D46_tmp_p + DifAndCtrl_B->d100) + DifAndCtrl_B->d23) +
    DifAndCtrl_B->d10) - DifAndCtrl_B->D47_tmp_c) - DifAndCtrl_B->d101) +
    DifAndCtrl_P.ArmConstants.Inertia1[7] * DifAndCtrl_B->D46_tmp_j) -
    DifAndCtrl_B->d37) + DifAndCtrl_B->d11) +
    DifAndCtrl_P.ArmConstants.Inertia1[6] * DifAndCtrl_B->D46_tmp_g) +
                        DifAndCtrl_B->d13) + DifAndCtrl_P.ArmConstants.Inertia1
                       [6] * DifAndCtrl_B->D46_tmp_b) + DifAndCtrl_B->d16;
  DifAndCtrl_B->dv[29] = -(((((((((((((((((((((DifAndCtrl_B->rtb_ginv_tmp_d -
    DifAndCtrl_B->tmp_tmp_d * DifAndCtrl_B->rtb_ginv_tmp_o) +
    DifAndCtrl_B->rtb_ginv_tmp_ox) + DifAndCtrl_P.ArmConstants.Inertia1[0] *
    DifAndCtrl_B->rtb_ginv_tmp_n) - DifAndCtrl_B->rtb_ginv_tmp_g) -
    DifAndCtrl_B->rtb_ginv_tmp_l) - DifAndCtrl_B->rtb_ginv_tmp_f) +
    DifAndCtrl_B->D46_tmp_mx * DifAndCtrl_B->D46_tmp_da) +
    DifAndCtrl_B->D46_tmp_pr * DifAndCtrl_B->D46_tmp_da) +
    DifAndCtrl_B->D47_tmp_i) + DifAndCtrl_B->rtb_ginv_tmp_k) + DifAndCtrl_B->D14)
    - DifAndCtrl_B->D24) - DifAndCtrl_B->D35) + DifAndCtrl_B->D46_tmp_dz *
    DifAndCtrl_B->rtb_ginv_tmp) + DifAndCtrl_B->d20) + DifAndCtrl_B->d21) +
    DifAndCtrl_B->d18) * DifAndCtrl_B->d22 + DifAndCtrl_B->D45 *
    DifAndCtrl_B->d99) + (((DifAndCtrl_B->D56_tmp - DifAndCtrl_B->D14_tmp_g1) +
    DifAndCtrl_B->D56_tmp_cx) + DifAndCtrl_B->D56_tmp_i) *
    DifAndCtrl_X->Integrator1_CSTATE[5]) * DifAndCtrl_B->x_tmp_cv +
    (((((-DifAndCtrl_P.ArmConstants.MC2 *
         DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
         DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D46_tmp_tmp_n +
         DifAndCtrl_B->D14_tmp_md) + DifAndCtrl_B->d11) + DifAndCtrl_B->d13) +
      DifAndCtrl_B->d16) * DifAndCtrl_B->tmp_tmp_i + DifAndCtrl_B->d10 *
     DifAndCtrl_B->tmp_tmp)) * 0.25);
  DifAndCtrl_B->tmp_tmp = 2.0 * DifAndCtrl_X->Integrator1_CSTATE[3];
  DifAndCtrl_B->tmp_tmp_d = DifAndCtrl_B->tmp_tmp * DifAndCtrl_B->D46_tmp_tmp_h;
  DifAndCtrl_B->D15_tmp_m = DifAndCtrl_B->tmp_tmp_j *
    DifAndCtrl_X->Integrator1_CSTATE[3];
  DifAndCtrl_B->D45 = 4.0 * DifAndCtrl_P.ArmConstants.MC2;
  DifAndCtrl_B->D46_tmp_lm = DifAndCtrl_B->D45 *
    DifAndCtrl_X->Integrator1_CSTATE[3];
  DifAndCtrl_B->tmp_tmp_j = DifAndCtrl_B->d40 * DifAndCtrl_B->D46_tmp_tmp_h;
  DifAndCtrl_B->tmp_tmp_i = DifAndCtrl_B->tmp_tmp *
    DifAndCtrl_P.HexaConstants.Inertia[4];
  DifAndCtrl_B->tmp_tmp_h = DifAndCtrl_B->tmp_tmp_g *
    DifAndCtrl_P.HexaConstants.Inertia[8];
  DifAndCtrl_B->tmp_tmp_n = DifAndCtrl_B->tmp_tmp_d *
    DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->tmp_tmp_d *= DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_o = DifAndCtrl_B->d12 * DifAndCtrl_B->D46_tmp_tmp_h;
  DifAndCtrl_B->D46_tmp_mj = DifAndCtrl_B->tmp_tmp_c *
    DifAndCtrl_X->Integrator1_CSTATE[3] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D46_tmp_f = DifAndCtrl_B->d40 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_cs = 4.0 * DifAndCtrl_P.ArmConstants.MC1;
  DifAndCtrl_B->D46_tmp_k = DifAndCtrl_B->D46_tmp_cs *
    DifAndCtrl_X->Integrator1_CSTATE[3] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D46_tmp_p4 = DifAndCtrl_B->d99 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_c = DifAndCtrl_B->tmp_tmp_g *
    DifAndCtrl_P.ArmConstants.Inertia1[0];
  DifAndCtrl_B->tmp_tmp_b = DifAndCtrl_B->tmp_tmp *
    DifAndCtrl_P.ArmConstants.Inertia1[4];
  DifAndCtrl_B->tmp_tmp_e = DifAndCtrl_B->D14_tmp_my *
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->tmp_tmp_dd = DifAndCtrl_B->tmp_tmp * DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_na = DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D15_tmp_m = DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D47_tmp = DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D46_tmp_lm = DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_ik = DifAndCtrl_B->D45 *
    DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->tmp_tmp_g *= DifAndCtrl_P.ArmConstants.Inertia2[0];
  DifAndCtrl_B->tmp_tmp *= DifAndCtrl_P.ArmConstants.Inertia2[4];
  DifAndCtrl_B->tmp_tmp_nn = DifAndCtrl_B->d8 * DifAndCtrl_X->
    Integrator1_CSTATE[3] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp_l = DifAndCtrl_B->D14_tmp_mv *
    DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->tmp_tmp_ce = DifAndCtrl_B->D14_tmp_mv *
    DifAndCtrl_P.ArmConstants.Inertia2[6];
  DifAndCtrl_B->tmp_tmp_p = DifAndCtrl_B->D47_tmp_tmp *
    DifAndCtrl_B->rtb_ginv_tmp;
  DifAndCtrl_B->tmp_tmp_dk = DifAndCtrl_B->d99 *
    DifAndCtrl_P.ArmConstants.Inertia1[3];
  DifAndCtrl_B->tmp_tmp_oi = DifAndCtrl_B->d99 *
    DifAndCtrl_P.ArmConstants.Inertia2[3];
  DifAndCtrl_B->tmp_tmp_jr = DifAndCtrl_B->d127 *
    DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->tmp_tmp_c2 = DifAndCtrl_B->d127 *
    DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->D47_tmp_tmp = DifAndCtrl_P.ArmConstants.Inertia1[0] -
    DifAndCtrl_P.ArmConstants.Inertia1[4];
  DifAndCtrl_B->D56_tmp = DifAndCtrl_B->d14 *
    DifAndCtrl_P.ArmConstants.Inertia1[3];
  DifAndCtrl_B->D56_tmp_mc = DifAndCtrl_B->d22 *
    DifAndCtrl_P.ArmConstants.Inertia1[0];
  DifAndCtrl_B->D56_tmp_ap = DifAndCtrl_B->d12 *
    DifAndCtrl_P.ArmConstants.Inertia1[4];
  DifAndCtrl_B->D56_tmp_jd = DifAndCtrl_B->D14_tmp_my *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->rtb_ginv_tmp = DifAndCtrl_B->d12 * DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->rtb_ginv_tmp_o = DifAndCtrl_B->d14 *
    DifAndCtrl_P.ArmConstants.Inertia2[3];
  DifAndCtrl_B->rtb_ginv_tmp_ox = DifAndCtrl_B->tmp_tmp_ik *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->rtb_ginv_tmp_k = DifAndCtrl_B->d22 *
    DifAndCtrl_P.ArmConstants.Inertia2[0];
  DifAndCtrl_B->rtb_ginv_tmp_d = DifAndCtrl_B->d12 *
    DifAndCtrl_P.ArmConstants.Inertia2[4];
  DifAndCtrl_B->rtb_ginv_tmp_g = DifAndCtrl_B->d8 *
    DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->rtb_ginv_tmp_l = DifAndCtrl_B->D46_tmp_mj *
    DifAndCtrl_B->D46_tmp_tmp_hc;
  DifAndCtrl_B->rtb_ginv_tmp_f = DifAndCtrl_B->D46_tmp_f *
    DifAndCtrl_B->D46_tmp_tmp_hc;
  DifAndCtrl_B->tmp_tmp_f = DifAndCtrl_B->D56_tmp * DifAndCtrl_B->d;
  DifAndCtrl_B->tmp_tmp_ji = DifAndCtrl_B->D56_tmp_mc * DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->tmp_tmp_oo = DifAndCtrl_B->D56_tmp_ap * DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->tmp_tmp_fr = DifAndCtrl_B->D56_tmp_jd * DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->tmp_tmp_oy = DifAndCtrl_B->rtb_ginv_tmp *
    DifAndCtrl_B->D56_tmp_f;
  DifAndCtrl_B->tmp_tmp_ln = DifAndCtrl_B->D15_tmp_m *
    DifAndCtrl_B->D46_tmp_tmp_n;
  DifAndCtrl_B->tmp_tmp_lu = DifAndCtrl_B->rtb_ginv_tmp_o *
    DifAndCtrl_B->D46_tmp_tmp_g;
  DifAndCtrl_B->tmp_tmp_gf = DifAndCtrl_B->rtb_ginv_tmp_ox *
    DifAndCtrl_B->D56_tmp_tmp_p;
  DifAndCtrl_B->tmp_tmp_d4 = DifAndCtrl_B->rtb_ginv_tmp_k *
    DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->tmp_tmp_dv = DifAndCtrl_B->rtb_ginv_tmp_d *
    DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->tmp_tmp_jo = DifAndCtrl_B->rtb_ginv_tmp_g *
    DifAndCtrl_B->D56_tmp_a;
  DifAndCtrl_B->tmp_tmp_f1 = DifAndCtrl_B->d14 *
    DifAndCtrl_P.ArmConstants.Inertia1[0];
  DifAndCtrl_B->tmp_tmp_js = DifAndCtrl_B->d14 *
    DifAndCtrl_P.ArmConstants.Inertia2[0];
  DifAndCtrl_B->tmp_tmp_ho = DifAndCtrl_B->D46_tmp_na *
    DifAndCtrl_B->D46_tmp_tmp_c;
  DifAndCtrl_B->D46_tmp_mj *= DifAndCtrl_B->D46_tmp_tmp_k;
  DifAndCtrl_B->D46_tmp_f *= DifAndCtrl_B->D46_tmp_tmp_k;
  DifAndCtrl_B->D15_tmp_m *= DifAndCtrl_B->D46_tmp_tmp_b;
  DifAndCtrl_B->D46_tmp_na *= DifAndCtrl_B->D46_tmp_tmp_p;
  DifAndCtrl_B->D46_tmp_tmp_g = DifAndCtrl_B->d47 * DifAndCtrl_B->D56_tmp_tmp;
  DifAndCtrl_B->d = DifAndCtrl_B->d161 * DifAndCtrl_B->D56_tmp_b;
  DifAndCtrl_B->D14_tmp_my = DifAndCtrl_B->D14_tmp_c0 * DifAndCtrl_B->D56_tmp_h;
  DifAndCtrl_B->d8 = DifAndCtrl_B->d48 * DifAndCtrl_B->D46_tmp_tmp_f;
  tmp =
    (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B->tmp_tmp_l *
    DifAndCtrl_B->rtb_ginv_tmp_tmp_l + DifAndCtrl_B->tmp_tmp_ce *
    DifAndCtrl_B->D68) + DifAndCtrl_B->tmp_tmp_i * DifAndCtrl_B->D56_tmp_tmp_a)
    + DifAndCtrl_B->d104) + DifAndCtrl_B->tmp_tmp_h *
    DifAndCtrl_B->D56_tmp_tmp_a) + DifAndCtrl_B->d105) + DifAndCtrl_B->tmp_tmp_n
    * DifAndCtrl_B->D56_tmp_tmp_a) + DifAndCtrl_B->d106) +
    DifAndCtrl_B->tmp_tmp_d * DifAndCtrl_B->D56_tmp_tmp_a) + DifAndCtrl_B->d107)
    + DifAndCtrl_B->D46_tmp_mj) + DifAndCtrl_B->D46_tmp_f) + DifAndCtrl_B->d108)
    + DifAndCtrl_B->d109) + DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->D27) +
    DifAndCtrl_B->d110) + DifAndCtrl_B->D46_tmp_p4 * DifAndCtrl_B->D27) +
    DifAndCtrl_B->d111) + DifAndCtrl_B->tmp_tmp_c * DifAndCtrl_B->D56_tmp_bj) +
    DifAndCtrl_B->d112) + DifAndCtrl_B->tmp_tmp_b * DifAndCtrl_B->D56_tmp_bj) +
    DifAndCtrl_B->d113) + DifAndCtrl_B->tmp_tmp_e * DifAndCtrl_B->D56_tmp_bj) +
    DifAndCtrl_B->d114) + DifAndCtrl_B->tmp_tmp_dd * DifAndCtrl_B->D56_tmp_bj) +
    DifAndCtrl_B->d115) + DifAndCtrl_B->D46_tmp_na) + DifAndCtrl_B->D15_tmp_m) +
    DifAndCtrl_B->d116) + DifAndCtrl_B->d117) + DifAndCtrl_B->D47_tmp *
    DifAndCtrl_B->D56_tmp_tmp_o) + DifAndCtrl_B->d118) +
    DifAndCtrl_B->D46_tmp_lm * DifAndCtrl_B->D56_tmp_tmp_l) + DifAndCtrl_B->d119)
    + DifAndCtrl_B->tmp_tmp_g * DifAndCtrl_B->D56_tmp_j) + DifAndCtrl_B->d120) +
    DifAndCtrl_B->tmp_tmp * DifAndCtrl_B->D56_tmp_j) + DifAndCtrl_B->d121) +
    DifAndCtrl_B->tmp_tmp_nn * DifAndCtrl_B->D56_tmp_j) + DifAndCtrl_B->d122) +
    DifAndCtrl_B->d40 * DifAndCtrl_P.ArmConstants.Inertia1[8] *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->d40 *
    DifAndCtrl_P.ArmConstants.Inertia2[8] * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->d40 * DifAndCtrl_P.HexaConstants.Inertia[0] *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->D46_tmp_m *
    DifAndCtrl_X->Integrator1_CSTATE[3] * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->tmp_tmp_j *
    DifAndCtrl_P.ArmConstants.Mass1 * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->d123 * DifAndCtrl_X->Integrator1_CSTATE[3] *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->tmp_tmp_j * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->x_tmp_cv) + DifAndCtrl_B->d40 * DifAndCtrl_B->D46_tmp_cn *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_cv) +
    DifAndCtrl_B->tmp_tmp_i * DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d12 *
    DifAndCtrl_P.HexaConstants.Inertia[4] * DifAndCtrl_B->D56_tmp_tmp_f) +
    DifAndCtrl_B->tmp_tmp_h * DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->d22 *
    DifAndCtrl_P.HexaConstants.Inertia[8] * DifAndCtrl_B->D56_tmp_tmp_f) +
    DifAndCtrl_B->tmp_tmp_n * DifAndCtrl_B->D56_tmp_tmp_f) +
    DifAndCtrl_B->tmp_tmp_o * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->tmp_tmp_d *
    DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->tmp_tmp_o *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D56_tmp_tmp_f) +
    DifAndCtrl_B->rtb_ginv_tmp_l) + DifAndCtrl_B->rtb_ginv_tmp_f) +
    DifAndCtrl_B->d124 * DifAndCtrl_B->D46_tmp_j) + DifAndCtrl_B->tmp_tmp_f) +
    DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->D56_tmp_tmp_m) +
    DifAndCtrl_B->D46_tmp_cs * DifAndCtrl_X->Integrator1_CSTATE[4] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->D56_tmp_tmp_m) + DifAndCtrl_B->D46_tmp_p4 *
    DifAndCtrl_B->D56_tmp_tmp_m) + DifAndCtrl_B->d31 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D56_tmp_tmp_m) +
    DifAndCtrl_B->tmp_tmp_c * DifAndCtrl_B->D56_tmp_f) +
    DifAndCtrl_B->tmp_tmp_ji) + DifAndCtrl_B->tmp_tmp_b *
    DifAndCtrl_B->D56_tmp_f) + DifAndCtrl_B->tmp_tmp_oo) +
    DifAndCtrl_B->tmp_tmp_e * DifAndCtrl_B->D56_tmp_f) +
    DifAndCtrl_B->tmp_tmp_fr) + DifAndCtrl_B->tmp_tmp_dd *
    DifAndCtrl_B->D56_tmp_f) + DifAndCtrl_B->tmp_tmp_oy) +
    DifAndCtrl_B->tmp_tmp_ho) + DifAndCtrl_B->tmp_tmp_ln) + DifAndCtrl_B->d125 *
    DifAndCtrl_B->D46_tmp_d) + DifAndCtrl_B->tmp_tmp_lu) + DifAndCtrl_B->D47_tmp
    * DifAndCtrl_B->D56_tmp_tmp_h2) + DifAndCtrl_B->tmp_tmp_ik *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->D56_tmp_tmp_h2) + DifAndCtrl_B->D46_tmp_lm *
    DifAndCtrl_B->D56_tmp_tmp_p) + DifAndCtrl_B->tmp_tmp_gf) +
    DifAndCtrl_B->tmp_tmp_g * DifAndCtrl_B->D56_tmp_a) +
    DifAndCtrl_B->tmp_tmp_d4) + DifAndCtrl_B->tmp_tmp * DifAndCtrl_B->D56_tmp_a)
    + DifAndCtrl_B->tmp_tmp_dv) + DifAndCtrl_B->tmp_tmp_nn *
    DifAndCtrl_B->D56_tmp_a) + DifAndCtrl_B->tmp_tmp_jo) +
    DifAndCtrl_B->tmp_tmp_l * DifAndCtrl_B->d1) + DifAndCtrl_B->tmp_tmp_ce *
    DifAndCtrl_B->d2) + ((((((DifAndCtrl_B->D48 + DifAndCtrl_B->D14) -
    DifAndCtrl_B->D24) - DifAndCtrl_B->D35) - DifAndCtrl_B->tmp_tmp_p) -
    DifAndCtrl_B->D48_tmp * DifAndCtrl_B->D46_tmp_a) + DifAndCtrl_B->d18) *
    (DifAndCtrl_B->D14_tmp * DifAndCtrl_B->x_tmp_cv)) +
    ((((((((((((((DifAndCtrl_B->D47_tmp_tmp - DifAndCtrl_B->D47_tmp_p) -
    DifAndCtrl_B->D47_tmp_px) * DifAndCtrl_B->rtb_ginv_tmp_n +
    DifAndCtrl_B->D47_tmp_n) + DifAndCtrl_B->d26 * DifAndCtrl_B->D46_tmp_da) -
    DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->D46_tmp_da) +
    DifAndCtrl_B->D47_tmp_i) + DifAndCtrl_B->D46_tmp_o) + DifAndCtrl_B->D14) -
    DifAndCtrl_B->D24) - DifAndCtrl_B->D35) - DifAndCtrl_B->tmp_tmp_p) +
    DifAndCtrl_B->d20) + DifAndCtrl_B->d21) + DifAndCtrl_B->d18) *
    (DifAndCtrl_B->D27_tmp_n * DifAndCtrl_B->x_tmp_cv)) + DifAndCtrl_B->d126) +
    DifAndCtrl_B->d41 * DifAndCtrl_B->d3) + DifAndCtrl_B->d42 * DifAndCtrl_B->d3)
    + DifAndCtrl_B->tmp_tmp_jr * DifAndCtrl_B->ab_a) + DifAndCtrl_B->d128) +
    DifAndCtrl_B->d129) + DifAndCtrl_B->d34 * DifAndCtrl_B->d6) +
    DifAndCtrl_B->d43 * DifAndCtrl_B->D37) + DifAndCtrl_B->tmp_tmp_c2 *
    DifAndCtrl_B->D67) + DifAndCtrl_B->d130) + DifAndCtrl_B->d131) +
    DifAndCtrl_B->d132) + DifAndCtrl_B->d133) - DifAndCtrl_B->d134) -
    DifAndCtrl_B->d135) - DifAndCtrl_B->d136) + DifAndCtrl_B->tmp_tmp_dk *
    DifAndCtrl_B->D56_tmp_d) + DifAndCtrl_B->d137) + DifAndCtrl_B->d138) +
                      DifAndCtrl_B->d139) - DifAndCtrl_B->d140) -
                    DifAndCtrl_B->d141) + DifAndCtrl_B->tmp_tmp_oi *
                   DifAndCtrl_B->D56_tmp_lx) + DifAndCtrl_B->d142) +
                 DifAndCtrl_B->tmp_tmp_f1 * DifAndCtrl_B->D46_tmp_pb) +
                DifAndCtrl_B->d143 * DifAndCtrl_B->D46_tmp_pb) +
               DifAndCtrl_B->D14_tmp_mv * DifAndCtrl_P.ArmConstants.Inertia1[8] *
               DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->tmp_tmp_js *
              DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d144 *
             DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->D14_tmp_mv *
            DifAndCtrl_P.ArmConstants.Inertia2[8] * DifAndCtrl_B->D46_tmp_pb) +
           DifAndCtrl_B->D14_tmp_mv * DifAndCtrl_P.HexaConstants.Inertia[0] *
           DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d145 *
          DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d14 *
         DifAndCtrl_P.HexaConstants.Inertia[8] * DifAndCtrl_B->D46_tmp_pb) +
        DifAndCtrl_B->d146 * DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d147 *
       DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d148 * DifAndCtrl_B->D46_tmp_pb)
     + DifAndCtrl_B->d39 * DifAndCtrl_B->D46_tmp_pb) + DifAndCtrl_B->d149 *
    DifAndCtrl_B->D46_tmp_pb;
  DifAndCtrl_B->dv[37] = -(((((((((((((((((((((((((((((((tmp +
    DifAndCtrl_B->d150) + DifAndCtrl_B->d151) + DifAndCtrl_B->d152) +
    DifAndCtrl_B->d153) - DifAndCtrl_B->d154) + DifAndCtrl_B->d155) +
    DifAndCtrl_B->d156) + DifAndCtrl_B->d157 * DifAndCtrl_B->D46_tmp_b) -
    DifAndCtrl_B->d158) + DifAndCtrl_B->d159) + DifAndCtrl_B->d160) +
    DifAndCtrl_B->D46_tmp_tmp_g) + DifAndCtrl_B->tmp_tmp_dk *
    DifAndCtrl_B->D56_tmp_b) + DifAndCtrl_B->d) + DifAndCtrl_B->d162 *
    DifAndCtrl_B->D46_tmp_ln) - DifAndCtrl_B->d163) + DifAndCtrl_B->d164) +
    DifAndCtrl_B->d165) + DifAndCtrl_B->tmp_tmp_oi * DifAndCtrl_B->D56_tmp_h) +
    DifAndCtrl_B->D14_tmp_my) + DifAndCtrl_B->d45 * DifAndCtrl_B->d5) +
    DifAndCtrl_B->d32 * DifAndCtrl_B->d5) + DifAndCtrl_B->tmp_tmp_jr *
    DifAndCtrl_B->D15_tmp_tmp) + DifAndCtrl_B->d48 * DifAndCtrl_B->d7) +
    DifAndCtrl_B->d33 * DifAndCtrl_B->D14_tmp_tmp) + DifAndCtrl_B->tmp_tmp_c2 *
    DifAndCtrl_B->D15_tmp_tmp_i) + DifAndCtrl_B->d45 * DifAndCtrl_B->y_a) +
    DifAndCtrl_B->d32 * DifAndCtrl_B->y_a) + DifAndCtrl_B->d33 *
    DifAndCtrl_B->D48_tmp_tmp) + DifAndCtrl_B->d8) * 0.125);
  DifAndCtrl_B->D56_tmp_tmp_f = DifAndCtrl_B->D46_tmp_fi *
    DifAndCtrl_B->rtb_ginv_tmp_tmp_n;
  DifAndCtrl_B->D56_tmp_tmp_a = -2.0 * DifAndCtrl_B->rtb_ginv_tmp_tmp_n *
    DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_n = DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_B->D15_tmp + DifAndCtrl_B->D24_tmp_h;
  DifAndCtrl_B->tmp_tmp = DifAndCtrl_P.ArmConstants.Hexa_to_joint_L *
    DifAndCtrl_B->x_tmp;
  DifAndCtrl_B->D14_tmp_mv = -2.0 * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D27_tmp_n = -2.0 * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d14 = 4.0 * DifAndCtrl_B->x_tmp_b;
  DifAndCtrl_B->D14_tmp = ((DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_B->D17_tmp_e + DifAndCtrl_B->tmp_tmp) +
    DifAndCtrl_P.ArmConstants.MC2 * DifAndCtrl_B->D17_tmp_o) *
    DifAndCtrl_B->Clock2 - DifAndCtrl_B->D24_tmp_d * DifAndCtrl_B->x_tmp_c *
    DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->d18 = 4.0 * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->d20 = DifAndCtrl_B->D16 * -2.0;
  DifAndCtrl_B->d21 = DifAndCtrl_B->D25 * DifAndCtrl_B->D56_tmp_tmp_tmp +
    DifAndCtrl_B->D47_tmp_tmp * DifAndCtrl_B->D46_tmp_ex;
  DifAndCtrl_B->tmp_tmp_g = DifAndCtrl_B->d14 * DifAndCtrl_B->D17_tmp_a *
    DifAndCtrl_B->x_tmp * (DifAndCtrl_B->rtb_ginv_tmp_tmp_pi +
    DifAndCtrl_B->rtb_ginv_tmp_tmp_a);
  DifAndCtrl_B->tmp_tmp_d = (DifAndCtrl_B->D45_tmp_e * 2.0 *
    DifAndCtrl_B->D46_tmp_ch + 4.0 * DifAndCtrl_P.ArmConstants.Inertia2[3] *
    DifAndCtrl_B->D46_tmp_h) * DifAndCtrl_B->rtb_ginv_tmp_pw;
  DifAndCtrl_B->tmp_tmp_c = (DifAndCtrl_B->D34 * 2.0 * DifAndCtrl_B->D46_tmp_ch
    + -4.0 * DifAndCtrl_P.ArmConstants.Inertia2[3] * DifAndCtrl_B->D46_tmp_h) *
    DifAndCtrl_B->rtb_ginv_tmp_ow;
  DifAndCtrl_B->tmp_tmp_i = DifAndCtrl_B->D14_tmp * DifAndCtrl_B->d18;
  DifAndCtrl_B->tmp_tmp = (DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_B->D17_tmp_e + DifAndCtrl_B->tmp_tmp) * DifAndCtrl_B->Clock2;
  DifAndCtrl_B->tmp_tmp_j = DifAndCtrl_B->D46_tmp_dau * DifAndCtrl_B->D14_tmp_jg
    * DifAndCtrl_B->D46_tmp_pb;
  DifAndCtrl_B->tmp_tmp_h = DifAndCtrl_B->D46_tmp_af * DifAndCtrl_B->d166 *
    DifAndCtrl_B->D46_tmp_pb;
  DifAndCtrl_B->dv[45] = -((((((((((((((((((((DifAndCtrl_B->D47_tmp_tmp *
    DifAndCtrl_B->D14_tmp_g * DifAndCtrl_B->smax +
    DifAndCtrl_P.ArmConstants.Inertia1[3] * DifAndCtrl_B->D56_tmp_tmp_tmp) *
    (DifAndCtrl_B->d14 * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp) *
    DifAndCtrl_B->x_tmp_p + (((DifAndCtrl_B->D56_tmp_tmp_f *
    DifAndCtrl_B->D46_tmp_ei + DifAndCtrl_B->D56_tmp_tmp_a *
    DifAndCtrl_B->D46_tmp_ax) + DifAndCtrl_B->D56_tmp_tmp_f *
    DifAndCtrl_B->D46_tmp_dau) + DifAndCtrl_B->D56_tmp_tmp_a *
    DifAndCtrl_B->D46_tmp_af)) + ((DifAndCtrl_B->D56_tmp_m *
    DifAndCtrl_B->D14_tmp_g * DifAndCtrl_B->smax + DifAndCtrl_B->D46_tmp_e) +
    DifAndCtrl_B->D46_tmp_bn) * (DifAndCtrl_B->d20 * DifAndCtrl_B->x_tmp_cv) *
    DifAndCtrl_B->x_tmp_p) + -2.0 * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D56 *
    DifAndCtrl_B->D26 * DifAndCtrl_B->x_tmp_p) - DifAndCtrl_B->D16 *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D46 * DifAndCtrl_B->x_tmp_p) -
    DifAndCtrl_B->D56 * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D47_tmp_pt *
    DifAndCtrl_B->x_tmp_p) + DifAndCtrl_B->D46_tmp_fi * DifAndCtrl_B->x_tmp_cv *
    DifAndCtrl_B->x_tmp * (DifAndCtrl_B->D15 * DifAndCtrl_B->D46_tmp_h +
    DifAndCtrl_B->D45_tmp_e * DifAndCtrl_B->D46_tmp_ch) * DifAndCtrl_B->x_tmp_p)
    + DifAndCtrl_B->rtb_ginv_tmp_tmp_n * DifAndCtrl_B->D14_tmp_mv *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp_c * (DifAndCtrl_B->tmp_tmp -
    DifAndCtrl_B->rtb_ginv_tmp_tmp_n * DifAndCtrl_B->x_tmp_c *
    DifAndCtrl_B->x_tmp_p)) + DifAndCtrl_B->D24_tmp_d * DifAndCtrl_B->D27_tmp_n *
    DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->D14_tmp) +
    DifAndCtrl_B->D14_tmp_mv * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->rtb_ginv_tmp_tmp_n * DifAndCtrl_B->x_tmp_cv *
    DifAndCtrl_B->D45_tmp) + DifAndCtrl_B->D27_tmp_n * DifAndCtrl_B->Clock2 *
    DifAndCtrl_B->D24_tmp_d * DifAndCtrl_B->x_tmp_cv * DifAndCtrl_B->D24_tmp_o)
    + DifAndCtrl_P.ArmConstants.Inertia1[8] * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_P.ArmConstants.Inertia2[8] * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_P.HexaConstants.Inertia[0] * DifAndCtrl_B->D46_tmp_pb) -
    DifAndCtrl_B->rtb_ginv_tmp_c * DifAndCtrl_B->D46_tmp_pb) - DifAndCtrl_B->D56
    * DifAndCtrl_P.HexaConstants.Inertia[4] * DifAndCtrl_B->D46_tmp_pb) *
    DifAndCtrl_B->d12 + ((((((DifAndCtrl_B->tmp_tmp_d + DifAndCtrl_B->tmp_tmp_g)
    + DifAndCtrl_B->tmp_tmp_c) + DifAndCtrl_B->D18_tmp * DifAndCtrl_B->d18 *
    DifAndCtrl_B->D24_tmp_o) + DifAndCtrl_B->tmp_tmp_i * DifAndCtrl_B->D17_tmp)
    + DifAndCtrl_B->tmp_tmp_j) + DifAndCtrl_B->tmp_tmp_h) *
    DifAndCtrl_X->Integrator1_CSTATE[7]) + (((((((((((((DifAndCtrl_B->D17_tmp_a *
    -2.0 * DifAndCtrl_B->D17 * (DifAndCtrl_B->D47_tmp_tmp *
    DifAndCtrl_B->D56_tmp_tmp_tmp + DifAndCtrl_B->D56_tmp_m *
    DifAndCtrl_B->D46_tmp_ex) + DifAndCtrl_B->d20 * DifAndCtrl_B->D17_tmp_a *
    DifAndCtrl_B->d21) + DifAndCtrl_B->D17_tmp_a * 2.0 * DifAndCtrl_B->D56 *
    DifAndCtrl_B->d21) + DifAndCtrl_B->tmp_tmp_g) + DifAndCtrl_B->tmp_tmp_d) +
    DifAndCtrl_B->tmp_tmp_c) + (DifAndCtrl_B->rtb_ginv_tmp_p *
    DifAndCtrl_B->D17_tmp_as + DifAndCtrl_B->rtb_ginv_tmp_a *
    DifAndCtrl_B->D17_tmp_j) * DifAndCtrl_B->d18 * DifAndCtrl_B->D24_tmp_o) +
    (DifAndCtrl_B->D14_tmp_tmp_p * -DifAndCtrl_B->D17_tmp_as +
     DifAndCtrl_B->rtb_ginv_tmp_i * DifAndCtrl_B->D17_tmp_j) *
    DifAndCtrl_B->tmp_tmp_i) + DifAndCtrl_B->D46_tmp_cs *
    DifAndCtrl_P.ArmConstants.Mass1 * DifAndCtrl_B->D45_tmp *
    (DifAndCtrl_B->D17_tmp_p * DifAndCtrl_B->x_tmp + DifAndCtrl_B->D17_tmp_ob *
     DifAndCtrl_B->x_tmp_b)) + ((DifAndCtrl_B->D14_tmp_g * DifAndCtrl_B->x_tmp_c
    * DifAndCtrl_B->x_tmp_p + -DifAndCtrl_B->Clock2 * DifAndCtrl_B->smax) *
    (DifAndCtrl_P.ArmConstants.MC1 * DifAndCtrl_B->x_tmp) +
    (DifAndCtrl_B->D17_tmp_tmp * DifAndCtrl_B->x_tmp_p +
     DifAndCtrl_B->D17_tmp_tmp_l) * (DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_B->x_tmp_b)) * ((-DifAndCtrl_B->rtb_ginv_tmp_tmp_n *
    DifAndCtrl_B->x_tmp_c * DifAndCtrl_B->x_tmp_p + DifAndCtrl_B->tmp_tmp) *
    (4.0 * DifAndCtrl_P.ArmConstants.Mass1))) + DifAndCtrl_B->D46_tmp_ei *
    DifAndCtrl_B->D14_tmp_jg * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_B->D46_tmp_ax * DifAndCtrl_B->d166 * DifAndCtrl_B->D46_tmp_pb) +
    DifAndCtrl_B->tmp_tmp_j) + DifAndCtrl_B->tmp_tmp_h) *
    DifAndCtrl_X->Integrator1_CSTATE[6]) -
    (((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B->D56_tmp_g *
    DifAndCtrl_B->D46_tmp_p + DifAndCtrl_B->D25 * DifAndCtrl_B->D56_tmp_bj) +
    DifAndCtrl_B->D56_tmp_c * DifAndCtrl_B->D46_tmp_l) + DifAndCtrl_B->D15 *
    DifAndCtrl_B->D56_tmp_j) + DifAndCtrl_B->D56_tmp_cj *
    DifAndCtrl_B->D46_tmp_j) + DifAndCtrl_B->D25 * DifAndCtrl_B->D56_tmp_f) +
    DifAndCtrl_B->D56_tmp_m1 * DifAndCtrl_B->D46_tmp_d) + DifAndCtrl_B->D15 *
    DifAndCtrl_B->D56_tmp_a) - DifAndCtrl_B->D56_tmp_tmp_k) +
    DifAndCtrl_B->D56_tmp_tmp_j) - DifAndCtrl_B->D56_tmp_tmp_fz) -
    DifAndCtrl_B->D56_tmp_tmp_cm) + DifAndCtrl_B->D56_tmp_n3 *
    DifAndCtrl_B->D46_tmp_g) + DifAndCtrl_B->D46_tmp_mx *
    DifAndCtrl_B->D56_tmp_l) + DifAndCtrl_B->D46_tmp_pr *
    DifAndCtrl_B->D56_tmp_l) + DifAndCtrl_B->D56_tmp_tmp_fq) -
    DifAndCtrl_B->D56_tmp_tmp_n) - DifAndCtrl_B->D56_tmp_tmp_i) -
    DifAndCtrl_B->D56_tmp_tmp_l4) + DifAndCtrl_B->D56_tmp_oy *
    DifAndCtrl_B->D46_tmp_dy) + DifAndCtrl_B->D46_tmp_dz *
    DifAndCtrl_B->D56_tmp_ju) + DifAndCtrl_B->D46_tmp_tmp_g4 *
    DifAndCtrl_B->D56_tmp_jz) + DifAndCtrl_B->D56_tmp_tmp_i3) -
    DifAndCtrl_B->D56_tmp_tmp_k1) - DifAndCtrl_B->D56_tmp_tmp_fc) -
                     DifAndCtrl_B->D56_tmp_tmp_al) + DifAndCtrl_B->D56_tmp_tmp_d)
                   - DifAndCtrl_B->D56_tmp_tmp_ey) +
                  -DifAndCtrl_B->D46_tmp_tmp_h * DifAndCtrl_P.ArmConstants.Mass2
                  * DifAndCtrl_B->D56_tmp_o) + DifAndCtrl_B->D56_tmp_nj *
                 DifAndCtrl_B->D46_tmp_b) + DifAndCtrl_B->D46_tmp_mx *
                DifAndCtrl_B->D56_tmp_n) + DifAndCtrl_B->D46_tmp_pr *
               DifAndCtrl_B->D56_tmp_n) + DifAndCtrl_B->D56_tmp_tmp_eh) -
             DifAndCtrl_B->D56_tmp_tmp_b) - DifAndCtrl_B->D56_tmp_tmp_a0) -
           DifAndCtrl_B->D56_tmp_tmp_il) + DifAndCtrl_B->D56_tmp_k *
          DifAndCtrl_B->D46_tmp_ln) + DifAndCtrl_B->D46_tmp_dz *
         DifAndCtrl_B->D56_tmp_o4) + DifAndCtrl_B->D46_tmp_tmp_g4 *
        DifAndCtrl_B->D56_tmp_ny) + DifAndCtrl_B->D14_tmp_g1) -
      DifAndCtrl_B->D56_tmp_cx) - DifAndCtrl_B->D56_tmp_i) *
    DifAndCtrl_B->D16_tmp_f) * 0.25);
  DifAndCtrl_B->D17 = DifAndCtrl_B->d99 * DifAndCtrl_P.ArmConstants.Inertia1[7];
  DifAndCtrl_B->D56_tmp_tmp_f = DifAndCtrl_B->D46_tmp_tmp_d *
    DifAndCtrl_X->Integrator1_CSTATE[4] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1;
  DifAndCtrl_B->D56_tmp_tmp_a = DifAndCtrl_B->d12 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_n = DifAndCtrl_B->d99 *
    DifAndCtrl_P.ArmConstants.Inertia2[7];
  DifAndCtrl_B->d166 = DifAndCtrl_B->D46_tmp_c *
    DifAndCtrl_X->Integrator1_CSTATE[4];
  DifAndCtrl_B->D16_tmp_f = DifAndCtrl_B->d166 *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->tmp_tmp = DifAndCtrl_B->d99 *
    DifAndCtrl_P.ArmConstants.Inertia1[6];
  DifAndCtrl_B->D14_tmp_jg = DifAndCtrl_B->d127 *
    DifAndCtrl_P.ArmConstants.Inertia2[3] * DifAndCtrl_B->D46_tmp_tmp_m;
  DifAndCtrl_B->D68 *= DifAndCtrl_B->d55;
  DifAndCtrl_B->D14_tmp_mv = DifAndCtrl_B->D47_tmp * DifAndCtrl_B->D46_tmp_tmp_b;
  DifAndCtrl_B->D46_tmp_tmp_b *= DifAndCtrl_B->D16_tmp_m;
  DifAndCtrl_B->D27_tmp_n = DifAndCtrl_B->rtb_ginv_tmp_tmp_n *
    DifAndCtrl_B->D46_tmp_l;
  DifAndCtrl_B->D46_tmp_tmp_i *= DifAndCtrl_B->rtb_ginv_tmp_o;
  DifAndCtrl_B->D56_tmp_tmp_o *= DifAndCtrl_B->D16_tmp_f;
  DifAndCtrl_B->d14 = DifAndCtrl_B->rtb_ginv_tmp_k * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->D14_tmp = DifAndCtrl_B->rtb_ginv_tmp_d * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->d18 = DifAndCtrl_B->rtb_ginv_tmp_g * DifAndCtrl_B->D56_tmp_j;
  DifAndCtrl_B->D16_tmp_m *= DifAndCtrl_B->D46_tmp_tmp_n;
  DifAndCtrl_B->rtb_ginv_tmp_tmp_n *= DifAndCtrl_B->D46_tmp_d;
  DifAndCtrl_B->D56_tmp_tmp_h2 *= DifAndCtrl_B->D16_tmp_f;
  DifAndCtrl_B->d2 *= DifAndCtrl_B->d53;
  DifAndCtrl_B->D16_tmp_f = -6.0 * DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->d20 = DifAndCtrl_B->D16_tmp_f *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->d21 = DifAndCtrl_B->tmp_tmp_js * DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->tmp_tmp_g = DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia2[4] * DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->D14_tmp_g1 = DifAndCtrl_B->d148 * DifAndCtrl_B->D46_tmp_bb;
  DifAndCtrl_B->tmp_tmp_d = DifAndCtrl_B->d33 * DifAndCtrl_B->D56_tmp_tmp_c;
  DifAndCtrl_B->D37 *= DifAndCtrl_B->D58;
  DifAndCtrl_B->D67 *= DifAndCtrl_B->d49;
  DifAndCtrl_B->D56_tmp_tmp_h *= DifAndCtrl_B->D58;
  DifAndCtrl_B->tmp_tmp_c = DifAndCtrl_B->d174 * DifAndCtrl_B->D46_tmp_dy;
  DifAndCtrl_B->tmp_tmp_i = DifAndCtrl_B->D14_tmp_c0 * DifAndCtrl_B->D56_tmp_lx;
  DifAndCtrl_B->tmp_tmp_j = DifAndCtrl_B->d174 * DifAndCtrl_B->D46_tmp_ln;
  DifAndCtrl_B->d11 = (((DifAndCtrl_B->D14_tmp_md - DifAndCtrl_B->d37) +
                        DifAndCtrl_B->d11) + DifAndCtrl_B->d13) +
    DifAndCtrl_B->d16;
  DifAndCtrl_B->d13 = DifAndCtrl_B->d11 * DifAndCtrl_B->d175;
  DifAndCtrl_B->D14_tmp_tmp *= DifAndCtrl_B->D58;
  DifAndCtrl_B->D15_tmp_tmp_i *= DifAndCtrl_B->d51;
  DifAndCtrl_B->D58 *= DifAndCtrl_B->D48_tmp_tmp;
  DifAndCtrl_B->d16 = DifAndCtrl_B->D38 * DifAndCtrl_B->d3;
  DifAndCtrl_B->d3 *= DifAndCtrl_B->D47;
  DifAndCtrl_B->D14_tmp_md = DifAndCtrl_B->D38 * DifAndCtrl_B->D56_tmp_tmp_e;
  DifAndCtrl_B->D56_tmp_tmp_e *= DifAndCtrl_B->D47;
  DifAndCtrl_B->tmp_tmp_h = DifAndCtrl_B->D38 * DifAndCtrl_B->d5;
  DifAndCtrl_B->d5 *= DifAndCtrl_B->D47;
  DifAndCtrl_B->D38 *= DifAndCtrl_B->y_a;
  DifAndCtrl_B->D47 *= DifAndCtrl_B->y_a;
  DifAndCtrl_B->dv[53] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((DifAndCtrl_B->d127 *
    DifAndCtrl_P.ArmConstants.Inertia1[3] * DifAndCtrl_B->rtb_ginv_tmp_n +
    DifAndCtrl_B->D14_tmp_jg) + DifAndCtrl_B->d54 *
    DifAndCtrl_B->rtb_ginv_tmp_tmp_l) + DifAndCtrl_B->D68) +
    DifAndCtrl_B->D46_tmp_k * DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->d4 *
    DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->D46_tmp_p4 *
    DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->D14_tmp_i *
    DifAndCtrl_B->D46_tmp_tmp_k) + DifAndCtrl_B->D17 * DifAndCtrl_B->D46_tmp_p)
    + DifAndCtrl_B->D56_tmp * DifAndCtrl_B->rtb_ginv_tmp_ie) +
    DifAndCtrl_B->D56_tmp_tmp_f * DifAndCtrl_B->D27) +
    DifAndCtrl_B->D56_tmp_tmp_a * DifAndCtrl_B->D27) + DifAndCtrl_B->D56_tmp_mc *
    DifAndCtrl_B->D56_tmp_bj) + DifAndCtrl_B->D56_tmp_ap *
    DifAndCtrl_B->D56_tmp_bj) + DifAndCtrl_B->D56_tmp_jd *
    DifAndCtrl_B->D56_tmp_bj) + DifAndCtrl_B->rtb_ginv_tmp *
    DifAndCtrl_B->D56_tmp_bj) + DifAndCtrl_B->d167) + DifAndCtrl_B->D14_tmp_mv)
    + DifAndCtrl_B->D46_tmp_tmp_b) + DifAndCtrl_B->D27_tmp_n) +
    DifAndCtrl_B->D46_tmp_tmp_i) + DifAndCtrl_B->D56_tmp_tmp_o) +
    DifAndCtrl_B->rtb_ginv_tmp_ox * DifAndCtrl_B->D56_tmp_tmp_l) +
    DifAndCtrl_B->d14) + DifAndCtrl_B->D14_tmp) + DifAndCtrl_B->d18) +
    DifAndCtrl_B->d168) + DifAndCtrl_B->d169) + DifAndCtrl_B->d170) +
    DifAndCtrl_B->d171) + DifAndCtrl_B->d172) + DifAndCtrl_B->rtb_ginv_tmp_l) +
    DifAndCtrl_B->d4 * DifAndCtrl_B->D46_tmp_tmp_hc) +
    DifAndCtrl_B->rtb_ginv_tmp_f) + DifAndCtrl_B->D14_tmp_i *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->D17 * DifAndCtrl_B->D46_tmp_j)
    + DifAndCtrl_B->tmp_tmp_f) + DifAndCtrl_B->D56_tmp_tmp_f *
    DifAndCtrl_B->D56_tmp_tmp_m) + DifAndCtrl_B->D56_tmp_tmp_a *
    DifAndCtrl_B->D56_tmp_tmp_m) + DifAndCtrl_B->tmp_tmp_ji) +
    DifAndCtrl_B->tmp_tmp_oo) + DifAndCtrl_B->tmp_tmp_fr) +
    DifAndCtrl_B->tmp_tmp_oy) + DifAndCtrl_B->d173) + DifAndCtrl_B->tmp_tmp_ln)
    + DifAndCtrl_B->D16_tmp_m) + DifAndCtrl_B->rtb_ginv_tmp_tmp_n) +
    DifAndCtrl_B->tmp_tmp_lu) + DifAndCtrl_B->D56_tmp_tmp_h2) +
    DifAndCtrl_B->tmp_tmp_gf) + DifAndCtrl_B->tmp_tmp_d4) +
    DifAndCtrl_B->tmp_tmp_dv) + DifAndCtrl_B->tmp_tmp_jo) + DifAndCtrl_B->d52 *
    DifAndCtrl_B->d1) + DifAndCtrl_B->d2) + -6.0 * DifAndCtrl_P.ArmConstants.MC1
    * DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->smax) + -6.0 * DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->smax) +
    DifAndCtrl_B->tmp_tmp_f1 * DifAndCtrl_B->D46_tmp_n) + DifAndCtrl_B->D16_tmp *
    DifAndCtrl_P.ArmConstants.Inertia1[4] * DifAndCtrl_B->D46_tmp_n) +
    DifAndCtrl_B->d146 * DifAndCtrl_B->D46_tmp_n) + DifAndCtrl_B->d149 *
    DifAndCtrl_B->D46_tmp_n) + DifAndCtrl_B->d45 * DifAndCtrl_B->D18) +
    DifAndCtrl_B->d32 * DifAndCtrl_B->D18) + DifAndCtrl_B->d20) +
    DifAndCtrl_B->d21) + DifAndCtrl_B->tmp_tmp_g) + DifAndCtrl_B->D14_tmp_g1) +
    DifAndCtrl_B->tmp_tmp_d) + DifAndCtrl_B->D45 *
    DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->D28) + DifAndCtrl_B->d48 *
    DifAndCtrl_B->D46_tmp_tmp) + DifAndCtrl_B->d16) + DifAndCtrl_B->d3) +
    DifAndCtrl_B->d46 * DifAndCtrl_B->ab_a) + DifAndCtrl_B->D14_tmp_md) +
    DifAndCtrl_B->D56_tmp_tmp_e) + DifAndCtrl_B->D37) + DifAndCtrl_B->D67) +
    DifAndCtrl_B->D56_tmp_tmp_h) + DifAndCtrl_B->tmp_tmp *
    DifAndCtrl_B->D46_tmp_g) - DifAndCtrl_B->d133) + DifAndCtrl_B->d134) +
    DifAndCtrl_B->d135) + DifAndCtrl_B->d136) + DifAndCtrl_B->d161 *
    DifAndCtrl_B->D56_tmp_d) + DifAndCtrl_B->tmp_tmp_c) +
    -DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Inertia2[0]
    * DifAndCtrl_B->D47_tmp_m) + DifAndCtrl_B->d140) + DifAndCtrl_B->d141) +
    DifAndCtrl_B->tmp_tmp_i) + DifAndCtrl_B->tmp_tmp * DifAndCtrl_B->D46_tmp_b)
    + -DifAndCtrl_X->Integrator1_CSTATE[5] * DifAndCtrl_P.ArmConstants.Inertia1
    [0] * DifAndCtrl_B->D56_tmp_tmp) + DifAndCtrl_B->d159) + DifAndCtrl_B->d160)
                        + DifAndCtrl_B->D46_tmp_tmp_g) + DifAndCtrl_B->d) +
                      DifAndCtrl_B->tmp_tmp_j) + DifAndCtrl_B->d13) +
                    DifAndCtrl_B->d10 * DifAndCtrl_B->d176) - DifAndCtrl_B->d163)
                  + DifAndCtrl_B->d164) + DifAndCtrl_B->d165) +
                DifAndCtrl_B->D14_tmp_my) + DifAndCtrl_B->tmp_tmp_h) +
              DifAndCtrl_B->d5) + DifAndCtrl_B->d50 * DifAndCtrl_B->D15_tmp_tmp)
            + DifAndCtrl_B->D14_tmp_tmp) + DifAndCtrl_B->D15_tmp_tmp_i) +
          DifAndCtrl_B->D38) + DifAndCtrl_B->D47) + DifAndCtrl_B->D58) +
       DifAndCtrl_B->d8) * 0.125);
  DifAndCtrl_B->D17 = DifAndCtrl_B->d166 * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2;
  DifAndCtrl_B->D27 = DifAndCtrl_B->D48_tmp_o * DifAndCtrl_B->D46_tmp_tmp;
  DifAndCtrl_B->D56_tmp_tmp_f = DifAndCtrl_B->D48_tmp_o * DifAndCtrl_B->d6;
  DifAndCtrl_B->D56_tmp_tmp_m = DifAndCtrl_B->D48_tmp_o * DifAndCtrl_B->d7;
  DifAndCtrl_B->D56_tmp_tmp_a = DifAndCtrl_B->D48_tmp_o *
    DifAndCtrl_B->D46_tmp_tmp_f;
  DifAndCtrl_B->dv[61] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B->D46_tmp_lm
    * DifAndCtrl_B->D46_tmp_tmp_p + (DifAndCtrl_B->D14_tmp_jg +
    DifAndCtrl_B->D68)) + DifAndCtrl_B->d9 * DifAndCtrl_B->D46_tmp_tmp_p) +
    DifAndCtrl_B->D14_tmp_mv) + DifAndCtrl_B->D46_tmp_tmp_b) +
    DifAndCtrl_B->D27_tmp_n) + DifAndCtrl_B->D46_tmp_tmp_i) +
    DifAndCtrl_B->D56_tmp_tmp_o) + DifAndCtrl_B->D17 *
    DifAndCtrl_B->D56_tmp_tmp_l) + DifAndCtrl_B->d14) + DifAndCtrl_B->D14_tmp) +
    DifAndCtrl_B->d18) + DifAndCtrl_B->d169) + DifAndCtrl_B->d171) +
    DifAndCtrl_B->tmp_tmp_ho) + DifAndCtrl_B->d9 * DifAndCtrl_B->D46_tmp_tmp_c)
    + DifAndCtrl_B->tmp_tmp_ln) + DifAndCtrl_B->D16_tmp_m) +
    DifAndCtrl_B->rtb_ginv_tmp_tmp_n) + DifAndCtrl_B->tmp_tmp_lu) +
    DifAndCtrl_B->D56_tmp_tmp_h2) + DifAndCtrl_B->D17 *
    DifAndCtrl_B->D56_tmp_tmp_p) + DifAndCtrl_B->tmp_tmp_d4) +
    DifAndCtrl_B->tmp_tmp_dv) + DifAndCtrl_B->tmp_tmp_jo) + DifAndCtrl_B->d2) +
    DifAndCtrl_B->D16_tmp_f * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->s) + DifAndCtrl_B->d20) +
    DifAndCtrl_B->d21) + DifAndCtrl_B->tmp_tmp_g) + DifAndCtrl_B->D14_tmp_g1) +
    DifAndCtrl_B->tmp_tmp_d) + DifAndCtrl_B->d48 * DifAndCtrl_B->D28) +
    DifAndCtrl_B->D27) + DifAndCtrl_B->D56_tmp_tmp_f) + DifAndCtrl_B->D37) +
    DifAndCtrl_B->D67) + DifAndCtrl_B->D56_tmp_tmp_h) + DifAndCtrl_B->tmp_tmp_c)
                      - DifAndCtrl_B->d139) + DifAndCtrl_B->d140) +
                    DifAndCtrl_B->d141) + DifAndCtrl_B->tmp_tmp_i) +
                  DifAndCtrl_B->tmp_tmp_j) + DifAndCtrl_B->d11 *
                 DifAndCtrl_B->d176) + DifAndCtrl_B->d13) - DifAndCtrl_B->d163)
              + DifAndCtrl_B->d164) + DifAndCtrl_B->d165) +
            DifAndCtrl_B->D14_tmp_my) + DifAndCtrl_B->D56_tmp_tmp_m) +
          DifAndCtrl_B->D14_tmp_tmp) + DifAndCtrl_B->D15_tmp_tmp_i) +
        DifAndCtrl_B->D58) + DifAndCtrl_B->D56_tmp_tmp_a) * 0.125);
  DifAndCtrl_B->D17 = DifAndCtrl_B->d27 * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->s;
  DifAndCtrl_B->D46_tmp_tmp_k = DifAndCtrl_X->Integrator1_CSTATE[3] -
    DifAndCtrl_B->rtb_ginv_tmp_tmp;
  DifAndCtrl_B->dv[30] = -(DifAndCtrl_B->d24 * DifAndCtrl_B->D46_tmp_tmp_k +
    DifAndCtrl_B->D17);
  DifAndCtrl_B->dv[38] = -((((((((((((((((DifAndCtrl_B->rtb_ginv_tmp_tmp_p +
    DifAndCtrl_B->d28) + DifAndCtrl_B->D24_tmp_l * DifAndCtrl_B->smax) -
    DifAndCtrl_B->D16_tmp_a) + DifAndCtrl_B->d19) + DifAndCtrl_B->D14_tmp_m3) +
    DifAndCtrl_B->rtb_ginv_tmp_tmp_g) + DifAndCtrl_B->D24_tmp *
    DifAndCtrl_B->D18) + DifAndCtrl_B->d29) + DifAndCtrl_B->d30) -
    DifAndCtrl_B->rtb_ginv_tmp_o2) + DifAndCtrl_B->D16_tmp_j) +
    DifAndCtrl_B->D27_tmp) + DifAndCtrl_B->d35) + DifAndCtrl_B->d177) *
    DifAndCtrl_B->d12 - DifAndCtrl_B->D14_tmp_h *
    DifAndCtrl_X->Integrator1_CSTATE[5]) * 0.25);
  DifAndCtrl_B->D46_tmp_tmp_p = DifAndCtrl_B->D47_tmp *
    DifAndCtrl_B->D46_tmp_tmp_n;
  DifAndCtrl_B->D46_tmp_tmp_b = 6.0 * DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[5];
  DifAndCtrl_B->D56_tmp_tmp_o = DifAndCtrl_B->D46_tmp_tmp_b *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->D14_tmp_f;
  DifAndCtrl_B->D56_tmp_tmp_l = DifAndCtrl_B->d43 * DifAndCtrl_B->D56_tmp_tmp_c;
  DifAndCtrl_B->dv[46] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_B->d178
    + DifAndCtrl_B->D46_tmp_mj) + DifAndCtrl_B->D46_tmp_f) + DifAndCtrl_B->d109)
    + DifAndCtrl_B->D15_tmp_m) + DifAndCtrl_B->d117) + DifAndCtrl_B->D46_tmp_k *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->D46_tmp_p4 *
    DifAndCtrl_B->D46_tmp_tmp_hc) + DifAndCtrl_B->d179) +
    DifAndCtrl_B->D46_tmp_tmp_p) + DifAndCtrl_B->d180) + DifAndCtrl_B->d181) +
    DifAndCtrl_B->d182) + 6.0 * DifAndCtrl_P.ArmConstants.MC1 *
    DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass1 *
    DifAndCtrl_B->smax) + 6.0 * DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.l1_dim
    * DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->smax) + DifAndCtrl_B->d183)
    + DifAndCtrl_B->d184) + DifAndCtrl_B->D46_tmp_tmp_j) + DifAndCtrl_B->d185) +
    DifAndCtrl_B->d41 * DifAndCtrl_B->D18) + DifAndCtrl_B->d42 *
    DifAndCtrl_B->D18) + DifAndCtrl_B->D56_tmp_tmp_o) + DifAndCtrl_B->d186) +
    DifAndCtrl_B->d187) + DifAndCtrl_B->D46_tmp_tmp_kn) +
    DifAndCtrl_B->D56_tmp_tmp_l) + DifAndCtrl_B->d188) + DifAndCtrl_B->d126) -
    DifAndCtrl_B->d16) - DifAndCtrl_B->d3) + DifAndCtrl_B->d189) -
    DifAndCtrl_B->D14_tmp_md) - DifAndCtrl_B->D56_tmp_tmp_e) - DifAndCtrl_B->D37)
    + DifAndCtrl_B->d190) - DifAndCtrl_B->D56_tmp_tmp_h) + DifAndCtrl_B->d133) -
    DifAndCtrl_B->d134) - DifAndCtrl_B->d135) - DifAndCtrl_B->d136) +
    DifAndCtrl_B->d139) - DifAndCtrl_B->d140) - DifAndCtrl_B->d141) +
                        DifAndCtrl_B->d191 * DifAndCtrl_P.ArmConstants.l1_dim *
                        DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->s *
                        DifAndCtrl_B->x_tmp_p) + DifAndCtrl_B->d158) -
                      DifAndCtrl_B->d159) - DifAndCtrl_B->d160) -
                    DifAndCtrl_B->D46_tmp_tmp_g) + DifAndCtrl_B->d163) -
                  DifAndCtrl_B->d164) - DifAndCtrl_B->d165) +
                ((((((((((((((((((((((((((((((((((((((((((-DifAndCtrl_P.ArmConstants.Inertia1
    [0] * DifAndCtrl_B->D56_tmp_bj + DifAndCtrl_B->D14_tmp_j) +
    DifAndCtrl_B->D14_tmp_tmp_pm) + DifAndCtrl_B->D14_tmp_tmp_p2) +
    DifAndCtrl_B->D14_tmp_ct) + DifAndCtrl_B->D15_tmp_tmp_c) + DifAndCtrl_B->d23)
    + DifAndCtrl_B->D15_tmp_tmp_f) + DifAndCtrl_B->d25) +
    DifAndCtrl_B->D16_tmp_tmp) - DifAndCtrl_B->D34_tmp_e) +
    DifAndCtrl_B->D37_tmp) + DifAndCtrl_B->D46_tmp_tmp_ft) +
    DifAndCtrl_B->rtb_ginv_tmp_oc) + DifAndCtrl_B->d56) + DifAndCtrl_B->d57) +
    DifAndCtrl_B->d58) + DifAndCtrl_B->d59) + DifAndCtrl_B->D47_tmp_c) +
    DifAndCtrl_B->d101) + DifAndCtrl_B->d60) + DifAndCtrl_B->d192) +
    DifAndCtrl_B->d193) - DifAndCtrl_B->d61) + DifAndCtrl_B->d62) +
    DifAndCtrl_B->d63) + DifAndCtrl_B->d64) + DifAndCtrl_B->d65) +
    DifAndCtrl_B->d37) + DifAndCtrl_B->d66) + DifAndCtrl_B->d38) +
    DifAndCtrl_B->d67) - DifAndCtrl_B->d68) + DifAndCtrl_B->d69) +
    DifAndCtrl_B->d70) + DifAndCtrl_B->d71) + DifAndCtrl_B->d72) +
                      DifAndCtrl_B->d73) + DifAndCtrl_B->d74) +
                    DifAndCtrl_B->d75) + DifAndCtrl_B->d76) + DifAndCtrl_B->d77)
                 + DifAndCtrl_B->d78) * DifAndCtrl_B->d22) -
               DifAndCtrl_B->tmp_tmp_h) - DifAndCtrl_B->d5) + DifAndCtrl_B->d194)
            - DifAndCtrl_B->D14_tmp_tmp) + DifAndCtrl_B->d195) -
          DifAndCtrl_B->D38) - DifAndCtrl_B->D47) - DifAndCtrl_B->D58) +
       DifAndCtrl_B->d196) * 0.125);
  DifAndCtrl_B->dv[54] = -DifAndCtrl_B->D17;
  DifAndCtrl_B->dv[62] = -(DifAndCtrl_B->D46_tmp * DifAndCtrl_B->s *
    DifAndCtrl_B->d17);
  DifAndCtrl_B->dv[31] = -((DifAndCtrl_X->Integrator1_CSTATE[6] *
    DifAndCtrl_P.ArmConstants.l1_dim * DifAndCtrl_B->s + DifAndCtrl_B->d44 *
    DifAndCtrl_B->D46_tmp_tmp_k) * DifAndCtrl_B->D14_tmp_m);
  DifAndCtrl_B->dv[39] = -((DifAndCtrl_B->d36 * DifAndCtrl_X->
    Integrator1_CSTATE[4] * DifAndCtrl_B->D17_tmp_o +
    -DifAndCtrl_X->Integrator1_CSTATE[4] * DifAndCtrl_P.ArmConstants.Inertia2[3]
    * DifAndCtrl_B->D46_tmp_tmp_m) + -0.25 * DifAndCtrl_X->Integrator1_CSTATE[5]
    * DifAndCtrl_B->d197);
  DifAndCtrl_B->dv[47] = -((((((((((((((((((((((((((((((((((DifAndCtrl_B->d198 +
    DifAndCtrl_B->d199) + DifAndCtrl_B->D46_tmp_na) + DifAndCtrl_B->D15_tmp_m) +
    DifAndCtrl_B->d117) + DifAndCtrl_B->D46_tmp_lm * DifAndCtrl_B->D46_tmp_tmp_c)
    + DifAndCtrl_B->D46_tmp_tmp_p) + DifAndCtrl_B->d180) + DifAndCtrl_B->d182) +
    DifAndCtrl_B->D46_tmp_tmp_b * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->s) +
    DifAndCtrl_B->D56_tmp_tmp_o) + DifAndCtrl_B->d186) + DifAndCtrl_B->d187) +
    DifAndCtrl_B->D46_tmp_tmp_kn) + DifAndCtrl_B->D56_tmp_tmp_l) +
    DifAndCtrl_B->d34 * DifAndCtrl_B->D28) - DifAndCtrl_B->D27) -
    DifAndCtrl_B->D56_tmp_tmp_f) - DifAndCtrl_B->D37) + DifAndCtrl_B->d190) -
    DifAndCtrl_B->D56_tmp_tmp_h) + DifAndCtrl_B->d139) - DifAndCtrl_B->d140) -
    DifAndCtrl_B->d141) + -8.0 * DifAndCtrl_P.ArmConstants.MC2 *
    DifAndCtrl_X->Integrator1_CSTATE[6] * DifAndCtrl_P.ArmConstants.l1_dim *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->s * DifAndCtrl_B->x_tmp_p) +
    DifAndCtrl_B->d163) - DifAndCtrl_B->d164) - DifAndCtrl_B->d165) +
    DifAndCtrl_B->d197 * DifAndCtrl_B->d22) - DifAndCtrl_B->D56_tmp_tmp_m) -
    DifAndCtrl_B->D14_tmp_tmp) + DifAndCtrl_B->d195) +
    -DifAndCtrl_P.ArmConstants.MC2 * DifAndCtrl_X->Integrator1_CSTATE[5] *
    DifAndCtrl_P.ArmConstants.Hexa_to_joint_L * DifAndCtrl_P.ArmConstants.Mass2 *
    DifAndCtrl_B->D48_tmp_tmp) - DifAndCtrl_B->D56_tmp_tmp_a) * 0.125);
  DifAndCtrl_B->dv[55] = -(DifAndCtrl_B->D48_tmp * DifAndCtrl_B->s *
    DifAndCtrl_B->d15);
  DifAndCtrl_B->dv[63] = -0.0;
  memset(&DifAndCtrl_B->dv[0], 0, 24U * sizeof(real_T));
  memset(&DifAndCtrl_B->dv2[0], 0, sizeof(real_T) << 3U);
  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    DifAndCtrl_B->D17 = DifAndCtrl_X->Integrator1_CSTATE[DifAndCtrl_B->c_j];
    for (DifAndCtrl_B->jj = 0; DifAndCtrl_B->jj < 8; DifAndCtrl_B->jj++) {
      DifAndCtrl_B->dv2[DifAndCtrl_B->jj] += DifAndCtrl_B->dv[(DifAndCtrl_B->c_j
        << 3) + DifAndCtrl_B->jj] * DifAndCtrl_B->D17;
    }
  }

  DifAndCtrl_B->dv3[0] = 0.0;
  DifAndCtrl_B->dv3[1] = 0.0;
  DifAndCtrl_B->dv3[2] = DifAndCtrl_B->D46_tmp_g2 * 9.80665;
  DifAndCtrl_B->D17 = -9.80665 * DifAndCtrl_B->x_tmp_cv;
  DifAndCtrl_B->dv3[3] = ((DifAndCtrl_B->D14_tmp_cf * DifAndCtrl_B->x_tmp -
    DifAndCtrl_B->D34_tmp) - DifAndCtrl_B->D34_tmp_f) * DifAndCtrl_B->D17;
  DifAndCtrl_B->dv3[4] = DifAndCtrl_B->D15_tmp_i * 9.80665 *
    DifAndCtrl_B->x_tmp_p;
  DifAndCtrl_B->dv3[5] = 0.0;
  DifAndCtrl_B->dv3[6] = (-DifAndCtrl_B->D14_tmp_c * DifAndCtrl_B->D17_tmp_e -
    DifAndCtrl_B->D34_tmp_f) * DifAndCtrl_B->D17;
  DifAndCtrl_B->dv3[7] = DifAndCtrl_P.ArmConstants.MC2 * 9.80665 *
    DifAndCtrl_P.ArmConstants.Mass2 * DifAndCtrl_B->x_tmp_cv *
    DifAndCtrl_B->D17_tmp_o;
  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    // MATLAB Function: '<S9>/MATLAB Function1'
    DifAndCtrl_B->fx[DifAndCtrl_B->c_j] = DifAndCtrl_B->dv2[DifAndCtrl_B->c_j] -
      DifAndCtrl_B->dv3[DifAndCtrl_B->c_j];
  }

  // MATLAB Function: '<S9>/MATLAB Function1'
  DifAndCtrl_mldivide_e(DifAndCtrl_B->ginv, DifAndCtrl_B->fx, DifAndCtrl_B);

  // Clock: '<S3>/Clock2'
  DifAndCtrl_B->Clock2 = DifAndCtrl_M->Timing.t[0];

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  propChange = true;
  DifAndCtrl_B->c_j = 0;
  exitg1 = false;
  while (!exitg1 && (DifAndCtrl_B->c_j < 16)) {
    if (!(DifAndCtrl_DW->obj.Waypoints[DifAndCtrl_B->c_j] ==
          DifAndCtrl_P.Trajectory.Waypoints[DifAndCtrl_B->c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      DifAndCtrl_B->c_j++;
    }
  }

  if (!propChange) {
    if (DifAndCtrl_DW->obj.isInitialized == 1) {
      DifAndCtrl_DW->obj.TunablePropsChanged = true;
      DifAndCtrl_DW->obj.tunablePropertyChanged[0] = true;
    }

    memcpy(&DifAndCtrl_DW->obj.Waypoints[0], &DifAndCtrl_P.Trajectory.Waypoints
           [0], sizeof(real_T) << 4U);
  }

  propChange = true;
  DifAndCtrl_B->c_j = 0;
  exitg1 = false;
  while (!exitg1 && (DifAndCtrl_B->c_j < 2)) {
    if (!(DifAndCtrl_DW->obj.TimePoints[DifAndCtrl_B->c_j] ==
          DifAndCtrl_P.Trajectory.Tstamps[DifAndCtrl_B->c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      DifAndCtrl_B->c_j++;
    }
  }

  if (!propChange) {
    if (DifAndCtrl_DW->obj.isInitialized == 1) {
      DifAndCtrl_DW->obj.TunablePropsChanged = true;
      DifAndCtrl_DW->obj.tunablePropertyChanged[1] = true;
    }

    DifAndCtrl_DW->obj.TimePoints[0] = DifAndCtrl_P.Trajectory.Tstamps[0];
    DifAndCtrl_DW->obj.TimePoints[1] = DifAndCtrl_P.Trajectory.Tstamps[1];
  }

  propChange = true;
  DifAndCtrl_B->c_j = 0;
  exitg1 = false;
  while (!exitg1 && (DifAndCtrl_B->c_j < 16)) {
    if (!(DifAndCtrl_DW->obj.VelocityBoundaryCondition[DifAndCtrl_B->c_j] ==
          DifAndCtrl_P.PolynomialTrajectory_VelocityBo[DifAndCtrl_B->c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      DifAndCtrl_B->c_j++;
    }
  }

  if (!propChange) {
    if (DifAndCtrl_DW->obj.isInitialized == 1) {
      DifAndCtrl_DW->obj.TunablePropsChanged = true;
      DifAndCtrl_DW->obj.tunablePropertyChanged[3] = true;
    }

    memcpy(&DifAndCtrl_DW->obj.VelocityBoundaryCondition[0],
           &DifAndCtrl_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) <<
           4U);
  }

  if (DifAndCtrl_DW->obj.TunablePropsChanged) {
    DifAndCtrl_DW->obj.TunablePropsChanged = false;
    if (DifAndCtrl_DW->obj.tunablePropertyChanged[0] ||
        DifAndCtrl_DW->obj.tunablePropertyChanged[1] ||
        DifAndCtrl_DW->obj.tunablePropertyChanged[2]) {
      propChange = true;
    } else {
      propChange = false;
    }

    if (!propChange) {
      if (DifAndCtrl_DW->obj.tunablePropertyChanged[3] ||
          DifAndCtrl_DW->obj.tunablePropertyChanged[4]) {
        propChange = true;
      } else {
        propChange = false;
      }
    }

    DifAndCtrl_DW->obj.PPFormUpdatedNeeded = propChange;
    if (DifAndCtrl_DW->obj.PPFormUpdatedNeeded) {
      PolyTrajSys_regeneratePPFormFro(&DifAndCtrl_DW->obj,
        DifAndCtrl_DW->obj.Waypoints, DifAndCtrl_DW->obj.TimePoints,
        DifAndCtrl_B);
    }

    for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 5; DifAndCtrl_B->c_j++) {
      DifAndCtrl_DW->obj.tunablePropertyChanged[DifAndCtrl_B->c_j] = false;
    }
  }

  DifAndCtrl_B->x_tmp_c = DifAndCtrl_B->Clock2;
  DifAndCtrl_B->x_tmp = DifAndCtrl_DW->obj.PPStruct.breaks[2];
  if (DifAndCtrl_B->Clock2 == DifAndCtrl_DW->obj.PPStruct.breaks[2]) {
    for (i = 0; i < 1; i++) {
      DifAndCtrl_B->x_tmp_c = DifAndCtrl_B->x_tmp - 2.220446049250313E-15;
    }
  }

  DifAndCtrl_ppval(DifAndCtrl_DW->obj.PPDDStruct.breaks,
                   DifAndCtrl_DW->obj.PPDDStruct.coefs, DifAndCtrl_B->x_tmp_c,
                   DifAndCtrl_B->dv2);
  DifAndCtrl_ppval(DifAndCtrl_DW->obj.PPStruct.breaks,
                   DifAndCtrl_DW->obj.PPStruct.coefs, DifAndCtrl_B->Clock2,
                   DifAndCtrl_B->dv3);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kp'

  DifAndCtrl_B->dv[0] = DifAndCtrl_P.PID.Kp[0];
  DifAndCtrl_B->dv[8] = 0.0;
  DifAndCtrl_B->dv[16] = 0.0;
  DifAndCtrl_B->dv[24] = 0.0;
  DifAndCtrl_B->dv[32] = 0.0;
  DifAndCtrl_B->dv[40] = 0.0;
  DifAndCtrl_B->dv[48] = 0.0;
  DifAndCtrl_B->dv[56] = 0.0;
  DifAndCtrl_B->dv[1] = 0.0;
  DifAndCtrl_B->dv[9] = DifAndCtrl_P.PID.Kp[1];
  DifAndCtrl_B->dv[17] = 0.0;
  DifAndCtrl_B->dv[25] = 0.0;
  DifAndCtrl_B->dv[33] = 0.0;
  DifAndCtrl_B->dv[41] = 0.0;
  DifAndCtrl_B->dv[49] = 0.0;
  DifAndCtrl_B->dv[57] = 0.0;
  DifAndCtrl_B->dv[2] = 0.0;
  DifAndCtrl_B->dv[10] = 0.0;
  DifAndCtrl_B->dv[18] = DifAndCtrl_P.PID.Kp[2];
  DifAndCtrl_B->dv[26] = 0.0;
  DifAndCtrl_B->dv[34] = 0.0;
  DifAndCtrl_B->dv[42] = 0.0;
  DifAndCtrl_B->dv[50] = 0.0;
  DifAndCtrl_B->dv[58] = 0.0;
  DifAndCtrl_B->dv[3] = 0.0;
  DifAndCtrl_B->dv[11] = 0.0;
  DifAndCtrl_B->dv[19] = 0.0;
  DifAndCtrl_B->dv[27] = DifAndCtrl_P.PID.Kp[3];
  DifAndCtrl_B->dv[35] = 0.0;
  DifAndCtrl_B->dv[43] = 0.0;
  DifAndCtrl_B->dv[51] = 0.0;
  DifAndCtrl_B->dv[59] = 0.0;
  DifAndCtrl_B->dv[4] = 0.0;
  DifAndCtrl_B->dv[12] = 0.0;
  DifAndCtrl_B->dv[20] = 0.0;
  DifAndCtrl_B->dv[28] = 0.0;
  DifAndCtrl_B->dv[36] = DifAndCtrl_P.PID.Kp[4];
  DifAndCtrl_B->dv[44] = 0.0;
  DifAndCtrl_B->dv[52] = 0.0;
  DifAndCtrl_B->dv[60] = 0.0;
  DifAndCtrl_B->dv[5] = 0.0;
  DifAndCtrl_B->dv[13] = 0.0;
  DifAndCtrl_B->dv[21] = 0.0;
  DifAndCtrl_B->dv[29] = 0.0;
  DifAndCtrl_B->dv[37] = 0.0;
  DifAndCtrl_B->dv[45] = DifAndCtrl_P.PID.Kp[5];
  DifAndCtrl_B->dv[53] = 0.0;
  DifAndCtrl_B->dv[61] = 0.0;
  DifAndCtrl_B->dv[6] = 0.0;
  DifAndCtrl_B->dv[14] = 0.0;
  DifAndCtrl_B->dv[22] = 0.0;
  DifAndCtrl_B->dv[30] = 0.0;
  DifAndCtrl_B->dv[38] = 0.0;
  DifAndCtrl_B->dv[46] = 0.0;
  DifAndCtrl_B->dv[54] = DifAndCtrl_P.PID.Kp[6];
  DifAndCtrl_B->dv[62] = 0.0;
  DifAndCtrl_B->dv[7] = 0.0;
  DifAndCtrl_B->dv[15] = 0.0;
  DifAndCtrl_B->dv[23] = 0.0;
  DifAndCtrl_B->dv[31] = 0.0;
  DifAndCtrl_B->dv[39] = 0.0;
  DifAndCtrl_B->dv[47] = 0.0;
  DifAndCtrl_B->dv[55] = 0.0;
  DifAndCtrl_B->dv[63] = DifAndCtrl_P.PID.Kp[7];

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  DifAndCtrl_ppval(DifAndCtrl_DW->obj.PPDStruct.breaks,
                   DifAndCtrl_DW->obj.PPDStruct.coefs, DifAndCtrl_B->x_tmp_c,
                   DifAndCtrl_B->rtb_uv_c);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kd'

  DifAndCtrl_B->dv1[0] = DifAndCtrl_P.PID.Kd[0];
  DifAndCtrl_B->dv1[8] = 0.0;
  DifAndCtrl_B->dv1[16] = 0.0;
  DifAndCtrl_B->dv1[24] = 0.0;
  DifAndCtrl_B->dv1[32] = 0.0;
  DifAndCtrl_B->dv1[40] = 0.0;
  DifAndCtrl_B->dv1[48] = 0.0;
  DifAndCtrl_B->dv1[56] = 0.0;
  DifAndCtrl_B->dv1[1] = 0.0;
  DifAndCtrl_B->dv1[9] = DifAndCtrl_P.PID.Kd[1];
  DifAndCtrl_B->dv1[17] = 0.0;
  DifAndCtrl_B->dv1[25] = 0.0;
  DifAndCtrl_B->dv1[33] = 0.0;
  DifAndCtrl_B->dv1[41] = 0.0;
  DifAndCtrl_B->dv1[49] = 0.0;
  DifAndCtrl_B->dv1[57] = 0.0;
  DifAndCtrl_B->dv1[2] = 0.0;
  DifAndCtrl_B->dv1[10] = 0.0;
  DifAndCtrl_B->dv1[18] = DifAndCtrl_P.PID.Kd[2];
  DifAndCtrl_B->dv1[26] = 0.0;
  DifAndCtrl_B->dv1[34] = 0.0;
  DifAndCtrl_B->dv1[42] = 0.0;
  DifAndCtrl_B->dv1[50] = 0.0;
  DifAndCtrl_B->dv1[58] = 0.0;
  DifAndCtrl_B->dv1[3] = 0.0;
  DifAndCtrl_B->dv1[11] = 0.0;
  DifAndCtrl_B->dv1[19] = 0.0;
  DifAndCtrl_B->dv1[27] = DifAndCtrl_P.PID.Kd[3];
  DifAndCtrl_B->dv1[35] = 0.0;
  DifAndCtrl_B->dv1[43] = 0.0;
  DifAndCtrl_B->dv1[51] = 0.0;
  DifAndCtrl_B->dv1[59] = 0.0;
  DifAndCtrl_B->dv1[4] = 0.0;
  DifAndCtrl_B->dv1[12] = 0.0;
  DifAndCtrl_B->dv1[20] = 0.0;
  DifAndCtrl_B->dv1[28] = 0.0;
  DifAndCtrl_B->dv1[36] = DifAndCtrl_P.PID.Kd[4];
  DifAndCtrl_B->dv1[44] = 0.0;
  DifAndCtrl_B->dv1[52] = 0.0;
  DifAndCtrl_B->dv1[60] = 0.0;
  DifAndCtrl_B->dv1[5] = 0.0;
  DifAndCtrl_B->dv1[13] = 0.0;
  DifAndCtrl_B->dv1[21] = 0.0;
  DifAndCtrl_B->dv1[29] = 0.0;
  DifAndCtrl_B->dv1[37] = 0.0;
  DifAndCtrl_B->dv1[45] = DifAndCtrl_P.PID.Kd[5];
  DifAndCtrl_B->dv1[53] = 0.0;
  DifAndCtrl_B->dv1[61] = 0.0;
  DifAndCtrl_B->dv1[6] = 0.0;
  DifAndCtrl_B->dv1[14] = 0.0;
  DifAndCtrl_B->dv1[22] = 0.0;
  DifAndCtrl_B->dv1[30] = 0.0;
  DifAndCtrl_B->dv1[38] = 0.0;
  DifAndCtrl_B->dv1[46] = 0.0;
  DifAndCtrl_B->dv1[54] = DifAndCtrl_P.PID.Kd[6];
  DifAndCtrl_B->dv1[62] = 0.0;
  DifAndCtrl_B->dv1[7] = 0.0;
  DifAndCtrl_B->dv1[15] = 0.0;
  DifAndCtrl_B->dv1[23] = 0.0;
  DifAndCtrl_B->dv1[31] = 0.0;
  DifAndCtrl_B->dv1[39] = 0.0;
  DifAndCtrl_B->dv1[47] = 0.0;
  DifAndCtrl_B->dv1[55] = 0.0;
  DifAndCtrl_B->dv1[63] = DifAndCtrl_P.PID.Kd[7];
  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    // Sum: '<S13>/Minus' incorporates:
    //   Integrator: '<S4>/Integrator'

    DifAndCtrl_B->rtb_uv_i_m[DifAndCtrl_B->c_j] = DifAndCtrl_B->dv3
      [DifAndCtrl_B->c_j] - DifAndCtrl_X->Integrator_CSTATE[DifAndCtrl_B->c_j];

    // Sum: '<S13>/Minus1' incorporates:
    //   Integrator: '<S4>/Integrator1'

    DifAndCtrl_B->dv4[DifAndCtrl_B->c_j] = DifAndCtrl_B->rtb_uv_c
      [DifAndCtrl_B->c_j] - DifAndCtrl_X->Integrator1_CSTATE[DifAndCtrl_B->c_j];

    // MATLAB Function: '<S11>/PD Controller'
    DifAndCtrl_B->dv5[DifAndCtrl_B->c_j] = 0.0;
  }

  // MATLAB Function: '<S11>/PD Controller'
  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    DifAndCtrl_B->D17 = DifAndCtrl_B->rtb_uv_i_m[DifAndCtrl_B->c_j];
    for (DifAndCtrl_B->jj = 0; DifAndCtrl_B->jj < 8; DifAndCtrl_B->jj++) {
      DifAndCtrl_B->dv5[DifAndCtrl_B->jj] += DifAndCtrl_B->dv[(DifAndCtrl_B->c_j
        << 3) + DifAndCtrl_B->jj] * DifAndCtrl_B->D17;
    }
  }

  memset(&DifAndCtrl_B->dv3[0], 0, sizeof(real_T) << 3U);
  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    DifAndCtrl_B->D17 = DifAndCtrl_B->dv4[DifAndCtrl_B->c_j];
    for (DifAndCtrl_B->jj = 0; DifAndCtrl_B->jj < 8; DifAndCtrl_B->jj++) {
      DifAndCtrl_B->dv3[DifAndCtrl_B->jj] += DifAndCtrl_B->dv1
        [(DifAndCtrl_B->c_j << 3) + DifAndCtrl_B->jj] * DifAndCtrl_B->D17;
    }
  }

  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    // Sum: '<S11>/Add1' incorporates:
    //   MATLAB Function: '<S11>/PD Controller'
    //   Sum: '<S11>/Sum'

    DifAndCtrl_B->rtb_uv_i_m[DifAndCtrl_B->c_j] = ((DifAndCtrl_B->
      dv5[DifAndCtrl_B->c_j] + DifAndCtrl_B->dv3[DifAndCtrl_B->c_j]) +
      DifAndCtrl_B->dv2[DifAndCtrl_B->c_j]) - DifAndCtrl_B->fx[DifAndCtrl_B->c_j];

    // Product: '<S11>/Matrix Multiply'
    DifAndCtrl_B->rtb_uv_c[DifAndCtrl_B->c_j] = 0.0;
  }

  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    // Product: '<S11>/Matrix Multiply'
    DifAndCtrl_B->D17 = DifAndCtrl_B->rtb_uv_i_m[DifAndCtrl_B->c_j];
    for (DifAndCtrl_B->jj = 0; DifAndCtrl_B->jj < 8; DifAndCtrl_B->jj++) {
      DifAndCtrl_B->rtb_uv_c[DifAndCtrl_B->jj] += DifAndCtrl_B->ginv
        [(DifAndCtrl_B->c_j << 3) + DifAndCtrl_B->jj] * DifAndCtrl_B->D17;
    }

    // Product: '<S2>/Matrix Multiply' incorporates:
    //   Outport: '<Root>/ForcesAndTorques'

    DifAndCtrl_Y->ForcesAndTorques[DifAndCtrl_B->c_j] = 0.0;
  }

  for (i = 0; i < 8; i++) {
    // Product: '<S2>/Matrix Multiply' incorporates:
    //   Outport: '<Root>/ForcesAndTorques'

    DifAndCtrl_B->D17 = DifAndCtrl_B->rtb_uv_c[i];
    for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
      DifAndCtrl_Y->ForcesAndTorques[DifAndCtrl_B->c_j] += DifAndCtrl_B->BMinv
        [(i << 3) + DifAndCtrl_B->c_j] * DifAndCtrl_B->D17;
    }

    // Sum: '<S4>/Sum1' incorporates:
    //   Integrator: '<S4>/Integrator'

    DifAndCtrl_B->fx[i] = DifAndCtrl_U->Positions[i] -
      DifAndCtrl_X->Integrator_CSTATE[i];
  }

  // MATLAB Function: '<S4>/U power x2' incorporates:
  //   Constant: '<S4>/Q3'

  DifAndCtrl_Upowerx1(DifAndCtrl_B->fx, DifAndCtrl_P.Differentiator.w1,
                      DifAndCtrl_B->rtb_uv_c);

  // MATLAB Function: '<S4>/U power x1' incorporates:
  //   Constant: '<S4>/Q5'

  DifAndCtrl_Upowerx1(DifAndCtrl_B->fx, DifAndCtrl_P.Differentiator.p1,
                      DifAndCtrl_B->rtb_uv_i_m);
  for (i = 0; i < 8; i++) {
    // Signum: '<S4>/Sign' incorporates:
    //   Sum: '<S4>/Sum1'

    DifAndCtrl_B->Clock2 = DifAndCtrl_B->fx[i];
    if (rtIsNaN(DifAndCtrl_B->Clock2)) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      DifAndCtrl_B->Clock2 = (rtNaN);
    } else if (DifAndCtrl_B->Clock2 < 0.0) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      DifAndCtrl_B->Clock2 = -1.0;
    } else {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      DifAndCtrl_B->Clock2 = (DifAndCtrl_B->Clock2 > 0.0);
    }

    DifAndCtrl_B->Sum4[i] = DifAndCtrl_B->Clock2;

    // Sum: '<S4>/Sum3' incorporates:
    //   Constant: '<S4>/G1'
    //   Constant: '<S4>/Q1'
    //   Integrator: '<S4>/Integrator1'
    //   Product: '<S4>/Product3'
    //   Product: '<S4>/Product4'
    //   Signum: '<S4>/Sign'
    //   Signum: '<S4>/Sign1'

    DifAndCtrl_B->Sum3[i] = (DifAndCtrl_P.Differentiator.G1[i] *
      DifAndCtrl_B->Clock2 * DifAndCtrl_B->rtb_uv_c[i] +
      DifAndCtrl_X->Integrator1_CSTATE[i]) + DifAndCtrl_P.Differentiator.Q1[i] *
      DifAndCtrl_B->Clock2 * DifAndCtrl_B->rtb_uv_i_m[i];
  }

  // MATLAB Function: '<S4>/U power x3' incorporates:
  //   Constant: '<S4>/Q4'

  DifAndCtrl_Upowerx1(DifAndCtrl_B->fx, DifAndCtrl_P.Differentiator.w2,
                      DifAndCtrl_B->rtb_uv_i_m);

  // MATLAB Function: '<S4>/U power x4' incorporates:
  //   Constant: '<S4>/Q6'

  DifAndCtrl_Upowerx1(DifAndCtrl_B->fx, DifAndCtrl_P.Differentiator.p2,
                      DifAndCtrl_B->rtb_uv_c);
  for (DifAndCtrl_B->c_j = 0; DifAndCtrl_B->c_j < 8; DifAndCtrl_B->c_j++) {
    // Signum: '<S4>/Sign2' incorporates:
    //   Constant: '<S4>/G2'
    //   Product: '<S4>/Product5'

    DifAndCtrl_B->Clock2 = DifAndCtrl_B->Sum4[DifAndCtrl_B->c_j];

    // Sum: '<S4>/Sum4' incorporates:
    //   Constant: '<S4>/G2'
    //   Constant: '<S4>/Q2'
    //   Product: '<S4>/Product5'
    //   Product: '<S4>/Product6'
    //   Signum: '<S4>/Sign'
    //   Signum: '<S4>/Sign2'
    //   Signum: '<S4>/Sign3'

    DifAndCtrl_B->Sum4[DifAndCtrl_B->c_j] =
      DifAndCtrl_P.Differentiator.G2[DifAndCtrl_B->c_j] * DifAndCtrl_B->Clock2 *
      DifAndCtrl_B->rtb_uv_i_m[DifAndCtrl_B->c_j] +
      DifAndCtrl_P.Differentiator.Q2[DifAndCtrl_B->c_j] * DifAndCtrl_B->Clock2 *
      DifAndCtrl_B->rtb_uv_c[DifAndCtrl_B->c_j];
  }

  if (DifAndCtrl_M->isMajorTimeStep()) {
    rt_ertODEUpdateContinuousStates(&DifAndCtrl_M->solverInfo, DifAndCtrl_M,
      DifAndCtrl_U, DifAndCtrl_Y);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++DifAndCtrl_M->Timing.clockTick0;
    DifAndCtrl_M->Timing.t[0] = rtsiGetSolverStopTime(&DifAndCtrl_M->solverInfo);

    {
      // Update absolute timer for sample time: [0.01s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.01, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      DifAndCtrl_M->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void DifAndCtrl_derivatives(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M)
{
  B_DifAndCtrl_T *DifAndCtrl_B = DifAndCtrl_M->blockIO;
  XDot_DifAndCtrl_T *_rtXdot;
  _rtXdot = ((XDot_DifAndCtrl_T *) DifAndCtrl_M->derivs);

  // Derivatives for Integrator: '<S4>/Integrator' incorporates:
  //   Sum: '<S4>/Sum3'

  memcpy(&_rtXdot->Integrator_CSTATE[0], &DifAndCtrl_B->Sum3[0], sizeof(real_T) <<
         3U);

  // Derivatives for Integrator: '<S4>/Integrator1' incorporates:
  //   Sum: '<S4>/Sum4'

  memcpy(&_rtXdot->Integrator1_CSTATE[0], &DifAndCtrl_B->Sum4[0], sizeof(real_T)
         << 3U);
}

// Model initialize function
void DifAndCtrl_initialize(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M,
  ExtU_DifAndCtrl_T *DifAndCtrl_U, ExtY_DifAndCtrl_T *DifAndCtrl_Y)
{
  B_DifAndCtrl_T *DifAndCtrl_B = DifAndCtrl_M->blockIO;
  DW_DifAndCtrl_T *DifAndCtrl_DW = DifAndCtrl_M->dwork;
  X_DifAndCtrl_T *DifAndCtrl_X = DifAndCtrl_M->contStates;
  XDis_DifAndCtrl_T *DifAndCtrl_XDis = ((XDis_DifAndCtrl_T *)
    DifAndCtrl_M->contStateDisabled);

  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&DifAndCtrl_M->solverInfo,
                          &DifAndCtrl_M->Timing.simTimeStep);
    rtsiSetTPtr(&DifAndCtrl_M->solverInfo, DifAndCtrl_M->getTPtrPtr());
    rtsiSetStepSizePtr(&DifAndCtrl_M->solverInfo,
                       &DifAndCtrl_M->Timing.stepSize0);
    rtsiSetdXPtr(&DifAndCtrl_M->solverInfo, &DifAndCtrl_M->derivs);
    rtsiSetContStatesPtr(&DifAndCtrl_M->solverInfo, (real_T **)
                         &DifAndCtrl_M->contStates);
    rtsiSetNumContStatesPtr(&DifAndCtrl_M->solverInfo,
      &DifAndCtrl_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&DifAndCtrl_M->solverInfo,
      &DifAndCtrl_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&DifAndCtrl_M->solverInfo,
      &DifAndCtrl_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&DifAndCtrl_M->solverInfo,
      &DifAndCtrl_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&DifAndCtrl_M->solverInfo, (boolean_T**)
      &DifAndCtrl_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&DifAndCtrl_M->solverInfo,
                          DifAndCtrl_M->getErrorStatusPtr());
    rtsiSetRTModelPtr(&DifAndCtrl_M->solverInfo, DifAndCtrl_M);
  }

  rtsiSetSimTimeStep(&DifAndCtrl_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&DifAndCtrl_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&DifAndCtrl_M->solverInfo, false);
  DifAndCtrl_M->intgData.y = DifAndCtrl_M->odeY;
  DifAndCtrl_M->intgData.f[0] = DifAndCtrl_M->odeF[0];
  DifAndCtrl_M->intgData.f[1] = DifAndCtrl_M->odeF[1];
  DifAndCtrl_M->intgData.f[2] = DifAndCtrl_M->odeF[2];
  DifAndCtrl_M->intgData.f[3] = DifAndCtrl_M->odeF[3];
  DifAndCtrl_M->contStates = ((X_DifAndCtrl_T *) DifAndCtrl_X);
  DifAndCtrl_M->contStateDisabled = ((XDis_DifAndCtrl_T *) DifAndCtrl_XDis);
  DifAndCtrl_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&DifAndCtrl_M->solverInfo, static_cast<void *>
                    (&DifAndCtrl_M->intgData));
  rtsiSetSolverName(&DifAndCtrl_M->solverInfo,"ode4");
  DifAndCtrl_M->setTPtr(&DifAndCtrl_M->Timing.tArray[0]);
  DifAndCtrl_M->Timing.stepSize0 = 0.01;

  // block I/O
  (void) memset((static_cast<void *>(DifAndCtrl_B)), 0,
                sizeof(B_DifAndCtrl_T));

  // states (continuous)
  {
    (void) memset(static_cast<void *>(DifAndCtrl_X), 0,
                  sizeof(X_DifAndCtrl_T));
  }

  // disabled states
  {
    (void) memset(static_cast<void *>(DifAndCtrl_XDis), 0,
                  sizeof(XDis_DifAndCtrl_T));
  }

  // states (dwork)
  (void) memset(static_cast<void *>(DifAndCtrl_DW), 0,
                sizeof(DW_DifAndCtrl_T));

  // external inputs
  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DifAndCtrl_U->Positions[i] = 0.0;
    }
  }

  // external outputs
  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DifAndCtrl_Y->ForcesAndTorques[i] = 0.0;
    }
  }

  {
    int32_T i;

    // InitializeConditions for Integrator: '<S4>/Integrator'
    memcpy(&DifAndCtrl_X->Integrator_CSTATE[0], &DifAndCtrl_P.Integrator_IC[0],
           sizeof(real_T) << 3U);

    // InitializeConditions for Integrator: '<S4>/Integrator1'
    memcpy(&DifAndCtrl_X->Integrator1_CSTATE[0], &DifAndCtrl_P.Integrator1_IC[0],
           sizeof(real_T) << 3U);

    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memset(&DifAndCtrl_DW->obj.AccelerationBoundaryCondition[0], 0, 10U * sizeof
           (real_T));
    for (i = 0; i < 5; i++) {
      DifAndCtrl_DW->obj.tunablePropertyChanged[i] = false;
    }

    DifAndCtrl_DW->obj.TimePoints[0] = DifAndCtrl_P.Trajectory.Tstamps[0];
    DifAndCtrl_DW->obj.TimePoints[1] = DifAndCtrl_P.Trajectory.Tstamps[1];
    memcpy(&DifAndCtrl_DW->obj.Waypoints[0], &DifAndCtrl_P.Trajectory.Waypoints
           [0], sizeof(real_T) << 4U);
    memcpy(&DifAndCtrl_DW->obj.VelocityBoundaryCondition[0],
           &DifAndCtrl_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) <<
           4U);
    DifAndCtrl_DW->obj.isInitialized = 1;
    PolyTrajSys_regeneratePPFormFro(&DifAndCtrl_DW->obj,
      DifAndCtrl_DW->obj.Waypoints, DifAndCtrl_DW->obj.TimePoints, DifAndCtrl_B);
    DifAndCtrl_DW->obj.TunablePropsChanged = false;

    // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  }
}

// Model terminate function
void DifAndCtrl_terminate(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M)
{
  // (no terminate code required)
  UNUSED_PARAMETER(DifAndCtrl_M);
}

B_DifAndCtrl_T* RT_MODEL_DifAndCtrl_T::getBlockIO() const
{
  return blockIO;
}

void RT_MODEL_DifAndCtrl_T::setBlockIO(B_DifAndCtrl_T* aBlockIO)
{
  blockIO = aBlockIO;
}

XDis_DifAndCtrl_T* RT_MODEL_DifAndCtrl_T::getContStateDisabled() const
{
  return contStateDisabled;
}

void RT_MODEL_DifAndCtrl_T::setContStateDisabled(XDis_DifAndCtrl_T
  * aContStateDisabled)
{
  contStateDisabled = aContStateDisabled;
}

const char_T** RT_MODEL_DifAndCtrl_T::getErrorStatusPtr()
{
  return &errorStatus;
}

X_DifAndCtrl_T* RT_MODEL_DifAndCtrl_T::getContStates() const
{
  return contStates;
}

void RT_MODEL_DifAndCtrl_T::setContStates(X_DifAndCtrl_T* aContStates)
{
  contStates = aContStates;
}

boolean_T RT_MODEL_DifAndCtrl_T::getStopRequested() const
{
  return (Timing.stopRequestedFlag);
}

void RT_MODEL_DifAndCtrl_T::setStopRequested(boolean_T aStopRequested)
{
  (Timing.stopRequestedFlag = aStopRequested);
}

ODE4_IntgData RT_MODEL_DifAndCtrl_T::getIntgData() const
{
  return intgData;
}

void RT_MODEL_DifAndCtrl_T::setIntgData(ODE4_IntgData aIntgData)
{
  intgData = aIntgData;
}

boolean_T RT_MODEL_DifAndCtrl_T::getDerivCacheNeedsReset() const
{
  return derivCacheNeedsReset;
}

void RT_MODEL_DifAndCtrl_T::setDerivCacheNeedsReset(boolean_T
  aDerivCacheNeedsReset)
{
  derivCacheNeedsReset = aDerivCacheNeedsReset;
}

const char_T* RT_MODEL_DifAndCtrl_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_DifAndCtrl_T::setErrorStatus(const char_T* const aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

boolean_T RT_MODEL_DifAndCtrl_T::
  getContTimeOutputInconsistentWithStateAtMajorStepFlag() const
{
  return CTOutputIncnstWithState;
}

void RT_MODEL_DifAndCtrl_T::
  setContTimeOutputInconsistentWithStateAtMajorStepFlag(boolean_T
  aContTimeOutputInconsistentWithStateAtMajorStepFlag)
{
  CTOutputIncnstWithState = aContTimeOutputInconsistentWithStateAtMajorStepFlag;
}

boolean_T RT_MODEL_DifAndCtrl_T::isMajorTimeStep() const
{
  return ((Timing.simTimeStep) == MAJOR_TIME_STEP);
}

const odeFSubArray* RT_MODEL_DifAndCtrl_T::getOdeF() const
{
  return odeF;
}

boolean_T RT_MODEL_DifAndCtrl_T::isMinorTimeStep() const
{
  return ((Timing.simTimeStep) == MINOR_TIME_STEP);
}

const real_T* RT_MODEL_DifAndCtrl_T::getOdeY() const
{
  return odeY;
}

int_T* RT_MODEL_DifAndCtrl_T::getPeriodicContStateIndices() const
{
  return periodicContStateIndices;
}

void RT_MODEL_DifAndCtrl_T::setPeriodicContStateIndices(int_T
  * aPeriodicContStateIndices)
{
  periodicContStateIndices = aPeriodicContStateIndices;
}

time_T* RT_MODEL_DifAndCtrl_T::getTPtr() const
{
  return (Timing.t);
}

void RT_MODEL_DifAndCtrl_T::setTPtr(time_T* aTPtr)
{
  (Timing.t = aTPtr);
}

real_T* RT_MODEL_DifAndCtrl_T::getPeriodicContStateRanges() const
{
  return periodicContStateRanges;
}

void RT_MODEL_DifAndCtrl_T::setPeriodicContStateRanges(real_T
  * aPeriodicContStateRanges)
{
  periodicContStateRanges = aPeriodicContStateRanges;
}

DW_DifAndCtrl_T* RT_MODEL_DifAndCtrl_T::getRootDWork() const
{
  return dwork;
}

void RT_MODEL_DifAndCtrl_T::setRootDWork(DW_DifAndCtrl_T* aRootDWork)
{
  dwork = aRootDWork;
}

boolean_T* RT_MODEL_DifAndCtrl_T::getStopRequestedPtr()
{
  return (&(Timing.stopRequestedFlag));
}

time_T** RT_MODEL_DifAndCtrl_T::getTPtrPtr()
{
  return &(Timing.t);
}

time_T RT_MODEL_DifAndCtrl_T::getTStart() const
{
  return (Timing.tStart);
}

boolean_T RT_MODEL_DifAndCtrl_T::getZCCacheNeedsReset() const
{
  return zCCacheNeedsReset;
}

void RT_MODEL_DifAndCtrl_T::setZCCacheNeedsReset(boolean_T aZCCacheNeedsReset)
{
  zCCacheNeedsReset = aZCCacheNeedsReset;
}

real_T* RT_MODEL_DifAndCtrl_T::getdX() const
{
  return derivs;
}

void RT_MODEL_DifAndCtrl_T::setdX(real_T* adX)
{
  derivs = adX;
}

//
// File trailer for generated code.
//
// [EOF]
//
