// Creators - Team #5: Patrick McDougle, Edgardo Navarro, William Scott
// Class: CSE 687 OOD
// School: Syracuse University
// Project Name: Test Harness
// Create Date: 2020-10-11
// Description: CPP File For LogData
#include <iostream>
#include <time.h>
#include "LogData.h"

using namespace logger;

// Return log results
bool LogData::isPassed()
{
	return passed_;
}

// Return log message
string logger::LogData::getMessage()
{
	return message_;
}

// Return current date and time
string logger::LogData::getDateTime()
{
	time_t rawtime;
    time (&rawtime);
    char *t = ctime(&rawtime);
    if (t[strlen(t)-1] == '\n') t[strlen(t)-1] = '\0';
    
    return t;
}

// Constructor
LogData::LogData(bool passed, const string& message) : passed_(passed), message_(message)
{
	time(&timestamp_);
}

// Return all details of Log Data
ostream& logger::operator<<(ostream& out, ILogData& logData)
{
	out << logData.getDateTime();
	out << " | ";
	out << logData.isPassed();
	out << " | ";
	out << logData.getMessage();
	return out;
}