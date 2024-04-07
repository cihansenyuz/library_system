#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, Library *lib, QString pv)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), library(lib), programVersion(pv), returnBookCompleter(nullptr), checkOutBookCompleter(nullptr), personCompleter(nullptr)
{
    ui->setupUi(this);

    // signal-slot connections for pushButtons clicks
    connect(ui->summaryButton, &QPushButton::clicked, this, &MainWindow::summaryButtonClicked);
    connect(ui->checkOutButton, &QPushButton::clicked, this, &MainWindow::checkOutButtonClicked);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::returnButtonClicked);
    connect(ui->switchButton, &QPushButton::clicked, this, &MainWindow::switchButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearButtonClickled);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::registerButtonClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::exitButtonClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeButtonClicked);

    // signal-slot connections for tableWidgets cell selections
    connect(ui->bookTableWidget, &QTableWidget::cellClicked, this, &MainWindow::tableItemSelected);
    connect(ui->personTableWidget, &QTableWidget::cellClicked, this, &MainWindow::tableItemSelected);

    // signal-slot connections for lineEdit edits
    connect(ui->returnBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::returnBookTitleLineEditUpdated);
    connect(ui->checkOutBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::checkOutBookTitleLineEditUpdated);
    connect(ui->checkOutPersonNameLineEdit, &QLineEdit::textEdited, this, &MainWindow::checkOutPersonTitleLineEditUpdated);

    // second signal-slot connections for user input actions
    connect(ui->bookTableWidget, &QTableWidget::cellClicked, this, &MainWindow::newUserInput);
    connect(ui->personTableWidget, &QTableWidget::cellClicked, this, &MainWindow::newUserInput);
    connect(ui->returnBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::newUserInput);
    connect(ui->checkOutBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::newUserInput);
    connect(ui->checkOutPersonNameLineEdit, &QLineEdit::textEdited, this, &MainWindow::newUserInput);

    // create tables for the first time
    updatePersonTable();
    updateBookTable();
    ui->tabWidget->setCurrentIndex(bookTable);  // init tabWidget showing book table

    // init unique number labels to prevent window resize after item selection
    ui->checkOutISBN->setText(NOT_VALID_INPUT_ISBN);
    ui->checkOutID->setText(NOT_VALID_INPUT_ID);
    ui->returnISBN->setText(NOT_VALID_INPUT_ISBN);

    // welcome user
    ui->infoTextBrowser->append("Welcome to the " + programVersion);
}

MainWindow::~MainWindow()
{
    library->saveLatestData();
    delete returnBookCompleter;
    delete checkOutBookCompleter;
    delete personCompleter;
    delete ui;
}

/**
 * @brief Updates content in tableWidget
 *
 * Gets book's contents from Library object. Creates and add items in the tableWidget
 *
* @param none
* @return none
 * */
