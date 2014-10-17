#include "fiction.h"


Fiction::Fiction(string author, string title, int year, char edition) 
	: Book(author,title,year,edition)
{
    pubType = 'F';
}


Fiction::~Fiction(void)
{
}
//----------------------------------------------------------------------------
/*
operator== Virtual Function

For the Function Class, operator will check equality of the title, type, 
and edition as found in the Action inut text files
*/
bool Fiction::operator==(const Publication & rhs) const {
    if(this == &rhs) {
        return true;
    }
    const Fiction& rightHS = static_cast<const Fiction&>(rhs);
    if(&rightHS == NULL) {
        return false;
    }
    return rightHS.pubTitle == pubTitle && 
		rightHS.pubAuthor == pubAuthor && 
		pubType == rightHS.pubType && rightHS.pubEdition == pubEdition;
}
//----------------------------------------------------------------------------
/*
operator< Virtual Function

Fiction objects are to be sorted by author and then title
*/
bool Fiction::operator<(const Publication& rhs) const {
    if(this == &rhs) {
        return false;
    }
	//Must cast as a Fiction Object to check equality
    Fiction rightHS = dynamic_cast<const Fiction&>(rhs);
    if(&rightHS == NULL) {
        return false;
    }
    if(pubAuthor < rightHS.pubAuthor) {
        return true;
    } else {
		//Must check equality of author before checking title
        if(rightHS.pubAuthor == pubAuthor) {
            return pubTitle < rightHS.pubTitle;
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
void Fiction::displayTitle() const {
	cout << setiosflags(ios::left);
	cout << "Fiction:" << endl;
	cout << setw(AVAIL_OUT_WIDTH) << "AVAIL" 
        << setw(AUTHOR_OUT_WIDTH) << "AUTHOR" 
        << setw(TITLE_OUT_WIDTH) << "TITLE" 
		<< setw(YEAR_OUT_WIDTH) << "YEAR" << endl;
}

ostream& operator<<(ostream& ostream, const Fiction& input) {
    ostream.setf(ios::left, ios::adjustfield);
    ostream  
		<< setw(input.AUTHOR_OUT_WIDTH) 
		<< input.pubAuthor.substr(0, input.AUTHOR_OUT_WIDTH-1) 
        << setw(input.TITLE_OUT_WIDTH) 
		<< input.pubTitle.substr(0, input.TITLE_OUT_WIDTH) 
        << input.pubDateYear << endl;
    return ostream;
}

void Fiction::display(bool showCOunt) const {
	cout << setiosflags(ios::left);
    if(showCOunt) {
        cout << setw(AVAIL_OUT_OFFSET) << " " 
			<< setw(AVAIL_OUT_WIDTH-AVAIL_OUT_OFFSET) << available();
    }
    cout << *this;
}
