// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Contains the main function

#include <array>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "AddressIp4.h"
#include "BlockingQueue.h"
#include "ChildTester.h"
//#include "ClassOfTests.h" // not good at this time.
#include "Communications.h"
#include "IAddressIp.h"
#include "ILogData.h"
#include "ITest.h"
#include "LogData.h"
#include "LoggerFactory.h"
#include "LogMessage.h"
#include "LogMessageDecorator.h"
#include "LogStatusDecorator.h"
#include "LogTimestampDecorator.h"
#include "Message.h"
#include "MotherController.h"
#include "SocketSystem.h"
#include "TestDriver.h"

// third party dlls.
#include "DllForTests.h"

using namespace logger;
using namespace test;
using std::string;
using std::ostream;
using std::cout;

// Method creating a 4 Log Data objects and test functionality
void TestingDevelopmentOfLogData(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing LogData functionality >===== ||\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	ILogData* logData1 = new LogData(true, string1);
	ILogData* logData2 = new LogData(false, string2);
	ILogData* logData3 = new LogData(true, string3);
	ILogData* logData4 = new LogData(true, "Look At Me Mom!");

	out_stream << "1 | " << logData1->getDateTime() << " | " << logData1->isPassed() << " | " << logData1->getMessage() << endl;
	out_stream << "2 | " << logData2->getDateTime() << " | " << logData2->isPassed() << " | " << logData2->getMessage() << endl;
	out_stream << "3 | " << logData3->getDateTime() << " | " << logData3->isPassed() << " | " << logData3->getMessage() << endl;
	out_stream << "4 | " << logData4->getDateTime() << " | " << logData4->isPassed() << " | " << logData4->getMessage() << endl;

	out_stream << "1 | " << *logData1 << endl;
	out_stream << "2 | " << *logData2 << endl;
	out_stream << "3 | " << *logData3 << endl;
	out_stream << "4 | " << *logData4 << endl;
}

// Method creating a 4 Log Decorator objects and test functionality
void TestingDevelopmentOfLogMessage(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing Logging of Messages >===== ||\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	ILogData* logData1 = new LogData(true, string1);
	ILogData* logData2 = new LogData(false, string2);
	ILogData* logData3 = new LogData(true, string3);
	ILogData* logData4 = new LogData(true, "Look At Me Mom!");

	LogMessage logMessage;
	LogStatusDecorator logStatusDec(&logMessage);
	LogMessageDecorator logMessageDec(&logStatusDec);
	LogTimestampDecorator logTimestampDec(&logMessageDec);

	out_stream << "Decorate 1: " << logTimestampDec.logInfo(*logData1) << endl;
	out_stream << "Decorate 2: " << logTimestampDec.logInfo(*logData2) << endl;
	out_stream << "Decorate 3: " << logTimestampDec.logInfo(*logData3) << endl;
	out_stream << "Decorate 4: " << logTimestampDec.logInfo(*logData4) << endl;

	LogMessage logMessage2;
	LogTimestampDecorator logTimestampDec2(&logMessage2);
	LogStatusDecorator logStatusDec2(&logTimestampDec2);
	LogMessageDecorator logMessageDec2(&logStatusDec2);

	out_stream << "Decorate 1: " << logMessageDec2.logInfo(*logData1) << endl;
	out_stream << "Decorate 2: " << logMessageDec2.logInfo(*logData2) << endl;
	out_stream << "Decorate 3: " << logMessageDec2.logInfo(*logData3) << endl;
	out_stream << "Decorate 4: " << logMessageDec2.logInfo(*logData4) << endl;
}

