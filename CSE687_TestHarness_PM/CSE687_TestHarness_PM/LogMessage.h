#pragma once

#ifndef __LOG_MESSAGE_H__
#define __LOG_MESSAGE_H__

#include "ILogComponent.h"

namespace logger {
	class LogMessage : public ILogComponent
	{
	public:
		LogMessage();

		string logInfo(data::ILogData& logData) const override;
	};
}

#endif // !__LOG_MESSAGE_H__