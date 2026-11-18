/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Solver Configuration'.
 */

#include <math.h>
#include <string.h>
#include "pm_std.h"
#include "pm_default_allocator.h"
#include "sm_std.h"
#include "ne_std.h"
#include "ssc_dae.h"
#include "sm_ssci_run_time_errors.h"
#include "sm_RuntimeDerivedValuesBundle.h"
#include "sm_CTarget.h"

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_setTargets(const
  RuntimeDerivedValuesBundle *rtdv, CTarget *targets)
{
  (void) rtdv;
  (void) targets;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_resetAsmStateVector(const void *mech,
  double *state)
{
  double xx[1];
  (void) mech;
  xx[0] = 0.0;

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(state + i) = xx[0];
  }

  state[3] = 1.0;

  {
    size_t i;
    for (i = 0; i < 25; ++i)
      *(state + 4 + i) = xx[0];
  }
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_initializeTrackedAngleState(const void
  *mech, const RuntimeDerivedValuesBundle *rtdv, const int *modeVector, const
  double *motionData, double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  (void) state;
  (void) modeVector;
  (void) motionData;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeDiscreteState(const void *mech,
  const RuntimeDerivedValuesBundle *rtdv, const int *modeVector, double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  (void) state;
  (void) modeVector;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_adjustPosition(const void *mech, const
  double *dofDeltas, double *state)
{
  double xx[11];
  (void) mech;
  memcpy(xx + 0, state + 3, 4 * sizeof(double));
  memcpy(xx + 4, dofDeltas + 3, 3 * sizeof(double));
  pm_math_Quaternion_compDeriv_ra(xx + 0, xx + 4, xx + 7);
  xx[0] = state[3] + xx[7];
  xx[1] = state[4] + xx[8];
  xx[2] = state[5] + xx[9];
  xx[3] = state[6] + xx[10];
  xx[4] = sqrt(xx[0] * xx[0] + xx[1] * xx[1] + xx[2] * xx[2] + xx[3] * xx[3]);
  xx[5] = 1.0e-64;
  if (xx[5] > xx[4])
    xx[4] = xx[5];
  state[0] = state[0] + dofDeltas[0];
  state[1] = state[1] + dofDeltas[1];
  state[2] = state[2] + dofDeltas[2];
  state[3] = xx[0] / xx[4];
  state[4] = xx[1] / xx[4];
  state[5] = xx[2] / xx[4];
  state[6] = xx[3] / xx[4];
  state[13] = state[13] + dofDeltas[6];
  state[15] = state[15] + dofDeltas[7];
  state[17] = state[17] + dofDeltas[8];
  state[19] = state[19] + dofDeltas[9];
  state[21] = state[21] + dofDeltas[10];
  state[23] = state[23] + dofDeltas[11];
  state[25] = state[25] + dofDeltas[12];
  state[27] = state[27] + dofDeltas[13];
}

static void perturbAsmJointPrimitiveState_0_0(double mag, double *state)
{
  state[0] = state[0] + mag;
}

static void perturbAsmJointPrimitiveState_0_0v(double mag, double *state)
{
  state[0] = state[0] + mag;
  state[7] = state[7] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_0_1(double mag, double *state)
{
  state[1] = state[1] + mag;
}

static void perturbAsmJointPrimitiveState_0_1v(double mag, double *state)
{
  state[1] = state[1] + mag;
  state[8] = state[8] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_0_2(double mag, double *state)
{
  state[2] = state[2] + mag;
}

static void perturbAsmJointPrimitiveState_0_2v(double mag, double *state)
{
  state[2] = state[2] + mag;
  state[9] = state[9] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_0_3(double mag, double *state)
{
  double xx[15];
  xx[0] = 1.0;
  xx[1] = fabs(mag);
  xx[2] = xx[0] / (xx[1] - floor(xx[1]) + 1.0e-9);
  xx[1] = sin(xx[2]);
  xx[3] = 0.0;
  xx[4] = cos(xx[2]);
  xx[5] = sin(2.0 * xx[2]);
  xx[2] = 0.5 * mag;
  xx[6] = sqrt(xx[1] * xx[1] + xx[4] * xx[4] + xx[5] * xx[5]);
  xx[7] = xx[6] == 0.0 ? 0.0 : xx[1] / xx[6];
  xx[8] = sin(xx[2]);
  xx[9] = xx[6] == 0.0 ? 0.0 : xx[4] / xx[6];
  xx[10] = xx[6] == 0.0 ? 0.0 : xx[5] / xx[6];
  xx[11] = xx[1] == xx[3] && xx[4] == xx[3] && xx[5] == xx[3] ? xx[0] : cos(xx[2]);
  xx[12] = xx[7] * xx[8];
  xx[13] = xx[9] * xx[8];
  xx[14] = xx[10] * xx[8];
  memcpy(xx + 0, state + 3, 4 * sizeof(double));
  pm_math_Quaternion_compose_ra(xx + 11, xx + 0, xx + 4);
  memcpy(state + 3, xx + 4, 4 * sizeof(double));
}

static void perturbAsmJointPrimitiveState_0_3v(double mag, double *state)
{
  double xx[15];
  xx[0] = 1.0;
  xx[1] = fabs(mag);
  xx[2] = xx[0] / (xx[1] - floor(xx[1]) + 1.0e-9);
  xx[1] = sin(xx[2]);
  xx[3] = 0.0;
  xx[4] = cos(xx[2]);
  xx[5] = sin(2.0 * xx[2]);
  xx[2] = 0.5 * mag;
  xx[6] = sqrt(xx[1] * xx[1] + xx[4] * xx[4] + xx[5] * xx[5]);
  xx[7] = xx[6] == 0.0 ? 0.0 : xx[1] / xx[6];
  xx[8] = sin(xx[2]);
  xx[9] = xx[6] == 0.0 ? 0.0 : xx[4] / xx[6];
  xx[10] = xx[6] == 0.0 ? 0.0 : xx[5] / xx[6];
  xx[11] = xx[1] == xx[3] && xx[4] == xx[3] && xx[5] == xx[3] ? xx[0] : cos(xx[2]);
  xx[12] = xx[7] * xx[8];
  xx[13] = xx[9] * xx[8];
  xx[14] = xx[10] * xx[8];
  memcpy(xx + 3, state + 3, 4 * sizeof(double));
  pm_math_Quaternion_compose_ra(xx + 11, xx + 3, xx + 7);
  memcpy(state + 3, xx + 7, 4 * sizeof(double));
  state[10] = state[10] + 1.2 * mag;
  state[11] = state[11] - xx[2];
  state[12] = state[12] + 0.9 * mag;
}

static void perturbAsmJointPrimitiveState_1_0(double mag, double *state)
{
  state[13] = state[13] + mag;
}

static void perturbAsmJointPrimitiveState_1_0v(double mag, double *state)
{
  state[13] = state[13] + mag;
  state[14] = state[14] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_2_0(double mag, double *state)
{
  state[15] = state[15] + mag;
}

static void perturbAsmJointPrimitiveState_2_0v(double mag, double *state)
{
  state[15] = state[15] + mag;
  state[16] = state[16] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_3_0(double mag, double *state)
{
  state[17] = state[17] + mag;
}

static void perturbAsmJointPrimitiveState_3_0v(double mag, double *state)
{
  state[17] = state[17] + mag;
  state[18] = state[18] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_4_0(double mag, double *state)
{
  state[19] = state[19] + mag;
}

static void perturbAsmJointPrimitiveState_4_0v(double mag, double *state)
{
  state[19] = state[19] + mag;
  state[20] = state[20] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_5_0(double mag, double *state)
{
  state[21] = state[21] + mag;
}

static void perturbAsmJointPrimitiveState_5_0v(double mag, double *state)
{
  state[21] = state[21] + mag;
  state[22] = state[22] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_6_0(double mag, double *state)
{
  state[23] = state[23] + mag;
}

static void perturbAsmJointPrimitiveState_6_0v(double mag, double *state)
{
  state[23] = state[23] + mag;
  state[24] = state[24] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_7_0(double mag, double *state)
{
  state[25] = state[25] + mag;
}

static void perturbAsmJointPrimitiveState_7_0v(double mag, double *state)
{
  state[25] = state[25] + mag;
  state[26] = state[26] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_8_0(double mag, double *state)
{
  state[27] = state[27] + mag;
}

static void perturbAsmJointPrimitiveState_8_0v(double mag, double *state)
{
  state[27] = state[27] + mag;
  state[28] = state[28] - 0.875 * mag;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_perturbAsmJointPrimitiveState(const void
  *mech, size_t stageIdx, size_t primIdx, double mag, boolean_T
  doPerturbVelocity, double *state)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) mag;
  (void) doPerturbVelocity;
  (void) state;
  switch ((stageIdx * 6 + primIdx) * 2 + (doPerturbVelocity ? 1 : 0))
  {
   case 0:
    perturbAsmJointPrimitiveState_0_0(mag, state);
    break;

   case 1:
    perturbAsmJointPrimitiveState_0_0v(mag, state);
    break;

   case 2:
    perturbAsmJointPrimitiveState_0_1(mag, state);
    break;

   case 3:
    perturbAsmJointPrimitiveState_0_1v(mag, state);
    break;

   case 4:
    perturbAsmJointPrimitiveState_0_2(mag, state);
    break;

   case 5:
    perturbAsmJointPrimitiveState_0_2v(mag, state);
    break;

   case 6:
    perturbAsmJointPrimitiveState_0_3(mag, state);
    break;

   case 7:
    perturbAsmJointPrimitiveState_0_3v(mag, state);
    break;

   case 12:
    perturbAsmJointPrimitiveState_1_0(mag, state);
    break;

   case 13:
    perturbAsmJointPrimitiveState_1_0v(mag, state);
    break;

   case 24:
    perturbAsmJointPrimitiveState_2_0(mag, state);
    break;

   case 25:
    perturbAsmJointPrimitiveState_2_0v(mag, state);
    break;

   case 36:
    perturbAsmJointPrimitiveState_3_0(mag, state);
    break;

   case 37:
    perturbAsmJointPrimitiveState_3_0v(mag, state);
    break;

   case 48:
    perturbAsmJointPrimitiveState_4_0(mag, state);
    break;

   case 49:
    perturbAsmJointPrimitiveState_4_0v(mag, state);
    break;

   case 60:
    perturbAsmJointPrimitiveState_5_0(mag, state);
    break;

   case 61:
    perturbAsmJointPrimitiveState_5_0v(mag, state);
    break;

   case 72:
    perturbAsmJointPrimitiveState_6_0(mag, state);
    break;

   case 73:
    perturbAsmJointPrimitiveState_6_0v(mag, state);
    break;

   case 84:
    perturbAsmJointPrimitiveState_7_0(mag, state);
    break;

   case 85:
    perturbAsmJointPrimitiveState_7_0v(mag, state);
    break;

   case 96:
    perturbAsmJointPrimitiveState_8_0(mag, state);
    break;

   case 97:
    perturbAsmJointPrimitiveState_8_0v(mag, state);
    break;
  }
}

static void computePosDofBlendMatrix_0_3(const double *state, int partialType,
  double *matrix)
{
  double xx[20];
  xx[0] = 9.87654321;
  xx[1] = 2.0;
  xx[2] = xx[1] * (state[4] * state[5] - state[3] * state[6]);
  xx[3] = xx[2] * xx[2];
  xx[4] = 1.0;
  xx[5] = (state[3] * state[3] + state[4] * state[4]) * xx[1] - xx[4];
  xx[6] = xx[5] * xx[5];
  xx[7] = sqrt(xx[3] + xx[6]);
  xx[8] = xx[7] == 0.0 ? 0.0 : - xx[2] / xx[7];
  xx[9] = xx[6] + xx[3];
  xx[3] = sqrt(xx[9]);
  xx[6] = xx[3] == 0.0 ? 0.0 : xx[5] / xx[3];
  xx[10] = 0.0;
  xx[11] = (state[4] * state[6] + state[3] * state[5]) * xx[1];
  xx[1] = sqrt(xx[9] + xx[11] * xx[11]);
  xx[12] = xx[1] == 0.0 ? 0.0 : xx[5] / xx[1];
  xx[14] = xx[8];
  xx[15] = xx[6];
  xx[16] = xx[10];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 17 + i) = xx[8];
  }

  xx[19] = xx[12];
  xx[6] = xx[13 + (partialType)];
  xx[8] = xx[7] == 0.0 ? 0.0 : xx[5] / xx[7];
  xx[7] = xx[3] == 0.0 ? 0.0 : xx[2] / xx[3];
  xx[3] = xx[1] == 0.0 ? 0.0 : xx[2] / xx[1];
  xx[13] = xx[8];
  xx[14] = xx[7];
  xx[15] = xx[10];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 16 + i) = xx[8];
  }

  xx[18] = xx[3];
  xx[2] = xx[12 + (partialType)];
  xx[3] = xx[1] == 0.0 ? 0.0 : xx[11] / xx[1];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 13 + i) = xx[10];
  }

  xx[15] = xx[4];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 16 + i) = xx[10];
  }

  xx[18] = xx[3];
  xx[1] = xx[12 + (partialType)];
  xx[3] = xx[11] * xx[5];
  xx[5] = sqrt(xx[9] * xx[9] + xx[3] * xx[3]);
  xx[7] = xx[5] == 0.0 ? 0.0 : xx[9] / xx[5];

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(xx + 12 + i) = xx[10];
  }

  xx[15] = xx[7];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 16 + i) = xx[10];
  }

  xx[7] = xx[11 + (partialType)];

  {
    size_t i;
    for (i = 0; i < 6; ++i)
      *(xx + 12 + i) = xx[10];
  }

  xx[8] = xx[11 + (partialType)];
  xx[9] = xx[5] == 0.0 ? 0.0 : xx[3] / xx[5];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 12 + i) = xx[4];
  }

  xx[14] = xx[10];
  memcpy(xx + 15, xx + 9, 2 * sizeof(double));
  xx[17] = xx[10];
  xx[0] = xx[11 + (partialType)];
  matrix[0] = xx[6];
  matrix[1] = xx[2];
  matrix[2] = xx[1];
  memcpy(matrix + 3, xx + 7, 2 * sizeof(double));
  matrix[5] = xx[0];

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(matrix + 6 + i) = xx[8];
  }
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computePosDofBlendMatrix(const void
  *mech, size_t stageIdx, size_t primIdx, const double *state, int partialType,
  double *matrix)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) state;
  (void) partialType;
  (void) matrix;
  switch ((stageIdx * 6 + primIdx))
  {
   case 3:
    computePosDofBlendMatrix_0_3(state, partialType, matrix);
    break;
  }
}

