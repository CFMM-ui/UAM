//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Hardware.cpp
//
// Code generated for Simulink model 'Hardware'.
//
// Model version                  : 1.57
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Fri Oct 23 10:27:09 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Hardware.h"
#include "rtwtypes.h"
#include "Hardware_types.h"
#include "Hardware_private.h"
#include <math.h>
#include "rt_powd_snf.h"
#include <string.h>

extern "C"
{

#include "rt_nonfinite.h"

}

P_Hardware_T Hardware_P = {
  // Expression: zeros( size(Trajectory.Waypoints) )
  //  Referenced by: '<S3>/Polynomial Trajectory'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0 },

  // Computed Parameter: DiscreteTimeIntegrator_gainval
  //  Referenced by: '<S4>/Discrete-Time Integrator'

  0.02,

  // Expression: 0
  //  Referenced by: '<S4>/Discrete-Time Integrator'

  0.0,

  // Computed Parameter: DiscreteTimeIntegrator1_gainval
  //  Referenced by: '<S4>/Discrete-Time Integrator1'

  0.02,

  // Expression: 0
  //  Referenced by: '<S4>/Discrete-Time Integrator1'

  0.0
};

// Forward declaration for local functions
static real_T Hardware_rt_powd_snf(real_T u0, real_T u1, B_Hardware_c_T *localB);
static void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
  const real_T waypoints[16], const real_T timeData[2], B_Hardware_c_T *localB);
static void Hardware_mldivide_0QKHZcd4_i(const real_T A[64], real_T B[8],
  B_Hardware_c_T *localB);
static void Hardware_ppval(const real_T pp_breaks[4], const real_T pp_coefs[96],
  real_T x, real_T v[8]);

//
// Output and update for atomic system:
//    '<S4>/U power x1'
//    '<S4>/U power x2'
//    '<S4>/U power x3'
//    '<S4>/U power x4'
//
void Hardware_Upowerx1(const real_T rtu_u[8], const real_T rtu_v[8], real_T
  rty_uv[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    rty_uv[i] = rt_powd_snf(fabs(rtu_u[i]), rtu_v[i]);
  }
}

static real_T Hardware_rt_powd_snf(real_T u0, real_T u1, B_Hardware_c_T *localB)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    localB->d201 = fabs(u0);
    localB->d202 = fabs(u1);
    if (rtIsInf(u1)) {
      if (localB->d201 == 1.0) {
        y = 1.0;
      } else if (localB->d201 > 1.0) {
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
    } else if (localB->d202 == 0.0) {
      y = 1.0;
    } else if (localB->d202 == 1.0) {
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
  const real_T waypoints[16], const real_T timeData[2], B_Hardware_c_T *localB)
{
  int32_T b_i;
  int32_T b_j;
  int32_T i;
  static const int8_T tmp[4] = { 0, 0, 0, 1 };

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  localB->finalTime = timeData[1] - timeData[0];
  for (b_j = 0; b_j < 8; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    localB->obj_PPStruct = waypoints[b_j];
    localB->obj_PPStruct_n = obj->VelocityBoundaryCondition[b_j];
    localB->waypoints_idx_0 = waypoints[b_j + 8] - (localB->finalTime *
      localB->obj_PPStruct_n + localB->obj_PPStruct);
    localB->xtmp = obj->VelocityBoundaryCondition[b_j + 8] - (0.0 *
      localB->obj_PPStruct + localB->obj_PPStruct_n);
    localB->obj_PPStruct_tmp = localB->finalTime * localB->finalTime;
    localB->obj_PPStruct_k = 3.0 / localB->obj_PPStruct_tmp *
      localB->waypoints_idx_0 + -1.0 / localB->finalTime * localB->xtmp;
    localB->waypoints_idx_0 = 1.0 / localB->obj_PPStruct_tmp * localB->xtmp +
      -2.0 / Hardware_rt_powd_snf(localB->finalTime, 3.0, localB) *
      localB->waypoints_idx_0;
    obj->PPStruct.breaks[0] = localB->waypoints_idx_0;
    obj->PPStruct.breaks[3] = localB->obj_PPStruct;
    obj->PPStruct.breaks[1] = localB->obj_PPStruct_k;
    obj->PPStruct.breaks[2] = localB->obj_PPStruct_n;
    localB->coefMat[b_j] = localB->waypoints_idx_0;
    localB->coefMat[b_j + 8] = localB->obj_PPStruct_k;
    localB->coefMat[b_j + 16] = localB->obj_PPStruct_n;
    localB->coefMat[b_j + 24] = localB->obj_PPStruct;
  }

  memset(&localB->coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&localB->coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    b_i = tmp[b_j];
    for (i = 0; i < 8; i++) {
      localB->coeffMat[i + 24] += localB->coefMat[(b_j << 3) + i] * static_cast<
        real_T>(b_i);
    }
  }

  memset(&localB->coefsWithFlatStart[0], 0, sizeof(real_T) << 6U);
  memcpy(&localB->coefsWithFlatStart[0], &localB->coeffMat[0], sizeof(real_T) <<
         3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&localB->coefsWithFlatStart[8], &localB->coefMat[0], sizeof(real_T) <<
         3U);
  memcpy(&localB->coefsWithFlatStart[16], &localB->coeffMat[8], sizeof(real_T) <<
         3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&localB->coefsWithFlatStart[24], &localB->coefMat[8], sizeof(real_T) <<
         3U);
  memcpy(&localB->coefsWithFlatStart[32], &localB->coeffMat[16], sizeof(real_T) <<
         3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&localB->coefsWithFlatStart[40], &localB->coefMat[16], sizeof(real_T) <<
         3U);
  memcpy(&localB->coefsWithFlatStart[48], &localB->coeffMat[24], sizeof(real_T) <<
         3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&localB->coefsWithFlatStart[56], &localB->coefMat[24], sizeof(real_T) <<
         3U);
  obj->PPStruct.breaks[0] = Hardware_rt_powd_snf(localB->finalTime, 3.0, localB);
  obj->PPStruct.breaks[1] = Hardware_rt_powd_snf(localB->finalTime, 2.0, localB);
  obj->PPStruct.breaks[2] = Hardware_rt_powd_snf(localB->finalTime, 1.0, localB);
  obj->PPStruct.breaks[3] = Hardware_rt_powd_snf(localB->finalTime, 0.0, localB);
  memset(&localB->coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&localB->coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    localB->finalTime = obj->PPStruct.breaks[b_j];
    for (b_i = 0; b_i < 8; b_i++) {
      localB->coeffMat[b_i + 24] += localB->coefsWithFlatStart[((b_j << 4) + b_i)
        + 8] * localB->finalTime;
    }
  }

  memset(&obj->PPDStruct.coefs[0], 0, 96U * sizeof(real_T));
  for (b_j = 0; b_j < 4; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memcpy(&obj->PPDStruct.coefs[b_j * 24], &localB->coefsWithFlatStart[b_j << 4],
           sizeof(real_T) << 4U);
    memcpy(&obj->PPDStruct.coefs[b_j * 24 + 16], &localB->coeffMat[b_j << 3],
           sizeof(real_T) << 3U);
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

// Function for MATLAB Function: '<S9>/MATLAB Function1'
static void Hardware_mldivide_0QKHZcd4_i(const real_T A[64], real_T B[8],
  B_Hardware_c_T *localB)
{
  int32_T jj;
  int32_T kAcol;
  memcpy(&localB->b_A[0], &A[0], sizeof(real_T) << 6U);
  for (int32_T j = 0; j < 8; j++) {
    localB->ipiv_m[j] = static_cast<int8_T>(j + 1);
  }

  for (int32_T j = 0; j < 7; j++) {
    int32_T a;
    int32_T jA;
    int32_T n;
    int8_T ipiv;
    jj = j * 9;
    n = 9 - j;
    a = 0;
    localB->smax_a = fabs(localB->b_A[jj]);
    for (kAcol = 2; kAcol < n; kAcol++) {
      localB->s_f = fabs(localB->b_A[(jj + kAcol) - 1]);
      if (localB->s_f > localB->smax_a) {
        a = kAcol - 1;
        localB->smax_a = localB->s_f;
      }
    }

    if (localB->b_A[jj + a] != 0.0) {
      if (a != 0) {
        n = j + a;
        localB->ipiv_m[j] = static_cast<int8_T>(n + 1);
        for (kAcol = 0; kAcol < 8; kAcol++) {
          jA = kAcol << 3;
          a = jA + j;
          localB->smax_a = localB->b_A[a];
          jA += n;
          localB->b_A[a] = localB->b_A[jA];
          localB->b_A[jA] = localB->smax_a;
        }
      }

      n = (jj - j) + 8;
      for (kAcol = jj + 2; kAcol <= n; kAcol++) {
        localB->b_A[kAcol - 1] /= localB->b_A[jj];
      }
    }

    a = 6 - j;
    jA = jj + 10;
    for (kAcol = 0; kAcol <= a; kAcol++) {
      localB->smax_a = localB->b_A[((kAcol << 3) + jj) + 8];
      if (localB->smax_a != 0.0) {
        int32_T c;
        c = (jA - j) + 6;
        for (n = jA; n <= c; n++) {
          localB->b_A[n - 1] += localB->b_A[((jj + n) - jA) + 1] *
            -localB->smax_a;
        }
      }

      jA += 8;
    }

    ipiv = localB->ipiv_m[j];
    if (j + 1 != ipiv) {
      localB->smax_a = B[j];
      B[j] = B[ipiv - 1];
      B[ipiv - 1] = localB->smax_a;
    }
  }

  for (int32_T j = 0; j < 8; j++) {
    kAcol = j << 3;
    if (B[j] != 0.0) {
      for (jj = j + 2; jj < 9; jj++) {
        B[jj - 1] -= localB->b_A[(jj + kAcol) - 1] * B[j];
      }
    }
  }

  for (int32_T j = 7; j >= 0; j--) {
    kAcol = j << 3;
    localB->smax_a = B[j];
    if (localB->smax_a != 0.0) {
      B[j] = localB->smax_a / localB->b_A[j + kAcol];
      for (jj = 0; jj < j; jj++) {
        B[jj] -= localB->b_A[jj + kAcol] * B[j];
      }
    }
  }
}

static void Hardware_ppval(const real_T pp_breaks[4], const real_T pp_coefs[96],
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

// System initialize for referenced model: 'Hardware'
void Hardware_Init(B_Hardware_c_T *localB, DW_Hardware_f_T *localDW)
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' 
    localDW->DiscreteTimeIntegrator_DSTATE[i] =
      Hardware_P.DiscreteTimeIntegrator_IC;

    // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' 
    localDW->DiscreteTimeIntegrator1_DSTATE[i] =
      Hardware_P.DiscreteTimeIntegrator1_IC;
  }

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&localDW->obj.AccelerationBoundaryCondition[0], 0, 10U * sizeof(real_T));
  for (i = 0; i < 5; i++) {
    localDW->obj.tunablePropertyChanged[i] = false;
  }

  localDW->objisempty = true;
  localDW->obj.TimePoints[0] = rtP_Trajectory.Tstamps[0];
  localDW->obj.TimePoints[1] = rtP_Trajectory.Tstamps[1];
  memcpy(&localDW->obj.Waypoints[0], &rtP_Trajectory.Waypoints[0], sizeof(real_T)
         << 4U);
  memcpy(&localDW->obj.VelocityBoundaryCondition[0],
         &Hardware_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) << 4U);
  localDW->obj.isInitialized = 1;
  PolyTrajSys_regeneratePPFormFro(&localDW->obj, localDW->obj.Waypoints,
    localDW->obj.TimePoints, localB);
  localDW->obj.TunablePropsChanged = false;

  // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
}

