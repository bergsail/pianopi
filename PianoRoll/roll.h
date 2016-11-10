#ifndef ROLL_H
#define ROLL_H

#include<QQuickView>
#include <QQuickPaintedItem>
#include<QQmlListProperty>
#include<QtQml/qqml.h>
#include <QBrush>
#include <QColor>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QTimer>


QT_FORWARD_DECLARE_CLASS(QPainter)

class Roll
{
public:
    Roll(const int &note,const int &tStart,const int &tEnd,const int &time,const int &volumn);
    ~Roll();
    void updateCache();
    void drawRoll(QPainter *painter);
    void move(int miliSecond);
    QRect activeRect();
    int note(){return m_note;}
    int tEnd(){return m_tEnd;}
    int played(){return m_played;}
    void setPlayed(bool played);
    void setNext(bool next);

private:

    int m_time;
    int m_note;
    int m_tStart;
    int m_tEnd;
    int m_volumn;

    bool m_black;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_yB;
    int m_yD;

    bool m_played;
    bool m_next;
    QColor m_color;
    QImage *m_cache;
    QImage *m_cacheB;
};

#endif // ROLL_H
