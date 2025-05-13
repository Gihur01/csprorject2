//
// Created by frank on 5/13/25.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include "Record.h"

#include <limits>
using namespace std;

void printRecordList(const vector<Record>& records) {
    // Column widths
    const int widthID = 10;
    const int widthSerial = 15;
    const int widthDate = 15;

    // Header
    cout << left
         << setw(widthID) << "User ID"
         << setw(widthSerial) << "Serial Num"
         << setw(widthDate) << "Borrow Date"
         << setw(widthDate) << "Return Date"
         << endl;

    cout << string(widthID + widthSerial + 2 * widthDate, '-') << endl;

    // Rows
    for (const auto& record : records) {
        cout << left
             << setw(widthID) << record.userID
             << setw(widthSerial) << record.serialNum
             << setw(widthDate) << record.borrowDate
             << setw(widthDate) << record.returnDate
             << endl;
    }
    cout<<"\n\n\n"; //This just separates the table from the menu options a bit
}