// Output and update for referenced model: 'Hardware'
void Hardware(RT_MODEL_Hardware_T * const Hardware_M, const real_T
              rtu_Positions[8], real_T rty_ForcesAndTorque[8], B_Hardware_c_T
              *localB, DW_Hardware_f_T *localDW)
{
  real_T tmp;
  int32_T i;
  int32_T jA;
  int32_T n;
  int8_T ipiv;
  boolean_T exitg1;
  boolean_T propChange;

  // MATLAB Function: '<S9>/MATLAB Function1' incorporates:
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  //   MATLAB Function: '<S2>/GetBInvMatrix'

  localB->smax = sin(localDW->DiscreteTimeIntegrator_DSTATE[5]);
  localB->D14_tmp = sin(localDW->DiscreteTimeIntegrator_DSTATE[6]);
  localB->s = cos(localDW->DiscreteTimeIntegrator_DSTATE[5]);
  localB->D14_tmp_c = sin(localDW->DiscreteTimeIntegrator_DSTATE[4]);
  localB->D14_tmp_k = sin(localDW->DiscreteTimeIntegrator_DSTATE[3]);
  localB->D14_tmp_cx = cos(localDW->DiscreteTimeIntegrator_DSTATE[3]);
  localB->D14_tmp_b = cos(localDW->DiscreteTimeIntegrator_DSTATE[7]);
  localB->D14_tmp_p = sin(localDW->DiscreteTimeIntegrator_DSTATE[7]);
  localB->D14_tmp_tmp = localDW->DiscreteTimeIntegrator_DSTATE[6] +
    localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->D14_tmp_cv = sin(localB->D14_tmp_tmp);
  localB->D14_tmp_f = cos(localDW->DiscreteTimeIntegrator_DSTATE[6]);
  localB->D14_tmp_g = cos(localB->D14_tmp_tmp);
  localB->D14_tmp_n = rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2;
  localB->D14_tmp_tmp_c = rtP_ArmConstants.MC1 * rtP_ArmConstants.Mass1;
  localB->D14_tmp_m = rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 +
    localB->D14_tmp_tmp_c;
  localB->D14_tmp_cz = rtP_ArmConstants.Mass1 + rtP_ArmConstants.Mass2;
  localB->D14_tmp_md = localB->D14_tmp_n * localB->D14_tmp_b + localB->D14_tmp_m;
  localB->D14_tmp_m3 = localB->D14_tmp_cz * rtP_ArmConstants.Hexa_to_joint_L;
  localB->D14_tmp_j = localB->D14_tmp_n * localB->D14_tmp_g;
  localB->D14_tmp_tmp_f = localB->D14_tmp_m * localB->D14_tmp;
  localB->D14_tmp_tmp_p = localB->D14_tmp_n * localB->D14_tmp_cv;
  localB->D14_tmp_h = localB->D14_tmp_tmp_f + localB->D14_tmp_tmp_p;
  localB->D14_tmp_c0 = localB->D14_tmp_h * localB->smax;
  localB->D14_tmp_nb = localB->D14_tmp_md * localB->s;
  localB->D14_tmp_i = localB->D14_tmp_n * localB->smax;
  localB->D14_tmp_my = localB->D14_tmp_n * localB->s * localB->D14_tmp_p *
    localB->D14_tmp_c;
  localB->D14_tmp_e = (-localB->D14_tmp_md * localB->smax + localB->D14_tmp_my) *
    localB->D14_tmp_cx;
  localB->D14_tmp_cf = localB->D14_tmp_cz * -rtP_ArmConstants.Hexa_to_joint_L;
  localB->D14 = (((localB->D14_tmp_i * localB->D14_tmp * localB->D14_tmp_p +
                   localB->D14_tmp_cf * localB->smax) + localB->D14_tmp_nb *
                  localB->D14_tmp * localB->D14_tmp_c) * localB->D14_tmp_cx +
                 ((localB->D14_tmp_m3 + localB->D14_tmp_j) * localB->s *
                  localB->D14_tmp_c + localB->D14_tmp_c0) * localB->D14_tmp_k) +
    (localB->D14_tmp_m * localB->s * localB->D14_tmp_k * localB->D14_tmp_c +
     localB->D14_tmp_e) * localB->D14_tmp_f;
  localB->D15_tmp = cos(localDW->DiscreteTimeIntegrator_DSTATE[4]);
  localB->D15_tmp_tmp = localDW->DiscreteTimeIntegrator_DSTATE[3] +
    localDW->DiscreteTimeIntegrator_DSTATE[6];
  localB->D15_tmp_g = cos(localB->D15_tmp_tmp);
  localB->D15_tmp_tmp_i = localB->D15_tmp_tmp +
    localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->D15_tmp_m = cos(localB->D15_tmp_tmp_i);
  localB->D15_tmp_tmp_n = localB->D14_tmp_m * localB->D15_tmp_g;
  localB->D15_tmp_tmp_c = localB->D14_tmp_n * localB->D15_tmp_m;
  localB->D15_tmp_a = (localB->D14_tmp_m3 * localB->D14_tmp_cx +
                       localB->D15_tmp_tmp_n) + localB->D15_tmp_tmp_c;
  localB->D15 = localB->D15_tmp_a * -localB->s * localB->D15_tmp;
  localB->D16_tmp_tmp = localB->D14_tmp_m * localB->D14_tmp_f;
  localB->D16_tmp = (localB->D16_tmp_tmp + localB->D14_tmp_m3) +
    localB->D14_tmp_j;
  localB->D16_tmp_m = localB->D16_tmp * localB->s;
  localB->D16_tmp_m0 = localB->D16_tmp * localB->smax;
  localB->D16_tmp_j = localB->D16_tmp_m0 * localB->D14_tmp_c;
  localB->D16_tmp_f = localB->D14_tmp_c0 * localB->D14_tmp_c + localB->D16_tmp_m;
  localB->D16 = (localB->D14_tmp_h * -localB->s + localB->D16_tmp_j) *
    localB->D14_tmp_cx + localB->D16_tmp_f * -localB->D14_tmp_k;
  localB->D17_tmp_tmp_o = localB->D14_tmp_k * localB->smax;
  localB->D17_tmp_tmp_o2 = localB->D14_tmp_cx * localB->s;
  localB->D17_tmp = localB->D17_tmp_tmp_o2 * localB->D14_tmp_c +
    localB->D17_tmp_tmp_o;
  localB->D17_tmp_p = rtP_ArmConstants.MC2 * localB->D14_tmp_cv;
  localB->D17_tmp_tmp = localB->s * localB->D14_tmp_k;
  localB->D17_tmp_tmp_a = -localB->D14_tmp_cx * localB->smax;
  localB->D17_tmp_p5 = localB->D17_tmp_tmp * localB->D14_tmp_c +
    localB->D17_tmp_tmp_a;
  localB->D17_tmp_a = rtP_ArmConstants.MC2 * localB->D14_tmp_g;
  localB->D17_tmp_e = rtP_ArmConstants.l1_dim * localB->D14_tmp_f;
  localB->D17_tmp_ax = rtP_ArmConstants.l1_dim * localB->D14_tmp +
    localB->D17_tmp_p;
  localB->D17_tmp_l = localB->D17_tmp_ax * rtP_ArmConstants.Mass2;
  localB->D17_tmp_o = localB->D17_tmp_e + localB->D17_tmp_a;
  localB->D17_tmp_tmp_ob = localB->smax * localB->D14_tmp;
  localB->D17_tmp_tmp_l = localB->s * localB->D14_tmp_f;
  localB->D17_tmp_j = localB->D17_tmp_tmp_l * localB->D14_tmp_c +
    localB->D17_tmp_tmp_ob;
  localB->D17_tmp_pi = localB->s * localB->D14_tmp * localB->D14_tmp_c +
    -localB->D14_tmp_f * localB->smax;
  localB->D17 = ((localB->D14_tmp_tmp_c * localB->D14_tmp_k * localB->D17_tmp_j
                  + localB->D17_tmp_l * localB->D17_tmp) + localB->D17_tmp_o *
                 rtP_ArmConstants.Mass2 * localB->D17_tmp_p5) +
    localB->D14_tmp_tmp_c * localB->D14_tmp_cx * localB->D17_tmp_pi;
  localB->D18_tmp = localB->D17_tmp * localB->D17_tmp_p + localB->D17_tmp_p5 *
    localB->D17_tmp_a;
  localB->D18 = localB->D18_tmp * rtP_ArmConstants.Mass2;
  localB->D24_tmp = rtP_ArmConstants.MC1 * localB->D14_tmp_f +
    rtP_ArmConstants.Hexa_to_joint_L;
  localB->D24_tmp_i = (localB->D17_tmp_e + rtP_ArmConstants.Hexa_to_joint_L) +
    localB->D17_tmp_a;
  localB->D24_tmp_o = localB->D17_tmp_p5 * localB->D17_tmp_ax;
  localB->D17_tmp_e = localB->D15_tmp * localB->D15_tmp;
  localB->D24_tmp_c = rtP_ArmConstants.Hexa_to_joint_L * localB->D14_tmp_cx;
  localB->D24_tmp_h = (rtP_ArmConstants.l1_dim * localB->D15_tmp_g +
                       localB->D24_tmp_c) + rtP_ArmConstants.MC2 *
    localB->D15_tmp_m;
  localB->D24 = (((localB->D24_tmp * localB->smax * localB->D14_tmp_c +
                   -rtP_ArmConstants.MC1 * localB->s * localB->D14_tmp) *
                  (rtP_ArmConstants.Mass1 * localB->D14_tmp_k) +
                  rtP_ArmConstants.Mass2 * localB->s * localB->D24_tmp_h *
                  localB->D17_tmp_e) + (rtP_ArmConstants.MC1 * localB->smax *
    localB->D14_tmp * localB->D14_tmp_c + localB->D24_tmp * localB->s) *
                 (rtP_ArmConstants.Mass1 * localB->D14_tmp_cx)) +
    (localB->D24_tmp_i * localB->D17_tmp - localB->D24_tmp_o) *
    (rtP_ArmConstants.Mass2 * localB->D14_tmp_c);
  localB->D25 = -localB->D15_tmp_a * localB->D15_tmp * localB->smax;
  localB->D26 = ((localB->D24_tmp * -rtP_ArmConstants.Mass1 * localB->D17_tmp -
                  localB->D24_tmp_i * rtP_ArmConstants.Mass2 * localB->D17_tmp)
                 + localB->D14_tmp_tmp_c * localB->D14_tmp * localB->D17_tmp_p5)
    + localB->D17_tmp_l * localB->D17_tmp_p5;
  localB->D17_tmp_tmp_o = localB->D17_tmp_tmp_o * localB->D14_tmp_c +
    localB->D17_tmp_tmp_o2;
  localB->D14_tmp_tmp_c = localB->D14_tmp_cx * localB->smax * localB->D14_tmp_c;
  localB->D17_tmp_tmp_o2 = localB->D17_tmp_tmp - localB->D14_tmp_tmp_c;
  localB->D27_tmp = localB->D16_tmp_tmp * localB->D17_tmp_tmp_o;
  localB->D27_tmp_g = localB->D17_tmp_tmp_o * localB->D14_tmp_j;
  localB->D27 = (-localB->D14_tmp_h * localB->D17_tmp_tmp_o2 + localB->D27_tmp)
    + localB->D27_tmp_g;
  localB->D14_tmp_tmp_c += -localB->s * localB->D14_tmp_k;
  localB->D17_tmp_p = localB->D14_tmp_tmp_c * localB->D17_tmp_p +
    localB->D17_tmp_tmp_o * localB->D17_tmp_a;
  localB->D28 = localB->D17_tmp_p * rtP_ArmConstants.Mass2;
  localB->D17_tmp_a = sin(localB->D15_tmp_tmp);
  localB->D17_tmp_l = sin(localB->D15_tmp_tmp_i);
  localB->D34_tmp = localB->D14_tmp_m * localB->D17_tmp_a;
  localB->D34_tmp_f = localB->D14_tmp_n * localB->D17_tmp_l;
  localB->D34_tmp_j = (localB->D14_tmp_m3 * localB->D14_tmp_k + localB->D34_tmp)
    + localB->D34_tmp_f;
  localB->D34 = localB->D34_tmp_j * localB->D15_tmp;
  localB->D35 = localB->D15_tmp_a * localB->D14_tmp_c;
  localB->D37_tmp = localB->D34_tmp + localB->D34_tmp_f;
  localB->D37 = localB->D37_tmp * localB->D15_tmp;
  localB->D38 = localB->D14_tmp_n * localB->D15_tmp * localB->D17_tmp_l;
  localB->D45_tmp = rtP_ArmConstants.Inertia2[7] * localB->D15_tmp_m;
  localB->D45_tmp_e = rtP_ArmConstants.Inertia2[6] * localB->D17_tmp_l;
  localB->D45 = ((rtP_ArmConstants.Inertia1[7] * localB->D15_tmp_g +
                  localB->D45_tmp) + rtP_ArmConstants.Inertia1[6] *
                 localB->D17_tmp_a) + localB->D45_tmp_e;
  localB->D46_tmp_tmp_a = localDW->DiscreteTimeIntegrator_DSTATE[6] -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp = sin(localB->D46_tmp_tmp_a);
  localB->D46_tmp_tmp_fb = localDW->DiscreteTimeIntegrator_DSTATE[4] +
    localDW->DiscreteTimeIntegrator_DSTATE[6];
  localB->D46_tmp_n = sin(localB->D46_tmp_tmp_fb);
  localB->D46_tmp_tmp = localB->D15_tmp_tmp -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_p = cos(localB->D46_tmp_tmp);
  localB->D46_tmp_tmp_i = localB->D15_tmp_tmp_i -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_l = cos(localB->D46_tmp_tmp_i);
  localB->D46_tmp_tmp_f = localB->D15_tmp_tmp +
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_j = cos(localB->D46_tmp_tmp_f);
  localB->D46_tmp_tmp_g = localB->D15_tmp_tmp_i +
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_d = cos(localB->D46_tmp_tmp_g);
  localB->D46_tmp_g = sin(localB->D46_tmp_tmp);
  localB->D46_tmp_dy = sin(localB->D46_tmp_tmp_i);
  localB->D46_tmp_b = sin(localB->D46_tmp_tmp_f);
  localB->D46_tmp_ln = sin(localB->D46_tmp_tmp_g);
  localB->D46_tmp_tmp_k = localDW->DiscreteTimeIntegrator_DSTATE[7] -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_bn = sin(localB->D46_tmp_tmp_k);
  localB->D46_tmp_tmp_pc = localB->D14_tmp_tmp -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_da = sin(localB->D46_tmp_tmp_pc);
  localB->D46_tmp_tmp_b = localDW->DiscreteTimeIntegrator_DSTATE[4] +
    localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->D46_tmp_e = sin(localB->D46_tmp_tmp_b);
  localB->D46_tmp_tmp_c = localB->D14_tmp_tmp +
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_bj = sin(localB->D46_tmp_tmp_c);
  localB->D46_tmp_c = 2.0 * rtP_ArmConstants.MC2;
  localB->D46_tmp_tmp_h = rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Hexa_to_joint_L;
  localB->D46_tmp_o = localB->D46_tmp_tmp_h * -2.0;
  localB->D46_tmp_lm = -2.0 * rtP_ArmConstants.MC2;
  localB->D46_tmp_m = rtP_ArmConstants.MC1 * rtP_ArmConstants.MC1;
  localB->D46_tmp_mj = rtP_ArmConstants.MC2 * rtP_ArmConstants.MC2;
  localB->D46_tmp_cn = rtP_ArmConstants.l1_dim * rtP_ArmConstants.l1_dim;
  localB->D46_tmp_f = localB->D46_tmp_c * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->D46_tmp_tmp_n = 2.0 * rtP_ArmConstants.MC1;
  localB->D46_tmp_cs = localB->D46_tmp_tmp_n * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  localB->D46_tmp_tmp_p = 2.0 * rtP_ArmConstants.Hexa_to_joint_L;
  localB->D46_tmp_k = localB->D46_tmp_tmp_p * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->D46_tmp_p4 = localB->D46_tmp_c * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->D46_tmp_tmp_m = rtP_ArmConstants.Inertia2[6] * localB->D46_tmp_d;
  localB->D46_tmp_bb = ((-rtP_ArmConstants.Inertia1[6] * localB->D46_tmp_p -
    rtP_ArmConstants.Inertia2[6] * localB->D46_tmp_l) -
                        rtP_ArmConstants.Inertia1[6] * localB->D46_tmp_j) -
    localB->D46_tmp_tmp_m;
  localB->D46_tmp_a = rtP_ArmConstants.Inertia1[7] * localB->D46_tmp_g;
  localB->D46_tmp_g2 = localB->D46_tmp_f * localB->D46_tmp_bn;
  localB->D46_tmp_ex = rtP_ArmConstants.Inertia2[7] * localB->D46_tmp_dy;
  localB->D46_tmp_fi = -2.0 * rtP_ArmConstants.Inertia1[8] * localB->D14_tmp_c;
  localB->D46_tmp_h = -2.0 * rtP_ArmConstants.Inertia2[8] * localB->D14_tmp_c;
  localB->D46_tmp_tmp_m1 = localB->D46_tmp_m * -2.0;
  localB->D46_tmp_ei = localB->D46_tmp_tmp_m1 * rtP_ArmConstants.Mass1 *
    localB->D14_tmp_c;
  localB->D46_tmp_tmp_j = localB->D46_tmp_mj * -2.0;
  localB->D46_tmp_ch = localB->D46_tmp_tmp_j * rtP_ArmConstants.Mass2 *
    localB->D14_tmp_c;
  localB->D46_tmp_ax = localB->D46_tmp_cn * -2.0 * rtP_ArmConstants.Mass2 *
    localB->D14_tmp_c;
  localB->D46_tmp_dau = rtP_ArmConstants.Inertia1[7] * localB->D46_tmp_b;
  localB->D46_tmp_tmp_d = localB->D46_tmp_lm * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->D46_tmp_af = localB->D46_tmp_tmp_d * localB->D46_tmp_e;
  localB->D46_tmp_pb = rtP_ArmConstants.Inertia2[7] * localB->D46_tmp_ln;
  localB->D46_tmp_d3 = -2.0 * rtP_ArmConstants.MC1;
  localB->D46_tmp_kn = localB->D46_tmp_d3 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  localB->D46_tmp_mx = -2.0 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->D46_tmp_pr = localB->D46_tmp_lm * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->D46 = ((((((((((((((((((((localB->D46_tmp_cs * localB->D46_tmp +
    localB->D46_tmp_bb) + localB->D46_tmp_k * localB->D46_tmp) +
    localB->D46_tmp_a) + localB->D46_tmp_g2) + localB->D46_tmp_p4 *
    localB->D46_tmp_da) + localB->D46_tmp_ex) + localB->D46_tmp_fi) +
    localB->D46_tmp_h) + -2.0 * rtP_HexaConstants.Inertia[0] * localB->D14_tmp_c)
    + localB->D46_tmp_ei) + localB->D46_tmp_o * rtP_ArmConstants.Mass1 *
    localB->D14_tmp_c) + localB->D46_tmp_ch) + localB->D46_tmp_o *
                        rtP_ArmConstants.Mass2 * localB->D14_tmp_c) +
                       localB->D46_tmp_ax) + localB->D46_tmp_kn *
                      localB->D46_tmp_n) + localB->D46_tmp_mx *
                     localB->D46_tmp_n) + localB->D46_tmp_dau) +
                   localB->D46_tmp_af) + localB->D46_tmp_pr * localB->D46_tmp_bj)
                 + localB->D46_tmp_pb) * 0.5;
  localB->D47_tmp = localB->D46_tmp_mj * rtP_ArmConstants.Mass2;
  localB->D47_tmp_tmp = rtP_ArmConstants.MC2 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->D46_tmp_o = localB->D47_tmp_tmp * localB->D14_tmp_g;
  localB->D47_tmp_p = localB->D46_tmp_m * rtP_ArmConstants.Mass1;
  localB->D47_tmp_px = localB->D46_tmp_cn * rtP_ArmConstants.Mass2;
  localB->D47_tmp_pe = rtP_ArmConstants.Inertia1[8] + rtP_ArmConstants.Inertia2
    [8];
  localB->D47_tmp_f = localB->D46_tmp_f * localB->D14_tmp_b;
  localB->D47_tmp_o = ((localB->D47_tmp_p + localB->D47_tmp_pe) +
                       localB->D47_tmp) + localB->D47_tmp_px;
  localB->D47_tmp_g = localB->D14_tmp_m * rtP_ArmConstants.Hexa_to_joint_L;
  localB->D47_tmp_c = localB->D47_tmp_g * localB->D14_tmp_f + localB->D47_tmp_o;
  localB->D47 = (localB->D47_tmp_c + localB->D47_tmp_f) + localB->D46_tmp_o;
  localB->D48_tmp = rtP_ArmConstants.MC2 * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->D48_tmp_tmp = localB->D47_tmp + rtP_ArmConstants.Inertia2[8];
  localB->D48_tmp_o = localB->D48_tmp * localB->D14_tmp_b + localB->D48_tmp_tmp;
  localB->D48 = localB->D48_tmp_o + localB->D46_tmp_o;
  localB->D56_tmp_tmp = 2.0 * localDW->DiscreteTimeIntegrator_DSTATE[3];
  localB->D56_tmp_tmp_m4 = localB->D56_tmp_tmp -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp = sin(localB->D56_tmp_tmp_m4);
  localB->D56_tmp_tmp_e = localB->D56_tmp_tmp +
    localDW->DiscreteTimeIntegrator_DSTATE[6];
  localB->D56_tmp_tmp_m = localB->D56_tmp_tmp_e -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_l = sin(localB->D56_tmp_tmp_m);
  localB->D56_tmp_tmp_tmp = 2.0 * localDW->DiscreteTimeIntegrator_DSTATE[6];
  localB->D56_tmp_tmp_p = localB->D56_tmp_tmp + localB->D56_tmp_tmp_tmp;
  localB->D56_tmp_tmp_h = localB->D56_tmp_tmp_p -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_d = sin(localB->D56_tmp_tmp_h);
  localB->D56_tmp_tmp_o = 2.0 * localDW->DiscreteTimeIntegrator_DSTATE[7] +
    localB->D56_tmp_tmp_p;
  localB->D56_tmp_tmp_l = localB->D56_tmp_tmp_o -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_lx = sin(localB->D56_tmp_tmp_l);
  localB->D56_tmp_tmp_c = localB->D56_tmp_tmp +
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_o = sin(localB->D56_tmp_tmp_c);
  localB->D56_tmp_tmp_hc = localB->D56_tmp_tmp_e +
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_n = sin(localB->D56_tmp_tmp_hc);
  localB->D56_tmp_tmp_h2 = localB->D56_tmp_tmp_p +
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_b = sin(localB->D56_tmp_tmp_h2);
  localB->D56_tmp_tmp_o += localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_h = sin(localB->D56_tmp_tmp_o);
  localB->D56_tmp_j = cos(localB->D56_tmp_tmp_h);
  localB->D56_tmp_f = cos(localB->D56_tmp_tmp_l);
  localB->D56_tmp_a = cos(localB->D56_tmp_tmp_h2);
  localB->D56_tmp_ju = cos(localB->D56_tmp_tmp_o);
  localB->D56_tmp_tmp_h = localB->D56_tmp_tmp_e +
    localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->D56_tmp_tmp_o = localB->D56_tmp_tmp_h -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_o4 = sin(localB->D56_tmp_tmp_o);
  localB->D56_tmp_tmp_p += localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->D56_tmp_tmp_l = localB->D56_tmp_tmp_p -
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_ny = sin(localB->D56_tmp_tmp_l);
  localB->D56_tmp_tmp_h2 = localB->D56_tmp_tmp_h +
    localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_i = sin(localB->D56_tmp_tmp_h2);
  localB->D56_tmp_tmp_p += localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_oy = sin(localB->D56_tmp_tmp_p);
  localB->D56_tmp_m = -2.0 * rtP_ArmConstants.Inertia1[3];
  localB->D56_tmp_mc = -2.0 * rtP_ArmConstants.Inertia2[3];
  localB->D56_tmp_ap = localB->D46_tmp_tmp_h * rtP_ArmConstants.Mass1;
  localB->D56_tmp_jd = localB->D46_tmp_tmp_h * rtP_ArmConstants.Mass2;
  localB->D56_tmp_p = 2.0 * rtP_ArmConstants.Inertia1[7];
  localB->D56_tmp_nj = 2.0 * rtP_ArmConstants.Inertia2[7];
  localB->D56_tmp_k = -2.0 * rtP_ArmConstants.Inertia1[7];
  localB->D56_tmp_n3 = -2.0 * rtP_ArmConstants.Inertia2[7];
  localB->D56_tmp_oyh = 2.0 * rtP_ArmConstants.Inertia1[6];
  localB->D56_tmp_g = 2.0 * rtP_ArmConstants.Inertia2[6];
  localB->D56_tmp_c = -2.0 * rtP_ArmConstants.Inertia1[6];
  localB->D56_tmp_cj = -2.0 * rtP_ArmConstants.Inertia2[6];
  localB->D56_tmp_tmp_k = rtP_HexaConstants.Inertia[4] * localB->D56_tmp;
  localB->D56_tmp_tmp_j = rtP_HexaConstants.Inertia[8] * localB->D56_tmp;
  localB->D56_tmp_tmp_f = localB->D56_tmp_ap * localB->D56_tmp;
  localB->D56_tmp_tmp_cm = localB->D56_tmp_jd * localB->D56_tmp;
  localB->D56_tmp_tmp_fq = rtP_ArmConstants.Inertia1[0] * localB->D56_tmp_d;
  localB->D56_tmp_tmp_n = rtP_ArmConstants.Inertia1[4] * localB->D56_tmp_d;
  localB->D56_tmp_tmp_i = localB->D47_tmp_p * localB->D56_tmp_d;
  localB->D56_tmp_tmp_l4 = localB->D47_tmp_px * localB->D56_tmp_d;
  localB->D56_tmp_tmp_i3 = rtP_ArmConstants.Inertia2[0] * localB->D56_tmp_lx;
  localB->D56_tmp_tmp_k1 = rtP_ArmConstants.Inertia2[4] * localB->D56_tmp_lx;
  localB->D56_tmp_tmp_fc = localB->D47_tmp * localB->D56_tmp_lx;
  localB->D56_tmp_tmp_a = rtP_HexaConstants.Inertia[4] * localB->D56_tmp_o;
  localB->D56_tmp_tmp_d = rtP_HexaConstants.Inertia[8] * localB->D56_tmp_o;
  localB->D56_tmp_tmp_ey = localB->D56_tmp_ap * localB->D56_tmp_o;
  localB->D56_tmp_tmp_eh = rtP_ArmConstants.Inertia1[0] * localB->D56_tmp_b;
  localB->D56_tmp_tmp_b = rtP_ArmConstants.Inertia1[4] * localB->D56_tmp_b;
  localB->D56_tmp_tmp_a0 = localB->D47_tmp_p * localB->D56_tmp_b;
  localB->D56_tmp_tmp_il = localB->D47_tmp_px * localB->D56_tmp_b;
  localB->D56_tmp = (((((((((((((((((((((((((((((((((((((localB->D56_tmp_c *
    localB->D46_tmp_p + localB->D56_tmp_m * localB->D56_tmp_j) +
    localB->D56_tmp_cj * localB->D46_tmp_l) + localB->D56_tmp_mc *
    localB->D56_tmp_f) + localB->D56_tmp_oyh * localB->D46_tmp_j) +
    localB->D56_tmp_m * localB->D56_tmp_a) + localB->D56_tmp_g *
    localB->D46_tmp_d) + localB->D56_tmp_mc * localB->D56_tmp_ju) +
    localB->D56_tmp_tmp_k) - localB->D56_tmp_tmp_j) + localB->D56_tmp_tmp_f) +
    localB->D56_tmp_tmp_cm) + localB->D56_tmp_p * localB->D46_tmp_g) +
    localB->D46_tmp_cs * localB->D56_tmp_l) + localB->D46_tmp_k *
    localB->D56_tmp_l) - localB->D56_tmp_tmp_fq) + localB->D56_tmp_tmp_n) +
    localB->D56_tmp_tmp_i) + localB->D56_tmp_tmp_l4) + localB->D56_tmp_nj *
    localB->D46_tmp_dy) + localB->D46_tmp_p4 * localB->D56_tmp_o4) +
    localB->D46_tmp_f * localB->D56_tmp_ny) - localB->D56_tmp_tmp_i3) +
    localB->D56_tmp_tmp_k1) + localB->D56_tmp_tmp_fc) + localB->D56_tmp_tmp_a) -
    localB->D56_tmp_tmp_d) + localB->D56_tmp_tmp_ey) + localB->D56_tmp_jd *
    localB->D56_tmp_o) + localB->D56_tmp_k * localB->D46_tmp_b) +
    localB->D46_tmp_cs * localB->D56_tmp_n) + localB->D46_tmp_k *
    localB->D56_tmp_n) - localB->D56_tmp_tmp_eh) + localB->D56_tmp_tmp_b) +
                        localB->D56_tmp_tmp_a0) + localB->D56_tmp_tmp_il) +
                      localB->D56_tmp_n3 * localB->D46_tmp_ln) +
                     localB->D46_tmp_p4 * localB->D56_tmp_i) + localB->D46_tmp_f
    * localB->D56_tmp_oy;
  localB->D56_tmp_c3 = rtP_ArmConstants.Inertia2[4] * localB->D56_tmp_h;
  localB->D56_tmp_cx = localB->D47_tmp * localB->D56_tmp_h;
  localB->D56 = (((-rtP_ArmConstants.Inertia2[0] * localB->D56_tmp_h +
                   localB->D56_tmp) + localB->D56_tmp_c3) + localB->D56_tmp_cx) *
    0.25;
  localB->D58 = localB->D45_tmp + localB->D45_tmp_e;
  localB->D45_tmp_e = rtP_ArmConstants.MC1 * localB->D14_tmp;
  localB->D45_tmp = localB->D17_tmp * -localB->D24_tmp + localB->D17_tmp_p5 *
    localB->D45_tmp_e;
  localB->D24_tmp_o += -localB->D24_tmp_i * localB->D17_tmp;
  localB->y_a = localB->D17_tmp_tmp_o2 * localB->D24_tmp + localB->D17_tmp_tmp_o
    * localB->D45_tmp_e;
  localB->ab_a = localB->D24_tmp_i * localB->D17_tmp_tmp_o2 +
    localB->D17_tmp_tmp_o * localB->D17_tmp_ax;
  localB->D24_tmp = rtP_ArmConstants.MC1 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  localB->D24_tmp_i = rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim
    * rtP_ArmConstants.Mass2;
  localB->D46_tmp_da *= localB->D47_tmp_tmp;
  localB->D46_tmp_bj *= localB->D47_tmp_tmp;
  localB->D67 = (((((((((((((((((localB->D24_tmp * localB->D46_tmp +
    localB->D46_tmp_bb) + localB->D24_tmp_i * localB->D46_tmp) +
    localB->D46_tmp_a) + localB->D46_tmp_g2) + localB->D46_tmp_da) +
    localB->D46_tmp_ex) + localB->D46_tmp_fi) + localB->D46_tmp_h) +
    localB->D46_tmp_ei) + localB->D46_tmp_ch) + localB->D46_tmp_ax) -
                      localB->D24_tmp * localB->D46_tmp_n) - localB->D24_tmp_i *
                     localB->D46_tmp_n) + localB->D46_tmp_dau) +
                   localB->D46_tmp_af) - localB->D46_tmp_bj) +
                 localB->D46_tmp_pb) * 0.5;
  localB->D46_tmp = -rtP_ArmConstants.MC2 * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->D68 = (((((((((-rtP_ArmConstants.Inertia2[6] * localB->D46_tmp_l -
    localB->D46_tmp_tmp_m) + localB->D48_tmp * localB->D46_tmp_bn) +
                       localB->D46_tmp_da) + localB->D46_tmp_ex) +
                     localB->D46_tmp_h) + localB->D46_tmp_ch) + localB->D46_tmp *
                   localB->D46_tmp_e) - localB->D46_tmp_bj) + localB->D46_tmp_pb)
    * 0.5;
  localB->rtb_ginv_tmp = cos(localB->D56_tmp_tmp);
  localB->rtb_ginv_tmp_tmp_n = localB->D15_tmp_tmp * 2.0;
  localB->D46_tmp_bn = cos(localB->rtb_ginv_tmp_tmp_n);
  localB->D46_tmp_e = cos(localB->D56_tmp_tmp_e);
  localB->rtb_ginv_tmp_tmp_l = localB->D15_tmp_tmp_i * 2.0;
  localB->D46_tmp_tmp_m = cos(localB->rtb_ginv_tmp_tmp_l);
  localB->D46_tmp_ex = sin(localB->D56_tmp_tmp_tmp);
  localB->rtb_ginv_tmp_tmp = localB->D14_tmp_tmp * 2.0;
  localB->D46_tmp_h = cos(localB->rtb_ginv_tmp_tmp);
  localB->D46_tmp_ch = sin(localB->rtb_ginv_tmp_tmp);
  localB->rtb_ginv_tmp_tmp = 2.0 * localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D46_tmp_pb = sin(localB->rtb_ginv_tmp_tmp);
  localB->D46_tmp_n = sin(localB->rtb_ginv_tmp_tmp_n);
  localB->D46_tmp_bb = sin(localB->rtb_ginv_tmp_tmp_l);
  localB->rtb_ginv_tmp_j = cos(localB->D56_tmp_tmp_h);
  localB->rtb_ginv_tmp_tmp_n += localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->D46_tmp_a = cos(localB->rtb_ginv_tmp_tmp_n);
  localB->D56_tmp_tmp_tmp = cos(localB->D56_tmp_tmp_tmp);
  localB->D46_tmp_g2 = (rtP_HexaConstants.Mass + rtP_ArmConstants.Mass1) +
    rtP_ArmConstants.Mass2;
  localB->ginv[0] = localB->D46_tmp_g2;
  localB->ginv[8] = 0.0;
  localB->ginv[16] = 0.0;
  localB->ginv[24] = localB->D14;
  localB->ginv[32] = localB->D15;
  localB->ginv[40] = localB->D16;
  localB->ginv[48] = localB->D17;
  localB->ginv[56] = localB->D18;
  localB->ginv[1] = 0.0;
  localB->ginv[9] = localB->D46_tmp_g2;
  localB->ginv[17] = 0.0;
  localB->ginv[25] = localB->D24;
  localB->ginv[33] = localB->D25;
  localB->ginv[41] = localB->D26;
  localB->ginv[49] = localB->D27;
  localB->ginv[57] = localB->D28;
  localB->ginv[2] = 0.0;
  localB->ginv[10] = 0.0;
  localB->ginv[18] = localB->D46_tmp_g2;
  localB->ginv[26] = localB->D34;
  localB->ginv[34] = localB->D35;
  localB->ginv[42] = 0.0;
  localB->ginv[50] = localB->D37;
  localB->ginv[58] = localB->D38;
  localB->ginv[3] = localB->D14;
  localB->ginv[11] = localB->D24;
  localB->ginv[19] = localB->D34;
  localB->rtb_ginv_tmp_tmp_l = localB->D14_tmp_m * localB->D46_tmp_tmp_p;
  localB->rtb_ginv_tmp_i = localB->rtb_ginv_tmp_tmp_l * localB->D14_tmp_f;
  localB->rtb_ginv_tmp_o = localB->D46_tmp_p4 * localB->D14_tmp_g;
  localB->rtb_ginv_tmp_if = (((((localB->D47_tmp_pe + rtP_HexaConstants.Inertia
    [0]) + localB->D47_tmp_p) + localB->D56_tmp_ap) + localB->D47_tmp) +
    localB->D56_tmp_jd) + localB->D47_tmp_px;
  localB->ginv[27] = ((localB->rtb_ginv_tmp_if + localB->rtb_ginv_tmp_i) +
                      localB->D47_tmp_f) + localB->rtb_ginv_tmp_o;
  localB->ginv[35] = localB->D45;
  localB->ginv[43] = localB->D46;
  localB->ginv[51] = localB->D47;
  localB->ginv[59] = localB->D48;
  localB->ginv[4] = localB->D15;
  localB->ginv[12] = localB->D25;
  localB->ginv[20] = localB->D35;
  localB->ginv[28] = localB->D45;
  localB->D15 = 2.0 * rtP_ArmConstants.Inertia2[3];
  localB->D25 = 2.0 * rtP_ArmConstants.Inertia1[3];
  localB->rtb_ginv_tmp_d = rtP_ArmConstants.Inertia1[4] * localB->D46_tmp_bn;
  localB->rtb_ginv_tmp_g = localB->D47_tmp_p * localB->D46_tmp_bn;
  localB->rtb_ginv_tmp_l = localB->D47_tmp_px * localB->D46_tmp_bn;
  localB->D14 = rtP_ArmConstants.Inertia2[0] * localB->D46_tmp_tmp_m;
  localB->D24 = rtP_ArmConstants.Inertia2[4] * localB->D46_tmp_tmp_m;
  localB->D35 = localB->D47_tmp * localB->D46_tmp_tmp_m;
  localB->ginv[36] = ((((((((((((((((((((((((((((((rtP_ArmConstants.Inertia1[0]
    + rtP_ArmConstants.Inertia1[4]) + rtP_ArmConstants.Inertia2[0]) +
    rtP_ArmConstants.Inertia2[4]) + rtP_HexaConstants.Inertia[4]) +
    rtP_HexaConstants.Inertia[8]) + localB->D47_tmp_p) + localB->D56_tmp_ap) +
    localB->D47_tmp) + localB->D56_tmp_jd) + localB->D47_tmp_px) +
    rtP_HexaConstants.Inertia[4] * localB->rtb_ginv_tmp) -
    rtP_HexaConstants.Inertia[8] * localB->rtb_ginv_tmp) + localB->D56_tmp_ap *
    localB->rtb_ginv_tmp) + localB->D56_tmp_jd * localB->rtb_ginv_tmp) +
    localB->rtb_ginv_tmp_i) + -rtP_ArmConstants.Inertia1[0] * localB->D46_tmp_bn)
    + localB->rtb_ginv_tmp_d) + localB->rtb_ginv_tmp_g) + localB->rtb_ginv_tmp_l)
    + localB->D46_tmp_cs * localB->D46_tmp_e) + localB->D46_tmp_k *
    localB->D46_tmp_e) + localB->D47_tmp_f) + localB->rtb_ginv_tmp_o) -
    localB->D14) + localB->D24) + localB->D35) + localB->D46_tmp_p4 *
    localB->rtb_ginv_tmp_j) + localB->D46_tmp_f * localB->D46_tmp_a) +
                       localB->D25 * localB->D46_tmp_n) + localB->D15 *
                      localB->D46_tmp_bb) * 0.5;
  localB->ginv[44] = localB->D56;
  localB->ginv[52] = localB->D45;
  localB->ginv[60] = localB->D58;
  localB->ginv[5] = localB->D16;
  localB->ginv[13] = localB->D26;
  localB->ginv[21] = 0.0;
  localB->ginv[29] = localB->D46;
  localB->ginv[37] = localB->D56;
  localB->D16 = localB->D14_tmp_cx * localB->D14_tmp_cx;
  localB->D26 = localB->D14_tmp_f * localB->D14_tmp_f;
  localB->D46 = localB->D14_tmp * localB->D14_tmp;
  localB->D56 = localB->D14_tmp_k * localB->D14_tmp_k;
  localB->D47_tmp_pe = rtP_ArmConstants.Inertia2[0] + rtP_ArmConstants.Inertia2
    [4];
  localB->D34 = -rtP_ArmConstants.Inertia2[0] + rtP_ArmConstants.Inertia2[4];
  localB->D46_tmp_fi = 2.0 * localB->D14_tmp_cx;
  localB->rtb_ginv_tmp_k = localB->D46_tmp_fi * localB->D17_tmp_e *
    localB->D14_tmp_k;
  localB->rtb_ginv_tmp_ie = localB->D14_tmp_c * localB->D14_tmp_c;
  localB->D46_tmp_ei = rtP_ArmConstants.Inertia1[6] * localB->D14_tmp_f -
    rtP_ArmConstants.Inertia1[7] * localB->D14_tmp;
  localB->D46_tmp_ax = rtP_ArmConstants.Inertia1[7] * localB->D14_tmp_f +
    rtP_ArmConstants.Inertia1[6] * localB->D14_tmp;
  localB->D46_tmp_dau = rtP_ArmConstants.Inertia2[6] * localB->D14_tmp_g -
    rtP_ArmConstants.Inertia2[7] * localB->D14_tmp_cv;
  localB->D46_tmp_af = rtP_ArmConstants.Inertia2[7] * localB->D14_tmp_g +
    rtP_ArmConstants.Inertia2[6] * localB->D14_tmp_cv;
  localB->D46_tmp_bj = localB->D26 * rtP_ArmConstants.Inertia1[0];
  localB->D46_tmp_da = localB->D46 * rtP_ArmConstants.Inertia1[4];
  localB->D26 = (localB->D26 * rtP_ArmConstants.Inertia1[4] + localB->D46 *
                 rtP_ArmConstants.Inertia1[0]) + rtP_ArmConstants.Inertia1[3] *
    localB->D46_tmp_ex;
  localB->D45_tmp_e = rtP_ArmConstants.Inertia2[0] - rtP_ArmConstants.Inertia2[4];
  localB->D46 = (localB->D45_tmp_e * localB->D46_tmp_h + localB->D47_tmp_pe) +
    localB->D56_tmp_mc * localB->D46_tmp_ch;
  localB->rtb_ginv_tmp_tmp_p = localB->D34 * localB->D46_tmp_h;
  localB->rtb_ginv_tmp_tmp_pi = localB->D15 * localB->D46_tmp_ch;
  localB->D47_tmp_pe = (localB->rtb_ginv_tmp_tmp_p + localB->D47_tmp_pe) +
    localB->rtb_ginv_tmp_tmp_pi;
  localB->rtb_ginv_tmp_da = localB->D16 * rtP_HexaConstants.Inertia[8];
  localB->rtb_ginv_tmp_c = localB->D17_tmp_e * localB->D56;
  localB->rtb_ginv_tmp_a = localB->D16 * localB->D17_tmp_e;
  localB->ginv[45] = ((((((((((((((((((-rtP_ArmConstants.Inertia1[0] +
    rtP_ArmConstants.Inertia1[4]) * localB->D14_tmp_f * localB->D14_tmp +
    -rtP_ArmConstants.Inertia1[3] * localB->D56_tmp_tmp_tmp) *
    localB->rtb_ginv_tmp_k + (localB->D17_tmp_e * rtP_HexaConstants.Inertia[4] *
    localB->D56 + localB->rtb_ginv_tmp_da * localB->D17_tmp_e)) +
    ((localB->D46_tmp_bj + localB->D46_tmp_da) + -rtP_ArmConstants.Inertia1[3] *
     localB->D46_tmp_ex) * localB->rtb_ginv_tmp_a) + localB->D26 *
    localB->rtb_ginv_tmp_c) + localB->D16 * 0.5 * localB->D17_tmp_e *
    localB->D46) + localB->D17_tmp_e * 0.5 * localB->D56 * localB->D47_tmp_pe) +
    (localB->D34 * 0.5 * localB->D46_tmp_ch + -rtP_ArmConstants.Inertia2[3] *
     localB->D46_tmp_h) * localB->rtb_ginv_tmp_k) + localB->rtb_ginv_tmp_ie *
    rtP_ArmConstants.Inertia1[8]) + localB->rtb_ginv_tmp_ie *
    rtP_ArmConstants.Inertia2[8]) + localB->rtb_ginv_tmp_ie *
    rtP_HexaConstants.Inertia[0]) + localB->D45_tmp * localB->D45_tmp *
    rtP_ArmConstants.Mass1) + localB->D24_tmp_o * localB->D24_tmp_o *
    rtP_ArmConstants.Mass2) + localB->y_a * localB->y_a * rtP_ArmConstants.Mass1)
    + localB->ab_a * localB->ab_a * rtP_ArmConstants.Mass2) + localB->D46_tmp_ei
                        * localB->D14_tmp_cx * localB->D46_tmp_pb) -
                       localB->D46_tmp_ax * localB->D14_tmp_k *
                       localB->D46_tmp_pb) + localB->D46_tmp_dau *
                      localB->D14_tmp_cx * localB->D46_tmp_pb) -
    localB->D46_tmp_af * localB->D14_tmp_k * localB->D46_tmp_pb;
  localB->ginv[53] = localB->D67;
  localB->ginv[61] = localB->D68;
  localB->ginv[6] = localB->D17;
  localB->ginv[14] = localB->D27;
  localB->ginv[22] = localB->D37;
  localB->ginv[30] = localB->D47;
  localB->ginv[38] = localB->D45;
  localB->ginv[46] = localB->D67;
  localB->ginv[54] = localB->D47_tmp_o + localB->D47_tmp_f;
  localB->ginv[62] = localB->D48_tmp_o;
  localB->ginv[7] = localB->D18;
  localB->ginv[15] = localB->D28;
  localB->ginv[23] = localB->D38;
  localB->ginv[31] = localB->D48;
  localB->ginv[39] = localB->D58;
  localB->ginv[47] = localB->D68;
  localB->ginv[55] = localB->D48_tmp_o;
  localB->ginv[63] = localB->D48_tmp_tmp;
  localB->D17 = sin(localB->D56_tmp_tmp);
  localB->D18 = sin(localB->D56_tmp_tmp_e);
  localB->D27 = cos(localB->D56_tmp_tmp_m);
  localB->D56_tmp_tmp_c = cos(localB->D56_tmp_tmp_c);
  localB->D46_tmp_tmp_fb = cos(localB->D46_tmp_tmp_fb);
  localB->D56_tmp_tmp_hc = cos(localB->D56_tmp_tmp_hc);
  localB->D56_tmp_tmp_m4 = cos(localB->D56_tmp_tmp_m4);
  localB->D46_tmp_tmp_a = cos(localB->D46_tmp_tmp_a);
  localB->D46_tmp_tmp_k = cos(localB->D46_tmp_tmp_k);
  localB->D46_tmp_tmp_pc = cos(localB->D46_tmp_tmp_pc);
  localB->D56_tmp_tmp_o = cos(localB->D56_tmp_tmp_o);
  localB->D56_tmp_tmp_l = cos(localB->D56_tmp_tmp_l);
  localB->D46_tmp_tmp_b = cos(localB->D46_tmp_tmp_b);
  localB->D46_tmp_tmp_c = cos(localB->D46_tmp_tmp_c);
  localB->D56_tmp_tmp_h2 = cos(localB->D56_tmp_tmp_h2);
  localB->D56_tmp_tmp_p = cos(localB->D56_tmp_tmp_p);
  localB->D56_tmp_tmp_m = sin(localB->D56_tmp_tmp_h);
  localB->D28 = sin(localB->rtb_ginv_tmp_tmp_n);
  localB->D37 = -2.0 * localDW->DiscreteTimeIntegrator_DSTATE[4];
  localB->D56_tmp_tmp_e = sin(localB->D56_tmp_tmp_e + localB->D37);
  localB->D46_tmp_tmp *= 2.0;
  localB->D38 = sin(localB->D46_tmp_tmp);
  localB->D46_tmp_tmp_i *= 2.0;
  localB->D47_tmp_o = sin(localB->D46_tmp_tmp_i);
  localB->D47 = sin((-localDW->DiscreteTimeIntegrator_DSTATE[3] +
                     localDW->DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  localB->D48_tmp_tmp = (localDW->DiscreteTimeIntegrator_DSTATE[3] +
    localDW->DiscreteTimeIntegrator_DSTATE[4]) * 2.0;
  localB->D48_tmp_o = sin(localB->D48_tmp_tmp);
  localB->D46_tmp_tmp_f *= 2.0;
  localB->D56_tmp_tmp = sin(localB->D46_tmp_tmp_f);
  localB->D46_tmp_tmp_g *= 2.0;
  localB->D58 = sin(localB->D46_tmp_tmp_g);
  localB->y_a = sin(localB->D48_tmp_tmp + localDW->
                    DiscreteTimeIntegrator_DSTATE[6]);
  localB->ab_a = localB->D15_tmp_tmp + localB->D37;
  localB->rtb_ginv_tmp_tmp_n = cos(localB->ab_a);
  localB->D67 = localB->D15_tmp_tmp_i + localB->D37;
  localB->D68 = cos(localB->D67);
  localB->rtb_ginv_tmp_k = cos(localB->D46_tmp_tmp);
  localB->D46_tmp_tmp_i = cos(localB->D46_tmp_tmp_i);
  localB->d = cos(localB->D46_tmp_tmp_f);
  localB->D46_tmp_tmp_g = cos(localB->D46_tmp_tmp_g);
  localB->D15_tmp_tmp += localB->rtb_ginv_tmp_tmp;
  localB->d1 = cos(localB->D15_tmp_tmp);
  localB->D15_tmp_tmp_i += localB->rtb_ginv_tmp_tmp;
  localB->d2 = cos(localB->D15_tmp_tmp_i);
  localB->D46_tmp_tmp = sin(localB->D46_tmp_tmp +
    localDW->DiscreteTimeIntegrator_DSTATE[7]);
  localB->d3 = sin(localB->D37 + localDW->DiscreteTimeIntegrator_DSTATE[6]);
  localB->ab_a = sin(localB->ab_a);
  localB->D67 = sin(localB->D67);
  localB->D56_tmp_tmp_h = sin(localB->D56_tmp_tmp_h + localB->D37);
  localB->d4 = sin((localDW->DiscreteTimeIntegrator_DSTATE[3] -
                    localDW->DiscreteTimeIntegrator_DSTATE[4]) * 2.0);
  localB->d5 = sin(localB->rtb_ginv_tmp_tmp +
                   localDW->DiscreteTimeIntegrator_DSTATE[6]);
  localB->D15_tmp_tmp = sin(localB->D15_tmp_tmp);
  localB->D15_tmp_tmp_i = sin(localB->D15_tmp_tmp_i);
  localB->D48_tmp_tmp = sin(localB->D48_tmp_tmp + localB->D14_tmp_tmp);
  localB->D46_tmp_tmp_f = sin(localB->D46_tmp_tmp_f +
    localDW->DiscreteTimeIntegrator_DSTATE[7]);
  localB->d6 = sin(localB->D37 + localDW->DiscreteTimeIntegrator_DSTATE[7]);
  localB->D37 = sin(localB->D14_tmp_tmp + localB->D37);
  localB->d7 = sin(localB->rtb_ginv_tmp_tmp +
                   localDW->DiscreteTimeIntegrator_DSTATE[7]);
  localB->D14_tmp_tmp = sin(localB->D14_tmp_tmp + localB->rtb_ginv_tmp_tmp);
  localB->rtb_ginv_tmp_tmp = cos(localB->rtb_ginv_tmp_tmp);
  localB->D14_tmp_nb = localB->D14_tmp_nb * localB->D14_tmp_c +
    localB->D14_tmp_i * localB->D14_tmp_p;
  localB->D14_tmp_i = localB->D14_tmp_h * localB->s;
  localB->d8 = 2.0 * localB->D14_tmp_k;
  localB->d9 = rtP_ArmConstants.MC2 * localDW->DiscreteTimeIntegrator1_DSTATE[7]
    * rtP_ArmConstants.Mass2;
  localB->D16_tmp_m = localB->D16_tmp_m * localB->D14_tmp_c + localB->D14_tmp_c0;
  localB->d10 = localB->D16_tmp_m * localB->D46_tmp_fi;
  localB->d11 = localB->D14_tmp_i * localB->D14_tmp_c;
  localB->d12 = 2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->d13 = -2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[6];
  localB->d167 = -2.0 * localB->D14_tmp_cx;
  localB->D14_tmp_i = (localB->D14_tmp_i - localB->D16_tmp_j) * localB->d8 +
    localB->D16_tmp_f * localB->d167;
  localB->D16_tmp_j = ((localDW->DiscreteTimeIntegrator_DSTATE[3] -
                        localDW->DiscreteTimeIntegrator_DSTATE[5]) +
                       localDW->DiscreteTimeIntegrator_DSTATE[6]) +
    localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->D16_tmp_f = ((localDW->DiscreteTimeIntegrator_DSTATE[3] +
                        localDW->DiscreteTimeIntegrator_DSTATE[5]) +
                       localDW->DiscreteTimeIntegrator_DSTATE[6]) +
    localDW->DiscreteTimeIntegrator_DSTATE[7];
  localB->tmp_tmp = 2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[6];
  localB->d20 = 2.0 * localB->s;
  localB->x[24] = -(((((((localB->D14_tmp_md * localB->smax - localB->D14_tmp_my)
    * localB->D14_tmp_k + localB->D14_tmp_nb * localB->D14_tmp_cx) *
                        (localB->tmp_tmp * localB->D14_tmp_f) + ((localB->d20 *
    localB->D15_tmp_m * localB->D14_tmp_c + (cos(localB->D16_tmp_j) - cos
    (localB->D16_tmp_f))) * localB->d9 + localB->d12 * localB->s *
    localB->D15_tmp * localB->D34_tmp_j)) + (localB->D14_tmp_nb *
    localB->D14_tmp_k + localB->D14_tmp_e) * (localB->d13 * localB->D14_tmp)) +
                      ((localB->D16_tmp_m0 - localB->d11) * localB->d8 +
                       localB->d10) * localDW->DiscreteTimeIntegrator1_DSTATE[3])
                     + localB->D14_tmp_i *
                     localDW->DiscreteTimeIntegrator1_DSTATE[5]) * 0.5);
  localB->x[32] = -((((localB->D15_tmp_a *
                       localDW->DiscreteTimeIntegrator1_DSTATE[5] *
                       localB->D15_tmp * localB->smax + localB->d9 * localB->s *
                       localB->D15_tmp * localB->D17_tmp_l) +
                      localDW->DiscreteTimeIntegrator1_DSTATE[6] * localB->s *
                      localB->D15_tmp * localB->D37_tmp) +
                     localDW->DiscreteTimeIntegrator1_DSTATE[3] * localB->s *
                     localB->D15_tmp * localB->D34_tmp_j) +
                    localDW->DiscreteTimeIntegrator1_DSTATE[4] * localB->s *
                    localB->D15_tmp_a * localB->D14_tmp_c);
  localB->D14_tmp_nb = localB->D46_tmp_lm *
    localDW->DiscreteTimeIntegrator1_DSTATE[7] * rtP_ArmConstants.Mass2;
  localB->D14_tmp_md = -localB->D16_tmp * localB->smax + localB->d11;
  localB->D14_tmp_my = -2.0 * localB->D14_tmp_k;
  localB->x[40] = -(((((((localB->D17_tmp_tmp_a * localB->D14_tmp_c +
    localB->D17_tmp_tmp) * -localB->D14_tmp_h + localB->D27_tmp) +
                        localB->D27_tmp_g) * localB->d13 + (localB->D15_tmp_a *
    localB->d12 * localB->D15_tmp * localB->smax + (localB->D14_tmp_tmp_c *
    localB->D14_tmp_cv + localB->D17_tmp_tmp_o * localB->D14_tmp_g) *
    localB->D14_tmp_nb)) + (localB->D14_tmp_md * localB->D14_tmp_my +
    localB->d10) * localDW->DiscreteTimeIntegrator1_DSTATE[5]) +
                     localB->D14_tmp_i * localDW->
                     DiscreteTimeIntegrator1_DSTATE[3]) * 0.5);
  localB->D14_tmp_i = rtP_ArmConstants.MC2 *
    localDW->DiscreteTimeIntegrator1_DSTATE[4] * rtP_ArmConstants.Mass2;
  localB->d10 = localDW->DiscreteTimeIntegrator1_DSTATE[3] +
    localDW->DiscreteTimeIntegrator1_DSTATE[6];
  localB->D17_tmp_tmp = localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    localB->D14_tmp_c;
  localB->D17_tmp_tmp_a = rtP_ArmConstants.MC1 *
    localDW->DiscreteTimeIntegrator1_DSTATE[4] * rtP_ArmConstants.Mass1 *
    localB->D15_tmp;
  localB->D14_tmp_e = localDW->DiscreteTimeIntegrator1_DSTATE[4] *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D15_tmp;
  localB->D16_tmp = localB->D14_tmp_i * localB->D15_tmp;
  localB->D16_tmp_m0 = 2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->D27_tmp = rtP_ArmConstants.MC2 *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] * rtP_ArmConstants.Mass2;
  localB->D27_tmp_g = localDW->DiscreteTimeIntegrator1_DSTATE[6] +
    localDW->DiscreteTimeIntegrator1_DSTATE[7];
  localB->d14 = localB->D27_tmp_g * 2.0 +
    localDW->DiscreteTimeIntegrator1_DSTATE[3];
  localB->d15 = -2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->d16 = localB->d10 - localB->D17_tmp_tmp;
  localB->D14_tmp_b *= localB->D27_tmp;
  localB->d17 = localB->d10 + localDW->DiscreteTimeIntegrator1_DSTATE[7];
  localB->d18 = localB->d17 - localB->D17_tmp_tmp;
  localB->d19 = localB->D14_tmp_m * localB->d15;
  localB->d21 = localB->D14_tmp_m * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->d22 = localB->d15 * localB->D14_tmp_c + localB->d14;
  localB->d46 = localB->D46_tmp_tmp_n * localDW->DiscreteTimeIntegrator1_DSTATE
    [5];
  localB->d49 = localB->D46_tmp_c * localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->tmp_tmp_ik = -2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[3];
  localB->x[48] = -(((((((((((((((((localB->d21 * localB->D14_tmp_f *
    localB->D15_tmp * localB->D14_tmp_k + localB->D14_tmp_i * localB->D14_tmp_g *
    localB->D15_tmp * localB->D14_tmp_k) + localB->d46 * rtP_ArmConstants.Mass1 *
    localB->D14_tmp_k * localB->D14_tmp) + localB->D16_tmp_m0 *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D14_tmp_k *
    localB->D14_tmp) + localB->D17_tmp_tmp_a * localB->D17_tmp_a) +
    localB->D14_tmp_e * localB->D17_tmp_a) + localB->d49 *
    rtP_ArmConstants.Mass2 * localB->D14_tmp_k * localB->D14_tmp_cv) +
    localB->D16_tmp * localB->D17_tmp_l) + localB->D46_tmp_d3 *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] * rtP_ArmConstants.Mass1 *
    localB->D14_tmp_k * localB->D14_tmp * localB->D14_tmp_c) +
    localB->D46_tmp_d3 * localDW->DiscreteTimeIntegrator1_DSTATE[6] *
    rtP_ArmConstants.Mass1 * localB->D14_tmp_k * localB->D14_tmp *
    localB->D14_tmp_c) + localB->tmp_tmp_ik * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * localB->D14_tmp_k * localB->D14_tmp *
    localB->D14_tmp_c) + localB->d13 * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * localB->D14_tmp_k * localB->D14_tmp *
    localB->D14_tmp_c) + localB->D46_tmp_lm *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] * rtP_ArmConstants.Mass2 *
    localB->D14_tmp_k * localB->D14_tmp_cv * localB->D14_tmp_c) +
                        localB->D46_tmp_lm *
                        localDW->DiscreteTimeIntegrator1_DSTATE[6] *
                        rtP_ArmConstants.Mass2 * localB->D14_tmp_k *
                        localB->D14_tmp_cv * localB->D14_tmp_c) +
                       localB->D14_tmp_nb * localB->D14_tmp_k *
                       localB->D14_tmp_cv * localB->D14_tmp_c) * localB->s +
                      (localB->D16_tmp_tmp * localB->d16 + localB->d18 *
                       localB->D14_tmp_j) * (localB->d8 * localB->smax)) +
                     ((((localB->d10 * 2.0 * localB->D14_tmp_m +
    localB->D14_tmp_b) * localB->D14_tmp_c + localB->d19) * localB->D14_tmp_f +
                       ((((localB->D17_tmp_tmp_a * localB->D14_tmp +
    localB->D14_tmp_e * localB->D14_tmp) + localB->D16_tmp * localB->D14_tmp_cv)
    - localB->D27_tmp * localB->D14_tmp * localB->D14_tmp_p * localB->D14_tmp_c)
                        - (localB->D16_tmp_m0 - localB->d14 * localB->D14_tmp_c)
                        * localB->D14_tmp_j)) * localB->s +
                      ((localDW->DiscreteTimeIntegrator1_DSTATE[3] *
                        localB->D14_tmp_f * localB->D14_tmp_p + localB->d22 *
                        localB->D14_tmp_cv) * localB->D14_tmp_n +
                       (localB->D14_tmp_m * 2.0 * localB->d16 +
                        localB->D14_tmp_b) * localB->D14_tmp) * localB->smax) *
                     localB->D14_tmp_cx) * 0.5);
  localB->D14_tmp_nb = localB->d17 * localB->D14_tmp_c;
  localB->d13 = localDW->DiscreteTimeIntegrator1_DSTATE[4] * localB->D15_tmp;
  localB->D17_tmp_tmp_a = 2.0 * localB->D14_tmp_g;
  localB->D14_tmp_e = localDW->DiscreteTimeIntegrator1_DSTATE[5] -
    localB->D14_tmp_nb;
  localB->x[56] = -(((((localDW->DiscreteTimeIntegrator1_DSTATE[4] *
                        localB->D14_tmp_g * localB->D15_tmp * localB->D14_tmp_k
                        + localB->d13 * localB->D17_tmp_l) + localB->d8 *
                       localB->D14_tmp_cv * localB->D14_tmp_e) * localB->s +
                      localB->D17_tmp_tmp_a * localB->D14_tmp_k * localB->smax *
                      localB->d18) + (((localB->D14_tmp_nb -
    localDW->DiscreteTimeIntegrator1_DSTATE[5]) * localB->D17_tmp_tmp_a +
    localB->d13 * localB->D14_tmp_cv) * localB->s + 2.0 * localB->smax *
    localB->D14_tmp_cv * localB->d18) * localB->D14_tmp_cx) * (0.5 *
    rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2));
  localB->D14_tmp_nb = localB->D15_tmp_tmp_n + localB->D15_tmp_tmp_c;
  localB->d8 = localB->d13 * localB->smax;
  localB->d13 = localB->D14_tmp_nb * localDW->DiscreteTimeIntegrator1_DSTATE[6];
  localB->x[25] = -(((((((((cos(localB->D16_tmp_j -
    localDW->DiscreteTimeIntegrator_DSTATE[4]) - cos(localB->D16_tmp_f -
    localDW->DiscreteTimeIntegrator_DSTATE[4])) - cos(localB->D16_tmp_j +
    localDW->DiscreteTimeIntegrator_DSTATE[4])) + cos(localB->D16_tmp_f +
    localDW->DiscreteTimeIntegrator_DSTATE[4])) + sin(localB->D16_tmp_j) * 2.0)
                        + sin(localB->D16_tmp_f) * 2.0) * (-0.25 *
    rtP_ArmConstants.MC2 * localDW->DiscreteTimeIntegrator1_DSTATE[7] *
    rtP_ArmConstants.Mass2) + (-localDW->DiscreteTimeIntegrator1_DSTATE[6] *
    localB->s * localB->D37_tmp + localB->D34_tmp_j * localB->d8)) + localB->d13
                      * localB->smax * localB->D14_tmp_c) + (localB->D15_tmp_a *
    localB->smax * localB->D14_tmp_c + localB->D34_tmp_j * -localB->s) *
                     localDW->DiscreteTimeIntegrator1_DSTATE[3]) +
                    (localB->D16_tmp_m * localB->D14_tmp_k + localB->D14_tmp_md *
                     localB->D14_tmp_cx) *
                    localDW->DiscreteTimeIntegrator1_DSTATE[5]);
  localB->D16_tmp_m = localB->D15_tmp_a *
    localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->D16_tmp_j = localDW->DiscreteTimeIntegrator1_DSTATE[3] *
    localB->D15_tmp;
  localB->x[33] = -((((-localDW->DiscreteTimeIntegrator1_DSTATE[5] * localB->s *
                       localB->D15_tmp_a * localB->D15_tmp + localB->d9 *
                       localB->D15_tmp * localB->smax * localB->D17_tmp_l) +
                      localDW->DiscreteTimeIntegrator1_DSTATE[6] *
                      localB->D15_tmp * localB->smax * localB->D37_tmp) +
                     localB->D16_tmp_j * localB->smax * localB->D34_tmp_j) +
                    localB->D16_tmp_m * localB->smax * localB->D14_tmp_c);
  localB->D16_tmp_f = localDW->DiscreteTimeIntegrator1_DSTATE[5] - localB->d10 *
    localB->D14_tmp_c;
  localB->D14_tmp_md = (((localB->tmp_tmp +
    localDW->DiscreteTimeIntegrator1_DSTATE[3]) * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 + localB->D46_tmp_tmp_n * localB->d10 *
    rtP_ArmConstants.Mass1) + localB->d19 * localB->D14_tmp_c) +
    localDW->DiscreteTimeIntegrator1_DSTATE[3] * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * localB->rtb_ginv_tmp_ie;
  localB->D17_tmp_tmp_a = -0.5 * rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2;
  localB->D16_tmp = 4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->d14 = -4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[6];
  localB->D14_tmp_b = -4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[7];
  localB->x[41] = -((((((((((-3.0 * localDW->DiscreteTimeIntegrator1_DSTATE[3] +
    localB->d14) + localB->D14_tmp_b) + localDW->DiscreteTimeIntegrator1_DSTATE
    [3] * localB->rtb_ginv_tmp_tmp) + localB->D16_tmp * localB->D14_tmp_c) *
    (localB->D17_tmp_tmp_a * localB->D14_tmp_g) +
    (-localDW->DiscreteTimeIntegrator1_DSTATE[5] * localB->D14_tmp_c +
     localDW->DiscreteTimeIntegrator1_DSTATE[3]) * (localB->D46_tmp_tmp_p *
    localB->D14_tmp_cz)) + localB->D14_tmp_md * localB->D14_tmp_f) *
                       localB->smax + ((localDW->DiscreteTimeIntegrator1_DSTATE
    [4] * rtP_ArmConstants.Hexa_to_joint_L * localB->D14_tmp_cz *
    localB->D15_tmp + localB->D14_tmp_tmp_f * localB->D16_tmp_f) +
    localB->D14_tmp_e * localB->D14_tmp_tmp_p) * localB->d20) *
                      -localB->D14_tmp_cx +
                      ((((-localDW->DiscreteTimeIntegrator1_DSTATE[3] *
    localB->D14_tmp_c + localDW->DiscreteTimeIntegrator1_DSTATE[5]) *
    localB->D14_tmp_m3 + localB->D16_tmp_tmp * localB->D16_tmp_f) +
                        localB->D14_tmp_e * localB->D14_tmp_j) *
                       localB->D14_tmp_k + (localB->d21 * localB->D15_tmp_g *
    localB->D15_tmp + localB->D14_tmp_i * localB->D15_tmp_m * localB->D15_tmp)) *
                      (-2.0 * localB->s)) + (((localB->rtb_ginv_tmp_ie *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] + localB->d22) *
    localB->D14_tmp_tmp_p + localB->D14_tmp_md * localB->D14_tmp) *
    localB->D14_tmp_k + (-localDW->DiscreteTimeIntegrator1_DSTATE[3] *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D15_tmp_g *
    localB->D17_tmp_e - localB->D27_tmp * localB->D15_tmp_m * localB->D17_tmp_e))
                     * localB->smax) * 0.5);
  localB->D14_tmp_i = localB->D16_tmp_tmp + localB->D14_tmp_j;
  localB->x[49] = -((((localB->D14_tmp_nb *
                       localDW->DiscreteTimeIntegrator1_DSTATE[3] * localB->smax
                       * localB->D14_tmp_c +
                       (-localDW->DiscreteTimeIntegrator1_DSTATE[3] * localB->s *
                        localB->D37_tmp + localB->D37_tmp * localB->d8)) -
                      (localB->s * localB->D17_tmp_l - localB->D15_tmp_m *
                       localB->smax * localB->D14_tmp_c) * localB->d9) +
                     (localB->D14_tmp_nb * localB->smax * localB->D14_tmp_c +
                      localB->D37_tmp * -localB->s) *
                     localDW->DiscreteTimeIntegrator1_DSTATE[6]) +
                    ((localB->D14_tmp_i * localB->s * localB->D14_tmp_c +
                      localB->D14_tmp_c0) * localB->D14_tmp_k +
                     (-localB->D14_tmp_i * localB->smax + localB->d11) *
                     localB->D14_tmp_cx) *
                    localDW->DiscreteTimeIntegrator1_DSTATE[5]);
  localB->x[57] = -(((((localB->d17 - localDW->DiscreteTimeIntegrator1_DSTATE[4])
                       * localB->D46_tmp_dy + localB->D16_tmp_m0 *
                       localB->D15_tmp_m) - (localB->d17 +
    localDW->DiscreteTimeIntegrator1_DSTATE[4]) * localB->D46_tmp_ln) *
                     localB->smax + localB->d20 * localB->D17_tmp_l *
                     localB->d18) * localB->D17_tmp_tmp_a);
  localB->x[26] = -(((localB->d9 * localB->D15_tmp_m * localB->D15_tmp +
                      localB->d13 * localB->D15_tmp) + localB->D15_tmp_a *
                     localDW->DiscreteTimeIntegrator1_DSTATE[3] *
                     localB->D15_tmp) - localB->D34_tmp_j *
                    localDW->DiscreteTimeIntegrator1_DSTATE[4] *
                    localB->D14_tmp_c);
  localB->x[34] = -(((localB->D16_tmp_m * localB->D15_tmp - localB->d9 *
                      localB->D17_tmp_l * localB->D14_tmp_c) + localB->D37_tmp *
                     -localDW->DiscreteTimeIntegrator1_DSTATE[6] *
                     localB->D14_tmp_c) - localB->D34_tmp_j *
                    localDW->DiscreteTimeIntegrator1_DSTATE[3] *
                    localB->D14_tmp_c);
  localB->x[42] = -0.0;
  localB->x[50] = -((localB->d17 * rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2
                     * localB->D15_tmp_m * localB->D15_tmp + localB->D14_tmp_m *
                     localB->d10 * localB->D15_tmp_g * localB->D15_tmp) -
                    localB->D37_tmp * localDW->DiscreteTimeIntegrator1_DSTATE[4]
                    * localB->D14_tmp_c);
  localB->x[58] = -((localB->d17 * localB->D15_tmp_m * localB->D15_tmp -
                     localDW->DiscreteTimeIntegrator1_DSTATE[4] *
                     localB->D17_tmp_l * localB->D14_tmp_c) * localB->D14_tmp_n);
  localB->x[27] = -(-localDW->DiscreteTimeIntegrator1_DSTATE[6] *
                    rtP_ArmConstants.Hexa_to_joint_L * localB->D14_tmp_m *
                    localB->D14_tmp - (localB->D27_tmp_g *
    rtP_ArmConstants.Hexa_to_joint_L * localB->D14_tmp_cv +
    localDW->DiscreteTimeIntegrator1_DSTATE[7] * rtP_ArmConstants.l1_dim *
    localB->D14_tmp_p) * localB->D14_tmp_n);
  localB->D14_tmp_nb = localB->D46_tmp_tmp_h * 2.0;
  localB->D14_tmp_i = localB->D46_tmp_m * 2.0;
  localB->d8 = localB->D46_tmp_mj * 2.0;
  localB->d9 = rtP_HexaConstants.Inertia[4] * localB->D17;
  localB->D16_tmp_m = rtP_HexaConstants.Inertia[8] * localB->D17;
  localB->d11 = localB->D56_tmp_ap * localB->D17;
  localB->d13 = localB->D56_tmp_jd * localB->D17;
  localB->D16_tmp_f = rtP_ArmConstants.Inertia1[0] * localB->D46_tmp_n;
  localB->d20 = rtP_ArmConstants.Inertia1[4] * localB->D46_tmp_n;
  localB->D14_tmp_md = localB->D47_tmp_p * localB->D46_tmp_n;
  localB->D17_tmp_tmp_a = localB->D47_tmp_px * localB->D46_tmp_n;
  localB->D14_tmp_e = rtP_ArmConstants.Inertia2[0] * localB->D46_tmp_bb;
  localB->D27_tmp = rtP_ArmConstants.Inertia2[4] * localB->D46_tmp_bb;
  localB->D27_tmp_g = localB->D47_tmp * localB->D46_tmp_bb;
  localB->d19 = localB->D14_tmp_i * rtP_ArmConstants.Mass1;
  localB->d21 = localB->D14_tmp_nb * rtP_ArmConstants.Mass1;
  localB->d22 = localB->d8 * rtP_ArmConstants.Mass2;
  localB->D14_tmp_nb *= rtP_ArmConstants.Mass2;
  localB->D14_tmp_g = localB->D46_tmp_cn * 2.0 * rtP_ArmConstants.Mass2;
  localB->D14_tmp_m3 = localB->D56_tmp_p * localB->D46_tmp_p;
  localB->D14_tmp_j = rtP_ArmConstants.Inertia1[0] * localB->D56_tmp_j;
  localB->D14_tmp_tmp_f = rtP_ArmConstants.Inertia1[4] * localB->D56_tmp_j;
  localB->D14_tmp_tmp_p = localB->D47_tmp_p * localB->D56_tmp_j;
  localB->D14_tmp_c0 = localB->D47_tmp_px * localB->D56_tmp_j;
  localB->D15_tmp_tmp_n = localB->D46_tmp_f * localB->D46_tmp_tmp_k;
  localB->D15_tmp_tmp_c = localB->D56_tmp_nj * localB->D46_tmp_l;
  localB->D16_tmp_tmp = localB->D46_tmp_f * localB->D56_tmp_tmp_l;
  localB->D34_tmp_j = rtP_ArmConstants.Inertia2[0] * localB->D56_tmp_f;
  localB->D37_tmp = rtP_ArmConstants.Inertia2[4] * localB->D56_tmp_f;
  localB->D46_tmp_tmp_p = localB->D47_tmp * localB->D56_tmp_f;
  localB->rtb_ginv_tmp_ie = 2.0 * rtP_ArmConstants.Inertia1[8] * localB->D15_tmp;
  localB->d57 = 2.0 * rtP_ArmConstants.Inertia2[8] * localB->D15_tmp;
  localB->d58 = localB->d19 * localB->D15_tmp;
  localB->d59 = localB->d22 * localB->D15_tmp;
  localB->d60 = localB->D14_tmp_g * localB->D15_tmp;
  localB->d61 = localB->D56_tmp_k * localB->D46_tmp_j;
  localB->d62 = rtP_ArmConstants.Inertia1[0] * localB->D56_tmp_a;
  localB->d63 = rtP_ArmConstants.Inertia1[4] * localB->D56_tmp_a;
  localB->d64 = localB->D47_tmp_p * localB->D56_tmp_a;
  localB->d65 = localB->D47_tmp_px * localB->D56_tmp_a;
  localB->d66 = localB->D46_tmp_f * localB->D46_tmp_tmp_b;
  localB->d67 = localB->D56_tmp_n3 * localB->D46_tmp_d;
  localB->d68 = localB->D46_tmp_f * localB->D56_tmp_tmp_p;
  localB->d69 = rtP_ArmConstants.Inertia2[0] * localB->D56_tmp_ju;
  localB->d70 = rtP_ArmConstants.Inertia2[4] * localB->D56_tmp_ju;
  localB->d71 = localB->D47_tmp * localB->D56_tmp_ju;
  localB->d72 = localB->D56_tmp_oyh * localB->D46_tmp_g;
  localB->d73 = localB->D25 * localB->D56_tmp_d;
  localB->d74 = localB->D56_tmp_g * localB->D46_tmp_dy;
  localB->d75 = localB->D15 * localB->D56_tmp_lx;
  localB->d76 = localB->D56_tmp_c * localB->D46_tmp_b;
  localB->d77 = localB->D25 * localB->D56_tmp_b;
  localB->d78 = localB->D56_tmp_cj * localB->D46_tmp_ln;
  localB->d79 = localB->D15 * localB->D56_tmp_h;
  localB->tmp_tmp_f = localB->D46_tmp_tmp_h * localB->D14_tmp_cz +
    (rtP_HexaConstants.Inertia[4] - rtP_HexaConstants.Inertia[8]);
  localB->D14_tmp_cz =
    ((((((((((((((((((((((((((((((((((((((((((((((((((((localB->tmp_tmp_f *
    localB->D56_tmp_tmp_m4 + localB->rtb_ginv_tmp_tmp_l * localB->D46_tmp_tmp_a)
    + localB->D14_tmp_m3) + localB->D46_tmp_cs * localB->D27) +
    localB->D46_tmp_k * localB->D27) - localB->D14_tmp_j) +
    localB->D14_tmp_tmp_f) + localB->D14_tmp_tmp_p) + localB->D14_tmp_c0) +
    localB->D15_tmp_tmp_n) + localB->D46_tmp_p4 * localB->D46_tmp_tmp_pc) +
    localB->D15_tmp_tmp_c) + localB->D46_tmp_p4 * localB->D56_tmp_tmp_o) +
    localB->D16_tmp_tmp) - localB->D34_tmp_j) + localB->D37_tmp) +
    localB->D46_tmp_tmp_p) + localB->rtb_ginv_tmp_ie) + localB->d57) + 2.0 *
    rtP_HexaConstants.Inertia[0] * localB->D15_tmp) + localB->d58) + localB->d21
    * localB->D15_tmp) + localB->d59) + localB->D14_tmp_nb * localB->D15_tmp) +
    localB->d60) + rtP_HexaConstants.Inertia[4] * localB->D56_tmp_tmp_c) -
    rtP_HexaConstants.Inertia[8] * localB->D56_tmp_tmp_c) + localB->D56_tmp_ap *
    localB->D56_tmp_tmp_c) + localB->D56_tmp_jd * localB->D56_tmp_tmp_c) +
    localB->D46_tmp_cs * localB->D46_tmp_tmp_fb) + localB->D46_tmp_k *
    localB->D46_tmp_tmp_fb) + localB->d61) + localB->D46_tmp_cs *
    localB->D56_tmp_tmp_hc) + localB->D46_tmp_k * localB->D56_tmp_tmp_hc) -
                       localB->d62) + localB->d63) + localB->d64) + localB->d65)
                   + localB->d66) + localB->D46_tmp_p4 * localB->D46_tmp_tmp_c)
                 + localB->d67) + localB->D46_tmp_p4 * localB->D56_tmp_tmp_h2) +
               localB->d68) - localB->d69) + localB->d70) + localB->d71) +
           localB->d72) + localB->d73) + localB->d74) + localB->d75) +
       localB->d76) + localB->d77) + localB->d78) + localB->d79;
  localB->rtb_ginv_tmp_tmp_l = localB->D56_tmp_m * localB->D46_tmp_bn +
    localB->D56_tmp_mc * localB->D46_tmp_tmp_m;
  localB->d178 = localB->D46_tmp_f * localB->D28;
  localB->x[35] = -(((((((((((((((((localB->rtb_ginv_tmp_tmp_l + localB->d9) -
    localB->D16_tmp_m) + localB->d11) + localB->d13) - localB->D16_tmp_f) +
    localB->d20) + localB->D14_tmp_md) + localB->D17_tmp_tmp_a) +
    localB->D46_tmp_cs * localB->D18) + localB->D46_tmp_k * localB->D18) -
    localB->D14_tmp_e) + localB->D27_tmp) + localB->D27_tmp_g) +
                       localB->D46_tmp_p4 * localB->D56_tmp_tmp_m) +
                      localB->d178) * localB->d12 + localB->D14_tmp_cz *
                     -localDW->DiscreteTimeIntegrator1_DSTATE[5]) * 0.25);
  localB->d23 = -2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->d24 = localB->d23 * localB->D46_tmp_tmp_h;
  localB->d25 = -4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->tmp_tmp_o = -4.0 * rtP_ArmConstants.MC1;
  localB->d26 = localB->tmp_tmp_o * localDW->DiscreteTimeIntegrator1_DSTATE[4] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  localB->tmp_tmp_j = localB->d25 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->tmp_tmp_d = -4.0 * rtP_ArmConstants.MC2;
  localB->tmp_tmp_i = localB->tmp_tmp_d *
    localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->d27 = localB->tmp_tmp_i * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->tmp_tmp_i = localB->tmp_tmp_i * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->d28 = localB->d25 * localB->D46_tmp_tmp_h;
  localB->d29 = localB->d23 * rtP_HexaConstants.Inertia[4];
  localB->d30 = localB->d12 * rtP_HexaConstants.Inertia[8];
  localB->d31 = localB->d24 * rtP_ArmConstants.Mass1;
  localB->d24 *= rtP_ArmConstants.Mass2;
  localB->tmp_tmp_fa = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia1[3];
  localB->tmp_tmp_ji = localB->d12 * rtP_ArmConstants.Inertia1[0];
  localB->tmp_tmp_oo = localB->d23 * rtP_ArmConstants.Inertia1[4];
  localB->tmp_tmp_fr = localB->D46_tmp_tmp_m1 *
    localDW->DiscreteTimeIntegrator1_DSTATE[4] * rtP_ArmConstants.Mass1;
  localB->tmp_tmp_oy = localB->d23 * localB->D46_tmp_cn * rtP_ArmConstants.Mass2;
  localB->d32 = 4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->tmp_tmp_ln = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia2[3];
  localB->tmp_tmp_lu = localB->d12 * rtP_ArmConstants.Inertia2[0];
  localB->tmp_tmp_gf = localB->d23 * rtP_ArmConstants.Inertia2[4];
  localB->tmp_tmp_d4 = localB->D46_tmp_tmp_j *
    localDW->DiscreteTimeIntegrator1_DSTATE[4] * rtP_ArmConstants.Mass2;
  localB->d33 = localB->d15 * localB->D46_tmp_tmp_h;
  localB->d34 = localB->tmp_tmp_d * localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->d35 = localB->D46_tmp_lm * localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->d36 = localB->D46_tmp_tmp_h * localDW->DiscreteTimeIntegrator1_DSTATE
    [5];
  localB->d37 = rtP_HexaConstants.Inertia[4] *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->d38 = localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_HexaConstants.Inertia[8];
  localB->d39 = localB->d36 * rtP_ArmConstants.Mass1;
  localB->d36 *= rtP_ArmConstants.Mass2;
  localB->tmp_tmp_dv = rtP_ArmConstants.Inertia1[0] *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->tmp_tmp_jo = rtP_ArmConstants.Inertia1[4] *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->tmp_tmp_f1 = localB->D46_tmp_m *
    localDW->DiscreteTimeIntegrator1_DSTATE[5] * rtP_ArmConstants.Mass1;
  localB->d40 = localB->d25 * rtP_ArmConstants.Inertia1[3];
  localB->tmp_tmp_js = rtP_ArmConstants.Inertia2[0] *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->tmp_tmp_ho = rtP_ArmConstants.Inertia2[4] *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->tmp_tmp_h = localB->D46_tmp_mj *
    localDW->DiscreteTimeIntegrator1_DSTATE[5] * rtP_ArmConstants.Mass2;
  localB->d41 = localB->d25 * rtP_ArmConstants.Inertia2[3];
  localB->d42 = localB->D46_tmp_d3 * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  localB->d43 = localB->d15 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->d44 = localB->d35 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->d35 = localB->d35 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->d45 = rtP_ArmConstants.l1_dim * localB->D14_tmp_p +
    rtP_ArmConstants.Hexa_to_joint_L * localB->D14_tmp_cv;
  localB->d47 = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia1[7];
  localB->d48 = localB->D46_tmp_cn * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Mass2;
  localB->d50 = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia2[7];
  localB->d51 = localB->d15 * rtP_ArmConstants.Inertia1[7];
  localB->d52 = localB->d15 * rtP_ArmConstants.Inertia2[7];
  localB->d53 = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia1[6];
  localB->d54 = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia2[6];
  localB->d55 = localB->d15 * rtP_ArmConstants.Inertia1[6];
  localB->d56 = localB->d15 * rtP_ArmConstants.Inertia2[6];
  localB->d105 = localB->d29 * localB->D56_tmp_tmp_m4;
  localB->d106 = localB->d30 * localB->D56_tmp_tmp_m4;
  localB->d107 = localB->d31 * localB->D56_tmp_tmp_m4;
  localB->d108 = localB->d24 * localB->D56_tmp_tmp_m4;
  localB->d125 = localB->d25 * rtP_ArmConstants.Inertia1[7];
  localB->d109 = localB->d125 * localB->D46_tmp_p;
  localB->d110 = localB->tmp_tmp_fa * localB->rtb_ginv_tmp_k;
  localB->d111 = localB->d26 * localB->D27;
  localB->d112 = localB->tmp_tmp_j * localB->D27;
  localB->d113 = localB->tmp_tmp_ji * localB->D56_tmp_j;
  localB->d114 = localB->tmp_tmp_oo * localB->D56_tmp_j;
  localB->d115 = localB->tmp_tmp_fr * localB->D56_tmp_j;
  localB->d116 = localB->tmp_tmp_oy * localB->D56_tmp_j;
  localB->d126 = localB->d25 * rtP_ArmConstants.Inertia2[7];
  localB->d117 = localB->d126 * localB->D46_tmp_l;
  localB->d118 = localB->tmp_tmp_ln * localB->D46_tmp_tmp_i;
  localB->d119 = localB->d27 * localB->D56_tmp_tmp_o;
  localB->d120 = localB->tmp_tmp_i * localB->D56_tmp_tmp_l;
  localB->d121 = localB->tmp_tmp_lu * localB->D56_tmp_f;
  localB->d122 = localB->tmp_tmp_gf * localB->D56_tmp_f;
  localB->d123 = localB->tmp_tmp_d4 * localB->D56_tmp_f;
  localB->D46_tmp_m *= -4.0;
  localB->d124 = localB->D46_tmp_mj * -4.0;
  localB->d127 = localB->d35 * localB->D46_tmp_tmp;
  localB->d128 = -4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->d129 = localB->d42 * localB->D56_tmp_tmp_e;
  localB->d130 = localB->d43 * localB->D56_tmp_tmp_e;
  localB->d131 = localB->d44 * localB->D56_tmp_tmp_h;
  localB->d132 = localB->d38 * localB->d4;
  localB->d158 = localB->d25 * rtP_ArmConstants.Inertia1[6];
  localB->d133 = localB->d158 * localB->D46_tmp_g;
  localB->d134 = localB->tmp_tmp_dv * localB->D38;
  localB->d135 = localB->tmp_tmp_jo * localB->D38;
  localB->d136 = localB->tmp_tmp_f1 * localB->D38;
  localB->d137 = localB->d48 * localB->D38;
  localB->d138 = localB->d40 * localB->D56_tmp_d;
  localB->d163 = localB->d25 * rtP_ArmConstants.Inertia2[6];
  localB->d139 = localB->d163 * localB->D46_tmp_dy;
  localB->d140 = localB->tmp_tmp_js * localB->D47_tmp_o;
  localB->d141 = localB->tmp_tmp_ho * localB->D47_tmp_o;
  localB->d142 = localB->tmp_tmp_h * localB->D47_tmp_o;
  localB->d143 = localB->d41 * localB->D56_tmp_lx;
  localB->d144 = localB->d15 * rtP_ArmConstants.Inertia1[4];
  localB->d145 = localB->d15 * rtP_ArmConstants.Inertia2[4];
  localB->d146 = localB->d15 * rtP_HexaConstants.Inertia[4];
  localB->d151 = localB->d37 * localB->D47;
  localB->d152 = localB->d39 * localB->D47;
  localB->d153 = localB->d36 * localB->D47;
  localB->d154 = localB->d37 * localB->D48_tmp_o;
  localB->d155 = localB->d38 * localB->D48_tmp_o;
  localB->d156 = localB->d39 * localB->D48_tmp_o;
  localB->d157 = localB->d36 * localB->D48_tmp_o;
  localB->d159 = localB->tmp_tmp_dv * localB->D56_tmp_tmp;
  localB->d160 = localB->tmp_tmp_jo * localB->D56_tmp_tmp;
  localB->d161 = localB->tmp_tmp_f1 * localB->D56_tmp_tmp;
  localB->d164 = localB->tmp_tmp_js * localB->D58;
  localB->d165 = localB->tmp_tmp_ho * localB->D58;
  localB->d166 = localB->tmp_tmp_h * localB->D58;
  localB->d168 = localB->tmp_tmp_i * localB->D46_tmp_tmp_k;
  localB->d169 = localB->d25 * rtP_ArmConstants.Inertia1[8] * localB->D15_tmp;
  localB->d170 = localB->d25 * rtP_ArmConstants.Inertia2[8] * localB->D15_tmp;
  localB->d171 = localB->D46_tmp_m * localDW->DiscreteTimeIntegrator1_DSTATE[4] *
    rtP_ArmConstants.Mass1 * localB->D15_tmp;
  localB->d172 = localB->d124 * localDW->DiscreteTimeIntegrator1_DSTATE[4] *
    rtP_ArmConstants.Mass2 * localB->D15_tmp;
  localB->d173 = localB->d25 * localB->D46_tmp_cn * rtP_ArmConstants.Mass2 *
    localB->D15_tmp;
  localB->d174 = localB->tmp_tmp_i * localB->D46_tmp_tmp_b;
  localB->d199 = localB->D16_tmp * rtP_ArmConstants.Inertia2[3] *
    localB->D46_tmp_tmp_m;
  localB->d200 = localB->d54 * localB->D68;
  localB->d179 = ((localB->D16_tmp * rtP_ArmConstants.Inertia1[3] *
                   localB->D46_tmp_bn + localB->d199) + localB->d53 *
                  localB->rtb_ginv_tmp_tmp_n) + localB->d200;
  localB->d180 = localB->tmp_tmp_fa * localB->d;
  localB->d181 = localB->tmp_tmp_ln * localB->D46_tmp_tmp_g;
  localB->d182 = localB->d55 * localB->d1;
  localB->d183 = localB->d56 * localB->d2;
  localB->d184 = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia1[0] *
    localB->D46_tmp_n;
  localB->d185 = localB->d144 * localB->D46_tmp_n;
  localB->D46_tmp_tmp_m1 = localB->D46_tmp_tmp_m1 *
    localDW->DiscreteTimeIntegrator1_DSTATE[5] * rtP_ArmConstants.Mass1 *
    localB->D46_tmp_n;
  localB->d186 = localB->d15 * localB->D46_tmp_cn * rtP_ArmConstants.Mass2 *
    localB->D46_tmp_n;
  localB->d187 = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia2[0] *
    localB->D46_tmp_bb;
  localB->d188 = localB->d145 * localB->D46_tmp_bb;
  localB->D46_tmp_tmp_j = localB->D46_tmp_tmp_j *
    localDW->DiscreteTimeIntegrator1_DSTATE[5] * rtP_ArmConstants.Mass2 *
    localB->D46_tmp_bb;
  localB->d189 = localB->d34 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 *
    localB->D28;
  localB->d190 = localB->d51 * localB->ab_a;
  localB->d191 = localB->d52 * localB->D67;
  localB->d192 = 8.0 * rtP_ArmConstants.MC2 *
    localDW->DiscreteTimeIntegrator1_DSTATE[7];
  localB->d195 = localB->d47 * localB->D15_tmp_tmp;
  localB->d196 = localB->d50 * localB->D15_tmp_tmp_i;
  localB->d197 = localB->d35 * localB->D46_tmp_tmp_f;
  localB->x[43] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    ((((((((((((((((((((((((((((((((((((((((localB->d179 + localB->d105) +
    localB->d106) + localB->d107) + localB->d108) + localB->d26 *
    localB->D46_tmp_tmp_a) + localB->tmp_tmp_j * localB->D46_tmp_tmp_a) +
    localB->d109) + localB->d110) + localB->d111) + localB->d112) + localB->d113)
    + localB->d114) + localB->d115) + localB->d116) + localB->d168) +
    localB->d27 * localB->D46_tmp_tmp_pc) + localB->d117) + localB->d118) +
    localB->d119) + localB->d120) + localB->d121) + localB->d122) + localB->d123)
    + localB->d169) + localB->d170) + localB->d25 * rtP_HexaConstants.Inertia[0]
    * localB->D15_tmp) + localB->d171) + localB->d28 * rtP_ArmConstants.Mass1 *
    localB->D15_tmp) + localB->d172) + localB->d28 * rtP_ArmConstants.Mass2 *
    localB->D15_tmp) + localB->d173) + localB->d29 * localB->D56_tmp_tmp_c) +
    localB->d30 * localB->D56_tmp_tmp_c) + localB->d31 * localB->D56_tmp_tmp_c)
    + localB->d24 * localB->D56_tmp_tmp_c) + localB->d26 *
    localB->D46_tmp_tmp_fb) + localB->tmp_tmp_j * localB->D46_tmp_tmp_fb) +
    localB->d32 * rtP_ArmConstants.Inertia1[7] * localB->D46_tmp_j) +
    localB->d180) + localB->d26 * localB->D56_tmp_tmp_hc) + localB->tmp_tmp_j *
    localB->D56_tmp_tmp_hc) + localB->tmp_tmp_ji * localB->D56_tmp_a) +
    localB->tmp_tmp_oo * localB->D56_tmp_a) + localB->tmp_tmp_fr *
    localB->D56_tmp_a) + localB->tmp_tmp_oy * localB->D56_tmp_a) + localB->d174)
    + localB->d27 * localB->D46_tmp_tmp_c) + localB->d32 *
    rtP_ArmConstants.Inertia2[7] * localB->D46_tmp_d) + localB->d181) +
    localB->d27 * localB->D56_tmp_tmp_h2) + localB->tmp_tmp_i *
    localB->D56_tmp_tmp_p) + localB->tmp_tmp_lu * localB->D56_tmp_ju) +
    localB->tmp_tmp_gf * localB->D56_tmp_ju) + localB->tmp_tmp_d4 *
    localB->D56_tmp_ju) + localB->d182) + localB->d183) + localB->d146 *
    localB->D17) + localB->D16_tmp_m0 * rtP_HexaConstants.Inertia[8] *
    localB->D17) + localB->d33 * rtP_ArmConstants.Mass1 * localB->D17) +
    localB->d33 * rtP_ArmConstants.Mass2 * localB->D17) + localB->d184) +
    localB->d185) + localB->D46_tmp_tmp_m1) + localB->d186) + localB->tmp_tmp_o *
    localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1 * localB->D18) +
    localB->d128 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * localB->D18) + localB->d187) + localB->d188) +
    localB->D46_tmp_tmp_j) + localB->d34 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2 * localB->D56_tmp_tmp_m) + localB->d189) +
    localB->d127) + localB->d190) + localB->d129) + localB->d130) + localB->d191)
    + localB->d131) + localB->d132) + localB->d133) + localB->d134) -
    localB->d135) - localB->d136) - localB->d137) + localB->d138) + localB->d139)
    + localB->d140) - localB->d141) - localB->d142) + localB->d143) +
    localB->d192 * rtP_ArmConstants.Mass2 * localB->d45 * localB->D14_tmp_c) +
    8.0 * localDW->DiscreteTimeIntegrator1_DSTATE[6] *
    rtP_ArmConstants.Hexa_to_joint_L * localB->D14_tmp_h * localB->D14_tmp_c) +
    localB->d151) + localB->d152) + localB->d153) - localB->d154) + localB->d155)
    - localB->d156) - localB->d157) + localB->d32 * rtP_ArmConstants.Inertia1[6]
                       * localB->D46_tmp_b) + localB->d159) - localB->d160) -
                    localB->d161) + localB->D46_tmp_cn *
                   -localDW->DiscreteTimeIntegrator1_DSTATE[5] *
                   rtP_ArmConstants.Mass2 * localB->D56_tmp_tmp) + localB->d40 *
                  localB->D56_tmp_b) + localB->d32 * rtP_ArmConstants.Inertia2[6]
                 * localB->D46_tmp_ln) + localB->d164) - localB->d165) -
              localB->d166) + localB->d41 * localB->D56_tmp_h) + localB->d195) +
           localB->d196) + localB->d42 * localB->y_a) + localB->d43 *
         localB->y_a) + localB->d44 * localB->D48_tmp_tmp) + localB->d197) *
      0.125);
  localB->d25 = localB->D14_tmp_h * rtP_ArmConstants.Hexa_to_joint_L;
  localB->d28 = -rtP_ArmConstants.MC2 * localDW->DiscreteTimeIntegrator1_DSTATE
    [7];
  localB->x[51] = -(localB->d28 * rtP_ArmConstants.Mass2 * localB->d45 -
                    localB->d25 * localB->d16);
  localB->x[59] = -(-rtP_ArmConstants.MC2 * rtP_ArmConstants.Mass2 * localB->d45
                    * localB->d18);
  localB->d46 = localB->d46 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  localB->d33 = localB->D16_tmp_m0 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->d34 = localB->d49 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->d49 = localB->d49 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->d40 = localB->D16_tmp_m0 * localB->D46_tmp_tmp_h;
  localB->d41 = -4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[3];
  localB->D14_tmp_h = localB->d32 * rtP_ArmConstants.Inertia2[3];
  localB->tmp_tmp_n = localB->D14_tmp_h * localB->D46_tmp_tmp_m;
  localB->d100 = 4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[3];
  localB->d162 = localB->d32 * rtP_ArmConstants.Inertia1[3];
  localB->d175 = localB->d100 * rtP_ArmConstants.Inertia2[6];
  localB->d176 = 4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[7];
  localB->d177 = 4.0 * localDW->DiscreteTimeIntegrator1_DSTATE[6];
  localB->d10 = ((((localB->d10 * 4.0 * rtP_ArmConstants.Inertia1[6] *
                    localB->D15_tmp_g + localB->d162 * localB->D46_tmp_bn) +
                   localB->d175 * localB->D15_tmp_m) + localB->d177 *
                  rtP_ArmConstants.Inertia2[6] * localB->D15_tmp_m) +
                 localB->d176 * rtP_ArmConstants.Inertia2[6] * localB->D15_tmp_m)
    + localB->tmp_tmp_n;
  localB->tmp_tmp_c = localB->d47 * localB->D46_tmp_p;
  localB->tmp_tmp_b = localB->tmp_tmp_dv * localB->D56_tmp_j;
  localB->tmp_tmp_e = localB->tmp_tmp_jo * localB->D56_tmp_j;
  localB->tmp_tmp_dd = localB->tmp_tmp_f1 * localB->D56_tmp_j;
  localB->tmp_tmp_g = localB->d48 * localB->D56_tmp_j;
  localB->tmp_tmp_nn = localB->d49 * localB->D46_tmp_tmp_k;
  localB->tmp_tmp_l = localB->d50 * localB->D46_tmp_l;
  localB->tmp_tmp_nc = localB->d49 * localB->D56_tmp_tmp_l;
  localB->tmp_tmp_p = localB->tmp_tmp_js * localB->D56_tmp_f;
  localB->tmp_tmp_dk = localB->tmp_tmp_ho * localB->D56_tmp_f;
  localB->tmp_tmp_oi = localB->tmp_tmp_h * localB->D56_tmp_f;
  localB->tmp_tmp_jr = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia1[8] *
    localB->D15_tmp;
  localB->d80 = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia2[8] *
    localB->D15_tmp;
  localB->d147 = localB->D14_tmp_i * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Mass1;
  localB->d81 = localB->d147 * localB->D15_tmp;
  localB->d149 = localB->d8 * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Mass2;
  localB->d82 = localB->d149 * localB->D15_tmp;
  localB->d150 = localB->D16_tmp_m0 * localB->D46_tmp_cn *
    rtP_ArmConstants.Mass2;
  localB->d83 = localB->d150 * localB->D15_tmp;
  localB->d84 = localB->d51 * localB->D46_tmp_j;
  localB->tmp_tmp_dv *= localB->D56_tmp_a;
  localB->tmp_tmp_jo *= localB->D56_tmp_a;
  localB->tmp_tmp_f1 *= localB->D56_tmp_a;
  localB->d85 = localB->d48 * localB->D56_tmp_a;
  localB->d86 = localB->d49 * localB->D46_tmp_tmp_b;
  localB->d87 = localB->d52 * localB->D46_tmp_d;
  localB->d88 = localB->d49 * localB->D56_tmp_tmp_p;
  localB->tmp_tmp_js *= localB->D56_tmp_ju;
  localB->tmp_tmp_ho *= localB->D56_tmp_ju;
  localB->tmp_tmp_h *= localB->D56_tmp_ju;
  localB->d89 = localB->d41 * rtP_ArmConstants.Inertia1[7] * localB->D17_tmp_a;
  localB->d90 = localB->d14 * rtP_ArmConstants.Inertia1[7] * localB->D17_tmp_a;
  localB->tmp_tmp_ji *= localB->D46_tmp_n;
  localB->tmp_tmp_oo *= localB->D46_tmp_n;
  localB->tmp_tmp_fr *= localB->D46_tmp_n;
  localB->tmp_tmp_oy *= localB->D46_tmp_n;
  localB->d91 = localB->d41 * rtP_ArmConstants.Inertia2[7] * localB->D17_tmp_l;
  localB->d92 = localB->d14 * rtP_ArmConstants.Inertia2[7] * localB->D17_tmp_l;
  localB->d93 = localB->D14_tmp_b * rtP_ArmConstants.Inertia2[7] *
    localB->D17_tmp_l;
  localB->tmp_tmp_lu *= localB->D46_tmp_bb;
  localB->tmp_tmp_gf *= localB->D46_tmp_bb;
  localB->tmp_tmp_d4 *= localB->D46_tmp_bb;
  localB->tmp_tmp_i *= localB->D28;
  localB->d94 = localB->d53 * localB->D46_tmp_g;
  localB->d95 = localB->tmp_tmp_fa * localB->D56_tmp_d;
  localB->d96 = localB->d54 * localB->D46_tmp_dy;
  localB->d97 = localB->tmp_tmp_ln * localB->D56_tmp_lx;
  localB->d98 = localB->d55 * localB->D46_tmp_b;
  localB->tmp_tmp_fa *= localB->D56_tmp_b;
  localB->d99 = localB->d56 * localB->D46_tmp_ln;
  localB->tmp_tmp_ln *= localB->D56_tmp_h;
  localB->d148 = localB->d40 * rtP_ArmConstants.Mass1;
  localB->d40 *= rtP_ArmConstants.Mass2;
  localB->x[28] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((localB->d37 * localB->D56_tmp_tmp_m4 + localB->d10) - localB->d38 *
    localB->D56_tmp_tmp_m4) + localB->d39 * localB->D56_tmp_tmp_m4) +
    localB->d36 * localB->D56_tmp_tmp_m4) + localB->d46 * localB->D46_tmp_tmp_a)
    + localB->d33 * localB->D46_tmp_tmp_a) + localB->tmp_tmp_c) + localB->d46 *
    localB->D27) + localB->d33 * localB->D27) - localB->tmp_tmp_b) +
    localB->tmp_tmp_e) + localB->tmp_tmp_dd) + localB->tmp_tmp_g) +
    localB->tmp_tmp_nn) + localB->d34 * localB->D46_tmp_tmp_pc) +
    localB->tmp_tmp_l) + localB->d34 * localB->D56_tmp_tmp_o) +
    localB->tmp_tmp_nc) - localB->tmp_tmp_p) + localB->tmp_tmp_dk) +
    localB->tmp_tmp_oi) + localB->tmp_tmp_jr) + localB->d80) +
    localB->D16_tmp_m0 * rtP_HexaConstants.Inertia[0] * localB->D15_tmp) +
    localB->d81) + localB->d148 * localB->D15_tmp) + localB->d82) + localB->d40 *
    localB->D15_tmp) + localB->d83) + localB->d37 * localB->D56_tmp_tmp_c) -
    localB->d38 * localB->D56_tmp_tmp_c) + localB->d39 * localB->D56_tmp_tmp_c)
    + localB->d36 * localB->D56_tmp_tmp_c) + localB->d46 *
    localB->D46_tmp_tmp_fb) + localB->d33 * localB->D46_tmp_tmp_fb) +
    localB->d84) + localB->d46 * localB->D56_tmp_tmp_hc) + localB->d33 *
    localB->D56_tmp_tmp_hc) - localB->tmp_tmp_dv) + localB->tmp_tmp_jo) +
    localB->tmp_tmp_f1) + localB->d85) + localB->d86) + localB->d34 *
    localB->D46_tmp_tmp_c) + localB->d87) + localB->d34 * localB->D56_tmp_tmp_h2)
    + localB->d88) - localB->tmp_tmp_js) + localB->tmp_tmp_ho) +
    localB->tmp_tmp_h) + localB->d29 * localB->D17) + localB->d30 * localB->D17)
    + localB->d31 * localB->D17) + localB->d24 * localB->D17) + localB->d89) +
    localB->d90) + localB->tmp_tmp_ji) + localB->tmp_tmp_oo) +
    localB->tmp_tmp_fr) + localB->tmp_tmp_oy) + localB->d26 * localB->D18) +
                       localB->tmp_tmp_j * localB->D18) + localB->d91) +
                     localB->d92) + localB->d93) + localB->tmp_tmp_lu) +
                  localB->tmp_tmp_gf) + localB->tmp_tmp_d4) + localB->d27 *
                localB->D56_tmp_tmp_m) + localB->tmp_tmp_i) + localB->d94) +
             localB->d95) + localB->d96) + localB->d97) + localB->d98) +
         localB->tmp_tmp_fa) + localB->d99) + localB->tmp_tmp_ln) * 0.25);
  localB->d24 = localB->D25 * localB->D46_tmp_bn + localB->D15 *
    localB->D46_tmp_tmp_m;
  localB->d26 = localB->D46_tmp_tmp_d * localB->D28;
  localB->tmp_tmp_j = 2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[7];
  localB->d27 = -rtP_ArmConstants.MC1 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass1;
  localB->d29 = localB->D24_tmp * localB->D14_tmp;
  localB->d30 = localB->D24_tmp_i * localB->D18;
  localB->d31 = localB->D47_tmp_tmp * localB->D14_tmp_cv;
  localB->d36 = localB->D47_tmp_tmp * localB->D56_tmp_tmp_m;
  localB->d37 = (localB->D47_tmp_tmp * localB->D14_tmp_cx + localB->D48_tmp *
                 localB->D15_tmp_g) + (localB->D47_tmp + localB->D34) *
    localB->D15_tmp_m;
  localB->x[36] = -((((((((((((((((((localB->d24 - localB->d9) +
    localB->D16_tmp_m) - localB->d11) - localB->d13) + localB->D16_tmp_f) -
    localB->d20) - localB->D14_tmp_md) - localB->D17_tmp_tmp_a) +
    localB->D46_tmp_kn * localB->D18) + localB->D46_tmp_mx * localB->D18) +
    localB->D14_tmp_e) - localB->D27_tmp) - localB->D27_tmp_g) +
                        localB->D46_tmp_pr * localB->D56_tmp_tmp_m) +
                       localB->d26) * localDW->DiscreteTimeIntegrator1_DSTATE[3]
                      + (-2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[7] *
    localB->d37 * localB->D17_tmp_l + localB->tmp_tmp_j *
    rtP_ArmConstants.Inertia2[3] * localB->D46_tmp_tmp_m)) +
                     (((((((((((((-rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D14_tmp +
    (localB->d24 - localB->d29)) + localB->D16_tmp_f) - localB->d20) -
    localB->D14_tmp_md) - localB->D17_tmp_tmp_a) + localB->d27 * localB->D18) -
    localB->d30) - localB->d31) + localB->D14_tmp_e) - localB->D27_tmp) -
                        localB->D27_tmp_g) - localB->d36) + localB->d26) *
                     localDW->DiscreteTimeIntegrator1_DSTATE[6]) * 0.5);
  localB->d9 = 4.0 * rtP_ArmConstants.Inertia1[6];
  localB->D16_tmp_m = 4.0 * rtP_ArmConstants.Inertia2[6];
  localB->d11 = -4.0 * rtP_ArmConstants.Inertia1[7];
  localB->d13 = -4.0 * rtP_ArmConstants.Inertia2[7];
  localB->d24 = localB->D47_tmp_tmp * localB->D46_tmp_tmp_pc;
  localB->d26 = localB->D47_tmp_tmp * localB->D56_tmp_tmp_o;
  localB->d38 = localB->D47_tmp_tmp * localB->D46_tmp_tmp_c;
  localB->d39 = localB->D47_tmp_tmp * localB->D56_tmp_tmp_h2;
  localB->d101 = localB->D47_tmp_g * localB->D46_tmp_tmp_a;
  localB->D47_tmp_g = localB->D24_tmp * localB->D46_tmp_tmp_fb;
  localB->d102 = localB->D24_tmp_i * localB->D46_tmp_tmp_fb;
  localB->d103 = localB->D48_tmp * localB->D46_tmp_tmp_k + localB->d24;
  localB->d104 = localB->D48_tmp * localB->D46_tmp_tmp_b;
  localB->D14_tmp_m3 = ((localB->d101 + localB->D14_tmp_m3) + localB->D24_tmp *
                        localB->D27) + localB->D24_tmp_i * localB->D27;
  localB->d193 = localB->D24_tmp * localB->D56_tmp_tmp_hc;
  localB->d194 = localB->D24_tmp_i * localB->D56_tmp_tmp_hc;
  localB->D14_tmp_j =
    (((((((((((((((((((((((((((((((((((((((((localB->D14_tmp_m3 -
    localB->D14_tmp_j) + localB->D14_tmp_tmp_f) + localB->D14_tmp_tmp_p) +
    localB->D14_tmp_c0) + localB->D15_tmp_tmp_n) + localB->d24) +
    localB->D15_tmp_tmp_c) + localB->d26) + localB->D16_tmp_tmp) -
    localB->D34_tmp_j) + localB->D37_tmp) + localB->D46_tmp_tmp_p) +
    localB->rtb_ginv_tmp_ie) + localB->d57) + localB->d58) + localB->d59) +
    localB->d60) + localB->D47_tmp_g) + localB->d102) + localB->d61) +
    localB->d193) + localB->d194) - localB->d62) + localB->d63) + localB->d64) +
                    localB->d65) + localB->d66) + localB->d38) + localB->d67) +
                localB->d39) + localB->d68) - localB->d69) + localB->d70) +
            localB->d71) + localB->d72) + localB->d73) + localB->d74) +
        localB->d75) + localB->d76) + localB->d77) + localB->d78) + localB->d79;
  localB->d198 = (((((((((((((((((((localB->d103 + localB->D15_tmp_tmp_c) +
    localB->d26) + localB->D48_tmp * localB->D56_tmp_tmp_l) - localB->D34_tmp_j)
    + localB->D37_tmp) + localB->D46_tmp_tmp_p) + localB->d57) + localB->d59) +
    localB->d104) + localB->d38) + localB->d67) + localB->d39) + localB->D48_tmp
                        * localB->D56_tmp_tmp_p) - localB->d69) + localB->d70) +
                     localB->d71) + localB->d74) + localB->d75) + localB->d78) +
    localB->d79;
  localB->x[44] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((localB->d9
    * localB->rtb_ginv_tmp_tmp_n + localB->D16_tmp_m * localB->D68) +
    localB->D25 * localB->rtb_ginv_tmp_k) + localB->D15 * localB->D46_tmp_tmp_i)
    + localB->D56_tmp_m * localB->d) + localB->D56_tmp_mc *
    localB->D46_tmp_tmp_g) + localB->d9 * localB->d1) + localB->D16_tmp_m *
    localB->d2) + localB->D46_tmp_tmp_d * localB->D46_tmp_tmp) +
    localB->D46_tmp_kn * localB->d3) + localB->D46_tmp_mx * localB->d3) +
    localB->d11 * localB->ab_a) + localB->D46_tmp_kn * localB->D56_tmp_tmp_e) +
    localB->D46_tmp_mx * localB->D56_tmp_tmp_e) + localB->D46_tmp_tmp_d *
    localB->d6) + localB->D46_tmp_pr * localB->D37) + localB->d13 * localB->D67)
    + localB->D46_tmp_pr * localB->D56_tmp_tmp_h) + rtP_HexaConstants.Inertia[8]
    * localB->d4) + rtP_ArmConstants.Inertia1[0] * localB->D38) -
    rtP_ArmConstants.Inertia1[4] * localB->D38) - localB->D47_tmp_p *
    localB->D38) - localB->D47_tmp_px * localB->D38) +
    rtP_ArmConstants.Inertia2[0] * localB->D47_tmp_o) -
    rtP_ArmConstants.Inertia2[4] * localB->D47_tmp_o) + -localB->D46_tmp_mj *
    rtP_ArmConstants.Mass2 * localB->D47_tmp_o) + -2.0 *
    rtP_ArmConstants.Inertia1[0] * localB->D46_tmp_pb) + -2.0 *
    rtP_ArmConstants.Inertia1[4] * localB->D46_tmp_pb) + 4.0 *
    rtP_ArmConstants.Inertia1[8] * localB->D46_tmp_pb) + -2.0 *
    rtP_ArmConstants.Inertia2[0] * localB->D46_tmp_pb) + -2.0 *
    rtP_ArmConstants.Inertia2[4] * localB->D46_tmp_pb) + 4.0 *
    rtP_ArmConstants.Inertia2[8] * localB->D46_tmp_pb) + 4.0 *
    rtP_HexaConstants.Inertia[0] * localB->D46_tmp_pb) + -2.0 *
    rtP_HexaConstants.Inertia[4] * localB->D46_tmp_pb) + -2.0 *
    rtP_HexaConstants.Inertia[8] * localB->D46_tmp_pb) + localB->d19 *
    localB->D46_tmp_pb) + localB->d21 * localB->D46_tmp_pb) + localB->d22 *
    localB->D46_tmp_pb) + localB->D14_tmp_nb * localB->D46_tmp_pb) +
    localB->D14_tmp_g * localB->D46_tmp_pb) + rtP_HexaConstants.Inertia[4] *
    localB->D47) + localB->D56_tmp_ap * localB->D47) + localB->D56_tmp_jd *
    localB->D47) + rtP_HexaConstants.Inertia[4] * localB->D48_tmp_o) -
    rtP_HexaConstants.Inertia[8] * localB->D48_tmp_o) + localB->D56_tmp_ap *
    localB->D48_tmp_o) + localB->D56_tmp_jd * localB->D48_tmp_o) -
                        rtP_ArmConstants.Inertia1[0] * localB->D56_tmp_tmp) +
                       rtP_ArmConstants.Inertia1[4] * localB->D56_tmp_tmp) +
                      localB->D47_tmp_p * localB->D56_tmp_tmp) +
                     localB->D47_tmp_px * localB->D56_tmp_tmp) -
                    rtP_ArmConstants.Inertia2[0] * localB->D58) +
                   rtP_ArmConstants.Inertia2[4] * localB->D58) + localB->D47_tmp
                  * localB->D58) + localB->D46_tmp_cs * localB->d5) +
                localB->D46_tmp_k * localB->d5) + localB->d11 *
               localB->D15_tmp_tmp) + localB->D46_tmp_f * localB->d7) +
             localB->D46_tmp_p4 * localB->D14_tmp_tmp) + localB->d13 *
            localB->D15_tmp_tmp_i) + localB->D46_tmp_cs * localB->y_a) +
          localB->D46_tmp_k * localB->y_a) + localB->D46_tmp_p4 *
         localB->D48_tmp_tmp) + localB->D46_tmp_f * localB->D46_tmp_tmp_f) *
       (-0.5 * localDW->DiscreteTimeIntegrator1_DSTATE[5]) + ((localB->D14_tmp_j
         * localDW->DiscreteTimeIntegrator1_DSTATE[6] + localB->d198 *
         localDW->DiscreteTimeIntegrator1_DSTATE[7]) + localB->D14_tmp_cz *
        localDW->DiscreteTimeIntegrator1_DSTATE[3])) * 0.25);
  localB->D38 = rtP_ArmConstants.MC1 * localDW->DiscreteTimeIntegrator1_DSTATE[5]
    * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  localB->D47 = localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->D48_tmp_o = rtP_ArmConstants.MC2 *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->D58 = localB->D48_tmp_o * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->d4 = localB->D46_tmp_d3 * localDW->DiscreteTimeIntegrator1_DSTATE[4] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  localB->D14_tmp_nb = localB->d23 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->d9 = localB->D46_tmp_lm * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->D16_tmp_m = localB->d9 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->d11 = localB->D58 * localB->D46_tmp_tmp_pc;
  localB->d13 = localB->D58 * localB->D56_tmp_tmp_o;
  localB->d19 = localB->D58 * localB->D46_tmp_tmp_c;
  localB->d21 = localB->D58 * localB->D56_tmp_tmp_h2;
  localB->d22 = localB->D16_tmp_m * localB->D14_tmp_cv;
  localB->D14_tmp_g = localB->D16_tmp_m * localB->D56_tmp_tmp_m;
  localB->x[52] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((localB->D38
    * localB->D46_tmp_tmp_a + localB->d10) + localB->D47 * localB->D46_tmp_tmp_a)
    + localB->tmp_tmp_c) + localB->D38 * localB->D27) + localB->D47 *
    localB->D27) - localB->tmp_tmp_b) + localB->tmp_tmp_e) + localB->tmp_tmp_dd)
    + localB->tmp_tmp_g) + localB->tmp_tmp_nn) + localB->d11) +
    localB->tmp_tmp_l) + localB->d13) + localB->tmp_tmp_nc) - localB->tmp_tmp_p)
    + localB->tmp_tmp_dk) + localB->tmp_tmp_oi) + localB->tmp_tmp_jr) +
    localB->d80) + localB->d81) + localB->d82) + localB->d83) + localB->D38 *
    localB->D46_tmp_tmp_fb) + localB->D47 * localB->D46_tmp_tmp_fb) +
    localB->d84) + localB->D38 * localB->D56_tmp_tmp_hc) + localB->D47 *
    localB->D56_tmp_tmp_hc) - localB->tmp_tmp_dv) + localB->tmp_tmp_jo) +
    localB->tmp_tmp_f1) + localB->d85) + localB->d86) + localB->d19) +
    localB->d87) + localB->d21) + localB->d88) - localB->tmp_tmp_js) +
    localB->tmp_tmp_ho) + localB->tmp_tmp_h) + localB->d4 * localB->D14_tmp) +
    localB->D14_tmp_nb * localB->D14_tmp) + localB->d89) + localB->d90) +
    localB->tmp_tmp_ji) + localB->tmp_tmp_oo) + localB->tmp_tmp_fr) +
    localB->tmp_tmp_oy) + localB->d4 * localB->D18) + localB->D14_tmp_nb *
                        localB->D18) + localB->d22) + localB->d91) + localB->d92)
                    + localB->d93) + localB->tmp_tmp_lu) + localB->tmp_tmp_gf) +
                 localB->tmp_tmp_d4) + localB->D14_tmp_g) + localB->tmp_tmp_i) +
              localB->d94) + localB->d95) + localB->d96) + localB->d97) +
          localB->d98) + localB->tmp_tmp_fa) + localB->d99) + localB->tmp_tmp_ln)
      * 0.25);
  localB->D48_tmp_o = localB->D48_tmp_o * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->d9 = localB->d9 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->x[60] = -((((((((((((((((((((((((((((((((((localB->d17 * 4.0 *
    rtP_ArmConstants.Inertia2[6] * localB->D15_tmp_m + localB->tmp_tmp_n) +
    localB->D48_tmp_o * localB->D46_tmp_tmp_k) + localB->d11) +
    localB->tmp_tmp_l) + localB->d13) + localB->D48_tmp_o *
    localB->D56_tmp_tmp_l) - localB->tmp_tmp_p) + localB->tmp_tmp_dk) +
    localB->tmp_tmp_oi) + localB->d80) + localB->d82) + localB->D48_tmp_o *
    localB->D46_tmp_tmp_b) + localB->d19) + localB->d87) + localB->d21) +
    localB->D48_tmp_o * localB->D56_tmp_tmp_p) - localB->tmp_tmp_js) +
    localB->tmp_tmp_ho) + localB->tmp_tmp_h) + localB->d9 * localB->D14_tmp_p) +
    localB->d22) + localB->d91) + localB->d92) + localB->d93) +
    localB->tmp_tmp_lu) + localB->tmp_tmp_gf) + localB->tmp_tmp_d4) +
    localB->D14_tmp_g) + localB->d9 * localB->D28) + localB->d96) + localB->d97)
                      + localB->d99) + localB->tmp_tmp_ln) * 0.25);
  localB->d10 = rtP_ArmConstants.Inertia2[7] * localB->D46_tmp_l;
  localB->d11 = rtP_ArmConstants.Inertia2[7] * localB->D46_tmp_d;
  localB->d13 = rtP_ArmConstants.Inertia2[6] * localB->D46_tmp_dy;
  localB->d17 = rtP_ArmConstants.Inertia2[6] * localB->D46_tmp_ln;
  localB->d19 = localB->D56_tmp_mc * localB->D46_tmp_bb;
  localB->d21 = localB->D46_tmp_tmp_d * localB->D46_tmp_a;
  localB->d22 = localB->D56_tmp_m * localB->D46_tmp_n;
  localB->D14_tmp_g = rtP_ArmConstants.Inertia2[0] * localB->D56_tmp_h;
  localB->D14_tmp_cz = (localB->d103 + localB->d10) - localB->d104;
  localB->d10 = (((((((((((rtP_ArmConstants.Inertia1[7] * localB->D46_tmp_p +
    localB->d101) + localB->d24) + localB->d10) - localB->D47_tmp_g) -
                       localB->d102) + rtP_ArmConstants.Inertia1[7] *
                      localB->D46_tmp_j) - localB->d38) + localB->d11) +
                   rtP_ArmConstants.Inertia1[6] * localB->D46_tmp_g) +
                  localB->d13) + rtP_ArmConstants.Inertia1[6] *
                 localB->D46_tmp_b) + localB->d17;
  localB->x[29] = -(((((((((((((((((((((localB->rtb_ginv_tmp_if -
    localB->tmp_tmp_f * localB->rtb_ginv_tmp) + localB->rtb_ginv_tmp_i) +
    rtP_ArmConstants.Inertia1[0] * localB->D46_tmp_bn) - localB->rtb_ginv_tmp_d)
    - localB->rtb_ginv_tmp_g) - localB->rtb_ginv_tmp_l) + localB->D46_tmp_kn *
    localB->D46_tmp_e) + localB->D46_tmp_mx * localB->D46_tmp_e) +
    localB->D47_tmp_f) + localB->rtb_ginv_tmp_o) + localB->D14) - localB->D24) -
    localB->D35) + localB->D46_tmp_pr * localB->rtb_ginv_tmp_j) + localB->d21) +
    localB->d22) + localB->d19) * localB->d23 + localB->D45 * localB->d100) +
                      (((localB->D56_tmp - localB->D14_tmp_g) +
                        localB->D56_tmp_c3) + localB->D56_tmp_cx) *
                      localDW->DiscreteTimeIntegrator1_DSTATE[5]) *
                     localB->D15_tmp + (((((-rtP_ArmConstants.MC2 *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 *
    localB->D46_tmp_tmp_c + localB->D14_tmp_cz) + localB->d11) + localB->d13) +
    localB->d17) * localB->tmp_tmp_j + localB->d10 * localB->tmp_tmp)) * 0.25);
  localB->tmp_tmp = 2.0 * localDW->DiscreteTimeIntegrator1_DSTATE[3];
  localB->tmp_tmp_f = localB->tmp_tmp * localB->D46_tmp_tmp_h;
  localB->D15_tmp_m = localB->tmp_tmp_d *
    localDW->DiscreteTimeIntegrator1_DSTATE[3];
  localB->D45 = 4.0 * rtP_ArmConstants.MC2;
  localB->D46_tmp_lm = localB->D45 * localDW->DiscreteTimeIntegrator1_DSTATE[3];
  localB->tmp_tmp_d = localB->d41 * localB->D46_tmp_tmp_h;
  localB->tmp_tmp_j = localB->tmp_tmp * rtP_HexaConstants.Inertia[4];
  localB->tmp_tmp_i = localB->tmp_tmp_ik * rtP_HexaConstants.Inertia[8];
  localB->tmp_tmp_h = localB->tmp_tmp_f * rtP_ArmConstants.Mass1;
  localB->tmp_tmp_f *= rtP_ArmConstants.Mass2;
  localB->tmp_tmp_n = localB->d12 * localB->D46_tmp_tmp_h;
  localB->D46_tmp_mj = localB->tmp_tmp_o *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  localB->D46_tmp_f = localB->d41 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->D46_tmp_cs = 4.0 * rtP_ArmConstants.MC1;
  localB->D46_tmp_k = localB->D46_tmp_cs *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  localB->D46_tmp_p4 = localB->d100 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->tmp_tmp_o = localB->tmp_tmp_ik * rtP_ArmConstants.Inertia1[0];
  localB->tmp_tmp_c = localB->tmp_tmp * rtP_ArmConstants.Inertia1[4];
  localB->tmp_tmp_b = localB->D14_tmp_i *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] * rtP_ArmConstants.Mass1;
  localB->tmp_tmp_e = localB->tmp_tmp * localB->D46_tmp_cn *
    rtP_ArmConstants.Mass2;
  localB->D46_tmp_d3 = localB->D15_tmp_m * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->D15_tmp_m = localB->D15_tmp_m * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->D47_tmp = localB->D46_tmp_lm * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->D46_tmp_lm = localB->D46_tmp_lm * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->tmp_tmp_dd = localB->D45 * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->tmp_tmp_ik *= rtP_ArmConstants.Inertia2[0];
  localB->tmp_tmp *= rtP_ArmConstants.Inertia2[4];
  localB->tmp_tmp_g = localB->d8 * localDW->DiscreteTimeIntegrator1_DSTATE[3] *
    rtP_ArmConstants.Mass2;
  localB->tmp_tmp_nn = localB->D16_tmp * rtP_ArmConstants.Inertia1[6];
  localB->tmp_tmp_l = localB->D16_tmp * rtP_ArmConstants.Inertia2[6];
  localB->tmp_tmp_nc = localB->D47_tmp_tmp * localB->rtb_ginv_tmp_j;
  localB->tmp_tmp_p = localB->d100 * rtP_ArmConstants.Inertia1[3];
  localB->tmp_tmp_dk = localB->d100 * rtP_ArmConstants.Inertia2[3];
  localB->tmp_tmp_oi = localB->d128 * rtP_ArmConstants.Inertia1[7];
  localB->tmp_tmp_jr = localB->d128 * rtP_ArmConstants.Inertia2[7];
  localB->D47_tmp_tmp = rtP_ArmConstants.Inertia1[0] -
    rtP_ArmConstants.Inertia1[4];
  localB->D56_tmp = localB->d15 * rtP_ArmConstants.Inertia1[3];
  localB->D56_tmp_mc = localB->d23 * rtP_ArmConstants.Inertia1[0];
  localB->D56_tmp_ap = localB->d12 * rtP_ArmConstants.Inertia1[4];
  localB->D56_tmp_jd = localB->D14_tmp_i *
    localDW->DiscreteTimeIntegrator1_DSTATE[4] * rtP_ArmConstants.Mass1;
  localB->rtb_ginv_tmp_j = localB->d12 * localB->D46_tmp_cn *
    rtP_ArmConstants.Mass2;
  localB->rtb_ginv_tmp = localB->d15 * rtP_ArmConstants.Inertia2[3];
  localB->rtb_ginv_tmp_i = localB->tmp_tmp_dd * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2;
  localB->rtb_ginv_tmp_o = localB->d23 * rtP_ArmConstants.Inertia2[0];
  localB->rtb_ginv_tmp_if = localB->d12 * rtP_ArmConstants.Inertia2[4];
  localB->rtb_ginv_tmp_d = localB->d8 * localDW->DiscreteTimeIntegrator1_DSTATE
    [4] * rtP_ArmConstants.Mass2;
  localB->rtb_ginv_tmp_g = localB->D46_tmp_mj * localB->D46_tmp_tmp_fb;
  localB->rtb_ginv_tmp_l = localB->D46_tmp_f * localB->D46_tmp_tmp_fb;
  localB->tmp_tmp_fa = localB->D56_tmp * localB->d;
  localB->tmp_tmp_ji = localB->D56_tmp_mc * localB->D56_tmp_a;
  localB->tmp_tmp_oo = localB->D56_tmp_ap * localB->D56_tmp_a;
  localB->tmp_tmp_fr = localB->D56_tmp_jd * localB->D56_tmp_a;
  localB->tmp_tmp_oy = localB->rtb_ginv_tmp_j * localB->D56_tmp_a;
  localB->tmp_tmp_ln = localB->D15_tmp_m * localB->D46_tmp_tmp_c;
  localB->tmp_tmp_lu = localB->rtb_ginv_tmp * localB->D46_tmp_tmp_g;
  localB->tmp_tmp_gf = localB->rtb_ginv_tmp_i * localB->D56_tmp_tmp_p;
  localB->tmp_tmp_d4 = localB->rtb_ginv_tmp_o * localB->D56_tmp_ju;
  localB->tmp_tmp_dv = localB->rtb_ginv_tmp_if * localB->D56_tmp_ju;
  localB->tmp_tmp_jo = localB->rtb_ginv_tmp_d * localB->D56_tmp_ju;
  localB->tmp_tmp_f1 = localB->d15 * rtP_ArmConstants.Inertia1[0];
  localB->tmp_tmp_js = localB->d15 * rtP_ArmConstants.Inertia2[0];
  localB->tmp_tmp_ho = localB->D46_tmp_d3 * localB->D46_tmp_tmp_b;
  localB->D46_tmp_mj *= localB->D46_tmp_tmp_a;
  localB->D46_tmp_f *= localB->D46_tmp_tmp_a;
  localB->D15_tmp_m *= localB->D46_tmp_tmp_pc;
  localB->D46_tmp_d3 *= localB->D46_tmp_tmp_k;
  localB->D46_tmp_tmp_g = localB->d48 * localB->D56_tmp_tmp;
  localB->d = localB->d162 * localB->D56_tmp_b;
  localB->D14_tmp_i = localB->D14_tmp_h * localB->D56_tmp_h;
  localB->d8 = localB->d49 * localB->D46_tmp_tmp_f;
  tmp =
    (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((((((((((((((((localB->tmp_tmp_nn *
    localB->rtb_ginv_tmp_tmp_n + localB->tmp_tmp_l * localB->D68) +
    localB->tmp_tmp_j * localB->D56_tmp_tmp_m4) + localB->d105) +
    localB->tmp_tmp_i * localB->D56_tmp_tmp_m4) + localB->d106) +
    localB->tmp_tmp_h * localB->D56_tmp_tmp_m4) + localB->d107) +
    localB->tmp_tmp_f * localB->D56_tmp_tmp_m4) + localB->d108) +
    localB->D46_tmp_mj) + localB->D46_tmp_f) + localB->d109) + localB->d110) +
    localB->D46_tmp_k * localB->D27) + localB->d111) + localB->D46_tmp_p4 *
    localB->D27) + localB->d112) + localB->tmp_tmp_o * localB->D56_tmp_j) +
    localB->d113) + localB->tmp_tmp_c * localB->D56_tmp_j) + localB->d114) +
    localB->tmp_tmp_b * localB->D56_tmp_j) + localB->d115) + localB->tmp_tmp_e *
    localB->D56_tmp_j) + localB->d116) + localB->D46_tmp_d3) + localB->D15_tmp_m)
    + localB->d117) + localB->d118) + localB->D47_tmp * localB->D56_tmp_tmp_o) +
    localB->d119) + localB->D46_tmp_lm * localB->D56_tmp_tmp_l) + localB->d120)
    + localB->tmp_tmp_ik * localB->D56_tmp_f) + localB->d121) + localB->tmp_tmp *
    localB->D56_tmp_f) + localB->d122) + localB->tmp_tmp_g * localB->D56_tmp_f)
    + localB->d123) + localB->d41 * rtP_ArmConstants.Inertia1[8] *
    localB->D15_tmp) + localB->d41 * rtP_ArmConstants.Inertia2[8] *
    localB->D15_tmp) + localB->d41 * rtP_HexaConstants.Inertia[0] *
    localB->D15_tmp) + localB->D46_tmp_m *
    localDW->DiscreteTimeIntegrator1_DSTATE[3] * rtP_ArmConstants.Mass1 *
    localB->D15_tmp) + localB->tmp_tmp_d * rtP_ArmConstants.Mass1 *
    localB->D15_tmp) + localB->d124 * localDW->DiscreteTimeIntegrator1_DSTATE[3]
    * rtP_ArmConstants.Mass2 * localB->D15_tmp) + localB->tmp_tmp_d *
    rtP_ArmConstants.Mass2 * localB->D15_tmp) + localB->d41 * localB->D46_tmp_cn
    * rtP_ArmConstants.Mass2 * localB->D15_tmp) + localB->tmp_tmp_j *
    localB->D56_tmp_tmp_c) + localB->d12 * rtP_HexaConstants.Inertia[4] *
    localB->D56_tmp_tmp_c) + localB->tmp_tmp_i * localB->D56_tmp_tmp_c) +
    localB->d23 * rtP_HexaConstants.Inertia[8] * localB->D56_tmp_tmp_c) +
    localB->tmp_tmp_h * localB->D56_tmp_tmp_c) + localB->tmp_tmp_n *
    rtP_ArmConstants.Mass1 * localB->D56_tmp_tmp_c) + localB->tmp_tmp_f *
    localB->D56_tmp_tmp_c) + localB->tmp_tmp_n * rtP_ArmConstants.Mass2 *
    localB->D56_tmp_tmp_c) + localB->rtb_ginv_tmp_g) + localB->rtb_ginv_tmp_l) +
    localB->d125 * localB->D46_tmp_j) + localB->tmp_tmp_fa) + localB->D46_tmp_k *
    localB->D56_tmp_tmp_hc) + localB->D46_tmp_cs *
    localDW->DiscreteTimeIntegrator1_DSTATE[4] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1 *
    localB->D56_tmp_tmp_hc) + localB->D46_tmp_p4 * localB->D56_tmp_tmp_hc) +
    localB->d32 * rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * localB->D56_tmp_tmp_hc) + localB->tmp_tmp_o *
    localB->D56_tmp_a) + localB->tmp_tmp_ji) + localB->tmp_tmp_c *
    localB->D56_tmp_a) + localB->tmp_tmp_oo) + localB->tmp_tmp_b *
    localB->D56_tmp_a) + localB->tmp_tmp_fr) + localB->tmp_tmp_e *
    localB->D56_tmp_a) + localB->tmp_tmp_oy) + localB->tmp_tmp_ho) +
    localB->tmp_tmp_ln) + localB->d126 * localB->D46_tmp_d) + localB->tmp_tmp_lu)
    + localB->D47_tmp * localB->D56_tmp_tmp_h2) + localB->tmp_tmp_dd *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 *
    localB->D56_tmp_tmp_h2) + localB->D46_tmp_lm * localB->D56_tmp_tmp_p) +
    localB->tmp_tmp_gf) + localB->tmp_tmp_ik * localB->D56_tmp_ju) +
    localB->tmp_tmp_d4) + localB->tmp_tmp * localB->D56_tmp_ju) +
    localB->tmp_tmp_dv) + localB->tmp_tmp_g * localB->D56_tmp_ju) +
    localB->tmp_tmp_jo) + localB->tmp_tmp_nn * localB->d1) + localB->tmp_tmp_l *
    localB->d2) + ((((((localB->D48 + localB->D14) - localB->D24) - localB->D35)
    - localB->tmp_tmp_nc) - localB->D48_tmp * localB->D46_tmp_a) + localB->d19) *
    (localB->D14_tmp_b * localB->D15_tmp)) + ((((((((((((((localB->D47_tmp_tmp -
    localB->D47_tmp_p) - localB->D47_tmp_px) * localB->D46_tmp_bn +
    localB->D47_tmp_c) + localB->d27 * localB->D46_tmp_e) - localB->D24_tmp_i *
    localB->D46_tmp_e) + localB->D47_tmp_f) + localB->D46_tmp_o) + localB->D14)
    - localB->D24) - localB->D35) - localB->tmp_tmp_nc) + localB->d21) +
    localB->d22) + localB->d19) * (localB->d14 * localB->D15_tmp)) +
    localB->d127) + localB->d42 * localB->d3) + localB->d43 * localB->d3) +
    localB->tmp_tmp_oi * localB->ab_a) + localB->d129) + localB->d130) +
    localB->d35 * localB->d6) + localB->d44 * localB->D37) + localB->tmp_tmp_jr *
    localB->D67) + localB->d131) + localB->d132) + localB->d133) + localB->d134)
    - localB->d135) - localB->d136) - localB->d137) + localB->tmp_tmp_p *
    localB->D56_tmp_d) + localB->d138) + localB->d139) + localB->d140) -
                     localB->d141) - localB->d142) + localB->tmp_tmp_dk *
                   localB->D56_tmp_lx) + localB->d143) + localB->tmp_tmp_f1 *
                 localB->D46_tmp_pb) + localB->d144 * localB->D46_tmp_pb) +
               localB->D16_tmp * rtP_ArmConstants.Inertia1[8] *
               localB->D46_tmp_pb) + localB->tmp_tmp_js * localB->D46_tmp_pb) +
             localB->d145 * localB->D46_tmp_pb) + localB->D16_tmp *
            rtP_ArmConstants.Inertia2[8] * localB->D46_tmp_pb) + localB->D16_tmp
           * rtP_HexaConstants.Inertia[0] * localB->D46_tmp_pb) + localB->d146 *
          localB->D46_tmp_pb) + localB->d15 * rtP_HexaConstants.Inertia[8] *
         localB->D46_tmp_pb) + localB->d147 * localB->D46_tmp_pb) + localB->d148
       * localB->D46_tmp_pb) + localB->d149 * localB->D46_tmp_pb) + localB->d40 *
     localB->D46_tmp_pb) + localB->d150 * localB->D46_tmp_pb;
  localB->x[37] = -(((((((((((((((((((((((((((((((tmp + localB->d151) +
    localB->d152) + localB->d153) + localB->d154) - localB->d155) + localB->d156)
    + localB->d157) + localB->d158 * localB->D46_tmp_b) - localB->d159) +
    localB->d160) + localB->d161) + localB->D46_tmp_tmp_g) + localB->tmp_tmp_p *
    localB->D56_tmp_b) + localB->d) + localB->d163 * localB->D46_tmp_ln) -
    localB->d164) + localB->d165) + localB->d166) + localB->tmp_tmp_dk *
    localB->D56_tmp_h) + localB->D14_tmp_i) + localB->d46 * localB->d5) +
    localB->d33 * localB->d5) + localB->tmp_tmp_oi * localB->D15_tmp_tmp) +
    localB->d49 * localB->d7) + localB->d34 * localB->D14_tmp_tmp) +
    localB->tmp_tmp_jr * localB->D15_tmp_tmp_i) + localB->d46 * localB->y_a) +
                       localB->d33 * localB->y_a) + localB->d34 *
                      localB->D48_tmp_tmp) + localB->d8) * 0.125);
  localB->D56_tmp_tmp_c = localB->D46_tmp_fi * localB->rtb_ginv_tmp_tmp;
  localB->D56_tmp_tmp_m4 = -2.0 * localB->rtb_ginv_tmp_tmp * localB->D14_tmp_k;
  localB->rtb_ginv_tmp_tmp = rtP_ArmConstants.MC1 * localB->D15_tmp_g +
    localB->D24_tmp_c;
  localB->tmp_tmp = rtP_ArmConstants.Hexa_to_joint_L * localB->D14_tmp_k;
  localB->D16_tmp = -2.0 * rtP_ArmConstants.Mass1;
  localB->d14 = -2.0 * rtP_ArmConstants.Mass2;
  localB->d15 = 4.0 * localB->D14_tmp_cx;
  localB->D14_tmp_b = ((rtP_ArmConstants.l1_dim * localB->D17_tmp_a +
                        localB->tmp_tmp) + rtP_ArmConstants.MC2 *
                       localB->D17_tmp_l) * localB->s - localB->D24_tmp_h *
    localB->smax * localB->D14_tmp_c;
  localB->d19 = 4.0 * rtP_ArmConstants.Mass2;
  localB->d21 = localB->D16 * -2.0;
  localB->d22 = localB->D25 * localB->D56_tmp_tmp_tmp + localB->D47_tmp_tmp *
    localB->D46_tmp_ex;
  localB->tmp_tmp_ik = localB->d15 * localB->D17_tmp_e * localB->D14_tmp_k *
    (localB->rtb_ginv_tmp_tmp_p + localB->rtb_ginv_tmp_tmp_pi);
  localB->tmp_tmp_f = (localB->D45_tmp_e * 2.0 * localB->D46_tmp_ch + 4.0 *
                       rtP_ArmConstants.Inertia2[3] * localB->D46_tmp_h) *
    localB->rtb_ginv_tmp_c;
  localB->tmp_tmp_o = (localB->D34 * 2.0 * localB->D46_tmp_ch + -4.0 *
                       rtP_ArmConstants.Inertia2[3] * localB->D46_tmp_h) *
    localB->rtb_ginv_tmp_a;
  localB->tmp_tmp_j = localB->D14_tmp_b * localB->d19;
  localB->tmp_tmp = (rtP_ArmConstants.MC1 * localB->D17_tmp_a + localB->tmp_tmp)
    * localB->s;
  localB->tmp_tmp_d = localB->D46_tmp_dau * localB->D14_tmp_my *
    localB->D46_tmp_pb;
  localB->tmp_tmp_i = localB->D46_tmp_af * localB->d167 * localB->D46_tmp_pb;
  localB->x[45] = -((((((((((((((((((((localB->D47_tmp_tmp * localB->D14_tmp_f *
    localB->D14_tmp + rtP_ArmConstants.Inertia1[3] * localB->D56_tmp_tmp_tmp) *
    (localB->d15 * localB->D15_tmp * localB->D14_tmp_k) * localB->D14_tmp_c +
    (((localB->D56_tmp_tmp_c * localB->D46_tmp_ei + localB->D56_tmp_tmp_m4 *
    localB->D46_tmp_ax) + localB->D56_tmp_tmp_c * localB->D46_tmp_dau) +
    localB->D56_tmp_tmp_m4 * localB->D46_tmp_af)) + ((localB->D56_tmp_m *
    localB->D14_tmp_f * localB->D14_tmp + localB->D46_tmp_bj) +
    localB->D46_tmp_da) * (localB->d21 * localB->D15_tmp) * localB->D14_tmp_c) +
    -2.0 * localB->D15_tmp * localB->D56 * localB->D26 * localB->D14_tmp_c) -
    localB->D16 * localB->D15_tmp * localB->D46 * localB->D14_tmp_c) -
    localB->D56 * localB->D15_tmp * localB->D47_tmp_pe * localB->D14_tmp_c) +
    localB->D46_tmp_fi * localB->D15_tmp * localB->D14_tmp_k * (localB->D15 *
    localB->D46_tmp_h + localB->D45_tmp_e * localB->D46_tmp_ch) *
    localB->D14_tmp_c) + localB->rtb_ginv_tmp_tmp * localB->D16_tmp *
    localB->D15_tmp * localB->smax * (localB->tmp_tmp - localB->rtb_ginv_tmp_tmp
    * localB->smax * localB->D14_tmp_c)) + localB->D24_tmp_h * localB->d14 *
    localB->D15_tmp * localB->smax * localB->D14_tmp_b) + localB->D16_tmp *
    localB->s * localB->rtb_ginv_tmp_tmp * localB->D15_tmp * localB->D45_tmp) +
    localB->d14 * localB->s * localB->D24_tmp_h * localB->D15_tmp *
    localB->D24_tmp_o) + rtP_ArmConstants.Inertia1[8] * localB->D46_tmp_pb) +
    rtP_ArmConstants.Inertia2[8] * localB->D46_tmp_pb) +
    rtP_HexaConstants.Inertia[0] * localB->D46_tmp_pb) - localB->rtb_ginv_tmp_da
    * localB->D46_tmp_pb) - localB->D56 * rtP_HexaConstants.Inertia[4] *
                        localB->D46_tmp_pb) * localB->d12 +
                       ((((((localB->tmp_tmp_f + localB->tmp_tmp_ik) +
    localB->tmp_tmp_o) + localB->D18_tmp * localB->d19 * localB->D24_tmp_o) +
    localB->tmp_tmp_j * localB->D17_tmp_p) + localB->tmp_tmp_d) +
                        localB->tmp_tmp_i) *
                       localDW->DiscreteTimeIntegrator1_DSTATE[7]) +
                      (((((((((((((localB->D17_tmp_e * -2.0 * localB->D17 *
    (localB->D47_tmp_tmp * localB->D56_tmp_tmp_tmp + localB->D56_tmp_m *
     localB->D46_tmp_ex) + localB->d21 * localB->D17_tmp_e * localB->d22) +
    localB->D17_tmp_e * 2.0 * localB->D56 * localB->d22) + localB->tmp_tmp_ik) +
    localB->tmp_tmp_f) + localB->tmp_tmp_o) + (localB->D17_tmp *
    localB->D17_tmp_ax + localB->D17_tmp_p5 * localB->D17_tmp_o) * localB->d19 *
    localB->D24_tmp_o) + (localB->D17_tmp_tmp_o2 * -localB->D17_tmp_ax +
    localB->D17_tmp_tmp_o * localB->D17_tmp_o) * localB->tmp_tmp_j) +
    localB->D46_tmp_cs * rtP_ArmConstants.Mass1 * localB->D45_tmp *
    (localB->D17_tmp_j * localB->D14_tmp_k + localB->D17_tmp_pi *
     localB->D14_tmp_cx)) + ((localB->D14_tmp_f * localB->smax *
    localB->D14_tmp_c + -localB->s * localB->D14_tmp) * (rtP_ArmConstants.MC1 *
    localB->D14_tmp_k) + (localB->D17_tmp_tmp_ob * localB->D14_tmp_c +
    localB->D17_tmp_tmp_l) * (rtP_ArmConstants.MC1 * localB->D14_tmp_cx)) *
    ((-localB->rtb_ginv_tmp_tmp * localB->smax * localB->D14_tmp_c +
      localB->tmp_tmp) * (4.0 * rtP_ArmConstants.Mass1))) + localB->D46_tmp_ei *
    localB->D14_tmp_my * localB->D46_tmp_pb) + localB->D46_tmp_ax * localB->d167
    * localB->D46_tmp_pb) + localB->tmp_tmp_d) + localB->tmp_tmp_i) *
                      localDW->DiscreteTimeIntegrator1_DSTATE[6]) -
                     (((((((((((((((((((((((((((((((((((((((((localB->D56_tmp_oyh
    * localB->D46_tmp_p + localB->D25 * localB->D56_tmp_j) + localB->D56_tmp_g *
    localB->D46_tmp_l) + localB->D15 * localB->D56_tmp_f) + localB->D56_tmp_c *
    localB->D46_tmp_j) + localB->D25 * localB->D56_tmp_a) + localB->D56_tmp_cj *
    localB->D46_tmp_d) + localB->D15 * localB->D56_tmp_ju) -
    localB->D56_tmp_tmp_k) + localB->D56_tmp_tmp_j) - localB->D56_tmp_tmp_f) -
    localB->D56_tmp_tmp_cm) + localB->D56_tmp_k * localB->D46_tmp_g) +
    localB->D46_tmp_kn * localB->D56_tmp_l) + localB->D46_tmp_mx *
    localB->D56_tmp_l) + localB->D56_tmp_tmp_fq) - localB->D56_tmp_tmp_n) -
    localB->D56_tmp_tmp_i) - localB->D56_tmp_tmp_l4) + localB->D56_tmp_n3 *
    localB->D46_tmp_dy) + localB->D46_tmp_pr * localB->D56_tmp_o4) +
    localB->D46_tmp_tmp_d * localB->D56_tmp_ny) + localB->D56_tmp_tmp_i3) -
    localB->D56_tmp_tmp_k1) - localB->D56_tmp_tmp_fc) - localB->D56_tmp_tmp_a) +
    localB->D56_tmp_tmp_d) - localB->D56_tmp_tmp_ey) + -localB->D46_tmp_tmp_h *
    rtP_ArmConstants.Mass2 * localB->D56_tmp_o) + localB->D56_tmp_p *
    localB->D46_tmp_b) + localB->D46_tmp_kn * localB->D56_tmp_n) +
    localB->D46_tmp_mx * localB->D56_tmp_n) + localB->D56_tmp_tmp_eh) -
    localB->D56_tmp_tmp_b) - localB->D56_tmp_tmp_a0) - localB->D56_tmp_tmp_il) +
    localB->D56_tmp_nj * localB->D46_tmp_ln) + localB->D46_tmp_pr *
    localB->D56_tmp_i) + localB->D46_tmp_tmp_d * localB->D56_tmp_oy) +
                        localB->D14_tmp_g) - localB->D56_tmp_c3) -
                      localB->D56_tmp_cx) * localB->D16_tmp_j) * 0.25);
  localB->D17 = localB->d100 * rtP_ArmConstants.Inertia1[7];
  localB->D56_tmp_tmp_c = localB->D46_tmp_tmp_n *
    localDW->DiscreteTimeIntegrator1_DSTATE[4] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1;
  localB->D56_tmp_tmp_m4 = localB->d12 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->rtb_ginv_tmp_tmp = localB->d100 * rtP_ArmConstants.Inertia2[7];
  localB->d167 = localB->D46_tmp_c * localDW->DiscreteTimeIntegrator1_DSTATE[4];
  localB->D16_tmp_j = localB->d167 * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2;
  localB->tmp_tmp = localB->d100 * rtP_ArmConstants.Inertia1[6];
  localB->D14_tmp_my = localB->d128 * rtP_ArmConstants.Inertia2[3] *
    localB->D46_tmp_tmp_m;
  localB->D68 *= localB->d56;
  localB->D16_tmp = localB->D47_tmp * localB->D46_tmp_tmp_pc;
  localB->D46_tmp_tmp_pc *= localB->D16_tmp_m;
  localB->d14 = localB->rtb_ginv_tmp_tmp * localB->D46_tmp_l;
  localB->D46_tmp_tmp_i *= localB->rtb_ginv_tmp;
  localB->D56_tmp_tmp_o *= localB->D16_tmp_j;
  localB->d15 = localB->rtb_ginv_tmp_o * localB->D56_tmp_f;
  localB->D14_tmp_b = localB->rtb_ginv_tmp_if * localB->D56_tmp_f;
  localB->d19 = localB->rtb_ginv_tmp_d * localB->D56_tmp_f;
  localB->D16_tmp_m *= localB->D46_tmp_tmp_c;
  localB->rtb_ginv_tmp_tmp *= localB->D46_tmp_d;
  localB->D56_tmp_tmp_h2 *= localB->D16_tmp_j;
  localB->d2 *= localB->d54;
  localB->D16_tmp_j = -6.0 * rtP_ArmConstants.MC2 *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->d21 = localB->D16_tmp_j * rtP_ArmConstants.Hexa_to_joint_L *
    rtP_ArmConstants.Mass2 * localB->D14_tmp_cv;
  localB->d22 = localB->tmp_tmp_js * localB->D46_tmp_bb;
  localB->tmp_tmp_ik = localB->D16_tmp_m0 * rtP_ArmConstants.Inertia2[4] *
    localB->D46_tmp_bb;
  localB->D14_tmp_g = localB->d149 * localB->D46_tmp_bb;
  localB->tmp_tmp_f = localB->d34 * localB->D56_tmp_tmp_m;
  localB->D37 *= localB->D58;
  localB->D67 *= localB->d50;
  localB->D56_tmp_tmp_h *= localB->D58;
  localB->tmp_tmp_o = localB->d175 * localB->D46_tmp_dy;
  localB->tmp_tmp_j = localB->D14_tmp_h * localB->D56_tmp_lx;
  localB->tmp_tmp_d = localB->d175 * localB->D46_tmp_ln;
  localB->d11 = (((localB->D14_tmp_cz - localB->d38) + localB->d11) +
                 localB->d13) + localB->d17;
  localB->d13 = localB->d11 * localB->d176;
  localB->D14_tmp_tmp *= localB->D58;
  localB->D15_tmp_tmp_i *= localB->d52;
  localB->D58 *= localB->D48_tmp_tmp;
  localB->d17 = localB->D38 * localB->d3;
  localB->d3 *= localB->D47;
  localB->D14_tmp_cz = localB->D38 * localB->D56_tmp_tmp_e;
  localB->D56_tmp_tmp_e *= localB->D47;
  localB->tmp_tmp_i = localB->D38 * localB->d5;
  localB->d5 *= localB->D47;
  localB->D38 *= localB->y_a;
  localB->D47 *= localB->y_a;
  localB->x[53] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((localB->d128 * rtP_ArmConstants.Inertia1
    [3] * localB->D46_tmp_bn + localB->D14_tmp_my) + localB->d55 *
    localB->rtb_ginv_tmp_tmp_n) + localB->D68) + localB->D46_tmp_k *
    localB->D46_tmp_tmp_a) + localB->d4 * localB->D46_tmp_tmp_a) +
    localB->D46_tmp_p4 * localB->D46_tmp_tmp_a) + localB->D14_tmp_nb *
    localB->D46_tmp_tmp_a) + localB->D17 * localB->D46_tmp_p) + localB->D56_tmp *
    localB->rtb_ginv_tmp_k) + localB->D56_tmp_tmp_c * localB->D27) +
    localB->D56_tmp_tmp_m4 * localB->D27) + localB->D56_tmp_mc *
    localB->D56_tmp_j) + localB->D56_tmp_ap * localB->D56_tmp_j) +
    localB->D56_tmp_jd * localB->D56_tmp_j) + localB->rtb_ginv_tmp_j *
    localB->D56_tmp_j) + localB->d168) + localB->D16_tmp) +
    localB->D46_tmp_tmp_pc) + localB->d14) + localB->D46_tmp_tmp_i) +
    localB->D56_tmp_tmp_o) + localB->rtb_ginv_tmp_i * localB->D56_tmp_tmp_l) +
    localB->d15) + localB->D14_tmp_b) + localB->d19) + localB->d169) +
    localB->d170) + localB->d171) + localB->d172) + localB->d173) +
    localB->rtb_ginv_tmp_g) + localB->d4 * localB->D46_tmp_tmp_fb) +
    localB->rtb_ginv_tmp_l) + localB->D14_tmp_nb * localB->D46_tmp_tmp_fb) +
    localB->D17 * localB->D46_tmp_j) + localB->tmp_tmp_fa) +
    localB->D56_tmp_tmp_c * localB->D56_tmp_tmp_hc) + localB->D56_tmp_tmp_m4 *
    localB->D56_tmp_tmp_hc) + localB->tmp_tmp_ji) + localB->tmp_tmp_oo) +
    localB->tmp_tmp_fr) + localB->tmp_tmp_oy) + localB->d174) +
    localB->tmp_tmp_ln) + localB->D16_tmp_m) + localB->rtb_ginv_tmp_tmp) +
    localB->tmp_tmp_lu) + localB->D56_tmp_tmp_h2) + localB->tmp_tmp_gf) +
    localB->tmp_tmp_d4) + localB->tmp_tmp_dv) + localB->tmp_tmp_jo) +
    localB->d53 * localB->d1) + localB->d2) + -6.0 * rtP_ArmConstants.MC1 *
    localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1 * localB->D14_tmp)
    + -6.0 * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * localB->D14_tmp) + localB->tmp_tmp_f1 *
    localB->D46_tmp_n) + localB->D16_tmp_m0 * rtP_ArmConstants.Inertia1[4] *
    localB->D46_tmp_n) + localB->d147 * localB->D46_tmp_n) + localB->d150 *
    localB->D46_tmp_n) + localB->d46 * localB->D18) + localB->d33 * localB->D18)
    + localB->d21) + localB->d22) + localB->tmp_tmp_ik) + localB->D14_tmp_g) +
    localB->tmp_tmp_f) + localB->D45 * localDW->DiscreteTimeIntegrator1_DSTATE[5]
    * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D28) +
    localB->d49 * localB->D46_tmp_tmp) + localB->d17) + localB->d3) +
    localB->d47 * localB->ab_a) + localB->D14_tmp_cz) + localB->D56_tmp_tmp_e) +
    localB->D37) + localB->D67) + localB->D56_tmp_tmp_h) + localB->tmp_tmp *
    localB->D46_tmp_g) - localB->d134) + localB->d135) + localB->d136) +
    localB->d137) + localB->d162 * localB->D56_tmp_d) + localB->tmp_tmp_o) +
    -localDW->DiscreteTimeIntegrator1_DSTATE[5] * rtP_ArmConstants.Inertia2[0] *
    localB->D47_tmp_o) + localB->d141) + localB->d142) + localB->tmp_tmp_j) +
    localB->tmp_tmp * localB->D46_tmp_b) +
    -localDW->DiscreteTimeIntegrator1_DSTATE[5] * rtP_ArmConstants.Inertia1[0] *
    localB->D56_tmp_tmp) + localB->d160) + localB->d161) + localB->D46_tmp_tmp_g)
                       + localB->d) + localB->tmp_tmp_d) + localB->d13) +
                    localB->d10 * localB->d177) - localB->d164) + localB->d165)
                 + localB->d166) + localB->D14_tmp_i) + localB->tmp_tmp_i) +
              localB->d5) + localB->d51 * localB->D15_tmp_tmp) +
            localB->D14_tmp_tmp) + localB->D15_tmp_tmp_i) + localB->D38) +
         localB->D47) + localB->D58) + localB->d8) * 0.125);
  localB->D17 = localB->d167 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2;
  localB->D27 = localB->D48_tmp_o * localB->D46_tmp_tmp;
  localB->D56_tmp_tmp_c = localB->D48_tmp_o * localB->d6;
  localB->D56_tmp_tmp_hc = localB->D48_tmp_o * localB->d7;
  localB->D56_tmp_tmp_m4 = localB->D48_tmp_o * localB->D46_tmp_tmp_f;
  localB->x[61] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((localB->D46_tmp_lm *
    localB->D46_tmp_tmp_k + (localB->D14_tmp_my + localB->D68)) + localB->d9 *
    localB->D46_tmp_tmp_k) + localB->D16_tmp) + localB->D46_tmp_tmp_pc) +
    localB->d14) + localB->D46_tmp_tmp_i) + localB->D56_tmp_tmp_o) + localB->D17
    * localB->D56_tmp_tmp_l) + localB->d15) + localB->D14_tmp_b) + localB->d19)
    + localB->d170) + localB->d172) + localB->tmp_tmp_ho) + localB->d9 *
    localB->D46_tmp_tmp_b) + localB->tmp_tmp_ln) + localB->D16_tmp_m) +
    localB->rtb_ginv_tmp_tmp) + localB->tmp_tmp_lu) + localB->D56_tmp_tmp_h2) +
    localB->D17 * localB->D56_tmp_tmp_p) + localB->tmp_tmp_d4) +
    localB->tmp_tmp_dv) + localB->tmp_tmp_jo) + localB->d2) + localB->D16_tmp_j *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D14_tmp_p) +
    localB->d21) + localB->d22) + localB->tmp_tmp_ik) + localB->D14_tmp_g) +
    localB->tmp_tmp_f) + localB->d49 * localB->D28) + localB->D27) +
    localB->D56_tmp_tmp_c) + localB->D37) + localB->D67) + localB->D56_tmp_tmp_h)
                       + localB->tmp_tmp_o) - localB->d140) + localB->d141) +
                    localB->d142) + localB->tmp_tmp_j) + localB->tmp_tmp_d) +
                 localB->d11 * localB->d177) + localB->d13) - localB->d164) +
              localB->d165) + localB->d166) + localB->D14_tmp_i) +
           localB->D56_tmp_tmp_hc) + localB->D14_tmp_tmp) +
         localB->D15_tmp_tmp_i) + localB->D58) + localB->D56_tmp_tmp_m4) * 0.125);
  localB->D17 = localB->d28 * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 *
    localB->D14_tmp_p;
  localB->D46_tmp_tmp_a = localDW->DiscreteTimeIntegrator1_DSTATE[3] -
    localB->D17_tmp_tmp;
  localB->x[30] = -(localB->d25 * localB->D46_tmp_tmp_a + localB->D17);
  localB->x[38] = -((((((((((((((((localB->rtb_ginv_tmp_tmp_l + localB->d29) +
    localB->D24_tmp_i * localB->D14_tmp) - localB->D16_tmp_f) + localB->d20) +
    localB->D14_tmp_md) + localB->D17_tmp_tmp_a) + localB->D24_tmp * localB->D18)
    + localB->d30) + localB->d31) - localB->D14_tmp_e) + localB->D27_tmp) +
                        localB->D27_tmp_g) + localB->d36) + localB->d178) *
                     localB->d12 - localB->D14_tmp_j *
                     localDW->DiscreteTimeIntegrator1_DSTATE[5]) * 0.25);
  localB->D46_tmp_tmp_k = localB->D47_tmp * localB->D46_tmp_tmp_c;
  localB->D46_tmp_tmp_pc = 6.0 * rtP_ArmConstants.MC2 *
    localDW->DiscreteTimeIntegrator1_DSTATE[5];
  localB->D56_tmp_tmp_o = localB->D46_tmp_tmp_pc *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 *
    localB->D14_tmp_cv;
  localB->D56_tmp_tmp_l = localB->d44 * localB->D56_tmp_tmp_m;
  localB->x[46] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((localB->d179 +
    localB->D46_tmp_mj) + localB->D46_tmp_f) + localB->d110) + localB->D15_tmp_m)
    + localB->d118) + localB->D46_tmp_k * localB->D46_tmp_tmp_fb) +
    localB->D46_tmp_p4 * localB->D46_tmp_tmp_fb) + localB->d180) +
    localB->D46_tmp_tmp_k) + localB->d181) + localB->d182) + localB->d183) + 6.0
    * rtP_ArmConstants.MC1 * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass1 * localB->D14_tmp)
    + 6.0 * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
    rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.l1_dim *
    rtP_ArmConstants.Mass2 * localB->D14_tmp) + localB->d184) + localB->d185) +
    localB->D46_tmp_tmp_m1) + localB->d186) + localB->d42 * localB->D18) +
    localB->d43 * localB->D18) + localB->D56_tmp_tmp_o) + localB->d187) +
    localB->d188) + localB->D46_tmp_tmp_j) + localB->D56_tmp_tmp_l) +
    localB->d189) + localB->d127) - localB->d17) - localB->d3) + localB->d190) -
    localB->D14_tmp_cz) - localB->D56_tmp_tmp_e) - localB->D37) + localB->d191)
    - localB->D56_tmp_tmp_h) + localB->d134) - localB->d135) - localB->d136) -
    localB->d137) + localB->d140) - localB->d141) - localB->d142) + localB->d192
                        * rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 *
                        localB->D14_tmp_p * localB->D14_tmp_c) + localB->d159) -
                      localB->d160) - localB->d161) - localB->D46_tmp_tmp_g) +
                   localB->d164) - localB->d165) - localB->d166) +
                ((((((((((((((((((((((((((((((((((((((((((-rtP_ArmConstants.Inertia1
    [0] * localB->D56_tmp_j + localB->D14_tmp_m3) + localB->D14_tmp_tmp_f) +
    localB->D14_tmp_tmp_p) + localB->D14_tmp_c0) + localB->D15_tmp_tmp_n) +
    localB->d24) + localB->D15_tmp_tmp_c) + localB->d26) + localB->D16_tmp_tmp)
    - localB->D34_tmp_j) + localB->D37_tmp) + localB->D46_tmp_tmp_p) +
    localB->rtb_ginv_tmp_ie) + localB->d57) + localB->d58) + localB->d59) +
    localB->d60) + localB->D47_tmp_g) + localB->d102) + localB->d61) +
    localB->d193) + localB->d194) - localB->d62) + localB->d63) + localB->d64) +
    localB->d65) + localB->d66) + localB->d38) + localB->d67) + localB->d39) +
    localB->d68) - localB->d69) + localB->d70) + localB->d71) + localB->d72) +
                       localB->d73) + localB->d74) + localB->d75) + localB->d76)
                   + localB->d77) + localB->d78) + localB->d79) * localB->d23) -
               localB->tmp_tmp_i) - localB->d5) + localB->d195) -
            localB->D14_tmp_tmp) + localB->d196) - localB->D38) - localB->D47) -
        localB->D58) + localB->d197) * 0.125);
  localB->x[54] = -localB->D17;
  localB->x[62] = -(localB->D46_tmp * localB->D14_tmp_p * localB->d18);
  localB->x[31] = -((localDW->DiscreteTimeIntegrator1_DSTATE[6] *
                     rtP_ArmConstants.l1_dim * localB->D14_tmp_p + localB->d45 *
                     localB->D46_tmp_tmp_a) * localB->D14_tmp_n);
  localB->x[39] = -((localB->d37 * localDW->DiscreteTimeIntegrator1_DSTATE[4] *
                     localB->D17_tmp_l +
                     -localDW->DiscreteTimeIntegrator1_DSTATE[4] *
                     rtP_ArmConstants.Inertia2[3] * localB->D46_tmp_tmp_m) +
                    -0.25 * localDW->DiscreteTimeIntegrator1_DSTATE[5] *
                    localB->d198);
  localB->x[47] = -((((((((((((((((((((((((((((((((((localB->d199 + localB->d200)
    + localB->D46_tmp_d3) + localB->D15_tmp_m) + localB->d118) +
    localB->D46_tmp_lm * localB->D46_tmp_tmp_b) + localB->D46_tmp_tmp_k) +
    localB->d181) + localB->d183) + localB->D46_tmp_tmp_pc *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D14_tmp_p) +
    localB->D56_tmp_tmp_o) + localB->d187) + localB->d188) +
    localB->D46_tmp_tmp_j) + localB->D56_tmp_tmp_l) + localB->d35 * localB->D28)
    - localB->D27) - localB->D56_tmp_tmp_c) - localB->D37) + localB->d191) -
    localB->D56_tmp_tmp_h) + localB->d140) - localB->d141) - localB->d142) +
    -8.0 * rtP_ArmConstants.MC2 * localDW->DiscreteTimeIntegrator1_DSTATE[6] *
    rtP_ArmConstants.l1_dim * rtP_ArmConstants.Mass2 * localB->D14_tmp_p *
    localB->D14_tmp_c) + localB->d164) - localB->d165) - localB->d166) +
    localB->d198 * localB->d23) - localB->D56_tmp_tmp_hc) - localB->D14_tmp_tmp)
                       + localB->d196) + -rtP_ArmConstants.MC2 *
                      localDW->DiscreteTimeIntegrator1_DSTATE[5] *
                      rtP_ArmConstants.Hexa_to_joint_L * rtP_ArmConstants.Mass2 *
                      localB->D48_tmp_tmp) - localB->D56_tmp_tmp_m4) * 0.125);
  localB->x[55] = -(localB->D48_tmp * localB->D14_tmp_p * localB->d16);
  localB->x[63] = -0.0;
  memset(&localB->x[0], 0, 24U * sizeof(real_T));
  memset(&localB->e_hat[0], 0, sizeof(real_T) << 3U);
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    localB->D17 = localDW->DiscreteTimeIntegrator1_DSTATE[localB->c_j];
    for (localB->jj = 0; localB->jj < 8; localB->jj++) {
      localB->e_hat[localB->jj] += localB->x[(localB->c_j << 3) + localB->jj] *
        localB->D17;
    }
  }

  localB->rtb_Product3_tmp[0] = 0.0;
  localB->rtb_Product3_tmp[1] = 0.0;
  localB->rtb_Product3_tmp[2] = localB->D46_tmp_g2 * 9.80665;
  localB->D17 = -9.80665 * localB->D15_tmp;
  localB->rtb_Product3_tmp[3] = ((localB->D14_tmp_cf * localB->D14_tmp_k -
    localB->D34_tmp) - localB->D34_tmp_f) * localB->D17;
  localB->rtb_Product3_tmp[4] = localB->D15_tmp_a * 9.80665 * localB->D14_tmp_c;
  localB->rtb_Product3_tmp[5] = 0.0;
  localB->rtb_Product3_tmp[6] = (-localB->D14_tmp_m * localB->D17_tmp_a -
    localB->D34_tmp_f) * localB->D17;
  localB->rtb_Product3_tmp[7] = rtP_ArmConstants.MC2 * 9.80665 *
    rtP_ArmConstants.Mass2 * localB->D15_tmp * localB->D17_tmp_l;
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    // MATLAB Function: '<S9>/MATLAB Function1'
    localB->fx[localB->c_j] = localB->e_hat[localB->c_j] -
      localB->rtb_Product3_tmp[localB->c_j];
  }

  // MATLAB Function: '<S9>/MATLAB Function1'
  Hardware_mldivide_0QKHZcd4_i(localB->ginv, localB->fx, localB);

  // MATLAB Function: '<S2>/GetBInvMatrix' incorporates:
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

  localB->D14_tmp = tan(localDW->DiscreteTimeIntegrator_DSTATE[4]);
  memset(&localB->x[0], 0, sizeof(real_T) << 6U);
  memset(&localB->BMinv[0], 0, sizeof(real_T) << 6U);
  localB->x[0] = localB->s * localB->D15_tmp;
  localB->x[8] = localB->D17_tmp_p5;
  localB->x[16] = localB->D17_tmp;
  localB->x[24] = 0.0;
  localB->x[32] = 0.0;
  localB->x[40] = 0.0;
  localB->x[1] = localB->D15_tmp * localB->smax;
  localB->x[9] = localB->D17_tmp_tmp_o;
  localB->x[17] = localB->D14_tmp_tmp_c;
  localB->x[25] = 0.0;
  localB->x[33] = 0.0;
  localB->x[41] = 0.0;
  localB->x[2] = -localB->D14_tmp_c;
  localB->x[10] = localB->D15_tmp * localB->D14_tmp_k;
  localB->x[18] = localB->D14_tmp_cx * localB->D15_tmp;
  localB->x[26] = 0.0;
  localB->x[34] = 0.0;
  localB->x[42] = 0.0;
  localB->x[3] = 0.0;
  localB->x[11] = 0.0;
  localB->x[19] = 0.0;
  localB->x[27] = 1.0;
  localB->x[35] = localB->D14_tmp_k * localB->D14_tmp;
  localB->x[43] = localB->D14_tmp_cx * localB->D14_tmp;
  localB->x[4] = 0.0;
  localB->x[12] = 0.0;
  localB->x[20] = 0.0;
  localB->x[28] = 0.0;
  localB->x[36] = localB->D14_tmp_cx;
  localB->x[44] = -localB->D14_tmp_k;
  localB->x[5] = 0.0;
  localB->x[13] = 0.0;
  localB->x[21] = 0.0;
  localB->x[29] = 0.0;
  localB->D14_tmp = 1.0 / localB->D15_tmp;
  localB->x[37] = localB->D14_tmp * localB->D14_tmp_k;
  localB->x[45] = localB->D14_tmp * localB->D14_tmp_cx;
  localB->x[54] = 1.0;
  localB->x[55] = 0.0;
  localB->x[62] = 0.0;
  localB->x[63] = 1.0;
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    localB->ipiv[localB->c_j] = static_cast<int8_T>(localB->c_j + 1);
  }

  for (localB->c_j = 0; localB->c_j < 7; localB->c_j++) {
    localB->jj = localB->c_j * 9;
    n = 9 - localB->c_j;
    localB->a = 0;
    localB->smax = fabs(localB->x[localB->jj]);
    for (i = 2; i < n; i++) {
      localB->s = fabs(localB->x[(localB->jj + i) - 1]);
      if (localB->s > localB->smax) {
        localB->a = i - 1;
        localB->smax = localB->s;
      }
    }

    if (localB->x[localB->jj + localB->a] != 0.0) {
      if (localB->a != 0) {
        n = localB->c_j + localB->a;
        localB->ipiv[localB->c_j] = static_cast<int8_T>(n + 1);
        for (i = 0; i < 8; i++) {
          jA = i << 3;
          localB->a = jA + localB->c_j;
          localB->smax = localB->x[localB->a];
          jA += n;
          localB->x[localB->a] = localB->x[jA];
          localB->x[jA] = localB->smax;
        }
      }

      n = (localB->jj - localB->c_j) + 8;
      for (i = localB->jj + 2; i <= n; i++) {
        localB->x[i - 1] /= localB->x[localB->jj];
      }
    }

    localB->a = 6 - localB->c_j;
    jA = localB->jj + 10;
    for (i = 0; i <= localB->a; i++) {
      localB->D17 = localB->x[((i << 3) + localB->jj) + 8];
      if (localB->D17 != 0.0) {
        localB->kAcol = (jA - localB->c_j) + 6;
        for (n = jA; n <= localB->kAcol; n++) {
          localB->x[n - 1] += localB->x[((localB->jj + n) - jA) + 1] *
            -localB->D17;
        }
      }

      jA += 8;
    }
  }

  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    localB->p[localB->c_j] = static_cast<int8_T>(localB->c_j + 1);
  }

  for (localB->c_j = 0; localB->c_j < 7; localB->c_j++) {
    ipiv = localB->ipiv[localB->c_j];
    if (ipiv > localB->c_j + 1) {
      localB->jj = localB->p[ipiv - 1];
      localB->p[ipiv - 1] = localB->p[localB->c_j];
      localB->p[localB->c_j] = static_cast<int8_T>(localB->jj);
    }
  }

  for (n = 0; n < 8; n++) {
    localB->jj = (localB->p[n] - 1) << 3;
    localB->BMinv[n + localB->jj] = 1.0;
    for (localB->a = n + 1; localB->a < 9; localB->a++) {
      localB->c_j = (localB->jj + localB->a) - 1;
      if (localB->BMinv[localB->c_j] != 0.0) {
        for (i = localB->a + 1; i < 9; i++) {
          jA = (localB->jj + i) - 1;
          localB->BMinv[jA] -= localB->x[(((localB->a - 1) << 3) + i) - 1] *
            localB->BMinv[localB->c_j];
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    jA = i << 3;
    for (n = 7; n >= 0; n--) {
      localB->kAcol = n << 3;
      localB->c_j = n + jA;
      localB->D17 = localB->BMinv[localB->c_j];
      if (localB->D17 != 0.0) {
        localB->BMinv[localB->c_j] = localB->D17 / localB->x[n + localB->kAcol];
        for (localB->a = 0; localB->a < n; localB->a++) {
          localB->jj = localB->a + jA;
          localB->BMinv[localB->jj] -= localB->x[localB->a + localB->kAcol] *
            localB->BMinv[localB->c_j];
        }
      }
    }
  }

  // DigitalClock: '<S3>/Digital Clock'
  localB->smax = (Hardware_M->getClockTick0() * 0.01);

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  propChange = true;
  localB->c_j = 0;
  exitg1 = false;
  while (!exitg1 && (localB->c_j < 16)) {
    if (!(localDW->obj.Waypoints[localB->c_j] == rtP_Trajectory.Waypoints
          [localB->c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      localB->c_j++;
    }
  }

  if (!propChange) {
    if (localDW->obj.isInitialized == 1) {
      localDW->obj.TunablePropsChanged = true;
      localDW->obj.tunablePropertyChanged[0] = true;
    }

    memcpy(&localDW->obj.Waypoints[0], &rtP_Trajectory.Waypoints[0], sizeof
           (real_T) << 4U);
  }

  propChange = true;
  localB->c_j = 0;
  exitg1 = false;
  while (!exitg1 && (localB->c_j < 2)) {
    if (!(localDW->obj.TimePoints[localB->c_j] == rtP_Trajectory.Tstamps
          [localB->c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      localB->c_j++;
    }
  }

  if (!propChange) {
    if (localDW->obj.isInitialized == 1) {
      localDW->obj.TunablePropsChanged = true;
      localDW->obj.tunablePropertyChanged[1] = true;
    }

    localDW->obj.TimePoints[0] = rtP_Trajectory.Tstamps[0];
    localDW->obj.TimePoints[1] = rtP_Trajectory.Tstamps[1];
  }

  propChange = true;
  localB->c_j = 0;
  exitg1 = false;
  while (!exitg1 && (localB->c_j < 16)) {
    if (!(localDW->obj.VelocityBoundaryCondition[localB->c_j] ==
          Hardware_P.PolynomialTrajectory_VelocityBo[localB->c_j])) {
      propChange = false;
      exitg1 = true;
    } else {
      localB->c_j++;
    }
  }

  if (!propChange) {
    if (localDW->obj.isInitialized == 1) {
      localDW->obj.TunablePropsChanged = true;
      localDW->obj.tunablePropertyChanged[3] = true;
    }

    memcpy(&localDW->obj.VelocityBoundaryCondition[0],
           &Hardware_P.PolynomialTrajectory_VelocityBo[0], sizeof(real_T) << 4U);
  }

  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
    if (localDW->obj.tunablePropertyChanged[0] ||
        localDW->obj.tunablePropertyChanged[1] ||
        localDW->obj.tunablePropertyChanged[2]) {
      propChange = true;
    } else {
      propChange = false;
    }

    if (!propChange) {
      if (localDW->obj.tunablePropertyChanged[3] ||
          localDW->obj.tunablePropertyChanged[4]) {
        propChange = true;
      } else {
        propChange = false;
      }
    }

    localDW->obj.PPFormUpdatedNeeded = propChange;
    if (localDW->obj.PPFormUpdatedNeeded) {
      PolyTrajSys_regeneratePPFormFro(&localDW->obj, localDW->obj.Waypoints,
        localDW->obj.TimePoints, localB);
    }

    for (localB->c_j = 0; localB->c_j < 5; localB->c_j++) {
      localDW->obj.tunablePropertyChanged[localB->c_j] = false;
    }
  }

  localB->D14_tmp = localB->smax;
  localB->s = localDW->obj.PPStruct.breaks[2];
  if (localB->smax == localDW->obj.PPStruct.breaks[2]) {
    for (i = 0; i < 1; i++) {
      localB->D14_tmp = localB->s - 2.220446049250313E-15;
    }
  }

  Hardware_ppval(localDW->obj.PPDDStruct.breaks, localDW->obj.PPDDStruct.coefs,
                 localB->D14_tmp, localB->e_hat);
  Hardware_ppval(localDW->obj.PPStruct.breaks, localDW->obj.PPStruct.coefs,
                 localB->smax, localB->rtb_Product3_tmp);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kp'

  localB->x[0] = rtP_PID.Kp[0];
  localB->x[8] = 0.0;
  localB->x[16] = 0.0;
  localB->x[24] = 0.0;
  localB->x[32] = 0.0;
  localB->x[40] = 0.0;
  localB->x[48] = 0.0;
  localB->x[56] = 0.0;
  localB->x[1] = 0.0;
  localB->x[9] = rtP_PID.Kp[1];
  localB->x[17] = 0.0;
  localB->x[25] = 0.0;
  localB->x[33] = 0.0;
  localB->x[41] = 0.0;
  localB->x[49] = 0.0;
  localB->x[57] = 0.0;
  localB->x[2] = 0.0;
  localB->x[10] = 0.0;
  localB->x[18] = rtP_PID.Kp[2];
  localB->x[26] = 0.0;
  localB->x[34] = 0.0;
  localB->x[42] = 0.0;
  localB->x[50] = 0.0;
  localB->x[58] = 0.0;
  localB->x[3] = 0.0;
  localB->x[11] = 0.0;
  localB->x[19] = 0.0;
  localB->x[27] = rtP_PID.Kp[3];
  localB->x[35] = 0.0;
  localB->x[43] = 0.0;
  localB->x[51] = 0.0;
  localB->x[59] = 0.0;
  localB->x[4] = 0.0;
  localB->x[12] = 0.0;
  localB->x[20] = 0.0;
  localB->x[28] = 0.0;
  localB->x[36] = rtP_PID.Kp[4];
  localB->x[44] = 0.0;
  localB->x[52] = 0.0;
  localB->x[60] = 0.0;
  localB->x[5] = 0.0;
  localB->x[13] = 0.0;
  localB->x[21] = 0.0;
  localB->x[29] = 0.0;
  localB->x[37] = 0.0;
  localB->x[45] = rtP_PID.Kp[5];
  localB->x[53] = 0.0;
  localB->x[61] = 0.0;
  localB->x[6] = 0.0;
  localB->x[14] = 0.0;
  localB->x[22] = 0.0;
  localB->x[30] = 0.0;
  localB->x[38] = 0.0;
  localB->x[46] = 0.0;
  localB->x[54] = rtP_PID.Kp[6];
  localB->x[62] = 0.0;
  localB->x[7] = 0.0;
  localB->x[15] = 0.0;
  localB->x[23] = 0.0;
  localB->x[31] = 0.0;
  localB->x[39] = 0.0;
  localB->x[47] = 0.0;
  localB->x[55] = 0.0;
  localB->x[63] = rtP_PID.Kp[7];

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  Hardware_ppval(localDW->obj.PPDStruct.breaks, localDW->obj.PPDStruct.coefs,
                 localB->D14_tmp, localB->Product4);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kd'

  localB->dv[0] = rtP_PID.Kd[0];
  localB->dv[8] = 0.0;
  localB->dv[16] = 0.0;
  localB->dv[24] = 0.0;
  localB->dv[32] = 0.0;
  localB->dv[40] = 0.0;
  localB->dv[48] = 0.0;
  localB->dv[56] = 0.0;
  localB->dv[1] = 0.0;
  localB->dv[9] = rtP_PID.Kd[1];
  localB->dv[17] = 0.0;
  localB->dv[25] = 0.0;
  localB->dv[33] = 0.0;
  localB->dv[41] = 0.0;
  localB->dv[49] = 0.0;
  localB->dv[57] = 0.0;
  localB->dv[2] = 0.0;
  localB->dv[10] = 0.0;
  localB->dv[18] = rtP_PID.Kd[2];
  localB->dv[26] = 0.0;
  localB->dv[34] = 0.0;
  localB->dv[42] = 0.0;
  localB->dv[50] = 0.0;
  localB->dv[58] = 0.0;
  localB->dv[3] = 0.0;
  localB->dv[11] = 0.0;
  localB->dv[19] = 0.0;
  localB->dv[27] = rtP_PID.Kd[3];
  localB->dv[35] = 0.0;
  localB->dv[43] = 0.0;
  localB->dv[51] = 0.0;
  localB->dv[59] = 0.0;
  localB->dv[4] = 0.0;
  localB->dv[12] = 0.0;
  localB->dv[20] = 0.0;
  localB->dv[28] = 0.0;
  localB->dv[36] = rtP_PID.Kd[4];
  localB->dv[44] = 0.0;
  localB->dv[52] = 0.0;
  localB->dv[60] = 0.0;
  localB->dv[5] = 0.0;
  localB->dv[13] = 0.0;
  localB->dv[21] = 0.0;
  localB->dv[29] = 0.0;
  localB->dv[37] = 0.0;
  localB->dv[45] = rtP_PID.Kd[5];
  localB->dv[53] = 0.0;
  localB->dv[61] = 0.0;
  localB->dv[6] = 0.0;
  localB->dv[14] = 0.0;
  localB->dv[22] = 0.0;
  localB->dv[30] = 0.0;
  localB->dv[38] = 0.0;
  localB->dv[46] = 0.0;
  localB->dv[54] = rtP_PID.Kd[6];
  localB->dv[62] = 0.0;
  localB->dv[7] = 0.0;
  localB->dv[15] = 0.0;
  localB->dv[23] = 0.0;
  localB->dv[31] = 0.0;
  localB->dv[39] = 0.0;
  localB->dv[47] = 0.0;
  localB->dv[55] = 0.0;
  localB->dv[63] = rtP_PID.Kd[7];
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    // Sum: '<S13>/Minus' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    localB->uv[localB->c_j] = localB->rtb_Product3_tmp[localB->c_j] -
      localDW->DiscreteTimeIntegrator_DSTATE[localB->c_j];

    // Sum: '<S13>/Minus1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'

    localB->dv1[localB->c_j] = localB->Product4[localB->c_j] -
      localDW->DiscreteTimeIntegrator1_DSTATE[localB->c_j];

    // MATLAB Function: '<S11>/PD Controller'
    localB->Product3[localB->c_j] = 0.0;
  }

  // MATLAB Function: '<S11>/PD Controller'
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    localB->D17 = localB->uv[localB->c_j];
    for (localB->jj = 0; localB->jj < 8; localB->jj++) {
      localB->Product3[localB->jj] += localB->x[(localB->c_j << 3) + localB->jj]
        * localB->D17;
    }
  }

  memset(&localB->rtb_Product3_tmp[0], 0, sizeof(real_T) << 3U);
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    localB->D17 = localB->dv1[localB->c_j];
    for (localB->jj = 0; localB->jj < 8; localB->jj++) {
      localB->rtb_Product3_tmp[localB->jj] += localB->dv[(localB->c_j << 3) +
        localB->jj] * localB->D17;
    }
  }

  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    // Sum: '<S11>/Add1' incorporates:
    //   MATLAB Function: '<S11>/PD Controller'
    //   Sum: '<S11>/Sum'

    localB->uv[localB->c_j] = ((localB->Product3[localB->c_j] +
      localB->rtb_Product3_tmp[localB->c_j]) + localB->e_hat[localB->c_j]) -
      localB->fx[localB->c_j];

    // Product: '<S11>/Matrix Multiply'
    localB->fx[localB->c_j] = 0.0;
  }

  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    // Product: '<S11>/Matrix Multiply'
    localB->D17 = localB->uv[localB->c_j];
    for (localB->jj = 0; localB->jj < 8; localB->jj++) {
      localB->fx[localB->jj] += localB->ginv[(localB->c_j << 3) + localB->jj] *
        localB->D17;
    }

    // Product: '<S2>/Matrix Multiply'
    rty_ForcesAndTorque[localB->c_j] = 0.0;
  }

  for (i = 0; i < 8; i++) {
    // Product: '<S2>/Matrix Multiply'
    localB->D17 = localB->fx[i];
    for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
      rty_ForcesAndTorque[localB->c_j] += localB->BMinv[(i << 3) + localB->c_j] *
        localB->D17;
    }

    // Sum: '<S4>/Sum1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    localB->e_hat[i] = rtu_Positions[i] - localDW->
      DiscreteTimeIntegrator_DSTATE[i];
  }

  // MATLAB Function: '<S4>/U power x2' incorporates:
  //   Constant: '<S4>/Q3'

  Hardware_Upowerx1(localB->e_hat, rtP_Differentiator.w1, localB->fx);
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    // Signum: '<S4>/Sign' incorporates:
    //   Sum: '<S4>/Sum1'

    localB->smax = localB->e_hat[localB->c_j];
    if (rtIsNaN(localB->smax)) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      localB->smax = (rtNaN);
    } else if (localB->smax < 0.0) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      localB->smax = -1.0;
    } else {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      localB->smax = (localB->smax > 0.0);
    }

    localB->rtb_Product3_tmp[localB->c_j] = localB->smax;

    // Product: '<S4>/Product3' incorporates:
    //   Constant: '<S4>/G1'
    //   Signum: '<S4>/Sign'

    localB->Product3[localB->c_j] = rtP_Differentiator.G1[localB->c_j] *
      localB->smax * localB->fx[localB->c_j];
  }

  // MATLAB Function: '<S4>/U power x1' incorporates:
  //   Constant: '<S4>/Q5'

  Hardware_Upowerx1(localB->e_hat, rtP_Differentiator.p1, localB->uv);

  // Product: '<S4>/Product4' incorporates:
  //   Constant: '<S4>/Q1'
  //   Signum: '<S4>/Sign1'

  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    localB->Product4[localB->c_j] = rtP_Differentiator.Q1[localB->c_j] *
      localB->rtb_Product3_tmp[localB->c_j] * localB->uv[localB->c_j];
  }

  // End of Product: '<S4>/Product4'

  // MATLAB Function: '<S4>/U power x3' incorporates:
  //   Constant: '<S4>/Q4'

  Hardware_Upowerx1(localB->e_hat, rtP_Differentiator.w2, localB->uv);

  // MATLAB Function: '<S4>/U power x4' incorporates:
  //   Constant: '<S4>/Q6'

  Hardware_Upowerx1(localB->e_hat, rtP_Differentiator.p2, localB->fx);
  for (localB->c_j = 0; localB->c_j < 8; localB->c_j++) {
    // DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    localB->s = localDW->DiscreteTimeIntegrator1_DSTATE[localB->c_j];

    // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
    //   Product: '<S4>/Product3'
    //   Product: '<S4>/Product4'
    //   Sum: '<S4>/Sum3'

    localDW->DiscreteTimeIntegrator_DSTATE[localB->c_j] += ((localB->
      Product3[localB->c_j] + localB->s) + localB->Product4[localB->c_j]) *
      Hardware_P.DiscreteTimeIntegrator_gainval;

    // Signum: '<S4>/Sign2' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'

    localB->smax = localB->rtb_Product3_tmp[localB->c_j];

    // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' incorporates:
    //   Constant: '<S4>/G2'
    //   Constant: '<S4>/Q2'
    //   Product: '<S4>/Product5'
    //   Product: '<S4>/Product6'
    //   Signum: '<S4>/Sign2'
    //   Signum: '<S4>/Sign3'
    //   Sum: '<S4>/Sum4'

    localDW->DiscreteTimeIntegrator1_DSTATE[localB->c_j] =
      (rtP_Differentiator.G2[localB->c_j] * localB->smax * localB->uv
       [localB->c_j] + rtP_Differentiator.Q2[localB->c_j] * localB->smax *
       localB->fx[localB->c_j]) * Hardware_P.DiscreteTimeIntegrator1_gainval +
      localB->s;
  }
}

