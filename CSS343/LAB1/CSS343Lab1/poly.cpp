#include "poly.h"

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

//---------------------------------------------------------------------------
/*Default Constructor 
Takes two int parameters, first is a coefficient and second is the exponent
Allocates an int array on the heap with the size of the exponent
Coefficient has to be positive
*/
Poly::Poly(int coeff, int expo)	{
	//If the exponent is negative
	//Create poly object the same as Poly(0,0)
	if(expo < 0) {
		polynomial = new int[1];
		polynomial[0] = 0;
		largestExpo = 0;
	} else {
		polynomial = new int[expo+1];
		//zero out array to overwrite garbage
		for(int i = 0; i <= expo; i++) {
			polynomial[i] = 0;
		}
		//Set the parameter values
		polynomial[expo] = coeff;
		largestExpo = expo;
	}
}

//---------------------------------------------------------------------------
/*
Copy Constructor
Allocate an array of the same size as the parameter and copy the values
in the array
*/
Poly::Poly(const Poly& param) {
	polynomial = new int[param.largestExpo+1];
	for(int i = 0; i <= param.largestExpo; i++)	{
		polynomial[i] = param.polynomial[i];
	}
	largestExpo = param.largestExpo;
}

//---------------------------------------------------------------------------
/*
De-constructor
Since the only non-primitive memory is the dynamic array, only the dynamic
array needs to be deleted
*/
Poly::~Poly(){
	delete[] polynomial;
}

//---------------------------------------------------------------------------
/*
setCoeff
Sets the parameter exponential to the parameter coefficient
If the exponent is negative, return false
If the exponent is larger than the size of the array, create a new array
*/
bool Poly::setCoeff(int coeff,int expo)	{
	if( expo < 0 ) {
		return false;
	} else {
		//If the parameter is larger than int array
		if(expo > largestExpo) {
			int* temp = new int[expo+1];
			//copy values from current array and zero out rest
			for(int i = 0; i <= expo; i++)	{
				if(i <= largestExpo) {
					temp[i] = polynomial[i];
				} else {
					temp[i] = 0;
				}
			}
			delete[] polynomial;
			polynomial = temp;
			largestExpo = expo;
		}
		polynomial[expo] = coeff;
		//If the largestExpo is set to zero find the next value
		getLargestExpo();
		return true;
	}
}

//---------------------------------------------------------------------------
/*
getCoeff
Return the coefficient value at the exponent parameter given
If the parameter is greater or equal than 0 and less than or equal to
largestExpo, there must exist a value to return
*/
int Poly::getCoeff(int expo)	{
	if(expo >= 0 && expo <= largestExpo) {
		return polynomial[expo];
	} else {
		return 0;
	}
}

//---------------------------------------------------------------------------
/*
operator+
Add two Poly objects together
Math rule a+b = b+a, we can take the largest poly object and add the other
poly object to it and return
*/
Poly Poly::operator+(const Poly& param) const {
	Poly temp;
	if(largestExpo >= param.largestExpo) {
		temp = Poly(*this);
		for(int i = 0; i <= param.largestExpo; i++) {
			temp.polynomial[i] += param.polynomial[i];
		}
	} else {
		temp = Poly(param);
		for(int i = 0; i <= largestExpo; i++) {
			temp.polynomial[i] += polynomial[i];
		}
	}
	return temp;
}

//---------------------------------------------------------------------------
/*
operator-
Subtracts the right poly object from the left poly object
Math rule a-b != b-a
Right poly object must always be subtracted from the left poly object
*/
Poly Poly::operator-(const Poly& param) const	{
	//Is exponents are equal or param is lower
	//Copy current object and subtract same indexes
	if(largestExpo >= param.largestExpo) {
		Poly temp = Poly(*this);
		for(int i = 0; i <= param.largestExpo; i++) {
			temp.polynomial[i] -= param.polynomial[i];
		}
		//In event subtraction causes largest index to become zero
		//get new largest exponent
		temp.getLargestExpo();
		return temp;
	} else {
		//Copy parameter object since it has a larger exponent
		Poly temp = Poly(param);
		//Multiply each index to -1 and then add the current object
		//Math proof a-b is equal to -b+a
		for(int i = 0; i <= temp.largestExpo; i++) {
			temp.polynomial[i] *= -1;
		}
		for(int i = 0; i <= largestExpo; i++) {
			temp.polynomial[i] += polynomial[i];
		}
		//in event that largest exponent becomes zero
		temp.getLargestExpo();
		return temp;
	}
	
}

