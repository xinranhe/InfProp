#include "Graph.h"

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
using namespace std;

const string CORA_GRAPH_FILE_PATH = "data/cora.cites";

int main(int argc, char** argv) {
	Graph coraGraph = Graph();
	coraGraph.initFromCoraGraphFile(CORA_GRAPH_FILE_PATH);
	coraGraph.sampleDegreeLiveEdgeGraph(0.5);
	return 0;
}
