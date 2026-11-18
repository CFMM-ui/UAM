//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: UAM_Hexa_PD_Obs_QGround.h
//
// Code generated for Simulink model 'UAM_Hexa_PD_Obs_QGround'.
//
// Model version                  : 1.113
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Sun Nov  8 18:50:33 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef UAM_HEXA_PD_OBS_QGROUND_H_
#define UAM_HEXA_PD_OBS_QGROUND_H_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "nesl_rtw.h"
#include "UAM_Hexa_PD_Obs_QGround_b715a46b_1_gateway.h"
#include "UAM_Hexa_PD_Obs_QGround_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include <string.h>
#include <stddef.h>

// Macros for accessing real-time model data structure
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

// Block signals (default storage)
struct B_UAM_Hexa_PD_Obs_QGround_T {
  real_T coefsWithFlatStart[128];
  real_T dv[113];
  real_T dv1[96];
  real_T coefMat[96];
  real_T dv2[96];
  real_T dv3[96];
  real_T dv4[96];
  real_T dv5[96];
  real_T x[64];
  real_T b_x[64];
  real_T b_A[64];
  real32_T rtb_TmpSignalConversionAtSFun_m[64];
  real32_T rtb_TmpSignalConversionAtSFun_c[64];
  real_T coeffMat[32];
  int_T iv[26];
  int_T iv1[25];
  int_T iv2[25];
  int_T iv3[25];
  int_T iv4[25];
  int_T iv5[25];
  real_T VectorConcatenate[9];
  real_T VectorConcatenate_k[9];
  real_T FMTq[8];                      // '<S10>/Matrix Multiply1'
  real_T Product5[8];                  // '<S169>/Product5'
  real_T gamma_hat_2[8];
  real_T gamma_hat_1[8];
  real_T gamma_hat_3[8];
  real_T dv6[8];
  NeModelParameters modelParameters;
  NeModelParameters modelParameters_c;
  real_T dv7[6];
  real_T breaksWithFlatStart[5];
  real_T INPUT_14_1_1[4];              // '<S302>/INPUT_14_1_1'
  real_T b_coeffVec[4];
  real32_T rtb_TmpSignalConversionAtSFun_p[8];
  real32_T rtb_TmpSignalConversionAtSFu_cv[8];
  real32_T fv[8];
  int32_T ipiv[8];
  int32_T ipiv_b[8];
  real_T UJoints[2];                   // '<S1>/Torque Saturation1'
  real_T INPUT_1_1_1[4];               // '<S302>/INPUT_1_1_1'
  real_T INPUT_2_1_1[4];               // '<S302>/INPUT_2_1_1'
  real_T w2[6];                        // '<S6>/Rotation Saturation1'
  real_T Fthrust[6];                   // '<S169>/Saturation1'
  real_T INPUT_8_1_1[4];               // '<S302>/INPUT_8_1_1'
  real_T INPUT_3_1_1[4];               // '<S302>/INPUT_3_1_1'
  real_T INPUT_4_1_1[4];               // '<S302>/INPUT_4_1_1'
  real_T INPUT_5_1_1[4];               // '<S302>/INPUT_5_1_1'
  real_T INPUT_6_1_1[4];               // '<S302>/INPUT_6_1_1'
  real_T INPUT_7_1_1[4];               // '<S302>/INPUT_7_1_1'
  real_T OUTPUT_1_0[17];               // '<S302>/OUTPUT_1_0'
  real_T Velocities[8];
  // '<S3>/TmpSignal ConversionAtTAQSigLogging_InsertedFor_Mux1_at_outport_0Inport1' 
  real_T Merge[3];                     // '<S190>/Merge'
  real_T Positions[8];
  // '<S3>/TmpSignal ConversionAtTAQSigLogging_InsertedFor_Mux_at_outport_0Inport1' 
  real_T DataTypeConversion1[8];       // '<S7>/Data Type Conversion1'
  real_T DataTypeConversion[8];        // '<S7>/Data Type Conversion'
  real_T Sum13[8];                     // '<S7>/Sum13'
  real_T Gain4[8];                     // '<S7>/Gain4'
  real_T Gain3[8];                     // '<S7>/Gain3'
  real_T Sum7[8];                      // '<S7>/Sum7'
  real_T Gain6[8];                     // '<S7>/Gain6'
  real_T u_d[8];                       // '<S7>/Matrix Multiply'
  real_T Gain5[8];                     // '<S7>/Gain5'
  real_T Sum11[8];                     // '<S7>/Sum11'
  boolean_T Compare[9];                // '<S216>/Compare'
  int8_T p[8];
  int8_T ipiv_f[8];
  int8_T p_g[8];
  real_T SM1;                          // '<S169>/Integrator7'
  real_T INPUT_10_1_1[4];              // '<S302>/INPUT_10_1_1'
  real_T SM2;                          // '<S169>/Integrator9'
  real_T INPUT_11_1_1[4];              // '<S302>/INPUT_11_1_1'
  real_T SM3;                          // '<S169>/Integrator10'
  real_T INPUT_12_1_1[4];              // '<S302>/INPUT_12_1_1'
  real_T SM4;                          // '<S169>/Integrator11'
  real_T INPUT_13_1_1[4];              // '<S302>/INPUT_13_1_1'
  real_T SM5;                          // '<S169>/Integrator12'
  real_T SM6;                          // '<S169>/Integrator13'
  real_T INPUT_9_1_1[4];               // '<S302>/INPUT_9_1_1'
  real_T STATE_1[17];                  // '<S302>/STATE_1'
  real_T INPUT_16_1_1[4];              // '<S302>/INPUT_16_1_1'
  real_T INPUT_15_1_1[4];              // '<S302>/INPUT_15_1_1'
  real_T INPUT_15_1_2[4];              // '<S302>/INPUT_15_1_2'
  real_T INPUT_15_1_3[4];              // '<S302>/INPUT_15_1_3'
  real_T INPUT_15_1_4[4];              // '<S302>/INPUT_15_1_4'
  real_T INPUT_15_1_5[4];              // '<S302>/INPUT_15_1_5'
  real_T INPUT_15_1_6[4];              // '<S302>/INPUT_15_1_6'
  real_T INPUT_15_1_7[4];              // '<S302>/INPUT_15_1_7'
  real_T INPUT_15_1_8[4];              // '<S302>/INPUT_15_1_8'
  real_T INPUT_15_1_9[4];              // '<S302>/INPUT_15_1_9'
  real_T error_q[8];                   // '<S11>/Minus'
  real_T error_dq[8];                  // '<S11>/Minus1'
  real_T u[8];                         // '<S1>/Matrix Multiply'
  real_T SquareRoot6;                  // '<S169>/Square Root6'
  real_T SquareRoot1;                  // '<S169>/Square Root1'
  real_T SquareRoot2;                  // '<S169>/Square Root2'
  real_T SquareRoot3;                  // '<S169>/Square Root3'
  real_T SquareRoot4;                  // '<S169>/Square Root4'
  real_T SquareRoot5;                  // '<S169>/Square Root5'
  real_T TmpSignalConversionAtTAQSigLogg[6];
  // '<S169>/TmpSignal ConversionAtTAQSigLogging_InsertedFor_Mux_at_outport_0Inport1' 
  real_T Gain6_o;                      // '<S169>/Gain6'
  real_T Gain4_j;                      // '<S169>/Gain4'
  real_T Gain3_j;                      // '<S169>/Gain3'
  real_T qd[8];                        // '<S5>/Polynomial Trajectory'
  real_T dqd[8];                       // '<S5>/Polynomial Trajectory'
  real_T ddqd[8];                      // '<S5>/Polynomial Trajectory'
  real_T m;                            // '<S4>/MATLAB Function'
  real_T I[9];                         // '<S4>/MATLAB Function'
  real_T BMinv[64];                    // '<S10>/GetBInvMatrix'
  real_T ginv[64];                     // '<S1>/MATLAB Function1'
  real_T g[64];                        // '<S1>/MATLAB Function1'
  real_T fx[8];                        // '<S1>/MATLAB Function1'
  real_T Merge_f;                      // '<S196>/Merge'
  real_T Merge_n;                      // '<S200>/Merge'
  real_T time;
  real_T time_g;
  real_T time_m;
  real_T time_n;
  real_T D26;
  real_T D27;
  real_T D28;
  real_T D34;
  real_T D35;
  real_T D37;
  real_T D38;
  real_T D45;
  real_T D46;
  real_T D47;
  real_T D48;
  real_T D56;
  real_T D57;
  real_T D58;
  real_T D67;
  real_T D68;
  real_T D78;
  real_T b_a;
  real_T c_a;
  real_T d_a;
  real_T e_a;
  real_T f_a;
  real_T g_a;
  real_T h_a;
  real_T i_a;
  real_T j_a;
  real_T k_a;
  real_T l_a;
  real_T m_a;
  real_T n_a;
  real_T o_a;
  real_T p_a;
  real_T q_a;
  real_T r_a;
  real_T s_a;
  real_T t_a;
  real_T u_a;
  real_T v_a;
  real_T w_a;
  real_T x_a;
  real_T y_a;
  real_T ab_a;
  real_T smax;
  real_T s;
  real_T DigitalClock;                 // '<S4>/Digital Clock'
  real_T Product_g;                    // '<S229>/Product'
  real_T rtb_VectorConcatenate_idx_2;
  real_T rtb_VectorConcatenate_idx_5;
  real_T rtb_VectorConcatenate_idx_6;
  real_T finalTime;
  real_T waypoints_idx_0;
  real_T waypoints_idx_1;
  real_T coefMat_tmp;
  real_T d;
  real_T d1;
  real_T d2;
  real_T smax_p;
  real_T s_l;
  real_T temp;
  real_T fixedStepSize;
  real_T xloc;
  real32_T ReadParameter_o1;           // '<S112>/ReadParameter'
  real32_T ReadParameter_o1_a;         // '<S111>/ReadParameter'
  real32_T ReadParameter_o1_g;         // '<S110>/ReadParameter'
  real32_T ReadParameter_o1_n;         // '<S109>/ReadParameter'
  real32_T ReadParameter_o1_e;         // '<S108>/ReadParameter'
  real32_T ReadParameter_o1_l;         // '<S107>/ReadParameter'
  real32_T ReadParameter_o1_ao;        // '<S106>/ReadParameter'
  real32_T ReadParameter_o1_ez;        // '<S102>/ReadParameter'
  real32_T ReadParameter_o1_k;         // '<S101>/ReadParameter'
  real32_T ReadParameter_o1_ab;        // '<S100>/ReadParameter'
  real32_T ReadParameter_o1_i;         // '<S99>/ReadParameter'
  real32_T ReadParameter_o1_d;         // '<S98>/ReadParameter'
  real32_T ReadParameter_o1_f;         // '<S97>/ReadParameter'
  real32_T ReadParameter_o1_j;         // '<S96>/ReadParameter'
  real32_T ReadParameter_o1_c;         // '<S92>/ReadParameter'
  real32_T ReadParameter_o1_h;         // '<S91>/ReadParameter'
  real32_T ReadParameter_o1_b;         // '<S90>/ReadParameter'
  real32_T ReadParameter_o1_fx;        // '<S89>/ReadParameter'
  real32_T ReadParameter_o1_hs;        // '<S88>/ReadParameter'
  real32_T ReadParameter_o1_it;        // '<S87>/ReadParameter'
  real32_T ReadParameter_o1_go;        // '<S86>/ReadParameter'
  real32_T ReadParameter_o1_p;         // '<S83>/ReadParameter'
  real32_T ReadParameter_o1_a5;        // '<S81>/ReadParameter'
  real32_T ReadParameter_o1_jo;        // '<S80>/ReadParameter'
  real32_T ReadParameter_o1_cl;        // '<S79>/ReadParameter'
  real32_T ReadParameter_o1_d3;        // '<S78>/ReadParameter'
  real32_T ReadParameter_o1_jb;        // '<S77>/ReadParameter'
  real32_T ReadParameter_o1_kx;        // '<S76>/ReadParameter'
  real32_T ReadParameter_o1_e1;        // '<S73>/ReadParameter'
  real32_T ReadParameter_o1_jf;        // '<S72>/ReadParameter'
  real32_T ReadParameter_o1_ac;        // '<S70>/ReadParameter'
  real32_T ReadParameter_o1_gw;        // '<S69>/ReadParameter'
  real32_T ReadParameter_o1_cu;        // '<S68>/ReadParameter'
  real32_T ReadParameter_o1_ba;        // '<S67>/ReadParameter'
  real32_T ReadParameter_o1_m;         // '<S66>/ReadParameter'
  real32_T ReadParameter_o1_nl;        // '<S63>/ReadParameter'
  real32_T ReadParameter_o1_ks;        // '<S62>/ReadParameter'
  real32_T ReadParameter_o1_nt;        // '<S61>/ReadParameter'
  real32_T ReadParameter_o1_nw;        // '<S59>/ReadParameter'
  real32_T ReadParameter_o1_ga;        // '<S58>/ReadParameter'
  real32_T ReadParameter_o1_al;        // '<S57>/ReadParameter'
  real32_T ReadParameter_o1_ea;        // '<S56>/ReadParameter'
  real32_T ReadParameter_o1_pv;        // '<S53>/ReadParameter'
  real32_T ReadParameter_o1_kw;        // '<S52>/ReadParameter'
  real32_T ReadParameter_o1_c5;        // '<S51>/ReadParameter'
  real32_T ReadParameter_o1_ml;        // '<S50>/ReadParameter'
  real32_T ReadParameter_o1_b5;        // '<S49>/ReadParameter'
  real32_T ReadParameter_o1_dv;        // '<S48>/ReadParameter'
  real32_T ReadParameter_o1_lb;        // '<S47>/ReadParameter'
  real32_T ReadParameter_o1_o;         // '<S44>/ReadParameter'
  real32_T ReadParameter_o1_h4;        // '<S43>/ReadParameter'
  real32_T ReadParameter_o1_ew;        // '<S42>/ReadParameter'
  real32_T ReadParameter_o1_bz;        // '<S41>/ReadParameter'
  real32_T ReadParameter_o1_mc;        // '<S40>/ReadParameter'
  real32_T ReadParameter_o1_jw;        // '<S39>/ReadParameter'
  real32_T ReadParameter_o1_ih;        // '<S16>/ReadParameter'
  real32_T u_aux[8];                   // '<S9>/PD Controller'
  real32_T ParamStep;
  real32_T ParamStep_j;
  real32_T ParamStep_d;
  real32_T ParamStep_g;
  real32_T ParamStep_l;
  real32_T ParamStep_dh;
  real32_T ParamStep_dy;
  real32_T ParamStep_lx;
  int32_T kAcol;
  int32_T jj;
  int32_T a;
  int32_T n;
  int32_T jA;
  int32_T ParamStep_o;
  int32_T i;
  int32_T i_b;
  int32_T info;
  int32_T pipk;
  int32_T jBcol;
  int32_T kAcol_n;
  int32_T b_i;
  int32_T ipiv_bs;
  int32_T jj_l;
  int32_T j;
  int32_T a_h;
  int32_T n_b;
  int32_T info_d;
  int32_T kAcol_e;
  int32_T ipiv_bj;
  int32_T i_j;
  int32_T b_i_f;
  int32_T b_j;
  int32_T low_i;
};

