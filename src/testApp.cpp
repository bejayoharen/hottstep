#include "testApp.h"

using namespace std;
using namespace hottstep::synth;

testApp::testApp():seq( 120, 44100, 2, 8 ){}

//--------------------------------------------------------------
void testApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";

	ofBackground(30, 30, 130);
    
    // 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)
	
	int bufferSize		= 512;
	sampleRate 			= 44100;
	phase 				= 0;
	phaseAdder 			= 0.0f;
	phaseAdderTarget 	= 0.0f;
	volume				= 0.1f;
	bNoise 				= false;
    
	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
    
    midi_notes[0] = 48;
    midi_notes[1] = 51;
    midi_notes[2] = 53;
    midi_notes[3] = 55;
    midi_notes[4] = 58;
    midi_notes[5] = 60;
    midi_notes[6] = 63;
    midi_notes[7] = 65;
    midi_notes[8] = 67;
    midi_notes[9] = 70;
    midi_notes[10] = 72;
    midi_notes[11] = 75;
    midi_notes[12] = 77;
    midi_notes[13] = 79;
    midi_notes[14] = 82;
    midi_notes[15] = 84;
	
	//soundStream.listDevices();
	
	//if you want to set the device id to be different than the default
	//soundStream.setDeviceID(1); 	//note some devices are input only and some are output only 
    
	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
    
	ofSetFrameRate(60);
    
//    seq.getNotes()[0]=64;
//    seq.getNotes()[2]=65;
//    seq.getNotes()[4]=66;
//    seq.getNotes()[6]=64;

}

//--------------------------------------------------------------
void testApp::update(){

	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		// check for slider 1
		if(m.getAddress() == "/fuck/0"){
            float value = m.getArgAsFloat(0);
//            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
//            int midi_note = midi_notes[ mapToMidi(value) ];
//            cout << "midi note: " << note_index << endl;
            seq.getNotes()[0]= midi_notes[note_index];
		}
		// check for slider 2
		else if(m.getAddress() == "/fuck/1"){
            float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[1]= midi_notes[note_index];
		}
        // check for slider 3
		else if(m.getAddress() == "/fuck/2"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[2]= midi_notes[note_index];
		}
        // check for slider 4
		else if(m.getAddress() == "/fuck/3"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[3]= midi_notes[note_index];
		}
        // check for slider 5
		else if(m.getAddress() == "/fuck/4"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[4]= midi_notes[note_index];
		}
        // check for slider 6
		else if(m.getAddress() == "/fuck/5"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[5]= midi_notes[note_index];
		}
        // check for slider 7
		else if(m.getAddress() == "/fuck/6"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[6]= midi_notes[note_index];
		}
        // check for slider 8
		else if(m.getAddress() == "/fuck/7"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[7]= midi_notes[note_index];
		}
        // check for slider 9
		else if(m.getAddress() == "/fuck/8"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[8]= midi_notes[note_index];
		}
        // check for slider 10
		else if(m.getAddress() == "/fuck/9"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[9]= midi_notes[note_index];
		}
        // check for slider 11
		else if(m.getAddress() == "/fuck/10"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[10]= midi_notes[note_index];
		}
        // check for slider 12
		else if(m.getAddress() == "/fuck/11"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[11]= midi_notes[note_index];
		}
        // check for slider 13
		else if(m.getAddress() == "/fuck/12"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[12]= midi_notes[note_index];
		}
        // check for slider 14
		else if(m.getAddress() == "/fuck/13"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[13]= midi_notes[note_index];
		}
        // check for slider 15
		else if(m.getAddress() == "/fuck/14"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[14]= midi_notes[note_index];
		}
        // check for slider 16
		else if(m.getAddress() == "/fuck/15"){
			float value = m.getArgAsFloat(0);
            //            cout << "currentValue: " << value << endl;
            int note_index = (int) ofMap(value, 18, 287, 0, 15);
            //            int midi_note = midi_notes[ mapToMidi(value) ];
            //            cout << "midi note: " << note_index << endl;
            seq.getNotes()[15]= midi_notes[note_index];
		}
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}

	}
}


//--------------------------------------------------------------
void testApp::draw(){

	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);

	// draw mouse state
	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
	ofDrawBitmapString(buf, 430, 20);
	ofDrawBitmapString(mouseButtonState, 580, 20);

	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
    //    printf("Play for %d seconds.\n", NUM_SECONDS );
    
    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
    for (int i = 0; i < bufferSize; i++){
        float sample = seq.tick();
        lAudio[i] = output[i*nChannels    ] = sample * volume;
        rAudio[i] = output[i*nChannels + 1] = sample * volume;
    }
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
int testApp::mapToMidi(float currentValue)
{
    int currentNote = (int) ofMap(currentValue, 18, 287, 0, 15);
    return currentNote;
}