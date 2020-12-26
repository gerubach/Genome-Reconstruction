#include "Edge.h"

using namespace std;

Edge::Edge() {
	start = "", end = "";
	explored = false;
}

void Edge::setStart(string s) {
	start = s;
}

void Edge::setEnd(string e) {
	end = e;
}

void Edge::makeExplored() {
	explored = true;
}

void Edge::makeUnExplored() {
	explored = false;
}

std::string Edge::getStart() {
	return start;
}

std::string Edge::getEnd() {
	return end;
}

bool Edge::isExplored() {
	return explored;
}