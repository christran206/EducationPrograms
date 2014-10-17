#include<string>
#include<iostream>
using namespace std;
/*
 *
 *
 * outcomes: pass-by-value, pass-by-reference, structs, const, function declaration order for single-pass compilers, 
 *  reference parameters, platform specific code, functional/imperative programming
 *
 */
 

//First use of structs - like classes, but all public and no methods
struct Rational {
    int n;   //crappy variable names here
    int d;
};


void reduce() {  /*left for the reader to implement; consider Euclids algorithm */}

//Pass-by-value or copy here
Rational add(const struct Rational lhs, struct Rational rhs) {  //lhs + rhs...what does const do here? should they both be const
    struct Rational retVal;
    
    retVal.n= lhs.n*rhs.d + rhs.n*lhs.d;
    retVal.d=lhs.d*rhs.d;  //notice inconsistent indentation/spacing style here
    reduce();  //just a dummy call, does nothing, affects no structs or objects
    
    return retVal;
    
}

//Pass-by-reference (or sharing, increasing the variables scope to include this function)
void subtract(struct Rational&  lhs, const struct Rational& rhs) {
    //rhs.d = 3;  //not allowed here
    lhs.n = lhs.n*rhs.d - rhs.n*lhs.d;
    lhs.d *= rhs.d;
    //no return type, yet values in the objects passed to this function have changed in main's scope
}

/* Below int-to-string code will work on many platforms - broken currently on some linux and mac (instantiation of undeclared template)
string itos(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}*/

//this should evolve to the operator<<
string toString(struct Rational target) {  //target becomes the "implicit parameter" (this) inside of a class.  This would point to "a" in "a.toString()";
    string retVal = string(" ") + to_string(target.n) + string("/") + to_string(target.d);  //" "  + target.n doesn't work.  why?
    
    return retVal;
}


int main() {
    Rational a;
    Rational b;
    Rational c;
    
    a.n=2;  //these are like public fields in java - anyone anywhere can access them.
    a.d=3;
    b.n=1;
    b.d=3;
    
    
    c = add(a,b);    //c = a + b would be better here
    cout << toString(c);
    
    
    subtract(c,b);  //how does this affect any struct or object if there is no assignment? "c = subtract(c,b)"
    cout << toString(c);  //how does C/C++'s definition of an object differ from Java's?  Are structs objects? ints?
    
    
    return 0;
}