void MainWindow::updateBookTable(){
    // preparetions for completer
    if(returnBookCompleter)             // delete old completer
        delete returnBookCompleter;
    if(checkOutBookCompleter)           // delete old completer
        delete checkOutBookCompleter;
    bookTitleCompletions.clear();       // delete old completions

    // create the table
    unsigned int rowCount = library->getBookList()->size();
    ui->bookTableWidget->setRowCount(rowCount);
    ui->bookTableWidget->setColumnCount(BOOK_DATA_COLUMN_COUNT);

    // set labels
    QStringList labels;
    labels << "Title" << "Author" << "ISBN" << "Availability";
    ui->bookTableWidget->setHorizontalHeaderLabels(labels);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (unsigned int currentRow = 0; currentRow < rowCount; currentRow++)
    {
        item = new QTableWidgetItem(QString::fromStdString(library->getBookList()->at(currentRow).getTitle()));
        ui->bookTableWidget->setItem(currentRow, titleColumn, item);
        bookTitleCompletions << item->text();

        item = new QTableWidgetItem(QString::fromStdString(library->getBookList()->at(currentRow).getAuthor()));
        ui->bookTableWidget->setItem(currentRow, authorColumn, item);

        item = new QTableWidgetItem(QString::number(library->getBookList()->at(currentRow).getISBN()));
        ui->bookTableWidget->setItem(currentRow, ISBNColumn, item);
        item->setTextAlignment(Qt::AlignCenter);

        if(library->getBookList()->at(currentRow).isAvailable())
            item = new QTableWidgetItem(BOOK_AVAILABLE);
        else
            item = new QTableWidgetItem(BOOK_NOT_AVAILABLE);
        item->setTextAlignment(Qt::AlignCenter);
        ui->bookTableWidget->setItem(currentRow, availabilityColumn, item);
    }
    ui->bookTableWidget->resizeColumnsToContents();

    // final configuration for completer
    checkOutBookCompleter = new QCompleter(bookTitleCompletions, ui->checkOutBookTitleLineEdit);    // create completer
    checkOutBookCompleter->setCaseSensitivity(Qt::CaseInsensitive);                                 // setting
    checkOutBookCompleter->setFilterMode(Qt::MatchContains);                                        // setting
    ui->checkOutBookTitleLineEdit->setCompleter(checkOutBookCompleter);                             // set completer for line edit
    connect(checkOutBookCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &MainWindow::checkOutBookTitleLineEditCompleterClicked);
    connect(checkOutBookCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &MainWindow::newUserInput);

    returnBookCompleter = new QCompleter(bookTitleCompletions, ui->returnBookTitleLineEdit);        // create completer
    returnBookCompleter->setCaseSensitivity(Qt::CaseInsensitive);                                   // setting
    returnBookCompleter->setFilterMode(Qt::MatchContains);                                          // setting
    ui->returnBookTitleLineEdit->setCompleter(returnBookCompleter);                                 // set completer for line edit
    connect(returnBookCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &MainWindow::returnBookTitleLineEditCompleterClicked);
    connect(returnBookCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &MainWindow::newUserInput);
}

/**
 * @brief Updates content in tableWidget
 *
 * Gets user's contents from Library object. Creates and add items in the tableWidget
 *
* @param none
* @return none
 * */
void MainWindow::updatePersonTable(){
    // preparetions for completer
    if(personCompleter)               // delete old completer
        delete personCompleter;
    personNameCompletions.clear();   // delete old completions

    // create the table
    unsigned int rowCount = library->getPersonList()->size();
    ui->personTableWidget->setRowCount(rowCount);
    ui->personTableWidget->setColumnCount(PERSON_DATA_COLUMN_COUNT);

    // set labels
    QStringList labels;
    labels << "Name" << "ID" << "Taken Book";
    ui->personTableWidget->setHorizontalHeaderLabels(labels);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (unsigned int currentRow = 0; currentRow < rowCount; currentRow++)
    {
        item = new QTableWidgetItem(QString::fromStdString(library->getPersonList()->at(currentRow).getName()));
        ui->personTableWidget->setItem(currentRow, nameColumn, item);
        personNameCompletions << item->text();

        item = new QTableWidgetItem(QString::fromStdString(std::to_string(library->getPersonList()->at(currentRow).getID())));
        ui->personTableWidget->setItem(currentRow, IDColumn, item);
        item->setTextAlignment(Qt::AlignCenter);

        if(library->getPersonList()->at(currentRow).getTakenBook())
            item = new QTableWidgetItem(QString::fromStdString(library->getPersonList()->at(currentRow).getTakenBook()->getTitle()));
        else{
            item = new QTableWidgetItem(NO_TAKEN_BOOK);
            item->setTextAlignment(Qt::AlignCenter);
        }
        ui->personTableWidget->setItem(currentRow, takenBookColumn, item);
    }
    ui->personTableWidget->resizeColumnsToContents();

    // final configuration for completer
    personCompleter = new QCompleter(personNameCompletions, ui->checkOutBookTitleLineEdit); // create completer
    personCompleter->setCaseSensitivity(Qt::CaseInsensitive);                               // setting
    personCompleter->setFilterMode(Qt::MatchContains);                                      // setting
    ui->checkOutPersonNameLineEdit->setCompleter(personCompleter);                          // set completer for line edit
    connect(personCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &MainWindow::checkOutPersonTitleLineEditCompleterClicked);
    connect(personCompleter, QOverload<const QString &>::of(&QCompleter::activated), this, &MainWindow::newUserInput);
}

