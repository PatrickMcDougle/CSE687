#pragma once
#ifndef __I_TEST_H__
#define __I_TEST_H__

#include "ILogger.h"

namespace test {
	class ITest
	{
	public:
		virtual ~ITest() {}
		virtual bool test() = 0;

		virtual std::string testLogResults() = 0;
		virtual ITest* loadLogger(logger::ILogger* logger) = 0;
		virtual ITest* loadMessage(const std::string& message) = 0;
	};
}

#endif // !__I_TEST_H__
