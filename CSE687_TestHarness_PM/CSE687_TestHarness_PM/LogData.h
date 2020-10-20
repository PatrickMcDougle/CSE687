#pragma once
#ifndef __LOG_DATA_H__
#define __LOG_DATA_H__

#include <iostream>
#include <string>
#include "ILogData.h"

using std::string;
using std::ostream;
using std::cout;
using std::endl;

namespace logger::data {
	class LogData : public ILogData {
	public:
		virtual ~LogData() {}
		virtual bool isPassed();
		virtual string getMessage();
		virtual string getDateTime();

		LogData(bool, const string&);

	private:
		bool passed_;
		string message_;
		time_t timestamp_;
	};

	ostream& operator<<(ostream& out, ILogData& logData);
}

#endif // !__LOG_DATA_H__
