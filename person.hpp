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
    Person(string n, int i);
    Person(const Person& p);
    Person& operator=(const Person& other);
    void displayInfo(void);
    string getName(void) const;
    int getID(void) const;
    void setTakenBook(Book& b);
    void resetTakenBook(void);
    Book* getTakenBook(void) const;
    ~Person(){}
}Person;

#endif
