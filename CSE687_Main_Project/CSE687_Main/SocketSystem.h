#pragma once
#ifndef __SOCKET_SYSTEM_H__
#define __SOCKET_SYSTEM_H__

#include <iostream>
#include <string>
#include <WinSock2.h>

namespace messaging {
	class SocketSystem
	{
	public:
		SocketSystem();
		~SocketSystem();

	private:
		int initialization_results_;
		WSADATA wsa_data_;
	};
}

#endif // !__SOCKET_SYSTEM_H__