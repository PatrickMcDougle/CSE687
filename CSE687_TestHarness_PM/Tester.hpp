//
//  Tester.hpp
//  TestHarnessv2
//
//  Created by William Scott on 10/21/20.
//  Copyright © 2020 William Scott. All rights reserved.
//

#ifndef Tester_hpp
#define Tester_hpp

#include <stdio.h>
#include <string>
using std::string;

namespace TestHarn {

    struct ITest{
      virtual ~ITest() {}
      virtual bool test() = 0;
      virtual std::string name() = 0;
    };

    /*-- method pointer type declaration --*/
    template<typename T>
    using MP = bool(T::*)();

    /*-- function pointer type declaration --*/
    using FP = bool(*)();

    ///////////////////////////////////////////////
    // Executor class

    template<typename T>
    class Executor {
    
    public:
      Executor() = default;

      /*-- execute test class instance's test method --*/
      bool doTest(MP<T> tp, T* pT) {
        bool result = false;
        try {
          result = (pT->*tp)();
        }
        catch (...) {
          result = false;
        }
        return result;
      }
        
        /*-- execute test class instance's test method --*/
        bool doTest(MP<T> tp) {
          bool result = false;
            try {
              result = (*tp)();
            }
            catch (...) {
              result = false;
            }
          return result;
        }
        
        /*-- execute test class instance's test method --*/
        bool doTest(T* pT) {
          bool result = false;
          return result;
        }
        
      /*-- execute test function --*/

      bool doTest(FP fp) {
        bool result = false;
        try {
          result = fp();
        }
        catch (...) {
          result = false;
        }
        return result;
      }
      /*-- report results to avoid repetition in test code --*/

      string showResult(bool r, const string& name) {
          string s;
          if (r) {
              s = name + " passed";
          }
          else {
              s = name + " failed";
          }
          
          return s;
          
      }
        
    };
}

#endif /* Tester_hpp */
