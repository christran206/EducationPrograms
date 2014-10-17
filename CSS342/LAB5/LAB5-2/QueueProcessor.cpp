//
//  QueueProcessor.cpp
//  lab5
//  Queue Processor implementation
//

#include "QueueProcessor.h"

//------------------------------------------------------------------------------
// Constructor
// 
QueueProcessor::QueueProcessor() {

}

//------------------------------------------------------------------------------
// Destructor
// 
QueueProcessor::~QueueProcessor() {

}

//------------------------------------------------------------------------------
// buildQueue
// build the queue of transactions based on type of transaction
void QueueProcessor::buildQueue(ifstream& infile) {
	char tType;
	int source;
	int destination;
	int value;
	string temp;
	while(!infile.eof()) {
		infile >> tType;
		switch (tType)
		{
		// Move
		case 'M':
			infile >> destination >> value >> source;
			transQ.addTransaction(Transaction(tType,destination,value,source));
			tType = '!';
			break;
		// Deposit
		case 'D':
			infile >> destination >> value;
			transQ.addTransaction(Transaction(tType,destination,value));
			tType = '!';
			break;
		// Withdraw
		case 'W':
			infile >> destination >> value;
			transQ.addTransaction(Transaction(tType,destination,value));
			tType = '!';
			break;
		// Place in History
		case 'H':
			infile >> destination;
			transQ.addTransaction(Transaction(tType,destination));
			tType = '!';
			break;
		case '!':
			getline(infile, temp);
			break;
		default:
			// if transaction type is invalid, line read and ignored
			transQ.addTransaction(Transaction(tType));
			getline(infile, temp);
			tType = '!';
			break;
		}
	}
}

//------------------------------------------------------------------------------
// runQueue
// process the queue of transactions
void QueueProcessor::runQueue(ClientList& clients) {
	while(!transQ.isEmpty()) {
		Transaction tempT = transQ.getTransaction();
		int source = tempT.getSourceAcct();
		int target = tempT.getTargetAcct();
		Client* sClient;
		Client* tClient;
		char tType = tempT.getTranType();
		switch(tType) {
		// Move
		case 'M':
			if(!clients.getClient(target/10,tClient)) {
				cout << "Move not performed to " << accountType(target) 
					<< " fund for client " << target/10 << endl;
				cout << "     Unknown client ID " << target/10 << " requested" 
					<< endl << endl;
				continue;
			}
			if(clients.getClient(source/10,sClient)) {
					moveHelper(*sClient,*tClient, tempT);
			} else {
				cout << "Move not performed from " << accountType(source) 
					<< " fund for client " << source/10 << endl;
				cout << "     Unknown client ID " << source/10 
					<< " requested" << endl << endl;
				continue;
			}
			break;
		// Withdraw
		case 'W':
			if(!clients.getClient(target/10,tClient)) {
				cout << "Withdrawal not performed from " << accountType(target) 
					<< " fund for client " << target/10 << endl;
				cout << "     Unknown client ID " << target/10 << " requested" 
					<< endl << endl;
				continue;
			}
			withdrawalHelper(*tClient, tempT);
			break;
		// Deposit
		case 'D':
			if(!clients.getClient(target/10,tClient)) {
				cout << "Deposit not performed to " << accountType(target) 
					<< " fund for client " << target/10 << endl;
				cout << "     Unknown client ID " << target/10 
					<< " requested" << endl << endl;
				continue;
			}
			depositHelper(*tClient,tempT);
			break;
		// Place in History
		case 'H':
			if(!clients.getClient(target,tClient)) {
				cout << "History not available for client " << target << endl;
				cout << "     Unknown client ID " << target 
					<< " requested" << endl << endl;
				continue;
			}
			showHistoryHelper(*tClient, tempT);
			break;
		default:
			cout << "Unknown transaction type '" << tType 
				<< "' requested" << endl << endl;
			break;
		}
	}
}

//------------------------------------------------------------------------------
// withdrawHelper
// helper for withdraw function
void QueueProcessor::withdrawalHelper(Client& account,  Transaction trans) {
	if(account.widthdrawlFromAccount(
			trans.getAmount(),trans.getTargetAcct()) < 0) {
		cout << "Withdrawal not performed on " 
			<< accountType(trans.getTargetAcct()) << " fund for client " 
			<< trans.getTargetAcct()/10 <<endl;
		cout << "     insufficient funds" << endl << endl;
	} else {
		account.addToHistory(trans);
	}
}

//------------------------------------------------------------------------------
// depositHelper
// helper for deposit function
void QueueProcessor::depositHelper(Client& account, Transaction trans) {
	if(account.depositToAccount(trans.getAmount(), trans.getTargetAcct())) {
		account.addToHistory(trans);
	} else {
		cout << "Deposit not performed on " << accountType(trans.getTargetAcct())
			<< " fund for client " << trans.getTargetAcct()/10 <<endl;
		cout << "     Deposit not greater than or equal to 0" << endl << endl;
	}
}

//------------------------------------------------------------------------------
// moveHelper
// helper for move function
void QueueProcessor::moveHelper(Client& source, Client& target, 
		Transaction trans) {
	int withdrawn = target.widthdrawlFromAccount(trans.getAmount(),
			trans.getTargetAcct());
	if(source.depositToAccount(withdrawn, trans.getSourceAcct())) {
		source.addToHistory(Transaction('D', trans.getSourceAcct(), 
			trans.getAmount()));
		target.addToHistory(trans);
	} else {
		cout << "Move not performed from " << accountType(trans.getSourceAcct())
			<< " fund for client " << trans.getSourceAcct()/10 <<endl;
		cout << "     insufficient funds" << endl << endl;
	}
}

//------------------------------------------------------------------------------
// showHistoryHelper
// helper for showHistory function
void QueueProcessor::showHistoryHelper(Client& account, Transaction trans) {
	account.addToHistory(trans);
	account.getHistory();
}

//------------------------------------------------------------------------------
// displayQueue
// displays the queue of transactions
void QueueProcessor::displayQueue() {
	transQ.showQueue();
}

//------------------------------------------------------------------------------
// accountType
// Returns the full name of the account type
string QueueProcessor::accountType(int account) {
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
