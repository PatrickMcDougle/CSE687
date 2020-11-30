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
	class ChildTester
	{
	private:
		IAddressIp* child_address_;
		IAddressIp* mother_address_;
		ILogger* logger_ = nullptr;
		string childs_name_;

		int test_performed = 0;

		BlockingQueue<ITest*>& blocking_queue_of_test_drivers_;

	public:

		ChildTester(IAddressIp* child_address, IAddressIp* mother_address, BlockingQueue<ITest*>& blocking_queue_of_test_drivers, const string& childs_name)
			: child_address_(child_address), mother_address_(mother_address),
			blocking_queue_of_test_drivers_(blocking_queue_of_test_drivers), childs_name_(childs_name)
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

		void setup(ILogger* logger);
		void run();
	};
}

#endif // !__CHILD_TESTER_H__
