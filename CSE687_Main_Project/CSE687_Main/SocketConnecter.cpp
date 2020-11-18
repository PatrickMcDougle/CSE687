#include "SocketConnecter.h"

messaging::SocketConnecter::SocketConnecter() : Socket()
{
	hints.ai_family = AF_UNSPEC;
}

messaging::SocketConnecter::SocketConnecter(SocketConnecter&& s) : Socket()
{
	socket_ = s.socket_;
	s.socket_ = INVALID_SOCKET;
	hints.ai_family = s.hints.ai_family;
	hints.ai_socktype = s.hints.ai_socktype;
	hints.ai_protocol = s.hints.ai_protocol;
}

messaging::SocketConnecter& messaging::SocketConnecter::operator=(SocketConnecter&& s)
{
	if (this == &s) return *this;
	socket_ = s.socket_;
	s.socket_ = INVALID_SOCKET;
	hints.ai_family = s.hints.ai_family;
	hints.ai_socktype = s.hints.ai_socktype;
	hints.ai_protocol = s.hints.ai_protocol;
	return *this;
}

messaging::SocketConnecter::~SocketConnecter()
{
}

bool messaging::SocketConnecter::connect(const std::string& ip, size_t port)
{
	size_t uport = htons((u_short)port);
	string port_string = std::to_string(uport);

	// Resolve the server address and port
	const char* p_temp_ip = ip.c_str();

	iResult = getaddrinfo(p_temp_ip, port_string.c_str(), &hints, &result);
	if (iResult != 0) {
		//Show::write("\n  -- getaddrinfo failed with error: " + std::to_string(iResult)); // TODO
		return false;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		char ip_char_array[INET6_ADDRSTRLEN];
		void* address;

		// get pointer to address - different fields in IPv4 and IPv6:

		if (ptr->ai_family == AF_INET) { // IPv4
			auto ipv4 = (struct sockaddr_in*)ptr->ai_addr;
			address = &(ipv4->sin_addr);
		}
		else {
			// ERROR
			// TODO
			// NOT SUPPORTING IPv6 at this time.
			continue;
		}

		// convert the IP to a string and print it:
		inet_ntop(ptr->ai_family, address, ip_char_array, sizeof ip_char_array);

		// Create a SOCKET for connecting to server
		socket_ = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (socket_ == INVALID_SOCKET) {
			//int error = WSAGetLastError(); // TODO
			//Show::write("\n\n  -- socket failed with error: " + std::to_string(error)); // TODO
			return false;
		}

		iResult = ::connect(socket_, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			socket_ = INVALID_SOCKET;
			int error = WSAGetLastError();
			//Show::write("\n  -- WSAGetLastError returned " + std::to_string(error)); // TODO
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (socket_ == INVALID_SOCKET) {
		int error = WSAGetLastError();
		//Show::write("\n  -- unable to connect to server, error = " + std::to_string(error)); // TODO
		return false;
	}
	return true;
}