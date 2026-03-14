#include <iostream>
#include "dataset.h"
#include "graph.h"

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

    return 0;
}