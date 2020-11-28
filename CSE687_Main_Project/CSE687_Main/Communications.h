#pragma once
#ifndef __COMMUNICATIONS_H__
#define __COMMUNICATIONS_H__

#include <string>

#include "Sender.h"
#include "Receiver.h"
#include "Message.h"
#include "ClientHandler.h"
#include "IAddressIp.h"

using std::string;
using messaging::IAddressIp;
using messaging::Message;
using messaging::Sender;
using messaging::Receiver;
using messaging::ClientHandler;

namespace threading {
	class Communications
	{
	private:

		Sender sender_;
		Receiver receiver_;
		string name_;

		ClientHandler* client_handler = nullptr;

	public:

		Communications(IAddressIp* end_point, const string& name)
			: receiver_(end_point, name), sender_(name), name_(name)
		{
		}

		~Communications() {};

		void start();
		void stop();
		void sendMessage(Message& message);
		Message getMessage();
		string getName() const;
	};
}

#endif // !__COMMUNICATIONS_H__
