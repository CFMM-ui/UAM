//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: DifAndCtrl.h
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
#ifndef DIFANDCTRL_H_
#define DIFANDCTRL_H_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "DifAndCtrl_types.h"

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
#include "rt_defines.h"
#include <stddef.h>

// Block signals (default storage)
struct B_DifAndCtrl_T {
  real_T BMinv[64];                    // '<S2>/GetBInvMatrix'
  real_T ginv[64];                     // '<S9>/MATLAB Function1'
  real_T dv[64];
  real_T dv1[64];
  real_T coefsWithFlatStart[64];
  real_T b_A[64];
  real_T coefMat[32];
  real_T coeffMat[32];
  real_T Sum3[8];                      // '<S4>/Sum3'
  real_T Sum4[8];                      // '<S4>/Sum4'
  real_T fx[8];                        // '<S9>/MATLAB Function1'
  real_T rtb_uv_i_m[8];
  real_T rtb_uv_c[8];
  real_T dv2[8];
  real_T dv3[8];
  real_T dv4[8];
  real_T dv5[8];
  int8_T p[8];
  int8_T ipiv[8];
  int8_T ipiv_k[8];
  real_T smax;
  real_T s;
  real_T D14;
  real_T D15;
  real_T D16;
  real_T D17;
  real_T D18;
  real_T D24;
  real_T D25;
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
  real_T D58;
  real_T D67;
  real_T D68;
  real_T y_a;
  real_T ab_a;
  real_T Clock2;                       // '<S3>/Clock2'
  real_T x_tmp;
  real_T x_tmp_c;
  real_T x_tmp_b;
  real_T x_tmp_p;
  real_T x_tmp_cv;
  real_T D14_tmp;
  real_T D14_tmp_f;
  real_T D14_tmp_g;
  real_T D14_tmp_g1;
  real_T D15_tmp;
  real_T D15_tmp_m;
  real_T D46_tmp;
  real_T D46_tmp_n;
  real_T D46_tmp_p;
  real_T D46_tmp_l;
  real_T D46_tmp_j;
  real_T D46_tmp_d;
  real_T D56_tmp;
  real_T D46_tmp_g;
  real_T D56_tmp_l;
  real_T D56_tmp_d;
  real_T D46_tmp_dy;
  real_T D56_tmp_lx;
  real_T D56_tmp_o;
  real_T D46_tmp_b;
  real_T D56_tmp_n;
  real_T D56_tmp_b;
  real_T D46_tmp_ln;
  real_T D56_tmp_h;
  real_T D46_tmp_bn;
  real_T D46_tmp_da;
  real_T D46_tmp_e;
  real_T D56_tmp_bj;
  real_T D56_tmp_j;
  real_T D56_tmp_f;
  real_T D56_tmp_a;
  real_T d;
  real_T d1;
  real_T d2;
  real_T d3;
  real_T d4;
  real_T d5;
  real_T rtb_ginv_tmp;
  real_T D56_tmp_ju;
  real_T D56_tmp_jz;
  real_T D56_tmp_o4;
  real_T D56_tmp_ny;
  real_T d6;
  real_T d7;
  real_T rtb_ginv_tmp_i;
  real_T rtb_ginv_tmp_o;
  real_T rtb_ginv_tmp_n;
  real_T D14_tmp_tmp;
  real_T D14_tmp_m;
  real_T D14_tmp_c;
  real_T D14_tmp_md;
  real_T D14_tmp_m3;
  real_T D15_tmp_tmp;
  real_T D14_tmp_j;
  real_T D14_tmp_h;
  real_T D14_tmp_c0;
  real_T D16_tmp;
  real_T D14_tmp_ct;
  real_T rtb_ginv_tmp_p;
  real_T D14_tmp_tmp_p;
  real_T rtb_ginv_tmp_a;
  real_T D17_tmp;
  real_T D17_tmp_e;
  real_T D24_tmp;
  real_T D17_tmp_a;
  real_T D17_tmp_as;
  real_T D15_tmp_i;
  real_T D24_tmp_l;
  real_T D17_tmp_o;
  real_T rtb_ginv_tmp_tmp;
  real_T D16_tmp_tmp;
  real_T rtb_ginv_tmp_o2;
  real_T D15_tmp_tmp_i;
  real_T D34_tmp;
  real_T D34_tmp_f;
  real_T D46_tmp_tmp;
  real_T D46_tmp_tmp_i;
  real_T D46_tmp_tmp_f;
  real_T D46_tmp_tmp_g;
  real_T D46_tmp_c;
  real_T D46_tmp_o;
  real_T D46_tmp_lm;
  real_T D46_tmp_m;
  real_T D46_tmp_mj;
  real_T D46_tmp_cn;
  real_T D46_tmp_f;
  real_T D47_tmp;
  real_T D56_tmp_tmp;
  real_T D56_tmp_tmp_p;
  real_T D56_tmp_tmp_e;
  real_T D56_tmp_tmp_o;
  real_T D56_tmp_tmp_h;
  real_T D56_tmp_tmp_l;
  real_T D56_tmp_tmp_h2;
  real_T D56_tmp_m;
  real_T D56_tmp_mc;
  real_T D46_tmp_tmp_h;
  real_T D46_tmp_cs;
  real_T D46_tmp_k;
  real_T D47_tmp_p;
  real_T D47_tmp_px;
  real_T D46_tmp_p4;
  real_T D56_tmp_ap;
  real_T D56_tmp_jd;
  real_T D45_tmp;
  real_T D45_tmp_e;
  real_T D24_tmp_o;
  real_T D46_tmp_bb;
  real_T D46_tmp_a;
  real_T D46_tmp_g2;
  real_T D47_tmp_tmp;
  real_T D46_tmp_ex;
  real_T D46_tmp_fi;
  real_T D46_tmp_h;
  real_T D46_tmp_ei;
  real_T D46_tmp_ch;
  real_T D46_tmp_ax;
  real_T D46_tmp_dau;
  real_T D46_tmp_af;
  real_T D46_tmp_pb;
  real_T D48_tmp;
  real_T D46_tmp_tmp_m;
  real_T D48_tmp_o;
  real_T D56_tmp_tmp_tmp;
  real_T rtb_ginv_tmp_tmp_n;
  real_T rtb_ginv_tmp_tmp_l;
  real_T rtb_ginv_tmp_tmp_p;
  real_T D47_tmp_pt;
  real_T D46_tmp_tmp_ft;
  real_T D47_tmp_i;
  real_T rtb_ginv_tmp_ox;
  real_T rtb_ginv_tmp_k;
  real_T rtb_ginv_tmp_ie;
  real_T rtb_ginv_tmp_oc;
  real_T D47_tmp_m;
  real_T D48_tmp_tmp;
  real_T D56_tmp_tmp_c;
  real_T D56_tmp_tmp_f;
  real_T D46_tmp_tmp_hc;
  real_T D56_tmp_tmp_m;
  real_T D56_tmp_tmp_a;
  real_T D46_tmp_tmp_k;
  real_T D46_tmp_tmp_p;
  real_T D46_tmp_tmp_b;
  real_T D46_tmp_tmp_c;
  real_T D46_tmp_tmp_n;
  real_T D14_tmp_i;
  real_T D14_tmp_my;
  real_T D14_tmp_jg;
  real_T D34_tmp_e;
  real_T D14_tmp_mv;
  real_T D16_tmp_m;
  real_T D16_tmp_j;
  real_T D16_tmp_f;
  real_T d8;
  real_T D16_tmp_a;
  real_T d9;
  real_T D37_tmp;
  real_T d10;
  real_T d11;
  real_T d12;
  real_T rtb_ginv_tmp_tmp_g;
  real_T D27_tmp;
  real_T D27_tmp_n;
  real_T d13;
  real_T D46_tmp_tmp_d;
  real_T D46_tmp_na;
  real_T d14;
  real_T d15;
  real_T d16;
  real_T d17;
  real_T D15_tmp_tmp_c;
  real_T D15_tmp_tmp_f;
  real_T d18;
  real_T D14_tmp_tmp_pm;
  real_T D14_tmp_tmp_p2;
  real_T d19;
  real_T d20;
  real_T d21;
  real_T D56_tmp_nj;
  real_T D56_tmp_k;
  real_T D56_tmp_n3;
  real_T D56_tmp_oy;
  real_T D56_tmp_g;
  real_T D56_tmp_c;
  real_T D56_tmp_cj;
  real_T D56_tmp_m1;
  real_T d22;
  real_T d23;
  real_T d24;
  real_T d25;
  real_T D46_tmp_tmp_j;
  real_T d26;
  real_T D46_tmp_tmp_kn;
  real_T d27;
  real_T d28;
  real_T d29;
  real_T d30;
  real_T d31;
  real_T d32;
  real_T d33;
  real_T d34;
  real_T d35;
  real_T d36;
  real_T d37;
  real_T d38;
  real_T d39;
  real_T d40;
  real_T d41;
  real_T d42;
  real_T d43;
  real_T d44;
  real_T d45;
  real_T d46;
  real_T d47;
  real_T d48;
  real_T d49;
  real_T d50;
  real_T d51;
  real_T d52;
  real_T d53;
  real_T d54;
  real_T d55;
  real_T D46_tmp_mx;
  real_T D46_tmp_pr;
  real_T D46_tmp_dz;
  real_T D46_tmp_tmp_g4;
  real_T D47_tmp_c;
  real_T d56;
  real_T d57;
  real_T d58;
  real_T d59;
  real_T d60;
  real_T d61;
  real_T d62;
  real_T d63;
  real_T d64;
  real_T d65;
  real_T d66;
  real_T d67;
  real_T d68;
  real_T d69;
  real_T d70;
  real_T d71;
  real_T d72;
  real_T d73;
  real_T d74;
  real_T d75;
  real_T d76;
  real_T d77;
  real_T d78;
  real_T d79;
  real_T d80;
  real_T d81;
  real_T d82;
  real_T d83;
  real_T d84;
  real_T d85;
  real_T d86;
  real_T d87;
  real_T d88;
  real_T d89;
  real_T d90;
  real_T d91;
  real_T d92;
  real_T d93;
  real_T d94;
  real_T d95;
  real_T d96;
  real_T d97;
  real_T d98;
  real_T D56_tmp_cx;
  real_T D56_tmp_i;
  real_T rtb_ginv_tmp_d;
  real_T rtb_ginv_tmp_g;
  real_T rtb_ginv_tmp_l;
  real_T rtb_ginv_tmp_f;
  real_T d99;
  real_T d100;
  real_T d101;
  real_T d102;
  real_T d103;
  real_T d104;
  real_T d105;
  real_T tmp_tmp;
  real_T d106;
  real_T tmp_tmp_d;
  real_T d107;
  real_T d108;
  real_T d109;
  real_T d110;
  real_T d111;
  real_T d112;
  real_T d113;
  real_T d114;
  real_T d115;
  real_T d116;
  real_T d117;
  real_T d118;
  real_T d119;
  real_T d120;
  real_T d121;
  real_T d122;
  real_T d123;
  real_T tmp_tmp_j;
  real_T tmp_tmp_i;
  real_T tmp_tmp_h;
  real_T tmp_tmp_n;
  real_T tmp_tmp_o;
  real_T d124;
  real_T tmp_tmp_c;
  real_T tmp_tmp_b;
  real_T tmp_tmp_e;
  real_T tmp_tmp_dd;
  real_T d125;
  real_T tmp_tmp_ik;
  real_T tmp_tmp_g;
  real_T tmp_tmp_nn;
  real_T tmp_tmp_l;
  real_T tmp_tmp_ce;
  real_T D47_tmp_n;
  real_T tmp_tmp_p;
  real_T d126;
  real_T d127;
  real_T d128;
  real_T d129;
  real_T d130;
  real_T d131;
  real_T d132;
  real_T d133;
  real_T d134;
  real_T d135;
  real_T d136;
  real_T d137;
  real_T d138;
  real_T d139;
  real_T d140;
  real_T d141;
  real_T d142;
  real_T d143;
  real_T d144;
  real_T d145;
  real_T d146;
  real_T d147;
  real_T d148;
  real_T d149;
  real_T d150;
  real_T d151;
  real_T d152;
  real_T d153;
  real_T d154;
  real_T d155;
  real_T d156;
  real_T d157;
  real_T d158;
  real_T d159;
  real_T d160;
  real_T tmp_tmp_dk;
  real_T d161;
  real_T d162;
  real_T d163;
  real_T d164;
  real_T d165;
  real_T tmp_tmp_oi;
  real_T tmp_tmp_jr;
  real_T tmp_tmp_c2;
  real_T D24_tmp_h;
  real_T D24_tmp_d;
  real_T rtb_ginv_tmp_c;
  real_T rtb_ginv_tmp_pw;
  real_T rtb_ginv_tmp_tmp_pi;
  real_T rtb_ginv_tmp_tmp_a;
  real_T rtb_ginv_tmp_ow;
  real_T D18_tmp;
  real_T d166;
  real_T D17_tmp_j;
  real_T D17_tmp_p;
  real_T D17_tmp_ob;
  real_T D17_tmp_tmp;
  real_T D17_tmp_tmp_l;
  real_T D56_tmp_tmp_k;
  real_T D56_tmp_tmp_j;
  real_T D56_tmp_tmp_fz;
  real_T D56_tmp_tmp_cm;
  real_T D56_tmp_tmp_fq;
  real_T D56_tmp_tmp_n;
  real_T D56_tmp_tmp_i;
  real_T D56_tmp_tmp_l4;
  real_T D56_tmp_tmp_i3;
  real_T D56_tmp_tmp_k1;
  real_T D56_tmp_tmp_fc;
  real_T D56_tmp_tmp_al;
  real_T D56_tmp_tmp_d;
  real_T D56_tmp_tmp_ey;
  real_T D56_tmp_tmp_eh;
  real_T D56_tmp_tmp_b;
  real_T D56_tmp_tmp_a0;
  real_T D56_tmp_tmp_il;
  real_T d167;
  real_T d168;
  real_T d169;
  real_T d170;
  real_T d171;
  real_T d172;
  real_T tmp_tmp_f;
  real_T tmp_tmp_ji;
  real_T tmp_tmp_oo;
  real_T tmp_tmp_fr;
  real_T tmp_tmp_oy;
  real_T d173;
  real_T tmp_tmp_ln;
  real_T tmp_tmp_lu;
  real_T tmp_tmp_gf;
  real_T tmp_tmp_d4;
  real_T tmp_tmp_dv;
  real_T tmp_tmp_jo;
  real_T tmp_tmp_f1;
  real_T tmp_tmp_js;
  real_T d174;
  real_T d175;
  real_T d176;
  real_T tmp_tmp_ho;
  real_T d177;
  real_T d178;
  real_T d179;
  real_T d180;
  real_T d181;
  real_T d182;
  real_T d183;
  real_T d184;
  real_T d185;
  real_T d186;
  real_T d187;
  real_T d188;
  real_T d189;
  real_T d190;
  real_T d191;
  real_T d192;
  real_T d193;
  real_T d194;
  real_T d195;
  real_T d196;
  real_T d197;
  real_T d198;
  real_T d199;
  real_T D14_tmp_cf;
  real_T finalTime;
  real_T xtmp;
  real_T waypoints_idx_0;
  real_T obj_PPStruct;
  real_T obj_PPStruct_n;
  real_T obj_PPStruct_k;
  real_T obj_PPStruct_tmp;
  real_T d200;
  real_T d201;
  real_T smax_a;
  real_T s_f;
  int32_T kAcol;
  int32_T jj;
  int32_T c_j;
  int32_T a;
};

