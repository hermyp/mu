#include "Player.h++"
#include "arg.h++"
#include "wav.h++"

#include <AL/al.h>
#include <iostream>

bool bufferData(ALuint buffer, ALenum format, ALvoid *data, ALsizei size, ALsizei freq, bool show_warn)
{   alBufferData(buffer, format, data, size, freq);
    ALenum error = alGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alBufferData: " << alGetString(error) << " (" << error << ")" << "\n";
        return false;
    }
    return true;
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

void play(std::string filename, ALuint *buffer, ALuint *source, bool verbose)
{   ALenum format;
    ALvoid *data;
    ALsizei size;
    ALsizei freq;
    ALboolean loop;
    if(!loadWav(filename, &format, &data, &size, &freq, &loop, verbose)) return;
    if(!bufferData(*buffer, format, data, size, freq, verbose)) return;
    uloadWav(format, data, size, freq, verbose);
    if(!bufferSource(*source, *buffer, verbose)) return;
    if(verbose) std::cout << "[PLAY] Playing ‘" << filename << "‘\n";
    alSourcePlay(*source);
    ALint state = AL_PLAYING;
    while(state == AL_PLAYING) {
        alGetSourcei(*source, AL_SOURCE_STATE, &state);
    }
    ubufferSource(*source, verbose);
}

int main(int argc, char *argv[]) {
    if(argHelp(argc, argv)) return 0;
    if(argVersion(argc, argv)) return 0;
    bool verbose = argVerbose(argc, argv);
    std::vector<std::string> filenames = argFilenames(argc, argv);
    if(filenames.size() == 0)
    {   std::cout << "[ERROR] No files provided\n";
        return 0;
    }
    Player player;

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
// Gen source
    ALuint source;
    alGenSources(1, &source);
    error = alGetError();
    if(error) {
        std::cout << "[ERROR] alGenBuffers: " << alGetString(error) << "\n";
        return 0;
    }
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);
// Play
    for(int i = 0; i < filenames.size(); i++)
    {   play(filenames[i], &buffer, &source, verbose);
    }
    if(verbose) std::cout << "[PLAY] End of queue\n";
}
