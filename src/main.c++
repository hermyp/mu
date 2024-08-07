#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
//#include "AudioFile.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
// Init
    ALCdevice *device = alcOpenDevice(NULL);
    ALCcontext *context;
    if(device) {
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);
    }

    ALenum error;
    alGetError();
// Gen buf
    ALuint buffer;
    alGenBuffers(1, &buffer);
    error = alGetError();
    if(error) {
        std::cout << "[ERROR] alGenBuffers: " << alGetString(error) << "\n";
        return 0;
    }
// Load wav
    std::string filename = "test.wav";
    ALenum format;
    ALvoid *data;
    ALsizei size;
    ALsizei freq;
    ALboolean loop;
    ALuint sndBuffer;
    alutLoadWAVFile((ALbyte*)&filename[0], &format, &data, &size, &freq, &loop);
    error = alutGetError();
    if(error) {
        std::cout << "[ERROR] alutLoadWAVFile: " << alutGetErrorString(error) << "\n";
        return 0;
    }
// Copy wav data to buf
    alBufferData(buffer, format, data, size, freq);
    error = alGetError();
    if(error) {
        std::cout << "[ERROR] alBufferData: " << alGetString(error) << "\n";
        return 0;
    }
// Uload wav
    alutUnloadWAV(format, data, size, freq);
    error = alutGetError();
    if(error) {
        std::cout << "[ERROR] alutUnloadWAV: " << alutGetErrorString(error) << "\n";
        return 0;
    }
// Gen source
    ALuint source;
    alGenSources(1, &source);
    error = alGetError();
    if(error) {
        std::cout << "[ERROR] alGenBuffers: " << alGetString(error) << "\n";
        return 0;
    }
// Attach buf to source
    alSourcei(source, AL_BUFFER, buffer);
    error = alGetError();
    if(error) {
        std::cout << "[ERROR] alSourcei: " << alGetString(error) << "\n";
        return 0;
    }
// Source params
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
// Play
    alSourcePlay(source);
    ALint play_state = AL_PLAYING;
    while(play_state == AL_PLAYING) {
        alGetSourcei(source, AL_SOURCE_STATE, &play_state);
    }
// Exit
    context = alcGetCurrentContext();
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
