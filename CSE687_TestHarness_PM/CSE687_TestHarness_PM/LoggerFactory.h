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

namespace logger {
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

		template<typename T>
		inline T* LoadDecorator(ILogComponent* aTemplate)
		{
			return new T(aTemplate);
		}
	};
}

#endif // !__LOGGER_FACTORY_H__
