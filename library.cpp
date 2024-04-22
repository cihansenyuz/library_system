#include "library.hpp"

/**
 * @brief Constructor from previously saved data.
 *
 * Creates input file from saved data, gets book informations, and sets bookList pointer
 * @param pathToBookData book data file name to be read
 * @param pathToPersonData person data file name to be read
 */
Library::Library(string pathToBookData, string pathToPersonData)
    : m_pathToBookData(pathToBookData), m_pathToPersonData(pathToPersonData){
    
    int result = sqlite3_open(DATABASE_PATH, &database);
    if (result != SQLITE_OK) {
        // Handle error
        //return 1;
    }

    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS books (isbn INTEGER PRIMARY KEY, title TEXT, author TEXT, available INTEGER)";
    sqlite3_exec(database, createTableSQL, NULL, 0, NULL);
    createTableSQL = "CREATE TABLE IF NOT EXISTS persons (id INTEGER PRIMARY KEY, name TEXT, takenBookIsbn INTEGER, takenDate INTEGER)";
    sqlite3_exec(database, createTableSQL, NULL, 0, NULL);

    m_bookList = make_unique<vector<Book>>();
    m_personList = make_unique<vector<Person>>();

    readBookData();
    readPersonData();
    sqlite3_close(database);
}

/**
 * @brief Adds a Book to the bookList.
 *
 * Takes an Book object as argumant, and pushes it to the vector pointed by bookList
 * @param newBook Book object to be added
 */
void Library::addBook(const Book& newBook){
    // once push back an obj to vector, objs pointed inside vector are lost
    // which causes crash in the program since tries to access wrong/not valid memory address
    // to overcome issue, temporarily saved information about which person points to which book
    vector<pair<int, long long int>> takenBookMatches;
    for(auto &person : *m_personList){
        if((person.getTakenBook()))
            takenBookMatches.push_back(make_pair(person.getID(), person.getTakenBook()->getISBN()));
    }
    m_bookList->push_back(newBook);

    // fix broken data
    for(auto &pair : takenBookMatches){                 // for each pair
        for(auto &person : *m_personList){              // iterate all persons and find who matches to the pair
            if(pair.first == person.getID()){           // once person matches
                for(auto &book : *m_bookList){          // iterate all books and find which matches to the pair
                    if(pair.second == book.getISBN())   // once also book matches
                        person.setTakenBook(book);      // set person taken book again which was broken
                }
            }
        }
    }
}

/**
 * @brief Creates a Book, and adds it to library.
 *
 * Takes Book constructor argumants, and creates an instance. Then adds it to the library.
 * @param bookTitle title of the book
 * @param bookAuthor author of the book
 * @param bookISBN ISBN of the book
 * @return informative messages about operation as QString
 */
QString Library::addBook(const string& bookTitle, const string& bookAuthor, const long long& bookISBN){
    if(checkBook(bookISBN))
        return "The book is already registered in the library";
    Book newBook(bookTitle, bookAuthor, bookISBN);
    this->addBook(newBook);
    return "New book is registered in the library";
}

/**
 * @brief Adds a Person to the personList.
 *
 * Takes an Person object as argumant, and pushes it to the vector pointed by personList
 * @param newPerson Person object to be added
 */
void Library::registerPerson(const Person& newPerson){
    m_personList->push_back(newPerson);
}

/**
 * @brief Creates a Person, and adds it to library.
 *
 * Takes Person constructor argumants, and creates an instance. Then registers it to the library.
 * @param personName name of the person
 * @param personId ID of the person
 * @return informative messages about operation as QString
 */
QString Library::registerPerson(const string& personName, const int& personId){
    if(checkPerson(personId))
        return "The user is already registered in the library";
    Person newPerson(personName, personId);
    this->registerPerson(newPerson);
    return "New user is registered in the library";
}

void Library::remove(Book* book){
    for(auto it = getBookList()->begin(); it != getBookList()->end(); it++){
        if(it->getISBN() == book->getISBN()){
            getBookList()->erase(it);
            break;
        }
    }
}

