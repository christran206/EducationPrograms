#include "shelf.h"

Shelf::Shelf() {
}

Shelf::~Shelf() {
    vector<BinTree*>::iterator it = shelves.begin();
    while(it != shelves.end()) {
        delete *it;
        ++it;
    }
}
//----------------------------------------------------------------------------
/*
insert function

Inserts a Publication into the container
*/
bool Shelf::insert(Publication* pubIn) {
	//get tree based on the character of the publication
    BinTree* bookShelf = *getTree(pubIn->getType());
	//inser the publication into the container
    return bookShelf->insert(pubIn);
}
//----------------------------------------------------------------------------
/*
Retrieve function

Retrieves a reference of an object inside the shelf based on publication
equality

Returns a NULL object if failed
*/
Publication& Shelf::retrieve(const Publication& target) {
	//Make a temp NULL to return if no object found
    Publication* temp = NULL;
	//get the proper tree
    BinTree* bookShelf = *getTree(target.getType());
	//If the tree is NULL, it does't exist
    if(bookShelf != NULL) {
		//get object within tree
        bookShelf->retrieve(target,temp);
    }
    return *temp;
}
//----------------------------------------------------------------------------
/*
getTree function

Takes in a char and finds the proper offset in the container that has the
proper tree.

Returns a pointer to a pointer to a BinTree
*/
BinTree** Shelf::getTree(char type)
{
	//if the size is too small, resize the container and make a new tree
    if((type - 'A') > (int)shelves.size()) {
        shelves.resize(type - 'A' + 1);
        shelves.at(type - 'A') = new BinTree();
    } else {
		//If there is no tree, instantiate a new one
        if(shelves.at(type - 'A') == NULL) {
            shelves.at(type - 'A') = new BinTree();
        }
    }
    return &shelves.at(type - 'A');
}
//----------------------------------------------------------------------------
/*
display function

Goes through the entire container and displays the Tree information
*/
void Shelf::display() {
	//Create an interator
    vector<BinTree*>::iterator it = shelves.begin();
	//Loop until reaching the end of container
    while(it != shelves.end()) {
		//Skip any null indexes
        if(*it == NULL) {
            ++it;
            continue;
        }
		//display the tree
        (*it)->display();
        ++it;
    }
}
//----------------------------------------------------------------------------
/*
buildShelf function

Takes in a text file as a prameter and builds out Publication objects and
adds them into the container

Assumption is that data is properly formatted for intended publications
*/
void Shelf::buildShelf(ifstream& infile) {
    string temp;
    string pubTitle;
	int pubDateYear;
	char pubType;
    Publication* tempPub = NULL;
    while(!infile.eof()) {
		//Check if the first char can be assigned to variable
		//If it can't, obviously not a valid Publication
        if(infile >> pubType) {
			//Checks only known publications, all other chars are invalid
			//After finding the proper case, gather parameters within format
			//and build Publication objects to be inserted
            switch (pubType)
            {
            case 'F': {
                string pubAuthor;
				//Check for leading space
                if(infile.peek() == ' ') {
                    getline(infile,temp,' ');
                }
                getline(infile, pubAuthor, ',');
				//Check for leading space
                if(infile.peek() == ' ') {
                    getline(infile,temp,' ');
                }
                getline(infile, pubTitle, ',');
                infile >> pubDateYear;
                tempPub = new Fiction(pubAuthor,pubTitle,pubDateYear);
                insert(tempPub);
                break;
                      }
            case 'P': {
                int pubDateMonth;
				//Check for leading space
                if(infile.peek() == ' ') {
                    getline(infile,temp,' ');
                }
                getline(infile, pubTitle, ',');
                infile >> pubDateMonth >> pubDateYear;
                tempPub = new Periodical(pubTitle,pubDateMonth, pubDateYear);
                insert(tempPub);
                break;
                      }
            case 'Y': {
                string pubAuthor;
				//Check for leading space
                if(infile.peek() == ' ') {
                    getline(infile,temp,' ');
                }
                getline(infile, pubAuthor, ',');
				//Check for leading space
                if(infile.peek() == ' ') {
                    getline(infile,temp,' ');
                }
                getline(infile, pubTitle, ',');
                infile >> pubDateYear;
                tempPub = new Youth(pubAuthor,pubTitle,pubDateYear);
                insert(tempPub);
                break;
                      }
            default:
                tempPub = NULL;
                break;
            }
        } else {
            getline(infile,temp);
            continue;
        }
    }
	pubType = 0;
    tempPub = NULL;
}
