#include "Audiofile.h++"

#include <AL/al.h>
#include <iostream>

Audiofile Audiofile::setFilename(std::string filename)
{   this->filename = filename;
    return *this;
}

std::string Audiofile::getFilename()
{   return filename;
}

/*
bool Audiofile::isFilenameGiven()
{   return filename.size() != 0;
}
*/

bool Audiofile::generateAlBuffer()
{   alGenBuffers(1, &al_buffer);
    ALenum error = alGetError();
    if(error) {
        std::cout << "[WARNING] alGenBuffers: " << alGetString(error) << "\n";
        return false;
    }
    return true;
}

void Audiofile::deleteAlBuffer()
{   alDeleteBuffers(1, &al_buffer);
}

unsigned int Audiofile::getAlBuffer()
{   return al_buffer;
}
