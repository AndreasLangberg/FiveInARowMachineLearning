#include "boardstateprobability.h"
#include <QHash>
#include <cstdlib>
#include <QHashIterator>
#include <QDebug>

BoardStateProbability::BoardStateProbability(QString printID, QList<QList<int>> boardState, bool starter)
{
    m_starter = starter;
    m_printID = printID;

    bool ok;
    m_stateProb = Lookup::findBoardProb(printID, m_starter, &ok);
    if(!ok)
    {
        availableSpaces = 0;
        for(int i = 0; i < 2; i++)
        {
            for(int x = 0; x < boardState.length(); x++)
            {
                QList<double> yState;
                for(int y = 0; y < boardState.at(x).length(); y++)
                {
                    if(i == 0 && boardState.at(x).at(y) == 0)
                        availableSpaces++;
                    else if(i == 1)
                    {
                        if(boardState.at(x).at(y) == 0)
                            yState.append((double)1/availableSpaces);
                        else
                            yState.append(0);
                    }
                }
                if(i == 1)
                    m_stateProb.append(yState);
            }
        }
    }
}

QString BoardStateProbability::returnStatePrint()
{
    return m_printID;
}

QString BoardStateProbability::getPlaySquare()
{
    QHash<QString, double> fullList;
    for(int x = 0; x < m_stateProb.length(); x++)
    {
        for(int y = 0; y < m_stateProb.at(x).length(); y++)
        {
            QString id = QString::number(x) + ":" + QString::number(y);
            fullList.insert(id, m_stateProb.at(x).at(y));
        }
    }
    m_playedSquare = getRandomFromList(fullList);
    return m_playedSquare;
}

QString BoardStateProbability::getRandomFromList(QHash<QString, double> hitList)
{
    while(1)
    {
        QHash<QString, double> newList;
        QHashIterator<QString, double> i(hitList);
        while (i.hasNext())
        {
            i.next();
            if(i.value() > 0)
            {
                int random = rand() % 101;
                if(random != 0)
                {
                    double ranProb = random/100;
                    if(ranProb < i.value())
                    {
                        newList.insert(i.key(), i.value());
                    }
                }
            }
        }
        if(newList.size() == 1)
            return newList.keys().at(0);
        else if(newList.size() > 1)
            return getRandomFromList(newList);
    }
}

void BoardStateProbability::saveWinningMove()
{
    QStringList xy = m_playedSquare.split(":");
    int x = xy.at(0).toInt();
    int y = xy.at(1).toInt();

    m_stateProb[x].insert(y, 100.0);
    bool ok;
    Lookup::saveBoardProb(m_printID, m_stateProb, m_starter, &ok);
    if(!ok)
        qDebug() << "Unable to save to file!";
}
void BoardStateProbability::saveWinningSeries()
{
    QStringList xy = m_playedSquare.split(":");
    int x = xy.at(0).toInt();
    int y = xy.at(1).toInt();

    if(m_stateProb.at(x).at(y) < 100)
        m_stateProb[x].insert(y, m_stateProb.at(x).at(y)+(((double)1/availableSpaces)*5));
    bool ok;
    Lookup::saveBoardProb(m_printID, m_stateProb, m_starter, &ok);
    if(!ok)
        qDebug() << "Unable to save to file!";
}
void BoardStateProbability::saveLosingMove()
{
    QStringList xy = m_playedSquare.split(":");
    int x = xy.at(0).toInt();
    int y = xy.at(1).toInt();
    bool ok;
    m_stateProb[x].insert(y, 0);
    Lookup::saveBoardProb(m_printID, m_stateProb, m_starter, &ok);

    if(!ok)
        qDebug() << "Unable to save to file!";
}
void BoardStateProbability::saveLosingSeries()
{
    QStringList xy = m_playedSquare.split(":");
    int x = xy.at(0).toInt();
    int y = xy.at(1).toInt();

    if(m_stateProb.at(x).at(y) > 0)
    {
        if(m_stateProb.at(x).at(y)-(((double)1/availableSpaces)*2) <= 0)
            m_stateProb[x].insert(y, m_stateProb.at(x).at(y)/2);
        else
            m_stateProb[x].insert(y, m_stateProb.at(x).at(y)-(((double)1/availableSpaces)*2));
    }
    bool ok;
    Lookup::saveBoardProb(m_printID, m_stateProb, m_starter, &ok);
    if(!ok)
        qDebug() << "Unable to save to file!";
}
