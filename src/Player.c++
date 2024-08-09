#include "Player.h++"

#include <AL/al.h>
#include <cstddef>
#include <iostream>

Player::Player()
{   device = alcOpenDevice(NULL);
    context;
    if(device) {
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);
    }
// Gen source
    alGenSources(1, &source);
    ALenum error = alGetError();
    if(error) {
        std::cout << "[ERROR] alGenBuffers: " << alGetString(error) << "\n";
        errors = true;
    }
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
}

Player::~Player()
{   alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

bool Player::isUsable()
{   return !errors;
}

bool Player::buffer_source(unsigned int buffer, bool show_warn)
{   alSourcei(source, AL_BUFFER, buffer);
    ALenum error = alGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alSourcei: " << alGetString(error) << "\n";
        return false;
    }
    return true;
}

bool Player::ubuffer_source(bool show_warn)
{   alSourcei(source, AL_BUFFER, 0);
    ALenum error = alGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alSourcei: " << alGetString(error) << "\n";
        return false;
    }
    return true;
}

void Player::play(Audiofile audiofile, bool verbose)
{   if(!audiofile.generateAlBuffer()) return;
    if(!audiofile.loadBuffer(verbose)) return;
    if(!buffer_source(audiofile.getAlBuffer(), verbose)) return;
    if(verbose) std::cout << "[PLAY] Playing ‘" << audiofile.getFilename() << "‘\n";
    alSourcePlay(source);
    ALint state = AL_PLAYING;
    while(state == AL_PLAYING) {
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }
    ubuffer_source(verbose);
    audiofile.deleteAlBuffer();
}
