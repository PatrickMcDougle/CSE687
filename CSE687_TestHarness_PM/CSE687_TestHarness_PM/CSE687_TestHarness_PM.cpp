// CSE687_TestHarness_PM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ILogData.h"
#include "LogData.h"
#include "LogMessage.h"
#include "LogMessageDecorator.h"
#include "LogStatusDecorator.h"
#include "LogTimestampDecorator.h"


int main()
{
	cout << "Hello World!\n";

	string string1("message one");
	string string2("message two");
	string string3("message three");

	logger::data::ILogData* logData1 = new logger::data::LogData(true, string1);
	logger::data::ILogData* logData2 = new logger::data::LogData(false, string2);
	logger::data::ILogData* logData3 = new logger::data::LogData(true, string3);
	logger::data::ILogData* logData4 = new logger::data::LogData(true, "Look At Me Mom!");

	cout << "1 | " << logData1->getDateTime() << " | " << logData1->isPassed() << " | " << logData1->getMessage() << endl;
	cout << "2 | " << logData2->getDateTime() << " | " << logData2->isPassed() << " | " << logData2->getMessage() << endl;
	cout << "3 | " << logData3->getDateTime() << " | " << logData3->isPassed() << " | " << logData3->getMessage() << endl;
	cout << "4 | " << logData4->getDateTime() << " | " << logData4->isPassed() << " | " << logData4->getMessage() << endl;

	cout << "1 | " << *logData1 << endl;
	cout << "2 | " << *logData2 << endl;
	cout << "3 | " << *logData3 << endl;
	cout << "4 | " << *logData4 << endl;

	// ===== LOG MESSAGE STUFF ===== //

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