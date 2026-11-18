//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: DifAndCtrl.cpp
//
// Code generated for Simulink model 'DifAndCtrl'.
//
// Model version                  : 1.86
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Tue Nov  3 12:53:19 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "DifAndCtrl.h"
#include "rtwtypes.h"
#include <math.h>
#include "rt_powd_snf.h"
#include <string.h>

extern "C"
{

#include "rt_nonfinite.h"

}

extern const real_T rtCP_pooled_n8w8CpUBwJ7m[144];
extern const real_T rtCP_pooled_lB2PFN5bUywH[18];
extern const real_T rtCP_pooled_2xEMKNuUErM3[8];
extern const real_T rtCP_pooled_2Ebj3bnmgfTz[8];
extern const real_T rtCP_pooled_JpKxGaYsa0Rk[8];
extern const real_T rtCP_pooled_Rx7TxxwvCRIS[8];
extern const real_T rtCP_pooled_vgdAiwBriN2f[8];
extern const real_T rtCP_pooled_G9Xcc5zim5Un[8];
extern const real_T rtCP_pooled_lvFkthokaUjs[8];

#define rtCP_PolynomialTrajectory_Waypo rtCP_pooled_n8w8CpUBwJ7m // Expression: Trajectory.Waypoints
                                                                 //  Referenced by: '<S3>/Polynomial Trajectory'

#define rtCP_PolynomialTrajectory_TimeP rtCP_pooled_lB2PFN5bUywH // Expression: Trajectory.Tstamps
                                                                 //  Referenced by: '<S3>/Polynomial Trajectory'

#define rtCP_G1_Value                  rtCP_pooled_2xEMKNuUErM3  // Expression: Differentiator.G1
                                                                 //  Referenced by: '<S4>/G1'

#define rtCP_G2_Value                  rtCP_pooled_2Ebj3bnmgfTz  // Expression: Differentiator.G2
                                                                 //  Referenced by: '<S4>/G2'

#define rtCP_Q2_Value                  rtCP_pooled_JpKxGaYsa0Rk  // Expression: Differentiator.Q2
                                                                 //  Referenced by: '<S4>/Q2'

#define rtCP_Q3_Value                  rtCP_pooled_Rx7TxxwvCRIS  // Expression: Differentiator.w1
                                                                 //  Referenced by: '<S4>/Q3'

#define rtCP_Q4_Value                  rtCP_pooled_vgdAiwBriN2f  // Expression: Differentiator.w2
                                                                 //  Referenced by: '<S4>/Q4'

#define rtCP_Q5_Value                  rtCP_pooled_G9Xcc5zim5Un  // Expression: Differentiator.p1
                                                                 //  Referenced by: '<S4>/Q5'

#define rtCP_Q6_Value                  rtCP_pooled_lvFkthokaUjs  // Expression: Differentiator.p2
                                                                 //  Referenced by: '<S4>/Q6'


//
// Output and update for atomic system:
//    '<S4>/U power x1'
//    '<S4>/U power x2'
//    '<S4>/U power x3'
//    '<S4>/U power x4'
//
void DifAndCtrl::DifAndCtrl_Upowerx1(const real_T rtu_u[8], const real_T rtu_v[8],
  real_T rty_uv[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    rty_uv[i] = rt_powd_snf(fabs(rtu_u[i]), rtu_v[i]);
  }
}

void DifAndCtrl::PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T
  *obj, const real_T waypoints[144], const real_T timeData[18])
{
  int32_T b_coeffVec_tmp;
  int32_T b_i;
  int32_T b_j;
  static const int8_T tmp[4] = { 0, 0, 0, 1 };

  memset(&DifAndCtrl_DW.coefMat[0], 0, 544U * sizeof(real_T));
  for (b_i = 0; b_i < 17; b_i++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    DifAndCtrl_DW.finalTime = timeData[b_i + 1] - timeData[b_i];
    for (b_j = 0; b_j < 8; b_j++) {
      // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
      b_coeffVec_tmp = (b_i << 3) + b_j;
      DifAndCtrl_DW.b_coeffVec[0] = waypoints[b_coeffVec_tmp];
      DifAndCtrl_DW.b_coeffVec[1] = obj->
        VelocityBoundaryCondition[b_coeffVec_tmp];
      b_coeffVec_tmp = ((b_i + 1) << 3) + b_j;
      DifAndCtrl_DW.waypoints_idx_0 = waypoints[b_coeffVec_tmp] -
        (DifAndCtrl_DW.finalTime * DifAndCtrl_DW.b_coeffVec[1] +
         DifAndCtrl_DW.b_coeffVec[0]);
      DifAndCtrl_DW.waypoints_idx_1 = obj->
        VelocityBoundaryCondition[b_coeffVec_tmp] - (0.0 *
        DifAndCtrl_DW.b_coeffVec[0] + DifAndCtrl_DW.b_coeffVec[1]);
      DifAndCtrl_DW.b_coeffVec[3] = DifAndCtrl_DW.b_coeffVec[0];
      b_coeffVec_tmp = ((b_i << 3) + b_j) + 1;
      DifAndCtrl_DW.coefMat_tmp = DifAndCtrl_DW.finalTime *
        DifAndCtrl_DW.finalTime;
      DifAndCtrl_DW.coefMat[b_coeffVec_tmp - 1] = 1.0 /
        DifAndCtrl_DW.coefMat_tmp * DifAndCtrl_DW.waypoints_idx_1 + -2.0 /
        rt_powd_snf(DifAndCtrl_DW.finalTime, 3.0) *
        DifAndCtrl_DW.waypoints_idx_0;
      DifAndCtrl_DW.coefMat[b_coeffVec_tmp + 135] = 3.0 /
        DifAndCtrl_DW.coefMat_tmp * DifAndCtrl_DW.waypoints_idx_0 + -1.0 /
        DifAndCtrl_DW.finalTime * DifAndCtrl_DW.waypoints_idx_1;
      DifAndCtrl_DW.coefMat[b_coeffVec_tmp + 271] = DifAndCtrl_DW.b_coeffVec[1];
      DifAndCtrl_DW.coefMat[b_coeffVec_tmp + 407] = DifAndCtrl_DW.b_coeffVec[3];
    }
  }

  memset(&DifAndCtrl_DW.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&DifAndCtrl_DW.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    b_i = tmp[b_j];
    for (b_coeffVec_tmp = 0; b_coeffVec_tmp < 8; b_coeffVec_tmp++) {
      DifAndCtrl_DW.coeffMat[b_coeffVec_tmp + 24] += DifAndCtrl_DW.coefMat[136 *
        b_j + b_coeffVec_tmp] * static_cast<real_T>(b_i);
    }
  }

  memset(&DifAndCtrl_DW.coefsWithFlatStart[0], 0, 576U * sizeof(real_T));
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[0], &DifAndCtrl_DW.coeffMat[0],
         sizeof(real_T) << 3U);
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[144], &DifAndCtrl_DW.coeffMat[8],
         sizeof(real_T) << 3U);
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[288], &DifAndCtrl_DW.coeffMat[16],
         sizeof(real_T) << 3U);
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[432], &DifAndCtrl_DW.coeffMat[24],
         sizeof(real_T) << 3U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[8], &DifAndCtrl_DW.coefMat[0], 136U *
         sizeof(real_T));
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[152], &DifAndCtrl_DW.coefMat[136],
         136U * sizeof(real_T));
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[296], &DifAndCtrl_DW.coefMat[272],
         136U * sizeof(real_T));
  memcpy(&DifAndCtrl_DW.coefsWithFlatStart[440], &DifAndCtrl_DW.coefMat[408],
         136U * sizeof(real_T));
  DifAndCtrl_DW.breaksWithFlatStart[0] = timeData[0] - 1.0;
  memcpy(&DifAndCtrl_DW.breaksWithFlatStart[1], &timeData[0], 18U * sizeof
         (real_T));
  DifAndCtrl_DW.finalTime = DifAndCtrl_DW.breaksWithFlatStart[18] -
    DifAndCtrl_DW.breaksWithFlatStart[17];
  DifAndCtrl_DW.b_coeffVec[0] = rt_powd_snf(DifAndCtrl_DW.finalTime, 3.0);
  DifAndCtrl_DW.b_coeffVec[1] = rt_powd_snf(DifAndCtrl_DW.finalTime, 2.0);
  DifAndCtrl_DW.b_coeffVec[2] = rt_powd_snf(DifAndCtrl_DW.finalTime, 1.0);
  DifAndCtrl_DW.b_coeffVec[3] = rt_powd_snf(DifAndCtrl_DW.finalTime, 0.0);
  memset(&DifAndCtrl_DW.coeffMat[0], 0, sizeof(real_T) << 5U);

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&DifAndCtrl_DW.coeffMat[24], 0, sizeof(real_T) << 3U);
  for (b_j = 0; b_j < 4; b_j++) {
    DifAndCtrl_DW.finalTime = DifAndCtrl_DW.b_coeffVec[b_j];
    for (b_i = 0; b_i < 8; b_i++) {
      DifAndCtrl_DW.coeffMat[b_i + 24] += DifAndCtrl_DW.coefsWithFlatStart[(144 *
        b_j + b_i) + 136] * DifAndCtrl_DW.finalTime;
    }
  }

  memset(&obj->PPDStruct.coefs[0], 0, 608U * sizeof(real_T));
  for (b_j = 0; b_j < 4; b_j++) {
    // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
    memcpy(&obj->PPDStruct.coefs[b_j * 152],
           &DifAndCtrl_DW.coefsWithFlatStart[b_j * 144], 144U * sizeof(real_T));
    memcpy(&obj->PPDStruct.coefs[b_j * 152 + 144], &DifAndCtrl_DW.coeffMat[b_j <<
           3], sizeof(real_T) << 3U);
  }

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memcpy(&obj->PPStruct.breaks[0], &DifAndCtrl_DW.breaksWithFlatStart[0], 19U *
         sizeof(real_T));
  obj->PPStruct.breaks[19] = DifAndCtrl_DW.breaksWithFlatStart[18] + 1.0;
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

// Function for MATLAB Function: '<S9>/MATLAB Function1'
void DifAndCtrl::DifAndCtrl_mldivide_0QKHZcd4_c(const real_T A[64], real_T B[8])
{
  int32_T iy;
  int32_T jj;
  memcpy(&DifAndCtrl_DW.b_A[0], &A[0], sizeof(real_T) << 6U);
  for (int32_T j = 0; j < 8; j++) {
    DifAndCtrl_DW.ipiv_l[j] = static_cast<int8_T>(j + 1);
  }

  for (int32_T j = 0; j < 7; j++) {
    int32_T b_ix;
    int32_T c_k;
    jj = j * 9;
    iy = 9 - j;
    b_ix = 0;
    DifAndCtrl_DW.smax_o = fabs(DifAndCtrl_DW.b_A[jj]);
    for (c_k = 2; c_k < iy; c_k++) {
      DifAndCtrl_DW.s_l = fabs(DifAndCtrl_DW.b_A[(jj + c_k) - 1]);
      if (DifAndCtrl_DW.s_l > DifAndCtrl_DW.smax_o) {
        b_ix = c_k - 1;
        DifAndCtrl_DW.smax_o = DifAndCtrl_DW.s_l;
      }
    }

    if (DifAndCtrl_DW.b_A[jj + b_ix] != 0.0) {
      if (b_ix != 0) {
        iy = j + b_ix;
        DifAndCtrl_DW.ipiv_l[j] = static_cast<int8_T>(iy + 1);
        for (b_ix = 0; b_ix < 8; b_ix++) {
          c_k = (b_ix << 3) + j;
          DifAndCtrl_DW.smax_o = DifAndCtrl_DW.b_A[c_k];
          DifAndCtrl_DW.b_A[c_k] = DifAndCtrl_DW.b_A[iy];
          DifAndCtrl_DW.b_A[iy] = DifAndCtrl_DW.smax_o;
          iy += 8;
        }
      }

      iy = (jj - j) + 8;
      for (b_ix = jj + 2; b_ix <= iy; b_ix++) {
        DifAndCtrl_DW.b_A[b_ix - 1] /= DifAndCtrl_DW.b_A[jj];
      }
    }

    iy = 6 - j;
    b_ix = jj + 10;
    for (c_k = 0; c_k <= iy; c_k++) {
      DifAndCtrl_DW.smax_o = DifAndCtrl_DW.b_A[((c_k << 3) + jj) + 8];
      if (DifAndCtrl_DW.smax_o != 0.0) {
        int32_T c;
        c = (b_ix - j) + 6;
        for (int32_T ijA = b_ix; ijA <= c; ijA++) {
          DifAndCtrl_DW.b_A[ijA - 1] += DifAndCtrl_DW.b_A[((jj + ijA) - b_ix) +
            1] * -DifAndCtrl_DW.smax_o;
        }
      }

      b_ix += 8;
    }
  }

  for (int32_T j = 0; j < 7; j++) {
    int8_T ipiv;
    ipiv = DifAndCtrl_DW.ipiv_l[j];
    if (j + 1 != ipiv) {
      DifAndCtrl_DW.smax_o = B[j];
      B[j] = B[ipiv - 1];
      B[ipiv - 1] = DifAndCtrl_DW.smax_o;
    }
  }

  for (int32_T j = 0; j < 8; j++) {
    jj = j << 3;
    if (B[j] != 0.0) {
      for (iy = j + 2; iy < 9; iy++) {
        B[iy - 1] -= DifAndCtrl_DW.b_A[(iy + jj) - 1] * B[j];
      }
    }
  }

  for (int32_T j = 7; j >= 0; j--) {
    jj = j << 3;
    DifAndCtrl_DW.smax_o = B[j];
    if (DifAndCtrl_DW.smax_o != 0.0) {
      B[j] = DifAndCtrl_DW.smax_o / DifAndCtrl_DW.b_A[j + jj];
      for (iy = 0; iy < j; iy++) {
        B[iy] -= DifAndCtrl_DW.b_A[iy + jj] * B[j];
      }
    }
  }
}

void DifAndCtrl::DifAndCtrl_ppval(const real_T pp_breaks[20], const real_T
  pp_coefs[608], real_T x, real_T v[8])
{
  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  if (rtIsNaN(x)) {
    for (int32_T low_ip1 = 0; low_ip1 < 8; low_ip1++) {
      v[low_ip1] = (rtNaN);
    }
  } else {
    real_T xloc;
    int32_T high_i;
    int32_T ic0;
    int32_T low_i;
    int32_T low_ip1;
    low_i = 0;
    low_ip1 = 1;
    high_i = 20;
    while (high_i > low_ip1 + 1) {
      ic0 = ((low_i + high_i) + 1) >> 1;
      if (x >= pp_breaks[ic0 - 1]) {
        low_i = ic0 - 1;
        low_ip1 = ic0;
      } else {
        high_i = ic0;
      }
    }

    low_ip1 = low_i << 3;
    xloc = x - pp_breaks[low_i];
    memcpy(&v[0], &pp_coefs[low_ip1], sizeof(real_T) << 3U);
    for (high_i = 0; high_i < 3; high_i++) {
      ic0 = ((high_i + 1) * 152 + low_ip1) - 1;
      for (low_i = 0; low_i < 8; low_i++) {
        v[low_i] = pp_coefs[(ic0 + low_i) + 1] + xloc * v[low_i];
      }
    }
  }

  // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
}

// System initialize for referenced model: 'DifAndCtrl'
void DifAndCtrl::init(void)
{
  int32_T i;

  // Start for MATLABSystem: '<S3>/Polynomial Trajectory'
  memset(&DifAndCtrl_DW.obj.AccelerationBoundaryCondition[0], 0, 10U * sizeof
         (real_T));
  for (i = 0; i < 5; i++) {
    DifAndCtrl_DW.obj.tunablePropertyChanged[i] = false;
  }

  DifAndCtrl_DW.objisempty = true;
  memcpy(&DifAndCtrl_DW.obj.Waypoints[0], &rtCP_PolynomialTrajectory_Waypo[0],
         144U * sizeof(real_T));
  memcpy(&DifAndCtrl_DW.obj.TimePoints[0], &rtCP_PolynomialTrajectory_TimeP[0],
         18U * sizeof(real_T));
  memset(&DifAndCtrl_DW.obj.VelocityBoundaryCondition[0], 0, 144U * sizeof
         (real_T));
  DifAndCtrl_DW.obj.isInitialized = 1;
  PolyTrajSys_regeneratePPFormFro(&DifAndCtrl_DW.obj,
    DifAndCtrl_DW.obj.Waypoints, DifAndCtrl_DW.obj.TimePoints);
  DifAndCtrl_DW.obj.TunablePropsChanged = false;

  // End of Start for MATLABSystem: '<S3>/Polynomial Trajectory'
}

