//
// Created by Frank on 5/10/2025.
//

#include "User.h"

#include <iostream>

User::User(std::string n, int id): name(n), userID(id) {}
void User::display() const {
    std::cout << "User: " << name << " (ID: " << userID << ")\n";
}

