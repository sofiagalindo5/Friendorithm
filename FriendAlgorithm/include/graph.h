#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include "user.h"

class Graph
{
private:
    std::unordered_map<int, User> users;
    std::unordered_map<int, std::vector<int>> adjList;
    std::unordered_map<int, std::unordered_map<int, int>> weights;

public:
    void addUser(const User& user);
    void addEdge(int user1, int user2);
    void addWeightedEdge(int user1, int user2, int weight);

    bool hasUser(int userId) const;
    bool areFriends(int user1, int user2) const;

    const User& getUser(int userId) const;
    const std::vector<int>& getNeighbors(int userId) const;
    int getWeight(int user1, int user2) const;

    int getNumUsers() const;
    int getNumEdges() const;
};

#endif