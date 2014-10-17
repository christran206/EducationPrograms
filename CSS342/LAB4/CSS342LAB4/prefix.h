/*
//-----------------------------------------------------------------------------
					Prefix Class
Class Description
A class that evaluates prefix expressions where the operands are single,
positive digits and converts prefix expressions into postfix expressions

Design Decisions:

Class Decisions:
--Why are arguements passed by reference?
When walking the prefix expression, the parameter value is stored outside
the recursive stack and so it can be changed inside recursive stacks.
When the stack unwinds, the values keep their needed values when back 
to first call and any additional branching

Assumptions
-Prefix expression is one operator followed by two operands
-Operator will be +,-,*,/
-All data input will be properly formatted, no format checking required
*/
// You add all appropriate comments describing the ADT 
// and class assumptions here.
// Add all member (data and functions) comments as well in this file.

#ifndef PREFIX_H
#define PREFIX_H
#include <iostream>
#include <fstream>
using namespace std;
//-----------------------------------------------------------------------------

int const MAXSIZE = 100;

class Prefix {
    friend ostream& operator<<(ostream&, const Prefix&);
//-----------------------------------------------------------------------------

public:
    Prefix();
    void setPrefix(ifstream& infile);		//Reads one prefix line
    int evaluatePrefix() const;				//Value of the prefix epxression
    void outputAsPostfix(ostream&) const;	//Shows postfix representation
//-----------------------------------------------------------------------------

private:
    char expr[MAXSIZE+1];					//Character array for prefix
    int evaluatePrefixHelper(int&) const;	//Recursive prefix evaluator
    void toPostfix(int&, char [], int&) const;	//Recursive postfix generator
};

#endif

