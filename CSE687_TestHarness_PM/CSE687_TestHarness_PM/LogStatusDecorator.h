#pragma once

#ifndef __LOG_STATUS_DECORATOR_H__
#define __LOG_STATUS_DECORATOR_H__

#include "ALogDecorator.h"

namespace logger {
	class LogStatusDecorator : public ALogDecorator
	{
	public:
		LogStatusDecorator(ILogComponent* component);

		string logInfo(data::ILogData& logData) const override;
	};
}

#endif // !__LOG_STATUS_DECORATOR_H__