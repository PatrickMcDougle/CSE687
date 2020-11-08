// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For MyLogger
#pragma once
#ifndef __MY_LOGGER_H__
#define __MY_LOGGER_H__

#include <string>

#include "ILogger.h"
#include "ILogComponent.h"
#include "ILogData.h"
#include "LogData.h"

using std::string;

// Namespace for Logger
namespace logger {
	// Class for MyLogger
	class MyLogger : public ILogger
	{
	public:
		MyLogger(); // Default Constructor
		string logInfo(bool, const string&)  override; // Return log details
		void setLogComponent(ILogComponent*)  override; // Update log_component_
	private:
		ILogComponent* log_component_;
	};
}

#endif // !__MY_LOGGER_H__
