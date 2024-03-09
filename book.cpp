#include "book.hpp"

/**
 * @brief Setter function for available varilable.
 *
 * @param opt true: book is available, false: book is taken by someone
 */
void Book::setAvailable(bool opt){
    available = opt;
}

/**
 * @brief Getter function for available varilable.
 *
 * @return true: book is available, false: book is taken by someone
 */
bool Book::isAvailable(void) {
    return available;
}

/**
 * @brief Prints properties of the object.
 *
 * Overriden function
 */
void Book::displayInfo(void){
    std::cout << "Title: " << getTitle() << endl;
    std::cout << "Author: " << getAuthor() << std::endl;
    std::cout << "ISBN: " << getISBN() << std::endl;
}

/**
 * @brief Getter function for title variable.
 *
 * @return Current value of the variable
 */
string Book::getTitle(void) {
    return title;
}