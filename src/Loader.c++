#include "Loader.h++"

#include <iostream>

bool Loader::load(std::string filename, bool verbose)
{   return false;
}

bool Loader::uload(bool verbose)
{   return false;
}

ALenum Loader::getFormat() {return format;}
ALvoid* Loader::getData() {return data;}
ALsizei Loader::getSize() {return size;}
ALsizei Loader::getFrequency() {return freq;}
