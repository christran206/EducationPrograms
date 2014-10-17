#include "graphl.h"

using namespace std;
//----------------------------------------------------------------------------
GraphL::GraphL() {
	size = 0;
	for(int i = 0; i < MAXNODES; i++) {
		adjList[i].edgeHead = NULL;
		adjList[i].visited = false;
		adjList[i].data = & data[i];
	}
}

//----------------------------------------------------------------------------
GraphL::~GraphL() {
	makeEmpty();
}

//----------------------------------------------------------------------------
/* Function buildGraph
Takes a properly formatted text input and creates class data
Properly formatted definition
First line contains an int of the number of nodes
Followed by a number of lines equal to the first line with node descriptions
followed by any number of three int with space delimiters
ends with a termination string of 0 0
*/
void GraphL::buildGraph(istream& infile) {
   int fromNode, toNode;              // from and to node ends of edge

   makeEmpty();                       // clear the graph of memory 

   infile >> size;     // read the number of nodes

   if (infile.eof()) return;          // stop if no more data
   
   string s;                          // used to read through to end of line
   getline(infile, s);

   // read graph node information
   for (int i=1; i <= size; i++) {
      // read using setData of the NodeData class,
      // something like: 
      //    adjList[i].data.setData(infile);
      // where adjList is the array of GraphNodes and
      // data is the NodeData object inside of GraphNode
       if(i > MAXNODES-1) {
			getline(infile,s);
		}
	   data[i].setData(infile);
   }
   if(size > MAXNODES-1) {
       size = MAXNODES-1;
   }
   // read the edge data and add to the adjacency list
   for (;;) {
      infile >> fromNode >> toNode;
      if (fromNode ==0 && toNode ==0) return;     // end of edge data
	  insertEdge(fromNode, toNode);
      // insert the edge into the adjacency list for fromNode

   }
}

//----------------------------------------------------------------------------
/* Function Depth First Search
Implementation of Depth First Search algorithm
Accesses every known node only once
*/
void GraphL::depthFirstSearch() {
	if(size == 0) {
		return;
	}
	cout << "Depth-first ordering:";
	for(int i = 1; i <= size; i++) {
		depthFirstSearchHelper(i);
	}
	//Sets visited bool to false to allow multiple function calls
	for(int i = 1; i <= size; i++) {
		adjList[i].visited = false;
	}
	cout << endl;
}
/*
Only operates on targets that have not been visited
Displays Node number before checking if adjacent edges need to be checked
*/
void GraphL::depthFirstSearchHelper(int target) {
	if(!adjList[target].visited) {
		adjList[target].visited = true;
		cout << " " << target;
		EdgeNode* current = adjList[target].edgeHead;
		while(current != NULL) {
			depthFirstSearchHelper(current->adjGraphNode);
			current = current->nextEdge;
		}
	}
}

//----------------------------------------------------------------------------
/* Function displayGraph
Shows all nodes, node descriptions, all all edges origininating from nodes
*/
void GraphL::displayGraph() {
	if(size == 0) {
		return;
	}
	cout << "Graph:" <<endl;
	//iterate through all nodes and show edge information
	for(int i = 1; i <= size; i++) {
		cout << "Node " << setw(8) << left << i << *adjList[i].data << endl;
		EdgeNode* current = adjList[i].edgeHead;
		//keep moving pointer through adjacent items in list
		//and output
		while(current != NULL) {
			cout << setw(7) << right << "edge " << i 
                << " " << current->adjGraphNode << endl;
			current = current->nextEdge;
		}
	}
}

//----------------------------------------------------------------------------
/* Function makeEmpty
Iternate through all GraphNodes and delete the EdgeNode memory
*/
void GraphL::makeEmpty() {
	EdgeNode* current;
	for(int i = 1; i <= size; i++) {
		while(adjList[i].edgeHead != NULL) {
			current = adjList[i].edgeHead;
			adjList[i].edgeHead = adjList[i].edgeHead->nextEdge;
			delete current;
		}
		adjList[i].visited = false;
	}
	size = 0;
}

//----------------------------------------------------------------------------
/* Function insertEdge
Inserts edge by creating EdgeNode data and inserting it in the front of
the list stored in the GraphNodes
Does not allow inserting edges to nodes that do not already exist
Allows edges to have the same source and destination
*/
bool GraphL::insertEdge(int source, int dest) {
	if(source <= 0 ||
		source > size ||
		dest <= 0 ||
		dest > size) {
			return false;
	}
	//Check if duplicate edge
	EdgeNode* current;
	current = adjList[source].edgeHead;
	while(current != NULL) {
		if(dest == current->adjGraphNode) {
			return false;
		}
		current = current->nextEdge;
	}
	//Always inserts new EdgeNode at the head of the list
	//in the GraphNodes
	EdgeNode* newEdge = new EdgeNode();
	newEdge->adjGraphNode = dest;
	if(adjList[source].edgeHead == NULL) {
		adjList[source].edgeHead = newEdge;
		newEdge->nextEdge = NULL;
		return true;
	}
	newEdge->nextEdge = adjList[source].edgeHead;
	adjList[source].edgeHead = newEdge;
	return true;
}
