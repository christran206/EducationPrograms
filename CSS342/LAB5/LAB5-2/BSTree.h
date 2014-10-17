//
//  BSTree.h
//  lab5
//  Binary Search Tree class
//

#pragma once
#include "Client.h"
#include <iostream>

using namespace std;

//------------------------------ class BSTree ---------------------------------
//  BSTree class: binary search tree to hold Client objects, with additional
//    functionality:
//    -- inserting a new client in the tree
//    -- retrieve a client
//    -- display client info
//    -- check if Firm is empty (contains no clients)
//    -- destroy Client Objects (makeEmpty used in destructor)
//
//  Assumptions:
//    -- each node has a pointer to two other nodes and a pointer to a Client
//    -- makeEmpty is used to delete a client from the tree (all account memory
//       is released
//    -- clients are sorted by client ID
//------------------------------------------------------------------------------

class BSTree { 
 public: 
	 BSTree(); 
	 ~BSTree(); // calls makeEmpty which deallocates all memory 
 
	 // insert object into the tree, parameter holds pointer to object to insert 
	 bool insert(Client*); 
 
	 // retrieve object, first parameter is object to retrieve 
	 // second parameter holds pointer to found object, NULL if not found 
	 bool retrieve(int , Client*&)const; 
 
	 void display()const; //displays the contents of a tree to cout 
	 void makeEmpty(); //empties the current tree, deallocates all memory 
	 bool isEmpty()const; //returns true if tree is empty 
private: 
	 struct Node{ //glue that holds data properly 
		 Client* data; 
		 Node* right; 
		 Node* left; 
	 }; 
	 Node* root; // root of the tree
	 void makeEmptyHelper(Node*);
	 void displayHelper(Node*) const;
	 bool insertHelper(Node*, Node*);
};

