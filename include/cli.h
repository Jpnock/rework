#ifndef LANGPROC_COMPILER_CLI_H
#define LANGPROC_COMPILER_CLI_H

#include <iostream>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig);
int parse_command_line_args(int argc, char **argv, std::string &sourcePath, std::string &outputPath);

#endif
