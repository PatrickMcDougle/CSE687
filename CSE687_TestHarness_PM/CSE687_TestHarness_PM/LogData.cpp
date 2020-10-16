#include "LogData.h"
#include <time.h>
#include <iostream>

bool logger::data::LogData::isPassed()
{
	return _passed;
}

string logger::data::LogData::getMessage()
{
	return _message;
}

string logger::data::LogData::getDateTime()
{
	char buffer[80];

	ctime_s(buffer, sizeof(buffer), &_timestamp);
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

logger::data::LogData::LogData(bool passed, const string& message) : _passed(passed), _message(message)
{
	time(&_timestamp);
}

//ostream& logger::data::LogData::operator<<(ostream& out)
//{
//	out << this->getDateTime() << " | " << this->isPassed() << " | " << this->getMessage();
//	return out;
//}

ostream& logger::data::operator<<(ostream& out, ILogData& logData)
{
	out << logData.getDateTime();
	out << " | ";
	out << logData.isPassed();
	out << " | ";
	out << logData.getMessage();
	return out;
}
