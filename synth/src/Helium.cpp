#include "Helium.h"
#include <math.h>
#include <iostream>

using namespace std;

namespace hottstep {
namespace synth {

class Helium;

Helium::Helium( float tempo, float sampleRate, int bars, int divisionsInBar )
      : SequencePlayer( tempo, sampleRate, bars, divisionsInBar ),
        noise(1),
        lpfilter(),
        modfilter(),
        delay1( 3 * lengthPerDivision / 4 ),
        delay2( 4 * lengthPerDivision / 5 )
{
   lpfilter.setupLowpass( sampleRate, 1000, 1 );
   modfilter.setupLowpass( sampleRate, 1000, 1 );
   setAdsr( 10, 10, .7, 10 );
}
void Helium::reset() {
   pos = 0;
   lpfilter.reset();
   delay1.reset();
   delay2.reset();
}

float *Helium::tick() {
   int note = getNotes()[ pos / lengthPerDivision ] ;
   int placeInNote = pos % lengthPerDivision;
   float signal;
   float gain = 0;
   if( note < 0 || note > 127 ) {
      signal = 0;
   } else {
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
      signal = sin( pitchTable[note] * placeInNote * 2 * M_PI / sampleRate ) ;
      signal = clip( signal, .7 );
      signal *= gain;
      signal = clip( signal, .5 );
      signal += n / 2.5;
   }
   //cout << p << " : " << ret << endl;
   ++pos;
   if( pos >= totalLength )
      pos = 0;

   //filter
   modfilter.setupLowpass( sampleRate, 200 + gain * 12000, .4 );
   lpfilter.setupLowpass( sampleRate, 1000 + 700*(1+sin( M_PI * 2 * pos / (float) lengthPerDivision ))/2 , 2 );
   signal = modfilter.process( signal );
   signal = lpfilter.process( signal );


   //delay
   retVals[0] = delay1.read();
   retVals[1] = delay2.read();

   delay1.process( ( retVals[0] / 2 + retVals[1] + signal ) * .55 );
   delay2.process( ( retVals[0] / 2 + retVals[1] + signal ) * .55 );

   retVals[0] = retVals[0] + signal ;
   retVals[1] = retVals[1] + signal ;

   return retVals;
}

} //namespace synth
} //namepsace hotstep
