#include <iostream>
#include <vector>
#include "user.h"
#include "graph.h"
#include "dataset.h"
#include "dijkstra.h"
#include <ctime>
#include <chrono>
#include "bfs.h"

using namespace std;

int main() {
    srand(time(0));
    int numUsers = 100000;
    int friendsPerUser = 10;
    int chosenUserId = 1;
    int topK = 10;

    if (chosenUserId <= 0 || chosenUserId > numUsers) {
        cout << "Error: Invalid user ID\n";
        return 0;
    }

    cout << "Comparing BFS and Dijkstra for friend recommendations...\n\n";
    cout << "Total Users: " << numUsers << endl;
    cout << "Generating users..." << endl;
    vector<User> users = generateUsers(numUsers);
    cout << "Creating graph..." << endl;
    Graph graph(numUsers);
    cout << "Generating friendships..." << endl;
    generateFriendships(graph, users, friendsPerUser);
    cout << "Generating recommendations for User " << chosenUserId << "..." << endl;
    cout << endl;

    //---------------------------------- Dijkstra ----------------------------------
    int nodesVisited = 0;
    auto start = chrono::high_resolution_clock::now();
    vector<int> recommendations = getDijkstraRecommendations(graph, chosenUserId, topK, nodesVisited);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Dijkstra Recommendations (Top " << topK << "):" << endl;

    if (recommendations.empty()) {
        cout << "No recommendations found.\n";
    }
    for (int i = 0; i < recommendations.size(); i++){
        int recommendedId = recommendations[i];
        cout << i + 1 << ". User ID: " << recommendedId << endl;
        cout << "    Age: " << users[recommendedId - 1].age << endl;
        cout << "    School: " << users[recommendedId - 1].school << endl;
        cout << "    Major: " << users[recommendedId - 1].major << endl;
        cout << "    Industry: " << users[recommendedId - 1].industry << endl;
        cout << endl;
    }
    cout << "Dijkstra Nodes Visited: " << nodesVisited << endl;
    cout << "Dijkstra Runtime: " << elapsed.count() << " seconds\n";


    //---------------------------------- BFS ----------------------------------
    int bfsVisited = 0;
    auto bfsStart = chrono::high_resolution_clock::now();
    vector<int> bfsRecs = bfsRecommend(graph, chosenUserId, 2, topK, bfsVisited);
    auto bfsEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> bfsTime = bfsEnd - bfsStart;

    cout << "\nBFS Recommendations (Top " << topK << "):\n";

    for (int i = 0; i < bfsRecs.size(); i++){
        int recommendedId = bfsRecs[i];
        cout << i + 1 << ". User ID: " << recommendedId << endl;
        cout << "    Age: " << users[recommendedId - 1].age << endl;
        cout << "    School: " << users[recommendedId - 1].school << endl;
        cout << "    Major: " << users[recommendedId - 1].major << endl;
        cout << "    Industry: " << users[recommendedId - 1].industry << endl;
        cout << endl;
    }

    cout << "BFS Nodes visited: " << bfsVisited << endl;
    cout << "BFS Time taken: " << bfsTime.count() << " seconds\n";


//-----------------------------------------summary------------------------------------------------
    cout << "_________________________________________________________";
    cout << "\nPERFORMANCE COMPARISON\n";
    cout << "Dijkstra visited: " << nodesVisited << " nodes in "<< elapsed.count() << " seconds.\n";;
    cout << "BFS visited: " << bfsVisited << " nodes in "<< bfsTime.count() << " seconds.\n";;
    cout << "-> BFS runs faster and is more practical.\n";
    cout << "    •  Dijkstra checks entire graph\n";
    cout << "    •  BFS only looks at nearby users.\n";
    cout << "Actual users created: " << users.size() << endl;
    cout << "Graph size (users): " << graph.getNumUsers() << endl;

    cout << "\nANALYSIS\n";
    cout << "BFS runs in O(V + E) but is limited to local connections.\n";
    cout << "Dijkstra runs in O((V + E) log V) using a priority queue.\n";

    return 0;
}