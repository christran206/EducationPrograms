#include "graphm.h"

using namespace std;

//----------------------------------------------------------------------------
/*  Default Constructor
Necessary to set all values to defaults
INFINITE is considered to be a non-existing edge

*/
GraphM::GraphM() {
    
    //Initialize adjacency matrix to INFINITE to indicate no known paths
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            C[i][j] = INFINITE;
        }
    }

    //Initialize size variable to 0
    size = 0;

    hasChanged = false;

    //Initialize all TableType data to default values
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            T[i][j].visited = false;
            T[i][j].dist = INFINITE;
            T[i][j].path = 0;

        }
    }
}

//----------------------------------------------------------------------------
/*  De-Constructor
No function necessary at this point as all data is on the stack and gets
deleted at termination
*/
GraphM::~GraphM() {

}

//----------------------------------------------------------------------------
/*  Function buildGraph
Takes in a properly formatted text file and builds the NodeData array
and adjacency matrix
*Properly Formatted Definition*
First line contains an int of the number of nodes
Followed by a number of lines equal to the first line with node descriptions
followed by any number of three int with space delimiters
ends with a termination string of 0 0 0
*/
void GraphM::buildGraph(ifstream& infile) {
    //Known data starts with an int of size
    //size could possibly be larger than MAXNODES
    infile >> size;

	if (infile.eof()) { 
		return;
	}
	string temp;
    getline(infile,temp);

    //Create NodeData in data array
    for(int i = 1; i <= size; i++) {
		//if data is attempted to be inserted in space outside of array
		//data must still be read and ignored
		if(i > MAXNODES-1) {
			getline(infile,temp);
		}
        data[i].setData(infile);
    }
    //If the size is larger than MAXNODES-1, reset to maximum of MAXNODES-1
    if(size > MAXNODES-1) {
        size = MAXNODES-1;
    }
    hasChanged = true;
    while(!infile.eof()) {
        int source, destination, value;
        infile >> source >> destination >> value;

        //termination clause of 0 0 0
        if(source == 0 && destination == 0 && value == 0) {
            break;
        }
        //Only positive value input is allowed.
        //value given can't be zero since two different nodes
        //can't have value of 0 between them.
        if(value < 0) {
            continue;
        }
        //If there is invalid data, skip the data.
        //Data is invalid is there is a negative value given or 
        //if source or destination is more than size
        if(source < 0 || 
            source > size ||
            destination < 0 ||
            destination > size ||
            value < 0) {
            continue;
        }
        //set values found in text file into adjacency matrix
        C[source][destination] = value;
    }
}

//----------------------------------------------------------------------------
/*	Function findShortestpath
Implementation of Dijkstra's shortest path algorithm
Find the shortest possible path from every node to every other node
This function does not check for valid data. It's expected that other
functions check data integrity before executing this function
*/
void GraphM::findShortestPath() {
    //If class has not changed, no need to execute
    if(!hasChanged) {
        return;
    }
    //if empty, nothing to do
    if(isEmpty()) {
        return;
    }
    for(int cNode = 1; cNode <= size; cNode++) {
		//First step
        //set from node to itself to zero and visited
        T[cNode][cNode].visited = true;
        T[cNode][cNode].dist = 0;
        T[cNode][cNode].path = 0;
        //set table with known adjacent edges to begin with
        for(int adj = 1; adj <= size; adj++) {
            if(C[cNode][adj] < INFINITE) {
                T[cNode][adj].dist = C[cNode][adj];
                T[cNode][adj].path = cNode;
            }
        }
        //find the first lowest distance node that hasn't been visited
        int lowestNode = findLowestRemainingNode(cNode);
        //Keep processing while lowestNode is not itself
        //Only a node to itself can be 0
        while(lowestNode != cNode) {
			//Set node to visited to be ignored if found again
            T[cNode][lowestNode].visited = true;
            for(int lAdj = 1; lAdj <= size; lAdj++) {
				//Path to node doesn't exist if path is infinite
                if(C[lowestNode][lAdj] == INFINITE) {
                    continue;
                }
                int newDist = T[cNode][lowestNode].dist + C[lowestNode][lAdj];
                if(T[cNode][lAdj].dist > newDist) {
                    T[cNode][lAdj].dist = newDist;
                    T[cNode][lAdj].path = lowestNode;
                }
            }
            lowestNode = findLowestRemainingNode(cNode);
        }

    }

}

//----------------------------------------------------------------------------
/*  Function displayAll
Displays all node information
-Description of Node
-Paths to all nodes (Existing and Non-Existing)
*/
void GraphM::displayAll() {
	//Nothing to display if there are no nodes
	if(isEmpty()) {
        return;
    }
    resetTable();
    cout << setw(31) << left << "Description" << setw(11) << left 
        << "From node" << setw(10) << left << "To node" 
        << "Dijkstra's Path" << endl;
	//Must go through every node
    for(int source = 1; source <= size; source++) {
		//Object has implementation for operator<<
        cout << data[source] << endl;
		//Check path from node to every other node
        for(int dest = 1; dest <= size; dest++) {
			//No need to check distance to itself
            if(source == dest) {
                continue;
            }
            cout << setw(33) << " ";
            displayAllHelper(source, dest);
        }
    }
}

