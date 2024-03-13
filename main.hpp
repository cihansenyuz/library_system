#include "library.hpp"
#include <iostream>
#include <fstream>

#define BOOK_DATA_FILE "book_data.txt"
#define PERSON_DATA_FILE "person_data.txt"

typedef enum Action{
    Exit, AddBook, RegisterPerson, CheckOut, Return
}Action;

Action getUserAction(void);
void addBookAction(Library&);
void registerPersonAction(Library&);
void checkOutBookAction(Library&);
void returnBookAction(Library&);

/*
1- add book to lib
2- register person
3- check out a book
4- return a book
5- display info
    1- book
    2- person
    3- library
0- exit
*/