//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ContModelHIL.h
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
#ifndef CONTMODELHIL_H_
#define CONTMODELHIL_H_
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "MW_uORB_Read.h"
#include "ContModelHIL_types.h"
#include <uORB/topics/uam_states.h>

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

#include <stddef.h>

// Block signals (default storage)
struct B_ContModelHIL_T {
  real_T coefsWithFlatStart[128];
  real_T coefMat[96];
  real_T ginv[64];                     // '<S1>/MATLAB Function1'
  real_T dv[64];
  real_T b_x[64];
  real_T b_A[64];
  real_T coeffMat[32];
  px4_Bus_uam_states In1;              // '<S10>/In1'
  px4_Bus_uam_states r;
  real_T Delay[8];                     // '<S4>/Delay'
  real_T fx[8];                        // '<S1>/MATLAB Function1'
  real_T dv1[8];
  real_T dv2[8];
  real_T dv3[8];
  real_T dv4[8];
  real_T dv5[8];
  real32_T motorValues[12];
  real32_T motorValues_m[12];
  real_T breaksWithFlatStart[5];
  real32_T servoValues[8];
  real_T b_coeffVec[4];
  int32_T ipiv[8];
  int32_T ipiv_c[8];
  int8_T p[8];
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
  real_T DigitalClock;                 // '<S3>/Digital Clock'
  real_T D14_tmp;
  real_T D14_tmp_k;
  real_T D14_tmp_c;
  real_T D14_tmp_b;
  real_T D14_tmp_p;
  real_T D14_tmp_cv;
  real_T D15_tmp;
  real_T D15_tmp_f;
  real_T D15_tmp_g;
  real_T D46_tmp;
  real_T D46_tmp_g;
  real_T D46_tmp_m;
  real_T D46_tmp_n;
  real_T D46_tmp_p;
  real_T D46_tmp_l;
  real_T D56_tmp;
  real_T D46_tmp_j;
  real_T D56_tmp_d;
  real_T D56_tmp_g;
  real_T D46_tmp_ld;
  real_T D56_tmp_dh;
  real_T D56_tmp_dy;
  real_T D46_tmp_lx;
  real_T D56_tmp_o;
  real_T D56_tmp_b;
  real_T D46_tmp_nu;
  real_T D56_tmp_bs;
  real_T D46_tmp_ln;
  real_T D46_tmp_h;
  real_T D46_tmp_b;
  real_T D46_tmp_d;
  real_T rtb_ginv_tmp;
  real_T D56_tmp_e;
  real_T D56_tmp_bj;
  real_T D56_tmp_j;
  real_T D56_tmp_f;
  real_T d;
  real_T d1;
  real_T d2;
  real_T d3;
  real_T d4;
  real_T d5;
  real_T d6;
  real_T d7;
  real_T rtb_ginv_tmp_a;
  real_T D56_tmp_ju;
  real_T D56_tmp_jz;
  real_T D56_tmp_o4;
  real_T D56_tmp_n;
  real_T d8;
  real_T d9;
  real_T DiscreteTimeIntegrator3_DSTATE;
  real_T Observer_beta;
  real_T u;
  real_T u_i;
  real_T D14_tmp_tmp;
  real_T D14_tmp_o;
  real_T D15_tmp_tmp;
  real_T D14_tmp_n;
  real_T D14_tmp_m;
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
  real_T D15_tmp_tmp_a;
  real_T D34_tmp;
  real_T D34_tmp_a;
  real_T D46_tmp_tmp;
  real_T D46_tmp_tmp_i;
  real_T D46_tmp_tmp_l;
  real_T D46_tmp_tmp_o;
  real_T D47_tmp;
  real_T D56_tmp_tmp;
  real_T D56_tmp_tmp_o;
  real_T D56_tmp_tmp_i;
  real_T D56_tmp_tmp_f;
  real_T D56_tmp_tmp_iz;
  real_T D56_tmp_tmp_ff;
  real_T D56_tmp_tmp_g;
  real_T D46_tmp_c;
  real_T D46_tmp_o;
  real_T D46_tmp_lm;
  real_T D46_tmp_mv;
  real_T D46_tmp_mj;
  real_T D45_tmp;
  real_T D45_tmp_c;
  real_T D24_tmp_f;
  real_T D46_tmp_p4;
  real_T D46_tmp_e;
  real_T D46_tmp_o4;
  real_T D46_tmp_hh;
  real_T D46_tmp_l5;
  real_T D46_tmp_h2;
  real_T D46_tmp_me;
  real_T D46_tmp_mc;
  real_T D46_tmp_h3;
  real_T D46_tmp_cs;
  real_T D56_tmp_k;
  real_T D48_tmp;
  real_T D56_tmp_tmp_tmp;
  real_T rtb_ginv_tmp_tmp;
  real_T rtb_ginv_tmp_tmp_p;
  real_T D47_tmp_p;
  real_T rtb_ginv_tmp_p;
  real_T rtb_ginv_tmp_ap;
  real_T rtb_ginv_tmp_j;
  real_T rtb_ginv_tmp_e;
  real_T D56_tmp_tmp_ol;
  real_T D56_tmp_tmp_b;
  real_T D46_tmp_tmp_a;
  real_T D56_tmp_tmp_g2;
  real_T D56_tmp_tmp_e;
  real_T D46_tmp_tmp_f;
  real_T D46_tmp_tmp_h;
  real_T D46_tmp_tmp_e;
  real_T D46_tmp_tmp_c;
  real_T D46_tmp_tmp_ax;
  real_T D14_tmp_d;
  real_T D14_tmp_a;
  real_T D14_tmp_pb;
  real_T D34_tmp_m;
  real_T D14_tmp_o3;
  real_T D16_tmp_n;
  real_T D16_tmp_l;
  real_T D16_tmp_p;
  real_T d10;
  real_T D16_tmp_pt;
  real_T d11;
  real_T D37_tmp;
  real_T d12;
  real_T d13;
  real_T d14;
  real_T D28_tmp;
  real_T D17_tmp_tmp_f;
  real_T D27_tmp;
  real_T D27_tmp_i;
  real_T d15;
  real_T d16;
  real_T d17;
  real_T d18;
  real_T d19;
  real_T D15_tmp_tmp_o;
  real_T D15_tmp_tmp_k;
  real_T d20;
  real_T d21;
  real_T D14_tmp_tmp_i;
  real_T D14_tmp_tmp_o;
  real_T d22;
  real_T d23;
  real_T d24;
  real_T D46_tmp_tmp_m;
  real_T D56_tmp_c;
  real_T D56_tmp_fb;
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
  real_T D56_tmp_h;
  real_T rtb_ginv_tmp_m;
  real_T rtb_ginv_tmp_ad;
  real_T rtb_ginv_tmp_k;
  real_T d90;
  real_T d91;
  real_T d92;
  real_T tmp_tmp;
  real_T d93;
  real_T tmp_tmp_p;
  real_T d94;
  real_T d95;
  real_T d96;
  real_T d97;
  real_T d98;
  real_T d99;
  real_T d100;
  real_T d101;
  real_T d102;
  real_T d103;
  real_T d104;
  real_T d105;
  real_T d106;
  real_T d107;
  real_T d108;
  real_T d109;
  real_T d110;
  real_T tmp_tmp_b;
  real_T tmp_tmp_c;
  real_T tmp_tmp_n;
  real_T tmp_tmp_i;
  real_T tmp_tmp_m;
  real_T d111;
  real_T tmp_tmp_j;
  real_T tmp_tmp_e;
  real_T tmp_tmp_mv;
  real_T tmp_tmp_m0;
  real_T tmp_tmp_jg;
  real_T tmp_tmp_f;
  real_T tmp_tmp_a;
  real_T D47_tmp_g;
  real_T tmp_tmp_nr;
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
  real_T D24_tmp_d;
  real_T D24_tmp_n;
  real_T D18_tmp;
  real_T rtb_ginv_tmp_c;
  real_T rtb_ginv_tmp_f;
  real_T rtb_ginv_tmp_pm;
  real_T d149;
  real_T rtb_ginv_tmp_p2;
  real_T D17_tmp_n;
  real_T D17_tmp_k;
  real_T D17_tmp_n3;
  real_T D17_tmp_tmp_o;
  real_T D17_tmp_tmp_g;
  real_T D56_tmp_tmp_c;
  real_T D56_tmp_tmp_cj;
  real_T D56_tmp_tmp_m;
  real_T D56_tmp_tmp_j;
  real_T D56_tmp_tmp_k;
  real_T D56_tmp_tmp_mx;
  real_T D56_tmp_tmp_p;
  real_T D56_tmp_tmp_d;
  real_T D56_tmp_tmp_g4;
  real_T D56_tmp_tmp_c3;
  real_T D56_tmp_tmp_cx;
  real_T D56_tmp_tmp_if;
  real_T D56_tmp_tmp_dx;
  real_T D56_tmp_tmp_g4k;
  real_T D56_tmp_tmp_l;
  real_T D56_tmp_tmp_f1;
  real_T D56_tmp_tmp_db;
  real_T D56_tmp_tmp_jr;
  real_T tmp_tmp_i3;
  real_T tmp_tmp_h;
  real_T d150;
  real_T tmp_tmp_nm;
  real_T tmp_tmp_o;
  real_T tmp_tmp_ch;
  real_T tmp_tmp_bd;
  real_T d151;
  real_T d152;
  real_T d153;
  real_T d154;
  real_T d155;
  real_T tmp_tmp_er;
  real_T tmp_tmp_d;
  real_T tmp_tmp_ik;
  real_T tmp_tmp_g;
  real_T tmp_tmp_nn;
  real_T tmp_tmp_l;
  real_T tmp_tmp_ce;
  real_T d156;
  real_T tmp_tmp_nc;
  real_T tmp_tmp_ph;
  real_T tmp_tmp_dk;
  real_T tmp_tmp_oi;
  real_T tmp_tmp_jr;
  real_T tmp_tmp_c2;
  real_T tmp_tmp_hp;
  real_T tmp_tmp_da;
  real_T d157;
  real_T d158;
  real_T tmp_tmp_c5;
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
  real_T d182;
  real_T d183;
  real_T d184;
  real_T d185;
  real_T finalTime;
  real_T d186;
  real_T smax;
  real_T s;
  int32_T i;
};