//---------------------------------------------------------------------------
/*
operator*
Multiplies two poly objects together
math rule a(b+c) = ab + ac
Check if either object is zero (largestExpo is 0 and coefficient is 0)
this automatically means the answer will be zero

*/
Poly Poly::operator*(const Poly& param) const {
	//If either objects are only a zero subscript with zero as the int
	//Return a Poly object of 0
	if(largestExpo == 0 || param.largestExpo == 0) {
		if(polynomial[0] == 0 || param.polynomial[0] == 0) {
			return Poly(0,0);
		}
	}
	//Create poly object with size equal to the sum of both objects
	//largest exponent
	Poly temp(0,largestExpo+param.largestExpo);
	//Multiple each coefficient together and add to proper location
	//x^a * x^b is equal to x^(a+b)
	for(int i = 0; i <= largestExpo; i++) {
		for(int j = 0; j <= param.largestExpo; j++) {
			temp.polynomial[i+j] += 
			polynomial[i]*param.polynomial[j];
		}
	}
	//determine the largest non zero exponent since it's possible to
	//have coefficients cancel each other out
	temp.getLargestExpo();
	return temp;
}

//---------------------------------------------------------------------------
//assignoper operator=
//Changes the current object to have the same properties as the object
//on the right
Poly& Poly::operator=(const Poly& param) {
	//If the parameter on both sides are the same, return this object
	if(&param == this) {
		return *this;
	}
	//if the right object is larger, create new int array and copy
	//source indexes
	if(param.largestExpo > largestExpo) {
		delete[] polynomial;
		polynomial = new int[param.largestExpo+1];
		largestExpo = param.largestExpo;
		for(int i = 0; i <= largestExpo; i++) {
			polynomial[i] = param.polynomial[i];
		}
	} else {
		//the current object has a lrger array
		//copy all indexes from target and zero remaining indexes
		for(int i = 0; i <= largestExpo; i++) {
			if(i <= param.largestExpo) {
				polynomial[i] = param.polynomial[i];
			} else {
				polynomial[i] = 0;
			}
		}
		//Since parameter has a smaller largest exponent
		//copy the parameters value into this object
		largestExpo = param.largestExpo;
	}
	return *this;
}

//---------------------------------------------------------------------------
//assignment operator +=
//Adds the right parameter to the current object
Poly& Poly::operator+=(const Poly& param) {
	//if the right object has a larger exponent
	//create a new int array with the same size as the 
	//right objects array
	if(param.largestExpo > largestExpo) {
		int* temp = new int[param.largestExpo+1];
		//Copy values of all indexes of the current int array into
		//new temp array
		for(int i = 0; i <= param.largestExpo; i++) {
			if(i <= largestExpo) {
				temp[i] = polynomial[i];
			} else {
				temp[i] = 0;
			}
		}
		delete[] polynomial;
		polynomial = temp;
		largestExpo = param.largestExpo;
	}
	//add all indexes of the right object into the current object
	for(int i = 0; i <= param.largestExpo; i++) {
		polynomial[i] += param.polynomial[i];
	}
	//in the event the addition results in the largest exponent
	//having a coefficient ofzero, find new largest exponent
	getLargestExpo();
	return *this;
}

//---------------------------------------------------------------------------
//Assignment operator -=
//Subtracts the right parameter from the current object
Poly& Poly::operator-=(const Poly& param) {
	//If the parameter object is larger, replace current objects
	//int array with copy with size of parameter array
	if(param.largestExpo > largestExpo) {
		int* temp = new int[param.largestExpo+1];
		for(int i = 0; i <= param.largestExpo; i++) {
			if(i <= largestExpo) {
				temp[i] = polynomial[i];
			} else {
				temp[i] = 0;
			}
		}
		delete[] polynomial;
		polynomial = temp;
		largestExpo = param.largestExpo;
	}
	//Subtract the value from the parameter index
	//from the parameter index of the current object
	for(int i = 0; i <= param.largestExpo; i++) {
		polynomial[i] -= param.polynomial[i];
	}
	//In the event subtraction results in the largest exponent
	//with a value of zero, find the next largest exponent
	getLargestExpo();
	return *this;
}

