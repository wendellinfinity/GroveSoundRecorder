/*
 GroveSoundRecorder.pde - Sample code for the Grove Sound Recorder Module library
 Created by Wendell Capili, August 29, 2011.
 
 adapted from Seeedstudio's sample code:
 http://garden.seeedstudio.com/index.php?title=Twig_-_Sound_Recorder_v0.92b
  
 Released into the public domain.
 */

// include our sound recorder library
#include <GroveSoundRecorder.h>

// initialize a recorder
#define SEL1 2 // this will be the pin# on the Stem Base Shield, only use the DIGITAL pins
// NOTE: for this example, we cannot use pin7 because the lib
//     uses direct port manipulation and pin7 and 8 are on different pin groups
// NOTE: we cannot also use pins 0 and 1 for good measure because
//     they are the RX and TX serial pins
// NOTE: we cannot also use pin13 as it is short of sel2 pin
GroveSoundRecorder recorder(SEL1);

void setup() {
     Serial.begin(9600);
     // initialize the sound recorder
     recorder.initialize();
}

char index;
char control;
char state;
TRACKS selectedTrack=ZERO;
void loop() {
     delay(50);
     //get the serial command
     // this is based from Seeedstudio's example code:
     // #rb = begin recording track #
     // #rs/rs = stop all recording
     // #p = play track # 
     if (Serial.available()>0)
     {   
          index = Serial.read();
          control = Serial.read();
          state = Serial.read();
     }
     Serial.flush();     
     // determine the track to play
     switch(index)
     {
     case '2':
          selectedTrack=TRACK2;
          break;
     case '3':
          selectedTrack=TRACK3;
          break;
     case '4':
          selectedTrack=TRACK4;
          break;
     default:
          selectedTrack=ZERO;
          break;
     }
     // get action to do
     switch(control) {
     case 'r':
          // RECORD: flip first the switch on the sound recorder board to REC
          // determine if start recording or stop recording
          if(state=='b') {
               // start recording
               Serial.print("start recording track #");
               Serial.println(selectedTrack+1,DEC);
               recorder.beginRecord(selectedTrack);
          } 
          else {
               // stop recording
               Serial.println("stopped all recording");
               recorder.stopRecord();
          }
          index=0; control=0; state=0; // reset command
          break;
     case 'p':
          // PLAYBACK: flip first the switch on the sound recorder board to PLAY
          // start playing track
          Serial.print("playing track #");
          Serial.println(selectedTrack+1,DEC);
          recorder.beginPlayback(selectedTrack);
          index=0; control=0; state=0;
          break;
     default:
          // do nothing
          break;
     }
}







