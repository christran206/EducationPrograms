//---------------------------------------------------------------------------
/*  PatronList class:	Container for the Patrons in any type of data
						structure but will use a custom hash map
Features:
	-- add a new Patron into the hash
	-- remove a Patron fron the hash
	-- retrive a patron from the hash
Assumptions:
	--  PatronHash must have add, remove, and retreive functions
*/   
//---------------------------------------------------------------------------
#include "patron.h"
#include "patronhash.h";
class PatronList {

public:
    PatronList();
    ~PatronList();

    void add(Patron&);
    void remove(Patron&);
    void retrieve(Patron&);

private:
	PatronHash PatList;
};