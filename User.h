//
// Created by Frank on 5/10/2025.
//

#ifndef USER_H
#define USER_H
#include <string>


class User {
    std::string name;
    int userID;
public:
    User(std::string n, int id);
    void display() const;

    std::string getName() const {return name;}
    int getID() const {return userID;}
};



#endif //USER_H
