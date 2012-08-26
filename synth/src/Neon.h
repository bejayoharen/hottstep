#ifndef __NEON_H
#define __NEON_H

#include "SequencePlayer.h"
#include "Filter.h"
#include "Delay.h"
#include "Noise.h"

namespace hottstep {
namespace synth {

class Neon : public SequencePlayer {
 private:
   ButterworthFilter modfilter;
   ButterworthFilter envfilter;
   ButterworthFilter lpfilter;
   ButterworthFilter d1filter, d2filter;
   Delay delay1, delay2;
   float envFollow;
   float retVals[2];

 public:
   Neon( float tempo, float sampleRate, int bars, int divisionsInBar ) ;
   void reset();
   float *tick();
} ;

} //namespace synth
} //namepsace hotstep

#endif //__NEON_H
