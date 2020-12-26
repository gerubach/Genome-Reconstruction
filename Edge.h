#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge {
public:
	Edge();
	void setStart(std::string s);
	void setEnd(std::string e);
	void makeExplored();
	void makeUnExplored();
	std::string getStart();
	std::string getEnd();
	bool isExplored();
private:
	bool explored;
	std::string start, end;
};

#endif