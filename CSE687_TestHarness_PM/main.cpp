//
//  main.cpp
//  TestHarnessv2
//
//  Created by William Scott on 10/21/20.
//  Copyright © 2020 William Scott. All rights reserved.
//

#include <iostream>
#include "FakeClass.hpp"
#include "Tester.hpp"
using std::cout;
using std::endl;
using namespace TestHarn;

bool alwaysTrue(){
    return true;
}

bool alwaysFalse(){
    return false;
}

int main(int argc, const char * argv[]) {

    cout << "*******************************" << endl << "Test 1" << endl
        << "*******************************" << endl;
    
    Executor<ITest> exec;
    cout << exec.showResult(exec.doTest(alwaysTrue),"alwaysTrue") << endl;
    cout << exec.showResult(exec.doTest(alwaysFalse),"alwaysFalse") << endl;
    
    bool test1 = exec.doTest(FakeClass::returnTrue);
    cout << exec.showResult(test1, "FakeClass returnTrue") << endl;
    
    bool test2 = exec.doTest(FakeClass::returnFalse);
    cout << exec.showResult(test2, "FakeClass returnFalse") << endl;

    
}
