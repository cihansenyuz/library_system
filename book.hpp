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
    bool m_available;     /** Check out availability of the book */
public:
    Book(string title, string author, long long int ISBN);
    Book(string title, string author, long long int ISBN, bool available);
    Book(const Book& other);
    Book& operator=(const Book& other);
    void setAvailable(bool option);
    bool isAvailable(void) const;
    void displayInfo(void) override;
    string getTitle(void);
    ~Book(){}
}Book;

#endif
