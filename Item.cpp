//
// Created by Frank on 5/9/2025.
//

#include "Item.h"

#include <iostream>
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
    std::cout << "EBook: " << title << " by " << author << " (Format: " << fileFormat << ")\n";
}

Magazine::Magazine(std::string t, std::string a, std::string s,  std::string d)
: Item(t, a, s,d) {
}

void Magazine::display() const  {
    std::cout << "Magazine: " << title << " by " << author << "\n";
}

