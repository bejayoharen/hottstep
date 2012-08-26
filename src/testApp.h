#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SequencePlayer.h"

using namespace std;
using namespace hottstep::synth;

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp {
	public:
        testApp();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        int mapToMidi(float currentValue);

		ofTrueTypeFont font;
		ofxOscReceiver receiver;

		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		int mouseX, mouseY;
		string mouseButtonState;
    
        void audioOut(float * input, int bufferSize, int nChannels);
        
        
        ofSoundStream soundStream;
        
        float 	pan;
        int		sampleRate;
        bool 	bNoise;
        float 	volume;
        
        vector <float> lAudio;
        vector <float> rAudio;
        
        //------------------- for the simple sine wave synthesis
        float 	targetFrequency;
        float 	phase;
        float 	phaseAdder;
        float 	phaseAdderTarget;
        
        SequencePlayer seq;
        
        int i;
        
        int midi_notes[];
        
};
