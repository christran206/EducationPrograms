//
//  Firm.cpp
//  lab5
//  Firm implementation
//

#include "Firm.h"

using namespace std;

//------------------------------------------------------------------------------
// Constructor
//
Firm::Firm() {
	clients = new ClientList();
	qProcessor = new QueueProcessor();
}

//------------------------------------------------------------------------------
// Destructor
//
Firm::~Firm() {
	delete clients;
	delete qProcessor;
}
void Firm::buildClientList(ifstream& infile) {
	string lName;
	string fName;
	int ID;
	int MM;
	int PMM;
	int LTB;
	int STB;
	int IF500;
	int CVF;
	int GEF;
	int GIF;
	int VF;
	int VSI;
	while(!infile.eof()) {
		if(infile >> lName >> fName >> ID >> MM >> PMM >> LTB >> STB >> 
				IF500 >> CVF >> GEF >> GIF >> VF >> VSI) {
			Client* tempClient = new Client(lName,fName,ID,MM,PMM,LTB,STB,
				IF500,CVF,GEF,GIF,VF,VSI);
			clients->addClient(tempClient);
		} else {
			string temp;
			getline(infile, temp);
		}
	}
}

//------------------------------------------------------------------------------
// displayEOD
// display all transactions made within the firm
void Firm::displayEOD() const {
	cout << "REPORT" << endl << endl;
	displayClients();
}

//------------------------------------------------------------------------------
// getClientHistory
// retrieve the history of a clients accounts
void Firm::getClientHistory(const Client) const {
}

//------------------------------------------------------------------------------
// depositToAccount
// deposit an amount to a clients account
bool Firm::depositToAccount(int acct, int amt) {
	return false;
}

//------------------------------------------------------------------------------
// withdrawFromAccount
// withdraw an amount from a clients account
int Firm::withdrawFromAccount(int acct, int amt) {
	return 0;
}

//------------------------------------------------------------------------------
// sendToProcessor
// build and run the queue of transactions from a text file
bool Firm::sendToProcessor(ifstream& infile) {
	qProcessor->buildQueue(infile);
	qProcessor->runQueue(*clients);
	return false;
}

//------------------------------------------------------------------------------
// moveFunds
// move funds from one account to another
bool Firm::moveFunds(int, int, int) {
	return false;
}

//------------------------------------------------------------------------------
// displayClients
// display the clients within the firm
void Firm::displayClients() const {
	clients->displayClients();
}
