/*
 * Differentiator0.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Differentiator0".
 *
 * Model version              : 1.66
 * Simulink Coder version : 26.1 (R2026a) 20-Nov-2025
 * C++ source code generated on : Thu Oct 22 12:09:20 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "Differentiator0.h"
#include "rtwtypes.h"
#include <cmath>
#include "Differentiator0_private.h"
#include <emmintrin.h>
#include <cstring>

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void Differentiator0::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 16 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Differentiator0_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  Differentiator0_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  Differentiator0_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (std::isinf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

/*
 * Output and update for atomic system:
 *    '<S1>/U power x1'
 *    '<S1>/U power x2'
 *    '<S1>/U power x3'
 *    '<S1>/U power x4'
 */
void Differentiator0::Differentiator0_Upowerx1(const real_T rtu_u[8], const
  real_T rtu_v[8], B_Upowerx1_Differentiator0_T *localB)
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    localB->uv[i] = rt_powd_snf(std::abs(rtu_u[i]), rtu_v[i]);
  }
}

/* Model step function */
void Differentiator0::step()
{
  /* local block i/o variables */
  real_T rtb_e_hat[8];
  __m128d tmp_0;
  real_T rtb_e_hat_0;
  real_T tmp;
  int32_T i;
  if (rtmIsMajorTimeStep((&Differentiator0_M))) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&(&Differentiator0_M)->solverInfo,
                          (((&Differentiator0_M)->Timing.clockTick0+1)*
      (&Differentiator0_M)->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Differentiator0_M))) {
    (&Differentiator0_M)->Timing.t[0] = rtsiGetT(&(&Differentiator0_M)
      ->solverInfo);
  }

  for (i = 0; i <= 6; i += 2) {
    /* Sum: '<S1>/Sum1' incorporates:
     *  Integrator: '<S1>/Integrator'
     */
    tmp_0 = _mm_loadu_pd(&Differentiator0_X.Integrator_CSTATE[i]);

    /* Sum: '<S1>/Sum1' incorporates:
     *  Inport generated from: '<Root>/Position'
     */
    _mm_storeu_pd(&rtb_e_hat[i], _mm_sub_pd(_mm_loadu_pd
      (&Differentiator0_U.Position[i]), tmp_0));
  }

  /* MATLAB Function: '<S1>/U power x2' incorporates:
   *  Constant: '<S1>/Q3'
   */
  Differentiator0_Upowerx1(rtb_e_hat, Differentiator0_ConstP.Q3_Value,
    &Differentiator0_B.sf_Upowerx2);

  /* MATLAB Function: '<S1>/U power x1' incorporates:
   *  Constant: '<S1>/Q5'
   */
  Differentiator0_Upowerx1(rtb_e_hat, Differentiator0_ConstP.Q5_Value,
    &Differentiator0_B.sf_Upowerx1);
  for (i = 0; i < 8; i++) {
    /* Signum: '<S1>/Sign' incorporates:
     *  Signum: '<S1>/Sign1'
     *  Sum: '<S1>/Sum1'
     */
    rtb_e_hat_0 = rtb_e_hat[i];
    if (std::isnan(rtb_e_hat_0)) {
      tmp = (rtNaN);
      rtb_e_hat_0 = (rtNaN);
    } else if (rtb_e_hat_0 < 0.0) {
      tmp = -1.0;
      rtb_e_hat_0 = -1.0;
    } else {
      tmp = (rtb_e_hat_0 > 0.0);
      rtb_e_hat_0 = tmp;
    }

    /* Sum: '<S1>/Sum3' incorporates:
     *  Constant: '<S1>/G1'
     *  Integrator: '<S1>/Integrator1'
     *  Product: '<S1>/Product3'
     *  Product: '<S1>/Product4'
     *  Signum: '<S1>/Sign'
     *  Signum: '<S1>/Sign1'
     */
    Differentiator0_B.Sum3[i] = (Differentiator0_ConstP.G1_Value[i] * tmp *
      Differentiator0_B.sf_Upowerx2.uv[i] +
      Differentiator0_X.Integrator1_CSTATE[i]) + 16.0 * rtb_e_hat_0 *
      Differentiator0_B.sf_Upowerx1.uv[i];
  }

  /* MATLAB Function: '<S1>/U power x3' incorporates:
   *  Constant: '<S1>/Q4'
   */
  Differentiator0_Upowerx1(rtb_e_hat, Differentiator0_ConstP.Q4_Value,
    &Differentiator0_B.sf_Upowerx3);

  /* MATLAB Function: '<S1>/U power x4' incorporates:
   *  Constant: '<S1>/Q6'
   */
  Differentiator0_Upowerx1(rtb_e_hat, Differentiator0_ConstP.Q6_Value,
    &Differentiator0_B.sf_Upowerx4);
  for (i = 0; i < 8; i++) {
    /* Signum: '<S1>/Sign2' incorporates:
     *  Signum: '<S1>/Sign3'
     *  Sum: '<S1>/Sum1'
     */
    rtb_e_hat_0 = rtb_e_hat[i];
    if (std::isnan(rtb_e_hat_0)) {
      tmp = (rtNaN);
      rtb_e_hat_0 = (rtNaN);
    } else if (rtb_e_hat_0 < 0.0) {
      tmp = -1.0;
      rtb_e_hat_0 = -1.0;
    } else {
      tmp = (rtb_e_hat_0 > 0.0);
      rtb_e_hat_0 = tmp;
    }

    /* Sum: '<S1>/Sum4' incorporates:
     *  Constant: '<S1>/G2'
     *  Constant: '<S1>/Q2'
     *  Product: '<S1>/Product5'
     *  Product: '<S1>/Product6'
     *  Signum: '<S1>/Sign2'
     *  Signum: '<S1>/Sign3'
     */
    Differentiator0_B.Sum4[i] = Differentiator0_ConstP.G2_Value[i] * tmp *
      Differentiator0_B.sf_Upowerx3.uv[i] + Differentiator0_ConstP.Q2_Value[i] *
      rtb_e_hat_0 * Differentiator0_B.sf_Upowerx4.uv[i];

    /* Outport generated from: '<Root>/OutBus_Outport_1' incorporates:
     *  Integrator: '<S1>/Integrator'
     */
    Differentiator0_Y.OutBus_Positions[i] =
      Differentiator0_X.Integrator_CSTATE[i];

    /* Outport generated from: '<Root>/OutBus_Outport_1' incorporates:
     *  Integrator: '<S1>/Integrator1'
     */
    Differentiator0_Y.OutBus_Velocities[i] =
      Differentiator0_X.Integrator1_CSTATE[i];
  }

  if (rtmIsMajorTimeStep((&Differentiator0_M))) {
    rt_ertODEUpdateContinuousStates(&(&Differentiator0_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++(&Differentiator0_M)->Timing.clockTick0;
    (&Differentiator0_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&Differentiator0_M)->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      (&Differentiator0_M)->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Differentiator0::Differentiator0_derivatives()
{
  XDot_Differentiator0_T *_rtXdot;
  _rtXdot = ((XDot_Differentiator0_T *) (&Differentiator0_M)->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator' incorporates:
   *  Sum: '<S1>/Sum3'
   */
  std::memcpy(&_rtXdot->Integrator_CSTATE[0], &Differentiator0_B.Sum3[0], sizeof
              (real_T) << 3U);

  /* Derivatives for Integrator: '<S1>/Integrator1' incorporates:
   *  Sum: '<S1>/Sum4'
   */
  std::memcpy(&_rtXdot->Integrator1_CSTATE[0], &Differentiator0_B.Sum4[0],
              sizeof(real_T) << 3U);
}

/* Model initialize function */
void Differentiator0::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Differentiator0_M)->solverInfo,
                          &(&Differentiator0_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&Differentiator0_M)->solverInfo, &rtmGetTPtr
                ((&Differentiator0_M)));
    rtsiSetStepSizePtr(&(&Differentiator0_M)->solverInfo, &(&Differentiator0_M
                       )->Timing.stepSize0);
    rtsiSetdXPtr(&(&Differentiator0_M)->solverInfo, &(&Differentiator0_M)
                 ->derivs);
    rtsiSetContStatesPtr(&(&Differentiator0_M)->solverInfo, (real_T **)
                         &(&Differentiator0_M)->contStates);
    rtsiSetNumContStatesPtr(&(&Differentiator0_M)->solverInfo,
      &(&Differentiator0_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Differentiator0_M)->solverInfo,
      &(&Differentiator0_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Differentiator0_M)->solverInfo,
      &(&Differentiator0_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Differentiator0_M)->solverInfo,
      &(&Differentiator0_M)->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&Differentiator0_M)->solverInfo, (boolean_T**)
      &(&Differentiator0_M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&Differentiator0_M)->solverInfo, (&rtmGetErrorStatus
      ((&Differentiator0_M))));
    rtsiSetRTModelPtr(&(&Differentiator0_M)->solverInfo, (&Differentiator0_M));
  }

  rtsiSetSimTimeStep(&(&Differentiator0_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&Differentiator0_M)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&Differentiator0_M)->solverInfo, false);
  (&Differentiator0_M)->intgData.y = (&Differentiator0_M)->odeY;
  (&Differentiator0_M)->intgData.f[0] = (&Differentiator0_M)->odeF[0];
  (&Differentiator0_M)->intgData.f[1] = (&Differentiator0_M)->odeF[1];
  (&Differentiator0_M)->intgData.f[2] = (&Differentiator0_M)->odeF[2];
  (&Differentiator0_M)->contStates = ((X_Differentiator0_T *) &Differentiator0_X);
  (&Differentiator0_M)->contStateDisabled = ((XDis_Differentiator0_T *)
    &Differentiator0_XDis);
  (&Differentiator0_M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&Differentiator0_M)->solverInfo, static_cast<void *>
                    (&(&Differentiator0_M)->intgData));
  rtsiSetSolverName(&(&Differentiator0_M)->solverInfo,"ode3");
  rtmSetTPtr((&Differentiator0_M), &(&Differentiator0_M)->Timing.tArray[0]);
  (&Differentiator0_M)->Timing.stepSize0 = 0.01;
  for (int32_T i{0}; i < 8; i++) {
    /* InitializeConditions for Integrator: '<S1>/Integrator' */
    Differentiator0_X.Integrator_CSTATE[i] =
      Differentiator0_ConstP.Integrator_IC[i];

    /* InitializeConditions for Integrator: '<S1>/Integrator1' */
    Differentiator0_X.Integrator1_CSTATE[i] = 0.0;
  }
}

/* Model terminate function */
void Differentiator0::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Differentiator0::Differentiator0() :
  Differentiator0_U(),
  Differentiator0_Y(),
  Differentiator0_B(),
  Differentiator0_X(),
  Differentiator0_XDis(),
  Differentiator0_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
Differentiator0::~Differentiator0() = default;

/* Real-Time Model get method */
RT_MODEL_Differentiator0_T * Differentiator0::getRTM()
{
  return (&Differentiator0_M);
}