void Library::remove(Person* person){
    for(auto it = getPersonList()->begin(); it != getPersonList()->end(); it++){
        if(it->getID() == person->getID()){
            getPersonList()->erase(it);
            break;
        }
    }
}

/**
 * @brief Check out a book from library
 *
 * Takes person name and book title, sets the book not available, sets persons takenBook pointer
 * @param personName name of the person
 * @param bookTitle title of the book
 * @return informative messages about operation as QString
 */
QString Library::checkOut(Person* person, Book* book){
    // check if given argumants are valid
    if(!book)
        return "No such book in the library!";
    else if(!person)
        return "This user is not registered!";

    // check availability of person and book
    if(book->isAvailable() && person->getTakenBook() == nullptr)
    {

        book->setAvailable(false); // set not available
        person->setTakenBook(*book); // give the book to the person setting takenBook
        return "Book '" + QString::fromStdString(book->getTitle()) + "' is given to " + QString::fromStdString(person->getName());
    }
    else if(!book->isAvailable())
        return "This book is already taken by someone else";
    else if(person->getTakenBook()){

        return QString::fromStdString(person->getName()) + " has already taken a book. Needs to return it to take a new one.";
    }
    return "supress for -Wreturn-type";
}

/**
 * @brief Returns a book to library
 *
 * Takes book title, sets the book available, sets persons takenBook pointer to nullptr
 * @param bookTitle title of the book
 * @return informative messages about operation as QString
 */
QString Library::returnBook(Book* book){
    // check if the book really exists
    if(!book)
        return "There is no such book! Please check spelling...";

    book->setAvailable(true);

    // find person and reset takenBook pointer
    for(auto &person : *m_personList){
        if(!person.getTakenBook())      // check if it s null before to get title, otherwise crashes
            continue;
        if(person.getTakenBook() == book){
            person.resetTakenBook();
            return "The book is taken back from " + QString::fromStdString(person.getName());
        }
    }
    return "This book is already available";
}

/**
 * @brief Gets summary of the library.
 *
 * Prints how many available/not available books there are.
 * Also, prints registered how many users registered
 * @return QString type of all the summary text
 */
QString Library::getSummary(void) {
    QString message = "Library Summary:\n";

    // temp counters to keep status of books
    short availableCount = 0;
    short nonAvailableCount = 0;

    // printing starts here
    message += " - " ;
    for(auto &book : *m_bookList) // print all books in the library
    {
        if(book.isAvailable()){
            availableCount++;
        }
        else{
            nonAvailableCount++;
        }
    }
    message += "Available: " + std::to_string(availableCount) + " Checked Out: " + std::to_string(nonAvailableCount) + '\n';
    message += " - " + std::to_string(m_personList->size()) + " users registered in the library" + '\n';
    return message;
}

/**
 * @brief Checks if a person is registered in the library
 *
 * Takes ID of the person, and searches for it in the vector pointed by personList
 * @param personID unique ID of the person
 * @return object adress which matches, otherwise returns nullptr
 */
Person* Library::checkPerson(const int &personID){
    for(auto &person : *m_personList)
        if(person.getID() == personID)
            return &person;
    return nullptr;
}

/**
 * @brief Checks if a book is registered in the library
 *
 * Takes ISBN of the book, and searches for it in the vector pointed by bookList
 * @param bookISBN unique ISBN of the book
 * @return object adress which matches, otherwise returns nullptr
 */
Book* Library::checkBook(const long long int &bookISBN){
    for(auto &book : *m_bookList)
        if(book.getISBN() == bookISBN)
            return &book;
    return nullptr;
}

/**
 * @brief Saves latest status of library
 *
 * Creates output file, and saves all related information inside.
 */
