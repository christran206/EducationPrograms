#include "library.h"


Library::Library() {
}


Library::~Library()
{
}

int main() {
    Library UWLibrary;
    ifstream patrons("patrons.txt");
    ifstream actions("actions.txt");
    ifstream publications("publications.txt");
    if(!patrons || !actions || !publications) {
        cout << "File not found" << endl;
        return 1;
    }
    UWLibrary.buildPatrons(patrons);
    UWLibrary.buildShelf(publications);
    UWLibrary.buildActions(actions);
    UWLibrary.runLibrarian();
    return 0;
};