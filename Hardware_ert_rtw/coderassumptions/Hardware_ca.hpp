/*
 * File: Hardware_ca.hpp
 *
 * Abstract: Tests assumptions in the generated code.
 */

#ifndef HARDWARE_CA_H
#define HARDWARE_CA_H

extern "C"
{
  /* preprocessor validation checks */
#include "Hardware_ca_preproc.hpp"
#include "coder_assumptions_hwimpl.h"

  /* variables holding test results */
  extern CA_ChecksTestResults CA_Hardware_Res;
  extern CA_PWS_TestResults CA_Hardware_PWSRes;

  /* variables holding "expected" and "actual" hardware implementation */
  extern const CA_Checks CA_Hardware_Exp;
  extern CA_Checks CA_Hardware_Act;
  extern const int numberOfImportedTypes;
  extern const int numberOfNonTunableEnumLiterals;

  /* entry point function to run tests */
  void Hardware_caRunTests(void);
}

#endif                                 /* HARDWARE_CA_H */
