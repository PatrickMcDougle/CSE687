#pragma once
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <vector>

#include "AddressIp4.h"
#include "StringHelper.h"

using std::string;
using std::vector;

namespace messaging {
	class Message
	{
	private:
		AddressIp4 source_address_;
		AddressIp4 destination_address_;
		time_t timestamp_;
		string type_;
		string author_;
		string body_message_;
		size_t content_length_;

		void read(AddressIp4& address, vector<string> strings) const;
		void read(string& attribute, vector<string> strings) const;
		void read(rsize_t& attribute, vector<string> strings) const;

	public:

		Message() {}
		~Message() {}

		bool setSource(AddressIp4);
		bool setDestination(AddressIp4);
		bool setType(const string&);
		bool setAuthor(const string&);
		bool setMessage(const string&);

		string getType() const { return type_; }
		string getAuthor() const { return author_; }
		AddressIp4 getDestination() const { return destination_address_; }
		AddressIp4 getSource() const { return source_address_; }

		string writeMessage();
		bool readMessage(const string&);
	};
}

#endif // !__MESSAGE_H__
