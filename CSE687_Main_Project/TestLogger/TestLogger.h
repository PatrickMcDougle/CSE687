#pragma once
#include <string>

#include "LogData.h"
#include "LogMessage.h"
#include "LoggerFactory.h"
#include "ILogger.h"
#include "MyLogger.h"
#include "ILogComponent.h"

#ifdef CLASSOFTESTS_EXPORTS
#define CLASSOFTESTS_API __declspec(dllexport)
#else
#define CLASSOFTESTS_API __declspec(dllimport)
#endif

extern "C" CLASSOFTESTS_API std::string * ListOfFunctions();
extern "C" CLASSOFTESTS_API size_t NumberOfTests();

extern "C" { CLASSOFTESTS_API bool Test_LogData_isPassed_true(); };
extern "C" { CLASSOFTESTS_API bool Test_LogData_isPassed_false(); };
extern "C" { CLASSOFTESTS_API bool Test_LogData_getDateTime(); };
extern "C" { CLASSOFTESTS_API bool Test_LogData_getMessage(); };
extern "C" { CLASSOFTESTS_API bool Test_LoggerFactory_create(); };
extern "C" { CLASSOFTESTS_API bool Test_LogMessage_logInfo(); };
extern "C" { CLASSOFTESTS_API bool Test_MyLogger_logInfo(); };