// Block states (default storage) for system '<Root>'
struct DW_UAM_Hexa_PD_Obs_QGround_T {
  robotics_slcore_internal_bloc_T obj; // '<S5>/Polynomial Trajectory'
  px4_internal_block_ParameterU_T obj_b;// '<S114>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bz;// '<S113>/ReadParameter'
  px4_internal_block_ParameterU_T obj_g;// '<S112>/ReadParameter'
  px4_internal_block_ParameterU_T obj_c;// '<S111>/ReadParameter'
  px4_internal_block_ParameterU_T obj_o;// '<S110>/ReadParameter'
  px4_internal_block_ParameterU_T obj_i;// '<S109>/ReadParameter'
  px4_internal_block_ParameterU_T obj_n;// '<S108>/ReadParameter'
  px4_internal_block_ParameterU_T obj_p;// '<S107>/ReadParameter'
  px4_internal_block_ParameterU_T obj_ot;// '<S106>/ReadParameter'
  px4_internal_block_ParameterU_T obj_k;// '<S105>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bl;// '<S104>/ReadParameter'
  px4_internal_block_ParameterU_T obj_gz;// '<S103>/ReadParameter'
  px4_internal_block_ParameterU_T obj_a;// '<S102>/ReadParameter'
  px4_internal_block_ParameterU_T obj_a4;// '<S101>/ReadParameter'
  px4_internal_block_ParameterU_T obj_pp;// '<S100>/ReadParameter'
  px4_internal_block_ParameterU_T obj_h;// '<S99>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cj;// '<S98>/ReadParameter'
  px4_internal_block_ParameterU_T obj_l;// '<S97>/ReadParameter'
  px4_internal_block_ParameterU_T obj_of;// '<S96>/ReadParameter'
  px4_internal_block_ParameterU_T obj_j;// '<S95>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bs;// '<S94>/ReadParameter'
  px4_internal_block_ParameterU_T obj_i5;// '<S93>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cv;// '<S92>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bb;// '<S91>/ReadParameter'
  px4_internal_block_ParameterU_T obj_k3;// '<S90>/ReadParameter'
  px4_internal_block_ParameterU_T obj_o0;// '<S89>/ReadParameter'
  px4_internal_block_ParameterU_T obj_on;// '<S88>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bj;// '<S87>/ReadParameter'
  px4_internal_block_ParameterU_T obj_e;// '<S86>/ReadParameter'
  px4_internal_block_ParameterU_T obj_o4;// '<S85>/ReadParameter'
  px4_internal_block_ParameterU_T obj_c4;// '<S84>/ReadParameter'
  px4_internal_block_ParameterU_T obj_c2;// '<S83>/ReadParameter'
  px4_internal_block_ParameterU_T obj_ov;// '<S82>/ReadParameter'
  px4_internal_block_ParameterU_T obj_gv;// '<S81>/ReadParameter'
  px4_internal_block_ParameterU_T obj_li;// '<S80>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cl;// '<S79>/ReadParameter'
  px4_internal_block_ParameterU_T obj_m;// '<S78>/ReadParameter'
  px4_internal_block_ParameterU_T obj_ai;// '<S77>/ReadParameter'
  px4_internal_block_ParameterU_T obj_j0;// '<S76>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cp;// '<S75>/ReadParameter'
  px4_internal_block_ParameterU_T obj_lm;// '<S74>/ReadParameter'
  px4_internal_block_ParameterU_T obj_by;// '<S73>/ReadParameter'
  px4_internal_block_ParameterU_T obj_hj;// '<S72>/ReadParameter'
  px4_internal_block_ParameterU_T obj_hy;// '<S71>/ReadParameter'
  px4_internal_block_ParameterU_T obj_e0;// '<S70>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bd;// '<S69>/ReadParameter'
  px4_internal_block_ParameterU_T obj_e1;// '<S68>/ReadParameter'
  px4_internal_block_ParameterU_T obj_hd;// '<S67>/ReadParameter'
  px4_internal_block_ParameterU_T obj_mk;// '<S66>/ReadParameter'
  px4_internal_block_ParameterU_T obj_m0;// '<S65>/ReadParameter'
  px4_internal_block_ParameterU_T obj_e4;// '<S64>/ReadParameter'
  px4_internal_block_ParameterU_T obj_k0;// '<S63>/ReadParameter'
  px4_internal_block_ParameterU_T obj_h3;// '<S62>/ReadParameter'
  px4_internal_block_ParameterU_T obj_e3;// '<S61>/ReadParameter'
  px4_internal_block_ParameterU_T obj_mv;// '<S60>/ReadParameter'
  px4_internal_block_ParameterU_T obj_a0;// '<S59>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bdp;// '<S58>/ReadParameter'
  px4_internal_block_ParameterU_T obj_jd;// '<S57>/ReadParameter'
  px4_internal_block_ParameterU_T obj_gl;// '<S56>/ReadParameter'
  px4_internal_block_ParameterU_T obj_jf;// '<S55>/ReadParameter'
  px4_internal_block_ParameterU_T obj_av;// '<S54>/ReadParameter'
  px4_internal_block_ParameterU_T obj_kz;// '<S53>/ReadParameter'
  px4_internal_block_ParameterU_T obj_nu;// '<S52>/ReadParameter'
  px4_internal_block_ParameterU_T obj_f;// '<S51>/ReadParameter'
  px4_internal_block_ParameterU_T obj_eq;// '<S50>/ReadParameter'
  px4_internal_block_ParameterU_T obj_k0q;// '<S49>/ReadParameter'
  px4_internal_block_ParameterU_T obj_oi;// '<S48>/ReadParameter'
  px4_internal_block_ParameterU_T obj_bi;// '<S47>/ReadParameter'
  px4_internal_block_ParameterU_T obj_f3;// '<S46>/ReadParameter'
  px4_internal_block_ParameterU_T obj_en;// '<S45>/ReadParameter'
  px4_internal_block_ParameterU_T obj_a4r;// '<S44>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cg;// '<S43>/ReadParameter'
  px4_internal_block_ParameterU_T obj_as;// '<S42>/ReadParameter'
  px4_internal_block_ParameterU_T obj_ea;// '<S41>/ReadParameter'
  px4_internal_block_ParameterU_T obj_ev;// '<S40>/ReadParameter'
  px4_internal_block_ParameterU_T obj_mt;// '<S39>/ReadParameter'
  px4_internal_block_ParameterU_T obj_pi;// '<S38>/ReadParameter'
  px4_internal_block_ParameterU_T obj_c4p;// '<S37>/ReadParameter'
  px4_internal_block_ParameterU_T obj_hm;// '<S36>/ReadParameter'
  px4_internal_block_ParameterU_T obj_c2x;// '<S35>/ReadParameter'
  px4_internal_block_ParameterU_T obj_ah;// '<S34>/ReadParameter'
  px4_internal_block_ParameterU_T obj_d;// '<S33>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cm;// '<S32>/ReadParameter'
  px4_internal_block_ParameterU_T obj_at;// '<S31>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cf;// '<S30>/ReadParameter'
  px4_internal_block_ParameterU_T obj_kg;// '<S29>/ReadParameter'
  px4_internal_block_ParameterU_T obj_e5;// '<S28>/ReadParameter'
  px4_internal_block_ParameterU_T obj_fg;// '<S27>/ReadParameter'
  px4_internal_block_ParameterU_T obj_a4v;// '<S26>/ReadParameter'
  px4_internal_block_ParameterU_T obj_mw;// '<S25>/ReadParameter'
  px4_internal_block_ParameterU_T obj_m5;// '<S24>/ReadParameter'
  px4_internal_block_ParameterU_T obj_dr;// '<S23>/ReadParameter'
  px4_internal_block_ParameterU_T obj_ds;// '<S22>/ReadParameter'
  px4_internal_block_ParameterU_T obj_b3;// '<S21>/ReadParameter'
  px4_internal_block_ParameterU_T obj_if;// '<S20>/ReadParameter'
  px4_internal_block_ParameterU_T obj_i4;// '<S19>/ReadParameter'
  px4_internal_block_ParameterU_T obj_c0;// '<S18>/ReadParameter'
  px4_internal_block_ParameterU_T obj_cs;// '<S17>/ReadParameter'
  px4_internal_block_ParameterU_T obj_a0p;// '<S16>/ReadParameter'
  px4_internal_block_ParameterU_T obj_c1;// '<S15>/ReadParameter'
  px4_internal_block_ParameterU_T obj_kb;// '<S14>/ReadParameter'
  real_T INPUT_10_1_1_SimscapeInternalDi;// '<S302>/INPUT_10_1_1'
  real_T INPUT_10_1_1_SimscapeInternalFi;// '<S302>/INPUT_10_1_1'
  real_T INPUT_11_1_1_SimscapeInternalDi;// '<S302>/INPUT_11_1_1'
  real_T INPUT_11_1_1_SimscapeInternalFi;// '<S302>/INPUT_11_1_1'
  real_T INPUT_12_1_1_SimscapeInternalDi;// '<S302>/INPUT_12_1_1'
  real_T INPUT_12_1_1_SimscapeInternalFi;// '<S302>/INPUT_12_1_1'
  real_T INPUT_13_1_1_SimscapeInternalDi;// '<S302>/INPUT_13_1_1'
  real_T INPUT_13_1_1_SimscapeInternalFi;// '<S302>/INPUT_13_1_1'
  real_T INPUT_14_1_1_SimscapeInternalDi;// '<S302>/INPUT_14_1_1'
  real_T INPUT_14_1_1_SimscapeInternalFi;// '<S302>/INPUT_14_1_1'
  real_T INPUT_9_1_1_SimscapeInternalDis;// '<S302>/INPUT_9_1_1'
  real_T INPUT_9_1_1_SimscapeInternalFir;// '<S302>/INPUT_9_1_1'
  real_T INPUT_16_1_1_SimscapeInternalDi[2];// '<S302>/INPUT_16_1_1'
  real_T INPUT_15_1_1_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_1'
  real_T INPUT_15_1_2_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_2'
  real_T INPUT_15_1_3_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_3'
  real_T INPUT_15_1_4_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_4'
  real_T INPUT_15_1_5_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_5'
  real_T INPUT_15_1_6_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_6'
  real_T INPUT_15_1_7_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_7'
  real_T INPUT_15_1_8_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_8'
  real_T INPUT_15_1_9_SimscapeInternalDi[2];// '<S302>/INPUT_15_1_9'
  real_T INPUT_1_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_1_1_1'
  real_T INPUT_2_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_2_1_1'
  real_T INPUT_8_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_8_1_1'
  real_T INPUT_3_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_3_1_1'
  real_T INPUT_4_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_4_1_1'
  real_T INPUT_5_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_5_1_1'
  real_T INPUT_6_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_6_1_1'
  real_T INPUT_7_1_1_SimscapeInternalDis[2];// '<S302>/INPUT_7_1_1'
  real_T STATE_1_Discrete;             // '<S302>/STATE_1'
  real_T STATE_1_JacobElems;           // '<S302>/STATE_1'
  real_T STATE_1_ZcValueStore;         // '<S302>/STATE_1'
  real_T OUTPUT_1_0_Discrete;          // '<S302>/OUTPUT_1_0'
  real_T OUTPUT_1_0_JacobElems;        // '<S302>/OUTPUT_1_0'
  real_T OUTPUT_1_0_ZcValueStore;      // '<S302>/OUTPUT_1_0'
  void* STATE_1_Simulator;             // '<S302>/STATE_1'
  void* STATE_1_SimData;               // '<S302>/STATE_1'
  void* STATE_1_DiagMgr;               // '<S302>/STATE_1'
  void* STATE_1_ZcLogger;              // '<S302>/STATE_1'
  void* STATE_1_TsInfo;                // '<S302>/STATE_1'
  void* SINK_1_RtwLogger;              // '<S302>/SINK_1'
  void* SINK_1_RtwLogBuffer;           // '<S302>/SINK_1'
  void* SINK_1_RtwLogFcnManager;       // '<S302>/SINK_1'
  void* SINK_1_InstRtwLogger;          // '<S302>/SINK_1'
  void* SINK_1_InstRtwLogBuffer;       // '<S302>/SINK_1'
  void* OUTPUT_1_0_Simulator;          // '<S302>/OUTPUT_1_0'
  void* OUTPUT_1_0_SimData;            // '<S302>/OUTPUT_1_0'
  void* OUTPUT_1_0_DiagMgr;            // '<S302>/OUTPUT_1_0'
  void* OUTPUT_1_0_ZcLogger;           // '<S302>/OUTPUT_1_0'
  void* OUTPUT_1_0_TsInfo;             // '<S302>/OUTPUT_1_0'
  struct {
    void *LoggedData;
  } Scope_PWORK;                       // '<S169>/Scope'

