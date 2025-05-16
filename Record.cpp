//
// Created by frank on 5/13/25.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

#include "Record.h"
#include "DynArr.h"


using namespace std;


void saveRecords(const DynArr<Record>& records) {
    ofstream outFile("recorddb.txt");

    for (int i=0;i<records.getLength();i++) {
        const Record& r=records[i];
        outFile << r.userID << ','
                << r.serialNum << ','
                << r.borrowDate << ','
                << r.returnDate << '\n';
    }

    outFile.close();
}

DynArr<Record> loadRecords() {
    DynArr<Record> borrowHistory;
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

        borrowHistory.push(r);
    }

    inFile.close();

    return borrowHistory;
}



