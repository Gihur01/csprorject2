//
// Created by frank on 5/13/25.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

#include "Record.h"
#include "Item.h"
#include "User.h"


using namespace std;


void saveRecords(const vector<Record>& records) {
    ofstream outFile("recorddb.txt");

    for (const Record& r : records) {
        outFile << r.userID << ','
                << r.serialNum << ','
                << r.borrowDate << ','
                << r.returnDate << '\n';
    }

    outFile.close();
}

vector<Record> loadRecords() {
    vector<Record> borrowHistory;
    ifstream inFile("recorddb.txt");
    if (!inFile) {
        return borrowHistory;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream ss(line);
        Record r;
        string token;

        getline(ss, token, ',');
        r.userID = stoi(token);

        getline(ss, r.serialNum, ',');
        getline(ss, r.borrowDate, ',');
        getline(ss, r.returnDate);

        borrowHistory.push_back(r);
    }

    inFile.close();

    return borrowHistory;
}