  int_T STATE_1_Modes;                 // '<S302>/STATE_1'
  int_T STATE_1_SwtgCoeffs;            // '<S302>/STATE_1'
  int_T OUTPUT_1_0_Modes;              // '<S302>/OUTPUT_1_0'
  int_T OUTPUT_1_0_SwtgCoeffs;         // '<S302>/OUTPUT_1_0'
  int8_T If_ActiveSubsystem;           // '<S190>/If'
  int8_T If1_ActiveSubsystem;          // '<S195>/If1'
  int8_T If_ActiveSubsystem_f;         // '<S196>/If'
  int8_T If_ActiveSubsystem_m;         // '<S200>/If'
  uint8_T STATE_1_ZcSignalDir;         // '<S302>/STATE_1'
  uint8_T STATE_1_ZcStateStore;        // '<S302>/STATE_1'
  uint8_T OUTPUT_1_0_ZcSignalDir;      // '<S302>/OUTPUT_1_0'
  uint8_T OUTPUT_1_0_ZcStateStore;     // '<S302>/OUTPUT_1_0'
  boolean_T STATE_1_FirstOutput;       // '<S302>/STATE_1'
  boolean_T OUTPUT_1_0_FirstOutput;    // '<S302>/OUTPUT_1_0'
  boolean_T doneDoubleBufferReInit;    // '<S4>/MATLAB Function'
  boolean_T doneDoubleBufferReInit_e;  // '<S10>/GetBInvMatrix'
  boolean_T doneDoubleBufferReInit_ec; // '<S9>/PD Controller'
  boolean_T doneDoubleBufferReInit_d;  // '<S1>/MATLAB Function1'
};

