#ifndef BOOK_HPP
#define BOOK_HPP

#include "item.hpp"
#include <iostream>

/**
 * @brief This class is for books derived from items in the library.
 *
 * Inherates Item class to demonstrate book items which are available in the library;
 */
typedef class Book : public Item
{
private:
    bool available;     /** Check out availability of the book */
public:
    Book(string t, string a, long long int i);
    Book(string t, string a, long long int i, bool av);
    Book(const Book& b);
    Book& operator=(const Book& other);
    void setAvailable(bool opt);
    bool isAvailable(void) const;
    void displayInfo(void) override;
    string getTitle(void);
    ~Book(){}
}Book;

#endif
