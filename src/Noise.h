#ifndef __HOTTSTEP_NOISE_H
#define __HOTTSTEP_NOISE_H

#include <iostream>

namespace hottstep {
namespace synth {

class Noise {
 private:
   long lastRand;

 public:
   Noise(long seed) : lastRand(seed) {
   }
   float generateUniformRandomDeviate() {
      lastRand = (lastRand*3877+29573) % 139968 ;
      return lastRand / (float) 139968 ;
   }
} ;

} //synth
} //hotstep

#endif //__HOTSTEP_NOISE_H
