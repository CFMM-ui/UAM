//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: DifAndCtrl.h
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
#ifndef DIFANDCTRL_H_
#define DIFANDCTRL_H_
#include "rtwtypes.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "model_reference_types.h"
#include <string.h>
#include <stddef.h>
#ifndef DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_
#define DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_

struct struct_8iq6TggEG7Fvgh27g9ENz
{
  real_T T1max;
  real_T T2max;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_JL8G2IM4LW6J1BY0KTXLFE_
#define DEFINED_TYPEDEF_FOR_STRUCT_JL8G2IM4LW6J1BY0KTXLFE_

struct struct_JL8g2iM4Lw6J1bY0kTxLfE
{
  real_T l1_dim;
  real_T l2_dim;
  real_T Hexa_to_joint_L;
  real_T Mass1;
  real_T Mass2;
  real_T Inertia1[9];
  real_T Inertia2[9];
  real_T MC1;
  real_T MC2;
  struct_8iq6TggEG7Fvgh27g9ENz Servos;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_Z1YY0B1SIREJJ6ODUGXXCE_
#define DEFINED_TYPEDEF_FOR_STRUCT_Z1YY0B1SIREJJ6ODUGXXCE_

struct struct_Z1yy0b1SiRejj6ODUGxXCE
{
  real_T Mass;
  real_T Inertia[9];
  real_T invallo[36];
  real_T kT;
};

#endif

#ifndef STRUCT_SSYZ0BPTOZBXQA0QQ45VSPE_DIFAN_T
#define STRUCT_SSYZ0BPTOZBXQA0QQ45VSPE_DIFAN_T

struct ssyz0BpTozbXQa0qq45VsPE_DifAn_T
{
  real_T breaks[20];
  real_T coefs[608];
};

#endif                                // STRUCT_SSYZ0BPTOZBXQA0QQ45VSPE_DIFAN_T

#ifndef STRUCT_CELL_WRAP_DIFANDCTRL_T
#define STRUCT_CELL_WRAP_DIFANDCTRL_T

struct cell_wrap_DifAndCtrl_T
{
  uint32_T f1[8];
};

#endif                                 // STRUCT_CELL_WRAP_DIFANDCTRL_T

#ifndef STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T
#define STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

struct robotics_slcore_internal_bloc_T
{
  boolean_T tunablePropertyChanged[5];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_DifAndCtrl_T inputVarSize;
  real_T Waypoints[144];
  real_T TimePoints[18];
  real_T VelocityBoundaryCondition[144];
  real_T AccelerationBoundaryCondition[10];
  ssyz0BpTozbXQa0qq45VsPE_DifAn_T PPStruct;
  ssyz0BpTozbXQa0qq45VsPE_DifAn_T PPDStruct;
  ssyz0BpTozbXQa0qq45VsPE_DifAn_T PPDDStruct;
  boolean_T PPFormUpdatedNeeded;
};

#endif                                // STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

// Class declaration for model DifAndCtrl
class DifAndCtrl
{
  // public data and function members
 public:
  // Block signals and states (default storage) for model 'DifAndCtrl'
  struct DW_DifAndCtrl_T {
    robotics_slcore_internal_bloc_T obj;// '<S3>/Polynomial Trajectory'
    real_T DiscreteTimeIntegrator_DSTATE[8];// '<S4>/Discrete-Time Integrator'
    real_T DiscreteTimeIntegrator2_DSTATE[8];// '<S4>/Discrete-Time Integrator2' 
    real_T coefMat[544];
    real_T coefsWithFlatStart[576];
    real_T x[64];
    real_T ginv[64];                   // '<S9>/MATLAB Function1'
    real_T BMinv[64];                  // '<S2>/GetBInvMatrix'
    real_T dv[64];
    real_T b_A[64];
    real_T fx[8];                      // '<S9>/MATLAB Function1'
    real_T uv[8];                      // '<S4>/U power x3'
    real_T e_hat[8];                   // '<S4>/Sum1'
    real_T Sum3[8];                    // '<S4>/Sum3'
    real_T rtb_Sum3_tmp[8];
    real_T dv1[8];
    real_T dv2[8];
    real_T coeffMat[32];
    real_T breaksWithFlatStart[19];
    real_T b_coeffVec[4];
    real_T D14;
    real_T D15;
    real_T D16;
    real_T D17;
    real_T D18;
    real_T D24;
    real_T D25;
    real_T D27;
    real_T D34;
    real_T D35;
    real_T D37;
    real_T D38;
    real_T D46;
    real_T D47;
    real_T D56;
    real_T D57;
    real_T w_a;
    real_T x_a;
    real_T ab_a;
    real_T smax;
    real_T s;
    real_T D14_tmp;
    real_T D14_tmp_m;
    real_T D14_tmp_c;
    real_T D14_tmp_k;
    real_T D14_tmp_cx;
    real_T D14_tmp_b;
    real_T D14_tmp_p;
    real_T D14_tmp_cv;
    real_T D14_tmp_f;
    real_T D15_tmp;
    real_T D15_tmp_g;
    real_T D15_tmp_g1;
    real_T D34_tmp;
    real_T D34_tmp_m;
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
    real_T D46_tmp_bj;
    real_T D56_tmp_j;
    real_T D56_tmp_f;
    real_T D56_tmp_a;
    real_T D56_tmp_ju;
    real_T rtb_ginv_tmp;
    real_T D56_tmp_jz;
    real_T D56_tmp_o4;
    real_T D56_tmp_ny;
    real_T D56_tmp_i;
    real_T D14_tmp_tmp;
    real_T D14_tmp_o;
    real_T D15_tmp_tmp;
    real_T D14_tmp_n;
    real_T D14_tmp_m3;
    real_T D16_tmp;
    real_T D14_tmp_cz;
    real_T D17_tmp;
    real_T D17_tmp_m;
    real_T D17_tmp_m3;
    real_T D17_tmp_j;
    real_T D24_tmp;
    real_T D17_tmp_h;
    real_T D17_tmp_c;
    real_T D15_tmp_c;
    real_T D24_tmp_p;
    real_T D17_tmp_p;
    real_T D17_tmp_tmp;
    real_T D17_tmp_tmp_a;
    real_T D17_tmp_tmp_e;
    real_T D16_tmp_tmp;
    real_T D27_tmp;
    real_T D15_tmp_tmp_a;
    real_T D34_tmp_a;
    real_T D34_tmp_i;
    real_T D46_tmp_tmp;
    real_T D46_tmp_tmp_l;
    real_T D46_tmp_tmp_o;
    real_T D46_tmp_tmp_o2;
    real_T D47_tmp;
    real_T D56_tmp_tmp;
    real_T D56_tmp_tmp_i;
    real_T D56_tmp_tmp_f;
    real_T D56_tmp_tmp_iz;
    real_T D56_tmp_tmp_ff;
    real_T D56_tmp_tmp_g;
    real_T D56_tmp_tmp_c;
    real_T D56_tmp_o3;
    real_T D56_tmp_lm;
    real_T D45_tmp;
    real_T D45_tmp_m;
    real_T D24_tmp_m;
    real_T w_a_tmp;
    real_T D46_tmp_c;
    real_T D46_tmp_f;
    real_T D46_tmp_p4;
    real_T D46_tmp_e1;
    real_T D46_tmp_o;
    real_T D46_tmp_h;
    real_T D46_tmp_l5;
    real_T D46_tmp_h2;
    real_T D46_tmp_m;
    real_T D46_tmp_mc;
    real_T D46_tmp_h3;
    real_T D46_tmp_cs;
    real_T D46_tmp_tmp_k;
    real_T D48_tmp;
    real_T D56_tmp_tmp_tmp;
    real_T D47_tmp_p;
    real_T D47_tmp_px;
    real_T rtb_ginv_tmp_p;
    real_T rtb_ginv_tmp_a;
    real_T rtb_ginv_tmp_j;
    real_T rtb_ginv_tmp_e;
    real_T rtb_ginv_tmp_o;
    real_T rtb_ginv_tmp_b;
    real_T D56_tmp_tmp_a;
    real_T D56_tmp_tmp_g2;
    real_T D46_tmp_tmp_e;
    real_T D56_tmp_tmp_fi;
    real_T D56_tmp_tmp_h;
    real_T D46_tmp_tmp_ei;
    real_T D46_tmp_tmp_c;
    real_T D46_tmp_tmp_a;
    real_T D46_tmp_tmp_d;
    real_T D46_tmp_tmp_af;
    real_T rtb_ginv_tmp_tmp;
    real_T rtb_ginv_tmp_tmp_p;
    real_T D14_tmp_ms;
    real_T D14_tmp_o3;
    real_T D14_tmp_nh;
    real_T D34_tmp_l;
    real_T D14_tmp_pe;
    real_T D16_tmp_p;
    real_T rtb_ginv_tmp_tmp_f;
    real_T D16_tmp_i;
    real_T D16_tmp_o;
    real_T D16_tmp_k;
    real_T D37_tmp;
    real_T d;
    real_T d1;
    real_T D17_tmp_tmp_i;
    real_T D27_tmp_o;
    real_T D27_tmp_m;
    real_T d2;
    real_T d3;
    real_T d4;
    real_T d5;
    real_T d6;
    real_T d7;
    real_T D15_tmp_tmp_c;
    real_T D15_tmp_tmp_f;
    real_T d8;
    real_T d9;
    real_T D14_tmp_tmp_h;
    real_T D14_tmp_tmp_m;
    real_T d10;
    real_T d11;
    real_T d12;
    real_T D56_tmp_ad;
    real_T D56_tmp_k;
    real_T D56_tmp_p;
    real_T D56_tmp_bp;
    real_T D56_tmp_c;
    real_T D56_tmp_nb;
    real_T D56_tmp_ij;
    real_T D56_tmp_m;
    real_T d13;
    real_T d14;
    real_T d15;
    real_T d16;
    real_T d17;
    real_T d18;
    real_T d19;
    real_T d20;
    real_T d21;
    real_T d22;
    real_T d23;
    real_T d24;
    real_T d25;
    real_T d26;
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
    real_T D56_tmp_jg;
    real_T D56_tmp_e;
    real_T rtb_ginv_tmp_m;
    real_T rtb_ginv_tmp_m0;
    real_T rtb_ginv_tmp_jg;
    real_T rtb_ginv_tmp_f;
    real_T D45_tmp_a;
    real_T d78;
    real_T d79;
    real_T d80;
    real_T d81;
    real_T d82;
    real_T d83;
    real_T d84;
    real_T tmp_tmp;
    real_T d85;
    real_T tmp_tmp_g;
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
    real_T d99;
    real_T d100;
    real_T d101;
    real_T tmp_tmp_n;
    real_T tmp_tmp_d;
    real_T tmp_tmp_na;
    real_T tmp_tmp_c;
    real_T tmp_tmp_f;
    real_T d102;
    real_T tmp_tmp_p;
    real_T tmp_tmp_p2;
    real_T tmp_tmp_nj;
    real_T tmp_tmp_k;
    real_T tmp_tmp_n3;
    real_T tmp_tmp_o;
    real_T d103;
    real_T tmp_tmp_gg;
    real_T tmp_tmp_cq;
    real_T tmp_tmp_cj;
    real_T tmp_tmp_m;
    real_T tmp_tmp_j;
    real_T D48_tmp_k;
    real_T D47_tmp_m;
    real_T tmp_tmp_pr;
    real_T d104;
    real_T d105;
    real_T d106;
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
    real_T d124;
    real_T d125;
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
    real_T tmp_tmp_dz;
    real_T d139;
    real_T d140;
    real_T d141;
    real_T d142;
    real_T d143;
    real_T tmp_tmp_g4;
    real_T d144;
    real_T tmp_tmp_c3;
    real_T tmp_tmp_cx;
    real_T rtb_ginv_tmp_i;
    real_T rtb_ginv_tmp_d;
    real_T rtb_ginv_tmp_g;
    real_T rtb_ginv_tmp_l;
    real_T tmp_tmp_f1;
    real_T rtb_ginv_tmp_db;
    real_T rtb_ginv_tmp_jr;
    real_T rtb_ginv_tmp_tmp_i;
    real_T D24_tmp_h;
    real_T D24_tmp_n;
    real_T rtb_ginv_tmp_o3;
    real_T rtb_ginv_tmp_c;
    real_T rtb_ginv_tmp_tmp_b;
    real_T rtb_ginv_tmp_tmp_e;
    real_T rtb_ginv_tmp_dd;
    real_T D18_tmp;
    real_T d145;
    real_T D17_tmp_i;
    real_T D17_tmp_g;
    real_T D17_tmp_n;
    real_T D17_tmp_tmp_l;
    real_T D17_tmp_tmp_c;
    real_T D56_tmp_tmp_n;
    real_T D56_tmp_tmp_p;
    real_T D56_tmp_tmp_d;
    real_T D56_tmp_tmp_o;
    real_T D56_tmp_tmp_j;
    real_T D56_tmp_tmp_c2;
    real_T D56_tmp_tmp_hp;
    real_T D56_tmp_tmp_da;
    real_T D56_tmp_tmp_c5;
    real_T D56_tmp_tmp_pw;
    real_T D56_tmp_tmp_pi;
    real_T D56_tmp_tmp_a4;
    real_T D56_tmp_tmp_ow;
    real_T D56_tmp_tmp_jw;
    real_T D56_tmp_tmp_pie;
    real_T D56_tmp_tmp_ob;
    real_T D56_tmp_tmp_l;
    real_T D56_tmp_tmp_k;
    real_T d146;
    real_T tmp_tmp_jk;
    real_T tmp_tmp_fz;
    real_T tmp_tmp_cm;
    real_T tmp_tmp_fq;
    real_T tmp_tmp_nl;
    real_T d147;
    real_T d148;
    real_T d149;
    real_T d150;
    real_T d151;
    real_T tmp_tmp_i;
    real_T tmp_tmp_l;
    real_T tmp_tmp_i3;
    real_T tmp_tmp_k1;
    real_T tmp_tmp_fc;
    real_T tmp_tmp_a;
    real_T tmp_tmp_d4;
    real_T d152;
    real_T tmp_tmp_e;
    real_T tmp_tmp_eh;
    real_T tmp_tmp_b;
    real_T tmp_tmp_a0;
    real_T tmp_tmp_il;
    real_T tmp_tmp_fa;
    real_T tmp_tmp_ji;
    real_T tmp_tmp_oo;
    real_T d153;
    real_T d154;
    real_T d155;
    real_T d156;
    real_T d157;
    real_T d158;
    real_T d159;
    real_T d160;
    real_T d161;
    real_T d162;
    real_T d163;
    real_T d164;
    real_T d165;
    real_T d166;
    real_T d167;
    real_T d168;
    real_T d169;
    real_T d170;
    real_T d171;
    real_T d172;
    real_T d173;
    real_T d174;
    real_T d175;
    real_T d176;
    real_T d177;
    real_T d178;
    real_T d179;
    real_T d180;
    real_T d181;
    real_T tmp_tmp_fr;
    real_T smax_o;
    real_T s_l;
    real_T finalTime;
    real_T waypoints_idx_0;
    real_T waypoints_idx_1;
    real_T coefMat_tmp;
    int32_T jj;
    int32_T ix;
    int32_T d_k;
    int32_T b_ix;
    int8_T p[8];
    int8_T ipiv[8];
    int8_T ipiv_l[8];
    boolean_T objisempty;              // '<S3>/Polynomial Trajectory'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_DifAndCtrl_T {
    const rtTimingBridge *timingBridge;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      int_T mdlref_GlobalTID[1];
    } Timing;

