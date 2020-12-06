// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ILogComponent

#pragma once
#ifndef __I_LOG_COMPONENT_H__
#define __I_LOG_COMPONENT_H__

#include <string>

#include "ILogData.h"

using namespace logger;
using std::string;

namespace logger {
	class ILogComponent {
	public:
		virtual ~ILogComponent() {} // Destructor
		virtual string logInfo(ILogData&) const = 0;  // Return log details
	};
}

#endif // !__I_LOG_COMPONENT_H__