// Block states (default storage) for system '<Root>'
struct DW_DifAndCtrl_T {
  robotics_slcore_internal_bloc_T obj; // '<S3>/Polynomial Trajectory'
};

// Continuous states (default storage)
struct X_DifAndCtrl_T {
  real_T Integrator_CSTATE[8];         // '<S4>/Integrator'
  real_T Integrator1_CSTATE[8];        // '<S4>/Integrator1'
};

// State derivatives (default storage)
struct XDot_DifAndCtrl_T {
  real_T Integrator_CSTATE[8];         // '<S4>/Integrator'
  real_T Integrator1_CSTATE[8];        // '<S4>/Integrator1'
};

// State disabled
struct XDis_DifAndCtrl_T {
  boolean_T Integrator_CSTATE[8];      // '<S4>/Integrator'
  boolean_T Integrator1_CSTATE[8];     // '<S4>/Integrator1'
};

#ifndef ODE4_INTG
#define ODE4_INTG

// ODE4 Integration Data
struct ODE4_IntgData {
  real_T *y;                           // output
  real_T *f[4];                        // derivatives
};

#endif

// External inputs (root inport signals with default storage)
struct ExtU_DifAndCtrl_T {
  real_T Positions[8];                 // '<Root>/Position'
};

// External outputs (root outports fed by signals with default storage)
struct ExtY_DifAndCtrl_T {
  real_T ForcesAndTorques[8];          // '<Root>/ForcesAndTorques'
};

