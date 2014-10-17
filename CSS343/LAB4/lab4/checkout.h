/////////////////////////////////////////////////////////////////////////////////////
// CheckOut Function Class
// Acts upon the shelf class to check out a book of the type requested by parameter
// Inherit from the class actionProcessor
// Features:
//      -- has no function to itself
// Assumptions:
//      -- data from the list are all valid
//      -- invalid data are checked and ignored while reading off file
//      -- the list is empty by default
/////////////////////////////////////////////////////////////////////////////////////
#ifndef CHECKOUT
#define CHECKOUT

#include <iostream>
#include "actionfactory.h"
#include "action.h"

using namespace std;


class CheckOut : public ActionFactory {
public:
    CheckOut();
     ~CheckOut();
	 
     void perform(Action&);
};

#endif