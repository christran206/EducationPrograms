//
//  Account.cpp
//  lab5
//  Account implementation
//

#include "TransQueue.h"

//------------------------------------------------------------------------------
// Constructor
// 
TransQueue::TransQueue() {
}

//------------------------------------------------------------------------------
// Destructor
//
TransQueue::~TransQueue() {
	while(!isEmpty()) {
		tQueue.pop();
	}
}

//------------------------------------------------------------------------------
// getTransaction
// Return the first transaction in the queue
Transaction& TransQueue::getTransaction() {
	Transaction* temp = NULL;
	if(!isEmpty()) {
		temp = &tQueue.front();
		tQueue.pop();
	}
	return *temp;
}

//------------------------------------------------------------------------------
// addTransaction
// add a transaction to the queue
void TransQueue::addTransaction(Transaction TransToAdd) {
	tQueue.push(TransToAdd);
}

//------------------------------------------------------------------------------
// isEmpty
// check if queue is empty
bool TransQueue::isEmpty() const {
	return tQueue.empty();
}

//------------------------------------------------------------------------------
// size
// Return the size of the queue
int TransQueue::size() const {
	return tQueue.size();
}

//------------------------------------------------------------------------------
// showQueue
// display the queue of transactions
void TransQueue::showQueue() {
	queue<Transaction> tempQ;
	while(!tQueue.empty()) {
		Transaction tempT = tQueue.front();
		cout << tempT << endl;
		tempQ.push(tempT);
		tQueue.pop();
	}
	while(!tempQ.empty()) {
		tQueue.push(tempQ.front());
		tempQ.pop();
	}
}
