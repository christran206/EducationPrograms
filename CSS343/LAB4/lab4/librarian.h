//---------------------------------------------------------------------------
/*  Librarian class:	Manager Type class that retrieves Action objects and
						determines the apprpriate actions to take
						to complete the parameters in the Action object

Features:
	--
Assumptions:
	--
*/
//---------------------------------------------------------------------------
#ifndef LIBRARIAN
#define LIBRARIAN

#include <string>
#include <iostream>
#include <queue>
#include "actionlist.h"
#include "actionfactory.h"
#include "shelf.h"

using namespace std;

class Librarian {
public:
	Librarian(ActionFactory&, ActionList&, Shelf&);
	~Librarian();

	void doAllTheAction();

private:

	ActionFactory *theFactory;
	ActionList librarianTasks;
	Shelf* PubSource;

	 
};

#endif