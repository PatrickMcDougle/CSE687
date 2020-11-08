// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ILogData

#pragma once
#ifndef __I_LOG_DATA_H__
#define __I_LOG_DATA_H__

#include <string>

using std::string;

// Namespace for Logger
namespace logger {
	// Class for ILogData
	class ILogData {
	public:
		virtual ~ILogData() {} // Destructor
		virtual bool isPassed() = 0; // Return log result
		virtual string getMessage() = 0; // Return log message
		virtual string getDateTime() = 0; // Return current date & time
	};
}

#endif // !__I_LOG_DATA_H__
