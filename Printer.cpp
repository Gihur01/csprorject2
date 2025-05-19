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
const int Printer::widthName = 15;
const int Printer::widthSerial = 15;
const int Printer::widthTitle = 20;
const int Printer::widthDate = 20;

const int Printer::widthCheckoutStatus=5;

const int Printer::widthSeparatorRecords= widthID+ widthName+ widthSerial+widthTitle+2*widthDate;
const int Printer::widthSeparatorItems=widthSerial+widthTitle+widthName+widthDate+widthCheckoutStatus;
const int Printer::widthSeparatorUsers=widthID+widthName;

void Printer::printRecordsHeader() {
    cout<< left
    << setw(widthID) << "User ID"
    << setw(widthName)<< "User name"
    << setw(widthSerial) << "Serial Num"
    << setw(widthTitle)<< "Title"
    << setw(widthDate) << "Borrow Date"
    << setw(widthDate) << "Return Date"
    << endl;

    cout << string(widthSeparatorRecords, '-') << endl; //horizontal separator
}


void Printer::printRecordList(const DynArr<Record>& records,
    const unordered_map<string, Item*>& items,
    const unordered_map<int, User>& users,
    const int userIDSearchValue) {

    printRecordsHeader();

    // Rows
    for (int i=0;i<records.getLength();i++) {
        const auto&[userID, serialNum, borrowDate, returnDate]=records[i];
        if(userIDSearchValue!=-1 && userID!=userIDSearchValue) {
            continue;
        }
            cout<< left
            << setw(widthID) << userID
            <<setw(widthName) << users.at(userID).getName()
            << setw(widthSerial) << serialNum
            << setw(widthTitle) << items.at(serialNum)->getTitle()
            << setw(widthDate) << borrowDate
            << setw(widthDate) << returnDate
            << endl;

    }
    cout<<"\n\n"; //This just separates the table from the menu options a bit
}


void Printer::printActiveBorrowList(const DynArr<Record>& records,
        const unordered_map<string, int>& activeBorrowMap,
        const unordered_map<string, Item*>& items,
        const unordered_map<int, User>& users) {
    printRecordsHeader();

    // Rows
    for (const auto& [id,index] : activeBorrowMap) {
        const Record& record=records[index];
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





void Printer::printUsersList(const unordered_map<int, User>& users) {
    cout<< left
    << setw(widthID) << "User ID"
    << setw(widthName)<< "User name"<<endl
    << string(widthSeparatorUsers, '-') << endl
    ;

    for(const auto&[id,user]:users) {
        cout<< left
        << setw(widthID) << user.getID()
        <<setw(widthName) << user.getName()
        <<endl;
    }
    cout<<endl;
}
void Printer::printItemList(const unordered_map<string, Item*>& items) {
    cout<< left
    << setw(widthSerial) << "Serial Num"
    << setw(widthTitle)<< "Title"
    << setw(widthName)<< "Author"
    << setw(widthDate)<< "Publish Date"
    << setw(widthCheckoutStatus)<< "Available"<<endl
    << string(widthSeparatorItems, '-') << endl
    ;
    for(const auto&[id,item]:items) {
        string isAvailable=item->isAvailable()? string("Yes"):string("No");
        cout<< left
        << setw(widthSerial) << id
        << setw(widthTitle)<< item->getTitle()
        << setw(widthName)<< item->getAuthor()
        << setw(widthDate)<< item->getPublishDate()
        << setw(widthCheckoutStatus)<< isAvailable
        <<endl;
    }
    cout<<endl;
}
