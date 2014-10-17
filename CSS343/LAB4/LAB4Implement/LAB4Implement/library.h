#ifndef LIBRARY_H
#define LIBRARY_H
#include "librarian.h"
/*---------------------------------------------------------------------------
Library Class
Integration Class

Features:

Assumptions:

---------------------------------------------------------------------------*/
class Library
{
public:
	Library();
	~Library();

    void buildPatron(ifstream&);
    void buildShelf(ifstream&);
    void doAction(ifstream&);
private:
    Shelf bookshelf;
	PatronDB pdb;
    Librarian* librarian;
};
#endif
