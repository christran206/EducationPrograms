/////////////////////////////////////////////////////////////////////////////
// Fiction
//    Derives from Publication to conform to Publication data requirements
// Features:
//      -- Implements Operator<
//      -- Implements Operator==
// Assumptions:
//      -- Operator< checks author then title
/////////////////////////////////////////////////////////////////////////////
#ifndef FICTION
#define FICTION

#include <string>
#include <iostream>
#include "publication.h"

using namespace std;

// ----- DERIVED CLASS Publication -------------------------------------------

class Fiction : public Publication {

public:
	Fiction();          // default constructor, data is set to an empty string
	virtual ~Fiction();          

	virtual Fiction& operator=(const Publication &) ;

	virtual bool operator==(const Fiction &) const ;
	virtual bool operator<(const Fiction &) const ;


 private:
};
#endif