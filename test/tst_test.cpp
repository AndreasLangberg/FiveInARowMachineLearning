#include <QtTest>
#include <QLineEdit>
#include "tst_test.h"
#include "boardsquare.h"

void Test::test_gui()
{
    QTest::mouseClick(mainWindow.m_squareList.at(1).at(1), Qt::LeftButton);
    QCOMPARE(mainWindow.m_squareList.at(1).at(1)->m_label->text(), "X");
}

void Test::test_restart()
{
    mainWindow.restartBoard();
    QCOMPARE(mainWindow.m_squareList.at(1).at(1)->m_label->text(), "");
}

void Test::test_bot()
{
    mainWindow.first = true;
    mainWindow.receiveTimer();
    mainWindow.receiveTimer();
    int X = 0;
    int O = 0;
    for(int x = 0; x < mainWindow.m_squareList.length(); x++)
    {
        for(int y = 0; y < mainWindow.m_squareList.at(x).length(); y++)
        {
            if(mainWindow.m_squareList.at(x).at(y)->m_label->text() == "X")
                X++;
            else if(mainWindow.m_squareList.at(x).at(y)->m_label->text() == "O")
                O++;
        }
    }

    QCOMPARE(X+O, 2);
}
