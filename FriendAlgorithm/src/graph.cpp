#include "graph.h"
#include <stdexcept>

void Graph::addUser(const User& user)
{
    users[user.user_id] = user;

    if (adjList.find(user.user_id) == adjList.end())
    {
        adjList[user.user_id] = std::vector<int>();
    }
}

void Graph::addEdge(int user1, int user2)
{
    if (user1 == user2)
    {
        return;
    }

    if (!hasUser(user1) || !hasUser(user2))
    {
        return;
    }

    if (areFriends(user1, user2))
    {
        return;
    }

    adjList[user1].push_back(user2);
    adjList[user2].push_back(user1);

    weights[user1][user2] = 1;
    weights[user2][user1] = 1;
}

void Graph::addWeightedEdge(int user1, int user2, int weight)
{
    if (user1 == user2)
    {
        return;
    }

    if (!hasUser(user1) || !hasUser(user2))
    {
        return;
    }

    if (areFriends(user1, user2))
    {
        return;
    }

    adjList[user1].push_back(user2);
    adjList[user2].push_back(user1);

    weights[user1][user2] = weight;
    weights[user2][user1] = weight;
}

bool Graph::hasUser(int userId) const
{
    return users.find(userId) != users.end();
}

bool Graph::areFriends(int user1, int user2) const
{
    auto it = adjList.find(user1);

    if (it == adjList.end())
    {
        return false;
    }

    for (int neighbor : it->second)
    {
        if (neighbor == user2)
        {
            return true;
        }
    }

    return false;
}

const User& Graph::getUser(int userId) const
{
    auto it = users.find(userId);

    if (it == users.end())
    {
        throw std::out_of_range("User not found");
    }

    return it->second;
}

const std::vector<int>& Graph::getNeighbors(int userId) const
{
    auto it = adjList.find(userId);

    if (it == adjList.end())
    {
        throw std::out_of_range("User not found in adjacency list");
    }

    return it->second;
}

int Graph::getWeight(int user1, int user2) const
{
    auto outerIt = weights.find(user1);

    if (outerIt == weights.end())
    {
        return -1;
    }

    auto innerIt = outerIt->second.find(user2);

    if (innerIt == outerIt->second.end())
    {
        return -1;
    }

    return innerIt->second;
}

int Graph::getNumUsers() const
{
    return static_cast<int>(users.size());
}

int Graph::getNumEdges() const
{
    int total = 0;

    for (const auto& pair : adjList)
    {
        total += static_cast<int>(pair.second.size());
    }

    return total / 2;
}