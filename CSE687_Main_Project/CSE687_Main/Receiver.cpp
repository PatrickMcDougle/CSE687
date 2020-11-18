#include "Receiver.h"


messaging::Receiver::Receiver(AddressIp4 address, const std::string& name) : socket_listener_(address.getPort()), receiver_name_(name)
{
	//StaticLogger<1>::write("\n  -- starting Receiver"); // TODO
}
//----< returns reference to receive queue >-------------------------

BlockingQueue<Message>* messaging::Receiver::queue()
{
	return &receiver_queue_;
}
//----< starts listener thread running callable object >-------------

template<typename CallableObject>
void messaging::Receiver::start(CallableObject& co)
{
	socket_listener_.start(co);
}
//----< stops listener thread >--------------------------------------

void messaging::Receiver::stop()
{
	socket_listener_.stop();
}
//----< retrieves received message >---------------------------------

Message messaging::Receiver::getMessage()
{
	//StaticLogger<1>::write("\n  -- " + rcvrName + " deQing message"); // TODO
	return receiver_queue_.dequeue();
}