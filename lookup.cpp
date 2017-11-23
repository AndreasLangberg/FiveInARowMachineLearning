#include "lookup.h"
#include <QTextStream>

QList<QList<double>> Lookup::findBoardProb(QString printID, bool starter, bool *ok)
{
    QList<QList<double>> retVal;
    QString filename;
    if(starter)
        filename = "StoredDataFirst.txt";
    else
        filename = "StoredDataSecond.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        *ok = false;
        return retVal;
    }
    while(!file.atEnd())
    {
        QString line = QString::fromUtf8(file.readLine());
        QStringList split = line.split("#");
        if(split.at(0) == printID)
        {
            QStringList xLine = split.at(1).split("-");
            for(int x = 0; x < xLine.length(); x++)
            {
                QStringList yLine = xLine.at(x).split(":");
                QList<double> yLineVal;
                for(int y = 0; y < yLine.length(); y++)
                {
                    yLineVal.append(yLine.at(y).toDouble());
                }
                retVal.append(yLineVal);
            }
            *ok = true;
            return retVal;
        }
    }
    file.close();
    *ok = false;
    return retVal;
}

void Lookup::saveBoardProb(QString printID, QList<QList<double>> inVal, bool starter, bool *ok)
{
    QString filename;
    if(starter)
        filename = "StoredDataFirst.txt";
    else
        filename = "StoredDataSecond.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        *ok = false;
        return;
    }

    QString s;
    QTextStream t(&file);
    while(!t.atEnd())
    {
        QString line = t.readLine();
        QStringList split = line.split("#");
        if(split.at(0) != printID)
        {
            s.append(line + "\n");
        }
    }

    QString printLine = printID + "#";
    for(int x = 0; x < inVal.length(); x++)
    {
        for(int y = 0; y < inVal.at(x).length(); y++)
        {
            printLine += QString::number(inVal.at(x).at(y)) + ":";
        }
        printLine += "-";
    }

    s.append(printLine + "\n");
    file.resize(0);
    t << s;
    file.close();
}
