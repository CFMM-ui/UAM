/*
 * PD_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PD".
 *
 * Model version              : 1.68
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Thu Oct 22 16:17:52 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "PD.h"

/* Block parameters (default storage) */
P_PD_T PD::PD_P{
  /* Variable: HexaConstants
   * Referenced by: '<S1>/MATLAB Function1'
   */
  struct_Z1yy0b1SiRejj6ODUGxXCE{
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

  /* Variable: ArmConstants
   * Referenced by: '<S1>/MATLAB Function1'
   */
  struct_JL8g2iM4Lw6J1bY0kTxLfE{
    0.17,
    0.17959,
    0.08312,
    0.142,
    0.143,

    { 5.484e-5, 0.0, 0.0, 0.0, 0.00050874, 0.0, 0.0, 0.0, 0.00046501 },

    { 8.085e-5, 0.0, 0.0, 0.0, 0.00034964, 0.0, 0.0, 0.0, 0.0003034 },
    0.11464,
    0.09794,
    struct_8iq6TggEG7Fvgh27g9ENz{
      2.5,
      2.5
    }
  },

  /* Variable: PID
   * Referenced by:
   *   '<S3>/Kd'
   *   '<S3>/Kp'
   */
  struct_CKTAE3dLo2KptrTZY712sF{
    { 0.5, 0.5, 1.0, 2.0, 2.0, 2.0, 50.0, 100.0 },

    { 0.5, 0.5, 1.0, 2.0, 2.0, 2.0, 50.0, 100.0 }
  }
};
