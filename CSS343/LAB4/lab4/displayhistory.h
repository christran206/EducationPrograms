//---------------------------------------------------------------------------
/*  DisplayHistory Function class:	Takes in an Action object that contains
									Patron information and retrives
									Patrons History
Features:
	-- this calls to display the history of transactions
Assumptions:
	-- must implement perform fuction
*/   
//---------------------------------------------------------------------------
#include "actionfactory.h"
class DisplayHistory: public ActionFactory {
	DisplayHistory();
	~DisplayHistory();
public:
	void perform(Action&);
}