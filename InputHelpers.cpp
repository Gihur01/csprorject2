
#include "InputHelpers.h"

    string readLine(const string& prompt ) {
        if (!prompt.empty())
            cout << prompt;
        string line;
        getline(cin, line);
        return line;
    }


    bool readYesNo(const string& prompt ) {
        while (true) {
            string line = readLine(prompt);
            if (!line.empty()) {
                char c = tolower(line[0]);
                if (c == 'y') return true;
                if (c == 'n') return false;
            }
            cout << "Please enter 'y' or 'n'." << endl;
        }
    }

    string readStr(const string& prompt ) {
        return readLine(prompt);
    }

    vector<string> readCSVFields(const string& prompt , size_t expectedCount) {
        while (true) {
            string line = readLine(prompt);
            stringstream ss(line);
            string segment;
            vector<string> fields;

            while (getline(ss, segment, ',')) {
                fields.push_back(segment);
            }

            if (expectedCount == 0 || fields.size() == expectedCount)
                return fields;

            cout << "Please enter exactly " << expectedCount << " comma-separated values." << endl;
        }
    }
