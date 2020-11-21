#include "ChildTester.h"

void threading::ChildTester::setup() const
{
	// do something soon.
}

void threading::ChildTester::run() const
{
	while (true) {
		Message message;
		message.setSource(child_address_);
		message.setDestination(mother_address_);
		message.setType("READY");
		message.setAuthor(childs_name_);
		message.setMessage("Good To Go Mother!");
	}
}