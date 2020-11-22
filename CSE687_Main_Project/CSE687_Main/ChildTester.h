#pragma once
#ifndef __CHILD_TESTER_H__
#define __CHILD_TESTER_H__

#include <string>
#include <iostream>

#include "AddressIp4.h"
#include "Message.h"
#include "Communications.h"
#include "SocketSystem.h"

using std::string;
using messaging::AddressIp4;
using messaging::Message;

namespace threading {
	class ChildTester
	{
	private:
		AddressIp4 child_address_;
		AddressIp4 mother_address_;
		string childs_name_;

	public:

		ChildTester(messaging::AddressIp4 child_address, messaging::AddressIp4 mother_address, const string& childs_name)
			: child_address_(child_address), mother_address_(mother_address), childs_name_(childs_name)
		{
			// nothing at this time.
		};
		~ChildTester() {};

		void setup() const;
		void run() const;
	};
}

#endif // !__CHILD_TESTER_H__
