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


int main()
{
	cout << "|| =====< Start of Program >===== ||\n";
	cout << "\n\n|| =====< Testing LogData functionality >===== ||\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	logger::ILogData* logData1 = new logger::LogData(true, string1);
	logger::ILogData* logData2 = new logger::LogData(false, string2);
	logger::ILogData* logData3 = new logger::LogData(true, string3);
	logger::ILogData* logData4 = new logger::LogData(true, "Look At Me Mom!");

	cout << "1 | " << logData1->getDateTime() << " | " << logData1->isPassed() << " | " << logData1->getMessage() << endl;
	cout << "2 | " << logData2->getDateTime() << " | " << logData2->isPassed() << " | " << logData2->getMessage() << endl;
	cout << "3 | " << logData3->getDateTime() << " | " << logData3->isPassed() << " | " << logData3->getMessage() << endl;
	cout << "4 | " << logData4->getDateTime() << " | " << logData4->isPassed() << " | " << logData4->getMessage() << endl;

	cout << "1 | " << *logData1 << endl;
	cout << "2 | " << *logData2 << endl;
	cout << "3 | " << *logData3 << endl;
	cout << "4 | " << *logData4 << endl;

	// ===== LOG MESSAGE STUFF ===== //
	cout << "\n\n|| =====< Testing Logging of Messages >===== ||\n";

	logger::LogMessage logMessage;
	logger::LogStatusDecorator logStatusDec(&logMessage);
	logger::LogMessageDecorator logMessageDec(&logStatusDec);
	logger::LogTimestampDecorator logTimestampDec(&logMessageDec);

	cout << "Decorate 1: " << logTimestampDec.logInfo(*logData1) << endl;
	cout << "Decorate 2: " << logTimestampDec.logInfo(*logData2) << endl;
	cout << "Decorate 3: " << logTimestampDec.logInfo(*logData3) << endl;
	cout << "Decorate 4: " << logTimestampDec.logInfo(*logData4) << endl;


	logger::LogMessage logMessage2;
	logger::LogTimestampDecorator logTimestampDec2(&logMessage2);
	logger::LogStatusDecorator logStatusDec2(&logTimestampDec2);
	logger::LogMessageDecorator logMessageDec2(&logStatusDec2);

	cout << "Decorate 1: " << logMessageDec2.logInfo(*logData1) << endl;
	cout << "Decorate 2: " << logMessageDec2.logInfo(*logData2) << endl;
	cout << "Decorate 3: " << logMessageDec2.logInfo(*logData3) << endl;
	cout << "Decorate 4: " << logMessageDec2.logInfo(*logData4) << endl;

	cout << "\n\n|| =====< Testing the Log Factory >===== ||\n";

	logger::LoggerFactory log_factory;
	logger::ILogger* logger = log_factory.create(1, 2, 3);

	cout << "LogFactory 1: " << logger->logInfo(true, string1) << endl;
	cout << "LogFactory 1: " << logger->logInfo(false, string2) << endl;
	cout << "LogFactory 1: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(2, 1, 3);

	cout << "LogFactory 1: " << logger->logInfo(true, string1) << endl;
	cout << "LogFactory 1: " << logger->logInfo(false, string2) << endl;
	cout << "LogFactory 1: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(20, 30, 10);

	cout << "LogFactory 1: " << logger->logInfo(true, string1) << endl;
	cout << "LogFactory 1: " << logger->logInfo(false, string2) << endl;
	cout << "LogFactory 1: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create();

	cout << "LogFactory 1: " << logger->logInfo(true, string1) << endl;
	cout << "LogFactory 1: " << logger->logInfo(false, string2) << endl;
	cout << "LogFactory 1: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(2, 1);

	cout << "LogFactory 1: " << logger->logInfo(true, string1) << endl;
	cout << "LogFactory 1: " << logger->logInfo(false, string2) << endl;
	cout << "LogFactory 1: " << logger->logInfo(true, string3) << endl;

	logger = log_factory.create(2, 0, 1);

	cout << "LogFactory 1: " << logger->logInfo(true, string1) << endl;
	cout << "LogFactory 1: " << logger->logInfo(false, string2) << endl;
	cout << "LogFactory 1: " << logger->logInfo(true, string3) << endl;

	cout << "\n\n|| =====< Testing the Test Driver >===== ||\n";

	//test::ITest* itest = new test::TestDriver<test::ClassOfTests>();

	test::TestDriver<test::ClassOfTests>* test_this = new test::TestDriver<test::ClassOfTests>();
	test::ClassOfTests class_of_tests;

	test_this->loadTest(&class_of_tests, &test::ClassOfTests::testTrue);

	cout << "Load True Test and Run : " << test_this->runTest() << endl;

	test_this->loadTest(&class_of_tests, &test::ClassOfTests::testFalse);

	cout << "Load False Test and Run : " << test_this->runTest() << endl;

	test_this->loadTest(&class_of_tests, &test::ClassOfTests::testException);

	cout << "Load Exception Test and Run : " << test_this->runTest() << endl;



	cout << "\n\n|| =====< Done With Program >===== ||\n\n\n";
	//cout << "|| =====< >===== ||\n"; // just easy way to copy and past.
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file