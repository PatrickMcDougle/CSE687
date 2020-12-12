#pragma once
#ifndef __ADDRESS_IP_4_H__
#define __ADDRESS_IP_4_H__

#include <string>

#include "IAddressIp.h"

using std::string;

namespace messaging {
	/// <summary>
	/// This class stores an IP version 4 network address for use by network code.
	/// </summary>
	class AddressIp4 : public IAddressIp
	{
	private:
		// an unsigned int value will store the whole IP address in it.
		// size is super small compared to storing string or individual addresses.
		// ip4_address : 127.0.0.1 = 2130706433
		unsigned int ip4_address = 2130706433;

		// store the port value.
		size_t ip_port = 50000;

	public:
		/// <summary>
		/// This method will return just the address as a string that is readable
		///  by humans and can be used by the system
		/// </summary>
		/// <returns>Returns a string of the address without the port number.</returns>
		string getAddress() const;

		/// <summary>
		/// This method will return just the port number.
		/// </summary>
		/// <returns>Returns the port number as a size_t(int) value.</returns>
		size_t getPort() const;

		/// <summary>
		/// This method will return the address as a string that is readable by
		///  humans and can be used by the system
		/// </summary>
		/// <returns>Returns a string of the address with the port number.</returns>
		string getAddressAndPort();

		/// <summary>
		/// This method will set the address
		/// </summary>
		/// <param name="">This value is the address as one int value.</param>
		/// <returns>Returns true on success.</returns>
		bool setAddress(unsigned int);

		/// <summary>
		/// This method will set the address
		/// </summary>
		/// <param name="">The first byte of the address</param>
		/// <param name="">The second byte of the address</param>
		/// <param name="">The third byte of the address</param>
		/// <param name="">The fourth byte of the address</param>
		/// <returns>Returns true on success.</returns>
		bool setAddress(int, int, int, int);

		/// <summary>
		/// This method will set the address
		/// </summary>
		/// <param name="">This value is the address as a string.  This string
		///  only contains the 4 ip address numbers seperated by '.'.</param>
		/// <returns>Returns true on success.</returns>
		bool setAddress(const string&);

		/// <summary>
		/// This method will set the port number.
		/// </summary>
		/// <param name="">This value is teh port number as a size_t(int)</param>
		/// <returns>Returns true on success.</returns>
		bool setPort(size_t);

		/// <summary>
		/// This method will set the address
		/// </summary>
		/// <param name="">The first byte of the address</param>
		/// <param name="">The second byte of the address</param>
		/// <param name="">The third byte of the address</param>
		/// <param name="">The fourth byte of the address</param>
		/// <param name="">This value is teh port number as a size_t(int)</param>
		/// <returns>Returns true on success.</returns>
		/// <returns></returns>
		bool set(int, int, int, int, size_t);

		/// <summary>
		/// This method will set the address
		/// </summary>
		/// <param name="">This value is the address as a string.  This string
		///   contains the 4 ip address numbers seperated by '.' as well as a port number after ':'.</param>
		/// <returns>Returns true on success.</returns>
		bool set(const string&);
	};
}

#endif // !__ADDRESS_IP_4_H__
