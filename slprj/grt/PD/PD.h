/*
 * Code generation for system model 'PD'
 * For more details, see corresponding source file PD.c
 *
 */

#ifndef PD_H_
#define PD_H_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "PD_types.h"
#include <cstring>

/* Block signals for model 'PD' */
struct B_PD_T {
  real_T error_q[8];                   /* '<S5>/Minus' */
  real_T error_dq[8];                  /* '<S5>/Minus1' */
  real_T Sum[8];                       /* '<S3>/Sum' */
  real_T Add1[8];                      /* '<S3>/Add1' */
  real_T u[8];                         /* '<S3>/Matrix Multiply' */
  real_T u_aux[8];                     /* '<S3>/PD Controller' */
  real_T BMinv[64];                    /* '<Root>/GetBInvMatrix' */
  real_T ginv[64];                     /* '<S1>/MATLAB Function1' */
  real_T fx[8];                        /* '<S1>/MATLAB Function1' */
};

/* Real-time Model Data Structure */
struct tag_RTM_PD_T {
  const char_T **errorStatus;
  RTWSolverInfo *solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize0;
    SimTimeStep *simTimeStep;
  } Timing;
};

/* Model block global parameters (default storage) */
extern struct_Z1yy0b1SiRejj6ODUGxXCE rtP_HexaConstants;/* Variable: HexaConstants
                                                        * Referenced by: '<S1>/MATLAB Function1'
                                                        */
extern struct_JL8g2iM4Lw6J1bY0kTxLfE rtP_ArmConstants;/* Variable: ArmConstants
                                                       * Referenced by: '<S1>/MATLAB Function1'
                                                       */
extern struct_CKTAE3dLo2KptrTZY712sF rtP_PID;/* Variable: PID
                                              * Referenced by:
                                              *   '<S3>/Kd'
                                              *   '<S3>/Kp'
                                              */

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

  /* member function to initialize Real-Time model */
  void initializeRTM(RTWSolverInfo *rt_solverInfo);

  /*member function to setup error status pointer */
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  /* model step function */
  void step(const real_T rtu_InBus_qd[8], const real_T rtu_InBus_dqd[8], const
            real_T rtu_InBus_ddqd[8], const real_T rtu_InBus1_Positions[8],
            const real_T rtu_InBus1_Velocities[8], real_T rty_Output2[8]);

  /* Constructor */
  PD();

  /* Destructor */
  ~PD();

  /* private data and function members */
 private:
  /* Block signals */
  B_PD_T PD_B;

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
