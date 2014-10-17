//
//  Client.cpp
//  lab5
//  Client implementation
//

#include "Client.h"
#include "Account.h"
#include "ODAccount.h"
#include <iomanip>


//------------------------------------------------------------------------------
// Constructor
// create a client and all of their accounts and history of transactions
Client::Client(string last, string first,int id, int mm, int pmm, int ltb, 
			int stb, int if500, int cvf, int gef, int gif, int vf, int vsi) {
	ID = id;
	owner = new Owner(last, first);
	cHistory = new ClientHistory();
	//ODAccounts take a reference to the pointer of the backup account
	accounts[MM] = new ODAccount(mm,&accounts[PMM]);
	accounts[PMM] = new ODAccount(pmm,&accounts[MM]);
	accounts[LTB] = new ODAccount(ltb,&accounts[STB]);
	accounts[STB] = new ODAccount(stb,&accounts[LTB]);
	accounts[IF500] = new Account(if500);
	accounts[CVF] = new Account(cvf);
	accounts[GEF] = new Account(gef);
	accounts[GIF] = new Account(gif);
	accounts[VF] = new Account(vf);
	accounts[VSI] = new Account(vsi);

	
}

//------------------------------------------------------------------------------
// Destructor
// deallocate memory from client
Client::~Client() {
	delete owner;
	for(int i = 0; i < FINAL_acct_ENTRY; i++) {
		delete accounts[i];
	}
	delete cHistory;
}

//------------------------------------------------------------------------------
// getID
// Returns the clients ID
int Client::getID() const {
	return ID;
}
//------------------------------------------------------------------------------
// getHistory
// display the history of transactions
void Client::getHistory() const {
	cout << "History of trancactions for client " << owner->getFirstName() 
		<< " " << owner->getLastName() << ", client ID = " << ID << endl;
	cHistory->displayHistory();
	cout << endl;
}
//------------------------------------------------------------------------------
// getOwner
// retrieve clients information
/*void Client::getOwner() const {
	cout << *owner;
}*/
//------------------------------------------------------------------------------
// operator >
//
bool Client::operator>( const Client& compareTo) const {
	return ID > compareTo.ID;
}
//------------------------------------------------------------------------------
// operator <
//
bool Client::operator<(const Client& compareTo) const {
	return ID < compareTo.ID;
}
//------------------------------------------------------------------------------
// operator ==
//
bool Client::operator==(const Client& compareTo) const {
	return ID == compareTo.ID;
}

//------------------------------------------------------------------------------
// addToHistory
// add a transaction to the history
void Client::addToHistory(Transaction tIn) {
	cHistory->addToHistory(tIn);
}

//------------------------------------------------------------------------------
// depositToAccount
// deposit an amount into a clients account
bool Client::depositToAccount(int amount, int account) {
	return accounts[account%10]->deposit(amount);
}

//------------------------------------------------------------------------------
// withdrawFromAccount
// withdraw funds from a clients account
int Client::widthdrawlFromAccount(int amount, int account) {
	return accounts[account%10]->withdraw(amount);
}

//------------------------------------------------------------------------------
// operator <<
// overload to output a client's acconts starting and current balance
ostream& operator<<(ostream& output, const Client& T) {
	output << setw(5) << left << T.ID << " " << T.owner->getFirstName() 
			<< " " << T.owner->getLastName() <<endl;
	output << setw(18) << left << "Initial Balances: ";
	for(int i = 0; i < FINAL_acct_ENTRY; i++) {
		output << setw(6) << right << T.accounts[i]->getStartBal();
	}
	output << endl;
	output << setw(18) << left << "Final Balances: ";
		for(int i = 0; i < FINAL_acct_ENTRY; i++) {
		output << setw(6) << right << T.accounts[i]->getBalance();
	}
	output << endl;
	return output;
}
