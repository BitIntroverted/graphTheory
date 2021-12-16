/*
 * 	Name: Lukas Friedrich
 * 	Final Project - Graphs
 * 	This program creates and displays several randomly generated bi-directional graphs
 */

#include "main.h"

int main() {
	cout << "Graph Demo" << endl;

	for (int i = 0; i < TESTCASES; i++) {
		Graph testing;
		srand(time(NULL));
		cout << "					_____________~Graph Demo: " << i+1 << "~_____________" << endl;
		cout << "Graph empty: " << testing.isEmpty() << endl;
		int testVs = (rand() % 10) + MINVERTEXCOUNT;
		cout << "Verticies being added..." << endl;
		for (int i = 0; i < testVs; i++) {
			testing.addVertex(i+1);
			cout << "Total verticies: " << testing.getTotalVerticies() << endl;
		}
		cout << "\nVerticies added" << endl;
		cout << "Graph empty: " << testing.isEmpty() << endl;
		testing.displayGraph();
		cout << "\nEdges being added..." << endl;
		for (int i = 0; i < (testVs+2)*2; i++) {
			if (i%2 == 0) {
				testing.addEdge((rand() % testVs), (rand() % testVs), rand() % 100);
			}
			else {
				testing.addEdge((rand() % testVs)+1, (rand() % testVs), rand() % 250, rand() % 500);
			}
		}
		cout << "\nEdges added" << endl;
		testing.displayGraph();
		
		//test bad data
		cout << "\nAll these value should come out as 0 indicating false\n_______________________________________________________" << endl;
		cout << "Add edge with -1 vetex: " << testing.addEdge(-1, 777777, 12) << endl;
		cout << "Add edge with negative weight: " << testing.addEdge(1, 2, -6) << endl;
		cout << "Edge exists with id out of bounds: " << testing.edgeExists(99999, 0) << endl;
		cout << "Edge exists with same edge: " << testing.edgeExists(6, 6) << endl;
		cout << "Add vertex that already exists: " << testing.addVertex(1) << endl;
		cout << "Remove edge that doesn't exists: " << testing.removeEdge(9, -6) << endl;
		cout << "Remove vertex that doesn't exists: " << testing.removeVertex(99999) << endl << endl;

		//display bfs/dfs
		testing.breadthFirstSearch((rand() % testVs) + 1);
		testing.depthFirstSearch((rand() % testVs) + 1);

		//clear and show empty
		cout << "Clearing graph now...." << endl;
		testing.clearGraph();
		cout << "Graph cleared: " << testing.isEmpty() << endl;
		testing.displayGraph();
		
		//if srand() isn't working quite right you can time delay each loop with a cin
		//int yo;
		//cout << "Enter a number and press enter to generate next Graph" << endl;
		//std::cin >> yo;
	}

	return 0;
}