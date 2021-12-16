/*
 * 	Name: Lukas Friedrich
 * 	Graph Theory
 * 	graph class, ID must be > 0, -1 weight flags "vertex" node in each linkedlist
 */

#include "graph.h"

Graph::Graph() {
	verticies = 0;
	edges = 0;
}

Graph::~Graph() {
    //clearGraph();
}

bool Graph::addVertex(int newID)
{
	bool added = false;
	if (newID > 0 && !vertexExists(newID)) {
		LinkedList* newVertex = new LinkedList;
		newVertex->addNode(newID, -1);
		adjList.push_back(newVertex);
		adjLabel.push_back(newID);
		verticies++;
		added = true;
	}

	return added;
}

//remove vertex from adjLabel/List and erase all "edge nodes" related
bool Graph::removeVertex(int id) {
	bool removed = false;
	if (vertexExists(id)) {
		int index = getIndex(id);
		adjList[index]->~LinkedList();
		adjLabel.erase(adjLabel.begin() + index);
		adjList.erase(adjList.begin() + index);
		//need to loop through adjList and remove edges
		for (LinkedList* edgeList : adjList) {
			if (edgeList->cleanList(id)) {
				edges--; edges--; //accounting for erase() edges above
			}
		}
		removed = true;
		verticies--;
	}
	return removed;
}

//keeping weights equal from A->B & B->A
bool Graph::addEdge(int vertexStart, int vertexEnd, int weight)
{
	bool added = false;
	if (weight > 0 && vertexStart != vertexEnd && vertexExists(vertexStart) && vertexExists(vertexEnd)) {
		int index = getIndex(vertexStart);
		if (adjList[index]->addNode(vertexEnd, weight)) { edges++; };
		index = getIndex(vertexEnd);
		if (adjList[index]->addNode(vertexStart, weight)) { edges++; };
		added = true;
	}
	return added;
}

//overloaded for seperate weights
bool Graph::addEdge(int vertexStart, int vertexEnd, int weightGoing, int weightComing)
{
	bool added = false;
	if (weightGoing > 0 && weightComing > 0 && vertexStart != vertexEnd && vertexExists(vertexStart) && vertexExists(vertexEnd)) {
		int index = getIndex(vertexStart);
		if (adjList[index]->addNode(vertexEnd, weightGoing)) { edges++; };
		index = getIndex(vertexEnd);
		if (adjList[index]->addNode(vertexStart, weightComing)) { edges++; };
		added = true;
	}
	return added;
}

bool Graph::removeEdge(int vertexStart, int vertexEnd)
{
	bool removed = false;
	if (edgeExists(vertexStart, vertexEnd)) {
		int index = getIndex(vertexStart);
		if (adjList[index]->deleteNode(vertexEnd)) { edges--; };
		index = getIndex(vertexEnd);
		if (adjList[index]->deleteNode(vertexStart)) { edges--; };
		removed = true;
	}
	return removed;
}

void Graph::clearGraph()
{
	for (LinkedList* vertex : adjList) {
		vertex->clearList();
	}
	vector<int>().swap(adjLabel);
	vector<LinkedList*>().swap(adjList);
	verticies = 0; edges = 0;
}

bool Graph::vertexExists(int id)
{
	bool exists = false;
	if(id > 0 && std::find(adjLabel.begin(), adjLabel.end(), id) != adjLabel.end()){ // end() points to one past the last element
		exists = true;
	}
	return exists;
}

bool Graph::edgeExists(int vertexStart, int vertexEnd)
{
	bool exists = false;
	if (vertexExists(vertexStart) && vertexExists(vertexEnd)) {
		int index = getIndex(vertexStart);
		exists = adjList[index]->exists(vertexEnd);
	}
	return exists;
}

void Graph::displayGraph() {
	cout << "\n    C++ goes brr.. displaying graph now...\n" << endl;
	if (isEmpty()) {
		cout << "Graph is empty" << endl;
	}
	else {
		cout << "Verticies: " << verticies << endl;
		cout << "Edges: " << edges << endl;
		cout << "\nVertex List\n----------" << endl;
		for (int i: adjLabel){
			cout << "Vertex: " << i << endl;
		}
		cout << "\nAdjacency List\n----------" << endl;
		int index = 0;
		for (LinkedList* vertex : adjList) {
			cout << adjLabel[index];
			vertex->printNodeCentricGraph(); cout << endl;
			index++;
			}
		
	}
}

void Graph::depthFirstSearch(int id)
{
	bool* visitedFlag = new bool[verticies];
	for (int i = 0; i < verticies; i++) {
		visitedFlag[i] = false;
	}
	cout << "Running DFS..." << endl;
	dfsWorker(id, visitedFlag);
}

void Graph::breadthFirstSearch(int id)
{
	bool* visitedFlag = new bool[verticies];
	for (int i = 0; i < verticies; i++) {
		visitedFlag[i] = false;
	}
	cout << "Running BFS..." << endl;
	dfsWorker(id, visitedFlag);
}

bool Graph::isEmpty()
{
	return (!verticies);
}

int Graph::getTotalVerticies()
{
	return verticies;
}

int Graph::getTotalEdges()
{
	return edges;
}



//private
int Graph::getIndex(int id)
{
	int element = -1;
	for (int i = 0; i < adjLabel.size(); i++)
	{
		if (adjLabel[i] == id)
		{
			element = i;
			break;
		}
	}

	return element;
}

void Graph::dfsWorker(int id, bool* visitedArr)
{
	int index = getIndex(id);
	cout << "Visiting Node: " << id << endl;
	visitedArr[index] = true;
	auto* i = adjList[index];

	Node* temp = i->getlist();
	while (temp) {
		if (temp->data.weight != -1) { //-1 indicates vertex
			int newID = temp->data.id;
			int ind = getIndex(newID);
			if (!visitedArr[ind])
				dfsWorker(newID, visitedArr);

		}
		temp = temp->next;

	}


}

void Graph::bfsWorker(int id, bool* visitedArr)
{
	int index = getIndex(id);
	cout << "Visiting Node: " << id << endl;
	visitedArr[index] = true;
	auto* i = adjList[index];

	std::queue<int> bfsQueue;

	Node* temp = i->getlist();
	while (temp) {
		if (temp->data.weight != -1) { //-1 indicates vertex
			int newID = temp->data.id;
			int ind = getIndex(newID);
			if (!visitedArr[ind])
				bfsQueue.push(newID);

		}
		temp = temp->next;

	}

	while (!bfsQueue.empty())
	{
		int nextID = bfsQueue.front();
		bfsQueue.pop();

		index = getIndex(nextID);
		cout << "Visiting Node: " << id << endl;
		visitedArr[index] = true;
		auto* i = adjList[index];

		Node* temp = i->getlist();
		while (temp) {
			if (temp->data.weight != -1) { //-1 indicates vertex
				int new_id = temp->data.id;
				int ind = getIndex(new_id);
				if (!visitedArr[ind])
					bfsQueue.push(new_id);

			}
			temp = temp->next;

		}


	}
}
