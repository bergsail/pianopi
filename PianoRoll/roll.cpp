
#include <QPainter>
#include "roll.h"
#define KEYWIDTH  27.7
#define KEYHEIGHT 180
#define MSPIX 200
#define STARTD -300

#include <QDebug>
Roll::Roll(const int &note,const int &tStart,const int &tEnd,const int &time,const int &volumn)
    : m_note(note), m_tStart(tStart),m_tEnd(tEnd),m_time(time),m_volumn(volumn)
{
    m_cache = 0;
    m_cacheB=0;
    m_color =QColor(Qt::red);
//  bool m_black;
    m_black= (note%12==1||note%12==4||note%12==6||note%12==9||note%12==11)?true:false;
//  int m_width;
    m_width= m_black?KEYWIDTH*6.5/10-1:KEYWIDTH*8/10;
//  int m_height;
    m_height=(tEnd-tStart)*MSPIX/1000;
//  int m_x;
    m_x=(note+9)%12>=5?(note+9)/12*7*KEYWIDTH+((note+9)%12+1)/2*KEYWIDTH+(((note+9)%12+1)%2==0?0:KEYWIDTH*6/10+1)-5*KEYWIDTH:
                       (note+9)/12*7*KEYWIDTH+((note+9)%12)/2*KEYWIDTH  +((note+9)%12%2==0?0:KEYWIDTH*6/10+1)-5*KEYWIDTH;
//  int m_y;
    m_y=(-1)*tStart*MSPIX/1000-m_height;
    m_yB=m_y;
    m_yD=m_y=(-1)*tStart*MSPIX/1000-m_height+STARTD;

    m_played=false;
    m_next=false;

    updateCache();

}
Roll::~Roll()
{
    if (m_cache)
        delete m_cache;
    if(m_cacheB)
        delete m_cacheB;
}

void Roll::updateCache()
{
    if (m_cache)
        delete m_cache;
    m_cache = new QImage(m_width, m_height, QImage::Format_ARGB32);
    m_cache->fill(0x00000000);
    QPainter p(m_cache);
    QPen pen(Qt::blue);
    QPen penPlayed(Qt::red);
    QBrush brush(m_color);
    QBrush brushB(Qt::blue);
    QBrush brashN(Qt::yellow);
    pen.setWidth(2);
    if(m_played){
        p.setPen(penPlayed);
    p.setBrush(brushB);
    }
    else{
        p.setPen(pen);
    p.setBrush(brush);
    }
    if(m_next)
        p.setBrush(brashN);
    p.drawRect(QRect(0,0,m_width,m_height));

//    if(m_cacheB)
//        delete m_cacheB;
//    m_cacheB = new QImage(m_width+2, m_height+2, QImage::Format_ARGB32);
//    m_cacheB->fill(0x00000000);
//    QPainter pB(m_cacheB);
//    QPen penB(Qt::black);
//    QBrush brushB(Qt::black);
//    pen.setWidth(2);
//    pB.setPen(penB);
//    pB.setBrush(brushB);
//    pB.drawRect(QRect(0,0,m_width,m_height));
}


void Roll::drawRoll(QPainter *painter)
{
//    painter->save();
//    painter->translate(m_x,m_yB);
//    painter->setOpacity(0.8);
//    painter->drawImage(0, 0, *m_cacheB);
//    painter->restore();

    painter->save();
    painter->translate(m_x,m_y);
    painter->setOpacity(1.0);
    painter->drawImage(0, 0, *m_cache);
    painter->restore();
}


void Roll::move(int miliSecond)
{
    m_yB=m_y;
    m_y=(miliSecond-m_time)*MSPIX/1000+m_yD;
}
QRect Roll::activeRect()
{
    return QRect(m_x,m_yB,m_width,m_height);
}
void Roll::setPlayed(bool played)
{
    m_played=played;
    updateCache();
}
void Roll::setNext(bool next)
{
    m_next=next;
    updateCache();
}
