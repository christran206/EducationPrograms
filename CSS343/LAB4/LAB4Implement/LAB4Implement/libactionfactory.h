#ifndef LIBACTIONFACTORY_H
#define LIBACTIONFACTORY_H
#include "libaction.h"
/*---------------------------------------------------------------------------
LibActionFactory
Instantiates all LibAction commands into a hash to allow caller to dynamically
choose which function to perform based on the char type action.

Features:
	--returns an action associated with a char or else returns NULL
Assumptions:
	--Instances stored in a container to avoid repeating creating of objects
---------------------------------------------------------------------------*/
class LibActionFactory
{
public:
	LibActionFactory();
	~LibActionFactory();

	LibAction* getAction(char type);	//Retrieves instance of Action

private:
    map<char,LibAction*> actionMap;	//Map STL storing Actions
};
#endif
