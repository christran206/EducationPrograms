#ifndef ACTIONPROCESSOR_H
#define ACTIONPROCESSOR_H

#include <iostream>
#include <queue>
#include "processor.h"
#include "action.h"
#include "actionlist.h"
using namespace std;

//---------------------------------------------------------------------------
//  DATAREADER class:  a class that read  lab5data.txt
//                      and creates the action classes to be used by
//						librarian
//  Assumptions:
//		--Data in text file is formatted properly
//		--Imporperly formatted data is ignored
//   
//---------------------------------------------------------------------------

class ActionProcessor:public  Processor{


public:
    ActionProcessor();                                  // default constructor
   virtual ~ActionProcessor();                                 // destructor

   virtual bool readData(ActionList&, ifstream&);             // read and store the Client


private:

  
};
#endif
