#include "AudioManager.h"
#include <stdio.h>
#include <string.h>

#define F_NAME "wavdata/FancyPants.wav"
AudioManager::AudioManager(){
	init();
}

void AudioManager::init(){
	bool ready=true;
	/*
	device = alcOpenDevice(NULL);
	if(!device){
        fprintf(stderr, "Oops. can't initialize Audio Manager\n");
        ready=false;
    }else{
    	ctx = alcCreateContext(device, NULL);
    	alcMakeContextCurrent(ctx);
    	if(!ctx){
    		ready=false;
    	}
    }*/

    if(ready){
    	printf("Audio manager initialized\n");
    }
}

void AudioManager::test(){
	printf("Testing sound.....\n");
	
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	// Velocity of the source sound.
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };

	// Position of the listener.
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

	// Velocity of the listener.
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

	// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

	ALenum format;
	ALsizei size;
	ALsizei freq;
	ALvoid* data;
	ALboolean loop;

	
	//alutLoadWAVFile(F_NAME, &format, &data, &size, &freq, &loop);
	printf("Done!\n");
}