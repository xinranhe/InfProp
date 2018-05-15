#include "Graph.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void Graph::addEdge(int st, int ed, double w) {
	inEdges[ed].push_back(Edge(st,ed,w));
	outEdges[st].push_back(Edge(st,ed,w));
}

void Graph::initFromCoraGraphFile(const string& fileName) {
	ifstream fin;
	fin.open(fileName);

	vector<Edge> edges;
	unordered_map<string, int> nodeNameToId;
	
	string stNodeName, edNodeName;
	int stNodeId, edNodeId;
	while(fin >> stNodeName >> edNodeName) {
		if (nodeNameToId.find(stNodeName) == nodeNameToId.end()) {
			nodeNameToId[stNodeName] = nodeNum++;
		}
		if (nodeNameToId.find(edNodeName) == nodeNameToId.end()) {
			nodeNameToId[edNodeName] = nodeNum++;
		}
		stNodeId = nodeNameToId[stNodeName];
		edNodeId = nodeNameToId[edNodeName];
		if (stNodeId == edNodeId) {
			cout << "Self loop found:" << stNodeId << endl;
			continue;
		}
		edgeNum++;
		edges.push_back(Edge(stNodeId, edNodeId, 1.0));
	}

	init();
	for (int i = 0; i < edges.size(); i++) {
		int st = edges[i].stId;
		int ed = edges[i].edId;
		addEdge(st, ed, 1.0);
	}
	cout << "Loaded graph with " << nodeNum << " nodes and " << edgeNum << " edges." << endl; 
}
	
Graph Graph::sampleDegreeLiveEdgeGraph(double edgeProb) {
	Graph newGraph = Graph(nodeNum);
	for (int i = 0; i < nodeNum; i++) {
		int outDegree = outEdges[i].size();
		if (outDegree == 0) {
			continue;
		}
		double weight = 1.0 / outDegree;
		for (int j = 0; j < outDegree; j++) {
			if (double(rand())/RAND_MAX < edgeProb) {
				newGraph.edgeNum++;
				newGraph.addEdge(outEdges[i][j].stId, outEdges[i][j].edId, weight);
			}
		}
	}
	cout << "Sampled live edge graph with " << nodeNum << " nodes and " << newGraph.edgeNum << " edges." << endl; 
	return newGraph;
}
