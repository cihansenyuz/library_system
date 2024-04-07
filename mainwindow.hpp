#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QCompleter>
#include "library.hpp"
#include "item.hpp"
#include "book.hpp"
#include "person.hpp"
#include "registerdialog.hpp"
#include "adddialog.hpp"
#include "removedialog.hpp"

#define BOOK_DATA_COLUMN_COUNT 4
#define PERSON_DATA_COLUMN_COUNT 3

typedef enum bookColumns{   // enum for column labels of book table
    titleColumn, authorColumn, ISBNColumn, availabilityColumn  
}bookColumns;

typedef enum personColumns{ // enum for column labels of user table
    nameColumn, IDColumn, takenBookColumn  
}personColumns;

#define MAX_POSSIBLE_ID 99999999    // user ID must be 8 digits
#define NO_ITEM -1                  // no item found

// strings for line edit labels
#define NOT_VALID_INPUT_ISBN "xxxxxxxxxxxxxx"
#define NOT_VALID_INPUT_ID "xxxxxxxx"

// strings for tables
#define NO_TAKEN_BOOK " - "
#define BOOK_AVAILABLE "Free"
#define BOOK_NOT_AVAILABLE "Already Booked"

typedef enum tableType{
    bookTable, personTable  // enum to track which list is visible at the moment
}tableType;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Library *lib = nullptr, QString pv = "Library System");
    ~MainWindow();
private slots:
    // button slots
    void summaryButtonClicked();
    void checkOutButtonClicked();
    void returnButtonClicked();
    void switchButtonClicked();
    void clearButtonClickled();
    void registerButtonClicked();
    void addButtonClicked();
    void removeButtonClicked();
    void exitButtonClicked();

    // dialog window slots
    void getRegisterInput(const string &name, const int &id);
    void getAddInput(const string &tit, const string &ath, const long long &isbn);
    void getRemoveInput(const long long int &uniqueData);

    // line edit slots
    void returnBookTitleLineEditUpdated(const QString& title);
    void returnBookTitleLineEditCompleterClicked(const QString &title);
    void checkOutBookTitleLineEditUpdated(const QString& title);
    void checkOutBookTitleLineEditCompleterClicked(const QString &title);
    void checkOutPersonTitleLineEditUpdated(const QString& name);
    void checkOutPersonTitleLineEditCompleterClicked(const QString &name);

    // others
    void tableItemSelected(const int &row, const int &column);
    void newUserInput();
private:
    Ui::MainWindow *ui;
    Library *library;
    QString programVersion;
    QStringList bookTitleCompletions;
    QStringList personNameCompletions;
    QCompleter *returnBookCompleter;
    QCompleter *checkOutBookCompleter;
    QCompleter *personCompleter;
    tableType currentTable;

    void updateBookTable();
    void updatePersonTable();
    void createDialog();
    void updateTables();
};
#endif // MAINWINDOW_HPP
