#include "Graph.h"
#include <string>
#include <iostream>

using namespace std;

// Constructor
// Constructs an empty graph
Graph::Graph(){
	numVertex = 0;
}

// JOHN NON-TESTED
// Delete
Graph::~Graph(){
	if(numVertex == 0){
		break;
	}
	else{
		vector<Vertex>::iterator vertIt;
		vector<Edge>::iterator edgeIt;
		for(vertIt = vertices.begin(); vertIt != vertices.end(); vertIt++){
			// ?? DEREFERANCE vertIt ??
			for(edgeIt = vertIt->edges.begin(); edgeIt != vertIt->edges.end; edgeIt++){
				if(edgeIt != nullptr){
					delete edgeIt;
				}
			}
			delete vertIt;
		}
	}
}

// MATT
// Reads a graph from a file
void Graph::readFromFile(string file){


	if(numVertex > 0)
        {
                for(int m = 0; m<numVertex; m++)
                        vertices.pop_back();
                numVertex = 0;
        }
        ifstream File;
        File.open(file);
        File>>numVertex;
        string line;
        string word;
        string value;
        string name;
        float num;
        for(int i = 0; i<numVertex; i++)
        {
                while(line.find(',',0) == std::string::npos)
                {
                        File>>line;
                        name.append(line);
                        name.append(" ");
                }
                line.erase(0, std::string::npos);
                File>>num;
                if(num>0)
                {
                size_t end = name.find(",", 0);
                word = name.substr(0, end);
                Vertex *vertex = new Vertex();
                vertex->value = num;
                vertex->name = word;
                vertices.push_back(*vertex);
                Vertex ver = vertices[i];
                cout << ver.name << "\n";
                cout << ver.value << "\n";
                }
                name.erase(0, std::string::npos);
        }
        string line2;
	string name1;
        string name2;
        string nameOne;
        string nameTwo;
        int weight;
        bool cont = true;
        while(File>>line2){
        name1.append(line2);
        name1.append(" ");
        while(line2.find(',',0) == std::string::npos)
        {
                File>>line2;
                name1.append(line2);
                name1.append(" ");
        }
        line2.erase(0, std::string::npos);
        while(line2.find(',',0) == std::string::npos)
        {
                File>>line2;
                name2.append(line2);
                name2.append(" ");
        }
        line2.erase(0, std::string::npos);
        File>>weight;
        if(weight>0)
        {
                size_t end1 = name1.find(",", 0);
                nameOne = name1.substr(0, end1);
                size_t end2 = name2.find(",", 0 );
                nameTwo = name2.substr(0, end2);
                addEdge(name1, name2, weight);
                cout << nameOne<< "\n";
                cout << nameTwo << "\n";
                cout << weight << "\n";
        }
        name1.erase(0, std::string::npos);
        name2.erase(0, std::string::npos);
        if(File.peek() == ' ')
                cont = false;
        }
        File.close();
}

// JOHN NON-TESTED
// Write a graph to a file
void Graph::writeToFile(string file){
	vector<Edge> pushedEdges;
	vector<Edge> writeEdge;
	vector<Vertex> writeVertex;
	ofstream writeFile;
	bool breakLoop;
	
	writeFile.open(file);
	writeFile << numVertex << "\n";
	for(int i = 0; i < numVertex; i++){
		// !! CAN I DO THIS? !!
		writeVertex = vertices[i];
		writeFile << writeVertex.name << ", " << writeVertex.value << "\n";
	}
	vector<Edge>::iterator edgeIt;
	for(int i = 0; i < numVertex; i++){
		// !! CAN I DO THIS? !!
		writeEdge = vertices[i]->edges;
		for(edgeIt = writeEdge.begin; edgeIt != writeEdge.end(); edgeIt++){
			for(vector<Edge>::iterator it = pushedEdges.begin(); it != pushedEdges.end(); ++it){
				// !! WILL THIS BREAK OUT OF THE edgeIt FOR LOOP? !!
				if(edgeIt->name1 == it->name1 && edgeIt->name2 == it->name2){
					breakLoop = true;
				}
			}
			if(breakLoop != true){
				writeFile << writeEdge.name1 << ", " << writeEdge.name2 << ", " << writeEdge.weight << "\n";
				pushedEdge.push_back(writeEdge);
			}
		}
	}
	writeFile.close();
}

// JOHN NON-TESTED
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
// Add edge to graph
void Graph::addEdge(string v1, string v2, int weight){
	vector<Edge>::iterator edgeIt;
	vector<Vertex>::iterator vertIt;
	vector<Vertex>::iterator vertStore1;
	vector<Vertex>::iterator vertStore2;
	bool v1Hit, v2Hit;

	for(vertIt = vertices.begin(); vertIt != vertices.end; vertIt++){
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
		Edge createdEdge = new Edge();
		createdEdge.name1 = v1;
		createdEdge.name2 = v2;
		createdEdge.weight = weight;
		vertStore1->edges.push_back(createdEdge);
		vertStore2->edges.push_back(createdEdge);
	}
}

// Add vertex to graph
void Graph::addVertex(string name, float val){
	 bool found = false;
        if(val>0)
        {
                int i = 0;
                while(found == false && i<vertices.size())
                {
                        if(vertices[i].name == name)
                                found == true;
                        i++;
                }
                Vertex *ver = new Vertex();
                ver->name = name;
                ver->value = val;
                vertices.push_back(*ver);
                cout << vertices[i].name << " " << vertices[i].value << "\n";
                numVertex++;
        }


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

// Depth First search
bool Graph::DFS(string source, string val){

}

// Bredath First search
bool Graph::BFS(string source, string val){

	if(source.compare(val)==0)
                return true;
        else
        {
                int positionSource= -1;
                int positionVal = -1;
                for(int i = 0; i<numVertex; i++)
                {
                        if(vertices[i].name.compare(source) == 0)
                                positionSource = i;
                        if(vertices[i].name.compare(val) == 0)
                                positionVal = i;
                        if(positionSource == -1 || positionVal == -1)
                                return false;
                }
                queue<string> nameQue;
                set<string> nameSet;
                nameQue.push(source);
                nameSet.insert(source);
                string find;
                string find2;
                while(!nameQue.empty())
                {
                        find = nameQue.front();
                        for(int v = 0; v<numVertex; v++)
                        {
                                if(vertices[v].name.compare(find) == 0)
                                        positionSource = v;
                        }
                        nameQue.pop();
                        if(find.compare(val) == 0)
                                return true;
                        for(int j = 0; j< vertices[positionSource].edges.size(); j++)
                        {
                                find2 = vertices[positionSource].edges[j].name2;
                                if(nameSet.find(find2)!= nameSet.end())
                                {
                                        nameQue.push(find2);
                                        nameSet.insert(find2);
                                }

}

// Determines closeness of two nodes
// Each edge used ++1, no vaild path = -1, look for minimum edges
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
