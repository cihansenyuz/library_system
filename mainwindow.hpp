#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "library.hpp"
#include "item.hpp"
#include "book.hpp"
#include "person.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createBookTable(Library&);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
