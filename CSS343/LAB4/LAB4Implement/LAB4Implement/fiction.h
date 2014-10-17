#ifndef FICTION_H
#define FICTION_H
#include "book.h"
//-----------------------------------------------------------------------------
/*  Fiction class:	Child of the book class that is a child of publication
    Fiction class extends the book and publication classes by implementing
	the necessary sorting requirements
Features:
	--allow users to compare to another publication with the equality operator
	--allow users to compare to another publication with the less than operator
Assumptions:
	--Must implements operator< and operator==
    --Sorts by author then by title
*/
//-----------------------------------------------------------------------------
class Fiction :
    public Book
{
    friend ostream & operator<<(ostream &, const Fiction &);
public:
    Fiction(string, string, int, char edition = 'H');
    ~Fiction(void);

    virtual bool operator==(const Publication&) const;
	virtual bool operator<(const Publication&) const;
	virtual void displayTitle() const;
    void display(bool showCount = false) const;
private:
};
#endif
