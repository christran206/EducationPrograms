//---------------------------------------------------------------------------
/*  CheckOutList class:	Contains container of pointers to Publication objects
                        that the patron has possession of.
Features:
	--Adding a Publication to the container
    --Removing a Publication from the container
    --Displaying Contents of Container
Assumptions:
	--Container in it's class to have ability to change data Structure
        without breaking contracts\features expected
*/   
//---------------------------------------------------------------------------
#include "publication.h"
#include <list>

class CheckedOutList {
    CheckedOutList();
    ~CheckedOutList();

    void add(Publication*);
    bool remove(Publication&);
    void display();

private:
    list<Publication*> ChOutList;
};