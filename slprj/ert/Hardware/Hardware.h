//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Hardware.h
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
#ifndef HARDWARE_H_
#define HARDWARE_H_
#include "rtwtypes.h"
#include "Hardware_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "model_reference_types.h"

// Block signals for model 'Hardware'
struct B_Hardware_c_T {
  real_T x[64];
  real_T ginv[64];                     // '<S9>/MATLAB Function1'
  real_T BMinv[64];                    // '<S2>/GetBInvMatrix'
  real_T dv[64];
  real_T coefsWithFlatStart[64];
  real_T b_A[64];
  real_T coefMat[32];
  real_T coeffMat[32];
  real_T fx[8];                        // '<S9>/MATLAB Function1'
  real_T uv[8];                        // '<S4>/U power x3'
  real_T e_hat[8];                     // '<S4>/Sum1'
  real_T Product3[8];                  // '<S4>/Product3'
  real_T Product4[8];                  // '<S4>/Product4'
  real_T rtb_Product3_tmp[8];
  real_T dv1[8];
  int8_T p[8];
  int8_T ipiv[8];
  int8_T ipiv_m[8];
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
  real_T smax;
  real_T s;
  real_T D14_tmp;
  real_T D14_tmp_c;
  real_T D14_tmp_k;
  real_T D14_tmp_cx;
  real_T D14_tmp_b;
  real_T D14_tmp_p;
  real_T D14_tmp_cv;
  real_T D14_tmp_f;
  real_T D14_tmp_g;
  real_T D15_tmp;
  real_T D15_tmp_g;
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
  real_T D46_tmp_bj;
  real_T rtb_ginv_tmp;
  real_T D56_tmp_j;
  real_T D56_tmp_f;
  real_T D56_tmp_a;
  real_T D56_tmp_ju;
  real_T d;
  real_T d1;
  real_T d2;
  real_T d3;
  real_T d4;
  real_T d5;
  real_T rtb_ginv_tmp_j;
  real_T D56_tmp_o4;
  real_T D56_tmp_ny;
  real_T D56_tmp_i;
  real_T D56_tmp_oy;
  real_T d6;
  real_T d7;
  real_T D14_tmp_tmp;
  real_T D14_tmp_n;
  real_T D14_tmp_m;
  real_T D14_tmp_cz;
  real_T D14_tmp_md;
  real_T D15_tmp_tmp;
  real_T D14_tmp_m3;
  real_T D14_tmp_j;
  real_T D14_tmp_h;
  real_T D16_tmp;
  real_T D14_tmp_c0;
  real_T D14_tmp_tmp_c;
  real_T D17_tmp;
  real_T D17_tmp_p;
  real_T D17_tmp_p5;
  real_T D17_tmp_a;
  real_T D24_tmp;
  real_T D17_tmp_e;
  real_T D17_tmp_ax;
  real_T D15_tmp_a;
  real_T D24_tmp_i;
  real_T D17_tmp_l;
  real_T D17_tmp_tmp;
  real_T D16_tmp_tmp;
  real_T D17_tmp_tmp_o;
  real_T D17_tmp_tmp_o2;
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
  real_T rtb_ginv_tmp_tmp;
  real_T rtb_ginv_tmp_tmp_n;
  real_T rtb_ginv_tmp_tmp_l;
  real_T D47_tmp_pe;
  real_T D46_tmp_tmp_p;
  real_T D47_tmp_f;
  real_T rtb_ginv_tmp_i;
  real_T rtb_ginv_tmp_o;
  real_T rtb_ginv_tmp_k;
  real_T rtb_ginv_tmp_ie;
  real_T D47_tmp_o;
  real_T D48_tmp_tmp;
  real_T D56_tmp_tmp_m;
  real_T D56_tmp_tmp_c;
  real_T D46_tmp_tmp_fb;
  real_T D56_tmp_tmp_hc;
  real_T D56_tmp_tmp_m4;
  real_T D46_tmp_tmp_a;
  real_T D46_tmp_tmp_k;
  real_T D46_tmp_tmp_pc;
  real_T D46_tmp_tmp_b;
  real_T D46_tmp_tmp_c;
  real_T D14_tmp_nb;
  real_T D14_tmp_i;
  real_T D14_tmp_my;
  real_T D34_tmp_j;
  real_T D14_tmp_e;
  real_T D16_tmp_m;
  real_T D16_tmp_m0;
  real_T D16_tmp_j;
  real_T d8;
  real_T D16_tmp_f;
  real_T d9;
  real_T D37_tmp;
  real_T d10;
  real_T d11;
  real_T d12;
  real_T D17_tmp_tmp_a;
  real_T D27_tmp;
  real_T D27_tmp_g;
  real_T d13;
  real_T D46_tmp_tmp_n;
  real_T D46_tmp_d3;
  real_T d14;
  real_T d15;
  real_T d16;
  real_T d17;
  real_T d18;
  real_T D15_tmp_tmp_n;
  real_T D15_tmp_tmp_c;
  real_T d19;
  real_T D14_tmp_tmp_f;
  real_T D14_tmp_tmp_p;
  real_T d20;
  real_T d21;
  real_T d22;
  real_T D56_tmp_p;
  real_T D56_tmp_nj;
  real_T D56_tmp_k;
  real_T D56_tmp_n3;
  real_T D56_tmp_oyh;
  real_T D56_tmp_g;
  real_T D56_tmp_c;
  real_T D56_tmp_cj;
  real_T d23;
  real_T d24;
  real_T d25;
  real_T d26;
  real_T D46_tmp_tmp_m1;
  real_T d27;
  real_T D46_tmp_tmp_j;
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
  real_T D46_tmp_kn;
  real_T D46_tmp_mx;
  real_T D46_tmp_pr;
  real_T D46_tmp_tmp_d;
  real_T D47_tmp_g;
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
  real_T d99;
  real_T D56_tmp_c3;
  real_T D56_tmp_cx;
  real_T rtb_ginv_tmp_if;
  real_T rtb_ginv_tmp_d;
  real_T rtb_ginv_tmp_g;
  real_T rtb_ginv_tmp_l;
  real_T d100;
  real_T d101;
  real_T d102;
  real_T d103;
  real_T d104;
  real_T d105;
  real_T d106;
  real_T tmp_tmp;
  real_T d107;
  real_T tmp_tmp_f;
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
  real_T tmp_tmp_d;
  real_T tmp_tmp_j;
  real_T tmp_tmp_i;
  real_T tmp_tmp_h;
  real_T tmp_tmp_n;
  real_T d125;
  real_T tmp_tmp_o;
  real_T tmp_tmp_c;
  real_T tmp_tmp_b;
  real_T tmp_tmp_e;
  real_T d126;
  real_T tmp_tmp_dd;
  real_T tmp_tmp_ik;
  real_T tmp_tmp_g;
  real_T tmp_tmp_nn;
  real_T tmp_tmp_l;
  real_T D47_tmp_c;
  real_T tmp_tmp_nc;
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
  real_T d161;
  real_T tmp_tmp_p;
  real_T d162;
  real_T d163;
  real_T d164;
  real_T d165;
  real_T d166;
  real_T tmp_tmp_dk;
  real_T tmp_tmp_oi;
  real_T tmp_tmp_jr;
  real_T D24_tmp_c;
  real_T D24_tmp_h;
  real_T rtb_ginv_tmp_da;
  real_T rtb_ginv_tmp_c;
  real_T rtb_ginv_tmp_tmp_p;
  real_T rtb_ginv_tmp_tmp_pi;
  real_T rtb_ginv_tmp_a;
  real_T D18_tmp;
  real_T d167;
  real_T D17_tmp_o;
  real_T D17_tmp_j;
  real_T D17_tmp_pi;
  real_T D17_tmp_tmp_ob;
  real_T D17_tmp_tmp_l;
  real_T D56_tmp_tmp_k;
  real_T D56_tmp_tmp_j;
  real_T D56_tmp_tmp_f;
  real_T D56_tmp_tmp_cm;
  real_T D56_tmp_tmp_fq;
  real_T D56_tmp_tmp_n;
  real_T D56_tmp_tmp_i;
  real_T D56_tmp_tmp_l4;
  real_T D56_tmp_tmp_i3;
  real_T D56_tmp_tmp_k1;
  real_T D56_tmp_tmp_fc;
  real_T D56_tmp_tmp_a;
  real_T D56_tmp_tmp_d;
  real_T D56_tmp_tmp_ey;
  real_T D56_tmp_tmp_eh;
  real_T D56_tmp_tmp_b;
  real_T D56_tmp_tmp_a0;
  real_T D56_tmp_tmp_il;
  real_T d168;
  real_T d169;
  real_T d170;
  real_T d171;
  real_T d172;
  real_T d173;
  real_T tmp_tmp_fa;
  real_T tmp_tmp_ji;
  real_T tmp_tmp_oo;
  real_T tmp_tmp_fr;
  real_T tmp_tmp_oy;
  real_T d174;
  real_T tmp_tmp_ln;
  real_T tmp_tmp_lu;
  real_T tmp_tmp_gf;
  real_T tmp_tmp_d4;
  real_T tmp_tmp_dv;
  real_T tmp_tmp_jo;
  real_T tmp_tmp_f1;
  real_T tmp_tmp_js;
  real_T d175;
  real_T d176;
  real_T d177;
  real_T tmp_tmp_ho;
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
  real_T d200;
  real_T D14_tmp_cf;
  real_T finalTime;
  real_T xtmp;
  real_T waypoints_idx_0;
  real_T obj_PPStruct;
  real_T obj_PPStruct_n;
  real_T obj_PPStruct_k;
  real_T obj_PPStruct_tmp;
  real_T d201;
  real_T d202;
  real_T smax_a;
  real_T s_f;
  int32_T kAcol;
  int32_T jj;
  int32_T c_j;
  int32_T a;
};

