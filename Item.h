//
// Created by Frank on 5/9/2025.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>


class Item {
protected:
    std::string title;
    std::string author;
    std::string publishDate;
    std::string SerialNum; //ISBN or ISSN depending on item type
    bool isCheckedOut;

public:
    Item(std::string t, std::string a, std::string s,  std::string d);
    virtual void display() const = 0;

    virtual void checkOut();
    virtual void checkIn();

    std::string getTitle() const {return title;}
    std::string getAuthor() const {return author;}
    std::string getSerialNum() const {return SerialNum;}
    bool isAvailable() const {return !isCheckedOut;}
    virtual std::string getType() =0; //gets the type of the current object

    // virtual ~Item();
};

class Book : public Item {
public:
    Book(std::string t, std::string a, std::string s, std::string d);
    void display() const override;
    std::string getType() override {return "Book";}

};

class EBook : public Item {
    std::string fileFormat;
public:
    EBook(std::string t, std::string a, std::string s,  std::string d, std::string format="pdf");
    std::string getFormat() const {return fileFormat;}
    void display() const override;
    std::string getType() override {return "EBook";}
};

class Magazine : public Item {
public:
    Magazine(std::string t, std::string a, std::string s,  std::string d);
    void display() const override;
    std::string getType() override {return "Magazine";}
};

#endif //ITEM_H
