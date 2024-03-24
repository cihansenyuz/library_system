#include "mainwindow.hpp"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    /*
     * Below this section must have a funtion that reads from local Books and Persons
     * Codes from terminal version does not work, needs reimplamentation
     * */
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

    // creation of a library
    Library lib(newBookList);
    lib.setPersonList(newPersonList);
    ////////////////////

    QApplication a(argc, argv);
    MainWindow w(nullptr, &lib);
    w.show();
    return a.exec();
}
