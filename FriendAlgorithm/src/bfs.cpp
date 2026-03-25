#include "bfs.h"
#include <queue>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;


struct Candidate {
    int id;
    int score;
    int distance;
};


int countMutualFriends(const Graph& graph, int user1, int user2) {
    const vector<pair<int,int>>& neighbors1 = graph.getNeighbors(user1);
    const vector<pair<int,int>>& neighbors2 = graph.getNeighbors(user2);

    unordered_set<int> set1;
    for (auto& n : neighbors1) {
        set1.insert(n.first);
    }

    int count = 0;
    for (auto& n : neighbors2) {
        if (set1.count(n.first)) {
            count++;
        }
    }
    return count;
}

int calculateScore(const Graph& graph, int startUserId, int neighbor) {
    return countMutualFriends(graph, startUserId, neighbor);
}


vector<int> bfsRecommend(const Graph& graph, int startUserId, int maxDepth, int topK, int& nodesVisited) {
    if (startUserId <= 0 || startUserId > graph.getNumUsers()) {
        return {};
    }

    vector<int> recommendations;
    nodesVisited = 0;
    queue<int> q;
    unordered_set<int> visited;
    vector<int> distance(graph.getNumUsers() + 1, -1);
    vector<Candidate> candidates;

    q.push(startUserId);
    visited.insert(startUserId);
    distance[startUserId] = 0;


    while (!q.empty()) {
        int current = q.front();
        q.pop();
        nodesVisited++;

        if (distance[current] >= maxDepth) continue;

        const vector<pair<int,int>>& neighbors = graph.getNeighbors(current);

        for (auto& neighborPair : neighbors) {
            int neighbor = neighborPair.first;
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
                if (neighbor != startUserId && !graph.areFriends(startUserId, neighbor)) {
                    int score = calculateScore(graph, startUserId, neighbor);
                    candidates.push_back({neighbor, score, distance[neighbor]});
                }
            }
        }
    }


    sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) {
        if (a.score != b.score)
            return a.score > b.score;
        if (a.distance != b.distance)
            return a.distance < b.distance;
        return a.id < b.id;
    });


    for (int i = 0; i < (int)candidates.size() && i < topK; i++) {
        recommendations.push_back(candidates[i].id);
    }
    return recommendations;
}