// Model initialize function
void Hardware_initialize(const char_T **rt_errorStatus, const rtTimingBridge
  *timingBridge, int_T mdlref_TID0, RT_MODEL_Hardware_T *const Hardware_M)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // setup the global timing engine
  Hardware_M->Timing.mdlref_GlobalTID[0] = mdlref_TID0;
  Hardware_M->timingBridge = (timingBridge);

  // initialize error status
  Hardware_M->setErrorStatusPointer(rt_errorStatus);
}

time_T RT_MODEL_Hardware_T::getClockTickH0() const
{
  return static_cast<time_T>( *(timingBridge->
    clockTickH[Timing.mdlref_GlobalTID[0]]) );
}

time_T RT_MODEL_Hardware_T::getClockTick0() const
{
  return static_cast<time_T>( *((timingBridge->
    clockTick[Timing.mdlref_GlobalTID[0]])) );
}

time_T RT_MODEL_Hardware_T::getT() const
{
  return (*(timingBridge->taskTime[0]));
}

const char_T* RT_MODEL_Hardware_T::getErrorStatus() const
{
  return (*(errorStatus));
}

void RT_MODEL_Hardware_T::setErrorStatus(const char_T* const aErrorStatus) const
{
  (*(errorStatus) = aErrorStatus);
}

boolean_T RT_MODEL_Hardware_T::isSampleHit(int32_T sti) const
{
  return (timingBridge->taskCounter[Timing.mdlref_GlobalTID[sti]] == 0);
}

const char_T** RT_MODEL_Hardware_T::getErrorStatusPointer() const
{
  return errorStatus;
}

void RT_MODEL_Hardware_T::setErrorStatusPointer(const char_T
  ** aErrorStatusPointer)
{
  (errorStatus = aErrorStatusPointer);
}

//
// File trailer for generated code.
//
// [EOF]
//
