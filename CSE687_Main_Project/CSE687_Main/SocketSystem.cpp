#include "SocketSystem.h"

messaging::SocketSystem::SocketSystem()
{
	initialization_results_ = WSAStartup(MAKEWORD(2, 2), &wsa_data_);
	if (initialization_results_ != 0) {
		std::cout << "\n  WSAStartup failed with error = " + std::to_string(initialization_results_);
		//Show::write("\n  WSAStartup failed with error = " + Conv<int>::toString(initialization_results_));  // TODO
	}
}

messaging::SocketSystem::~SocketSystem()
{
	int error = WSACleanup();
	std::cout
		<< "\n  -- Socket System cleaning up with error code ["
		<< std::to_string(error)
		<< "]\n";
	//Show::write("\n  -- Socket System cleaning up\n");  // TODO
}