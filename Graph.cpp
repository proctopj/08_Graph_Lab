/*****
 * Author   : brinkmwj
 * Date     : 2009-11-06
 * Sources  : All code is original
 */
#include "Graph.h"

Graph::Graph(unsigned int numNodes){
	adjList.resize(numNodes);
}

double Graph::getCost(int node1, int node2){
	int index = edgeExists(node1, node2);
	if(index != -1)
		return adjList[node1].edgeList[index].cost;
	else
		return -1;
}

//Add an edge from node1 to node2, and from node2 to node1, with
// the given cost. If the cost is < 0, throw a string exception.
void Graph::addEdge(int node1, int node2, double cost){
	if(cost<0)
		throw std::string("You provided a negative cost value. We are not breaking Physics today...");
	if(node1 < 0 || node1 >= adjList.size() || node2 < 0 || node2 > adjList.size())
		throw std::string("You have tried to add an edge between one or more non-existent nodes.");

	int index = edgeExists(node1, node2);           //this seems to be an elegant handling: searching one list to check existence.
	if(index != -1){
		adjList[node1].edgeList[index].cost = cost;
		int other = edgeExists(node2, node1);  //guaranteed a return other than -1
		adjList[node2].edgeList[other].cost = cost;
		return;
	}

	adjList[node1].edgeList.push_back(Edge(cost, node2));
	adjList[node2].edgeList.push_back(Edge(cost, node1));
}

//Remove the edge from node1 to node2, and also from node2 to node1.
// If there are no such edges, then don't do anything.
void Graph::removeEdge(int node1, int node2){
	if(node1 < 0 || node2 < 0 || node1 >= adjList.size() || node2 >= adjList.size())//because, on average, users are stupid...
		return;
	int index = edgeExists(node1, node2);
	if(index!=-1){
		Edge temp = adjList[node1].edgeList[index];
		adjList[node1].edgeList[index] = adjList[node1].edgeList[adjList[node1].edgeList.size()-1];
		adjList[node1].edgeList[adjList[node1].edgeList.size()-1] = temp;
		adjList[node1].edgeList.pop_back(); //very tough to tell which is more efficient: swap and pop, or erase and repopulate. The latter is more elegant of course...
		//adjList[node1].edgeList.erase(adjList[node1].edgeList.begin()+index);
		int other = edgeExists(node2, node1);
		Edge temp2 = adjList[node2].edgeList[other];
		adjList[node2].edgeList[other] = adjList[node2].edgeList[adjList[node2].edgeList.size()-1];
		adjList[node2].edgeList[adjList[node2].edgeList.size()-1] = temp;
		adjList[node2].edgeList.pop_back();
		//adjList[node2].edgeList.erase(adjList[node2].edgeList.begin()+index);
	}
	return;
}

int Graph::edgeExists(int node1, int node2){
	int size = adjList[node1].edgeList.size();
	for(int i=0; i<size; i++){
		if(adjList[node1].edgeList[i].dest==node2)//if the list of nodes adjacent to node1 contains an Edge 
			return i;							  //with destination node2, return the index of that Edge.
	}
	return -1;
}

//this implementation returns the shortest path between two particular nodes, but with a slight modification, it can generate the entire shortest path tree.
double Graph::shortestPath(int node1, int node2){
	if(node1 < 0 || node1 >= adjList.size() || node2 < 0 || node2 >= adjList.size())
		throw std::string("You have asked for a path with a node which doesn't exist in the graph.");

	int numVertices = adjList.size(), numVisited = 1, *visited = new int[numVertices];
	double *distances = new double[numVertices]; //if you want the shortest path for each node, take this array and return it after
	visited[0] = node1;							 //the algorithm runs. To get the whole tree, simply keep a "parents" array on the side
	for(int i=0; i<numVertices; i++)
		distances[i] = DBL_MAX; //we have to do this so there is a way to get the "shortest" path to the node by comparison.
	distances[node1] = 0;
	Heap<double, int> paths; //remember the priority is the distance and T is the parent and then the destination.
	paths.add(std::make_pair(0, node1));

	while(numVisited < numVertices){
		std::pair<double, int> current = paths.remove();
		int numEdges = adjList[current.second].edgeList.size();
		for(int j=0; j<numEdges; j++){ //for each edge, relax them, toss them onto the heap (lowest priorities will bubble up on their own,
			Edge curEdge = adjList[current.second].edgeList[j];
			if((curEdge.cost + distances[current.second]) < distances[curEdge.dest]){
				distances[curEdge.dest] = curEdge.cost + distances[current.second];

				bool isVisited = false;
				for(int k=0; k<numVisited; k++){
					if(curEdge.dest == visited[k]){
						isVisited = true;
						break;
					}//end iff
				}//end inner for
				if(!(isVisited))
					paths.add(std::make_pair(curEdge.cost, curEdge.dest)); //this way you don't get stuck in an infinite loop, but values are still updated.
				else
					numVisited++;
			}//end outter if
		}//end for
	}//end while
	paths.~Heap();
	double toReturn = distances[node2];
	delete[] distances; delete[] visited;
	return toReturn;
}
