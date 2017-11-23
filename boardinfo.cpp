#include "boardinfo.h"
#include <QDebug>

BoardInfo::BoardInfo(int boardSize)
{
    m_boardSize = boardSize;
    for(int x = 0; x < boardSize; x++)
    {
        QList<int> yState;
        for(int y = 0; y < boardSize; y++)
        {
            yState.append(0);
        }
        boardState.append(yState);
    }
}

void BoardInfo::addState(int x, int y, int state) //State 0 = empty. State 1 = player 1. State 2 = player 2;
{
    boardState[x].replace(y, state);
}

int BoardInfo::checkState(int x, int y)
{
    return boardState.at(x).at(y);
}

QString BoardInfo::printState()
{
    QString print;
    for(int x = 0; x < m_boardSize; x++)
    {
        for(int y = 0; y < m_boardSize; y++)
        {
            print += QString::number(boardState.at(x).at(y)) + ":";
        }
    }
    return print;
}

QString BoardInfo::findBiggestProbability(bool first)
{
    if(first)
    {
        BoardStateProbability *BSP = new BoardStateProbability(printState(), boardState, true);
        m_probStateListFirst.insert(m_probStateCounterFirst, BSP);
        m_probStateCounterFirst++;
        return BSP->getPlaySquare();
    }
    else
    {
        BoardStateProbability *BSP = new BoardStateProbability(printState(), boardState, false);
        m_probStateListSecond.insert(m_probStateCounterSecond, BSP);
        m_probStateCounterSecond++;
        return BSP->getPlaySquare();
    }
}

void BoardInfo::registerWinner(bool first)
{
    if(first)
    {
        QMapIterator<int, BoardStateProbability*> i(m_probStateListFirst);
        while (i.hasNext())
        {
            i.next();
            if(!i.hasNext())
                i.value()->saveWinningMove();
            else
                i.value()->saveWinningSeries();
        }

        QMapIterator<int, BoardStateProbability*> j(m_probStateListSecond);
        while (j.hasNext())
        {
            j.next();
            if(!j.hasNext())
                j.value()->saveLosingMove();
            else
                j.value()->saveLosingSeries();
        }
    }
    else
    {
        QMapIterator<int, BoardStateProbability*> i(m_probStateListSecond);
        while (i.hasNext())
        {
            i.next();
            if(!i.hasNext())
                i.value()->saveWinningMove();
            else
                i.value()->saveWinningSeries();
        }

        QMapIterator<int, BoardStateProbability*> j(m_probStateListFirst);
        while (j.hasNext())
        {
            j.next();
            if(!j.hasNext())
                j.value()->saveLosingMove();
            else
                j.value()->saveLosingSeries();
        }
    }
}

bool BoardInfo::checkForWinner()
{
    QHash<int, int> xCounter;
    for(int x = 0; x < boardState.length(); x++)
    {
        int yCounter = 0;
        for(int y = 0; y < boardState.at(x).length(); y++)
        {
            if(y > 0)
            {
                if(boardState.at(x).at(y) == boardState.at(x).at(y-1) && boardState.at(x).at(y) != 0)
                    yCounter++;
                else
                    yCounter = 0;
                if(yCounter >= 4)
                    return true;
            }

            if(x > 0)
            {
                if(boardState.at(x).at(y) == boardState.at(x-1).at(y) && boardState.at(x).at(y) != 0)
                    xCounter.insert(y, xCounter.value(y, 0)+1);
                else
                    xCounter.insert(y, 0);
                if(xCounter.value(y, 0) >= 4)
                    return true;
            }

            if(x-4 >= 0 && y-4 >= 0)
            {
                if(boardState.at(x).at(y) == boardState.at(x-1).at(y-1) &&
                        boardState.at(x).at(y) == boardState.at(x-2).at(y-2) &&
                        boardState.at(x).at(y) == boardState.at(x-3).at(y-3) &&
                        boardState.at(x).at(y) == boardState.at(x-4).at(y-4) &&
                        boardState.at(x).at(y) != 0)
                        return true;
            }

            if(x-4 >= 0  && y+5 <= boardState.at(x).length())
                if(boardState.at(x).at(y) == boardState.at(x-1).at(y+1) &&
                        boardState.at(x).at(y) == boardState.at(x-2).at(y+2) &&
                        boardState.at(x).at(y) == boardState.at(x-3).at(y+3) &&
                        boardState.at(x).at(y) == boardState.at(x-4).at(y+4) &&
                        boardState.at(x).at(y) != 0)
                        return true;
        }
    }
    return false;
}

