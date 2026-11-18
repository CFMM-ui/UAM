/*
 * rtGetNaN.cpp
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

#include "rtwtypes.h"

extern "C"
{

#include "rtGetNaN.h"

}

extern "C"
{
  /* Return rtNaN needed by the generated code. */
  real_T rtGetNaN(void)
  {
    return rtNaN;
  }

  /* Return rtNaNF needed by the generated code. */
  real32_T rtGetNaNF(void)
  {
    return rtNaNF;
  }
}
