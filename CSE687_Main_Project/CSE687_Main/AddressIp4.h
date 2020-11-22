#pragma once
#ifndef __ADDRESS_IP_4_H__
#define __ADDRESS_IP_4_H__

#include <string>

using std::string;

namespace messaging {
	class AddressIp4
	{
	private:
		// ip4_address : 127.0.0.1 = 2130706433
		unsigned int ip4_address;
		size_t ip_port;

	public:
		string getAddress() const;
		size_t getPort() const;
		string getAddressAndPort();

		bool setAddress(unsigned int);
		bool setAddress(int, int, int, int);
		bool setAddress(const string&);
		bool setPort(size_t);

		bool set(int, int, int, int, size_t);
		bool set(const string&);
	};
}

#endif // !__ADDRESS_IP_4_H__