static void computeVelDofBlendMatrix_0_3(const double *state, int partialType,
  double *matrix)
{
  double xx[15];
  (void) state;
  xx[0] = 9.87654321;
  xx[1] = 0.0;
  xx[2] = 1.0;
  memcpy(xx + 4, xx + 1, 2 * sizeof(double));
  memcpy(xx + 6, xx + 1, 2 * sizeof(double));
  memcpy(xx + 8, xx + 1, 2 * sizeof(double));
  xx[10] = xx[3 + (partialType)];
  xx[4] = xx[2];

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(xx + 5 + i) = xx[1];
  }

  xx[8] = xx[2];
  xx[9] = xx[1];
  xx[11] = xx[3 + (partialType)];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 4 + i) = xx[1];
  }

  xx[6] = xx[2];

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(xx + 7 + i) = xx[1];
  }

  xx[12] = xx[3 + (partialType)];

  {
    size_t i;
    for (i = 0; i < 6; ++i)
      *(xx + 4 + i) = xx[1];
  }

  xx[13] = xx[3 + (partialType)];

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(xx + 4 + i) = xx[1];
  }

  xx[7] = xx[2];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 8 + i) = xx[1];
  }

  xx[14] = xx[3 + (partialType)];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 4 + i) = xx[2];
  }

  {
    size_t i;
    for (i = 0; i < 4; ++i)
      *(xx + 6 + i) = xx[1];
  }

  xx[0] = xx[3 + (partialType)];
  memcpy(matrix, xx + 10, 5 * sizeof(double));
  matrix[5] = xx[0];

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(matrix + 6 + i) = xx[13];
  }
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeVelDofBlendMatrix(const void
  *mech, size_t stageIdx, size_t primIdx, const double *state, int partialType,
  double *matrix)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) state;
  (void) partialType;
  (void) matrix;
  switch ((stageIdx * 6 + primIdx))
  {
   case 3:
    computeVelDofBlendMatrix_0_3(state, partialType, matrix);
    break;
  }
}

