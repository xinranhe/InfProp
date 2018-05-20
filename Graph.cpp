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
}

void Graph::initFromCoraGraphFile(const string& fileName) {
	ifstream fin;
	fin.open(fileName);
	vector<Edge> edges;
	
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
		edges.push_back(Edge(edNodeId, stNodeId, 1.0));
	}

	init();
	for (int i = 0; i < edges.size(); i++) {
		int st = edges[i].stId;
		int ed = edges[i].edId;
		addEdge(st, ed, 1.0);
	}
	cout << "Loaded graph with " << nodeNum << " nodes and " << edgeNum << " edges." << endl; 
}

void Graph::loadCoraLabelFile(const string& labelFile) {
	ifstream fin;
	fin.open(labelFile);
	labelNameToId.clear();
	labels = vector<int>(nodeNum, 0);
	labelNum = 0;
	string tempLine;
	while(getline(fin, tempLine)) {
		stringstream sin(tempLine);
		string field;
		vector<string> fields;
		while(sin >> field) fields.push_back(field);
		int nodeId = nodeNameToId[fields[0]];
		string labelName = fields[fields.size() - 1];
		if (labelNameToId.find(labelName) == labelNameToId.end()) {
			labelNameToId[labelName] =  ++labelNum;
		}
		labels[nodeId] = labelNameToId[labelName];
	}
}
