//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: UorbRead_types.h
//
// Code generated for Simulink model 'UorbRead'.
//
// Model version                  : 1.4
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Mon Nov 16 18:37:07 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef UORBREAD_TYPES_H_
#define UORBREAD_TYPES_H_
#include "rtwtypes.h"
#include <uORB/topics/uam_states.h>
#ifndef STRUCT_D_PX4_INTERNAL_BLOCK_SAMPLETI_T
#define STRUCT_D_PX4_INTERNAL_BLOCK_SAMPLETI_T

struct d_px4_internal_block_SampleTi_T
{
  int32_T __dummy;
};

#endif                                // STRUCT_D_PX4_INTERNAL_BLOCK_SAMPLETI_T

#ifndef STRUCT_PX4_INTERNAL_BLOCK_SUBSCRIBER_T
#define STRUCT_PX4_INTERNAL_BLOCK_SUBSCRIBER_T

struct px4_internal_block_Subscriber_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  d_px4_internal_block_SampleTi_T SampleTimeHandler;
  pollfd_t eventStructObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // STRUCT_PX4_INTERNAL_BLOCK_SUBSCRIBER_T

#ifndef STRUCT_PX4_INTERNAL_BLOCK_PX4ACTUATO_T
#define STRUCT_PX4_INTERNAL_BLOCK_PX4ACTUATO_T

struct px4_internal_block_PX4Actuato_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T ValidMotorIdx[12];
  boolean_T ValidServoIdx[8];
};

#endif                                // STRUCT_PX4_INTERNAL_BLOCK_PX4ACTUATO_T

// Parameters (default storage)
typedef struct P_UorbRead_T_ P_UorbRead_T;

// Forward declaration for rtModel
typedef struct tag_RTM_UorbRead_T RT_MODEL_UorbRead_T;

#endif                                 // UORBREAD_TYPES_H_

//
// File trailer for generated code.
//
// [EOF]
//
