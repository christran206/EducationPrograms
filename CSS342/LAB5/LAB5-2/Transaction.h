//
//  Transaction.h
//  lab5
//  Transaction class
//

#pragma once
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//------------------------------ class Transaction -----------------------------
//  Transaction class: stores the transactions to be made on each clients
//    account, with functionality:
//    -- get the type of transaction
//    -- get the source account ID
//    -- get the destination account ID
//    -- get the amount of funds
//
//  Assumptions:
//    -- Client IDs must be valid
//    -- Transactions must contain a transaction type, client ID, account number 
//       and transaction ammount.
//    -- Cannot withdraw a negative amount
//------------------------------------------------------------------------------

class Transaction {

	friend ostream& operator<<(ostream &, const Transaction &);

public:
    Transaction(char = NULL, int = 0, int = 0, int = 0);      // Constructor
    ~Transaction();                        // Destructor

    char getTranType() const;              // return transaction type
    int getSourceAcct() const;             // return source account ID
    int getTargetAcct() const;                 // return destination account ID
    int getAmount() const;                 // return transaction amount
    
private:
    char transType;     // transaction type
    int sourceAcct;     // source account id
    int targetAcct;         // destination account id
    int amount;         // transaction amount
	string accountType(int) const;
};

