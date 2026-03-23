#include "bfs.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

int countMutualFriends(const Graph& graph, int user1, int user2) {
    const vector<pair<int,int>>& neighbors1 = graph.getNeighbors(user1);
    const vector<pair<int,int>>& neighbors2 = graph.getNeighbors(user2);

    unordered_set<int> set1;
    for (auto n : neighbors1){
        set1.insert(n.first);
    }
    int count = 0;
    for (auto n : neighbors2){
        if (set1.find(n.first) != set1.end())
        {
            count++;
        }
    }
    return count;
}

vector<int> bfsRecommend(const Graph& graph, int startUserId, int maxDepth, int topK, int& nodesVisited) {
    if (startUserId <= 0 || startUserId > graph.getNumUsers()) {
        return {};
    }
    if (graph.getNumUsers() == 0) {
        return {};
    }

    vector<int> recommendations;
    nodesVisited = 0;

    queue<int> q;
    unordered_set<int> visited;
    unordered_map<int,int> distance;

    vector<pair<int,pair<int,int>>> candidates;
    unordered_set<int> added;
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
        const vector<pair<int,int>>& neighbors = graph.getNeighbors(current);
        for (auto neighborPair : neighbors){
            int neighbor = neighborPair.first;
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
                if (neighbor != startUserId && !graph.areFriends(startUserId, neighbor)) {
                    if (added.find(neighbor) == added.end()) {
                        int mutual = countMutualFriends(graph, startUserId, neighbor);
                        int weight = 10;
                        for (auto p : graph.getNeighbors(startUserId)) {
                            if (p.first == neighbor) {
                                weight = p.second;
                                break;
                            }
                        }
                        int score = mutual * 3 - weight;
                        candidates.push_back({neighbor,{score,distance[neighbor]}});
                        added.insert(neighbor);
                    }
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