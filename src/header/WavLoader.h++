#pragma once

#include "Loader.h++"

class WavLoader : public Loader {
public:
    virtual bool load(std::string filename, bool verbose);
    virtual bool uload(bool verbose);
};
