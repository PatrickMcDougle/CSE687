#include "LogStatusDecorator.h"

logger::LogStatusDecorator::LogStatusDecorator(ILogComponent* component) : ALogDecorator(component)
{
}

string logger::LogStatusDecorator::logInfo(logger::ILogData& logData) const
{
	string other = ALogDecorator::logInfo(logData);

	if (other.length() > 1) {
		other.append(" | ");
	}

	other.append(logData.isPassed() ? "TRUE " : "FALSE");

	return other;
}
