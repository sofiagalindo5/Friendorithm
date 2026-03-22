#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User
{
public:
    int user_id;
    int age;
    string school;
    string major;
    string industry;

    User();
    User(int id, int age, const string& school, const string& major, const string& industry);
};

#endif