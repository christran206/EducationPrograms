#include "nodedata.h"
#include <iomanip>
//---------------------------------------------------------------------------
/*
GraphL class: Given a number of nodes and node edges, this class provides
the ability to display Node information and edges and a function to
display a Depth First Search representation of the Class with source node 
at Node1

-- Reads node information from a text file
-- Provides information for all Nodes and Node Source Edges
-- Provides function to display Depth First Search
Assumptions:
-- Insert edge does not have ability to insert a vertex/node
-- Supports a maximum of 99 Nodes (100-1) as 0 index is unused
-- Nodes can have an edge to itself
-- Does not allow duplicate edges

*/
//----------------------------------------------------------------------------
class GraphL {
    static const int MAXNODES = 100;
public:
    GraphL();
    ~GraphL();

    void buildGraph(istream&);	//Builds Nodes and Edges from file
    void depthFirstSearch();	//Displays Class using DepthFirstSearch
    void displayGraph();		//Shows all nodes and all edges
	void makeEmpty();			//Removes all nodes and edges

private:
    struct EdgeNode;
	struct GraphNode {
		EdgeNode* edgeHead;
		bool visited;
		NodeData* data;
	};
	struct EdgeNode {
		int adjGraphNode;
		EdgeNode* nextEdge;
	};

	bool insertEdge(int, int);	//Inserts an edge
	void depthFirstSearchHelper(int);//Recursive helper for DFS

    int size; // number of nodes in the graph 
	GraphNode adjList[MAXNODES];	//Adjacency List
	NodeData data[MAXNODES];		//NodeData container

};

