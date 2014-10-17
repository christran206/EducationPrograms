/*---------------------------------------------------------------------------
BookType
Contains all possible editions of publications

Features:
    --Allows set and retrieval function
Assumptions:
    
---------------------------------------------------------------------------*/
#ifndef PUBLICATIONTYPE
#define PUBLICATIONTYPE

#include <string>
#include <iostream>
using namespace std;


class PublicationType {
public:
    PublicationType(char);
    ~PublicationType();

    bool setType(char);
    char getType();
private:
    char edition;

};

#endif

