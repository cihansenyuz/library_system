#include "item.hpp"

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object
 * @param t title
 * @param a author
 * @param i ISBN
 */
Item::Item(string t, string a, long long int i):title(t),author(a),ISBN(i){}

/**
 * @brief Getter function for author variable.
 *
 * @return Current value of the variable
 */
string Item::getAuthor(void){
    return author;
}

/**
 * @brief Getter function for ISBN variable.
 *
 * @return Current value of the variable
 */
long long int Item::getISBN(void){
    return ISBN;
}
