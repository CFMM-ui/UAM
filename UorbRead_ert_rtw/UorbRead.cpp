//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: UorbRead.cpp
//
// Code generated for Simulink model 'UorbRead'.
//
// Model version                  : 1.4
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Mon Nov 16 18:37:07 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "UorbRead.h"
#include "MW_PX4_Actuators.h"
#include "rtwtypes.h"
#include "UorbRead_private.h"

extern "C"
{

#include "rt_nonfinite.h"

}

// Block signals (default storage)
B_UorbRead_T UorbRead_B;

// Block states (default storage)
DW_UorbRead_T UorbRead_DW;

// Real-time model
RT_MODEL_UorbRead_T UorbRead_M_ = RT_MODEL_UorbRead_T();
RT_MODEL_UorbRead_T *const UorbRead_M = &UorbRead_M_;

// Model step function
void UorbRead_step(void)
{
  int32_T i;
  real32_T servoValues[8];
  uint8_T b_varargout_1;

  // MATLABSystem: '<S1>/SourceBlock' incorporates:
  //   Constant: '<S1>/Constant'

  UorbRead_B.r = UorbRead_P.Constant_Value;
  b_varargout_1 = uORB_read_topic_exists(UorbRead_DW.obj_n.orbMetadataObj, 0);
  if (b_varargout_1 != 2) {
    b_varargout_1 = uORB_read_step(UorbRead_DW.obj_n.orbMetadataObj,
      &UorbRead_DW.obj_n.eventStructObj, &UorbRead_B.r, false, 1.0);
  }

  // Outputs for Enabled SubSystem: '<S1>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S3>/Enable'

  // RelationalOperator: '<S2>/Compare' incorporates:
  //   Constant: '<S2>/Constant'
  //   MATLABSystem: '<S1>/SourceBlock'
  //
  if (b_varargout_1 == UorbRead_P.CompareToConstant_const) {
    // SignalConversion generated from: '<S3>/In1'
    UorbRead_B.In1 = UorbRead_B.r;
  }

  // End of RelationalOperator: '<S2>/Compare'
  // End of Outputs for SubSystem: '<S1>/Enabled Subsystem'

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.x = UorbRead_B.In1.x;

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.y = UorbRead_B.In1.y;

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.z = UorbRead_B.In1.z;

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.roll = UorbRead_B.In1.roll;

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.pitch = UorbRead_B.In1.pitch;

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.yaw = UorbRead_B.In1.yaw;

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.linkone = UorbRead_B.In1.linkone;

  // SignalConversion generated from: '<Root>/Bus Selector5'
  UorbRead_B.linktwo = UorbRead_B.In1.linktwo;

  // MATLABSystem: '<Root>/PX4 Actuator Write' incorporates:
  //   Constant: '<Root>/Constant'
  //   DataTypeConversion: '<Root>/Data Type Conversion'
  //   DataTypeConversion: '<Root>/Data Type Conversion1'
  //   DataTypeConversion: '<Root>/Data Type Conversion2'
  //   DataTypeConversion: '<Root>/Data Type Conversion3'
  //   DataTypeConversion: '<Root>/Data Type Conversion4'
  //   DataTypeConversion: '<Root>/Data Type Conversion5'
  //   DataTypeConversion: '<Root>/Data Type Conversion6'
  //   DataTypeConversion: '<Root>/Data Type Conversion7'

  for (i = 0; i < 12; i++) {
    UorbRead_B.motorValues[i] = (rtNaNF);
  }

  for (i = 0; i < 8; i++) {
    servoValues[i] = (rtNaNF);
  }

  UorbRead_B.motorValues[0] = static_cast<real32_T>(UorbRead_B.x);
  UorbRead_B.motorValues[1] = static_cast<real32_T>(UorbRead_B.y);
  UorbRead_B.motorValues[2] = static_cast<real32_T>(UorbRead_B.z);
  UorbRead_B.motorValues[3] = static_cast<real32_T>(UorbRead_B.roll);
  UorbRead_B.motorValues[4] = static_cast<real32_T>(UorbRead_B.pitch);
  UorbRead_B.motorValues[5] = static_cast<real32_T>(UorbRead_B.yaw);
  UorbRead_B.motorValues[6] = static_cast<real32_T>(UorbRead_B.linkone);
  UorbRead_B.motorValues[7] = static_cast<real32_T>(UorbRead_B.linktwo);
  MW_actuators_set(UorbRead_P.Constant_Value_a, &UorbRead_B.motorValues[0],
                   &servoValues[0]);

  // End of MATLABSystem: '<Root>/PX4 Actuator Write'

  // Update absolute time for base rate
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  UorbRead_M->Timing.clockTick0++;
}

