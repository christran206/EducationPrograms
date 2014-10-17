#include "patrondb.h"


PatronDB::PatronDB() {
}


PatronDB::~PatronDB() {
    map<int,Patron*>::iterator it = patrons.begin();
    while(it != patrons.end()) {
        delete it->second;
        it++;
    }
}

//----------------------------------------------------------------------------
/*
*/
bool PatronDB::insert(Patron* patron) {
    if(patron == NULL) {
        return false;
    }
    patrons.insert(make_pair(patron->getID(), patron));
    return true;
}
//----------------------------------------------------------------------------
/*
*/
Patron* PatronDB::retrieve(Patron& target) {
    map<int,Patron*>::iterator it = patrons.begin();
    it = patrons.find(target.getID());
    return it->second;
}
//----------------------------------------------------------------------------
/*
*/
Patron* PatronDB::retrieve(string name) {
    string firstName;
    string lastName;
    stringstream ss(name);
    
    if(ss >> firstName >> lastName) {
        Patron* current;
        map<int,Patron*>::iterator it = patrons.begin();
        while(it != patrons.end()) {
            current = it->second;
            if(current->getName() == name) {
                return current;
            }
        }
    }

    return NULL;
}
//----------------------------------------------------------------------------
/*
*/
Patron* PatronDB::retrieve(int pid) {
    map<int,Patron*>::iterator it = patrons.begin();
    it = patrons.find(pid);
	if(it == patrons.end()) {
		return NULL;
	}
    return it->second;
}
//----------------------------------------------------------------------------
/*
*/
void PatronDB::build(ifstream& infile) {
    int id;
    string firstName;
    string lastName;
    Patron* temp;
    while(!infile.eof()) {
        if(infile >> id >> lastName >> firstName) {
            temp = new Patron(id, firstName, lastName);
            insert(temp);
            temp = NULL;
            continue;
        }
    }
}
//----------------------------------------------------------------------------
/*
*/
void PatronDB::display() {
    map<int,Patron*>::iterator it = patrons.begin();
    while(it != patrons.end()) {
        cout << *it->second;
        it++;
    }
}
