#ifndef INPUTHELPERS_H
#define INPUTHELPERS_H


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

//The problem with cin is that the \n remains, and messes up the buffer. These helper functions fix this with `getline()`.

    //Read a full line from cin with an optional prompt
    string readLine(const string& prompt = "");

    // Template function to read multiple tyopes
    template <typename T>
    T readValue(const string& prompt = "") {
        while (true) {
            string line = readLine(prompt);
            stringstream ss(line);
            T value;
            if (ss >> value && ss.eof()) {
                return value;
            }
            cout << "Invalid input. Please try again." << endl;
        }
    }

    // Separate function to read a raw string
    string readStr(const string& prompt = "");

    // Reads a yes/no response, returns true for 'y' or 'Y'
    bool readYesNo(const string& prompt = "Continue? (y/n): ");

    // Reads a line and splits it into comma-separated fields
    vector<string> readCSVFields(const string& prompt = "", size_t expectedCount = 0);





#endif //INPUTHELPERS_H