// Block states (default storage) for system '<Root>'
struct DW_ContModelHIL_T {
  robotics_slcore_internal_bloc_T obj; // '<S3>/Polynomial Trajectory'
  px4_internal_block_PX4Actuato_T obj_a;// '<Root>/PX4 Actuator Write'
  px4_internal_block_Subscriber_T obj_h;// '<S2>/SourceBlock'
  real_T Delay5_DSTATE[64];            // '<S4>/Delay5'
  real_T Delay3_DSTATE[8];             // '<S4>/Delay3'
  real_T Delay7_DSTATE[8];             // '<S4>/Delay7'
  real_T Delay9_DSTATE[8];             // '<S4>/Delay9'
  real_T Delay8_DSTATE[8];             // '<S4>/Delay8'
  real_T DiscreteTimeIntegrator3_DSTATE[8];// '<S4>/Discrete-Time Integrator3'
  real_T Delay4_DSTATE[8];             // '<S4>/Delay4'
  real_T Delay6_DSTATE[8];             // '<S4>/Delay6'
  real_T DiscreteTimeIntegrator1_DSTATE[8];// '<S4>/Discrete-Time Integrator1'
  real_T Delay2_DSTATE[8];             // '<S4>/Delay2'
  real_T Delay1_DSTATE[8];             // '<S4>/Delay1'
  real_T DiscreteTimeIntegrator_DSTATE[8];// '<S4>/Discrete-Time Integrator'
  real_T Delay_DSTATE[8];              // '<S1>/Delay'
  real_T Delay_DSTATE_a[8];            // '<S4>/Delay'
};

