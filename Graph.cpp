#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void Graph::addEdge(int st, int ed, double w) {
	inEdges[ed].push_back(Edge(st,ed,w));
	outEdges[st].push_back(Edge(st,ed,w));
	edgeNum++;
}

void Graph::randomTrainTestSplit(double trainRatio) {
	trainNodes.clear();
	testNodes.clear();
	for (int i = 0; i < nodeNum; i++) {
		// No label available for the node
		if (labels[i].size() == 0 || labels[i][0] == 0) {
			continue;
		}
		if (1.0 * rand() / RAND_MAX <= trainRatio) {
			trainNodes.push_back(i);
		} else {
			testNodes.push_back(i);
		}
	}
	printf("Sampled %d train nodes and %d test nodes", trainNodes.size(), testNodes.size());
}
