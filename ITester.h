
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//CES687_20_Test Harness Project - by Team 4
//Edgardo Navarro MS candidate, Computer Engineering, Syracuse University.
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Test_Harness abstract class interface.
/////////////////////////////////////////////////////////////////////////////////////////
//Introduction: 
//We provide a high - level overview of the architecture & design of our Test Harness. It
//will explain in detail the two key elements : Tester and Logger.The Tester object can be
//fed new classes & functions, and the Logger object keeps track of the results of each test. 
//Following, we cover how each test is designedand how they will be utilized.
//Purpose:
//The purpose of a Test Harness is to more easily test if new classesand functions are 
//behaving as expected.Rather than manually typing up logic for each case, the harness will
//provide a faster and cleaner alternative once completed.The developer simply needs to 
//pass the class and method that needs to be tested, and then select which type of test(s) 
//need(s) to be performed.The developer could switch to another function, then re - run all
//the same test if needed without having to copy, adjust, and run logic again.

//The Tester will be the main object used by the developer.The object once created needs to
//be fed the new Class, Function, and type of test(s).The first two items will be populated
//with the elements “setClass”and “setMethod” respectively.The original request only 
//requires the ability to process methods with no argumentsand returns a Boolean result.
//The two Boolean functions that create tests are : “isTrue” and “isFalse”. Once all the 
//key items have been filled, the developer can finally run the test with “runTest”. After
//careful consideration on how to expand these two methods with different output types(not
//Boolean), other methods are considered as options to help cover majority of numeric types.
//The “and”and “or” methods will come in handy for tests where the results need say less 
//than or equal to a specific value.

//The Logger will be an object within the Tester which will record all the test results. 
//The idea is to have the results(logs) populate a vector which can then be accessed.The 
//vector is comprised of individual logs which are made up of 3 pieces: Result(Pass or Fail),
//Message, and Timestamp.In addition, we can save results to an output file or database if
//historical results were needed. "
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _ITESTER_H
#define	_ITESTER_H


	class ITester {
	public:
		virtual string setClass() = 0;
		virtual string setMethod() = 0;
		virtual bool isTrue() = 0;
		virtual bool isFalse() = 0;
		virtual string setMessage() = 0;
		virtual string logResults() = 0;
		virtual bool runTest() = 0;
		virtual ~ITester() {};
	};

#endif 