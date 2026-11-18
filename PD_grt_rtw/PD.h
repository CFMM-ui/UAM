/*
 * PD.h
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

#ifndef PD_H_
#define PD_H_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "PD_types.h"
#include <cfloat>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
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

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
struct B_PD_T {
  real_T error_q[8];                   /* '<S5>/Minus' */
  real_T error_dq[8];                  /* '<S5>/Minus1' */
  real_T Sum[8];                       /* '<S3>/Sum' */
  real_T Add1[8];                      /* '<S3>/Add1' */
  real_T u[8];                         /* '<S3>/Matrix Multiply' */
  real_T FMTq[8];                      /* '<Root>/Matrix Multiply' */
  real_T u_aux[8];                     /* '<S3>/PD Controller' */
  real_T BMinv[64];                    /* '<Root>/GetBInvMatrix' */
  real_T ginv[64];                     /* '<S1>/MATLAB Function1' */
  real_T fx[8];                        /* '<S1>/MATLAB Function1' */
};

/* External inputs (root inport signals with default storage) */
struct ExtU_PD_T {
  real_T InBus_qd[8];                  /* '<Root>/InBus_qd' */
  real_T InBus_dqd[8];                 /* '<Root>/InBus_dqd' */
  real_T InBus_ddqd[8];                /* '<Root>/InBus_ddqd' */
  real_T InBus1_Positions[8];          /* '<Root>/InBus1_Positions' */
  real_T InBus1_Velocities[8];         /* '<Root>/InBus1_Velocities' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_PD_T {
  real_T Output2[8];                   /* '<Root>/Output2' */
};

/* Parameters (default storage) */
struct P_PD_T_ {
  struct_Z1yy0b1SiRejj6ODUGxXCE HexaConstants;/* Variable: HexaConstants
                                               * Referenced by: '<S1>/MATLAB Function1'
                                               */
  struct_JL8g2iM4Lw6J1bY0kTxLfE ArmConstants;/* Variable: ArmConstants
                                              * Referenced by: '<S1>/MATLAB Function1'
                                              */
  struct_CKTAE3dLo2KptrTZY712sF PID;   /* Variable: PID
                                        * Referenced by:
                                        *   '<S3>/Kd'
                                        *   '<S3>/Kp'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PD_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    struct {
      uint8_T TID[2];
    } TaskCounters;

    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model PD */
class PD final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  PD(PD const&) = delete;

  /* Assignment Operator */
  PD& operator= (PD const&) & = delete;

  /* Move Constructor */
  PD(PD &&) = delete;

  /* Move Assignment Operator */
  PD& operator= (PD &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_PD_T * getRTM();

  /* External inputs */
  ExtU_PD_T PD_U;

  /* External outputs */
  ExtY_PD_T PD_Y;

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  PD();

  /* Destructor */
  ~PD();

  /* private data and function members */
 private:
  /* Block signals */
  B_PD_T PD_B;

  /* Tunable parameters */
  static P_PD_T PD_P;

  /* private member function(s) for subsystem '<Root>'*/
  void PD_mldivide_j(const real_T A[64], real_T B[8]);

  /* Real-Time Model */
  RT_MODEL_PD_T PD_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PD'
 * '<S1>'   : 'PD/Get f(x) and g(x)^-1'
 * '<S2>'   : 'PD/GetBInvMatrix'
 * '<S3>'   : 'PD/PID'
 * '<S4>'   : 'PD/Get f(x) and g(x)^-1/MATLAB Function1'
 * '<S5>'   : 'PD/PID/Obtain Error'
 * '<S6>'   : 'PD/PID/PD Controller'
 */
#endif                                 /* PD_H_ */
