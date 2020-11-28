#pragma once
#ifndef __RECEOVER_H__
#define __RECEOVER_H__

#include <functional>
#include <string>
#include <thread>

#include "BlockingQueue.h"
#include "IAddressIp.h"
#include "Message.h"
#include "SocketConnecter.h"
#include "SocketListener.h"

using std::string;
using std::thread;
using messaging::Message;
using messaging::IAddressIp;
using messaging::SocketConnecter;
using queue::BlockingQueue;

namespace messaging {
	class Receiver
	{
	private:
		BlockingQueue<Message> receiver_queue_;
		SocketListener socket_listener_;
		std::string receiver_name_;

	public:
		Receiver(const IAddressIp* address, const std::string& name = "Receiver")
			: socket_listener_(address->getPort()), receiver_name_(name)
		{
			// do nothing at this time.
		}

		template<typename CallableObject>
		void start(CallableObject& callable_object) {
			socket_listener_.start(callable_object);
		};

		template<typename T>
		void start(T* the_class, bool(T::* the_method)()) {
			socket_listener_.start(the_class, the_method);
		};

		void stop();
		Message getMessage();
		BlockingQueue<Message>* queue();
	};
}

#endif // !__RECEOVER_H__
