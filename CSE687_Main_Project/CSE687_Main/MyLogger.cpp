// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For MyLogger
#include "MyLogger.h"

using namespace logger;

//  Default Constructor
MyLogger::MyLogger()
{
}

// Returns the passed test result and message as neat string
string MyLogger::logInfo(bool test_results, const string& test_message)
{
	// If Log Compent is not set, returns an empty string
	if (this->log_component_ == nullptr) {
		return string();
	}

	// Create new ILogData with paramaters
	ILogData* log_data = new LogData(test_results, test_message);

	// Return log details
	return this->log_component_->logInfo(*log_data);
}

// Update log_component_
void MyLogger::setLogComponent(ILogComponent* log_component)
{
	this->log_component_ = log_component;
}