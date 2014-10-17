//---------------------------------------------------------------------------
#ifndef POLY_H
#define POLY_H

#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
/*
// Poly class:  Object mimics the properties of a mathematics polynomial
//   also includes additional features:
//   -- Perform math functions on Poly object (add, Sub, Multi)
//   -- Allows for comparison of two Poly Objects
//   -- Allows for assignment operators and math assignment operators
//
// Assumptions:
//   -- Constructor only takes one coefficient
//   -- Follows Math Rules
//   -- User enters integers in input stream
//   -- Output stream does not display x^0 coefficient if it's zero
//   -- Negative coefficients are not allowed
*/
//---------------------------------------------------------------------------
class Poly {
	friend ostream& operator<<(ostream &, const Poly &);
	friend istream& operator>>(istream &, Poly &);

public:
	//Constructors
	Poly(int coeff = 0, int expo = 0);//Default Constructor
	Poly(const Poly &);//Copy Constructor
	~Poly();//De-constructor

	//Functions
	bool setCoeff(int,int);//Set a coefficient
	int getCoeff(int);//Return value of coefficient

	//Overloaded Functions
	Poly operator+(const Poly &) const;//Add two polynomials
	Poly operator-(const Poly &) const;//Subtract two polynomials
	Poly operator*(const Poly &) const;//Multiply two polynomials

	//Assignment Operators
	Poly& operator=(const Poly &);//Current object equals parameter
	Poly& operator+=(const Poly &);//Param is added to current object
	Poly& operator-=(const Poly &);//Param is subt. from current object
	Poly& operator*=(const Poly &);//Param is multip. to current object

	//Comparison Operators
	bool operator==(const Poly &) const;//Are two polynomials equal?
	bool operator!=(const Poly &) const;//Are two polynomials different?

private:
	//Object Variables
	int* polynomial;//Container for Coefficient
	int largestExpo;//Largest Exponent in Object

	void getLargestExpo();	//Find largest Exponent
};
#endif
