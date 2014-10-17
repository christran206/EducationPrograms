#include "nodedata.h"
#include <iomanip>
#include <string>
#include <sstream>
#include <stack>

//---------------------------------------------------------------------------
/*
GraphM class: Given a number of nodes and information of the distance
    between the nodes, this class provides the optimal route
    if a path exists between nodes.

-- Reads node information from a text file
-- Provides information to all known nodes and possible paths to other nodes
-- Provides details on a specific route from one node to another
-- Provides function to add and remove edges
Assumptions:
-- No specific deconstructor is needed
-- INFINITE distance is considered to be a non-existant edge
-- Distance must be greater than 0 and less than INFINITE
-- INFINITE is defined as INT_MAX and can change based on system
-- Insert edge does not have ability to insert a vertex/node
-- Insert edge does not insert edge that can have distance of INFINITE
-- Remove Edge can not remove an edge that does not exist
-- Supports a maximum of 99 Nodes (100-1) as 0 index is unused

*/
//---------------------------------------------------------------------------
//----------------------------------------------------------------------------
class GraphM {
    static const int MAXNODES = 100;	//Maximum number of nodes supported
    static const int INFINITE = INT_MAX;//Class INFINTE representation

public:
    GraphM();
    ~GraphM();

    void buildGraph(ifstream&);		//Builds Nodes and Edges from file
    void findShortestPath();		//Finds shortests paths for all nodes
    void displayAll() ;		//Displays all known Node information
    void display(int, int) ;	//Displays path from one node to another
    bool isEmpty() const;			//Determines if there exists Nodes
    bool insertEdge(int, int, int);	//Inserts an edge to and from known nodes
    bool removeEdge(int, int);		//Removes an edge if it exists

private:
    struct TableType {
        bool visited;
        int dist;
        int path;
    };

    int findLowestRemainingNode(int);//Dijkstra's helper function
    void displayAllHelper(int, int, bool showDesc = false);//show node
    void resetTable();//Resets TableType and finds shortest paths
	bool insertEdgeHelper(int, int, int);//Changes adj matrix information

    NodeData data[MAXNODES]; // data for graph nodes information 
    int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix 
    int size; // number of nodes in the graph 
    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path 
    bool hasChanged;//Tracks if data changed to have T updated

};

