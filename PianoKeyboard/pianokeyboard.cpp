#include "pianokeyboard.h"
#include <iostream>
#include "RtMidi.h"

#include  <QDebug>
#define KEYWIDTH  27.7
#define KEYHEIGHT 180
PianoKeyboard::PianoKeyboard()
{
    midiout=createMidiOut();
    midiin=createMidiIn();
    midiin->setCallback(&midiincallback,this);
    midiin->ignoreTypes( false, false, false );
    int i, numkeys = 7 * 12+4;
    for(i = 0; i < numkeys; ++i)
    {
        float x = 0;
        PianoKey* key = NULL;
        int ii=i+9;
        int octave = ii / 12 * 7;
        int j = ii % 12;
        if (j >= 5) j++;
        if ((j % 2) == 0) {
            x = (octave + j / 2) * KEYWIDTH;
            key = new PianoKey( QRect(x-KEYWIDTH*5, 0, KEYWIDTH, KEYHEIGHT), false, i );
            m_keysW.insert(i, key);
        } else {
            x = (octave + j / 2) * KEYWIDTH + KEYWIDTH * 6/10 + 1;
            key = new PianoKey( QRect( x-KEYWIDTH*5, 0, KEYWIDTH * 6.5/10 - 1, KEYHEIGHT * 6/10 ), true, i );
            m_keysB.insert(i, key);
        }

    }
    connect(this,SIGNAL(keyPress(int)),this,SLOT(noteOn(int)));
}
void PianoKeyboard::paint(QPainter *painter)
{
    foreach (PianoKey *key, m_keysW) {
        key->drawPianoKey(painter);
    }
    foreach (PianoKey *key, m_keysB) {
        key->drawPianoKey(painter);
    }
}
void PianoKeyboard::noteOn(int note)
{
    int ii=note+9;
    int j = ii % 12;
    if (j >= 5) j++;
    if ((j % 2) == 0) {
        foreach(PianoKey* key,m_keysW)
            if(key->getNote()==note)
            {key->isPressed()?key->setPressed(false):key->setPressed(true);update();}

    } else {
        foreach(PianoKey* key,m_keysB)
            if(key->getNote()==note)
            {key->isPressed()?key->setPressed(false):key->setPressed(true);update();}
    }
}
void PianoKeyboard::noteOff(int note)
{
    int ii=note+9;
    int j = ii % 12;
    if (j >= 5) j++;
    if ((j % 2) == 0) {
        foreach(PianoKey* key,m_keysW)
            if(key->getNote()==note)
            {key->setPressed(false);update();}

    } else {
        foreach(PianoKey* key,m_keysB)
            if(key->getNote()==note)
            {key->setPressed(false);update();}
    }
}


RtMidiIn* PianoKeyboard::createMidiIn(){
    RtMidiIn* midiin=new RtMidiIn();
//    qDebug("createMidiIn");
    std::string portName;
     // Check available ports.
     unsigned int nPorts = midiin->getPortCount();
     if ( nPorts == 0 ) {
       std::cout << "No ports available!\n";
       midiin->openVirtualPort();
       delete midiin;
       return NULL;
     }
     std::cout << "\nThere are " << nPorts << " MIDI input ports available.\n";
     for ( unsigned int i=0; i<nPorts; i++ ) {
         try {
             portName = midiin->getPortName(i);
         }
         catch (RtError &error) {
             error.printMessage();
             //goto cleanup;
         }
         std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
     }
     //open
     midiin->openPort(nPorts>1?1:0);
     midiin->openVirtualPort();

    return midiin;
}
RtMidiOut* PianoKeyboard::createMidiOut(){
    RtMidiOut *midiout = new RtMidiOut();
    std::string portName;
    unsigned int nPorts = midiout->getPortCount();
    if ( nPorts == 0 ) {
        std::cout << "No ports available!\n";
        midiout->openVirtualPort();
        //goto cleanup;
        return NULL;
    }
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiout->getPortName(i);
        }
        catch (RtError &error) {
            error.printMessage();
            //goto cleanup;
        }
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    midiout->openPort(nPorts>1?1:0);
   // midiout->openPort(1);
    midiout->openVirtualPort();
    return midiout;
}
void PianoKeyboard::midiincallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
//  unsigned int nBytes = message->size();
//  for ( unsigned int i=0; i<nBytes; i++ )
//    std::std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
//  if ( nBytes > 0 )
//    std::std::cout << "stamp = " << deltatime << std::std::endl;
  PianoKeyboard* main=static_cast<PianoKeyboard*>(userData);
  unsigned int nBytes;
  unsigned char buffer[11] = {0};
  //std::cout << (int)buffer[10] << std::endl;
  nBytes = message->size();
  bool flag_emit=false;
  for (int i = 0; i < nBytes; i++)
  {
     // std::cout << "Byte " << i << ": ";
      //printf("0x%x\n", (int)message->at(i));

      if ((message->at(i+0) & 0xA0) == 0xA0)
          continue;
      else if ((message->at(i+0) & 0xF0) == 0xF0)
          continue;
      else if ((message->at(i+0) & 0xE0) == 0xE0)
          continue;
      else if ((message->at(i+0) & 0xD0) == 0xD0)
          continue;
      else if ((message->at(i+0) & 0xC0) == 0xC0)
          continue;
      else if ((message->at(i+0) & 0xB0) == 0xB0)
          continue;
      else if ((message->at(i+0) & 0xA0) == 0xA0)
          continue;
      else if ((message->at(i+0) & 0x80) == 0x80)
      {
          std::cout << "Note OFF: " << (int)message->at(i+1) << std::endl;
          main->keyPress((int)message->at(i+1)-21);
//          if(note_array[message->at(i+1)])
//              note_array[message->at(i+1)] = false;
//          else
//              note_array[message->at(i+1)] = true;
//          flag_emit=true;
      }
      else if ((message->at(i+0) & 0x90) == 0x90)
      {
          std::cout << "Note ON: " << (int)message->at(i+1) << std::endl;
//          note_array[message->at(i+1)] = true;
//          flag_emit=true;
      }
      //std::cout << "a" << (int)buffer[10] << std::endl;
  }
  if (message->size() > 0&&flag_emit)
  {
     // std::cout << "b" << (int)buffer[10] << std::endl;

      for (int i = 21; i < 108; i++)
      {
//          if (note_array[i])
//          {
//             // std::cout << 1;
//              emit(main->shwNoteOn(i,100));
//          }
//          else
//          {
//             // std::cout << 0;
//              emit(main->shwNoteOff(i,0));
//          }
      }
     // std::cout << std::endl;

  }
  //byte classification
  //emit
}
