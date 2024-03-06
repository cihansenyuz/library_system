#include "book.hpp"
#include "person.hpp"
#include <vector>
#include <set>

typedef class Library
{
private:
    vector<Book>* bookList;
    set<Person>* personList;
    bool available;
public:
    Library(vector<Book>* bl) : bookList(bl){
        if(bookList)
            available = true;
    }
    void addBook(Book& newBook){
        bookList->push_back(newBook);
    }
    void displayAvailables(void){
        if(!available)
            cout << "All books are taken!\n";
        else
        {
            for(auto &book : *bookList)
            {
                cout << "Available books in the library:\n";
                if(book.isAvailable())
                {
                    cout << book.getTitle() << endl;
                }
            }
        }

    }
    void checkOut(Person* p, string title){
        for(auto &book : *bookList)
        {
            if(book.getTitle() == title && book.isAvailable())
            {
                cout << book.getTitle() << "is given to" << p->getName() << endl;
                book.setAvailable(false);
            }
            else if(book.getTitle() == title && !book.isAvailable())
                cout << "This book is already taken by someone" << endl;
            else
                cout << "There is no such book in the library" << endl;
        }
    }
    void returnBook(Book*, Person*);
    void displayInfo(void) {

    }
    void setPersonList(set<Person>* list){
        personList = list;
    }
}Library;