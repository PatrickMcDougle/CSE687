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

using std::string;
using messaging::IAddressIp;
using messaging::Message;
using test::ITest;
using logger::ILogger;

// used to print out better.
static std::mutex print_mutex;

namespace threading {
	class ChildTester
	{
	private:
		IAddressIp* child_address_;
		IAddressIp* mother_address_;
		BlockingQueue<ITest*>& blocking_queue_of_test_drivers_;
		ILogger* logger_ = nullptr;
		string childs_name_;

		int test_performed = 0;

	public:

		ChildTester(IAddressIp* child_address, IAddressIp* mother_address, BlockingQueue<ITest*>& blocking_queue_of_test_drivers, const string& childs_name)
			: child_address_(child_address), mother_address_(mother_address),
			blocking_queue_of_test_drivers_(blocking_queue_of_test_drivers), childs_name_(childs_name)
		{
			// nothing to do in the body of the constructor.
		};
		~ChildTester() {};

		void setup(ILogger* logger);
		void run();
	};
}

#endif // !__CHILD_TESTER_H__
