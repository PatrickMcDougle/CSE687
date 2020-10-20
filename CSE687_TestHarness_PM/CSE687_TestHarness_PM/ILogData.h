#pragma once
#ifndef __I_LOG_DATA_H__
#define __I_LOG_DATA_H__

#include <string>

using std::string;

namespace logger::data {
	class ILogData {
	public:
		virtual ~ILogData() {}
		virtual bool isPassed() = 0;
		virtual string getMessage() = 0;
		virtual string getDateTime() = 0;
	};
}

#endif // !__I_LOG_DATA_H__
