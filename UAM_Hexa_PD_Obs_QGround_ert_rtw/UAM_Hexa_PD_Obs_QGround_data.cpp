//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: UAM_Hexa_PD_Obs_QGround_data.cpp
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
#include "UAM_Hexa_PD_Obs_QGround.h"

// Block parameters (default storage)
P_UAM_Hexa_PD_Obs_QGround_T UAM_Hexa_PD_Obs_QGround_P = {
  // Variable: HexaConstants
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S169>/Thrust Factor (kT)1'

  {
    1.8188,

    { 0.0393748, 0.0, 0.0, 0.0, 0.04043155, 0.0, 0.0, 0.0, 0.06214814 },

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
    8.0082e-6
  },

  // Variable: Trajectory
  //  Referenced by: '<S5>/Polynomial Trajectory'

  {
    { 0.0, 10.0, 20.0, 30.0 },

    { 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.78539816339744828,
      0.78539816339744828, 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.78539816339744828,
      0.78539816339744828 }
  },

  // Variable: ArmConstants
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S1>/Torque Saturation1'

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

  // Variable: PickObj
  //  Referenced by: '<S4>/MATLAB Function'

  {
    0.023,
    0.05,

    { 48.0, 143.0 }
  },

  // Mask Parameter: DCM2Ang_tolerance
  //  Referenced by:
  //    '<S216>/Constant'
  //    '<S218>/Constant'

  4.4408920985006262E-16,

  // Mask Parameter: DCM2Ang_action
  //  Referenced by:
  //    '<S195>/Constant'
  //    '<S205>/Constant'
  //    '<S207>/Constant'

  1U,

  // Expression: 1
  //  Referenced by: '<S201>/Constant'

  1.0,

  // Expression: -1
  //  Referenced by: '<S202>/Constant'

  -1.0,

  // Expression: 1
  //  Referenced by: '<S197>/Constant'

  1.0,

  // Expression: -1
  //  Referenced by: '<S198>/Constant'

  -1.0,

  // Expression: 0
  //  Referenced by: '<S207>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S205>/Constant1'

  0.0,

  // Expression: -eye(3)
  //  Referenced by: '<S208>/Bias1'

  { -1.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -1.0 },

  // Expression: -1
  //  Referenced by: '<S209>/Bias'

  -1.0,

  // Expression: zeros( size(Trajectory.Waypoints) )
  //  Referenced by: '<S5>/Polynomial Trajectory'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0 },

  // Expression: [0; 0; 0.24; 0; 0; 0; 0; 0]
  //  Referenced by: '<S7>/gamma_hat_1'

  { 0.0, 0.0, 0.24, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: zeros(8,1)
  //  Referenced by: '<S7>/gamma_hat_2'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: inv(1.0e-05*[-0.2372    0.2372    0.0000   -0.2372    0.2372    0.0000;...
  // 0.1369    0.1369   -0.2739    0.1369    0.1369   -0.2739;...
  // 0.7525    0.7525    0.7525    0.7525    0.7525    0.7525;...
  // 0.1694    0.1694    0.0000   -0.1694   -0.1694    0.0000;...
  // -0.0978    0.0978    0.1956    0.0978   -0.0978   -0.1956;...
  // 0.0830   -0.0830    0.0830   -0.0830    0.0830   -0.0830])
  //  Referenced by: '<S6>/Constant'

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
  //  Referenced by: '<S169>/Integrator7'

  0.0,

  // Expression: 0
  //  Referenced by: '<S169>/Integrator9'

  0.0,

  // Expression: 0
  //  Referenced by: '<S169>/Integrator10'

  0.0,

  // Expression: 0
  //  Referenced by: '<S169>/Integrator11'

  0.0,

  // Expression: 0
  //  Referenced by: '<S169>/Integrator12'

  0.0,

  // Expression: 0
  //  Referenced by: '<S169>/Integrator13'

  0.0,

  // Expression: [0; 0; -9.81; 0; 0; 0; 0; 0]
  //  Referenced by: '<S7>/gamma_3_hat'

  { 0.0, 0.0, -9.81, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 8.77e+05

  //  Referenced by: '<S6>/Rotation Saturation1'

  877000.0,

  // Expression: 0
  //  Referenced by: '<S6>/Rotation Saturation1'

  0.0,

  // Expression: 7
  //  Referenced by: '<S169>/Saturation1'

  7.0,

  // Expression: 0
  //  Referenced by: '<S169>/Saturation1'

  0.0,

  // Expression: 2
  //  Referenced by: '<S222>/Gain'

  2.0,

  // Expression: 2
  //  Referenced by: '<S225>/Gain'

  2.0,

  // Expression: 2
  //  Referenced by: '<S220>/Gain'

  2.0,

  // Expression: 2
  //  Referenced by: '<S226>/Gain'

  2.0,

  // Expression: 2
  //  Referenced by: '<S221>/Gain'

  2.0,

  // Expression: 2
  //  Referenced by: '<S224>/Gain'

  2.0,

  // Expression: [1 1 -1]
  //  Referenced by: '<S194>/Gain1'

  { 1.0, 1.0, -1.0 },

  // Expression: [1 1]
  //  Referenced by: '<S194>/Gain2'

  { 1.0, 1.0 },

  // Expression: [-1 1]
  //  Referenced by: '<S194>/Gain3'

  { -1.0, 1.0 },

  // Expression: [2;2;2;2;2;2;2;2]
  //  Referenced by: '<S7>/Constant4'

  { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 },

  // Expression: 1/3
  //  Referenced by: '<S7>/Gain4'

  0.33333333333333331,

  // Expression: [2;2;2;2;2;2;2;2]
  //  Referenced by: '<S7>/Constant2'

  { 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0 },

  // Expression: 1/3
  //  Referenced by: '<S7>/Gain3'

  0.33333333333333331,

  // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
  //  Referenced by: '<S7>/Constant7'

  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  // Expression: 0.5
  //  Referenced by: '<S7>/Gain6'

  0.5,

  // Expression: [1; 1; 1; 1; 1; 1; 1; 1]
  //  Referenced by: '<S7>/Constant6'

  { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },

  // Expression: 0.5
  //  Referenced by: '<S7>/Gain5'

  0.5,

  // Expression: -1
  //  Referenced by: '<S169>/Gain6'

  -1.0,

  // Expression: -1
  //  Referenced by: '<S169>/Gain4'

  -1.0,

  // Expression: -1
  //  Referenced by: '<S169>/Gain3'

  -1.0,

  // Computed Parameter: Assertion_Enabled
  //  Referenced by: '<S215>/Assertion'

  true,

  // Computed Parameter: Assertion_Enabled_f
  //  Referenced by: '<S213>/Assertion'

  true,

  // Computed Parameter: Assertion_Enabled_c
  //  Referenced by: '<S212>/Assertion'

  true,

  // Computed Parameter: Assertion_Enabled_i
  //  Referenced by: '<S210>/Assertion'

  true
};

//
// File trailer for generated code.
//
// [EOF]
//
