/////////////////////////////////////////////////////////////////////////////////////
// Author Class
// A class that contains a description of authors
// The descripton includes name of author
// Features:
//      -- allow users to retrieve the name of author
// Assumptions:
//      -- the names are valid and have maximum length of 50.
/////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------
Author Class
Contains the name(s) of author(s)

Features:
    --Supports more than a single author
Assumptions:
    --
---------------------------------------------------------------------------*/
#ifndef AUTHOR
#define AUTHOR

#include <string>
#include <iostream>
using namespace std;

class Author {
public:
    Author(string);
     ~Author();
     string getName();
     void setName(string);
private:
	 string authorInfo;

};

#endif