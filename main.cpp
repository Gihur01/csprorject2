#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
using namespace std;

//--------------------------- ITEMS -----------------------------
class Item {
protected:
    string title;
    string author;
    string itemID; //ISBN or ISSN depending on item type
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

    string getTitle() const {return title;}
    string getAuthor() const {return author;}
    string getitemID() const {return itemID;}
    bool isAvailable() const {return !isCheckedOut;}

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

    string getFormat() const {return fileFormat;}

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

    string getName() const {return name;}
    int getID() const {return userID;}
};


//--------------------------- RECORDS -----------------------------
struct BorrowRecord {
    int userID;
    string itemID;
    string borrowDate;
    string returnDate;
};

//--------------------------- MODULES ---------------------------
void displayInstructions() {
    cout<<endl
    <<"Please write a number from the list below to use the function!"<<endl
    <<"1: Check out an item"<<endl
    <<"2: Check in an item"<<endl
    <<"3: Exit"<<endl
    ;
}

//saving & loading usewrs

void saveUsers(const std::unordered_map<int, User>& users) {
    std::ofstream outFile("userdb.txt",fstream::out);
    for (const auto& [id, user] : users) {
        outFile << id << "," << user.getName() << "\n";
    }
}

unordered_map<int,User> loadUsers() {
    unordered_map<int, User> users;
    std::ifstream inFile("userdb.txt");
    if(!inFile)
        return users;
    int id;
    string name;

    while (inFile>>id) {
        if (inFile.get() == ',')
            std::getline(inFile, name);
        users.emplace(id, User(name, id));
    }
    return users;
}

//saving & loading items

void saveItems(const std::unordered_map<std::string, Item*>& items) {
    std::ofstream outFile("itemdb.txt",fstream::out);
    for (const auto& [isbn, item] : items) {
        // Identify type using dynamic_cast
        if (auto* book = dynamic_cast<Book*>(item)) {
            outFile << "Book," << book->getitemID() << ","
            << book->getTitle()<< ","
            << book->getAuthor() << ","
            << book->isAvailable() << endl;
        }
        else if (auto* ebook = dynamic_cast<EBook*>(item)) {
            outFile << "EBook," << ebook->getitemID() << ","
            << ebook->getTitle()<< ","
            << ebook->getAuthor() << ","
            << ebook->getFormat()<< ","
            << ebook->isAvailable() << endl;
        }
    }
}


std::unordered_map<string, Item*> loadItems() {
    std::unordered_map<string, Item*> items;
    std::ifstream inFile("itemdb.txt");
    if(!inFile)
        return items;

    string line;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        string type, isbn, title, author, format, availableStr;
        bool available;

        std::getline(ss, type, ',');
        std::getline(ss, isbn, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');

        if (type == "Book") {
            std::getline(ss, availableStr);
            available = (availableStr == "1");
            auto* book = new Book(title, author, isbn);
            if (!available) book->checkOut(); //setting  available state
            items[isbn] = book;
        }
        else if (type == "EBook") {
            std::getline(ss, format, ',');
            std::getline(ss, availableStr);
            available = (availableStr == "1");
            auto* ebook = new EBook(title, author, isbn, format);
            if (!available) ebook->checkOut();
            items[isbn] = ebook;
        }
    }

    return items;
}



int handleAddItem(unordered_map<string, Item*>& items) {

}



int handleCheckOutItem(unordered_map<string, Item*>& items, unordered_map<int, User>& users) {
    int userID;
    string itemID;
    cout<<"Please write the item id: "<<endl;
    cin>>itemID;

    auto it=items.find(itemID);
    if(it!=items.end()) {
        if(!(it->second->isAvailable())) {
            cout<<"item is not available!"<<endl;
            return 3;
        }
    }
    else {
        cout<<"item id is not found in list!"<<endl;
        return 1;
    }

    cout<<"Please write the user id: "<<endl;
    cin>>userID;

    auto it1=users.find(userID);
    if(it1==users.end()) {
        cout<<"user id is not found in list!"<<endl;
        return 2;
    }

    //TODO: insert result into Record vector

    return 0;
}

int handleCheckInItem(unordered_map<string, Item*>& items) {
    string itemID;
    cout<<"Please write the item id: "<<endl;
    cin>>itemID;
    auto it=items.find(itemID);
    if(it!=items.end()) {
        if(!(it->second->isAvailable())) {
            it->second->checkIn();
            //TODO: update in record vector

        }
        else {
            cout<<"This item is already checked out!"<<endl;
            return 3;
        }
    }
    else {
        cout<<"item id is not found in list!"<<endl;
        return 1;
    }
}


//--------------------------MAIN----------------------------

int main() {
    //loading two sets from files
    unordered_map<string, Item*> items=loadItems();
    unordered_map<int, User> users=loadUsers();
    bool continueFlag=true;

    //test values
    User u1("john",1);
    User u2("Alice",2);
    Book b1("test1","oliver","1");
    Book b22("test22","eszter","2");

    while(continueFlag) {
        displayInstructions();
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:
                handleCheckOutItem(items,users);
                break;
            case 2:
                handleCheckInItem(items);
                break;
            case 3:
                continueFlag=false;
            saveItems(items);
            saveUsers(users);
                break;

            default:
                break;
        }

    }

    return 0;
}
