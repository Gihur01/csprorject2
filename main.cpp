#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <chrono>
#include <format>

#include "Item.h"
#include "User.h"
#include "Record.h"
using namespace std;




//--------------------------- HELPERS ---------------------------
string getDate() {
    auto now = std::chrono::system_clock::now();
    std::string date_string = std::format("{:%Y-%m-%d}", now);
    return date_string;
}


//--------------------------- MODULES ---------------------------


//saving & loading usewrs

void saveUsers(const std::unordered_map<int, User>& users) {
    std::ofstream outFile("userdb.txt",fstream::out);
    for (const auto& [id, user] : users) {
        outFile << id << "," << user.getName() << "\n";
    }
}

unordered_map<int,User> loadUsers() {
    unordered_map<int, User> users;
    std::ifstream inFile("userdb.txt");
    if(!inFile)
        return users;
    int id;
    string name;

    while (inFile>>id) {
        if (inFile.get() == ',')
            std::getline(inFile, name);
        users.emplace(id, User(name, id));
    }
    return users;
}

//saving & loading items

void saveItems(const std::unordered_map<std::string, Item*>& items) {
    std::ofstream outFile("itemdb.txt",fstream::out);
    for (const auto& [isbn, item] : items) {

        if (auto* book = dynamic_cast<Book*>(item)) {
            outFile << "Book," << book->getSerialNum() << ","
            << book->getTitle()<< ","
            << book->getAuthor() << ","
            << book->isAvailable() << endl;
        }
        else if (auto* ebook = dynamic_cast<EBook*>(item)) {
            outFile << "EBook," << ebook->getSerialNum() << ","
            << ebook->getTitle()<< ","
            << ebook->getAuthor() << ","
            << ebook->getFormat()<< ","
            << ebook->isAvailable() << endl;
        }
    }
}


std::unordered_map<string, Item*> loadItems() {
    std::unordered_map<string, Item*> items;
    std::ifstream inFile("itemdb.txt");
    if(!inFile)
        return items;

    string line;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        string type, serial, title, author, publishDate, format, availableStr;
        bool available;

        std::getline(ss, type, ',');
        std::getline(ss, serial, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');

        if (type == "Book") {
            std::getline(ss, availableStr);
            available = (availableStr == "1");
            auto* book = new Book(title, author, serial, publishDate);
            if (!available) book->checkOut(); //setting  available state
            items[serial] = book;
        }
        else if (type == "EBook") {
            std::getline(ss, format, ',');
            std::getline(ss, availableStr);
            available = (availableStr == "1");
            auto* ebook = new EBook(title, author, serial, publishDate, format);
            if (!available) ebook->checkOut();
            items[serial] = ebook;
        }
    }

    return items;
}



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



//--------------------------MAIN----------------------------

void displayInstructions() {
    cout<<endl
    <<"Please write a number from the list below to use the function!"<<endl
    <<"1: Check out an item"<<endl
    <<"2: Check in an item"<<endl
    <<"3: Add a user"<<endl
    <<"4: Add an item"<<endl
    <<"5: View all borrow history"<<endl
    <<"6: View borrow history of a user"<<endl
    <<"7: Exit"<<endl
    ;
}

int main() {
    //loading data from files
    unordered_map<string, Item*> items=loadItems(); //stores all items. Serial number is index
    unordered_map<int, User> users=loadUsers(); //stores all users. userID is index (User is simple, so store by value)

    //defining the remaining data structures
    vector<Record> borrowHistory; //list of all borrow records
    std::unordered_map<std::string, Record*> activeBorrowMap;  //records, where the item is not yet checked in

    bool continueFlag=true;

    //test values
    User u1("john",1);
    User u2("Alice",2);
    Book b1("test1","oliver","1","1900-01-01");
    Book b2("test2","eszter","2","2021-04-27");

    // users.emplace(1,u1);
    // users.emplace(2,u2);
    // items.emplace("1",&b1);
    // items.emplace("2",&b2);

    //test print
    for(const auto&[id,user]:users) {
        cout<<"["<<id<<","<<user.getName()<<"]"<<", "<<endl;
    }
    for(const auto&[id,item]:items) {
        cout<<"["<<id<<","<<item->getTitle()<<"]"<<", "<<endl;
    }

    while(continueFlag) {
        displayInstructions();
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:
                handleCheckOutItem(borrowHistory,items,users);
                break;
            case 2:
                handleCheckInItem(borrowHistory,items,users);
                break;
            case 3:

            case 4:
                handleAddItem(items);
                break;
            case 5:
                printRecordList(borrowHistory);
                break;
            case 6:

            case 7:
                continueFlag=false;
                saveItems(items);
                saveUsers(users);
                cout<<"Goodbye!";
                break;

            default:
                break;
        }

    }

    return 0;
}
