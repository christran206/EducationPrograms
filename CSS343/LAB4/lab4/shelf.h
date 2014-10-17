//---------------------------------------------------------------------------
/*  Shelf class:	Container of the different kinds of PublicationDB
					classes.
Features:
    -- insert a book into sprcific database
	-- retrive an book from publication database in the list
Assumptions:
	-- for this project, theShelfInTheLibrary only holds 3 type of 
	   publication database
*/   
//---------------------------------------------------------------------------
#ifndef SHELF	
#define SHELF

#include <string>
#include <iostream>
#include <list>
#include "publicationDB.h"
#include "publication.h"
using namespace std;



class Shelf {
public:
    Shelf();
     ~Shelf();

	 Publication& getTheBookFromTheShelf(Action&); // retrive a target book
	 bool insert(Publication*);  // insert a book to correct DB
private:
	// holds different type of publications database
	 list<PublicationDB> theShelfInTheLibrary; 
	 

};

#endif

