#include "libaction.h"
//----------------------------------------------------------------------------
/*
perform Virtual Function
For the checkin function, there will be a check to determine if the Patron
has a publication in possession to check back in
*/
void CheckIn::perform(Patron& pat, Publication& pub) {
	//Check if the patron has the book checked out
	if(pat.removeFromChecked(&pub)) {
		pub.checkIn(); //Checks in the book
		pat.addToHistory("Return", &pub); //Adds instance to patron history
	} else {
		cout << "Unable to CheckIn or return Book" << endl;
	}
}
