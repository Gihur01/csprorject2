//
// Created by Frank on 5/10/2025.
//

#ifndef USER_H
#define USER_H
#include <string>
#include <unordered_map>


class User {
    std::string name;
    int userID;
    static int userIDCounter;
public:
    User(std::string n);
    User(User& theOther);
    void display() const;

    std::string getName() const {return name;}
    int getID() const {return userID;}
};


void saveUsers(const std::unordered_map<int, User>& users);
std::unordered_map<int,User> loadUsers();



#endif //USER_H
