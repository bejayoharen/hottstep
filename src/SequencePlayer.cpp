#include "SequencePlayer.h"
#include <math.h>
#include <iostream>

using namespace std;

namespace hottstep {
namespace synth {

class SequencePlayer ;

SequencePlayer::SequencePlayer( float tempo, float sampleRate, int bars, int divisionsInBar )
      : pos(0), sampleRate(sampleRate), loopData( tempo, sampleRate, bars, divisionsInBar )
{
   totalLength = (int) ( ( sampleRate * bars * 4 * 60 ) / ( tempo ) ) ;
   lengthPerDivision = totalLength / ( bars * divisionsInBar );
   cout << totalLength << " : " << lengthPerDivision << endl;
   //p = 0;
   for( int i=0; i<127; ++i ) {
      pitchTable[i] = ( 440.0 / 32.0 ) * pow( 2, (i-9.0)/12.0 ) ;
   }
   setAdsr( 10, 10, .7, 10 );
}

void SequencePlayer::setAdsr( float attackMs, float decayMs, float sustainLevel, float releaseMs )
{
}

float SequencePlayer::tick() {
   int note = getNotes()[ pos / lengthPerDivision ] ;
   int placeInNote = pos % lengthPerDivision;
   float ret;
   if( note == -1 ) {
      ret = 0;
   } else {
      ret = sin( pitchTable[note] * placeInNote * 2 * M_PI / sampleRate )  * placeInNote / (float) lengthPerDivision ;
      if( ret > .6 )
         ret = .6;
      if( ret < -.6 )
         ret = -.6 ;
   }
   //cout << p << " : " << ret << endl;
   ++pos;
   if( pos >= totalLength )
      pos = 0;
   return ret;
}

} //namespace synth
} //namepsace hotstep
