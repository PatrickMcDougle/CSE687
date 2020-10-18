#pragma once
#ifndef __LOG_DATA_H__
#define __LOG_DATA_H__

#include <string>
#include "ILogData.h"

using namespace std;

namespace logger::data {
	class LogData : public ILogData {
	public:
		virtual bool isPassed();
		virtual string getMessage();
		virtual string getDateTime();

		LogData(bool, const string&);

	private:
		bool _passed;
		string _message;
		time_t _timestamp;
	};

	ostream& operator<<(ostream& out, ILogData& logData);
}

#endif // !__LOG_DATA_H__
