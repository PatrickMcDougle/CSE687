#include "ClientHandler.h"

void messaging::ClientHandler::setQueue(BlockingQueue<Message>* blocking_queue)
{
	blocking_queue_ = blocking_queue;
}

string messaging::ClientHandler::readMessage(Socket& socket) const
{
	string temp;
	string message_string;

	while (socket.validState()) {
		temp = socket.recvString('\n');
		message_string += temp;
		if (temp.length() < 2) {
			// if the line is empty, then we are done.
			break;
		}
	}

	return message_string;
}

void messaging::ClientHandler::operator()(Socket socket)
{
	while (socket.validState()) {
		string message_string = readMessage(socket);
		if (message_string.length() == 0) {
			// invalid message
			break;
		}

		Message message;
		message.readMessage(message_string);
		blocking_queue_->enqueue(message);

		if (message.getType() == "QUIT") {
			break;
		}
	}
}