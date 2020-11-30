#include "Message.h"

void messaging::Message::read(IAddressIp* address, vector<string>& strings)
{
	if (strings.size() == 2) {
		address->set(strings[1]);
	}
	else {
		address->setAddress(strings[1]);
		address->setPort(std::stoi(strings[2]));
	}
}

void messaging::Message::read(string& attribute, vector<string>& strings)
{
	int count = 0;

	attribute.clear();
	while (++count < strings.size()) {
		attribute += strings[count];
	}
}

void messaging::Message::read(rsize_t& attribute, vector<string>& strings)
{
	attribute = std::stoi(strings[1]);
}

bool messaging::Message::setType(const string& type)
{
	this->type_ = type;
	return true;
}

bool messaging::Message::setAuthor(const string& author)
{
	this->author_ = author;
	return true;
}

bool messaging::Message::setMessage(const string& message)
{
	this->body_message_ = message;
	this->content_length_ = message.size();
	return true;
}

string messaging::Message::writeMessage()
{
	string final_message;

	final_message += "source:" + this->source_address_->getAddressAndPort() + "\n";
	final_message += "destination:" + this->destination_address_->getAddressAndPort() + "\n";
	final_message += "type:" + this->type_ + "\n";
	final_message += "author:" + this->author_ + "\n";
	final_message += "content-length:" + std::to_string(this->content_length_) + "\n";

	final_message += "body:" + this->body_message_ + "\n";
	final_message += "\n";

	return final_message;
}

messaging::Message messaging::Message::readMessage(const string& message)
{
	vector<string> new_line_split = utility::StringHelper::split(message);

	IAddressIp* source_address = nullptr;
	IAddressIp* destination_address = nullptr;
	string type;
	string author;
	string body;
	rsize_t length;

	for (string line : new_line_split)
	{
		vector<string> colon_split = utility::StringHelper::split(line, ':');

		if (colon_split.size() < 2) {
			// throw an error.  Throwing 20 for some reason.
			throw 20;
		}

		if (colon_split[0] == "source") {
			source_address = new AddressIp4();
			read(source_address, colon_split);
		}
		else if (colon_split[0] == "destination") {
			destination_address = new AddressIp4();
			read(destination_address, colon_split);
		}
		else if (colon_split[0] == "type") {
			read(type, colon_split);
		}
		else if (colon_split[0] == "author") {
			read(author, colon_split);
		}
		else if (colon_split[0] == "content-length") {
			read(length, colon_split);
		}
		else if (colon_split[0] == "body") {
			read(body, colon_split);
		}
	}

	auto the_message = new Message(source_address, destination_address);
	the_message->setAuthor(author);
	the_message->setType(type);
	the_message->setMessage(body);

	return *the_message;
}