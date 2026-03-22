#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

using namespace std;

class Graph
{
private:
//outer vector = each index is a user id
//inner vecyor list of user friendships 
    vector<vector<pair<int, int>>> adjList;

//each pair stores friendId and weight 
    vector<pair<int, int>> emptyList;

    void resizeIfNeeded(int userId);

public:
    Graph();
    Graph(int numUsers);

    void addWeightedEdge(int user1, int user2, int weight);

    bool areFriends(int user1, int user2) const;

    const vector<pair<int, int>>& getNeighbors(int userId) const;

    int getNumUsers() const;
};

#endif