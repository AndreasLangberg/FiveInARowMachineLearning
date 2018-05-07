#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QWidget>
#include <QEvent>
#include <QLabel>

class BoardSquare : public QWidget
{
    Q_OBJECT

    friend class Test;
public:
    explicit BoardSquare(int x, int y, QWidget *parent = nullptr);

private:
    int m_x;
    int m_y;
    QLabel *m_label;

signals:
    void sendClickedEvent(int x, int y);

public slots:
    void receiveChangeState(int player);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // BOARDSQUARE_H
