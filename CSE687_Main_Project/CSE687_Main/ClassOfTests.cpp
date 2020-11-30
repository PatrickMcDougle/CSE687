// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For ClassofTests: This is dummy class for testing purposes.

#include "ClassOfTests.h"

// Always returns true
bool test::ClassOfTests::testTrue()
{
	return true;
}

// Always returns false
bool test::ClassOfTests::testFalse()
{
	return false;
}

// Always returns true, but has exception at the start
bool test::ClassOfTests::testException()
{
	throw std::invalid_argument("Exception Thrown Test");
	return true;
}

bool test::ClassOfTests::testSecond()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return true;
}

bool test::ClassOfTests::testMilliSeconds()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	return true;
}

bool test::ClassOfTests::test10MilliSeconds()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return true;
}

bool test::ClassOfTests::test100MilliSeconds()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return true;
}