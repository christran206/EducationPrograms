/*
------------------------------Class List Template------------------------------
Template ADT List:	finite, ordered collection of zero or more objects
			Ordering is determined by the operator< of T class

Class description
An Abstract Data Type List that takes in Objects and stores them sorted 
from smallest to largest

Design Decisions:

Assumptions:
--Controll of <, printing, etc of T information is in the T class
--There is no dummy head node, head points to first node
	If the list is empty, head is NULL
--Insert allocates memory for a Node, ptr to the data is passed in.
	Allocation memory and setting data is the responsibility of the caller
--Constructors and Destructors must be O(n) time;
--Data files are expected to be properly formatted
--Use nodedata.cpp and employee.cpp from example code
--list.h should not include other headerfiles
--Any class will be used to test this template, not only provided examples
*/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
using namespace std;


template <typename T>
class List {
	//Output Ooerator for class List, print data
	//responsibility for output is left to the object stored in the list
	friend ostream& operator<<(ostream& output, const List<T>& thelist) {
		ListNode* current = thelist.head;
		while (current != NULL) { 
			output << *current->data;
			current = current->next;
		}
		return output;
	}
	
public:
	//Constructors and Deconstructors
	List<T>();			//Default constructor
	~List<T>();			//Deconstructor
	List<T>(const List<T>&);	//Copy Constructor

	//Functions
	void buildList(ifstream& input);	//Build list from Data file
	void makeEmpty();			//Empty the List
	bool insert(T* in);			//Insert node into List
	bool remove(T& target, T*& out);	//Remove target with return
	bool retrieve(T& target, T*& out) const;//Retrieve target
	bool isEmpty() const;			//Is the list empty?
	//Merge and sort two lists
	void merge(List<T>& firstList, List<T>& secList);
	//Merge and Sort two lists with same objects
	void intersect(const List<T>& firstList,const List<T>& secList);

	//Operators
	List<T>& operator=(const List<T>&);	//Make list the same as another
	bool operator==(const List<T>&) const;	//Are two lists equal?
	bool operator!=(const List<T>&) const;	//Are two lists not equal?

private:
	//Using struct instead of external node class
	struct ListNode {
		T* data;
		struct ListNode* next;
	};
	ListNode* head;		//pointer to first node in list
};
// ----------------------------------------------------------------------------
//Default Constructor
template <typename T>
List<T>::List() {
	head = NULL;
}

// ----------------------------------------------------------------------------
//Copy Constructor
//Assumptions
//Must be of O(n) time.
//Objects have properly implemented a copy constructor
//Not using
template <typename T>
List<T>::List(const List<T>& in) {
	//Pointers to walk through both Lists and creaing new nodes
	ListNode* nodePtr = in.head;
	ListNode* current = head = NULL;
	ListNode* newNode;
	while(nodePtr != NULL) {
		newNode = new ListNode;	
		newNode->data = new T(*nodePtr->data); //call copy constructor
		newNode->next = NULL;	//null in case last object to add
		//Set head to object if list is empty
		if(isEmpty()) {			
			head = newNode;
			current = head;
			nodePtr = nodePtr->next;
			continue;
		}
		current->next = newNode;
		current = current->next;
		nodePtr = nodePtr->next;
	}
}

// ----------------------------------------------------------------------------
//Deconstructor
//Function call to deallocate memory
template <typename T>
List<T>::~List() {
	makeEmpty();
}


//Functions
// ----------------------------------------------------------------------------
//Make empty
//Function will walk though List and deallocate object data before 
//deallocating ListNode
//Starting from head, walk through list and deallocate
//No need to set parameters to NULL since they will be at end of List
template <typename T>
void List<T>::makeEmpty() {
	ListNode* current = head;
	while(!isEmpty()) {
		head = head->next;
		delete current->data;
		delete current;
		current = head;
	}
}

//-----------------------------------------------------------------------------
//IsEmpty
//Empty list is pointed to NULL
//Return is head is NULL
template <typename T>
bool List<T>::isEmpty() const {
	return head == NULL;
}

