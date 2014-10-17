#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include <fstream>
#include <string>
#include <iostream>
#include "libactionfactory.h"
#include "shelf.h"
#include "patrondb.h"
/*---------------------------------------------------------------------------
Librarian
Manager Style Class
Class is responsible for accessing and performing the actions needed.
Actions are stored in a text file and are processed as they are recognized.

Features:
	--takes in a text file containing properly formatted actions.
Assumptions:
	--Invalid actions are ignored
---------------------------------------------------------------------------*/
using namespace std;
class Librarian {
public:
	Librarian(Shelf&,PatronDB&);
	~Librarian();

    void processActions(ifstream&); //read text file and process
private:
    LibAction* lAction;		//
    Shelf* shelf;
    PatronDB* pdb;
    LibActionFactory laf;
};
#endif
