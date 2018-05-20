#include "Graph.h"
#include "InfoProp.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
using namespace std;

const string CORA_GRAPH_FILE_PATH = "data/cora.cites";
const string CORA_LABEL_FILE_PATH = "data/cora.content";

struct ExperimentParams {
	// Train/test split
	double trainRatio;
	// Algorithm params
	int numSimulations;
	double edgeProb;

	// Default parameters
	ExperimentParams() {
		trainRatio = 0.005;
		numSimulations = 1000;
		edgeProb = 0.5;
	}

	string toString() {
		return "trainRatio:" + to_string(trainRatio) + 
			   " numSims:" + to_string(numSimulations) + 
		       " edgProb:" + to_string(edgeProb);
	}
};

double computeAccuracy(Graph& graph, vector<vector<double>> results, vector<int> testNodes) {
	int count = 0;
	for (int i = 0; i < testNodes.size(); i++) {
		int nid = testNodes[i];
		int trueLabel = graph.labels[nid];
		int inferredLabel = distance(results[nid].begin(), max_element(results[nid].begin()+1, results[nid].end()));
		count += trueLabel == inferredLabel;
	}
	return 1.0 * count / testNodes.size();
}

void runInfoPropExperiment(Graph& graph, ExperimentParams params) {
	// Train test split
	unordered_map<int, int> trainSeedsLabels;
	vector<int> testNodes;
	for (int i = 0; i < graph.nodeNum; i++) {
		// No label available for the node
		if (graph.labels[i] == 0) {
			continue;
		}
		if (1.0 * rand() / RAND_MAX <= params.trainRatio) {
			trainSeedsLabels[i] = graph.labels[i];
		} else {
			testNodes.push_back(i);
		}
	}
	cout << "numTrainNodes:" << trainSeedsLabels.size() << " " << "numTestNodes:" << testNodes.size() << endl;

	// Run InfoProp algoirthm
	vector<vector<double>> results = infoProp(graph, trainSeedsLabels, params.edgeProb, params.numSimulations);
	cout << "Exp setting:" << params.toString() << endl;
	cout << "Accuracy:" << computeAccuracy(graph, results, testNodes) << endl;
}


int main(int argc, char** argv) {
	srand (time(NULL));
	// Load cora dataset
	Graph coraGraph = Graph();
	coraGraph.initFromCoraGraphFile(CORA_GRAPH_FILE_PATH);
	coraGraph.loadCoraLabelFile(CORA_LABEL_FILE_PATH);

	// Experiment setting
	ExperimentParams params = ExperimentParams();
	runInfoPropExperiment(coraGraph, params);
	return 0;
}
