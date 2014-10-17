
// -----------------------------------------------------------------------------
/*  CheckIn Function class: Takes an Action Object that contains information
 on checking in a Publication and performs
 the CheckIn Action
 Features:
   --perform a check in action
 Assumptions:
    -- data from the list are all valid
    -- invalid data are checked and ignored while reading off file
    -- the list is empty by default */
// -----------------------------------------------------------------------------

#ifndef __Lab4__checkIn__
#define __Lab4__checkIn__

#include "actionfactory.h"

class CheckIn:public ActionFactory {
    
public:
    CheckIn();
    ~CheckIn();
    
    void perform(Action&);
    
private:
    void checkIn(Publication&);
};

#endif /* defined(__Lab4__checkIn__) */
