/////////////////////////////////////////////////////////////////////////////////////
/* AbourPatron Class
// A class that contains a description of Patrons
// Contains the following information
// First Name
// Last Name
// Features:
//      -- allow users to retrieve the first name and last name
// Assumptions:
//      -- the names are valid and have maximum length of 50.
//      -- this class can be modified to add additional details without breaking
//          other classes
*////////////////////////////////////////////////////////////////////////////////////

#ifndef ABOUTPATRON
#define ABOUTPATRON

#include <string>
#include <iostream>
using namespace std;

class AboutPatron {
public:
    AboutPatron(string,string);
    ~AboutPatron();

    void setFirstName(string);
    void setLastName(string);
    string getFirstName();
    string getLastName();

private:
	string patronLastName;
	string patronFirstName;
};

#endif