//---------------------------------------------------------------------------
/*  PeriodicalDB class:	Contains a sorted list of Periodical Objects

Features:
	--Insert into class
	--Remove from class
	--Retrieve from class
Assumptions:
	--Periodical class implements operator< and operator==
	--Implements any type of container it wants to
*/
//---------------------------------------------------------------------------
#ifndef PERIODICAL
#define PERIODICAL

#include <string>
#include <iostream>
#include "publicationdb.h"
#include "bintree.h"
#include "periodical.h"

using namespace std;

class PeriodicalDB: public PublicationDB{

public:
   PeriodicalDB();          // default constructor, data is set to an empty string
   ~PeriodicalDB();
   virtual void insert(Periodical*);
   virtual void remove(Periodical*);
   virtual void retrieve(Periodical*, Periodical&);
private:
   BinTree PeriodicalList;


};
#endif