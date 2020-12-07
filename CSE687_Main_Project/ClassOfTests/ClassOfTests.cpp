// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For ClassofTests: This is dummy class for testing purposes.

#include "ClassOfTests.h"

static const size_t number_of_test = 2;

std::string* ListOfFunctions() {
	auto listOfFunctions = new std::string[number_of_test];
	listOfFunctions[0] = "GetTestTrue";
	listOfFunctions[1] = "GetTestFalse";
	return listOfFunctions;
}

size_t NumberOfTests() { return number_of_test; }

bool GetTestTrue() {
	test::SimpleTests simpleTest;
	return simpleTest.testTrue();
}

bool GetTestFalse() {
	test::SimpleTests simpleTest;
	return simpleTest.testFalse();
}