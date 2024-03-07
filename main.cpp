#include <iostream>
#include "library.hpp"

int main()
{
    Book b1("Kurk Mantolu Madonna", "Sabahattin Ali", 9789753638029);
    Book b2("Seker Portakali", "Jose Mauro De Vasconcelos", 9789750738609);
    Book b3("1984", "George Orwell", 9789750718533);
    Book b4("Kirmizi Pazartesi", "Gabriel Garcia Marquez", 9789750721571);

    set<Book>* newBookList = new set<Book>;
    newBookList->insert(b1);
    newBookList->insert(b2);
    newBookList->insert(b3);
    newBookList->insert(b4);

    Person p1("Cihan Senyuz", 26007567);
    Person p2("Can Gorkem Gunes", 26100010);
    set<Person>* newPersonList = new set<Person>;

    newPersonList->insert(p1);
    newPersonList->insert(p2);

    //auto it = newPersonList->find(p2);
    //it->displayInfo();

    Library MustafaInanKutuphanesi(newBookList);
    MustafaInanKutuphanesi.setPersonList(newPersonList);

    MustafaInanKutuphanesi.displayAvailables();

    return EXIT_SUCCESS;
}