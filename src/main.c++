#include "Loaders.h++"
#include "Player.h++"
#include "arg.h++"

#include <AL/al.h>
#include <iostream>

std::vector<Audiofile> getAudiofilesFromFilenames(std::vector<std::string> filenames, Loaders *loaders)
{   std::vector<Audiofile> audiofiles;
    for(int i = 0; i < filenames.size(); i++)
    {   Audiofile audiofile = Audiofile().setFilename(filenames[i]);
        audiofile.setLoader(&loaders->wav_loader);
        audiofiles.push_back(audiofile);
    }
    return audiofiles;
}

int main(int argc, char *argv[]) {
    if(argHelp(argc, argv)) return 0;
    if(argVersion(argc, argv)) return 0;
    bool verbose = argVerbose(argc, argv);
    Loaders loaders;
    std::vector<Audiofile> audiofiles = getAudiofilesFromFilenames(argFilenames(argc, argv), &loaders);
// Play
    Player player;
    if(!player.isUsable()) return 0;
    for(int i = 0; i < audiofiles.size(); i++)
    {   player.play(audiofiles[i], verbose);
    }
    if(verbose) std::cout << "[PLAY] End of queue\n";
}
