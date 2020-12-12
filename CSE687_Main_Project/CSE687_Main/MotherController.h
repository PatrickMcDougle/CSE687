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
	/// <summary>
	/// This class creates the children tester threads and is the main communciations hub for all the testing.
	/// </summary>
	class MotherController
	{
	private:
		ILogger* logger_ = nullptr;
		IAddressIp* address_mother_ = nullptr;
		vector<IAddressIp*>& children_addresses_;

		Communications* mother_communications_;
		BlockingQueue<ITest*>& blocking_queue_of_test_drivers_;
		vector<thread*> child_threads_;
		vector<ChildTester*> child_testers_;

		string mothers_name_;

		int children_counter = 0;
		bool done_ = false;

		MotherController() = delete;
		MotherController(MotherController&) = delete;
		MotherController(MotherController&&) = delete;

	public:
		/// <summary>
		/// The main constructor for this class.
		/// </summary>
		/// <param name="address_mother">The address for this class</param>
		/// <param name="children_addresses">An array (vector) of addresses for all the children processes/threads.</param>
		/// <param name="blocking_queue_of_test_drivers">The queue where all the tests are located.</param>
		/// <param name="mothers_name">The name of this class for network and output needs.</param>
		MotherController(IAddressIp* address_mother, vector<IAddressIp*>& children_addresses, BlockingQueue<ITest*>& blocking_queue_of_test_drivers, string const& mothers_name)
			: address_mother_(address_mother), children_addresses_(children_addresses),
			blocking_queue_of_test_drivers_(blocking_queue_of_test_drivers), mothers_name_(mothers_name)
		{
			print_mutex.lock();
			std::cout << std::endl << "Hello! My name is " << mothers_name_ << "!";
			print_mutex.unlock();
			mother_communications_ = new Communications(address_mother_, mothers_name_);
		};

		/// <summary>
		/// The destructor for this class.  Print out that things are done and shut down things.
		/// </summary>
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

		/// <summary>
		/// The setup method is used to set the logger and other things needed before running.
		/// </summary>
		void setup(ILogger* logger);

		/// <summary>
		/// This method will start running things.  Generate child threads and communicate with them.
		/// </summary>
		void run();

		/// <summary>
		/// This method is a way for people to know if this class is done.
		/// </summary>
		bool isDone() const { return done_; };
	};
}

#endif // !__MOTHER_CONTROLLER_H__
