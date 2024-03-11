#include <iostream>
#include "library.hpp"
#include <fstream>

#define bookDataFile "book_data.txt"
#define personDataFile "person_data.txt"

int main()
{
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

    // creation of a library
    Library MustafaInanKutuphanesi(bookDataFile, personDataFile);

    // check out a book for a user
    //MustafaInanKutuphanesi.checkOut("Cihan Senyuz", "1984");
    //MustafaInanKutuphanesi.displayInfo();

    //MustafaInanKutuphanesi.returnBook("1984");
    //MustafaInanKutuphanesi.displayInfo();
    
    // below is debug purporsed
    //newPersonList->at(0).getTakenBook()->displayInfo();
    //cout << static_cast<int> (newBookList->at(2).isAvailable()) << endl;
    //cout << static_cast<int> (newBookList->at(1).isAvailable());
    
    MustafaInanKutuphanesi.saveLatestData();
    cout << "all is well" << endl;

    //MustafaInanKutuphanesi.displayAvailables();

    return EXIT_SUCCESS;
}