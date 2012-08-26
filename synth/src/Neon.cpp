#include "Neon.h"
#include <math.h>
#include <iostream>

using namespace std;

namespace hottstep {
namespace synth {

class Neon;

Neon::Neon( float tempo, float sampleRate, int bars, int divisionsInBar )
      : SequencePlayer( tempo, sampleRate, bars, divisionsInBar ),
        modfilter(),
        envfilter(),
        lpfilter(),
        d1filter(),
        d2filter(),
        delay1( lengthPerDivision / 4 ),
        delay2( lengthPerDivision / 3 ),
        envFollow( 0 )
{
   lpfilter.setupLowpass( sampleRate, 3500 , .2f );
   d1filter.setupLowpass( sampleRate, 3000 , .2f );
   d2filter.setupLowpass( sampleRate, 3000 , .2f );
   setAdsr( 80, 80, .9, 100 );
}
void Neon::reset() {
   pos = 0;
   modfilter.reset();
   envfilter.reset();
   lpfilter.reset();
   d1filter.reset();
   d2filter.reset();
   envfilter.reset();
   delay1.reset();
   delay2.reset();
   envFollow = 0;
}

float *Neon::tick() {
   int note = getNotes()[ pos / lengthPerDivision ] ;
   int placeInNote = pos % lengthPerDivision;
   float signal;
   float gain = 0;
   float pitch = 100;
   float lp = 1;
   float rp = 1;
   if( note < 0 || note > 127 ) {
      signal = 0;
   } else {
      gain = sustainLevel;
      pitch = pitchTable[note];
      lp = note % 2;
      rp = 1 - note % 2;
      float n = 0;
      if( placeInNote < attackSamples ) {
         gain = placeInNote / (float) attackSamples ;
         //n = noise.generateUniformRandomDeviate() * gain ;
      } else if( placeInNote < attackSamples + decaySamples ) {
         int p = placeInNote - attackSamples;
         float r = p / (float) decaySamples ;
         gain = ( 1 - r ) + sustainLevel * r ;
         //n = noise.generateUniformRandomDeviate() * (1-r) ;
      } else if( placeInNote > lengthPerDivision - releaseSamples ) {
         int p = placeInNote - ( lengthPerDivision - releaseSamples ) ;
         float r = p / (float) releaseSamples ;
         gain = ( 1 - r ) * sustainLevel ;
      } else {
      }
      signal = sin( pitch * placeInNote * 2 * M_PI / sampleRate ) ;
      //if( signal > .5 ) signal = 1;
      //else if( signal < -.5 ) signal = -1;
      signal *= gain;
      signal *= 2 ;
      signal = clip( signal, .6 );
   }
   //cout << p << " : " << ret << endl;
   ++pos;
   if( pos >= totalLength )
      pos = 0;

   // add nosie:
   //signal += .2 * (gain*gain) * noise.generateUniformRandomDeviate();
   // modulate
   modfilter.setupLowpass( sampleRate, 1000 + 700*(1+sin( M_PI * 7 * pos / (float) lengthPerDivision ))/2 , 2 );
   signal = modfilter.process( signal );

   //env filter
   envFollow = gain * .0005 + envFollow * .9995 ;
   envfilter.setupLowpass( sampleRate, ( .1 + .9*envFollow ) * pitch , 1 );
   signal = envfilter.process( signal );

   //final LP and clip
   signal = lpfilter.process( signal );
   signal = clip( signal, .95 );

   //delay and panning
   float ld = delay1.read() ;
   float rd = delay2.read() ;
   retVals[0] = signal * lp + .9 * ld;
   retVals[1] = signal * rp + .9 * rd;
   delay1.process( d1filter.process(signal * lp) + .9 * rd);
   delay2.process( d2filter.process(signal * rp) + .9 * ld );

   // neon should be quieter compared to other instruments
   retVals[0] *= .85;
   retVals[1] *= .85;

   return retVals;
}

} //namespace synth
} //namepsace hotstep
