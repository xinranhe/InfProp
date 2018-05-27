#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct Edge {
	int stId;
	int edId;
	double w;
	Edge(int _stId, int _edId, double _w) : stId(_stId), edId(_edId), w(_w) {}
	Edge() {}
};

struct Graph {
	// number of node
	int nodeNum;
	// number of edge
	int edgeNum;
	// number of labels
	int labelNum;

	// Node labels: label id starts from 1, 0 is reserved for unknown
	vector<vector<int>> labels;

	// Train and test nodes if provided
	vector<int> trainNodes;
	vector<int> testNodes;

	// storage for edges
	vector<vector<Edge> > inEdges;
	vector<vector<Edge> > outEdges;

	// constructor
	Graph(int _nodeNum): nodeNum(_nodeNum) {
		edgeNum = 0;
		labelNum = 0;
		init();
	}
	Graph(): nodeNum(0) {
		edgeNum = 0;
		labelNum = 0;
		init();
	}
	void init() {
		inEdges.resize(nodeNum);
		outEdges.resize(nodeNum);
		labels.resize(nodeNum);
	}

	void addEdge(int st, int ed, double w);
	void randomTrainTestSplit(double trainRatio);
};

#endif
