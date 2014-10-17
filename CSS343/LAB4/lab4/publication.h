//---------------------------------------------------------------------------
/*  Publication class:	Pure Virtual class that describes the information
						on a publication intended to be extended
Features:
	--Displays details on publication
	--Displays information with output<<
	-- allow users to compare to another publication with the equality operator
	-- allow users to compare to another publication with the less than operator
Assumptions:
	--Must implements operator< and operator==
*/
//---------------------------------------------------------------------------
#ifndef PUBLICATION
#define PUBLICATION

#include <string>
#include <iostream>
#include "title.h"
#include "author.h"
#include "date.h"
#include "publicationtype.h"
#include "edition.h"

using namespace std;

class Publication {

   friend ostream & operator<<(ostream &, const Publication &);

public:
	Publication();          // default constructor, data is set to an empty string
	virtual ~Publication()= 0;          

	virtual Publication& operator=(const Publication &) = 0;
	virtual bool operator==(const Publication &) const = 0;
	virtual bool operator<(const Publication &) const = 0;
    //Functions to set private variables

protected:

    Title pubTitle;
	Author pubAuthor; 
	Date pubDate;
	PublicationType pubType;
    Edition pubEdition;
	int quatity;


};

#endif
