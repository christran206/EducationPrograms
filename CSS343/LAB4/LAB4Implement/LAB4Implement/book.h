#ifndef BOOK_H
#define BOOK_H
#include "publication.h"
/*---------------------------------------------------------------------------
Book Class	Child of Publication
Book have an additional variable containing the author name and a common
output operator.

Features:
	--Display output with and without available count
Assumptions:
	--All Books display in the same format even if they are sorted different
---------------------------------------------------------------------------*/
class Book :
    public Publication
{
    


public:
    Book(string, string, int, char edition = 'H');
    ~Book();

    void display(bool showCount = false) const = 0;	//Displays book information
	virtual void displayTitle() const = 0;
    virtual bool operator==(const Publication&) const = 0;
	virtual bool operator<(const Publication&) const = 0;
protected:
	
    static const int AUTHOR_OUT_WIDTH = 22;	//Max char output of author
    string pubAuthor;	//Book Author
};
#endif
