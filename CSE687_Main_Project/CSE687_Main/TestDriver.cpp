#include "TestDriver.h"

template<typename T>
bool test::TestDriver<T>::test()
{
	return false;
}

template<typename T>
bool test::TestDriver<T>::loadTest(T* the_class,  bool(T::* the_method)())
{
	this.the_method_ = the_method;
	this.the_class_ = the_class;

	return true;
}

//template<typename T>
//bool test::TestDriver<T>::runTest()
//{
//	bool result = false;
//	try {
//		result = (the_class_->*the_method_)();
//	}
//	catch (...) {
//		std::cout << "\n  exception thrown";
//		result = false;
//	}
//	return result;
//}
