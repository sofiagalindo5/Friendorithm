#include <iostream>
#include "dataset.h"
#include "graph.h"
#include "bfs.h"
#include <chrono>
using namespace std;

int main()
{
    vector<User> users = generateUsers(100000);

    Graph graph;

    for (const User& user : users)
    {
        graph.addUser(user);
    }

    generateFriendships(graph, users, 10); //gives each user 10 friends

    cout << "Users: " << graph.getNumUsers() << endl;
    cout << "Edges: " << graph.getNumEdges() << endl;

    auto start = chrono::high_resolution_clock::now();
    int nodesVisited = 0;
    vector<int> recs = bfsRecommend(graph, 25, 2, 10, nodesVisited);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "BFS runtime: " << duration.count() << " ms" << endl;
    cout << "Nodes visited: " << nodesVisited << endl;

    return 0;
}