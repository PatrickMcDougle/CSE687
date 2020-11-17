#include "Message.h"

bool messaging::Message::setSource(AddressIp4 source)
{
	this->source_address = source;
	return true;
}

bool messaging::Message::setDestination(AddressIp4 destination)
{
	this->destination_address = destination;
	return true;
}

bool messaging::Message::setType(const string& type)
{
	this->type = type;
	return true;
}

bool messaging::Message::setAuthor(const string& author)
{
	this->author = author;
	return true;
}

bool messaging::Message::setMessage(const string& message)
{
	this->body_message = message;
	this->body_size = message.size();
	return true;
}

string messaging::Message::writeMessage()
{
	string final_message;

	final_message += "source:" + this->source_address.getAddressAndPort() + "\n";
	final_message += "destination:" + this->destination_address.getAddressAndPort() + "\n";
	final_message += "type:" + this->type + "\n";
	final_message += "author:" + this->author + "\n";
	final_message += "content-length:" + std::to_string(this->body_size) + "\n";
	final_message += "\n";
	final_message += this->body_message;

	return final_message;
}

bool messaging::Message::readMessage(const string& message)
{
	return false;
}