// Parameters (default storage)
struct P_DifAndCtrl_T_ {
  struct_bwZkdZIRabTIxeUCMoFaDG Differentiator;// Variable: Differentiator
                                                  //  Referenced by:
                                                  //    '<S4>/G1'
                                                  //    '<S4>/G2'
                                                  //    '<S4>/Q1'
                                                  //    '<S4>/Q2'
                                                  //    '<S4>/Q3'
                                                  //    '<S4>/Q4'
                                                  //    '<S4>/Q5'
                                                  //    '<S4>/Q6'

  struct_Z1yy0b1SiRejj6ODUGxXCE HexaConstants;// Variable: HexaConstants
                                                 //  Referenced by: '<S9>/MATLAB Function1'

  struct_JL8g2iM4Lw6J1bY0kTxLfE ArmConstants;// Variable: ArmConstants
                                                //  Referenced by: '<S9>/MATLAB Function1'

  struct_8gU0TGGHeyi782Q5TKcTyF Trajectory;// Variable: Trajectory
                                              //  Referenced by: '<S3>/Polynomial Trajectory'

  struct_CKTAE3dLo2KptrTZY712sF PID;   // Variable: PID
                                          //  Referenced by:
                                          //    '<S11>/Kd'
                                          //    '<S11>/Kp'

