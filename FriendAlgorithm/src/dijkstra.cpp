#include "dijkstra.h"
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

//will get shortest weighted path (most similiar)
vector<int> dijkstraShortestPaths(const Graph& graph, int startUserId, int& nodesVisited){
    if (startUserId <= 0 || startUserId > graph.getNumUsers()) {
        return {};
    }

    int numUsers = graph.getNumUsers();
    vector<int> dist(numUsers + 1, INT_MAX);
    vector<bool> visited(numUsers + 1, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[startUserId] = 0;
    pq.push({0, startUserId});
    nodesVisited = 0;

    while (!pq.empty()){
        int currentUser = pq.top().second;
        pq.pop();

        if (visited[currentUser]) {
            continue;
        }

        visited[currentUser] = true;
        nodesVisited++;

        const vector<pair<int,int>>& neighbors = graph.getNeighbors(currentUser);

        for (auto& neighborPair : neighbors){
            int neighbor = neighborPair.first;
            int weight = neighborPair.second;

            if (dist[currentUser] + weight < dist[neighbor]){
                dist[neighbor] = dist[currentUser] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    return dist;
}

// recommendations
vector<int> getDijkstraRecommendations(const Graph& graph, int startUserId, int topK, int& nodesVisited){
    vector<int> dist = dijkstraShortestPaths(graph, startUserId, nodesVisited);
    vector<pair<int, int>> candidates;

    for (int userId = 1; userId <= graph.getNumUsers(); userId++){
        if (userId == startUserId) continue;
        if (dist[userId] == INT_MAX) continue;
        if (graph.areFriends(startUserId, userId)) continue;

        int score = dist[userId];
        candidates.push_back({score, userId});
    }
    sort(candidates.begin(), candidates.end());
    vector<int> recommendations;

    for (int i = 0; i < candidates.size() && i < topK; i++){
        recommendations.push_back(candidates[i].second);
    }
    return recommendations;
}