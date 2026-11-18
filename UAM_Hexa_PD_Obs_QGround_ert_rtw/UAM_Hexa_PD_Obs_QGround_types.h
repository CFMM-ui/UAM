//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: UAM_Hexa_PD_Obs_QGround_types.h
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
#ifndef UAM_HEXA_PD_OBS_QGROUND_TYPES_H_
#define UAM_HEXA_PD_OBS_QGROUND_TYPES_H_
#include "rtwtypes.h"
#include "MW_Parameter.h"
#ifndef DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_
#define DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_

struct struct_8iq6TggEG7Fvgh27g9ENz
{
  real_T T1max;
  real_T T2max;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_JL8G2IM4LW6J1BY0KTXLFE_
#define DEFINED_TYPEDEF_FOR_STRUCT_JL8G2IM4LW6J1BY0KTXLFE_

struct struct_JL8g2iM4Lw6J1bY0kTxLfE
{
  real_T l1_dim;
  real_T l2_dim;
  real_T Hexa_to_joint_L;
  real_T Mass1;
  real_T Mass2;
  real_T Inertia1[9];
  real_T Inertia2[9];
  real_T MC1;
  real_T MC2;
  struct_8iq6TggEG7Fvgh27g9ENz Servos;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_MBCKNH9NPGZZNAHCPBRZ5_
#define DEFINED_TYPEDEF_FOR_STRUCT_MBCKNH9NPGZZNAHCPBRZ5_

struct struct_MBcKnh9NPgZzNahcpBRZ5
{
  real_T Radius;
  real_T Mass;
  real_T Time[2];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_Z1YY0B1SIREJJ6ODUGXXCE_
#define DEFINED_TYPEDEF_FOR_STRUCT_Z1YY0B1SIREJJ6ODUGXXCE_

struct struct_Z1yy0b1SiRejj6ODUGxXCE
{
  real_T Mass;
  real_T Inertia[9];
  real_T invallo[36];
  real_T kT;
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

#ifndef STRUCT_PX4_INTERNAL_BLOCK_PARAMETERU_T
#define STRUCT_PX4_INTERNAL_BLOCK_PARAMETERU_T

struct px4_internal_block_ParameterU_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Param_Handle MW_PARAMHANDLE;
};

#endif                                // STRUCT_PX4_INTERNAL_BLOCK_PARAMETERU_T

#ifndef STRUCT_SVOF13A781XHCKQKGCNSAFF_UAM_H_T
#define STRUCT_SVOF13A781XHCKQKGCNSAFF_UAM_H_T

struct sVoF13a781XHckqKGcnSAFF_UAM_H_T
{
  real_T breaks[6];
  real_T coefs[160];
};

#endif                                // STRUCT_SVOF13A781XHCKQKGCNSAFF_UAM_H_T

#ifndef STRUCT_CELL_WRAP_UAM_HEXA_PD_OBS_QGR_T
#define STRUCT_CELL_WRAP_UAM_HEXA_PD_OBS_QGR_T

struct cell_wrap_UAM_Hexa_PD_Obs_QGr_T
{
  uint32_T f1[8];
};

#endif                                // STRUCT_CELL_WRAP_UAM_HEXA_PD_OBS_QGR_T

#ifndef STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T
#define STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

struct robotics_slcore_internal_bloc_T
{
  boolean_T tunablePropertyChanged[5];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_UAM_Hexa_PD_Obs_QGr_T inputVarSize;
  real_T Waypoints[32];
  real_T TimePoints[4];
  real_T VelocityBoundaryCondition[32];
  real_T AccelerationBoundaryCondition[10];
  sVoF13a781XHckqKGcnSAFF_UAM_H_T PPStruct;
  sVoF13a781XHckqKGcnSAFF_UAM_H_T PPDStruct;
  sVoF13a781XHckqKGcnSAFF_UAM_H_T PPDDStruct;
  boolean_T PPFormUpdatedNeeded;
};

#endif                                // STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

// Parameters (default storage)
typedef struct P_UAM_Hexa_PD_Obs_QGround_T_ P_UAM_Hexa_PD_Obs_QGround_T;

// Forward declaration for rtModel
typedef struct tag_RTM_UAM_Hexa_PD_Obs_QGrou_T RT_MODEL_UAM_Hexa_PD_Obs_QGro_T;

#endif                                 // UAM_HEXA_PD_OBS_QGROUND_TYPES_H_

//
// File trailer for generated code.
//
// [EOF]
//
