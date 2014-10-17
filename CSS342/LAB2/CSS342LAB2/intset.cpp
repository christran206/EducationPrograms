/*
IntSet Class
To hold a variable number of Integers to represent a Set and functions that provide commonly used operations

Class description and structure:
Set is represented as a bool array where each index value is the value of the integer in the set.
To determine if a value is a part of a set, the index is set to true, otherwise it's false
IntSet contains a dynamic array that will size itself as needed to contain at least the largest true index and will allow array size to be larger than needed

Design Decisions:
--largestNumber is specified for function use in addition to allowing IntSet to remove indexes without resizing
--Code class to minimize the number of deallocations and allocations

Assumptions:
--Only non-negative integers. Includes zero
--Operations on Sets is the same as the mathematical standard operations
--All IntSets must construct an array, even IntSets with no valid values
--IntSet class is designed to work with integers and does not type check
--IntSet constructor is only required to handle up to five int parameters
--IntSet constructed with no parameters is valid
--IntSet functions will ignore invalid values
--Size of bool array will be "at least" 1 + largest contained Integer (ex. num = 12, size = 13)
--Input operator will terminate as sentinel value(original: -1, revised: number < 0)
--insert function will return false if attempting to insert an integer that already exist
--remove function will return false if attempting to remove an integer that doesn't exist
*/

#include "intset.h"

// --------------------------------------------------------------------------
//Default constructor
//Constructs IntSet using up to five int parameters
//Personal Preference: Finding largest int parameter passed into constructor and constructs the bool array a single time in constructor
IntSet::IntSet(int num1, int num2, int num3, int num4, int num5)
{
	largestNumber = -1;	 //largestNumber is assumed to be -1 for error checking logic later
	int params[5] = {num1, num2, num3, num4, num5}; //Put all parameters into an array
	bool isValidParam[5] = {false}; //Create a corresponding bool array for the parameters with default false values
	//Determine which parameters are valid( >= 0) and set corresponding bool array
	for(int i = 0; i < 5; i++) {
		if(params[i] >= 0) {
			isValidParam[i] = true;
			if(params[i] > largestNumber) {
				largestNumber = params[i]; //Determine largest int parameter for future array construction
			}
		}
	}
	//If valid params have been found, instantiate a new array with size largestNumber and populate
	if (largestNumber > -1) {
		SetArray = new bool[largestNumber+1];	//new array of size largestNumber+1
		clear();								//Make all indexes False
		for(int i = 0; i < 5; i++) {			//for loop to iterate through bool array
			if(isValidParam[i] == true){		//Check if bool is true
				SetArray[params[i]] = true;		//Index of param value is set to true
			}
		}
	} else {
		SetArray = new bool[1];					//Default empty array of size 1
	}
}

// --------------------------------------------------------------------------
//Copy Constructor
//Copy largestNumber, construct a new bool array of the same size, copy index bool values
IntSet::IntSet(const IntSet &iSet) {
	largestNumber = iSet.largestNumber;			//Copy largestNumber Int
	SetArray = new bool[(largestNumber+1 <= 0? 1 : largestNumber+1)];		//Allocate new bool array of size largestNumber+1
	//Copy source array values into current array
	for(int i = 0; i <= largestNumber; i++) {
		SetArray[i] = iSet.SetArray[i];
	}
}

// --------------------------------------------------------------------------
//De-constructor
//Delete allocated array and set to NULL
IntSet::~IntSet()
{
	delete[] SetArray;	//Delete allocated array
	SetArray = NULL;	//Set pointer to NULL
}

// --------------------------------------------------------------------------
//operator<<
//Overloaded output operator for class IntSet
//Returns integers in IntSet within curly brackets delimited with a single space
ostream& operator<<(ostream &output, const IntSet &iSet) {
	output << "{";
	//Loop through bool array and output true index locations with space prefix
	for(int i = 0; i <= iSet.largestNumber; i++) {
		if(iSet.SetArray[i] == true) {
			output << " " << i;
		}
	}
	output << "}";
	return output;
}

// --------------------------------------------------------------------------
//operator>>
//Overloaded input operator for class IntSet
//Input can be single ints or space delimited ints
//Will terminate at invalid inputs. Non ints & values < 0
istream& operator>>(istream &input, IntSet &iSet) {
	int in;
	//stream input to "in" variable to allow multiple ints in one line Ex. 4 89 46
	while(input >> in) {
		//
		if(iSet.insert(in)) {
			continue;
		} else {
			break;
		}
	}
	return input;
}

