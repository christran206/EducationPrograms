//---------------------------------------------------------------------------
/*  Periodical class:	Contains information of periodicals such as
						Title and Date(Year, Month)

Features:
	--Displays information with the output operator<<
	--Implements comparison operator<
	--Implements 
Assumptions:
	--All child classes must implement the operator functions based on their
		own specifications
*/
//---------------------------------------------------------------------------
#ifndef PERIODICAL
#define PERIODICAL

#include <string>
#include <iostream>
#include "publication.h"

using namespace std;

// ----- DERIVED CLASS Apple -------------------------------------------------

class Periodical : public Publication {

public:
	Periodical();          // default constructor, data is set to an empty string
	~Periodical();          

	virtual Periodical& operator=(const Publication &) ;
	virtual bool operator==(const Periodical &) const ;
	virtual bool operator<(const Periodical &) const ;

	
 private:
	


    
};


#endif
