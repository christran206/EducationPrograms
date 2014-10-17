//
//  ClientHistory.h
//  lab5
//  Client History class
//

#pragma once
#include "Transaction.h"
#include <queue>
#include <iomanip>

//------------------------------ class ClientHistory ---------------------------
//  ClientHistory class: Holds client's history in a queue, with additional
//    functionality:
//    -- add a transaction to the queue
//    -- display the transaction history
//
//  Assumptions:
//    -- a transaction contains type of transaction, client's ID, account type,
//       amount, and destination, if applicable
//------------------------------------------------------------------------------

class ClientHistory {
	friend ostream& operator<<(ostream &, const ClientHistory &);
public:
	ClientHistory();    // constructor
	~ClientHistory();   // destructor
	void addToHistory(const Transaction&);  // add trans to client's history
	void displayHistory() ;                 // display the transaction history
private:
    queue<Transaction> history;   // history queue
};

