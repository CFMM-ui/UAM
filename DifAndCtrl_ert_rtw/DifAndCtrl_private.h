//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: DifAndCtrl_private.h
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
#ifndef DIFANDCTRL_PRIVATE_H_
#define DIFANDCTRL_PRIVATE_H_
#include "rtwtypes.h"
#include "DifAndCtrl_types.h"
#include "DifAndCtrl.h"

extern real_T rt_powd_snf(real_T u0, real_T u1);
extern void DifAndCtrl_Upowerx1(const real_T rtu_u[8], const real_T rtu_v[8],
  real_T rty_uv[8]);

// private model entry point functions
extern void DifAndCtrl_derivatives(RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M);

#endif                                 // DIFANDCTRL_PRIVATE_H_

//
// File trailer for generated code.
//
// [EOF]
//