/**
* @brief Slot method to handle click action on summaryButton
*
* Gets summary from the library and appends it to infoTextBrowser.
*
* @param none
* @return none
*/
void MainWindow::summaryButtonClicked()
{
    ui->infoTextBrowser->append(this->library->getSummary());
}

/**
* @brief Slot method to handle click action on checkOutButton
*
* Gets texts on editLines, and passes relevant book or person object to Library::checkOut function.
*
* @param none
* @return none
*/
void MainWindow::checkOutButtonClicked(){
    QString resultMessage;
    Book *bookToCheckOut;
    Person *userCheckingOut;
    bookToCheckOut = this->library->checkBook(std::stoll(ui->checkOutISBN->text().toStdString()));
    userCheckingOut = this->library->checkPerson(std::stoi(ui->checkOutID->text().toStdString()));
    resultMessage = this->library->checkOut(userCheckingOut, bookToCheckOut);
    ui->checkOutBookTitleLineEdit->clear();
    ui->checkOutPersonNameLineEdit->clear();
    ui->infoTextBrowser->append(resultMessage);
    updateTables();
}

/**
* @brief Slot method to handle click action on returnButton
*
* Gets the text on editLine, and passes relevant book to Library::returnBook function.
*
* @param none
* @return none
*/
void MainWindow::returnButtonClicked(){
    QString resultMessage;
    Book *bookToReturn;
    bookToReturn = this->library->checkBook(std::stoll(ui->returnISBN->text().toStdString()));
    resultMessage = this->library->returnBook(bookToReturn);
    ui->returnBookTitleLineEdit->clear();
    ui->infoTextBrowser->append(resultMessage);
    updateTables();
}

/**
* @brief Slot method to handle click action on switchButton
*
* Switches between tabWidget tabs
*
* @param none
* @return none
*/
void MainWindow::switchButtonClicked(){
    if(ui->tabWidget->currentIndex() == personTable)
        ui->tabWidget->setCurrentIndex(bookTable);
    else // bookTable
        ui->tabWidget->setCurrentIndex(personTable);
}

/**
* @brief Slot method to handle click action on clearButton
*
* Clears all appended text on the infoTextBrowser.
*
* @param none
* @return none
*/
void MainWindow::clearButtonClickled(){
    ui->infoTextBrowser->clear();
}

/**
* @brief Slot method to handle click action on registerButton
*
* Creates an RegisterDialog object, makes signal/slot connection to get user input from
* RegisterDialog to MainWindow
*
* @param none
* @return none
*/
void MainWindow::registerButtonClicked(){
    RegisterDialog dialog;
    connect(&dialog, &RegisterDialog::userInputReady, this, &MainWindow::getRegisterInput);
    updatePersonTable();
    dialog.setModal(true);
    dialog.exec();
}

/**
* @brief Slot method to handle signal from RegisterDialog
*
* Takes argumants from the signal and registers new Person in the library
*
* @param name name of the Person
* @param id id of the Person
* @return none
*/
void MainWindow::getRegisterInput(const string &name, const int &id){
    this->library->registerPerson(name, id);
    updateTables();
    ui->infoTextBrowser->append("New user registered in the system!");
}

/**
* @brief Slot method to handle click action on addButton
*
* Creates an AddDialog object, makes signal/slot connection to get user input from
* AddDialog to MainWindow
*
* @param none
* @return none
*/
void MainWindow::addButtonClicked(){
    AddDialog dialog;
    connect(&dialog, &AddDialog::userInputReady, this, &MainWindow::getAddInput);
    updateBookTable();
    dialog.setModal(true);
    dialog.exec();
}

/**
* @brief Slot method to handle signal from AddDialog
*
* Takes argumants from the signal and registers new Person in the library
*
* @param tit title of the Book
* @param ath author of the Book
* @param isbn ISBN of the Book
* @return none
*/
void MainWindow::getAddInput(const string &tit, const string &ath, const long long &isbn){
    QString result = this->library->addBook(tit, ath, isbn);
    ui->infoTextBrowser->append(result);
    updateTables();
}

/**
* @brief Slot method to handle click action on removeButton
*
* Creates an RemoveDialog object, makes signal/slot connection to get user input from
* RemoveDialog to MainWindow
*
* @param none
* @return none
*/
void MainWindow::removeButtonClicked(){
    RemoveDialog dialog;
    connect(&dialog, &RemoveDialog::userInputReady, this, &MainWindow::getRemoveInput);
    updateTables();
    dialog.setModal(true);
    dialog.exec();
}

