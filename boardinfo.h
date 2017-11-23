#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QList>
#include <QMap>
#include "boardstateprobability.h"

class BoardInfo : public QObject
{
    Q_OBJECT
public:
    explicit BoardInfo(int boardSize);
    void addState(int x, int y, int state);
    QString printState();
    int checkState(int x, int y);
    QString findBiggestProbability(bool first);
    bool checkForWinner();
    void registerWinner(bool first);
    int m_probStateCounterSecond = 0;
    int m_probStateCounterFirst = 0;

private:
    QList<QList<int>> boardState;
    int m_boardSize;
    QMap<int, BoardStateProbability*> m_probStateListFirst;
    QMap<int, BoardStateProbability*> m_probStateListSecond;


signals:

public slots:
};

#endif // BOARD_H
