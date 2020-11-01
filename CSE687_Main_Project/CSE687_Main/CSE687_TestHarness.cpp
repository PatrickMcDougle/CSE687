// CSE687_TestHarness.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ILogData.h"
#include "LogData.h"
#include "LogMessage.h"
#include "LogMessageDecorator.h"
#include "LogStatusDecorator.h"
#include "LogTimestampDecorator.h"
#include "LoggerFactory.h"

#include "ITest.h"
#include "TestDriver.h"
#include "ClassOfTests.h"
#include <vector>
#include <list>

void TestingDevelopmentOfLogData(std::ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing LogData functionality >===== ||\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	logger::ILogData* logData1 = new logger::LogData(true, string1);
	logger::ILogData* logData2 = new logger::LogData(false, string2);
	logger::ILogData* logData3 = new logger::LogData(true, string3);
	logger::ILogData* logData4 = new logger::LogData(true, "Look At Me Mom!");

	out_stream << "1 | " << logData1->getDateTime() << " | " << logData1->isPassed() << " | " << logData1->getMessage() << endl;
	out_stream << "2 | " << logData2->getDateTime() << " | " << logData2->isPassed() << " | " << logData2->getMessage() << endl;
	out_stream << "3 | " << logData3->getDateTime() << " | " << logData3->isPassed() << " | " << logData3->getMessage() << endl;
	out_stream << "4 | " << logData4->getDateTime() << " | " << logData4->isPassed() << " | " << logData4->getMessage() << endl;

	out_stream << "1 | " << *logData1 << endl;
	out_stream << "2 | " << *logData2 << endl;
	out_stream << "3 | " << *logData3 << endl;
	out_stream << "4 | " << *logData4 << endl;
}

void TestingDevelopmentOfLogMessage(std::ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing Logging of Messages >===== ||\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	logger::ILogData* logData1 = new logger::LogData(true, string1);
	logger::ILogData* logData2 = new logger::LogData(false, string2);
	logger::ILogData* logData3 = new logger::LogData(true, string3);
	logger::ILogData* logData4 = new logger::LogData(true, "Look At Me Mom!");

	logger::LogMessage logMessage;
	logger::LogStatusDecorator logStatusDec(&logMessage);
	logger::LogMessageDecorator logMessageDec(&logStatusDec);
	logger::LogTimestampDecorator logTimestampDec(&logMessageDec);

	out_stream << "Decorate 1: " << logTimestampDec.logInfo(*logData1) << endl;
	out_stream << "Decorate 2: " << logTimestampDec.logInfo(*logData2) << endl;
	out_stream << "Decorate 3: " << logTimestampDec.logInfo(*logData3) << endl;
	out_stream << "Decorate 4: " << logTimestampDec.logInfo(*logData4) << endl;

	logger::LogMessage logMessage2;
	logger::LogTimestampDecorator logTimestampDec2(&logMessage2);
	logger::LogStatusDecorator logStatusDec2(&logTimestampDec2);
	logger::LogMessageDecorator logMessageDec2(&logStatusDec2);

	out_stream << "Decorate 1: " << logMessageDec2.logInfo(*logData1) << endl;
	out_stream << "Decorate 2: " << logMessageDec2.logInfo(*logData2) << endl;
	out_stream << "Decorate 3: " << logMessageDec2.logInfo(*logData3) << endl;
	out_stream << "Decorate 4: " << logMessageDec2.logInfo(*logData4) << endl;
}

void TestingDevelopmentOfLogFactory(std::ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Log Factory >===== ||\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	logger::LoggerFactory log_factory;
	logger::ILogger* logger = log_factory.create(1, 2, 3);

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

void TestingDevelopmentOfTestDriver(std::ostream& out_stream) {
	out_stream << "\n\n|| =====< Testing the Test Driver >===== ||\n";

	auto test_this = new test::TestDriver<test::ClassOfTests>();
	test::ClassOfTests class_of_tests;

	logger::LoggerFactory log_factory;

	test_this
		->loadClass(&class_of_tests)
		->loadMethod(&test::ClassOfTests::testTrue)
		->loadLogger(log_factory.create(30, 50, 10))
		->loadMessage("Testing if method returns true.")
		->test();

	out_stream << "Test 1 : " << test_this->testLogResults() << endl;

	test_this
		->loadMethod(&test::ClassOfTests::testFalse)
		->loadMessage("Testing if method returns false.")
		->test();

	out_stream << "Test 2 : " << test_this->testLogResults() << endl;

	test_this
		->loadMethod(&test::ClassOfTests::testException)
		->loadMessage("Testing if method throws an exception.")
		->test();

	out_stream << "Test 3 : " << test_this->testLogResults() << endl;

	//std::list<test::ITest> list_of_tests;
	test::TestDriver<test::ClassOfTests> first_test_class;

	//list_of_tests.push_back(first_test_class);

	delete test_this;
}

int main()
{
	std::ostream& out_stream = std::cout;

	out_stream << "|| =====< Start of Program >===== ||\n";

	TestingDevelopmentOfLogData(out_stream);

	TestingDevelopmentOfLogMessage(out_stream);

	TestingDevelopmentOfLogFactory(out_stream);

	TestingDevelopmentOfTestDriver(out_stream);

	out_stream << "\n\n|| =====< Done With Program >===== ||\n\n\n";
}