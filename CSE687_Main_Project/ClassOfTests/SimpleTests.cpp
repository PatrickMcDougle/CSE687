// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For ClassofTests: This is dummy class for testing purposes.

#include "SimpleTests.h"

using namespace test;

// Always returns true
bool SimpleTests::testTrue()
{
	return true;
}

// Always returns false
bool SimpleTests::testFalse()
{
	return false;
}

// Always returns true, but has exception at the start
bool SimpleTests::testException()
{
	throw std::invalid_argument("Exception Thrown Test");
	return true;
}