// --------------------------------------------------------------------------
//operator+
//Overloaded addition operator for class IntSet
//Returns an IntSet containing the true index values in two IntSets
IntSet IntSet::operator+(const IntSet &iSet) const {
	if(&iSet != this) { //Check if comparing the same IntSet
		//Determine which IntSet has a larger number and construct a new IntSet using result
		IntSet rSet((largestNumber >= iSet.largestNumber ? largestNumber : iSet.largestNumber));
		//Loop through "this" IntSet and copy same Array Values
		for(int i = 0; i <= largestNumber; i++) {
			rSet.SetArray[i] = SetArray[i];
		}
		//Loop through parameter IntSet and only check true indexes
		for(int i = 0; i <= iSet.largestNumber; i++) {
			if(iSet.SetArray[i]) {
				rSet.SetArray[i] = iSet.SetArray[i];
			}
		}
		return rSet;
	}
	return *this;
}

// --------------------------------------------------------------------------
//operator*
//Returns an IntSet containing the true index values that exist in both IntSets
//If calling against itself, will return itself as result as all values intersect
IntSet IntSet::operator*(const IntSet &iSet) const {
	if(&iSet != this) { //Will return itself if called against itself
		//Determine which IntSet is larger, saved in bool variable to be used more than once
		bool isThisLarger = largestNumber >= iSet.largestNumber;
		//Create IntSet with the size from the smaller IntSet
		IntSet rSet = IntSet((isThisLarger? iSet.largestNumber : largestNumber));
		rSet.clear();		//Reset all values to false
		//Loop through both IntSet arrays to determine which values exist in both
		for(int i = 0; i <= rSet.largestNumber; i++) {
			if(SetArray[i] == true && iSet.SetArray[i] == true) {
				rSet.SetArray[i] = true;
			}
		}
		return rSet;
	}
	return *this;
}
// --------------------------------------------------------------------------
//operator-
//Returns an IntSet containing values that exist in "this" IntSet but not existant in parameter IntSet
//If called against itself, will return an empty IntSet
IntSet IntSet::operator-(const IntSet &iSet) const {
	//Create a copy of "this" IntSet
	IntSet rSet(*this);
	if(&iSet != this) {
		//Loop until the smaller largestNumber of the two IntSets is reached
		for(int i = 0; i <= (rSet.largestNumber >= iSet.largestNumber? iSet.largestNumber : rSet.largestNumber); i++) {
			if(rSet.SetArray[i] == iSet.SetArray[i]) {
				rSet.SetArray[i] = false;
			}
		}
		return rSet;
	} else {
		//clears result IntSet if comparing against itself
		rSet.clear();
	}
	return rSet;
}

// --------------------------------------------------------------------------
//operator=
//Returns an IntSet that is equal to the parameter IntSet
IntSet& IntSet::operator=(const IntSet &iSet) {
	if(&iSet != this) { //No operations needed if assigning to itself
		delete [] SetArray;	//Delete the current bool array
		largestNumber = iSet.largestNumber;	//Set largestNumber to value of parameter IntSet
		SetArray = new bool[largestNumber+1];  //Allocate new bool array of proper size. No need to initialize values to false as they will be taken from source IntSet array
		for(int i = 0; i <= largestNumber; i++) { //Loop through array and copy bool values
			SetArray[i] = iSet.SetArray[i];
		}
	}
	return *this;
}

// --------------------------------------------------------------------------
//operator+=
//overloaded += : current object = current object + parameter
//Adds parameter IntSet values into current IntSet
IntSet& IntSet::operator+=(const IntSet &iSet)  {
	if(&iSet != this) { //Check if adding to itself
		//Loop through parameter IntSet and insert all values contained
		//Design Choice: Start from largest value to only cause a single resize
		for(int i = iSet.largestNumber; i >= 0; i--) {
			if(iSet.SetArray[i]) {
				insert(i);
			}
		}
	}
	return *this;
}

// --------------------------------------------------------------------------
//operator -=
//overloaded -=: current object = current object - parameter
//Removes values in current IntSet that are also exist in parameter Intset
IntSet& IntSet::operator-=(const IntSet &iSet)  {
	for(int i = 0; i <= (largestNumber >= iSet.largestNumber? iSet.largestNumber : largestNumber); i++) {
		if(SetArray[i] == iSet.SetArray[i]) {
			remove(i);
		}
	}
	return *this;
}

