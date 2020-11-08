// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ITest

#pragma once
#ifndef __I_TEST_H__
#define __I_TEST_H__

#include "ILogger.h"

using namespace logger;
using std::string;

// Namespace for test
namespace test {
	// Class for ITest
	class ITest
	{
	public:
		virtual ~ITest() {} // Destructor
		virtual bool test() = 0; // Set Test Result
		virtual string testLogResults() = 0; // Return Log Details
		virtual ITest* loadLogger(ILogger* logger) = 0; // Load logger
		virtual ITest* loadMessage(const string& message) = 0; // Load message
	};
}

#endif // !__I_TEST_H__
