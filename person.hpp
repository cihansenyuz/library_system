#ifndef PERSON_HPP
#define PERSON_HPP

#include "book.hpp"
#include <iostream>

typedef class Person
{
private:
    string name;        /** Name of the person */
    int id;             /** ID of the person */
    Book* takenBook;    /** Pointed book taken by the person */
public:
    /**
     * @brief Parameterized constructor.
     *
     * Initiliazes variables of the object, and sets takenBook to nullptr
     * @param n name
     * @param i ID
     */
    Person(string n, int i) : name(n), id(i), takenBook(nullptr){}
    void displayInfo(void);
    string getName(void);
    int getId(void);
    void setTakenBook(Book& b);
    void resetTakenBook(void);
    Book* getTakenBook(void);
}Person;

#endif