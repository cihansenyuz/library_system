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
    /**
     * @brief Parameterized constructor.
     *
     * Initiliazes variables of the object, and sets availability of them true
     * @param t title
     * @param a author
     * @param i ISBN
     */
    Book(string t, string a, long long int i):Item(t, a, i){
        available = true;
    }
    Book(string t, string a, long long int i, bool av):Item(t, a, i){
        available = av;
    }
    void setAvailable(bool opt);
    bool isAvailable(void);
    void displayInfo(void) override;
    string getTitle(void);
}Book;

#endif