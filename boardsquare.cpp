#include "boardsquare.h"
#include <QVBoxLayout>

BoardSquare::BoardSquare(int x, int y, QWidget *parent) : QWidget(parent)
{
    m_x = x;
    m_y = y;
    setMinimumSize(20,20);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    m_label = new QLabel("");
    m_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_label);
    this->setLayout(layout);
    installEventFilter(this);
    setStyleSheet("border: 1px solid black; margin: 0px; padding: 0px;");
}

void BoardSquare::receiveChangeState(int player) //0 = none, 1 = player 1, 2 = player 2;
{
    if(player == 1)
        m_label->setText("X");
    else if(player == 2)
        m_label->setText("O");
    else
        m_label->setText("");
}

bool BoardSquare::eventFilter(QObject *obj, QEvent *event)
 {
     if (event->type() == QEvent::MouseButtonRelease) {
         if(m_label->text() == "")
         {
             m_label->setText("X");
             emit sendClickedEvent(m_x, m_y);
         }
         return true;
     } else {
         // standard event processing
         return QObject::eventFilter(obj, event);
     }
 }
