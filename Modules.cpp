//
// Created by Frank on 5/13/2025.
//


#include <string>
#include <unordered_map>
#include <vector>


#include "Modules.h"

#include <chrono>
#include <iostream>
#include <limits>
#include <sstream>

#include "Item.h"
#include "Record.h"
#include "User.h"
using namespace std;


//--------------------------- HELPERS ---------------------------
string getDate() {
    auto now = std::chrono::system_clock::now();
    std::string date_string = std::format("{:%Y-%m-%d}", now);
    return date_string;
}

//--------------------------- MODULES ---------------------------

int handleAddItem(unordered_map<string, Item*>& items) {
    cout<<"Please select the type of the new item with 1,2,3:"<<endl
    <<"1. Book"<<endl
    <<"2. Ebook"<<endl
    <<"3. Magazine"<<endl
    ;
    int type=0;

    std::string line;
    std::string segment;
    string title, author, publishDate, serial;
    char cont=0;

    while(true) {
        cont=0;
        cin>>type;
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the \n leftover in buffer

        if(type<=0 || type>3) {
            cout<<"Invalid item type! Please enter again"<<endl;

            continue;
        }
        cout<<"Please write the title, author, publish date and the serial number (separated by a comma)"<<endl;

        std::getline(std::cin, line);
        std::stringstream ss(line);

        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, publishDate, ',');
        std::getline(ss, serial, ',');

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
        cout<<"Do you want to add another item? type 'y' to continue adding."<<endl;
        cin>>cont;
        if(cont!='y')
            break;
    }
    return 0;
}



int handleCheckOutItem(vector<Record>& borrowHistory,unordered_map<string, Item*>& items, unordered_map<int, User>& users) {
    int userID;
    string SerialNum;
    cout<<"Please write the serial number: "<<endl;
    cin>>SerialNum;

    //Inputs & checking
    auto itemIt=items.find(SerialNum);
    if(itemIt!=items.end()) {
        if(!(itemIt->second->isAvailable())) {
            cout<<"item is not available! Exiting..."<<endl;
            return 3;
        }
    }
    else {
        cout<<"item id is not found in list! Exiting..."<<endl;
        return 1;
    }
    cout<<SerialNum;
    cout<<"Please write the user id: "<<endl;
    cin>>userID;

    auto userIt=users.find(userID);
    if(userIt==users.end()) {
        cout<<"user id is not found in list! Exiting..."<<endl;
        return 2;
    }

    //Getting Today's date
    string today=getDate();

    Record record{userIt->second.getID(),itemIt->second->getSerialNum(),today,""};
    borrowHistory.push_back(record);

    cout<<"Check out success!";


    return 0;
}

int handleCheckInItem(vector<Record>& borrowHistory,unordered_map<string, Item*>& items, unordered_map<int, User>& users) {
    string SerialNum;
    cout<<"Please write the serial number: "<<endl;
    cin>>SerialNum;
    auto it=items.find(SerialNum);
    if(it!=items.end()) {
        if(!(it->second->isAvailable())) {
            it->second->checkIn();
            string today=getDate();

            //TODO: Change this to active borrow map
            auto it = std::find_if(borrowHistory.rbegin(), borrowHistory.rend(),
    [&](const Record& record) {
                return record.serialNum == SerialNum && record.returnDate.empty();
            });

            if (it != borrowHistory.rend()) {
                it->returnDate = today;
            } else {
                std::cout << "Item is not currently checked out.\n";
            }

        }
        else {
            cout<<"This item is already checked out!"<<endl;
            return 3;
        }
    }
    else {
        cout<<"serial number is not found in list!"<<endl;
        return 1;
    }
    return 0;
}
