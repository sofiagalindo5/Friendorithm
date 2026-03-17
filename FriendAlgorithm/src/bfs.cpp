#include "bfs.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

int countMutualFriends(const Graph& graph, int user1, int user2) {
    const vector<int>& neighbors1 = graph.getNeighbors(user1);
    const vector<int>& neighbors2 = graph.getNeighbors(user2);

    unordered_set<int> set1;
    for (int n : neighbors1)
    {
        set1.insert(n);
    }
    int count = 0;
    for (int n : neighbors2)
    {
        if (set1.find(n) != set1.end())
        {
            count++;
        }
    }
    return count;
}

vector<int> bfsRecommend(const Graph& graph, int startUserId, int maxDepth, int topK, int& nodesVisited) {
    vector<int> recommendations;
    nodesVisited = 0;

    if (!graph.hasUser(startUserId)) {
        return recommendations;
    }

    queue<int> q;
    unordered_set<int> visited;
    unordered_map<int,int> distance;

    vector<pair<int,pair<int,int>>> candidates;
    q.push(startUserId);
    visited.insert(startUserId);
    distance[startUserId] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        nodesVisited++;
        if (distance[current] >= maxDepth){
            continue;
        }
        const vector<int>& neighbors = graph.getNeighbors(current);
        for (int neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
                if (neighbor != startUserId && !graph.areFriends(startUserId, neighbor)) {
                    int mutual = countMutualFriends(graph,startUserId,neighbor);
                    candidates.push_back({neighbor,{mutual,distance[neighbor]}});
                }
            }
        }
    }
    sort(candidates.begin(), candidates.end(),[](const pair<int,pair<int,int>>& a, const pair<int,pair<int,int>>& b){
        if (a.second.first != b.second.first){
            return a.second.first > b.second.first;
        }
        if (a.second.second != b.second.second){
            return a.second.second < b.second.second;
        }
        return a.first < b.first;
    });
    for (int i = 0; i < (int)candidates.size() && i < topK; i++) {
        recommendations.push_back(candidates[i].first);
    }
    return recommendations;
}