//
// Created by Frank on 5/14/2025.
//

#include "Printer.h"

#include <iomanip>
#include <iostream>
#include <unordered_map>

#include "Item.h"
#include "User.h"
using namespace std;

const int Printer::widthID = 10;
const int Printer::widthName = 10;
const int Printer::widthSerial = 15;
const int Printer::widthTitle = 15;
const int Printer::widthDate = 15;

const int Printer::widthSeparator= widthID+ widthName+ widthSerial+widthTitle+2*widthDate;

void Printer::printTableHeader() {
    cout<< left
    << setw(widthID) << "User ID"
    << setw(widthName)<< "User name"
    << setw(widthSerial) << "Serial Num"
    << setw(widthTitle)<< "Title"
    << setw(widthDate) << "Borrow Date"
    << setw(widthDate) << "Return Date"
    << endl;

    cout << string(widthSeparator, '-') << endl; //horizontal separator
}


void Printer::printRecordList(const vector<Record>& records,
    const unordered_map<string, Item*>& items,
    const unordered_map<int, User>& users,
    const int userID) {

    printTableHeader();

    // Rows
    for (const auto& record : records) {
        if(userID!=-1 && record.userID!=userID) {
            continue;
        }
            cout<< left
            << setw(widthID) << record.userID
            <<setw(widthName) << users.at(record.userID).getName()
            << setw(widthSerial) << record.serialNum
            << setw(widthTitle) << items.at(record.serialNum)->getTitle()
            << setw(widthDate) << record.borrowDate
            << setw(widthDate) << record.returnDate
            << endl;

    }
    cout<<"\n\n"; //This just separates the table from the menu options a bit
}


void Printer::printActiveBorrowList(const unordered_map<string, Record*>& activeBorrowMap,
        const unordered_map<string, Item*>& items,
        const unordered_map<int, User>& users) {
    printTableHeader();

    // Rows
    for (const auto& [id,record] : activeBorrowMap) {
            cout<< left
            << setw(widthID) << record->userID
            <<setw(widthName) << users.at(record->userID).getName()
            << setw(widthSerial) << record->serialNum
            << setw(widthTitle) << items.at(record->serialNum)->getTitle()
            << setw(widthDate) << record->borrowDate
            << setw(widthDate) << record->returnDate
            << endl;
    }
    cout<<"\n\n"; //This just separates the table from the menu options a bit

}





void Printer::printUsersList(const unordered_map<int, User>& users) {
    for(const auto&[id,user]:users) {
        cout<<id<<": ["<<user.getID()<<","<<user.getName()<<"]"<<", ";
    }
    cout<<endl;
}
void Printer::printItemList(const unordered_map<string, Item*>& items) {
    for(const auto&[id,item]:items) {
        cout<<"["<<id<<", title: "<<item->getTitle()<<", author: "<<item->getAuthor()<<", availability: "<<item->isAvailable()<<"]"<<", "<<endl;
    }
    cout<<endl;
}
