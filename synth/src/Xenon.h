#ifndef __XENON_H
#define __XENON_H

#include "SequencePlayer.h"
#include "Filter.h"
#include "Noise.h"

namespace hottstep {
namespace synth {

class Xenon : public SequencePlayer {
 private:
   Noise noise;
   ButterworthFilter envfilter;
   ButterworthFilter lpfilter;
   float envFollow;
   float retVals[2];

 public:
   Xenon( float tempo, float sampleRate, int bars, int divisionsInBar ) ;
   void reset();
   float *tick();
} ;

} //namespace synth
} //namepsace hotstep

#endif //__XENON_H
