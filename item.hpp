#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

/**
 * @brief This abstract class is for items (books) in the library.
 *
 * Inhereted by Book class to demonstrate book items in the library.
 */
typedef class Item
{
private:
    string author;      /**< Author of the book */
    long long int ISBN; /**< ISBN of the book */
protected:
    string title;       /**< Title of the book */
public:
    /**
     * @brief Parameterized constructor.
     *
     * Initiliazes variables of the object
     * @param t title
     * @param a author
     * @param i ISBN
     */
    Item(string t, string a, long long int i):title(t),author(a),ISBN(i){}
    /**
     * @brief Pure virtual function to be defined in the derived class.
     *
     * Prints variables of the object
     */
    virtual void displayInfo(void) = 0;
    /**
     * @brief Getter function for author variable.
     *
     * @return Current value of the variable
     */
    string getAuthor(void);
    /**
     * @brief Getter function for ISBN variable.
     *
     * @return Current value of the variable
     */
    long long int getISBN(void) const;
}Item;

#endif