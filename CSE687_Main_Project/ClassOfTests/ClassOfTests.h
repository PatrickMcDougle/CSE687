// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ClassofTests: This is dummy class for testing purposes.

#pragma once

#include <ITest.h>
#include <TestDriver.h>
#include <ILogger.h>
#include <LoggerFactory.h>
#include <vector>

#include "SimpleTests.h"

#ifdef CLASSOFTESTS_EXPORTS
#define CLASSOFTESTS_API __declspec(dllexport)
#else
#define CLASSOFTESTS_API __declspec(dllimport)
#endif

extern "C" CLASSOFTESTS_API std::string * ListOfFunctions();
extern "C" CLASSOFTESTS_API size_t NumberOfTests();

extern "C" { CLASSOFTESTS_API bool GetTestTrue(); };
extern "C" { CLASSOFTESTS_API bool GetTestFalse(); };