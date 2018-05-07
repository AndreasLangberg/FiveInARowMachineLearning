#ifndef TST_TEST_H
#define TST_TEST_H

#include "mainwindow.h"

class Test : public QObject
{
    Q_OBJECT

private slots:
    void test_gui();
    void test_restart();
    void test_bot();

private:
    MainWindow mainWindow;
};

#endif // TST_TEST_H
