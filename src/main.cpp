#include "main.hpp"
#include <limits>

int main()
{
    Library MustafaInanKutuphanesi(BOOK_DATA_FILE, PERSON_DATA_FILE);   // creation of a library
    bool exitFlag = true;   // flag to determine quitting program

    cout << "\n## Welcome to Library System ##" << endl;
    while(exitFlag){
        Action userSelection = getUserAction();
        switch (userSelection){
            case AddBook:
                addBookAction(MustafaInanKutuphanesi);
                break;
            case RegisterPerson:
                registerPersonAction(MustafaInanKutuphanesi);
                break;
            case CheckOut:
                checkOutBookAction(MustafaInanKutuphanesi);
                break;
            case Return:
                returnBookAction(MustafaInanKutuphanesi);
                break;
            case Display:
                MustafaInanKutuphanesi.displayInfo();
                break;
            case Exit:
                exitFlag = false;
                break;
        }
    }
    
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
    cout << "\n1-Add a book to library\n2-Register a person\n3-Check out a book\n4-Return a book\n5-Display library information\n0-Save & exit" << endl;
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