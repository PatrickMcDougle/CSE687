#include "Receiver.h"

BlockingQueue<Message>* messaging::Receiver::queue()
{
	return &receiver_queue_;
}

void messaging::Receiver::stop()
{
	socket_listener_.stop();
}

Message messaging::Receiver::getMessage()
{
	//StaticLogger<1>::write("\n  -- " + rcvrName + " deQing message"); // TODO
	return receiver_queue_.dequeue();
}