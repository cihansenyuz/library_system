#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using namespace std;

typedef class Item
{
private:
    string author;
    long long int ISBN;
protected:
    string title;
public:
    Item(string t, string a, long long int i):title(t),author(a),ISBN(i){}
    virtual void displayInfo(void) = 0;
    string getAuthor(void);
    long long int getISBN(void) const;
}Item;

#endif