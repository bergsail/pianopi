#include "pianokey.h"

#include <QPainter>
#include <QPalette>
#include <QDebug>
static const QBrush blackBrush = QBrush(Qt::black);
static const QBrush whiteBrush = QBrush(Qt::white);

PianoKey::PianoKey(const QRect &rect, const bool black, const int note)
    :m_rect(rect),
    m_pressed(false),
    m_brush( black ? blackBrush : whiteBrush ),
    m_note(note),
    m_black(black)
{
//    qDebug("rect.x=%d,rect.y=%d,rect.width=%d,rect.heigth=%d",rect.x(),rect.y(),rect.width(),rect.height());
    m_selectedBrush=QBrush(Qt::red);
}

void PianoKey::drawPianoKey(QPainter *painter)
{
    static const QPen blackPen(Qt::black, 1);
    static const QPen grayPen(QBrush(Qt::gray), 1, Qt::SolidLine,  Qt::RoundCap, Qt::RoundJoin);
    if (m_pressed) {
        painter->setBrush(m_selectedBrush);

    } else {
        painter->setBrush(m_brush);
    }

 //   painter->setPen(blackPen);
//    if(m_black)
    painter->drawRoundRect(m_rect, 15, 15);
    if (m_black)
        ;
    else {
        QPointF points[3] = {
             QPointF(m_rect.left()+1.5, m_rect.bottom()-1),
             QPointF(m_rect.right()-1, m_rect.bottom()-1),
             QPointF(m_rect.right()-1, m_rect.top()+1),
        };

//        painter->setPen(grayPen);
//        painter->drawPolyline(points, 3);
    }
}

void PianoKey::setPressed(bool p)
{
    if (p != m_pressed) {
        m_pressed = p;
    }
}
