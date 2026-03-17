#ifndef BFS_H
#define BFS_H
#include "graph.h"
#include <vector>
int countMutualFriends(const Graph& graph, int user1, int user2);
std::vector<int> bfsRecommend(const Graph& graph, int startUserId, int maxDepth, int topK, int& nodesVisited);
#endif