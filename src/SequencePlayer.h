#ifndef __SEQUENCE_PLAYER_H
#define __SEQUENCE_PLAYER_H

#include "LoopData.h"

namespace hottstep {
namespace synth {

class SequencePlayer {
 private:
   float pitchTable[127];
   float sampleRate;
   int pos;
   int totalLength;
   int lengthPerDivision;
   int attackSamples, decaySamples, releaseSamples;
   float sustainLevel;
   LoopData loopData;

 public:
   SequencePlayer( float tempo, float sampleRate, int bars, int divisionsInBar ) ;
   inline vector<int>& getNotes() { return loopData.getNotes(); }
   /** sets up the adsr envelope. default is 10 ms for all time values and .7 for sustain.
    * sustain should be between 0 and 1. */
   void setAdsr( float attackMs, float decayMs, float sustainLevel, float releaseMs );
   float tick();
} ;

} //namespace synth
} //namepsace hotstep

#endif //__SEQUENCE_PLAYER
