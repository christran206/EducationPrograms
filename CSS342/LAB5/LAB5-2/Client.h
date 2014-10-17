//
//  client.h
//  lab5
//  Client class
//

#pragma once
#include <iostream>
#include "Account.h"
#include "Owner.h"
#include "ClientHistory.h"

using namespace std;

//------------------------------ class Client ----------------------------------
//  Client class: contains all firm-related information of a client such as
//    ID, accounts, transaction history, with the following features:
//    -- get a client's ID
//    -- get a client's transaction history
//    -- deposit funds to a specific account
//    -- withdraw funds from a specific account
//    -- retrieve an account's owner information
//    -- add a transaction to history
//    -- comparison operator overloads (>, <, ==)
//
//  Assumptions:
//    -- IDs must be 4 digits
//    -- deposit or withdrawal amount cannot be less than 0
//------------------------------------------------------------------------------

enum acctType {
	MM,
	PMM,
	LTB,
	STB,
	IF500,
	CVF,
	GEF,
	GIF,
	VF,
	VSI,
	FINAL_acct_ENTRY
};
class Client {
	friend ostream& operator<<(ostream &, const Client &);
public:
	Client(string,string,int, int, int, int, int, int, int, int, int, int, int);
	virtual ~Client();

	int getID() const;                     // get client ID
    void getHistory() const;               // display history
    bool depositToAccount(int, int);       // deposit to a specified account
    int widthdrawlFromAccount(int, int);   // withdraw from a specified account
    bool operator>(const Client&) const;   // compares for greater ID
    bool operator<(const Client&) const;   // compares for lesser ID
    bool operator==(const Client&) const;  // compares for equal ID
	void addToHistory(Transaction);
    
private:
    int ID;                       // client ID number
    Account* accounts[FINAL_acct_ENTRY];   // array of account pointers
    Owner* owner;                  // owner information
	ClientHistory* cHistory;

};

