#include "midifile.h"
#include <iostream>
#include <cstdlib>
 #include <unistd.h>
#include <QDebug>

#include "../jmidi/world.h"
#include "../jmidi/track.h"
#include "../jmidi/multitrack.h"
#include "../jmidi/filereadmultitrack.h"
#include "../jmidi/fileread.h"
#include "../jmidi/fileshow.h"
#include "../jmidi/sequencer.h"
using namespace jdksmidi;
using namespace std;

#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )

MidiFile::MidiFile()
{
}
MIDISequencer* MidiFile::loadMIDIFile (std::string file)

{
        const char *infile_name = file.c_str();

        MIDIFileReadStreamFile *rs=new MIDIFileReadStreamFile( infile_name );
        MIDIMultiTrack *tracks=new MIDIMultiTrack;
        MIDIFileReadMultiTrack *track_loader=new MIDIFileReadMultiTrack( tracks );
        MIDIFileRead *reader=new MIDIFileRead( rs, track_loader );

        // set amount of tracks equal to midifile
        tracks->ClearAndResize( reader->ReadNumTracks() );

//      MIDISequencerGUIEventNotifierText notifier( stdout );
//      MIDISequencer seq( &tracks, &notifier );
        MIDISequencer *seq =new MIDISequencer( tracks );

        // load the midifile into the multitrack object
        if ( !reader->Parse() )
        {
            cerr << "\nError parse file " << infile_name << endl;
        }
        return seq;


}
std::list<std::pair<unsigned int,MIDITimedBigMessage> > MidiFile::PlayDumpSequencer( MIDISequencer *seq)
{
    std::vector<unsigned char> message(3);
    std::list<std::pair<unsigned int,MIDITimedBigMessage> > tones;
    float pretend_clock_time = 0.0;
    float next_event_time = 0.0;
    MIDITimedBigMessage ev;
    int ev_track;
    seq->GoToTimeMs ( pretend_clock_time );

    if ( !seq->GetNextEventTimeMs ( &next_event_time ) )
    {
        return tones;
    }

    float max_time = 3600. * 1000.;
    long mtime=0;

    for ( ; pretend_clock_time < max_time; pretend_clock_time += 10. )
    {
        while ( next_event_time <= pretend_clock_time )
        {
            if ( seq->GetNextEvent ( &ev_track, &ev ) )
            {
                MIDITimedBigMessage *msg=&ev;
                tones.push_back(std::pair<unsigned int,MIDITimedBigMessage>(pretend_clock_time,ev));
//                qDebug("teim:%4.2f",pretend_clock_time);
                if ( !seq->GetNextEventTimeMs ( &next_event_time ) )
                {
                    // no events left so end
                    fprintf ( stdout, "End\n" );
                    return tones;
                }
            }
        }
    }
    return tones;
}
std::list<std::pair<unsigned int,MidiRoll> > MidiFile::PlayRollSequencer(std::list<std::pair<unsigned int, MIDITimedBigMessage> > *midiList)
{
     std::list<std::pair<unsigned int,MidiRoll> > rollList;
     std::list<std::pair<unsigned int,MidiRoll> > tmpList;
     MidiRoll midiroll;
     MIDITimedBigMessage msg;
     std::list<std::pair<unsigned int, MIDITimedBigMessage> >::iterator iter;
     iter=midiList->begin();
//     qDebug("neum:%d",midiList->size());
     while(iter != midiList->end())
     {
         msg=iter->second;
         std::vector<unsigned char> message(3);
         message[0]=msg.GetStatus();
         message[1]=msg.GetByte1();
         message[2]=msg.GetByte2();
         message[3]=msg.GetByte3();
         if ( (message[0]  & 0xF0) == 0x80)
         {

         }
         if ( (message[0] & 0xF0 ) == 0x90 )
         {

             if (message[2]==0)
             {
                 std::list<std::pair<unsigned int,MidiRoll> >::iterator iterT;
                 iterT=tmpList.begin();
                 while(iterT!=tmpList.end())
                 {
                     if(iterT->second.note==(int)(message[1])&iter->first>iterT->first)
                     {
                         midiroll.note=message[1];
                         midiroll.tEnd=iter->first;
                         midiroll.volumn=message[2];
//                         qDebug("noteoff:%d,time:%d",midiroll.note,iterT->first);
                         rollList.push_back(std::pair<unsigned int,MidiRoll>(iterT->first,midiroll));
                         iterT = tmpList.erase(iterT);
                     }
                     else iterT++;
                 }
             }
             else
             {
                 midiroll.note=message[1];
                 midiroll.volumn=message[2];

                 bool notinOK=true;
                 std::list<std::pair<unsigned int,MidiRoll> >::iterator iterT;
                 iterT=tmpList.begin();
                 while(iterT!=tmpList.end())
                 {
                     if(iterT->second.note==midiroll.note&&iterT->first==iter->first)
                     {notinOK=false;break;}
                     iterT++;
                 }
                 if(notinOK)
                 {
//                     qDebug("noteon:%d,time:%d",midiroll.note,iter->first);
                     tmpList.push_back(std::pair<unsigned int,MidiRoll>(iter->first,midiroll));
                 }
             }

         }
         iter++;
     }

     return rollList;
}