// Parameters (default storage)
struct P_ContModelHIL_T_ {
  struct_dsZHuztvFQ2jHmAMZlAOhG Observer;// Variable: Observer
                                            //  Referenced by:
                                            //    '<S4>/Constant'
                                            //    '<S4>/Constant1'
                                            //    '<S4>/Constant10'
                                            //    '<S4>/Constant11'
                                            //    '<S4>/Constant12'
                                            //    '<S4>/Constant3'
                                            //    '<S4>/Constant5'
                                            //    '<S4>/Constant8'
                                            //    '<S4>/Constant9'

  struct_u7NbN6ywI9YZ24VWuwFOtG Trajectory;// Variable: Trajectory
                                              //  Referenced by: '<S3>/Polynomial Trajectory'

  struct_CKTAE3dLo2KptrTZY712sF PID;   // Variable: PID
                                          //  Referenced by:
                                          //    '<S6>/Kd'
                                          //    '<S6>/Kp'

  uint8_T CompareToConstant_const;    // Mask Parameter: CompareToConstant_const
                                         //  Referenced by: '<S9>/Constant'

  px4_Bus_uam_states Out1_Y0;          // Computed Parameter: Out1_Y0
                                          //  Referenced by: '<S10>/Out1'

  px4_Bus_uam_states Constant_Value;   // Computed Parameter: Constant_Value
                                          //  Referenced by: '<S2>/Constant'

  real_T PolynomialTrajectory_VelocityBo[32];
                              // Expression: zeros( size(Trajectory.Waypoints) )
                                 //  Referenced by: '<S3>/Polynomial Trajectory'

