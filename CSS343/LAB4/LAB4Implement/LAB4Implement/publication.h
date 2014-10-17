#ifndef PUBLICATION_H
#define PUBLICATION_H
#include <string>
#include <iostream>
#include <iomanip>

//-----------------------------------------------------------------------------
/*  Publication class:	Intended to be used as a base class adn therefore can't
						be instantiated on it's own. Values stored in class
						are the minimal expected for any piece of stored
						information that will be common to all child classes
Features:
	--Forces all child classes to implement operator< and operator==
	--Information on Publications can be shown using display
	--allow users to compare to another publication with the equality operator
	--allow users to compare to another publication with the less than operator
	--Allows common checkout and checkin functions
	--Common function to show availability of the publication
Assumptions:
	--Must implements operator< and operator==
    --Child classes implement operators based on sorting requirements
*/
//-----------------------------------------------------------------------------
using namespace std;

class Publication {

public:
    Publication();
	virtual ~Publication()= 0;

	//Virtual Functions
    virtual void display(bool showCount = false) const = 0; //Text Output
	virtual void displayTitle() const = 0; //Output title
    virtual bool operator==(const Publication&) const = 0; //Equality Operator
	virtual bool operator<(const Publication&) const = 0;//Less than operator
    //Functions to set private variables

    bool checkOut();	//Check a publication out if possible
    void checkIn();		//Return a publication
    bool canCheckOut() const;	//Can you check this publication out?
    char getType() const;	//Get the char type of the publication
    int compareString(string,string);	//case-insensitive string comparing
    int available() const;	//Number of publications available
    
    
protected:
    static const int STARTQTY = 5;	//Starting quantity of publications
    static const int AVAIL_OUT_WIDTH = 6; //Width of the available number
	static const int AVAIL_OUT_OFFSET = 2; //Width of the available number
    static const int YEAR_OUT_WIDTH = 5; //Width of the year number
	static const int TITLE_OUT_WIDTH = 40;	//Max char output of title
    string pubTitle;	//Title of the publication
	int pubDateYear;	//Year of the publication
	char pubType;		//Type of publication
    char pubEdition;	//Edition or version of publication
	int quantity;		//Number of publications that exist
    int numOut;			//Number of publications that are checked out
};
#endif