//-----------------------------------------------------------------------------
//Insert
//Inserts object into new ListNode and positions in sorted order
//Check for true cases of insertion, otherwise return false
template <typename T>
bool List<T>::insert(T* in) {
	ListNode* newNode = new ListNode;
	if(newNode->data = in) {
		//If the List is empty or if node is to be in head position
		if(isEmpty() || *newNode->data < *head->data) {
			newNode->next = head;
			head = newNode;
			return true;
		} else {
			//Pointers to trackwallking through previous and
			//current nodes to insert newNode in sorted location
			ListNode* current = head->next;
			ListNode* previous = head;
			//Walk pointers until end of list or when 
			//newNode is < Object at current
			while(current != NULL && 
				*current->data < *newNode->data) {
				previous = current;
				current = current->next;
			}
			newNode->next = current;
			previous->next = newNode;
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------------
//remove
//Remove target object from List and return object using 
//parameter passed into function
//True if successful, false otherwise
//Assumptions
//Second parameter is unreliable, will set to NULL if no target found
template <typename T>
bool List<T>::remove(T& target, T*& out) {
	if(!isEmpty()) {	//No need to check list if it's empty
		if(*head->data == target) {
			out = head->data; //point param to Object to return
			ListNode* temp = head;
			head = head->next;
			delete temp;
			return true;
		}
		//Pointers to walk through List so ListNode can be removed
		//current will be removed
		ListNode* current = head->next;
		ListNode* previous = head;
		while(current != NULL) {
			if(*current->data == target) {
				ListNode* temp = current;
				previous->next = current->next;
				out = temp->data;
				delete temp;
				return true;
			}
			previous = current;
			current = current->next;
		}
	}
	out = NULL;		//If no object found, set parameter to NULL
	return false;
}
//-----------------------------------------------------------------------------
//retrieve
//Will find first match of Object in List and return 
//True if successful, false otherwise
//Assumptions
//Second parameter is unreliable, will set to NULL if no target found
template <typename T>
bool List<T>::retrieve(T& target, T*& out) const {
	ListNode* current = head;
	while(current != NULL) {
		if(*current->data == target) {
			out = new T();
			*out = *current->data;
			return true;
		}
		current = current->next;
	}
	out = NULL;
	return false;
}
//-----------------------------------------------------------------------------
//buildList
//continually insert new objects into the list from a data file
//Assumptions
//Objects will have implementation to read infile for object construction
//If file not found, ignore and don't do anything
template <typename T>
void List<T>::buildList(ifstream& infile) {
	if(infile) {
		T* ptr;
		bool successfulRead;	// read good data
		bool success;		// successfully insert
		for (;;) {
			ptr = new T;
			successfulRead = ptr->setData(infile);//fill the T obj
			if (infile.eof()) {
				delete ptr;
				break;
			}
		// insert good data into the list, otherwise ignore it
		if (successfulRead) {
			success = insert(ptr);
		} else {
			delete ptr;
		}
			if (!success) break;
		}
	}
   
}
//-----------------------------------------------------------------------------
//merge
//Takes two sorted lists and merges them into one
//Assumptions
//No new memory is allocated
//At termination of function, two parameter lists are empty
//	Except in the event one of the parameters is the current objject
//Duplicates are allowed in merged list
//Implementation must take O(n) time
//Design Decision
//If one or both lists are empty check is done at the end to keep similar code
//	function together(empty list parameter or if one list becomes empty)
template <typename T>
void List<T>::merge(List<T>& firstList, List<T>& secList) {
	//Additional check, do nothing if merging with two
	//self parameters
	if(this == &firstList && this == &secList){
		return;
	}
	//Pointers to the heads of parameter Lists to allow lists to be 
	//set to NULL and still have access to data
	ListNode* fListPtr = firstList.head;
	ListNode* sListPtr = secList.head;
	firstList.head = NULL;
	secList.head=NULL;
	makeEmpty();//Empty the current list to deallocate existing memory
	//Check if either of the lists are NULL
	//If not, set head to the lowest object to begin the merged list
	//Walk the pointer of the list that initial head was set to 
	//for future comparisons
	if(fListPtr != NULL && sListPtr != NULL) {
		if(*fListPtr->data <= *sListPtr->data) {
			head = fListPtr;
			fListPtr = fListPtr->next;
		} else {
			head = sListPtr;
			sListPtr = sListPtr->next;
		}
	}
	ListNode* current = head;//pointer to head to be used for Node sorting
	//Only compares while both lists are not Null
	//If a list becomes null, later code will add remaining ListNodes 
	//to end of list as no more comparisons needed
	//Compares the Objects and sets the ListNode at current to point 
	//to the lower of the two ListNodes being walked through
	//current is set to the ListNode just pointed to for the next loop
	while(fListPtr != NULL && sListPtr != NULL) {
		if(*fListPtr->data <= *sListPtr->data) {
			current->next = fListPtr;
			current = fListPtr;
			fListPtr = fListPtr->next;
		} else {
			current->next = sListPtr;
			current = sListPtr;
			sListPtr = sListPtr->next;
		}
	}
	//Once one list becomes NULL, remaining nodes in the non NULL list 
	//can be placed on the end
	//In the event that one or both Lists are empty,
	//this code will handle situation appropriately
	if(fListPtr == NULL && sListPtr != NULL) {
		if(isEmpty()) {
			head = sListPtr;
		} else {
			current->next = sListPtr;
		}
	}
	if(sListPtr == NULL && fListPtr != NULL) {
		if(isEmpty()) {
			head = fListPtr;
		} else {
			current->next = fListPtr;
		}
	}
}
//-----------------------------------------------------------------------------
//intersect
//Takes two sorted lists and finds the items in common in both lists.
template <typename T>
void List<T>::intersect(const List<T>& firstList,const List<T>& secList) {
	//Pointerts that start at the head of each List for walking comparisons
	ListNode* fListPtr = firstList.head;
	ListNode* sListPtr = secList.head;
	makeEmpty();	//Make the current list empty
	ListNode* current = head;
	while(fListPtr != NULL && sListPtr != NULL) {
		if(*fListPtr->data == *sListPtr->data) {
			ListNode* newNode = new ListNode;
			newNode->data = new T(*fListPtr->data);
			newNode->next = NULL;
			if(isEmpty()){
				current = head = newNode;
			} else {
				current->next = newNode;
				current = current->next;
			}
		}
		//Walk the pointer with the lower value for the next comparison
		(*fListPtr->data < *sListPtr->data ? 
			fListPtr=fListPtr->next : sListPtr = sListPtr->next);
	}
}
//-----------------------------------------------------------------------------
//operator=
//Assigns one list to another (Deep Copying)
template <typename T>
List<T>& List<T>::operator=(const List<T>& in) {
	if(&in != this) { //Dont do anything if assigning to itself
		makeEmpty();	//Empty the current List
		ListNode* nodePtr = in.head;
		ListNode* current = head;
		ListNode* newNode;
		//Walk parameter List and allocate new ListNodes in order
		while(nodePtr != NULL) {
			newNode = new ListNode;
			newNode->data = new T(*nodePtr->data);
			newNode->next = NULL; //Null in event this is last
			//if the list is empty, set first ListNode as head
			if(isEmpty()) {
				head = newNode;
				current = head;
				nodePtr = nodePtr->next;
				continue;
			}
			current->next = newNode;
			current = current->next;
			nodePtr = nodePtr->next;
		}
	}
	return *this;
}
//-----------------------------------------------------------------------------
//operator==
//Compares two lists for equality
//Two lists are equal if they hold identical objects in the same arrangement
template <typename T>
bool List<T>::operator==(const List<T>& in) const {
	if(&in != this) { //No need to check if comparing against itself
		ListNode* current = head;
		ListNode* inCurrent = in.head;
		//Walk through both lists and check if objects are equal
		while(current != NULL && inCurrent != NULL) {
			if(*current->data != *inCurrent->data) {
				return false;
			}
			//Walk both pointers to checking identical arrangements
			current = current->next;
			inCurrent = inCurrent->next;
		}
		//In the event that one list ends, if both pointers don't
		//point to NULL, one list has more ListNodes
		//So they are not equal
		if(current != NULL && inCurrent != NULL) {
			return false;
		}
	}
	return true;
}
//-----------------------------------------------------------------------------
//operator!=
//Compares two lists for inequality
//Returns the inverse of overloaded==
template <typename T>
bool List<T>::operator!=(const List<T>& in) const {
	return !(*this == in);
}

#endif
