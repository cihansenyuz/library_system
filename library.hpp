#ifndef LIBRARY_HPP
#define LIBRARY_HPP

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
    void addBook(const Book& newBook);
    void registerPerson(const Person& newPerson);
    void displayAvailables(void);
    void checkOut(const string personName, const string bookTitle);
    void returnBook(const string bookTitle);
    void displayInfo(void);
    void setPersonList(vector<Person>* list);
    bool checkPerson(const string name);
    bool checkBook(const string title);
}Library;

#endif