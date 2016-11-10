#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <vector>
#include <list>
#include <string>
#include "../jmidi/sequencer.h"
#include "../jmidi/msg.h"
namespace jdksmidi{
class MIDISequencer;
};
class RtMidiOut;
struct MidiTone{
    int code;
    int vel;
};
struct MidiRoll{
    int note;
    int tEnd;
    int volumn;
};

class MidiFile
{
public:
    MidiFile();
    jdksmidi::MIDISequencer* loadMIDIFile (std::string file) ;
    std::list<std::pair<unsigned int,jdksmidi::MIDITimedBigMessage> > PlayDumpSequencer( jdksmidi::MIDISequencer *seq);
    std::list<std::pair<unsigned int,MidiRoll> > PlayRollSequencer(std::list<std::pair<unsigned int,jdksmidi::MIDITimedBigMessage> >* midiList);

};

#endif // MIDIFILE_H




