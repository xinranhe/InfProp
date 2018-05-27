#include "Dataset.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

Graph loadFromRawCoraDataset(const string& graphFile, const string& labelFile) {
	int nodeNum = 0;
	int edgeNum = 0;
	// Node name to id map
	unordered_map<string, int> nodeNameToId;
	// Node labels
	unordered_map<string, int> labelNameToId;

	// Load edges from graph file
	ifstream fin1;
	fin1.open(graphFile);
	
	vector<Edge> edges;
	string stNodeName, edNodeName;
	int stNodeId, edNodeId;
	while(fin1 >> stNodeName >> edNodeName) {
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
		// Though the citation graph is directional, we populate the graph for both direction for better performance.
		edges.push_back(Edge(stNodeId, edNodeId, 1.0));
		edges.push_back(Edge(edNodeId, stNodeId, 1.0));
	}
	fin1.close();
	Graph graph = Graph(nodeNum);
	for (int i = 0; i < edges.size(); i++) {
		graph.addEdge(edges[i].stId, edges[i].edId, edges[i].w);
	}

	// Load nodes labels from label file
	ifstream fin2;
	fin2.open(labelFile);
	string tempLine;
	while(getline(fin2, tempLine)) {
		stringstream sin(tempLine);
		string field;
		vector<string> fields;
		while(sin >> field) fields.push_back(field);
		int nodeId = nodeNameToId[fields[0]];
		string labelName = fields[fields.size() - 1];
		if (labelNameToId.find(labelName) == labelNameToId.end()) {
			labelNameToId[labelName] =  ++graph.labelNum;
		}
		graph.labels[nodeId] = vector<int>({labelNameToId[labelName]});
	}
	fin2.close();

	printf("Loaded graph with %d node %d edges and %d labels\n", graph.nodeNum, graph.edgeNum, graph.labelNum);
	return graph;
}
