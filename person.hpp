#ifndef PERSON_HPP
#define PERSON_HPP

#include "book.hpp"
#include <iostream>
#include <ctime>
#include <vector>

typedef class Person
{
private:
    string m_name;              /** Name of the person */
    int m_ID;                   /** ID of the person */
    vector<Book*> m_takenBook;          /** Pointed book taken by the person */
    vector<int> m_takenDate;    /** The date book is taken by the person
                                    in the form of {day,month,year} */
public:
    Person(string name, int ID);
    Person(string name, int ID, vector<Book*>& takenBook, vector<int>& takenDate);
    Person(const Person& other);
    Person& operator=(const Person& other);
    void displayInfo(void);
    string getName(void) const;
    int getID(void) const;
    bool setTakenBook(Book& takenBook);
    void resetTakenBook(void);
    vector<Book*> getTakenBook(void) const;
    void stampTime(void);
    vector<int> getTakenDate(void) const;
    ~Person(){}
}Person;

#endif
