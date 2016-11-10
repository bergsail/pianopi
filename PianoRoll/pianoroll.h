#ifndef PIANOROLL_H
#define PIANOROLL_H

#include<QQuickView>
#include <QQuickPaintedItem>
#include <QColor>
#include<QQmlListProperty>
#include<QtQml/qqml.h>
#include <QTimer>
#include <QTime>

#include"roll.h"
#include"midifile.h"
class PianoRoll : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int widthd READ width WRITE setWidthd)
    Q_PROPERTY(int heightd READ height WRITE setHeightd)


public:
    Q_INVOKABLE void syncTime(int time_ms);
//    Q_INVOKABLE void startPlay();
    Q_INVOKABLE void keyPress(int note);
    Q_INVOKABLE void continuePlay();
    PianoRoll();

    int widthd() const{return m_widthd;}
    void setWidthd(const int &widthd);
    int heightd() const{return m_heightd;}
    void setHeightd(const int &heightd);

signals:
    void noteOn(int note);
    void noteOff(int note);
    void startPlay();

protected:
    void paint(QPainter *painter);
    void pianoRollDataG();

protected slots:
    void paintRect();
    void dataPump();

private:
    int m_widthd;
    int m_heightd;
    QList<Roll*> m_rolls;
    QTimer* timer10;
    QTimer* timer1000;
    QTime time;
    QTime timeT;
    int timeAC_ms;
    int timeAC_base_ms;
    bool timeTOK;

    int m_time_ms;
    int m_sync_d_time_ms;
    Roll* m_roll_next;
    Roll* m_roll_cur;
    Roll* m_roll_his;
    QList<Roll*> m_rolls_tmp;
    bool m_start;
    bool m_first_roll;
    bool m_keyPressOK;
    bool m_continueOK;

    int m_state;// 0:play 1:practice 2:test
    MidiFile* midifile;
    std::list<std::pair<unsigned int,MidiRoll> > m_rollList;
    std::list<std::pair<unsigned int,MidiRoll> >::iterator m_iterRoll;

};

#endif // PIANOROLL_H
