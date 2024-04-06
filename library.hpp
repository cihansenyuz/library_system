#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "book.hpp"
#include "person.hpp"
#include <vector>
#include <fstream>
#include <QString>

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
    string fileNameBook;
    string fileNamePerson;
public:
    /**
     * @brief Parameterized constructor.
     *
     * Initiliazes bookList, and sets availability of the library true
     * @param bl pointer of a vector of Books
     */
    Library(vector<Book>* bl) : bookList(bl){
        if(bookList)
            available = true;
    }
    Library(string bdf, string pdf);
    void addBook(const Book& newBook);
    void addBook(const string& bookTitle, const string& bookAuthor, const long long int& bookISBN);
    void registerPerson(const Person& newPerson);
    void registerPerson(const string& personName, const int& personId);
    void displayAvailables(void);
    QString checkOut(Person* person, Book* book);
    QString returnBook(Book* book);
    QString getSummary(void);
    void setPersonList(vector<Person>* list);
    Person* checkPerson(const int& personID);
    Book* checkBook(const long long int& bookISBN);
    void saveLatestData(void);
    vector<Book>* getBookList(void);
    vector<Person>* getPersonList(void);
    ~Library(){
        delete bookList;
        delete personList;
    }
}Library;

#endif
