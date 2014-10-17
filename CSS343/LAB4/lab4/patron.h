//---------------------------------------------------------------------------
/*  Patron class:	Contains information and functions to retrieve info
					on a Patron
					Information Stored
					-Patron ID
					-Information on Patron in container class
					-Information on a Patrons Library History
					-Current Checked out books
Features:
	-- a patron can keep its record of activity(checkin, checkout)
	-- a patron can keep track of the pubications that it checks out

Assumptions:
	-- ID and patron's info is correct, invalid data is checked and ignored at file reading
*/   
//---------------------------------------------------------------------------
#ifndef PATRON
#define PATRON

#include <string>
#include <iostream>
#include "historylist.h"
#include "aboutpatron.h"
#include "checkedoutlist.h"

using namespace std;



class Patron {

   friend ostream & operator<<(ostream &, const Patron &);

public:
	Patron();          // default constructor, data is set to an empty string
	~Patron();          

	//Functions to set and get Patron Details
	bool Patron::operator==(Patron&);
    void setID(int);
    int getID();
    void setName(string, string);
    void getName();
    void addToHistory(string);
    void getHistory();
    void addToCheckedOut(Publication&);
    void getCheckedOut();

private:

    int ID ;
	AboutPatron aboutThisPatron;
	HistoryList historyOfThisPatron;
	CheckedOutList COutList;


};
#endif

