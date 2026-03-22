#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
#include "user.h"
#include "graph.h"

//creates vector of users
std::vector<User> generateUsers(int numUsers);

//adds friendship edges 
void generateFriendships(Graph& graph, const std::vector<User>& users, int friendsPerUser);

//calculate edge weight between users
int calculateWeight(const User& user1, const User& user2);

// save/load user to file 
void saveUsersToFile(const std::vector<User>& users, const std::string& filename);
std::vector<User> loadUsersFromFile(const std::string& filename);

#endif