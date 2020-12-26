#include "Graph.h"
#include "constants.h"
#include <vector>

using namespace std;

Graph::Graph(vector<Edge> e, int numOfEdges) {
	for (int i = 0; i < numOfEdges; i++) edges[i] = e[i];
}

//k denotes index of starting edge, j denotes how many edges are in constructed cycle
int Graph::findCycle(Edge* e, int* indices, int numOfEdges, int k, int j) {
	*e = edges[k];
	edges[k].makeExplored();
	*indices = k;
	if (k != 0 && edges[k].getEnd() == (e - j)->getStart()) return j + 1;
	for (int i = 0; i < numOfEdges; i++) {
		if (!edges[i].isExplored() && edges[i].getStart() == e->getEnd()) {
			int temp = findCycle(e + 1, indices + 1, numOfEdges, i, j + 1);
			if (temp != 0) return temp; 
		}
	}
	return 0;
}

//k denotes index of starting edge, j denotes how many edges are in constructed cycle
int Graph::findSpecialCycle(Edge* e, int* indices, int numOfEdges, int k, int j) {
	*e = edges[k];
	edges[k].makeExplored();
	*indices = k;
	if (k == numOfEdges - 1) {
		//mark unexplored/explored edges
		for (int i = 0; i < numOfEdges; i++) edges[i].makeUnExplored();
		for (int i = 0; i < j + 1; i++) edges[*(indices - i)].makeExplored();
		return j + 1;
	}
	for (int i = 0; i < numOfEdges; i++) {
		if (!edges[i].isExplored() && edges[i].getStart() == e->getEnd()) {
			int temp = findSpecialCycle(e + 1, indices + 1, numOfEdges, i, j + 1);
			if (temp != 0) return temp;
		}
	}
	return 0;
}

void Graph::findEulerianCycle(Edge* e, int* indices, int numOfEdges) {
	int originalLength = findSpecialCycle(e, indices, numOfEdges);

	while (originalLength != numOfEdges) {
		for (int i = 0; i < numOfEdges; i++) {
			for (int j = 0; j < originalLength; j++) {
				if (!edges[i].isExplored() && edges[i].getStart() == (e + j)->getStart()) {
					//create new cycle
					Edge* otherEdges = new Edge[numOfEdges];
					int newLength = findCycle(otherEdges, indices + originalLength, numOfEdges, i);

					//mark unexplored/explored edges
					for (int k = 0; k < numOfEdges; k++) edges[k].makeUnExplored();
					for (int k = 0; k < originalLength + newLength; k++) edges[*(indices + k)].makeExplored();

					//combine cycles
					for (int k = 0; k < originalLength - j; k++) *(otherEdges + newLength + k) = *(e + j + k);
					for (int k = 0; k < newLength; k++) *(e + j + k) = *(otherEdges + k);
					for (int k = 0; k < originalLength - j; k++) *(e + j + newLength + k) = *(otherEdges + newLength + k);

					originalLength += newLength;
					delete[] otherEdges;
					break;
				}
			}
		}
	}
}

//k denotes index of starting edge, j denotes how many edges are in constructed cycle, m denotes number of attempts
int Graph::findCorrectEulerianCycle(int* indices, string genome, int numOfEdges, int& m, int k, int j) {
	*(indices + j) = k;

	if (k == numOfEdges - 1 && j == numOfEdges - 1) {
		string* reconstruction = new string;
		*reconstruction = "";
		for (int i = 0; i < j; i++) *reconstruction += edges[*(indices + i)].getStart()[0];
		*reconstruction += edges[*(indices + j)].getStart();
		if (genome == *reconstruction) {
			delete reconstruction;
			return m;
		}
		else {
			delete reconstruction;
			m++;
		}
	}
	else if (j == numOfEdges - 1) return 0;
	for (int i = 0; i < numOfEdges; i++) {
		int p = 0;
		while (p <= j) {
			if (*(indices + p) == i) break;
			p++;
		}
		if (p == j + 1 && edges[i].getStart() == edges[*(indices + j)].getEnd()) {
			int temp = findCorrectEulerianCycle(indices, genome, numOfEdges, m, i, j + 1);
			if (temp != 0) return temp;
		}
	}
	return 0;
}