  real_T Delay5_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay5'

  real_T Delay3_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay3'

  real_T Constant6_Value[8];           // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
                                          //  Referenced by: '<S4>/Constant6'

  real_T Gain5_Gain;                   // Expression: 0.5
                                          //  Referenced by: '<S4>/Gain5'

  real_T Delay7_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay7'

  real_T Delay9_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay9'

  real_T Delay8_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay8'

  real_T DiscreteTimeIntegrator3_gainval;
                          // Computed Parameter: DiscreteTimeIntegrator3_gainval
                             //  Referenced by: '<S4>/Discrete-Time Integrator3'

  real_T DiscreteTimeIntegrator3_IC[8];
                                     // Expression: [0; 0; -9.81; 0; 0; 0; 0; 0]
                                        //  Referenced by: '<S4>/Discrete-Time Integrator3'

  real_T Delay4_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay4'

  real_T Delay6_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay6'

  real_T Constant7_Value[8];           // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
                                          //  Referenced by: '<S4>/Constant7'

  real_T Gain6_Gain;                   // Expression: 0.5
                                          //  Referenced by: '<S4>/Gain6'

  real_T DiscreteTimeIntegrator1_gainval;
                          // Computed Parameter: DiscreteTimeIntegrator1_gainval
                             //  Referenced by: '<S4>/Discrete-Time Integrator1'

  real_T DiscreteTimeIntegrator1_IC[8];// Expression: zeros(8,1)
                                          //  Referenced by: '<S4>/Discrete-Time Integrator1'

  real_T Delay2_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay2'

  real_T Constant2_Value[8];           // Expression: [2;2;2;2;2;2;2;2]
                                          //  Referenced by: '<S4>/Constant2'

  real_T Gain3_Gain;                   // Expression: 1/3
                                          //  Referenced by: '<S4>/Gain3'

  real_T Delay1_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S4>/Delay1'

  real_T Constant4_Value[8];           // Expression: [2;2;2;2;2;2;2;2]
                                          //  Referenced by: '<S4>/Constant4'

  real_T Gain4_Gain;                   // Expression: 1/3
                                          //  Referenced by: '<S4>/Gain4'

  real_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<S4>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC[8];// Expression: [0; 0; 0.24; 0; 0; 0; 0; 0]
                                         //  Referenced by: '<S4>/Discrete-Time Integrator'

  real_T Delay_InitialCondition;       // Expression: 0
                                          //  Referenced by: '<S1>/Delay'

  real_T Constant_Value_l;             // Expression: 100
                                          //  Referenced by: '<S1>/Constant'

  real_T Delay_InitialCondition_b;     // Expression: 0
                                          //  Referenced by: '<S4>/Delay'

  boolean_T Constant_Value_h;          // Expression: true
                                          //  Referenced by: '<Root>/Constant'

};

// Real-time Model Data Structure
struct tag_RTM_ContModelHIL_T {
  const char_T * volatile errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
  } Timing;

  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_ContModelHIL_T ContModelHIL_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_ContModelHIL_T ContModelHIL_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_ContModelHIL_T ContModelHIL_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void ContModelHIL_initialize(void);
  extern void ContModelHIL_step(void);
  extern void ContModelHIL_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_ContModelHIL_T *const ContModelHIL_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Scope' : Unused code path elimination
//  Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion2' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion3' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion4' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion5' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion6' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion7' : Eliminate redundant data type conversion


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
//  '<Root>' : 'ContModelHIL'
//  '<S1>'   : 'ContModelHIL/Controller And Observer1'
//  '<S2>'   : 'ContModelHIL/PX4 uORB Read4'
//  '<S3>'   : 'ContModelHIL/Trajectory1'
//  '<S4>'   : 'ContModelHIL/Controller And Observer1/ExtendedStateObserver'
//  '<S5>'   : 'ContModelHIL/Controller And Observer1/MATLAB Function1'
//  '<S6>'   : 'ContModelHIL/Controller And Observer1/PDController1'
//  '<S7>'   : 'ContModelHIL/Controller And Observer1/PDController1/Obtain Error'
//  '<S8>'   : 'ContModelHIL/Controller And Observer1/PDController1/PD Controller'
//  '<S9>'   : 'ContModelHIL/PX4 uORB Read4/Compare To Constant'
//  '<S10>'  : 'ContModelHIL/PX4 uORB Read4/Enabled Subsystem'

#endif                                 // CONTMODELHIL_H_

//
// File trailer for generated code.
//
// [EOF]
//