  real_T PolynomialTrajectory_VelocityBo[16];
                              // Expression: zeros( size(Trajectory.Waypoints) )
                                 //  Referenced by: '<S3>/Polynomial Trajectory'

  real_T Integrator_IC[8];            // Expression: [0; 0; 0.28; 0; 0; 0; 0; 0]
                                         //  Referenced by: '<S4>/Integrator'

  real_T Integrator1_IC[8];            // Expression: [0; 0; 0; 0; 0; 0; 0; 0]
                                          //  Referenced by: '<S4>/Integrator1'

};

// Real-time Model Data Structure
using odeFSubArray = real_T[16];
struct tag_RTM_DifAndCtrl_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  B_DifAndCtrl_T *blockIO;
  X_DifAndCtrl_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_DifAndCtrl_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[16];
  real_T odeF[4][16];
  ODE4_IntgData intgData;
  DW_DifAndCtrl_T *dwork;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;

  B_DifAndCtrl_T* getBlockIO() const;
  void setBlockIO(B_DifAndCtrl_T* aBlockIO);
  XDis_DifAndCtrl_T* getContStateDisabled() const;
  void setContStateDisabled(XDis_DifAndCtrl_T* aContStateDisabled);
  const char_T** getErrorStatusPtr();
  X_DifAndCtrl_T* getContStates() const;
  void setContStates(X_DifAndCtrl_T* aContStates);
  boolean_T getStopRequested() const;
  void setStopRequested(boolean_T aStopRequested);
  ODE4_IntgData getIntgData() const;
  void setIntgData(ODE4_IntgData aIntgData);
  boolean_T getDerivCacheNeedsReset() const;
  void setDerivCacheNeedsReset(boolean_T aDerivCacheNeedsReset);
  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const aErrorStatus);
  boolean_T getContTimeOutputInconsistentWithStateAtMajorStepFlag() const;
  void setContTimeOutputInconsistentWithStateAtMajorStepFlag(boolean_T
    aContTimeOutputInconsistentWithStateAtMajorStepFlag);
  boolean_T isMajorTimeStep() const;
  const odeFSubArray* getOdeF() const;
  boolean_T isMinorTimeStep() const;
  const real_T* getOdeY() const;
  int_T* getPeriodicContStateIndices() const;
  void setPeriodicContStateIndices(int_T* aPeriodicContStateIndices);
  time_T* getTPtr() const;
  void setTPtr(time_T* aTPtr);
  real_T* getPeriodicContStateRanges() const;
  void setPeriodicContStateRanges(real_T* aPeriodicContStateRanges);
  DW_DifAndCtrl_T* getRootDWork() const;
  void setRootDWork(DW_DifAndCtrl_T* aRootDWork);
  boolean_T* getStopRequestedPtr();
  time_T** getTPtrPtr();
  time_T getTStart() const;
  boolean_T getZCCacheNeedsReset() const;
  void setZCCacheNeedsReset(boolean_T aZCCacheNeedsReset);
  real_T* getdX() const;
  void setdX(real_T* adX);
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_DifAndCtrl_T DifAndCtrl_P;

