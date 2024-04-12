#ifndef ADDDIALOG_HPP
#define ADDDIALOG_HPP

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

signals:
    void userInputReady(const std::string &title,
                        const std::string &author,
                        const long long &ISBN);

private slots:
    void addButtonClicked();
    void cancelButtonClicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_HPP
