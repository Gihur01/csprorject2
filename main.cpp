
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
#include "DynArr.h"

using namespace std;

void displayMainMenu() {
    cout<<endl
    <<"Please write a number from the list below to use the function!"<<endl
    <<"1: Check out an item"<<endl
    <<"2: Check in an item"<<endl
    <<"3: Add a user"<<endl
    <<"4: Add an item"<<endl
    <<"5: Enter views submenu"<<endl
    <<"6: Save & exit"<<endl
    ;
}

void displayViewsMenu() {
    cout<<endl
    <<"Please select what to view!"<<endl
    <<"1: View items list"<<endl
    <<"2: View users list"<<endl
    <<"3: View all borrow history"<<endl
    <<"4: View borrow history of a user"<<endl
    <<"5: View all current checked out items"<<endl
    <<"6: Back to main menu"<<endl
    // <<"7: "<<endl
    // <<"8: "<<endl
    ;
}

int viewsMenu(DynArr<Record>& borrowHistory,
    unordered_map<string, int>& activeBorrowMap,
    unordered_map<string, Item*>& items,
    unordered_map<int, User>& users) {

    bool continueFlag=true;
    while(continueFlag) {
        displayViewsMenu();
        int choice=readValue<int>();
        switch (choice) {
            case 1:
                Printer::printItemList(items);break;

            case 2:
                Printer::printUsersList(users);break;
            case 3:
                Printer::printRecordList(borrowHistory,items,users);break;
            case 4:
                handlePrintUserRecords(borrowHistory,items,users);break;
            case 5:
                Printer::printActiveBorrowList(borrowHistory,activeBorrowMap,items,users);break;
            case 6:
                continueFlag=false;break;

            default:
                cout<<"Not a valid option. Try again!"<<endl;

        }

    }
    cout<<endl;
    return 0;
}

int main() {
    //loading data from files
    unordered_map<string, Item*> items=loadItems(); //stores all items. Serial number is index
    unordered_map<int, User> users=loadUsers(); //stores all users. userID is index (User is simple, so store by value)
        //this loading has the consequence of reading the static variable "userIDCounter" from userdb too.

    //defining the remaining data structures
    DynArr<Record> borrowHistory=loadRecords(); //list of all borrow records
    unordered_map<string, int> activeBorrowMap =loadActiveBorrowMap(borrowHistory); //stores all records that are yet to be checked in. Here, indices of `borrowHistory` is stored.

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

    //main menu
    while(continueFlag) {
        displayMainMenu();
        int choice=readValue<int>();
        switch (choice) {
            case 1:
                handleCheckOutItem(borrowHistory,activeBorrowMap,items,users);break;
            case 2:
                handleCheckInItem(borrowHistory,activeBorrowMap,items);break;
            case 3:
                handleAddUser(users);break;
            case 4:
                handleAddItem(items);break;
            case 5:
                viewsMenu(borrowHistory,activeBorrowMap,items,users);break;
            case 6:
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
