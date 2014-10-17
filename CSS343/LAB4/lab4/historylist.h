/////////////////////////////////////////////////////////////////////////////
// HistoryList
//    Class that contains records in the order they are added
//      to represent a history of records in chronological order
//    Example: Checkouts, Returns
// Features:
//      -- allow users to display the history of transactions
//      -- has a queue to store and display the history in order of time
// Assumptions:
//      -- operator<< must be implemented
/////////////////////////////////////////////////////////////////////////////
#include "record.h"
#include <queue>

class HistoryList {
       friend ostream & operator<<(ostream &, const HistoryList &);

public:
    HistoryList();
    ~HistoryList();

private:
    queue<Record> Records;
};