// Continuous states (default storage)
struct X_UAM_Hexa_PD_Obs_QGround_T {
  real_T gamma_hat_1_CSTATE[8];        // '<S7>/gamma_hat_1'
  real_T gamma_hat_2_CSTATE[8];        // '<S7>/gamma_hat_2'
  real_T Integrator7_CSTATE;           // '<S169>/Integrator7'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_Arm[2];// '<S302>/INPUT_10_1_1'
  real_T Integrator9_CSTATE;           // '<S169>/Integrator9'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_a[2];// '<S302>/INPUT_11_1_1'
  real_T Integrator10_CSTATE;          // '<S169>/Integrator10'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_i[2];// '<S302>/INPUT_12_1_1'
  real_T Integrator11_CSTATE;          // '<S169>/Integrator11'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_o[2];// '<S302>/INPUT_13_1_1'
  real_T Integrator12_CSTATE;          // '<S169>/Integrator12'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_e[2];// '<S302>/INPUT_14_1_1'
  real_T Integrator13_CSTATE;          // '<S169>/Integrator13'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_c[2];// '<S302>/INPUT_9_1_1'
  real_T UAM_Hexa_PD_Obs_QGroundHexa__ac[17];// '<S302>/STATE_1'
  real_T gamma_3_hat_CSTATE[8];        // '<S7>/gamma_3_hat'
};

