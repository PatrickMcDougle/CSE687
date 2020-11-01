#include "LoggerFactory.h"

logger::ILogger* logger::LoggerFactory::create(int test_pass_result_order, int test_message_order, int test_timestamp_order)
{
	int max_value = 0;
	
	max_value = (test_pass_result_order > test_message_order) ? test_pass_result_order : test_message_order;
	max_value = (max_value > test_timestamp_order) ? max_value : test_timestamp_order;

	logger::ILogComponent* last_component = new logger::LogMessage();

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


	ILogger* logger = new MyLogger();

	logger->setLogComponent(last_component);

	return logger;
}