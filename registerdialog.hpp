#ifndef REGISTERDIALOG_HPP
#define REGISTERDIALOG_HPP

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

signals:
    void userInputReady(const std::string &name, const int &ID);

private slots:
    void registerButtonClicked();
    void cancelButtonClicked();

private:
    Ui::RegisterDialog *ui;

};

#endif // REGISTERDIALOG_HPP
