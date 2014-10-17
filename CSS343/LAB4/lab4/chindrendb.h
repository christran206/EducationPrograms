//---------------------------------------------------------------------------
/*  ChildrenDB class:	Container Class that derives from PublicationDB
						Implemented specifically to store Children type of
						Publications

Features:
	-- allows user to insert in a book
	-- allows user to remove a book
    -- allows user to retreive a book
Assumptions:
	-- Children class implements operator< and operator==
*/
//---------------------------------------------------------------------------
#ifndef CHILDRENDB
#define CHILDRENNDB



#include <string>
#include <iostream>
#include "publicationdb.h"
#include "bintree.h"
#include "children.h"

using namespace std;

// ----- DERIVED CLASS Apple -------------------------------------------------

class ChildrenDB : public PublicationDB {

public:
   ChildrenDB();          // default constructor, data is set to an empty string
   virtual ~ChildrenDB();

   virtual void insert(Children*);
   virtual void remove(Children*);
   virtual void retrieve(Children*, Children&);
private:
	BinTree ChildrensBooks;
};
#endif