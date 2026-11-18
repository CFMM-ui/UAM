/*
 * PD_types.h
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

#ifndef PD_TYPES_H_
#define PD_TYPES_H_
#include "rtwtypes.h"
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

/* Parameters (default storage) */
typedef struct P_PD_T_ P_PD_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_PD_T RT_MODEL_PD_T;

#endif                                 /* PD_TYPES_H_ */
