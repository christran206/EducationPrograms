#include "history.h"


History::History(Publication* pubIn,string actionIn) {
    action = actionIn;
    pub = pubIn;
}


History::~History(void)
{
}
//----------------------------------------------------------------------------
/*
operator<<

History objects only output the type of action and minimal details of the
publication
*/
ostream & operator<<(ostream& outstream, const History& input) {
    outstream << setw(12) << input.action;
    input.pub->display(false);
    return outstream;
}
