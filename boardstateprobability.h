#ifndef BOARDSTATEPROBABILITY_H
#define BOARDSTATEPROBABILITY_H

#include <QObject>
#include <QList>
#include "lookup.h"

class BoardStateProbability : public QObject
{
    Q_OBJECT

public:
    BoardStateProbability(QString printID, QList<QList<int>> boardState, bool starter);
    QString returnStatePrint();
    QString getPlaySquare();
    void saveWinningMove();
    void saveWinningSeries();
    void saveLosingMove();
    void saveLosingSeries();

private:
    QString m_printID;
    QList<QList<double>> m_stateProb;
    QString getRandomFromList(QHash<QString, double> hitList);
    QString m_playedSquare;
    int availableSpaces;
    bool m_starter;

};

#endif // BOARDSTATEPROBABILITY_H
