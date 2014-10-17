//
//  Transaction.cpp
//  lab5
//  Transaction implementation
//

#include "Transaction.h"

//------------------------------------------------------------------------------
// Constructor
// 
Transaction::Transaction(char type, int dest, int value, int source) {
	transType = type;
	sourceAcct = source;
	targetAcct = dest;
	amount = value;
}

//------------------------------------------------------------------------------
// Destructor
// 
Transaction::~Transaction() {
}

//------------------------------------------------------------------------------
// getTranType
// Return the character for the transaction type
char Transaction::getTranType() const {
	return transType;
}

//------------------------------------------------------------------------------
// getSourceAcct
// Return the digit of the source account
int Transaction::getSourceAcct() const {
	return sourceAcct;
}


int Transaction::getTargetAcct() const {
	return targetAcct;
}

//------------------------------------------------------------------------------
// getAmount
// Return the amount of funds
int Transaction::getAmount() const {
	return amount;
}

//------------------------------------------------------------------------------
// operator <<
// overloaded operator to display transactions
ostream& operator<<(ostream& output, const Transaction& T) {
	switch (T.transType)
	{
	case 'H':
		output << setw(9) << left << "History";
		break;
	case 'D':
		output << setw(9) << left << "Deposit" << " $" << setw(6) << right 
			<< T.amount << " into " << T.accountType(T.targetAcct) << " fund";
		break;
	case 'W':
		output << setw(9) << left << "Withdraw" << " $" << setw(6) << right 
			<< T.amount << " from " << T.accountType(T.targetAcct) << " fund";
		break;
	case 'M':
		output << setw(9) << left << "Move" << " $" << setw(6) << right 
			<< T.amount << " from " << T.accountType(T.targetAcct) 
			<< " fund" << endl
			<< setw(18) << " " << "to " << T.accountType(T.sourceAcct) 
			<< " fund for client " << T.sourceAcct/10;
		break;
	default:
		break;
	}
	return output;
}

//------------------------------------------------------------------------------
// accountType
// Returns the full name of the account type
string Transaction::accountType(int account) const {
	switch (account%10) {
	case 0:
		return "Money Market";
	case 1:
		return "Prime Money Market";
	case 2:
		return "Long-Term Bond";
	case 3:
		return "Short-Term Bond";
	case 4:
		return "500 Index Fund ";
	case 5:
		return "Capital Value Fund";
	case 6:
		return "Growth Equity Fund";
	case 7:
		return "Growth Index Fund";
	case 8:
		return "Value Fund";
	case 9:
		return "Value Stock Index";
	default:
		return "";
	}
}
