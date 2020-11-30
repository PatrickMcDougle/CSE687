#pragma once
#ifndef __SOCKET_CONNECTER_H__
#define __SOCKET_CONNECTER_H__

#include <WS2tcpip.h>

#include "Socket.h"

namespace messaging {
	class SocketConnecter : public Socket
	{
	public:
		SocketConnecter(const SocketConnecter& s) = delete;
		SocketConnecter& operator=(const SocketConnecter& s) = delete;

		SocketConnecter();
		SocketConnecter(SocketConnecter&& s);
		SocketConnecter& operator=(SocketConnecter&& s);
		virtual ~SocketConnecter();

		bool connect(const std::string& ip, size_t port);
	};
}

#endif // !__SOCKET_CONNECTER_H__