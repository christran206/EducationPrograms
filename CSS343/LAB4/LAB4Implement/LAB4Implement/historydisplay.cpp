#include "libaction.h"
//----------------------------------------------------------------------------
/*
perform virtual function

For HistoryDisplay, we are only interested in displaying the patrons history
Patron has already implemented such functionality.
*/
void HistoryDisplay::perform(Patron& pat, Publication& pub) {
	pat.displayHistory();
}
