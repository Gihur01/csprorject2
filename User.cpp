//
// Created by Frank on 5/10/2025.
//

#include "User.h"

#include <fstream>
#include <iostream>

User::User(std::string n, int id): name(n), userID(id) {}
void User::display() const {
    std::cout << "User: " << name << " (ID: " << userID << ")\n";
}

void saveUsers(const std::unordered_map<int, User>& users) {
    std::ofstream outFile("userdb.txt", std::fstream::out);
    for (const auto& [id, user] : users) {
        outFile << id << "," << user.getName() << "\n";
    }
}

std::unordered_map<int,User> loadUsers() {
    std::unordered_map<int, User> users;
    std::ifstream inFile("userdb.txt");
    if(!inFile)
        return users;
    int id;
    std::string name;

    while (inFile>>id) {
        if (inFile.get() == ',')
            std::getline(inFile, name);
        users.emplace(id, User(name, id));
    }
    return users;
}