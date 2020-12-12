#include "pch.h"
#include "TestLogger.h"

static const size_t number_of_test = 7;

std::string* ListOfFunctions() {
	auto listOfFunctions = new std::string[number_of_test];
	listOfFunctions[0] = "Test_LogData_isPassed_true";
	listOfFunctions[1] = "Test_LogData_isPassed_false";
	listOfFunctions[2] = "Test_LogData_getDateTime";
	listOfFunctions[3] = "Test_LogData_getMessage";
	listOfFunctions[4] = "Test_LoggerFactory_create";
	listOfFunctions[5] = "Test_LogMessage_logInfo";
	listOfFunctions[6] = "Test_MyLogger_logInfo";
	return listOfFunctions;
}

size_t NumberOfTests() { return number_of_test; }

bool Test_LogData_isPassed_true() {
	logger::LogData logData(true, "Test isPassed true");
	return logData.isPassed();
}
bool Test_LogData_isPassed_false() {
	logger::LogData logData(false, "Test isPassed false");
	return !logData.isPassed();
}
bool Test_LogData_getDateTime() {
	logger::LogData logData(true, "Testing DateTime");
	return (logData.getDateTime().length() > 10) &&
		(logData.getDateTime().length() > 10);
}
bool Test_LogData_getMessage() {
	std::string message = "Testing getMessage";
	logger::LogData logData(true, message);
	return (logData.getMessage() == message);
}

bool Test_LoggerFactory_create() {
	logger::LoggerFactory loggerFactory;
	logger::ILogger* logger = loggerFactory.create(10, 20, 30);

	bool was_created = logger != nullptr;

	delete logger;
	logger = nullptr;

	return was_created;
}

bool Test_LogMessage_logInfo() {
	logger::LogMessage logMessage;
	logger::LogData logData(true, "Testing LogMessage");
	return logMessage.logInfo(logData).empty();
}

bool Test_MyLogger_logInfo() {
	logger::MyLogger myMessage;
	logger::ILogComponent* logComponent = new LogMessage();

	myMessage.setLogComponent(logComponent);

	bool was_valid = !myMessage.logInfo(true, "Testing myMessage").empty();

	delete logComponent;
	logComponent = nullptr;

	return was_valid;
}