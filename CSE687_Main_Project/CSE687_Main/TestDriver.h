#pragma once
#ifndef __I_TEST_DRIVER_H__
#define __I_TEST_DRIVER_H__

#include <iostream>

namespace test {

	template<typename T>
	class TestDriver
	{
	private:
		bool(T::* the_method_)();
		T* the_class_;
	public:
		~TestDriver() {}
		bool test();

		bool loadTest(T* the_class, bool(T::* the_method)());
		//bool loadTest(T* the_class, bool(T::* the_method)()) {
		//	this.the_method_ = the_method;
		//	this.the_class_ = the_class;

		//	return true;
		//};

		bool runTest()
		{
			bool result = false;
			try {
				result = (the_class_->*the_method_)();
			}
			catch (...) {
				std::cout << "\n  exception thrown";
				result = false;
			}
			return result;
		};
	};
}

#endif // !__I_TEST_DRIVER_H__