// Model initialize function
void UorbRead_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(UorbRead_M, -1);

  // External mode info
  UorbRead_M->Sizes.checksums[0] = (618830634U);
  UorbRead_M->Sizes.checksums[1] = (2228363781U);
  UorbRead_M->Sizes.checksums[2] = (4047130400U);
  UorbRead_M->Sizes.checksums[3] = (3297421294U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    UorbRead_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(UorbRead_M->extModeInfo,
      &UorbRead_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(UorbRead_M->extModeInfo, UorbRead_M->Sizes.checksums);
    rteiSetTFinalTicks(UorbRead_M->extModeInfo, -1);
  }

  {
    int32_T i;
    static const boolean_T tmp[12] = { true, true, true, true, true, true, true,
      true, false, false, false, false };

    // SystemInitialize for Enabled SubSystem: '<S1>/Enabled Subsystem'
    // SystemInitialize for SignalConversion generated from: '<S3>/In1' incorporates:
    //   Outport: '<S3>/Out1'

    UorbRead_B.In1 = UorbRead_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S1>/Enabled Subsystem'

    // Start for MATLABSystem: '<S1>/SourceBlock'
    UorbRead_DW.obj_n.matlabCodegenIsDeleted = false;
    UorbRead_DW.obj_n.isSetupComplete = false;
    UorbRead_DW.obj_n.isInitialized = 1;
    UorbRead_DW.obj_n.orbMetadataObj = ORB_ID(uam_states);
    uORB_read_initialize(UorbRead_DW.obj_n.orbMetadataObj,
                         &UorbRead_DW.obj_n.eventStructObj);
    UorbRead_DW.obj_n.isSetupComplete = true;

    // Start for MATLABSystem: '<Root>/PX4 Actuator Write'
    UorbRead_DW.obj.matlabCodegenIsDeleted = false;
    UorbRead_DW.obj.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      UorbRead_DW.obj.ValidMotorIdx[i] = tmp[i];
    }

    for (i = 0; i < 8; i++) {
      UorbRead_DW.obj.ValidServoIdx[i] = false;
    }

    MW_actuators_init();
    UorbRead_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<Root>/PX4 Actuator Write'
  }
}

// Model terminate function
void UorbRead_terminate(void)
{
  int32_T i;
  real32_T servoValues[8];

  // Terminate for MATLABSystem: '<S1>/SourceBlock'
  if (!UorbRead_DW.obj_n.matlabCodegenIsDeleted) {
    UorbRead_DW.obj_n.matlabCodegenIsDeleted = true;
    if ((UorbRead_DW.obj_n.isInitialized == 1) &&
        UorbRead_DW.obj_n.isSetupComplete) {
      uORB_read_terminate(&UorbRead_DW.obj_n.eventStructObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S1>/SourceBlock'

  // Terminate for MATLABSystem: '<Root>/PX4 Actuator Write'
  if (!UorbRead_DW.obj.matlabCodegenIsDeleted) {
    UorbRead_DW.obj.matlabCodegenIsDeleted = true;
    if ((UorbRead_DW.obj.isInitialized == 1) && UorbRead_DW.obj.isSetupComplete)
    {
      for (i = 0; i < 12; i++) {
        UorbRead_B.motorValues_m[i] = (rtNaNF);
      }

      for (i = 0; i < 8; i++) {
        servoValues[i] = (rtNaNF);
      }

      for (i = 0; i < 12; i++) {
        if (UorbRead_DW.obj.ValidMotorIdx[i]) {
          UorbRead_B.motorValues_m[i] = 0.0F;
        }
      }

      for (i = 0; i < 8; i++) {
        if (UorbRead_DW.obj.ValidServoIdx[i]) {
          servoValues[i] = 0.0F;
        }
      }

      MW_actuators_set(false, &UorbRead_B.motorValues_m[0], &servoValues[0]);
      MW_actuators_terminate();
    }
  }

  // End of Terminate for MATLABSystem: '<Root>/PX4 Actuator Write'
}

//
// File trailer for generated code.
//
// [EOF]
//
