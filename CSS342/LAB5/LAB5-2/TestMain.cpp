/*
Christopher Tran and Filip Todorovic
Assignment #5 Lab5
Due: 12/4/2013
*/

//
//  TestMain.cpp
//  lab5
//  Main implementation
//
#include "Firm.h"
#include "Transaction.h"
#include <fstream>

int main() {
	// read files
	ifstream queueCommands("lab5command.txt");
	ifstream clientData("lab5data.txt");
	Firm testFirm;
	// build the firm with clients
	testFirm.buildClientList(clientData);
	// process the transactions
	testFirm.sendToProcessor(queueCommands);
	// output end-of-day transaction report
	testFirm.displayEOD();
}
