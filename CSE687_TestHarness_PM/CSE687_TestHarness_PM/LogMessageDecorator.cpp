#include "LogMessageDecorator.h"

logger::LogMessageDecorator::LogMessageDecorator(ILogComponent* component) : ALogDecorator(component)
{
}

string logger::LogMessageDecorator::logInfo(data::ILogData& logData) const
{
	string other = ALogDecorator::logInfo(logData);

	if (other.length() > 1) {
		other.append(" | ");
	}

	other.append(logData.getMessage());

	return other;
}
