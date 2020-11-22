#include "ChildTester.h"

void threading::ChildTester::setup() const
{
	// do something soon.
}

void threading::ChildTester::run() const
{
	// socket system will setup the sockets and tears them down when the
	// class is destroyed.
	messaging::SocketSystem socket_system_setup;

	int sleep_time_milliseconds = 1000 + (childs_name_.size() * 100);

	Communications communications(child_address_, childs_name_);

	communications.start();

	Message message_ready;
	message_ready.setSource(child_address_);
	message_ready.setDestination(mother_address_);
	message_ready.setType("READY");
	message_ready.setAuthor(childs_name_);
	message_ready.setMessage("Good To Go Mother!");

	communications.sendMessage(message_ready);

	while (true) {
		Message message;
		message.setSource(child_address_);
		message.setDestination(mother_address_);
		message.setType("TEST");
		message.setAuthor(childs_name_);
		message.setMessage("I need a test Mother!");

		communications.sendMessage(message);
		Message response = communications.getMessage();

		std::cout
			<< std::endl
			<< " =====< "
			<< communications.getName()
			<< " received message: "
			<< response.getAuthor()
			<< " >=====";

		::Sleep(sleep_time_milliseconds);

		if (response.getType() == "QUIT") {
			break;
		}
	}

	Message message_done;
	message_done.setSource(child_address_);
	message_done.setDestination(mother_address_);
	message_done.setType("STOP");
	message_done.setAuthor(childs_name_);
	message_done.setMessage("All Done Mother!");

	std::cout << std::endl << "DONE: [" << childs_name_ << "]#";
}