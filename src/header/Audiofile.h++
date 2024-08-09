#pragma once

#include <string>

#define FILEFORMAT_NOT_SUPPORTED -1
#define FILEFORMAT_UNKNOWN 0
#define FILEFORMAT_WAV 1

class Audiofile {
// filename
public:
    Audiofile setFilename(std::string filename);
    std::string getFilename();
    bool isFilenameGiven();
private:
    std::string filename = "";

// file loader

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
