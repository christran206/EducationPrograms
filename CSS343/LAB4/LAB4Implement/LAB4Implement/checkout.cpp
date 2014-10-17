#include "libaction.h"
//----------------------------------------------------------------------------
/*
perform Virtual Function

For the Checkout function, we determine if the publication can still
be checked out before adding it to the patrons history and checkout list
*/
void CheckOut::perform(Patron& pat, Publication& pub) {
	//Function to checkout and return bool result
	if(pub.checkOut()) {
		pat.addToChecked(&pub);
		pat.addToHistory("Checked Out", &pub);
	} else {
		cout << "Unable to checkout publication" << endl;
	}
}
