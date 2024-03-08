#include "person.hpp"

void Person::displayInfo(void) {
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    if(takenBook)
        cout << "Book: " << takenBook->getTitle() << endl;
    else
        cout << "Book: not taken" << endl;
}
string Person::getName(void) {
    return name;
}
bool Person::operator<(const Person& other)const{
    if(id < other.id)
        return true;
    else
        return false;
}
void Person::setTakenBook(Book& b){
    takenBook = &b;
}
void Person::resetTakenBook(void){
    takenBook = nullptr;
}
Book* Person::getTakenBook(void){
    return takenBook;
}