// Method creating a 6 Log Factory objects and test functionality
void TestingDevelopmentOfLogFactory(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Log Factory >===== ||\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	LoggerFactory log_factory;
	ILogger* logger = log_factory.create(1, 2, 3);

	out_stream << "LogFactory 1: " << logger->logInfo(true, string1) << endl;
	out_stream << "LogFactory 1: " << logger->logInfo(false, string2) << endl;
	out_stream << "LogFactory 1: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(2, 1, 3);

	out_stream << "LogFactory 2: " << logger->logInfo(true, string1) << endl;
	out_stream << "LogFactory 2: " << logger->logInfo(false, string2) << endl;
	out_stream << "LogFactory 2: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(20, 30, 10);

	out_stream << "LogFactory 3: " << logger->logInfo(true, string1) << endl;
	out_stream << "LogFactory 3: " << logger->logInfo(false, string2) << endl;
	out_stream << "LogFactory 3: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create();

	out_stream << "LogFactory 4: " << logger->logInfo(true, string1) << endl;
	out_stream << "LogFactory 4: " << logger->logInfo(false, string2) << endl;
	out_stream << "LogFactory 4: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(2, 1);

	out_stream << "LogFactory 5: " << logger->logInfo(true, string1) << endl;
	out_stream << "LogFactory 5: " << logger->logInfo(false, string2) << endl;
	out_stream << "LogFactory 5: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(2, 0, 1);

	out_stream << "LogFactory 6: " << logger->logInfo(true, string1) << endl;
	out_stream << "LogFactory 6: " << logger->logInfo(false, string2) << endl;
	out_stream << "LogFactory 6: " << logger->logInfo(true, string3) << endl;
}

// Method creating a 3 Test Driver objects and test functionality
//void TestingDevelopmentOfTestDriver(ostream& out_stream) {
//	out_stream << "\n\n|| =====< Testing the Test Driver >===== ||\n";
//
//	auto test_this = new TestDriver<ClassOfTests>();
//
//	ClassOfTests class_of_tests;
//
//	LoggerFactory log_factory;
//
//	test_this
//		->loadClass(&class_of_tests)
//		->loadMethod(&ClassOfTests::testTrue)
//		->loadLogger(log_factory.create(30, 50, 10))
//		->loadMessage("Testing if method returns true.")
//		->test();
//
//	out_stream << "Test 1 : " << test_this->testLogResults() << endl;
//
//	test_this = new TestDriver<ClassOfTests>();
//	test_this
//		->loadClass(&class_of_tests)
//		->loadMethod(&ClassOfTests::testFalse)
//		->loadLogger(log_factory.create(30, 50, 10))
//		->loadMessage("Testing if method returns false.")
//		->test();
//
//	out_stream << "Test 2 : " << test_this->testLogResults() << endl;
//
//	test_this
//		->loadMethod(&ClassOfTests::testException)
//		->loadMessage("Testing if method throws an exception.")
//		->test();
//
//	out_stream << "Test 3 : " << test_this->testLogResults() << endl;
//
//	TestDriver<ClassOfTests> first_test_class;
//
//	//std::list<ITest> list_of_tests;             // setup of list of ITests
//	//list_of_tests.push_back(first_test_class);  // add first test class to the list.
//
//	delete test_this;
//}

void TestingAddressIp4(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Address IP4 class >===== ||\n";

	messaging::AddressIp4 ip1;

	ip1.setPort(1337);

	out_stream << "Port [1337] : " << ip1.getPort() << endl;

	ip1.setAddress(1, 2, 3, 4);

	out_stream << "Address     [1.2.3.4]      : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [1.2.3.4:1337] : " << ip1.getAddressAndPort() << endl;

	ip1.setAddress(11, 22, 33, 44);

	out_stream << "Address     [11.22.33.44]      : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [11.22.33.44:1337] : " << ip1.getAddressAndPort() << endl;

	ip1.setAddress(111, 122, 133, 144);

	out_stream << "Address     [111.122.133.144]      : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [111.122.133.144:1337] : " << ip1.getAddressAndPort() << endl;

	ip1.setAddress("9.8.7.6");
	ip1.setPort(54321);

	out_stream << "Address     [9.8.7.6]       : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [9.8.7.6:54321] : " << ip1.getAddressAndPort() << endl;

	ip1.setAddress("91.82.73.64");
	ip1.setPort(53210);

	out_stream << "Address     [91.82.73.64]       : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [91.82.73.64:53210] : " << ip1.getAddressAndPort() << endl;

	ip1.setAddress("191.182.173.164");
	ip1.setPort(52100);

	out_stream << "Address     [191.182.173.164]       : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [191.182.173.164:52100] : " << ip1.getAddressAndPort() << endl;

	ip1.set("5.6.7.8:9");

	out_stream << "Address     [5.6.7.8]   : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [5.6.7.8:9] : " << ip1.getAddressAndPort() << endl;

	ip1.set("55.65.75.85:955");

	out_stream << "Address     [55.65.75.85]     : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [55.65.75.85:955] : " << ip1.getAddressAndPort() << endl;

	ip1.set("155.165.175.185:11955");

	out_stream << "Address     [155.165.175.185]       : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [155.165.175.185:11955] : " << ip1.getAddressAndPort() << endl;

	ip1.set(123, 234, 134, 245, 14725);

	out_stream << "Address     [123.234.134.245]       : " << ip1.getAddress() << endl;
	out_stream << "AddressPort [123.234.134.245:14725] : " << ip1.getAddressAndPort() << endl;
}

