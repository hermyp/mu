#pragma once

#include "Audiofile.h++"

#include <AL/alc.h>
#include <string>

class Player {
public:
    Player();
    ~Player();
    bool isUsable();
    void play(Audiofile audiofile, bool verbose);
private:
    bool buffer_source(unsigned int buffer, bool verbose);
    bool ubuffer_source(bool verbose);
private:
    bool errors = false;
    ALCdevice *device;
    ALCcontext *context;
    ALuint source;
};
