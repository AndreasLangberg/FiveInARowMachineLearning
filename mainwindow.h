#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "boardsquare.h"
#include "boardinfo.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class Test;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setupBoard(int boardSize);
    void restartBoard();

    QList<QList<BoardSquare*>> m_squareList;
    BoardInfo *m_boardState;
    bool first = true;
    QWidget *mainBoard;

public slots:
    void receiveSquareState(int x, int y);
    void receiveTimer();

signals:
};

#endif // MAINWINDOW_H
