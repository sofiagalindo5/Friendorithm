#include <iostream>
#include <vector>
#include "user.h"
#include "graph.h"
#include "dataset.h"
#include "dijkstra.h"

using namespace std;

int main()
{
    int numUsers = 100;
    int friendsPerUser = 5;
    int chosenUserId = 1;
    int topK = 10;

    cout << "Generating users..." << endl;
    vector<User> users = generateUsers(numUsers);

    cout << "Creating graph..." << endl;
    Graph graph(numUsers);

    cout << "Generating friendships..." << endl;
    generateFriendships(graph, users, friendsPerUser);

    cout << endl;
    cout << "Testing recommendations for User " << chosenUserId << ":" << endl;

    int nodesVisited = 0;
    vector<int> recommendations = getDijkstraRecommendations(graph, chosenUserId, topK, nodesVisited);

    cout << "Top " << topK << " recommended friends:" << endl;

    for (int i = 0; i < recommendations.size(); i++)
    {
        int recommendedId = recommendations[i];

        cout << i + 1 << ". User ID: " << recommendedId << endl;
        cout << "   Age: " << users[recommendedId - 1].age << endl;
        cout << "   School: " << users[recommendedId - 1].school << endl;
        cout << "   Major: " << users[recommendedId - 1].major << endl;
        cout << "   Industry: " << users[recommendedId - 1].industry << endl;
        cout << endl;
    }

    cout << "Nodes visited by Dijkstra: " << nodesVisited << endl;

    return 0;
}