#include "person.hpp"

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
string Person::getName(void) {
    return name;
}

/**
 * @brief Getter function for name variable.
 *
 * @return name of the person
 */
int Person::getId(void){
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
Book* Person::getTakenBook(void){
    return takenBook;
}