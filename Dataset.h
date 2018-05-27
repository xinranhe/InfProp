#ifndef DATASET_H
#define DATASET_H

#include "Graph.h"

#include <string>
using namespace std;

Graph loadFromRawCoraDataset(const string& graphFile, const string& labelFile);

#endif
