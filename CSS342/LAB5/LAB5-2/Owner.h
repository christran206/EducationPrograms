//
//  Owner.h
//  lab5
//  Owner class
//

#pragma once
#include <string>

using namespace std;

//--------------------------------- class Owner --------------------------------
//  Owner class: contains the personal information of the client (first, last
//    name) with additional functionality:
//    -- retrieve the clients last name
//    -- retrieve the clients first name
//    -- set the clients last name
//    -- set the clients first name
//
//  Assumptions:
//    -- owner must have first and last name
//    -- last and first name cannot contain spaces within either
//------------------------------------------------------------------------------

class Owner {

	//friend ostream& operator<<(ostream &, const Owner &);

public:
	Owner(string , string);   // constructor
	~Owner();                 // destructor

    string getFirstName() const;    // returns owner first name
    string getLastName() const;     // return owner last name
    void setLastName(string);       // set owner last name
    void setFirstName(string);      // set owner first name
    
private:
    string lastName;          // string to hold client's last name   
    string firstName;         // string to hold client's first name
};

