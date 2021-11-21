#include "morse.h"

int areErrors = 0;

int main(int argc, char *argv[]) {
    // Check for possible input errors
    errorsHandling::noArgumentsProvided(argc);
    errorsHandling::fileNamesMissing(argc, argv);
    errorsHandling::unrecognizedCommands(argc, argv);
    errorsHandling::invalidCommands(argc, argv);
    errorsHandling::conflictedCommands(argc, argv);
    errorsHandling::duplicatedArguments(argc, argv);
    errorsHandling::tooManyArguments(argc, argv);
    if (areErrors) {
        std::cout << "Type 'morse -h' for more help." << std::endl;
        return 1;
    }

    // Process the user's input
    std::vector<char *> fileNames = getFileNames(argc, argv);
    std::vector<char *> commands = getCommands(argc, argv);

    // Perform the program's main tasks
    // e. g. content conversion, help message, logging, etc.
    if (fileNames.size() 
    && !doesArgvIncludeCommand(argc, argv, "-m") 
    && !doesArgvIncludeCommand(argc, argv, "-t")) {
        // If input file type isn't specified, deduce type from file's content.
        tasks::convert(fileNames[0], fileNames[1]);
    }
    for (int i = 0; i < commands.size(); i++) {
        // Perform argument-specified tasks
        switch (commands[i][1]) {
        case 'm':
            tasks::convertMorse(fileNames[0], fileNames[1]);
            break;
        case 't':
            tasks::convertText(fileNames[0], fileNames[1]);
            break;
        case 'h':
            tasks::help();
            break;
        case 'c':
            tasks::log();
            break;
        }
    }
    return 0;
}