//----------------------------------------------------------------------------
/*	Function displayAllHelper

*/
void GraphM::displayAllHelper(int source, int dest, bool showDesc)  {
	//Check if source and destination is valid
    if(source <= 0 ||
        source > size ||
        dest <= 0 ||
        dest > size) {
            return;
    }
    int distance = T[source][dest].dist;
    if(distance == INFINITE) {
        cout << "   "<< setw(8) << source 
            << setw(8) << dest << "----" << endl;
        return;
    }
    cout << "   " << setw(8) << source 
        << setw(8) << dest << setw(10) << distance;
	//Create stack of ints
    stack<int> path;
	stack<int> descriptions;
	//Destination to be pushed first
    path.push(dest);
    int current = dest;
	//Starting with the destination, check the path to Node
	//until route to node is itself
    while(current != source) {
        path.push(T[source][current].path);
        current = T[source][current].path;
    }
	//If the function is to show descriptions, copy the path stack
	//to iterate through later
	if(showDesc) {
		descriptions = path;
	}
	//Pop the stack showing the proper order of nodes
    while(!path.empty()) {
        cout << " " << path.top();
        path.pop();
    }
	//Pop the stack and use the output operator of NodeData
	if(showDesc) {
		cout << endl;
		while(!descriptions.empty()) {
			cout << data[descriptions.top()] << endl;
			descriptions.pop();
		}
	}
    cout << endl;
}

//----------------------------------------------------------------------------
/*	Function display
Using displayall helper, show the same information in addition to
descriptions of each node
*/
void GraphM::display(int source, int dest)  {
    resetTable();
    if(T[source][dest].dist == INFINITE) {
        return;
    }
    displayAllHelper(source,dest,true);
}

//----------------------------------------------------------------------------
/*
	Function insertEdge
Adds an edge from one node to another node and returns bool value indicating
success or failure
Only capable of adding an edge to known nodes and does not allow edges to
nodes unknown
Allows replacement of existing edges
Does not allow inserting edge of distance defined as INFINITE
*/
bool GraphM::insertEdge(int source, int dest, int dist) {
	//unable to insert edge of INFINITE distance
	if(dist == INFINITE) {
		return false;
	}
	return insertEdgeHelper(source, dest, dist);
    
}

//----------------------------------------------------------------------------
/*	Function insertEdge
Removes an edge if it exists
If an edge does not exist, function returns false
*/
bool GraphM::removeEdge(int source, int dest) {
	//If edge doesnt exist (equal to INFINITE)
	//edge does not exist to be removed
	if(C[source][dest] == INFINITE) {
		return false;
	}
    return insertEdgeHelper(source,dest,INFINITE);
}

//----------------------------------------------------------------------------
/*	Helper Function to insert edge
Sets the adjacency matrix to reflect the change
Function is private and other functions that call must check distance data
*/
bool GraphM::insertEdgeHelper(int source, int dest, int dist) {
	if(source <= 0 ||
        source > size ||
        dest <= 0 ||
        dest > size ||
        dist < 1) {
            return false;
    }
    C[source][dest] = dist;
    hasChanged = true;
	return true;
}
//----------------------------------------------------------------------------
//Funtion isEmpty
//Returns true if there are any nodes
bool GraphM::isEmpty() const {
    return size == 0;
}

//----------------------------------------------------------------------------
//Finds the next lowest nonvisted adjacent Node
//If all nodes are visited, return itself
int GraphM::findLowestRemainingNode(int source) {
    int lowest = source;
    int value = INFINITE;
    for(int i = size; i > 0; i--) {
        //Skip when reaching to compare itself
        if(i == source) {
            continue;
        }
        if(C[source][i] < value) {
            //skip if node has been visited
            if(T[source][i].visited) {
                continue;
            } else {
                lowest = i;
                value = T[source][i].dist;
            }
        }
    }
    return lowest;
}

//----------------------------------------------------------------------------
/* Function resetTable
Resets table by setting Table values to defaults before 
finding shortests paths
This is necessary when changes are made to adjacency matrix
*/
void GraphM::resetTable() {
    if(hasChanged) {
        for(int i = 0; i < MAXNODES; i++) {
            for(int j = 0; j < MAXNODES; j++) {
                T[i][j].visited = false;
                T[i][j].dist = INFINITE;
                T[i][j].path = 0;

            }
        }
        findShortestPath();
        hasChanged = false;
    }
}
