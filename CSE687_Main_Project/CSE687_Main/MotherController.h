#pragma once
#ifndef __MOTHER_CONTROLLER_H__
#define __MOTHER_CONTROLLER_H__

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "BlockingQueue.h"
#include "ChildTester.h"
#include "Communications.h"
#include "IAddressIp.h"
#include "ILogger.h"
#include "ITest.h"
#include "Message.h"
#include "SocketSystem.h"

using std::string;
using std::to_string;
using messaging::IAddressIp;
using messaging::Message;
using test::ITest;
using logger::ILogger;

namespace threading {
	class MotherController
	{
	private:
		vector<IAddressIp*>& children_addresses_;
		IAddressIp* address_mother_;
		ILogger* logger_ = nullptr;
		string mothers_name_;

		int children_counter = 0;
		bool done_ = false;

		Communications mother_communications_;
		BlockingQueue<ITest*>& blocking_queue_of_test_drivers_;

	public:

		MotherController(IAddressIp* address_mother, vector<IAddressIp*>& children_addresses, BlockingQueue<ITest*>& blocking_queue_of_test_drivers, string const& mothers_name)
			: address_mother_(address_mother), children_addresses_(children_addresses),
			blocking_queue_of_test_drivers_(blocking_queue_of_test_drivers), mothers_name_(mothers_name),
			mother_communications_(address_mother, mothers_name)
		{
			// nothing to do in the body of the constructor.
		};
		~MotherController() {};

		void setup(ILogger* logger);
		void run();

		bool isDone() const { return done_; };
	};
}

#endif // !__MOTHER_CONTROLLER_H__
