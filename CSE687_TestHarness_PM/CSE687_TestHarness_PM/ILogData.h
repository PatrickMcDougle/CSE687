#pragma once
#ifndef __I_LOG_DATA_H__
#define __I_LOG_DATA_H__

#include <string>

using namespace std;

namespace logger::data {
	class ILogData {
	public:
		virtual bool isPassed() = 0;
		virtual string getMessage() = 0;
		virtual string getDateTime() = 0;
	};
}

#endif // !__I_LOG_DATA_H__
