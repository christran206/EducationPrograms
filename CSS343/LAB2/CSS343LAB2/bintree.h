#ifndef BINTREE_H
#define BINTREE_H
#include <string>
#include <iostream>
#include "nodedata.h"

//---------------------------------------------------------------------------
/*
BinTree class: Data type that is intended to store NodeData objects
    where lower valued NodeData objects are positioned to the left
    and higher valued NodeData objects are positioned to the right

  -- Allows for comparison of two BinTree Objects
  -- Allows for assignment operator=
  -- Allows for getting height of any Node in any order
  -- Allows for displaying the tree sideways
  -- Can change structure from a tree to an array with inOrder processing
  -- Can change an array into a tree with the order equal to inOrder
Assumptions:
  -- Constructor takes no arguments
  -- Copy Constructor and Assignment operator does not use insert
  -- NodeData class is responsible for comparison operator<
  -- NodeData class is responsible for output operator<<
  -- in <<, NodeData is displayed using inOrder processing
  -- NodeData array is initialized to NULL
  -- Does not allow duplicate NodeData objects in tree
*/
//---------------------------------------------------------------------------

using namespace std;

class BinTree {
//---------------------------------------------------------------------------

    friend ostream& operator<<(ostream &, const BinTree &);
public:
    //Constructors/Destructors
    BinTree();                  //Default Constructor
    BinTree(const BinTree &);   //Copy Constructor
    ~BinTree();                 //Destructor

    //Class Functions
    bool isEmpty() const;       //Empty Tree?
    void makeEmpty();           //Make the tree empty
    BinTree& operator=(const BinTree &);//Set this tree to be like another
    bool operator==(const BinTree &) const;//Are two trees the same?
    bool operator!=(const BinTree &) const;//Are two trees different?
    bool insert(NodeData*);//insert NodeData in tree in correct order
    bool retrieve(const NodeData &, NodeData*&) const;//Get NodeData if
                                                      //it's in tree
    void displaySideways() const;//Display the Tree sideways
    int getHeight(const NodeData &) const;//Get Height of NodeData
                                          //if it's in tree
    void bstreeToArray(NodeData* []);//Change Tree into an Array
    void arrayToBSTree(NodeData* []);//Change Array into a tree
//---------------------------------------------------------------------------

private:
    struct Node {
        NodeData* data;
        Node* left;
        Node* right;
    };
    Node* root;

    //Utility Functions
    void inorderHelper(ostream&,const Node*) const;//recursive helper for 
                                                   //output
    void sideways(Node*, int) const;//helper for displaySideways
    void makeEmptyHelper(Node*);//recursive helper for makeEmpty
    Node* copyNode(const Node*);//recursive helper to copy entire Node
    bool nodeEqual(const Node*, const Node*) const;//Helper to check if Nodes
                                                   //are equal
    int getHeightHelper(const Node*) const;//helper for Height
    //private function to get target Node even in a non-ordered tree
    void inOrderRetrieve(const NodeData&, Node*&, Node*) const;
    //recursive helper to change tree to array
    void bstreeToArrayHelper(Node*,NodeData* [], int&);
    //recursive helper to change array to tree
    Node* arrayToBSTreeHelper(NodeData* [], int, int);
};

#endif
