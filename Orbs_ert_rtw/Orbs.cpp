//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Orbs.cpp
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
#include "Orbs.h"
#include "Orbs_private.h"

// Block signals (default storage)
B_Orbs_T Orbs_B;

// Block states (default storage)
DW_Orbs_T Orbs_DW;

// Real-time model
RT_MODEL_Orbs_T Orbs_M_ = RT_MODEL_Orbs_T();
RT_MODEL_Orbs_T *const Orbs_M = &Orbs_M_;

// Model step function
void Orbs_step(void)
{
  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Constant: '<S1>/Constant'

  Orbs_B.BusAssignment = Orbs_P.Constant_Value;

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Constant: '<Root>/Constant'
  //   Constant: '<Root>/Constant1'
  //   Constant: '<Root>/Constant2'
  //   Constant: '<Root>/Constant3'

  Orbs_B.BusAssignment.lat = Orbs_P.Constant_Value_a;
  Orbs_B.BusAssignment.alt = Orbs_P.Constant1_Value;
  Orbs_B.BusAssignment.lon = Orbs_P.Constant2_Value;
  Orbs_B.BusAssignment.terrain_alt = Orbs_P.Constant3_Value;

  // MATLABSystem: '<S2>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  uORB_write_step(Orbs_DW.obj.orbMetadataObj, &Orbs_DW.obj.orbAdvertiseObj,
                  &Orbs_B.BusAssignment);

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.2, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  Orbs_M->Timing.clockTick0++;
}

// Model initialize function
void Orbs_initialize(void)
{
  // Registration code
  rtmSetTFinal(Orbs_M, -1);

  // External mode info
  Orbs_M->Sizes.checksums[0] = (71772773U);
  Orbs_M->Sizes.checksums[1] = (1569413264U);
  Orbs_M->Sizes.checksums[2] = (3175643896U);
  Orbs_M->Sizes.checksums[3] = (1687916953U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    Orbs_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Orbs_M->extModeInfo,
      &Orbs_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Orbs_M->extModeInfo, Orbs_M->Sizes.checksums);
    rteiSetTFinalTicks(Orbs_M->extModeInfo, -1);
  }

  // Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  Orbs_DW.obj.matlabCodegenIsDeleted = false;
  Orbs_DW.obj.isSetupComplete = false;
  Orbs_DW.obj.isInitialized = 1;
  Orbs_DW.obj.orbAdvertiseObj = NULL;
  Orbs_DW.obj.orbMetadataObj = ORB_ID(vehicle_global_position);
  uORB_write_initialize(Orbs_DW.obj.orbMetadataObj, &Orbs_DW.obj.orbAdvertiseObj,
                        &Orbs_B.BusAssignment);
  Orbs_DW.obj.isSetupComplete = true;
}

// Model terminate function
void Orbs_terminate(void)
{
  // Terminate for MATLABSystem: '<S2>/SinkBlock'
  if (!Orbs_DW.obj.matlabCodegenIsDeleted) {
    Orbs_DW.obj.matlabCodegenIsDeleted = true;
    if ((Orbs_DW.obj.isInitialized == 1) && Orbs_DW.obj.isSetupComplete) {
      uORB_write_terminate(&Orbs_DW.obj.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S2>/SinkBlock'
}

//
// File trailer for generated code.
//
// [EOF]
//
