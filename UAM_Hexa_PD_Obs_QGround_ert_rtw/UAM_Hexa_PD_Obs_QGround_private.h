//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: UAM_Hexa_PD_Obs_QGround_private.h
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
#ifndef UAM_HEXA_PD_OBS_QGROUND_PRIVATE_H_
#define UAM_HEXA_PD_OBS_QGROUND_PRIVATE_H_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "UAM_Hexa_PD_Obs_QGround_types.h"

// Private macros used by the generated code to access rtModel
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_atan2d_snf(real_T u0, real_T u1);

// private model entry point functions
extern void UAM_Hexa_PD_Obs_QGround_derivatives(void);

#endif                                 // UAM_HEXA_PD_OBS_QGROUND_PRIVATE_H_

//
// File trailer for generated code.
//
// [EOF]
//
