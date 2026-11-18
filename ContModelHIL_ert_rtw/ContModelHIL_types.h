//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ContModelHIL_types.h
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
#ifndef CONTMODELHIL_TYPES_H_
#define CONTMODELHIL_TYPES_H_
#include "rtwtypes.h"
#include <uORB/topics/uam_states.h>
#ifndef DEFINED_TYPEDEF_FOR_STRUCT_CKTAE3DLO2KPTRTZY712SF_
#define DEFINED_TYPEDEF_FOR_STRUCT_CKTAE3DLO2KPTRTZY712SF_

struct struct_CKTAE3dLo2KptrTZY712sF
{
  real_T Kp[8];
  real_T Kd[8];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_DSZHUZTVFQ2JHMAMZLAOHG_
#define DEFINED_TYPEDEF_FOR_STRUCT_DSZHUZTVFQ2JHMAMZLAOHG_

struct struct_dsZHuztvFQ2jHmAMZlAOhG
{
  real_T E1[8];
  real_T E2[8];
  real_T E3[8];
  real_T E4[8];
  real_T MU1[8];
  real_T MU2[8];
  real_T MU3[8];
  real_T alpha[8];
  real_T beta[8];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_U7NBN6YWI9YZ24VWUWFOTG_
#define DEFINED_TYPEDEF_FOR_STRUCT_U7NBN6YWI9YZ24VWUWFOTG_

struct struct_u7NbN6ywI9YZ24VWuwFOtG
{
  real_T Tstamps[4];
  real_T Waypoints[32];
};

#endif

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

#ifndef STRUCT_SVOF13A781XHCKQKGCNSAFF_CONTM_T
#define STRUCT_SVOF13A781XHCKQKGCNSAFF_CONTM_T

struct sVoF13a781XHckqKGcnSAFF_ContM_T
{
  real_T breaks[6];
  real_T coefs[160];
};

#endif                                // STRUCT_SVOF13A781XHCKQKGCNSAFF_CONTM_T

#ifndef STRUCT_CELL_WRAP_CONTMODELHIL_T
#define STRUCT_CELL_WRAP_CONTMODELHIL_T

struct cell_wrap_ContModelHIL_T
{
  uint32_T f1[8];
};

#endif                                 // STRUCT_CELL_WRAP_CONTMODELHIL_T

#ifndef STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T
#define STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

struct robotics_slcore_internal_bloc_T
{
  boolean_T tunablePropertyChanged[5];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_ContModelHIL_T inputVarSize;
  real_T Waypoints[32];
  real_T TimePoints[4];
  real_T VelocityBoundaryCondition[32];
  real_T AccelerationBoundaryCondition[10];
  sVoF13a781XHckqKGcnSAFF_ContM_T PPStruct;
  sVoF13a781XHckqKGcnSAFF_ContM_T PPDStruct;
  sVoF13a781XHckqKGcnSAFF_ContM_T PPDDStruct;
  boolean_T PPFormUpdatedNeeded;
};

#endif                                // STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

// Parameters (default storage)
typedef struct P_ContModelHIL_T_ P_ContModelHIL_T;

// Forward declaration for rtModel
typedef struct tag_RTM_ContModelHIL_T RT_MODEL_ContModelHIL_T;

#endif                                 // CONTMODELHIL_TYPES_H_

//
// File trailer for generated code.
//
// [EOF]
//
