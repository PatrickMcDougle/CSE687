// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For LoggerFactory

#include "LoggerFactory.h"

using namespace logger;

// Create a new ILogger
ILogger* LoggerFactory::create(int test_pass_result_order, int test_message_order, int test_timestamp_order)
{
    // Initialize max_value
	int max_value = 0;
	
    // Determines which parameter has highest value
	max_value = (test_pass_result_order > test_message_order) ? test_pass_result_order : test_message_order;
	max_value = (max_value > test_timestamp_order) ? max_value : test_timestamp_order;

    // New Log Component
	ILogComponent* last_component = new LogMessage();

    // Puts each of the log elements into the last_component
	for (int i = 1; i <= max_value; ++i) {
		if (i == test_pass_result_order) {
			last_component = LoadDecorator<LogStatusDecorator>(last_component);
		}
		if (i == test_message_order) {
			last_component = LoadDecorator<LogMessageDecorator>(last_component);
		}
		if (i == test_timestamp_order) {
			last_component = LoadDecorator<LogTimestampDecorator>(last_component);
		}
	}

    // Cretes new logger
	ILogger* logger = new MyLogger();

    // Add last component to logger
	logger->setLogComponent(last_component);

    // return logger
	return logger;
}