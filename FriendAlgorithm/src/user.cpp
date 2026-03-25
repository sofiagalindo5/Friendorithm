#include "user.h"

using namespace std;

User::User(){
    user_id = 0;
    age = 0;
    school = "";
    major = "";
    industry = "";
}

User::User(int id, int age, const string& school, const string& major, const string& industry){
    user_id = id;
    this->age = age;
    this->school = school;
    this->major = major;
    this->industry = industry;
}