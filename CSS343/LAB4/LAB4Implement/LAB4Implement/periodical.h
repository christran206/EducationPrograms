#ifndef PERIODICAL_H
#define PERIODICAL_H
#include "publication.h"
/*---------------------------------------------------------------------------
Periodical Class	Child of Publication
Extends the publication class and adds an additonal class variable for
month. Periodicals have their own implemented comparison operators
based on sorting requirements

Features:
	--Display contents of Periodical
	--Can output using display function or operator<<
Assumptions:
	--Sorts by Month, Year, then title
---------------------------------------------------------------------------*/
class Periodical :
    public Publication
{
    friend ostream & operator<<(ostream &, const Periodical &);
public:
    Periodical(string, int, int,char edition = 'H');
    ~Periodical(void);

    virtual void display(bool showCount = false) const;
	virtual void displayTitle() const;
	virtual bool operator==(const Publication&) const;
	virtual bool operator<(const Publication&) const;
private:
	static const int MONTH_OUT_WIDTH = 3;
    int pubDateMonth;
};
#endif
