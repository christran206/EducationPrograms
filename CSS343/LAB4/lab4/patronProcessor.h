#ifndef PATRONPROCESSOR_H
#define PATRONPROCESSOR_H

#include <iostream>
#include <hash_map>
#include "patron.h"
#include "processor.h"
#include "patronlist.h"
using namespace std;

//---------------------------------------------------------------------------
//  DATAREADER class:  Reads information from a text file and creates
//						Patron Objects to be inserted into the PatronList
//  Features:
//    readData will need to be implemented in the children classes
//---------------------------------------------------------------------------

class PatronProcessor:public Processor{


public:
	PatronProcessor();                                  // default constructor
	virtual ~PatronProcessor();                                 // destructor

	virtual bool readData(PatronList&, ifstream&);             // read and store the Client


private:

  
};
#endif
