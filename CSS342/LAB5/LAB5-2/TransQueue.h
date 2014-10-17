//
// TransQueue.h
// lab5
// Transaction Queue class
//

#pragma once
#include <queue>
#include "Transaction.h"

//------------------------------ class TransQueue ------------------------------
//  Transaction class: stores the transactions to be made on each clients
//    account, with functionality:
//    -- add a transaction to the queue
//    -- check if the queue is empty
//    -- check how many transactions are in the queue
//    -- display the transaction queue
//
//  Assumptions:
//    -- Client IDs must be valid
//    -- Transactions must contain a transaction type, client ID, account number 
//       and transaction ammount.
//    -- Cannot withdraw a negative amount
//------------------------------------------------------------------------------

class TransQueue {
public:
	TransQueue();    // constructor
	~TransQueue();   // destructor
	Transaction& getTransaction();    // return a transaction
	void addTransaction(Transaction); // add a transaction to the queue
	bool isEmpty() const;             // check if queue is empty
	int size() const;                 // check size of queue
	void showQueue();                 // display the transaction queue
private:
	queue<Transaction> tQueue;    // queue of transactions
};


