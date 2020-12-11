// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For LogData

#pragma once
#ifndef __LOG_DATA_H__
#define __LOG_DATA_H__

#include <iostream>
#include <string>
#include "ILogData.h"

using std::string;
using std::ostream;
using std::cout;
using std::endl;

// Namespace for Logger
namespace logger {
	// Class for LogData
	class LogData : public ILogData {
	public:
		LogData(bool passed, const string& message); // Constructor
		virtual ~LogData() {} // Destructor
		virtual bool isPassed(); //
		virtual string getMessage();
		virtual string getDateTime();
	private:
		bool passed_; // Log result
		string message_; // Log message
		time_t timestamp_; // Time stamp of when log was created
	};

	ostream& operator<<(ostream& out, ILogData& logData);  // Return all element of a Log Data
}

#endif // !__LOG_DATA_H__
