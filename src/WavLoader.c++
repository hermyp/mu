#include "WavLoader.h++"

#include <AL/alut.h>
#include <iostream>

bool WavLoader::load(std::string filename, bool verbose)
{   ALboolean loop;
    alutLoadWAVFile((ALbyte*)&filename[0], &format, &data, &size, &freq, &loop);
    ALenum error = alutGetError();
    if(error) {
        if(verbose) std::cout <<
            "[WARNING] Failed to load ‘" << filename << "‘: " << alutGetErrorString(error) << "\n";
        return false;
    }
    return true;
}

bool WavLoader::uload(bool verbose)
{   alutUnloadWAV(format, data, size, freq);
    ALenum error = alutGetError();
    if(error) {
        if(verbose) std::cout <<
            "[WARNING] alutUnloadWAV: " << alutGetErrorString(error) << "\n";
        return false;
    }
    return true;
}
