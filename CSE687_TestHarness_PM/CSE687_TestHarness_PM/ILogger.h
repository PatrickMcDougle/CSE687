#pragma once
#ifndef __I_LOGGER_H__
#define __I_LOGGER_H__

#include <string>

#include "ILogComponent.h"


using std::string;

namespace logger {
	class ILogger
	{
	public :
		virtual ~ILogger() {}
		virtual string logInfo(bool, const string&)  = 0;
		virtual void setLogComponent(ILogComponent*)  = 0;
	};
}

#endif // !__I_LOGGER_H__
