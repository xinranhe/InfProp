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
	
	// Node name to id map
	unordered_map<string, int> nodeNameToId;

	// Node labels
	unordered_map<string, int> labelNameToId;
	vector<int> labels;

	// storage for edges
	vector<vector<Edge> > inEdges;
	vector<vector<Edge> > outEdges;

	// constructor
	Graph(int _nodeNum): nodeNum(_nodeNum) {
		edgeNum = 0;
		init();
	}
	Graph(): nodeNum(0) {
		edgeNum = 0;
		init();
	}
	void init() {
		inEdges.resize(nodeNum);
		outEdges.resize(nodeNum);
	}

	void addEdge(int st, int ed, double w);

	// Read from cora format
	// fromNodeId	toNodeId
	void initFromCoraGraphFile(const string& fileName);
	void loadCoraLabelFile(const string& labelFile);
};

#endif
