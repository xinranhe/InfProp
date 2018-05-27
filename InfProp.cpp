#include "InfProp.h"

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
vector<vector<double>> infoProp(Graph& graph, vector<int>& train_nodes, double edgeProb, int numSimulations, bool useDegreeWeight) {
	default_random_engine generator;
	int n =  graph.nodeNum;
	vector<vector<double>> results = vector<vector<double>>(n, vector<double>(graph.labelNum + 1, 0.0));
	cout << "Runing info prop:";
	for (int i = 0; i < numSimulations; i++) {
		labelNodesWithDijkstra(graph, train_nodes, results, generator, edgeProb, useDegreeWeight);
		if (true) {
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

void labelNodesWithDijkstra(Graph& graph, vector<int>& train_nodes, vector<vector<double>>& results, default_random_engine& generator, double edgeProb, bool useDegreeWeight) {
	vector<int> result(graph.nodeNum, 0);
	vector<double> distance = vector<double>(graph.nodeNum, 1e100);
	priority_queue<DijNode> myQueue;
	for (int i = 0; i < train_nodes.size(); i++) {
		// For multi-label case, we uniformly sample one for propagation.
		const vector<int>& allLables = graph.labels[train_nodes[i]];
		if (allLables.size() == 0) {
			continue;
		}
		int label;
		if (allLables.size() == 1) {
			label = allLables[0];
		} else {
			label = allLables[rand() % allLables.size()];
		}
		myQueue.push(DijNode(train_nodes[i], label, 0));
		distance[train_nodes[i]] = 0.0;
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
			double expParam;
			if (useDegreeWeight) {
				expParam = 1.0 / graph.outEdges[nid].size();
			} else {
				expParam = graph.outEdges[nid][i].w;
			}
			exponential_distribution<double> myDist = exponential_distribution<double>(expParam);
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
