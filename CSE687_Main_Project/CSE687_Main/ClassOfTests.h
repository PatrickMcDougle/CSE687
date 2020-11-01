#pragma once
#ifndef __I_CLASS_OF_TESTS_H__
#define __I_CLASS_OF_TESTS_H__

#include <exception>

namespace test {
	class ClassOfTests
	{
	public:
		~ClassOfTests() {}
		bool testTrue();
		bool testFalse();
		bool testException();
	};
}

#endif // !__I_CLASS_OF_TESTS_H__
