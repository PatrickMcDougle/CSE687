// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For LogStatusDecorator
#pragma once

#ifndef __LOG_STATUS_DECORATOR_H__
#define __LOG_STATUS_DECORATOR_H__

#include "ALogDecorator.h"

// Namespace for Logger
namespace logger {
    // Class for LogStatusDecorator
	class LogStatusDecorator : public ALogDecorator
	{
	public:
		LogStatusDecorator(ILogComponent* component); // Constructor
		string logInfo(ILogData& logData) const override; // Return log data
	};
}

#endif // !__LOG_STATUS_DECORATOR_H__