void Library::saveLatestData(void){
    int result = sqlite3_open(DATABASE_PATH, &database);
    if (result != SQLITE_OK) {
        // Handle error
        //return 1;
    }

    sqlite3_exec(database, "DELETE FROM books", NULL, 0, NULL);
    sqlite3_exec(database, "DELETE FROM persons", NULL, 0, NULL);

    string insertSQL = "";
    for(auto &book : *m_bookList){
        insertSQL = "INSERT INTO books (isbn, title, author, available) VALUES (";
        insertSQL += to_string(book.getISBN()) + ", '" + book.getTitle() + "', '" + book.getAuthor() + "', " + to_string(book.isAvailable()) + ")";
        sqlite3_exec(database, insertSQL.c_str(), NULL, 0, NULL);
    }
    
    for(auto &person : *m_personList)
    {
        insertSQL = "INSERT INTO persons (id, name, takenBookIsbn, takenDate) VALUES (";
        insertSQL += to_string(person.getID()) + ", '" + person.getName() + "', '";
        if((person.getTakenBook())){
            insertSQL += person.getTakenBook()->getTitle() + "', '";
            vector<int> takenDate = person.getTakenDate();
            for(auto &date : takenDate){
                insertSQL += to_string(date) + "/";
            }
            insertSQL += "')";
        }
        else
            insertSQL += " - ', ' - ')";
        sqlite3_exec(database, insertSQL.c_str(), NULL, 0, NULL);
    }
    
    sqlite3_close(database);
}

/**
 * @brief Getter function for bookList pointer.
 *
 * @return addres of the bookList
 */
vector<Book>* Library::getBookList(void){
    return m_bookList.get();
}

/**
 * @brief Getter function for personList pointer.
 *
 * @return addres of the personList
 */
vector<Person>* Library::getPersonList(void){
    return m_personList.get();
}

/**
 * @brief Reading process for book data
 * Reads from given book data input file stream, and creates a Book object,
 * Then adds it to given book list
 *
 * @param bookData input file stream to be read
 * @param bookList book list which gets created book
 * @return none
 */
void Library::readBookData(){
    ifstream bookData(m_pathToBookData);
    string subString;
    while(!bookData.eof()){
        getline(bookData, subString, DATA_SEPERATOR);
        string title = subString;
        getline(bookData, subString, DATA_SEPERATOR);
        string author = subString;
        getline(bookData, subString, DATA_SEPERATOR);
        long long int ISBN;
        try{
            ISBN = stoll(subString);
        }
        catch (const std::invalid_argument& e) {
            // no problem, this is workaround
        }
        getline(bookData, subString, DATA_SEPERATOR);
        char available = subString[0];
        if(available == BOOK_NOT_AVAILABLE)
            m_bookList->push_back(Book(title, author, ISBN, false));
        else if(available == BOOK_AVAILABLE)
            m_bookList->push_back(Book(title, author, ISBN));
    }
    bookData.close();
}

/**
 * @brief Reading process for person data
 * Reads from given person data input file stream, and creates a Pook object,
 * Then adds it to given person list
 *
 * @param personData input file stream to be read
 * @param personList person list which gets created person
 * @return none
 */
void Library::readPersonData(){
    ifstream personData(m_pathToPersonData);
    string subString;
    while(!personData.eof()){
        getline(personData, subString, DATA_SEPERATOR);
        string name = subString;
        getline(personData, subString, DATA_SEPERATOR);
        int ID;
        try{
            ID = stoi(subString);
        }
        catch (const std::invalid_argument& e) {
            // no problem, this is workaround
        }
        getline(personData, subString, DATA_SEPERATOR);
        string takenBookTitle = subString;

        if(name == "") // the end of the data
            return;

        Person person(name, ID);
        for(auto &book : *m_bookList){
            if(book.getTitle() == takenBookTitle){    // if not taken any book, then it is already nullptr
                vector<int> takenDate;
                for(int i=0; i<3; i++){
                    getline(personData, subString, DATA_SEPERATOR);
                    int date;
                    try{
                        date = stoi(subString);
                    }
                    catch (const std::invalid_argument& e) {
                        // no problem, this is workaround
                    }
                    takenDate.push_back(date);
                }
                person = Person(name, ID, book, takenDate);
            }
        }
        m_personList->push_back(person);
    }
    personData.close();
}
