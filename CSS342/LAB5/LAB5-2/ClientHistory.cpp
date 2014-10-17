//
//  ClientHistory.cpp
//  lab5
//  Client History implementation
//

#include "ClientHistory.h"

//------------------------------------------------------------------------------
// Constructor
// 
ClientHistory::ClientHistory() {
}


ClientHistory::~ClientHistory() {

}

//------------------------------------------------------------------------------
// addToHistory
// add a transaction to the history
void ClientHistory::addToHistory(const Transaction& trans) {
	history.push(trans);
}

//------------------------------------------------------------------------------
// displayHistory
// display the history of transactions
void ClientHistory::displayHistory()  {
	queue<Transaction> tempQ;
	cout << setw(9) << left << "Type" << " " << setw(7) << "Amount" 
			<< " " << "Detail" << endl;
	cout << setw(9) << left << "---------" << " " << setw(7) << "-------" 
			<< " " << "--------------------------------------" << endl;
	while(!history.empty()) {
		Transaction tempT = history.front();
		cout << tempT << endl;
		tempQ.push(tempT);
		history.pop();
	}
	while(!tempQ.empty()) {
		history.push(tempQ.front());
		tempQ.pop();
	}
}

//------------------------------------------------------------------------------
// operator <<
// 
ostream& operator<<(ostream& output, const ClientHistory& T) {
	return output;
}
