//
// Created by Frank on 5/13/2025.
//

#ifndef MODULES_H
#define MODULES_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Item.h"
#include "Record.h"
#include "User.h"
using namespace std;


int handleAddItem(unordered_map<string, Item*>& items);
int handleAddUser(unordered_map<int, User>& users);
int handleCheckOutItem(vector<Record>& borrowHistory,unordered_map<string, Item*>& items, unordered_map<int, User>& users);
int handleCheckInItem(vector<Record>& borrowHistory,unordered_map<string, Item*>& items, unordered_map<int, User>& users);


#endif //MODULES_H
