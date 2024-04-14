#include "library.hpp"

/**
 * @brief Constructor from previously saved data.
 *
 * Creates input file from saved data, gets book informations, and sets bookList pointer
 * @param pathToBookData book data file name to be read
 * @param pathToPersonData person data file name to be read
 */
Library::Library(string pathToBookData, string pathToPersonData) : m_pathToBookData(pathToBookData), m_pathToPersonData(pathToPersonData){
    // create input file and open it
    ifstream bookData(pathToBookData);
    string subString;    // string to store input file reads
    unique_ptr<vector<Book>> savedBookList = make_unique<vector<Book>>();

    // read until end of file
    while(!bookData.eof())
    {
        getline(bookData, subString, '\t');
        string title = subString;
        getline(bookData, subString, '\t');
        string author = subString;
        getline(bookData, subString, '\t');
        long long int ISBN;
        try{
            ISBN = stoll(subString);
        }
        catch (const std::invalid_argument& e) {
            // no problem, this is workaround
        }
        getline(bookData, subString, '\t');
        char available = subString[0];

        // create book instances with proper availability
        if(available == BOOK_NOT_AVAILABLE){
            Book book(title, author, ISBN, false);
            savedBookList->push_back(book);
        }
        else if(available == BOOK_AVAILABLE){
            Book book(title, author, ISBN);
            savedBookList.get()->push_back(book);
        }
    }
    m_bookList = std::move(savedBookList);
    m_available = true;
    bookData.close();

    ifstream personData(pathToPersonData);
    unique_ptr<vector<Person>> savedPersonList = make_unique<vector<Person>>();

    while(!personData.eof()){
        string subString;
        getline(personData, subString, '\t');
        string name = subString;
        getline(personData, subString, '\t');
        int ID;
        try{
            ID = stoi(subString);
        }
        catch (const std::invalid_argument& e) {
            // no problem, this is workaround
        }
        Person person(name, ID);

        getline(personData, subString, '\t');
        while(subString != "STOP"){
            string takenBookTitle = subString;  // so it is a title
            vector<int> takenDates;
            vector<Book*> takenBooks;
            for(auto &book : *m_bookList){
                if(book.getTitle() == takenBookTitle){
                    Book* taken= &book;
                    takenBooks.push_back(taken);
                    int date;
                    for(int i=0; i<3; i++){
                        getline(personData, subString, '\t');
                        try{
                            date = stoi(subString);
                        }
                        catch (const std::invalid_argument& e) {
                            // no problem, this is workaround
                        }
                        takenDates.push_back(date);
                    }
                    break;
                }
            }
            getline(personData, subString, '\t');
            if(subString == "STOP")
                person = Person(name, ID, takenBooks, takenDates);
        }
        savedPersonList.get()->push_back(person);
        m_personList = std::move(savedPersonList);
        personData.close();
    }
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
        if(person.getTakenBook().size()){
            for(auto it=person.getTakenBook().begin(); it != person.getTakenBook().end(); it++)
                takenBookMatches.push_back(make_pair(person.getID(), (*it)->getISBN()));
        }
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
    if(book->isAvailable() && person->getTakenBook().size() == 0)
    {
        book->setAvailable(false); // set not available
        person->setTakenBook(*book); // give the book to the person setting takenBook
        return "Book '" + QString::fromStdString(book->getTitle()) + "' is given to " + QString::fromStdString(person->getName());
    }
    else if(!book->isAvailable())
        return "This book is already taken by someone else";
    else if(person->getTakenBook().size() == 3){

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
        // create output file
        ofstream bookData(m_pathToBookData);
        if(!(bookData.is_open()))
            cout << "couldnot open the data file" << endl;
        
        // keep record of every book, \t is seperator for reading operation
        for(auto &book : *m_bookList)
        {
            bookData << book.getTitle() << '\t' 
                    << book.getAuthor() << "\t" 
                    << book.getISBN() << '\t' 
                    << book.isAvailable() << '\t';
        }
        bookData.close();
        
        ofstream personData(m_pathToPersonData);
        if(!(personData.is_open()))
            cout << "couldnot open the person file" << endl;

        // keep record of every person, \t is seperator for reading operation
        for(auto &person : *m_personList)
            personData << writePersonData(person);
        personData.close();
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

void Library::writePersonData(const Person& person){
    string data;
    data << person.getName() << '\t' << person.getID() << "\t";

    if(person.getTakenBook()->size() != 0){
        auto dateIterator = person.getTakenDate().begin();
        for(auto &taken : *person.getTakenBook()){
            data << taken.getTitle() << '\t';
            data << *dateIterator << '\t';  // day
            dateIterator++;
            data << *dateIterator << '\t';  // month
            dateIterator++;
            data << *dateIterator << '\t';  // year
            dateIterator++;
        }
    }
    data << "STOP" << '\t';
    return data;
}
