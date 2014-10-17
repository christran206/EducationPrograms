/////////////////////////////////////////////////////////////////////////////
// FictionDB
//    Derives from PublicationDB
//    Inside its own class to have ability to change container type without
//    Affecting external classes
// Features:
//      -- allows user to insert in a book
//      -- allows user to remove a book
//      -- allows user to retreive a book
// Assumptions:
//      -- Fiction class implements operator< and operator==
/////////////////////////////////////////////////////////////////////////////
#ifndef FICTIONDB
#define FICTIONDB

#include <string>
#include <iostream>
#include "publicationdb.h"
#include "fiction.h"
#include "bintree.h"

using namespace std;

// ----- DERIVED CLASS PublicationDB ----------------------------------------

class FictionDB : public PublicationDB {

public:
   FictionDB();          // default constructor, data is set to an empty string
   virtual ~FictionDB();     

   virtual void insert(Fiction*);
   virtual void remove(Fiction*);
   virtual void retrieve(Fiction*, Fiction&);
private:
	BinTree FictionBooks;
};
#endif