// State derivatives (default storage)
struct XDot_UAM_Hexa_PD_Obs_QGround_T {
  real_T gamma_hat_1_CSTATE[8];        // '<S7>/gamma_hat_1'
  real_T gamma_hat_2_CSTATE[8];        // '<S7>/gamma_hat_2'
  real_T Integrator7_CSTATE;           // '<S169>/Integrator7'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_Arm[2];// '<S302>/INPUT_10_1_1'
  real_T Integrator9_CSTATE;           // '<S169>/Integrator9'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_a[2];// '<S302>/INPUT_11_1_1'
  real_T Integrator10_CSTATE;          // '<S169>/Integrator10'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_i[2];// '<S302>/INPUT_12_1_1'
  real_T Integrator11_CSTATE;          // '<S169>/Integrator11'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_o[2];// '<S302>/INPUT_13_1_1'
  real_T Integrator12_CSTATE;          // '<S169>/Integrator12'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_e[2];// '<S302>/INPUT_14_1_1'
  real_T Integrator13_CSTATE;          // '<S169>/Integrator13'
  real_T UAM_Hexa_PD_Obs_QGroundHexa_A_c[2];// '<S302>/INPUT_9_1_1'
  real_T UAM_Hexa_PD_Obs_QGroundHexa__ac[17];// '<S302>/STATE_1'
  real_T gamma_3_hat_CSTATE[8];        // '<S7>/gamma_3_hat'
};

// State disabled
struct XDis_UAM_Hexa_PD_Obs_QGround_T {
  boolean_T gamma_hat_1_CSTATE[8];     // '<S7>/gamma_hat_1'
  boolean_T gamma_hat_2_CSTATE[8];     // '<S7>/gamma_hat_2'
  boolean_T Integrator7_CSTATE;        // '<S169>/Integrator7'
  boolean_T UAM_Hexa_PD_Obs_QGroundHexa_Arm[2];// '<S302>/INPUT_10_1_1'
  boolean_T Integrator9_CSTATE;        // '<S169>/Integrator9'
  boolean_T UAM_Hexa_PD_Obs_QGroundHexa_A_a[2];// '<S302>/INPUT_11_1_1'
  boolean_T Integrator10_CSTATE;       // '<S169>/Integrator10'
  boolean_T UAM_Hexa_PD_Obs_QGroundHexa_A_i[2];// '<S302>/INPUT_12_1_1'
  boolean_T Integrator11_CSTATE;       // '<S169>/Integrator11'
  boolean_T UAM_Hexa_PD_Obs_QGroundHexa_A_o[2];// '<S302>/INPUT_13_1_1'
  boolean_T Integrator12_CSTATE;       // '<S169>/Integrator12'
  boolean_T UAM_Hexa_PD_Obs_QGroundHexa_A_e[2];// '<S302>/INPUT_14_1_1'
  boolean_T Integrator13_CSTATE;       // '<S169>/Integrator13'
  boolean_T UAM_Hexa_PD_Obs_QGroundHexa_A_c[2];// '<S302>/INPUT_9_1_1'
  boolean_T UAM_Hexa_PD_Obs_QGroundHexa__ac[17];// '<S302>/STATE_1'
  boolean_T gamma_3_hat_CSTATE[8];     // '<S7>/gamma_3_hat'
};

#ifndef ODE4_INTG
#define ODE4_INTG

// ODE4 Integration Data
struct ODE4_IntgData {
  real_T *y;                           // output
  real_T *f[4];                        // derivatives
};

#endif

// Parameters (default storage)
struct P_UAM_Hexa_PD_Obs_QGround_T_ {
  struct_Z1yy0b1SiRejj6ODUGxXCE HexaConstants;// Variable: HexaConstants
                                                 //  Referenced by:
                                                 //    '<S1>/MATLAB Function1'
                                                 //    '<S169>/Thrust Factor (kT)1'

  struct_u7NbN6ywI9YZ24VWuwFOtG Trajectory;// Variable: Trajectory
                                              //  Referenced by: '<S5>/Polynomial Trajectory'

  struct_JL8g2iM4Lw6J1bY0kTxLfE ArmConstants;// Variable: ArmConstants
                                                //  Referenced by:
                                                //    '<S1>/MATLAB Function1'
                                                //    '<S1>/Torque Saturation1'

  struct_MBcKnh9NPgZzNahcpBRZ5 PickObj;// Variable: PickObj
                                          //  Referenced by: '<S4>/MATLAB Function'

  real_T DCM2Ang_tolerance;            // Mask Parameter: DCM2Ang_tolerance
                                          //  Referenced by:
                                          //    '<S216>/Constant'
                                          //    '<S218>/Constant'

  uint8_T DCM2Ang_action;              // Mask Parameter: DCM2Ang_action
                                          //  Referenced by:
                                          //    '<S195>/Constant'
                                          //    '<S205>/Constant'
                                          //    '<S207>/Constant'

  real_T Constant_Value;               // Expression: 1
                                          //  Referenced by: '<S201>/Constant'

  real_T Constant_Value_i;             // Expression: -1
                                          //  Referenced by: '<S202>/Constant'

  real_T Constant_Value_o;             // Expression: 1
                                          //  Referenced by: '<S197>/Constant'

  real_T Constant_Value_m;             // Expression: -1
                                          //  Referenced by: '<S198>/Constant'

  real_T Constant1_Value;              // Expression: 0
                                          //  Referenced by: '<S207>/Constant1'

  real_T Constant1_Value_a;            // Expression: 0
                                          //  Referenced by: '<S205>/Constant1'

  real_T Bias1_Bias[9];                // Expression: -eye(3)
                                          //  Referenced by: '<S208>/Bias1'

  real_T Bias_Bias;                    // Expression: -1
                                          //  Referenced by: '<S209>/Bias'

  real_T PolynomialTrajectory_VelocityBo[32];
                              // Expression: zeros( size(Trajectory.Waypoints) )
                                 //  Referenced by: '<S5>/Polynomial Trajectory'

  real_T gamma_hat_1_IC[8];           // Expression: [0; 0; 0.24; 0; 0; 0; 0; 0]
                                         //  Referenced by: '<S7>/gamma_hat_1'

