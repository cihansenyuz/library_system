#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "library.hpp"
#include "item.hpp"
#include "book.hpp"
#include "person.hpp"

#define BOOK_DATA_COLUMN_COUNT 4
#define PERSON_DATA_COLUMN_COUNT 3

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Library *lib = nullptr);
    ~MainWindow();
    void updateBookTable();
    void updatePersonTable();
    int currentTable; // 0: Book, 1: Person
private slots:
    void summaryButtonClicked();
    void checkOutButtonClicked();
    void returnButtonClicked();
    void switchButtonClicked();
    void clearButtonClickled();
private:
    Ui::MainWindow *ui;
    Library *library;
};
#endif // MAINWINDOW_HPP
