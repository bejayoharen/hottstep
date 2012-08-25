#include "SequencePlayer.h"
#include "Filter.h"
#include <math.h>
#include <iostream>

using namespace std;

namespace hottstep {
namespace synth {

static int computeSamples( float milliseconds, float srate ) {
   return (int) ( ( milliseconds / 1000 ) * srate + .5 );
}

class SequencePlayer ;

SequencePlayer::SequencePlayer( float tempo, float sampleRate, int bars, int divisionsInBar )
      : pos(0), sampleRate(sampleRate), loopData( tempo, sampleRate, bars, divisionsInBar ),
        lpfilter(), modfilter()
{
   totalLength = (int) ( ( sampleRate * bars * 4 * 60 ) / ( tempo ) ) ;
   lengthPerDivision = totalLength / ( bars * divisionsInBar );
   //cout << totalLength << " : " << lengthPerDivision << endl;
   for( int i=0; i<127; ++i ) {
      pitchTable[i] = ( 440.0 / 32.0 ) * pow( 2, (i-9.0)/12.0 ) ;
   }
   setAdsr( 10, 10, .7, 10 );
   lpfilter.setupLowpass( sampleRate, 1000, 1 );
   modfilter.setupLowpass( sampleRate, 1000, 1 );
}
void SequencePlayer::reset() {
   pos = 0;
   lpfilter.reset();
}

void SequencePlayer::setAdsr( float attackMs, float decayMs, float sustainLevel, float releaseMs )
{
   attackSamples = computeSamples( attackMs, sampleRate );
   decaySamples  = computeSamples( decayMs, sampleRate );
   this->sustainLevel = sustainLevel;
   releaseSamples = computeSamples( releaseMs, sampleRate );
}

float SequencePlayer::tick() {
   int note = getNotes()[ pos / lengthPerDivision ] ;
   int placeInNote = pos % lengthPerDivision;
   float ret;
   float gain = 0;
   if( note == -1 ) {
      ret = 0;
   } else {
      gain = sustainLevel;
      if( placeInNote < attackSamples ) {
         gain = placeInNote / (float) attackSamples ;
      } else if( placeInNote < attackSamples + decaySamples ) {
         int p = placeInNote - attackSamples;
         float r = p / (float) decaySamples ;
         gain = ( 1 - r ) + sustainLevel * r ;
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
   }
   //cout << p << " : " << ret << endl;
   ++pos;
   if( pos >= totalLength )
      pos = 0;

   //filter
   modfilter.setupLowpass( sampleRate, 200 + gain * 1000, .5 );
   lpfilter.setupLowpass( sampleRate, 600 + 400*(1+sin( M_PI * 2 * pos / (float) lengthPerDivision ))/2 , 2 );
   ret = lpfilter.process( ret );
   return ret;
}

} //namespace synth
} //namepsace hotstep
