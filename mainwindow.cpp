#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, unique_ptr<Library> library, QString programVersion)
    : QMainWindow(parent), ui(new Ui::MainWindow),
                           m_library(std::move(library)),
                           m_programVersion(programVersion),
                           returnBookCompleter(nullptr),
                           checkOutBookCompleter(nullptr),
                           personCompleter(nullptr)
{
    ui->setupUi(this);

    connect(ui->summaryButton, &QPushButton::clicked, this, &MainWindow::summaryButtonClicked);
    connect(ui->checkOutButton, &QPushButton::clicked, this, &MainWindow::checkOutButtonClicked);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::returnButtonClicked);
    connect(ui->switchButton, &QPushButton::clicked, this, &MainWindow::switchButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearButtonClickled);
    connect(ui->registerButton, &QPushButton::clicked, this, &MainWindow::registerButtonClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::exitButtonClicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeButtonClicked);
    connect(ui->filterClearButton, &QPushButton::clicked, this, &MainWindow::filterClearButtonClicked);

    connect(ui->bookTableWidget, &QTableWidget::cellClicked, this, &MainWindow::tableItemSelected);
    connect(ui->personTableWidget, &QTableWidget::cellClicked, this, &MainWindow::tableItemSelected);

    connect(ui->returnBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::bookTitleLineEditUpdated);
    connect(ui->checkOutBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::bookTitleLineEditUpdated);
    connect(ui->checkOutPersonNameLineEdit, &QLineEdit::textEdited, this, &MainWindow::checkOutPersonTitleLineEditUpdated);
    connect(ui->filterLineEdit, &QLineEdit::textEdited, this, &MainWindow::filterLineEditUpdated);

    connect(ui->bookTableWidget, &QTableWidget::cellClicked, this, &MainWindow::newUserInput);
    connect(ui->personTableWidget, &QTableWidget::cellClicked, this, &MainWindow::newUserInput);
    connect(ui->returnBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::newUserInput);
    connect(ui->checkOutBookTitleLineEdit, &QLineEdit::textEdited, this, &MainWindow::newUserInput);
    connect(ui->checkOutPersonNameLineEdit, &QLineEdit::textEdited, this, &MainWindow::newUserInput);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::currentTabChanged);

    // create tables for the first time to make them ready at start up
    ui->bookTableWidget->setColumnCount(BOOK_DATA_COLUMN_COUNT);    // fixed at compile time
    ui->personTableWidget->setColumnCount(PERSON_DATA_COLUMN_COUNT);
    ui->bookTableWidget->setHorizontalHeaderLabels(QStringList({"Title", "Author", "ISBN", "Availability"}));
    ui->personTableWidget->setHorizontalHeaderLabels(QStringList({"Name", "ID", "Taken Book", "Taken Date"}));
    updatePersonTable();
    updateBookTable();
    ui->tabWidget->setCurrentIndex(bookTable);

    // init unique number labels to prevent window resize after item selection
    ui->checkOutISBN->setText(NOT_VALID_INPUT_ISBN);
    ui->checkOutID->setText(NOT_VALID_INPUT_ID);
    ui->returnISBN->setText(NOT_VALID_INPUT_ISBN);

    ui->infoTextBrowser->append("Welcome to the " + m_programVersion);
}

