#ifndef INFO_PROP_H
#define INFO_PROP_H

#include "Graph.h"

#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

vector<vector<double>> infoProp(Graph& graph, unordered_map<int, int>& seedToLabel, double edgeProb, int numSimulations);

void labelNodesWithDijkstra(Graph& graph, unordered_map<int, int>& seedToLabel, vector<vector<double>>& results, default_random_engine& generator, double edgeProb);

# endif