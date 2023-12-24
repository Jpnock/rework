#include <fstream>
#include <iostream>
#include <unistd.h>

#include "cli.h"
#include "ast.hpp"

void compile(std::ostream &w)
{
    w << ".text" << std::endl;
    w << ".globl f" << std::endl;
    w << std::endl;

    w << "f:" << std::endl;
    w << "addi  t0, zero, 0" << std::endl;
    w << "addi  t0, t0,   5" << std::endl;
    w << "add   a0, zero, t0" << std::endl;
    w << "ret" << std::endl;
}

extern FILE *yyin;

int main(int argc, char **argv)
{
    // Parse CLI arguments, to fetch the values of the source and output files.
    std::string sourcePath = "";
    std::string compiledOutputPath = "";
    if (parse_command_line_args(argc, argv, sourcePath, compiledOutputPath))
    {
        return 1;
    }
    auto printedOutputPath = compiledOutputPath + ".printed";

    // This configures Flex to look at sourcePath instead of
    // reading from stdin.
    yyin = fopen(sourcePath.c_str(), "r");
    if (yyin == NULL)
    {
        perror("Could not open source file");
        return 1;
    }

    // Open the output file in truncation mode (to overwrite the contents)
    std::ofstream compiledOutput, describeOutput;
    compiledOutput.open(compiledOutputPath, std::ios::trunc);
    describeOutput.open(printedOutputPath, std::ios::trunc);

    // Compile the input
    std::cout << "Compiling: " << sourcePath << std::endl;

    auto root = parseAST();
    std::cout << "AST parsing complete" << std::endl;

    if (root == nullptr)
    {
        std::cerr << "The root of the AST was a null pointer. Likely the root was never initialised correctly during parsing." << std::endl;
        return 2;
    }

    root->print(describeOutput);
    compiledOutput.close();
    std::cout << "Printed to: " << printedOutputPath << std::endl;

    Context ctx;
    root->compile(ctx, compiledOutput);
    describeOutput.close();

    std::cout << "Compiled to: " << compiledOutputPath << std::endl;

    return 0;
}
