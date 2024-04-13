#include "person.hpp"

/**
 * @brief Parameterized constructor.
 *
 * Initiliazes variables of the object, and sets takenBook to nullptr
 * @param name name of the person
 * @param ID ID of the person
 */
Person::Person(string name, int ID)
    : m_name(name), m_ID(ID), m_takenBook(nullptr){}

Person::Person(string name, int ID, Book& takenBook, vector<int>& takenDate)
    : m_name(name), m_ID(ID), m_takenBook(&takenBook), m_takenDate(takenDate){}

/**
 * @brief Copy constructor.
 *
 * Initiliazes variables of the object as the given object
 * @param other the person object to be copied
 */
Person::Person(const Person& other)
    : m_name(other.getName()), m_ID(other.getID()), m_takenBook(other.getTakenBook()){
    m_takenDate = other.getTakenDate();
}

/**
 * @brief Copy assignment operator.
 *
 * Initiliazes variables of the assignee object as the assigned object
 * @param other the person object to be assigned
 */
Person& Person::operator=(const Person& other){
    if(this != &other){
        m_name = other.getName();
        m_ID = other.getID();
        m_takenBook = other.getTakenBook();
        m_takenDate = other.getTakenDate();
    }
    return *this;
}

/**
 * @brief Prints properties of the object.
 *
 * Prints Name, ID and the title of the taken book
 */
void Person::displayInfo(void) {
    cout << "Name: " << m_name << endl;
    cout << "ID: " << m_ID << endl;
    if(m_takenBook)
        cout << "Book: " << m_takenBook->getTitle() << endl;
    else
        cout << "Book: not taken" << endl;
}

/**
 * @brief Getter function for name variable.
 *
 * @return name of the person
 */
string Person::getName(void) const{
    return m_name;
}

/**
 * @brief Getter function for ID variable.
 *
 * @return ID number of the person
 */
int Person::getID(void) const{
    return m_ID;
}

/**
 * @brief Setter function for takenBook pointer.
 * 
 * @param takenBook the book object which is taken by the person
 */
void Person::setTakenBook(Book& takenBook){
    m_takenBook = &takenBook;
    stampTime();
}

/**
 * @brief Reset function for takenBook pointer.
 * 
 * Resets the takenBook pointer to nullptr
 */
void Person::resetTakenBook(void){
    m_takenBook = nullptr;
    m_takenDate.clear();
}

/**
 * @brief Getter function for takenBook pointer.
 * 
 * @return adress of the pointed object
 */
Book* Person::getTakenBook(void) const{
    return m_takenBook;
}

/**
 * @brief Saves the current date into takenBookDate
 *
 * @return none
 */
void Person::stampTime(){
    m_takenDate.clear();
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);  // Convert current time to local time
    m_takenDate.push_back(localTime->tm_mday);          // Day of the month
    m_takenDate.push_back(localTime->tm_mon + 1);       // Months start from 0
    m_takenDate.push_back(localTime->tm_year + 1900);   // Years since 1900
}

/**
 * @brief Getter function for takenDate vector
 *
 * @return Copy of the takenDate vector
 */
vector<int> Person::getTakenDate() const{
    return m_takenDate;
}
