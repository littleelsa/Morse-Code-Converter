#include "morse.h"

// Value of which will be modified by input errors handling functions
bool areInputErrors = false;

int main(int argc, char *argv[]) {
    // Check for possible input errors
    errorsHandling::noArgumentsProvided(argc);
    errorsHandling::fileNamesMissing(argc, argv);
    errorsHandling::unrecognizedCommands(argc, argv);
    errorsHandling::invalidCommands(argc, argv);
    errorsHandling::conflictedCommands(argc, argv);
    errorsHandling::duplicatedArguments(argc, argv);
    errorsHandling::tooManyArguments(argc, argv);
    if (areInputErrors) {
        std::cout << "Type 'morse -h' for more help." << std::endl;
        return 1;
    }

    // Process the user's input
    std::vector<char *> fileNames = getFileNames(argc, argv);
    std::vector<char *> commands = getCommands(argc, argv);

    // Perform the program's main tasks
    // e. g. content conversion, help message, logging, etc.
    if (fileNames.size()) { 
        // Check for possible file opening errors
        errorsHandling::inputFileNotExist(fileNames[0]);
        errorsHandling::outputFileExist(fileNames[1]);
        if (!(doesArgvIncludeCommand(argc, argv, "-m") || doesArgvIncludeCommand(argc, argv, "-t"))) {
            // If input file type isn't specified, deduce type from file's content.
            tasks::convert(fileNames[0], fileNames[1]);
    }
    // Perform argument-specified tasks
    if (doesArgvIncludeCommand(argc, argv, "-m"))
        tasks::log();
    if (doesArgvIncludeCommand(argc, argv, "-t"))
        tasks::log();
    if (doesArgvIncludeCommand(argc, argv, "-h"))
        tasks::help();
    if (doesArgvIncludeCommand(argc, argv, "-c"))
        tasks::log();
    return 0;
}