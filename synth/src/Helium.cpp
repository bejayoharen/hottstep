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
        delay( 2 * totalLength / ( bars * divisionsInBar * 3) )
{
   lpfilter.setupLowpass( sampleRate, 1000, 1 );
   modfilter.setupLowpass( sampleRate, 1000, 1 );
}
void Helium::reset() {
   pos = 0;
   lpfilter.reset();
   delay.reset();
}

float Helium::tick() {
   int note = getNotes()[ pos / lengthPerDivision ] ;
   int placeInNote = pos % lengthPerDivision;
   float ret;
   float gain = 0;
   if( note < 0 || note > 127 ) {
      ret = 0;
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
      ret = sin( pitchTable[note] * placeInNote * 2 * M_PI / sampleRate ) ;
      if( ret > .7 )
         ret = .7;
      if( ret < -.7 )
         ret = -.7 ;
      ret *= gain;
      if( ret > .5 )
         ret = .5;
      if( ret < -.5 )
         ret = -.5 ;
      ret += n / 2.5;
   }
   //cout << p << " : " << ret << endl;
   ++pos;
   if( pos >= totalLength )
      pos = 0;

   //filter
   modfilter.setupLowpass( sampleRate, 200 + gain * 12000, .4 );
   lpfilter.setupLowpass( sampleRate, 1000 + 700*(1+sin( M_PI * 2 * pos / (float) lengthPerDivision ))/2 , 2 );
   ret = modfilter.process( ret );
   ret = lpfilter.process( ret );
   ret = delay.process( ret, .5 );
   return ret;
}

} //namespace synth
} //namepsace hotstep
