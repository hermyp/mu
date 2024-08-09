#pragma once

#include "Audiofile.h++"

#include <AL/alc.h>
#include <string>

class Player {
public:
    Player();
    ~Player();
    void play(Audiofile audiofile, unsigned int *source, bool verbose);
private:
    ALCdevice *device;
    ALCcontext *context;
};
