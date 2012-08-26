#ifndef __HELIUM_H
#define __HELIUM_H

#include "SequencePlayer.h"
#include "Filter.h"
#include "Delay.h"
#include "Noise.h"

namespace hottstep {
namespace synth {

class Helium : public SequencePlayer {
 private:
   Noise noise;
   ButterworthFilter lpfilter;
   ButterworthFilter modfilter;
   Delay delay1, delay2;
   float retVals[2];

 public:
   Helium( float tempo, float sampleRate, int bars, int divisionsInBar ) ;
   void reset();
   float *tick();
} ;

} //namespace synth
} //namepsace hotstep

#endif //__HELIUM_H
