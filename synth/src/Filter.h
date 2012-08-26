#ifndef __HOTTSTEP_FILTER_H
#define __HOTTSTEP_FILTER_H

#include <math.h>

#define IS_DENORMAL(f) (((*(unsigned int *)&(f))&0x7f800000) == 0)

namespace hottstep {
namespace synth {

class ButterworthFilter {
 private:
   float b0, b1, b2, a1, a2;
   float lastx, lastlastx, lasty, lastlasty;

 public:
   ButterworthFilter() : b0(0), b1(0), b2(0), a1(0), a2(0), lastx(0), lastlastx(0), lasty(0), lastlasty(0) {
   }
   void reset() {
      lastx = lastlastx = lasty = lastlasty = 0;
   }
   void setupLowpass( float srate, float cutoff, float Q ) {
      float w0 = 2*M_PI*cutoff/srate;
      float alpha = sin(w0)/( 2 * Q );
      float cosw0 = cos( w0 );

      float a0;
      b0 =  (1 - cosw0)/2 ;
      b1 =   1 - cosw0 ;
      b2 =  (1 - cosw0)/2 ;
      a0 =   1 + alpha ;
      a1 =  -2*cosw0 ;
      a2 =   1 - alpha ;

      b0 /= a0 ;
      b1 /= a0 ;
      b2 /= a0 ;
      a1 /= a0 ;
      a2 /= a0 ;
   }

   float inline process( float x ) {
      float y = b0*x + b1*lastx + b2*lastlastx - a1*lasty - a2*lastlasty;
      //if( IS_DENORMAL(y) )
      //    y = 0;

      lastlasty = lasty;
      lasty = y;
      lastlastx = lastx;
      lastx = x;

      return y;
   }
} ;

} //synth
} //hotstep

#endif //__HOTSTEP_FILTER_H
