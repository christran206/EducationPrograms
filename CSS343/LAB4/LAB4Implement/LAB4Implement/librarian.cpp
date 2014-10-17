#include "librarian.h"


Librarian::Librarian(Shelf& inputShelf, PatronDB& inputPDB) {
    shelf = &inputShelf;
    pdb = &inputPDB;
}


Librarian::~Librarian() {
}
//----------------------------------------------------------------------------
/*
processAction function

Processes the command text file in sequence. Since we have specialized input
a specialized function is used to process the input and execute the commands.



Programmer notes:
Avoided the use of a queue of specialized objects as once I wrote the code,
it seemed better to execure the commands instead of storing objects
to run later.
*/
void Librarian::processActions(ifstream& infile) {
    Patron* patron;
    Publication* pub;
    while(!infile.eof()) {
        string temp;
        char action;
        string title;
        infile >> action;
        //if within set to known actions, carry on, otherwise skip line
        switch (action)
        {
        case 'C':
        case 'R':
            lAction = laf.getAction(action);
            int ID;
            char pubType;
            char pubEdition;
            if(infile >> ID >> pubType >> pubEdition) {
                
                patron = pdb->retrieve(ID);
                if(patron == NULL) {
                    continue;
                }
                switch (pubType)
                {
                case 'F':
                case 'Y':
                    {
                        string name;
                        if(pubType == 'F'){
                            if(infile.peek() == ' ') {
                                getline(infile,temp,' ');
                            }
                            getline(infile,name,',');
                            if(infile.peek() == ' ') {
                                getline(infile,temp,' ');
                            }
                            getline(infile,title,',');
                            pub = &shelf->retrieve(Fiction(name,title,0,pubEdition));
                            if(pub == NULL) {
                                cout << "Checkout/Return of Book Not Found" << endl;
                                break;
                            }
                            lAction->perform(*patron, *pub);
                        }
                        if(pubType == 'Y'){
                            if(infile.peek() == ' ') {
                                getline(infile,temp,' ');
                            }
                            getline(infile,title,',');
                            if(infile.peek() == ' ') {
                                getline(infile,temp,' ');
                            }
                            getline(infile,name,',');
                            pub = &shelf->retrieve(Youth(name,title,0,pubEdition));
                            if(pub == NULL) {
                                cout << "Checkout/Return of Book Not Found" << endl;
                                break;
                            }
                            lAction->perform(*patron, *pub);
                        }
                        break;
                    }
                case 'P':
                    {
                        int year,month;
                        infile >> year >> month;
                        if(infile.peek() == ' ') {
                                getline(infile,temp,' ');
                        }
                        getline(infile,title,',');
                        pub = &shelf->retrieve(Periodical(title,month,year));
                        if(pub == NULL) {
                            cout << "Checkout/Return of Periodical Not Found" << endl;
                            break;
                        }
                        lAction->perform(*patron, *pub);
                        break;
                    }
                default:
                    break;
                }
            }
            
            break;
        case 'D':
            shelf->display();
            break;
        case 'H':
            lAction = laf.getAction(action);
            {
                int ID;
                infile >> ID;
                patron = pdb->retrieve(ID);
                if(patron != NULL) {
                    patron->displayHistory();
                } else {
                    cout << "Patron with ID: " << ID << "does not exist" << endl;
                }
                patron = NULL;
                break;
            }
        default:
            getline(infile,temp);
            break;
        }
		action = 0;
    }
}
