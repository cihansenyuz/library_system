#include "library.hpp"

void Library::addBook(const Book& newBook){
    bookList->push_back(newBook);
}

void Library::registerPerson(const Person& newPerson){
    personList->push_back(newPerson);
}

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

void Library::setPersonList(vector<Person>* list){
    personList = list;
}

bool Library::checkPerson(const string name){
    for(auto &person : *personList)
        if(person.getName() == name)
            return true;
    return false;
}

bool Library::checkBook(const string title){
    for(auto &book : *bookList)
        if(book.getTitle() == title)
            return true;
    return false;
}