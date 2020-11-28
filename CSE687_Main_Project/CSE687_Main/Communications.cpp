#include "Communications.h"

void threading::Communications::start()
{
	BlockingQueue<Message>* blocking_queue = receiver_.queue();

	client_handler = new ClientHandler(blocking_queue, name_);

	receiver_.start(*client_handler);
	sender_.start();
}

void threading::Communications::stop()
{
	receiver_.stop();
	sender_.stop();

	delete client_handler;
}

void threading::Communications::sendMessage(Message& message)
{
	sender_.postMessage(message);
}

Message threading::Communications::getMessage()
{
	return receiver_.getMessage();
}

string threading::Communications::getName() const
{
	return name_;
}