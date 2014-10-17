//
//  firm.h
//  lab5
//  Firm class
//

#pragma once
#include <iostream>
#include "ClientList.h"
#include "QueueProcessor.h"

using namespace std;

//------------------------------ class Firm ---------------------------------
//  Firm class: contains a binary search tree of pointers to clients sorted
//    by id number, with additional features:
//    -- build the list of clients from a text file
//    -- display all clients within the firm
//    -- retrieve a clients transaction history
//    -- display the firm's end-of-day transaction history
//    -- deposit funds to a client's account
//    -- withdraw funds from a client's account
//    -- move funds from one account to another
//
//  Assumptions:
//    -- A firm can hold 0 to multiple clients (cannot have negative Clients)
//    -- Clients are placed in a binary search tree, sorted by ID
//    -- Each client must have a last name, first name, 4 digit ID, and all
//       ten accoutns set to a minimum of 0
//---------------------------------------------------------------------------

class Firm {

public:
	Firm();    // constructor
	~Firm();   // destructor
	
	void buildClientList(ifstream& infile);    // read in client data
	void displayClients() const;               // display a firms clients
    void displayEOD() const;             // display firm transaction history
    void getClientHistory(const Client) const; // get client account history
    bool depositToAccount(int acct, int amt);  // deposit to client's account

	// withdraw from a clients account
    int withdrawFromAccount(int acct, int amt); 
    bool sendToProcessor(ifstream& infile);    // load processor from file
    bool moveFunds(int, int, int);       // transfer funds between accounts 
   
private:
    ClientList* clients;           // tree of clients
    QueueProcessor* qProcessor;    // processor
};

