#pragma once
#ifndef __CHILD_TESTER_H__
#define __CHILD_TESTER_H__

#include <string>
#include <iostream>

#include "AddressIp4.h"
#include "BlockingQueue.h"
#include "Communications.h"
#include "ILogger.h"
#include "ITest.h"
#include "Message.h"
#include "SocketSystem.h"

using std::string;
using messaging::AddressIp4;
using messaging::Message;
using test::ITest;
using logger::ILogger;

static std::mutex print_mutex;

namespace threading {
	class ChildTester
	{
	private:
		AddressIp4 child_address_;
		AddressIp4 mother_address_;
		string childs_name_;
		BlockingQueue<ITest*>* blocking_queue_of_test_drivers_ = nullptr;
		ILogger* logger_ = nullptr;

	public:

		ChildTester(messaging::AddressIp4 child_address, messaging::AddressIp4 mother_address, const string& childs_name)
			: child_address_(child_address), mother_address_(mother_address), childs_name_(childs_name)
		{
			// nothing to do in the body of the constructor.
		};
		~ChildTester() {};

		void setup(BlockingQueue<ITest*>* blocking_queue_of_test_drivers, ILogger* logger);
		void run() const;
	};
}

#endif // !__CHILD_TESTER_H__
