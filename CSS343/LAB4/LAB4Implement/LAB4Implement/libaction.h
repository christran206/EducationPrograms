#ifndef LIBACTION_H
#define LIBACTION_H
#include "publication.h"
#include "patron.h"
#include <map>
/*---------------------------------------------------------------------------
LibAction
Interface class for creating objects for a Factory Constructor. LibAction
objects will be used by the librarian to act upon a patron and an
associated publication

Features:
	--All child classes implement a perform action
Assumptions:
	--
---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
class LibAction{
public:

    virtual void perform(Patron& pat, Publication& pub) = 0;
private:
    map<char,LibAction*> actionMap;
};

//---------------------------------------------------------------------------
//HistoryDisplay Class
/*
Assumptions
History will provide an error if patron has no history
*/
class HistoryDisplay : public LibAction {
public:
    void perform(Patron&, Publication&);
};

//---------------------------------------------------------------------------
//CheckOut Class
/*
Assumptions
Unable to checkout a book if there are no more left

*/
class CheckOut : public LibAction {
public:
    void perform(Patron&, Publication&);
};

//---------------------------------------------------------------------------
//CheckIn Class
/*
Assumptions
Unable to check in a book if patron did not check it out
*/
class CheckIn : public LibAction {
public:
    void perform(Patron&, Publication&);
};

#endif
