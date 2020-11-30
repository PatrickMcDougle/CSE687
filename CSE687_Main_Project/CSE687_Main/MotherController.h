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
		IAddressIp* address_mother_ = nullptr;
		ILogger* logger_ = nullptr;
		string mothers_name_;

		int children_counter = 0;
		bool done_ = false;

		Communications* mother_communications_;
		BlockingQueue<ITest*>& blocking_queue_of_test_drivers_;

		vector<ChildTester*> child_testers_;
		vector<thread> child_threads_;

	public:

		MotherController(IAddressIp* address_mother, vector<IAddressIp*>& children_addresses, BlockingQueue<ITest*>& blocking_queue_of_test_drivers, string const& mothers_name)
			: address_mother_(address_mother), children_addresses_(children_addresses),
			blocking_queue_of_test_drivers_(blocking_queue_of_test_drivers), mothers_name_(mothers_name)
		{
			print_mutex.lock();
			std::cout << std::endl << "Hello! My name is " << mothers_name_ << "!";
			print_mutex.unlock();
			mother_communications_ = new Communications(address_mother_, mothers_name_);
		};
		~MotherController() {
			if (done_) {
				mother_communications_->stop();

				print_mutex.lock();
				std::cout << std::endl << "DONE: [..." << mothers_name_ << "...]#";
				print_mutex.unlock();

				// terminate all the child testers for they should all be done.
				for (ChildTester* ct : child_testers_) {
					delete ct;
					ct = nullptr;
				}
			}
		};

		void setup(ILogger* logger);
		void run();

		bool isDone() const { return done_; };
	};
}

#endif // !__MOTHER_CONTROLLER_H__
