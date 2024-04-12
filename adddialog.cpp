#include "adddialog.hpp"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    // signal-slot connections
    connect(ui->addButton, &QPushButton::clicked, this, &AddDialog::addButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddDialog::cancelButtonClicked);
}

AddDialog::~AddDialog()
{
    delete ui;
}

/**
* @brief Slot method to handle click action on addButton
*
* Gets user inpuıs from lineEdits and emits signal for MainWindow to catch
*
* @param none
* @return none
*/
void AddDialog::addButtonClicked(){
    std::string title = ui->titleLineEdit->text().toStdString();
    std::string author = ui->authorLineEdit->text().toStdString();
    long long int ISBN = std::stoll(ui->ISBNLineEdit->text().toStdString());
    emit userInputReady(title, author, ISBN);
    if(!ui->multipleCheckBox->isChecked())
        this->close();
    ui->titleLineEdit->clear();
    ui->authorLineEdit->clear();
    ui->ISBNLineEdit->clear();
}

/**
* @brief Slot method to handle click action on cancelButton
*
* Closes the dialog box without any action
*
* @param none
* @return none
*/
void AddDialog::cancelButtonClicked(){
    this->close();
}
