#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>
#include <string>
#include <vector>

int searchArg(std::string arg, bool *has_arg, int argc, char *argv[])
{   for(int i = 0; i < argc; i++) if(arg == argv[i])
    {   *has_arg = true;
        return i;
    }
    *has_arg = false;
    return 0;
}

bool argHelp(int argc, char *argv[])
{   bool has_arg;
    searchArg("-h", &has_arg, argc, argv);
    if(has_arg)
    {   std::cout <<
            "About: A simple CLI audio player.\n"
            "Usage: mu [option]... [file]...\n"
            "\n"
            "Options:\n"
            "  -h    Display this information and exit.\n"
            "  -V    Display version information and exit.\n"
            "  -v    Verbose (e.g. print what it\'s playing).\n"
            "\n"
            "Supported formats:\n"
            ".wav\n"
        ;
    }
    return has_arg;
}

bool argVersion(int argc, char *argv[])
{   bool has_arg;
    searchArg("-V", &has_arg, argc, argv);
    if(has_arg)
    {   std::cout <<
            "mu v.0.1\n";
    }
    return has_arg;
}

bool argVerbose(int argc, char *argv[])
{   bool has_arg;
    searchArg("-v", &has_arg, argc, argv);
    return has_arg;
}

std::vector<std::string> argFilenames(int argc, char *argv[])
{   std::vector<std::string> filenames;
    for(int i = 1; i < argc; i++)
    {   if(argv[i][0] != '-')
        {   filenames.push_back(argv[i]);
        }
    }
    return filenames;
}

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

bool uloadWav(ALenum *format, ALvoid **data, ALsizei *size, ALsizei *freq, bool show_warn)
{   alutUnloadWAV(*format, *data, *size, *freq);
    ALenum error = alutGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alutUnloadWAV: " << alutGetErrorString(error) << "\n";
        return false;
    }
    return true;
}

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

bool bufferSource(ALuint *source, ALuint *buffer, bool show_warn)
{   alSourcei(*source, AL_BUFFER, *buffer);
    ALenum error = alGetError();
    if(error) {
        if(show_warn) std::cout <<
            "[WARNING] alSourcei: " << alGetString(error) << "\n";
        return false;
    }
    return true;
}

bool ubufferSource(ALuint *source, bool show_warn)
{   alSourcei(*source, AL_BUFFER, 0);
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
    uloadWav(&format, &data, &size, &freq, verbose);
    if(!bufferSource(source, buffer, verbose)) return;
    if(verbose) std::cout << "[PLAY] Playing ‘" << filename << "‘\n";
    alSourcePlay(*source);
    ALint state = AL_PLAYING;
    while(state == AL_PLAYING) {
        alGetSourcei(*source, AL_SOURCE_STATE, &state);
    }
    ubufferSource(source, verbose);
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
// Exit
    context = alcGetCurrentContext();
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
