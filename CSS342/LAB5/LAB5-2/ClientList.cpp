//
//  ClientList.cpp
//  lab5
//  Client List implementation
//

#include "ClientList.h"

//------------------------------------------------------------------------------
// Constructor
// 
ClientList::ClientList() {
}

//------------------------------------------------------------------------------
// Destructor
// 
ClientList::~ClientList() {
}

//------------------------------------------------------------------------------
// addClient
// add a client to the firms tree of clients
// returns true if client was added successfully
bool ClientList::addClient(Client* newClient) {
	return cList.insert(newClient);
}

//------------------------------------------------------------------------------
// getClient
// retrieve a client from the tree
// Returns true if client is found
bool ClientList::getClient(int target, Client*& ptr) const {
	return cList.retrieve(target, ptr);
}

//------------------------------------------------------------------------------
// displayClients
// display all clients in the tree
void ClientList::displayClients() const {
	cList.display();
}

//------------------------------------------------------------------------------
// clearList
// destroy all clients in the tree
void ClientList::clearList() {
	cList.makeEmpty();
}

//------------------------------------------------------------------------------
// isEmpty
// check if firm's tree has no clients
// Returns true if no clients are found
bool ClientList::isEmpty() const {
	return cList.isEmpty();
}
