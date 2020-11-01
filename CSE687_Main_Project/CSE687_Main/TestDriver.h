#pragma once
#ifndef __I_TEST_DRIVER_H__
#define __I_TEST_DRIVER_H__

#include <iostream>

#include "ITest.h"
#include "ILogger.h"

namespace test {
	template<typename T>
	class TestDriver : public ITest
	{
	private:
		bool(T::* the_method_)();
		T* the_class_;
		logger::ILogger* the_logger_;
		std::string& the_message_;
		std::string the_log_results_;

	public:
		TestDriver() : 
			the_message_(*new std::string()),
			the_class_(nullptr),
			the_method_(nullptr),
			the_logger_(nullptr)
		{
			// no other initializations needed at this time.
		}

		~TestDriver() {}

		bool test()
		{
			bool result = false;
			try {
				result = (the_class_->*the_method_)();
				the_log_results_ = the_logger_->logInfo(result, the_message_);
			}
			catch (...) {
				result = false;
				the_log_results_ = the_logger_->logInfo(result, " [Exception Thrown] " + the_message_);
			}

			return result;
		}

		std::string testLogResults() {
			return the_log_results_;
		}

		TestDriver* loadClass(T* the_class) {
			this->the_class_ = the_class;
			return this;
		}

		TestDriver* loadMethod(bool(T::* the_method)()) {
			this->the_method_ = the_method;
			return this;
		}

		TestDriver* loadLogger(logger::ILogger* logger) {
			this->the_logger_ = logger;
			return this;
		}

		TestDriver* loadMessage(const std::string& message) {
			this->the_message_ = message;
			return this;
		}
	};
}

#endif // !__I_TEST_DRIVER_H__