MainWindow::~MainWindow()
{
    m_library->saveLatestData();
    freeTableMemory(ui->bookTableWidget);
    freeTableMemory(ui->personTableWidget);
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
    returnBookCompleter.reset();
    checkOutBookCompleter.reset();
    bookTitleCompletions.clear();
    ui->bookTableWidget->clearContents();
    freeTableMemory(ui->bookTableWidget);

    unsigned int rowCount = m_library->getBookList()->size(); // since can change at runtime, need to be updated
    ui->bookTableWidget->setRowCount(rowCount);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (unsigned int currentRow = 0; currentRow < rowCount; currentRow++)
    {
        item = new QTableWidgetItem(QString::fromStdString(m_library->getBookList()->at(currentRow).getTitle()));
        ui->bookTableWidget->setItem(currentRow, titleColumn, item);
        bookTitleCompletions << item->text();

        item = new QTableWidgetItem(QString::fromStdString(m_library->getBookList()->at(currentRow).getAuthor()));
        ui->bookTableWidget->setItem(currentRow, authorColumn, item);

        item = new QTableWidgetItem(QString::number(m_library->getBookList()->at(currentRow).getISBN()));
        ui->bookTableWidget->setItem(currentRow, ISBNColumn, item);
        item->setTextAlignment(Qt::AlignCenter);

        if(m_library->getBookList()->at(currentRow).isAvailable())
            item = new QTableWidgetItem(TABLE_BOOK_AVAILABLE);
        else
            item = new QTableWidgetItem(TABLE_BOOK_NOT_AVAILABLE);
        item->setTextAlignment(Qt::AlignCenter);
        ui->bookTableWidget->setItem(currentRow, availabilityColumn, item);
        ui->bookTableWidget->setRowHidden(currentRow, false);
    }

    ui->bookTableWidget->resizeColumnsToContents();

    checkOutBookCompleter = make_unique<QCompleter>(bookTitleCompletions, ui->checkOutBookTitleLineEdit);    // create completer
    checkOutBookCompleter.get()->setCaseSensitivity(Qt::CaseInsensitive);
    checkOutBookCompleter.get()->setFilterMode(Qt::MatchContains);
    ui->checkOutBookTitleLineEdit->setCompleter(checkOutBookCompleter.get());                             // set completer for line edit
    connect(checkOutBookCompleter.get(), QOverload<const QString &>::of(&QCompleter::activated),
            this, &MainWindow::checkOutBookTitleLineEditCompleterClicked);
    connect(checkOutBookCompleter.get(), QOverload<const QString &>::of(&QCompleter::activated),
            this, &MainWindow::newUserInput);

    returnBookCompleter = make_unique<QCompleter>(bookTitleCompletions, ui->returnBookTitleLineEdit);        // create completer
    returnBookCompleter.get()->setCaseSensitivity(Qt::CaseInsensitive);
    returnBookCompleter.get()->setFilterMode(Qt::MatchContains);
    ui->returnBookTitleLineEdit->setCompleter(returnBookCompleter.get());                                 // set completer for line edit
    connect(returnBookCompleter.get(), QOverload<const QString &>::of(&QCompleter::activated),
            this, &MainWindow::returnBookTitleLineEditCompleterClicked);
    connect(returnBookCompleter.get(), QOverload<const QString &>::of(&QCompleter::activated),
            this, &MainWindow::newUserInput);
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
    personCompleter.reset();
    personNameCompletions.clear();
    ui->personTableWidget->clearContents();
    freeTableMemory(ui->personTableWidget);

    unsigned int rowCount = m_library->getPersonList()->size();
    ui->personTableWidget->setRowCount(rowCount);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (unsigned int currentRow = 0; currentRow < rowCount; currentRow++)
    {
        item = new QTableWidgetItem(QString::fromStdString(m_library->getPersonList()->at(currentRow).getName()));
        ui->personTableWidget->setItem(currentRow, nameColumn, item);
        personNameCompletions << item->text();

        item = new QTableWidgetItem(QString::fromStdString(std::to_string(m_library->getPersonList()->at(currentRow).getID())));
        ui->personTableWidget->setItem(currentRow, IDColumn, item);
        item->setTextAlignment(Qt::AlignCenter);

        if(m_library->getPersonList()->at(currentRow).getTakenBook()){
            item = new QTableWidgetItem(QString::fromStdString(m_library->getPersonList()->at(currentRow).getTakenBook()->getTitle()));
            ui->personTableWidget->setItem(currentRow, takenBookColumn, item);

            QString takenDate = QString::fromStdString(std::to_string(m_library->getPersonList()->at(currentRow).getTakenDate().at(DAY)));
            takenDate += "/" + QString::fromStdString(std::to_string(m_library->getPersonList()->at(currentRow).getTakenDate().at(MONTH)));
            takenDate += "/" + QString::fromStdString(std::to_string(m_library->getPersonList()->at(currentRow).getTakenDate().at(YEAR)));
            item = new QTableWidgetItem(takenDate);
            item->setTextAlignment(Qt::AlignCenter);
            ui->personTableWidget->setItem(currentRow, takenDateColumn, item);
        }
        else{
            item = new QTableWidgetItem(TABLE_NO_TAKEN_BOOK);
            ui->personTableWidget->setItem(currentRow, takenBookColumn, item);
            item->setTextAlignment(Qt::AlignCenter);
            item = new QTableWidgetItem(TABLE_NO_TAKEN_BOOK);
            ui->personTableWidget->setItem(currentRow, takenDateColumn, item);
            item->setTextAlignment(Qt::AlignCenter);
        }
        ui->personTableWidget->setRowHidden(currentRow, false);
    }
    ui->personTableWidget->resizeColumnsToContents();

    personCompleter = make_unique<QCompleter>(personNameCompletions, ui->checkOutBookTitleLineEdit); // create completer
    personCompleter.get()->setCaseSensitivity(Qt::CaseInsensitive);
    personCompleter.get()->setFilterMode(Qt::MatchContains);
    ui->checkOutPersonNameLineEdit->setCompleter(personCompleter.get());                          // set completer for line edit
    connect(personCompleter.get(), QOverload<const QString &>::of(&QCompleter::activated),
            this, &MainWindow::checkOutPersonTitleLineEditCompleterClicked);
    connect(personCompleter.get(), QOverload<const QString &>::of(&QCompleter::activated),
            this, &MainWindow::newUserInput);
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
    ui->infoTextBrowser->append(this->m_library->getSummary());
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
    bookToCheckOut = this->m_library->checkBook(std::stoll(ui->checkOutISBN->text().toStdString()));
    userCheckingOut = this->m_library->checkPerson(std::stoi(ui->checkOutID->text().toStdString()));
    resultMessage = this->m_library->checkOut(userCheckingOut, bookToCheckOut);
    ui->checkOutBookTitleLineEdit->clear();
    ui->checkOutPersonNameLineEdit->clear();
    ui->checkOutISBN->setText(NOT_VALID_INPUT_ISBN);
    ui->checkOutID->setText(NOT_VALID_INPUT_ID);
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
    bookToReturn = this->m_library->checkBook(std::stoll(ui->returnISBN->text().toStdString()));
    resultMessage = this->m_library->returnBook(bookToReturn);
    ui->returnBookTitleLineEdit->clear();
    ui->returnISBN->setText(NOT_VALID_INPUT_ISBN);
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
    connect(&dialog, &RegisterDialog::userInputReady,
            this, [&](const string &name, const int &ID){
                        this->getDialogInputs(name, ID);
                    });
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
void MainWindow::getDialogInputs(const string &name, const int &ID){
    this->m_library->registerPerson(name, ID);
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
    connect(&dialog, &AddDialog::userInputReady,
            this, [&](const string &title, const string &author, const long long &ISBN){
                        this->getDialogInputs(title, author, ISBN);
                    });
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
void MainWindow::getDialogInputs(const string &tit, const string &ath, const long long &isbn){
    QString result = this->m_library->addBook(tit, ath, isbn);
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
    connect(&dialog, &RemoveDialog::userInputReady,
            this, [&](const long long int &uniqueData, const char& selection){
                        this->getDialogInputs(uniqueData, selection);
                    });
    updateTables();
    dialog.setModal(true);
    dialog.exec();
}

/**
* @brief Slot method to handle signal from RemoveDialog
*
* Takes argumants from the signal and decides which object need to be removed
* then calls relevant remove function in the library
*
* @param uniqueData ISBN of the Book or user ID
* @return none
*/
void MainWindow::getDialogInputs(const long long int &uniqueData, const char& selection){
    if(selection == BOOK_SELECTION){
        Book* temp = m_library->checkBook(uniqueData);
        if(temp){
            m_library->remove(temp);
            ui->infoTextBrowser->append("The book removed from the database!");
        }
        else
            ui->infoTextBrowser->append("Error: Could not find such book in the library");
    }
    else if(selection == USER_SELECTION){
        Person* temp = m_library->checkPerson(uniqueData);
        if(temp){
            m_library->remove(temp);
            ui->infoTextBrowser->append("The user removed from the database!");
        }
        else
            ui->infoTextBrowser->append("Error: Could not find such user in the system");
    }
    else
        ui->infoTextBrowser->append("Error: Invalid input, please be sure that input only contains digits");
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
    this->close();
}

/**
* @brief Slot method to handle click action on filterClearButton
*
* Basicly, calls destructor to save latest status and exit
*
* @param none
* @return none
*/
void MainWindow::filterClearButtonClicked(){
    ui->filterLineEdit->clear();
    filterLineEditUpdated("");
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
        if((ui->bookTableWidget->item(row, availabilityColumn)->text() == TABLE_BOOK_AVAILABLE)){ // book is free
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
        if(bookTitle == TABLE_NO_TAKEN_BOOK){   // person can take
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
            returnBookTitleLineEditCompleterClicked(bookTitle);    // set ISBN for return action
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
void MainWindow::bookTitleLineEditUpdated(const QString& title){
    QList temp = ui->bookTableWidget->findItems(title, Qt::MatchFixedString);
    if(temp.size() == 0 && ui->returnBookTitleLineEdit->text() == title)      // no match with title
        ui->returnISBN->setText(NOT_VALID_INPUT_ISBN);
    else if(temp.size() == 0 && ui->checkOutBookTitleLineEdit->text() == title)
        ui->checkOutISBN->setText(NOT_VALID_INPUT_ISBN);
    else if(temp.size() != 0 && ui->returnBookTitleLineEdit->text() == title) // matches
        ui->returnISBN->setText(ui->bookTableWidget->item(ui->bookTableWidget->row(temp[0]), ISBNColumn)->text());
    else
        ui->checkOutISBN->setText(ui->bookTableWidget->item(ui->bookTableWidget->row(temp[0]), ISBNColumn)->text());
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
    if(temp.size() == 0){       // no match with title
        ui->checkOutID->setText(NOT_VALID_INPUT_ID);
    }
    else{                       // matches
        int row = ui->personTableWidget->row(temp[0]);    // take first element since all books are unique
        ui->checkOutID->setText(ui->personTableWidget->item(row, IDColumn)->text());
    }
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

/**
* @brief Manages whether check out and return buttons to be enabled or disabled
*
* Each time user inputs something, checks if ISBN and ID labels are valid or not.
* Then sets relevant buttons enable or disable.
*
* @param none
* @return none
*/
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

void MainWindow::currentTabChanged(const int &index){
    ui->filterLineEdit->clear();
    filterLineEditUpdated("");
    if(index == personTable)
        ui->filterLabel->setText("Filter Names:");
    else if(index == bookTable)
        ui->filterLabel->setText("Filter Titles:");
}

/**
* @brief Deallocates allocated memory for table items
*
* Iterates through all items in the table, and deletes
*
* @param table Table need to be deallocated
* @return none
*/
void MainWindow::freeTableMemory(QTableWidget* table){
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            delete table->item(row, col);
        }
    }
}

/**
* @brief Filters rows that contains to user input
*
* Iterates through all items in the table, and hides or unhides
*
* @param table Table need to be filtered
* @param filter user input from line edits
* @return none
*/
void MainWindow::filterTable(QTableWidget *table, const QString& filter){
    for(int row=0; row < table->rowCount(); ++row)
    {
        bool match = false;
        QTableWidgetItem *item = table->item(row, titleColumn);   // or nameColumn, nothing matters
        if(item->text().contains(filter, Qt::CaseInsensitive)){
            match = true;
        }
        table->setRowHidden(row, !match);
    }
}

void MainWindow::filterLineEditUpdated(const QString& filter){
    if(ui->tabWidget->currentIndex() == personTable)
        filterTable(ui->personTableWidget, filter);
    else if(ui->tabWidget->currentIndex() == bookTable)
        filterTable(ui->bookTableWidget, filter);
}

