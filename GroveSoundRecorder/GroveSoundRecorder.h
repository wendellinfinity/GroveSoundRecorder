/*
 GroveSoundRecorder.h - Library for the Grove Sound Recorder Module
 Created by Wendell Capili, August 29, 2011.
 
 adapted from Seeedstudio's sample code:
 http://garden.seeedstudio.com/index.php?title=Twig_-_Sound_Recorder_v0.92b
  
 Released into the public domain.
 */


#ifndef GroveSoundRecorder_h
#define GroveSoundRecorder_h

#include "WProgram.h"

// some helper macros
#define SETPINS(port,pins) (port=pins)
#define PORTMODE(port,pins) (port|=pins)
#define DIGWRITE(port,pins) (port&=pins)

// track numbers
enum TRACKS {
    ZERO = 0,
    TRACK2 = 1,
    TRACK3 = 2,
    TRACK4 = 3
};

// sound recorder operations
enum SOUNDREDOP {
    NONE = 0,
    PLAYSTART = 1,
    PLAYSTOP = 2,
    RECSTART = 3,
    RECSTOP = 4,
};

// selected port from Stem base
enum SOUNDRECPORTREG {
    SELPORTD = 100,  // digital pins 0 to 6, no pin 7
    SELPORTB = 200   // digital pins 8 to 13
};


class GroveSoundRecorder {
    public:
    GroveSoundRecorder(int sel1);
    void initialize();
    void beginRecord(TRACKS seg); // limit to 30s for safety
    void stopRecord();    
    void beginPlayback(TRACKS seg);
    void beginPlaybackLoop(TRACKS seg);    
    void stopPlayback();    
    
    private:
    boolean _initialized;
    int _sel1;
    byte _PORT;
    SOUNDRECPORTREG _register;
    void pushCommand(TRACKS track, SOUNDREDOP op);
    
};


#endif