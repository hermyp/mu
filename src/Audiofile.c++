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

void Audiofile::setLoader(Loader *loader)
{   this->loader = loader;
    loader_is_provided = true;
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

bool Audiofile::loadBuffer(bool verbose)
{   if(!loader_is_provided) return false;
    if(!loader->load(filename, verbose)) return false;
    if(!bufferData(al_buffer, loader->getFormat(), loader->getData(), loader->getSize(), loader->getFrequency(), verbose)) return false;
    loader->uload(verbose);
    return true;
}


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
