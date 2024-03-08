#include <iostream>
#include "library.hpp"

int main()
{
    // creation of books
    Book b1("Kurk Mantolu Madonna", "Sabahattin Ali", 9789753638029);
    Book b2("Seker Portakali", "Jose Mauro De Vasconcelos", 9789750738609);
    Book b3("1984", "George Orwell", 9789750718533);
    Book b4("Kirmizi Pazartesi", "Gabriel Garcia Marquez", 9789750721571);

    // push them into a vector to give it to library
    vector<Book>* newBookList = new vector<Book>;
    newBookList->push_back(b1);
    newBookList->push_back(b2);
    newBookList->push_back(b3);
    newBookList->push_back(b4);

    // creation of book users
    Person p1("Cihan Senyuz", 26007567);
    Person p2("Can Gorkem Gunes", 26100010);

    // push them into a vector to give it to library
    vector<Person>* newPersonList = new vector<Person>;
    newPersonList->push_back(p1);
    newPersonList->push_back(p2);

    // below is debug purposed
    //auto it = newPersonList->find(p2);
    //it->displayInfo();

    // creation of a library
    Library MustafaInanKutuphanesi(newBookList);
    MustafaInanKutuphanesi.setPersonList(newPersonList);

    // check out a book for a user
    MustafaInanKutuphanesi.checkOut("Cihan Senyuz", "1984");
    MustafaInanKutuphanesi.displayInfo();

    MustafaInanKutuphanesi.returnBook("1984");
    MustafaInanKutuphanesi.displayInfo();
    
    // below is debug purporsed
    //newPersonList->at(0).getTakenBook()->displayInfo();
    //cout << static_cast<int> (newBookList->at(2).isAvailable()) << endl;
    //cout << static_cast<int> (newBookList->at(1).isAvailable());
    

    cout << "all is well" << endl;

    // dont forget to deallocate !
    delete newBookList;
    delete newPersonList;
    return EXIT_SUCCESS;
}