#include "item.hpp"

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object
 * @param t title
 * @param a author
 * @param i ISBN
 */
Item::Item(string title, string author, long long int ISBN) : m_title(title),
                                                              m_author(author),
                                                              m_ISBN(ISBN){}

/**
 * @brief Getter function for author variable.
 *
 * @return Current value of the variable
 */
string Item::getAuthor(void){
    return m_author;
}

/**
 * @brief Getter function for ISBN variable.
 *
 * @return Current value of the variable
 */
long long int Item::getISBN(void){
    return m_ISBN;
}
