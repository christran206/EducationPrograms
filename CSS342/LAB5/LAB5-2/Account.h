//
//  Account.h
//  lab5
//  Account class
//

#pragma once
#include <iostream>

using namespace std;

//------------------------------ class Account ---------------------------------
//  Account class: stores a monetary balance, starting and currnet, and provides 
//	basic functionality:
//    -- withdraw or deposit funds from account
//    -- clear an account's balance
//    -- retrieve an account's current balance
//    -- retrieve an accoutn's starting balance
//    -- check if account is empty
//    -- transfer funds between accounts
//
//  Assumptions:
//    -- balance cannot be negative (cannot overdraw)
//    -- cannot withdraw a negative amount
//    -- clearing an account sets the total funds to 0
//------------------------------------------------------------------------------

class Account {
public:
    Account(int balance = 0);       // constructor
    ~Account();                     // destructor
    
    bool deposit(int);              // make a deposit
    virtual int withdraw(int);              // withdraw from account
    void clearAcct();               // empty account
    int getBalance() const;         // get balance
	int getStartBal() const;
    bool isEmpty() const;           // see if account is empty
    bool transferFunds(Account& acct, int); // transfer between account

protected:
    int startingBal;         // account's starting amount
    int currentBal;          // account's end of transaction amount
};
