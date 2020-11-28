#include "MotherController.h"

void threading::MotherController::setup(ILogger* logger)
{
	this->logger_ = logger;

	std::array<string, 5> children_names = { "Boy", "Girl", "Child", "Person", "Heiress" };

	mother_communications_.start();

	children_counter = 0;

	for (IAddressIp* address : children_addresses_) {
		string child_name(children_names[children_counter % children_names.size()]);
		child_name.append("-" + std::to_string(children_counter));

		ChildTester child_tester(address, address_mother_, blocking_queue_of_test_drivers_, child_name);
		child_tester.setup(logger);

		std::thread child_thread(&threading::ChildTester::run, child_tester);
		child_thread.join();

		++children_counter;
	}
}

void threading::MotherController::run()
{
	size_t number_of_tests = blocking_queue_of_test_drivers_.size();
	size_t number_of_children = children_counter;

	done_ = false;

	while (true) {
		// Wait for Children to respond when ready.
		Message message = mother_communications_.getMessage();

		print_mutex.lock();
		std::cout
			<< std::endl
			<< " =====< "
			<< mother_communications_.getName()
			<< " received message: "
			<< message.getAuthor()
			<< " ["
			<< message.getMessage()
			<< "] >=====";
		print_mutex.unlock();

		if (message.getType() == "STOP") {
			if (--number_of_children == 0)
			{
				break;
			}
			// The child is done.
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

			mother_communications_.sendMessage(reply);
		}
	}

	mother_communications_.stop();

	print_mutex.lock();
	std::cout << std::endl << "DONE: [" << mothers_name_ << "]#";
	print_mutex.unlock();

	done_ = true;
}