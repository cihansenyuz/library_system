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
protected:
    string title;       /**< Title of the book */
private:
    string author;      /**< Author of the book */
    long long int ISBN; /**< ISBN of the book */
public:
    Item(string t, string a, long long int i);
    virtual void displayInfo(void) = 0;
    string getAuthor(void);
    long long int getISBN(void);
}Item;

#endif
