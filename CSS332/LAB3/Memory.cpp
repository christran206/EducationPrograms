//
//  Memory.cpp
//  ClassExamples
//
//  Created by Rob Nash on 10/1/13.
//  Copyright (c) 2013 Rob Nash. All rights reserved.
//
#include<iostream>
using namespace std;

static int i;  //a global (bad)

void foo(double a, double* b) {  //these params - are they local autos?
    static int count;            //lives where? Accessable where?
    count++;
    cout << count <<endl;

    *b=42;  //what does this have to do with x in main?
    i=6;    //does this "i" leave scope on the next line?
}



int main() {
    char* cStr = new char[30];   //lives where?
    double x=3.0;
    
    cout << "x is " << x <<endl;
    
    foo(3.5, &x);
    
    cout << "x is " << x <<endl;
    
    cout << "sizeof char " <<sizeof (int) <<endl;
    
    delete [] cStr;             //does what to the stack? heap?
    cStr=NULL;                  //stack or heap?
    return 0;                   //in which stack frame is this 0 returned?
}
