#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Item {
protected:
    string title;
    string author;
    string itemID; //ISBN or ISSN depending on book or magazine
    bool isCheckedOut;

public:
    Item(string t, string a, string i) : title(t), author(a), itemID(i), isCheckedOut(false) {}

    virtual void display() const = 0;
    
    virtual void checkOut() {
        if (!isCheckedOut) {
            isCheckedOut = true;
            cout << title << " checked out.\n";
        }
        else {
            cout << title << " is already checked out.\n";
        }
    }

    virtual void checkIn() {
        isCheckedOut = false;
        cout << title << " checked in.\n";
    }

    virtual ~Item() {} // Virtual destructor for proper cleanup
};


class Book : public Item {
public:
    Book(string t, string a, string i)
        : Item(t, a, i) {}

    void display() const override {
        cout << "Book: " << title << " by " << author << " (ISBN: " << itemID << ")\n";
    }
};

class EBook : public Item {
    string fileFormat;
public:
    EBook(string t, string a, string i, string format) : Item(t, a, i), fileFormat(format) {}

    void display() const override {
        cout << "EBook: " << title << " by " << author << " (Format: " << fileFormat << ")\n";
    }
};

class Magazine : public Item {
    Magazine(string t, string a, string i) : Item(t, a, i) {}

    void display() const override {
        cout << "Magazine: " << title << " by " << author << "\n";
    }
};

//--------------------------- ROLES -----------------------------



class User {
    string name;
    int userID;
public:
    User(string n, int id) : name(n), userID(id) {}

    void display() const {
        cout << "User: " << name << " (ID: " << userID << ")\n";
    }
};


//--------------------------- RECORDS -----------------------------
struct BorrowRecord {
    int userID;
    string itemID;
    string borrowDate;
    string returnDate;
};


int main() {


    return 0;
}