// --------------------------------------------------------------------------
//operator *=
//overloaded *=: current object = current object * parameter
//Will not change if calling against itself as all values will intersect
IntSet& IntSet::operator*=(const IntSet &iSet)  {
	if(&iSet != this) {  //Check if intersecting against itself
		//Only loop until the largestNumber of either IntSet is reached
		//If true in both IntSet, no need to change bool, else change value to false
		int currentLargest = largestNumber;
		for(int i = 0; i <= currentLargest && i <= iSet.largestNumber; i++) {
			if(SetArray[i] == true && iSet.SetArray[i] == true) {
				largestNumber = i; //Last known true index is now the largestNumber
			} else {
				SetArray[i] = false;
			}
		}
	}
	return *this;
}

// --------------------------------------------------------------------------
//operator==
//overloaded ==: true if current object == parameter, otherwise false
//IntSets are equal if all indexes contain same bool values
bool IntSet::operator==(const IntSet &iSet) const {
	//If largest values aren't the same, IntSets are different without need to check inside
	if(largestNumber != iSet.largestNumber) {
		return false;
	}
	//Check all indexes for same bool value except for largest value since it was checked previously
	for(int i = 0; i < largestNumber; i++) {
		if(SetArray[i] != iSet.SetArray[i]) {
			return false;
		}
	}
	return true;
}

// --------------------------------------------------------------------------
//operator!=
//overloaded !=:true if current object != parameter, otherwise false
//Returns inverse result of overloaded==
bool IntSet::operator!=(const IntSet &iSet) const {
	return !(*this == iSet);
}

// --------------------------------------------------------------------------
//insert function
//insert valid integer into current object
//Returns true if insertion was successful
//Assumption, will return false if the value is already a part of the set
bool IntSet::insert(int a) {
	if(a < 0) { //Check if int is valid
		return false;
	}
	if (a > largestNumber) { //Check if int to be added will require resizing array
		resize(a);	//private function to resize array
		largestNumber = a; //largestNumber is now "a" parameter
	} else {
		if(SetArray[a]) { //If index is already true, return false
			return false;
		}
	}
	SetArray[a] = true; //Set index at "a" parameter to true
	return true;
}

// --------------------------------------------------------------------------
//remove function
//remove valid integer from current object
//Returns false if index value of parameter is already false or if parameter is out of range
bool IntSet::remove(int a) {
	if(a < 0 || a > largestNumber) { //Check if parameter request is a valid removal request
		return false;
	}
	if(SetArray[a] == false) { //if index is already false, can't remove so return false
		return false;
	}
	SetArray[a] = false;
	if(a == largestNumber) { //In case largest number is removed, find the next largest number
		largestNumber = findLargestNumber(); 
	}
	return true;
}

// --------------------------------------------------------------------------
//isEmpty function
//Returns true if IntSet is determined to be empty, otherwise false
//By design, if largestNumber < 0 then it's empty
bool IntSet::isEmpty() const {
	return largestNumber < 0;
}

// --------------------------------------------------------------------------
//isInSet function
//Returns true if the parameter is true in the current object
bool IntSet::isInSet(int a) const {
	if(a < 0 || a > largestNumber) { //Return false if parameter is out of range
		return false;
	}
	return SetArray[a]; //Return bool value at index of parameter
}

// --------------------------------------------------------------------------
//resize function
//Resize the current object bool array to the size specified by parameter
//Parameter passed in will be the largestNumber needed
void IntSet::resize(int a){
	bool *tempArray = new bool[a+1]; //Allocate new bool array of size largestNumber+1
	for(int i = 0; i <= a; i++) { //Set all values to false to avoid using uninitialied data
		tempArray[i] = false;
	}
	for(int i = 0; i <= largestNumber; i++) { //Copy array values from current object array to temp array
		tempArray[i] = SetArray[i];
	}
	delete[] SetArray; //Delete current object array
	SetArray = tempArray; //Set current object array to point to temp array
}

// --------------------------------------------------------------------------
//clear function
//Set all values in current object array to false
//Needed to either avoid usage of uninitialized data
void IntSet::clear() {
	for(int i = 0; i <= largestNumber; i++) {
		SetArray[i] = false;
	}
}

// --------------------------------------------------------------------------
//findLargestNumber function
//returns the largest index that has a true value which will be the largestNumber in current object
//needed when removing the largest value from the current object
int IntSet::findLargestNumber() const {
	//Loop from the largest index and return index value at first encounter of true value
	for(int i = largestNumber; i >= 0; i--) {
		if(SetArray[i]) {
			return i;
		}
	}
	//If no indexes are true, IntSet is empty and largestNumber is set to -1
	return -1;
}
