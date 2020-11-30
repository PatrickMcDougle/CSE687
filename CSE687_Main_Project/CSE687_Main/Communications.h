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

namespace messaging {
	class Communications
	{
	private:

		Sender sender_;
		Receiver receiver_;
		string name_;

		ClientHandler* client_handler_ = nullptr;

	public:

		Communications(IAddressIp* end_point, const string& name)
			: receiver_(end_point, name), sender_(name), name_(name)
		{
		}

		~Communications() {
			if (client_handler_ != nullptr) {
				delete client_handler_;
				client_handler_ = nullptr;
			}
		};

		void start();
		void stop();
		void sendMessage(Message& message);
		Message getMessage();
		string getName() const;
	};
}

#endif // !__COMMUNICATIONS_H__
