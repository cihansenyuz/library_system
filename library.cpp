#include "library.hpp"

/**
 * @brief Constructor from previously saved data.
 *
 * Creates input file from saved data, gets book informations, and sets bookList pointer
 * @param bdf book data file name to be read
 * @param pdf person data file name to be read
 */
Library::Library(string bdf, string pdf) : fileNameBook(bdf), fileNamePerson(pdf){
    // create input file and open it

    ifstream bookData(bdf);
    string temp;    // string to store input file reads
    vector<Book>* savedBookList = new vector<Book>;

    // read until end of file
    while(!bookData.eof())
    {
        getline(bookData, temp, '\t');
        string t = temp;    // title
        getline(bookData, temp, '\t');
        string a = temp;    // author
        getline(bookData, temp, '\t');
        long long int n;    // ISBN
        try{
            n = stoll(temp);
        }
        catch (const std::invalid_argument& e) {
            // no problem
        }
        getline(bookData, temp, '\t');
        char b = temp[0];   // availability
        // create book instances with proper availability
        if(b == '0'){
            Book book(t,a,n,false);
            savedBookList->push_back(book);
        }
        else if(b == '1'){
            Book book(t,a,n);
            savedBookList->push_back(book);
        }
    }
    bookList = savedBookList;   // set bookList pointer
    available = true;           // set library availability
    bookData.close();

    ifstream personData(pdf);
    vector<Person>* savedPersonList = new vector<Person>;

    while(!personData.eof()){
        string temp;
        getline(personData, temp, '\t');
        string n = temp;    // name
        getline(personData, temp, '\t');
        int i; // id
        try{
            i = stoll(temp);
        }
        catch (const std::invalid_argument& e) {
            // no problem
        }
        getline(personData, temp, '\t');
        string t = temp;    // title

        if(n == "") // workaround of a bug
            break;

        // create person and set takenBook
        Person person(n,i);
        for(auto &book : *bookList)
            if(book.getTitle() == t)    // if not taken any book, then it is already nullptr
                person.setTakenBook(book);
        savedPersonList->push_back(person);
    }
    personList = savedPersonList;   // set personList pointer
    personData.close();
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
    vector<pair<int, long long int>> temp;
    for(auto &person : *personList){
        if((person.getTakenBook()))
            temp.push_back(make_pair(person.getId(), person.getTakenBook()->getISBN()));
    }

    bookList->push_back(newBook);

    // fix broken data
    for(auto &pair : temp){                             // for each pair
        for(auto &person : *personList){                // iterate all persons and find who matches to the pair
            if(pair.first == person.getId()){           // once person matches
                for(auto &book : *bookList){            // iterate all books and find which matches to the pair
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
 */
void Library::addBook(const string& bookTitle, const string& bookAuthor, const long long& bookISBN){
    Book b(bookTitle, bookAuthor, bookISBN);
    this->addBook(b);
}

/**
 * @brief Adds a Person to the personList.
 *
 * Takes an Person object as argumant, and pushes it to the vector pointed by personList
 * @param newPerson Person object to be added
 */
void Library::registerPerson(const Person& newPerson){
    personList->push_back(newPerson);
}

/**
 * @brief Creates a Person, and adds it to library.
 *
 * Takes Person constructor argumants, and creates an instance. Then registers it to the library.
 * @param personName name of the person
 * @param personId ID of the person
 */
void Library::registerPerson(const string& personName, const int& personId){
    Person p(personName, personId);
    this->registerPerson(p);
}

/**
 * @brief Prints all available books
 *
 * Prints titles of books that are not taken by anyone
 */
void Library::displayAvailables(void){
    if(!available)
        cout << "All books are taken!\n";
    else
    {
        cout << "Available books in the library:\n";
        for(auto &book : *bookList)
            if(book.isAvailable())
                cout << "- " << book.getTitle() << endl;
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
QString Library::checkOut(const string personName, const string bookTitle){
    bool bookAvailable = false;
    bool personAvailable = false;
    for(auto &book : *bookList)
        if(book.getTitle() == bookTitle)
            bookAvailable = book.isAvailable();
    for(auto &person : *personList)
        if(person.getName() == personName && person.getTakenBook() == nullptr)
            personAvailable = true;

    // check if given argumants are valid
    if(!checkBook(bookTitle))
        return "No such book in the library: " + QString::fromStdString(bookTitle);
    else if(!checkPerson(personName))
        return "This person is not registered: " + QString::fromStdString(personName);

    // check availability of person and book
    if(bookAvailable && personAvailable)
    {   
        for(auto &book : *bookList) // find the book in the list
            if(book.getTitle() == bookTitle)
            {   
                book.setAvailable(false); // set not available
                for(auto &person : *personList) // find the person in the list
                    if(person.getName() == personName)
                    {   
                        person.setTakenBook(book); // give the book to the person setting takenBook
                        return "Book '" + QString::fromStdString(bookTitle) + "' is given to " + QString::fromStdString(personName);
                    }
            }
    }
    else if(!bookAvailable)
        return "This book is already taken by someone else";
    else if(!personAvailable)
        return QString::fromStdString(personName) + " has already taken a book. Needs to return it to take a new one.";
}

/**
 * @brief Returns a book to library
 *
 * Takes book title, sets the book available, sets persons takenBook pointer to nullptr
 * @param bookTitle title of the book
 * @return informative messages about operation as QString
 */
QString Library::returnBook(const string bookTitle){
    // check if the book really exists
    if(!checkBook(bookTitle))
        return "There is no such book! Please check spelling...";

    // find book in the library and set availability true
    for(auto &book : *bookList)
        if(book.getTitle() == bookTitle)
            book.setAvailable(true);

    // find person and reset takenBook pointer
    for(auto &person : *personList){
        if(!person.getTakenBook())      // check if it s null before to get title, otherwise crashes
            continue;
        if(person.getTakenBook()->getTitle() == bookTitle){
            person.resetTakenBook();
            return QString::fromStdString(bookTitle) + " is taken back from " + QString::fromStdString(person.getName());
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
    QString result = "Library Summary:\n";

    // counters to keep status of books
    short availableCount = 0;
    short nonAvailableCount = 0;

    // printing starts here
    result += " - " ;//+ QString::fromStdString(std::to_string(bookList->size())) + " books in the library" + '\n';
    for(auto &book : *bookList) // print all books in the library
    {
        if(book.isAvailable()){
            availableCount++;
        }
        else{
            nonAvailableCount++;
        }
    }
    result += "Available: " + std::to_string(availableCount) + " Checked Out: " + std::to_string(nonAvailableCount) + '\n';
    result += " - " + std::to_string(personList->size()) + " users registered in the library" + '\n';
    return result;
}

/**
 * @brief Setter function for personList pointer.
 *
 * @param list pointer of a vector of Persons
 */
void Library::setPersonList(vector<Person>* list){
    personList = list;
}

/**
 * @brief Checks if a person is registered in the library
 *
 * Takes name of the person, and searches for it in the vector pointed by personList
 * @param name name of the person
 * @return true: name exists, false: does not
 */
bool Library::checkPerson(const string name){
    for(auto &person : *personList)
        if(person.getName() == name)
            return true;
    return false;
}

/**
 * @brief Checks if a book is registered in the library
 *
 * Takes title of the book, and searches for it in the vector pointed by bookList
 * @param title title of the book
 * @return true: title exists, false: does not
 */
bool Library::checkBook(const string title){
    for(auto &book : *bookList)
        if(book.getTitle() == title)
            return true;
    return false;
}

/**
 * @brief Saves latest status of library
 *
 * Creates output file, and saves all related information inside.
 */
void Library::saveLatestData(void){
        // create output file
        ofstream bookData(fileNameBook);
        if(!(bookData.is_open()))
            cout << "couldnot open the data file" << endl;
        
        // keep record of every book, \t is terminator for reading operation
        for(auto &book : *bookList)
        {
            bookData << book.getTitle() << '\t' 
                    << book.getAuthor() << "\t" 
                    << book.getISBN() << '\t' 
                    << book.isAvailable() << '\t';
        }
        bookData.close();
        
        ofstream personData(fileNamePerson);
        if(!(personData.is_open()))
            cout << "couldnot open the person file" << endl;

        // keep record of every person, \t is terminator for reading operation
        for(auto &person : *personList)
        {
            personData << person.getName() << '\t' << person.getId() << "\t";
            if((person.getTakenBook()))
                personData << person.getTakenBook()->getTitle() << '\t';
            else
                personData << '-' << '\t';
        }
        personData.close();
    }

/**
 * @brief Getter function for bookList pointer.
 *
 * @return addres of the bookList
 */
vector<Book>* Library::getBookList(void){
    return bookList;
}

/**
 * @brief Getter function for personList pointer.
 *
 * @return addres of the personList
 */
vector<Person>* Library::getPersonList(void){
    return personList;
}
