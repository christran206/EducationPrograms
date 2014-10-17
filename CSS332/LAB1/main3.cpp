//
//  main3.cpp
//  ClassExamples
//
//  Created by Rob Nash on 9/26/13.
//  Copyright (c) 2013 Rob Nash. All rights reserved.
//


#include <iostream>
using namespace std;


void display(int l, int m, int n, int o, int* p) {
    cout << "var1 is " << l << endl;
    cout << "var2 is " << m << endl;
    cout << "var3 is " << n << endl;
    cout << "var4 is " << o << endl;
    cout << "address of l (var1) is " << &l << endl;
    
    //todo2: why are the addresses of l and a different?  If I print the address of a in main, I get X
    //but if I print the address of l (which was initialized by a) in here, I see address Y?  
		//Because it's passed by value so the memory address of l is not the same as the memory address of a
}

int main3()
{
    int a = 3;
    int b,c,d;
    int* aPtr, bPtr;  //Pitfall: note that bPtr is an int, not an int *
    b=3;
    c=5;
    d = a + b + c;
    
    aPtr = &a;
    
    display(a,b,c,d,aPtr);
    
    cout << "aPtr's value is " << aPtr << endl;
    cout << "This is the same as &a, or " << &a << endl;
    
    
    cout << "aPtr points to the following value:  " << *aPtr << endl;
    cout << "This is the same as a, or " << a <<endl;

    
    //todo1: assign the data that aPtr points to a new value (hint: use the dereference operator)
    cout << "Change the data that aPtr points to, and output both *p and var1 - what has happened?";

    return 0;
}
