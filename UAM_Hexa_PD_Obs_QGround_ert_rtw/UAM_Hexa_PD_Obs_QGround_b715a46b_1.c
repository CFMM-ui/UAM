/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'UAM_Hexa_PD_Obs_QGround/Hexa Arm Model/Hexa Model/Subsystem/Solver Configuration'.
 */

#include "ne_std.h"
#include "pm_default_allocator.h"
#include "ssc_dae.h"
#include "sm_ssci_NeDaePrivateData.h"

NeDae *sm_ssci_constructDae(NeDaePrivateData *smData);
void UAM_Hexa_PD_Obs_QGround_b715a46b_1_NeDaePrivateData_create(NeDaePrivateData
  *smData);
void UAM_Hexa_PD_Obs_QGround_b715a46b_1_dae(
  NeDae **dae,
  const NeModelParameters *modelParams,
  const NeSolverParameters *solverParams)
{
  PmAllocator *alloc = pm_default_allocator();
  NeDaePrivateData *smData =
    (NeDaePrivateData *) alloc->mCallocFcn(alloc, sizeof(NeDaePrivateData), 1);
  (void) modelParams;
  (void) solverParams;
  UAM_Hexa_PD_Obs_QGround_b715a46b_1_NeDaePrivateData_create(smData);
  *dae = sm_ssci_constructDae(smData);
}
