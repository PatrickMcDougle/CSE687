#pragma once
#ifndef __SOCKET_LISTENER_H__
#define __SOCKET_LISTENER_H__

#include <WS2tcpip.h>     // support for IPv6 and other things
#include <iphlpapi.h>     // ip helpers

#include <atomic>
#include <thread>

#include "Socket.h"

namespace messaging {
	class SocketListener : public Socket
	{
	public:
		SocketListener(const SocketListener& s) = delete;
		SocketListener& operator=(const SocketListener& s) = delete;

		SocketListener(size_t port);
		SocketListener(SocketListener&& s) noexcept;
		SocketListener& operator=(SocketListener&& s) noexcept;
		virtual ~SocketListener();

		template<typename CallObj>
		bool start(CallObj& co);

		template<typename T>
		bool start(T* the_class, bool(T::* the_method)());

		void stop();
	private:
		bool bind();
		bool listen();
		Socket accept();

		std::atomic<bool> stop_ = false;
		size_t port_ = 60000;
		bool accept_failed_ = false;
	};

	template<typename CallObj>
	bool messaging::SocketListener::start(CallObj& co)
	{
		if (!bind())
		{
			return false;
		}

		if (!listen())
		{
			return false;
		}
		// listen on a dedicated thread so server's main thread won't block

		std::thread ListenThread(
			[&]()
			{
				//StaticLogger<1>::write("\n  -- server waiting for connection"); // TODO

				while (!accept_failed_)
				{
					if (stop_.load())
						break;

					// Accept a client socket - blocking call

					Socket clientSocket = accept();    // uses move ctor
					if (!clientSocket.validState()) {
						continue;
					}
					//StaticLogger<1>::write("\n  -- server accepted connection"); // TODO

					// start thread to handle client request

					//std::thread clientThread(std::ref(co), std::move(clientSocket)); // Why commented out?
					std::thread clientThread(co, std::move(clientSocket));
					clientThread.detach();  // detach - listener won't access thread again
				}
				//StaticLogger<1>::write("\n  -- Listen thread stopping"); // TODO
			}
		);
		ListenThread.detach();
		return true;
	}

	template<typename T>
	bool messaging::SocketListener::start(T* the_class, bool(T::* the_method)())
	{
		if (!bind())
		{
			return false;
		}

		if (!listen())
		{
			return false;
		}
		// listen on a dedicated thread so server's main thread won't block

		std::thread ListenThread(
			[&]()
			{
				//StaticLogger<1>::write("\n  -- server waiting for connection"); // TODO

				while (!accept_failed_)
				{
					if (stop_.load())
						break;

					// Accept a client socket - blocking call

					Socket clientSocket = accept();    // uses move ctor
					if (!clientSocket.validState()) {
						continue;
					}
					//StaticLogger<1>::write("\n  -- server accepted connection"); // TODO

					// start thread to handle client request

					//std::thread clientThread(std::ref(co), std::move(clientSocket)); // Why commented out?
					//std::thread clientThread(co, std::move(clientSocket)); // original way of doing this.
					std::thread clientThread(the_class, the_method, std::move(clientSocket));
					clientThread.detach();  // detach - listener won't access thread again
				}
				//StaticLogger<1>::write("\n  -- Listen thread stopping"); // TODO
			}
		);
		ListenThread.detach();
		return true;
	}
}

#endif // !__SOCKET_LISTENER_H__