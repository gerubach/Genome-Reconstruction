#include <string>
#include <stdlib.h>
#include "Edge.h"
#include "constants.h"
#include "Graph.h"
#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
	srand(time(0));
	string* genome = new string;
	string* reconstruction = new string;
	string* repeat = new string;
	string* nonRepeat = new string;
	int temp, useless, count = 0;
	int readLength, repeatLength, numOfRepeats;
	ofstream fileOut("results.txt");
	cout << "Enter 1 if you want to perform the first set of trials. Enter 0 for the second set of trials: ";
	cin >> useless;
	cout << "Enter read length: ";
	cin >> readLength;
	if (!useless) {
		cout << "Enter repeat length: ";
		cin >> repeatLength;
		cout << "Enter number of repeats: ";
		cin >> numOfRepeats;
	}
	else repeatLength = 0, numOfRepeats = 0;

	for (int j = 0; j < 10; j++) {//loop to test different genomes
		int num = 0;
		*genome = "", *repeat = "", *reconstruction = "", *nonRepeat = "";

		for (int i = 0; i < repeatLength; i++) {//generate random repeat
			temp = rand() % 4;
			switch (temp) {
			case 0: *repeat += "A"; break;
			case 1: *repeat += "C"; break;
			case 2: *repeat += "G"; break;
			case 3: *repeat += "T"; break;
			}
		}
		for (int i = 0; i < GENOME_LENGTH - repeatLength * numOfRepeats; i++) {//generate non-repeat part of genome
			temp = rand() % 4;
			switch (temp) {
			case 0: *nonRepeat += "A"; break;
			case 1: *nonRepeat += "C"; break;
			case 2: *nonRepeat += "G"; break;
			case 3: *nonRepeat += "T"; break;
			}
		}

		//randomize locations of repeats
		vector <int> locations(numOfRepeats);
		for (int i = 0; i < numOfRepeats; i++) locations[i] = rand() % (GENOME_LENGTH - repeatLength * numOfRepeats + 1);

		//insert repeats
		string* insert = new string[GENOME_LENGTH - repeatLength * numOfRepeats + 1];
		for (int i = 0; i < GENOME_LENGTH - repeatLength * numOfRepeats + 1; i++) *(insert + i) = "";

		for (int i = 0; i < GENOME_LENGTH - repeatLength * numOfRepeats + 1; i++) {
			for (int k = 0; k < locations.size(); k++) {
				if (locations[locations.size() - 1 - k] == i) {
					*(insert + i) += *repeat;
					locations.erase(locations.end() - 1 - k);
				}
			}
		}
	
		for (int i = 0; i < GENOME_LENGTH - repeatLength * numOfRepeats; i++) {
			*genome += *(insert + i);
			*genome += (*nonRepeat)[i];
		}
		*genome += *(insert + GENOME_LENGTH - repeatLength * numOfRepeats);
		delete[] insert;

		//create each edge in the de Bruijn graph
		int numOfEdges = GENOME_LENGTH - readLength + 2;
		vector<Edge> e1(numOfEdges);
		for (int i = 0; i < numOfEdges - 1; i++) {
			e1[i].setStart(genome->substr(i, readLength - 1));
			e1[i].setEnd(genome->substr(i + 1, readLength - 1));
		}

		//create edge connecting ending node to beginning node
		e1[numOfEdges - 1].setStart(genome->substr(GENOME_LENGTH - readLength + 1));
		e1[numOfEdges - 1].setEnd(genome->substr(0, readLength - 1));

		//Scramble the order of all the edges except for the first and last ones
		vector<Edge> e2(numOfEdges);
		e2[0] = e1[0], e2[numOfEdges - 1] = e1[numOfEdges - 1];
		e1.erase(e1.begin()), e1.erase(e1.end() - 1);
		for (int i = 1; i < numOfEdges - 1; i++) {
			int temp = rand() % size(e1);
			e2[i] = e1[temp];
			e1.erase(e1.begin() + temp);
		}

		//output results
		Graph g(e2, numOfEdges);
		int* indices = new int[numOfEdges];
		int m = 1;
	//	g.findEulerianCycle(e, indices);
	//	for (int i = 0; i < NUM_OF_EDGES - 1; i++) *reconstruction += ((e + i)->getStart())[0];
	//	*reconstruction += (e + NUM_OF_EDGES - 1)->getStart();
	//	if (*genome == *reconstruction) count++;
		if (!useless) fileOut << g.findCorrectEulerianCycle(indices, *genome, numOfEdges, m) << endl;
		else {
			Edge* e = new Edge[numOfEdges];
			g.findEulerianCycle(e, indices, numOfEdges);
			for (int i = 0; i < numOfEdges - 1; i++) *reconstruction += ((e + i)->getStart())[0];
			*reconstruction += (e + numOfEdges - 1)->getStart();
			if (*genome == *reconstruction) count++;
		}
		delete[] indices;
	}
	if (useless) fileOut << count;
	fileOut.close();
	cout << "All data has been generated" << endl;
}