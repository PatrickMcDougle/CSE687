#pragma once
#ifndef __I_LOG_COMPONENT_H__
#define __I_LOG_COMPONENT_H__

#include <string>

#include "ILogData.h"

using std::string;

namespace logger {
	class ILogComponent {
	public:
		virtual ~ILogComponent() {}
		virtual string logInfo(data::ILogData&) const = 0;
	};
}

#endif // !__I_LOG_COMPONENT_H__
