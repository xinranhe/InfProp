#include "InfoProp.h"

#include <iostream>
#include <queue>
#include <random>
using namespace std;

struct DijNode {
	int nodeId;
	int label;
	double distance;
	bool isVisited;

	DijNode() {}
	DijNode(int _nodeId, int _label, double _distance) {
		nodeId = _nodeId;
		label = _label;
		distance = _distance;
	}

	bool operator < (const DijNode& other) const {
		return distance > other.distance;
	}
};

// label id starts from 1, 0 is reserved for the node not activated
vector<vector<double>> infoProp(Graph& graph, unordered_map<int, int>& seedToLabel, double edgeProb, int numSimulations) {
	default_random_engine generator;
	int n =  graph.nodeNum;
	vector<vector<double>> results = vector<vector<double>>(n, vector<double>(graph.labelNum + 1, 0.0));
	cout << "Runing info prop:";
	for (int i = 0; i < numSimulations; i++) {
		labelNodesWithDijkstra(graph, seedToLabel, results, generator, edgeProb);
		if (i % 100 == 1) {
			cout << i << " ";
			cout.flush();
		}
	}
	cout << endl;
	for (int i = 0; i < graph.nodeNum; i++) {
		for(int j = 0; j < graph.labelNum + 1; j++) {
			results[i][j] /= numSimulations;
		}
	}
	return results;
}

int bfs(Graph& graph, unordered_map<int, int>& seedToLabel) {
	vector<bool> isVisited(graph.nodeNum, 0);
	queue<DijNode> myQueue;
	for (auto it = seedToLabel.begin(); it != seedToLabel.end(); ++it) {
		myQueue.push(DijNode(it->first, it->second, 0));
		isVisited[it->first] = true;
	}
	while(!myQueue.empty()) {
		const DijNode topNode = myQueue.front();
		myQueue.pop();
		int nid = topNode.nodeId;
		for (int i = 0; i < graph.outEdges[nid].size(); i++) {
			int ed = graph.outEdges[nid][i].edId;
			if (!isVisited[ed]) {
				isVisited[ed] = true;
				myQueue.push(DijNode(ed, topNode.label, 0));
			}
		}
	}
	int count = 0;
	for (int i = 0; i < graph.nodeNum; i++) {
		count += isVisited[i];
	}
	return count;
}

void labelNodesWithDijkstra(Graph& graph, unordered_map<int, int>& seedToLabel, vector<vector<double>>& results, default_random_engine& generator, double edgeProb) {
	vector<int> result(graph.nodeNum, 0);
	vector<double> distance = vector<double>(graph.nodeNum, 1e100);
	priority_queue<DijNode> myQueue;
	for (auto it = seedToLabel.begin(); it != seedToLabel.end(); ++it) {
		myQueue.push(DijNode(it->first, it->second, 0));
		distance[it->first] = 0.0;
	}
	while(!myQueue.empty()) {
		const DijNode topNode = myQueue.top();
		myQueue.pop();
		int nid = topNode.nodeId;
		if (result[nid] > 0) {
			continue;
		}
		result[nid] = topNode.label;
		for (int i = 0; i < graph.outEdges[nid].size(); i++) {
			if (double(rand())/RAND_MAX > edgeProb) {
				continue;
			}
			int ed = graph.outEdges[nid][i].edId;
			exponential_distribution<double> myDist = exponential_distribution<double>(1.0 / graph.outEdges[nid].size());
			double weight = myDist(generator);
			if (distance[nid] + weight < distance[ed]) {
				distance[ed] = distance[nid] + weight;
				myQueue.push(DijNode(ed, topNode.label, distance[ed]));
			}
		}
	}
	for (int i = 0; i < graph.nodeNum; i++) {
		results[i][result[i]]++;
	}
}
