#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Library *lib)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), library(lib)
{
    ui->setupUi(this);

    // signal-slot connections
    connect(ui->summaryButton, &QPushButton::clicked, this, &MainWindow::summaryButtonClicked);
    connect(ui->checkOutButton, &QPushButton::clicked, this, &MainWindow::checkOutButtonClicked);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::returnButtonClicked);
    connect(ui->switchButton, &QPushButton::clicked, this, &MainWindow::switchButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearButtonClickled);

    // init the table
    updateBookTable();
}

MainWindow::~MainWindow()
{
    library->saveLatestData();
    delete ui;
}

/**
 * @brief Updates content in tableWidget
 *
 * Gets book's contents from Library object. Creates and add items in the tableWidget
 * */
void MainWindow::updateBookTable(){
    // create the table
    unsigned int rowCount = library->getBookList()->size();
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(BOOK_DATA_COLUMN_COUNT);

    // set labels
    QStringList labels;
    labels << "Title" << "Author" << "ISBN" << "Availability";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (unsigned int row = 0; row < rowCount; row++)
    {
        item = new QTableWidgetItem(QString::fromStdString(library->getBookList()->at(row).getTitle()));
        ui->tableWidget->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::fromStdString(library->getBookList()->at(row).getAuthor()));
        ui->tableWidget->setItem(row, 1, item);

        item = new QTableWidgetItem(QString::number(library->getBookList()->at(row).getISBN()));
        ui->tableWidget->setItem(row, 2, item);

        if(library->getBookList()->at(row).isAvailable())
            item = new QTableWidgetItem("Free");
        else
            item = new QTableWidgetItem("Already Booked");
        item->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->setItem(row, 3, item);
    }
    ui->tableWidget->resizeColumnsToContents();
    this->currentTable = 0;
}

/**
 * @brief Updates content in tableWidget
 *
 * Gets user's contents from Library object. Creates and add items in the tableWidget
 * */
void MainWindow::updatePersonTable(){
    // create the table
    unsigned int rowCount = library->getPersonList()->size();
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(PERSON_DATA_COLUMN_COUNT);

    // set labels
    QStringList labels;
    labels << "Name" << "ID" << "Taken Book";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (unsigned int row = 0; row < rowCount; row++)
    {
        item = new QTableWidgetItem(QString::fromStdString(library->getPersonList()->at(row).getName()));
        ui->tableWidget->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::fromStdString(std::to_string(library->getPersonList()->at(row).getId())));
        ui->tableWidget->setItem(row, 1, item);


        if(library->getPersonList()->at(row).getTakenBook())
            item = new QTableWidgetItem(QString::fromStdString(library->getPersonList()->at(row).getTakenBook()->getTitle()));
        else
            item = new QTableWidgetItem(" - ");
        item->setTextAlignment(Qt::AlignHCenter);
        ui->tableWidget->setItem(row, 2, item);
    }
    ui->tableWidget->resizeColumnsToContents();
    this->currentTable = 1;
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
* Gets texts on editLines, and passes it to Library::checkOut function.
*
* @param none
* @return none
*/
void MainWindow::checkOutButtonClicked(){
    QString result;
    result = this->library->checkOut(ui->checkOutPersonNameLineEdit->text().toStdString(),
                            ui->checkOutBookTitleLineEdit->text().toStdString());
    ui->checkOutBookTitleLineEdit->clear();
    ui->checkOutPersonNameLineEdit->clear();
    ui->infoTextBrowser->append(result);
    updateBookTable();
}

/**
* @brief Slot method to handle click action on returnButton
*
* Gets the text on editLine, and passes it to Library::returnBook function.
*
* @param none
* @return none
*/
void MainWindow::returnButtonClicked(){
    QString result;
    result = this->library->returnBook(ui->returnBookTitleLineEdit->text().toStdString());
    ui->returnBookTitleLineEdit->clear();
    ui->infoTextBrowser->append(result);
    updateBookTable();
}

/**
* @brief Slot method to handle click action on switchButton
*
* Calls updatePersonTable function to recreate the table.
*
* @param none
* @return none
*/
void MainWindow::switchButtonClicked(){
    if(this->currentTable)
        this->updateBookTable();
    else
        this->updatePersonTable();
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
