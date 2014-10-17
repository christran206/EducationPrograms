// -----------------------------------------------------------------------------
/*  Library class:	Instance Class, contains the primary classes
					and method calls to read data and process data

  The Library class contains four data members, which are a container for user
 patrons(PatronList class), the library curator(Librarian class), the factory
 pattern/process(Processors class), and a storage system in which books can be
 stored(Shelf class).
 
Features:
	-- Has a librarian to deal with transactions
	-- Has a bookshelf to keep track of books
	-- Has a processor to call for actions when there are commands
	-- Has a list to keep track of the patrons
Assumptions:
	-- A library must have all of the members (librarian, shelf, processor, patronlist)
	-- even when they are empty
*/
// -----------------------------------------------------------------------------

#ifndef LIBRARY
#define LIBRARY

#include "librarian.h"
#include "shelf.h"
#include "processor.h"
#include "patronlist.h"
#include <iostream>

class Library
{
public:
    Library();
    virtual ~Library(void);

    void buildShelf(ifstream&);
    void buildActions(ifstream&);
    void buildPatrons(ifstream&);
    void runLibrarian();
private:
	Librarian librarian;
	Shelf bookshelf;
	Processor* process;
	PatronList plist;
};

#endif /* defined(LIBRARY_) */
