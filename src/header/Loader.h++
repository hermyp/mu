#pragma once

#include <AL/al.h>
#include <string>

class Loader {
public:
    virtual bool load(std::string filename, bool verbose);
    virtual bool uload(bool verbose);
    ALenum getFormat();
    ALvoid* getData();
    ALsizei getSize();
    ALsizei getFrequency();
protected:
    ALenum format;
    ALvoid *data;
    ALsizei size;
    ALsizei freq;
};
