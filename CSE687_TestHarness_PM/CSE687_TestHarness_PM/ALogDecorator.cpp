#include "ALogDecorator.h"

logger::ALogDecorator::ALogDecorator(ILogComponent* component) : log_component_(component)
{
}

string logger::ALogDecorator::logInfo(data::ILogData& logData) const
{
	return this->log_component_->logInfo(logData);
}
