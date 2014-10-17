/////////////////////////////////////////////////////////////////////////////////////
// Action Class
// A class that contains a description of an action for specific Patrons and allows
// retrieving the information stored
//	Containing Action in its own class allows code changes within the class to not
//	affect changes in other classes as long as contracts are set properly
// The description includes:
//       a character that determine the actions:
//               -- C for checkout
//               -- R for return
//               -- H for displaying the history
//       an integer refers to the patron's ID
//       title of the book
//       author of the book
//       date of the book
//       a character determines what type of book it is:
//               -- Y for children
//               -- F for fiction
//               -- P for periodicals
//               -- Support for future additions
// Features:
//      -- allow users to retrieve the action
//      -- allow users to retrieve the id
//      -- allow users to retrieve the book title
//      -- allow users to retrieve the book author
//      -- allow users to retrieve the book type
//      -- allow users to retrieve the book date
// Assumptions:
//      -- all the data is correctly formated
//      -- invalid data is checked and ignored while reading the file
/////////////////////////////////////////////////////////////////////////////////////
#ifndef ACTION
#define ACTION

#include <string>
#include <iostream>
#include "publication.h"
using namespace std;

class Action {
public:
     Action(char, int, char, char, string, string);
     ~Action();

	 //Functions to set and access data
private:
	 char theActionYouWillDo;
	 int patronID;
	 Title titleOfTheBook;
	 Author authorOfTheBook;
	 char typeOfBook;
	 Date dateOfBook;
};

#endif