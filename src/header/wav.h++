#pragma once

#include <AL/al.h>
#include <string>

bool loadWav(std::string filename, ALenum *format, ALvoid **data, ALsizei *size, ALsizei *freq, ALboolean *loop, bool show_warn);
bool uloadWav(ALenum format, ALvoid *data, ALsizei size, ALsizei freq, bool show_warn);
