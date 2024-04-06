#ifndef REMOVEDIALOG_HPP
#define REMOVEDIALOG_HPP

#include <QDialog>

#define INVALID_INPUT 0

namespace Ui {
class RemoveDialog;
}

class RemoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveDialog(QWidget *parent = nullptr);
    ~RemoveDialog();

signals:
    void userInputReady(const long long int &uniqueData);

private slots:
    void deleteButtonClicked();
    void cancelButtonClicked();
    void selectionToggled();

private:
    Ui::RemoveDialog *ui;
};

#endif // REMOVEDIALOG_HPP
