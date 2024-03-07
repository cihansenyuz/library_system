#include <iostream>
#include "library.hpp"

int main()
{
    Book b1("Kurk Mantolu Madonna", "Sabahattin Ali", 9789753638029);
    Book b2("Seker Portakali", "Jose Mauro De Vasconcelos", 9789750738609);
    Book b3("1984", "George Orwell", 9789750718533);
    Book b4("Kirmizi Pazartesi", "Gabriel Garcia Marquez", 9789750721571);

    vector<Book>* newBookList = new vector<Book>;
    newBookList->push_back(b1);
    newBookList->push_back(b2);
    newBookList->push_back(b3);
    newBookList->push_back(b4);

    Person p1("Cihan Senyuz", 26007567);
    Person p2("Can Gorkem Gunes", 26100010);
    vector<Person>* newPersonList = new vector<Person>;

    newPersonList->push_back(p1);
    newPersonList->push_back(p2);

    //auto it = newPersonList->find(p2);
    //it->displayInfo();

    Library MustafaInanKutuphanesi(newBookList);
    MustafaInanKutuphanesi.setPersonList(newPersonList);

    MustafaInanKutuphanesi.checkOut("Cihan Senyuz", "1984");
    
    // to check functionality of checkOut()
    newPersonList->at(0).getTakenBook()->displayInfo();
    cout << static_cast<int> (newBookList->at(2).isAvailable()) << endl;
    cout << static_cast<int> (newBookList->at(1).isAvailable());

    delete newBookList;
    delete newPersonList;
    return EXIT_SUCCESS;
}