  real_T gamma_hat_2_IC[8];            // Expression: zeros(8,1)
                                          //  Referenced by: '<S7>/gamma_hat_2'

  real_T Constant_Value_f[36];
  // Expression: inv(1.0e-05*[-0.2372    0.2372    0.0000   -0.2372    0.2372    0.0000;...
     // 0.1369    0.1369   -0.2739    0.1369    0.1369   -0.2739;...
     // 0.7525    0.7525    0.7525    0.7525    0.7525    0.7525;...
     // 0.1694    0.1694    0.0000   -0.1694   -0.1694    0.0000;...
     // -0.0978    0.0978    0.1956    0.0978   -0.0978   -0.1956;...
     // 0.0830   -0.0830    0.0830   -0.0830    0.0830   -0.0830])
     //  Referenced by: '<S6>/Constant'

  real_T Integrator7_IC;               // Expression: 0
                                          //  Referenced by: '<S169>/Integrator7'

  real_T Integrator9_IC;               // Expression: 0
                                          //  Referenced by: '<S169>/Integrator9'

  real_T Integrator10_IC;              // Expression: 0
                                          //  Referenced by: '<S169>/Integrator10'

  real_T Integrator11_IC;              // Expression: 0
                                          //  Referenced by: '<S169>/Integrator11'

  real_T Integrator12_IC;              // Expression: 0
                                          //  Referenced by: '<S169>/Integrator12'

  real_T Integrator13_IC;              // Expression: 0
                                          //  Referenced by: '<S169>/Integrator13'

  real_T gamma_3_hat_IC[8];          // Expression: [0; 0; -9.81; 0; 0; 0; 0; 0]
                                        //  Referenced by: '<S7>/gamma_3_hat'

  real_T RotationSaturation1_UpperSat; // Expression: 8.77e+05

                                          //  Referenced by: '<S6>/Rotation Saturation1'

  real_T RotationSaturation1_LowerSat; // Expression: 0
                                          //  Referenced by: '<S6>/Rotation Saturation1'

  real_T Saturation1_UpperSat;         // Expression: 7
                                          //  Referenced by: '<S169>/Saturation1'

  real_T Saturation1_LowerSat;         // Expression: 0
                                          //  Referenced by: '<S169>/Saturation1'

  real_T Gain_Gain;                    // Expression: 2
                                          //  Referenced by: '<S222>/Gain'

  real_T Gain_Gain_m;                  // Expression: 2
                                          //  Referenced by: '<S225>/Gain'

  real_T Gain_Gain_f;                  // Expression: 2
                                          //  Referenced by: '<S220>/Gain'

  real_T Gain_Gain_h;                  // Expression: 2
                                          //  Referenced by: '<S226>/Gain'

  real_T Gain_Gain_p;                  // Expression: 2
                                          //  Referenced by: '<S221>/Gain'

  real_T Gain_Gain_g;                  // Expression: 2
                                          //  Referenced by: '<S224>/Gain'

  real_T Gain1_Gain[3];                // Expression: [1 1 -1]
                                          //  Referenced by: '<S194>/Gain1'

  real_T Gain2_Gain[2];                // Expression: [1 1]
                                          //  Referenced by: '<S194>/Gain2'

  real_T Gain3_Gain[2];                // Expression: [-1 1]
                                          //  Referenced by: '<S194>/Gain3'

  real_T Constant4_Value[8];           // Expression: [2;2;2;2;2;2;2;2]
                                          //  Referenced by: '<S7>/Constant4'

  real_T Gain4_Gain;                   // Expression: 1/3
                                          //  Referenced by: '<S7>/Gain4'

  real_T Constant2_Value[8];           // Expression: [2;2;2;2;2;2;2;2]
                                          //  Referenced by: '<S7>/Constant2'

  real_T Gain3_Gain_j;                 // Expression: 1/3
                                          //  Referenced by: '<S7>/Gain3'

  real_T Constant7_Value[8];           // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
                                          //  Referenced by: '<S7>/Constant7'

  real_T Gain6_Gain;                   // Expression: 0.5
                                          //  Referenced by: '<S7>/Gain6'

  real_T Constant6_Value[8];           // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
                                          //  Referenced by: '<S7>/Constant6'

  real_T Gain5_Gain;                   // Expression: 0.5
                                          //  Referenced by: '<S7>/Gain5'

  real_T Gain6_Gain_p;                 // Expression: -1
                                          //  Referenced by: '<S169>/Gain6'

  real_T Gain4_Gain_a;                 // Expression: -1
                                          //  Referenced by: '<S169>/Gain4'

  real_T Gain3_Gain_e;                 // Expression: -1
                                          //  Referenced by: '<S169>/Gain3'

  boolean_T Assertion_Enabled;         // Computed Parameter: Assertion_Enabled
                                          //  Referenced by: '<S215>/Assertion'

  boolean_T Assertion_Enabled_f;      // Computed Parameter: Assertion_Enabled_f
                                         //  Referenced by: '<S213>/Assertion'

  boolean_T Assertion_Enabled_c;      // Computed Parameter: Assertion_Enabled_c
                                         //  Referenced by: '<S212>/Assertion'

  boolean_T Assertion_Enabled_i;      // Computed Parameter: Assertion_Enabled_i
                                         //  Referenced by: '<S210>/Assertion'

};

// Real-time Model Data Structure
struct tag_RTM_UAM_Hexa_PD_Obs_QGrou_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  X_UAM_Hexa_PD_Obs_QGround_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_UAM_Hexa_PD_Obs_QGround_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[59];
  real_T odeF[4][59];
  ODE4_IntgData intgData;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    uint32_T checksums[4];
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  //
  //  SpecialInfo:
  //  The following substructure contains special information
  //  related to other components that are dependent on RTW.

  struct {
    const void *mappingInfo;
  } SpecialInfo;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_UAM_Hexa_PD_Obs_QGround_T UAM_Hexa_PD_Obs_QGround_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_UAM_Hexa_PD_Obs_QGround_T UAM_Hexa_PD_Obs_QGround_B;

#ifdef __cplusplus

}

#endif

// Continuous states (default storage)
extern X_UAM_Hexa_PD_Obs_QGround_T UAM_Hexa_PD_Obs_QGround_X;

// Disabled states (default storage)
extern XDis_UAM_Hexa_PD_Obs_QGround_T UAM_Hexa_PD_Obs_QGround_XDis;

// Block states (default storage)
extern struct DW_UAM_Hexa_PD_Obs_QGround_T UAM_Hexa_PD_Obs_QGround_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void UAM_Hexa_PD_Obs_QGround_initialize(void);
  extern void UAM_Hexa_PD_Obs_QGround_step(void);
  extern void UAM_Hexa_PD_Obs_QGround_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_UAM_Hexa_PD_Obs_QGro_T *const UAM_Hexa_PD_Obs_QGround_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S194>/Reshape' : Reshape block reduction
