/*
 GroveSoundRecorder.cpp - Library for the Grove Sound Recorder Module
 Created by Wendell Capili, August 29, 2011.
 
 adapted from Seeedstudio's sample code:
 http://garden.seeedstudio.com/index.php?title=Twig_-_Sound_Recorder_v0.92b
 
 For port manipulation code, refer to:
 http://www.arduino.cc/en/Reference/PortManipulation
 
 Released into the public domain.
 */

// defines below used only for debugging
//#define __AVR_ATmega328P__
//#define __AVR_ATmega168P__

#include <avr/io.h>
#include "GroveSoundRecorder.h"

GroveSoundRecorder::GroveSoundRecorder(int sel1) {
    if(sel1 < 2 || sel1 > 12 || sel1 == 7) {
        _sel1 = 2;
        _register = SELPORTD;
    } else {
        _sel1 = sel1;
        if(sel1 < 6) {
            _register = SELPORTD;
        } else if(sel1 > 7) {
            _sel1 = _sel1-8; // to match the pins
            _register = SELPORTB;
        }
    }
    _initialized = false;
}

void GroveSoundRecorder::initialize() {
    _PORT = 0x03; // start with  2 HIGH pins, to be shifted later
    _PORT = _PORT<<_sel1; // shift the port to specified pins
    if(_register == SELPORTD) {
        PORTMODE(DDRD,_PORT); // pins are set in write mode;
        DIGWRITE(PORTD, ~(_PORT)); // write LOW to pins
    } else {
        PORTMODE(DDRB,_PORT); // pins are set in write mode;
        DIGWRITE(PORTB, ~(_PORT)); // write LOW to pins
    }
    _initialized = true;
}

void GroveSoundRecorder::pushCommand(TRACKS track, SOUNDREDOP op) {
    if(!_initialized) {
        return; // do noting when not initialized
    }
    // only PLAYSTART and RECSTART has relevance for track param
    byte command;
    switch (op) {
        case PLAYSTART:
        case RECSTART:
            // write selected track to sel1 and sel2 ports
            command=(~(_PORT&(~(track<<_sel1))));
            break;
        case NONE:
        case PLAYSTOP:
        case RECSTOP:
            // set both pins to low
            command=(~(_PORT)); // write LOW to pins
            break;
        default:
            break;
    }
    if (_register==SELPORTD) {
        SETPINS(PORTD, command);
    } else {
        SETPINS(PORTB, command);        
    }
}

void GroveSoundRecorder::beginRecord(TRACKS seg) {
    if (seg < TRACK2 || seg > TRACK4) {
        return;
    }
    pushCommand(seg, RECSTART);
}

void GroveSoundRecorder::stopRecord() {
    pushCommand(ZERO, RECSTOP);
}

void GroveSoundRecorder::beginPlayback(TRACKS seg) {
    if (seg < TRACK2 || seg > TRACK4) {
        return;
    }
    pushCommand(seg, PLAYSTART);
    delay(500); // let it play
    pushCommand(ZERO, PLAYSTOP);
}

void GroveSoundRecorder::stopPlayback() {
    pushCommand(ZERO, PLAYSTOP);
}

