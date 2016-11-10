#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H
#include<QQuickView>
#include <QQuickPaintedItem>
#include <QColor>
#include<QQmlListProperty>
#include<QtQml/qqml.h>
#include"pianokey.h"

class RtMidiIn;
class RtMidiOut;

class PianoKeyboard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    Q_INVOKABLE void noteOn(int note);
    Q_INVOKABLE void noteOff(int note);
    PianoKeyboard();
signals:
    void keyPress(int note);
protected:
    void paint(QPainter *painter);
    RtMidiIn* createMidiIn();
    RtMidiOut* createMidiOut();
   static void midiincallback( double deltatime, std::vector< unsigned char > *message, void *userData );
private:
    QList<PianoKey*> m_keysW;
    QList<PianoKey*> m_keysB;
    RtMidiIn* midiin;
    RtMidiOut* midiout;
};

#endif // PIANOKEYBOARD_H
