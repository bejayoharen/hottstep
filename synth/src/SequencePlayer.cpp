#include "SequencePlayer.h"
#include <iostream>
#include <math.h>

using namespace std;

namespace hottstep {
namespace synth {

class SequencePlayer ;

SequencePlayer::SequencePlayer( float tempo, float sampleRate, int bars, int divisionsInBar )
      : pos(0),
        totalLength( (int) ( ( sampleRate * bars * 4 * 60 ) / ( tempo ) ) ),
        lengthPerDivision( totalLength / ( bars * divisionsInBar ) ),
        sampleRate(sampleRate),
        loopData( tempo, sampleRate, bars, divisionsInBar )
{
   for( int i=0; i<128; ++i ) {
      pitchTable[i] = ( 440.0 / 32.0 ) * pow( 2, (i-9.0)/12.0 ) ;
   }
   setAdsr( 10, 10, .7, 10 );
}

void SequencePlayer::setAdsr( float attackMs, float decayMs, float sustainLevel, float releaseMs )
{
   attackSamples = computeSamples( attackMs );
   decaySamples  = computeSamples( decayMs );
   this->sustainLevel = sustainLevel;
   releaseSamples = computeSamples( releaseMs );
}

} //namespace synth
} //namepsace hotstep
