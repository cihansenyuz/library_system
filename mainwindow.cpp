#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Library *l)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), lib(l)
{
    ui->setupUi(this);

    // signal-slot connections
    connect(ui->summaryButton, &QPushButton::clicked, this, &MainWindow::summaryButtonClicked);

    // creation of book table
    createBookTable();
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
void MainWindow::createBookTable(){

    // create the table
    ui->bookTableWidget->setRowCount(lib->getBookList()->size());
    ui->bookTableWidget->setColumnCount(4);

    // set labels
    QStringList labels;
    labels << "Title" << "Author" << "ISBN" << "Availability";
    ui->bookTableWidget->setHorizontalHeaderLabels(labels);

    // create items and add them into the table
    QTableWidgetItem *item;
    for (int row = 0; row < 4; row++)
    {
        item = new QTableWidgetItem(QString::fromStdString(lib->getBookList()->at(row).getTitle()));
        ui->bookTableWidget->setItem(row, 0, item);

        item = new QTableWidgetItem(QString::fromStdString(lib->getBookList()->at(row).getAuthor()));
        ui->bookTableWidget->setItem(row, 1, item);

        item = new QTableWidgetItem(QString::number(lib->getBookList()->at(row).getISBN()));
        ui->bookTableWidget->setItem(row, 2, item);

        if(lib->getBookList()->at(row).isAvailable())
            item = new QTableWidgetItem("Free");
        else
            item = new QTableWidgetItem("Already Booked");
        item->setTextAlignment(Qt::AlignHCenter);
        ui->bookTableWidget->setItem(row, 3, item);
    }
    ui->bookTableWidget->resizeColumnsToContents();
}

void MainWindow::summaryButtonClicked()
{
    ui->infoTextBrowser->append("deneme");

}
