#include "person.hpp"

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object, and sets takenBook to nullptr
 * @param n name
 * @param i ID
 */
Person::Person(string n, int i) : name(n), id(i), takenBook(nullptr){}

/**
 * @brief Copy constructor.
 *
 * Initiliazes variables of the object as the given object
 * @param p the person object to be copied
 */
Person::Person(const Person& p) : name(p.getName()), id(p.getID()), takenBook(p.getTakenBook()){}

/**
 * @brief Copy assignment operator.
 *
 * Initiliazes variables of the assignee object as the assigned object
 * @param other the person object to be assigned
 */
Person& Person::operator=(const Person& other){
    if(this != &other){
        name = other.getName();
        id = other.getID();
        takenBook = other.getTakenBook();
    }
    return *this;
}

/**
 * @brief Prints properties of the object.
 *
 * Prints Name, ID and the title of the taken book
 */
void Person::displayInfo(void) {
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    if(takenBook)
        cout << "Book: " << takenBook->getTitle() << endl;
    else
        cout << "Book: not taken" << endl;
}

/**
 * @brief Getter function for name variable.
 *
 * @return name of the person
 */
string Person::getName(void) const{
    return name;
}

/**
 * @brief Getter function for name variable.
 *
 * @return name of the person
 */
int Person::getID(void) const{
    return id;
}

/**
 * @brief Setter function for takenBook pointer.
 * 
 * @param b the book object which is taken by the person
 */
void Person::setTakenBook(Book& b){
    takenBook = &b;
}

/**
 * @brief Reset function for takenBook pointer.
 * 
 * Resets the takenBook pointer to nullptr
 */
void Person::resetTakenBook(void){
    takenBook = nullptr;
}

/**
 * @brief Getter function for takenBook pointer.
 * 
 * @return adress of the pointed object
 */
Book* Person::getTakenBook(void) const{
    return takenBook;
}
