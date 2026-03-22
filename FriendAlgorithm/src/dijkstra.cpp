

//weights of all edges must be non negative 
//must keep track of nodes visited 

#include "dijkstra.h"
#include <algorithm>

using namespace std;

const int INF = 1000000000;

int getMinDistanceUser(const vector<int>& dist, const vector<bool>& visited)
{
    int minDistance = INF;
    int minUser = -1;

    for (int i = 1; i < dist.size(); i++)
    {
        if (!visited[i] && dist[i] < minDistance)
        {
            minDistance = dist[i];
            minUser = i;
        }
    }

    //returns next node to visit (smallest path)
    return minUser;
}

//will get shortest weighted path (most similiar)
vector<int> dijkstraShortestPaths( const Graph& graph, int startUserId, int& nodesVisited)
{
    int numUsers = graph.getNumUsers();

    vector<int> dist(numUsers + 1, INF);
    vector<bool> visited(numUsers + 1, false);

    dist[startUserId] = 0;
    nodesVisited = 0;

    for (int count = 1; count <= numUsers; count++)
    {
        int currentUser = getMinDistanceUser(dist, visited);

        if (currentUser == -1)
        {
            break;
        }

        //marks visited
        visited[currentUser] = true;
        nodesVisited++;

        const vector<pair<int, int>>& neighbors = graph.getNeighbors(currentUser);

        for (int i = 0; i < neighbors.size(); i++)
        {
            int neighborId = neighbors[i].first;
            int weight = neighbors[i].second;

            if (!visited[neighborId] && dist[currentUser] + weight < dist[neighborId])
            {
                dist[neighborId] = dist[currentUser] + weight;
            }
        }
    }

    return dist;
}

vector<int> getDijkstraRecommendations(const Graph& graph, int startUserId, int topK, int& nodesVisited)
{
    vector<int> dist = dijkstraShortestPaths(graph, startUserId, nodesVisited);

    vector<pair<int, int>> candidates;

    for (int userId = 1; userId < dist.size(); userId++)
    {
        if (userId == startUserId)
        {
            continue;
        }

        if (graph.areFriends(startUserId, userId))
        {
            continue;
        }

        if (dist[userId] == INF)
        {
            continue;
        }

        candidates.push_back(make_pair(dist[userId], userId));
    }

    sort(candidates.begin(), candidates.end());

    vector<int> recommendations;

    //takes first 10
    for (int i = 0; i < candidates.size() && i < topK; i++)
    {
        recommendations.push_back(candidates[i].second);
    }

    //returns only user Id
    return recommendations;
}