//
// Created by Frank on 5/13/2025.
//

#ifndef MODULES_H
#define MODULES_H

#include <string>
#include <unordered_map>

#include "Item.h"
#include "Record.h"
#include "User.h"
using namespace std;

//date function
string getDate();



//actual modules
int handleAddItem(unordered_map<string, Item*>& items);
int handleAddUser(unordered_map<int, User>& users);
int handleCheckOutItem(DynArr<Record>& borrowHistory,
    unordered_map<string, int>& activeBorrowMap,
    unordered_map<string, Item*>& items,
    unordered_map<int, User>& users);

int handleCheckInItem(DynArr<Record>& borrowHistory,
    unordered_map<string, int>& activeBorrowMap,
    unordered_map<string, Item*>& items);

void handlePrintUserRecords(const DynArr<Record>& borrowHistory,
    const unordered_map<string, Item*>& items,
    const unordered_map<int, User>& users);

unordered_map<string, int> loadActiveBorrowMap(DynArr<Record>& borrowHistory);

#endif //MODULES_H
