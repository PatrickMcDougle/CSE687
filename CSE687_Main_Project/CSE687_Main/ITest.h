#pragma once
#ifndef __I_TEST_H__
#define __I_TEST_H__

namespace test {
	class ITest
	{
	public:
		virtual ~ITest() {}
		virtual bool test() = 0;
	};
}

#endif // !__I_TEST_H__
