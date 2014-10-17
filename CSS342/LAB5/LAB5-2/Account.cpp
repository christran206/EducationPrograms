//
//  Account.cpp
//  lab5
//  Account implementation
//

#include "Account.h"

//------------------------------------------------------------------------------
// Constructor
// sets the current balance to the starting balance from text file
Account::Account(int balance) {

	currentBal = startingBal = balance;
}
//------------------------------------------------------------------------------
// Destructor
// assumption: All primitive memory, no custom destructor needed
Account::~Account() {
}
//------------------------------------------------------------------------------
// deposit
// deposit an amount into the account
// Return true if deposit was successful
bool Account::deposit(int amount) {
	if(amount >= 0) {
		currentBal += amount;
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
// withdraw
// withdraw an amount from the account
// Returns the amount, or -1 if amount is greater than account balance
int Account::withdraw(int amount) {
	if(amount <= currentBal) {
		currentBal -= amount;
		return amount;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
// clearAcct
// clears an accounts funds, setting it to 0
void Account::clearAcct() {
	currentBal = 0;
}

//------------------------------------------------------------------------------
// getBalance
// retrieve the current balance of the account
// Returns the amount
int Account::getBalance() const {
	return currentBal;
}

//------------------------------------------------------------------------------
// getStartBal
// retrieve the starting balance of the account
// Returns the amount
int Account::getStartBal() const {
	return startingBal;
}

//------------------------------------------------------------------------------
// isEmpty
// check if the account has 0 funds
// Returns true if empty
bool Account::isEmpty() const {
	return currentBal > 0;
}

//------------------------------------------------------------------------------
// transferFunds
// transfer funds from one account to another
// Returns true if successful
bool Account::transferFunds (Account& acct, int amount) {
	return acct.deposit(withdraw(amount));
}
