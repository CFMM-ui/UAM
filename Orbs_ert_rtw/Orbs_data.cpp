//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Orbs_data.cpp
//
// Code generated for Simulink model 'Orbs'.
//
// Model version                  : 1.1
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Mon Nov  9 17:55:24 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "Orbs.h"

// Block parameters (default storage)
P_Orbs_T Orbs_P = {
  // Computed Parameter: Constant_Value
  //  Referenced by: '<S1>/Constant'

  {
    (0ULL),                            // timestamp
    (0ULL),                            // timestamp_sample
    0.0,                               // lat
    0.0,                               // lon
    0.0F,                              // alt
    0.0F,                              // alt_ellipsoid
    0.0F,                              // delta_alt
    0.0F,                              // eph
    0.0F,                              // epv
    0.0F,                              // terrain_alt
    0U,                                // lat_lon_reset_counter
    0U,                                // alt_reset_counter
    false,                             // terrain_alt_valid
    false,                             // dead_reckoning

    {
      0U, 0U, 0U, 0U }
    // _padding0
  },

  // Expression: 1
  //  Referenced by: '<Root>/Constant'

  1.0,

  // Expression: 1
  //  Referenced by: '<Root>/Constant2'

  1.0,

  // Computed Parameter: Constant1_Value
  //  Referenced by: '<Root>/Constant1'

  1.0F,

  // Computed Parameter: Constant3_Value
  //  Referenced by: '<Root>/Constant3'

  0.0F
};

//
// File trailer for generated code.
//
// [EOF]
//
