//
//  ClientList.h
//  lab5
//  Client List class
//

#pragma once
#include "BSTree.h"
#include "Client.h"

//------------------------------ class ClientList ----------------------------
//  ClientList class: functionality for modifying the firm's tree of clients,
//       with additional functionality:
//    -- add a client
//    -- retrieve a client
//    -- display all clients clients
//    -- clear all clients
//    -- check if the list is empty
//------------------------------------------------------------------------------

class ClientList
{
public:
	ClientList();   // constructor
	~ClientList();  // destructor
	bool addClient(Client*);               // add a client
	bool getClient(int , Client*&) const;  // retrieve a client
	void displayClients() const;           // display all clients
	void clearList();                      // clear all clients
	bool isEmpty() const;                  // check if a firm has clients
private:
	BSTree cList;    // binary search tree of clients
};