void TestingMessage(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Message class >===== ||\n";

	messaging::AddressIp4 source;
	source.setAddress(127, 0, 0, 1);
	source.setPort(12345);

	messaging::AddressIp4 destination;
	destination.setAddress(127, 0, 0, 1);
	destination.setPort(15432);

	messaging::Message the_message(&source, &destination);

	the_message.setAuthor("Mother");
	the_message.setType("DoTest");
	the_message.setMessage("<runtest><location>2</location></runtest>");

	out_stream << "The Message from Mother to Child " << endl
		<< the_message.writeMessage() << endl;

	queue::BlockingQueue<int> bq;

	bq.enqueue(1);
}

/// <summary>
/// This is the best method, I mean function in the world.
/// </summary>
/// <param name="out_stream">Need an out.</param>
void TestingChildThreads(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Children Threads - START >===== ||\n";
	out_stream << "Number of Hardware Threads:" << thread::hardware_concurrency() << "\n";

	// TODO
	LoggerFactory log_factory;
	ILogger* logger = log_factory.create(30, 50, 10);

	// socket system will setup the sockets and tears them down when the
	// class is destroyed.
	messaging::SocketSystem socket_system_setup;

	BlockingQueue<ITest*> blocking_queue_of_test_drivers;

	//ClassOfTests class_of_tests;

	int number_of_children_threads = thread::hardware_concurrency() / 6;

	if (number_of_children_threads < 3) {
		number_of_children_threads *= 3;
	}
	if (number_of_children_threads == 0) {
		number_of_children_threads = 3;
	}

	//number_of_children_threads = 1;

	out_stream << "Number of children:" << number_of_children_threads << "\n";

	for (int i = 0; i < number_of_children_threads * 1; ++i) {
		//auto test_this = new TestDriver<ClassOfTests>();

		//test_this
		//	->loadClass(&class_of_tests)
		//	->loadMethod(&ClassOfTests::testTrue)
		//	->loadLogger(logger)
		//	->loadMessage("Testing if method returns true.");

		//blocking_queue_of_test_drivers.enqueue(test_this);

		//test_this = new TestDriver<ClassOfTests>();
		//test_this
		//	->loadClass(&class_of_tests)
		//	->loadMethod(&ClassOfTests::testFalse)
		//	->loadLogger(logger)
		//	->loadMessage("Testing if method returns false.");

		//blocking_queue_of_test_drivers.enqueue(test_this);

		//test_this = new TestDriver<ClassOfTests>();
		//test_this
		//	->loadClass(&class_of_tests)
		//	->loadMethod(&ClassOfTests::testException)
		//	->loadLogger(logger)
		//	->loadMessage("Testing if method returns an exception.");

		//blocking_queue_of_test_drivers.enqueue(test_this);
	}

	out_stream << "Number of tests to run:" << blocking_queue_of_test_drivers.size() << "\n";

	messaging::AddressIp4 address_mother;

	address_mother.set(127, 0, 0, 1, 51000);

	vector<messaging::IAddressIp*> children_addresses;

	int child_port = 52010;
	for (int i = 0; i < number_of_children_threads; ++i) {
		messaging::IAddressIp* address_child = new messaging::AddressIp4();

		address_child->set(127, 0, 0, 1, child_port);

		children_addresses.push_back(address_child);

		child_port += 10;
	}

	threading::MotherController mother(&address_mother, children_addresses, blocking_queue_of_test_drivers, "Mother");
	mother.setup(logger);

	//mother.run(); // when threads don't work, we can just call the run method.

	std::thread mother_thread(&threading::MotherController::run, std::ref(mother));

	// wait here until the mother_thread is done processing information.
	mother_thread.join(); // must join with thread.

	logger = nullptr;
	delete logger;

	out_stream << "\n\n|| =====< Testing the Children Threads - DONE >===== ||\n";
}

