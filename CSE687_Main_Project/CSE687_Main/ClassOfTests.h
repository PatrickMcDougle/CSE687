// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Header File For ClassofTests: This is dummy class for testing purposes.

#pragma once
#ifndef __I_CLASS_OF_TESTS_H__
#define __I_CLASS_OF_TESTS_H__

#include <exception>

// Namespace for Test
namespace test {
    // Class for ClassofTests
	class ClassOfTests
	{
	public:
		~ClassOfTests() {} // Destructor
		bool testTrue(); // Method to always return true
		bool testFalse(); // Method to always return false
		bool testException(); // Method to always return true but has exception first
	};
}

#endif // !__I_CLASS_OF_TESTS_H__
