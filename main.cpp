#include "Dataset.h"
#include "Graph.h"
#include "InfProp.h"

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
	// Train/test split: -1 if use dataset provided train test split
	double trainRatio;
	// Algorithm params
	int numSimulations;
	double edgeProb;
	bool useDegreeWeight;
	// Default parameters
	ExperimentParams() {
		trainRatio = 0.1;
		numSimulations = 1000;
		edgeProb = 1.0;
		useDegreeWeight = false;
	}

	string toString() {
		return "trainRatio:" + to_string(trainRatio) + 
			   " numSims:" + to_string(numSimulations) + 
		       " edgProb:" + to_string(edgeProb) +
		       " useDegreeWeight:" + to_string(useDegreeWeight);
	}
};

void saveInforPropResult(const string& resultFile, const vector<vector<double>>& results) {
	ofstream fout(resultFile);
	for (int i = 0; i < results.size(); i++) {
		fout << i;
		for (int j = 0; j < results[i].size(); j++) {
			fout << " " << results[i][j];
		}
		fout << endl;
	}
	fout.close();
}

double computeAccuracy(Graph& graph, vector<vector<double>>& results, vector<int> testNodes) {
	int count = 0;
	for (int i = 0; i < testNodes.size(); i++) {
		int nid = testNodes[i];
		int trueLabel = graph.labels[nid][0];
		int inferredLabel = distance(results[nid].begin(), max_element(results[nid].begin()+1, results[nid].end()));
		count += trueLabel == inferredLabel;
	}
	return 1.0 * count / testNodes.size();
}

vector<vector<double>> runInfoPropExperiment(Graph& graph, ExperimentParams params) {
	// Train test split
	if (params.trainRatio > 0) {
		graph.randomTrainTestSplit(params.trainRatio);
	}
	// Run InfoProp algoirthm
	vector<vector<double>> results = infoProp(graph, graph.trainNodes, params.edgeProb, params.numSimulations, params.useDegreeWeight);
	cout << "Exp setting:" << params.toString() << endl;
	cout << "Accuracy:" << computeAccuracy(graph, results, graph.testNodes) << endl;
	return results;
}

void runCoraExperiment() {
	Graph coraGraph = loadFromRawCoraDataset(CORA_GRAPH_FILE_PATH, CORA_LABEL_FILE_PATH);
	ExperimentParams params = ExperimentParams();
	runInfoPropExperiment(coraGraph, params);
}


int main(int argc, char** argv) {
	srand (time(NULL));
	runCoraExperiment();
	return 0;
}
