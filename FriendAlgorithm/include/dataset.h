#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
#include "user.h"
#include "graph.h"

std::vector<User> generateUsers(int numUsers);
void generateFriendships(Graph& graph, const std::vector<User>& users, int friendsPerUser);
int calculateWeight(const User& user1, const User& user2);

void saveUsersToFile(const std::vector<User>& users, const std::string& filename);
std::vector<User> loadUsersFromFile(const std::string& filename);

#endif