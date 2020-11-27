#pragma once
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <string>
#include <vector>

#include "AddressIp4.h"
#include "IAddressIp.h"
#include "StringHelper.h"

using std::string;
using std::vector;

namespace messaging {
	class Message
	{
	private:
		time_t timestamp_ = 0;

		IAddressIp* source_address_;
		IAddressIp* destination_address_;

		string type_;
		string author_;

		string body_message_;
		size_t content_length_ = 0;

		static	void read(IAddressIp* address, vector<string>& strings);
		static	void read(string& attribute, vector<string>& strings);
		static	void read(rsize_t& attribute, vector<string>& strings);

	public:

		Message(IAddressIp* address_source, IAddressIp* address_destination)
			: source_address_(address_source), destination_address_(address_destination)
		{
			// do nothing else at this time.
		}
		~Message() {}

		bool setType(const string&);
		bool setAuthor(const string&);
		bool setMessage(const string&);

		string getType() const { return type_; }
		string getAuthor() const { return author_; }
		IAddressIp* getDestination() const { return destination_address_; }
		IAddressIp* getSource() const { return source_address_; }
		string getMessage() const { return body_message_; }

		string writeMessage();
		static	Message readMessage(const string&);
	};
}

#endif // !__MESSAGE_H__
