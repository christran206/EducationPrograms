//
// ODAccount.h
// lab5
// Overdraft Account class
//

#pragma once
#include "Account.h"

//------------------------------ class ODAccount ------------------------------
//  ODAccount class: Inherited Account class for use with Money Market, 
//       Prime Money Market, Long-Term Bond, and Short-TermBond, with
//       additional functionality:
//    -- withdraw from account, with added functionality if an ODAccount has
//       insufficient funds, and its associated account has sufficient funds,
//       then funds will be withdrawn from its associated account instead
//
//  Assumptions:
//    -- funds must be greater than or equal to 0
//------------------------------------------------------------------------------

class ODAccount : public Account {
public:
	ODAccount(int balance,Account**); // constructor
	~ODAccount();                     // destructor

	virtual int withdraw(int);        // withdraw funds
private:
	Account **backupAcct;		      //Account to pull funds if overdrafting
};

