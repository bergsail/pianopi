#include "pianoroll.h"
#define CONFIG_PLAY_DELAY 180
#define CONFIG_PRAC_DELAY 180
#define CONFIG_STAR -1300
#define CONFIG_SYNC 7000
#define INIT_POS 2000
using namespace jdksmidi;

PianoRoll::PianoRoll()
{
    midifile=new MidiFile();
    pianoRollDataG();

    timer10=new QTimer();
    timer10->setInterval(10);
    QObject::connect(timer10,SIGNAL(timeout()),this,SLOT(paintRect()));
    timer10->start();
    timer1000=new QTimer();
    timer1000->setInterval(1000);
    QObject::connect(timer1000,SIGNAL(timeout()),this,SLOT(dataPump()));
    timer1000->start();

    time.start();
//    timeT.start();
    timeTOK=false;
    timeAC_ms=0;
    timeAC_base_ms=0;

    m_time_ms=0;
    m_sync_d_time_ms=0;
    m_roll_cur=0;
    m_roll_his=0;
    m_roll_next=0;

    m_start=false;
    m_first_roll=true;
    m_keyPressOK=false;
    m_continueOK=true;

    m_state=1;

}
void PianoRoll::paint(QPainter *painter)
{

    foreach(Roll* roll,m_rolls)
    {
            roll->drawRoll(painter);
    }
}
void PianoRoll::paintRect()
{
    if(m_state==0||m_state==2)
    {
        foreach(Roll* roll,m_rolls)
        {
            if(roll->activeRect().y()+roll->activeRect().height()>m_heightd-CONFIG_PLAY_DELAY
                    &&roll->activeRect().y()<m_heightd-CONFIG_PLAY_DELAY)
            {
                if(m_state==0)
                {
                    if(!m_start){
                        emit(startPlay());
                        m_start=true;
                    }
                }
                emit(noteOn(roll->note()));
            }
            else if(roll->activeRect().y()>m_heightd-CONFIG_PLAY_DELAY)
            {
                emit(noteOff(roll->note()));
            }
        }
        foreach(Roll* roll,m_rolls)
        {
           roll->move(time.elapsed()+CONFIG_STAR);
        }
        update();
    }
    if(m_state==1)
    {
        if(m_rolls.length()==0)
            return;
        //if null ,find critical roll
        if(m_roll_cur==0){
            foreach(Roll* roll,m_rolls){
                if(!roll->played()){
                    m_roll_cur=roll;
                    break;}
            }
        }
        if(m_continueOK==false)
            return;
        if(timeTOK)
        {
            timeAC_ms+=timeT.elapsed();
            timeTOK=false;
        }
        //
        int y1=m_roll_cur->activeRect().y();
        int y2=m_roll_cur->activeRect().y()+m_roll_cur->activeRect().height();
        if(y2>m_heightd-CONFIG_PRAC_DELAY&&y1<m_heightd-CONFIG_PRAC_DELAY)
        {
            timeT.restart();
            m_continueOK=false;
            timeTOK=true;
        }
        //normal play
        if(m_continueOK)
        {
            foreach(Roll* roll,m_rolls){
                if(roll->activeRect().y()+roll->activeRect().height()>m_heightd-CONFIG_PRAC_DELAY
                    &&roll->activeRect().y()<m_heightd-CONFIG_PRAC_DELAY)
                {
                    if(!roll->played())
                        continue;
                    emit(noteOn(roll->note()));
                }
                else if(roll->activeRect().y()>m_heightd-CONFIG_PRAC_DELAY)
                {
                    emit(noteOff(roll->note()));
                }
            }
            foreach(Roll* roll,m_rolls)
            {
               roll->move(time.elapsed()-timeAC_ms);
            }
            update();
        }
    }
}
void PianoRoll::dataPump()
{
    if(m_continueOK==false)
        return;
    //delete
    QList<Roll*>::Iterator it = m_rolls.begin();
    QList<Roll*>::Iterator end = m_rolls.end();
    while ( it != end ) {
        Roll* roll = *it;
        if ( roll->activeRect().y()>m_heightd ) {

            it = m_rolls.erase( it );
            delete roll;
        }
        else {
            ++it;
            break;
        }
    }
    //add
    MidiRoll roll;
    int m_time_ms_t=time.elapsed()+CONFIG_STAR-timeAC_ms;
    while(m_iterRoll!=m_rollList.end()&&m_iterRoll->first<m_time_ms_t)
    {
        roll=m_iterRoll->second;

        Roll* r=new Roll(roll.note-21,m_iterRoll->first-m_time_ms,roll.tEnd-m_time_ms,m_time_ms,roll.volumn);
        m_rolls.append(r);
        m_iterRoll++;
    }
    m_time_ms=m_time_ms_t;

}
void PianoRoll::pianoRollDataG()
{
    QString file="/home/pi/wmhxznjg.mid";
    jdksmidi::MIDISequencer *seq;
    seq=midifile->loadMIDIFile(file.toLatin1().data());
    std::list<std::pair<unsigned int,jdksmidi::MIDITimedBigMessage> > midilist;
    midilist=midifile->PlayDumpSequencer(seq);

    m_rollList=midifile->PlayRollSequencer(&midilist);
    m_iterRoll=m_rollList.begin();
//    std::list<std::pair<unsigned int,MidiRoll> >::iterator ite=m_rollList.begin();
//    while(ite!=m_rollList.end())
//    {
//        qDebug("teimess:%d",ite->second.tEnd);
//        ite++;
//    }
}
void PianoRoll::setWidthd(const int &widthd)
{
    m_widthd=widthd;
}
void PianoRoll::setHeightd(const int &heightd)
{
    m_heightd=heightd;
//    qDebug("m_height:%d",m_heightd);
}
void PianoRoll::syncTime(int time_ms)
{

//    m_sync_d_time_ms=time_ms-time.elapsed();
//    qDebug("m_timesy:%d",m_sync_d_time_ms);
}
void PianoRoll::keyPress(int note)
{
    //find current rolls
    qDebug("note%d",note);
    qDebug("rol_cur:%d",m_roll_cur->note());
    int y0=m_roll_cur->activeRect().y()+m_roll_cur->activeRect().height();
    int y;
    int i=0;
    int count=0;
    foreach (Roll* roll, m_rolls) {
        if(roll->played())
            continue;
        y=roll->activeRect().y()+roll->activeRect().height();
        if(abs(y-y0)<=10)
        {
            if(roll->note()==note)
                roll->setPlayed(true);
            m_rolls_tmp.append(roll);
            qDebug("appd");
        }
        else if(i++>10) break;
    }
    bool continueOK=true;
    foreach(Roll* roll,m_rolls_tmp)
    {
        if(!roll->played())
            continueOK=false;

    }
    if(continueOK)
        continuePlay();
    //dataclear
    m_rolls_tmp.clear();
}
void PianoRoll::continuePlay()
{
    //set next multi-keys played
    m_roll_cur->setPlayed(true);

    int y0=m_roll_cur->activeRect().y()+m_roll_cur->activeRect().height();
    int y;
    int i=0;
    foreach(Roll* roll,m_rolls)
    {
        if(roll->played())
            continue;
        y=roll->activeRect().y()+roll->activeRect().height();
        if(abs(y-y0)<=10)
        {
            roll->setPlayed(true);
        }
        else if(i==0)
        {
            m_roll_cur=roll;
            roll->setNext(true);
            i++;
        }
        else
        {
            if(i++>10) break;
        }
    }
    m_continueOK=true;
    paintRect();
}
//void PianoRoll::startPlay()
//{
//    timer10=new QTimer();
//    timer10->setInterval(10);
//    QObject::connect(timer10,SIGNAL(timeout()),this,SLOT(paintRect()));
//    timer10->start();
//    timer1000=new QTimer();
//    timer1000->setInterval(1000);
//    QObject::connect(timer1000,SIGNAL(timeout()),this,SLOT(dataPump()));
//    timer1000->start();

//    m_time_ms=0;
//    m_sync_d_time_ms=0;

//    m_start=true;
//}
//                if(roll->played()==false)
//                {

//                    if(m_roll_his==0||roll==m_roll_cur)
//                    {
//                        qDebug("psoidspodifsssss");
//                        qDebug("y:%d,y+height:%d",roll->activeRect().y(),roll->activeRect().y()+roll->activeRect().height());
//                        qDebug("note:%d",roll->note());
//                        qDebug("num:%d",m_rolls.indexOf(roll));

//                    m_continueOK=false;
//    //                playedOK=false;
//                    timeTOK=true;
//                    m_first_roll=false;
//                    m_keyPressOK=false;
//                    m_roll_cur=m_roll_next;

//                    break;
//                    }
//                }
