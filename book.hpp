#ifndef BOOK_HPP
#define BOOK_HPP

#include "item.hpp"
#include <iostream>

typedef class Book : public Item
{
private:
    bool available;
public:
    Book(string t, string a, long long int i):Item(t, a, i){
        available = true;
    }
    bool operator<(const Book& other) const;
    void setAvailable(bool opt);
    bool isAvailable(void);
    void displayInfo(void) override;
    string getTitle(void);
}Book;

#endif