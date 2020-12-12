#pragma once
#ifndef __TEST_HARNESS_DLL_H__
#define __TEST_HARNESS_DLL_H__

// sytem include files first.
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <WinSock2.h>
#include <wtypes.h>

// program defined include files second.
#include "AddressIp4.h"
#include "BlockingQueue.h"
#include "DirectoryReader.h"
#include "DllClient.h"
#include "ITest.h"
#include "LoggerFactory.h"
#include "MotherController.h"
#include "SocketSystem.h"
#include "TestDllFunction.h"
#include "TestDriver.h"

// using list of things we will be using.
using std::ostream;
using std::cout;
using std::thread;
using std::vector;
using std::string;

// using list of things this program defined.
using messaging::AddressIp4;
using messaging::IAddressIp;
using messaging::SocketSystem;
using queue::BlockingQueue;
using test::ITest;
using test::TestDriver;
using test::TestDllFunction;
using threading::MotherController;

// type definitions for function pointers.
typedef bool (*funcTestbool)(void);
typedef string* (*funcListOfFunctions)(void);
typedef size_t(*funcNumberOfTests)(void);

/// <summary>
/// This class is the main class that will setup everything that will
/// test the tests in the DLL file(s).
/// </summary>
class TestHarnessDll
{
private:
	ILogger* logger = nullptr;
	int number_of_children_threads = 3;
	ostream& out_stream = std::cout;
	string dll_directory_location;

	/// <summary>
	/// The default constructor is private so no one tries to instatiate
	/// the class this way.  Use other constructor.
	/// </summary>
	TestHarnessDll() {};

public:
	/// <summary>
	/// The main constructor to setup everything properly.
	/// </summary>
	/// <param name="logger">a pointer to the logger to log stuff.</param>
	/// <param name="number_of_children">an integer of the number of threads that will be generated to test functions/methods.</param>
	/// <param name="output_stream">an output stream to print things out.</param>
	/// <param name="dll_directory">a string containing the location of the DLL(s) that need to be tested.</param>
	TestHarnessDll(
		ILogger* logger,
		int number_of_children = 3,
		ostream& output_stream = std::cout,
		const string& dll_directory = "../x64/Debug/"
	)
		:
		logger(logger),
		number_of_children_threads(number_of_children),
		out_stream(output_stream),
		dll_directory_location(dll_directory)
	{};
	~TestHarnessDll();

	/// <summary>
	/// This method is the one that runs everything.
	/// </summary>
	void Run();
};

#endif // !__TEST_HARNESS_DLL_H__