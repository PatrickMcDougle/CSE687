#pragma once
#ifndef __SENDER_H__
#define __SENDER_H__

#include <string>
#include <thread>
#include <functional>

#include "BlockingQueue.h"
#include "IAddressIp.h"
#include "Message.h"
#include "SocketConnecter.h"

using std::string;
using std::thread;
using messaging::Message;
using messaging::IAddressIp;
using messaging::SocketConnecter;
using queue::BlockingQueue;

namespace messaging {
	class Sender
	{
	public:
		Sender(const std::string& name = "Sender");
		~Sender();
		void start();
		void stop();
		bool connect(IAddressIp* ip_address);
		void postMessage(Message message);
	private:
		BlockingQueue<Message> sender_queue_;
		SocketConnecter socket_connecter_;
		IAddressIp* last_ip_address_ = new AddressIp4();
		thread sender_thread_;
		string sender_name_;
	};
}

#endif // !__SENDER_H__
