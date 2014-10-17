/////////////////////////////////////////////////////////////////////////////////////
// Action Factory Class
//	Virtual Class to describe and structure how librarian will execute Actions
//  Librarian will call this function using an appropriate parameter and
//  class will run the appropriate function class
//  
//	
// 
// Features:
//      -- To be used for parent function classes
//		-- Performs no action itself
// Assumptions:
//      -- Unable to instantiate the ActionFactory class directly.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef ACTIONFACTORY
#define ACTIONFACTORY

#include <string>
#include <iostream>
#include "action.h"

using namespace std;



class ActionFactory {
public:
    ActionFactory();
     ~ActionFactory();
	 virtual void perform(Action&) = 0;
};

#endif