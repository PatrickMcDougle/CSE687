// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: Contains the main function

#include <iostream>
#include <list>
#include <vector>

#include "ClassOfTests.h"
#include "ILogData.h"
#include "ITest.h"
#include "LogData.h"
#include "LoggerFactory.h"
#include "LogMessage.h"
#include "LogMessageDecorator.h"
#include "LogStatusDecorator.h"
#include "LogTimestampDecorator.h"
#include "TestDriver.h"

#include "AddressIp4.h"
#include "Message.h"
#include "BlockingQueue.h"
#include "Communications.h"
#include "ChildTester.h"
#include "SocketSystem.h"

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
void TestingDevelopmentOfTestDriver(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Test Driver >===== ||\n";

	auto test_this = new TestDriver<ClassOfTests>();

	ClassOfTests class_of_tests;

	LoggerFactory log_factory;

	test_this
		->loadClass(&class_of_tests)
		->loadMethod(&ClassOfTests::testTrue)
		->loadLogger(log_factory.create(30, 50, 10))
		->loadMessage("Testing if method returns true.")
		->test();

	out_stream << "Test 1 : " << test_this->testLogResults() << endl;

	test_this = new TestDriver<ClassOfTests>();
	test_this
		->loadClass(&class_of_tests)
		->loadMethod(&ClassOfTests::testFalse)
		->loadLogger(log_factory.create(30, 50, 10))
		->loadMessage("Testing if method returns false.")
		->test();

	out_stream << "Test 2 : " << test_this->testLogResults() << endl;

	test_this
		->loadMethod(&ClassOfTests::testException)
		->loadMessage("Testing if method throws an exception.")
		->test();

	out_stream << "Test 3 : " << test_this->testLogResults() << endl;

	TestDriver<ClassOfTests> first_test_class;

	//std::list<ITest> list_of_tests;             // setup of list of ITests
	//list_of_tests.push_back(first_test_class);  // add first test class to the list.

	delete test_this;
}

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

	messaging::Message the_message;

	messaging::AddressIp4 source;
	source.setAddress(127, 0, 0, 1);
	source.setPort(12345);
	the_message.setSource(source);

	messaging::AddressIp4 destination;
	destination.setAddress(127, 0, 0, 1);
	destination.setPort(15432);
	the_message.setDestination(destination);

	the_message.setAuthor("Mother");
	the_message.setType("DoTest");
	the_message.setMessage("<runtest><location>2</location></runtest>");

	out_stream << "The Message from Mother to Child " << endl
		<< the_message.writeMessage() << endl;

	queue::BlockingQueue<int> bq;

	bq.enqueue(1);
}

void TestingChildThreads(ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Children Threads >===== ||\n";

	// socket system will setup the sockets and tears them down when the
	// class is destroyed.
	messaging::SocketSystem socket_system_setup;

	messaging::AddressIp4 mother_address;
	messaging::AddressIp4 child1_address;
	messaging::AddressIp4 child2_address;

	mother_address.set(127, 0, 0, 1, 12000);
	child1_address.set(127, 0, 0, 1, 12010);
	child2_address.set(127, 0, 0, 1, 12020);

	threading::ChildTester child1_tester(child1_address, mother_address, "Boy");
	threading::ChildTester child2_tester(child2_address, mother_address, "Girl");

	threading::Communications mother_communications(mother_address, "Mother");
	mother_communications.start();

	std::thread child1_thread(&threading::ChildTester::run, child1_tester);
	child1_thread.detach();

	std::thread child2_thread(&threading::ChildTester::run, child2_tester);
	child2_thread.detach();

	Message message;
	Message reply;
	size_t count = 0;

	while (true) {
		message = mother_communications.getMessage();
		out_stream
			<< std::endl
			<< " =====< "
			<< mother_communications.getName()
			<< " received message: "
			<< message.getAuthor()
			<< " >=====";

		reply.setDestination(message.getSource());
		reply.setSource(mother_address);
		reply.setAuthor("Mother");
		reply.setType("TEST");
		reply.setMessage("Another test to do");

		mother_communications.sendMessage(reply);

		if (message.getType() == "STOP") {
			break;
		}
	}

	mother_communications.stop();
}

// Main Function
int main()
{
	// Initialize out_stream
	ostream& out_stream = cout;

	// Alert User of Program Start
	out_stream << "|| =====< Start of Program >===== ||\n";

	//// Run Method Testing the Log Data Classes
	//TestingDevelopmentOfLogData(out_stream);

	//// Run Method Tesing the Log Message Classes
	//TestingDevelopmentOfLogMessage(out_stream);

	//// Run Method Testing the Log Factory
	//TestingDevelopmentOfLogFactory(out_stream);

	//// Run Method Testing the Test Driver Classes
	//TestingDevelopmentOfTestDriver(out_stream);

	//TestingAddressIp4(out_stream);
	//TestingMessage(out_stream);

	TestingChildThreads(out_stream);

	// Alert User of Program End
	out_stream << "\n\n|| =====< Done With Program >===== ||\n\n\n";
}