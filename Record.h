//
// Created by frank on 5/13/25.
//

#ifndef RECORD_H
#define RECORD_H
#include <string>
#include <vector>

using namespace std;


struct Record {
    int userID;
    string serialNum;
    string  borrowDate;
    string  returnDate;
};



void saveRecords(const vector<Record>& records);

vector<Record> loadRecords();

#endif //RECORD_H
