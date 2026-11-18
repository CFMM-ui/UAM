//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Differentiator0.h
//
// Code generated for Simulink model 'Differentiator0'.
//
// Model version                  : 1.67
// Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
// C/C++ source code generated on : Thu Oct 22 16:55:00 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef DIFFERENTIATOR0_H_
#define DIFFERENTIATOR0_H_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "Differentiator0_types.h"

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include <cstring>
#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
struct ODE3_IntgData {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
};

#endif

// Class declaration for model Differentiator0
class Differentiator0 final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_Differentiator0_T {
    real_T Sum3[8];                    // '<S1>/Sum3'
    real_T Sum4[8];                    // '<S1>/Sum4'
  };

  // Continuous states (default storage)
  struct X_Differentiator0_T {
    real_T Integrator_CSTATE[8];       // '<S1>/Integrator'
    real_T Integrator1_CSTATE[8];      // '<S1>/Integrator1'
  };

  // State derivatives (default storage)
  struct XDot_Differentiator0_T {
    real_T Integrator_CSTATE[8];       // '<S1>/Integrator'
    real_T Integrator1_CSTATE[8];      // '<S1>/Integrator1'
  };

  // State disabled
  struct XDis_Differentiator0_T {
    boolean_T Integrator_CSTATE[8];    // '<S1>/Integrator'
    boolean_T Integrator1_CSTATE[8];   // '<S1>/Integrator1'
  };

  // Constant parameters (default storage)
  struct ConstP_Differentiator0_T {
    // Expression: Differentiator.G1
    //  Referenced by: '<S1>/G1'

    real_T G1_Value[8];

    // Expression: Differentiator.G2
    //  Referenced by: '<S1>/G2'

    real_T G2_Value[8];

    // Expression: Differentiator.Q2
    //  Referenced by: '<S1>/Q2'

    real_T Q2_Value[8];

    // Expression: Differentiator.w1
    //  Referenced by: '<S1>/Q3'

    real_T Q3_Value[8];

    // Expression: Differentiator.w2
    //  Referenced by: '<S1>/Q4'

    real_T Q4_Value[8];

    // Expression: Differentiator.p1
    //  Referenced by: '<S1>/Q5'

    real_T Q5_Value[8];

    // Expression: Differentiator.p2
    //  Referenced by: '<S1>/Q6'

    real_T Q6_Value[8];

    // Expression: [0; 0; 0.28; 0; 0; 0; 0; 0]
    //  Referenced by: '<S1>/Integrator'

    real_T Integrator_IC[8];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_Differentiator0_T {
    real_T Position[8];                // '<Root>/Position'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_Differentiator0_T {
    real_T OutBus_Positions[8];        // '<Root>/OutBus_Positions'
    real_T OutBus_Velocities[8];       // '<Root>/OutBus_Velocities'
  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[16];
  struct RT_MODEL_Differentiator0_T {
    const char_T *errorStatus;
    RTWSolverInfo solverInfo;
    X_Differentiator0_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    XDis_Differentiator0_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeY[16];
    real_T odeF[3][16];
    ODE3_IntgData intgData;

    //
    //  Sizes:
    //  The following substructure contains sizes information
    //  for many of the model attributes such as inputs, outputs,
    //  dwork, sample times, etc.

    struct {
      int_T numContStates;
      int_T numPeriodicContStates;
      int_T numSampTimes;
    } Sizes;

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

      time_T tStart;
      SimTimeStep simTimeStep;
      boolean_T stopRequestedFlag;
      time_T *t;
      time_T tArray[2];
    } Timing;

    time_T** getTPtrPtr();
    boolean_T getStopRequested() const;
    void setStopRequested(boolean_T aStopRequested);
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const aErrorStatus);
    time_T* getTPtr() const;
    void setTPtr(time_T* aTPtr);
    boolean_T* getStopRequestedPtr();
    const char_T** getErrorStatusPtr();
    boolean_T isMajorTimeStep() const;
    boolean_T isMinorTimeStep() const;
    time_T getTStart() const;
  };

  // Copy Constructor
  Differentiator0(Differentiator0 const&) = delete;

  // Assignment Operator
  Differentiator0& operator= (Differentiator0 const&) & = delete;

  // Move Constructor
  Differentiator0(Differentiator0 &&) = delete;

  // Move Assignment Operator
  Differentiator0& operator= (Differentiator0 &&) = delete;

  // Real-Time Model get method
  Differentiator0::RT_MODEL_Differentiator0_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_Differentiator0_T *pExtU_Differentiator0_T)
  {
    Differentiator0_U = *pExtU_Differentiator0_T;
  }

  // Root outports get method
  const ExtY_Differentiator0_T &getExternalOutputs() const
  {
    return Differentiator0_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  Differentiator0();

  // Destructor
  ~Differentiator0();

  // private data and function members
 private:
  // External inputs
  ExtU_Differentiator0_T Differentiator0_U;

  // External outputs
  ExtY_Differentiator0_T Differentiator0_Y;

  // Block signals
  B_Differentiator0_T Differentiator0_B;

  // Block continuous states
  X_Differentiator0_T Differentiator0_X;

  // Block Continuous state disabled vector
  XDis_Differentiator0_T Differentiator0_XDis;

  // private member function(s) for subsystem '<S1>/U power x1'
  static void Differentiator0_Upowerx1(const real_T rtu_u[8], const real_T
    rtu_v[8], real_T rty_uv[8]);

  // Global mass matrix

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void Differentiator0_derivatives();

  // Real-Time Model
  RT_MODEL_Differentiator0_T Differentiator0_M;
};

// Constant parameters (default storage)
extern const Differentiator0::ConstP_Differentiator0_T Differentiator0_ConstP;

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
//  '<Root>' : 'Differentiator0'
//  '<S1>'   : 'Differentiator0/Fixed-Time Differentiator1'
//  '<S2>'   : 'Differentiator0/Fixed-Time Differentiator1/U power x1'
//  '<S3>'   : 'Differentiator0/Fixed-Time Differentiator1/U power x2'
//  '<S4>'   : 'Differentiator0/Fixed-Time Differentiator1/U power x3'
//  '<S5>'   : 'Differentiator0/Fixed-Time Differentiator1/U power x4'

#endif                                 // DIFFERENTIATOR0_H_

//
// File trailer for generated code.
//
// [EOF]
//
