#ifndef __LOOP_DATA_H
#define __LOOP_DATA_H

#include <vector>

using namespace std;

namespace hottstep {
namespace synth {

class LoopData {
 private:
   float tempo;
   float sampleRate;
   int bars;
   int divisionsInBar;
   vector< int > notes;

 public:
   LoopData( float tempo, float sampleRate, int bars, int divisionsInBar ) :
      tempo( tempo ),
      sampleRate( sampleRate ),
      bars( bars ),
      divisionsInBar( divisionsInBar ),
      notes( bars * divisionsInBar )
   {
      for( int i=0; i<bars*divisionsInBar; ++i )
         notes[i] = -1;
   }
   float getTempo() { return tempo; }
   float getSampleRate() { return sampleRate; }
   int getBars() { return bars; }
   int getDivisionsInBar() { return divisionsInBar; }
   inline vector<int>& getNotes() { return notes; }
} ;

} //namespace synth
} //namepsace hotstep

#endif //__LOOP_DATA_H
