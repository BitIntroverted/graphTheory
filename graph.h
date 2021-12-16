/*
 * 	Name: Lukas Friedrich
 * 	Final Project - Graphs
 * 	graph class - bidirectional weighted
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "data.h"
#include "linkedlist.h"
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;

class Graph {

public:
	Graph();
	~Graph();

	bool addVertex(int);
	bool removeVertex(int);
	bool addEdge(int, int, int); //equal weights
	bool addEdge(int, int, int, int); //seperate weights
	bool removeEdge(int, int);
	void clearGraph();

	bool vertexExists(int);
	bool edgeExists(int, int);
	bool isEmpty();
	int getTotalVerticies();
	int getTotalEdges();
	void displayGraph();
	void depthFirstSearch(int);
	void breadthFirstSearch(int);


private:

	vector<LinkedList*> adjList;
	vector<int> adjLabel;
	int verticies;
	int edges;

	int getIndex(int);
	void dfsWorker(int, bool*);
	void bfsWorker(int, bool*);
	
};


#endif /* GRAPH_H */
