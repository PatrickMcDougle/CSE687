// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For LogStatusDecorator

#include "LogMessageDecorator.h"

using namespace logger;

// Constructor
LogMessageDecorator::LogMessageDecorator(ILogComponent* component)
    :ALogDecorator(component)
{
}

//  Return log details
string LogMessageDecorator::logInfo(logger::ILogData& logData) const
{
    // Initialize other
	string other = ALogDecorator::logInfo(logData);

    // Logic to format other string
	if (other.length() > 1) {
		other.append(" | ");
	}

    // Logic to add message to other string
	other.append(logData.getMessage());

    // Return other string
	return other;
}
