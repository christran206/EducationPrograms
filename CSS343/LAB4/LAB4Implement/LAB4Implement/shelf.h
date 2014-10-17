#ifndef SHELF_H
#define SHELF_F

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "bintree.h"
#include "publications.h"
/*---------------------------------------------------------------------------
Shelf Class
Self implemented basic hash with containers storing Publication objects
in sorted order.

Features:
	--Insert any derived Publication object
	--retrieve any derived publication object
Assumptions:
    --User does not have to specify where the object gets placed, it's
	handled automatically based on char type
---------------------------------------------------------------------------*/

using namespace std;
class Shelf {
public:
    Shelf();
    ~Shelf();

    bool insert(Publication*);//Insert publication
    Publication& retrieve(const Publication&) ;//Retrieve publication
    void display() ; //Display all contents

    void buildShelf(ifstream&);//Build Publication objects from file
private:
    vector<BinTree*> shelves;	//Vector holding binary trees
    BinTree** getTree(char);	//Command to get tree to insert or retrieve
};
#endif
