#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <iostream>
#include <iomanip>
#include <deque>
#include <list>
#include "history.h"
#include "publication.h"
/*---------------------------------------------------------------------------
Patron Class
Patron is a class representing a physical person and their interests
in the library. These interest include knowing what publications are checked
out in addition to a history representing the users record with the library

Features:
	--Displays users history
	--Implementation to add to the users history
	--Implementation to add to a users list of checked out publications
	--Implementation to remove a checked out publication
	--Retrieve the patrons ID
Assumptions:
	--Checked out record to keep track of books that can be turned in.
	--Name is stored with first and laast name separate in even names
	are presented first name then last name or vise versa.
	--Unable to check in a book that is not checked out
---------------------------------------------------------------------------*/
using namespace std;

class Patron
{
    friend ostream & operator<<(ostream &, const Patron &);
public:
    Patron(int, string, string);
    ~Patron();

    void displayHistory();	//Show users history
    void addToHistory(string, Publication*);//Add to users history
	void addToChecked(Publication*);//Add to checked out publications
	bool removeFromChecked(Publication*);//remove from checked out publications
    int getID();	//retrieves patrons ID
    string getName();	//retrives patrons name
	bool operator==(const Patron&) const;	//If two patrons are the same
private:
    int pid;	//Patron int ID
    string firstName;	//Patron First Name
    string lastName;	//Patron Last Name
    deque<History> histlist;	//History of Patron
	list<Publication*> currentChecked;//Currently checked out pubs
};
#endif
