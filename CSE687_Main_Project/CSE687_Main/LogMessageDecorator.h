#pragma once

#ifndef __LOG_MESSAGE_DECORATOR_H__
#define __LOG_MESSAGE_DECORATOR_H__

#include "ALogDecorator.h"

namespace logger {
	class LogMessageDecorator : public ALogDecorator
	{
	public:
		LogMessageDecorator(ILogComponent* component);

		string logInfo(logger::ILogData& logData) const override;
	};
}

#endif // !__LOG_MESSAGE_DECORATOR_H__