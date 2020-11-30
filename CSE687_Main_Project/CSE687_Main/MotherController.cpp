#include "MotherController.h"

void threading::MotherController::setup(ILogger* logger)
{
	this->logger_ = logger;

	std::array<string, 5> children_names = { "Boy", "Girl", "Child", "Person", "Heiress" };

	mother_communications_->start();

	children_counter = 0;

	for (IAddressIp* address : children_addresses_) {
		string child_name(children_names[children_counter % children_names.size()]);
		child_name.append("-" + std::to_string(children_counter));

		auto child_tester = new ChildTester(address, address_mother_, blocking_queue_of_test_drivers_, child_name);
		child_tester->setup(logger);
		child_testers_.push_back(child_tester);

		child_threads_.push_back(std::thread(&threading::ChildTester::run, std::move(child_tester)));
		//child_thread.detach();  // this will cause the thread to continue to run even though the scope is over.

		++children_counter;
	}
}

void threading::MotherController::run()
{
	size_t number_of_tests = blocking_queue_of_test_drivers_.size();
	size_t number_of_children = children_counter;

	done_ = false;

	//DWORD sleep_time_milliseconds = ((DWORD)mothers_name_.size() * 20);  // mother needs no sleep time

	while (true) {
		// Wait for Children to respond when ready.
		Message message = mother_communications_->getMessage();

		print_mutex.lock();
		std::cout
			<< std::endl
			<< " =====< "
			<< mother_communications_->getName()
			<< " received message: "
			<< message.getAuthor()
			<< " ["
			<< message.getMessage()
			<< "] >=====";
		print_mutex.unlock();

		if (message.getType() == "STOP") {
			if (--number_of_children == 0)
			{
				// all children are done.
				break;
			}
			// a child is done.
			continue;
		}

		if (message.getType() == "READY" || message.getType() == "TEST_RESULTS") {
			Message reply(address_mother_, message.getSource());
			reply.setAuthor("Mother");

			if (number_of_tests > 0) {
				reply.setType("TEST_REQUEST");
				reply.setMessage("Do test number [" + std::to_string(number_of_tests) + "]");
				--number_of_tests;
			}
			else {
				reply.setType("QUIT");
				reply.setMessage("You are done.");
			}

			mother_communications_->sendMessage(reply);
		}

		//::Sleep(sleep_time_milliseconds);  // mother needs no sleep time
	}

	//::Sleep(sleep_time_milliseconds);  // mother needs no sleep time

	for (auto& t : child_threads_) {
		while (t.joinable()) {
			//t.join();
			//t.detach();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	done_ = true;
}