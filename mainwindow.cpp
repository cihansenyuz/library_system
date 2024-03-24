#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * Below this section must have a funtion that reads from local Books and Persons
     * Codes from terminal version does not work, needs reimplamentation
     * */
    // creation of books
    Book b1("Kurk Mantolu Madonna", "Sabahattin Ali", 9789753638029);
    Book b2("Seker Portakali", "Jose Mauro De Vasconcelos", 9789750738609);
    Book b3("1984", "George Orwell", 9789750718533);
    Book b4("Kirmizi Pazartesi", "Gabriel Garcia Marquez", 9789750721571);

    // push them into a vector to give it to library
    vector<Book>* newBookList = new vector<Book>;
    newBookList->push_back(b1);
    newBookList->push_back(b2);
    newBookList->push_back(b3);
    newBookList->push_back(b4);

    // creation of book users
    Person p1("Cihan Senyuz", 26007567);
    Person p2("Can Gorkem Gunes", 26100010);

    // push them into a vector to give it to library
    vector<Person>* newPersonList = new vector<Person>;
    newPersonList->push_back(p1);
    newPersonList->push_back(p2);

    // below is debug purposed
    //auto it = newPersonList->find(p2);
    //it->displayInfo();

    // creation of a library
    Library lib(newBookList);
    lib.setPersonList(newPersonList);

    // creation of book table
    createBookTable(lib);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief Initializes bookTableWidget
 *
 * @param lib Library object whose bookList will be listed in the bookTableWidget
 * */
void MainWindow::createBookTable(Library& lib){

    // create the table
    ui->bookTableWidget->setRowCount(lib.getBookList()->size());
    ui->bookTableWidget->setColumnCount(4);

    // set labels
    QStringList labels;
    labels << "Title" << "Author" << "ISBN" << "Availability";
    ui->bookTableWidget->setHorizontalHeaderLabels(labels);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (int row = 0; row < 4; row++)
    {
        item = new QTableWidgetItem(QString::fromStdString(lib.getBookList()->at(row).getTitle()));
        ui->bookTableWidget->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::fromStdString(lib.getBookList()->at(row).getAuthor()));
        ui->bookTableWidget->setItem(row, 1, item);

        item = new QTableWidgetItem(QString::number(lib.getBookList()->at(row).getISBN()));
        ui->bookTableWidget->setItem(row, 2, item);

        if(lib.getBookList()->at(row).isAvailable())
            item = new QTableWidgetItem("Free");
        else
            item = new QTableWidgetItem("Already Booked");
        item->setTextAlignment(Qt::AlignHCenter);
        ui->bookTableWidget->setItem(row, 3, item);
    }
    ui->bookTableWidget->resizeColumnsToContents();
}
