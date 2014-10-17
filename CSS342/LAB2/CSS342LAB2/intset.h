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
#pragma once

#ifndef INTSET_H
#define INTSET_H
#include <iostream>

using namespace std;

class IntSet
{

	friend ostream& operator<<(ostream&, const IntSet&);
	friend istream& operator>>(istream&, IntSet&);


public:
	//Default constructor
	IntSet(int = -1, int = -1, int = -1, int = -1, int = -1);
	//Copy Constructor
	IntSet(const IntSet &iSet);
	//De-constructor
	~IntSet(void);

	//Arithmetic operators
	IntSet operator+(const IntSet &) const;
	IntSet operator*(const IntSet &) const;
	IntSet operator-(const IntSet &) const;

	//Assignment operators
	IntSet& operator=(const IntSet &);
	IntSet& operator+=(const IntSet &) ;
	IntSet& operator-=(const IntSet &) ;
	IntSet& operator*=(const IntSet &) ;

	//Boolean operators
	bool operator==(const IntSet &) const;
	bool operator!=(const IntSet &) const;

	//Class Functions
	bool insert(int a);
	bool remove(int a);
	bool isEmpty() const;
	bool isInSet(int a) const;
private:
	int largestNumber;
	bool *SetArray;
	void resize(int a);
	void clear();
	int findLargestNumber() const;
};

#endif
