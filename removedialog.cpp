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

void RemoveDialog::cancelButtonClicked(){
    this->close();
}

void RemoveDialog::selectionToggled(){
    if(ui->bookRadioButton->isChecked())
        ui->selectionLabel->setText("ISBN");
    else
        ui->selectionLabel->setText("ID     ");
}
