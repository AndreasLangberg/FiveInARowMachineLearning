#ifndef LOOKUP_H
#define LOOKUP_H

#include <QList>
#include <QFile>

class Lookup
{
public:
    static QList<QList<double>> findBoardProb(QString printID, bool starter, bool *ok);
    static void saveBoardProb(QString printId, QList<QList<double>> inVal, bool starter, bool *ok);
};

#endif // LOOKUP_H
