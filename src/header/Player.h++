#pragma once

#include <AL/alc.h>

class Player {
public:
    Player();
    ~Player();
private:
    ALCdevice *device;
    ALCcontext *context;
};
