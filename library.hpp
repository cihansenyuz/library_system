#include "book.hpp"
#include "person.hpp"
#include <vector>

typedef class Library
{
private:
    vector<Book>* bookList;
    vector<Person>* personList;
    bool available;
public:
    Library(vector<Book>* bl) : bookList(bl){
        if(bookList)
            available = true;
    }
    void addBook(Book& newBook){
        bookList->push_back(newBook);
    }
    void registerPerson(Person& newPerson){
        personList->push_back(newPerson);
    }
    void displayAvailables(void){
        if(!available)
            cout << "All books are taken!\n";
        else
        {
            cout << "Available books in the library:\n";
            for(auto &book : *bookList)
                if(book.isAvailable())
                    cout << "- " << book.getTitle() << endl;
        }
    }
    void checkOut(string personName, string bookTitle){
        bool bookAvailable = false;
        bool personAvailable = false;
        for(auto &book : *bookList)
            if(book.getTitle() == bookTitle)
                bookAvailable = book.isAvailable();
        for(auto &person : *personList)
            if(person.getName() == personName && person.getTakenBook() == nullptr)
                personAvailable = true;

        // check if given argumants are valid
        bool bookExists = checkBook(bookTitle);
        bool personExists = checkPerson(personName);
        if(!bookExists || !personExists)
        {
            cout << "No such book or registered person" << endl;
            return;
        }

        // check availability of person and book
        if(bookAvailable && personAvailable)
        {   
            for(auto &book : *bookList) // find the book in the list
                if(book.getTitle() == bookTitle)
                {   
                    book.setAvailable(false); // set not available
                    for(auto &person : *personList) // find the person in the list
                        if(person.getName() == personName)
                        {   
                            person.setTakenBook(book); // give the book to the person setting takenBook
                            cout << "Book '" << bookTitle << "' is given to " << personName << endl;
                        }
                }
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
    void setPersonList(vector<Person>* list){
        personList = list;
    }
    bool checkPerson(string name){
        for(auto &person : *personList)
            if(person.getName() == name)
                return true;
        return false;
    }
    bool checkBook(string title){
        for(auto &book : *bookList)
            if(book.getTitle() == title)
                return true;
        return false;
    }
}Library;
