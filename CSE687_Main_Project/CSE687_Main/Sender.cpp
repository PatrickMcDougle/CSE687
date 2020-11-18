#include "Sender.h"

messaging::Sender::Sender(const std::string& name) : sender_name_(name)
{
	last_ip_address_ = AddressIp4();  // used to detect change in destination
}

messaging::Sender::~Sender()
{
	if (sender_thread_.joinable())
		sender_thread_.join();
}

void messaging::Sender::start()
{
	std::function <void()> threadProc = [&]() {
		while (true)
		{
			Message message = sender_queue_.dequeue();

			if (message.getType() == "quit")
			{
				//StaticLogger<1>::write("\n  -- send thread shutting down"); // TODO
				return;
			}
			//StaticLogger<1>::write("\n  -- " + sender_name_ + " send thread sending " + msg.name()); // TODO
			string message_string = message.writeMessage();

			if (message.getDestination().getAddressAndPort() != last_ip_address_.getAddressAndPort())
			{
				socket_connecter_.shutDown();

				//StaticLogger<1>::write("\n  -- attempting to connect to new endpoint: " + msg.to().toString()); // TODO
				if (!connect(message.getDestination()))
				{
					//StaticLogger<1>::write("\n can't connect"); // TODO
					continue;
				}
				else
				{
					//StaticLogger<1>::write("\n  connected to " + msg.to().toString()); // TODO
				}
			}
			socket_connecter_.send(message_string.length(), (Socket::byte*)message_string.c_str());
		}
	};
	std::thread t(threadProc);
	sender_thread_ = std::move(t);
}

void messaging::Sender::stop()
{
	Message message;
	message.setAuthor(sender_name_);
	message.setType("quit");
	postMessage(message);
	socket_connecter_.shutDown();
}

bool messaging::Sender::connect(AddressIp4 ip_address)
{
	last_ip_address_ = ip_address;
	return socket_connecter_.connect(ip_address.getAddress(), ip_address.getPort());
}

void messaging::Sender::postMessage(Message message)
{
	sender_queue_.enqueue(message);
}