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
    void addBook(const string& bookTitle, const string& bookAuthor, const long long& bookISBN);
    void registerPerson(const Person& newPerson);
    void registerPerson(const string& personName, const int& personId);
    void displayAvailables(void);
    QString checkOut(const string personName, const string bookTitle);
    void returnBook(const string bookTitle);
    QString getSummary(void);
    void setPersonList(vector<Person>* list);
    bool checkPerson(const string name);
    bool checkBook(const string title);
    void saveLatestData(void);
    vector<Book>* getBookList(void);
    ~Library(){
        delete bookList;
        delete personList;
    }
}Library;

#endif
