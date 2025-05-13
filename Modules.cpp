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

using namespace std;


//--------------------------- HELPERS ----------------
string getDate() {
    auto now = std::chrono::system_clock::now();
    std::string date_string = std::format("{:%Y-%m-%d}", now);
    return date_string;
}

//--------------------------- MODULES ---------------------

int handleAddItem(unordered_map<string, Item*>& items) {
    cout<<"Please select the type of the new item with 1,2,3:"<<endl
    <<"1. Book"<<endl
    <<"2. Ebook"<<endl
    <<"3. Magazine"<<endl
    ;
    int type=0;

    string line;
    string title, author, publishDate, serial;
    vector<string> CSVList;

    while(true) {
        string typeInput;
        getline(cin, typeInput);
        std::stringstream(typeInput) >> type; // Clear the \n leftover in buffer

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
}


int handleCheckOutItem(vector<Record>& borrowHistory,unordered_map<string, Item*>& items, unordered_map<int, User>& users) {
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
        userIt->second.display();

        if (userIt == users.end()) {
            throw 2;  // User not found
        }

        //Getting Today's date
        string today=getDate();

        Record record{userIt->second.getID(),itemIt->second->getSerialNum(),today,""};
        borrowHistory.push_back(record);

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

int handleCheckInItem(vector<Record>& borrowHistory,unordered_map<string, Item*>& items, unordered_map<int, User>& users) {
    try{
        string SerialNum=readStr("Please write the serial number: \n");

        auto it = items.find(SerialNum);
        if (it == items.end()) {
            throw 1; //Item not found
        }

        if (it->second->isAvailable()) {
            throw 3; //Item already checked in
        }

        //Check in the item
        it->second->checkIn();
        string today = getDate();

        //Find the record without return date
        auto recordIt = std::find_if(borrowHistory.rbegin(), borrowHistory.rend(),
            [&](const Record& record) {
                return record.serialNum == SerialNum && record.returnDate.empty();
            });

        if (recordIt != borrowHistory.rend()) {
            recordIt->returnDate = today;
        } else {
            throw 2;
        }

        cout << "Check in successful!\n";
        return 0;
    }
    catch (int e) {
        switch (e) {
            case 1:
                cout<<"Error: Serial number not found in item list!"<< endl;
                break;
            case 2:
                cout <<"Error: No checkout record was found for this item.\n";
            case 3:
                cout<< "Error: This item is already checked in!" << endl;
                break;
            default:
                cout<< "Unknown error occurred during check-in." << endl;
        }
        return e;
    }
}
