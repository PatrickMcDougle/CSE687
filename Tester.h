
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//CES687_20_Test Harness Project. By Team 4
//Edgardo Navarro MS candidate, Computer Engineering, Syracuse University.
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tester class interface. Evaluates Methods
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef TESTER_H
#define	TESTER_H


#include "ITester.h"
#include<string>
#include<iostream>

using std::string;
using std::cout;
using std::endl;

	class Tester : public ITester {
	public:
		Tester(string*, string*);
		Tester(string*, method*, ILogData*, ILogger*, string);
		virtual string setClass() const;
		virtual string setMethod() const;
		virtual bool isTrue();
		virtual bool isFalse();
		virtual string setMessage();
		virtual string logResults();
		virtual bool runTest();
		virtual ~Tester() { cout << "Tester destroyed" << endl; };

	private:
		string* theClass;
		method* theMethod;
		ILogData* theLogData;
		ILogger* theLogger;
		string theMessage;
	};
#endif
