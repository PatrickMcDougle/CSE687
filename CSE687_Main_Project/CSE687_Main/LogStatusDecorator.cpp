// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For LogStatusDecorator
#include "LogStatusDecorator.h"

using namespace logger;

// Constructor
LogStatusDecorator::LogStatusDecorator(ILogComponent* component)
	:ALogDecorator(component)
{
}

// Return log details
string LogStatusDecorator::logInfo(logger::ILogData& logData) const
{
	// Initialize other
	string other = ALogDecorator::logInfo(logData);

	// Logic to format other string
	if (other.length() > 1) {
		other.append(" | ");
	}

	// Add info regarding pass or fail to other
	other.append(logData.isPassed() ? "TRUE " : "FALSE");

	// Return other
	return other;
}