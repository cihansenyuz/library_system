#ifndef PERSON_HPP
#define PERSON_HPP

#include "book.hpp"
#include <iostream>

typedef class Person
{
private:
    string name;
    int id;
    Book* takenBook;
public:
    Person(string n, int i) : name(n), id(i), takenBook(nullptr){}
    void displayInfo(void);
    string getName(void);
    bool operator<(const Person& other)const;
    void setTakenBook(Book& b);
    void resetTakenBook(void);
    Book* getTakenBook(void);
}Person;

#endif