// Block states (default storage) for model 'Hardware'
struct DW_Hardware_f_T {
  robotics_slcore_internal_bloc_T obj; // '<S3>/Polynomial Trajectory'
  real_T DiscreteTimeIntegrator_DSTATE[8];// '<S4>/Discrete-Time Integrator'
  real_T DiscreteTimeIntegrator1_DSTATE[8];// '<S4>/Discrete-Time Integrator1'
  boolean_T objisempty;                // '<S3>/Polynomial Trajectory'
};

// Parameters (default storage)
struct P_Hardware_T_ {
  real_T PolynomialTrajectory_VelocityBo[16];
                              // Expression: zeros( size(Trajectory.Waypoints) )
                                 //  Referenced by: '<S3>/Polynomial Trajectory'

  real_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<S4>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC;    // Expression: 0
                                          //  Referenced by: '<S4>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator1_gainval;
                          // Computed Parameter: DiscreteTimeIntegrator1_gainval
                             //  Referenced by: '<S4>/Discrete-Time Integrator1'

  real_T DiscreteTimeIntegrator1_IC;   // Expression: 0
                                          //  Referenced by: '<S4>/Discrete-Time Integrator1'

};

// Real-time Model Data Structure
struct tag_RTM_Hardware_T {
  const char_T **errorStatus;
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
  time_T getT() const;
  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const aErrorStatus) const;
  boolean_T isSampleHit(int32_T sti) const;
  const char_T** getErrorStatusPointer() const;
  void setErrorStatusPointer(const char_T** aErrorStatusPointer);
};

