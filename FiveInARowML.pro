#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T16:59:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FiveInARowML
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    boardstateprobability.cpp \
    lookup.cpp \
    boardsquare.cpp \
    boardinfo.cpp

HEADERS += \
        mainwindow.h \
    boardstateprobability.h \
    lookup.h \
    boardsquare.h \
    boardinfo.h

FORMS += \
        mainwindow.ui

test {
    message(Test build)

    QT += testlib
    TARGET = FIAR-test
    SOURCES -= main.cpp #Remove old main.cpp

    #Add new main.cpp (With different name to remove confusion for the compiler), and the test files themselves.
    HEADERS  += \
        test/tst_test.h

    SOURCES += \
        test/tst_main.cpp \
        test/tst_test.cpp
} else {
    message(Normal build)
}