    time_T getClockTickH0() const;
    time_T getClockTick0() const;
    boolean_T isSampleHit(int32_T sti) const;
    time_T getT() const;
  };

  // Constant parameters (default storage)
  struct ConstP_DifAndCtrl_T {
    // Expression: HexaConstants
    //  Referenced by: '<S9>/MATLAB Function1'

    struct_Z1yy0b1SiRejj6ODUGxXCE MATLABFunction1_HexaConstants;

    // Expression: ArmConstants
    //  Referenced by: '<S9>/MATLAB Function1'

    struct_JL8g2iM4Lw6J1bY0kTxLfE MATLABFunction1_ArmConstants;
  };

  // model initialize function
  void initialize();

  // Initial conditions function
  void init();

  // model step function
  void step(const real_T arg_Position[8], real_T arg_ForcesAndTorques[8]);

  // Real-Time Model get method
  DifAndCtrl::RT_MODEL_DifAndCtrl_T * getRTM();

  // member function to initialize Real-Time model
  void initializeRTM(const rtTimingBridge *timingBridge, int_T mdlref_TID0);

  // Constructor
  DifAndCtrl();

  // Destructor
  ~DifAndCtrl();

  // private data and function members
 private:
  // Block states
  DW_DifAndCtrl_T DifAndCtrl_DW;