// Output and update for referenced model: 'DifAndCtrl'
void DifAndCtrl::step(const real_T arg_Position[8], real_T arg_ForcesAndTorques
                      [8])
{
  real_T tmp;
  int32_T d;
  int32_T i;
  int32_T iy;
  int8_T ipiv;
  boolean_T exitg1;
  boolean_T propChange;

  // MATLAB Function: '<S9>/MATLAB Function1' incorporates:
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator2'
  //   MATLAB Function: '<S2>/GetBInvMatrix'

  DifAndCtrl_DW.smax = sin(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[5]);
  DifAndCtrl_DW.D14_tmp = sin(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]);
  DifAndCtrl_DW.s = cos(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[5]);
  DifAndCtrl_DW.D14_tmp_m = sin(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]);
  DifAndCtrl_DW.D14_tmp_c = sin(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3]);
  DifAndCtrl_DW.D14_tmp_k = cos(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3]);
  DifAndCtrl_DW.D14_tmp_cx = cos(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7]);
  DifAndCtrl_DW.D14_tmp_b = sin(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7]);
  DifAndCtrl_DW.D14_tmp_tmp = DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6] +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.D14_tmp_p = sin(DifAndCtrl_DW.D14_tmp_tmp);
  DifAndCtrl_DW.D14_tmp_cv = cos(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]);
  DifAndCtrl_DW.D14_tmp_f = cos(DifAndCtrl_DW.D14_tmp_tmp);
  DifAndCtrl_DW.D14_tmp_o = 0.01400542 * DifAndCtrl_DW.D14_tmp_cx +
    0.040588879999999994;
  DifAndCtrl_DW.D14_tmp_n = 0.01400542 * DifAndCtrl_DW.D14_tmp_f;
  DifAndCtrl_DW.D14_tmp_tmp_h = 0.040588879999999994 * DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.D14_tmp_tmp_m = 0.01400542 * DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.D14_tmp_m3 = DifAndCtrl_DW.D14_tmp_tmp_h +
    DifAndCtrl_DW.D14_tmp_tmp_m;
  DifAndCtrl_DW.D14_tmp_cz = DifAndCtrl_DW.D14_tmp_m3 * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D14_tmp_ms = DifAndCtrl_DW.D14_tmp_o * DifAndCtrl_DW.s;
  DifAndCtrl_DW.D14_tmp_o3 = 0.01400542 * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D14_tmp_nh = 0.01400542 * DifAndCtrl_DW.s *
    DifAndCtrl_DW.D14_tmp_b * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D14_tmp_pe = (-DifAndCtrl_DW.D14_tmp_o * DifAndCtrl_DW.smax +
    DifAndCtrl_DW.D14_tmp_nh) * DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.D14 = (((DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D14_tmp *
    DifAndCtrl_DW.D14_tmp_b + -0.023689199999999997 * DifAndCtrl_DW.smax) +
                        DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D14_tmp *
                        DifAndCtrl_DW.D14_tmp_m) * DifAndCtrl_DW.D14_tmp_k +
                       ((DifAndCtrl_DW.D14_tmp_n + 0.023689199999999997) *
                        DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp_m +
                        DifAndCtrl_DW.D14_tmp_cz) * DifAndCtrl_DW.D14_tmp_c) +
    (0.040588879999999994 * DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp_c *
     DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.D14_tmp_pe) *
    DifAndCtrl_DW.D14_tmp_cv;
  DifAndCtrl_DW.D15_tmp = cos(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]);
  DifAndCtrl_DW.D15_tmp_tmp = DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3] +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6];
  DifAndCtrl_DW.D15_tmp_g = cos(DifAndCtrl_DW.D15_tmp_tmp);
  DifAndCtrl_DW.D15_tmp_tmp_a = DifAndCtrl_DW.D15_tmp_tmp +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.D15_tmp_g1 = cos(DifAndCtrl_DW.D15_tmp_tmp_a);
  DifAndCtrl_DW.D15_tmp_tmp_c = 0.040588879999999994 * DifAndCtrl_DW.D15_tmp_g;
  DifAndCtrl_DW.D15_tmp_tmp_f = 0.01400542 * DifAndCtrl_DW.D15_tmp_g1;
  DifAndCtrl_DW.D15_tmp_c = (0.023689199999999997 * DifAndCtrl_DW.D14_tmp_k +
    DifAndCtrl_DW.D15_tmp_tmp_c) + DifAndCtrl_DW.D15_tmp_tmp_f;
  DifAndCtrl_DW.D15 = DifAndCtrl_DW.D15_tmp_c * -DifAndCtrl_DW.s *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D16_tmp_tmp = 0.040588879999999994 * DifAndCtrl_DW.D14_tmp_cv;
  DifAndCtrl_DW.D16_tmp = (DifAndCtrl_DW.D16_tmp_tmp + 0.023689199999999997) +
    DifAndCtrl_DW.D14_tmp_n;
  DifAndCtrl_DW.D16_tmp_p = DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.s;
  DifAndCtrl_DW.D16_tmp_i = DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D16_tmp_o = DifAndCtrl_DW.D16_tmp_i * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D16_tmp_k = DifAndCtrl_DW.D14_tmp_cz * DifAndCtrl_DW.D14_tmp_m +
    DifAndCtrl_DW.D16_tmp_p;
  DifAndCtrl_DW.D16 = (DifAndCtrl_DW.D14_tmp_m3 * -DifAndCtrl_DW.s +
                       DifAndCtrl_DW.D16_tmp_o) * DifAndCtrl_DW.D14_tmp_k +
    DifAndCtrl_DW.D16_tmp_k * -DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.D17_tmp_tmp_a = DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D17_tmp_tmp_e = DifAndCtrl_DW.D14_tmp_k * DifAndCtrl_DW.s;
  DifAndCtrl_DW.D17_tmp = DifAndCtrl_DW.D17_tmp_tmp_e * DifAndCtrl_DW.D14_tmp_m
    + DifAndCtrl_DW.D17_tmp_tmp_a;
  DifAndCtrl_DW.D17_tmp_m = 0.09794 * DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.D17_tmp_tmp = DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.D17_tmp_tmp_i = -DifAndCtrl_DW.D14_tmp_k * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D17_tmp_m3 = DifAndCtrl_DW.D17_tmp_tmp * DifAndCtrl_DW.D14_tmp_m
    + DifAndCtrl_DW.D17_tmp_tmp_i;
  DifAndCtrl_DW.D17_tmp_j = 0.09794 * DifAndCtrl_DW.D14_tmp_f;
  DifAndCtrl_DW.D17_tmp_h = 0.17 * DifAndCtrl_DW.D14_tmp_cv;
  DifAndCtrl_DW.D17_tmp_c = 0.17 * DifAndCtrl_DW.D14_tmp +
    DifAndCtrl_DW.D17_tmp_m;
  DifAndCtrl_DW.D17_tmp_p = DifAndCtrl_DW.D17_tmp_c * 0.143;
  DifAndCtrl_DW.D17_tmp_i = DifAndCtrl_DW.D17_tmp_h + DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.D17_tmp_tmp_l = DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.D17_tmp_tmp_c = DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp_cv;
  DifAndCtrl_DW.D17_tmp_g = DifAndCtrl_DW.D17_tmp_tmp_c *
    DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.D17_tmp_tmp_l;
  DifAndCtrl_DW.D17_tmp_n = DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp *
    DifAndCtrl_DW.D14_tmp_m + -DifAndCtrl_DW.D14_tmp_cv * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D17 = ((0.01627888 * DifAndCtrl_DW.D14_tmp_c *
                        DifAndCtrl_DW.D17_tmp_g + DifAndCtrl_DW.D17_tmp_p *
                        DifAndCtrl_DW.D17_tmp) + DifAndCtrl_DW.D17_tmp_i * 0.143
                       * DifAndCtrl_DW.D17_tmp_m3) + 0.01627888 *
    DifAndCtrl_DW.D14_tmp_k * DifAndCtrl_DW.D17_tmp_n;
  DifAndCtrl_DW.D18_tmp = DifAndCtrl_DW.D17_tmp * DifAndCtrl_DW.D17_tmp_m +
    DifAndCtrl_DW.D17_tmp_m3 * DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.D18 = DifAndCtrl_DW.D18_tmp * 0.143;
  DifAndCtrl_DW.D24_tmp = 0.11464 * DifAndCtrl_DW.D14_tmp_cv + 0.08312;
  DifAndCtrl_DW.D24_tmp_p = (DifAndCtrl_DW.D17_tmp_h + 0.08312) +
    DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.D24_tmp_m = DifAndCtrl_DW.D17_tmp_m3 * DifAndCtrl_DW.D17_tmp_c;
  DifAndCtrl_DW.D17_tmp_h = DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D24_tmp_h = 0.08312 * DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.D24_tmp_n = (0.17 * DifAndCtrl_DW.D15_tmp_g +
    DifAndCtrl_DW.D24_tmp_h) + 0.09794 * DifAndCtrl_DW.D15_tmp_g1;
  DifAndCtrl_DW.D24 = (((DifAndCtrl_DW.D24_tmp * DifAndCtrl_DW.smax *
    DifAndCtrl_DW.D14_tmp_m + -0.11464 * DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp)
                        * (0.142 * DifAndCtrl_DW.D14_tmp_c) + 0.143 *
                        DifAndCtrl_DW.s * DifAndCtrl_DW.D24_tmp_n *
                        DifAndCtrl_DW.D17_tmp_h) + (0.11464 * DifAndCtrl_DW.smax
    * DifAndCtrl_DW.D14_tmp * DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.D24_tmp *
    DifAndCtrl_DW.s) * (0.142 * DifAndCtrl_DW.D14_tmp_k)) +
    (DifAndCtrl_DW.D24_tmp_p * DifAndCtrl_DW.D17_tmp - DifAndCtrl_DW.D24_tmp_m) *
    (0.143 * DifAndCtrl_DW.D14_tmp_m);
  DifAndCtrl_DW.D25 = -DifAndCtrl_DW.D15_tmp_c * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D17_tmp_p = ((DifAndCtrl_DW.D24_tmp * -0.142 *
    DifAndCtrl_DW.D17_tmp - DifAndCtrl_DW.D24_tmp_p * 0.143 *
    DifAndCtrl_DW.D17_tmp) + 0.01627888 * DifAndCtrl_DW.D14_tmp *
    DifAndCtrl_DW.D17_tmp_m3) + DifAndCtrl_DW.D17_tmp_p *
    DifAndCtrl_DW.D17_tmp_m3;
  DifAndCtrl_DW.D17_tmp_tmp_a = DifAndCtrl_DW.D17_tmp_tmp_a *
    DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.D17_tmp_tmp_e;
  DifAndCtrl_DW.D27_tmp = DifAndCtrl_DW.D14_tmp_k * DifAndCtrl_DW.smax *
    DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D17_tmp_tmp_e = DifAndCtrl_DW.D17_tmp_tmp -
    DifAndCtrl_DW.D27_tmp;
  DifAndCtrl_DW.D27_tmp_o = DifAndCtrl_DW.D17_tmp_tmp_a *
    DifAndCtrl_DW.D16_tmp_tmp;
  DifAndCtrl_DW.D27_tmp_m = DifAndCtrl_DW.D17_tmp_tmp_a *
    DifAndCtrl_DW.D14_tmp_n;
  DifAndCtrl_DW.D27 = (DifAndCtrl_DW.D17_tmp_tmp_e * -DifAndCtrl_DW.D14_tmp_m3 +
                       DifAndCtrl_DW.D27_tmp_o) + DifAndCtrl_DW.D27_tmp_m;
  DifAndCtrl_DW.D27_tmp += -DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.D17_tmp_m = DifAndCtrl_DW.D27_tmp * DifAndCtrl_DW.D17_tmp_m +
    DifAndCtrl_DW.D17_tmp_tmp_a * DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.D17_tmp_j = DifAndCtrl_DW.D17_tmp_m * 0.143;
  DifAndCtrl_DW.D34_tmp = sin(DifAndCtrl_DW.D15_tmp_tmp);
  DifAndCtrl_DW.D34_tmp_m = sin(DifAndCtrl_DW.D15_tmp_tmp_a);
  DifAndCtrl_DW.D34_tmp_a = 0.040588879999999994 * DifAndCtrl_DW.D34_tmp;
  DifAndCtrl_DW.D34_tmp_i = 0.01400542 * DifAndCtrl_DW.D34_tmp_m;
  DifAndCtrl_DW.D34_tmp_l = (0.023689199999999997 * DifAndCtrl_DW.D14_tmp_c +
    DifAndCtrl_DW.D34_tmp_a) + DifAndCtrl_DW.D34_tmp_i;
  DifAndCtrl_DW.D34 = DifAndCtrl_DW.D34_tmp_l * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D35 = DifAndCtrl_DW.D15_tmp_c * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D37_tmp = DifAndCtrl_DW.D34_tmp_a + DifAndCtrl_DW.D34_tmp_i;
  DifAndCtrl_DW.D37 = DifAndCtrl_DW.D37_tmp * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D38 = 0.01400542 * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.D34_tmp_m;
  DifAndCtrl_DW.D45_tmp =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D15_tmp_g1;
  DifAndCtrl_DW.D45_tmp_m =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
    DifAndCtrl_DW.D34_tmp_m;
  DifAndCtrl_DW.D45_tmp_a =
    ((DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
      DifAndCtrl_DW.D15_tmp_g + DifAndCtrl_DW.D45_tmp) +
     DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
     DifAndCtrl_DW.D34_tmp) + DifAndCtrl_DW.D45_tmp_m;
  DifAndCtrl_DW.D46_tmp_tmp_ei = DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]
    - DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp = sin(DifAndCtrl_DW.D46_tmp_tmp_ei);
  DifAndCtrl_DW.D46_tmp_tmp_e = DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]
    + DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6];
  DifAndCtrl_DW.D46_tmp_n = sin(DifAndCtrl_DW.D46_tmp_tmp_e);
  DifAndCtrl_DW.D46_tmp_tmp = DifAndCtrl_DW.D15_tmp_tmp -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_p = cos(DifAndCtrl_DW.D46_tmp_tmp);
  DifAndCtrl_DW.D46_tmp_tmp_l = DifAndCtrl_DW.D15_tmp_tmp_a -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_l = cos(DifAndCtrl_DW.D46_tmp_tmp_l);
  DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.D15_tmp_tmp +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_j = cos(DifAndCtrl_DW.D46_tmp_tmp_o);
  DifAndCtrl_DW.D46_tmp_tmp_o2 = DifAndCtrl_DW.D15_tmp_tmp_a +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_d = cos(DifAndCtrl_DW.D46_tmp_tmp_o2);
  DifAndCtrl_DW.D46_tmp_g = sin(DifAndCtrl_DW.D46_tmp_tmp);
  DifAndCtrl_DW.D46_tmp_dy = sin(DifAndCtrl_DW.D46_tmp_tmp_l);
  DifAndCtrl_DW.D46_tmp_b = sin(DifAndCtrl_DW.D46_tmp_tmp_o);
  DifAndCtrl_DW.D46_tmp_ln = sin(DifAndCtrl_DW.D46_tmp_tmp_o2);
  DifAndCtrl_DW.D46_tmp_tmp_c = DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7]
    - DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_bn = sin(DifAndCtrl_DW.D46_tmp_tmp_c);
  DifAndCtrl_DW.D46_tmp_tmp_a = DifAndCtrl_DW.D14_tmp_tmp -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_da = sin(DifAndCtrl_DW.D46_tmp_tmp_a);
  DifAndCtrl_DW.D46_tmp_tmp_d = DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]
    + DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.D46_tmp_e = sin(DifAndCtrl_DW.D46_tmp_tmp_d);
  DifAndCtrl_DW.D46_tmp_tmp_af = DifAndCtrl_DW.D14_tmp_tmp +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_bj = sin(DifAndCtrl_DW.D46_tmp_tmp_af);
  DifAndCtrl_DW.D46_tmp_tmp_k =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
    DifAndCtrl_DW.D46_tmp_d;
  DifAndCtrl_DW.D46_tmp_c =
    ((-DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
      DifAndCtrl_DW.D46_tmp_p -
      DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
      DifAndCtrl_DW.D46_tmp_l) -
     DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
     DifAndCtrl_DW.D46_tmp_j) - DifAndCtrl_DW.D46_tmp_tmp_k;
  DifAndCtrl_DW.D46_tmp_f =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    DifAndCtrl_DW.D46_tmp_g;
  DifAndCtrl_DW.D46_tmp_p4 = 0.004761842800000001 * DifAndCtrl_DW.D46_tmp_bn;
  DifAndCtrl_DW.D46_tmp_e1 =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D46_tmp_dy;
  DifAndCtrl_DW.D46_tmp_o = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D46_tmp_h = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D46_tmp_l5 = -0.0037324216063999997 * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D46_tmp_h2 = -0.0027433816695999996 * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D46_tmp_m = -0.008265400000000001 * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D46_tmp_mc =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    DifAndCtrl_DW.D46_tmp_b;
  DifAndCtrl_DW.D46_tmp_h3 = -0.004761842800000001 * DifAndCtrl_DW.D46_tmp_e;
  DifAndCtrl_DW.D46_tmp_cs =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D46_tmp_ln;
  DifAndCtrl_DW.D46 = ((((((((((((((((((((0.0027062010112 *
    DifAndCtrl_DW.D46_tmp + DifAndCtrl_DW.D46_tmp_c) + 0.0040412944 *
    DifAndCtrl_DW.D46_tmp) + DifAndCtrl_DW.D46_tmp_f) + DifAndCtrl_DW.D46_tmp_p4)
    + 0.0023282610207999996 * DifAndCtrl_DW.D46_tmp_da) +
    DifAndCtrl_DW.D46_tmp_e1) + DifAndCtrl_DW.D46_tmp_o) +
    DifAndCtrl_DW.D46_tmp_h) + -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.D46_tmp_l5) +
    -0.0019621373695999996 * DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.D46_tmp_h2)
    + -0.0019759552383999996 * DifAndCtrl_DW.D14_tmp_m) +
    DifAndCtrl_DW.D46_tmp_m) + -0.0027062010112 * DifAndCtrl_DW.D46_tmp_n) +
    -0.0040412944 * DifAndCtrl_DW.D46_tmp_n) + DifAndCtrl_DW.D46_tmp_mc) +
    DifAndCtrl_DW.D46_tmp_h3) + -0.0023282610207999996 *
                        DifAndCtrl_DW.D46_tmp_bj) + DifAndCtrl_DW.D46_tmp_cs) *
    0.5;
  DifAndCtrl_DW.D47_tmp = 0.0011641305103999998 * DifAndCtrl_DW.D14_tmp_f;
  DifAndCtrl_DW.D47_tmp_p =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8];
  DifAndCtrl_DW.D47_tmp_px = 0.004761842800000001 * DifAndCtrl_DW.D14_tmp_cx;
  DifAndCtrl_DW.D47_tmp_m = (((DifAndCtrl_DW.D47_tmp_p + 0.0018662108031999999)
    + 0.0013716908347999998) + 0.0041327000000000004) + 0.0033737477055999993 *
    DifAndCtrl_DW.D14_tmp_cv;
  DifAndCtrl_DW.D47 = (DifAndCtrl_DW.D47_tmp_m + DifAndCtrl_DW.D47_tmp_px) +
    DifAndCtrl_DW.D47_tmp;
  DifAndCtrl_DW.D48_tmp =
    (DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] +
     0.0013716908347999998) + 0.0023809214000000004 * DifAndCtrl_DW.D14_tmp_cx;
  DifAndCtrl_DW.D48_tmp_k = DifAndCtrl_DW.D48_tmp + DifAndCtrl_DW.D47_tmp;
  DifAndCtrl_DW.D56_tmp_tmp = 2.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3];
  DifAndCtrl_DW.D56_tmp_tmp_h = DifAndCtrl_DW.D56_tmp_tmp -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp = sin(DifAndCtrl_DW.D56_tmp_tmp_h);
  DifAndCtrl_DW.D56_tmp_tmp_f = DifAndCtrl_DW.D56_tmp_tmp +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6];
  DifAndCtrl_DW.D56_tmp_tmp_a = DifAndCtrl_DW.D56_tmp_tmp_f -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_l = sin(DifAndCtrl_DW.D56_tmp_tmp_a);
  DifAndCtrl_DW.D56_tmp_tmp_tmp = 2.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6];
  DifAndCtrl_DW.D56_tmp_tmp_i = DifAndCtrl_DW.D56_tmp_tmp +
    DifAndCtrl_DW.D56_tmp_tmp_tmp;
  DifAndCtrl_DW.D56_tmp_tmp_ff = DifAndCtrl_DW.D56_tmp_tmp_i -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_d = sin(DifAndCtrl_DW.D56_tmp_tmp_ff);
  DifAndCtrl_DW.D56_tmp_tmp_iz = 2.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7] +
    DifAndCtrl_DW.D56_tmp_tmp_i;
  DifAndCtrl_DW.D56_tmp_tmp_g = DifAndCtrl_DW.D56_tmp_tmp_iz -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_lx = sin(DifAndCtrl_DW.D56_tmp_tmp_g);
  DifAndCtrl_DW.D56_tmp_tmp_g2 = DifAndCtrl_DW.D56_tmp_tmp +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_o = sin(DifAndCtrl_DW.D56_tmp_tmp_g2);
  DifAndCtrl_DW.D56_tmp_tmp_fi = DifAndCtrl_DW.D56_tmp_tmp_f +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_n = sin(DifAndCtrl_DW.D56_tmp_tmp_fi);
  DifAndCtrl_DW.D56_tmp_tmp_c = DifAndCtrl_DW.D56_tmp_tmp_i +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_b = sin(DifAndCtrl_DW.D56_tmp_tmp_c);
  DifAndCtrl_DW.D56_tmp_tmp_iz += DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_h = sin(DifAndCtrl_DW.D56_tmp_tmp_iz);
  DifAndCtrl_DW.D56_tmp_j = cos(DifAndCtrl_DW.D56_tmp_tmp_ff);
  DifAndCtrl_DW.D56_tmp_f = cos(DifAndCtrl_DW.D56_tmp_tmp_g);
  DifAndCtrl_DW.D56_tmp_a = cos(DifAndCtrl_DW.D56_tmp_tmp_c);
  DifAndCtrl_DW.D56_tmp_ju = cos(DifAndCtrl_DW.D56_tmp_tmp_iz);
  DifAndCtrl_DW.D56_tmp_tmp_ff = DifAndCtrl_DW.D56_tmp_tmp_f +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.D56_tmp_tmp_iz = DifAndCtrl_DW.D56_tmp_tmp_ff -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_jz = sin(DifAndCtrl_DW.D56_tmp_tmp_iz);
  DifAndCtrl_DW.D56_tmp_tmp_i += DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.D56_tmp_tmp_g = DifAndCtrl_DW.D56_tmp_tmp_i -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_o4 = sin(DifAndCtrl_DW.D56_tmp_tmp_g);
  DifAndCtrl_DW.D56_tmp_tmp_c = DifAndCtrl_DW.D56_tmp_tmp_ff +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_ny = sin(DifAndCtrl_DW.D56_tmp_tmp_c);
  DifAndCtrl_DW.D56_tmp_tmp_i += DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56_tmp_i = sin(DifAndCtrl_DW.D56_tmp_tmp_i);
  DifAndCtrl_DW.D56_tmp_o3 = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  DifAndCtrl_DW.D56_tmp_lm = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  DifAndCtrl_DW.D56_tmp_ad = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.D56_tmp_k = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.D56_tmp_p = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.D56_tmp_bp = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.D56_tmp_c = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.D56_tmp_nb = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.D56_tmp_ij = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.D56_tmp_m = -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.D56_tmp_tmp_n =
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D56_tmp;
  DifAndCtrl_DW.D56_tmp_tmp_p =
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.D56_tmp;
  DifAndCtrl_DW.D56_tmp_tmp_d = 0.0009810686847999998 * DifAndCtrl_DW.D56_tmp;
  DifAndCtrl_DW.D56_tmp_tmp_o = 0.0009879776191999998 * DifAndCtrl_DW.D56_tmp;
  DifAndCtrl_DW.D56_tmp_tmp_j =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D56_tmp_d;
  DifAndCtrl_DW.D56_tmp_tmp_c2 =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D56_tmp_d;
  DifAndCtrl_DW.D56_tmp_tmp_hp = 0.0018662108031999999 * DifAndCtrl_DW.D56_tmp_d;
  DifAndCtrl_DW.D56_tmp_tmp_da = 0.0041327000000000004 * DifAndCtrl_DW.D56_tmp_d;
  DifAndCtrl_DW.D56_tmp_tmp_c5 =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.D56_tmp_lx;
  DifAndCtrl_DW.D56_tmp_tmp_pw =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D56_tmp_lx;
  DifAndCtrl_DW.D56_tmp_tmp_pi = 0.0013716908347999998 *
    DifAndCtrl_DW.D56_tmp_lx;
  DifAndCtrl_DW.D56_tmp_tmp_a4 =
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D56_tmp_o;
  DifAndCtrl_DW.D56_tmp_tmp_ow =
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.D56_tmp_o;
  DifAndCtrl_DW.D56_tmp_tmp_jw = 0.0009810686847999998 * DifAndCtrl_DW.D56_tmp_o;
  DifAndCtrl_DW.D56_tmp_tmp_pie =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D56_tmp_b;
  DifAndCtrl_DW.D56_tmp_tmp_ob =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D56_tmp_b;
  DifAndCtrl_DW.D56_tmp_tmp_l = 0.0018662108031999999 * DifAndCtrl_DW.D56_tmp_b;
  DifAndCtrl_DW.D56_tmp_tmp_k = 0.0041327000000000004 * DifAndCtrl_DW.D56_tmp_b;
  DifAndCtrl_DW.D56_tmp =
    (((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.D56_tmp_ij *
    DifAndCtrl_DW.D46_tmp_p + DifAndCtrl_DW.D56_tmp_o3 * DifAndCtrl_DW.D56_tmp_j)
    + DifAndCtrl_DW.D56_tmp_m * DifAndCtrl_DW.D46_tmp_l) +
    DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D56_tmp_f) +
    DifAndCtrl_DW.D56_tmp_c * DifAndCtrl_DW.D46_tmp_j) +
    DifAndCtrl_DW.D56_tmp_o3 * DifAndCtrl_DW.D56_tmp_a) +
    DifAndCtrl_DW.D56_tmp_nb * DifAndCtrl_DW.D46_tmp_d) +
    DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D56_tmp_ju) +
    DifAndCtrl_DW.D56_tmp_tmp_n) - DifAndCtrl_DW.D56_tmp_tmp_p) +
    DifAndCtrl_DW.D56_tmp_tmp_d) + DifAndCtrl_DW.D56_tmp_tmp_o) +
    DifAndCtrl_DW.D56_tmp_ad * DifAndCtrl_DW.D46_tmp_g) + 0.0027062010112 *
    DifAndCtrl_DW.D56_tmp_l) + 0.0040412944 * DifAndCtrl_DW.D56_tmp_l) -
    DifAndCtrl_DW.D56_tmp_tmp_j) + DifAndCtrl_DW.D56_tmp_tmp_c2) +
    DifAndCtrl_DW.D56_tmp_tmp_hp) + DifAndCtrl_DW.D56_tmp_tmp_da) +
                       DifAndCtrl_DW.D56_tmp_k * DifAndCtrl_DW.D46_tmp_dy) +
                      0.0023282610207999996 * DifAndCtrl_DW.D56_tmp_jz) +
                     0.004761842800000001 * DifAndCtrl_DW.D56_tmp_o4) -
                    DifAndCtrl_DW.D56_tmp_tmp_c5) + DifAndCtrl_DW.D56_tmp_tmp_pw)
                  + DifAndCtrl_DW.D56_tmp_tmp_pi) + DifAndCtrl_DW.D56_tmp_tmp_a4)
                - DifAndCtrl_DW.D56_tmp_tmp_ow) + DifAndCtrl_DW.D56_tmp_tmp_jw)
              + 0.0009879776191999998 * DifAndCtrl_DW.D56_tmp_o) +
             DifAndCtrl_DW.D56_tmp_p * DifAndCtrl_DW.D46_tmp_b) +
            0.0027062010112 * DifAndCtrl_DW.D56_tmp_n) + 0.0040412944 *
           DifAndCtrl_DW.D56_tmp_n) - DifAndCtrl_DW.D56_tmp_tmp_pie) +
         DifAndCtrl_DW.D56_tmp_tmp_ob) + DifAndCtrl_DW.D56_tmp_tmp_l) +
       DifAndCtrl_DW.D56_tmp_tmp_k) + DifAndCtrl_DW.D56_tmp_bp *
      DifAndCtrl_DW.D46_tmp_ln) + 0.0023282610207999996 *
     DifAndCtrl_DW.D56_tmp_ny) + 0.004761842800000001 * DifAndCtrl_DW.D56_tmp_i;
  DifAndCtrl_DW.D56_tmp_jg =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D56_tmp_h;
  DifAndCtrl_DW.D56_tmp_e = 0.0013716908347999998 * DifAndCtrl_DW.D56_tmp_h;
  DifAndCtrl_DW.D56 =
    (((-DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
       DifAndCtrl_DW.D56_tmp_h + DifAndCtrl_DW.D56_tmp) +
      DifAndCtrl_DW.D56_tmp_jg) + DifAndCtrl_DW.D56_tmp_e) * 0.25;
  DifAndCtrl_DW.D45_tmp += DifAndCtrl_DW.D45_tmp_m;
  DifAndCtrl_DW.w_a_tmp = 0.11464 * DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.D45_tmp_m = DifAndCtrl_DW.D17_tmp * -DifAndCtrl_DW.D24_tmp +
    DifAndCtrl_DW.D17_tmp_m3 * DifAndCtrl_DW.w_a_tmp;
  DifAndCtrl_DW.D24_tmp_m += -DifAndCtrl_DW.D24_tmp_p * DifAndCtrl_DW.D17_tmp;
  DifAndCtrl_DW.D24_tmp = DifAndCtrl_DW.D17_tmp_tmp_e * DifAndCtrl_DW.D24_tmp +
    DifAndCtrl_DW.D17_tmp_tmp_a * DifAndCtrl_DW.w_a_tmp;
  DifAndCtrl_DW.ab_a = DifAndCtrl_DW.D24_tmp_p * DifAndCtrl_DW.D17_tmp_tmp_e +
    DifAndCtrl_DW.D17_tmp_tmp_a * DifAndCtrl_DW.D17_tmp_c;
  DifAndCtrl_DW.D46_tmp_da *= 0.0011641305103999998;
  DifAndCtrl_DW.D46_tmp_bj *= 0.0011641305103999998;
  DifAndCtrl_DW.D24_tmp_p = (((((((((((((((((0.0013531005056 *
    DifAndCtrl_DW.D46_tmp + DifAndCtrl_DW.D46_tmp_c) + 0.0020206472 *
    DifAndCtrl_DW.D46_tmp) + DifAndCtrl_DW.D46_tmp_f) + DifAndCtrl_DW.D46_tmp_p4)
    + DifAndCtrl_DW.D46_tmp_da) + DifAndCtrl_DW.D46_tmp_e1) +
    DifAndCtrl_DW.D46_tmp_o) + DifAndCtrl_DW.D46_tmp_h) +
    DifAndCtrl_DW.D46_tmp_l5) + DifAndCtrl_DW.D46_tmp_h2) +
    DifAndCtrl_DW.D46_tmp_m) - 0.0013531005056 * DifAndCtrl_DW.D46_tmp_n) -
    0.0020206472 * DifAndCtrl_DW.D46_tmp_n) + DifAndCtrl_DW.D46_tmp_mc) +
    DifAndCtrl_DW.D46_tmp_h3) - DifAndCtrl_DW.D46_tmp_bj) +
    DifAndCtrl_DW.D46_tmp_cs) * 0.5;
  DifAndCtrl_DW.D46_tmp_e1 =
    (((((((((-DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
             DifAndCtrl_DW.D46_tmp_l - DifAndCtrl_DW.D46_tmp_tmp_k) +
            0.0023809214000000004 * DifAndCtrl_DW.D46_tmp_bn) +
           DifAndCtrl_DW.D46_tmp_da) + DifAndCtrl_DW.D46_tmp_e1) +
         DifAndCtrl_DW.D46_tmp_h) + DifAndCtrl_DW.D46_tmp_h2) +
       -0.0023809214000000004 * DifAndCtrl_DW.D46_tmp_e) -
      DifAndCtrl_DW.D46_tmp_bj) + DifAndCtrl_DW.D46_tmp_cs) * 0.5;
  DifAndCtrl_DW.D46_tmp_bn = cos(DifAndCtrl_DW.D56_tmp_tmp);
  DifAndCtrl_DW.D46_tmp_tmp_k = DifAndCtrl_DW.D15_tmp_tmp * 2.0;
  DifAndCtrl_DW.D46_tmp_da = cos(DifAndCtrl_DW.D46_tmp_tmp_k);
  DifAndCtrl_DW.D46_tmp_e = cos(DifAndCtrl_DW.D56_tmp_tmp_f);
  DifAndCtrl_DW.D46_tmp_c = DifAndCtrl_DW.D15_tmp_tmp_a * 2.0;
  DifAndCtrl_DW.D46_tmp_bj = cos(DifAndCtrl_DW.D46_tmp_c);
  DifAndCtrl_DW.D46_tmp = sin(DifAndCtrl_DW.D56_tmp_tmp_tmp);
  DifAndCtrl_DW.D46_tmp_h = DifAndCtrl_DW.D14_tmp_tmp * 2.0;
  DifAndCtrl_DW.D46_tmp_n = cos(DifAndCtrl_DW.D46_tmp_h);
  DifAndCtrl_DW.D46_tmp_h = sin(DifAndCtrl_DW.D46_tmp_h);
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_p = 2.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D46_tmp_h2 = sin(DifAndCtrl_DW.rtb_ginv_tmp_tmp_p);
  DifAndCtrl_DW.D46_tmp_cs = sin(DifAndCtrl_DW.D46_tmp_tmp_k);
  DifAndCtrl_DW.D46_tmp_c = sin(DifAndCtrl_DW.D46_tmp_c);
  DifAndCtrl_DW.rtb_ginv_tmp = cos(DifAndCtrl_DW.D56_tmp_tmp_ff);
  DifAndCtrl_DW.rtb_ginv_tmp_tmp = DifAndCtrl_DW.D46_tmp_tmp_k +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.D46_tmp_tmp_k = cos(DifAndCtrl_DW.rtb_ginv_tmp_tmp);
  DifAndCtrl_DW.D56_tmp_tmp_tmp = cos(DifAndCtrl_DW.D56_tmp_tmp_tmp);
  DifAndCtrl_DW.ginv[0] = 2.1037999999999997;
  DifAndCtrl_DW.ginv[8] = 0.0;
  DifAndCtrl_DW.ginv[16] = 0.0;
  DifAndCtrl_DW.ginv[24] = DifAndCtrl_DW.D14;
  DifAndCtrl_DW.ginv[32] = DifAndCtrl_DW.D15;
  DifAndCtrl_DW.ginv[40] = DifAndCtrl_DW.D16;
  DifAndCtrl_DW.ginv[48] = DifAndCtrl_DW.D17;
  DifAndCtrl_DW.ginv[56] = DifAndCtrl_DW.D18;
  DifAndCtrl_DW.ginv[1] = 0.0;
  DifAndCtrl_DW.ginv[9] = 2.1037999999999997;
  DifAndCtrl_DW.ginv[17] = 0.0;
  DifAndCtrl_DW.ginv[25] = DifAndCtrl_DW.D24;
  DifAndCtrl_DW.ginv[33] = DifAndCtrl_DW.D25;
  DifAndCtrl_DW.ginv[41] = DifAndCtrl_DW.D17_tmp_p;
  DifAndCtrl_DW.ginv[49] = DifAndCtrl_DW.D27;
  DifAndCtrl_DW.ginv[57] = DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.ginv[2] = 0.0;
  DifAndCtrl_DW.ginv[10] = 0.0;
  DifAndCtrl_DW.ginv[18] = 2.1037999999999997;
  DifAndCtrl_DW.ginv[26] = DifAndCtrl_DW.D34;
  DifAndCtrl_DW.ginv[34] = DifAndCtrl_DW.D35;
  DifAndCtrl_DW.ginv[42] = 0.0;
  DifAndCtrl_DW.ginv[50] = DifAndCtrl_DW.D37;
  DifAndCtrl_DW.ginv[58] = DifAndCtrl_DW.D38;
  DifAndCtrl_DW.ginv[3] = DifAndCtrl_DW.D14;
  DifAndCtrl_DW.ginv[11] = DifAndCtrl_DW.D24;
  DifAndCtrl_DW.ginv[19] = DifAndCtrl_DW.D34;
  DifAndCtrl_DW.rtb_ginv_tmp_p = 0.006747495411199999 * DifAndCtrl_DW.D14_tmp_cv;
  DifAndCtrl_DW.rtb_ginv_tmp_a = 0.0023282610207999996 * DifAndCtrl_DW.D14_tmp_f;
  DifAndCtrl_DW.rtb_ginv_tmp_m = (((((DifAndCtrl_DW.D47_tmp_p +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0]) +
    0.0018662108031999999) + 0.0009810686847999998) + 0.0013716908347999998) +
    0.0009879776191999998) + 0.0041327000000000004;
  DifAndCtrl_DW.ginv[27] = ((DifAndCtrl_DW.rtb_ginv_tmp_m +
    DifAndCtrl_DW.rtb_ginv_tmp_p) + DifAndCtrl_DW.D47_tmp_px) +
    DifAndCtrl_DW.rtb_ginv_tmp_a;
  DifAndCtrl_DW.ginv[35] = DifAndCtrl_DW.D45_tmp_a;
  DifAndCtrl_DW.ginv[43] = DifAndCtrl_DW.D46;
  DifAndCtrl_DW.ginv[51] = DifAndCtrl_DW.D47;
  DifAndCtrl_DW.ginv[59] = DifAndCtrl_DW.D48_tmp_k;
  DifAndCtrl_DW.ginv[4] = DifAndCtrl_DW.D15;
  DifAndCtrl_DW.ginv[12] = DifAndCtrl_DW.D25;
  DifAndCtrl_DW.ginv[20] = DifAndCtrl_DW.D35;
  DifAndCtrl_DW.ginv[28] = DifAndCtrl_DW.D45_tmp_a;
  DifAndCtrl_DW.D46_tmp_f = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  DifAndCtrl_DW.D46_tmp_p4 = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  DifAndCtrl_DW.rtb_ginv_tmp_m0 =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D46_tmp_da;
  DifAndCtrl_DW.rtb_ginv_tmp_jg = 0.0018662108031999999 *
    DifAndCtrl_DW.D46_tmp_da;
  DifAndCtrl_DW.rtb_ginv_tmp_f = 0.0041327000000000004 *
    DifAndCtrl_DW.D46_tmp_da;
  DifAndCtrl_DW.D46_tmp_o =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.D46_tmp_l5 =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.D46_tmp_m = 0.0013716908347999998 * DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.ginv[36] =
    ((((((((((((((((((((((((((((((DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1
    [0] + DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4]) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0]) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4]) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4]) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8]) +
    0.0018662108031999999) + 0.0009810686847999998) + 0.0013716908347999998) +
    0.0009879776191999998) + 0.0041327000000000004) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D46_tmp_bn) -
                       DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8]
                       * DifAndCtrl_DW.D46_tmp_bn) + 0.0009810686847999998 *
                      DifAndCtrl_DW.D46_tmp_bn) + 0.0009879776191999998 *
                     DifAndCtrl_DW.D46_tmp_bn) + DifAndCtrl_DW.rtb_ginv_tmp_p) +
                   -DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
                   DifAndCtrl_DW.D46_tmp_da) + DifAndCtrl_DW.rtb_ginv_tmp_m0) +
                 DifAndCtrl_DW.rtb_ginv_tmp_jg) + DifAndCtrl_DW.rtb_ginv_tmp_f)
               + 0.0027062010112 * DifAndCtrl_DW.D46_tmp_e) + 0.0040412944 *
              DifAndCtrl_DW.D46_tmp_e) + DifAndCtrl_DW.D47_tmp_px) +
            DifAndCtrl_DW.rtb_ginv_tmp_a) - DifAndCtrl_DW.D46_tmp_o) +
          DifAndCtrl_DW.D46_tmp_l5) + DifAndCtrl_DW.D46_tmp_m) +
        0.0023282610207999996 * DifAndCtrl_DW.rtb_ginv_tmp) +
       0.004761842800000001 * DifAndCtrl_DW.D46_tmp_tmp_k) +
      DifAndCtrl_DW.D46_tmp_p4 * DifAndCtrl_DW.D46_tmp_cs) +
     DifAndCtrl_DW.D46_tmp_f * DifAndCtrl_DW.D46_tmp_c) * 0.5;
  DifAndCtrl_DW.ginv[44] = DifAndCtrl_DW.D56;
  DifAndCtrl_DW.ginv[52] = DifAndCtrl_DW.D45_tmp_a;
  DifAndCtrl_DW.ginv[60] = DifAndCtrl_DW.D45_tmp;
  DifAndCtrl_DW.ginv[5] = DifAndCtrl_DW.D16;
  DifAndCtrl_DW.ginv[13] = DifAndCtrl_DW.D17_tmp_p;
  DifAndCtrl_DW.ginv[21] = 0.0;
  DifAndCtrl_DW.ginv[29] = DifAndCtrl_DW.D46;
  DifAndCtrl_DW.ginv[37] = DifAndCtrl_DW.D56;
  DifAndCtrl_DW.D46_tmp_mc = DifAndCtrl_DW.D14_tmp_k * DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.D46_tmp_h3 = DifAndCtrl_DW.D14_tmp_cv * DifAndCtrl_DW.D14_tmp_cv;
  DifAndCtrl_DW.w_a_tmp = DifAndCtrl_DW.D14_tmp * DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.rtb_ginv_tmp_j = DifAndCtrl_DW.D14_tmp_c *
    DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.rtb_ginv_tmp_e =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  DifAndCtrl_DW.rtb_ginv_tmp_o =
    -DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_f = 2.0 * DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.D14 = DifAndCtrl_DW.rtb_ginv_tmp_tmp_f * DifAndCtrl_DW.D17_tmp_h
    * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.rtb_ginv_tmp_b = DifAndCtrl_DW.D14_tmp_m *
    DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.rtb_ginv_tmp_i =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
    DifAndCtrl_DW.D14_tmp_cv -
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.rtb_ginv_tmp_d =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    DifAndCtrl_DW.D14_tmp_cv +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
    DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.rtb_ginv_tmp_g =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
    DifAndCtrl_DW.D14_tmp_f -
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.rtb_ginv_tmp_l =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D14_tmp_f +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
    DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.rtb_ginv_tmp_db = DifAndCtrl_DW.D46_tmp_h3 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  DifAndCtrl_DW.rtb_ginv_tmp_jr = DifAndCtrl_DW.w_a_tmp *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  DifAndCtrl_DW.D46_tmp_h3 = (DifAndCtrl_DW.D46_tmp_h3 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] +
    DifAndCtrl_DW.w_a_tmp *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0]) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3] *
    DifAndCtrl_DW.D46_tmp;
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_i =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] -
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  DifAndCtrl_DW.w_a_tmp = (DifAndCtrl_DW.rtb_ginv_tmp_tmp_i *
    DifAndCtrl_DW.D46_tmp_n + DifAndCtrl_DW.rtb_ginv_tmp_e) +
    DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D46_tmp_h;
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_b = DifAndCtrl_DW.rtb_ginv_tmp_o *
    DifAndCtrl_DW.D46_tmp_n;
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_e = DifAndCtrl_DW.D46_tmp_f *
    DifAndCtrl_DW.D46_tmp_h;
  DifAndCtrl_DW.rtb_ginv_tmp_e = (DifAndCtrl_DW.rtb_ginv_tmp_tmp_b +
    DifAndCtrl_DW.rtb_ginv_tmp_e) + DifAndCtrl_DW.rtb_ginv_tmp_tmp_e;
  DifAndCtrl_DW.rtb_ginv_tmp_o3 = DifAndCtrl_DW.D46_tmp_mc *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8];
  DifAndCtrl_DW.rtb_ginv_tmp_c = DifAndCtrl_DW.D17_tmp_h *
    DifAndCtrl_DW.rtb_ginv_tmp_j;
  DifAndCtrl_DW.rtb_ginv_tmp_dd = DifAndCtrl_DW.D46_tmp_mc *
    DifAndCtrl_DW.D17_tmp_h;
  DifAndCtrl_DW.ginv[45] =
    ((((((((((((((((((-DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0]
                      + DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1
                      [4]) * DifAndCtrl_DW.D14_tmp_cv * DifAndCtrl_DW.D14_tmp +
                     -DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3]
                     * DifAndCtrl_DW.D56_tmp_tmp_tmp) * DifAndCtrl_DW.D14 +
                    (DifAndCtrl_DW.D17_tmp_h *
                     DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
                     DifAndCtrl_DW.rtb_ginv_tmp_j +
                     DifAndCtrl_DW.rtb_ginv_tmp_o3 * DifAndCtrl_DW.D17_tmp_h)) +
                   ((DifAndCtrl_DW.rtb_ginv_tmp_db +
                     DifAndCtrl_DW.rtb_ginv_tmp_jr) +
                    -DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3] *
                    DifAndCtrl_DW.D46_tmp) * DifAndCtrl_DW.rtb_ginv_tmp_dd) +
                  DifAndCtrl_DW.D46_tmp_h3 * DifAndCtrl_DW.rtb_ginv_tmp_c) +
                 DifAndCtrl_DW.D46_tmp_mc * 0.5 * DifAndCtrl_DW.D17_tmp_h *
                 DifAndCtrl_DW.w_a_tmp) + DifAndCtrl_DW.D17_tmp_h * 0.5 *
                DifAndCtrl_DW.rtb_ginv_tmp_j * DifAndCtrl_DW.rtb_ginv_tmp_e) +
               (DifAndCtrl_DW.rtb_ginv_tmp_o * 0.5 * DifAndCtrl_DW.D46_tmp_h +
                -DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3] *
                DifAndCtrl_DW.D46_tmp_n) * DifAndCtrl_DW.D14) +
              DifAndCtrl_DW.rtb_ginv_tmp_b *
              DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8]) +
             DifAndCtrl_DW.rtb_ginv_tmp_b *
             DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8]) +
            DifAndCtrl_DW.rtb_ginv_tmp_b *
            DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0]) +
           DifAndCtrl_DW.D45_tmp_m * DifAndCtrl_DW.D45_tmp_m * 0.142) +
          DifAndCtrl_DW.D24_tmp_m * DifAndCtrl_DW.D24_tmp_m * 0.143) +
         DifAndCtrl_DW.D24_tmp * DifAndCtrl_DW.D24_tmp * 0.142) +
        DifAndCtrl_DW.ab_a * DifAndCtrl_DW.ab_a * 0.143) +
       DifAndCtrl_DW.rtb_ginv_tmp_i * DifAndCtrl_DW.D14_tmp_k *
       DifAndCtrl_DW.D46_tmp_h2) - DifAndCtrl_DW.rtb_ginv_tmp_d *
      DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D46_tmp_h2) +
     DifAndCtrl_DW.rtb_ginv_tmp_g * DifAndCtrl_DW.D14_tmp_k *
     DifAndCtrl_DW.D46_tmp_h2) - DifAndCtrl_DW.rtb_ginv_tmp_l *
    DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D46_tmp_h2;
  DifAndCtrl_DW.ginv[53] = DifAndCtrl_DW.D24_tmp_p;
  DifAndCtrl_DW.ginv[61] = DifAndCtrl_DW.D46_tmp_e1;
  DifAndCtrl_DW.ginv[6] = DifAndCtrl_DW.D17;
  DifAndCtrl_DW.ginv[14] = DifAndCtrl_DW.D27;
  DifAndCtrl_DW.ginv[22] = DifAndCtrl_DW.D37;
  DifAndCtrl_DW.ginv[30] = DifAndCtrl_DW.D47;
  DifAndCtrl_DW.ginv[38] = DifAndCtrl_DW.D45_tmp_a;
  DifAndCtrl_DW.ginv[46] = DifAndCtrl_DW.D24_tmp_p;
  DifAndCtrl_DW.ginv[54] = (((DifAndCtrl_DW.D47_tmp_p + 0.0018662108031999999) +
    0.0013716908347999998) + 0.0041327000000000004) + DifAndCtrl_DW.D47_tmp_px;
  DifAndCtrl_DW.ginv[62] = DifAndCtrl_DW.D48_tmp;
  DifAndCtrl_DW.ginv[7] = DifAndCtrl_DW.D18;
  DifAndCtrl_DW.ginv[15] = DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.ginv[23] = DifAndCtrl_DW.D38;
  DifAndCtrl_DW.ginv[31] = DifAndCtrl_DW.D48_tmp_k;
  DifAndCtrl_DW.ginv[39] = DifAndCtrl_DW.D45_tmp;
  DifAndCtrl_DW.ginv[47] = DifAndCtrl_DW.D46_tmp_e1;
  DifAndCtrl_DW.ginv[55] = DifAndCtrl_DW.D48_tmp;
  DifAndCtrl_DW.ginv[63] =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] +
    0.0013716908347999998;
  DifAndCtrl_DW.D14 = sin(DifAndCtrl_DW.D56_tmp_tmp);
  DifAndCtrl_DW.D15 = sin(DifAndCtrl_DW.D56_tmp_tmp_f);
  DifAndCtrl_DW.D16 = cos(DifAndCtrl_DW.D56_tmp_tmp_a);
  DifAndCtrl_DW.D17 = cos(DifAndCtrl_DW.D56_tmp_tmp_g2);
  DifAndCtrl_DW.D18 = cos(DifAndCtrl_DW.D46_tmp_tmp_e);
  DifAndCtrl_DW.D24 = cos(DifAndCtrl_DW.D56_tmp_tmp_fi);
  DifAndCtrl_DW.D25 = cos(DifAndCtrl_DW.D56_tmp_tmp_h);
  DifAndCtrl_DW.D17_tmp_p = cos(DifAndCtrl_DW.D46_tmp_tmp_ei);
  DifAndCtrl_DW.D27 = cos(DifAndCtrl_DW.D46_tmp_tmp_c);
  DifAndCtrl_DW.D17_tmp_j = cos(DifAndCtrl_DW.D46_tmp_tmp_a);
  DifAndCtrl_DW.D34 = cos(DifAndCtrl_DW.D56_tmp_tmp_iz);
  DifAndCtrl_DW.D35 = cos(DifAndCtrl_DW.D56_tmp_tmp_g);
  DifAndCtrl_DW.D37 = cos(DifAndCtrl_DW.D46_tmp_tmp_d);
  DifAndCtrl_DW.D38 = cos(DifAndCtrl_DW.D46_tmp_tmp_af);
  DifAndCtrl_DW.D46_tmp_tmp_ei = cos(DifAndCtrl_DW.D56_tmp_tmp_c);
  DifAndCtrl_DW.D46 = cos(DifAndCtrl_DW.D56_tmp_tmp_i);
  DifAndCtrl_DW.D47 = sin(DifAndCtrl_DW.D56_tmp_tmp_ff);
  DifAndCtrl_DW.D56_tmp_tmp_i = sin(DifAndCtrl_DW.rtb_ginv_tmp_tmp);
  DifAndCtrl_DW.D56_tmp_tmp_g = -2.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4];
  DifAndCtrl_DW.D56 = sin(DifAndCtrl_DW.D56_tmp_tmp_f +
    DifAndCtrl_DW.D56_tmp_tmp_g);
  DifAndCtrl_DW.D46_tmp_tmp_a = DifAndCtrl_DW.D46_tmp_tmp * 2.0;
  DifAndCtrl_DW.D57 = sin(DifAndCtrl_DW.D46_tmp_tmp_a);
  DifAndCtrl_DW.D46_tmp_tmp_l *= 2.0;
  DifAndCtrl_DW.D45_tmp = sin(DifAndCtrl_DW.D46_tmp_tmp_l);
  DifAndCtrl_DW.w_a = sin((-DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3] +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]) * 2.0);
  DifAndCtrl_DW.D56_tmp_tmp_h = (DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3]
    + DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]) * 2.0;
  DifAndCtrl_DW.x_a = sin(DifAndCtrl_DW.D56_tmp_tmp_h);
  DifAndCtrl_DW.D56_tmp_tmp_a = DifAndCtrl_DW.D46_tmp_tmp_o * 2.0;
  DifAndCtrl_DW.D24_tmp = sin(DifAndCtrl_DW.D56_tmp_tmp_a);
  DifAndCtrl_DW.D56_tmp_tmp_f = DifAndCtrl_DW.D46_tmp_tmp_o2 * 2.0;
  DifAndCtrl_DW.ab_a = sin(DifAndCtrl_DW.D56_tmp_tmp_f);
  DifAndCtrl_DW.D24_tmp_p = sin(DifAndCtrl_DW.D56_tmp_tmp_h +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]);
  DifAndCtrl_DW.D46_tmp_tmp_af = DifAndCtrl_DW.D15_tmp_tmp +
    DifAndCtrl_DW.D56_tmp_tmp_g;
  DifAndCtrl_DW.D46_tmp_e1 = cos(DifAndCtrl_DW.D46_tmp_tmp_af);
  DifAndCtrl_DW.D47_tmp_p = DifAndCtrl_DW.D15_tmp_tmp_a +
    DifAndCtrl_DW.D56_tmp_tmp_g;
  DifAndCtrl_DW.D46_tmp_tmp_o2 = cos(DifAndCtrl_DW.D47_tmp_p);
  DifAndCtrl_DW.D46_tmp_tmp_o = cos(DifAndCtrl_DW.D46_tmp_tmp_a);
  DifAndCtrl_DW.D46_tmp_tmp_l = cos(DifAndCtrl_DW.D46_tmp_tmp_l);
  DifAndCtrl_DW.D46_tmp_tmp = cos(DifAndCtrl_DW.D56_tmp_tmp_a);
  DifAndCtrl_DW.D56_tmp_tmp_f = cos(DifAndCtrl_DW.D56_tmp_tmp_f);
  DifAndCtrl_DW.D15_tmp_tmp += DifAndCtrl_DW.rtb_ginv_tmp_tmp_p;
  DifAndCtrl_DW.D46_tmp_tmp_e = cos(DifAndCtrl_DW.D15_tmp_tmp);
  DifAndCtrl_DW.D15_tmp_tmp_a += DifAndCtrl_DW.rtb_ginv_tmp_tmp_p;
  DifAndCtrl_DW.D46_tmp_tmp_c = cos(DifAndCtrl_DW.D15_tmp_tmp_a);
  DifAndCtrl_DW.D46_tmp_tmp_a = sin(DifAndCtrl_DW.D46_tmp_tmp_a +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7]);
  DifAndCtrl_DW.D46_tmp_tmp_d = sin(DifAndCtrl_DW.D56_tmp_tmp_g +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]);
  DifAndCtrl_DW.D46_tmp_tmp_af = sin(DifAndCtrl_DW.D46_tmp_tmp_af);
  DifAndCtrl_DW.D47_tmp_p = sin(DifAndCtrl_DW.D47_tmp_p);
  DifAndCtrl_DW.D56_tmp_tmp_ff = sin(DifAndCtrl_DW.D56_tmp_tmp_ff +
    DifAndCtrl_DW.D56_tmp_tmp_g);
  DifAndCtrl_DW.D48_tmp = sin((DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3] -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]) * 2.0);
  DifAndCtrl_DW.D56_tmp_tmp = sin(DifAndCtrl_DW.rtb_ginv_tmp_tmp_p +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]);
  DifAndCtrl_DW.D15_tmp_tmp = sin(DifAndCtrl_DW.D15_tmp_tmp);
  DifAndCtrl_DW.D15_tmp_tmp_a = sin(DifAndCtrl_DW.D15_tmp_tmp_a);
  DifAndCtrl_DW.D56_tmp_tmp_h = sin(DifAndCtrl_DW.D56_tmp_tmp_h +
    DifAndCtrl_DW.D14_tmp_tmp);
  DifAndCtrl_DW.D56_tmp_tmp_a = sin(DifAndCtrl_DW.D56_tmp_tmp_a +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7]);
  DifAndCtrl_DW.D56_tmp_tmp_iz = sin(DifAndCtrl_DW.D56_tmp_tmp_g +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7]);
  DifAndCtrl_DW.D56_tmp_tmp_g = sin(DifAndCtrl_DW.D14_tmp_tmp +
    DifAndCtrl_DW.D56_tmp_tmp_g);
  DifAndCtrl_DW.D56_tmp_tmp_g2 = sin(DifAndCtrl_DW.rtb_ginv_tmp_tmp_p +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7]);
  DifAndCtrl_DW.D14_tmp_tmp = sin(DifAndCtrl_DW.D14_tmp_tmp +
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_p);
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_p = cos(DifAndCtrl_DW.rtb_ginv_tmp_tmp_p);
  DifAndCtrl_DW.D14_tmp_ms = DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D14_tmp_m
    + DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D14_tmp_b;
  DifAndCtrl_DW.D14_tmp_o3 = DifAndCtrl_DW.D14_tmp_m3 * DifAndCtrl_DW.s;
  DifAndCtrl_DW.D56_tmp_tmp_fi = 2.0 * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.D56_tmp_tmp_c = 0.09794 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7] * 0.143;
  DifAndCtrl_DW.D16_tmp_p = DifAndCtrl_DW.D16_tmp_p * DifAndCtrl_DW.D14_tmp_m +
    DifAndCtrl_DW.D14_tmp_cz;
  DifAndCtrl_DW.rtb_ginv_tmp_tmp = DifAndCtrl_DW.D16_tmp_p *
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_f;
  DifAndCtrl_DW.d = DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.d1 = 2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.d2 = -2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6];
  DifAndCtrl_DW.d145 = -2.0 * DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.D14_tmp_o3 = (DifAndCtrl_DW.D14_tmp_o3 - DifAndCtrl_DW.D16_tmp_o)
    * DifAndCtrl_DW.D56_tmp_tmp_fi + DifAndCtrl_DW.D16_tmp_k *
    DifAndCtrl_DW.d145;
  DifAndCtrl_DW.D16_tmp_o = ((DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3] -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[5]) +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]) +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.D16_tmp_k = ((DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[3] +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[5]) +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[6]) +
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[7];
  DifAndCtrl_DW.d8 = 2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6];
  DifAndCtrl_DW.d10 = 2.0 * DifAndCtrl_DW.s;
  DifAndCtrl_DW.x[24] = -(((((((DifAndCtrl_DW.D14_tmp_o * DifAndCtrl_DW.smax -
    DifAndCtrl_DW.D14_tmp_nh) * DifAndCtrl_DW.D14_tmp_c +
    DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D14_tmp_k) * (DifAndCtrl_DW.d8 *
    DifAndCtrl_DW.D14_tmp_cv) + ((DifAndCtrl_DW.d10 * DifAndCtrl_DW.D15_tmp_g1 *
    DifAndCtrl_DW.D14_tmp_m + (cos(DifAndCtrl_DW.D16_tmp_o) - cos
    (DifAndCtrl_DW.D16_tmp_k))) * DifAndCtrl_DW.D56_tmp_tmp_c + DifAndCtrl_DW.d1
    * DifAndCtrl_DW.s * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D34_tmp_l)) +
    (DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D14_tmp_c +
     DifAndCtrl_DW.D14_tmp_pe) * (DifAndCtrl_DW.d2 * DifAndCtrl_DW.D14_tmp)) +
    ((DifAndCtrl_DW.D16_tmp_i - DifAndCtrl_DW.d) * DifAndCtrl_DW.D56_tmp_tmp_fi
     + DifAndCtrl_DW.rtb_ginv_tmp_tmp) *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3]) + DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]) * 0.5);
  DifAndCtrl_DW.x[32] = -((((DifAndCtrl_DW.D15_tmp_c *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.smax + DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.s *
    DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D34_tmp_m) +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * DifAndCtrl_DW.s *
    DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D37_tmp) +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * DifAndCtrl_DW.s *
    DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D34_tmp_l) +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * DifAndCtrl_DW.s *
    DifAndCtrl_DW.D15_tmp_c * DifAndCtrl_DW.D14_tmp_m);
  DifAndCtrl_DW.D14_tmp_ms = -0.19588 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7] * 0.143;
  DifAndCtrl_DW.D14_tmp_o = -DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.smax +
    DifAndCtrl_DW.d;
  DifAndCtrl_DW.D14_tmp_nh = -2.0 * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.x[40] = -(((((((DifAndCtrl_DW.D17_tmp_tmp_i *
    DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.D17_tmp_tmp) *
    -DifAndCtrl_DW.D14_tmp_m3 + DifAndCtrl_DW.D27_tmp_o) +
    DifAndCtrl_DW.D27_tmp_m) * DifAndCtrl_DW.d2 + (DifAndCtrl_DW.D15_tmp_c *
    DifAndCtrl_DW.d1 * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.smax +
    (DifAndCtrl_DW.D27_tmp * DifAndCtrl_DW.D14_tmp_p +
     DifAndCtrl_DW.D17_tmp_tmp_a * DifAndCtrl_DW.D14_tmp_f) *
    DifAndCtrl_DW.D14_tmp_ms)) + (DifAndCtrl_DW.D14_tmp_o *
    DifAndCtrl_DW.D14_tmp_nh + DifAndCtrl_DW.rtb_ginv_tmp_tmp) *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]) + DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3]) * 0.5);
  DifAndCtrl_DW.D14_tmp_o3 = 0.09794 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.143;
  DifAndCtrl_DW.rtb_ginv_tmp_tmp = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3]
    + DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6];
  DifAndCtrl_DW.D17_tmp_tmp = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D17_tmp_tmp_i = 0.11464 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.142 *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D14_tmp_pe = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    0.17 * 0.143 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D16_tmp = DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D16_tmp_i = 2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.D27_tmp_o = 0.09794 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.143;
  DifAndCtrl_DW.D27_tmp_m = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7];
  DifAndCtrl_DW.d3 = DifAndCtrl_DW.D27_tmp_m * 2.0 +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3];
  DifAndCtrl_DW.d4 = -2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.D14_tmp_cx *= DifAndCtrl_DW.D27_tmp_o;
  DifAndCtrl_DW.d5 = DifAndCtrl_DW.rtb_ginv_tmp_tmp - DifAndCtrl_DW.D17_tmp_tmp;
  DifAndCtrl_DW.d6 = DifAndCtrl_DW.rtb_ginv_tmp_tmp +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7];
  DifAndCtrl_DW.d7 = DifAndCtrl_DW.d6 - DifAndCtrl_DW.D17_tmp_tmp;
  DifAndCtrl_DW.d9 = DifAndCtrl_DW.d4 * 0.040588879999999994;
  DifAndCtrl_DW.d11 = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    0.040588879999999994;
  DifAndCtrl_DW.d12 = DifAndCtrl_DW.d4 * DifAndCtrl_DW.D14_tmp_m +
    DifAndCtrl_DW.d3;
  DifAndCtrl_DW.d42 = 0.22928 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.d45 = 0.19588 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.d83 = -2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3];
  DifAndCtrl_DW.x[48] = -(((((((((((((((((DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D14_tmp_f * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D14_tmp_c +
    DifAndCtrl_DW.d11 * DifAndCtrl_DW.D14_tmp_cv * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.D14_tmp_c) + DifAndCtrl_DW.d42 * 0.142 *
    DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp) + DifAndCtrl_DW.D16_tmp_i *
    0.17 * 0.143 * DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp) +
    DifAndCtrl_DW.D17_tmp_tmp_i * DifAndCtrl_DW.D34_tmp) +
    DifAndCtrl_DW.D14_tmp_pe * DifAndCtrl_DW.D34_tmp) + DifAndCtrl_DW.d45 *
    0.143 * DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp_p) +
    DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.D34_tmp_m) + -0.22928 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.142 *
    DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp * DifAndCtrl_DW.D14_tmp_m) +
    -0.22928 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * 0.142 *
    DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp * DifAndCtrl_DW.D14_tmp_m) +
    DifAndCtrl_DW.d83 * 0.17 * 0.143 * DifAndCtrl_DW.D14_tmp_c *
    DifAndCtrl_DW.D14_tmp * DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.d2 * 0.17 *
    0.143 * DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp *
    DifAndCtrl_DW.D14_tmp_m) + -0.19588 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.143 *
    DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp_p * DifAndCtrl_DW.D14_tmp_m)
    + -0.19588 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * 0.143 *
    DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp_p * DifAndCtrl_DW.D14_tmp_m)
    + DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D14_tmp_c *
    DifAndCtrl_DW.D14_tmp_p * DifAndCtrl_DW.D14_tmp_m) * DifAndCtrl_DW.s +
    (DifAndCtrl_DW.d7 * DifAndCtrl_DW.D14_tmp_n + DifAndCtrl_DW.d5 *
     DifAndCtrl_DW.D16_tmp_tmp) * (DifAndCtrl_DW.D56_tmp_tmp_fi *
    DifAndCtrl_DW.smax)) + ((((DifAndCtrl_DW.rtb_ginv_tmp_tmp * 2.0 *
    0.040588879999999994 + DifAndCtrl_DW.D14_tmp_cx) * DifAndCtrl_DW.D14_tmp_m +
    DifAndCtrl_DW.d9) * DifAndCtrl_DW.D14_tmp_cv +
    ((((DifAndCtrl_DW.D17_tmp_tmp_i * DifAndCtrl_DW.D14_tmp +
        DifAndCtrl_DW.D14_tmp_pe * DifAndCtrl_DW.D14_tmp) +
       DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.D14_tmp_p) -
      DifAndCtrl_DW.D27_tmp_o * DifAndCtrl_DW.D14_tmp * DifAndCtrl_DW.D14_tmp_b *
      DifAndCtrl_DW.D14_tmp_m) - (DifAndCtrl_DW.D16_tmp_i - DifAndCtrl_DW.d3 *
    DifAndCtrl_DW.D14_tmp_m) * DifAndCtrl_DW.D14_tmp_n)) * DifAndCtrl_DW.s +
    ((DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * DifAndCtrl_DW.D14_tmp_cv *
      DifAndCtrl_DW.D14_tmp_b + DifAndCtrl_DW.d12 * DifAndCtrl_DW.D14_tmp_p) *
     0.01400542 + (DifAndCtrl_DW.d5 * 0.08117775999999999 +
                   DifAndCtrl_DW.D14_tmp_cx) * DifAndCtrl_DW.D14_tmp) *
    DifAndCtrl_DW.smax) * DifAndCtrl_DW.D14_tmp_k) * 0.5);
  DifAndCtrl_DW.D14_tmp_ms = DifAndCtrl_DW.d6 * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.d2 = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D17_tmp_tmp_i = 2.0 * DifAndCtrl_DW.D14_tmp_f;
  DifAndCtrl_DW.D14_tmp_pe = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] -
    DifAndCtrl_DW.D14_tmp_ms;
  DifAndCtrl_DW.x[56] = -(((((DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    DifAndCtrl_DW.D14_tmp_f * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D14_tmp_c +
    DifAndCtrl_DW.d2 * DifAndCtrl_DW.D34_tmp_m) + DifAndCtrl_DW.D56_tmp_tmp_fi *
    DifAndCtrl_DW.D14_tmp_p * DifAndCtrl_DW.D14_tmp_pe) * DifAndCtrl_DW.s +
    DifAndCtrl_DW.D17_tmp_tmp_i * DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.smax *
    DifAndCtrl_DW.d7) + (((DifAndCtrl_DW.D14_tmp_ms -
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]) *
    DifAndCtrl_DW.D17_tmp_tmp_i + DifAndCtrl_DW.d2 * DifAndCtrl_DW.D14_tmp_p) *
    DifAndCtrl_DW.s + 2.0 * DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_p *
    DifAndCtrl_DW.d7) * DifAndCtrl_DW.D14_tmp_k) * 0.00700271);
  DifAndCtrl_DW.D14_tmp_ms = DifAndCtrl_DW.D15_tmp_tmp_c +
    DifAndCtrl_DW.D15_tmp_tmp_f;
  DifAndCtrl_DW.D56_tmp_tmp_fi = DifAndCtrl_DW.d2 * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.d2 = DifAndCtrl_DW.D14_tmp_ms *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6];
  DifAndCtrl_DW.x[25] = -(((((((((cos(DifAndCtrl_DW.D16_tmp_o -
    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]) - cos
    (DifAndCtrl_DW.D16_tmp_k - DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]))
    - cos(DifAndCtrl_DW.D16_tmp_o +
          DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4])) + cos
    (DifAndCtrl_DW.D16_tmp_k + DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]))
    + sin(DifAndCtrl_DW.D16_tmp_o) * 2.0) + sin(DifAndCtrl_DW.D16_tmp_k) * 2.0) *
    (-0.024485 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7] * 0.143) +
    (-DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * DifAndCtrl_DW.s *
     DifAndCtrl_DW.D37_tmp + DifAndCtrl_DW.D34_tmp_l *
     DifAndCtrl_DW.D56_tmp_tmp_fi)) + DifAndCtrl_DW.d2 * DifAndCtrl_DW.smax *
    DifAndCtrl_DW.D14_tmp_m) + (DifAndCtrl_DW.D15_tmp_c * DifAndCtrl_DW.smax *
    DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.D34_tmp_l * -DifAndCtrl_DW.s) *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3]) + (DifAndCtrl_DW.D16_tmp_p *
    DifAndCtrl_DW.D14_tmp_c + DifAndCtrl_DW.D14_tmp_o * DifAndCtrl_DW.D14_tmp_k)
    * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]);
  DifAndCtrl_DW.D16_tmp_p = DifAndCtrl_DW.D15_tmp_c *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.D16_tmp_o = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.x[33] = -((((-DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    DifAndCtrl_DW.s * DifAndCtrl_DW.D15_tmp_c * DifAndCtrl_DW.D15_tmp +
    DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.smax *
    DifAndCtrl_DW.D34_tmp_m) + DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] *
    DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.smax * DifAndCtrl_DW.D37_tmp) +
    DifAndCtrl_DW.D16_tmp_o * DifAndCtrl_DW.smax * DifAndCtrl_DW.D34_tmp_l) +
    DifAndCtrl_DW.D16_tmp_p * DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_m);
  DifAndCtrl_DW.D16_tmp_k = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] -
    DifAndCtrl_DW.rtb_ginv_tmp_tmp * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.D14_tmp_o = (((DifAndCtrl_DW.d8 +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3]) * 0.17 * 0.143 +
    DifAndCtrl_DW.rtb_ginv_tmp_tmp * 0.22928 * 0.142) + DifAndCtrl_DW.d9 *
    DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] *
    0.17 * 0.143 * DifAndCtrl_DW.rtb_ginv_tmp_b;
  DifAndCtrl_DW.D17_tmp_tmp_i = 4.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.D16_tmp = -4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6];
  DifAndCtrl_DW.d3 = -4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7];
  DifAndCtrl_DW.x[41] = -((((((((((-3.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] + DifAndCtrl_DW.D16_tmp) +
    DifAndCtrl_DW.d3) + DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] *
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_p) + DifAndCtrl_DW.D17_tmp_tmp_i *
    DifAndCtrl_DW.D14_tmp_m) * (-0.00700271 * DifAndCtrl_DW.D14_tmp_f) +
    (-DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * DifAndCtrl_DW.D14_tmp_m +
     DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3]) * 0.047378399999999994) +
    DifAndCtrl_DW.D14_tmp_o * DifAndCtrl_DW.D14_tmp_cv) * DifAndCtrl_DW.smax +
    ((DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.08312 * 0.285 *
      DifAndCtrl_DW.D15_tmp + DifAndCtrl_DW.D16_tmp_k *
      DifAndCtrl_DW.D14_tmp_tmp_h) + DifAndCtrl_DW.D14_tmp_pe *
     DifAndCtrl_DW.D14_tmp_tmp_m) * DifAndCtrl_DW.d10) *
    -DifAndCtrl_DW.D14_tmp_k + ((((-DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE
    [3] * DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE
    [5]) * 0.023689199999999997 + DifAndCtrl_DW.D16_tmp_k *
    DifAndCtrl_DW.D16_tmp_tmp) + DifAndCtrl_DW.D14_tmp_pe *
    DifAndCtrl_DW.D14_tmp_n) * DifAndCtrl_DW.D14_tmp_c +
    (DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D15_tmp_g1 * DifAndCtrl_DW.D15_tmp
     + DifAndCtrl_DW.d11 * DifAndCtrl_DW.D15_tmp_g * DifAndCtrl_DW.D15_tmp)) * (
    -2.0 * DifAndCtrl_DW.s)) + (((DifAndCtrl_DW.rtb_ginv_tmp_b *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] + DifAndCtrl_DW.d12) *
    DifAndCtrl_DW.D14_tmp_tmp_m + DifAndCtrl_DW.D14_tmp_o *
    DifAndCtrl_DW.D14_tmp) * DifAndCtrl_DW.D14_tmp_c +
    (-DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.17 * 0.143 *
     DifAndCtrl_DW.D15_tmp_g * DifAndCtrl_DW.D17_tmp_h - DifAndCtrl_DW.D27_tmp_o
     * DifAndCtrl_DW.D15_tmp_g1 * DifAndCtrl_DW.D17_tmp_h)) * DifAndCtrl_DW.smax)
    * 0.5);
  DifAndCtrl_DW.D14_tmp_o3 = DifAndCtrl_DW.D16_tmp_tmp + DifAndCtrl_DW.D14_tmp_n;
  DifAndCtrl_DW.x[49] = -((((DifAndCtrl_DW.D14_tmp_ms *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * DifAndCtrl_DW.smax *
    DifAndCtrl_DW.D14_tmp_m + (-DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] *
    DifAndCtrl_DW.s * DifAndCtrl_DW.D37_tmp + DifAndCtrl_DW.D56_tmp_tmp_fi *
    DifAndCtrl_DW.D37_tmp)) - (DifAndCtrl_DW.s * DifAndCtrl_DW.D34_tmp_m -
    DifAndCtrl_DW.D15_tmp_g1 * DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_m) *
    DifAndCtrl_DW.D56_tmp_tmp_c) + (DifAndCtrl_DW.D14_tmp_ms *
    DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_m + DifAndCtrl_DW.D37_tmp *
    -DifAndCtrl_DW.s) * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6]) +
    ((DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.s * DifAndCtrl_DW.D14_tmp_m +
      DifAndCtrl_DW.D14_tmp_cz) * DifAndCtrl_DW.D14_tmp_c +
     (-DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.smax + DifAndCtrl_DW.d) *
     DifAndCtrl_DW.D14_tmp_k) * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]);
  DifAndCtrl_DW.x[57] = -(((((DifAndCtrl_DW.d6 -
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4]) * DifAndCtrl_DW.D46_tmp_dy +
    DifAndCtrl_DW.D16_tmp_i * DifAndCtrl_DW.D15_tmp_g1) - (DifAndCtrl_DW.d6 +
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4]) * DifAndCtrl_DW.D46_tmp_ln) *
    DifAndCtrl_DW.smax + DifAndCtrl_DW.d10 * DifAndCtrl_DW.D34_tmp_m *
    DifAndCtrl_DW.d7) * -0.00700271);
  DifAndCtrl_DW.x[26] = -(((DifAndCtrl_DW.D56_tmp_tmp_c *
    DifAndCtrl_DW.D15_tmp_g1 * DifAndCtrl_DW.D15_tmp + DifAndCtrl_DW.d2 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.D15_tmp_c *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * DifAndCtrl_DW.D15_tmp) -
    DifAndCtrl_DW.D34_tmp_l * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    DifAndCtrl_DW.D14_tmp_m);
  DifAndCtrl_DW.x[34] = -(((DifAndCtrl_DW.D16_tmp_p * DifAndCtrl_DW.D15_tmp -
    DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.D34_tmp_m *
    DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.D37_tmp *
    -DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * DifAndCtrl_DW.D14_tmp_m) -
    DifAndCtrl_DW.D34_tmp_l * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] *
    DifAndCtrl_DW.D14_tmp_m);
  DifAndCtrl_DW.x[42] = -0.0;
  DifAndCtrl_DW.x[50] = -((DifAndCtrl_DW.d6 * 0.09794 * 0.143 *
    DifAndCtrl_DW.D15_tmp_g1 * DifAndCtrl_DW.D15_tmp +
    DifAndCtrl_DW.rtb_ginv_tmp_tmp * 0.040588879999999994 *
    DifAndCtrl_DW.D15_tmp_g * DifAndCtrl_DW.D15_tmp) - DifAndCtrl_DW.D37_tmp *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * DifAndCtrl_DW.D14_tmp_m);
  DifAndCtrl_DW.x[58] = -((DifAndCtrl_DW.d6 * DifAndCtrl_DW.D15_tmp_g1 *
    DifAndCtrl_DW.D15_tmp - DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    DifAndCtrl_DW.D34_tmp_m * DifAndCtrl_DW.D14_tmp_m) * 0.01400542);
  DifAndCtrl_DW.x[27] = -(-DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] *
    0.08312 * 0.040588879999999994 * DifAndCtrl_DW.D14_tmp -
    (DifAndCtrl_DW.D27_tmp_m * 0.08312 * DifAndCtrl_DW.D14_tmp_p +
     DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7] * 0.17 *
     DifAndCtrl_DW.D14_tmp_b) * 0.01400542);
  DifAndCtrl_DW.D14_tmp_ms =
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D14;
  DifAndCtrl_DW.D14_tmp_o3 =
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.D14;
  DifAndCtrl_DW.D56_tmp_tmp_fi = 0.0009810686847999998 * DifAndCtrl_DW.D14;
  DifAndCtrl_DW.D56_tmp_tmp_c = 0.0009879776191999998 * DifAndCtrl_DW.D14;
  DifAndCtrl_DW.D16_tmp_p =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d2 = 0.0018662108031999999 * DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.D16_tmp_k = 0.0041327000000000004 * DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d10 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0]
    * DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.D14_tmp_o =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.D14_tmp_pe = 0.0013716908347999998 * DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.D27_tmp_o = DifAndCtrl_DW.D56_tmp_ad * DifAndCtrl_DW.D46_tmp_p;
  DifAndCtrl_DW.D27_tmp_m =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.D14_tmp_cx =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.d9 = 0.0018662108031999999 * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.d11 = 0.0041327000000000004 * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.d12 = 0.004761842800000001 * DifAndCtrl_DW.D27;
  DifAndCtrl_DW.D14_tmp_f = DifAndCtrl_DW.D56_tmp_k * DifAndCtrl_DW.D46_tmp_l;
  DifAndCtrl_DW.D14_tmp_n = 0.004761842800000001 * DifAndCtrl_DW.D35;
  DifAndCtrl_DW.D14_tmp_tmp_h =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.D14_tmp_tmp_m =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.D14_tmp_cz = 0.0013716908347999998 * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.D15_tmp_tmp_c = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D15_tmp_tmp_f = 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D16_tmp_tmp = 0.0037324216063999997 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D34_tmp_l = 0.0027433816695999996 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.D37_tmp = 0.008265400000000001 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.rtb_ginv_tmp_b = DifAndCtrl_DW.D56_tmp_p *
    DifAndCtrl_DW.D46_tmp_j;
  DifAndCtrl_DW.d54 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0]
    * DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.d55 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4]
    * DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.d56 = 0.0018662108031999999 * DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.d57 = 0.0041327000000000004 * DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.d58 = 0.004761842800000001 * DifAndCtrl_DW.D37;
  DifAndCtrl_DW.d59 = DifAndCtrl_DW.D56_tmp_bp * DifAndCtrl_DW.D46_tmp_d;
  DifAndCtrl_DW.d60 = 0.004761842800000001 * DifAndCtrl_DW.D46;
  DifAndCtrl_DW.d61 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0]
    * DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.d62 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4]
    * DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.d63 = 0.0013716908347999998 * DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.d64 = DifAndCtrl_DW.D56_tmp_c * DifAndCtrl_DW.D46_tmp_g;
  DifAndCtrl_DW.d65 = DifAndCtrl_DW.D46_tmp_p4 * DifAndCtrl_DW.D56_tmp_d;
  DifAndCtrl_DW.d66 = DifAndCtrl_DW.D56_tmp_nb * DifAndCtrl_DW.D46_tmp_dy;
  DifAndCtrl_DW.d67 = DifAndCtrl_DW.D46_tmp_f * DifAndCtrl_DW.D56_tmp_lx;
  DifAndCtrl_DW.d68 = DifAndCtrl_DW.D56_tmp_ij * DifAndCtrl_DW.D46_tmp_b;
  DifAndCtrl_DW.d69 = DifAndCtrl_DW.D46_tmp_p4 * DifAndCtrl_DW.D56_tmp_b;
  DifAndCtrl_DW.d70 = DifAndCtrl_DW.D56_tmp_m * DifAndCtrl_DW.D46_tmp_ln;
  DifAndCtrl_DW.d71 = DifAndCtrl_DW.D46_tmp_f * DifAndCtrl_DW.D56_tmp_h;
  DifAndCtrl_DW.tmp_tmp =
    (DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] -
     DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8]) +
    0.0019690463039999996;
  DifAndCtrl_DW.d53 =
    ((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.tmp_tmp *
    DifAndCtrl_DW.D25 + 0.006747495411199999 * DifAndCtrl_DW.D17_tmp_p) +
    DifAndCtrl_DW.D27_tmp_o) + 0.0027062010112 * DifAndCtrl_DW.D16) +
    0.0040412944 * DifAndCtrl_DW.D16) - DifAndCtrl_DW.D27_tmp_m) +
    DifAndCtrl_DW.D14_tmp_cx) + DifAndCtrl_DW.d9) + DifAndCtrl_DW.d11) +
    DifAndCtrl_DW.d12) + 0.0023282610207999996 * DifAndCtrl_DW.D17_tmp_j) +
    DifAndCtrl_DW.D14_tmp_f) + 0.0023282610207999996 * DifAndCtrl_DW.D34) +
    DifAndCtrl_DW.D14_tmp_n) - DifAndCtrl_DW.D14_tmp_tmp_h) +
    DifAndCtrl_DW.D14_tmp_tmp_m) + DifAndCtrl_DW.D14_tmp_cz) +
    DifAndCtrl_DW.D15_tmp_tmp_c) + DifAndCtrl_DW.D15_tmp_tmp_f) + 2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.D16_tmp_tmp) + 0.0019621373695999996 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.D34_tmp_l) + 0.0019759552383999996 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.D37_tmp) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D17) -
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.D17) + 0.0009810686847999998 * DifAndCtrl_DW.D17) +
    0.0009879776191999998 * DifAndCtrl_DW.D17) + 0.0027062010112 *
    DifAndCtrl_DW.D18) + 0.0040412944 * DifAndCtrl_DW.D18) +
    DifAndCtrl_DW.rtb_ginv_tmp_b) + 0.0027062010112 * DifAndCtrl_DW.D24) +
    0.0040412944 * DifAndCtrl_DW.D24) - DifAndCtrl_DW.d54) + DifAndCtrl_DW.d55)
                     + DifAndCtrl_DW.d56) + DifAndCtrl_DW.d57) +
                   DifAndCtrl_DW.d58) + 0.0023282610207999996 *
                  DifAndCtrl_DW.D38) + DifAndCtrl_DW.d59) +
                0.0023282610207999996 * DifAndCtrl_DW.D46_tmp_tmp_ei) +
               DifAndCtrl_DW.d60) - DifAndCtrl_DW.d61) + DifAndCtrl_DW.d62) +
            DifAndCtrl_DW.d63) + DifAndCtrl_DW.d64) + DifAndCtrl_DW.d65) +
         DifAndCtrl_DW.d66) + DifAndCtrl_DW.d67) + DifAndCtrl_DW.d68) +
      DifAndCtrl_DW.d69) + DifAndCtrl_DW.d70) + DifAndCtrl_DW.d71;
  DifAndCtrl_DW.d156 = DifAndCtrl_DW.D56_tmp_o3 * DifAndCtrl_DW.D46_tmp_da +
    DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.d157 = 0.004761842800000001 * DifAndCtrl_DW.D56_tmp_tmp_i;
  DifAndCtrl_DW.x[35] = -(((((((((((((((((DifAndCtrl_DW.d156 +
    DifAndCtrl_DW.D14_tmp_ms) - DifAndCtrl_DW.D14_tmp_o3) +
    DifAndCtrl_DW.D56_tmp_tmp_fi) + DifAndCtrl_DW.D56_tmp_tmp_c) -
    DifAndCtrl_DW.D16_tmp_p) + DifAndCtrl_DW.d) + DifAndCtrl_DW.d2) +
    DifAndCtrl_DW.D16_tmp_k) + 0.0027062010112 * DifAndCtrl_DW.D15) +
    0.0040412944 * DifAndCtrl_DW.D15) - DifAndCtrl_DW.d10) +
    DifAndCtrl_DW.D14_tmp_o) + DifAndCtrl_DW.D14_tmp_pe) + 0.0023282610207999996
    * DifAndCtrl_DW.D47) + DifAndCtrl_DW.d157) * DifAndCtrl_DW.d1 +
    DifAndCtrl_DW.d53 * -DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]) * 0.25);
  DifAndCtrl_DW.d13 = -2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.d14 = DifAndCtrl_DW.d13 * 0.0069089343999999995;
  DifAndCtrl_DW.d15 = -4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.d16 = -0.45856 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    0.08312 * 0.142;
  DifAndCtrl_DW.tmp_tmp_g = DifAndCtrl_DW.d15 * 0.08312 * 0.17 * 0.143;
  DifAndCtrl_DW.d17 = -0.39176 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.d18 = DifAndCtrl_DW.d17 * 0.08312 * 0.143;
  DifAndCtrl_DW.d17 = DifAndCtrl_DW.d17 * 0.17 * 0.143;
  DifAndCtrl_DW.d19 = DifAndCtrl_DW.d15 * 0.0069089343999999995;
  DifAndCtrl_DW.d20 = DifAndCtrl_DW.d13 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4];
  DifAndCtrl_DW.d21 = DifAndCtrl_DW.d1 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8];
  DifAndCtrl_DW.d22 = DifAndCtrl_DW.d14 * 0.142;
  DifAndCtrl_DW.d14 *= 0.143;
  DifAndCtrl_DW.d23 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  DifAndCtrl_DW.d24 = DifAndCtrl_DW.d1 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  DifAndCtrl_DW.d25 = DifAndCtrl_DW.d13 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  DifAndCtrl_DW.d26 = -0.0262846592 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.142;
  DifAndCtrl_DW.d27 = DifAndCtrl_DW.d13 * 0.028900000000000006 * 0.143;
  DifAndCtrl_DW.d28 = 4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.d29 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  DifAndCtrl_DW.tmp_tmp_n = DifAndCtrl_DW.d1 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  DifAndCtrl_DW.tmp_tmp_d = DifAndCtrl_DW.d13 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  DifAndCtrl_DW.tmp_tmp_na = -0.0191844872 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.143;
  DifAndCtrl_DW.d30 = DifAndCtrl_DW.d4 * 0.0069089343999999995;
  DifAndCtrl_DW.d31 = -0.39176 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.d32 = -0.19588 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.d33 = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    0.0069089343999999995;
  DifAndCtrl_DW.d34 = DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4]
    * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.tmp_tmp_f1 = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8];
  DifAndCtrl_DW.d35 = DifAndCtrl_DW.d33 * 0.142;
  DifAndCtrl_DW.d33 *= 0.143;
  DifAndCtrl_DW.tmp_tmp_oo =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.tmp_tmp_jk =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.tmp_tmp_cm = 0.0131423296 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.142;
  DifAndCtrl_DW.d36 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  DifAndCtrl_DW.tmp_tmp_fq =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.tmp_tmp_nl =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.tmp_tmp_c = 0.0095922436 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.143;
  DifAndCtrl_DW.d37 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  DifAndCtrl_DW.d38 = -0.22928 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    0.08312 * 0.142;
  DifAndCtrl_DW.d39 = DifAndCtrl_DW.d4 * 0.08312;
  DifAndCtrl_DW.d40 = DifAndCtrl_DW.d32 * 0.08312 * 0.143;
  DifAndCtrl_DW.d32 = DifAndCtrl_DW.d32 * 0.17 * 0.143;
  DifAndCtrl_DW.d41 = 0.17 * DifAndCtrl_DW.D14_tmp_b + 0.08312 *
    DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.d43 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.d44 = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    0.028900000000000006 * 0.143;
  DifAndCtrl_DW.d46 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.d47 = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.d48 = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.d49 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.d50 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.d51 = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.d52 = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.d82 = DifAndCtrl_DW.d20 * DifAndCtrl_DW.D25;
  DifAndCtrl_DW.d84 = DifAndCtrl_DW.d21 * DifAndCtrl_DW.D25;
  DifAndCtrl_DW.d85 = DifAndCtrl_DW.d22 * DifAndCtrl_DW.D25;
  DifAndCtrl_DW.d86 = DifAndCtrl_DW.d14 * DifAndCtrl_DW.D25;
  DifAndCtrl_DW.d102 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.d87 = DifAndCtrl_DW.d102 * DifAndCtrl_DW.D46_tmp_p;
  DifAndCtrl_DW.d88 = DifAndCtrl_DW.d23 * DifAndCtrl_DW.D46_tmp_tmp_o;
  DifAndCtrl_DW.d89 = DifAndCtrl_DW.d16 * DifAndCtrl_DW.D16;
  DifAndCtrl_DW.d90 = DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D16;
  DifAndCtrl_DW.d91 = DifAndCtrl_DW.d24 * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.d92 = DifAndCtrl_DW.d25 * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.d93 = DifAndCtrl_DW.d26 * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.d94 = DifAndCtrl_DW.d27 * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.d103 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.d95 = DifAndCtrl_DW.d103 * DifAndCtrl_DW.D46_tmp_l;
  DifAndCtrl_DW.d96 = DifAndCtrl_DW.d29 * DifAndCtrl_DW.D46_tmp_tmp_l;
  DifAndCtrl_DW.d97 = DifAndCtrl_DW.d18 * DifAndCtrl_DW.D34;
  DifAndCtrl_DW.d98 = DifAndCtrl_DW.d17 * DifAndCtrl_DW.D35;
  DifAndCtrl_DW.d99 = DifAndCtrl_DW.tmp_tmp_n * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.d100 = DifAndCtrl_DW.tmp_tmp_d * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.d101 = DifAndCtrl_DW.tmp_tmp_na * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.d104 = DifAndCtrl_DW.d32 * DifAndCtrl_DW.D46_tmp_tmp_a;
  DifAndCtrl_DW.d105 = DifAndCtrl_DW.d39 * 0.17 * 0.143;
  DifAndCtrl_DW.d106 = -4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.d107 = DifAndCtrl_DW.d38 * DifAndCtrl_DW.D56;
  DifAndCtrl_DW.d108 = DifAndCtrl_DW.d40 * DifAndCtrl_DW.D56_tmp_tmp_ff;
  DifAndCtrl_DW.d109 = DifAndCtrl_DW.tmp_tmp_f1 * DifAndCtrl_DW.D48_tmp;
  DifAndCtrl_DW.d135 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.d110 = DifAndCtrl_DW.d135 * DifAndCtrl_DW.D46_tmp_g;
  DifAndCtrl_DW.d111 = DifAndCtrl_DW.tmp_tmp_oo * DifAndCtrl_DW.D57;
  DifAndCtrl_DW.d112 = DifAndCtrl_DW.tmp_tmp_jk * DifAndCtrl_DW.D57;
  DifAndCtrl_DW.d113 = DifAndCtrl_DW.tmp_tmp_cm * DifAndCtrl_DW.D57;
  DifAndCtrl_DW.d114 = DifAndCtrl_DW.d44 * DifAndCtrl_DW.D57;
  DifAndCtrl_DW.d115 = DifAndCtrl_DW.d36 * DifAndCtrl_DW.D56_tmp_d;
  DifAndCtrl_DW.d140 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.d116 = DifAndCtrl_DW.d140 * DifAndCtrl_DW.D46_tmp_dy;
  DifAndCtrl_DW.d117 = DifAndCtrl_DW.tmp_tmp_fq * DifAndCtrl_DW.D45_tmp;
  DifAndCtrl_DW.d118 = DifAndCtrl_DW.tmp_tmp_nl * DifAndCtrl_DW.D45_tmp;
  DifAndCtrl_DW.d119 = DifAndCtrl_DW.tmp_tmp_c * DifAndCtrl_DW.D45_tmp;
  DifAndCtrl_DW.d120 = DifAndCtrl_DW.d37 * DifAndCtrl_DW.D56_tmp_lx;
  DifAndCtrl_DW.d121 = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  DifAndCtrl_DW.d122 = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  DifAndCtrl_DW.d123 = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4];
  DifAndCtrl_DW.d128 = DifAndCtrl_DW.d34 * DifAndCtrl_DW.w_a;
  DifAndCtrl_DW.d129 = DifAndCtrl_DW.d35 * DifAndCtrl_DW.w_a;
  DifAndCtrl_DW.d130 = DifAndCtrl_DW.d33 * DifAndCtrl_DW.w_a;
  DifAndCtrl_DW.d131 = DifAndCtrl_DW.d34 * DifAndCtrl_DW.x_a;
  DifAndCtrl_DW.d132 = DifAndCtrl_DW.tmp_tmp_f1 * DifAndCtrl_DW.x_a;
  DifAndCtrl_DW.d133 = DifAndCtrl_DW.d35 * DifAndCtrl_DW.x_a;
  DifAndCtrl_DW.d134 = DifAndCtrl_DW.d33 * DifAndCtrl_DW.x_a;
  DifAndCtrl_DW.d136 = DifAndCtrl_DW.tmp_tmp_oo * DifAndCtrl_DW.D24_tmp;
  DifAndCtrl_DW.d137 = DifAndCtrl_DW.tmp_tmp_jk * DifAndCtrl_DW.D24_tmp;
  DifAndCtrl_DW.d138 = DifAndCtrl_DW.tmp_tmp_cm * DifAndCtrl_DW.D24_tmp;
  DifAndCtrl_DW.d141 = DifAndCtrl_DW.tmp_tmp_fq * DifAndCtrl_DW.ab_a;
  DifAndCtrl_DW.d142 = DifAndCtrl_DW.tmp_tmp_nl * DifAndCtrl_DW.ab_a;
  DifAndCtrl_DW.d143 = DifAndCtrl_DW.tmp_tmp_c * DifAndCtrl_DW.ab_a;
  DifAndCtrl_DW.d146 = DifAndCtrl_DW.d17 * DifAndCtrl_DW.D27;
  DifAndCtrl_DW.d147 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d148 = DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d149 = -0.0525693184 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.142 *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d150 = -0.0383689744 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.143 *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d151 = DifAndCtrl_DW.d15 * 0.028900000000000006 * 0.143 *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d152 = DifAndCtrl_DW.d17 * DifAndCtrl_DW.D37;
  DifAndCtrl_DW.d180 = DifAndCtrl_DW.D17_tmp_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3] *
    DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.d181 = DifAndCtrl_DW.d50 * DifAndCtrl_DW.D46_tmp_tmp_o2;
  DifAndCtrl_DW.d158 = ((DifAndCtrl_DW.D17_tmp_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3] *
    DifAndCtrl_DW.D46_tmp_da + DifAndCtrl_DW.d180) + DifAndCtrl_DW.d49 *
                        DifAndCtrl_DW.D46_tmp_e1) + DifAndCtrl_DW.d181;
  DifAndCtrl_DW.d159 = DifAndCtrl_DW.d23 * DifAndCtrl_DW.D46_tmp_tmp;
  DifAndCtrl_DW.d160 = DifAndCtrl_DW.d29 * DifAndCtrl_DW.D56_tmp_tmp_f;
  DifAndCtrl_DW.d161 = DifAndCtrl_DW.d51 * DifAndCtrl_DW.D46_tmp_tmp_e;
  DifAndCtrl_DW.d162 = DifAndCtrl_DW.d52 * DifAndCtrl_DW.D46_tmp_tmp_c;
  DifAndCtrl_DW.d163 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d164 = DifAndCtrl_DW.d121 * DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d165 = -0.0262846592 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.142 *
    DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d166 = DifAndCtrl_DW.d4 * 0.028900000000000006;
  DifAndCtrl_DW.d39 = DifAndCtrl_DW.d39 * 0.17 * 0.143;
  DifAndCtrl_DW.d167 = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.d168 = DifAndCtrl_DW.d122 * DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.d169 = -0.0191844872 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.143 *
    DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.d170 = DifAndCtrl_DW.d31 * 0.17 * 0.143 *
    DifAndCtrl_DW.D56_tmp_tmp_i;
  DifAndCtrl_DW.d171 = DifAndCtrl_DW.d47 * DifAndCtrl_DW.D46_tmp_tmp_af;
  DifAndCtrl_DW.d172 = DifAndCtrl_DW.d48 * DifAndCtrl_DW.D47_tmp_p;
  DifAndCtrl_DW.d173 = 0.78352 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7];
  DifAndCtrl_DW.d176 = DifAndCtrl_DW.d43 * DifAndCtrl_DW.D15_tmp_tmp;
  DifAndCtrl_DW.d177 = DifAndCtrl_DW.d46 * DifAndCtrl_DW.D15_tmp_tmp_a;
  DifAndCtrl_DW.d178 = DifAndCtrl_DW.d32 * DifAndCtrl_DW.D56_tmp_tmp_a;
  DifAndCtrl_DW.x[43] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    ((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.d158 +
    DifAndCtrl_DW.d82) + DifAndCtrl_DW.d84) + DifAndCtrl_DW.d85) +
    DifAndCtrl_DW.d86) + DifAndCtrl_DW.d16 * DifAndCtrl_DW.D17_tmp_p) +
    DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D17_tmp_p) + DifAndCtrl_DW.d87) +
    DifAndCtrl_DW.d88) + DifAndCtrl_DW.d89) + DifAndCtrl_DW.d90) +
    DifAndCtrl_DW.d91) + DifAndCtrl_DW.d92) + DifAndCtrl_DW.d93) +
    DifAndCtrl_DW.d94) + DifAndCtrl_DW.d146) + DifAndCtrl_DW.d18 *
    DifAndCtrl_DW.D17_tmp_j) + DifAndCtrl_DW.d95) + DifAndCtrl_DW.d96) +
    DifAndCtrl_DW.d97) + DifAndCtrl_DW.d98) + DifAndCtrl_DW.d99) +
    DifAndCtrl_DW.d100) + DifAndCtrl_DW.d101) + DifAndCtrl_DW.d147) +
    DifAndCtrl_DW.d148) + DifAndCtrl_DW.d15 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.d149) + DifAndCtrl_DW.d19 * 0.142 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.d150) + DifAndCtrl_DW.d19 * 0.143 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.d151) + DifAndCtrl_DW.d20 *
    DifAndCtrl_DW.D17) + DifAndCtrl_DW.d21 * DifAndCtrl_DW.D17) +
    DifAndCtrl_DW.d22 * DifAndCtrl_DW.D17) + DifAndCtrl_DW.d14 *
    DifAndCtrl_DW.D17) + DifAndCtrl_DW.d16 * DifAndCtrl_DW.D18) +
    DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D18) + DifAndCtrl_DW.d28 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    DifAndCtrl_DW.D46_tmp_j) + DifAndCtrl_DW.d159) + DifAndCtrl_DW.d16 *
    DifAndCtrl_DW.D24) + DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D24) +
    DifAndCtrl_DW.d24 * DifAndCtrl_DW.D56_tmp_a) + DifAndCtrl_DW.d25 *
    DifAndCtrl_DW.D56_tmp_a) + DifAndCtrl_DW.d26 * DifAndCtrl_DW.D56_tmp_a) +
    DifAndCtrl_DW.d27 * DifAndCtrl_DW.D56_tmp_a) + DifAndCtrl_DW.d152) +
    DifAndCtrl_DW.d18 * DifAndCtrl_DW.D38) + DifAndCtrl_DW.d28 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D46_tmp_d) + DifAndCtrl_DW.d160) + DifAndCtrl_DW.d18 *
    DifAndCtrl_DW.D46_tmp_tmp_ei) + DifAndCtrl_DW.d17 * DifAndCtrl_DW.D46) +
    DifAndCtrl_DW.tmp_tmp_n * DifAndCtrl_DW.D56_tmp_ju) +
    DifAndCtrl_DW.tmp_tmp_d * DifAndCtrl_DW.D56_tmp_ju) +
    DifAndCtrl_DW.tmp_tmp_na * DifAndCtrl_DW.D56_tmp_ju) + DifAndCtrl_DW.d161) +
    DifAndCtrl_DW.d162) + DifAndCtrl_DW.d123 * DifAndCtrl_DW.D14) +
    DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.D14) + DifAndCtrl_DW.d30 * 0.142 * DifAndCtrl_DW.D14) +
    DifAndCtrl_DW.d30 * 0.143 * DifAndCtrl_DW.D14) + DifAndCtrl_DW.d163) +
    DifAndCtrl_DW.d164) + DifAndCtrl_DW.d165) + DifAndCtrl_DW.d166 * 0.143 *
    DifAndCtrl_DW.D46_tmp_cs) + -0.45856 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.08312 * 0.142 *
    DifAndCtrl_DW.D15) + DifAndCtrl_DW.d106 * 0.08312 * 0.17 * 0.143 *
    DifAndCtrl_DW.D15) + DifAndCtrl_DW.d167) + DifAndCtrl_DW.d168) +
    DifAndCtrl_DW.d169) + DifAndCtrl_DW.d31 * 0.08312 * 0.143 *
    DifAndCtrl_DW.D47) + DifAndCtrl_DW.d170) + DifAndCtrl_DW.d104) +
    DifAndCtrl_DW.d171) + DifAndCtrl_DW.d107) + DifAndCtrl_DW.d39 *
    DifAndCtrl_DW.D56) + DifAndCtrl_DW.d172) + DifAndCtrl_DW.d108) +
    DifAndCtrl_DW.d109) + DifAndCtrl_DW.d110) + DifAndCtrl_DW.d111) -
    DifAndCtrl_DW.d112) - DifAndCtrl_DW.d113) - DifAndCtrl_DW.d114) +
    DifAndCtrl_DW.d115) + DifAndCtrl_DW.d116) + DifAndCtrl_DW.d117) -
    DifAndCtrl_DW.d118) - DifAndCtrl_DW.d119) + DifAndCtrl_DW.d120) +
    DifAndCtrl_DW.d173 * 0.143 * DifAndCtrl_DW.d41 * DifAndCtrl_DW.D14_tmp_m) +
    8.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * 0.08312 *
    DifAndCtrl_DW.D14_tmp_m3 * DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.d128) +
    DifAndCtrl_DW.d129) + DifAndCtrl_DW.d130) - DifAndCtrl_DW.d131) +
    DifAndCtrl_DW.d132) - DifAndCtrl_DW.d133) - DifAndCtrl_DW.d134) +
                       DifAndCtrl_DW.d28 *
                       DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6]
                       * DifAndCtrl_DW.D46_tmp_b) + DifAndCtrl_DW.d136) -
                     DifAndCtrl_DW.d137) - DifAndCtrl_DW.d138) +
                   -DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
                   0.028900000000000006 * 0.143 * DifAndCtrl_DW.D24_tmp) +
                  DifAndCtrl_DW.d36 * DifAndCtrl_DW.D56_tmp_b) +
                 DifAndCtrl_DW.d28 *
                 DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
                 DifAndCtrl_DW.D46_tmp_ln) + DifAndCtrl_DW.d141) -
               DifAndCtrl_DW.d142) - DifAndCtrl_DW.d143) + DifAndCtrl_DW.d37 *
             DifAndCtrl_DW.D56_tmp_h) + DifAndCtrl_DW.d176) + DifAndCtrl_DW.d177)
          + DifAndCtrl_DW.d38 * DifAndCtrl_DW.D24_tmp_p) + DifAndCtrl_DW.d105 *
         DifAndCtrl_DW.D24_tmp_p) + DifAndCtrl_DW.d40 *
        DifAndCtrl_DW.D56_tmp_tmp_h) + DifAndCtrl_DW.d178) * 0.125);
  DifAndCtrl_DW.d15 = -0.09794 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7];
  DifAndCtrl_DW.d19 = DifAndCtrl_DW.D14_tmp_m3 * 0.08312;
  DifAndCtrl_DW.x[51] = -(DifAndCtrl_DW.d15 * 0.143 * DifAndCtrl_DW.d41 -
    DifAndCtrl_DW.d19 * DifAndCtrl_DW.d5);
  DifAndCtrl_DW.x[59] = -(DifAndCtrl_DW.d41 * -0.01400542 * DifAndCtrl_DW.d7);
  DifAndCtrl_DW.d42 = DifAndCtrl_DW.d42 * 0.08312 * 0.142;
  DifAndCtrl_DW.d30 = DifAndCtrl_DW.D16_tmp_i * 0.08312;
  DifAndCtrl_DW.d31 = DifAndCtrl_DW.d30 * 0.17 * 0.143;
  DifAndCtrl_DW.d36 = DifAndCtrl_DW.d45 * 0.08312 * 0.143;
  DifAndCtrl_DW.d45 = DifAndCtrl_DW.d45 * 0.17 * 0.143;
  DifAndCtrl_DW.d37 = DifAndCtrl_DW.D16_tmp_i * 0.0069089343999999995;
  DifAndCtrl_DW.D14_tmp_m3 = -4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE
    [3];
  DifAndCtrl_DW.d144 = DifAndCtrl_DW.d28 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  DifAndCtrl_DW.tmp_tmp_fz = DifAndCtrl_DW.d144 * DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.d78 = 4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3];
  DifAndCtrl_DW.d139 = DifAndCtrl_DW.d28 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  DifAndCtrl_DW.d153 = DifAndCtrl_DW.d78 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.d154 = 4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7];
  DifAndCtrl_DW.d155 = 4.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6];
  DifAndCtrl_DW.rtb_ginv_tmp_tmp = ((((DifAndCtrl_DW.rtb_ginv_tmp_tmp * 4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
    DifAndCtrl_DW.D15_tmp_g + DifAndCtrl_DW.d139 * DifAndCtrl_DW.D46_tmp_da) +
    DifAndCtrl_DW.d153 * DifAndCtrl_DW.D15_tmp_g1) + DifAndCtrl_DW.d155 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
    DifAndCtrl_DW.D15_tmp_g1) + DifAndCtrl_DW.d154 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
    DifAndCtrl_DW.D15_tmp_g1) + DifAndCtrl_DW.tmp_tmp_fz;
  DifAndCtrl_DW.tmp_tmp_i = DifAndCtrl_DW.d43 * DifAndCtrl_DW.D46_tmp_p;
  DifAndCtrl_DW.tmp_tmp_l = DifAndCtrl_DW.tmp_tmp_oo * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.tmp_tmp_i3 = DifAndCtrl_DW.tmp_tmp_jk * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.tmp_tmp_k1 = DifAndCtrl_DW.tmp_tmp_cm * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.tmp_tmp_fc = DifAndCtrl_DW.d44 * DifAndCtrl_DW.D56_tmp_j;
  DifAndCtrl_DW.tmp_tmp_a = DifAndCtrl_DW.d45 * DifAndCtrl_DW.D27;
  DifAndCtrl_DW.tmp_tmp_d4 = DifAndCtrl_DW.d46 * DifAndCtrl_DW.D46_tmp_l;
  DifAndCtrl_DW.tmp_tmp_e = DifAndCtrl_DW.d45 * DifAndCtrl_DW.D35;
  DifAndCtrl_DW.tmp_tmp_eh = DifAndCtrl_DW.tmp_tmp_fq * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.tmp_tmp_b = DifAndCtrl_DW.tmp_tmp_nl * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.tmp_tmp_a0 = DifAndCtrl_DW.tmp_tmp_c * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.tmp_tmp_il = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.tmp_tmp_fa = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d124 = 0.0262846592 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.142;
  DifAndCtrl_DW.tmp_tmp_ji = DifAndCtrl_DW.d124 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d126 = 0.0191844872 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.143;
  DifAndCtrl_DW.tmp_tmp_fr = DifAndCtrl_DW.d126 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.d127 = DifAndCtrl_DW.D16_tmp_i * 0.028900000000000006 * 0.143;
  DifAndCtrl_DW.tmp_tmp_f = DifAndCtrl_DW.d127 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.tmp_tmp_p = DifAndCtrl_DW.d47 * DifAndCtrl_DW.D46_tmp_j;
  DifAndCtrl_DW.tmp_tmp_oo *= DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_jk *= DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_cm *= DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_p2 = DifAndCtrl_DW.d44 * DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_nj = DifAndCtrl_DW.d45 * DifAndCtrl_DW.D37;
  DifAndCtrl_DW.tmp_tmp_k = DifAndCtrl_DW.d48 * DifAndCtrl_DW.D46_tmp_d;
  DifAndCtrl_DW.tmp_tmp_n3 = DifAndCtrl_DW.d45 * DifAndCtrl_DW.D46;
  DifAndCtrl_DW.tmp_tmp_fq *= DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.tmp_tmp_nl *= DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.tmp_tmp_c *= DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.tmp_tmp_o = DifAndCtrl_DW.D14_tmp_m3 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    DifAndCtrl_DW.D34_tmp;
  DifAndCtrl_DW.tmp_tmp_gg = DifAndCtrl_DW.D16_tmp *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
    DifAndCtrl_DW.D34_tmp;
  DifAndCtrl_DW.d24 *= DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d25 *= DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d26 *= DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d27 *= DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.tmp_tmp_cq = DifAndCtrl_DW.D14_tmp_m3 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D34_tmp_m;
  DifAndCtrl_DW.tmp_tmp_cj = DifAndCtrl_DW.D16_tmp *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D34_tmp_m;
  DifAndCtrl_DW.tmp_tmp_m = DifAndCtrl_DW.d3 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D34_tmp_m;
  DifAndCtrl_DW.tmp_tmp_n *= DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.tmp_tmp_d *= DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.tmp_tmp_na *= DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.d17 *= DifAndCtrl_DW.D56_tmp_tmp_i;
  DifAndCtrl_DW.tmp_tmp_j = DifAndCtrl_DW.d49 * DifAndCtrl_DW.D46_tmp_g;
  DifAndCtrl_DW.tmp_tmp_pr = DifAndCtrl_DW.d23 * DifAndCtrl_DW.D56_tmp_d;
  DifAndCtrl_DW.tmp_tmp_dz = DifAndCtrl_DW.d50 * DifAndCtrl_DW.D46_tmp_dy;
  DifAndCtrl_DW.tmp_tmp_g4 = DifAndCtrl_DW.d29 * DifAndCtrl_DW.D56_tmp_lx;
  DifAndCtrl_DW.tmp_tmp_c3 = DifAndCtrl_DW.d51 * DifAndCtrl_DW.D46_tmp_b;
  DifAndCtrl_DW.d23 *= DifAndCtrl_DW.D56_tmp_b;
  DifAndCtrl_DW.tmp_tmp_cx = DifAndCtrl_DW.d52 * DifAndCtrl_DW.D46_tmp_ln;
  DifAndCtrl_DW.d29 *= DifAndCtrl_DW.D56_tmp_h;
  DifAndCtrl_DW.d125 = DifAndCtrl_DW.d37 * 0.142;
  DifAndCtrl_DW.d37 *= 0.143;
  DifAndCtrl_DW.x[28] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((DifAndCtrl_DW.d34 * DifAndCtrl_DW.D25 + DifAndCtrl_DW.rtb_ginv_tmp_tmp) -
    DifAndCtrl_DW.tmp_tmp_f1 * DifAndCtrl_DW.D25) + DifAndCtrl_DW.d35 *
    DifAndCtrl_DW.D25) + DifAndCtrl_DW.d33 * DifAndCtrl_DW.D25) +
    DifAndCtrl_DW.d42 * DifAndCtrl_DW.D17_tmp_p) + DifAndCtrl_DW.d31 *
    DifAndCtrl_DW.D17_tmp_p) + DifAndCtrl_DW.tmp_tmp_i) + DifAndCtrl_DW.d42 *
    DifAndCtrl_DW.D16) + DifAndCtrl_DW.d31 * DifAndCtrl_DW.D16) -
    DifAndCtrl_DW.tmp_tmp_l) + DifAndCtrl_DW.tmp_tmp_i3) +
    DifAndCtrl_DW.tmp_tmp_k1) + DifAndCtrl_DW.tmp_tmp_fc) +
    DifAndCtrl_DW.tmp_tmp_a) + DifAndCtrl_DW.d36 * DifAndCtrl_DW.D17_tmp_j) +
    DifAndCtrl_DW.tmp_tmp_d4) + DifAndCtrl_DW.d36 * DifAndCtrl_DW.D34) +
    DifAndCtrl_DW.tmp_tmp_e) - DifAndCtrl_DW.tmp_tmp_eh) +
    DifAndCtrl_DW.tmp_tmp_b) + DifAndCtrl_DW.tmp_tmp_a0) +
    DifAndCtrl_DW.tmp_tmp_il) + DifAndCtrl_DW.tmp_tmp_fa) +
    DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.tmp_tmp_ji) + DifAndCtrl_DW.d125 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.tmp_tmp_fr) + DifAndCtrl_DW.d37 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.tmp_tmp_f) + DifAndCtrl_DW.d34 *
    DifAndCtrl_DW.D17) - DifAndCtrl_DW.tmp_tmp_f1 * DifAndCtrl_DW.D17) +
    DifAndCtrl_DW.d35 * DifAndCtrl_DW.D17) + DifAndCtrl_DW.d33 *
    DifAndCtrl_DW.D17) + DifAndCtrl_DW.d42 * DifAndCtrl_DW.D18) +
    DifAndCtrl_DW.d31 * DifAndCtrl_DW.D18) + DifAndCtrl_DW.tmp_tmp_p) +
    DifAndCtrl_DW.d42 * DifAndCtrl_DW.D24) + DifAndCtrl_DW.d30 * 0.17 * 0.143 *
    DifAndCtrl_DW.D24) - DifAndCtrl_DW.tmp_tmp_oo) + DifAndCtrl_DW.tmp_tmp_jk) +
    DifAndCtrl_DW.tmp_tmp_cm) + DifAndCtrl_DW.tmp_tmp_p2) +
    DifAndCtrl_DW.tmp_tmp_nj) + DifAndCtrl_DW.d36 * DifAndCtrl_DW.D38) +
    DifAndCtrl_DW.tmp_tmp_k) + DifAndCtrl_DW.d36 * DifAndCtrl_DW.D46_tmp_tmp_ei)
    + DifAndCtrl_DW.tmp_tmp_n3) - DifAndCtrl_DW.tmp_tmp_fq) +
    DifAndCtrl_DW.tmp_tmp_nl) + DifAndCtrl_DW.tmp_tmp_c) + DifAndCtrl_DW.d20 *
    DifAndCtrl_DW.D14) + DifAndCtrl_DW.d21 * DifAndCtrl_DW.D14) +
    DifAndCtrl_DW.d22 * DifAndCtrl_DW.D14) + DifAndCtrl_DW.d14 *
    DifAndCtrl_DW.D14) + DifAndCtrl_DW.tmp_tmp_o) + DifAndCtrl_DW.tmp_tmp_gg) +
    DifAndCtrl_DW.d24) + DifAndCtrl_DW.d25) + DifAndCtrl_DW.d26) +
    DifAndCtrl_DW.d27) + DifAndCtrl_DW.d16 * DifAndCtrl_DW.D15) +
                       DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D15) +
                      DifAndCtrl_DW.tmp_tmp_cq) + DifAndCtrl_DW.tmp_tmp_cj) +
                    DifAndCtrl_DW.tmp_tmp_m) + DifAndCtrl_DW.tmp_tmp_n) +
                  DifAndCtrl_DW.tmp_tmp_d) + DifAndCtrl_DW.tmp_tmp_na) +
                DifAndCtrl_DW.d18 * DifAndCtrl_DW.D47) + DifAndCtrl_DW.d17) +
              DifAndCtrl_DW.tmp_tmp_j) + DifAndCtrl_DW.tmp_tmp_pr) +
            DifAndCtrl_DW.tmp_tmp_dz) + DifAndCtrl_DW.tmp_tmp_g4) +
          DifAndCtrl_DW.tmp_tmp_c3) + DifAndCtrl_DW.d23) +
        DifAndCtrl_DW.tmp_tmp_cx) + DifAndCtrl_DW.d29) * 0.25);
  DifAndCtrl_DW.d14 = DifAndCtrl_DW.D46_tmp_p4 * DifAndCtrl_DW.D46_tmp_da +
    DifAndCtrl_DW.D46_tmp_f * DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.d16 = -0.004761842800000001 * DifAndCtrl_DW.D56_tmp_tmp_i;
  DifAndCtrl_DW.tmp_tmp_g = 2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7];
  DifAndCtrl_DW.d18 = 0.0013531005056 * DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.d20 = 0.0020206472 * DifAndCtrl_DW.D15;
  DifAndCtrl_DW.d21 = 0.0011641305103999998 * DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.d22 = 0.0011641305103999998 * DifAndCtrl_DW.D47;
  DifAndCtrl_DW.d30 = (DifAndCtrl_DW.rtb_ginv_tmp_o + 0.0013716908347999998) *
    DifAndCtrl_DW.D15_tmp_g1 + (0.0011641305103999998 * DifAndCtrl_DW.D14_tmp_k
    + 0.0023809214000000004 * DifAndCtrl_DW.D15_tmp_g);
  DifAndCtrl_DW.x[36] = -((((((((((((((((((DifAndCtrl_DW.d14 -
    DifAndCtrl_DW.D14_tmp_ms) + DifAndCtrl_DW.D14_tmp_o3) -
    DifAndCtrl_DW.D56_tmp_tmp_fi) - DifAndCtrl_DW.D56_tmp_tmp_c) +
    DifAndCtrl_DW.D16_tmp_p) - DifAndCtrl_DW.d) - DifAndCtrl_DW.d2) -
    DifAndCtrl_DW.D16_tmp_k) + -0.0027062010112 * DifAndCtrl_DW.D15) +
    -0.0040412944 * DifAndCtrl_DW.D15) + DifAndCtrl_DW.d10) -
    DifAndCtrl_DW.D14_tmp_o) - DifAndCtrl_DW.D14_tmp_pe) +
    -0.0023282610207999996 * DifAndCtrl_DW.D47) + DifAndCtrl_DW.d16) *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] + (-2.0 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7] * DifAndCtrl_DW.d30 *
    DifAndCtrl_DW.D34_tmp_m + DifAndCtrl_DW.tmp_tmp_g *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3] *
    DifAndCtrl_DW.D46_tmp_bj)) + ((((((((((((((DifAndCtrl_DW.d14 -
    DifAndCtrl_DW.d18) + -0.0020206472 * DifAndCtrl_DW.D14_tmp) +
    DifAndCtrl_DW.D16_tmp_p) - DifAndCtrl_DW.d) - DifAndCtrl_DW.d2) -
    DifAndCtrl_DW.D16_tmp_k) + -0.0013531005056 * DifAndCtrl_DW.D15) -
    DifAndCtrl_DW.d20) - DifAndCtrl_DW.d21) + DifAndCtrl_DW.d10) -
    DifAndCtrl_DW.D14_tmp_o) - DifAndCtrl_DW.D14_tmp_pe) - DifAndCtrl_DW.d22) +
    DifAndCtrl_DW.d16) * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6]) * 0.5);
  DifAndCtrl_DW.D14_tmp_ms = 4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.D14_tmp_o3 = 4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.D56_tmp_tmp_fi = -4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.D56_tmp_tmp_c = -4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.d14 = 0.0011641305103999998 * DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.d16 = 0.0011641305103999998 * DifAndCtrl_DW.D34;
  DifAndCtrl_DW.d33 = 0.0011641305103999998 * DifAndCtrl_DW.D38;
  DifAndCtrl_DW.d34 = 0.0011641305103999998 * DifAndCtrl_DW.D46_tmp_tmp_ei;
  DifAndCtrl_DW.tmp_tmp_f1 = 0.0033737477055999993 * DifAndCtrl_DW.D17_tmp_p;
  DifAndCtrl_DW.d35 = 0.0013531005056 * DifAndCtrl_DW.D18;
  DifAndCtrl_DW.d79 = 0.0020206472 * DifAndCtrl_DW.D18;
  DifAndCtrl_DW.d80 = 0.0023809214000000004 * DifAndCtrl_DW.D27 +
    DifAndCtrl_DW.d14;
  DifAndCtrl_DW.d81 = 0.0023809214000000004 * DifAndCtrl_DW.D37;
  DifAndCtrl_DW.D27_tmp_o = ((DifAndCtrl_DW.D27_tmp_o + DifAndCtrl_DW.tmp_tmp_f1)
    + 0.0013531005056 * DifAndCtrl_DW.D16) + 0.0020206472 * DifAndCtrl_DW.D16;
  DifAndCtrl_DW.d174 = 0.0013531005056 * DifAndCtrl_DW.D24;
  DifAndCtrl_DW.d175 = 0.0020206472 * DifAndCtrl_DW.D24;
  DifAndCtrl_DW.D27_tmp_m =
    (((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.D27_tmp_o -
    DifAndCtrl_DW.D27_tmp_m) + DifAndCtrl_DW.D14_tmp_cx) + DifAndCtrl_DW.d9) +
    DifAndCtrl_DW.d11) + DifAndCtrl_DW.d12) + DifAndCtrl_DW.d14) +
    DifAndCtrl_DW.D14_tmp_f) + DifAndCtrl_DW.d16) + DifAndCtrl_DW.D14_tmp_n) -
    DifAndCtrl_DW.D14_tmp_tmp_h) + DifAndCtrl_DW.D14_tmp_tmp_m) +
    DifAndCtrl_DW.D14_tmp_cz) + DifAndCtrl_DW.D15_tmp_tmp_c) +
    DifAndCtrl_DW.D15_tmp_tmp_f) + DifAndCtrl_DW.D16_tmp_tmp) +
    DifAndCtrl_DW.D34_tmp_l) + DifAndCtrl_DW.D37_tmp) + DifAndCtrl_DW.d35) +
    DifAndCtrl_DW.d79) + DifAndCtrl_DW.rtb_ginv_tmp_b) + DifAndCtrl_DW.d174) +
    DifAndCtrl_DW.d175) - DifAndCtrl_DW.d54) + DifAndCtrl_DW.d55) +
                     DifAndCtrl_DW.d56) + DifAndCtrl_DW.d57) + DifAndCtrl_DW.d58)
                  + DifAndCtrl_DW.d33) + DifAndCtrl_DW.d59) + DifAndCtrl_DW.d34)
               + DifAndCtrl_DW.d60) - DifAndCtrl_DW.d61) + DifAndCtrl_DW.d62) +
            DifAndCtrl_DW.d63) + DifAndCtrl_DW.d64) + DifAndCtrl_DW.d65) +
         DifAndCtrl_DW.d66) + DifAndCtrl_DW.d67) + DifAndCtrl_DW.d68) +
      DifAndCtrl_DW.d69) + DifAndCtrl_DW.d70) + DifAndCtrl_DW.d71;
  DifAndCtrl_DW.d179 = (((((((((((((((((((DifAndCtrl_DW.d80 +
    DifAndCtrl_DW.D14_tmp_f) + DifAndCtrl_DW.d16) + 0.0023809214000000004 *
    DifAndCtrl_DW.D35) - DifAndCtrl_DW.D14_tmp_tmp_h) +
    DifAndCtrl_DW.D14_tmp_tmp_m) + DifAndCtrl_DW.D14_tmp_cz) +
    DifAndCtrl_DW.D15_tmp_tmp_f) + DifAndCtrl_DW.D34_tmp_l) + DifAndCtrl_DW.d81)
    + DifAndCtrl_DW.d33) + DifAndCtrl_DW.d59) + DifAndCtrl_DW.d34) +
    0.0023809214000000004 * DifAndCtrl_DW.D46) - DifAndCtrl_DW.d61) +
    DifAndCtrl_DW.d62) + DifAndCtrl_DW.d63) + DifAndCtrl_DW.d66) +
    DifAndCtrl_DW.d67) + DifAndCtrl_DW.d70) + DifAndCtrl_DW.d71;
  DifAndCtrl_DW.x[44] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.D14_tmp_ms
    * DifAndCtrl_DW.D46_tmp_e1 + DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D46_tmp_tmp_o2) + DifAndCtrl_DW.D46_tmp_p4 *
    DifAndCtrl_DW.D46_tmp_tmp_o) + DifAndCtrl_DW.D46_tmp_f *
    DifAndCtrl_DW.D46_tmp_tmp_l) + DifAndCtrl_DW.D56_tmp_o3 *
    DifAndCtrl_DW.D46_tmp_tmp) + DifAndCtrl_DW.D56_tmp_lm *
    DifAndCtrl_DW.D56_tmp_tmp_f) + DifAndCtrl_DW.D14_tmp_ms *
    DifAndCtrl_DW.D46_tmp_tmp_e) + DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D46_tmp_tmp_c) + -0.004761842800000001 *
    DifAndCtrl_DW.D46_tmp_tmp_a) + -0.0027062010112 *
    DifAndCtrl_DW.D46_tmp_tmp_d) + -0.0040412944 * DifAndCtrl_DW.D46_tmp_tmp_d)
    + DifAndCtrl_DW.D56_tmp_tmp_fi * DifAndCtrl_DW.D46_tmp_tmp_af) +
    -0.0027062010112 * DifAndCtrl_DW.D56) + -0.0040412944 * DifAndCtrl_DW.D56) +
    -0.004761842800000001 * DifAndCtrl_DW.D56_tmp_tmp_iz) +
    -0.0023282610207999996 * DifAndCtrl_DW.D56_tmp_tmp_g) +
    DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.D47_tmp_p) +
    -0.0023282610207999996 * DifAndCtrl_DW.D56_tmp_tmp_ff) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.D48_tmp) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D57) -
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D57) - 0.0018662108031999999 * DifAndCtrl_DW.D57) -
    0.0041327000000000004 * DifAndCtrl_DW.D57) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.D45_tmp) -
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D45_tmp) + -0.0013716908347999998 * DifAndCtrl_DW.D45_tmp) +
    -2.0 * DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D46_tmp_h2) + -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D46_tmp_h2) + 4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    DifAndCtrl_DW.D46_tmp_h2) + -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.D46_tmp_h2) + -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D46_tmp_h2) + 4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    DifAndCtrl_DW.D46_tmp_h2) + 4.0 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    DifAndCtrl_DW.D46_tmp_h2) + -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D46_tmp_h2) + -2.0 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.D46_tmp_h2) + 0.0037324216063999997 * DifAndCtrl_DW.D46_tmp_h2)
    + 0.0019621373695999996 * DifAndCtrl_DW.D46_tmp_h2) + 0.0027433816695999996 *
    DifAndCtrl_DW.D46_tmp_h2) + 0.0019759552383999996 * DifAndCtrl_DW.D46_tmp_h2)
    + 0.008265400000000001 * DifAndCtrl_DW.D46_tmp_h2) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.w_a) + 0.0009810686847999998 * DifAndCtrl_DW.w_a) +
    0.0009879776191999998 * DifAndCtrl_DW.w_a) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.x_a) -
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
    DifAndCtrl_DW.x_a) + 0.0009810686847999998 * DifAndCtrl_DW.x_a) +
    0.0009879776191999998 * DifAndCtrl_DW.x_a) -
                        DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1
                        [0] * DifAndCtrl_DW.D24_tmp) +
                       DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4]
                       * DifAndCtrl_DW.D24_tmp) + 0.0018662108031999999 *
                      DifAndCtrl_DW.D24_tmp) + 0.0041327000000000004 *
                     DifAndCtrl_DW.D24_tmp) -
                    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
                    DifAndCtrl_DW.ab_a) +
                   DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
                   DifAndCtrl_DW.ab_a) + 0.0013716908347999998 *
                  DifAndCtrl_DW.ab_a) + 0.0027062010112 *
                 DifAndCtrl_DW.D56_tmp_tmp) + 0.0040412944 *
                DifAndCtrl_DW.D56_tmp_tmp) + DifAndCtrl_DW.D56_tmp_tmp_fi *
               DifAndCtrl_DW.D15_tmp_tmp) + 0.004761842800000001 *
              DifAndCtrl_DW.D56_tmp_tmp_g2) + 0.0023282610207999996 *
             DifAndCtrl_DW.D14_tmp_tmp) + DifAndCtrl_DW.D56_tmp_tmp_c *
            DifAndCtrl_DW.D15_tmp_tmp_a) + 0.0027062010112 *
           DifAndCtrl_DW.D24_tmp_p) + 0.0040412944 * DifAndCtrl_DW.D24_tmp_p) +
         0.0023282610207999996 * DifAndCtrl_DW.D56_tmp_tmp_h) +
        0.004761842800000001 * DifAndCtrl_DW.D56_tmp_tmp_a) * (-0.5 *
        DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]) +
       ((DifAndCtrl_DW.D27_tmp_m * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6]
         + DifAndCtrl_DW.d179 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7])
        + DifAndCtrl_DW.d53 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3])) *
      0.25);
  DifAndCtrl_DW.D48_tmp = 0.11464 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE
    [5];
  DifAndCtrl_DW.D14_tmp_ms = DifAndCtrl_DW.D48_tmp * 0.08312 * 0.142;
  DifAndCtrl_DW.D14_tmp_o3 = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    0.08312 * 0.17;
  DifAndCtrl_DW.D56_tmp_tmp_fi = DifAndCtrl_DW.D14_tmp_o3 * 0.143;
  DifAndCtrl_DW.D56_tmp_tmp_c = 0.09794 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.d53 = DifAndCtrl_DW.D56_tmp_tmp_c * 0.08312 * 0.143;
  DifAndCtrl_DW.ab_a = -0.22928 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4]
    * 0.08312 * 0.142;
  DifAndCtrl_DW.D57 = DifAndCtrl_DW.d13 * 0.08312 * 0.17 * 0.143;
  DifAndCtrl_DW.x_a = -0.19588 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.w_a = DifAndCtrl_DW.x_a * 0.08312 * 0.143;
  DifAndCtrl_DW.d72 = DifAndCtrl_DW.d53 * DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.d73 = DifAndCtrl_DW.d53 * DifAndCtrl_DW.D34;
  DifAndCtrl_DW.d74 = DifAndCtrl_DW.d53 * DifAndCtrl_DW.D38;
  DifAndCtrl_DW.d75 = DifAndCtrl_DW.d53 * DifAndCtrl_DW.D46_tmp_tmp_ei;
  DifAndCtrl_DW.d76 = DifAndCtrl_DW.w_a * DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.d77 = DifAndCtrl_DW.w_a * DifAndCtrl_DW.D47;
  DifAndCtrl_DW.D48_tmp = DifAndCtrl_DW.D48_tmp * 0.08312 * 0.142;
  DifAndCtrl_DW.x[52] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.D14_tmp_ms
    * DifAndCtrl_DW.D17_tmp_p + DifAndCtrl_DW.rtb_ginv_tmp_tmp) +
    DifAndCtrl_DW.D56_tmp_tmp_fi * DifAndCtrl_DW.D17_tmp_p) +
    DifAndCtrl_DW.tmp_tmp_i) + DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D16) +
    DifAndCtrl_DW.D56_tmp_tmp_fi * DifAndCtrl_DW.D16) - DifAndCtrl_DW.tmp_tmp_l)
    + DifAndCtrl_DW.tmp_tmp_i3) + DifAndCtrl_DW.tmp_tmp_k1) +
    DifAndCtrl_DW.tmp_tmp_fc) + DifAndCtrl_DW.tmp_tmp_a) + DifAndCtrl_DW.d72) +
    DifAndCtrl_DW.tmp_tmp_d4) + DifAndCtrl_DW.d73) + DifAndCtrl_DW.tmp_tmp_e) -
    DifAndCtrl_DW.tmp_tmp_eh) + DifAndCtrl_DW.tmp_tmp_b) +
    DifAndCtrl_DW.tmp_tmp_a0) + DifAndCtrl_DW.tmp_tmp_il) +
    DifAndCtrl_DW.tmp_tmp_fa) + DifAndCtrl_DW.tmp_tmp_ji) +
    DifAndCtrl_DW.tmp_tmp_fr) + DifAndCtrl_DW.tmp_tmp_f) +
    DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D18) + DifAndCtrl_DW.D14_tmp_o3 *
    0.143 * DifAndCtrl_DW.D18) + DifAndCtrl_DW.tmp_tmp_p) +
    DifAndCtrl_DW.D48_tmp * DifAndCtrl_DW.D24) + DifAndCtrl_DW.D56_tmp_tmp_fi *
    DifAndCtrl_DW.D24) - DifAndCtrl_DW.tmp_tmp_oo) + DifAndCtrl_DW.tmp_tmp_jk) +
    DifAndCtrl_DW.tmp_tmp_cm) + DifAndCtrl_DW.tmp_tmp_p2) +
    DifAndCtrl_DW.tmp_tmp_nj) + DifAndCtrl_DW.d74) + DifAndCtrl_DW.tmp_tmp_k) +
    DifAndCtrl_DW.d75) + DifAndCtrl_DW.tmp_tmp_n3) - DifAndCtrl_DW.tmp_tmp_fq) +
    DifAndCtrl_DW.tmp_tmp_nl) + DifAndCtrl_DW.tmp_tmp_c) + DifAndCtrl_DW.ab_a *
    DifAndCtrl_DW.D14_tmp) + DifAndCtrl_DW.D57 * DifAndCtrl_DW.D14_tmp) +
    DifAndCtrl_DW.tmp_tmp_o) + DifAndCtrl_DW.tmp_tmp_gg) + DifAndCtrl_DW.d24) +
    DifAndCtrl_DW.d25) + DifAndCtrl_DW.d26) + DifAndCtrl_DW.d27) +
    DifAndCtrl_DW.ab_a * DifAndCtrl_DW.D15) + DifAndCtrl_DW.D57 *
                        DifAndCtrl_DW.D15) + DifAndCtrl_DW.d76) +
                      DifAndCtrl_DW.tmp_tmp_cq) + DifAndCtrl_DW.tmp_tmp_cj) +
                    DifAndCtrl_DW.tmp_tmp_m) + DifAndCtrl_DW.tmp_tmp_n) +
                  DifAndCtrl_DW.tmp_tmp_d) + DifAndCtrl_DW.tmp_tmp_na) +
                DifAndCtrl_DW.d77) + DifAndCtrl_DW.d17) +
              DifAndCtrl_DW.tmp_tmp_j) + DifAndCtrl_DW.tmp_tmp_pr) +
            DifAndCtrl_DW.tmp_tmp_dz) + DifAndCtrl_DW.tmp_tmp_g4) +
          DifAndCtrl_DW.tmp_tmp_c3) + DifAndCtrl_DW.d23) +
        DifAndCtrl_DW.tmp_tmp_cx) + DifAndCtrl_DW.d29) * 0.25);
  DifAndCtrl_DW.D14_tmp_o3 = DifAndCtrl_DW.D56_tmp_tmp_c * 0.17 * 0.143;
  DifAndCtrl_DW.D56_tmp_tmp_c = DifAndCtrl_DW.x_a * 0.17 * 0.143;
  DifAndCtrl_DW.x[60] = -((((((((((((((((((((((((((((((((((DifAndCtrl_DW.d6 *
    4.0 * DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6] *
    DifAndCtrl_DW.D15_tmp_g1 + DifAndCtrl_DW.tmp_tmp_fz) +
    DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D27) + DifAndCtrl_DW.d72) +
    DifAndCtrl_DW.tmp_tmp_d4) + DifAndCtrl_DW.d73) + DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D35) - DifAndCtrl_DW.tmp_tmp_eh) + DifAndCtrl_DW.tmp_tmp_b) +
    DifAndCtrl_DW.tmp_tmp_a0) + DifAndCtrl_DW.tmp_tmp_fa) +
    DifAndCtrl_DW.tmp_tmp_fr) + DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D37) +
    DifAndCtrl_DW.d74) + DifAndCtrl_DW.tmp_tmp_k) + DifAndCtrl_DW.d75) +
    DifAndCtrl_DW.D14_tmp_o3 * DifAndCtrl_DW.D46) - DifAndCtrl_DW.tmp_tmp_fq) +
    DifAndCtrl_DW.tmp_tmp_nl) + DifAndCtrl_DW.tmp_tmp_c) +
    DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.D14_tmp_b) + DifAndCtrl_DW.d76)
    + DifAndCtrl_DW.tmp_tmp_cq) + DifAndCtrl_DW.tmp_tmp_cj) +
    DifAndCtrl_DW.tmp_tmp_m) + DifAndCtrl_DW.tmp_tmp_n) +
    DifAndCtrl_DW.tmp_tmp_d) + DifAndCtrl_DW.tmp_tmp_na) + DifAndCtrl_DW.d77) +
    DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.D56_tmp_tmp_i) +
    DifAndCtrl_DW.tmp_tmp_dz) + DifAndCtrl_DW.tmp_tmp_g4) +
    DifAndCtrl_DW.tmp_tmp_cx) + DifAndCtrl_DW.d29) * 0.25);
  DifAndCtrl_DW.rtb_ginv_tmp_tmp =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D46_tmp_l;
  DifAndCtrl_DW.d6 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7] *
    DifAndCtrl_DW.D46_tmp_d;
  DifAndCtrl_DW.d17 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6]
    * DifAndCtrl_DW.D46_tmp_dy;
  DifAndCtrl_DW.d23 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6]
    * DifAndCtrl_DW.D46_tmp_ln;
  DifAndCtrl_DW.d24 = DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.d25 = -0.004761842800000001 * DifAndCtrl_DW.D46_tmp_tmp_k;
  DifAndCtrl_DW.d26 = DifAndCtrl_DW.D56_tmp_o3 * DifAndCtrl_DW.D46_tmp_cs;
  DifAndCtrl_DW.d27 = DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0]
    * DifAndCtrl_DW.D56_tmp_h;
  DifAndCtrl_DW.d29 = (DifAndCtrl_DW.d80 + DifAndCtrl_DW.rtb_ginv_tmp_tmp) -
    DifAndCtrl_DW.d81;
  DifAndCtrl_DW.rtb_ginv_tmp_tmp =
    (((((((((((DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
               DifAndCtrl_DW.D46_tmp_p + DifAndCtrl_DW.tmp_tmp_f1) +
              DifAndCtrl_DW.d14) + DifAndCtrl_DW.rtb_ginv_tmp_tmp) -
            DifAndCtrl_DW.d35) - DifAndCtrl_DW.d79) +
          DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7] *
          DifAndCtrl_DW.D46_tmp_j) - DifAndCtrl_DW.d33) + DifAndCtrl_DW.d6) +
       DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
       DifAndCtrl_DW.D46_tmp_g) + DifAndCtrl_DW.d17) +
     DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6] *
     DifAndCtrl_DW.D46_tmp_b) + DifAndCtrl_DW.d23;
  DifAndCtrl_DW.x[29] = -(((((((((((((((((((((DifAndCtrl_DW.rtb_ginv_tmp_m -
    DifAndCtrl_DW.tmp_tmp * DifAndCtrl_DW.D46_tmp_bn) +
    DifAndCtrl_DW.rtb_ginv_tmp_p) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D46_tmp_da) - DifAndCtrl_DW.rtb_ginv_tmp_m0) -
    DifAndCtrl_DW.rtb_ginv_tmp_jg) - DifAndCtrl_DW.rtb_ginv_tmp_f) +
    -0.0027062010112 * DifAndCtrl_DW.D46_tmp_e) + -0.0040412944 *
    DifAndCtrl_DW.D46_tmp_e) + DifAndCtrl_DW.D47_tmp_px) +
    DifAndCtrl_DW.rtb_ginv_tmp_a) + DifAndCtrl_DW.D46_tmp_o) -
    DifAndCtrl_DW.D46_tmp_l5) - DifAndCtrl_DW.D46_tmp_m) +
    -0.0023282610207999996 * DifAndCtrl_DW.rtb_ginv_tmp) + DifAndCtrl_DW.d25) +
    DifAndCtrl_DW.d26) + DifAndCtrl_DW.d24) * DifAndCtrl_DW.d13 +
    DifAndCtrl_DW.D45_tmp_a * DifAndCtrl_DW.d78) + (((DifAndCtrl_DW.D56_tmp -
    DifAndCtrl_DW.d27) + DifAndCtrl_DW.D56_tmp_jg) + DifAndCtrl_DW.D56_tmp_e) *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]) * DifAndCtrl_DW.D15_tmp +
    (((((-0.0011641305103999998 * DifAndCtrl_DW.D38 + DifAndCtrl_DW.d29) +
        DifAndCtrl_DW.d6) + DifAndCtrl_DW.d17) + DifAndCtrl_DW.d23) *
     DifAndCtrl_DW.tmp_tmp_g + DifAndCtrl_DW.rtb_ginv_tmp_tmp * DifAndCtrl_DW.d8))
    * 0.25);
  DifAndCtrl_DW.tmp_tmp = 2.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3];
  DifAndCtrl_DW.tmp_tmp_g = DifAndCtrl_DW.tmp_tmp * 0.0069089343999999995;
  DifAndCtrl_DW.D15_tmp_g1 = -0.39176 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3];
  DifAndCtrl_DW.D45_tmp_a = 0.39176 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3];
  DifAndCtrl_DW.tmp_tmp_n = DifAndCtrl_DW.D14_tmp_m3 * 0.0069089343999999995;
  DifAndCtrl_DW.tmp_tmp_d = DifAndCtrl_DW.tmp_tmp *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4];
  DifAndCtrl_DW.tmp_tmp_na = DifAndCtrl_DW.d83 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8];
  DifAndCtrl_DW.tmp_tmp_c = DifAndCtrl_DW.tmp_tmp_g * 0.142;
  DifAndCtrl_DW.tmp_tmp_g *= 0.143;
  DifAndCtrl_DW.tmp_tmp_f = DifAndCtrl_DW.d1 * 0.0069089343999999995;
  DifAndCtrl_DW.D46_tmp_bn = -0.45856 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.08312 * 0.142;
  DifAndCtrl_DW.D56_tmp = DifAndCtrl_DW.D14_tmp_m3 * 0.08312 * 0.17 * 0.143;
  DifAndCtrl_DW.D56_tmp_lm = 0.45856 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.08312 * 0.142;
  DifAndCtrl_DW.tmp_tmp_p = DifAndCtrl_DW.d78 * 0.08312 * 0.17;
  DifAndCtrl_DW.tmp_tmp_p2 = DifAndCtrl_DW.d83 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  DifAndCtrl_DW.tmp_tmp_nj = DifAndCtrl_DW.tmp_tmp *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  DifAndCtrl_DW.tmp_tmp_k = 0.0262846592 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.142;
  DifAndCtrl_DW.tmp_tmp_n3 = DifAndCtrl_DW.tmp_tmp * 0.028900000000000006 *
    0.143;
  DifAndCtrl_DW.tmp_tmp_o = DifAndCtrl_DW.D15_tmp_g1 * 0.17 * 0.143;
  DifAndCtrl_DW.rtb_ginv_tmp_p = DifAndCtrl_DW.D15_tmp_g1 * 0.08312 * 0.143;
  DifAndCtrl_DW.rtb_ginv_tmp_a = DifAndCtrl_DW.D45_tmp_a * 0.08312 * 0.143;
  DifAndCtrl_DW.D45_tmp_a = DifAndCtrl_DW.D45_tmp_a * 0.17 * 0.143;
  DifAndCtrl_DW.tmp_tmp_gg = 0.39176 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.tmp_tmp_cq = DifAndCtrl_DW.d83 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  DifAndCtrl_DW.tmp_tmp *=
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  DifAndCtrl_DW.tmp_tmp_cj = 0.0191844872 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.143;
  DifAndCtrl_DW.tmp_tmp_m = DifAndCtrl_DW.D17_tmp_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.tmp_tmp_j = DifAndCtrl_DW.D17_tmp_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[6];
  DifAndCtrl_DW.tmp_tmp_pr = 0.0011641305103999998 * DifAndCtrl_DW.rtb_ginv_tmp;
  DifAndCtrl_DW.tmp_tmp_dz = DifAndCtrl_DW.d78 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  DifAndCtrl_DW.tmp_tmp_g4 = DifAndCtrl_DW.d78 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  DifAndCtrl_DW.tmp_tmp_c3 = DifAndCtrl_DW.d106 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.tmp_tmp_cx = DifAndCtrl_DW.d106 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.tmp_tmp_f1 =
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] -
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  DifAndCtrl_DW.rtb_ginv_tmp = DifAndCtrl_DW.tmp_tmp_p * 0.143;
  DifAndCtrl_DW.rtb_ginv_tmp_m = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3];
  DifAndCtrl_DW.rtb_ginv_tmp_m0 = DifAndCtrl_DW.d13 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  DifAndCtrl_DW.rtb_ginv_tmp_jg = DifAndCtrl_DW.d1 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4];
  DifAndCtrl_DW.rtb_ginv_tmp_f = 0.0262846592 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.142;
  DifAndCtrl_DW.x_a = DifAndCtrl_DW.d1 * 0.028900000000000006 * 0.143;
  DifAndCtrl_DW.tmp_tmp_jk = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3];
  DifAndCtrl_DW.tmp_tmp_fz = DifAndCtrl_DW.tmp_tmp_gg * 0.17 * 0.143;
  DifAndCtrl_DW.tmp_tmp_cm = DifAndCtrl_DW.d13 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  DifAndCtrl_DW.tmp_tmp_fq = DifAndCtrl_DW.d1 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4];
  DifAndCtrl_DW.tmp_tmp_nl = 0.0191844872 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.143;
  DifAndCtrl_DW.tmp_tmp_i = DifAndCtrl_DW.D46_tmp_bn * DifAndCtrl_DW.D18;
  DifAndCtrl_DW.tmp_tmp_l = DifAndCtrl_DW.D56_tmp * DifAndCtrl_DW.D18;
  DifAndCtrl_DW.tmp_tmp_i3 = DifAndCtrl_DW.rtb_ginv_tmp_m *
    DifAndCtrl_DW.D46_tmp_tmp;
  DifAndCtrl_DW.tmp_tmp_k1 = DifAndCtrl_DW.rtb_ginv_tmp_m0 *
    DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_fc = DifAndCtrl_DW.rtb_ginv_tmp_jg *
    DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_a = DifAndCtrl_DW.rtb_ginv_tmp_f *
    DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_d4 = DifAndCtrl_DW.x_a * DifAndCtrl_DW.D56_tmp_a;
  DifAndCtrl_DW.tmp_tmp_e = DifAndCtrl_DW.rtb_ginv_tmp_p * DifAndCtrl_DW.D38;
  DifAndCtrl_DW.tmp_tmp_eh = DifAndCtrl_DW.tmp_tmp_jk *
    DifAndCtrl_DW.D56_tmp_tmp_f;
  DifAndCtrl_DW.tmp_tmp_b = DifAndCtrl_DW.tmp_tmp_fz * DifAndCtrl_DW.D46;
  DifAndCtrl_DW.tmp_tmp_a0 = DifAndCtrl_DW.tmp_tmp_cm * DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.tmp_tmp_il = DifAndCtrl_DW.tmp_tmp_fq * DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.tmp_tmp_fa = DifAndCtrl_DW.tmp_tmp_nl * DifAndCtrl_DW.D56_tmp_ju;
  DifAndCtrl_DW.tmp_tmp_ji = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0];
  DifAndCtrl_DW.tmp_tmp_oo = DifAndCtrl_DW.d4 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0];
  DifAndCtrl_DW.D46_tmp_bn *= DifAndCtrl_DW.D17_tmp_p;
  DifAndCtrl_DW.D56_tmp *= DifAndCtrl_DW.D17_tmp_p;
  DifAndCtrl_DW.rtb_ginv_tmp_p *= DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.tmp_tmp_fr = DifAndCtrl_DW.tmp_tmp_o * DifAndCtrl_DW.D27;
  DifAndCtrl_DW.D46_tmp_tmp = DifAndCtrl_DW.d44 * DifAndCtrl_DW.D24_tmp;
  DifAndCtrl_DW.D56_tmp_tmp_f = DifAndCtrl_DW.d139 * DifAndCtrl_DW.D56_tmp_b;
  DifAndCtrl_DW.d8 = DifAndCtrl_DW.d144 * DifAndCtrl_DW.D56_tmp_h;
  DifAndCtrl_DW.d83 = DifAndCtrl_DW.d45 * DifAndCtrl_DW.D56_tmp_tmp_a;
  tmp =
    (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.tmp_tmp_m *
    DifAndCtrl_DW.D46_tmp_e1 + DifAndCtrl_DW.tmp_tmp_j *
    DifAndCtrl_DW.D46_tmp_tmp_o2) + DifAndCtrl_DW.tmp_tmp_d * DifAndCtrl_DW.D25)
    + DifAndCtrl_DW.d82) + DifAndCtrl_DW.tmp_tmp_na * DifAndCtrl_DW.D25) +
    DifAndCtrl_DW.d84) + DifAndCtrl_DW.tmp_tmp_c * DifAndCtrl_DW.D25) +
    DifAndCtrl_DW.d85) + DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D25) +
    DifAndCtrl_DW.d86) + DifAndCtrl_DW.D46_tmp_bn) + DifAndCtrl_DW.D56_tmp) +
    DifAndCtrl_DW.d87) + DifAndCtrl_DW.d88) + DifAndCtrl_DW.D56_tmp_lm *
    DifAndCtrl_DW.D16) + DifAndCtrl_DW.d89) + DifAndCtrl_DW.tmp_tmp_p * 0.143 *
    DifAndCtrl_DW.D16) + DifAndCtrl_DW.d90) + DifAndCtrl_DW.tmp_tmp_p2 *
    DifAndCtrl_DW.D56_tmp_j) + DifAndCtrl_DW.d91) + DifAndCtrl_DW.tmp_tmp_nj *
    DifAndCtrl_DW.D56_tmp_j) + DifAndCtrl_DW.d92) + DifAndCtrl_DW.tmp_tmp_k *
    DifAndCtrl_DW.D56_tmp_j) + DifAndCtrl_DW.d93) + DifAndCtrl_DW.tmp_tmp_n3 *
    DifAndCtrl_DW.D56_tmp_j) + DifAndCtrl_DW.d94) + DifAndCtrl_DW.tmp_tmp_fr) +
    DifAndCtrl_DW.rtb_ginv_tmp_p) + DifAndCtrl_DW.d95) + DifAndCtrl_DW.d96) +
    DifAndCtrl_DW.rtb_ginv_tmp_a * DifAndCtrl_DW.D34) + DifAndCtrl_DW.d97) +
    DifAndCtrl_DW.D45_tmp_a * DifAndCtrl_DW.D35) + DifAndCtrl_DW.d98) +
    DifAndCtrl_DW.tmp_tmp_cq * DifAndCtrl_DW.D56_tmp_f) + DifAndCtrl_DW.d99) +
    DifAndCtrl_DW.tmp_tmp * DifAndCtrl_DW.D56_tmp_f) + DifAndCtrl_DW.d100) +
    DifAndCtrl_DW.tmp_tmp_cj * DifAndCtrl_DW.D56_tmp_f) + DifAndCtrl_DW.d101) +
    DifAndCtrl_DW.D14_tmp_m3 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.D14_tmp_m3 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.D14_tmp_m3 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    DifAndCtrl_DW.D15_tmp) + -0.0525693184 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.142 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.tmp_tmp_n * 0.142 *
    DifAndCtrl_DW.D15_tmp) + -0.0383689744 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] * 0.143 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.tmp_tmp_n * 0.143 *
    DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.D14_tmp_m3 * 0.028900000000000006 *
    0.143 * DifAndCtrl_DW.D15_tmp) + DifAndCtrl_DW.tmp_tmp_d * DifAndCtrl_DW.D17)
    + DifAndCtrl_DW.d1 *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D17) + DifAndCtrl_DW.tmp_tmp_na * DifAndCtrl_DW.D17) +
    DifAndCtrl_DW.d13 * DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia
    [8] * DifAndCtrl_DW.D17) + DifAndCtrl_DW.tmp_tmp_c * DifAndCtrl_DW.D17) +
    DifAndCtrl_DW.tmp_tmp_f * 0.142 * DifAndCtrl_DW.D17) +
    DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D17) + DifAndCtrl_DW.tmp_tmp_f *
    0.143 * DifAndCtrl_DW.D17) + DifAndCtrl_DW.tmp_tmp_i) +
    DifAndCtrl_DW.tmp_tmp_l) + DifAndCtrl_DW.d102 * DifAndCtrl_DW.D46_tmp_j) +
    DifAndCtrl_DW.tmp_tmp_i3) + DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D24) +
    0.45856 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * 0.08312 * 0.142 *
    DifAndCtrl_DW.D24) + DifAndCtrl_DW.rtb_ginv_tmp * DifAndCtrl_DW.D24) +
    DifAndCtrl_DW.d28 * 0.08312 * 0.17 * 0.143 * DifAndCtrl_DW.D24) +
    DifAndCtrl_DW.tmp_tmp_p2 * DifAndCtrl_DW.D56_tmp_a) +
    DifAndCtrl_DW.tmp_tmp_k1) + DifAndCtrl_DW.tmp_tmp_nj *
    DifAndCtrl_DW.D56_tmp_a) + DifAndCtrl_DW.tmp_tmp_fc) +
    DifAndCtrl_DW.tmp_tmp_k * DifAndCtrl_DW.D56_tmp_a) + DifAndCtrl_DW.tmp_tmp_a)
    + DifAndCtrl_DW.tmp_tmp_n3 * DifAndCtrl_DW.D56_tmp_a) +
    DifAndCtrl_DW.tmp_tmp_d4) + DifAndCtrl_DW.tmp_tmp_o * DifAndCtrl_DW.D37) +
    DifAndCtrl_DW.tmp_tmp_e) + DifAndCtrl_DW.d103 * DifAndCtrl_DW.D46_tmp_d) +
    DifAndCtrl_DW.tmp_tmp_eh) + DifAndCtrl_DW.rtb_ginv_tmp_a *
    DifAndCtrl_DW.D46_tmp_tmp_ei) + DifAndCtrl_DW.tmp_tmp_gg * 0.08312 * 0.143 *
    DifAndCtrl_DW.D46_tmp_tmp_ei) + DifAndCtrl_DW.D45_tmp_a * DifAndCtrl_DW.D46)
    + DifAndCtrl_DW.tmp_tmp_b) + DifAndCtrl_DW.tmp_tmp_cq *
    DifAndCtrl_DW.D56_tmp_ju) + DifAndCtrl_DW.tmp_tmp_a0) +
    DifAndCtrl_DW.tmp_tmp * DifAndCtrl_DW.D56_tmp_ju) + DifAndCtrl_DW.tmp_tmp_il)
    + DifAndCtrl_DW.tmp_tmp_cj * DifAndCtrl_DW.D56_tmp_ju) +
    DifAndCtrl_DW.tmp_tmp_fa) + DifAndCtrl_DW.tmp_tmp_m *
    DifAndCtrl_DW.D46_tmp_tmp_e) + DifAndCtrl_DW.tmp_tmp_j *
    DifAndCtrl_DW.D46_tmp_tmp_c) + ((((((DifAndCtrl_DW.D48_tmp_k +
    DifAndCtrl_DW.D46_tmp_o) - DifAndCtrl_DW.D46_tmp_l5) -
    DifAndCtrl_DW.D46_tmp_m) - DifAndCtrl_DW.tmp_tmp_pr) - 0.0023809214000000004
    * DifAndCtrl_DW.D46_tmp_tmp_k) + DifAndCtrl_DW.d24) * (DifAndCtrl_DW.d3 *
    DifAndCtrl_DW.D15_tmp)) + ((((((((((((((DifAndCtrl_DW.tmp_tmp_f1 -
    0.0018662108031999999) - 0.0041327000000000004) * DifAndCtrl_DW.D46_tmp_da +
    DifAndCtrl_DW.D47_tmp_m) + -0.0013531005056 * DifAndCtrl_DW.D46_tmp_e) -
    0.0020206472 * DifAndCtrl_DW.D46_tmp_e) + DifAndCtrl_DW.D47_tmp_px) +
    DifAndCtrl_DW.D47_tmp) + DifAndCtrl_DW.D46_tmp_o) - DifAndCtrl_DW.D46_tmp_l5)
    - DifAndCtrl_DW.D46_tmp_m) - DifAndCtrl_DW.tmp_tmp_pr) + DifAndCtrl_DW.d25)
    + DifAndCtrl_DW.d26) + DifAndCtrl_DW.d24) * (DifAndCtrl_DW.D16_tmp *
    DifAndCtrl_DW.D15_tmp)) + DifAndCtrl_DW.d104) + DifAndCtrl_DW.d38 *
    DifAndCtrl_DW.D46_tmp_tmp_d) + DifAndCtrl_DW.d105 *
    DifAndCtrl_DW.D46_tmp_tmp_d) + DifAndCtrl_DW.tmp_tmp_c3 *
    DifAndCtrl_DW.D46_tmp_tmp_af) + DifAndCtrl_DW.d107) + DifAndCtrl_DW.d105 *
    DifAndCtrl_DW.D56) + DifAndCtrl_DW.d32 * DifAndCtrl_DW.D56_tmp_tmp_iz) +
    DifAndCtrl_DW.d40 * DifAndCtrl_DW.D56_tmp_tmp_g) + DifAndCtrl_DW.tmp_tmp_cx *
    DifAndCtrl_DW.D47_tmp_p) + DifAndCtrl_DW.d108) + DifAndCtrl_DW.d109) +
    DifAndCtrl_DW.d110) + DifAndCtrl_DW.d111) - DifAndCtrl_DW.d112) -
    DifAndCtrl_DW.d113) - DifAndCtrl_DW.d114) + DifAndCtrl_DW.tmp_tmp_dz *
    DifAndCtrl_DW.D56_tmp_d) + DifAndCtrl_DW.d115) + DifAndCtrl_DW.d116) +
                      DifAndCtrl_DW.d117) - DifAndCtrl_DW.d118) -
                    DifAndCtrl_DW.d119) + DifAndCtrl_DW.tmp_tmp_g4 *
                   DifAndCtrl_DW.D56_tmp_lx) + DifAndCtrl_DW.d120) +
                 DifAndCtrl_DW.tmp_tmp_ji * DifAndCtrl_DW.D46_tmp_h2) +
                DifAndCtrl_DW.d121 * DifAndCtrl_DW.D46_tmp_h2) +
               DifAndCtrl_DW.D17_tmp_tmp_i *
               DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
               DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.tmp_tmp_oo *
              DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.d122 *
             DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.D17_tmp_tmp_i *
            DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
            DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.D17_tmp_tmp_i *
           DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
           DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.d123 *
          DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.d4 *
         DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[8] *
         DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.d124 *
        DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.d125 *
       DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.d126 * DifAndCtrl_DW.D46_tmp_h2)
     + DifAndCtrl_DW.d37 * DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.d127 *
    DifAndCtrl_DW.D46_tmp_h2;
  DifAndCtrl_DW.x[37] = -(((((((((((((((((((((((((((((((tmp + DifAndCtrl_DW.d128)
    + DifAndCtrl_DW.d129) + DifAndCtrl_DW.d130) + DifAndCtrl_DW.d131) -
    DifAndCtrl_DW.d132) + DifAndCtrl_DW.d133) + DifAndCtrl_DW.d134) +
    DifAndCtrl_DW.d135 * DifAndCtrl_DW.D46_tmp_b) - DifAndCtrl_DW.d136) +
    DifAndCtrl_DW.d137) + DifAndCtrl_DW.d138) + DifAndCtrl_DW.D46_tmp_tmp) +
    DifAndCtrl_DW.tmp_tmp_dz * DifAndCtrl_DW.D56_tmp_b) +
    DifAndCtrl_DW.D56_tmp_tmp_f) + DifAndCtrl_DW.d140 * DifAndCtrl_DW.D46_tmp_ln)
    - DifAndCtrl_DW.d141) + DifAndCtrl_DW.d142) + DifAndCtrl_DW.d143) +
    DifAndCtrl_DW.tmp_tmp_g4 * DifAndCtrl_DW.D56_tmp_h) + DifAndCtrl_DW.d8) +
    DifAndCtrl_DW.d42 * DifAndCtrl_DW.D56_tmp_tmp) + DifAndCtrl_DW.d31 *
    DifAndCtrl_DW.D56_tmp_tmp) + DifAndCtrl_DW.tmp_tmp_c3 *
    DifAndCtrl_DW.D15_tmp_tmp) + DifAndCtrl_DW.d45 *
    DifAndCtrl_DW.D56_tmp_tmp_g2) + DifAndCtrl_DW.d36 *
    DifAndCtrl_DW.D14_tmp_tmp) + DifAndCtrl_DW.tmp_tmp_cx *
    DifAndCtrl_DW.D15_tmp_tmp_a) + DifAndCtrl_DW.d42 * DifAndCtrl_DW.D24_tmp_p)
    + DifAndCtrl_DW.d31 * DifAndCtrl_DW.D24_tmp_p) + DifAndCtrl_DW.d36 *
    DifAndCtrl_DW.D56_tmp_tmp_h) + DifAndCtrl_DW.d83) * 0.125);
  DifAndCtrl_DW.D17_tmp_tmp_i = DifAndCtrl_DW.rtb_ginv_tmp_tmp_f *
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_p;
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_p = -2.0 * DifAndCtrl_DW.rtb_ginv_tmp_tmp_p *
    DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.D16_tmp = 0.11464 * DifAndCtrl_DW.D15_tmp_g +
    DifAndCtrl_DW.D24_tmp_h;
  DifAndCtrl_DW.d3 = 0.08312 * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.d4 = 4.0 * DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.tmp_tmp = ((0.17 * DifAndCtrl_DW.D34_tmp + DifAndCtrl_DW.d3) +
    0.09794 * DifAndCtrl_DW.D34_tmp_m) * DifAndCtrl_DW.s -
    DifAndCtrl_DW.D24_tmp_n * DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.tmp_tmp_g = DifAndCtrl_DW.D46_tmp_mc * -2.0;
  DifAndCtrl_DW.d24 = DifAndCtrl_DW.D46_tmp_p4 * DifAndCtrl_DW.D56_tmp_tmp_tmp +
    DifAndCtrl_DW.tmp_tmp_f1 * DifAndCtrl_DW.D46_tmp;
  DifAndCtrl_DW.d25 = DifAndCtrl_DW.d4 * DifAndCtrl_DW.D17_tmp_h *
    DifAndCtrl_DW.D14_tmp_c * (DifAndCtrl_DW.rtb_ginv_tmp_tmp_b +
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_e);
  DifAndCtrl_DW.d26 = (DifAndCtrl_DW.rtb_ginv_tmp_tmp_i * 2.0 *
                       DifAndCtrl_DW.D46_tmp_h + 4.0 *
                       DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3]
                       * DifAndCtrl_DW.D46_tmp_n) * DifAndCtrl_DW.rtb_ginv_tmp_c;
  DifAndCtrl_DW.d28 = (DifAndCtrl_DW.rtb_ginv_tmp_o * 2.0 *
                       DifAndCtrl_DW.D46_tmp_h + -4.0 *
                       DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3]
                       * DifAndCtrl_DW.D46_tmp_n) *
    DifAndCtrl_DW.rtb_ginv_tmp_dd;
  DifAndCtrl_DW.tmp_tmp_n = DifAndCtrl_DW.tmp_tmp * 0.572;
  DifAndCtrl_DW.d3 = (0.11464 * DifAndCtrl_DW.D34_tmp + DifAndCtrl_DW.d3) *
    DifAndCtrl_DW.s;
  DifAndCtrl_DW.tmp_tmp_d = DifAndCtrl_DW.rtb_ginv_tmp_g *
    DifAndCtrl_DW.D14_tmp_nh * DifAndCtrl_DW.D46_tmp_h2;
  DifAndCtrl_DW.tmp_tmp_na = DifAndCtrl_DW.rtb_ginv_tmp_l * DifAndCtrl_DW.d145 *
    DifAndCtrl_DW.D46_tmp_h2;
  DifAndCtrl_DW.x[45] = -((((((((((((((((((((DifAndCtrl_DW.tmp_tmp_f1 *
    DifAndCtrl_DW.D14_tmp_cv * DifAndCtrl_DW.D14_tmp +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3] *
    DifAndCtrl_DW.D56_tmp_tmp_tmp) * (DifAndCtrl_DW.d4 * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.D14_tmp_c) * DifAndCtrl_DW.D14_tmp_m +
    (((DifAndCtrl_DW.D17_tmp_tmp_i * DifAndCtrl_DW.rtb_ginv_tmp_i +
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_p * DifAndCtrl_DW.rtb_ginv_tmp_d) +
    DifAndCtrl_DW.D17_tmp_tmp_i * DifAndCtrl_DW.rtb_ginv_tmp_g) +
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_p * DifAndCtrl_DW.rtb_ginv_tmp_l)) +
    ((DifAndCtrl_DW.D56_tmp_o3 * DifAndCtrl_DW.D14_tmp_cv *
    DifAndCtrl_DW.D14_tmp + DifAndCtrl_DW.rtb_ginv_tmp_db) +
     DifAndCtrl_DW.rtb_ginv_tmp_jr) * (DifAndCtrl_DW.tmp_tmp_g *
    DifAndCtrl_DW.D15_tmp) * DifAndCtrl_DW.D14_tmp_m) + -2.0 *
    DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.rtb_ginv_tmp_j *
    DifAndCtrl_DW.D46_tmp_h3 * DifAndCtrl_DW.D14_tmp_m) -
    DifAndCtrl_DW.D46_tmp_mc * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.w_a_tmp *
    DifAndCtrl_DW.D14_tmp_m) - DifAndCtrl_DW.rtb_ginv_tmp_j *
    DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.rtb_ginv_tmp_e *
    DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.rtb_ginv_tmp_tmp_f *
    DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D14_tmp_c * (DifAndCtrl_DW.D46_tmp_f *
    DifAndCtrl_DW.D46_tmp_n + DifAndCtrl_DW.rtb_ginv_tmp_tmp_i *
    DifAndCtrl_DW.D46_tmp_h) * DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.D16_tmp *
    -0.284 * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.smax * (DifAndCtrl_DW.d3 -
    DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_m)) +
    DifAndCtrl_DW.D24_tmp_n * -0.286 * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.smax * DifAndCtrl_DW.tmp_tmp) + -0.284 * DifAndCtrl_DW.s *
    DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D45_tmp_m) +
    -0.286 * DifAndCtrl_DW.s * DifAndCtrl_DW.D24_tmp_n * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.D24_tmp_m) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[8] *
    DifAndCtrl_DW.D46_tmp_h2) +
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[8] *
    DifAndCtrl_DW.D46_tmp_h2) +
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[0] *
    DifAndCtrl_DW.D46_tmp_h2) - DifAndCtrl_DW.rtb_ginv_tmp_o3 *
    DifAndCtrl_DW.D46_tmp_h2) - DifAndCtrl_DW.rtb_ginv_tmp_j *
    DifAndCtrl_ConstP.MATLABFunction1_HexaConstants.Inertia[4] *
    DifAndCtrl_DW.D46_tmp_h2) * DifAndCtrl_DW.d1 + ((((((DifAndCtrl_DW.d26 +
    DifAndCtrl_DW.d25) + DifAndCtrl_DW.d28) + DifAndCtrl_DW.D18_tmp * 0.572 *
    DifAndCtrl_DW.D24_tmp_m) + DifAndCtrl_DW.tmp_tmp_n * DifAndCtrl_DW.D17_tmp_m)
    + DifAndCtrl_DW.tmp_tmp_d) + DifAndCtrl_DW.tmp_tmp_na) *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[7]) +
    (((((((((((((DifAndCtrl_DW.D17_tmp_h * -2.0 * DifAndCtrl_DW.D14 *
                 (DifAndCtrl_DW.tmp_tmp_f1 * DifAndCtrl_DW.D56_tmp_tmp_tmp +
                  DifAndCtrl_DW.D56_tmp_o3 * DifAndCtrl_DW.D46_tmp) +
                 DifAndCtrl_DW.tmp_tmp_g * DifAndCtrl_DW.D17_tmp_h *
                 DifAndCtrl_DW.d24) + DifAndCtrl_DW.D17_tmp_h * 2.0 *
                DifAndCtrl_DW.rtb_ginv_tmp_j * DifAndCtrl_DW.d24) +
               DifAndCtrl_DW.d25) + DifAndCtrl_DW.d26) + DifAndCtrl_DW.d28) +
            (DifAndCtrl_DW.D17_tmp * DifAndCtrl_DW.D17_tmp_c +
             DifAndCtrl_DW.D17_tmp_m3 * DifAndCtrl_DW.D17_tmp_i) * 0.572 *
            DifAndCtrl_DW.D24_tmp_m) + (DifAndCtrl_DW.D17_tmp_tmp_e *
    -DifAndCtrl_DW.D17_tmp_c + DifAndCtrl_DW.D17_tmp_tmp_a *
    DifAndCtrl_DW.D17_tmp_i) * DifAndCtrl_DW.tmp_tmp_n) +
          (DifAndCtrl_DW.D17_tmp_g * DifAndCtrl_DW.D14_tmp_c +
           DifAndCtrl_DW.D17_tmp_n * DifAndCtrl_DW.D14_tmp_k) *
          (DifAndCtrl_DW.D45_tmp_m * 0.06511552)) + ((DifAndCtrl_DW.D14_tmp_cv *
    DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_m + -DifAndCtrl_DW.s *
    DifAndCtrl_DW.D14_tmp) * (0.11464 * DifAndCtrl_DW.D14_tmp_c) +
    (DifAndCtrl_DW.D17_tmp_tmp_l * DifAndCtrl_DW.D14_tmp_m +
     DifAndCtrl_DW.D17_tmp_tmp_c) * (0.11464 * DifAndCtrl_DW.D14_tmp_k)) *
         ((-DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_m
           + DifAndCtrl_DW.d3) * 0.568)) + DifAndCtrl_DW.rtb_ginv_tmp_i *
        DifAndCtrl_DW.D14_tmp_nh * DifAndCtrl_DW.D46_tmp_h2) +
       DifAndCtrl_DW.rtb_ginv_tmp_d * DifAndCtrl_DW.d145 *
       DifAndCtrl_DW.D46_tmp_h2) + DifAndCtrl_DW.tmp_tmp_d) +
     DifAndCtrl_DW.tmp_tmp_na) * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6])
    - (((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.D56_tmp_c *
    DifAndCtrl_DW.D46_tmp_p + DifAndCtrl_DW.D46_tmp_p4 * DifAndCtrl_DW.D56_tmp_j)
    + DifAndCtrl_DW.D56_tmp_nb * DifAndCtrl_DW.D46_tmp_l) +
    DifAndCtrl_DW.D46_tmp_f * DifAndCtrl_DW.D56_tmp_f) +
    DifAndCtrl_DW.D56_tmp_ij * DifAndCtrl_DW.D46_tmp_j) +
    DifAndCtrl_DW.D46_tmp_p4 * DifAndCtrl_DW.D56_tmp_a) +
    DifAndCtrl_DW.D56_tmp_m * DifAndCtrl_DW.D46_tmp_d) + DifAndCtrl_DW.D46_tmp_f
    * DifAndCtrl_DW.D56_tmp_ju) - DifAndCtrl_DW.D56_tmp_tmp_n) +
    DifAndCtrl_DW.D56_tmp_tmp_p) - DifAndCtrl_DW.D56_tmp_tmp_d) -
    DifAndCtrl_DW.D56_tmp_tmp_o) + DifAndCtrl_DW.D56_tmp_p *
    DifAndCtrl_DW.D46_tmp_g) + -0.0027062010112 * DifAndCtrl_DW.D56_tmp_l) +
    -0.0040412944 * DifAndCtrl_DW.D56_tmp_l) + DifAndCtrl_DW.D56_tmp_tmp_j) -
    DifAndCtrl_DW.D56_tmp_tmp_c2) - DifAndCtrl_DW.D56_tmp_tmp_hp) -
    DifAndCtrl_DW.D56_tmp_tmp_da) + DifAndCtrl_DW.D56_tmp_bp *
    DifAndCtrl_DW.D46_tmp_dy) + -0.0023282610207999996 *
    DifAndCtrl_DW.D56_tmp_jz) + -0.004761842800000001 * DifAndCtrl_DW.D56_tmp_o4)
    + DifAndCtrl_DW.D56_tmp_tmp_c5) - DifAndCtrl_DW.D56_tmp_tmp_pw) -
    DifAndCtrl_DW.D56_tmp_tmp_pi) - DifAndCtrl_DW.D56_tmp_tmp_a4) +
                      DifAndCtrl_DW.D56_tmp_tmp_ow) -
                     DifAndCtrl_DW.D56_tmp_tmp_jw) + -0.0009879776191999998 *
                    DifAndCtrl_DW.D56_tmp_o) + DifAndCtrl_DW.D56_tmp_ad *
                   DifAndCtrl_DW.D46_tmp_b) + -0.0027062010112 *
                  DifAndCtrl_DW.D56_tmp_n) + -0.0040412944 *
                 DifAndCtrl_DW.D56_tmp_n) + DifAndCtrl_DW.D56_tmp_tmp_pie) -
               DifAndCtrl_DW.D56_tmp_tmp_ob) - DifAndCtrl_DW.D56_tmp_tmp_l) -
             DifAndCtrl_DW.D56_tmp_tmp_k) + DifAndCtrl_DW.D56_tmp_k *
            DifAndCtrl_DW.D46_tmp_ln) + -0.0023282610207999996 *
           DifAndCtrl_DW.D56_tmp_ny) + -0.004761842800000001 *
          DifAndCtrl_DW.D56_tmp_i) + DifAndCtrl_DW.d27) -
        DifAndCtrl_DW.D56_tmp_jg) - DifAndCtrl_DW.D56_tmp_e) *
    DifAndCtrl_DW.D16_tmp_o) * 0.25);
  DifAndCtrl_DW.rtb_ginv_tmp_tmp_p = DifAndCtrl_DW.d78 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[7];
  DifAndCtrl_DW.d145 = 0.22928 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    0.08312 * 0.142;
  DifAndCtrl_DW.D16_tmp_o = DifAndCtrl_DW.d1 * 0.08312 * 0.17 * 0.143;
  DifAndCtrl_DW.D14_tmp_nh = DifAndCtrl_DW.d78 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[7];
  DifAndCtrl_DW.D17_tmp_tmp_i = 0.19588 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4];
  DifAndCtrl_DW.D16_tmp = DifAndCtrl_DW.D17_tmp_tmp_i * 0.08312 * 0.143;
  DifAndCtrl_DW.d3 = DifAndCtrl_DW.d78 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[6];
  DifAndCtrl_DW.d4 = DifAndCtrl_DW.d106 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3] *
    DifAndCtrl_DW.D46_tmp_bj;
  DifAndCtrl_DW.tmp_tmp = DifAndCtrl_DW.d52 * DifAndCtrl_DW.D46_tmp_tmp_o2;
  DifAndCtrl_DW.tmp_tmp_g = DifAndCtrl_DW.rtb_ginv_tmp_a *
    DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.d24 = DifAndCtrl_DW.w_a * DifAndCtrl_DW.D17_tmp_j;
  DifAndCtrl_DW.d25 = DifAndCtrl_DW.D14_tmp_nh * DifAndCtrl_DW.D46_tmp_l;
  DifAndCtrl_DW.D46_tmp_tmp_l *= DifAndCtrl_DW.tmp_tmp_jk;
  DifAndCtrl_DW.d26 = DifAndCtrl_DW.D16_tmp * DifAndCtrl_DW.D34;
  DifAndCtrl_DW.d27 = DifAndCtrl_DW.tmp_tmp_cm * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.d28 = DifAndCtrl_DW.tmp_tmp_fq * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.tmp_tmp_n = DifAndCtrl_DW.tmp_tmp_nl * DifAndCtrl_DW.D56_tmp_f;
  DifAndCtrl_DW.tmp_tmp_d = DifAndCtrl_DW.w_a * DifAndCtrl_DW.D38;
  DifAndCtrl_DW.D14_tmp_nh *= DifAndCtrl_DW.D46_tmp_d;
  DifAndCtrl_DW.D16_tmp *= DifAndCtrl_DW.D46_tmp_tmp_ei;
  DifAndCtrl_DW.D46_tmp_tmp_c *= DifAndCtrl_DW.d50;
  DifAndCtrl_DW.tmp_tmp_na = -0.5876399999999999 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.tmp_tmp_f1 = DifAndCtrl_DW.tmp_tmp_na * 0.08312 * 0.143 *
    DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.tmp_tmp_oo *= DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.tmp_tmp_jk = DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[4] *
    DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.tmp_tmp_cm = DifAndCtrl_DW.d126 * DifAndCtrl_DW.D46_tmp_c;
  DifAndCtrl_DW.d36 *= DifAndCtrl_DW.D47;
  DifAndCtrl_DW.D56_tmp_tmp_g *= DifAndCtrl_DW.d53;
  DifAndCtrl_DW.D47_tmp_p *= DifAndCtrl_DW.d46;
  DifAndCtrl_DW.D56_tmp_tmp_ff *= DifAndCtrl_DW.d53;
  DifAndCtrl_DW.tmp_tmp_fq = DifAndCtrl_DW.d153 * DifAndCtrl_DW.D46_tmp_dy;
  DifAndCtrl_DW.tmp_tmp_nl = DifAndCtrl_DW.d144 * DifAndCtrl_DW.D56_tmp_lx;
  DifAndCtrl_DW.tmp_tmp_c = DifAndCtrl_DW.d153 * DifAndCtrl_DW.D46_tmp_ln;
  DifAndCtrl_DW.d6 = (((DifAndCtrl_DW.d29 - DifAndCtrl_DW.d33) +
                       DifAndCtrl_DW.d6) + DifAndCtrl_DW.d17) +
    DifAndCtrl_DW.d23;
  DifAndCtrl_DW.d17 = DifAndCtrl_DW.d6 * DifAndCtrl_DW.d154;
  DifAndCtrl_DW.D14_tmp_tmp *= DifAndCtrl_DW.d53;
  DifAndCtrl_DW.D15_tmp_tmp_a *= DifAndCtrl_DW.d48;
  DifAndCtrl_DW.d53 *= DifAndCtrl_DW.D56_tmp_tmp_h;
  DifAndCtrl_DW.d23 = DifAndCtrl_DW.D56_tmp_tmp_fi * DifAndCtrl_DW.D46_tmp_tmp_d;
  DifAndCtrl_DW.d29 = DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D56;
  DifAndCtrl_DW.d37 = DifAndCtrl_DW.D56_tmp_tmp_fi * DifAndCtrl_DW.D56;
  DifAndCtrl_DW.d44 = DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D56_tmp_tmp;
  DifAndCtrl_DW.D56_tmp_tmp *= DifAndCtrl_DW.D56_tmp_tmp_fi;
  DifAndCtrl_DW.d46 = DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D24_tmp_p;
  DifAndCtrl_DW.D56_tmp_tmp_fi *= DifAndCtrl_DW.D24_tmp_p;
  DifAndCtrl_DW.x[53] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    (((((((((((((((((((((((((((((((((((DifAndCtrl_DW.d106 *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[3] *
    DifAndCtrl_DW.D46_tmp_da + DifAndCtrl_DW.d4) + DifAndCtrl_DW.d51 *
    DifAndCtrl_DW.D46_tmp_e1) + DifAndCtrl_DW.tmp_tmp) +
    DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D17_tmp_p) + DifAndCtrl_DW.ab_a *
    DifAndCtrl_DW.D17_tmp_p) + DifAndCtrl_DW.rtb_ginv_tmp *
    DifAndCtrl_DW.D17_tmp_p) + DifAndCtrl_DW.D57 * DifAndCtrl_DW.D17_tmp_p) +
    DifAndCtrl_DW.rtb_ginv_tmp_tmp_p * DifAndCtrl_DW.D46_tmp_p) +
    DifAndCtrl_DW.rtb_ginv_tmp_m * DifAndCtrl_DW.D46_tmp_tmp_o) +
    DifAndCtrl_DW.d145 * DifAndCtrl_DW.D16) + DifAndCtrl_DW.D16_tmp_o *
    DifAndCtrl_DW.D16) + DifAndCtrl_DW.rtb_ginv_tmp_m0 * DifAndCtrl_DW.D56_tmp_j)
    + DifAndCtrl_DW.rtb_ginv_tmp_jg * DifAndCtrl_DW.D56_tmp_j) +
    DifAndCtrl_DW.rtb_ginv_tmp_f * DifAndCtrl_DW.D56_tmp_j) + DifAndCtrl_DW.x_a *
    DifAndCtrl_DW.D56_tmp_j) + DifAndCtrl_DW.d146) + DifAndCtrl_DW.tmp_tmp_g) +
    DifAndCtrl_DW.d24) + DifAndCtrl_DW.d25) + DifAndCtrl_DW.D46_tmp_tmp_l) +
    DifAndCtrl_DW.d26) + DifAndCtrl_DW.tmp_tmp_fz * DifAndCtrl_DW.D35) +
    DifAndCtrl_DW.d27) + DifAndCtrl_DW.d28) + DifAndCtrl_DW.tmp_tmp_n) +
    DifAndCtrl_DW.d147) + DifAndCtrl_DW.d148) + DifAndCtrl_DW.d149) +
    DifAndCtrl_DW.d150) + DifAndCtrl_DW.d151) + DifAndCtrl_DW.tmp_tmp_i) +
    DifAndCtrl_DW.ab_a * DifAndCtrl_DW.D18) + DifAndCtrl_DW.tmp_tmp_l) +
    DifAndCtrl_DW.D57 * DifAndCtrl_DW.D18) + DifAndCtrl_DW.rtb_ginv_tmp_tmp_p *
    DifAndCtrl_DW.D46_tmp_j) + DifAndCtrl_DW.tmp_tmp_i3) + DifAndCtrl_DW.d145 *
    DifAndCtrl_DW.D24) + DifAndCtrl_DW.D16_tmp_o * DifAndCtrl_DW.D24) +
    DifAndCtrl_DW.tmp_tmp_k1) + DifAndCtrl_DW.tmp_tmp_fc) +
    DifAndCtrl_DW.tmp_tmp_a) + DifAndCtrl_DW.tmp_tmp_d4) + DifAndCtrl_DW.d152) +
    DifAndCtrl_DW.tmp_tmp_e) + DifAndCtrl_DW.tmp_tmp_d) +
    DifAndCtrl_DW.D14_tmp_nh) + DifAndCtrl_DW.tmp_tmp_eh) +
    DifAndCtrl_DW.D16_tmp) + DifAndCtrl_DW.tmp_tmp_b) + DifAndCtrl_DW.tmp_tmp_a0)
    + DifAndCtrl_DW.tmp_tmp_il) + DifAndCtrl_DW.tmp_tmp_fa) + DifAndCtrl_DW.d49 *
    DifAndCtrl_DW.D46_tmp_tmp_e) + DifAndCtrl_DW.D46_tmp_tmp_c) + -0.68784 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.08312 * 0.142 *
    DifAndCtrl_DW.D14_tmp) + -6.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE
    [5] * 0.08312 * 0.17 * 0.143 * DifAndCtrl_DW.D14_tmp) +
    DifAndCtrl_DW.tmp_tmp_ji * DifAndCtrl_DW.D46_tmp_cs) +
    DifAndCtrl_DW.D16_tmp_i *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[4] *
    DifAndCtrl_DW.D46_tmp_cs) + DifAndCtrl_DW.d124 * DifAndCtrl_DW.D46_tmp_cs) +
    DifAndCtrl_DW.d127 * DifAndCtrl_DW.D46_tmp_cs) + DifAndCtrl_DW.d42 *
    DifAndCtrl_DW.D15) + DifAndCtrl_DW.d31 * DifAndCtrl_DW.D15) +
    DifAndCtrl_DW.tmp_tmp_f1) + DifAndCtrl_DW.tmp_tmp_oo) +
    DifAndCtrl_DW.tmp_tmp_jk) + DifAndCtrl_DW.tmp_tmp_cm) + DifAndCtrl_DW.d36) +
    0.39176 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.17 * 0.143 *
    DifAndCtrl_DW.D56_tmp_tmp_i) + DifAndCtrl_DW.d45 *
    DifAndCtrl_DW.D46_tmp_tmp_a) + DifAndCtrl_DW.D48_tmp *
    DifAndCtrl_DW.D46_tmp_tmp_d) + DifAndCtrl_DW.d23) + DifAndCtrl_DW.d43 *
    DifAndCtrl_DW.D46_tmp_tmp_af) + DifAndCtrl_DW.d29) + DifAndCtrl_DW.d37) +
    DifAndCtrl_DW.D56_tmp_tmp_g) + DifAndCtrl_DW.D47_tmp_p) +
    DifAndCtrl_DW.D56_tmp_tmp_ff) + DifAndCtrl_DW.d3 * DifAndCtrl_DW.D46_tmp_g)
    - DifAndCtrl_DW.d111) + DifAndCtrl_DW.d112) + DifAndCtrl_DW.d113) +
    DifAndCtrl_DW.d114) + DifAndCtrl_DW.d139 * DifAndCtrl_DW.D56_tmp_d) +
    DifAndCtrl_DW.tmp_tmp_fq) + -DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[0] *
    DifAndCtrl_DW.D45_tmp) + DifAndCtrl_DW.d118) + DifAndCtrl_DW.d119) +
    DifAndCtrl_DW.tmp_tmp_nl) + DifAndCtrl_DW.d3 * DifAndCtrl_DW.D46_tmp_b) +
    -DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1[0] *
    DifAndCtrl_DW.D24_tmp) + DifAndCtrl_DW.d137) + DifAndCtrl_DW.d138) +
                        DifAndCtrl_DW.D46_tmp_tmp) + DifAndCtrl_DW.D56_tmp_tmp_f)
                      + DifAndCtrl_DW.tmp_tmp_c) + DifAndCtrl_DW.d17) +
                    DifAndCtrl_DW.rtb_ginv_tmp_tmp * DifAndCtrl_DW.d155) -
                   DifAndCtrl_DW.d141) + DifAndCtrl_DW.d142) +
                 DifAndCtrl_DW.d143) + DifAndCtrl_DW.d8) + DifAndCtrl_DW.d44) +
              DifAndCtrl_DW.D56_tmp_tmp) + DifAndCtrl_DW.d47 *
             DifAndCtrl_DW.D15_tmp_tmp) + DifAndCtrl_DW.D14_tmp_tmp) +
           DifAndCtrl_DW.D15_tmp_tmp_a) + DifAndCtrl_DW.d46) +
         DifAndCtrl_DW.D56_tmp_tmp_fi) + DifAndCtrl_DW.d53) + DifAndCtrl_DW.d83)
      * 0.125);
  DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.D17_tmp_tmp_i * 0.17 * 0.143;
  DifAndCtrl_DW.D56_tmp_tmp_f = DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D46_tmp_tmp_a;
  DifAndCtrl_DW.D15_tmp_tmp = DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D56_tmp_tmp_iz;
  DifAndCtrl_DW.D46_tmp_tmp_e = DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D56_tmp_tmp_g2;
  DifAndCtrl_DW.D46_tmp_tmp_a = DifAndCtrl_DW.D14_tmp_o3 *
    DifAndCtrl_DW.D56_tmp_tmp_a;
  DifAndCtrl_DW.x[61] =
    -((((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.d4 +
    DifAndCtrl_DW.tmp_tmp) + DifAndCtrl_DW.D45_tmp_a * DifAndCtrl_DW.D27) +
    DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.D27) + DifAndCtrl_DW.tmp_tmp_g)
    + DifAndCtrl_DW.d24) + DifAndCtrl_DW.d25) + DifAndCtrl_DW.D46_tmp_tmp_l) +
    DifAndCtrl_DW.d26) + DifAndCtrl_DW.D46_tmp_tmp_o * DifAndCtrl_DW.D35) +
    DifAndCtrl_DW.d27) + DifAndCtrl_DW.d28) + DifAndCtrl_DW.tmp_tmp_n) +
    DifAndCtrl_DW.d148) + DifAndCtrl_DW.d150) + DifAndCtrl_DW.D15_tmp_g1 * 0.17 *
    0.143 * DifAndCtrl_DW.D37) + DifAndCtrl_DW.D56_tmp_tmp_c * DifAndCtrl_DW.D37)
    + DifAndCtrl_DW.tmp_tmp_e) + DifAndCtrl_DW.tmp_tmp_d) +
    DifAndCtrl_DW.D14_tmp_nh) + DifAndCtrl_DW.tmp_tmp_eh) +
    DifAndCtrl_DW.D16_tmp) + DifAndCtrl_DW.D46_tmp_tmp_o * DifAndCtrl_DW.D46) +
    DifAndCtrl_DW.tmp_tmp_a0) + DifAndCtrl_DW.tmp_tmp_il) +
    DifAndCtrl_DW.tmp_tmp_fa) + DifAndCtrl_DW.D46_tmp_tmp_c) +
    DifAndCtrl_DW.tmp_tmp_na * 0.17 * 0.143 * DifAndCtrl_DW.D14_tmp_b) +
    DifAndCtrl_DW.tmp_tmp_f1) + DifAndCtrl_DW.tmp_tmp_oo) +
    DifAndCtrl_DW.tmp_tmp_jk) + DifAndCtrl_DW.tmp_tmp_cm) + DifAndCtrl_DW.d36) +
    DifAndCtrl_DW.d45 * DifAndCtrl_DW.D56_tmp_tmp_i) +
    DifAndCtrl_DW.D56_tmp_tmp_f) + DifAndCtrl_DW.D15_tmp_tmp) +
    DifAndCtrl_DW.D56_tmp_tmp_g) + DifAndCtrl_DW.D47_tmp_p) +
                        DifAndCtrl_DW.D56_tmp_tmp_ff) + DifAndCtrl_DW.tmp_tmp_fq)
                      - DifAndCtrl_DW.d117) + DifAndCtrl_DW.d118) +
                    DifAndCtrl_DW.d119) + DifAndCtrl_DW.tmp_tmp_nl) +
                  DifAndCtrl_DW.tmp_tmp_c) + DifAndCtrl_DW.d6 *
                 DifAndCtrl_DW.d155) + DifAndCtrl_DW.d17) - DifAndCtrl_DW.d141)
              + DifAndCtrl_DW.d142) + DifAndCtrl_DW.d143) + DifAndCtrl_DW.d8) +
           DifAndCtrl_DW.D46_tmp_tmp_e) + DifAndCtrl_DW.D14_tmp_tmp) +
         DifAndCtrl_DW.D15_tmp_tmp_a) + DifAndCtrl_DW.d53) +
       DifAndCtrl_DW.D46_tmp_tmp_a) * 0.125);
  DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.d15 * 0.17 * 0.143 *
    DifAndCtrl_DW.D14_tmp_b;
  DifAndCtrl_DW.D46_tmp_tmp_l = DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[3] -
    DifAndCtrl_DW.D17_tmp_tmp;
  DifAndCtrl_DW.x[30] = -(DifAndCtrl_DW.d19 * DifAndCtrl_DW.D46_tmp_tmp_l +
    DifAndCtrl_DW.D46_tmp_tmp_o);
  DifAndCtrl_DW.x[38] = -((((((((((((((((DifAndCtrl_DW.d156 + DifAndCtrl_DW.d18)
    + 0.0020206472 * DifAndCtrl_DW.D14_tmp) - DifAndCtrl_DW.D16_tmp_p) +
    DifAndCtrl_DW.d) + DifAndCtrl_DW.d2) + DifAndCtrl_DW.D16_tmp_k) +
    0.0013531005056 * DifAndCtrl_DW.D15) + DifAndCtrl_DW.d20) +
    DifAndCtrl_DW.d21) - DifAndCtrl_DW.d10) + DifAndCtrl_DW.D14_tmp_o) +
    DifAndCtrl_DW.D14_tmp_pe) + DifAndCtrl_DW.d22) + DifAndCtrl_DW.d157) *
    DifAndCtrl_DW.d1 - DifAndCtrl_DW.D27_tmp_m *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]) * 0.25);
  DifAndCtrl_DW.D15_tmp_tmp_a = DifAndCtrl_DW.rtb_ginv_tmp_a * DifAndCtrl_DW.D38;
  DifAndCtrl_DW.D46_tmp_tmp_c = 0.5876399999999999 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5];
  DifAndCtrl_DW.D46_tmp_tmp_af = DifAndCtrl_DW.D46_tmp_tmp_c * 0.08312 * 0.143 *
    DifAndCtrl_DW.D14_tmp_p;
  DifAndCtrl_DW.D47_tmp_p = DifAndCtrl_DW.d40 * DifAndCtrl_DW.D47;
  DifAndCtrl_DW.x[46] =
    -(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((DifAndCtrl_DW.d158
    + DifAndCtrl_DW.D46_tmp_bn) + DifAndCtrl_DW.D56_tmp) + DifAndCtrl_DW.d88) +
    DifAndCtrl_DW.rtb_ginv_tmp_p) + DifAndCtrl_DW.d96) +
    DifAndCtrl_DW.D56_tmp_lm * DifAndCtrl_DW.D18) + DifAndCtrl_DW.rtb_ginv_tmp *
    DifAndCtrl_DW.D18) + DifAndCtrl_DW.d159) + DifAndCtrl_DW.D15_tmp_tmp_a) +
    DifAndCtrl_DW.d160) + DifAndCtrl_DW.d161) + DifAndCtrl_DW.d162) + 0.68784 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.08312 * 0.142 *
    DifAndCtrl_DW.D14_tmp) + 6.0 * DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5]
    * 0.08312 * 0.17 * 0.143 * DifAndCtrl_DW.D14_tmp) + DifAndCtrl_DW.d163) +
    DifAndCtrl_DW.d164) + DifAndCtrl_DW.d165) + DifAndCtrl_DW.d166 * 0.143 *
    DifAndCtrl_DW.D46_tmp_cs) + DifAndCtrl_DW.d38 * DifAndCtrl_DW.D15) +
    DifAndCtrl_DW.d39 * DifAndCtrl_DW.D15) + DifAndCtrl_DW.D46_tmp_tmp_af) +
    DifAndCtrl_DW.d167) + DifAndCtrl_DW.d168) + DifAndCtrl_DW.d169) +
    DifAndCtrl_DW.D47_tmp_p) + DifAndCtrl_DW.d170) + DifAndCtrl_DW.d104) -
    DifAndCtrl_DW.D14_tmp_ms * DifAndCtrl_DW.D46_tmp_tmp_d) - DifAndCtrl_DW.d23)
    + DifAndCtrl_DW.d171) - DifAndCtrl_DW.d29) - DifAndCtrl_DW.d37) -
    DifAndCtrl_DW.D56_tmp_tmp_g) + DifAndCtrl_DW.d172) -
    DifAndCtrl_DW.D56_tmp_tmp_ff) + DifAndCtrl_DW.d111) - DifAndCtrl_DW.d112) -
    DifAndCtrl_DW.d113) - DifAndCtrl_DW.d114) + DifAndCtrl_DW.d117) -
    DifAndCtrl_DW.d118) - DifAndCtrl_DW.d119) + DifAndCtrl_DW.d173 * 0.17 *
                        0.143 * DifAndCtrl_DW.D14_tmp_b *
                        DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.d136) -
                      DifAndCtrl_DW.d137) - DifAndCtrl_DW.d138) -
                    DifAndCtrl_DW.D46_tmp_tmp) + DifAndCtrl_DW.d141) -
                  DifAndCtrl_DW.d142) - DifAndCtrl_DW.d143) +
                ((((((((((((((((((((((((((((((((((((((((((-DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia1
    [0] * DifAndCtrl_DW.D56_tmp_j + DifAndCtrl_DW.D27_tmp_o) +
    DifAndCtrl_DW.D14_tmp_cx) + DifAndCtrl_DW.d9) + DifAndCtrl_DW.d11) +
    DifAndCtrl_DW.d12) + DifAndCtrl_DW.d14) + DifAndCtrl_DW.D14_tmp_f) +
    DifAndCtrl_DW.d16) + DifAndCtrl_DW.D14_tmp_n) - DifAndCtrl_DW.D14_tmp_tmp_h)
    + DifAndCtrl_DW.D14_tmp_tmp_m) + DifAndCtrl_DW.D14_tmp_cz) +
    DifAndCtrl_DW.D15_tmp_tmp_c) + DifAndCtrl_DW.D15_tmp_tmp_f) +
    DifAndCtrl_DW.D16_tmp_tmp) + DifAndCtrl_DW.D34_tmp_l) +
    DifAndCtrl_DW.D37_tmp) + DifAndCtrl_DW.d35) + DifAndCtrl_DW.d79) +
    DifAndCtrl_DW.rtb_ginv_tmp_b) + DifAndCtrl_DW.d174) + DifAndCtrl_DW.d175) -
    DifAndCtrl_DW.d54) + DifAndCtrl_DW.d55) + DifAndCtrl_DW.d56) +
    DifAndCtrl_DW.d57) + DifAndCtrl_DW.d58) + DifAndCtrl_DW.d33) +
    DifAndCtrl_DW.d59) + DifAndCtrl_DW.d34) + DifAndCtrl_DW.d60) -
    DifAndCtrl_DW.d61) + DifAndCtrl_DW.d62) + DifAndCtrl_DW.d63) +
                        DifAndCtrl_DW.d64) + DifAndCtrl_DW.d65) +
                      DifAndCtrl_DW.d66) + DifAndCtrl_DW.d67) +
                    DifAndCtrl_DW.d68) + DifAndCtrl_DW.d69) + DifAndCtrl_DW.d70)
                 + DifAndCtrl_DW.d71) * DifAndCtrl_DW.d13) - DifAndCtrl_DW.d44)
              - DifAndCtrl_DW.D56_tmp_tmp) + DifAndCtrl_DW.d176) -
            DifAndCtrl_DW.D14_tmp_tmp) + DifAndCtrl_DW.d177) - DifAndCtrl_DW.d46)
         - DifAndCtrl_DW.D56_tmp_tmp_fi) - DifAndCtrl_DW.d53) +
       DifAndCtrl_DW.d178) * 0.125);
  DifAndCtrl_DW.x[54] = -DifAndCtrl_DW.D46_tmp_tmp_o;
  DifAndCtrl_DW.x[62] = -(-0.0023809214000000004 * DifAndCtrl_DW.D14_tmp_b *
    DifAndCtrl_DW.d7);
  DifAndCtrl_DW.x[31] = -((DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * 0.17
    * DifAndCtrl_DW.D14_tmp_b + DifAndCtrl_DW.d41 * DifAndCtrl_DW.D46_tmp_tmp_l)
    * 0.01400542);
  DifAndCtrl_DW.x[39] = -((DifAndCtrl_DW.d30 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] * DifAndCtrl_DW.D34_tmp_m +
    -DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[4] *
    DifAndCtrl_ConstP.MATLABFunction1_ArmConstants.Inertia2[3] *
    DifAndCtrl_DW.D46_tmp_bj) + -0.25 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * DifAndCtrl_DW.d179);
  DifAndCtrl_DW.x[47] = -((((((((((((((((((((((((((((((((((DifAndCtrl_DW.d180 +
    DifAndCtrl_DW.d181) + DifAndCtrl_DW.tmp_tmp_fr) +
    DifAndCtrl_DW.rtb_ginv_tmp_p) + DifAndCtrl_DW.d96) + DifAndCtrl_DW.D45_tmp_a
    * DifAndCtrl_DW.D37) + DifAndCtrl_DW.D15_tmp_tmp_a) + DifAndCtrl_DW.d160) +
    DifAndCtrl_DW.d162) + DifAndCtrl_DW.D46_tmp_tmp_c * 0.17 * 0.143 *
    DifAndCtrl_DW.D14_tmp_b) + DifAndCtrl_DW.D46_tmp_tmp_af) +
    DifAndCtrl_DW.d167) + DifAndCtrl_DW.d168) + DifAndCtrl_DW.d169) +
    DifAndCtrl_DW.D47_tmp_p) + DifAndCtrl_DW.d32 * DifAndCtrl_DW.D56_tmp_tmp_i)
    - DifAndCtrl_DW.D56_tmp_tmp_f) - DifAndCtrl_DW.D15_tmp_tmp) -
    DifAndCtrl_DW.D56_tmp_tmp_g) + DifAndCtrl_DW.d172) -
    DifAndCtrl_DW.D56_tmp_tmp_ff) + DifAndCtrl_DW.d117) - DifAndCtrl_DW.d118) -
    DifAndCtrl_DW.d119) + -0.78352 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[6] * 0.17 * 0.143 *
    DifAndCtrl_DW.D14_tmp_b * DifAndCtrl_DW.D14_tmp_m) + DifAndCtrl_DW.d141) -
    DifAndCtrl_DW.d142) - DifAndCtrl_DW.d143) + DifAndCtrl_DW.d179 *
    DifAndCtrl_DW.d13) - DifAndCtrl_DW.D46_tmp_tmp_e) -
    DifAndCtrl_DW.D14_tmp_tmp) + DifAndCtrl_DW.d177) + -0.09794 *
    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[5] * 0.08312 * 0.143 *
    DifAndCtrl_DW.D56_tmp_tmp_h) - DifAndCtrl_DW.D46_tmp_tmp_a) * 0.125);
  DifAndCtrl_DW.x[55] = -(0.0023809214000000004 * DifAndCtrl_DW.D14_tmp_b *
    DifAndCtrl_DW.d5);
  DifAndCtrl_DW.x[63] = -0.0;
  memset(&DifAndCtrl_DW.x[0], 0, 24U * sizeof(real_T));
  memset(&DifAndCtrl_DW.e_hat[0], 0, sizeof(real_T) << 3U);
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    DifAndCtrl_DW.D46_tmp_tmp_o =
      DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[DifAndCtrl_DW.ix];
    for (i = 0; i < 8; i++) {
      DifAndCtrl_DW.e_hat[i] += DifAndCtrl_DW.x[(DifAndCtrl_DW.ix << 3) + i] *
        DifAndCtrl_DW.D46_tmp_tmp_o;
    }
  }

  DifAndCtrl_DW.rtb_Sum3_tmp[0] = 0.0;
  DifAndCtrl_DW.rtb_Sum3_tmp[1] = 0.0;
  DifAndCtrl_DW.rtb_Sum3_tmp[2] = 20.631230269999996;
  DifAndCtrl_DW.D46_tmp_tmp_o = -9.80665 * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.rtb_Sum3_tmp[3] = ((-0.023689199999999997 *
    DifAndCtrl_DW.D14_tmp_c - DifAndCtrl_DW.D34_tmp_a) - DifAndCtrl_DW.D34_tmp_i)
    * DifAndCtrl_DW.D46_tmp_tmp_o;
  DifAndCtrl_DW.rtb_Sum3_tmp[4] = DifAndCtrl_DW.D15_tmp_c * 9.80665 *
    DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.rtb_Sum3_tmp[5] = 0.0;
  DifAndCtrl_DW.rtb_Sum3_tmp[6] = (-0.040588879999999994 * DifAndCtrl_DW.D34_tmp
    - DifAndCtrl_DW.D34_tmp_i) * DifAndCtrl_DW.D46_tmp_tmp_o;
  DifAndCtrl_DW.rtb_Sum3_tmp[7] = 0.137346252043 * DifAndCtrl_DW.D15_tmp *
    DifAndCtrl_DW.D34_tmp_m;
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    // MATLAB Function: '<S9>/MATLAB Function1'
    DifAndCtrl_DW.fx[DifAndCtrl_DW.ix] = DifAndCtrl_DW.e_hat[DifAndCtrl_DW.ix] -
      DifAndCtrl_DW.rtb_Sum3_tmp[DifAndCtrl_DW.ix];
  }

  // MATLAB Function: '<S9>/MATLAB Function1'
  DifAndCtrl_mldivide_0QKHZcd4_c(DifAndCtrl_DW.ginv, DifAndCtrl_DW.fx);

  // MATLAB Function: '<S2>/GetBInvMatrix' incorporates:
  //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator2'

  DifAndCtrl_DW.D14_tmp = tan(DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[4]);
  memset(&DifAndCtrl_DW.x[0], 0, sizeof(real_T) << 6U);
  memset(&DifAndCtrl_DW.BMinv[0], 0, sizeof(real_T) << 6U);
  DifAndCtrl_DW.x[0] = DifAndCtrl_DW.s * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.x[8] = DifAndCtrl_DW.D17_tmp_m3;
  DifAndCtrl_DW.x[16] = DifAndCtrl_DW.D17_tmp;
  DifAndCtrl_DW.x[24] = 0.0;
  DifAndCtrl_DW.x[32] = 0.0;
  DifAndCtrl_DW.x[40] = 0.0;
  DifAndCtrl_DW.x[1] = DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.smax;
  DifAndCtrl_DW.x[9] = DifAndCtrl_DW.D17_tmp_tmp_a;
  DifAndCtrl_DW.x[17] = DifAndCtrl_DW.D27_tmp;
  DifAndCtrl_DW.x[25] = 0.0;
  DifAndCtrl_DW.x[33] = 0.0;
  DifAndCtrl_DW.x[41] = 0.0;
  DifAndCtrl_DW.x[2] = -DifAndCtrl_DW.D14_tmp_m;
  DifAndCtrl_DW.x[10] = DifAndCtrl_DW.D15_tmp * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.x[18] = DifAndCtrl_DW.D14_tmp_k * DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.x[26] = 0.0;
  DifAndCtrl_DW.x[34] = 0.0;
  DifAndCtrl_DW.x[42] = 0.0;
  DifAndCtrl_DW.x[3] = 0.0;
  DifAndCtrl_DW.x[11] = 0.0;
  DifAndCtrl_DW.x[19] = 0.0;
  DifAndCtrl_DW.x[27] = 1.0;
  DifAndCtrl_DW.x[35] = DifAndCtrl_DW.D14_tmp_c * DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.x[43] = DifAndCtrl_DW.D14_tmp_k * DifAndCtrl_DW.D14_tmp;
  DifAndCtrl_DW.x[4] = 0.0;
  DifAndCtrl_DW.x[12] = 0.0;
  DifAndCtrl_DW.x[20] = 0.0;
  DifAndCtrl_DW.x[28] = 0.0;
  DifAndCtrl_DW.x[36] = DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.x[44] = -DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.x[5] = 0.0;
  DifAndCtrl_DW.x[13] = 0.0;
  DifAndCtrl_DW.x[21] = 0.0;
  DifAndCtrl_DW.x[29] = 0.0;
  DifAndCtrl_DW.smax = 1.0 / DifAndCtrl_DW.D15_tmp;
  DifAndCtrl_DW.x[37] = DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_c;
  DifAndCtrl_DW.x[45] = DifAndCtrl_DW.smax * DifAndCtrl_DW.D14_tmp_k;
  DifAndCtrl_DW.x[54] = 1.0;
  DifAndCtrl_DW.x[55] = 0.0;
  DifAndCtrl_DW.x[62] = 0.0;
  DifAndCtrl_DW.x[63] = 1.0;
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    DifAndCtrl_DW.ipiv[DifAndCtrl_DW.ix] = static_cast<int8_T>(DifAndCtrl_DW.ix
      + 1);
  }

  for (i = 0; i < 7; i++) {
    DifAndCtrl_DW.jj = i * 9;
    iy = 9 - i;
    DifAndCtrl_DW.b_ix = 0;
    DifAndCtrl_DW.smax = fabs(DifAndCtrl_DW.x[DifAndCtrl_DW.jj]);
    for (DifAndCtrl_DW.d_k = 2; DifAndCtrl_DW.d_k < iy; DifAndCtrl_DW.d_k++) {
      DifAndCtrl_DW.s = fabs(DifAndCtrl_DW.x[(DifAndCtrl_DW.jj +
        DifAndCtrl_DW.d_k) - 1]);
      if (DifAndCtrl_DW.s > DifAndCtrl_DW.smax) {
        DifAndCtrl_DW.b_ix = DifAndCtrl_DW.d_k - 1;
        DifAndCtrl_DW.smax = DifAndCtrl_DW.s;
      }
    }

    if (DifAndCtrl_DW.x[DifAndCtrl_DW.jj + DifAndCtrl_DW.b_ix] != 0.0) {
      if (DifAndCtrl_DW.b_ix != 0) {
        iy = i + DifAndCtrl_DW.b_ix;
        DifAndCtrl_DW.ipiv[i] = static_cast<int8_T>(iy + 1);
        DifAndCtrl_DW.b_ix = i;
        for (DifAndCtrl_DW.d_k = 0; DifAndCtrl_DW.d_k < 8; DifAndCtrl_DW.d_k++)
        {
          DifAndCtrl_DW.smax = DifAndCtrl_DW.x[DifAndCtrl_DW.b_ix];
          DifAndCtrl_DW.x[DifAndCtrl_DW.b_ix] = DifAndCtrl_DW.x[iy];
          DifAndCtrl_DW.x[iy] = DifAndCtrl_DW.smax;
          DifAndCtrl_DW.b_ix += 8;
          iy += 8;
        }
      }

      iy = (DifAndCtrl_DW.jj - i) + 8;
      for (DifAndCtrl_DW.d_k = DifAndCtrl_DW.jj + 2; DifAndCtrl_DW.d_k <= iy;
           DifAndCtrl_DW.d_k++) {
        DifAndCtrl_DW.x[DifAndCtrl_DW.d_k - 1] /=
          DifAndCtrl_DW.x[DifAndCtrl_DW.jj];
      }
    }

    DifAndCtrl_DW.b_ix = 6 - i;
    DifAndCtrl_DW.ix = DifAndCtrl_DW.jj + 10;
    for (DifAndCtrl_DW.d_k = 0; DifAndCtrl_DW.d_k <= DifAndCtrl_DW.b_ix;
         DifAndCtrl_DW.d_k++) {
      DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.x[((DifAndCtrl_DW.d_k << 3) +
        DifAndCtrl_DW.jj) + 8];
      if (DifAndCtrl_DW.D46_tmp_tmp_o != 0.0) {
        d = (DifAndCtrl_DW.ix - i) + 6;
        for (iy = DifAndCtrl_DW.ix; iy <= d; iy++) {
          DifAndCtrl_DW.x[iy - 1] += DifAndCtrl_DW.x[((DifAndCtrl_DW.jj + iy) -
            DifAndCtrl_DW.ix) + 1] * -DifAndCtrl_DW.D46_tmp_tmp_o;
        }
      }

      DifAndCtrl_DW.ix += 8;
    }
  }

  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    DifAndCtrl_DW.p[DifAndCtrl_DW.ix] = static_cast<int8_T>(DifAndCtrl_DW.ix + 1);
  }

  for (i = 0; i < 7; i++) {
    ipiv = DifAndCtrl_DW.ipiv[i];
    if (ipiv > i + 1) {
      DifAndCtrl_DW.jj = DifAndCtrl_DW.p[ipiv - 1];
      DifAndCtrl_DW.p[ipiv - 1] = DifAndCtrl_DW.p[i];
      DifAndCtrl_DW.p[i] = static_cast<int8_T>(DifAndCtrl_DW.jj);
    }
  }

  for (i = 0; i < 8; i++) {
    d = (DifAndCtrl_DW.p[i] - 1) << 3;
    DifAndCtrl_DW.BMinv[i + d] = 1.0;
    for (DifAndCtrl_DW.jj = i + 1; DifAndCtrl_DW.jj < 9; DifAndCtrl_DW.jj++) {
      DifAndCtrl_DW.ix = (d + DifAndCtrl_DW.jj) - 1;
      if (DifAndCtrl_DW.BMinv[DifAndCtrl_DW.ix] != 0.0) {
        for (DifAndCtrl_DW.d_k = DifAndCtrl_DW.jj + 1; DifAndCtrl_DW.d_k < 9;
             DifAndCtrl_DW.d_k++) {
          iy = (d + DifAndCtrl_DW.d_k) - 1;
          DifAndCtrl_DW.BMinv[iy] -= DifAndCtrl_DW.x[(((DifAndCtrl_DW.jj - 1) <<
            3) + DifAndCtrl_DW.d_k) - 1] * DifAndCtrl_DW.BMinv[DifAndCtrl_DW.ix];
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    iy = i << 3;
    for (DifAndCtrl_DW.jj = 7; DifAndCtrl_DW.jj >= 0; DifAndCtrl_DW.jj--) {
      DifAndCtrl_DW.b_ix = DifAndCtrl_DW.jj << 3;
      DifAndCtrl_DW.ix = DifAndCtrl_DW.jj + iy;
      DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.BMinv[DifAndCtrl_DW.ix];
      if (DifAndCtrl_DW.D46_tmp_tmp_o != 0.0) {
        DifAndCtrl_DW.BMinv[DifAndCtrl_DW.ix] = DifAndCtrl_DW.D46_tmp_tmp_o /
          DifAndCtrl_DW.x[DifAndCtrl_DW.jj + DifAndCtrl_DW.b_ix];
        for (DifAndCtrl_DW.d_k = 0; DifAndCtrl_DW.d_k < DifAndCtrl_DW.jj;
             DifAndCtrl_DW.d_k++) {
          d = DifAndCtrl_DW.d_k + iy;
          DifAndCtrl_DW.BMinv[d] -= DifAndCtrl_DW.x[DifAndCtrl_DW.d_k +
            DifAndCtrl_DW.b_ix] * DifAndCtrl_DW.BMinv[DifAndCtrl_DW.ix];
        }
      }
    }
  }

  // DigitalClock: '<S3>/Digital Clock'
  DifAndCtrl_DW.smax = ((&DifAndCtrl_M)->getClockTick0() * 0.01);

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  propChange = true;
  i = 0;
  exitg1 = false;
  while (!exitg1 && (i < 144)) {
    if (!(DifAndCtrl_DW.obj.Waypoints[i] == rtCP_PolynomialTrajectory_Waypo[i]))
    {
      propChange = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (!propChange) {
    if (DifAndCtrl_DW.obj.isInitialized == 1) {
      DifAndCtrl_DW.obj.TunablePropsChanged = true;
      DifAndCtrl_DW.obj.tunablePropertyChanged[0] = true;
    }

    memcpy(&DifAndCtrl_DW.obj.Waypoints[0], &rtCP_PolynomialTrajectory_Waypo[0],
           144U * sizeof(real_T));
  }

  propChange = true;
  i = 0;
  exitg1 = false;
  while (!exitg1 && (i < 18)) {
    if (!(DifAndCtrl_DW.obj.TimePoints[i] == rtCP_PolynomialTrajectory_TimeP[i]))
    {
      propChange = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (!propChange) {
    if (DifAndCtrl_DW.obj.isInitialized == 1) {
      DifAndCtrl_DW.obj.TunablePropsChanged = true;
      DifAndCtrl_DW.obj.tunablePropertyChanged[1] = true;
    }

    memcpy(&DifAndCtrl_DW.obj.TimePoints[0], &rtCP_PolynomialTrajectory_TimeP[0],
           18U * sizeof(real_T));
  }

  propChange = true;
  i = 0;
  exitg1 = false;
  while (!exitg1 && (i < 144)) {
    if (!(DifAndCtrl_DW.obj.VelocityBoundaryCondition[i] == 0.0)) {
      propChange = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (!propChange) {
    if (DifAndCtrl_DW.obj.isInitialized == 1) {
      DifAndCtrl_DW.obj.TunablePropsChanged = true;
      DifAndCtrl_DW.obj.tunablePropertyChanged[3] = true;
    }

    memset(&DifAndCtrl_DW.obj.VelocityBoundaryCondition[0], 0, 144U * sizeof
           (real_T));
  }

  if (DifAndCtrl_DW.obj.TunablePropsChanged) {
    DifAndCtrl_DW.obj.TunablePropsChanged = false;
    if (DifAndCtrl_DW.obj.tunablePropertyChanged[0] ||
        DifAndCtrl_DW.obj.tunablePropertyChanged[1] ||
        DifAndCtrl_DW.obj.tunablePropertyChanged[2]) {
      propChange = true;
    } else {
      propChange = false;
      if (DifAndCtrl_DW.obj.tunablePropertyChanged[3] ||
          DifAndCtrl_DW.obj.tunablePropertyChanged[4]) {
        propChange = true;
      }
    }

    DifAndCtrl_DW.obj.PPFormUpdatedNeeded = propChange;
    if (DifAndCtrl_DW.obj.PPFormUpdatedNeeded) {
      PolyTrajSys_regeneratePPFormFro(&DifAndCtrl_DW.obj,
        DifAndCtrl_DW.obj.Waypoints, DifAndCtrl_DW.obj.TimePoints);
    }

    for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 5; DifAndCtrl_DW.ix++) {
      DifAndCtrl_DW.obj.tunablePropertyChanged[DifAndCtrl_DW.ix] = false;
    }
  }

  DifAndCtrl_DW.D14_tmp = DifAndCtrl_DW.smax;
  DifAndCtrl_DW.D14_tmp_c = DifAndCtrl_DW.obj.PPStruct.breaks[18];
  if (DifAndCtrl_DW.smax == DifAndCtrl_DW.obj.PPStruct.breaks[18]) {
    for (i = 0; i < 1; i++) {
      DifAndCtrl_DW.D14_tmp = DifAndCtrl_DW.D14_tmp_c - 2.220446049250313E-15;
    }
  }

  DifAndCtrl_ppval(DifAndCtrl_DW.obj.PPDDStruct.breaks,
                   DifAndCtrl_DW.obj.PPDDStruct.coefs, DifAndCtrl_DW.D14_tmp,
                   DifAndCtrl_DW.e_hat);
  DifAndCtrl_ppval(DifAndCtrl_DW.obj.PPStruct.breaks,
                   DifAndCtrl_DW.obj.PPStruct.coefs, DifAndCtrl_DW.smax,
                   DifAndCtrl_DW.rtb_Sum3_tmp);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kp'

  DifAndCtrl_DW.x[0] = 0.5;
  DifAndCtrl_DW.x[8] = 0.0;
  DifAndCtrl_DW.x[16] = 0.0;
  DifAndCtrl_DW.x[24] = 0.0;
  DifAndCtrl_DW.x[32] = 0.0;
  DifAndCtrl_DW.x[40] = 0.0;
  DifAndCtrl_DW.x[48] = 0.0;
  DifAndCtrl_DW.x[56] = 0.0;
  DifAndCtrl_DW.x[1] = 0.0;
  DifAndCtrl_DW.x[9] = 0.5;
  DifAndCtrl_DW.x[17] = 0.0;
  DifAndCtrl_DW.x[25] = 0.0;
  DifAndCtrl_DW.x[33] = 0.0;
  DifAndCtrl_DW.x[41] = 0.0;
  DifAndCtrl_DW.x[49] = 0.0;
  DifAndCtrl_DW.x[57] = 0.0;
  DifAndCtrl_DW.x[2] = 0.0;
  DifAndCtrl_DW.x[10] = 0.0;
  DifAndCtrl_DW.x[18] = 1.0;
  DifAndCtrl_DW.x[26] = 0.0;
  DifAndCtrl_DW.x[34] = 0.0;
  DifAndCtrl_DW.x[42] = 0.0;
  DifAndCtrl_DW.x[50] = 0.0;
  DifAndCtrl_DW.x[58] = 0.0;
  DifAndCtrl_DW.x[3] = 0.0;
  DifAndCtrl_DW.x[11] = 0.0;
  DifAndCtrl_DW.x[19] = 0.0;
  DifAndCtrl_DW.x[27] = 2.0;
  DifAndCtrl_DW.x[35] = 0.0;
  DifAndCtrl_DW.x[43] = 0.0;
  DifAndCtrl_DW.x[51] = 0.0;
  DifAndCtrl_DW.x[59] = 0.0;
  DifAndCtrl_DW.x[4] = 0.0;
  DifAndCtrl_DW.x[12] = 0.0;
  DifAndCtrl_DW.x[20] = 0.0;
  DifAndCtrl_DW.x[28] = 0.0;
  DifAndCtrl_DW.x[36] = 2.0;
  DifAndCtrl_DW.x[44] = 0.0;
  DifAndCtrl_DW.x[52] = 0.0;
  DifAndCtrl_DW.x[60] = 0.0;
  DifAndCtrl_DW.x[5] = 0.0;
  DifAndCtrl_DW.x[13] = 0.0;
  DifAndCtrl_DW.x[21] = 0.0;
  DifAndCtrl_DW.x[29] = 0.0;
  DifAndCtrl_DW.x[37] = 0.0;
  DifAndCtrl_DW.x[45] = 2.0;
  DifAndCtrl_DW.x[53] = 0.0;
  DifAndCtrl_DW.x[61] = 0.0;
  DifAndCtrl_DW.x[6] = 0.0;
  DifAndCtrl_DW.x[14] = 0.0;
  DifAndCtrl_DW.x[22] = 0.0;
  DifAndCtrl_DW.x[30] = 0.0;
  DifAndCtrl_DW.x[38] = 0.0;
  DifAndCtrl_DW.x[46] = 0.0;
  DifAndCtrl_DW.x[54] = 40.0;
  DifAndCtrl_DW.x[62] = 0.0;
  DifAndCtrl_DW.x[7] = 0.0;
  DifAndCtrl_DW.x[15] = 0.0;
  DifAndCtrl_DW.x[23] = 0.0;
  DifAndCtrl_DW.x[31] = 0.0;
  DifAndCtrl_DW.x[39] = 0.0;
  DifAndCtrl_DW.x[47] = 0.0;
  DifAndCtrl_DW.x[55] = 0.0;
  DifAndCtrl_DW.x[63] = 70.0;

  // MATLABSystem: '<S3>/Polynomial Trajectory'
  DifAndCtrl_ppval(DifAndCtrl_DW.obj.PPDStruct.breaks,
                   DifAndCtrl_DW.obj.PPDStruct.coefs, DifAndCtrl_DW.D14_tmp,
                   DifAndCtrl_DW.dv1);

  // MATLAB Function: '<S11>/PD Controller' incorporates:
  //   Constant: '<S11>/Kd'

  DifAndCtrl_DW.dv[0] = 0.5;
  DifAndCtrl_DW.dv[8] = 0.0;
  DifAndCtrl_DW.dv[16] = 0.0;
  DifAndCtrl_DW.dv[24] = 0.0;
  DifAndCtrl_DW.dv[32] = 0.0;
  DifAndCtrl_DW.dv[40] = 0.0;
  DifAndCtrl_DW.dv[48] = 0.0;
  DifAndCtrl_DW.dv[56] = 0.0;
  DifAndCtrl_DW.dv[1] = 0.0;
  DifAndCtrl_DW.dv[9] = 0.5;
  DifAndCtrl_DW.dv[17] = 0.0;
  DifAndCtrl_DW.dv[25] = 0.0;
  DifAndCtrl_DW.dv[33] = 0.0;
  DifAndCtrl_DW.dv[41] = 0.0;
  DifAndCtrl_DW.dv[49] = 0.0;
  DifAndCtrl_DW.dv[57] = 0.0;
  DifAndCtrl_DW.dv[2] = 0.0;
  DifAndCtrl_DW.dv[10] = 0.0;
  DifAndCtrl_DW.dv[18] = 1.0;
  DifAndCtrl_DW.dv[26] = 0.0;
  DifAndCtrl_DW.dv[34] = 0.0;
  DifAndCtrl_DW.dv[42] = 0.0;
  DifAndCtrl_DW.dv[50] = 0.0;
  DifAndCtrl_DW.dv[58] = 0.0;
  DifAndCtrl_DW.dv[3] = 0.0;
  DifAndCtrl_DW.dv[11] = 0.0;
  DifAndCtrl_DW.dv[19] = 0.0;
  DifAndCtrl_DW.dv[27] = 2.0;
  DifAndCtrl_DW.dv[35] = 0.0;
  DifAndCtrl_DW.dv[43] = 0.0;
  DifAndCtrl_DW.dv[51] = 0.0;
  DifAndCtrl_DW.dv[59] = 0.0;
  DifAndCtrl_DW.dv[4] = 0.0;
  DifAndCtrl_DW.dv[12] = 0.0;
  DifAndCtrl_DW.dv[20] = 0.0;
  DifAndCtrl_DW.dv[28] = 0.0;
  DifAndCtrl_DW.dv[36] = 2.0;
  DifAndCtrl_DW.dv[44] = 0.0;
  DifAndCtrl_DW.dv[52] = 0.0;
  DifAndCtrl_DW.dv[60] = 0.0;
  DifAndCtrl_DW.dv[5] = 0.0;
  DifAndCtrl_DW.dv[13] = 0.0;
  DifAndCtrl_DW.dv[21] = 0.0;
  DifAndCtrl_DW.dv[29] = 0.0;
  DifAndCtrl_DW.dv[37] = 0.0;
  DifAndCtrl_DW.dv[45] = 2.0;
  DifAndCtrl_DW.dv[53] = 0.0;
  DifAndCtrl_DW.dv[61] = 0.0;
  DifAndCtrl_DW.dv[6] = 0.0;
  DifAndCtrl_DW.dv[14] = 0.0;
  DifAndCtrl_DW.dv[22] = 0.0;
  DifAndCtrl_DW.dv[30] = 0.0;
  DifAndCtrl_DW.dv[38] = 0.0;
  DifAndCtrl_DW.dv[46] = 0.0;
  DifAndCtrl_DW.dv[54] = 40.0;
  DifAndCtrl_DW.dv[62] = 0.0;
  DifAndCtrl_DW.dv[7] = 0.0;
  DifAndCtrl_DW.dv[15] = 0.0;
  DifAndCtrl_DW.dv[23] = 0.0;
  DifAndCtrl_DW.dv[31] = 0.0;
  DifAndCtrl_DW.dv[39] = 0.0;
  DifAndCtrl_DW.dv[47] = 0.0;
  DifAndCtrl_DW.dv[55] = 0.0;
  DifAndCtrl_DW.dv[63] = 70.0;
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    // Sum: '<S13>/Minus' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator2'

    DifAndCtrl_DW.uv[DifAndCtrl_DW.ix] =
      DifAndCtrl_DW.rtb_Sum3_tmp[DifAndCtrl_DW.ix] -
      DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[DifAndCtrl_DW.ix];

    // Sum: '<S13>/Minus1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    DifAndCtrl_DW.dv2[DifAndCtrl_DW.ix] = DifAndCtrl_DW.dv1[DifAndCtrl_DW.ix] -
      DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[DifAndCtrl_DW.ix];

    // MATLAB Function: '<S11>/PD Controller'
    DifAndCtrl_DW.Sum3[DifAndCtrl_DW.ix] = 0.0;
  }

  // MATLAB Function: '<S11>/PD Controller'
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.uv[DifAndCtrl_DW.ix];
    for (i = 0; i < 8; i++) {
      DifAndCtrl_DW.Sum3[i] += DifAndCtrl_DW.x[(DifAndCtrl_DW.ix << 3) + i] *
        DifAndCtrl_DW.D46_tmp_tmp_o;
    }
  }

  memset(&DifAndCtrl_DW.rtb_Sum3_tmp[0], 0, sizeof(real_T) << 3U);
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.dv2[DifAndCtrl_DW.ix];
    for (i = 0; i < 8; i++) {
      DifAndCtrl_DW.rtb_Sum3_tmp[i] += DifAndCtrl_DW.dv[(DifAndCtrl_DW.ix << 3)
        + i] * DifAndCtrl_DW.D46_tmp_tmp_o;
    }
  }

  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    // Sum: '<S11>/Add1' incorporates:
    //   MATLAB Function: '<S11>/PD Controller'
    //   Sum: '<S11>/Sum'

    DifAndCtrl_DW.uv[DifAndCtrl_DW.ix] = ((DifAndCtrl_DW.Sum3[DifAndCtrl_DW.ix]
      + DifAndCtrl_DW.rtb_Sum3_tmp[DifAndCtrl_DW.ix]) +
      DifAndCtrl_DW.e_hat[DifAndCtrl_DW.ix]) - DifAndCtrl_DW.fx[DifAndCtrl_DW.ix];

    // Product: '<S11>/Matrix Multiply'
    DifAndCtrl_DW.fx[DifAndCtrl_DW.ix] = 0.0;
  }

  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    // Product: '<S11>/Matrix Multiply'
    DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.uv[DifAndCtrl_DW.ix];
    for (i = 0; i < 8; i++) {
      DifAndCtrl_DW.fx[i] += DifAndCtrl_DW.ginv[(DifAndCtrl_DW.ix << 3) + i] *
        DifAndCtrl_DW.D46_tmp_tmp_o;
    }

    // Product: '<S2>/Matrix Multiply'
    arg_ForcesAndTorques[DifAndCtrl_DW.ix] = 0.0;
  }

  for (i = 0; i < 8; i++) {
    // Product: '<S2>/Matrix Multiply'
    DifAndCtrl_DW.D46_tmp_tmp_o = DifAndCtrl_DW.fx[i];
    for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
      arg_ForcesAndTorques[DifAndCtrl_DW.ix] += DifAndCtrl_DW.BMinv[(i << 3) +
        DifAndCtrl_DW.ix] * DifAndCtrl_DW.D46_tmp_tmp_o;
    }

    // Sum: '<S4>/Sum1' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator2'

    DifAndCtrl_DW.e_hat[i] = arg_Position[i] -
      DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[i];
  }

  // MATLAB Function: '<S4>/U power x2' incorporates:
  //   Constant: '<S4>/Q3'

  DifAndCtrl_Upowerx1(DifAndCtrl_DW.e_hat, rtCP_Q3_Value, DifAndCtrl_DW.fx);

  // MATLAB Function: '<S4>/U power x1' incorporates:
  //   Constant: '<S4>/Q5'

  DifAndCtrl_Upowerx1(DifAndCtrl_DW.e_hat, rtCP_Q5_Value, DifAndCtrl_DW.uv);
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    // Signum: '<S4>/Sign' incorporates:
    //   Sum: '<S4>/Sum1'

    DifAndCtrl_DW.smax = DifAndCtrl_DW.e_hat[DifAndCtrl_DW.ix];
    if (rtIsNaN(DifAndCtrl_DW.smax)) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      DifAndCtrl_DW.smax = (rtNaN);
    } else if (DifAndCtrl_DW.smax < 0.0) {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      DifAndCtrl_DW.smax = -1.0;
    } else {
      // Signum: '<S4>/Sign1' incorporates:
      //   Signum: '<S4>/Sign2'
      //   Signum: '<S4>/Sign3'

      DifAndCtrl_DW.smax = (DifAndCtrl_DW.smax > 0.0);
    }

    DifAndCtrl_DW.rtb_Sum3_tmp[DifAndCtrl_DW.ix] = DifAndCtrl_DW.smax;

    // Sum: '<S4>/Sum3' incorporates:
    //   Constant: '<S4>/G1'
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
    //   Product: '<S4>/Product3'
    //   Product: '<S4>/Product4'
    //   Signum: '<S4>/Sign'
    //   Signum: '<S4>/Sign1'

    DifAndCtrl_DW.Sum3[DifAndCtrl_DW.ix] = (rtCP_G1_Value[DifAndCtrl_DW.ix] *
      DifAndCtrl_DW.smax * DifAndCtrl_DW.fx[DifAndCtrl_DW.ix] +
      DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[DifAndCtrl_DW.ix]) + 16.0 *
      DifAndCtrl_DW.smax * DifAndCtrl_DW.uv[DifAndCtrl_DW.ix];
  }

  // MATLAB Function: '<S4>/U power x3' incorporates:
  //   Constant: '<S4>/Q4'

  DifAndCtrl_Upowerx1(DifAndCtrl_DW.e_hat, rtCP_Q4_Value, DifAndCtrl_DW.uv);

  // MATLAB Function: '<S4>/U power x4' incorporates:
  //   Constant: '<S4>/Q6'

  DifAndCtrl_Upowerx1(DifAndCtrl_DW.e_hat, rtCP_Q6_Value, DifAndCtrl_DW.fx);
  for (DifAndCtrl_DW.ix = 0; DifAndCtrl_DW.ix < 8; DifAndCtrl_DW.ix++) {
    // Signum: '<S4>/Sign2' incorporates:
    //   DiscreteIntegrator: '<S4>/Discrete-Time Integrator'

    DifAndCtrl_DW.smax = DifAndCtrl_DW.rtb_Sum3_tmp[DifAndCtrl_DW.ix];

    // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
    //   Constant: '<S4>/G2'
    //   Constant: '<S4>/Q2'
    //   Product: '<S4>/Product5'
    //   Product: '<S4>/Product6'
    //   Signum: '<S4>/Sign2'
    //   Signum: '<S4>/Sign3'
    //   Sum: '<S4>/Sum4'

    DifAndCtrl_DW.DiscreteTimeIntegrator_DSTATE[DifAndCtrl_DW.ix] +=
      (rtCP_G2_Value[DifAndCtrl_DW.ix] * DifAndCtrl_DW.smax *
       DifAndCtrl_DW.uv[DifAndCtrl_DW.ix] + rtCP_Q2_Value[DifAndCtrl_DW.ix] *
       DifAndCtrl_DW.smax * DifAndCtrl_DW.fx[DifAndCtrl_DW.ix]) * 0.01;

    // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' incorporates:
    //   Sum: '<S4>/Sum3'

    DifAndCtrl_DW.DiscreteTimeIntegrator2_DSTATE[DifAndCtrl_DW.ix] += 0.01 *
      DifAndCtrl_DW.Sum3[DifAndCtrl_DW.ix];
  }
}