#ifdef __cplusplus

}

#endif

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void DifAndCtrl_initialize(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M,
    ExtU_DifAndCtrl_T *DifAndCtrl_U, ExtY_DifAndCtrl_T *DifAndCtrl_Y);
  extern void DifAndCtrl_step(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M,
    ExtU_DifAndCtrl_T *DifAndCtrl_U, ExtY_DifAndCtrl_T *DifAndCtrl_Y);
  extern void DifAndCtrl_terminate(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M);

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

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
//  '<Root>' : 'DifAndCtrl'
//  '<S1>'   : 'DifAndCtrl/DifferentiatorHITL'
//  '<S2>'   : 'DifAndCtrl/PDHITL'
//  '<S3>'   : 'DifAndCtrl/TrajectoryUAM'
//  '<S4>'   : 'DifAndCtrl/DifferentiatorHITL/Fixed-Time Differentiator1'
//  '<S5>'   : 'DifAndCtrl/DifferentiatorHITL/Fixed-Time Differentiator1/U power x1'
//  '<S6>'   : 'DifAndCtrl/DifferentiatorHITL/Fixed-Time Differentiator1/U power x2'
//  '<S7>'   : 'DifAndCtrl/DifferentiatorHITL/Fixed-Time Differentiator1/U power x3'
//  '<S8>'   : 'DifAndCtrl/DifferentiatorHITL/Fixed-Time Differentiator1/U power x4'
//  '<S9>'   : 'DifAndCtrl/PDHITL/Get f(x) and g(x)^-1'
//  '<S10>'  : 'DifAndCtrl/PDHITL/GetBInvMatrix'
//  '<S11>'  : 'DifAndCtrl/PDHITL/PID'
//  '<S12>'  : 'DifAndCtrl/PDHITL/Get f(x) and g(x)^-1/MATLAB Function1'
//  '<S13>'  : 'DifAndCtrl/PDHITL/PID/Obtain Error'
//  '<S14>'  : 'DifAndCtrl/PDHITL/PID/PD Controller'

#endif                                 // DIFANDCTRL_H_

//
// File trailer for generated code.
//
// [EOF]
//
