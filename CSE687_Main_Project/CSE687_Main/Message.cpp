#include "Message.h"

void messaging::Message::read(AddressIp4& address, vector<string> strings) const
{
	if (strings.size() == 2) {
		address.set(strings[1]);
	}
	else {
		address.setAddress(strings[1]);
		address.setPort(std::stoi(strings[2]));
	}
}

void messaging::Message::read(string& attribute, vector<string> strings) const
{
	int count = 0;

	attribute.clear();
	while (++count < strings.size()) {
		attribute += strings[count];
	}
}

void messaging::Message::read(rsize_t& attribute, vector<string> strings) const
{
	attribute = std::stoi(strings[1]);
}

bool messaging::Message::setSource(AddressIp4 source)
{
	this->source_address_ = source;
	return true;
}

bool messaging::Message::setDestination(AddressIp4 destination)
{
	this->destination_address_ = destination;
	return true;
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

	final_message += "source:" + this->source_address_.getAddressAndPort() + "\n";
	final_message += "destination:" + this->destination_address_.getAddressAndPort() + "\n";
	final_message += "type:" + this->type_ + "\n";
	final_message += "author:" + this->author_ + "\n";
	final_message += "content-length:" + std::to_string(this->content_length_) + "\n";
	final_message += "body:" + this->body_message_ + "\n";
	final_message += "\n";

	return final_message;
}

bool messaging::Message::readMessage(const string& message)
{
	vector<string> new_line_split = utility::StringHelper::split(message);
	for (string line : new_line_split)
	{
		vector<string> colon_split = utility::StringHelper::split(line, ':');

		if (colon_split.size() > 1) {
			if (colon_split[0] == "source") {
				read(this->source_address_, colon_split);
			}
			else if (colon_split[0] == "destination") {
				read(this->destination_address_, colon_split);
			}
			else if (colon_split[0] == "type") {
				read(this->type_, colon_split);
			}
			else if (colon_split[0] == "author") {
				read(this->author_, colon_split);
			}
			else if (colon_split[0] == "content-length") {
				read(this->content_length_, colon_split);
			}
			else if (colon_split[0] == "body") {
				read(this->body_message_, colon_split);
			}
		}
	}

	return false;
}