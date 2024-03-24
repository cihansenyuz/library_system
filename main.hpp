#ifndef MAIN_HPP
#define MAIN_HPP

/**
 * @brief This header contains prototypes and defines for main source file.
 *
 * 
 */

#include "library.hpp"
#include <iostream>
#include <fstream>

#if defined(__linux__)
    #define BOOK_DATA_FILE "./book_data.txt"
    #define PERSON_DATA_FILE "./person_data.txt"
#else
    #define BOOK_DATA_FILE ".\\book_data.txt"
    #define PERSON_DATA_FILE ".\\person_data.txt"
#endif

using namespace std;

/*typedef enum Action{
    Exit, AddBook, RegisterPerson, CheckOut, Return, Display
}Action;

Action getUserAction(void);
void addBookAction(Library&);
void registerPersonAction(Library&);
void checkOutBookAction(Library&);
void returnBookAction(Library&);*/

/*
1- add book to lib
2- register person
3- check out a book
4- return a book
5- display info
0- exit
*/

#endif
