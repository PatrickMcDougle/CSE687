#include "ChildTester.h"

void threading::ChildTester::setup(ILogger* logger)
{
	this->logger_ = logger;
}

void threading::ChildTester::run()
{
	// socket system will setup the sockets and tears them down when the
	// class is destroyed.
	messaging::SocketSystem socket_system_setup;

	DWORD sleep_time_milliseconds = 500 + ((DWORD)childs_name_.size() * 200);

	Communications communications(child_address_, childs_name_);

	communications.start();

	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_milliseconds));
	//::Sleep(sleep_time_milliseconds);

	Message message_ready(child_address_, mother_address_);
	message_ready.setType("READY");
	message_ready.setAuthor(childs_name_);
	message_ready.setMessage("Ready To Go Mother!");

	communications.sendMessage(message_ready);

	while (true) {
		// Wait for Mother to respond back.
		Message response = communications.getMessage();

		print_mutex.lock();
		std::cout
			<< std::endl
			<< " =====< "
			<< communications.getName()
			<< " received message: "
			<< response.getAuthor()
			<< " ["
			<< response.getMessage()
			<< "] >=====";
		print_mutex.unlock();

		if (response.getType() == "QUIT") {
			// mother says we are done.
			break;
		}
		if (response.getType() == "TEST_REQUEST") {
			ITest* itest = this->blocking_queue_of_test_drivers_.dequeue();

			++test_performed;
			bool results = itest->test();

			Message message(child_address_, mother_address_);
			message.setType("TEST_RESULTS");
			message.setAuthor(childs_name_);
			message.setMessage("<test><results>" + std::to_string(results) + "</results><log>" + itest->testLogResults() + "</log></test>");

			delete itest;

			communications.sendMessage(message);
		}
	}

	Message message_done(child_address_, mother_address_);
	message_done.setType("STOP");
	message_done.setAuthor(childs_name_);
	message_done.setMessage("All Done Mother!");

	communications.sendMessage(message_done);

	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_milliseconds));

	communications.stop();

	print_mutex.lock();
	std::cout
		<< std::endl
		<< " #####< "
		<< childs_name_
		<< " RUN DONE "
		<< " >#####";
	print_mutex.unlock();
}