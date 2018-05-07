#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define HUMAN true

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_boardState = new BoardInfo(20);
    setupBoard(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBoard(int boardSize)
{
    QHBoxLayout *xLayout = new QHBoxLayout();
    xLayout->setSpacing(0);
    xLayout->setMargin(0);
    for(int x = 0; x < boardSize; x++)
    {
        QVBoxLayout *yLayout = new QVBoxLayout();
        yLayout->setSpacing(0);
        yLayout->setMargin(0);
        QList<BoardSquare*> yList;
        for(int y = 0; y < boardSize; y++)
        {
            BoardSquare *square = new BoardSquare(x,y,this);
            yLayout->addWidget(square);
            connect(square, &BoardSquare::sendClickedEvent, this, &MainWindow::receiveSquareState);
            yList.append(square);
        }
        xLayout->addLayout(yLayout);
        m_squareList.append(yList);
    }

    mainBoard = new QWidget();
    mainBoard->setLayout(xLayout);

    ui->verticalLayout_main->addWidget(mainBoard);
    if(!HUMAN)
    {
        QTimer::singleShot(1, this, SLOT(receiveTimer()));
    }
}

void MainWindow::receiveSquareState(int x, int y)
{
    m_boardState->addState(x, y, 1);
    if(m_boardState->checkForWinner())
    {
        m_boardState->registerWinner(true);
        qDebug() << "Player 1 wins!";
        restartBoard();
    }
    else
    {
        QStringList placement = m_boardState->findBiggestProbability(false).split(":");
        m_boardState->addState(placement.at(0).toInt(), placement.at(1).toInt(), 2);
        m_squareList.at(placement.at(0).toInt()).at(placement.at(1).toInt())->receiveChangeState(2);
        if(m_boardState->checkForWinner())
        {
            m_boardState->registerWinner(false);
            qDebug() << "Player 2 wins!";
            restartBoard();
        }
    }
}

void MainWindow::receiveTimer()
{
    QStringList placement = m_boardState->findBiggestProbability(first).split(":");
    m_boardState->addState(placement.at(0).toInt(), placement.at(1).toInt(), first ? 1 : 2);
    m_squareList.at(placement.at(0).toInt()).at(placement.at(1).toInt())->receiveChangeState(first ? 1 : 2);
    if(m_boardState->checkForWinner())
    {
        m_boardState->registerWinner(first);
        qDebug() << "Player " + QString::number(first ? 1 : 2) + " won after playing " + QString::number(m_boardState->m_probStateCounterFirst) + " moves";
        restartBoard();
    }
    else
    {
        first = !first;
        QTimer::singleShot(1, this, SLOT(receiveTimer()));
    }
}

void MainWindow::restartBoard()
{
    delete m_boardState;
    delete mainBoard;
    m_squareList.clear();
    first = true;

    m_boardState = new BoardInfo(20);
    setupBoard(20);
}
