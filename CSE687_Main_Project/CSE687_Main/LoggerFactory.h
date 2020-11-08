// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For LoggerFactory

#pragma once
#ifndef __LOGGER_FACTORY_H__
#define __LOGGER_FACTORY_H__

#include <string>
#include "LogMessage.h"
#include "LogMessageDecorator.h"
#include "LogStatusDecorator.h"
#include "LogTimestampDecorator.h"
#include "ILogger.h"
#include "MyLogger.h"

using std::string;

// Namespace for Logger
namespace logger {
    // Class for LoggerFactory
	class LoggerFactory
	{
	public:
		/*
		 * Order value of 0 (zero) will setup up logger to NOT use that part.
		 * Order determins the order to print.
		 */
		ILogger* create(
			int test_pass_result_order = 1,
			int test_message_order = 0,
			int test_timestamp_order = 0
		);

	private:

        // LoadDecorator Inline Function
		template<typename T>
		inline T* LoadDecorator(ILogComponent* aTemplate)
		{
			return new T(aTemplate);
		}
	};
}

#endif // !__LOGGER_FACTORY_H__
