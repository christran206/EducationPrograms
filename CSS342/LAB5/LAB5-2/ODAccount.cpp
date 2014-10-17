//
//  ODAccount.cpp
//  lab5
//  Overdraft Account implementation
//


#include "ODAccount.h"

//------------------------------------------------------------------------------
// Constructor
// 
ODAccount::ODAccount(int balance,Account **backA):Account(balance) {
	backupAcct = backA;
}

//------------------------------------------------------------------------------
// Destructor
// 
ODAccount::~ODAccount() {
	backupAcct = NULL;
}

//------------------------------------------------------------------------------
// withdraw
// withdraw an amount from an overdraft type account
// Return the amount withdrawn, or -1 if both accounts contain insufficient
// funds, or amount is less than 0
int ODAccount::withdraw(int amount) {
	if(amount > currentBal) {
		int neededAmount = amount - currentBal;
		if(neededAmount > (*backupAcct)->getBalance()) {
			return -1;
		} else {
			this->deposit((*backupAcct)->withdraw(neededAmount));
		}
	}
	currentBal -= amount;
	return amount;
}
