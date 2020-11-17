#pragma once
#ifndef __ADDRESS_IP_4_H__
#define __ADDRESS_IP_4_H__

#include <string>

using std::string;

namespace messaging {
	class AddressIp4
	{
	private:
		unsigned int ip4_address;
		int ip_port;

	public:
		string getAddress();
		int getPort();
		string getAddressAndPort();

		bool setAddress(unsigned int);
		bool setAddress(int, int, int, int);
		bool setAddress(const string&);
		bool setPort(int);

		bool set(int, int, int, int, int);
		bool set(const string&);
	};
}

#endif // !__ADDRESS_IP_4_H__
