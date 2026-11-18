//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: untitled.cpp
//
// Code generated for Simulink model 'untitled'.
//
// Model version                  : 1.0
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Fri Nov  6 19:14:42 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "untitled.h"
#include "MW_Parameter.h"
#include "MW_PX4_Parameter.h"
#include "rtwtypes.h"
#include "untitled_private.h"

// Block signals (default storage)
B_untitled_T untitled_B;

// Block states (default storage)
DW_untitled_T untitled_DW;

// Real-time model
RT_MODEL_untitled_T untitled_M_ = RT_MODEL_untitled_T();
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

// Model step function
void untitled_step(void)
{
  // MATLABSystem: '<S1>/ReadParameter'
  untitled_B.ReadParameter_o2 = MW_ParamRead_Step(untitled_DW.obj.MW_PARAMHANDLE,
    MW_INT32, &untitled_B.ReadParameter_o1);
  if (untitled_B.ReadParameter_o2) {
    untitled_B.ReadParameter_o1 = 0;
  }

  // End of MATLABSystem: '<S1>/ReadParameter'

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.5, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  untitled_M->Timing.clockTick0++;
}

// Model initialize function
void untitled_initialize(void)
{
  // Registration code
  rtmSetTFinal(untitled_M, -1);

  // External mode info
  untitled_M->Sizes.checksums[0] = (1189709825U);
  untitled_M->Sizes.checksums[1] = (2793294553U);
  untitled_M->Sizes.checksums[2] = (933450613U);
  untitled_M->Sizes.checksums[3] = (3435440769U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    untitled_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(untitled_M->extModeInfo,
      &untitled_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(untitled_M->extModeInfo, untitled_M->Sizes.checksums);
    rteiSetTFinalTicks(untitled_M->extModeInfo, -1);
  }

  {
    static const char_T ParameterNameStr[9] = "TRAJ_SEL";

    // Start for MATLABSystem: '<S1>/ReadParameter'
    untitled_DW.obj.matlabCodegenIsDeleted = false;
    untitled_DW.obj.isInitialized = 1;
    untitled_DW.obj.MW_PARAMHANDLE = MW_Init_Param(&ParameterNameStr[0], true,
      500.0);
    untitled_DW.obj.isSetupComplete = true;
  }
}

// Model terminate function
void untitled_terminate(void)
{
  // Terminate for MATLABSystem: '<S1>/ReadParameter'
  if (!untitled_DW.obj.matlabCodegenIsDeleted) {
    untitled_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S1>/ReadParameter'
}

//
// File trailer for generated code.
//
// [EOF]
//
