#ifndef __SEQUENCE_PLAYER_H
#define __SEQUENCE_PLAYER_H

#include "LoopData.h"

namespace hottstep {
namespace synth {

class SequencePlayer {
 protected:
   float pitchTable[128];
   int pos;
   int totalLength;
   int lengthPerDivision;
   float sampleRate;
   int attackSamples, decaySamples, releaseSamples;
   float sustainLevel;

   LoopData loopData;

 public:
   SequencePlayer( float tempo, float sampleRate, int bars, int divisionsInBar ) ;
   inline vector<int>& getNotes() { return loopData.getNotes(); }
   virtual void reset() = 0;
   /** sets up the adsr envelope. A default should be set already.
    * Some instruments may ignore all or part of this.
    */
   void setAdsr( float attackMs, float decayMs, float sustainLevel, float releaseMs );
   virtual float tick() = 0;
   inline int computeSamples( float milliseconds ) {
      return (int) ( ( milliseconds / 1000 ) * sampleRate + .5 );
   }
   inline float clip( float val, float range ) {
      if( val > range )
         return range;
      else if( val < -range )
         return -range;
      else
         return val;
   }
} ;

} //namespace synth
} //namepsace hotstep

#endif //__SEQUENCE_PLAYER