//  Block '<S194>/Reshape1' : Reshape block reduction
//  Block '<S194>/Reshape2' : Reshape block reduction
//  Block '<S208>/Reshape' : Reshape block reduction
//  Block '<S228>/Reshape (9) to [3x3] column-major' : Reshape block reduction
//  Block '<S306>/RESHAPE_0' : Reshape block reduction
//  Block '<S306>/RESHAPE_1' : Reshape block reduction
//  Block '<S306>/RESHAPE_2' : Reshape block reduction


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'UAM_Hexa_PD_Obs_QGround'
//  '<S1>'   : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer'
//  '<S2>'   : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters'
//  '<S3>'   : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model'
//  '<S4>'   : 'UAM_Hexa_PD_Obs_QGround/PickingObj'
//  '<S5>'   : 'UAM_Hexa_PD_Obs_QGround/Trajectory'
//  '<S6>'   : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/Allocation Matrix'
//  '<S7>'   : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/ExtendedStateObserver'
//  '<S8>'   : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/MATLAB Function1'
//  '<S9>'   : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/PDController1'
//  '<S10>'  : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/U_to_Forces'
//  '<S11>'  : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/PDController1/Obtain Error'
//  '<S12>'  : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/PDController1/PD Controller'
//  '<S13>'  : 'UAM_Hexa_PD_Obs_QGround/Controller And Observer/U_to_Forces/GetBInvMatrix'
//  '<S14>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter1'
//  '<S15>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter10'
//  '<S16>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter100'
//  '<S17>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter101'
//  '<S18>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter11'
//  '<S19>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter12'
//  '<S20>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter13'
//  '<S21>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter14'
//  '<S22>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter15'
//  '<S23>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter16'
//  '<S24>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter17'
//  '<S25>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter18'
//  '<S26>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter19'
//  '<S27>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter2'
//  '<S28>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter20'
//  '<S29>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter21'
//  '<S30>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter22'
//  '<S31>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter23'
//  '<S32>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter24'
//  '<S33>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter25'
//  '<S34>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter26'
//  '<S35>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter27'
//  '<S36>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter28'
//  '<S37>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter29'
//  '<S38>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter3'
//  '<S39>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter30'
//  '<S40>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter31'
//  '<S41>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter32'
//  '<S42>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter33'
//  '<S43>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter34'
//  '<S44>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter35'
//  '<S45>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter36'
//  '<S46>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter37'
//  '<S47>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter38'
//  '<S48>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter39'
//  '<S49>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter4'
//  '<S50>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter40'
//  '<S51>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter41'
//  '<S52>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter42'
//  '<S53>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter43'
//  '<S54>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter44'
//  '<S55>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter45'
//  '<S56>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter46'
//  '<S57>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter47'
//  '<S58>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter48'
//  '<S59>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter49'
//  '<S60>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter5'
//  '<S61>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter50'
//  '<S62>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter51'
//  '<S63>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter52'
//  '<S64>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter53'
//  '<S65>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter54'
//  '<S66>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter55'
//  '<S67>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter56'
//  '<S68>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter57'
//  '<S69>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter58'
//  '<S70>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter59'
//  '<S71>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter6'
//  '<S72>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter60'
//  '<S73>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter61'
//  '<S74>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter62'
//  '<S75>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter63'
//  '<S76>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter64'
//  '<S77>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter65'
//  '<S78>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter66'
//  '<S79>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter67'
//  '<S80>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter68'
//  '<S81>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter69'
//  '<S82>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter7'
//  '<S83>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter70'
//  '<S84>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter71'
//  '<S85>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter72'
//  '<S86>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter73'
//  '<S87>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter74'
//  '<S88>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter75'
//  '<S89>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter76'
//  '<S90>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter77'
//  '<S91>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter78'
//  '<S92>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter79'
//  '<S93>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter8'
//  '<S94>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter80'
//  '<S95>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter81'
//  '<S96>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter82'
//  '<S97>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter83'
//  '<S98>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter84'
//  '<S99>'  : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter85'
//  '<S100>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter86'
//  '<S101>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter87'
//  '<S102>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter88'
//  '<S103>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter89'
//  '<S104>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter9'
//  '<S105>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter90'
//  '<S106>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter91'
//  '<S107>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter92'
//  '<S108>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter93'
//  '<S109>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter94'
//  '<S110>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter95'
//  '<S111>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter96'
//  '<S112>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter97'
//  '<S113>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter98'
//  '<S114>' : 'UAM_Hexa_PD_Obs_QGround/GetQGC Parameters/Read Parameter99'
//  '<S115>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm'
//  '<S116>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model'
//  '<S117>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Adjust Rev1'
//  '<S118>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Adjust Rev2'
//  '<S119>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID'
//  '<S120>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID'
//  '<S121>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter'
//  '<S122>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter1'
//  '<S123>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter2'
//  '<S124>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter3'
//  '<S125>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Return Rev1'
//  '<S126>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Return Rev2'
//  '<S127>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Servo1_RIGID'
//  '<S128>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Simulink-PS Converter'
//  '<S129>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Simulink-PS Converter1'
//  '<S130>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID/Rueda_abajo_1_RIGID'
//  '<S131>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID/Rueda_arriba_1_RIGID'
//  '<S132>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID/Servo_RDS3225_1_RIGID'
//  '<S133>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID/Soporte_U_corto_1_RIGID'
//  '<S134>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID/Soporte_U_largo_1_RIGID'
//  '<S135>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID/Soporte_U_largo_2_RIGID'
//  '<S136>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_1_RIGID/Soporte_U_mediano_1_RIGID'
//  '<S137>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Base_tubo_1_RIGID'
//  '<S138>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Base_tubo_2_RIGID'
//  '<S139>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Cuerpo_Tubo_1_RIGID'
//  '<S140>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID'
//  '<S141>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Hitec_HS_300_1_RIGID'
//  '<S142>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Rueda_abajo_1_RIGID'
//  '<S143>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Rueda_arriba_1_RIGID'
//  '<S144>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Rueda_arriba_2_RIGID'
//  '<S145>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Soporte_U_mediano_1_RIGID'
//  '<S146>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_1_1_RIGID'
//  '<S147>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_1_2_RIGID'
//  '<S148>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_1_3_RIGID'
//  '<S149>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_1_4_RIGID'
//  '<S150>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_2_1_RIGID'
//  '<S151>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_2_2_RIGID'
//  '<S152>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_2_3_RIGID'
//  '<S153>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_2_4_RIGID'
//  '<S154>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_3_1_RIGID'
//  '<S155>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_4_1_RIGID'
//  '<S156>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_4_2_RIGID'
//  '<S157>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_5_1_RIGID'
//  '<S158>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Link_2_RIGID/Gripper_1_RIGID/Fix_1_1_Ref_Capit_5_2_RIGID'
//  '<S159>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter/EVAL_KEY'
//  '<S160>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter1/EVAL_KEY'
//  '<S161>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter2/EVAL_KEY'
//  '<S162>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/PS-Simulink Converter3/EVAL_KEY'
//  '<S163>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Servo1_RIGID/Base_Plate_1_RIGID'
//  '<S164>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Servo1_RIGID/Servo_RDS3225_1_RIGID'
//  '<S165>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Servo1_RIGID/Soporte_U_corto_1_RIGID'
//  '<S166>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Simulink-PS Converter/EVAL_KEY'
//  '<S167>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Arm/Simulink-PS Converter1/EVAL_KEY'
//  '<S168>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem'
//  '<S169>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem Reference2'
//  '<S170>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/CMToTopPlate'
//  '<S171>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint'
//  '<S172>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID'
//  '<S173>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors'
//  '<S174>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers'
//  '<S175>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Solver Configuration'
//  '<S176>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/PS-Simulink Converter3'
//  '<S177>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/PS-Simulink Converter4'
//  '<S178>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/PS-Simulink Converter5'
//  '<S179>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1'
//  '<S180>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Sx4'
//  '<S181>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/x'
//  '<S182>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/xp'
//  '<S183>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/y'
//  '<S184>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/yp'
//  '<S185>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/z'
//  '<S186>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/zp'
//  '<S187>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/PS-Simulink Converter3/EVAL_KEY'
//  '<S188>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/PS-Simulink Converter4/EVAL_KEY'
//  '<S189>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/PS-Simulink Converter5/EVAL_KEY'
//  '<S190>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang'
//  '<S191>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM'
//  '<S192>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotDefault'
//  '<S193>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotZeroR3'
//  '<S194>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Get DCM Values'
//  '<S195>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM'
//  '<S196>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotDefault/Protect asincos input'
//  '<S197>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotDefault/Protect asincos input/If Action Subsystem'
//  '<S198>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotDefault/Protect asincos input/If Action Subsystem1'
//  '<S199>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotDefault/Protect asincos input/If Action Subsystem2'
//  '<S200>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotZeroR3/Protect asincos input'
//  '<S201>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotZeroR3/Protect asincos input/If Action Subsystem'
//  '<S202>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotZeroR3/Protect asincos input/If Action Subsystem1'
//  '<S203>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/AxisRotZeroR3/Protect asincos input/If Action Subsystem2'
//  '<S204>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error'
//  '<S205>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/Else If Not Orthogonal'
//  '<S206>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/Else No Action'
//  '<S207>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/If Not Proper'
//  '<S208>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/isNotOrthogonal'
//  '<S209>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/isNotProper'
//  '<S210>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/Else If Not Orthogonal/Error'
//  '<S211>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/Else If Not Orthogonal/None'
//  '<S212>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/Else If Not Orthogonal/Warning'
//  '<S213>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/If Not Proper/Error'
//  '<S214>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/If Not Proper/None'
//  '<S215>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/If Not Proper/Warning'
//  '<S216>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/isNotOrthogonal/transpose*dcm ~= eye(3)'
//  '<S217>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/isNotProper/Determinant of 3x3 Matrix'
//  '<S218>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/DCM2Ang/Validate DCM/If Warning//Error/isNotProper/determinant does not equal 1'
//  '<S219>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A11'
//  '<S220>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A12'
//  '<S221>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A13'
//  '<S222>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A21'
//  '<S223>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A22'
//  '<S224>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A23'
//  '<S225>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A31'
//  '<S226>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A32'
//  '<S227>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/A33'
//  '<S228>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/Create 3x3 Matrix'
//  '<S229>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/Quaternion Normalize'
//  '<S230>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/Quaternion Normalize/Quaternion Modulus'
//  '<S231>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Quaternions to Rotation Angles1/Quat2DCM/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
//  '<S232>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/Sx4/EVAL_KEY'
//  '<S233>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/x/EVAL_KEY'
//  '<S234>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/xp/EVAL_KEY'
//  '<S235>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/y/EVAL_KEY'
//  '<S236>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/yp/EVAL_KEY'
//  '<S237>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/z/EVAL_KEY'
//  '<S238>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa6DOFJoint/zp/EVAL_KEY'
//  '<S239>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Arm_1_RIGID'
//  '<S240>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Arm_2_RIGID'
//  '<S241>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Arm_3_RIGID'
//  '<S242>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Arm_4_RIGID'
//  '<S243>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Arm_5_RIGID'
//  '<S244>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Arm_6_RIGID'
//  '<S245>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base1_1_RIGID'
//  '<S246>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base2_1_RIGID'
//  '<S247>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base_20deg_6Compensation_Motor1_3_5_V2_1_RIGID'
//  '<S248>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base_20deg_6Compensation_Motor1_3_5_V2_2_RIGID'
//  '<S249>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base_20deg_6Compensation_Motor1_3_5_V2_3_RIGID'
//  '<S250>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base_20deg_6Compensation_Motor2_4_6_V2_1_RIGID'
//  '<S251>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base_20deg_6Compensation_Motor2_4_6_V2_2_RIGID'
//  '<S252>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Base_20deg_6Compensation_Motor2_4_6_V2_3_RIGID'
//  '<S253>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Bottom_Plate_S550_1_RIGID'
//  '<S254>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/CaseB_1_RIGID'
//  '<S255>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/CaseT_1_RIGID'
//  '<S256>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Landing_support_1_RIGID'
//  '<S257>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Landing_support_2_RIGID'
//  '<S258>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/NAVIO2_1_RIGID'
//  '<S259>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Raspberry_Pi_4_Model_B_1_RIGID'
//  '<S260>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Rubber_V2_1_RIGID'
//  '<S261>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Rubber_V2_2_RIGID'
//  '<S262>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Rubber_V2_3_RIGID'
//  '<S263>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Rubber_V2_4_RIGID'
//  '<S264>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Top_Plate_S550_1_RIGID'
//  '<S265>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Hexa_RIGID/Turnigy_5000mAh_3S_2_RIGID'
//  '<S266>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/A2212Motor_1_RIGID'
//  '<S267>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/A2212Motor_2_RIGID'
//  '<S268>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/A2212Motor_3_RIGID'
//  '<S269>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/A2212Motor_4_RIGID'
//  '<S270>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/A2212Motor_5_RIGID'
//  '<S271>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/A2212Motor_6_RIGID'
//  '<S272>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter1'
//  '<S273>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter2'
//  '<S274>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter3'
//  '<S275>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter4'
//  '<S276>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter5'
//  '<S277>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter6'
//  '<S278>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter1/EVAL_KEY'
//  '<S279>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter2/EVAL_KEY'
//  '<S280>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter3/EVAL_KEY'
//  '<S281>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter4/EVAL_KEY'
//  '<S282>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter5/EVAL_KEY'
//  '<S283>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Motors/Simulink-PS Converter6/EVAL_KEY'
//  '<S284>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/P1_RIGID'
//  '<S285>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/P2_RIGID'
//  '<S286>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/P3_RIGID'
//  '<S287>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/P4_RIGID'
//  '<S288>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/P5_RIGID'
//  '<S289>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/P6_RIGID'
//  '<S290>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter1'
//  '<S291>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter10'
//  '<S292>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter11'
//  '<S293>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter12'
//  '<S294>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter2'
//  '<S295>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter9'
//  '<S296>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter1/EVAL_KEY'
//  '<S297>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter10/EVAL_KEY'
//  '<S298>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter11/EVAL_KEY'
//  '<S299>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter12/EVAL_KEY'
//  '<S300>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter2/EVAL_KEY'
//  '<S301>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Propellers/Simulink-PS Converter9/EVAL_KEY'
//  '<S302>' : 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Solver Configuration/EVAL_KEY'
//  '<S303>' : 'UAM_Hexa_PD_Obs_QGround/PickingObj/MATLAB Function'
//  '<S304>' : 'UAM_Hexa_PD_Obs_QGround/PickingObj/Simulink-PS Converter'
//  '<S305>' : 'UAM_Hexa_PD_Obs_QGround/PickingObj/Simulink-PS Converter1'
//  '<S306>' : 'UAM_Hexa_PD_Obs_QGround/PickingObj/Simulink-PS Converter/EVAL_KEY'
//  '<S307>' : 'UAM_Hexa_PD_Obs_QGround/PickingObj/Simulink-PS Converter1/EVAL_KEY'

#endif                                 // UAM_HEXA_PD_OBS_QGROUND_H_

//
// File trailer for generated code.
//
// [EOF]
//
