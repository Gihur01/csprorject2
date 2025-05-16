//
// Created by Frank on 5/13/2025.
//


#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <iostream>
#include <sstream>

#include "Item.h"
#include "Record.h"
#include "User.h"
#include "Modules.h"
#include "InputHelpers.h"
#include "Printer.h"
#include "DynArr.h"

using namespace std;


//--------------------------- HELPERS ----------------
string getDate() {
    auto now = chrono::system_clock::now();
    string date_string = format("{:%Y-%m-%d}", now);
    return date_string;
}


//--------------------------- MODULES ---------------------

int handleAddItem(unordered_map<string, Item*>& items) {

    int type=0;

    string line;
    string title, author, publishDate, serial;
    vector<string> CSVList;

    while(true) {
        cout<<"Please select the type of the new item with 1,2,3:"<<endl
        <<"1. Book"<<endl
        <<"2. Ebook"<<endl
        <<"3. Magazine"<<endl
        ;

        string typeInput;
        getline(cin, typeInput);
        stringstream(typeInput) >> type; // Clear the \n leftover in buffer

        if(type<=0 || type>3) {
            cout<<"Invalid item type! Please enter again"<<endl;

            continue;
        }


        CSVList=readCSVFields("Please write the title, author, publish date and the serial number (separated by a comma)\n",4);
        title=CSVList[0];
        author=CSVList[1];
        publishDate=CSVList[2];
        serial=CSVList[3];

        Item* item;
        switch (type) {
            case 1:
                item= new Book(title,author,serial,publishDate);
                break;
            case 2:
                item =new EBook(title,author,serial,publishDate);
                break;
            case 3:
                item =new Magazine(title,author,serial,publishDate);
                break;
        }

        item->display();
        items.emplace(serial,item);

        //Showing the continue option
        bool contInput=readYesNo("Do you want to add another item? (y/n)\n");
        if (!contInput)
            break;


    }
    return 0;
}


int handleAddUser(unordered_map<int, User>& users) {
    while(true) {
        string name=readStr("Please enter the user's name (the ID is automatically assigned)\n");
        User tempUser(name);
        users.emplace(tempUser.getID(),tempUser);
        cout<<"Success!"<<endl;
        bool contInput=readYesNo("Do you want to add another user? (y/n)\n");
        if(!contInput)
            break;
    }
    return 0;
}


int handleCheckOutItem(DynArr<Record>& borrowHistory,
    unordered_map<string, Record*>& activeBorrowMap,
    unordered_map<string, Item*>& items,
    unordered_map<int, User>& users) {
    try {
        string SerialNum=readStr("Please write the serial number: \n");

        //Check if item exists
        auto itemIt = items.find(SerialNum);
        if (itemIt == items.end()) {
            throw 1;  // Item not found
        }

        //Check availability
        if (!(itemIt->second->isAvailable())) {
            throw 3;  // Item not available
        }

        // cout<<SerialNum;
        int userID=readValue<int>("Please write the user id: \n");

        //Check if user exists
        auto userIt = users.find(userID);
        // userIt->second.display();

        if (userIt == users.end()) {
            throw 2;  // User not found
        }

        itemIt->second->checkOut();

        //Getting Today's date
        string today=getDate();
        Record record{userIt->second.getID(),SerialNum,today,""};
        borrowHistory.push(record);

        // activeBorrowMap[SerialNum]; //Adding this new record to activeBorrowMap.
        Record* temppRecordPointer=borrowHistory.pLast();
        Record* temp2=borrowHistory.pLast();
        activeBorrowMap.emplace(SerialNum,temppRecordPointer);

        // printItemList(items);

        cout<<"Check out success!";


        return 0;
    }
    catch (int e) {
        switch (e) {
            case 1:
                cout << "Error: Item serial number not found in the list!" << endl; break;
            case 2:
                cout << "Error: User ID not found in the list!" << endl; break;
            case 3:
                cout << "Error: Item is not available!" << endl; break;
            default:
                cout << "Unknown error occurred." << endl;
        }
        return e;
    }
}

int handleCheckInItem(unordered_map<string, Record*>& activeBorrowMap,
    unordered_map<string, Item*>& items) {
    try{
        string SerialNum=readStr("Please write the serial number: \n");

        auto itemIt = items.find(SerialNum);
        if (itemIt == items.end()) {
            throw 1; //Item not found
        }

        if (itemIt->second->isAvailable()) {
            throw 3; //Item already checked in
        }

        //Check in the item
        itemIt->second->checkIn();
        string today = getDate();

        //Find the record without return date
        auto recordIt = activeBorrowMap.find(SerialNum);
        if (recordIt != activeBorrowMap.end()) {
            recordIt->second->returnDate = today;
            activeBorrowMap.erase(recordIt);
        } else {
            throw 2;
        }

        itemIt->second->checkIn();

        cout << "Check in successful!\n\n";

        // Printer::printItemList(items);

        return 0;
    }
    catch (int e) {
        switch (e) {
            case 1:
                cout<<"Error: Serial number not found in item list!"<< endl;
                break;
            case 2:
                cout <<"Error: No checkout record was found for this item.\n";
                break;
            case 3:
                cout<< "Error: This item is already checked in!" << endl;
                break;
            default:
                cout<< "Unknown error occurred during check-in." << endl;
        }
        return e;
    }
}


void handlePrintUserRecords(const DynArr<Record>& borrowHistory,
    const unordered_map<string, Item*>& items,
    const unordered_map<int, User>& users) {
    try {
        int userID;
        while(true) {
             userID=readValue<int>("Please write the user id: \n");
            auto userIt = users.find(userID);
            if (userIt == users.end()) {
                throw 1;  //User not found
            }
            break;
        }
        Printer::printRecordList(borrowHistory,items,users,userID);

    }
    catch (int e) {
        switch (e) {
            case 1:
                cout << "Error: User ID not found in the list!" << endl; break;
            default:
                cout << "Unknown error occurred." << endl;
        }

    }
}

unordered_map<string, Record*> loadActiveBorrowMap(DynArr<Record>& borrowHistory) {
    unordered_map<string, Record*> activeBorrowMap;
    for (int i=0;i<borrowHistory.getLength();i++) {
        Record& record=borrowHistory[i];
        if(record.returnDate.empty()) {
            activeBorrowMap.emplace(record.serialNum,&record);
        }
    }
    return  activeBorrowMap;
}