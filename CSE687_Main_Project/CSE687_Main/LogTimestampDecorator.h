#pragma once

#ifndef __LOG_TIMESTAMP_DECORATOR_H__
#define __LOG_TIMESTAMP_DECORATOR_H__

#include "ALogDecorator.h"

namespace logger {
	class LogTimestampDecorator : public ALogDecorator
	{
	public:
		LogTimestampDecorator(ILogComponent* component);

		string logInfo(logger::ILogData& logData) const override;
	};
}

#endif // !__LOG_TIMESTAMP_DECORATOR_H__