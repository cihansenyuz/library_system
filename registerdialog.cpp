#include "registerdialog.hpp"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    // signal-slot connections
    connect(ui->registerButton, &QPushButton::clicked, this, &RegisterDialog::registerButtonClicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

/**
* @brief Slot method to handle click action on registerButton
*
* Gets user inpuıs from lineEdits and emits signal for MainWindow to catch
*
* @param none
* @return none
*/
void RegisterDialog::registerButtonClicked(){
    std::string name = ui->nameLineEdit->text().toStdString();
    int id = std::stoi(ui->IDLineEdit->text().toStdString());
    emit userInputReady(name, id);
}
