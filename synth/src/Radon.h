#ifndef __RADON_H
#define __RADON_H

#include "SequencePlayer.h"
#include "Filter.h"
#include "Delay.h"
#include "Noise.h"

namespace hottstep {
namespace synth {

class Radon : public SequencePlayer {
 private:
   Noise noise;
   ButterworthFilter lpfilter;
   ButterworthFilter bpfilter;
   ButterworthFilter d1filter;
   ButterworthFilter d2filter;
   Delay delayl, delayr;
   float retVals[2];

 public:
   Radon( float tempo, float sampleRate, int bars, int divisionsInBar ) ;
   void reset();
   float *tick();
} ;

} //namespace synth
} //namepsace hotstep

#endif //__RADON_H
