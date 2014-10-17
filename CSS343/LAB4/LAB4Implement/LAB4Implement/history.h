#ifndef HISTORY_H
#define HISTORY_H
#include <string>
#include "publication.h"
/*---------------------------------------------------------------------------
History Class
Contains a record of an action associated with a publication

Features:
	--Implements output operator<<
Assumptions:
	--Data record does not change
---------------------------------------------------------------------------*/
using namespace std;
class History {
    friend ostream & operator<<(ostream &, const History &);
public:
    History(Publication*, string);
    ~History();
private:
    string action;		//Action of the task
    Publication* pub;	//Publication acted upon
};
#endif
