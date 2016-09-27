#include "Graph.h"
#include <string>
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

// Constructor
// Constructs an empty graph
Graph::Graph(){
	numVertex = 0;
}

// JOHN NON-TESTED
// Edited: 12/11 by John
// Delete
Graph::~Graph(){
	if(numVertex == 0){
		return;
	}
	else{
		int vertIt;
		int edgeIt;

		for(vertIt = 0; vertIt < vertices.size(); vertIt++){
			// ?? DEREFERANCE vertIt ??
			for(edgeIt = 0; edgeIt < vertices[vertIt].edges.size(); edgeIt++){
				// !! HOW DO I TELL IF AN EDGE EXISTS OR NOT? !!
					//delete vertices[vertIt].edges[edgeIt];
				}
			}
			//delete vertices[vertIt];
		}
	}

// MATT
// Reads a graph from a file
void Graph::readFromFile(string file){

}

// JOHN NON-TESTED
// Edited:: 12/11 by John
// Write a graph to a file
void Graph::writeToFile(string file){
	vector<Edge> pushedEdges;
	vector<Edge> writeEdge;
	Vertex writeVertex;
	ofstream writeFile; // !! error: aggregate 'std::ofstream writeFile' has incomplete type and cannot be defined !!
	bool breakLoop;
	
	writeFile.open(file);
	writeFile << numVertex << "\n";
	for(int i = 0; i < numVertex; i++){
		writeVertex = vertices[i];
		writeFile << writeVertex.name << ", " << writeVertex.value << "\n";
	}
	int edgeIt;
	for(int i = 0; i < numVertex; i++){
		// !! CAN I DO THIS? !!
		writeEdge = vertices[i].edges;
		for(edgeIt = 0; edgeIt < writeEdge.size(); edgeIt++){
			for(int it = 0; it < pushedEdges.size(); it++){
				if(writeEdge[edgeIt].name1 == pushedEdges[it].name1 && writeEdge[edgeIt].name2 == pushedEdges[it].name2){
					breakLoop = true;
				}
			}
			if(breakLoop != true){
				writeFile << writeEdge[edgeIt].name1 << ", " << writeEdge[edgeIt].name2 << ", " << writeEdge[edgeIt].weight << "\n";
				pushedEdges.push_back(writeEdge[edgeIt]);
			}
		}
	}
	writeFile.close();
}

// JOHN NON-TESTED
// Edited: 12/11 by John
// Checks if graph is empty
bool Graph::empty(){
	if(numVertex == 0){
		return true;
	}
	else{
		return false;
	}
}

// JOHN WIP
// Edited: 12/11 by John
// Add edge to graph
void Graph::addEdge(string v1, string v2, int weight){
	vector<Edge>::iterator edgeIt;
	vector<Vertex>::iterator vertIt;
	vector<Vertex>::iterator vertStore1;
	vector<Vertex>::iterator vertStore2;
	bool v1Hit, v2Hit;

	for(vertIt = vertices.begin(); vertIt != vertices.end(); vertIt++){
		// Edge already exists -> lower weight if weight is less than current
		// NEEDS WORK TO CHECK THOUGH ALL EDGES
		for(edgeIt = vertIt->edges.begin(); edgeIt != vertIt->edges.end(); edgeIt++){
			if(edgeIt->name1 == v1 && edgeIt->name2 == v2){
				// !! WILL WEIGHT VS WEIGHT FUCK UP? !!
				if(weight < edgeIt->weight){
					edgeIt->weight = weight;
					return;
				}
				else{
					return;
				}
			}
		}
		// Edge doesn't exist but vertices do -> make the edge
		// Vertex/Vertices don't exist -> don't make the edge
		if(vertIt->name == v1){
			v1Hit = true;
			vertStore1 = vertIt;
		}
		else if(vertIt->name == v2){
			v2Hit = true;
			vertStore2 = vertIt;
		}
	}
	if(v1Hit == true && v2Hit == true){
		Edge createdEdge;
		createdEdge.name1 = v1;
		createdEdge.name2 = v2;
		createdEdge.weight = weight;
		vertStore1->edges.push_back(createdEdge);
		vertStore2->edges.push_back(createdEdge);
	}
}

// MATT
// Add vertex to graph
void Graph::addVertex(string name, float val){

}

// Counts number of connected components
// Think separate graphs within the overall graph
int Graph::numConnectedComponents(){

}

// Check if graph is a tree
bool Graph::tree(){

}

// Finds the lowest weight component and prints out the links
void Graph::minWeightComponent(string src){

}

// JOHN UNTESTED
// Edited: 12/12 by John
// Depth First search
bool Graph::DFS(string source, string val){
	vector<Vertex> visited;
	// !! DO I HAVE TO INITLIZE A QUEUE? !!
	queue<Vertex> toSearch;
	Vertex sourceVertex;
	Vertex searching;
	int edgeIt;
	
	// If search and val are the same
	if(source == val){
		return true;
	}
	else{
		// Find the correct source vertex to start
		int vertIt;
		for(vertIt = 0; vertIt < vertices.size(); vertIt++){
			if(vertices[vertIt].name == source){
				// !! CAN I COPY VERTICES OVER WITHOUT OVERLOADING =OPERATOR? !!
				sourceVertex = vertices[vertIt];
			}
		}
		// Push source vertex on a queue to be searched
		toSearch.push(sourceVertex);
		// While there are still vertices to be searched, loop
		while(!toSearch.empty()){
			// Pull the front of the search queue out
			searching = toSearch.front();
			// If the vertex that's being search matches val, return true
			if(searching.name == val){
				return true;
			}
			// Push the vertex being searched onto a list of vertices that have already been visited
			visited.push_back(searching);
			// Pop off the vertex being searched from the list of vertices to be searched
			toSearch.pop();
			string vertexName;
			// Go down each edge that the searching vertex has
			for(edgeIt = 0; edgeIt < searching.edges.size(); edgeIt++){
				// Follow down the edge and get the vertex that connects to it
				vertexName = searching.edges[edgeIt].name2;
				for(vertIt = 0; vertIt < vertices.size(); vertIt++){
					if(vertices[vertIt].name == vertexName){
						sourceVertex = vertices[vertIt];
					}
				}
				// Check to see if the next vertex was visited yet
				bool visitedYet = false;
				for(vertIt = 0; vertIt < visited.size(); vertIt++){
					// !! CORRECT SNYTAX FOR sourceVertex->name? !!
					if(visited[vertIt].name == sourceVertex.name){
						visitedYet = true;
					}
				}
				// If the vertex hasn't be visited yet, push it onto the queue to be searched next
				if(visitedYet != true){
					toSearch.push(sourceVertex);
				}
			}
		}
		// If queue runs out of vertices to check, the search has failed
		return false;
	}
}

// MATT
// Breadth First search
bool Graph::BFS(string source, string val){

}

// Determines closeness of two nodes
// Each edge used ++1, no valid path = -1, look for minimum edges
int Graph::closeness(string v1, string v2){

}

// Partition
bool Graph::partitionable(){

}

// * Subgraph Test
bool Graph::isSubGraph(const Graph& g){

}

// Print Valued Path
void Graph::printPathCloseVal(float value){

}

int main(){
	return 0;
}