  // private member function(s) for subsystem '<S4>/U power x1'
  static void DifAndCtrl_Upowerx1(const real_T rtu_u[8], const real_T rtu_v[8],
    real_T rty_uv[8]);

  // private member function(s) for subsystem '<Root>/TmpModelReferenceSubsystem'
  void PolyTrajSys_regeneratePPFormFro(robotics_slcore_internal_bloc_T *obj,
    const real_T waypoints[144], const real_T timeData[18]);
  void DifAndCtrl_mldivide_0QKHZcd4_c(const real_T A[64], real_T B[8]);
  void DifAndCtrl_ppval(const real_T pp_breaks[20], const real_T pp_coefs[608],
                        real_T x, real_T v[8]);

  // Private member function to set up the global timing engine
  void setupGlobalTimingEngine(const rtTimingBridge *timingBridge, int_T
    mdlref_TID0);

  // Real-Time Model
  RT_MODEL_DifAndCtrl_T DifAndCtrl_M;
};

// Constant parameters (default storage)
extern const DifAndCtrl::ConstP_DifAndCtrl_T DifAndCtrl_ConstP;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S4>/Scope' : Unused code path elimination
//  Block '<S4>/Scope1' : Unused code path elimination
//  Block '<S4>/Scope2' : Unused code path elimination
//  Block '<S4>/Scope3' : Unused code path elimination
//  Block '<S4>/Scope4' : Unused code path elimination
//  Block '<S4>/Scope5' : Unused code path elimination


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
