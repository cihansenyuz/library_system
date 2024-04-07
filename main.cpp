#include "main.hpp"

int main(int argc, char *argv[])
{
    Library lib(BOOK_DATA_FILE_PATH, PERSON_DATA_FILE_PATH);
    QApplication a(argc, argv);
    MainWindow w(nullptr, &lib, PROGRAM_VERSION);
    w.show();
    return a.exec();
}
