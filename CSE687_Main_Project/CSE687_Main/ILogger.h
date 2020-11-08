// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ILogger

#pragma once
#ifndef __I_LOGGER_H__
#define __I_LOGGER_H__

#include <string>

#include "ILogComponent.h"

using std::string;

// Namespace for Logger
namespace logger {
	// Class for ILogger
	class ILogger
	{
	public:
		virtual ~ILogger() {} // Destructor
		virtual string logInfo(bool, const string&) = 0; // Return log detials
		virtual void setLogComponent(ILogComponent*) = 0; // Sets the log component
	};
}

#endif // !__I_LOGGER_H__
