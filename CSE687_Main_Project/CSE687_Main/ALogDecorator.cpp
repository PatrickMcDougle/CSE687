// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ALogDecorator

#include "ALogDecorator.h"
using namespace logger;

// Constructor
ALogDecorator::ALogDecorator(ILogComponent* component)
	:log_component_(component)
{
}

// Return logData details
string ALogDecorator::logInfo(logger::ILogData& logData) const
{
	return this->log_component_->logInfo(logData);
}