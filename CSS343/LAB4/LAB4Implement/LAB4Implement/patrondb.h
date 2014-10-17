#ifndef PATRONDB_H
#define PATRONDB_H
#include "patron.h"
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
/*---------------------------------------------------------------------------
PatronDB Class
Container for all patrons

Features:
	-Inserting a patron
	-Retrieving a patron by patron object, name, and ID
	-Displays all patrons
Assumptions:
	-patrons not required to be stored in sorted order
	-Patrons will have unique IDs, no duoplicate ID numbers
---------------------------------------------------------------------------*/
using namespace std;
class PatronDB
{
public:
    PatronDB();
    ~PatronDB();

    bool insert(Patron*);	//Insert a patron
    Patron* retrieve(Patron&);//Retrieve patron by similar object
    void build(ifstream&);//Build patronDB with file
    Patron* retrieve(string);//Retrieve patron by name
    Patron* retrieve(int);//Retrieve patron by ID
    void display();//Display all patrons in PatronDB class
private:
    map<int,Patron*> patrons;//STL Map containing patrons
};
#endif
