#pragma once
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

using std::string;

namespace messaging {
	class Socket
	{
	public:
		using byte = char;

		// disable copy construction and assignment
		Socket(const Socket& s) = delete;
		Socket& operator=(const Socket& s) = delete;

		Socket();
		Socket(::SOCKET);
		Socket(Socket&& s);
		operator ::SOCKET() { return socket_; }
		Socket& operator=(Socket&& s);
		virtual ~Socket();

		bool send(size_t bytes, byte* buffer);
		bool recv(size_t bytes, byte* buffer);
		size_t sendStream(size_t bytes, byte* buffer) const;
		size_t recvStream(size_t bytes, byte* buffer) const;
		bool sendString(const string& str, byte terminator = '\0');
		string recvString(byte terminator = '\0');
		static string removeTerminator(const string& src);
		size_t bytesWaiting();
		bool waitForData(size_t timeToWait, size_t timeToCheck);
		bool shutDownSend() const;
		bool shutDownRecv() const;
		bool shutDown() const;
		void close() const;

		bool validState() { return socket_ != INVALID_SOCKET; }

	protected:
		WSADATA wsaData;
		SOCKET socket_;
		struct addrinfo* result = NULL, * ptr = NULL, hints;
		int iResult;
	};
}

#endif // !__SOCKET_H__