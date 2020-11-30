#pragma once
#ifndef __STRING_HELPER_H__
#define __STRING_HELPER_H__

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace utility {
	class StringHelper
	{
	public:
		static vector<string> split(const string& src, char splitter = '\n');

	private:
		// make constructor private so that no one tries to instantiate this class.
		StringHelper() {}
	};
}

#endif // !__STRING_HELPER_H__