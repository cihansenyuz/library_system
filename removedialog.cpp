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
    QString temp = ui->selectionLineEdit->text();
    long long int uniqueData;

    if(temp == "")
        uniqueData = INVALID_INPUT;
    else
        uniqueData = std::stoll(temp.toStdString());

    if(uniqueData)
        emit userInputReady(uniqueData);
    else
        emit userInputReady(INVALID_INPUT);

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
