#include "removedialog.hpp"
#include "ui_removedialog.h"

RemoveDialog::RemoveDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveDialog)
{
    ui->setupUi(this);

    // signal-slot connections
    connect(ui->deleteButton, &QPushButton::clicked, this, &RemoveDialog::deleteButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &RemoveDialog::cancelButtonClicked);
    connect(ui->bookRadioButton, &QRadioButton::toggled, this, &RemoveDialog::selectionToggled);
}

RemoveDialog::~RemoveDialog()
{
    delete ui;
}

/**
* @brief Slot method to handle click action on deleteButton
*
* Gets user inpuıs from lineEdit and emits signal for MainWindow to catch
*
* @param none
* @return none
*/
void RemoveDialog::deleteButtonClicked(){
    QString strData = ui->selectionLineEdit->text();
    long long int uniqueData = 0;

    // check if the input is digit
    try{
        uniqueData = std::stoll(strData.toStdString());
    }
    catch (const std::invalid_argument& e) {
        emit userInputReady(uniqueData, INVALID_INPUT);
        this->close();
        return;
    }

    // since input is digit, emit relevant signal
    if(ui->bookRadioButton->isChecked())    // check which radio button is clicked
        emit userInputReady(uniqueData, BOOK_SELECTION);
    else
        emit userInputReady(uniqueData, USER_SELECTION);
    this->close();
}

/**
* @brief Slot method to handle click action on cancelButton
*
* Closes the dialog box without any action
*
* @param none
* @return none
*/
void RemoveDialog::cancelButtonClicked(){
    this->close();
}

/**
* @brief Slot method to handle selection on radioButtons
*
* Edits relevant labels on the window upon selection change
*
* @param none
* @return none
*/
void RemoveDialog::selectionToggled(){
    if(ui->bookRadioButton->isChecked())
        ui->selectionLabel->setText("ISBN");
    else
        ui->selectionLabel->setText("ID     ");
}
