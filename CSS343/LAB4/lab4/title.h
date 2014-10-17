/*---------------------------------------------------------------------------
Title
A class that describes the title of a publication in full name and in
abbriviated form when necessary
   
Features:
    -- Retreival of Title in Full Form
    -- Retreival of Title in Abbriviated form
    -- Implements the output<< operator
Assumptions:
    -- Handles title of any length
---------------------------------------------------------------------------*/
#ifndef TITLE
#define TITLE

#include <string>
#include <iostream>
using namespace std;

class Title {
public:
    Title(string);
    ~Title();

    void setTitle(string);
    string getTitle();

private:
    string titleFull;
    string titleShort;
    int test;

};

#endif

