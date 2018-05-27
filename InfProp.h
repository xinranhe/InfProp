#ifndef INF_PROP_H
#define INF_PROP_H

#include "Graph.h"

#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

vector<vector<double>> infoProp(Graph& graph, vector<int>& train_nodes, double edgeProb, int numSimulations, bool useDegreeWeight);

void labelNodesWithDijkstra(Graph& graph, vector<int>& train_nodes, vector<vector<double>>& results, default_random_engine& generator, double edgeProb, bool useDegreeWeight);

# endif
