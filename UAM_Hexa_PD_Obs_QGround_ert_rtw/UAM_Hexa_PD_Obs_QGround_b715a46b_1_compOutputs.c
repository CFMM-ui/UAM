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
#include "UAM_Hexa_PD_Obs_QGround_b715a46b_1_geometries.h"

PmfMessageId UAM_Hexa_PD_Obs_QGround_b715a46b_1_compOutputs(const
  RuntimeDerivedValuesBundle *rtdv, const double *state, const int *modeVector,
  const double *input, const double *inputDot, const double *inputDdot, const
  double *discreteState, double *output, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[28];
  (void) rtdvd;
  (void) rtdvi;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
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
  pm_math_Quaternion_compose_ra(xx + 8, xx + 4, xx + 18);
  memcpy(xx + 22, state + 7, 3 * sizeof(double));
  pm_math_Quaternion_inverseXform_ra(xx + 8, xx + 22, xx + 25);
  memcpy(xx + 8, state + 10, 3 * sizeof(double));
  pm_math_Quaternion_xform_ra(xx + 4, xx + 8, xx + 22);
  xx[8] = xx[0];
  xx[9] = - xx[1];
  xx[10] = xx[2];
  pm_math_Vector3_cross_ra(xx + 22, xx + 8, xx + 0);
  pm_math_Vector3_cross_ra(xx + 22, xx + 12, xx + 8);
  xx[11] = xx[25] + xx[0] + xx[8];
  xx[12] = xx[26] + xx[1] + xx[9];
  xx[13] = xx[27] + xx[2] + xx[10];
  pm_math_Quaternion_inverseXform_ra(xx + 4, xx + 11, xx + 0);
  pm_math_Quaternion_xform_ra(xx + 18, xx + 0, xx + 8);
  pm_math_Quaternion_inverseXform_ra(xx + 4, xx + 22, xx + 0);
  memcpy(output, state + 13, 4 * sizeof(double));
  output[4] = xx[15] + state[0] - xx[15];
  output[5] = xx[16] + state[1] - xx[16];
  output[6] = xx[17] + state[2] - xx[17] + 0.23862;
  memcpy(output + 7, xx + 8, 3 * sizeof(double));
  output[10] = - xx[18];
  output[11] = - xx[19];
  output[12] = - xx[20];
  output[13] = - xx[21];
  memcpy(output + 14, xx + 0, 3 * sizeof(double));
  return NULL;
}
