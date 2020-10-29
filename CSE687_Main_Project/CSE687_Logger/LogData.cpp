#include <iostream>
#include <time.h>
#include "LogData.h"

bool logger::LogData::isPassed()
{
	return passed_;
}

string logger::LogData::getMessage()
{
	return message_;
}

string logger::LogData::getDateTime()
{
	char buffer[80];

	ctime_s(buffer, sizeof(buffer), &timestamp_);
	string timestring(buffer);
	return timestring.substr(0, timestring.length() - 1); // remove the \n from string and return the rest.

	//auto* time = new tm(); // create a structure tm to hold time info.
	//errno_t error = localtime_s(time, &_timestamp); // set local time.
	//strftime(buffer, sizeof(buffer), "%c", time);  // set buffer string to have time info.

	//// done with time so need to delete it.
	//delete time;  // delete
	//return  string(buffer); // return time.

	//return to_string( _timestamp);  // just return a number value.
}

logger::LogData::LogData(bool passed, const string& message) : passed_(passed), message_(message)
{
	time(&timestamp_);
}

ostream& logger::operator<<(ostream& out, ILogData& logData)
{
	out << logData.getDateTime();
	out << " | ";
	out << logData.isPassed();
	out << " | ";
	out << logData.getMessage();
	return out;
}