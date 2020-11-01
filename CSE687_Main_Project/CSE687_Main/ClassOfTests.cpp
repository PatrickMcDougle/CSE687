#include "ClassOfTests.h"

bool test::ClassOfTests::testTrue()
{
	return true;
}

bool test::ClassOfTests::testFalse()
{
	return false;
}

bool test::ClassOfTests::testException()
{
	throw std::exception("Exception Thrown Test");
	return true;
}