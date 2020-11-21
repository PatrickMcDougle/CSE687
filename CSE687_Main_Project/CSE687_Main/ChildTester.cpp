#include "ChildTester.h"

void threading::ChildTester::setup() const
{
	// do something soon.
}

void threading::ChildTester::run() const
{
	Communications communications(child_address_, childs_name_);

	communications.start();
	
	while (true) {
		Message message;
		message.setSource(child_address_);
		message.setDestination(mother_address_);
		message.setType("READY");
		message.setAuthor(childs_name_);
		message.setMessage("Good To Go Mother!");

		communications.sendMessage(message);
		Message response = communications.getMessage();

		::Sleep(1000);

		if (response.getType() == "QUIT") {
			break;
		}
	}

	Message message;
	message.setSource(child_address_);
	message.setDestination(mother_address_);
	message.setType("STOP");
	message.setAuthor(childs_name_);
	message.setMessage("All Done Mother!");
}