/**
* @brief Slot method to handle signal from AddDialog
*
* Takes argumants from the signal and decides which object need to be removed
* then calls relevant remove function in the library
*
* @param uniqueData ISBN of the Book or user ID
* @return none
*/
void MainWindow::getRemoveInput(const long long int &uniqueData){
    if(uniqueData == INVALID_INPUT){
        ui->infoTextBrowser->append("Cannot remove any book or user; invalid input");
        return;
    }
    if(uniqueData > MAX_POSSIBLE_ID){
        Book* temp = library->checkBook(uniqueData);
        library->remove(temp);
        ui->infoTextBrowser->append("The book removed from the database!");
    }
    else{
        Person* temp = library->checkPerson(uniqueData);
        library->remove(temp);
        ui->infoTextBrowser->append("The user removed from the database!");
    }
    updateTables();
}


/**
* @brief Slot method to handle click action on exitButton
*
* Basicly, calls destructor to save latest status and exit
*
* @param none
* @return none
*/
void MainWindow::exitButtonClicked(){
    this->~MainWindow();
}

/**
* @brief Slot method to handle item selection on tableWidget
*
* Gets row number of the selected item and decides which lineEdit to be auto filled.
* Also sets relevant QLabels to pass unique data to be later on used action buttons
*
* @param row Row number of the selected item
* @param column Column number of the selected item(not used)
* @return none
*/
void MainWindow::tableItemSelected(const int &row, const int &column){
    (void) column;
    if(ui->tabWidget->currentIndex() == bookTable){
        QString bookTitle = (ui->bookTableWidget->item(row, titleColumn))->text();                    // get book title
        if((ui->bookTableWidget->item(row, availabilityColumn)->text() == BOOK_AVAILABLE)){ // book is free
            ui->returnBookTitleLineEdit->clear();
            ui->returnISBN->setText(NOT_VALID_INPUT_ISBN);
            ui->checkOutBookTitleLineEdit->setText(bookTitle);
            ui->checkOutISBN->setText(ui->bookTableWidget->item(row, ISBNColumn)->text());  // set ISBN for checkOut action
        }
        else{   // or already booked
            ui->checkOutBookTitleLineEdit->clear();
            ui->checkOutISBN->setText(NOT_VALID_INPUT_ISBN);
            ui->checkOutPersonNameLineEdit->clear();
            ui->checkOutID->setText(NOT_VALID_INPUT_ID);
            ui->returnBookTitleLineEdit->setText(bookTitle);
            ui->returnISBN->setText(ui->bookTableWidget->item(row, ISBNColumn)->text());    // set ISBN for checkOut action
        }
    }
    else{   // personTable
        QString bookTitle = (ui->personTableWidget->item(row, takenBookColumn))->text();    // get taken book title
        QString personName = (ui->personTableWidget->item(row, nameColumn))->text();        // get user name
        if(bookTitle == NO_TAKEN_BOOK){   // person can take
            ui->returnBookTitleLineEdit->clear();
            ui->returnISBN->setText(NOT_VALID_INPUT_ISBN);
            ui->checkOutPersonNameLineEdit->setText(personName);
            ui->checkOutID->setText(ui->personTableWidget->item(row, IDColumn)->text());    // set ID for checkOut action
        }
        else{   // or already taken
            ui->checkOutBookTitleLineEdit->clear();
            ui->checkOutISBN->setText(NOT_VALID_INPUT_ISBN);
            ui->checkOutPersonNameLineEdit->clear();
            ui->checkOutID->setText(NOT_VALID_INPUT_ID);
            ui->returnBookTitleLineEdit->setText(bookTitle);
            returnBookTitleLineEditUpdated(bookTitle);                  // set ISBN for return action
        }
    }
}

