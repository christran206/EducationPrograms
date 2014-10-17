#include "library.h"


Library::Library() {
    librarian = new Librarian(bookshelf,pdb);
}


Library::~Library() {
    delete librarian;
    librarian = NULL;
}

void Library::buildPatron(ifstream& infile) {
    pdb.build(infile);
}

void Library::buildShelf(ifstream& infile) {
    bookshelf.buildShelf(infile);
}

void Library::doAction(ifstream& infile) {
    librarian->processActions(infile);
}
