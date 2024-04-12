#include "book.hpp"

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object, and sets availability of them true
 * @param title title of the book
 * @param author author of the book
 * @param ISBN ISBN of the book
 */
Book::Book(string title, string author, long long int ISBN) : Item(title, author, ISBN),
                                                            m_available(true){}

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object, and sets availability of them as given
 * @param t title
 * @param a author
 * @param i ISBN
 * @param av Availability
 */
Book::Book(string title, string author, long long int ISBN, bool available) : Item(title, author, ISBN),
                                                                            m_available(available){}

/**
 * @brief Copy constructor.
 *
 * Initiliazes variables of the object as the given object
 * @param b the book object to be copied
 */
Book::Book(const Book& other) : Item(other), m_available(other.isAvailable()){}

/**
 * @brief Copy assignment operator.
 *
 * Initiliazes variables of the assignee object as the assigned object
 * @param other the person object to be assigned
 */
Book& Book::operator=(const Book& other){
    if(this != &other){
        static_cast<Item&>(*this) = static_cast<const Item&>(other);
        m_available = other.isAvailable();
    }
    return *this;
}
/**
 * @brief Setter function for available varilable.
 *
 * @param opt true: book is available, false: book is taken by someone
 */
void Book::setAvailable(bool option){
    m_available = option;
}

/**
 * @brief Getter function for available varilable.
 *
 * @return true: book is available, false: book is taken by someone
 */
bool Book::isAvailable(void) const{
    return m_available;
}

/**
 * @brief Prints properties of the object.
 *
 * Overriden function
 */
void Book::displayInfo(void){
    std::cout << "Title: " << getTitle() << std::endl;
    std::cout << "Author: " << getAuthor() << std::endl;
    std::cout << "ISBN: " << getISBN() << std::endl;
}

/**
 * @brief Getter function for title variable.
 *
 * @return Current value of the variable
 */
string Book::getTitle(void) {
    return m_title;
}
