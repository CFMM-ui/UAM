//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Orbs_types.h
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
#ifndef ORBS_TYPES_H_
#define ORBS_TYPES_H_
#include "rtwtypes.h"
#include <uORB/topics/vehicle_global_position.h>
#ifndef STRUCT_PX4_INTERNAL_BLOCK_PUBLISHER__T
#define STRUCT_PX4_INTERNAL_BLOCK_PUBLISHER__T

struct px4_internal_block_Publisher__T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  orb_advert_t orbAdvertiseObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // STRUCT_PX4_INTERNAL_BLOCK_PUBLISHER__T

// Parameters (default storage)
typedef struct P_Orbs_T_ P_Orbs_T;

// Forward declaration for rtModel
typedef struct tag_RTM_Orbs_T RT_MODEL_Orbs_T;

#endif                                 // ORBS_TYPES_H_

//
// File trailer for generated code.
//
// [EOF]
//
