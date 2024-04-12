#include "book.hpp"

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object, and sets availability of them true
 * @param t title
 * @param a author
 * @param i ISBN
 */
Book::Book(string t, string a, long long int i):Item(t, a, i), available(true){}

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object, and sets availability of them as given
 * @param t title
 * @param a author
 * @param i ISBN
 * @param av Availability
 */
Book::Book(string t, string a, long long int i, bool av):Item(t, a, i), available(av){}

/**
 * @brief Copy constructor.
 *
 * Initiliazes variables of the object as the given object
 * @param b the book object to be copied
 */
Book::Book(const Book& b) : Item(b), available(b.isAvailable()){}

/**
 * @brief Copy assignment operator.
 *
 * Initiliazes variables of the assignee object as the assigned object
 * @param other the person object to be assigned
 */
Book& Book::operator=(const Book& other){
    if(this != &other){
        static_cast<Item&>(*this) = static_cast<const Item&>(other);
        available = other.isAvailable();
    }
    return *this;
}
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
bool Book::isAvailable(void) const{
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
