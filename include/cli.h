#ifndef LANGPROC_COMPILER_CLI_H
#define LANGPROC_COMPILER_CLI_H

#include <iostream>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

struct CommandLineArguments
{
    std::string compileSourcePath;
    std::string compileOutputPath;
};

void handler(int sig);
CommandLineArguments parse_command_line_args(int argc, char **argv);

#endif
