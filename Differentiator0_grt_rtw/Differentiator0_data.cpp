/*
 * Differentiator0_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Differentiator0".
 *
 * Model version              : 1.66
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Thu Oct 22 12:09:20 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Differentiator0.h"

/* Constant parameters (default storage) */
const ConstP_Differentiator0_T Differentiator0_ConstP{
  /* Expression: Differentiator.G1
   * Referenced by: '<S1>/G1'
   */
  { 5.0, 5.0, 10.0, 5.0, 5.0, 5.0, 20.0, 20.0 },

  /* Expression: Differentiator.G2
   * Referenced by: '<S1>/G2'
   */
  { 10.0, 10.0, 20.0, 10.0, 10.0, 10.0, 150.0, 200.0 },

  /* Expression: Differentiator.Q2
   * Referenced by: '<S1>/Q2'
   */
  { 16.0, 16.0, 16.0, 40.0, 40.0, 40.0, 150.0, 200.0 },

  /* Expression: Differentiator.w1
   * Referenced by: '<S1>/Q3'
   */
  { 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.55, 0.55 },

  /* Expression: Differentiator.w2
   * Referenced by: '<S1>/Q4'
   */
  { 0.19999999999999996, 0.19999999999999996, 0.19999999999999996,
    0.19999999999999996, 0.19999999999999996, 0.19999999999999996,
    0.10000000000000009, 0.10000000000000009 },

  /* Expression: Differentiator.p1
   * Referenced by: '<S1>/Q5'
   */
  { 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.05, 1.05 },

  /* Expression: Differentiator.p2
   * Referenced by: '<S1>/Q6'
   */
  { 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.1, 1.1 },

  /* Expression: [0; 0; 0.28; 0; 0; 0; 0; 0]
   * Referenced by: '<S1>/Integrator'
   */
  { 0.0, 0.0, 0.28, 0.0, 0.0, 0.0, 0.0, 0.0 }
};
