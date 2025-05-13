
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <format>

#include "Item.h"
#include "Modules.h"
#include "User.h"
#include "Record.h"
#include "InputHelpers.h"
using namespace std;




void displayInstructions() {
    cout<<endl
    <<"Please write a number from the list below to use the function!"<<endl
    <<"1: Check out an item"<<endl
    <<"2: Check in an item"<<endl
    <<"3: Add a user"<<endl
    <<"4: Add an item"<<endl
    <<"5: View all borrow history"<<endl
    <<"6: Exit"<<endl
    ;
}

int main() {
    //loading data from files
    unordered_map<string, Item*> items=loadItems(); //stores all items. Serial number is index
    unordered_map<int, User> users=loadUsers(); //stores all users. userID is index (User is simple, so store by value)

    //defining the remaining data structures
    vector<Record> borrowHistory; //list of all borrow records

    bool continueFlag=true;

    //test values
    // User u1("john");
    // User u2("Alice");
    // Book b1("test1","oliver","1","1900-01-01");
    // Book b2("test2","eszter","2","2021-04-27");

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
        int choice=readValue<int>();
        switch (choice) {
            case 1:
                handleCheckOutItem(borrowHistory,items,users);
                break;
            case 2:
                handleCheckInItem(borrowHistory,items,users);
                break;
            case 3:
                handleAddUser(users);
            case 4:
                handleAddItem(items);
                break;
            case 5:
                printRecordList(borrowHistory);
                break;
            case 6:
                continueFlag=false;
                saveItems(items);
                saveUsers(users);
                cout<<"Goodbye!";
                break;

            default:
                cout<<"Not a valid option. Try again!"<<endl;
                break;
        }

    }

    return 0;
}
