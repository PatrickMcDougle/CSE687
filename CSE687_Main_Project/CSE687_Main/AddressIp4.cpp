#include "AddressIp4.h"

string messaging::AddressIp4::getAddress()
{
	int p1 = 0;
	int p2 = 0;
	int p3 = 0;
	int p4 = 0;

	p1 = (this->ip4_address >> 24) & 255;
	p2 = (this->ip4_address >> 16) & 255;
	p3 = (this->ip4_address >> 8) & 255;
	p4 = (this->ip4_address >> 0) & 255;

	string address_string;
	address_string.append(std::to_string(p1));
	address_string.append(".");
	address_string.append(std::to_string(p2));
	address_string.append(".");
	address_string.append(std::to_string(p3));
	address_string.append(".");
	address_string.append(std::to_string(p4));

	return address_string;
}

size_t messaging::AddressIp4::getPort()
{
	return this->ip_port;
}

string messaging::AddressIp4::getAddressAndPort()
{
	string full_address;

	full_address.append(this->getAddress());
	full_address.append(":");
	full_address.append(std::to_string(this->getPort()));

	return full_address;
}

bool messaging::AddressIp4::setAddress(unsigned int address)
{
	this->ip4_address = address;

	return true;
}

bool messaging::AddressIp4::setAddress(int p1, int p2, int p3, int p4)
{
	this->ip4_address = 0;

	if (p1 < 0 || p1 > 255) {
		return false;
	}
	if (p2 < 0 || p2 > 255) {
		return false;
	}
	if (p3 < 0 || p3 > 255) {
		return false;
	}
	if (p4 < 0 || p4 > 255) {
		return false;
	}

	unsigned int p = p1;
	this->ip4_address |= (p << 24);
	p = p2;
	this->ip4_address |= (p << 16);
	p = p3;
	this->ip4_address |= (p << 8);
	p = p4;
	this->ip4_address |= (p << 0);

	return true;
}

bool messaging::AddressIp4::setAddress(const string& address)
{
	this->ip4_address = 0;

	// 8.8.8.8 = 7
	// 255.255.255.255 = 15
	if (address.size() < 7 || address.size() > 15) {
		return false;
	}

	size_t find_dot_1 = address.find('.', 0);
	if (find_dot_1 == string::npos) { return false; }
	if (find_dot_1 < 1 || find_dot_1 > 3) { return false; }

	size_t find_dot_2 = address.find('.', find_dot_1 + 1);
	if (find_dot_2 == string::npos) { return false; }
	if (find_dot_2 < 3 || find_dot_2 > 7) { return false; }

	size_t find_dot_3 = address.find('.', find_dot_2 + 1);
	if (find_dot_3 == string::npos) { return false; }
	if (find_dot_3 < 5 || find_dot_3 > 11) { return false; }

	setAddress(
		std::stoi(address.substr(0, find_dot_1)),
		std::stoi(address.substr(find_dot_1 + 1, find_dot_2 - find_dot_1 - 1)),
		std::stoi(address.substr(find_dot_2 + 1, find_dot_3 - find_dot_2 - 1)),
		std::stoi(address.substr(find_dot_3 + 1))
	);

	return true;
}

bool messaging::AddressIp4::setPort(size_t port)
{
	if (port < 0 || port > 65353) {
		this->ip_port = 0;
		return false;
	}

	this->ip_port = port;
	return true;
}

bool messaging::AddressIp4::set(int p1, int p2, int p3, int p4, size_t port)
{
	return
		setAddress(p1, p2, p3, p4) &&
		setPort(port);
}

bool messaging::AddressIp4::set(const string& address_port)
{
	// 8.8.8.8:1 = 9
	// 255.255.255.255:65353 = 21
	if (address_port.size() < 9 || address_port.size() > 21) {
		return false;
	}

	size_t find_colon = address_port.find(':', 0);
	if (find_colon == string::npos) { return false; }
	if (find_colon < 7 || find_colon > 15) { return false; }

	return
		setAddress(address_port.substr(0, find_colon)) &&
		setPort(std::stoi(address_port.substr(find_colon + 1)));
}