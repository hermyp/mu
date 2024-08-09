#include "Player.h++"
#include "arg.h++"

#include <AL/al.h>
#include <iostream>

std::vector<Audiofile> getAudiofilesFromFilenames(std::vector<std::string> filenames)
{   std::vector<Audiofile> audiofiles;
    for(int i = 0; i < filenames.size(); i++)
        audiofiles.push_back(Audiofile().setFilename(filenames[i]));
    return audiofiles;
}

int main(int argc, char *argv[]) {
    if(argHelp(argc, argv)) return 0;
    if(argVersion(argc, argv)) return 0;
    bool verbose = argVerbose(argc, argv);
    /*
    std::vector<std::string> filenames = argFilenames(argc, argv);
    if(filenames.size() == 0)
    {   std::cout << "[ERROR] No files provided\n";
        return 0;
    }
    */
    std::vector<Audiofile> audiofiles = getAudiofilesFromFilenames(argFilenames(argc, argv));
    Player player;

    ALenum error;
    alGetError();
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
    for(int i = 0; i < audiofiles.size(); i++)
    {   player.play(audiofiles[i], &source, verbose);
    }
    if(verbose) std::cout << "[PLAY] End of queue\n";
}