//---------------------------------------------------------------------------
//Assignment operator *=
//Multiplies each coefficient of the current object
//with each coefficient of the parameter object
//to create a product of both objects and assigns
//to the current object
Poly& Poly::operator*=(const Poly& param) {
	//If this Poly object has only x^0 coefficient of zero, 
	//return itself
	//Reason 0*anything is still 0
	if(largestExpo == 0 && polynomial[0] == 0) {
		return *this;
	}
	//If the parameter only has coefficient of x^0
	//multiply each coefficient of this object with
	//the 0 index value of the parameter object
	if(param.largestExpo == 0) {
		for(int i = 0; i <= largestExpo; i++) {
			polynomial[i] *= param.polynomial[0];
		}
		//In case the parameter is a zero poly object
		//get largest will result in 0 as the largestExpo
		getLargestExpo();
		return *this;
	}
	//if coefficient is above x^0
	int* temp = new int[largestExpo+param.largestExpo+1];
	//zero out the new temp array
	for(int i = 0; i <= largestExpo+param.largestExpo; i++) {
		temp[i] = 0;
	}
	//Multiply each coeff and add to the proper position in temp array
	for(int i = 0; i <= largestExpo; i++) {
		for(int j = 0; j <= param.largestExpo; j++) {
			temp[i+j] += polynomial[i]*param.polynomial[j];
		}
	}
	//x^a*x^b is equal to x^(a+b)
	largestExpo += param.largestExpo;
	delete[] polynomial;
	polynomial = temp;
	getLargestExpo();
	return *this;
}

//---------------------------------------------------------------------------
//Comparison operator==
//Compares two Poly Object that have identical values at each index
bool Poly::operator==(const Poly& param) const {
	//Check if both largestExpo values are identical
	//If not, then immediately they are not equal
	if(largestExpo == param.largestExpo) {
		bool isEqual = true;
		while(isEqual) {
			//Compare int values at each index to determine
			//if they hold the same value
			for(int i = 0; i <= largestExpo; i++) {
				isEqual = 
				polynomial[i] == param.polynomial[i];
			}
			//If for loop completes and all indexes are the same
			//return true
			return isEqual;
		}
	}
	//All other cases are false
	return false;
}

//---------------------------------------------------------------------------
//Comparison operator !=
//executes operator== and returns opposite result
bool Poly::operator!=(const Poly& param) const	{
	return !(*this == param);
}

//---------------------------------------------------------------------------
//Private function getLargestExpo
//Many situations may cause the index of largestExpo to become zero
//This will be executed to find the next index that has a 
//non zero value to keep the largestExpo value accurate
void Poly::getLargestExpo() {
	for(int i = largestExpo; i >= 0; i--) {
		if(polynomial[i] != 0) {
			largestExpo = i;
			break;
		}
	}
}
//---------------------------------------------------------------------------
//Stream output operator<<
//Prints the Poly object as a string starting from the largest exponent
//format int followed by x^ followed by index
ostream& operator<<(ostream &output, const Poly& r)	{
	//Loop through int array starting from largestExpo
	//Stop when index 1 is reached but do not process
	for(int i = r.largestExpo; i > 1; i--) {
		if(r.polynomial[i] != 0) {
			if(r.polynomial[i] >0) {
				output << " +" 
				<< r.polynomial[i] << "x^" << i;
			} else {
				output << " " 
				<< r.polynomial[i] << "x^" << i;
			}
		}
	}
	//index of 1 does not print the carrot symbol
	if(r.polynomial[1] != 0) {
		if(r.polynomial[1] > 0) {
			output << " +" << r.polynomial[1] << "x";
		} else {
			output << " " << r.polynomial[1] << "x";
		}
	}
	//index of 0 only prints the int value
	if(r.polynomial[0] != 0) {
		if(r.polynomial[0] >= 0) {
			output << " +" << r.polynomial[0];
		} else {
			output << " " << r.polynomial[0];
		}
	}
	return output;
}

//---------------------------------------------------------------------------
//Stream input operator>>
//input stream takes in two int values until a -1 pair is encountered
istream& operator>>(istream &input, Poly &r)	{
	//initialize int variables
	int coeff,expo;
	//while the input is valid to put into the int variables
	//keep looping
	while(input >> coeff >> expo) {
		//if both values are -1 break from loop
		if(coeff == -1 && expo == -1) {
			break;
		}
		r.setCoeff(coeff, expo);
	}
	return input;
}


