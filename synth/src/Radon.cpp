#include "Radon.h"
#include <math.h>
#include <iostream>

using namespace std;

namespace hottstep {
namespace synth {

class Radon;

Radon::Radon( float tempo, float sampleRate, int bars, int divisionsInBar )
      : SequencePlayer( tempo, sampleRate, bars, divisionsInBar ),
        noise(3),
        lpfilter(),
        bpfilter(),
        d1filter(),
        d2filter(),
        delayl( lengthPerDivision ),
        delayr( lengthPerDivision*2 )
{
   bpfilter.setupLowpass( sampleRate, 1000, 1 );
   d1filter.setupBandpass( sampleRate, 3000, .4 );
   d2filter.setupBandpass( sampleRate, 3000, .4 );
   lpfilter.setupLowpass( sampleRate, 700 , .25 );
   setAdsr( 40, 20, .7, 10 );
}
void Radon::reset() {
   pos = 0;
   lpfilter.reset();
   bpfilter.reset();
   d1filter.reset();
   d2filter.reset();
   delayl.reset();
   delayr.reset();
}

float *Radon::tick() {
   int note = getNotes()[ pos / lengthPerDivision ] ;
   int placeInNote = pos % lengthPerDivision;
   float signal;
   float gain = 0;
   float f0 = 20;
   float lp = 1;
   float rp = 1;
   if( note < 0 || note > 127 ) {
      signal = 0;
   } else {
      f0 = pitchTable[note];
      if( note < 40 ) {
         lp = rp = 1;
      } else if( note % 2 == 0 ) {
         lp = 1;
         rp = 0;
      } else {
         lp = 0;
         rp = 1;
      }
      gain = sustainLevel;
      float n = 0;
      if( placeInNote < attackSamples ) {
         gain = placeInNote / (float) attackSamples ;
         n = noise.generateUniformRandomDeviate() * gain ;
      } else if( placeInNote < attackSamples + decaySamples ) {
         int p = placeInNote - attackSamples;
         float r = p / (float) decaySamples ;
         gain = ( 1 - r ) + sustainLevel * r ;
         n = noise.generateUniformRandomDeviate() * (1-r) ;
      } else if( placeInNote > lengthPerDivision - releaseSamples ) {
         int p = placeInNote - ( lengthPerDivision - releaseSamples ) ;
         float r = p / (float) releaseSamples ;
         gain = ( 1 - r ) * sustainLevel ;
      } else {
      }
      //cout << placeInNote << " : " << gain << " : " << sustainLevel << " : " << attackSamples ;
      //for( int i=0; i<80*gain; ++i )
      //   cout << "*" ;
      //cout << endl;
      //signal = sin( f0 * placeInNote * 2 * M_PI / sampleRate ) ;
      //signal = clip( signal, .7 );
      //signal *= gain;
      //signal = clip( signal, .5 );
      signal = n ;
   }
   //cout << p << " : " << ret << endl;
   ++pos;
   if( pos >= totalLength )
      pos = 0;

   //filter
   bpfilter.setupBandpass( sampleRate, f0, 5 );
   signal = bpfilter.process( clip(signal, .4 ) ) * 100 ;
   signal = clip( signal, .95 );
   signal = lpfilter.process( signal );

   // delay
   retVals[0] = d1filter.process( delayl.read() );
   retVals[1] = d2filter.process( delayr.read() );
   delayl.process( retVals[0] * .6 + retVals[1] * .2 +  rp * signal );
   delayr.process( retVals[1] * .6 + retVals[0] * .2 +  lp * signal );

   //panning
   retVals[0] = lp * signal + .7 * retVals[0];
   retVals[1] = rp * signal + .7 * retVals[1];
/*
   retVals[0] = retVals[1] = signal;
*/

   //cout << max( retVals[0], retVals[1] ) << endl ;

   return retVals;
}

} //namespace synth
} //namepsace hotstep
