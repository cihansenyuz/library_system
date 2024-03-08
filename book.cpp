#include "book.hpp"


bool Book::operator<(const Book& other) const{
    if(this->getISBN() < other.getISBN())
        return true;
    else
        return false;
}

void Book::setAvailable(bool opt){
    available = opt;
}

bool Book::isAvailable(void) {
    return available;
}

void Book::displayInfo(void){
    std::cout << "Title: " << getTitle() << endl;
    std::cout << "Author: " << getAuthor() << std::endl;
    std::cout << "ISBN: " << getISBN() << std::endl;
}

string Book::getTitle(void) {
    return title;
}