#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <QBrush>
#include <QColor>
#include <QPointF>
#include <QRect>
#include <QRectF>

QT_FORWARD_DECLARE_CLASS(QPainter)

class PianoKey
{
public:

    PianoKey(const QRect &rect, const bool black, const int note);
    void drawPianoKey(QPainter *painter);
    int getNote() const { return m_note; }
    void setPressedBrush(const QBrush& b) { m_selectedBrush = b; }
    bool isPressed() const { return m_pressed; }
    void setPressed(bool p);

private:
    QRectF m_rect;
    bool m_pressed;
    QBrush m_selectedBrush;
    QBrush m_brush;
    int m_note;
    bool m_black;
};



#endif // PIANOKEY_H
