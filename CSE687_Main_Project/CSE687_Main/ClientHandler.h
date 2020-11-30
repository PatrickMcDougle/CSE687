#pragma once
#ifndef __CLIENT_HANDLER_H__
#define __CLIENT_HANDLER_H__

#include <string>
#include "BlockingQueue.h"
#include "Message.h"
#include "Socket.h"

using std::string;
using queue::BlockingQueue;

namespace messaging {
	class ClientHandler {
	public:
		ClientHandler(BlockingQueue<Message>* blocking_queue, const string& name)
			: blocking_queue_(blocking_queue), name_(name) {};
		~ClientHandler() {};

		void setQueue(BlockingQueue<Message>* blocking_queue);

		void operator()(Socket socket);

	private:
		BlockingQueue<Message>* blocking_queue_ = nullptr;
		string name_;

		string readMessage(Socket& socket) const;
	};
}

#endif // !__CLIENT_HANDLER_H__
