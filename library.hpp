#include "book.hpp"
#include "person.hpp"
#include <set>

typedef class Library
{
private:
    set<Book>* bookList;
    set<Person>* personList;
    bool available;
public:
    Library(set<Book>* bl) : bookList(bl){
        if(bookList)
            available = true;
    }
    void addBook(Book& newBook){
        bookList->insert(newBook);
    }
    void registerPerson(Person& newPerson){
        personList->insert(newPerson);
    }
    void displayAvailables(void){
        if(!available)
            cout << "All books are taken!\n";
        else
        {
            cout << "Available books in the library:\n";
            for(auto &book : *bookList)
            {
                cout << "debug"<< endl;
                if(book.isAvailable())
                {
                    cout << book.getTitle() << endl;
                }
            }
        }

    }
    void checkOut(string personName, string bookTitle){

        bool bookAvailable = false;
        bool personAvailable = false;

        for(auto &book : *bookList)
        {
            if(book.getTitle() == bookTitle)
                break;
        }

        if(bookAvailable && personAvailable)
        {
            // check out
        }
        else if(!bookAvailable)
            cout << "This book is already taken by someone" << endl;
        else if(!personAvailable)
            cout << personName << " has already taken a book. Needs to return it to take a new one." << endl;
    }
    void returnBook(Book*, Person*){

    }
    void displayInfo(void) {

    }
    void setPersonList(set<Person>* list){
        personList = list;
    }
}Library;