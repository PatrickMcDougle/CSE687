// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For LogMessage

#pragma once

#ifndef __LOG_MESSAGE_H__
#define __LOG_MESSAGE_H__

#include "ILogComponent.h"

// Namespace for Logger
namespace logger {
	// Class for LogMessage
	class LogMessage : public ILogComponent
	{
	public:
		LogMessage(); // Default constructor
		string logInfo(ILogData& logData) const override; // Return log details
	};
}

#endif // !__LOG_MESSAGE_H__