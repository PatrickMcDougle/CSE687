#pragma once
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include "AddressIp4.h"

using std::string;

namespace messaging {
	class Message
	{
	private:
		AddressIp4 source_address;
		AddressIp4 destination_address;
		time_t timestamp;
		string type;
		string author;
		string body_message;
		size_t body_size;

	public:

		Message() {}
		~Message() {}

		bool setSource(AddressIp4);
		bool setDestination(AddressIp4);
		bool setType(const string&);
		bool setAuthor(const string&);
		bool setMessage(const string&);

		string getType() const { return type; }
		AddressIp4 getDestination() const { return destination_address; }

		string writeMessage();
		bool readMessage(const string&);
	};
}

#endif // !__MESSAGE_H__