static void projectPartiallyTargetedPos_0_3(const double *origState, int
  partialType, double *state)
{
  boolean_T bb[2];
  double xx[17];
  xx[0] = 2.0;
  xx[1] = (state[4] * state[6] + state[3] * state[5]) * xx[0];
  xx[2] = 0.99999999999999;
  bb[0] = fabs(xx[1]) > xx[2];
  xx[3] = 1.570796326794897;
  if (xx[1] < 0.0)
    xx[4] = -1.0;
  else if (xx[1] > 0.0)
    xx[4] = +1.0;
  else
    xx[4] = 0.0;
  xx[5] = fabs(xx[1]) > 1.0 ? atan2(xx[1], 0.0) : asin(xx[1]);
  xx[1] = bb[0] ? xx[3] * xx[4] : xx[5];
  xx[5] = (origState[4] * origState[6] + origState[3] * origState[5]) * xx[0];
  bb[1] = fabs(xx[5]) > xx[2];
  if (xx[5] < 0.0)
    xx[2] = -1.0;
  else if (xx[5] > 0.0)
    xx[2] = +1.0;
  else
    xx[2] = 0.0;
  xx[6] = fabs(xx[5]) > 1.0 ? atan2(xx[5], 0.0) : asin(xx[5]);
  xx[5] = bb[1] ? xx[3] * xx[2] : xx[6];

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 6 + i) = xx[1];
  }

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 8 + i) = xx[5];
  }

  {
    size_t i;
    for (i = 0; i < 2; ++i)
      *(xx + 10 + i) = xx[1];
  }

  xx[12] = xx[5];
  xx[1] = xx[6 + (partialType)];
  xx[3] = cos(xx[1]);
  xx[5] = 0.5;
  xx[6] = state[5] * state[6];
  xx[7] = state[3] * state[4];
  xx[8] = state[3] * state[3];
  xx[9] = 1.0;
  xx[10] = (xx[8] + state[5] * state[5]) * xx[0] - xx[9];
  xx[11] = (xx[6] + xx[7]) * xx[0];
  xx[10] = (xx[11] == 0.0 && xx[10] == 0.0) ? 0.0 : atan2(xx[11], xx[10]);
  xx[11] = (xx[8] + state[6] * state[6]) * xx[0] - xx[9];
  xx[12] = - (xx[0] * (xx[6] - xx[7]));
  xx[11] = (xx[12] == 0.0 && xx[11] == 0.0) ? 0.0 : atan2(xx[12], xx[11]);
  xx[6] = bb[0] ? xx[5] * xx[10] : xx[11];
  xx[7] = (xx[8] + state[4] * state[4]) * xx[0] - xx[9];
  xx[10] = - (xx[0] * (state[4] * state[5] - state[3] * state[6]));
  xx[7] = (xx[10] == 0.0 && xx[7] == 0.0) ? 0.0 : atan2(xx[10], xx[7]);
  xx[8] = bb[0] ? xx[4] * xx[6] : xx[7];
  xx[4] = origState[5] * origState[6];
  xx[7] = origState[3] * origState[4];
  xx[10] = origState[3] * origState[3];
  xx[11] = (xx[10] + origState[5] * origState[5]) * xx[0] - xx[9];
  xx[12] = (xx[4] + xx[7]) * xx[0];
  xx[11] = (xx[12] == 0.0 && xx[11] == 0.0) ? 0.0 : atan2(xx[12], xx[11]);
  xx[12] = (xx[10] + origState[6] * origState[6]) * xx[0] - xx[9];
  xx[13] = - (xx[0] * (xx[4] - xx[7]));
  xx[12] = (xx[13] == 0.0 && xx[12] == 0.0) ? 0.0 : atan2(xx[13], xx[12]);
  xx[4] = bb[1] ? xx[5] * xx[11] : xx[12];
  xx[5] = (xx[10] + origState[4] * origState[4]) * xx[0] - xx[9];
  xx[7] = - (xx[0] * (origState[4] * origState[5] - origState[3] * origState[6]));
  xx[5] = (xx[7] == 0.0 && xx[5] == 0.0) ? 0.0 : atan2(xx[7], xx[5]);
  xx[0] = bb[1] ? xx[2] * xx[4] : xx[5];

  {
    size_t i;
    for (i = 0; i < 4; ++i)
      *(xx + 9 + i) = xx[8];
  }

  {
    size_t i;
    for (i = 0; i < 3; ++i)
      *(xx + 13 + i) = xx[0];
  }

  xx[0] = xx[9 + (partialType)];
  xx[2] = cos(xx[0]);
  xx[7] = xx[6];
  xx[8] = xx[4];
  xx[9] = xx[6];
  xx[10] = xx[4];
  xx[11] = xx[6];
  xx[12] = xx[4];
  xx[13] = xx[6];
  xx[4] = xx[7 + (partialType)];
  xx[5] = cos(xx[4]);
  xx[6] = sin(xx[0]);
  xx[0] = sin(xx[4]);
  xx[4] = xx[2] * xx[0];
  xx[7] = sin(xx[1]);
  xx[1] = xx[5] * xx[2];
  xx[8] = xx[3] * xx[2];
  xx[9] = xx[5] * xx[6] + xx[4] * xx[7];
  xx[10] = xx[0] * xx[6] - xx[1] * xx[7];
  xx[11] = - (xx[3] * xx[6]);
  xx[12] = xx[1] - xx[0] * xx[7] * xx[6];
  xx[13] = xx[4] + xx[5] * xx[7] * xx[6];
  xx[14] = xx[7];
  xx[15] = - (xx[3] * xx[0]);
  xx[16] = xx[5] * xx[3];
  pm_math_Quaternion_Matrix3x3Ctor_ra(xx + 8, xx + 0);
  memcpy(state + 3, xx + 0, 4 * sizeof(double));
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_projectPartiallyTargetedPos(const void
  *mech, size_t stageIdx, size_t primIdx, const double *origState, int
  partialType, double *state)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) origState;
  (void) partialType;
  (void) state;
  switch ((stageIdx * 6 + primIdx))
  {
   case 3:
    projectPartiallyTargetedPos_0_3(origState, partialType, state);
    break;
  }
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_propagateMotion(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, const double *state, double *motionData)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[134];
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  memcpy(xx + 0, state + 3, 4 * sizeof(double));
  xx[4] = - 7.953457878587247e-5;
  xx[5] = 1.037555182289732e-5;
  xx[6] = 0.7062800008593415;
  xx[7] = 0.7079325913904003;
  pm_math_Quaternion_composeInverse_ra(xx + 0, xx + 4, xx + 8);
  xx[0] = 1.525792495965325e-4;
  xx[1] = 1.303297674270197e-3;
  xx[2] = 6.481520710989565e-4;
  xx[12] = - xx[0];
  xx[13] = xx[1];
  xx[14] = - xx[2];
  pm_math_Quaternion_xform_ra(xx + 8, xx + 12, xx + 15);
  xx[18] = - 0.7070583871109583;
  xx[19] = 5.679508889285256e-4;
  xx[20] = - 0.7070973528450791;
  xx[21] = - 9.024868271603981e-3;
  xx[3] = 0.5;
  xx[12] = xx[3] * state[13];
  xx[13] = 8.029196371983453e-6;
  xx[14] = sin(xx[12]);
  xx[22] = 0.01346899178434196;
  xx[23] = 0.999909288983678;
  xx[24] = cos(xx[12]);
  xx[25] = xx[13] * xx[14];
  xx[26] = xx[22] * xx[14];
  xx[27] = - (xx[23] * xx[14]);
  pm_math_Quaternion_compose_ra(xx + 18, xx + 24, xx + 28);
  xx[18] = 2.20745382934972e-5;
  xx[19] = 0.1149240934718477;
  xx[20] = - 0.02011850541179939;
  pm_math_Quaternion_xform_ra(xx + 28, xx + 18, xx + 24);
  xx[12] = - (0.02189445492212523 + xx[24]);
  xx[14] = - (0.08181860544085766 + xx[25]);
  xx[18] = - (8.396436632778668e-4 + xx[26]);
  xx[24] = - 0.9698533317008132;
  xx[25] = 0.08771859952513025;
  xx[26] = 0.2216592853450177;
  xx[27] = 0.05056800872605433;
  xx[19] = xx[3] * state[15];
  xx[20] = 0.4395758590350312;
  xx[21] = sin(xx[19]);
  xx[32] = 0.1609111459511914;
  xx[33] = 0.8836745256384213;
  xx[34] = cos(xx[19]);
  xx[35] = - (xx[20] * xx[21]);
  xx[36] = xx[32] * xx[21];
  xx[37] = - (xx[33] * xx[21]);
  pm_math_Quaternion_compose_ra(xx + 24, xx + 34, xx + 38);
  xx[24] = - 9.105317956012418e-3;
  xx[25] = 0.08932765445918953;
  xx[26] = - 0.01618853665892053;
  pm_math_Quaternion_xform_ra(xx + 38, xx + 24, xx + 34);
  xx[19] = 1.390594030460353e-5 - xx[34];
  xx[21] = - (0.05585658930563103 + xx[35]);
  xx[24] = - (0.02206892601527486 + xx[36]);
  xx[34] = - 0.6176095297070431;
  xx[35] = - 0.7656667455115048;
  xx[36] = 0.01809115169385729;
  xx[37] = 0.1788452232050284;
  xx[25] = xx[3] * state[17];
  xx[26] = 9.594608608490126e-5;
  xx[27] = sin(xx[25]);
  xx[42] = 1.776993604830533e-6;
  xx[43] = 0.9999999953955954;
  xx[44] = cos(xx[25]);
  xx[45] = xx[26] * xx[27];
  xx[46] = xx[42] * xx[27];
  xx[47] = xx[43] * xx[27];
  pm_math_Quaternion_compose_ra(xx + 34, xx + 44, xx + 48);
  xx[34] = 5.327308204667181e-7;
  xx[35] = 7.053611160355946e-7;
  xx[36] = 2.636540714786262e-3;
  pm_math_Quaternion_xform_ra(xx + 48, xx + 34, xx + 44);
  xx[25] = - (0.1264591662103758 + xx[44]);
  xx[27] = 0.06248829547551044 - xx[45];
  xx[37] = 0.2356070507097101 - xx[46];
  xx[44] = - 0.6392954636561274;
  xx[45] = - 0.7508228867239062;
  xx[46] = - 0.1512720030010929;
  xx[47] = - 0.06843306239176812;
  xx[52] = xx[3] * state[19];
  xx[53] = sin(xx[52]);
  xx[54] = cos(xx[52]);
  xx[55] = xx[26] * xx[53];
  xx[56] = xx[42] * xx[53];
  xx[57] = xx[43] * xx[53];
  pm_math_Quaternion_compose_ra(xx + 44, xx + 54, xx + 58);
  pm_math_Quaternion_xform_ra(xx + 58, xx + 34, xx + 44);
  xx[47] = 0.1262020412183443 - xx[44];
  xx[52] = 0.0625130446900017 - xx[45];
  xx[44] = 0.2355749531986704 - xx[46];
  xx[53] = - 0.682124747335163;
  xx[54] = - 0.478896746705338;
  xx[55] = 0.3174716913482926;
  xx[56] = - 0.4523001882162326;
  xx[45] = xx[3] * state[21];
  xx[46] = 9.594608608490127e-5;
  xx[57] = sin(xx[45]);
  xx[62] = 1.776993604830524e-6;
  xx[63] = cos(xx[45]);
  xx[64] = xx[46] * xx[57];
  xx[65] = xx[62] * xx[57];
  xx[66] = xx[43] * xx[57];
  pm_math_Quaternion_compose_ra(xx + 53, xx + 63, xx + 67);
  pm_math_Quaternion_xform_ra(xx + 67, xx + 34, xx + 53);
  xx[45] = 0.2674702776869563 - xx[53];
  xx[56] = 0.06309886405061478 - xx[54];
  xx[53] = - (9.180040957230233e-3 + xx[55]);
  xx[63] = - 0.6356589735212261;
  xx[64] = - 0.75676425753846;
  xx[65] = 0.1178684678153821;
  xx[66] = 0.0967085941840715;
  xx[54] = xx[3] * state[23];
  xx[55] = sin(xx[54]);
  xx[71] = cos(xx[54]);
  xx[72] = xx[26] * xx[55];
  xx[73] = xx[42] * xx[55];
  xx[74] = xx[43] * xx[55];
  pm_math_Quaternion_compose_ra(xx + 63, xx + 71, xx + 75);
  pm_math_Quaternion_xform_ra(xx + 75, xx + 34, xx + 63);
  xx[54] = 0.1411118266961335 - xx[63];
  xx[55] = 0.06359787447147908 - xx[64];
  xx[57] = - (0.2279744198473475 + xx[65]);
  xx[63] = - 0.6377635698081449;
  xx[64] = - 0.7537560813690898;
  xx[65] = - 0.1359114519880532;
  xx[66] = - 0.08147070665696939;
  xx[71] = xx[3] * state[25];
  xx[72] = sin(xx[71]);
  xx[79] = cos(xx[71]);
  xx[80] = xx[26] * xx[72];
  xx[81] = xx[42] * xx[72];
  xx[82] = xx[43] * xx[72];
  pm_math_Quaternion_compose_ra(xx + 63, xx + 79, xx + 71);
  pm_math_Quaternion_xform_ra(xx + 71, xx + 34, xx + 63);
  xx[66] = - (0.1414869399826881 + xx[63]);
  xx[79] = 0.06357019274873783 - xx[64];
  xx[63] = - (0.2279385191361722 + xx[65]);
  xx[80] = - 0.6719536063254669;
  xx[81] = - 0.4717596808874458;
  xx[82] = 0.3279845637595254;
  xx[83] = - 0.46727644962126;
  xx[64] = xx[3] * state[27];
  xx[3] = sin(xx[64]);
  xx[84] = cos(xx[64]);
  xx[85] = xx[46] * xx[3];
  xx[86] = xx[62] * xx[3];
  xx[87] = xx[43] * xx[3];
  pm_math_Quaternion_compose_ra(xx + 80, xx + 84, xx + 88);
  pm_math_Quaternion_xform_ra(xx + 88, xx + 34, xx + 80);
  xx[3] = - (0.2677896964205858 + xx[80]);
  xx[34] = 0.06304643311338254 - xx[81];
  xx[35] = - (9.112042735014963e-3 + xx[82]);
  memcpy(xx + 80, state + 10, 3 * sizeof(double));
  pm_math_Quaternion_xform_ra(xx + 4, xx + 80, xx + 83);
  memcpy(xx + 4, state + 7, 3 * sizeof(double));
  pm_math_Quaternion_inverseXform_ra(xx + 8, xx + 4, xx + 80);
  xx[4] = xx[0];
  xx[5] = - xx[1];
  xx[6] = xx[2];
  pm_math_Vector3_cross_ra(xx + 83, xx + 4, xx + 0);
  xx[4] = xx[80] + xx[0];
  xx[5] = xx[81] + xx[1];
  xx[0] = xx[82] + xx[2];
  pm_math_Quaternion_inverseXform_ra(xx + 28, xx + 83, xx + 80);
  xx[1] = xx[80] + xx[13] * state[14];
  xx[2] = xx[81] + xx[22] * state[14];
  xx[6] = xx[82] - xx[23] * state[14];
  xx[80] = xx[12];
  xx[81] = xx[14];
  xx[82] = xx[18];
  pm_math_Vector3_cross_ra(xx + 83, xx + 80, xx + 92);
  xx[80] = xx[92] + xx[4];
  xx[81] = xx[93] + xx[5];
  xx[82] = xx[94] + xx[0];
  pm_math_Quaternion_inverseXform_ra(xx + 28, xx + 80, xx + 92);
  xx[7] = xx[92] - 0.1146426926064243 * state[14];
  xx[13] = xx[93] + 2.191100045903161e-5 * state[14];
  xx[22] = xx[94] - 6.254263394393915e-7 * state[14];
  memcpy(xx + 80, xx + 1, 2 * sizeof(double));
  xx[82] = xx[6];
  pm_math_Quaternion_inverseXform_ra(xx + 38, xx + 80, xx + 92);
  xx[95] = xx[19];
  xx[96] = xx[21];
  xx[97] = xx[24];
  pm_math_Vector3_cross_ra(xx + 80, xx + 95, xx + 98);
  xx[80] = xx[98] + xx[7];
  xx[81] = xx[99] + xx[13];
  xx[82] = xx[100] + xx[22];
  pm_math_Quaternion_inverseXform_ra(xx + 38, xx + 80, xx + 95);
  pm_math_Quaternion_inverseXform_ra(xx + 48, xx + 83, xx + 80);
  xx[98] = xx[25];
  xx[99] = xx[27];
  xx[100] = xx[37];
  pm_math_Vector3_cross_ra(xx + 83, xx + 98, xx + 101);
  xx[98] = xx[101] + xx[4];
  xx[99] = xx[102] + xx[5];
  xx[100] = xx[103] + xx[0];
  pm_math_Quaternion_inverseXform_ra(xx + 48, xx + 98, xx + 101);
  xx[23] = 7.006759967987761e-7;
  xx[36] = 2.797650556265801e-7;
  xx[64] = 6.67299790990277e-11;
  pm_math_Quaternion_inverseXform_ra(xx + 58, xx + 83, xx + 98);
  xx[104] = xx[47];
  xx[105] = xx[52];
  xx[106] = xx[44];
  pm_math_Vector3_cross_ra(xx + 83, xx + 104, xx + 107);
  xx[104] = xx[107] + xx[4];
  xx[105] = xx[108] + xx[5];
  xx[106] = xx[109] + xx[0];
  pm_math_Quaternion_inverseXform_ra(xx + 58, xx + 104, xx + 107);
  pm_math_Quaternion_inverseXform_ra(xx + 67, xx + 83, xx + 104);
  xx[110] = xx[45];
  xx[111] = xx[56];
  xx[112] = xx[53];
  pm_math_Vector3_cross_ra(xx + 83, xx + 110, xx + 113);
  xx[110] = xx[113] + xx[4];
  xx[111] = xx[114] + xx[5];
  xx[112] = xx[115] + xx[0];
  pm_math_Quaternion_inverseXform_ra(xx + 67, xx + 110, xx + 113);
  xx[65] = 7.006759967987762e-7;
  xx[86] = 6.672997909902772e-11;
  pm_math_Quaternion_inverseXform_ra(xx + 75, xx + 83, xx + 110);
  memcpy(xx + 116, xx + 54, 2 * sizeof(double));
  xx[118] = xx[57];
  pm_math_Vector3_cross_ra(xx + 83, xx + 116, xx + 119);
  xx[116] = xx[119] + xx[4];
  xx[117] = xx[120] + xx[5];
  xx[118] = xx[121] + xx[0];
  pm_math_Quaternion_inverseXform_ra(xx + 75, xx + 116, xx + 119);
  pm_math_Quaternion_inverseXform_ra(xx + 71, xx + 83, xx + 116);
  xx[122] = xx[66];
  xx[123] = xx[79];
  xx[124] = xx[63];
  pm_math_Vector3_cross_ra(xx + 83, xx + 122, xx + 125);
  xx[122] = xx[125] + xx[4];
  xx[123] = xx[126] + xx[5];
  xx[124] = xx[127] + xx[0];
  pm_math_Quaternion_inverseXform_ra(xx + 71, xx + 122, xx + 125);
  pm_math_Quaternion_inverseXform_ra(xx + 88, xx + 83, xx + 122);
  xx[128] = xx[3];
  memcpy(xx + 129, xx + 34, 2 * sizeof(double));
  pm_math_Vector3_cross_ra(xx + 83, xx + 128, xx + 131);
  xx[128] = xx[131] + xx[4];
  xx[129] = xx[132] + xx[5];
  xx[130] = xx[133] + xx[0];
  pm_math_Quaternion_inverseXform_ra(xx + 88, xx + 128, xx + 131);
  memcpy(motionData, xx + 8, 4 * sizeof(double));
  motionData[4] = state[0] - xx[15];
  motionData[5] = state[1] - xx[16];
  motionData[6] = state[2] - xx[17] + 0.23862;
  memcpy(motionData + 7, xx + 28, 4 * sizeof(double));
  motionData[11] = xx[12];
  motionData[12] = xx[14];
  motionData[13] = xx[18];
  memcpy(motionData + 14, xx + 38, 4 * sizeof(double));
  motionData[18] = xx[19];
  motionData[19] = xx[21];
  motionData[20] = xx[24];
  memcpy(motionData + 21, xx + 48, 4 * sizeof(double));
  motionData[25] = xx[25];
  motionData[26] = xx[27];
  motionData[27] = xx[37];
  memcpy(motionData + 28, xx + 58, 4 * sizeof(double));
  motionData[32] = xx[47];
  motionData[33] = xx[52];
  motionData[34] = xx[44];
  memcpy(motionData + 35, xx + 67, 4 * sizeof(double));
  motionData[39] = xx[45];
  motionData[40] = xx[56];
  motionData[41] = xx[53];
  memcpy(motionData + 42, xx + 75, 4 * sizeof(double));
  memcpy(motionData + 46, xx + 54, 2 * sizeof(double));
  motionData[48] = xx[57];
  memcpy(motionData + 49, xx + 71, 4 * sizeof(double));
  motionData[53] = xx[66];
  motionData[54] = xx[79];
  motionData[55] = xx[63];
  memcpy(motionData + 56, xx + 88, 4 * sizeof(double));
  motionData[60] = xx[3];
  memcpy(motionData + 61, xx + 34, 2 * sizeof(double));
  memcpy(motionData + 63, xx + 83, 3 * sizeof(double));
  memcpy(motionData + 66, xx + 4, 2 * sizeof(double));
  memcpy(motionData + 68, xx + 0, 3 * sizeof(double));
  memcpy(motionData + 71, xx + 6, 2 * sizeof(double));
  motionData[73] = xx[13];
  motionData[74] = xx[22];
  motionData[75] = xx[92] - xx[20] * state[16];
  motionData[76] = xx[93] + xx[32] * state[16];
  motionData[77] = xx[94] - xx[33] * state[16];
  motionData[78] = xx[95] - 0.07633165669555735 * state[16];
  motionData[79] = xx[96] - 9.300476172011884e-4 * state[16];
  motionData[80] = xx[97] + 0.03780113329793076 * state[16];
  motionData[81] = xx[80] + xx[26] * state[18];
  motionData[82] = xx[81] + xx[42] * state[18];
  motionData[83] = xx[82] + xx[43] * state[18];
  motionData[84] = xx[101] + xx[23] * state[18];
  motionData[85] = xx[102] - xx[36] * state[18];
  motionData[86] = xx[103] - xx[64] * state[18];
  motionData[87] = xx[98] + xx[26] * state[20];
  motionData[88] = xx[99] + xx[42] * state[20];
  motionData[89] = xx[100] + xx[43] * state[20];
  motionData[90] = xx[107] + xx[23] * state[20];
  motionData[91] = xx[108] - xx[36] * state[20];
  motionData[92] = xx[109] - xx[64] * state[20];
  motionData[93] = xx[104] + xx[46] * state[22];
  motionData[94] = xx[105] + xx[62] * state[22];
  motionData[95] = xx[106] + xx[43] * state[22];
  motionData[96] = xx[113] + xx[65] * state[22];
  motionData[97] = xx[114] - xx[36] * state[22];
  motionData[98] = xx[115] - xx[86] * state[22];
  motionData[99] = xx[110] + xx[26] * state[24];
  motionData[100] = xx[111] + xx[42] * state[24];
  motionData[101] = xx[112] + xx[43] * state[24];
  motionData[102] = xx[119] + xx[23] * state[24];
  motionData[103] = xx[120] - xx[36] * state[24];
  motionData[104] = xx[121] - xx[64] * state[24];
  motionData[105] = xx[116] + xx[26] * state[26];
  motionData[106] = xx[117] + xx[42] * state[26];
  motionData[107] = xx[118] + xx[43] * state[26];
  motionData[108] = xx[125] + xx[23] * state[26];
  motionData[109] = xx[126] - xx[36] * state[26];
  motionData[110] = xx[127] - xx[64] * state[26];
  motionData[111] = xx[122] + xx[46] * state[28];
  motionData[112] = xx[123] + xx[62] * state[28];
  motionData[113] = xx[124] + xx[43] * state[28];
  motionData[114] = xx[131] + xx[65] * state[28];
  motionData[115] = xx[132] - xx[36] * state[28];
  motionData[116] = xx[133] - xx[86] * state[28];
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeTransforms(const void *mech,
  const RuntimeDerivedValuesBundle *rtdv, const double *state, double
  *motionData)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[88];
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  memcpy(xx + 0, state + 3, 4 * sizeof(double));
  xx[4] = - 7.953457878587247e-5;
  xx[5] = 1.037555182289732e-5;
  xx[6] = 0.7062800008593415;
  xx[7] = 0.7079325913904003;
  pm_math_Quaternion_composeInverse_ra(xx + 0, xx + 4, xx + 8);
  xx[0] = - 1.525792495965325e-4;
  xx[1] = 1.303297674270197e-3;
  xx[2] = - 6.481520710989565e-4;
  pm_math_Quaternion_xform_ra(xx + 8, xx + 0, xx + 3);
  xx[12] = - 0.7070583871109583;
  xx[13] = 5.679508889285256e-4;
  xx[14] = - 0.7070973528450791;
  xx[15] = - 9.024868271603981e-3;
  xx[0] = 0.5;
  xx[1] = xx[0] * state[13];
  xx[2] = sin(xx[1]);
  xx[16] = cos(xx[1]);
  xx[17] = 8.029196371983453e-6 * xx[2];
  xx[18] = 0.01346899178434196 * xx[2];
  xx[19] = - (0.999909288983678 * xx[2]);
  pm_math_Quaternion_compose_ra(xx + 12, xx + 16, xx + 20);
  xx[12] = 2.20745382934972e-5;
  xx[13] = 0.1149240934718477;
  xx[14] = - 0.02011850541179939;
  pm_math_Quaternion_xform_ra(xx + 20, xx + 12, xx + 15);
  xx[24] = - 0.9698533317008132;
  xx[25] = 0.08771859952513025;
  xx[26] = 0.2216592853450177;
  xx[27] = 0.05056800872605433;
  xx[1] = xx[0] * state[15];
  xx[2] = sin(xx[1]);
  xx[28] = cos(xx[1]);
  xx[29] = - (0.4395758590350312 * xx[2]);
  xx[30] = 0.1609111459511914 * xx[2];
  xx[31] = - (0.8836745256384213 * xx[2]);
  pm_math_Quaternion_compose_ra(xx + 24, xx + 28, xx + 32);
  xx[12] = - 9.105317956012418e-3;
  xx[13] = 0.08932765445918953;
  xx[14] = - 0.01618853665892053;
  pm_math_Quaternion_xform_ra(xx + 32, xx + 12, xx + 24);
  xx[27] = - 0.6176095297070431;
  xx[28] = - 0.7656667455115048;
  xx[29] = 0.01809115169385729;
  xx[30] = 0.1788452232050284;
  xx[1] = xx[0] * state[17];
  xx[2] = 9.594608608490126e-5;
  xx[6] = sin(xx[1]);
  xx[7] = 1.776993604830533e-6;
  xx[12] = 0.9999999953955954;
  xx[36] = cos(xx[1]);
  xx[37] = xx[2] * xx[6];
  xx[38] = xx[7] * xx[6];
  xx[39] = xx[12] * xx[6];
  pm_math_Quaternion_compose_ra(xx + 27, xx + 36, xx + 40);
  xx[27] = 5.327308204667181e-7;
  xx[28] = 7.053611160355946e-7;
  xx[29] = 2.636540714786262e-3;
  pm_math_Quaternion_xform_ra(xx + 40, xx + 27, xx + 36);
  xx[44] = - 0.6392954636561274;
  xx[45] = - 0.7508228867239062;
  xx[46] = - 0.1512720030010929;
  xx[47] = - 0.06843306239176812;
  xx[1] = xx[0] * state[19];
  xx[6] = sin(xx[1]);
  xx[48] = cos(xx[1]);
  xx[49] = xx[2] * xx[6];
  xx[50] = xx[7] * xx[6];
  xx[51] = xx[12] * xx[6];
  pm_math_Quaternion_compose_ra(xx + 44, xx + 48, xx + 52);
  pm_math_Quaternion_xform_ra(xx + 52, xx + 27, xx + 44);
  xx[47] = - 0.682124747335163;
  xx[48] = - 0.478896746705338;
  xx[49] = 0.3174716913482926;
  xx[50] = - 0.4523001882162326;
  xx[1] = xx[0] * state[21];
  xx[6] = 9.594608608490127e-5;
  xx[13] = sin(xx[1]);
  xx[14] = 1.776993604830524e-6;
  xx[56] = cos(xx[1]);
  xx[57] = xx[6] * xx[13];
  xx[58] = xx[14] * xx[13];
  xx[59] = xx[12] * xx[13];
  pm_math_Quaternion_compose_ra(xx + 47, xx + 56, xx + 60);
  pm_math_Quaternion_xform_ra(xx + 60, xx + 27, xx + 47);
  xx[56] = - 0.6356589735212261;
  xx[57] = - 0.75676425753846;
  xx[58] = 0.1178684678153821;
  xx[59] = 0.0967085941840715;
  xx[1] = xx[0] * state[23];
  xx[13] = sin(xx[1]);
  xx[64] = cos(xx[1]);
  xx[65] = xx[2] * xx[13];
  xx[66] = xx[7] * xx[13];
  xx[67] = xx[12] * xx[13];
  pm_math_Quaternion_compose_ra(xx + 56, xx + 64, xx + 68);
  pm_math_Quaternion_xform_ra(xx + 68, xx + 27, xx + 56);
  xx[64] = - 0.6377635698081449;
  xx[65] = - 0.7537560813690898;
  xx[66] = - 0.1359114519880532;
  xx[67] = - 0.08147070665696939;
  xx[1] = xx[0] * state[25];
  xx[13] = sin(xx[1]);
  xx[72] = cos(xx[1]);
  xx[73] = xx[2] * xx[13];
  xx[74] = xx[7] * xx[13];
  xx[75] = xx[12] * xx[13];
  pm_math_Quaternion_compose_ra(xx + 64, xx + 72, xx + 76);
  pm_math_Quaternion_xform_ra(xx + 76, xx + 27, xx + 64);
  xx[72] = - 0.6719536063254669;
  xx[73] = - 0.4717596808874458;
  xx[74] = 0.3279845637595254;
  xx[75] = - 0.46727644962126;
  xx[1] = xx[0] * state[27];
  xx[0] = sin(xx[1]);
  xx[80] = cos(xx[1]);
  xx[81] = xx[6] * xx[0];
  xx[82] = xx[14] * xx[0];
  xx[83] = xx[12] * xx[0];
  pm_math_Quaternion_compose_ra(xx + 72, xx + 80, xx + 84);
  pm_math_Quaternion_xform_ra(xx + 84, xx + 27, xx + 0);
  memcpy(motionData, xx + 8, 4 * sizeof(double));
  motionData[4] = state[0] - xx[3];
  motionData[5] = state[1] - xx[4];
  motionData[6] = state[2] - xx[5] + 0.23862;
  memcpy(motionData + 7, xx + 20, 4 * sizeof(double));
  motionData[11] = - (0.02189445492212523 + xx[15]);
  motionData[12] = - (0.08181860544085766 + xx[16]);
  motionData[13] = - (8.396436632778668e-4 + xx[17]);
  memcpy(motionData + 14, xx + 32, 4 * sizeof(double));
  motionData[18] = 1.390594030460353e-5 - xx[24];
  motionData[19] = - (0.05585658930563103 + xx[25]);
  motionData[20] = - (0.02206892601527486 + xx[26]);
  memcpy(motionData + 21, xx + 40, 4 * sizeof(double));
  motionData[25] = - (0.1264591662103758 + xx[36]);
  motionData[26] = 0.06248829547551044 - xx[37];
  motionData[27] = 0.2356070507097101 - xx[38];
  memcpy(motionData + 28, xx + 52, 4 * sizeof(double));
  motionData[32] = 0.1262020412183443 - xx[44];
  motionData[33] = 0.0625130446900017 - xx[45];
  motionData[34] = 0.2355749531986704 - xx[46];
  memcpy(motionData + 35, xx + 60, 4 * sizeof(double));
  motionData[39] = 0.2674702776869563 - xx[47];
  motionData[40] = 0.06309886405061478 - xx[48];
  motionData[41] = - (9.180040957230233e-3 + xx[49]);
  memcpy(motionData + 42, xx + 68, 4 * sizeof(double));
  motionData[46] = 0.1411118266961335 - xx[56];
  motionData[47] = 0.06359787447147908 - xx[57];
  motionData[48] = - (0.2279744198473475 + xx[58]);
  memcpy(motionData + 49, xx + 76, 4 * sizeof(double));
  motionData[53] = - (0.1414869399826881 + xx[64]);
  motionData[54] = 0.06357019274873783 - xx[65];
  motionData[55] = - (0.2279385191361722 + xx[66]);
  memcpy(motionData + 56, xx + 84, 4 * sizeof(double));
  motionData[60] = - (0.2677896964205858 + xx[0]);
  motionData[61] = 0.06304643311338254 - xx[1];
  motionData[62] = - (9.112042735014963e-3 + xx[2]);
}

