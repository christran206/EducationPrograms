//---------------------------------------------------------------------------
/*  Processor class:	Pure Virtual Factory class
						Takes in a test file and creates objects for
						other classes

Features:
--Reads data from a text file and converts them into objects
--
Assumptions:
--
*/
//---------------------------------------------------------------------------
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
using namespace std;


class Processor {


public:
	Processor();                                  // default constructor
	virtual ~Processor();                                 // destructor

	virtual bool readData(ifstream&)    = 0     ;    // read and store the Client

private:

  
};
#endif
