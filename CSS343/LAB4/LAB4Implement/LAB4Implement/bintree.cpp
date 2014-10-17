#include "bintree.h"


BinTree::BinTree(){
    root = NULL;
}


BinTree::~BinTree() {
    if(!isEmpty()) {
        makeEmpty();
    }
    delete root;
}
//----------------------------------------------------------------------------
/* Function insert
Creates a Node with data from parameter.
Inserts into tree in a location that satisfies the condition of a binary
search tree. NodeData contained in Nodes to the left of another Node
are lower in value and NodeDaa contained in Nodes to the right of
another Node are higher in value

Duplicate values are not allowed in this Binary Search Tree
It's expected that this function does not delete the NodeData
as an external function will be responsible for this in the
event the NodeData can't be inserted
*/
bool BinTree::insert(Publication* target) {
    Node* toInsert = new Node;
    toInsert->data = target;
    toInsert->left = toInsert->right = NULL;
    if(isEmpty()) {
        root = toInsert;
    } else {
        Node* current = root;
        bool inserted = false;

        while(!inserted) {
            //if data is a duplicate, delete the Node and break loop
            //Global function will delete NodeData
            if(*toInsert->data == *current->data) {
                delete toInsert->data;
                delete toInsert;
                break;
            }
            //If data to be inserted is lower, 
            if(*toInsert->data < *current->data) {
                if(current->left == NULL) {
                    current->left = toInsert;
                    inserted = true;
                } else {
                    current = current->left;
                }
            } else {
                if(current->right == NULL) {
                    current->right = toInsert;
                    inserted = true;
                } else {
                    current = current->right;
                }
            }
        }
    }
    return true;
}

bool BinTree::isEmpty() const{
    return root == NULL;
}

//----------------------------------------------------------------------------
/*Function retrieve
Attempts to find NodeData matching target parameter. If found, the returned
parameter is set to point to the NodeData within the tree.
If no matching data is found, return false and set parameter reference to NULL
It's up to the caller to ensure the data deletes properly
*/
bool BinTree::retrieve(const Publication& target, Publication*& returned) const {
    //If tree is empty, there can be no matching possiilities
    if(isEmpty()) {
        return false;
    }
    Node* current = root;
    returned = NULL;
    bool found = false;
    while(!found) {
        //Check if the current node contains the data
        if(target == *current->data) {
            returned = current->data;
            found = true;
        } else {
            //If current Node does not have a valid continuing path, break
            //if target is lower, move pointer to the left Node
            if(target < *current->data) {
                if(current->left == NULL) {
                    break;
                } else {
                    current = current->left;
                }
            } else { //if target isn't lower, move pointer to the right node
                if(current->right == NULL) {
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }
    return found;
}

void BinTree::display() const{
	root->data->displayTitle();
    inOrderDisplay(root);
}

//----------------------------------------------------------------------------
/* Function makeEmpty
Using a recursive helper, traverses through Binary Search Tree and deletes
NodeData and the Nodes
*/
void BinTree::makeEmpty() {
    makeEmptyHelper(root);
    root = NULL;
}

//Recursion function to delete NodeData and the Nodes
void BinTree::makeEmptyHelper(Node* target) {
    if(target != NULL) {
        makeEmptyHelper(target->left);
        makeEmptyHelper(target->right);
        delete target->data;
        target->data = NULL;
        delete target;
        target = NULL;
    }
    
}

void BinTree::inOrderDisplay(Node* current) const {
    if(current != NULL) {
        inOrderDisplay(current->left);
        current->data->display(true);
        inOrderDisplay(current->right);
    }
}
