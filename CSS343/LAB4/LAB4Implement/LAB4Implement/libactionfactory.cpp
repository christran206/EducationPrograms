#include "libactionfactory.h"


LibActionFactory::LibActionFactory() {
    actionMap.insert(make_pair('C', new CheckOut()));
    actionMap.insert(make_pair('R', new CheckIn()));
    actionMap.insert(make_pair('H', new HistoryDisplay()));
}


LibActionFactory::~LibActionFactory() {
	//Iterates through all map indexes and deletes object in second pair
    map<char,LibAction*>::iterator it = actionMap.begin();
    while(it != actionMap.end()) {
        delete it->second;
        it++;
    }
}


//----------------------------------------------------------------------------
/*
getAction function

returns a pointer to the object stored in a char mapping. If no index is
found, the end of the map is given and any function calling must account
for the possibility of not recieving an actual command
*/
LibAction* LibActionFactory::getAction(char type) {
    return actionMap.find(type)->second;
}