/**
* @brief Slot method to handle editing on returnBookTitleLineEdit
*
* Takes book title, finds corresponding QTableWidgetItem, passes ISBN data to relevant label
*
* @param title edited book title
* @return none
*/
void MainWindow::returnBookTitleLineEditUpdated(const QString& title){
    QList temp = ui->bookTableWidget->findItems(title, Qt::MatchFixedString);
    if(temp.size() == 0)
        return;
    int row = ui->bookTableWidget->row(temp[0]);    // take first element since all books are unique
    if(row == NO_ITEM)
        return;
    else
        ui->returnISBN->setText(ui->bookTableWidget->item(row, ISBNColumn)->text());
}

/**
* @brief Slot method to handle click action on returnBookTitleLineEditCompleter
*
* Takes book title, finds corresponding QTableWidgetItem, passes ISBN data to relevant label
*
* @param title edited book title
* @return none
*/
void MainWindow::returnBookTitleLineEditCompleterClicked(const QString &title){
    QList temp = ui->bookTableWidget->findItems(title, Qt::MatchExactly);
    int row = ui->bookTableWidget->row(temp[0]);
    ui->returnISBN->setText(ui->bookTableWidget->item(row, ISBNColumn)->text());
}

/**
* @brief Slot method to handle editing on checkOutBookTitleLineEdit
*
* Takes book title, finds corresponding QTableWidgetItem, passes ISBN data to relevant label
*
* @param title edited book title
* @return none
*/
void MainWindow::checkOutBookTitleLineEditUpdated(const QString& title){
    QList temp = ui->bookTableWidget->findItems(title, Qt::MatchFixedString);
    if(temp.size() == 0)
        return;
    int row = ui->bookTableWidget->row(temp[0]);
    if(row == NO_ITEM)
        return;
    else
        ui->checkOutISBN->setText(ui->bookTableWidget->item(row, ISBNColumn)->text());
}

/**
* @brief Slot method to handle click action on checkOutBookTitleLineEditCompleter
*
* Takes book title, finds corresponding QTableWidgetItem, passes ISBN data to relevant label
*
* @param title edited book title
* @return none
*/
void MainWindow::checkOutBookTitleLineEditCompleterClicked(const QString &title){
    QList temp = ui->bookTableWidget->findItems(title, Qt::MatchExactly);
    int row = ui->bookTableWidget->row(temp[0]);
    ui->checkOutISBN->setText(ui->bookTableWidget->item(row, ISBNColumn)->text());
}

/**
* @brief Slot method to handle editing on checkOutPersonTitleLineEdit
*
* Takes user name, finds corresponding QTableWidgetItem, passes user ID data to relevant label
*
* @param name edited user name
* @return none
*/
void MainWindow::checkOutPersonTitleLineEditUpdated(const QString& name){
    QList temp = ui->personTableWidget->findItems(name, Qt::MatchFixedString);
    if(temp.size() == 0)
        return;
    int row = ui->personTableWidget->row(temp[0]);
    if(row == NO_ITEM)
        return;
    else
        ui->checkOutID->setText(ui->personTableWidget->item(row, IDColumn)->text());
}

/**
* @brief Slot method to handle click action on checkOutPersonTitleLineEditCompleter
*
* Takes user name, finds corresponding QTableWidgetItem, passes user ID data to relevant label
*
* @param name edited user name
* @return none
*/
void MainWindow::checkOutPersonTitleLineEditCompleterClicked(const QString &name){
    QList temp = ui->personTableWidget->findItems(name, Qt::MatchExactly);
    int row = ui->personTableWidget->row(temp[0]);
    ui->checkOutID->setText(ui->personTableWidget->item(row, IDColumn)->text());
}

/**
* @brief Update data on the tableWidget
*
* Updates data on current table. Does not change table type.
*
* @param none
* @return none
*/
void MainWindow::updateTables(){
    updateBookTable();
    updatePersonTable();
}


void MainWindow::newUserInput(){
    //check if inputs are proper for checkout action
    if(ui->checkOutISBN->text() != NOT_VALID_INPUT_ISBN && ui->checkOutID->text() != NOT_VALID_INPUT_ID)
        ui->checkOutButton->setEnabled(true);
    else
        ui->checkOutButton->setEnabled(false);

    //check if inputs are proper for return action
    if(ui->returnISBN->text() != NOT_VALID_INPUT_ISBN)
        ui->returnButton->setEnabled(true);
    else
        ui->returnButton->setEnabled(false);
}