size_t UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeAssemblyPosError(const void
  *mech, const RuntimeDerivedValuesBundle *rtdv, size_t constraintIdx, const int
  *modeVector, const double *motionData, double *error)
{
  (void) mech;
  (void)rtdv;
  (void) modeVector;
  (void) motionData;
  (void) error;
  switch (constraintIdx)
  {
  }

  return 0;
}

size_t UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeAssemblyJacobian(const void
  *mech, const RuntimeDerivedValuesBundle *rtdv, size_t constraintIdx, boolean_T
  forVelocitySatisfaction, const double *state, const int *modeVector, const
  double *motionData, double *J)
{
  (void) mech;
  (void) rtdv;
  (void) state;
  (void) modeVector;
  (void) forVelocitySatisfaction;
  (void) motionData;
  (void) J;
  switch (constraintIdx)
  {
  }

  return 0;
}

size_t UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeFullAssemblyJacobian(const void
  *mech, const RuntimeDerivedValuesBundle *rtdv, const double *state, const int *
  modeVector, const double *motionData, double *J)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  (void) state;
  (void) modeVector;
  (void) motionData;
  (void) J;
  return 0;
}

boolean_T UAM_Hexa_PD_Obs_QGround_b715a46b_1_isInKinematicSingularity(const void
  *mech, const RuntimeDerivedValuesBundle *rtdv, size_t constraintIdx, const int
  *modeVector, const double *motionData)
{
  (void) mech;
  (void) rtdv;
  (void) modeVector;
  (void) motionData;
  switch (constraintIdx)
  {
  }

  return 0;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_convertStateVector(const void *asmMech,
  const RuntimeDerivedValuesBundle *rtdv, const void *simMech, const double
  *asmState, const int *asmModeVector, const int *simModeVector, double
  *simState)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) asmMech;
  (void) rtdvd;
  (void) rtdvi;
  (void) simMech;
  (void) asmModeVector;
  (void) simModeVector;
  memcpy(simState, asmState + 0, 29 * sizeof(double));
}
