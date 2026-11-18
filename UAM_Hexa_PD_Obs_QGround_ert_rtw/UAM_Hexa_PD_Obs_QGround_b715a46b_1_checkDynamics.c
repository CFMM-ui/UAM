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

PmfMessageId UAM_Hexa_PD_Obs_QGround_b715a46b_1_checkDynamics(const
  RuntimeDerivedValuesBundle *rtdv, const double *state, const double *input,
  const double *inputDot, const double *inputDdot, const double *discreteState,
  const int *modeVector, int *errorResult, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvd;
  (void) rtdvi;
  (void) state;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) modeVector;
  (void) neDiagMgr;
  errorResult[0] = 0;
  return NULL;
}
