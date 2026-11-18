//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ContModelHIL_data.cpp
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

// Block parameters (default storage)
P_ContModelHIL_T ContModelHIL_P = {
  // Variable: Observer
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

  {
    { 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 50.0, 50.0 },

    { 60.0, 60.0, 60.0, 150.0, 150.0, 150.0, 500.0, 500.0 },

    { 100.0, 100.0, 100.0, 450.0, 450.0, 450.0, 2000.0, 2000.0 },

    { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 },

    { 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 50.0, 50.0 },

    { 60.0, 60.0, 60.0, 150.0, 150.0, 150.0, 500.0, 500.0 },

    { 100.0, 100.0, 100.0, 450.0, 450.0, 450.0, 2000.0, 2000.0 },

    { 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6 },

    { 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2 }
  },

  // Variable: Trajectory
  //  Referenced by: '<S3>/Polynomial Trajectory'

  {
    { 0.0, 10.0, 20.0, 30.0 },

    { 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.78539816339744828,
      0.78539816339744828, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.0, 0.0 }
  },

  // Variable: PID
  //  Referenced by:
  //    '<S6>/Kd'
  //    '<S6>/Kp'

  {
    { 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 10.0, 10.0 },

    { 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 10.0, 10.0 }
  },

  // Mask Parameter: CompareToConstant_const
  //  Referenced by: '<S9>/Constant'

  0U,

  // Computed Parameter: Out1_Y0
  //  Referenced by: '<S10>/Out1'

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
  //  Referenced by: '<S2>/Constant'

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

  // Expression: zeros( size(Trajectory.Waypoints) )
  //  Referenced by: '<S3>/Polynomial Trajectory'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S4>/Delay5'

  0.0,

  // Expression: 0
  //  Referenced by: '<S4>/Delay3'

  0.0,

  // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
  //  Referenced by: '<S4>/Constant6'

  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  // Expression: 0.5
  //  Referenced by: '<S4>/Gain5'

  0.5,

  // Expression: 0
  //  Referenced by: '<S4>/Delay7'

  0.0,

  // Expression: 0
  //  Referenced by: '<S4>/Delay9'

  0.0,

  // Expression: 0
  //  Referenced by: '<S4>/Delay8'

  0.0,

  // Computed Parameter: DiscreteTimeIntegrator3_gainval
  //  Referenced by: '<S4>/Discrete-Time Integrator3'

  0.01,

  // Expression: [0; 0; -9.81; 0; 0; 0; 0; 0]
  //  Referenced by: '<S4>/Discrete-Time Integrator3'

  { 0.0, 0.0, -9.81, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S4>/Delay4'

  0.0,

  // Expression: 0
  //  Referenced by: '<S4>/Delay6'

  0.0,

  // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
  //  Referenced by: '<S4>/Constant7'

  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  // Expression: 0.5
  //  Referenced by: '<S4>/Gain6'

  0.5,

  // Computed Parameter: DiscreteTimeIntegrator1_gainval
  //  Referenced by: '<S4>/Discrete-Time Integrator1'

  0.01,

  // Expression: zeros(8,1)
  //  Referenced by: '<S4>/Discrete-Time Integrator1'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S4>/Delay2'

  0.0,

  // Expression: [2;2;2;2;2;2;2;2]
  //  Referenced by: '<S4>/Constant2'

  { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 },

  // Expression: 1/3
  //  Referenced by: '<S4>/Gain3'

  0.33333333333333331,

  // Expression: 0
  //  Referenced by: '<S4>/Delay1'

  0.0,

  // Expression: [2;2;2;2;2;2;2;2]
  //  Referenced by: '<S4>/Constant4'

  { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 },

  // Expression: 1/3
  //  Referenced by: '<S4>/Gain4'

  0.33333333333333331,

  // Computed Parameter: DiscreteTimeIntegrator_gainval
  //  Referenced by: '<S4>/Discrete-Time Integrator'

  0.01,

  // Expression: [0; 0; 0.24; 0; 0; 0; 0; 0]
  //  Referenced by: '<S4>/Discrete-Time Integrator'

  { 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S1>/Delay'

  0.0,

  // Expression: 100
  //  Referenced by: '<S1>/Constant'

  100.0,

  // Expression: 0
  //  Referenced by: '<S4>/Delay'

  0.0,

  // Expression: true
  //  Referenced by: '<Root>/Constant'

  true
};

//
// File trailer for generated code.
//
// [EOF]
//
