#ifndef __HOTTSTEP_DELAY_H
#define __HOTTSTEP_DELAY_H

#include <iostream>

namespace hottstep {
namespace synth {

class Delay {
 private:
   vector<float> dat;
   int index;

 public:
   Delay(int samples) : dat(samples), index(0) {
   }
   void reset() {
      for( int i=0; i<dat.size(); ++i )
         dat[i] = 0;
      index = 0;
   }

   float inline read() {
      return dat[index];
   }

   float inline process( float x ) {
      float ret = dat[index];
      dat[index] = x;
      ++index;
      if( index >= dat.size() )
         index = 0;

      return ret;
   }
} ;

} //synth
} //hotstep

#endif //__HOTSTEP_DELAY_H
