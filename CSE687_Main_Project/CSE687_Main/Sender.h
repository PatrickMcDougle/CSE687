#pragma once
#ifndef __SENDER_H__
#define __SENDER_H__

#include <string>
#include <thread>
#include <functional>

#include "Message.h"
#include "BlockingQueue.h"
#include "SocketConnecter.h"

using std::string;
using std::thread;
using messaging::Message;
using messaging::AddressIp4;
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
		bool connect(AddressIp4 ip_address);
		void postMessage(Message message);
	private:
		BlockingQueue<Message> sender_queue_;
		SocketConnecter socket_connecter_;
		thread sender_thread_;
		AddressIp4 last_ip_address_;
		string sender_name_;
	};
}

#endif // !__SENDER_H__
