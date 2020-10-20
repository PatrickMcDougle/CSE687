#include "LogTimestampDecorator.h"

logger::LogTimestampDecorator::LogTimestampDecorator(ILogComponent* component) : ALogDecorator(component)
{
}

string logger::LogTimestampDecorator::logInfo(data::ILogData& logData) const
{
	string other = ALogDecorator::logInfo(logData);

	if (other.length() > 1) {
		other.append(" | ");
	}

	other.append(logData.getDateTime());

	return other;
}
