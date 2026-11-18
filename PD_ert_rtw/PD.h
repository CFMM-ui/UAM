//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: PD.h
//
// Code generated for Simulink model 'PD'.
//
// Model version                  : 1.68
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Thu Oct 22 16:39:09 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef PD_H_
#define PD_H_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#ifndef DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_
#define DEFINED_TYPEDEF_FOR_STRUCT_8IQ6TGGEG7FVGH27G9ENZ_

struct struct_8iq6TggEG7Fvgh27g9ENz
{
  real_T T1max;
  real_T T2max;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_JL8G2IM4LW6J1BY0KTXLFE_
#define DEFINED_TYPEDEF_FOR_STRUCT_JL8G2IM4LW6J1BY0KTXLFE_

struct struct_JL8g2iM4Lw6J1bY0kTxLfE
{
  real_T l1_dim;
  real_T l2_dim;
  real_T Hexa_to_joint_L;
  real_T Mass1;
  real_T Mass2;
  real_T Inertia1[9];
  real_T Inertia2[9];
  real_T MC1;
  real_T MC2;
  struct_8iq6TggEG7Fvgh27g9ENz Servos;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_STRUCT_Z1YY0B1SIREJJ6ODUGXXCE_
#define DEFINED_TYPEDEF_FOR_STRUCT_Z1YY0B1SIREJJ6ODUGXXCE_

struct struct_Z1yy0b1SiRejj6ODUGxXCE
{
  real_T Mass;
  real_T Inertia[9];
  real_T invallo[36];
  real_T kT;
};

#endif

// Class declaration for model PD
class PD final
{
  // public data and function members
 public:
  // Constant parameters (default storage)
  struct ConstP {
    // Expression: HexaConstants
    //  Referenced by: '<S1>/MATLAB Function1'

    struct_Z1yy0b1SiRejj6ODUGxXCE MATLABFunction1_HexaConstants;

    // Expression: ArmConstants
    //  Referenced by: '<S1>/MATLAB Function1'

    struct_JL8g2iM4Lw6J1bY0kTxLfE MATLABFunction1_ArmConstants;
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T InBus_qd[8];                // '<Root>/InBus_qd'
    real_T InBus_dqd[8];               // '<Root>/InBus_dqd'
    real_T InBus_ddqd[8];              // '<Root>/InBus_ddqd'
    real_T InBus1_Positions[8];        // '<Root>/InBus1_Positions'
    real_T InBus1_Velocities[8];       // '<Root>/InBus1_Velocities'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T Output2[8];                 // '<Root>/Output2'
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T *errorStatus;
    RTWSolverInfo solverInfo;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
      time_T stepSize0;
      uint32_T clockTick1;
      struct {
        uint8_T TID[2];
      } TaskCounters;

      SimTimeStep simTimeStep;
      time_T *t;
      time_T tArray[2];
    } Timing;

    time_T** getTPtrPtr();
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const aErrorStatus);
    time_T* getTPtr() const;
    void setTPtr(time_T* aTPtr);
    const char_T** getErrorStatusPtr();
    boolean_T isMajorTimeStep() const;
    boolean_T isMinorTimeStep() const;
  };

  // Copy Constructor
  PD(PD const&) = delete;

  // Assignment Operator
  PD& operator= (PD const&) & = delete;

  // Move Constructor
  PD(PD &&) = delete;

  // Move Assignment Operator
  PD& operator= (PD &&) = delete;

  // Real-Time Model get method
  PD::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  PD();

  // Destructor
  ~PD();

  // private data and function members
 private:
  // private member function(s) for subsystem '<Root>'
  void mldivide_j(const real_T A[64], real_T B_1[8]);

  // Real-Time Model
  RT_MODEL rtM;
};

// Constant parameters (default storage)
extern const PD::ConstP rtConstP;

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
//  '<Root>' : 'PD'
//  '<S1>'   : 'PD/Get f(x) and g(x)^-1'
//  '<S2>'   : 'PD/GetBInvMatrix'
//  '<S3>'   : 'PD/PID'
//  '<S4>'   : 'PD/Get f(x) and g(x)^-1/MATLAB Function1'
//  '<S5>'   : 'PD/PID/Obtain Error'
//  '<S6>'   : 'PD/PID/PD Controller'

#endif                                 // PD_H_

//
// File trailer for generated code.
//
// [EOF]
//
