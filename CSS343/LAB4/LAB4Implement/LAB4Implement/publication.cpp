#include "publication.h"


Publication::Publication()
{
    pubDateYear = 0;
    quantity = STARTQTY;
    numOut = 0;
}


Publication::~Publication()
{
}
//----------------------------------------------------------------------------
/*
CheckOut function

Returns if a publication was checked out.
*/
bool Publication::checkOut() {
	//Check if publication can be checked out
    if(canCheckOut()) {
		//increase number of publications out
        numOut++;
        return true;
    } else {
        return false;
    }
}
//----------------------------------------------------------------------------
/*
CheckIn function

called to checkin and decrease the number of publications that are checked
out. It's expected that other functions will check for validity of a check in
*/
void Publication::checkIn() {
    if(numOut > 0) {
        numOut--;
    }
}
//----------------------------------------------------------------------------
/*
canCheckOut function

All publications share similar quantity restrictions. canCheckOut will
determine if there still exists a publication to checkout
*/
bool Publication::canCheckOut() const {
    return ((quantity - numOut) > 0);
}
//----------------------------------------------------------------------------
/*
getType Function
Return the character representing the type of Publication
*/
char Publication::getType() const {
    return pubType;
}
//----------------------------------------------------------------------------
/*
available function

returns an int indicating the number available to be checked out
*/
int Publication::available() const{
    return quantity - numOut;
}
//----------------------------------------------------------------------------
//NOT USED ANYMORE
/*
compareString function

In the event of case insensitive checking, this function can be used to 
determine if two strings are equal

*/
int Publication::compareString(string left, string right) {
	//Check lengths, if un-equal, automatically false
    int leftLength = left.length();
    int rightLength = right.length();
    int leftChar,rightChar;
    if(leftLength == rightLength) {
        for(int i = 0; i < (int)left.length(); i++) {
            leftChar = toupper(left[i]);
            rightChar = toupper(right[i]);
            if(leftChar != rightChar) {
                return leftChar - rightChar;
            }
        }
        return 0;
    } else {
        int lowest = min(leftLength,rightLength);
        for(int i = 0; i < lowest; i++) {
            leftChar = toupper(left[i]);
            rightChar = toupper(right[i]);
            if(leftChar != rightChar) {
                return leftChar - rightChar;
            }
        }
        return 1;
    }
}
