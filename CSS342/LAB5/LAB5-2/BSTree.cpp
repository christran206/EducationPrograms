//
//  BSTree.cpp
//  lab5
//  Binary Search Tree implementation
//

#include "BSTree.h"

//------------------------------------------------------------------------------
// Constructor
//
BSTree::BSTree() {
	root = NULL;
}

//------------------------------------------------------------------------------
// Destructor
// calls makeEmpty() to destroy data
BSTree::~BSTree() {
	makeEmpty();
}

//------------------------------------------------------------------------------
// insert
// insert a client within the tree, placing it in the correct, sorted spot
bool BSTree::insert(Client* dataptr) {
   	Node* ptr = new Node;
	if (ptr == NULL) { return false; }
	ptr->data = dataptr;
	ptr->left = ptr->right = NULL;
	if (isEmpty()) {
		root = ptr;
	}
	else {
		Node* current = root;
		return insertHelper(current, ptr);
	}
	return true;
}

//------------------------------------------------------------------------------
bool BSTree::insertHelper(Node* current, Node* ptr) {

	if (*current->data < *ptr->data) {
		if (current->right != NULL) {
			insertHelper(current->right, ptr);
		}
		else {
			current->right = ptr;
		}
	}
	else if (*current->data > *ptr->data) {
		if (current->left != NULL) {
			insertHelper(current->left, ptr);
		}
		else {
			current->left = ptr;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
// retrieve
// returns true if a specific node is found
bool BSTree::retrieve(int target, Client*& returned)const {
	Node* current = root;
	returned = NULL;
	while(current != NULL) {
		//If data is NULL, target wasn't found
		if (target == current->data->getID()) {
			returned = current->data;
			return true;
		}
		if(target < current->data->getID()) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return false;
}

//------------------------------------------------------------------------------
// isEmpty
// returns true if the tree is empty
bool BSTree::isEmpty() const {
	return root == NULL;
}

//------------------------------------------------------------------------------
// makeEmpty
// deallocates all memory from the tree
void BSTree::makeEmpty() {
	makeEmptyHelper(root);
}

//------------------------------------------------------------------------------
// makeEmptyHelper
// helper to makeEmpty function
void BSTree::makeEmptyHelper(Node* target) {
	if(target == NULL) {
		return;
	}
	makeEmptyHelper(target->left);
	makeEmptyHelper(target->right);
	delete target->data;
	target->data = NULL;
	target->left = NULL;
	target->right = NULL;
	delete target;
	target = NULL;
}

//------------------------------------------------------------------------------
// display
// displays the entire tree
void BSTree::display() const {
	displayHelper(root);
}

//------------------------------------------------------------------------------
// displayHelper
// helper to display function
void BSTree::displayHelper(Node* target) const{
	if(target == NULL) {
		return;
	}
	displayHelper(target->left);
	cout << *target->data << endl;
	displayHelper(target->right);
}
