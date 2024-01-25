#include <fstream>
#include <iostream>
#include <unistd.h>

#include "cli.h"
#include "ast.hpp"

extern FILE *yyin;

int main(int argc, char **argv)
{
    // Parse CLI arguments to fetch the source file to compile and the path to output to.
    // This retrives [source-file.c] and [dest-file.s], when the compiler is invoked as follows:
    // ./bin/c_compiler -S [source-file.c] -o [dest-file.s]
    auto commandLineArguments = parse_command_line_args(argc, argv);

    // Configure Flex to read from the compileSourcePath file instead of reading from stdin.
    yyin = fopen(commandLineArguments.compileSourcePath.c_str(), "r");
    if (yyin == NULL)
    {
        perror("Could not open source file");
        return 1;
    }

    // Open the output files in truncation mode (to overwrite the contents)
    std::ofstream compiledOutput, prettyPrintOutput;
    compiledOutput.open(commandLineArguments.compileOutputPath, std::ios::trunc);

    auto prettyPrintOutputPath = commandLineArguments.compileOutputPath + ".printed";
    prettyPrintOutput.open(prettyPrintOutputPath, std::ios::trunc);

    // Parse the input source file
    std::cout << "Parsing: " << commandLineArguments.compileSourcePath << std::endl;
    auto root = parseAST();
    std::cout << "AST parsing complete" << std::endl;

    if (root == nullptr)
    {
        // Check something was actually returned by parseAST().
        std::cerr << "The root of the AST was a null pointer. Likely the root was never initialised correctly during parsing." << std::endl;
        return 3;
    }

    // Output the pretty print version of what was parsed to the .printed output
    // file.
    std::cout << "Printing parsed AST..." << std::endl;
    root->print(prettyPrintOutput);
    prettyPrintOutput.close();
    std::cout << "Printed parsed AST to: " << prettyPrintOutputPath << std::endl;

    // Compile from the root of the AST and output this to the compiledOutput
    // file.
    std::cout << "Compiling parsed AST..." << std::endl;
    root->compile(compiledOutput);
    compiledOutput.close();
    std::cout << "Compiled to: " << commandLineArguments.compileOutputPath << std::endl;

    // Clean up afterwards.
    delete root;
    return 0;
}
