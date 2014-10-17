#ifndef YOUTH_H
#define YOUTH_H
#include "book.h"
//-----------------------------------------------------------------------------
/*  Youth class:	Child of the book class that is a child of publication
    Youth class extends the parent classes by implementing the required
	sorting requirements.
Features:
	--allow users to compare to another publication with the equality operator
	--allow users to compare to another publication with the less than operator
Assumptions:
	--Must implements operator< and operator==
    --Sort by title, then by author
*/
//-----------------------------------------------------------------------------
class Youth :
    public Book
{
    friend ostream & operator<<(ostream &, const Youth&);
public:
    Youth(string, string, int,char edition = 'H');
    ~Youth();
    
	virtual void displayTitle() const;
    void display(bool showCount = false) const;
	virtual bool operator==(const Publication&) const;
	virtual bool operator<(const Publication&) const;
private:

};
#endif
