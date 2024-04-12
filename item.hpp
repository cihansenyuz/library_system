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
    string m_title;       /**< Title of the book */
private:
    string m_author;      /**< Author of the book */
    long long int m_ISBN; /**< ISBN of the book */
public:
    Item(string title, string author, long long int ISBN);
    virtual void displayInfo(void) = 0;
    string getAuthor(void);
    long long int getISBN(void);
}Item;

#endif
