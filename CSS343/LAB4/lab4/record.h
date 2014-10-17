///////////////////////////////////////////////////////////////////////////////
// Record
//    Detail of information on the checkout and return history
// Features:
//      -- Displays the record details as a string
// Assumptions:
//     --Can be modified in the future and changes contained in class
///////////////////////////////////////////////////////////////////////////////
#ifndef RECORDS
#define RECORDS

#include <string>
#include <iostream>
using namespace std;



class Record {
public:
    Record();
     ~Record();

private:
	string historyRecord;
};

#endif