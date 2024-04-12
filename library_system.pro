QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddialog.cpp \
    book.cpp \
    item.cpp \
    library.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    registerdialog.cpp \
    removedialog.cpp

HEADERS += \
    adddialog.hpp \
    book.hpp \
    item.hpp \
    library.hpp \
    main.hpp \
    mainwindow.hpp \
    person.hpp \
    registerdialog.hpp \
    removedialog.hpp

FORMS += \
    adddialog.ui \
    mainwindow.ui \
    registerdialog.ui \
    removedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    book_data.txt \
    person_data.txt
