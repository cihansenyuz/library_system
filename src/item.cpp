#include "item.hpp"

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
long long int Item::getISBN(void) const{
    return ISBN;
}