// Model initialize function
void DifAndCtrl::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

time_T DifAndCtrl::RT_MODEL_DifAndCtrl_T::getClockTickH0() const
{
  return static_cast<time_T>( *(timingBridge->
    clockTickH[Timing.mdlref_GlobalTID[0]]) );
}

time_T DifAndCtrl::RT_MODEL_DifAndCtrl_T::getClockTick0() const
{
  return static_cast<time_T>( *((timingBridge->
    clockTick[Timing.mdlref_GlobalTID[0]])) );
}

boolean_T DifAndCtrl::RT_MODEL_DifAndCtrl_T::isSampleHit(int32_T sti) const
{
  return (timingBridge->taskCounter[Timing.mdlref_GlobalTID[sti]] == 0);
}

time_T DifAndCtrl::RT_MODEL_DifAndCtrl_T::getT() const
{
  return (*(timingBridge->taskTime[0]));
}

// Constructor
DifAndCtrl::DifAndCtrl() :
  DifAndCtrl_DW(),
  DifAndCtrl_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
DifAndCtrl::~DifAndCtrl()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
DifAndCtrl::RT_MODEL_DifAndCtrl_T * DifAndCtrl::getRTM()
{
  return (&DifAndCtrl_M);
}

// member function to initialize Real-Time model
void DifAndCtrl::initializeRTM(const rtTimingBridge *timingBridge, int_T
  mdlref_TID0)
{
  setupGlobalTimingEngine(timingBridge, mdlref_TID0);
}

// Private member function to set up the global timing engine
void DifAndCtrl::setupGlobalTimingEngine(const rtTimingBridge *timingBridge,
  int_T mdlref_TID0)
{
  (&DifAndCtrl_M)->Timing.mdlref_GlobalTID[0] = mdlref_TID0;
  (&DifAndCtrl_M)->timingBridge = timingBridge;
}

//
// File trailer for generated code.
//
// [EOF]
//
