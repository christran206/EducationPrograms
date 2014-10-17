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
// While I have done much of this for you, make sure you understand it all.
// Make sure you understand why the parameters are pass by reference
// in evaluatePrefixHelper and toPostfix.

#include "prefix.h"

//-----------------------------------------------------------------------------
// constructor
// initialize the array to the empty string 
// char arrays are terminated with '\0' so operator<< works properly

Prefix::Prefix() {
   expr[0] = '\0'; 
} 

//-----------------------------------------------------------------------------
// setPrefix
// Set a prefix expression made of single digit operands, operators +,-,*,/
// and no blanks or tabs contained in a file. The expression is valid in
// that each operator has two valid operands.

void Prefix::setPrefix(ifstream& infile) { 
    infile >> expr;
}

//-----------------------------------------------------------------------------
// evaluatePrefix 
// Evaluate a prefix expr made of single digit operands and operators +,-,*,/
// Calls helper function evaluatePrefixHelper for evaluation
int Prefix::evaluatePrefix() const {
    if (expr[0] == '\0') 
        return 0;

    int index = -1;                               // to walk through expr
    return evaluatePrefixHelper(index);
}
//-----------------------------------------------------------------------------
//evaluatePrefixHelper
//Evaluates the correct answer from a properly formatted prefix expression
//Assumptions
//Prefix expression is an operater followed by two operands
//Prefix expression will contain a single positive int for the operands 0-9
//Prefix expression will contain +,-,*,/ for the operator
//Divide by zero and non digits will return 0
int Prefix::evaluatePrefixHelper(int& index) const {
    char symbol = expr[++index];
	switch (symbol) {
	//In all cases where there is an operator, use infix expression to
	//return evaluation with operands
	case '+':
		return evaluatePrefixHelper(index) + evaluatePrefixHelper(index);
		break;
	case '-':
		return evaluatePrefixHelper(index) - evaluatePrefixHelper(index);
		break;
	case '*':
		return evaluatePrefixHelper(index) * evaluatePrefixHelper(index);
		break;
	case '/': {
		int numerator = evaluatePrefixHelper(index);
		int denominator = evaluatePrefixHelper(index);
		//divide by zero
		if(denominator == 0) {
			//If denominator is 0, return 0 since a value must be returned
			return 0;
		}
		return  numerator / denominator;
		break;
			  }
	//This should never be reached but included in case
	case '\0':
		break;
	//Since we assume all properly formatted data, if the symbol isn't an
	//operator, the remaining must be digits so return int value
	default:
		if(isdigit(symbol)) {
			return symbol -'0';
		} else {
			return 0;
		}
	}
}

//-----------------------------------------------------------------------------
// outputAsPostfix, toPostfix
// Convert prefix expression to postfix and output
// Calls toPostfix to populate character array with postfix expression
void Prefix::outputAsPostfix(ostream& out) const {
    if (expr[0] == '\0') 
        return;

    int index = -1;                           // to walk through expr
    int count = -1;                           // used to build postfix array
    char postfix[MAXSIZE+1];                  // holds postfix expression
    toPostfix(index, postfix, count);
    postfix[++count] = '\0';
    out << postfix;
}
//-----------------------------------------------------------------------------
//toPostfix
//Populate character array with postfix representation of prefix expression
//Assumptions
//index and count parameters start at -1
void Prefix::toPostfix(int& index, char postfix[], int& count) const {
    char symbol = expr[++index];
	switch (symbol)	{
	//In all cases of an operator, recursive call function twice to store
	//operands and store operator after
	case '+':
	case '-':
	case '*':
	case '/':
		toPostfix(index,postfix,count);
		toPostfix(index,postfix,count);
		postfix[++count] = symbol;
		break;
	//If the symbole is not an operator, it must be an operand
	//store in position one higher than current count
	default:
		postfix[++count] = symbol;
	}
}

//-----------------------------------------------------------------------------
// operator<<
// display prefix expression as a string (char array)

ostream& operator<<(ostream& output, const Prefix& expression) {
    output << expression.expr;
    return output;
}

