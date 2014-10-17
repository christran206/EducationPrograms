//---------------------------------------------------------------------------
/*  Children class:	Contains information on Children objects derived
					from Publication. Will implement the Operators
					differently

Features:
	-- allow users to compare to another children book with the equality operator
	-- allow users to compare to another children book with the less than operator
Assumptions:
	-- Must implements operator< and operator==
*/
//---------------------------------------------------------------------------
#ifndef CHILDREN
#define CHILDREN

#include <string>
#include <iostream>

#include "publication.h"


using namespace std;

// ----- DERIVED CLASS Publication -------------------------------------------

class Children : public Publication {

public:
	Children();          // default constructor, data is set to an empty string
	virtual ~Children();          

	virtual Children& operator=(const Publication &) ;
	virtual bool operator==(const Children &) const ;
	virtual bool operator<(const Children &) const ;

private:
};
#endif