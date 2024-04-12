#ifndef PERSON_HPP
#define PERSON_HPP

#include "book.hpp"
#include <iostream>

typedef class Person
{
private:
    string m_name;        /** Name of the person */
    int m_ID;             /** ID of the person */
    Book* m_takenBook;    /** Pointed book taken by the person */
public:
    Person(string name, int ID);
    Person(const Person& p);
    Person& operator=(const Person& other);
    void displayInfo(void);
    string getName(void) const;
    int getID(void) const;
    void setTakenBook(Book& takenBook);
    void resetTakenBook(void);
    Book* getTakenBook(void) const;
    ~Person(){}
}Person;

#endif
