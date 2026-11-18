//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ContModelSIL_data.cpp
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

// Block parameters (default storage)
P_ContModelSIL_T ContModelSIL_P = {
  // Variable: Observer
  //  Referenced by:
  //    '<S8>/Constant'
  //    '<S8>/Constant1'
  //    '<S8>/Constant10'
  //    '<S8>/Constant11'
  //    '<S8>/Constant12'
  //    '<S8>/Constant3'
  //    '<S8>/Constant5'
  //    '<S8>/Constant8'
  //    '<S8>/Constant9'

  {
    { 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 50.0, 50.0 },

    { 60.0, 60.0, 60.0, 150.0, 150.0, 150.0, 1000.0, 1000.0 },

    { 100.0, 100.0, 100.0, 450.0, 450.0, 450.0, 5000.0, 5000.0 },

    { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 },

    { 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 50.0, 50.0 },

    { 60.0, 60.0, 60.0, 150.0, 150.0, 150.0, 1000.0, 1000.0 },

    { 100.0, 100.0, 100.0, 450.0, 450.0, 450.0, 5000.0, 5000.0 },

    { 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6 },

    { 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2 }
  },

  // Variable: Trajectory
  //  Referenced by: '<S6>/Polynomial Trajectory'

  {
    { 0.0, 10.0, 20.0, 30.0 },

    { 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.78539816339744828,
      0.78539816339744828, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.78539816339744828,
      0.78539816339744828 }
  },

  // Variable: ArmConstants
  //  Referenced by: '<S1>/Torque Saturation1'

  {
    0.17,
    0.17959,
    0.08312,
    0.142,
    0.143,

    { 5.484e-5, 0.0, 0.0, 0.0, 0.00050874, 0.0, 0.0, 0.0, 0.00046501 },

    { 8.085e-5, 0.0, 0.0, 0.0, 0.00034964, 0.0, 0.0, 0.0, 0.0003034 },
    0.11464,
    0.09794,

    {
      2.5,
      2.5
    }
  },

  // Variable: PID
  //  Referenced by:
  //    '<S10>/Kd'
  //    '<S10>/Kp'

  {
    { 0.5, 0.5, 250.0, 2.0, 2.0, 2.0, 20.0, 20.0 },

    { 0.5, 0.5, 250.0, 2.0, 2.0, 2.0, 20.0, 20.0 }
  },

  // Mask Parameter: CompareToConstant_const
  //  Referenced by: '<S15>/Constant'

  0U,

  // Mask Parameter: CompareToConstant_const_o
  //  Referenced by: '<S17>/Constant'

  0U,

  // Computed Parameter: Out1_Y0
  //  Referenced by: '<S18>/Out1'

  {
    (0ULL),                            // timestamp
    0.0,                               // x
    0.0,                               // y
    0.0,                               // z
    0.0,                               // roll
    0.0,                               // pitch
    0.0,                               // yaw
    0.0,                               // linkone
    0.0                                // linktwo
  },

  // Computed Parameter: Constant_Value
  //  Referenced by: '<S5>/Constant'

  {
    (0ULL),                            // timestamp
    0.0,                               // x
    0.0,                               // y
    0.0,                               // z
    0.0,                               // roll
    0.0,                               // pitch
    0.0,                               // yaw
    0.0,                               // linkone
    0.0                                // linktwo
  },

  // Computed Parameter: Out1_Y0_o
  //  Referenced by: '<S16>/Out1'

  {
    (0ULL),                            // timestamp
    false,                             // armed
    false,                             // prearmed
    false,                             // ready_to_arm
    false,                             // lockdown
    false,                             // manual_lockdown
    false,                             // force_failsafe
    false,                             // in_esc_calibration_mode
    0U                                 // _padding0
  },

  // Computed Parameter: Constant_Value_p
  //  Referenced by: '<S4>/Constant'

  {
    (0ULL),                            // timestamp
    false,                             // armed
    false,                             // prearmed
    false,                             // ready_to_arm
    false,                             // lockdown
    false,                             // manual_lockdown
    false,                             // force_failsafe
    false,                             // in_esc_calibration_mode
    0U                                 // _padding0
  },

  // Expression: zeros( size(Trajectory.Waypoints) )
  //  Referenced by: '<S6>/Polynomial Trajectory'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S8>/Delay5'

  0.0,

  // Expression: 0
  //  Referenced by: '<S8>/Delay2'

  0.0,

  // Expression: [2;2;2;2;2;2;2;2]
  //  Referenced by: '<S8>/Constant2'

  { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 },

  // Expression: 1/3
  //  Referenced by: '<S8>/Gain3'

  0.33333333333333331,

  // Expression: 0
  //  Referenced by: '<S8>/Delay3'

  0.0,

  // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
  //  Referenced by: '<S8>/Constant6'

  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  // Expression: 0.5
  //  Referenced by: '<S8>/Gain5'

  0.5,

  // Expression: 0
  //  Referenced by: '<S8>/Delay7'

  0.0,

  // Expression: 0
  //  Referenced by: '<S8>/Delay9'

  0.0,

  // Expression: 0
  //  Referenced by: '<S8>/Delay8'

  0.0,

  // Computed Parameter: DiscreteTimeIntegrator3_gainval
  //  Referenced by: '<S8>/Discrete-Time Integrator3'

  0.01,

  // Expression: [0; 0; -9.81; 0; 0; 0; 0; 0]
  //  Referenced by: '<S8>/Discrete-Time Integrator3'

  { 0.0, 0.0, -9.81, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S8>/Delay4'

  0.0,

  // Expression: 0
  //  Referenced by: '<S8>/Delay6'

  0.0,

  // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
  //  Referenced by: '<S8>/Constant7'

  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  // Expression: 0.5
  //  Referenced by: '<S8>/Gain6'

  0.5,

  // Computed Parameter: DiscreteTimeIntegrator1_gainval
  //  Referenced by: '<S8>/Discrete-Time Integrator1'

  0.01,

  // Expression: zeros(8,1)
  //  Referenced by: '<S8>/Discrete-Time Integrator1'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S8>/Delay1'

  0.0,

  // Expression: [2;2;2;2;2;2;2;2]
  //  Referenced by: '<S8>/Constant4'

  { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 },

  // Expression: 1/3
  //  Referenced by: '<S8>/Gain4'

  0.33333333333333331,

  // Computed Parameter: DiscreteTimeIntegrator_gainval
  //  Referenced by: '<S8>/Discrete-Time Integrator'

  0.01,

  // Expression: [0; 0; 0.24; 0; 0; 0; 0; 0]
  //  Referenced by: '<S8>/Discrete-Time Integrator'

  { 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: inv(1.0e-05*[-0.2372    0.2372    0.0000   -0.2372    0.2372    0.0000;...
  // 0.1369    0.1369   -0.2739    0.1369    0.1369   -0.2739;...
  // 0.7525    0.7525    0.7525    0.7525    0.7525    0.7525;...
  // 0.1694    0.1694    0.0000   -0.1694   -0.1694    0.0000;...
  // -0.0978    0.0978    0.1956    0.0978   -0.0978   -0.1956;...
  // 0.0830   -0.0830    0.0830   -0.0830    0.0830   -0.0830])
  //  Referenced by: '<S7>/Constant'

  { -105396.29005059021, 105396.29005059021, 0.0, -105396.29005059021,
    105396.29005059021, 0.0, 60856.864654332967, 60856.864654333025,
    -121713.72930866599, 60856.86465433304, 60856.864654332981,
    -121713.72930866599, 22151.0900050788, 22151.090005078811,
    22143.002714094855, 22151.090005078826, 22151.090005078815,
    22143.002714094851, 147579.6930342385, 147579.6930342385, 0.0,
    -147579.6930342385, -147579.6930342385, 0.0, -85207.907293796889,
    85207.907293796889, 170415.81458759369, 85207.907293796889,
    -85207.907293796889, -170415.81458759369, 200803.21285140561,
    -200803.21285140561, 200803.21285140555, -200803.21285140561,
    200803.21285140561, -200803.21285140555 },

  // Expression: 0
  //  Referenced by: '<S1>/Delay'

  0.0,

  // Expression: 8.77e+05

  //  Referenced by: '<S7>/Rotation Saturation1'

  877000.0,

  // Expression: 0
  //  Referenced by: '<S7>/Rotation Saturation1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S8>/Delay'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
