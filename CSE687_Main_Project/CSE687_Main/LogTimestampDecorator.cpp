// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For LogTimestampDecorator
#include "LogTimestampDecorator.h"

using namespace logger;

// Constructor
LogTimestampDecorator::LogTimestampDecorator(ILogComponent* component)
    :ALogDecorator(component)
{
}

// Return details of log
string LogTimestampDecorator::logInfo(logger::ILogData& logData) const
{
    // Initialize other
	string other = ALogDecorator::logInfo(logData);

    // Logic to format other string
	if (other.length() > 1) {
		other.append(" | ");
	}

    // Add timestamp to other
	other.append(logData.getDateTime());

    // Return other
	return other;
}