//void TestingUsingDlls(ostream& out_stream) {
//	// Initialize a Fibonacci relation sequence.
//	fibonacci_init(1, 1);
//	// Write out the sequence values until overflow.
//	do {
//		out_stream << fibonacci_index() << ": " << fibonacci_current() << std::endl;
//	} while (fibonacci_next());
//	// Report count of values written before overflow.
//	out_stream << fibonacci_index() + 1 << " Fibonacci sequence values fit in an " << "unsigned 64-bit integer." << std::endl;
//}

typedef bool (*funcTestbool)(void);

typedef std::string* (*funcListOfFunctions)(void);
typedef size_t(*funcNumberOfTests)(void);

void TestingDllLoading(ostream& out_stream) {
	HINSTANCE hDLL;
	funcListOfFunctions list_of_functions;
	funcNumberOfTests number_of_tests;
	funcTestbool test_bool;

	const wchar_t* libName = L"ClassOfTests";

	hDLL = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL

	if (hDLL != NULL) {
		list_of_functions = (funcListOfFunctions)GetProcAddress(hDLL, "ListOfFunctions");
		number_of_tests = (funcNumberOfTests)GetProcAddress(hDLL, "NumberOfTests");

		if (list_of_functions != NULL) {
			out_stream << "Loaded list_of_functions correctly." << std::endl;
		}
		else {
			out_stream << "Did not load list_of_functions correctly." << std::endl;
		}

		if (number_of_tests != NULL) {
			out_stream << "Loaded number_of_tests correctly." << std::endl;
		}
		else {
			out_stream << "Did not load number_of_tests correctly." << std::endl;
		}

		std::string* list_functions = list_of_functions();
		size_t number_tests = number_of_tests();

		for (size_t i = 0; i < number_tests; i++)
		{
			out_stream << "Function: " << list_functions[i] << std::endl;
			LPCSTR function_name = list_functions[i].c_str();

			test_bool = (funcTestbool)GetProcAddress(hDLL, function_name);

			if (test_bool != NULL) {
				out_stream
					<< "Loaded test_bool["
					<< list_functions[i]
					<< "] correctly."
					<< std::endl;
			}
			else {
				out_stream
					<< "Did not load test_bool["
					<< list_functions[i]
					<< "] correctly."
					<< std::endl;
			}

			out_stream
				<< "Results for test "
				<< list_functions[i]
				<< " = "
				<< test_bool()
				<< "."
				<< std::endl;
		}

		//{ // pretend to be in child.
		//		bool theResulsts =	test_bool();
		//}

		//out_stream << "Test Results: " << iTest->test() << " : " << iTest->() << std::endl;
		//// Report count of values written before overflow.
		//out_stream << Indx() + 1 << " Fibonacci sequence values fit in an " << "unsigned 64-bit integer." << std::endl;

		FreeLibrary(hDLL);
	}
	else {
		out_stream << "Library load failed!" << std::endl;
	}
}

// Main Function
int main()
{
	// Initialize out_stream
	ostream& out_stream = cout;

	// Alert User of Program Start
	out_stream << "|| =====< Start of Program >===== ||\n";

	//// Run Method Testing the Log Data Classes
	//TestingDevelopmentOfLogData(out_stream); // don't need to run at this time.

	//// Run Method Tesing the Log Message Classes
	//TestingDevelopmentOfLogMessage(out_stream); // don't need to run at this time.

	//// Run Method Testing the Log Factory
	//TestingDevelopmentOfLogFactory(out_stream); // don't need to run at this time.

	//// Run Method Testing the Test Driver Classes
	//TestingDevelopmentOfTestDriver(out_stream); // don't need to run at this time.

	//TestingAddressIp4(out_stream); // don't need to run at this time.
	//TestingMessage(out_stream); // don't need to run at this time.

	//TestingChildThreads(out_stream);

	//TestingUsingDlls(out_stream);

	TestingDllLoading(out_stream);

	// Alert User of Program End
	out_stream << "\n\n|| =====< Done With Program >===== ||\n\n\n";
}