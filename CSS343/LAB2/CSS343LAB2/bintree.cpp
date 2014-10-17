#include "bintree.h"

//----------------------------------------------------------------------------
/* Default Constructor
Takes no arguments and creates an empty tree
*/
BinTree::BinTree() {
    root = NULL;
}

//----------------------------------------------------------------------------
/*Copy Constructor
Creates a duplicate node structure and data of the input BinTree
*/
BinTree::BinTree(const BinTree& input) {
    //Check if the input BinTree has any Nodes before attempting to copy
    if(!input.isEmpty()) {
        //recursive copy method
        root = copyNode(input.root);
    }
}
//----------------------------------------------------------------------------
/* Destructor
If the tree isn't empty, make it empty
*/
BinTree::~BinTree() {
    if(!isEmpty()) {
        makeEmpty();
    }
    delete root;
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

//----------------------------------------------------------------------------
/* Function isEmpty
Checks if the BinTree is empty and is determined if the BinTree object has
no node referenced
*/
bool BinTree::isEmpty() const {
    return root == NULL;
}


//----------------------------------------------------------------------------
/*Function operator=
Assignment operator
Changes the current object to the parameter object using recursive copy
function
*/
BinTree& BinTree::operator=(const BinTree& target) {
    //Assignment to itself requires no actions
    if(this == &target) {
        return *this;
    }
    makeEmpty();
    delete root;
    //Recursive helper to copy root node and all nodes connected
    root = copyNode(target.root);
    return *this;
}
//----------------------------------------------------------------------------
/*Comparison operator==
Returns true if this objects root and the parameter root are equal in value
and structure
Compares two root nodes and determines if both trees have the same structure
and all NodeData values are equal
*/
bool BinTree::operator==(const BinTree& target) const {
    //Recursive helper to check NodeData and structure
    return nodeEqual(root,target.root);
}
//----------------------------------------------------------------------------
/*Comparison operator!=
Returns true if this object and the parameter object are different
Uses the operator== function and returns the inverse result
*/
bool BinTree::operator!=(const BinTree & target) const {
    return !(*this==target);
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
bool BinTree::insert(NodeData* target) {
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

//----------------------------------------------------------------------------
/*Function retrieve
Attempts to find NodeData matching target parameter. If found, the returned
parameter is set to point to the NodeData within the tree.
If no matching data is found, return false
*/
bool BinTree::retrieve(const NodeData& target, NodeData*& returned) const {
    //If tree is empty, there can be no matching possiilities
    if(isEmpty()) {
        return false;
    }
    Node* current = root;
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

//----------------------------------------------------------------------------
/*Function getHeight
Height is the longest path to a downward leaf
Nodes not found and empty trees return 0
*/
int BinTree::getHeight(const NodeData& target) const {
    //if the tree is empty, no need to do anything further and return 0;
    if(isEmpty()) {
        return 0;
    }
    //Create a temp node and use recursive function to find a matching Node
    Node* temp;
    temp = NULL;
    inOrderRetrieve(target, temp, root);
    //if a node is found, get the height with a recursive helper
    if(temp != NULL) {
        return getHeightHelper(temp);
    } else {
        return 0;
    }
}

/*
recursively finds the height of a Node
Traverse and keep adding a value of 1 each time there exist downward path(s)
*/
int BinTree::getHeightHelper(const Node* target) const {
    //If leaf node, return 1
    if(target->left == NULL && target->right == NULL) {
        return 1;
    }
    //if only left existing Node, recursive call left node
    if(target->left != NULL && target->right == NULL) {
        return 1+getHeightHelper(target->left);
    }
    //if only right existing Node, recursive call right node
    if(target->right != NULL && target->left == NULL) {
        return 1+getHeightHelper(target->right);
    }
    //Both left and right exist, only use the largest value of either path
    return 1+max(getHeightHelper(target->left),
                 getHeightHelper(target->right));
}

/*
getHeight can be called on any generic tree. Therefore, to find a Node
the tree must be iterated in order since the NodeData doesn't have to follow
Binary Search Tree design
*/
void BinTree::inOrderRetrieve(const NodeData& target, 
                              Node*& returned, Node* current) const {
    //Use inOrder recursion to find data. 
    if(current->left != NULL) {
        inOrderRetrieve(target,returned,current->left);
    }
    if(target == *current->data) {
        returned = current;
        return;
    }
    if(current->right != NULL) {
        inOrderRetrieve(target,returned,current->right);
    }
}

//----------------------------------------------------------------------------
/*Function bstreeToArray
Change the Binary Search Tree into an array
Use inOrder recursion to iterate through tree from smallest to largest
NodeData values
*/
void BinTree::bstreeToArray(NodeData*  nodeArray[]) {
    //if tree is empty, nothing is to be done
    if(isEmpty()) {
        return;
    }
    //int index is called outside recursion to keep value changes
    //intact in recursion stack
    int index = 0;
    bstreeToArrayHelper(root,nodeArray, index);
    //tree should be empty after function executes
    makeEmpty();
}
/*
Using inOrder recursion, set pointers in array to the NodeData
as the tree is traversed
index is passed by reference to keep value intact through recursion
*/
void BinTree::bstreeToArrayHelper(Node* target,
                                  NodeData* nodeArray[], int& index) {
    if(target->left != NULL) {
        bstreeToArrayHelper(target->left,nodeArray,index);
    }
    nodeArray[index++] = target->data;
    target->data = NULL;
    if(target->right != NULL) {
        bstreeToArrayHelper(target->right,nodeArray,index);
    }
}

//----------------------------------------------------------------------------
/* Function arrayToBSTree
Takes a sorted array of data and converts it into a balanced Binary Search
Tree
*/
void BinTree::arrayToBSTree(NodeData* nodeArray[]) {
    //find how many valid NodeData are inside Array
    int size = 0;
    for(;;) {
        if(nodeArray[size] != NULL) {
            size++;
        } else {
            break;
        }
    }
    //Destroy current tree
    //Array of 0 NodeData objects is the same as empty tree
    makeEmpty();
    //Only need to make tree if size is more than 0
    if(size > 0) {
        root = arrayToBSTreeHelper(nodeArray,0,size-1);
    }
}
/*
Find midpoints to get parent Nodes
Recursive run on the left and right sections of the array
Each midpoint links to the parent midpoint above it.
*/
BinTree::Node* BinTree::arrayToBSTreeHelper(NodeData* nodeArray[], 
                                            int begin, int end) {
    if(begin > end) {
        return NULL;
    }
    int mid = (begin+end)/2;
    Node* temp = new Node;
    temp->data = nodeArray[mid];
    temp->left = arrayToBSTreeHelper(nodeArray,begin,mid-1);
    temp->right = arrayToBSTreeHelper(nodeArray,mid+1,end);
    return temp;
}

//----------------------------------------------------------------------------
/*private function copyNode
Recursively copies a target Node and all Nodes downward
*/
BinTree::Node* BinTree::copyNode(const Node* target) {
    //Return NULL if reaching a Null Node
    if(target == NULL) {
        return NULL;
    }
    //Using Pre-order operation, copy existing Node
    //then recursively call left and right Nodes
    Node* nodeCopy = new Node;
    nodeCopy->data = new NodeData(*target->data);
    nodeCopy->left = copyNode(target->left);
    nodeCopy->right = copyNode(target->right);
    
    return nodeCopy;
}

//----------------------------------------------------------------------------
/*private function nodeEqual
Returns true if Nodes are equal in NodeData value and in structure of
all downward Nodes
Look for any false condition, if none are encountered, return true
*/
bool BinTree::nodeEqual(const Node* node1, const Node* node2) const {
    //if NodeData for both nodes are equal
    //Process further cases
    if(*node1->data == *node2->data) {
        //Leaf check and storing result in variable for future use
        bool leftNull = node1->left == NULL && node2->left == NULL;
        bool rightNuLL = node1->right == NULL && node2->right == NULL;
        //If this is a leaf, return true (base case)
        if(leftNull && rightNuLL) {
            return true;
        } else {
            //check if both nodes have existing left and right pointers
            //if there are differences, result is false
            if(!leftNull) {
                if(node1->left != NULL && node2->left == NULL) {
                    return false;
                }
                if(node1->left == NULL && node2->left != NULL) {
                    return false;
                }
                return nodeEqual(node1->left,node2->left);
            } 
            if(!rightNuLL) {
                if(node1->right != NULL && node2->right == NULL) {
                    return false;
                }
                if(node1->right == NULL && node2->right != NULL) {
                    return false;
                }
                return nodeEqual(node1->right, node2->right);
            }
            // previous if conditions satisfy that both the left and right
            //of both nodes can be compared. Results are recursively
            //multiplied to roll up any false (0 value) result
            return nodeEqual(node1->left,node2->left) * 
                nodeEqual(node1->right, node1->right);
        }
        
    } else {
        return false;
    }
}

//----------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

void BinTree::displaySideways() const {
    sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level 
        for(int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl; // display information of object
        sideways(current->left, level);
    }
}

//----------------------------------------------------------------------------
/* Output operator<<
Using recursive inorderHelper function, traverse binary tree in order and
output NodeData values using NodeData operator<< functions if they exist
Prints out a Binary Search Tree in order or any generic tree in the order
if they were sorted
*/
ostream& operator<<(ostream &output, const BinTree& a) {
    a.inorderHelper(output,a.root);
    output << endl;
    return output;
}

//----------------------------------------------------------------------------
/*
private function inorderHelper
In order traversal of Binary Tree
NodeData must implement operator<< to display proper values
Single Space between NodeData output
*/
void BinTree::inorderHelper(ostream& output,const Node* target) const {
    if(target->left != NULL) {
        inorderHelper(output,target->left);
    }
    output << *target->data << " ";
    if(target->right != NULL) {
        inorderHelper(output,target->right);
    }
}
