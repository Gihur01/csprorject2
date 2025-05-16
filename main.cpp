
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
#include "Printer.h"

using namespace std;




void displayInstructions() {
    cout<<endl
    <<"Please write a number from the list below to use the function!"<<endl
    <<"1: Check out an item"<<endl
    <<"2: Check in an item"<<endl
    <<"3: Add a user"<<endl
    <<"4: Add an item"<<endl
    <<"5: View all borrow history"<<endl
    <<"6: View borrow history of a user"<<endl
    <<"7: View all current checked out items"<<endl
    <<"8: Exit"<<endl
    ;
}

int main() {
    //loading data from files
    unordered_map<string, Item*> items=loadItems(); //stores all items. Serial number is index
    unordered_map<int, User> users=loadUsers(); //stores all users. userID is index (User is simple, so store by value)
        //this loading has the consequence of reading the static variable "userIDCounter" from userdb too.

    //defining the remaining data structures
    vector<Record> borrowHistory=loadRecords(); //list of all borrow records
    std::unordered_map<std::string, Record*> activeBorrowMap =loadActiveBorrowMap(borrowHistory); //stores all records that are yet to be checked in.

    bool continueFlag=true;

    // test values
     // User u1("john");
     // User u2("Alice");
     // Book b1("book1","oliver","1","1900-01-01");
     // Book b2("book2","eszter","2","2021-04-27");
     //
     // users.emplace(1,u1);
     // users.emplace(2,u2);
     // items.emplace("1",&b1);
     // items.emplace("2",&b2);

    //test print

    Printer::printUsersList(users);
    Printer::printItemList(items);


    while(continueFlag) {
        displayInstructions();
        int choice=readValue<int>();
        switch (choice) {
            case 1:
                handleCheckOutItem(borrowHistory,activeBorrowMap,items,users);
                break;
            case 2:
                handleCheckInItem(activeBorrowMap,items);
                break;
            case 3:
                handleAddUser(users);
                break;
            case 4:
                handleAddItem(items);
                break;
            case 5:
                Printer::printRecordList(borrowHistory,items,users);
                break;
            case 6:
                handlePrintUserRecords(borrowHistory,items,users);
                break;

            case 7:
                Printer::printActiveBorrowList(activeBorrowMap,items,users);
                break;

            case 8:
                continueFlag=false;
                saveItems(items);
                saveUsers(users);
                saveRecords(borrowHistory);
                cout<<"Goodbye!";

                break;

            default:
                cout<<"Not a valid option. Try again!"<<endl;

        }

    }

    return 0;
}
