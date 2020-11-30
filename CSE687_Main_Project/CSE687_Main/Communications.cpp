#include "Communications.h"

void messaging::Communications::start()
{
	BlockingQueue<Message>* blocking_queue = receiver_.queue();

	client_handler_ = new ClientHandler(blocking_queue, name_);

	receiver_.start(*client_handler_);
	sender_.start();
}

void messaging::Communications::stop()
{
	sender_.stop();
	receiver_.stop();
}

void messaging::Communications::sendMessage(Message& message)
{
	sender_.postMessage(message);
}

Message messaging::Communications::getMessage()
{
	return receiver_.getMessage();
}

string messaging::Communications::getName() const
{
	return name_;
}