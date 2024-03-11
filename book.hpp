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
    /**
     * @brief Setter function for available varilable.
     *
     * @param opt true: book is available, false: book is taken by someone
     */
    void setAvailable(bool opt);
    /**
     * @brief Getter function for available varilable.
     *
     * @return true if the book is available, false if the book is taken by someone
     */
    bool isAvailable(void);
    /**
     * @brief Prints properties of the object.
     *
     * Overriden function
     */
    void displayInfo(void) override;
    /**
     * @brief Getter function for title variable.
     *
     * @return Current value of the variable
     */
    string getTitle(void);
}Book;

#endif