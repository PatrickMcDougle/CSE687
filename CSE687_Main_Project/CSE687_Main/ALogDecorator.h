// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ALogDecorator

#pragma once

#ifndef __A_LOG_DECORATOR_H__
#define __A_LOG_DECORATOR_H__

#include "ILogComponent.h"
#include "ILogData.h"

// Namespace for Logger
namespace logger {
    // Class for ALogDecorator
	class ALogDecorator : public ILogComponent
	{
	private:
		ILogComponent* log_component_; // Log Component
	public:
		ALogDecorator(ILogComponent* component); // Constructor
		string logInfo(logger::ILogData& logData) const override; // Return Log Details
	};
}

#endif // !__A_LOG_DECORATOR_H__