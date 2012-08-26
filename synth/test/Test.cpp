#include <math.h>

#include "SequencePlayer.h"
#include "Helium.h"
#include "Xenon.h"

#include "portaudio.h"

using namespace std;
using namespace hottstep::synth ;

#define NUM_SECONDS   (20)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)

static int paCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
{
    vector<SequencePlayer*>& sps = *(vector<SequencePlayer*> *) userData;
    float *out = (float*)outputBuffer;
    unsigned long i;

    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer;
    
    for( i=0; i<framesPerBuffer; i++ )
    {
        float l = 0;
        float r = 0;
        for( int j=0; j<sps.size(); ++j ) {
           float *ar = sps[j]->tick();
           l += ar[0];
           r += ar[1];
        }
        l /= sps.size();
        r /= sps.size();
        *out++ = l;  /* left */
        *out++ = r;  /* right */
    }
    
    return paContinue;
}



int main( int args, char **argv ) {
    Helium helium( 120, 44100, 2, 8 );
    Xenon xenon( 120, 44100, 2, 8 );
    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;
    int i;

    vector<SequencePlayer *> seq;
    seq.push_back( &helium );
    seq.push_back( &xenon );


    printf("\n\n");
    printf("Sequencer Test. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);
    
    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
      goto error;
    }
    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

/*
    seq.getNotes()[ 0]=48;
    seq.getNotes()[ 1]=51;
    seq.getNotes()[ 2]=53;
    seq.getNotes()[ 3]=55;
    seq.getNotes()[ 4]=58;
    seq.getNotes()[ 5]=60;
    seq.getNotes()[ 6]=63;
    seq.getNotes()[ 7]=65;
    seq.getNotes()[ 8]=67;
    seq.getNotes()[ 9]=70;
    seq.getNotes()[10]=72;
    seq.getNotes()[11]=75;
    seq.getNotes()[12]=77;
    seq.getNotes()[13]=79;
    seq.getNotes()[14]=82;
    seq.getNotes()[15]=84;
*/
    helium.getNotes()[ 0]=53;
    helium.getNotes()[ 1]=-1;
    helium.getNotes()[ 2]=48;
    helium.getNotes()[ 3]=-1;

    helium.getNotes()[ 4]=53;
    helium.getNotes()[ 5]=-1;
    helium.getNotes()[ 6]=-1;
    helium.getNotes()[ 7]=60;

    helium.getNotes()[ 8]=53;
    helium.getNotes()[ 9]=51;
    helium.getNotes()[10]=63;
    helium.getNotes()[11]=48;

    helium.getNotes()[12]=53;
    helium.getNotes()[13]=70;
    helium.getNotes()[14]=-1;
    helium.getNotes()[15]=-1;

    xenon.getNotes()[ 0]=48;
    xenon.getNotes()[ 1]=-1;
    xenon.getNotes()[ 2]=60;
    xenon.getNotes()[ 3]=-1;

    xenon.getNotes()[ 4]=48;
    xenon.getNotes()[ 5]=-1;
    xenon.getNotes()[ 6]=55;
    xenon.getNotes()[ 7]=-1;

    xenon.getNotes()[ 8]=48;
    xenon.getNotes()[ 9]=-1;
    xenon.getNotes()[10]=60;
    xenon.getNotes()[11]=55;

    xenon.getNotes()[12]=48;
    xenon.getNotes()[13]=53;
    xenon.getNotes()[14]=55;
    xenon.getNotes()[15]=60;

    for( int i=0; i<xenon.getNotes().size(); ++i )
       xenon.getNotes()[i] -= 24 ; // down two octaves


    err = Pa_OpenStream(
              &stream,
              NULL, /* no input */
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              paCallback,
              &seq );
    if( err != paNoError ) goto error;

    //sprintf( data.message, "No Message" );
    //err = Pa_SetStreamFinishedCallback( stream, &StreamFinished );
    //if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    printf("Play for %d seconds.\n", NUM_SECONDS );
    Pa_Sleep( NUM_SECONDS * 1000 );

    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    Pa_Terminate();
    printf("Test finished.\n");
    
    return err;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;
}
