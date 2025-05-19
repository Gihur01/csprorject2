//
// Created by Frank on 5/9/2025.
//

#include "Item.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//Item
Item::Item(std::string t, std::string a, std::string s,  std::string d)
: title(t), author(a), SerialNum(s),publishDate(d), isCheckedOut(false) {
}

void Item::checkOut() {
    if (!isCheckedOut) {
        isCheckedOut = true;
        std::cout << title << " checked out.\n";
    } else {
        std::cout << title << " is already checked out.\n";
    }
}

void Item::checkIn() {
    isCheckedOut = false;
    std::cout << title << " checked in.\n";
}



//Books:
Book::Book(std::string t, std::string a, std::string s,  std::string d)
    : Item(t, a, s,d) {
}

void Book::display() const  {
    std::cout << "Book: " << title << " by " << author << " (ISBN: " << SerialNum << ")\n";
}




//EBooks
EBook::EBook(std::string t, std::string a, std::string s,  std::string d, std::string format)
: Item(t, a, s,d), fileFormat(format) {
}

void EBook::display() const  {
    std::cout << "EBook: " << title << " by " << author << " (ISBN: "<<SerialNum<<" Format: " << fileFormat << ")\n";
}

Magazine::Magazine(std::string t, std::string a, std::string s,  std::string d)
: Item(t, a, s,d) {
}


void Magazine::display() const  {
    std::cout << "Magazine: " << title << " by " << author<< " (ISSN: "<<SerialNum<< ")\n";
}



//Serialization

void saveItems(const std::unordered_map<std::string, Item*>& items) {
    std::ofstream outFile("itemdb.txt", std::fstream::out);
    for (const auto& [isbn, item] : items) {

        if (item->getType()=="Book") {
            outFile << "Book," << item->getSerialNum() << ","
            << item->getTitle()<< ","
            << item->getAuthor() << ","
            << item->getPublishDate() << ","
            << item->isAvailable() << std::endl;
        }
        else if (item->getType()=="EBook") {
            outFile << "EBook," << item->getSerialNum() << ","
            << item->getTitle()<< ","
            << item->getAuthor() << ","
            << item->getPublishDate() << ","
            << item->getFormat()<< ","
            << item->isAvailable() << std::endl;
        }
        else if (item->getType()=="Magazine") {
            outFile << "Magazine," << item->getSerialNum() << ","
            << item->getTitle()<< ","
            << item->getAuthor() << ","
            << item->getPublishDate() << ","
            << item->isAvailable() << std::endl;
        }
    }
    outFile.close();
}


std::unordered_map<std::string, Item*> loadItems() {
    std::unordered_map<std::string, Item*> items;
    std::ifstream inFile("itemdb.txt");
    if(!inFile)
        return items;

    std::string line;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string type, serial, title, author, publishDate, format, availableStr;
        bool available;

        std::getline(ss, type, ',');
        std::getline(ss, serial, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, publishDate, ',');

        if (type == "Book") {
            std::getline(ss, availableStr);
            available = (availableStr == "1");
            auto* book = new Book(title, author, serial, publishDate);
            if (!available) book->checkOut(); //setting  available state
            items[serial] = book;
        }
        else if (type == "EBook") {
            std::getline(ss, format, ',');
            std::getline(ss, availableStr);
            available = (availableStr == "1");
            auto* ebook = new EBook(title, author, serial, publishDate, format);
            if (!available) ebook->checkOut();
            items[serial] = ebook;
        }
        else if (type == "Magazine") {
            std::getline(ss, availableStr);
            available = (availableStr == "1");
            auto* magazine = new Magazine(title, author, serial, publishDate);
            if (!available) magazine->checkOut(); //setting  available state
            items[serial] = magazine;
        }
    }

    inFile.close();
    return items;
}
