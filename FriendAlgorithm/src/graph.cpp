#include "graph.h"

using namespace std;

Graph::Graph()
{
    //user ids start at 1 not 0 
    adjList.resize(1);
}

Graph::Graph(int numUsers)
{
    //makes graph big enough
    adjList.resize(numUsers + 1);
}

void Graph::resizeIfNeeded(int userId)
{
    if (userId >= adjList.size())
    {
        adjList.resize(userId + 1);
    }
}

void Graph::addWeightedEdge(int user1, int user2, int weight)
{
    //edge cases
    if (user1 <= 0 || user2 <= 0 || user1 == user2)
    {
        return;
    }

    resizeIfNeeded(user1);
    resizeIfNeeded(user2);

    if (!areFriends(user1, user2))
    {
        //adds edges for both 
        adjList[user1].push_back(make_pair(user2, weight));
        adjList[user2].push_back(make_pair(user1, weight));
    }
}

bool Graph::areFriends(int user1, int user2) const
{
    if (user1 <= 0 || user2 <= 0)
    {
        return false;
    }

    if (user1 >= adjList.size() || user2 >= adjList.size())
    {
        return false;
    }

    for (int i = 0; i < adjList[user1].size(); i++)
    {
        if (adjList[user1][i].first == user2)
        {
            return true;
        }
    }

    return false;
}

const vector<pair<int, int>>& Graph::getNeighbors(int userId) const
{
    if (userId <= 0 || userId >= adjList.size())
    {
        return emptyList;
    }
    
    //returns full list of neighbors
    return adjList[userId];
}

int Graph::getNumUsers() const
{
    return adjList.size() - 1;
}