struct MdlrefDW_Hardware_T {
  B_Hardware_c_T rtb;
  DW_Hardware_f_T rtdw;
  RT_MODEL_Hardware_T rtm;
};

// Model block global parameters (default storage)
extern struct_bwZkdZIRabTIxeUCMoFaDG rtP_Differentiator;// Variable: Differentiator
                                                           //  Referenced by:
                                                           //    '<S4>/G1'
                                                           //    '<S4>/G2'
                                                           //    '<S4>/Q1'
                                                           //    '<S4>/Q2'
                                                           //    '<S4>/Q3'
                                                           //    '<S4>/Q4'
                                                           //    '<S4>/Q5'
                                                           //    '<S4>/Q6'

extern struct_Z1yy0b1SiRejj6ODUGxXCE rtP_HexaConstants;// Variable: HexaConstants
                                                          //  Referenced by: '<S9>/MATLAB Function1'

extern struct_JL8g2iM4Lw6J1bY0kTxLfE rtP_ArmConstants;// Variable: ArmConstants
                                                         //  Referenced by: '<S9>/MATLAB Function1'

extern struct_8gU0TGGHeyi782Q5TKcTyF rtP_Trajectory;// Variable: Trajectory
                                                       //  Referenced by: '<S3>/Polynomial Trajectory'

extern struct_CKTAE3dLo2KptrTZY712sF rtP_PID;// Variable: PID
                                                //  Referenced by:
                                                //    '<S11>/Kd'
                                                //    '<S11>/Kp'


// Model reference registration function
extern void Hardware_initialize(const char_T **rt_errorStatus, const
  rtTimingBridge *timingBridge, int_T mdlref_TID0, RT_MODEL_Hardware_T *const
  Hardware_M);
extern void Hardware_Upowerx1(const real_T rtu_u[8], const real_T rtu_v[8],
  real_T rty_uv[8]);
extern void Hardware_Init(B_Hardware_c_T *localB, DW_Hardware_f_T *localDW);
extern void Hardware(RT_MODEL_Hardware_T * const Hardware_M, const real_T
                     rtu_Positions[8], real_T rty_ForcesAndTorque[8],
                     B_Hardware_c_T *localB, DW_Hardware_f_T *localDW);

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
//  '<Root>' : 'Hardware'
//  '<S1>'   : 'Hardware/DifferentiatorDisc'
//  '<S2>'   : 'Hardware/PDHard'
//  '<S3>'   : 'Hardware/TrajectoryHard'
//  '<S4>'   : 'Hardware/DifferentiatorDisc/Fixed-Time Differentiator1'
//  '<S5>'   : 'Hardware/DifferentiatorDisc/Fixed-Time Differentiator1/U power x1'
//  '<S6>'   : 'Hardware/DifferentiatorDisc/Fixed-Time Differentiator1/U power x2'
//  '<S7>'   : 'Hardware/DifferentiatorDisc/Fixed-Time Differentiator1/U power x3'
//  '<S8>'   : 'Hardware/DifferentiatorDisc/Fixed-Time Differentiator1/U power x4'
//  '<S9>'   : 'Hardware/PDHard/Get f(x) and g(x)^-1'
//  '<S10>'  : 'Hardware/PDHard/GetBInvMatrix'
//  '<S11>'  : 'Hardware/PDHard/PID'
//  '<S12>'  : 'Hardware/PDHard/Get f(x) and g(x)^-1/MATLAB Function1'
//  '<S13>'  : 'Hardware/PDHard/PID/Obtain Error'
//  '<S14>'  : 'Hardware/PDHard/PID/PD Controller'

#endif                                 // HARDWARE_H_

//
// File trailer for generated code.
//
// [EOF]
//
