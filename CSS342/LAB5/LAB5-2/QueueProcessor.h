#pragma once
#include "TransQueue.h"
#include "ClientList.h"
#include <fstream>
#include <string>
//
// QueueProcessor.h
// lab5
// Queue Processor class
//

using namespace std;

//------------------------------ class QueueProcessor --------------------------
//  QueueuProcessor class: Queue class to build, process, and display the queue
//       of transactions, with functionality:
//    -- build the queue of transactions
//    -- process the transactions
//    -- display the queue of transactions
//    -- helper functions for withdraw, deposit, move and show transaction
//       history
//
//  Assumptions:
//    -- Client IDs must be a valid 4 digit number
//    -- Transactions must contain a transaction type, client ID, account number 
//       and transaction ammount.
//    -- Cannot withdraw, deposit, or move a negative amount
//------------------------------------------------------------------------------

class QueueProcessor
{
public:
	QueueProcessor();     // constructor
	~QueueProcessor();    // destructor
	void buildQueue(ifstream&);  // build the queue of transactions
	void runQueue(ClientList&);  // process the queue of transactions
	void displayQueue() ;        // display the queue of transactions

private:
	TransQueue transQ;         // queue of transactions
	void withdrawalHelper(Client&, Transaction);
	void depositHelper(Client&, Transaction);
	void moveHelper(Client&, Client&, Transaction);
	void showHistoryHelper(Client&, Transaction);
	string accountType(int);  // full name of accounts
};

