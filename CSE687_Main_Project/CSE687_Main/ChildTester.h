#pragma once
#ifndef __CHILD_TESTER_H__
#define __CHILD_TESTER_H__

#include <string>
#include <iostream>

#include "BlockingQueue.h"
#include "Communications.h"
#include "IAddressIp.h"
#include "ILogger.h"
#include "ITest.h"
#include "Message.h"
#include "SocketSystem.h"

using logger::ILogger;
using messaging::Communications;
using messaging::IAddressIp;
using messaging::Message;
using std::string;
using test::ITest;

// used to print out better.
static std::mutex print_mutex;

namespace threading {
	/// <summary>
	/// This class handles getting message about testing and running tests.
	/// </summary>
	class ChildTester
	{
	private:
		ILogger* logger_ = nullptr;
		IAddressIp* child_address_;
		IAddressIp* mother_address_;
		BlockingQueue<ITest*>& blocking_queue_of_test_drivers_;

		string childs_name_;
		int test_performed = 0;

		ChildTester() = delete;
		ChildTester(ChildTester&) = delete;
		ChildTester(ChildTester&&) = delete;

	public:

		ChildTester(IAddressIp* child_address, IAddressIp* mother_address, BlockingQueue<ITest*>& blocking_queue_of_test_drivers, const string& childs_name)
			: child_address_(child_address), mother_address_(mother_address),
			blocking_queue_of_test_drivers_(blocking_queue_of_test_drivers),
			childs_name_(childs_name)
		{
			print_mutex.lock();
			std::cout << std::endl << "HI! My name is " << childs_name_ << "!";
			print_mutex.unlock();
		};

		~ChildTester() {
			print_mutex.lock();
			std::cout << std::endl << "DONE: [" << childs_name_ << "," << test_performed << "]#";
			print_mutex.unlock();
		};

		/// <summary>
		/// The setup method is used to set the logger and other things needed before running.
		/// </summary>
		void setup(ILogger* logger);

		/// <summary>
		/// This method will start running things.  Start communications and run test when asked.
		/// </summary>
		void run();
	};
}

#endif // !__CHILD_TESTER_H__
