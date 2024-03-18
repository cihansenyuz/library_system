#include "main.hpp"
#include <limits>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    cout << "debug" << BOOK_DATA_FILE;
    Library MustafaInanKutuphanesi(BOOK_DATA_FILE, PERSON_DATA_FILE);   // creation of a library

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    
    MustafaInanKutuphanesi.saveLatestData();
    cout << "all is well" << endl;

    //MustafaInanKutuphanesi.displayAvailables();

    return EXIT_SUCCESS;
}

/**
 * @brief Gets action type from the user.
 *
 * Prints relevant messages, and inputs selected action.
 * @return Action enum of selection
 */
Action getUserAction(void){
    short selection;
    cout << "\n1-Add a book to library | 2-Register a person | 3-Check out a book | 4-Return a book | 5-Display library information | 0-Save & exit" << endl;
    cout << "Select an Action: ";
    cin >> selection;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return static_cast<Action> (selection);
}

/**
 * @brief Takes action for user selection: add a book.
 *
 * Prints relevant messages, and inputs user data. Calls addBook method of the Library object
 * @param lib Library object to be configurated
 */
void addBookAction(Library& lib){
    cout << "Enter book title: ";
    string title;
    getline(cin, title);
    cout << "Enter book author: ";
    string author;
    getline(cin, author);
    cout << "Enter book ISBN: ";
    long long int ISBN;
    cin >> ISBN;
    lib.addBook(title, author, ISBN);
}

/**
 * @brief Takes action for user selection: register a person.
 *
 * Prints relevant messages, and inputs user data. Calls registerPerson method of the Library object
 * @param lib Library object to be configurated
 */
void registerPersonAction(Library& lib){
    cout << "Enter user name: ";
    string name;
    getline(cin, name);
    cout << "Enter user ID: ";
    int id;
    cin >> id;
    lib.registerPerson(name, id);
}

/**
 * @brief Takes action for user selection: check out a book.
 *
 * Prints relevant messages, and inputs user data. Calls checkOut method of the Library object
 * @param lib Library object to be configurated
 */
void checkOutBookAction(Library& lib){
    cout << "Enter book title: ";
    string title;
    getline(cin, title);
    cout << "Enter person name: ";
    string name;
    getline(cin, name);
    lib.checkOut(name, title);
}

/**
 * @brief Takes action for user selection: return a book.
 *
 * Prints relevant messages, and inputs user data. Calls returnBook method of the Library object
 * @param lib Library object to be configurated
 */
void returnBookAction(Library& lib){
    cout << "Enter book title: ";
    string title;
    getline(cin, title);
    lib.returnBook(title);
}