#include "youth.h"

Youth::Youth(string author, string title, int year, char edition) : 
	Book(author,title,year,edition) {
    pubType = 'Y';
}


Youth::~Youth()
{
}
//----------------------------------------------------------------------------
/*
operator== function

Checked for equality of youth objects

Youth are equal if they share the same address space or if the following
parameters are equal:
Title, Author, Type, Edition
*/
bool Youth::operator==(const Publication & rhs) const {
    if(this == &rhs) {
        return true;
    }
	//must try and cast all parameters as youth
    const Youth& rightHS = static_cast<const Youth&>(rhs);
	//If the object is NULL, casting failed and object can't be compared
    if(&rightHS == NULL) {
        return false;
    }
    return rightHS.pubTitle == pubTitle && 
		rightHS.pubAuthor == pubAuthor && 
		pubType == rightHS.pubType && rightHS.pubEdition == pubEdition;
}
//----------------------------------------------------------------------------
/*
opertor< function

Function for determining if this is smaller than the RHS object

Youth are smaller if the title is less than the RHS title.
If equal, the authors are compared.
*/
bool Youth::operator<(const Publication& rhs) const {
    if(this == &rhs) {
        return false;
    }
	//must try and cast all parameters as youth
    Youth rightHS = dynamic_cast<const Youth&>(rhs);
	//If the object is NULL, casting failed and object can't be compared
    if(&rightHS == NULL) {
        return false;
    }
    if(pubTitle < rightHS.pubTitle) {
        return true;
    } else {
        if(rightHS.pubTitle == pubTitle) {
            return pubAuthor < rightHS.pubAuthor;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
/*
displayTitle function

In order to display Object specific titles when outputing all objects,
the object itself will store the heading. This allows each object
to display different headings if necessary
*/
void Youth::displayTitle() const {
	cout << setiosflags(ios::left);
	cout << "Youth:" << endl;
	cout << setw(AVAIL_OUT_WIDTH) << "AVAIL" 
        << setw(TITLE_OUT_WIDTH) << "TITLE" 
        << setw(AUTHOR_OUT_WIDTH) << "AUTHOR" 
        << setw(YEAR_OUT_WIDTH) << "YEAR" << endl;
}

ostream & operator<<(ostream& outstream, const Youth& input) {
    outstream.setf(ios::left, ios::adjustfield);
    outstream  
        << setw(input.TITLE_OUT_WIDTH) 
		<< input.pubTitle.substr(0, input.TITLE_OUT_WIDTH) 
        << setw(input.AUTHOR_OUT_WIDTH) 
		<< input.pubAuthor.substr(0, input.AUTHOR_OUT_WIDTH-1) 
		<< input.pubDateYear << endl;
    return outstream;
}

void Youth::display(bool showCOunt) const {
	cout << setiosflags(ios::left);
    if(showCOunt) {
        cout << setw(AVAIL_OUT_OFFSET) << " " 
			<< setw(AVAIL_OUT_WIDTH-AVAIL_OUT_OFFSET) << available();
    }
    cout << *this;
}
