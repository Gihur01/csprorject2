//
// Created by Frank on 5/14/2025.
//

#ifndef PRINTER_H
#define PRINTER_H
#include <unordered_map>
#include <vector>

#include "Item.h"
#include "Record.h"
#include "User.h"

using namespace std;


class Printer {
public:
    //Column widths
    static const int widthID;
    static const int widthName;
    static const int widthSerial;
    static const int widthTitle;
    static const int widthDate;

    static const int widthCheckoutStatus;

    static const int widthSeparatorRecords;
    static const int widthSeparatorItems;
    static const int widthSeparatorUsers;

    static void printRecordsHeader();

    static void printRecordList(const DynArr<Record>& records,
        const unordered_map<string, Item*>& items,
        const unordered_map<int, User>& users,
        int userID=-1);

    static void printActiveBorrowList(const DynArr<Record>& records,
        const unordered_map<string, int>& activeBorrowMap,
        const unordered_map<string, Item*>& items,
        const unordered_map<int, User>& users);

    //testing functions
    static void printUsersList(const unordered_map<int, User>& users);
    static void printItemList(const unordered_map<string, Item*>& items);
};



#endif //PRINTER_H
