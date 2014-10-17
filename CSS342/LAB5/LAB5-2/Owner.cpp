//
//  Owner.cpp
//  lab5
//  Owner implementation
//

#include "Owner.h"

//------------------------------------------------------------------------------
// Constructor
// set first and last name of client
Owner::Owner(string last, string first) {
	setLastName(last);
	setFirstName(first);
}

//------------------------------------------------------------------------------
// Destructor
//
Owner::~Owner() {

}

//------------------------------------------------------------------------------
// getFirstName
// Returns the first name of the client
string Owner::getFirstName() const {
	return firstName;
}

//------------------------------------------------------------------------------
// getLastName
// Returns the last name of the client
string Owner::getLastName() const {
	return lastName;
}

//------------------------------------------------------------------------------
// setLastName
// sets the last name of the client
void Owner::setLastName(string last) {
	lastName = last;
}

//------------------------------------------------------------------------------
// setFirstName
// sets the first name of the client
void Owner::setFirstName(string first) {
	firstName = first;
}

//------------------------------------------------------------------------------
// Operator <<
// overloaded operator to output the first and last name of a client
/*ostream& operator<<(ostream& output, const Owner& O) {
	output << O.getFirstName() << " " << O.getLastName();
	return output;
}*/
