#include "Player.h++"

#include <cstddef>

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
