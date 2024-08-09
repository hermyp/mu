#include "wav.h++"

#include <AL/alut.h>
#include <iostream>

bool loadWav(std::string filename, ALenum *format, ALvoid **data, ALsizei *size, ALsizei *freq, ALboolean *loop, bool show_warn)
{   alutLoadWAVFile((ALbyte*)&filename[0], format, data, size, freq, loop);
    ALenum error = alutGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] Failed to load ‘" << filename << "‘: " << alutGetErrorString(error) << "\n";
        return false;
    }
    return true;
}

bool uloadWav(ALenum format, ALvoid *data, ALsizei size, ALsizei freq, bool show_warn)
{   alutUnloadWAV(format, data, size, freq);
    ALenum error = alutGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alutUnloadWAV: " << alutGetErrorString(error) << "\n";
        return false;
    }
    return true;
}
