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
    /**
     * @brief Prints properties of the object.
     *
     * Prints Name, ID and the title of the taken book
     */
    void displayInfo(void);
    /**
     * @brief Getter function for name variable.
     *
     * @return name of the person
     */
    string getName(void);
    /**
     * @brief Setter function for takenBook pointer.
     * 
     * @param b the book object which is taken by the person
     */
    void setTakenBook(Book& b);
    /**
     * @brief Reset function for takenBook pointer.
     * 
     * Resets the takenBook pointer to nullptr
     */
    void resetTakenBook(void);
    /**
     * @brief Getter function for takenBook pointer.
     *
     * @return adress of the pointed object
     */
    Book* getTakenBook(void);
}Person;

#endif