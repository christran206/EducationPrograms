#include "book.h"

Book::Book(string author, string title, int year, char edition):Publication()
{
    pubAuthor = author;
    pubTitle = title;
    pubDateYear = year;
    pubEdition = edition;
}


Book::~Book() {
}

//----------------------------------------------------------------------------
/*
Operator<<

Outputs the information from the Book class.
Contents:
Title, Author, Year
*/
/*
ostream& operator<<(ostream& ostream, const Book& input) {
    ostream.setf(ios::left, ios::adjustfield);
    ostream  << setw(input.TITLE_OUT_WIDTH) 
		<< input.pubTitle.substr(0, input.TITLE_OUT_WIDTH) 
		<< setw(input.AUTHOR_OUT_WIDTH) 
		<< input.pubAuthor.substr(0, input.AUTHOR_OUT_WIDTH-1) 
		<< input.pubDateYear << endl;
    return ostream;
}
*/
//----------------------------------------------------------------------------
/*
Display
Helper job to assist in creating a virtual function for Publications
Each class will implement similarly

Bool parameter enables the available count.

utilizes the output<< for the remaining output
*/
/*
void Book::display(bool showCOunt) const {
	cout << setiosflags(ios::left);
    if(showCOunt) {
        cout << setw(AVAIL_OUT_OFFSET) << " " 
			<< setw(AVAIL_OUT_WIDTH-AVAIL_OUT_OFFSET) << available();
    }
    cout << *this;
}
*/
