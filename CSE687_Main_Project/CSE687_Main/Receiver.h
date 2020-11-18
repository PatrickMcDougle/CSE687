#pragma once
#ifndef __RECEOVER_H__
#define __RECEOVER_H__

#include <string>
#include <thread>
#include <functional>

#include "Message.h"
#include "BlockingQueue.h"
#include "SocketConnecter.h"
#include "SocketListener.h"

using std::string;
using std::thread;
using messaging::Message;
using messaging::AddressIp4;
using messaging::SocketConnecter;
using queue::BlockingQueue;

namespace messaging {
	class Receiver
	{
	public:
		Receiver(AddressIp4 address, const std::string& name = "Receiver");
		template<typename CallableObject>
		void start(CallableObject& co);
		void stop();
		Message getMessage();
		BlockingQueue<Message>* queue();
	private:
		BlockingQueue<Message> receiver_queue_;
		SocketListener socket_listener_;
		std::string receiver_name_;
	};
}

#endif // !__RECEOVER_H__
