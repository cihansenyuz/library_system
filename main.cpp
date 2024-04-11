#include "main.hpp"

int main(int argc, char *argv[])
{
    unique_ptr<Library> lib = make_unique<Library>(BOOK_DATA_FILE_PATH, PERSON_DATA_FILE_PATH);
    QApplication a(argc, argv);
    MainWindow w(nullptr, std::move(lib), PROGRAM_VERSION);
    w.show();
    return a.exec();
}
