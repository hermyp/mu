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
}

Player::~Player()
{   alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

bool bufferSource(ALuint source, ALuint buffer, bool show_warn)
{   alSourcei(source, AL_BUFFER, buffer);
    ALenum error = alGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alSourcei: " << alGetString(error) << "\n";
        return false;
    }
    return true;
}

bool ubufferSource(ALuint source, bool show_warn)
{   alSourcei(source, AL_BUFFER, 0);
    ALenum error = alGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alSourcei: " << alGetString(error) << "\n";
        return false;
    }
    return true;
}

void Player::play(Audiofile audiofile, unsigned int *source, bool verbose)
{   if(!audiofile.generateAlBuffer()) return;
    if(!audiofile.loadBuffer(verbose)) return;
    if(!bufferSource(*source, audiofile.getAlBuffer(), verbose)) return;
    if(verbose) std::cout << "[PLAY] Playing ‘" << audiofile.getFilename() << "‘\n";
    alSourcePlay(*source);
    ALint state = AL_PLAYING;
    while(state == AL_PLAYING) {
        alGetSourcei(*source, AL_SOURCE_STATE, &state);
    }
    ubufferSource(*source, verbose);
    audiofile.deleteAlBuffer();
}
