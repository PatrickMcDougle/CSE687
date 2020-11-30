#pragma once
#ifndef __I_ADDRESS_IP_H__
#define __I_ADDRESS_IP_H__

#include <string>

using std::string;

namespace messaging {
	/// <summary>
	/// Interface Class to handle IP Addressing.
	/// </summary>
	class IAddressIp {
	public:
		virtual ~IAddressIp() {};

		virtual string getAddress() const = 0;
		virtual size_t getPort() const = 0;
		virtual string getAddressAndPort() = 0;

		virtual bool setAddress(unsigned int) = 0;
		virtual bool setAddress(int, int, int, int) = 0;
		virtual bool setAddress(const string&) = 0;
		virtual bool setPort(size_t) = 0;

		virtual bool set(int, int, int, int, size_t) = 0;
		virtual bool set(const string&) = 0;
	};
}

#endif // !__I_ADDRESS_IP_H__