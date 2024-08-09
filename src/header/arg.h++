#pragma once

#include <string>
#include <vector>

int searchArg(std::string arg, bool *has_arg, int argc, char *argv[]);

bool argHelp(int argc, char *argv[]);
bool argVersion(int argc, char *argv[]);
bool argVerbose(int argc, char *argv[]);

std::vector<std::string> argFilenames(int argc, char *argv[]);
