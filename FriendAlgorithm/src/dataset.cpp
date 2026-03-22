#include "dataset.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// possible attributes to randomize
vector<string> schools = {
    "University of Florida",
    "Florida State University",
    "Harvard University",
    "Boston University",
    "University of Miami",
    "University of Central Florida",
    "Florida International University",
    "University of South Florida",
    "Florida Atlantic University",
    "Florida A&M University"
};

vector<string> majors = {
    "Computer Science",
    "Business",
    "Biology",
    "Engineering",
    "Psychology",
    "Education",
    "Nursing",
    "Communications",
    "Economics",
    "Political Science"
};

vector<string> industries = {
    "Technology",
    "Healthcare",
    "Education",
    "Finance",
    "Marketing",
    "Manufacturing",
    "Retail",
    "Government",
    "Nonprofit",
    "Media"
};

// creates certain number of fake users
vector<User> generateUsers(int numUsers)
{
    vector<User> users;

    for (int i = 1; i <= numUsers; i++)
    {
        int age = rand() % 13 + 18;
        string school = schools[rand() % schools.size()];
        string major = majors[rand() % majors.size()];
        string industry = industries[rand() % industries.size()];

        users.push_back(User(i, age, school, major, industry));
    }

    return users;
}

// calculates how similar two users are
// smaller edge weight = very similar
// larger edge weight = not similar
int calculateWeight(const User& user1, const User& user2)
{
    int weight = 10;

    if (user1.school == user2.school)
    {
        weight -= 3;
    }

    if (user1.major == user2.major)
    {
        weight -= 3;
    }

    if (user1.industry == user2.industry)
    {
        weight -= 2;
    }

    if (abs(user1.age - user2.age) <= 2)
    {
        weight -= 2;
    }

    if (weight < 1)
    {
        weight = 1;
    }

    return weight;
}

// creates friendship edges
void generateFriendships(Graph& graph, const vector<User>& users, int friendsPerUser)
{
    int numUsers = users.size();

    for (int i = 0; i < numUsers; i++)
    {
        int currentUserId = users[i].user_id;
        int added = 0;
        int attempts = 0;
        int maxAttempts = friendsPerUser * 20;

        while (added < friendsPerUser && attempts < maxAttempts)
        {
            int randomIndex = rand() % numUsers;
            int friendId = users[randomIndex].user_id;

            if (friendId != currentUserId && !graph.areFriends(currentUserId, friendId))
            {
                int weight = calculateWeight(users[i], users[randomIndex]);
                graph.addWeightedEdge(currentUserId, friendId, weight);
                added++;
            }

            attempts++;
        }
    }
}

// saves users to file
void saveUsersToFile(const vector<User>& users, const string& filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Could not open file for writing: " << filename << endl;
        return;
    }

    for (int i = 0; i < users.size(); i++)
    {
        file << users[i].user_id << ","
             << users[i].age << ","
             << users[i].school << ","
             << users[i].major << ","
             << users[i].industry << "\n";
    }

    file.close();
}

// reads and saves users to vector
vector<User> loadUsersFromFile(const string& filename)
{
    vector<User> users;
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Could not open file for reading: " << filename << endl;
        return users;
    }

    int id;
    int age;
    string school;
    string major;
    string industry;
    char comma;

    while (file >> id >> comma >> age >> comma)
    {
        getline(file, school, ',');
        getline(file, major, ',');
        getline(file, industry);

        users.push_back(User(id, age, school, major, industry));
    }

    file.close();
    return users;
}