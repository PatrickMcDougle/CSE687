#pragma once
#ifndef __SOCKET_LISTENER_H__
#define __SOCKET_LISTENER_H__

#include <WS2tcpip.h>
#include <atomic>

#include "Socket.h"

namespace messaging {
	class SocketListener : public Socket
	{
	public:
		SocketListener(const SocketListener& s) = delete;
		SocketListener& operator=(const SocketListener& s) = delete;

		SocketListener(size_t port);
		SocketListener(SocketListener&& s);
		SocketListener& operator=(SocketListener&& s) noexcept;
		virtual ~SocketListener();

		template<typename CallObj>
		bool start(CallObj& co);
		void stop();
	private:
		bool bind();
		bool listen();
		Socket accept();

		std::atomic<bool> stop_ = false;
		size_t port_;
		bool accept_failed_ = false;
	};
}

#endif // !__SOCKET_LISTENER_H__