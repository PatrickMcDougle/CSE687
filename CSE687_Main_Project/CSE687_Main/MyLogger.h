#pragma once
#ifndef __MY_LOGGER_H__
#define __MY_LOGGER_H__

#include <string>

#include "ILogger.h"
#include "ILogComponent.h"
#include "ILogData.h"
#include "LogData.h"

using std::string;

namespace logger {
	class MyLogger : public ILogger
	{
	public:
		MyLogger();

		string logInfo(bool, const string&)  override;

		void setLogComponent(ILogComponent*)  override;
	private:
		ILogComponent* log_component_;
	};
}

#endif // !__MY_LOGGER_H__
