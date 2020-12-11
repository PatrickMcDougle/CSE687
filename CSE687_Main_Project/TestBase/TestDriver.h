// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For Test Driver
#pragma once
#ifndef __I_TEST_DRIVER_H__
#define __I_TEST_DRIVER_H__

#include <iostream>

#include "ITest.h"
#include "ILogger.h"

using std::string;

// Namespace for Test
namespace test {
	// Class for Test Driver
	template<typename T>
	class TestDriver : public ITest
	{
	private:
		T* the_class_;                  // Current Test Class
		bool(T::* the_method_)();		// Current Test Method
		logger::ILogger* the_logger_;	// The Logger
		string& the_message_;			// Current Message
		string the_log_results_;		// Log Results
		string the_method_name_;

	public:
		TestDriver() : // Default Constructor All Elements Set to NullPTR
			the_message_(*new std::string()),
			the_class_(nullptr),
			the_method_(nullptr),
			the_logger_(nullptr)
		{
			// no other initializations needed at this time.
		}

		~TestDriver() {} // Destructor

		bool test() // Runs the test based on the the items that have been set
		{
			bool result = false; // Default Result to False
			try {
				result = (the_class_->*the_method_)(); // Executes the Class and Method
				the_log_results_ = the_logger_->logInfo(result, the_message_); // Log the Results
			}
			catch (...) {
				result = false; // Any issues with class and method, sets results to false
				the_log_results_ = the_logger_->logInfo(result, " [Exception Thrown] " + the_message_); // Sends error message to logger
			}

			return result; // Returns final value of result
		}

		virtual string testLogResults() {  // Returns the current log results
			return the_log_results_;
		}

		string methodName() { return this->the_method_name_; }

		TestDriver* methodName(string& method_name) {
			this->the_method_name_ = method_name;
			return this;
		}

		TestDriver* loadClass(T* the_class) { // Updates the value of the_class_ with provided class
			this->the_class_ = the_class;
			return this;
		}

		TestDriver* loadMethod(bool(T::* the_method)()) { // Update the pointer for the_method_ provided method
			this->the_method_ = the_method;
			return this;
		}

		virtual ITest* loadLogger(logger::ILogger* logger) { // Update the logger
			this->the_logger_ = logger;
			return this;
		}

		virtual ITest* loadMessage(const std::string& message) { // Update the message
			this->the_message_ = message;
			return this;
		}
	};
}

#endif // !__I_TEST_DRIVER_H__
