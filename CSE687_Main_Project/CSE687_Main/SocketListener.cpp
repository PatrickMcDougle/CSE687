#include "SocketListener.h"

messaging::SocketListener::SocketListener(size_t port) : Socket(), port_(port)
{
	socket_ = INVALID_SOCKET;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;        // this gives IP4 address
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

messaging::SocketListener::SocketListener(SocketListener&& s) noexcept : Socket()
{
	socket_ = s.socket_;
	s.socket_ = INVALID_SOCKET;
	hints.ai_family = s.hints.ai_family;
	hints.ai_socktype = s.hints.ai_socktype;
	hints.ai_protocol = s.hints.ai_protocol;
	hints.ai_flags = s.hints.ai_flags;
}

messaging::SocketListener& messaging::SocketListener::operator=(messaging::SocketListener&& s) noexcept
{
	if (this == &s) { return *this; }

	socket_ = s.socket_;
	s.socket_ = INVALID_SOCKET;
	hints.ai_family = s.hints.ai_family;
	hints.ai_socktype = s.hints.ai_socktype;
	hints.ai_protocol = s.hints.ai_protocol;
	hints.ai_flags = s.hints.ai_flags;
	return *this;
}

messaging::SocketListener::~SocketListener()
{
	//Show::write("\n  -- SocketListener instance destroyed"); // TODO
}

bool messaging::SocketListener::bind()
{
	//Show::write("\n  -- staring bind operation"); // TODO

	// Resolve the server address and port

	size_t uport = ::htons((u_short)port_);
	//StaticLogger<1>::write("\n  -- netstat uport = " + std::to_string(uport)); // TODO
	std::string sPort = std::to_string(uport);
	iResult = getaddrinfo(NULL, sPort.c_str(), &hints, &result);
	if (iResult != 0) {
		//Show::write("\n  -- getaddrinfo failed with error: " + std::to_string(iResult)); // TODO
		return false;
	}

	// Iterate through all results and bind to first available or all, depending on else condition, below

	for (auto pResult = result; pResult != NULL; pResult = pResult->ai_next)
	{
		// Create a SOCKET for connecting to server

		socket_ = socket(pResult->ai_family, pResult->ai_socktype, pResult->ai_protocol);
		if (socket_ == INVALID_SOCKET) {
			//int error = WSAGetLastError(); // TODO
			//Show::write("\n  -- socket failed with error: " + std::to_string(error)); // TODO
			continue;
		}
		//Show::write("\n  -- server created ListenSocket"); // TODO

		// Setup the TCP listening socket

		iResult = ::bind(socket_, pResult->ai_addr, (int)pResult->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			//int error = WSAGetLastError(); // TODO
			//Show::write("\n  -- bind failed with error: " + std::to_string(error)); // TODO
			socket_ = INVALID_SOCKET;
			continue;
		}
		else
		{
			//break;  // bind to first available
			continue;   // bind to all
		}
	}
	freeaddrinfo(result);
	//Show::write("\n  -- bind operation complete"); // TODO
	return true;
}

bool messaging::SocketListener::listen()
{
	//Show::write("\n  -- starting TCP listening socket setup"); // TODO
	iResult = ::listen(socket_, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		//int error = WSAGetLastError(); // TODO
		//Show::write("\n  -- listen failed with error: " + std::to_string(error)); // TODO
		socket_ = INVALID_SOCKET;
		return false;
	}
	//Show::write("\n  -- server TCP listening socket setup complete"); // TODO
	return true;
}

messaging::Socket messaging::SocketListener::accept()
{
	::SOCKET sock = ::accept(socket_, NULL, NULL);
	Socket clientSocket = sock;    // uses Socket(::SOCKET) promotion ctor
	if (!clientSocket.validState()) {
		accept_failed_ = true;
		//int error = WSAGetLastError(); // TODO
		//Show::write("\n  -- server accept failed with error: " + std::to_string(error)); // TODO
		//Show::write("\n  -- this occurs when application shuts down while listener thread is blocked on Accept call"); // TODO
		//return clientSocket; // TODO
	}
	return clientSocket;
}

void messaging::SocketListener::stop()
{
	stop_.exchange(true);
	sendString("Stop!");
}