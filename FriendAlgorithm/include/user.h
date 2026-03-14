#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
    int user_id;
    int age;
    std::string school;
    std::string major;
    std::string industry;

    User();
    User(int id, int age, const std::string& school, const std::string& major, const std::string& industry);
};

#endif