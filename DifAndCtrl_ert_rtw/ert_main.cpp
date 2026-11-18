//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.cpp
//
// Code generated for Simulink model 'DifAndCtrl'.
//
// Model version                  : 1.70
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Thu Oct 22 18:50:01 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include <stdio.h>
#include <stdlib.h>
#include "DifAndCtrl.h"
#include "DifAndCtrl_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "MW_PX4_TaskControl.h"
#include "nuttxinitialize.h"
#define UNUSED(x)                      x = x

static RT_MODEL_DifAndCtrl_T DifAndCtrl_M_;
static RT_MODEL_DifAndCtrl_T *const DifAndCtrl_MPtr = &DifAndCtrl_M_;// Real-time model 
static B_DifAndCtrl_T DifAndCtrl_B;    // Observable signals
static DW_DifAndCtrl_T DifAndCtrl_DW;  // Observable states
static X_DifAndCtrl_T DifAndCtrl_X;    // Observable continuous states
static XDis_DifAndCtrl_T DifAndCtrl_XDis;// Continuous states Disabled
static ExtU_DifAndCtrl_T DifAndCtrl_U; // External inputs
static ExtY_DifAndCtrl_T DifAndCtrl_Y; // External outputs

#define NAMELEN                        16

// Function prototype declaration
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
px4_sem_t stopSem;
px4_sem_t baserateTaskSem;
pthread_t schedulerThread;
pthread_t baseRateThread;
void *threadJoinStatus;
int terminatingmodel = 0;
void *baseRateTask(void *arg)
{
  RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M = DifAndCtrl_MPtr;
  runModel = (DifAndCtrl_M->getErrorStatus() == (NULL)) &&
    !DifAndCtrl_M->getStopRequested();
  while (runModel) {
    px4_sem_wait(&baserateTaskSem);
    DifAndCtrl_step(DifAndCtrl_M, &DifAndCtrl_U, &DifAndCtrl_Y);

    // Get model outputs here
    stopRequested = !((DifAndCtrl_M->getErrorStatus() == (NULL)) &&
                      !DifAndCtrl_M->getStopRequested());
  }

  runModel = 0;
  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M = DifAndCtrl_MPtr;
  UNUSED(sig);
  DifAndCtrl_M->setErrorStatus("stopping the model");
  runModel = 0;
}

void *terminateTask(void *arg)
{
  RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M = DifAndCtrl_MPtr;
  UNUSED(arg);
  terminatingmodel = 1;

  {
    runModel = 0;
  }

  MW_PX4_Terminate();

  // Terminate model
  DifAndCtrl_terminate(DifAndCtrl_M);
  px4_sem_post(&stopSem);
  return NULL;
}

int px4_simulink_app_task_main (int argc, char *argv[])
{
  RT_MODEL_DifAndCtrl_T *const DifAndCtrl_M = DifAndCtrl_MPtr;
  px4_simulink_app_control_MAVLink();
  DifAndCtrl_M->setErrorStatus(0);

  // Unused arguments
  (void)(argc);
  (void)(argv);

  // Pack model data into RTM
  DifAndCtrl_M->blockIO = &DifAndCtrl_B;
  DifAndCtrl_M->dwork = &DifAndCtrl_DW;
  DifAndCtrl_M->contStates = &DifAndCtrl_X;
  DifAndCtrl_M->contStateDisabled = &DifAndCtrl_XDis;

  // Initialize model
  DifAndCtrl_initialize(DifAndCtrl_M, &DifAndCtrl_U, &DifAndCtrl_Y);

  // Call RTOS Initialization function
  nuttxRTOSInit(0.01, 0);

  // Wait for stop semaphore
  px4_sem_wait(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(px4_sem_destroy(&timerTaskSem[i]), 0, "px4_sem_destroy");
    }
  }

#endif

  return 0;
}

//
// File trailer for generated code.
//
// [EOF]
//
