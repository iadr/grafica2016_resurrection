#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <AL/al.h>
//#include <AL/alu.h>
#include <AL/alc.h>
#include <AL/alut.h>
class AudioManager{
private:
	ALCdevice *device;
	ALCcontext *ctx;

	ALuint Buffer;
	ALuint Source;
public:
	AudioManager();
	~AudioManager();
	
	void init();
	void test();
};
#endif