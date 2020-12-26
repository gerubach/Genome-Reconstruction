#ifndef GRAPH_H
#define GRAPH_H
#include "Edge.h"
#include "constants.h"
#include <vector>

class Graph {
public:
	Graph(std::vector<Edge> e, int numOfEdges);
	int findCycle(Edge* e, int* indices, int numOfEdges, int k = 0, int j = 0);
	int findSpecialCycle(Edge* e, int* indices, int numOfEdges, int k = 0, int j = 0);
	void findEulerianCycle(Edge* e, int* indices, int numOfEdges);
	int findCorrectEulerianCycle(int* indices, std::string genome, int numOfEdges, int& m, int k = 0, int j = 0);
private:
	Edge edges[1000];
};

#endif
