#include "patron.h"


Patron::Patron(int id, string fName, string lName) {
    pid = id;
    firstName = fName;
    lastName = lName;
}


Patron::~Patron(void)
{
}
//----------------------------------------------------------------------------
/*
getID function

returns the value of the Patron ID
*/
int Patron::getID() {
    return pid;
}
//----------------------------------------------------------------------------
/*
getName function

returns the value of the Patrons name by last name then first name
*/
string Patron::getName() {
    return lastName+" "+firstName;
}
//----------------------------------------------------------------------------
/*
operator<<

Outputs the same information given in
Outputs in the following order
ID
Last Name
First name
*/
ostream& operator<<(ostream& ostream, const Patron& input) {
    ostream << input.pid << " " << input.lastName 
		<< " " << input.firstName << endl;
    return ostream;
}
//----------------------------------------------------------------------------
/*
displayHistory function

Iterates through the deque and displays users history in order placed into
deque
*/
void Patron::displayHistory() {
	cout << "*** Patron ID = " << *this;
	//If there is no history, report an error
    if(histlist.size() == 0) {
        cout << "Patron " << pid << " has no history to display" << endl;
    }
    deque<History>::iterator it = histlist.begin();
    while(it != histlist.end()) {
        cout << *it;
		it++;
    }
}
//----------------------------------------------------------------------------
/*
addToChecked function

Takes a publication and adds a pointer to the object in a list. 
*/
void Patron::addToChecked(Publication* pubptr) {
	if(pubptr == NULL) {
		return;
	}
	currentChecked.push_back(pubptr);
}
//----------------------------------------------------------------------------
/*
removedFromChecked function

When removing an item from the list, this function checks if the publication
exists for the user to return the publication
*/
bool Patron::removeFromChecked(Publication* target) {
	//Create iterator
	list<Publication*>::iterator it = currentChecked.begin();
	//Loop until the end
	while(it != currentChecked.end()) {
		//Check if list contains the publication
		if(**it == *target) {
			currentChecked.erase(it);
			return true;
		} else {
			it++;
		}
	}
	cout << "Patron has not checked out book to return" << endl;
	return false;
}
//----------------------------------------------------------------------------
/*
operator== function

Since IDs are unique, they can be used to compare equality.
*/
bool Patron::operator==(const Patron& rhs) const {
	return pid == rhs.pid;
}
//----------------------------------------------------------------------------
/*
addToHistory function

Adds a history record to the Patron container.
*/
void Patron::addToHistory(string action, Publication* pub) {
	histlist.push_back(History(pub,action));
}
