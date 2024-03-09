#include "library.hpp"

/**
 * @brief Adds a Book to the bookList.
 *
 * Takes an Book object as argumant, and pushes it to the vector pointed by bookList
 * @param newBook Book object to be added
 */
void Library::addBook(const Book& newBook){
    bookList->push_back(newBook);
}

/**
 * @brief Adds a Person to the personList.
 *
 * Takes an Person object as argumant, and pushes it to the vector pointed by personList
 * @param newPerson Person object to be added
 */
void Library::registerPerson(const Person& newPerson){
    personList->push_back(newPerson);
}

/**
 * @brief Prints all available books
 *
 * Prints titles of books that are not taken by anyone
 */
void Library::displayAvailables(void){
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

/**
 * @brief Check out a book from library
 *
 * Takes person name and book title, sets the book not available, sets persons takenBook pointer
 * @param personName name of the person
 * @param bookTitle title of the book
 */
void Library::checkOut(const string personName, const string bookTitle){
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

/**
 * @brief Returns a book to library
 *
 * Takes book title, sets the book available, sets persons takenBook pointer to nullptr
 * @param bookTitle title of the book
 */
void Library::returnBook(const string bookTitle){
    for(auto &book : *bookList)
        if(book.getTitle() == bookTitle)
            book.setAvailable(true);

    for(auto &person : *personList)
    {
        
        if(person.getTakenBook()->getTitle() == bookTitle)
        {

            person.resetTakenBook();                
            return;
        }

    }

    
}

/**
 * @brief Prints properties of the library.
 *
 * Prints book information in the library and how many available/not available.
 * Also, prints registered persons and which book is taken by whom.
 */
void Library::displayInfo(void) {
    // counters to keep status of books
    short availableCount = 0;
    short nonAvailableCount = 0;

    // printing starts here
    cout << "Library Information: " << endl;
    cout << " - " << bookList->size() << " books in the library" << endl;
    for(auto &book : *bookList) // print all books in the library
    {
        cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << endl;
        if(book.isAvailable())
            availableCount++;
        else
            nonAvailableCount++;
    }
    cout << "Available: " << availableCount << " Checked Out: " << nonAvailableCount << endl;
    cout << "- " << personList->size() << " users registered in the library" << endl;
    for(auto &person : *personList) // print all users in the library
    {
        cout << "Name: " << person.getName() << " Book: ";
        if(person.getTakenBook())
            cout << person.getTakenBook()->getTitle() << endl;
        else
            cout << "-" << endl;
    }
}

/**
 * @brief Setter function for personList pointer.
 *
 * @param list pointer of a vector of Persons
 */
void Library::setPersonList(vector<Person>* list){
    personList = list;
}

/**
 * @brief Checks if a person is registered in the library
 *
 * Takes name of the person, and searches for it in the vector pointed by personList
 * @param name name of the person
 * @return true: name exists, false: does not
 */
bool Library::checkPerson(const string name){
    for(auto &person : *personList)
        if(person.getName() == name)
            return true;
    return false;
}

/**
 * @brief Checks if a book is registered in the library
 *
 * Takes title of the book, and searches for it in the vector pointed by bookList
 * @param title title of the book
 * @return true: title exists, false: does not
 */
bool Library::checkBook(const string title){
    for(auto &book : *bookList)
        if(book.getTitle() == title)
            return true;
    return false;
}