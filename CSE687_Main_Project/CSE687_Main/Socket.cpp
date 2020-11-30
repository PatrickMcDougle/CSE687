#include "Socket.h"

messaging::Socket::Socket()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

messaging::Socket::Socket(::SOCKET sock) : socket_(sock)
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

messaging::Socket::Socket(Socket&& s) : socket_(s.socket_)
{
	s.socket_ = INVALID_SOCKET;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = s.hints.ai_family;
	hints.ai_socktype = s.hints.ai_socktype;
	hints.ai_protocol = s.hints.ai_protocol;
}

messaging::Socket& messaging::Socket::operator=(messaging::Socket&& s)
{
	if (this == &s) return *this;
	socket_ = s.socket_;
	s.socket_ = INVALID_SOCKET;
	hints.ai_family = s.hints.ai_family;
	hints.ai_socktype = s.hints.ai_socktype;
	hints.ai_protocol = s.hints.ai_protocol;
	return *this;
}

void messaging::Socket::close() const
{
	if (socket_ != INVALID_SOCKET)
		::closesocket(socket_);
}

bool messaging::Socket::shutDownSend() const
{
	::shutdown(socket_, SD_SEND);
	if (socket_ != INVALID_SOCKET)
		return true;
	return false;
}

bool messaging::Socket::shutDownRecv() const
{
	::shutdown(socket_, SD_RECEIVE);
	if (socket_ != INVALID_SOCKET)
		return true;
	return false;
}

bool messaging::Socket::shutDown() const
{
	::shutdown(socket_, SD_BOTH);
	if (socket_ != INVALID_SOCKET)
		return true;
	return false;
}

messaging::Socket::~Socket() {
	shutDown();
	close();
}

bool messaging::Socket::send(size_t bytes, byte* buffer)
{
	size_t bytesSent = 0;
	size_t bytesLeft = bytes;
	byte* pBuf = buffer;

	while (bytesLeft > 0)
	{
		bytesSent = ::send(socket_, pBuf, bytesLeft, 0);
		if (socket_ == INVALID_SOCKET || bytesSent == 0)
			return false;
		bytesLeft -= bytesSent;
		pBuf += bytesSent;
	}
	return true;
}

bool messaging::Socket::recv(size_t bytes, byte* buffer)
{
	size_t bytesRecvd = 0;
	size_t bytesLeft = bytes;
	byte* pBuf = buffer;

	while (bytesLeft > 0)
	{
		bytesRecvd = ::recv(socket_, pBuf, bytesLeft, 0);
		if (socket_ == INVALID_SOCKET || bytesRecvd == 0)
			return false;
		bytesLeft -= bytesRecvd;
		pBuf += bytesRecvd;
	}
	return true;
}

bool messaging::Socket::sendString(const std::string& str, byte terminator)
{
	size_t bytesSent;
	size_t bytesRemaining = str.size();

	const byte* pBuf = &(*str.begin());
	while (bytesRemaining > 0)
	{
		bytesSent = ::send(socket_, pBuf, bytesRemaining, 0);
		if (bytesSent == INVALID_SOCKET || bytesSent == 0)
			return false;
		bytesRemaining -= bytesSent;
		pBuf += bytesSent;
	}
	::send(socket_, &terminator, 1, 0);
	return true;
}

std::string messaging::Socket::recvString(byte terminator)
{
	static const int buflen = 1;
	char buffer[1];
	std::string str;
	bool first = true;

	while (true)
	{
		iResult = ::recv(socket_, buffer, buflen, 0);
		if (iResult == 0 || iResult == INVALID_SOCKET)
		{
			//StaticLogger<1>::write("\n  -- invalid socket in Socket::recvString");
			break;
		}
		if (buffer[0] == terminator)
		{
			// added 9/29/2017
			str += terminator;
			break;
		}
		str += buffer[0];
	}
	return str;
}

std::string messaging::Socket::removeTerminator(const std::string& src)
{
	return src.substr(0, src.size() - 1);
}

size_t messaging::Socket::sendStream(size_t bytes, byte* pBuf) const
{
	return ::send(socket_, pBuf, bytes, 0);
}

size_t messaging::Socket::recvStream(size_t bytes, byte* pBuf) const
{
	return ::recv(socket_, pBuf, bytes, 0);
}

size_t messaging::Socket::bytesWaiting()
{
	unsigned long int ret;

	ioctlsocket(socket_, FIONREAD, &ret);
	return (size_t)ret;
}

bool messaging::Socket::waitForData(size_t time_to_wait, size_t time_to_check)
{
	size_t max_count = time_to_wait / time_to_check;
	static size_t count = 0;
	while (bytesWaiting() == 0)
	{
		if (++count > max_count) {
			return false;
		}

		Sleep(time_to_check);
	}
	return true;
}