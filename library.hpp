#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "book.hpp"
#include "person.hpp"
#include <vector>
#include <fstream>
#include <QString>
#include <sstream>
#include "sqlite3.h"

#define BOOK_NOT_AVAILABLE false
#define BOOK_AVAILABLE true
#define DATE_SEPERATOR '/'

#define DATABASE_BOOK_ISBN 0
#define DATABASE_BOOK_TITLE 1
#define DATABASE_BOOK_AUTHOR 2
#define DATABASE_BOOK_AVAILABLE 3

#define DATABASE_PERSON_ID 0
#define DATABASE_PERSON_NAME 1
#define DATABASE_PERSON_TAKENBOOK 2
#define DATABASE_PERSON_TAKENDATE 3

/**
 * @brief This class is to handle behaviours in the library.
 *
 * Add book, register person, check out or return a book etc.
 */
typedef class Library
{
private:
    unique_ptr<vector<Book>> m_bookList;        /** vector pointer for all books */
    unique_ptr<vector<Person>> m_personList;    /** vector pointer for all persons */
    bool m_available;                           /** availability of the library */

    void addBook(const Book& newBook);
    void registerPerson(const Person& newPerson);
    void readBookData(void);
    void readPersonData(void);
public:
    const char* m_databasePath;                 /** Path to the database */
    sqlite3* database;                          /** Pointer to the database */

    Library(const char* databasePath);
    QString addBook(const string& bookTitle, const string& bookAuthor, const long long int& bookISBN);
    QString registerPerson(const string& personName, const int& personId);
    void remove(Book* book);
    void remove(Person* person);
    QString checkOut(Person* person, Book* book);
    QString returnBook(Book* book);
    QString getSummary(void);
    Person* checkPerson(const int& personID);
    Book* checkBook(const long long int& bookISBN);
    vector<Book>* getBookList(void);
    vector<Person>* getPersonList(void);
    void saveLatestData(void);
    ~Library(){
        //delete bookList;
        //delete personList;
    }
}Library;

#endif
