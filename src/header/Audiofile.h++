#pragma once

#include "Loader.h++"
#include "fileformats.h++"

#include <string>

class Audiofile {
// filename
public:
    Audiofile setFilename(std::string filename);
    std::string getFilename();
    bool isFilenameGiven();
private:
    std::string filename = "";

// file loader
public:
    void setLoader(Loader *loader);
    bool loadBuffer(bool verbose);
private:
    bool loader_is_provided = false;
    Loader *loader;

// fileformat
public:
    Audiofile detectFileformat();
    int getFileformat();
private:
    int file_format = FILEFORMAT_UNKNOWN;

// AL buffer
public:
    bool generateAlBuffer();
    void deleteAlBuffer();
    unsigned int getAlBuffer();
private:
    unsigned int al_buffer = 0;
};
