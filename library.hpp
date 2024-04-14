#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "book.hpp"
#include "person.hpp"
#include <vector>
#include <fstream>
#include <QString>

#define BOOK_NOT_AVAILABLE '0'
#define BOOK_AVAILABLE '1'
#define DATA_SEPERATOR '\t'

/**
 * @brief This class is to handle behaviours in the library.
 *
 * Add book, register person, check out or return a book etc.
 */
typedef class Library
{
private:
    unique_ptr<vector<Book>> m_bookList;         /** vector pointer for all books */
    unique_ptr<vector<Person>> m_personList;     /** vector pointer for all persons */
    bool m_available;                 /** availability of the library */

    void addBook(const Book& newBook);
    void registerPerson(const Person& newPerson);
    void readBookData(void);
    void readPersonData(void);
public:
    const string m_pathToBookData;            /** path to txt where book data kept */
    const string m_pathToPersonData;          /** path to txt where user data kept */

    Library(string pathToBookData, string pathToPersonData);
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
