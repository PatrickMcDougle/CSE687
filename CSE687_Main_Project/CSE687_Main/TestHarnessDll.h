#pragma once
#ifndef __TEST_HARNESS_DLL_H__
#define __TEST_HARNESS_DLL_H__

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <WinSock2.h>
#include <wtypes.h>

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

using std::ostream;
using std::cout;
using std::thread;
using std::vector;
using std::string;

using messaging::AddressIp4;
using messaging::IAddressIp;
using messaging::SocketSystem;
using queue::BlockingQueue;
using test::ITest;
using test::TestDriver;
using test::TestDllFunction;
using threading::MotherController;

typedef bool (*funcTestbool)(void);
typedef string* (*funcListOfFunctions)(void);
typedef size_t(*funcNumberOfTests)(void);

class TestHarnessDll
{
private:
	ostream& out_stream;
	string dll_directory_location;
	int number_of_children_threads;
	ILogger* logger;

public:
	TestHarnessDll(
		ILogger* logger,
		int number_of_children = 3,
		ostream& output_stream = std::cout,
		const string& dll_directory = "../x64/Debug/"
	)
		:
		out_stream(output_stream),
		dll_directory_location(dll_directory),
		number_of_children_threads(number_of_children),
		logger(logger)
	{};
	~TestHarnessDll();

	void Run();
};

#endif // !__TEST_HARNESS_DLL_H__