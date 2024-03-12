#include <iostream>
#include "library.hpp"
#include <fstream>
#include <limits>
#define bookDataFile "book_data.txt"
#define personDataFile "person_data.txt"

int main()
{
    // creation of a library
    Library MustafaInanKutuphanesi(bookDataFile, personDataFile);

    /*
    1- add book to lib
    2- register person
    3- check out a book
    4- return a book
    5- display info
        1- book
        2- person
        3- library
    0- exit
    */
    bool exitFlag = true;

    while(exitFlag){
        short selection = 0;
        cout << "## Welcome to Library System ##\n1-Add a book to library\n2-Register a person\n3-Check out a book\n4-Return a book\n\n0-Save & exit" << endl;
        cout << "Select an Action: ";
        cin >> selection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (selection){
            case 1:
            {
                cout << "Enter book title: ";
                string title;
                getline(cin, title);
                cout << "Enter book author: ";
                string author;
                getline(cin, author);
                cout << "Enter book ISBN: ";
                long long int ISBN;
                cin >> ISBN;
                MustafaInanKutuphanesi.addBook(title, author, ISBN);
                break;
            }
            case 2:
            {
                cout << "Enter user name: ";
                string name;
                getline(cin, name);
                cout << "Enter user ID: ";
                int id;
                cin >> id;
                MustafaInanKutuphanesi.registerPerson(name, id);
                break;
            }
            case 3:
            {
                cout << "Enter book title: ";
                string title;
                getline(cin, title);
                cout << "Enter person name: ";
                string name;
                getline(cin, name);
                MustafaInanKutuphanesi.checkOut(name, title);
                break;
            }
            case 4:
            {
                cout << "Enter book title: ";
                string title;
                getline(cin, title);
                MustafaInanKutuphanesi.returnBook(title);
                break;
            }
            case 0:
                exitFlag = false;
                break;
        }
    }
    
    MustafaInanKutuphanesi.saveLatestData();
    cout << "all is well" << endl;

    //MustafaInanKutuphanesi.displayAvailables();

    return EXIT_SUCCESS;
}