#ifndef PUBLICATIONPROCESSOR_H
#define PUBLICATIONPROCESSOR_H

#include <iostream>
#include <list>
#include "shelf.h"
#include "processor.h"
using namespace std;

//---------------------------------------------------------------------------
//  DATAREADER class:  a class that read  lab5data.txt
//                      and creates publication classes and stores them in
//						the shelf
//  Assumptions:
//		--Shelf supports the type of Publication being inserted
//---------------------------------------------------------------------------

class PublicationProcessor:public  Processor{


public:
    PublicationProcessor();                                  // default constructor
   virtual ~PublicationProcessor();                                 // destructor

   virtual bool readData(Shelf&, ifstream&);             // read and store the Client


private:

  
};
#endif
