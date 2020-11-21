#include "Receiver.h"


messaging::Receiver::Receiver(AddressIp4 address, const std::string& name) : socket_listener_(address.getPort()), receiver_name_(name)
{
	//StaticLogger<1>::write("\n  -- starting Receiver"); // TODO
}

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