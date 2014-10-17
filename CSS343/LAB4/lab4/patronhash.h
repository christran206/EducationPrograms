//---------------------------------------------------------------------------
/*  PatronHash class:	Stores Patrons in a Hashmap. Class takes in Patron
						and creates a hash based on ID, in the case
						of collisions names will be used to hash again
Features:
	-- allow users to insert a patron
	-- allow users to remove a patron
	-- allow users to retreive a patron
Assumptions:
	-- a Patron is uniquely identify by its ID
*/   
//---------------------------------------------------------------------------
#include "patron.h"
#include <vector>

class PatronHash {
public:
	PatronHash ();
	~PatronHash ();

	bool insert(Patron*);
	bool remove(Patron&);
	bool retrieve(Patron*, Patron&);
private:
	vector<Patron> PatronList;
	int primeNumbers[];
};
