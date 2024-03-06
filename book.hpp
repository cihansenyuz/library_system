#include "item.hpp"

typedef class Book : public Item
{
private:
    bool available;
public:
    Book(string t, string a, long long int i):Item(t, a, i){
        setAvailable(true);
    }
    void setAvailable(bool opt){
        available = opt;
    }
    bool isAvailable(void){
        return available;
    }
    void displayInfo(void) override{
        cout << "Title: " << getTitle() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "ISBN: " << getISBN() << endl;
    }
}Book;