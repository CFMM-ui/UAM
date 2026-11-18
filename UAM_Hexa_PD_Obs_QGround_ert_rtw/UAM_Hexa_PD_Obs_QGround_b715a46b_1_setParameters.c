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

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeRuntimeParameters(real_T *in,
  real_T *out)
{
  (void) in;
  (void) out;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeAsmRuntimeDerivedValuesDoubles(
  const double *rtp, double *rtdvd)
{
  (void) rtp;
  (void) rtdvd;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeAsmRuntimeDerivedValuesInts(const
  double *rtp, int *rtdvi)
{
  (void) rtp;
  (void) rtdvi;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeAsmRuntimeDerivedValues(const
  double *rtp, RuntimeDerivedValuesBundle *rtdv)
{
  UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeAsmRuntimeDerivedValuesDoubles(rtp,
    rtdv->mDoubles.mValues);
  UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeAsmRuntimeDerivedValuesInts(rtp,
    rtdv->mInts.mValues);
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeSimRuntimeDerivedValuesDoubles(
  const double *rtp, double *rtdvd)
{
  (void) rtp;
  (void) rtdvd;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeSimRuntimeDerivedValuesInts(const
  double *rtp, int *rtdvi)
{
  (void) rtp;
  (void) rtdvi;
}

void UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeSimRuntimeDerivedValues(const
  double *rtp, RuntimeDerivedValuesBundle *rtdv)
{
  UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeSimRuntimeDerivedValuesDoubles(rtp,
    rtdv->mDoubles.mValues);
  UAM_Hexa_PD_Obs_QGround_b715a46b_1_computeSimRuntimeDerivedValuesInts(rtp,
    rtdv->mInts.mValues);
}
