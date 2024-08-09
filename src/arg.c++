#include "arg.h++"

#include <iostream>

int searchArg(std::string arg, bool *has_arg, int argc, char *argv[])
{   for(int i = 0; i < argc; i++) if(arg == argv[i])
    {   *has_arg = true;
        return i;
    }
    *has_arg = false;
    return 0;
}

bool argHelp(int argc, char *argv[])
{   bool has_arg;
    searchArg("-h", &has_arg, argc, argv);
    if(has_arg)
    {   std::cout <<
            "About: A simple CLI audio player.\n"
            "Usage: mu [option]... [file]...\n"
            "\n"
            "Options:\n"
            "  -h    Display this information and exit.\n"
            "  -V    Display version information and exit.\n"
            "  -v    Verbose (e.g. print what it\'s playing).\n"
            "\n"
            "Supported formats:\n"
            ".wav\n"
        ;
    }
    return has_arg;
}

bool argVersion(int argc, char *argv[])
{   bool has_arg;
    searchArg("-V", &has_arg, argc, argv);
    if(has_arg)
    {   std::cout <<
            "mu v.0.1\n";
    }
    return has_arg;
}

bool argVerbose(int argc, char *argv[])
{   bool has_arg;
    searchArg("-v", &has_arg, argc, argv);
    return has_arg;
}

std::vector<std::string> argFilenames(int argc, char *argv[])
{   std::vector<std::string> filenames;
    for(int i = 1; i < argc; i++)
    {   if(argv[i][0] != '-')
        {   filenames.push_back(argv[i]);
        }
    }
    return filenames;
}
