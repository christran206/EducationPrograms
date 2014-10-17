#ifndef TEST
#define TEST
//#include "shelf.h"
#include "patrondb.h"
#include "library.h"

int main() {
    ifstream comfile("data4commands.txt");
    if (!comfile) {
        cout << "File could not be opened." << endl;
        return 1;
    }

	ifstream bookfile("data4books.txt");
    if (!bookfile) {
        cout << "File could not be opened." << endl;
        return 1;
    }

	ifstream patfile("data4patrons.txt");
    if (!patfile) {
        cout << "File could not be opened." << endl;
        return 1;
    }

	Library library;
    library.buildShelf(bookfile);
    library.buildPatron(patfile);
    library.doAction(comfile);
    return 0;
};
#endif
