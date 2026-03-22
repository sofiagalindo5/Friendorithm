#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include "graph.h"

using namespace std;

int getMinDistanceUser(const vector<int>& dist, const vector<bool>& visited);
vector<int> dijkstraShortestPaths(const Graph& graph, int startUserId, int& nodesVisited);
vector<int> getDijkstraRecommendations(const Graph& graph, int startUserId, int topK, int& nodesVisited);

#endif