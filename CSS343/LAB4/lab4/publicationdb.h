//---------------------------------------------------------------------------
/*  PublicationDB class:	Pure Virtual class used as a type of interface
							for Publication types to implement common
							function calls. Child Classes provide their
							own containers
Features:
	--Insert into class
	--Remove from class
	--Retrieve from class
Assumptions:
	--Publication class implements operator< and operator==
*/   
//---------------------------------------------------------------------------
#ifndef PUBLICATIONDB
#define PUBLICATIONDB

#include <string>
#include <iostream>
#include "bintree.h"
#include "publication.h"

using namespace std;

class PublicationDB {

public:
   PublicationDB();          
   ~PublicationDB();
   virtual void insert(Publication*) = 0;
   virtual void remove(Publication*) = 0;
   virtual void retrieve(Publication*, Publication&) = 0;


};

#endif
