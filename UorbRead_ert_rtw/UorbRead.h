//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: UorbRead.h
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
#ifndef UORBREAD_H_
#define UORBREAD_H_
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "MW_uORB_Read.h"
#include "UorbRead_types.h"
#include <uORB/topics/uam_states.h>

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include <stddef.h>

// Macros for accessing real-time model data structure
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&)
#endif

// Block signals (default storage)
struct B_UorbRead_T {
  px4_Bus_uam_states In1;              // '<S3>/In1'
  px4_Bus_uam_states r;
  real32_T motorValues[12];
  real32_T motorValues_m[12];
  real_T x;    // '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_0'
  real_T y;    // '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_1'
  real_T z;    // '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_2'
  real_T roll; // '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_3'
  real_T pitch;// '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_4'
  real_T yaw;  // '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_5'
  real_T linkone;
               // '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_6'
  real_T linktwo;
               // '<Root>/SigConversion_InsertedFor_Bus Selector5_at_outport_7'
};

// Block states (default storage) for system '<Root>'
struct DW_UorbRead_T {
  px4_internal_block_PX4Actuato_T obj; // '<Root>/PX4 Actuator Write'
  px4_internal_block_Subscriber_T obj_n;// '<S1>/SourceBlock'
};

// Parameters (default storage)
struct P_UorbRead_T_ {
  uint8_T CompareToConstant_const;    // Mask Parameter: CompareToConstant_const
                                         //  Referenced by: '<S2>/Constant'

  px4_Bus_uam_states Out1_Y0;          // Computed Parameter: Out1_Y0
                                          //  Referenced by: '<S3>/Out1'

  px4_Bus_uam_states Constant_Value;   // Computed Parameter: Constant_Value
                                          //  Referenced by: '<S1>/Constant'

  boolean_T Constant_Value_a;          // Expression: true
                                          //  Referenced by: '<Root>/Constant'

};

// Real-time Model Data Structure
struct tag_RTM_UorbRead_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    uint32_T checksums[4];
  } Sizes;

  //
  //  SpecialInfo:
  //  The following substructure contains special information
  //  related to other components that are dependent on RTW.

  struct {
    const void *mappingInfo;
  } SpecialInfo;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_UorbRead_T UorbRead_P;

#ifdef __cplusplus

}

#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_UorbRead_T UorbRead_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_UorbRead_T UorbRead_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void UorbRead_initialize(void);
  extern void UorbRead_step(void);
  extern void UorbRead_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_UorbRead_T *const UorbRead_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'UorbRead'
//  '<S1>'   : 'UorbRead/PX4 uORB Read'
//  '<S2>'   : 'UorbRead/PX4 uORB Read/Compare To Constant'
//  '<S3>'   : 'UorbRead/PX4 uORB Read/Enabled Subsystem'

#endif                                 // UORBREAD_H_

//
// File trailer for generated code.
//
// [EOF]
//
