#include "MyLogger.h"

logger::MyLogger::MyLogger()
{
}

string logger::MyLogger::logInfo(bool test_results, const string& test_message)
{
	if (this->log_component_ == nullptr) {
		return string();
	}

	logger::ILogData* log_data = new logger::LogData(test_results, test_message);

	return this->log_component_->logInfo(*log_data);
}

void logger::MyLogger::setLogComponent(ILogComponent* log_component) 
{
	this->log_component_ = log_component;
}