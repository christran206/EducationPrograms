#include "periodical.h"


Periodical::Periodical(string title, int month, int year, char edition)
{
    pubType = 'P';
    pubTitle = title;
    pubDateMonth = month;
    pubDateYear = year;
    pubEdition = edition;
	quantity = 1;
}


Periodical::~Periodical(void)
{
}

//----------------------------------------------------------------------------
/*
operator== function

Equality of periodicals is when both objects share the same memory space
or if the Title, Month Date, Year Date, Type, and edition match
*/
bool Periodical::operator==(const Publication & rhs) const {
    if(this == &rhs) {
        return true;
    }
    const Periodical& rightHS = static_cast<const Periodical&>(rhs);
    if(&rightHS == NULL) {
        return false;
    }
    return rightHS.pubTitle == pubTitle && 
		rightHS.pubDateYear == pubDateYear && 
		pubDateMonth == rightHS.pubDateMonth && 
		pubType == rightHS.pubType && rightHS.pubEdition == pubEdition;
}
//----------------------------------------------------------------------------
/*
operator< function

returns if this object is lesser than the RHS object

This object is lesser if the year is lessor, followed by the month,
then title
*/
bool Periodical::operator<(const Publication & rhs) const {
    if(this == &rhs) { //If same space, not lower than
        return false;
    }
	//Must cast
    Periodical rightHS = dynamic_cast<const Periodical&>(rhs);
	//If null, casting failed and can't be compared, return false
    if(&rightHS == NULL) {
        return false;
    }
	//Compare Year, Month, then Date
    if(pubDateYear < rightHS.pubDateYear) {
        return true;
    } else {
        if(pubDateYear == rightHS.pubDateYear) {
            if(pubDateMonth < rightHS.pubDateMonth) {
                return true;
            } else {
                if(pubDateMonth == rightHS.pubDateMonth) {
                    return pubTitle < rightHS.pubTitle;
                }
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------
/*
display function
Helper job to assist in creating a virtual function for Publications
Each class will implement similarly

Bool parameter enables the available count.

utilizes the output<< for the remaining output
*/
void Periodical::display(bool showCount) const {
	cout << setiosflags(ios::left);
    if(showCount) {
        cout << setw(AVAIL_OUT_OFFSET) << " " 
			<< setw(AVAIL_OUT_WIDTH-AVAIL_OUT_OFFSET) << available();
    }
    cout << *this;
}
//----------------------------------------------------------------------------
/*
operator<< function

Outputs Periodical iformation in the following order
Year, Month, Title
*/
ostream& operator<<(ostream& ostream, const Periodical& input) {
	ostream.setf(ios::left, ios::adjustfield);
    ostream << setw(input.YEAR_OUT_WIDTH) << input.pubDateYear 
		<< setw(input.MONTH_OUT_WIDTH) << input.pubDateMonth 
		<< setw(input.TITLE_OUT_WIDTH) 
		<< input.pubTitle.substr(0, input.TITLE_OUT_WIDTH) << endl;
    return ostream;
}
//----------------------------------------------------------------------------
/*
displaytitle function

In order to display Object specific titles when outputing all objects,
the object itself will store the heading. This allows each object
to display different headings if necessary
*/
void Periodical::displayTitle() const {
	cout << setiosflags(ios::left);
	cout << "Periodicals:" <<endl;
	cout << setw(AVAIL_OUT_WIDTH) << "AVAIL" << setw(YEAR_OUT_WIDTH) 
		<< "YEAR" << setw(MONTH_OUT_WIDTH) << "MO" 
		<< setw(TITLE_OUT_WIDTH) << "TITLE" << endl;
}
