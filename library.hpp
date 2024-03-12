#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "book.hpp"
#include "person.hpp"
#include <vector>
#include <fstream>

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
    /**
     * @brief Constructor from previously saved data.
     *
     * Creates input file from saved data, gets book informations, and sets bookList pointer
     * @param bdf book data file name to be read
     */
    Library(string bdf, string pdf);
    /**
     * @brief Adds a Book to the bookList.
     *
     * Takes an Book object as argumant, and pushes it to the vector pointed by bookList
     * @param newBook Book object to be added
     */
    void addBook(const Book& newBook);
    void addBook(const string& bookTitle, const string& bookAuthor, const long long& bookISBN);
    /**
     * @brief Adds a Person to the personList.
     *
     * Takes an Person object as argumant, and pushes it to the vector pointed by personList
     * @param newPerson Person object to be added
     */
    void registerPerson(const Person& newPerson);
    void registerPerson(const string& personName, const int& personId);
    /**
     * @brief Prints all available books
     *
     * Prints books that are not taken by anyone
     */
    void displayAvailables(void);
    /**
     * @brief Check out a book from library
     *
     * Takes person name and book title, sets the book not available, sets persons takenBook pointer
     * @param personName name of the person
     * @param bookTitle title of the book
     */
    void checkOut(const string personName, const string bookTitle);
    /**
     * @brief Returns a book to library
     *
     * Takes book title, sets the book available, sets persons takenBook pointer to nullptr
     * @param bookTitle title of the book
     */
    void returnBook(const string bookTitle);
    /**
     * @brief Prints properties of the library.
     *
     * Prints book information in the library and how many available/not available.
     * Also, prints registered persons and which book is taken by whom.
     */
    void displayInfo(void);
    /**
     * @brief Setter function for personList pointer.
     *
     * @param list pointer of a vector of Persons
     */
    void setPersonList(vector<Person>* list);
    /**
     * @brief Checks if a person is registered in the library
     *
     * Takes name of the person, and searches for it in the vector pointed by personList
     * @param name name of the person
     * @return true: name exists, false: does not
     */
    bool checkPerson(const string name);
    /**
     * @brief Checks if a book is registered in the library
     *
     * Takes title of the book, and searches for it in the vector pointed by bookList
     * @param title title of the book
     * @return true: title exists, false: does not
     */
    bool checkBook(const string title);
    /**
     * @brief Saves latest status of library
     *
     * Creates output file, and saves all related information inside.
     */
    void saveLatestData(void);
    ~Library(){
        delete bookList;
        delete personList;
    }
}Library;

#endif