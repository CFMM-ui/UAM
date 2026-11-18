//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: DifAndCtrl_types.h
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
#ifndef DIFANDCTRL_TYPES_H_
#define DIFANDCTRL_TYPES_H_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_STRUCT_8GU0TGGHEYI782Q5TKCTYF_
#define DEFINED_TYPEDEF_FOR_STRUCT_8GU0TGGHEYI782Q5TKCTYF_

struct struct_8gU0TGGHeyi782Q5TKcTyF
{
  real_T Tstamps[2];
  real_T Waypoints[16];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_
#define DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_

struct struct_8iq6TggEG7Fvgh27g9ENz
{
  real_T T1max;
  real_T T2max;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_CKTAE3DLO2KPTRTZY712SF_
#define DEFINED_TYPEDEF_FOR_STRUCT_CKTAE3DLO2KPTRTZY712SF_

struct struct_CKTAE3dLo2KptrTZY712sF
{
  real_T Kp[8];
  real_T Kd[8];
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

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_BWZKDZIRABTIXEUCMOFADG_
#define DEFINED_TYPEDEF_FOR_STRUCT_BWZKDZIRABTIXEUCMOFADG_

struct struct_bwZkdZIRabTIxeUCMoFaDG
{
  real_T G1[8];
  real_T G2[8];
  real_T Q1[8];
  real_T Q2[8];
  real_T w1[8];
  real_T w2[8];
  real_T p1[8];
  real_T p2[8];
};

#endif

#ifndef STRUCT_SZOPACAE5DPHXOVJVDGDTWF_DIFAN_T
#define STRUCT_SZOPACAE5DPHXOVJVDGDTWF_DIFAN_T

struct sZoPacaE5DPHxovjVdgdtWF_DifAn_T
{
  real_T breaks[4];
  real_T coefs[96];
};

#endif                                // STRUCT_SZOPACAE5DPHXOVJVDGDTWF_DIFAN_T

#ifndef STRUCT_CELL_WRAP_DIFANDCTRL_T
#define STRUCT_CELL_WRAP_DIFANDCTRL_T

struct cell_wrap_DifAndCtrl_T
{
  uint32_T f1[8];
};

#endif                                 // STRUCT_CELL_WRAP_DIFANDCTRL_T

#ifndef STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T
#define STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

struct robotics_slcore_internal_bloc_T
{
  boolean_T tunablePropertyChanged[5];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_DifAndCtrl_T inputVarSize;
  real_T Waypoints[16];
  real_T TimePoints[2];
  real_T VelocityBoundaryCondition[16];
  real_T AccelerationBoundaryCondition[10];
  sZoPacaE5DPHxovjVdgdtWF_DifAn_T PPStruct;
  sZoPacaE5DPHxovjVdgdtWF_DifAn_T PPDStruct;
  sZoPacaE5DPHxovjVdgdtWF_DifAn_T PPDDStruct;
  boolean_T PPFormUpdatedNeeded;
};

#endif                                // STRUCT_ROBOTICS_SLCORE_INTERNAL_BLOC_T

// Parameters (default storage)
typedef struct P_DifAndCtrl_T_ P_DifAndCtrl_T;

// Forward declaration for rtModel
typedef struct tag_RTM_DifAndCtrl_T RT_MODEL_DifAndCtrl_T;

#endif                                 // DIFANDCTRL_TYPES_H_

//
// File trailer for generated code.
//
// [EOF]
//
