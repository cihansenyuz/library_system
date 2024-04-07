#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "book.hpp"
#include "person.hpp"
#include <vector>
#include <fstream>
#include <QString>

#define BOOK_NOT_AVAILABLE '0'
#define BOOK_AVAILABLE '1'

/**
 * @brief This class is to handle behaviours in the library.
 *
 * Add book, register person, check out or return a book etc.
 */
typedef class Library
{
private:
    vector<Book>* bookList;         /** vector pointer for all books */
    vector<Person>* personList;     /** vector pointer for all persons */
    bool available;                 /** availability of the library */
    string fileNameBook;            /** path to txt where book data kept */
    string fileNamePerson;          /** path to txt where user data kept */

    void addBook(const Book& newBook);
    void registerPerson(const Person& newPerson);
public:
    Library(string bdf, string pdf);
    QString addBook(const string& bookTitle, const string& bookAuthor, const long long int& bookISBN);
    QString registerPerson(const string& personName, const int& personId);
    void remove(Book* book);
    void remove(Person* person);
    QString checkOut(Person* person, Book* book);
    QString returnBook(Book* book);
    QString getSummary(void);
    void setPersonList(vector<Person>* list);
    Person* checkPerson(const int& personID);
    Book* checkBook(const long long int& bookISBN);
    vector<Book>* getBookList(void);
    vector<Person>* getPersonList(void);
    void saveLatestData(void);
    ~Library(){
        delete bookList;
        delete personList;
    }
}Library;

#endif
