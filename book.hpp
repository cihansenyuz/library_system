#include "item.hpp"

typedef class Book : public Item
{
private:
    bool available;
public:
    Book(string t, string a, long long int i):Item(t, a, i){
        available = true;
    }
    bool operator<(const Book& other) const{
        if(this->getISBN() < other.getISBN())
            return true;
        else
            return false;
    }
    void setAvailable(bool opt){
        available = opt;
    }
    bool isAvailable(void) {
        return available;
    }
    void displayInfo(void) override{
        cout << "Title: " << getTitle() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "ISBN: " << getISBN() << endl;
    }
    string getTitle(void) {
        return title;
    }
}Book;
