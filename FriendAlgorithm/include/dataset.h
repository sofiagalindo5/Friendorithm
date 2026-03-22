#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
#include "user.h"
#include "graph.h"

using namespace std;

// creates vector of users
vector<User> generateUsers(int numUsers);

// adds friendship edges
void generateFriendships(Graph& graph, const vector<User>& users, int friendsPerUser);

// calculate edge weight between users
int calculateWeight(const User& user1, const User& user2);

// save/load users to file
void saveUsersToFile(const vector<User>& users, const string& filename);
vector<User> loadUsersFromFile(const string& filename);

#endif