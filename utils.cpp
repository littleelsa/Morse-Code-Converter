#include "morse.h"

std::string programCommands[NUM_PROGRAM_COMMANDS] = {"-m", "-t", "-h", "-c"};

// Functions that perform micellaneous tasks

/* Check if argument is one of program commands */
int isRecognizableCommand(char *command) {
    for (int i = 0; i < NUM_PROGRAM_COMMANDS; i++)
        if (command == programCommands[i])
            return 1;
    return 0;
}

/* Check if argument is one of program commands */
int isValidCommand(char *command) {
    return command[0] == '-' && isalpha(command[1]) && strlen(command) == 2;
}

/* Check if a specific command was included in the arguments list */
int doesArgvIncludeCommand(int argc, char *argv[], std::string programCommand) {
    for (int i = 0; i < argc; i++)
        if (argv[i] == programCommand)
            return 1;
    return 0;
}

/* Count the number of file names included in the argument list */
int countFileNames(int argc, char *argv[]) {
    int fileNameCount = 0;
    for (int i = 1; i < argc; i++) {
        if (!isRecognizableCommand(argv[i]))
            fileNameCount++;
    }
    return fileNameCount;
}

/* Store file names arguments into a vector */
std::vector<char *> getFileNames (int argc, char *argv[]) {
    std::vector<char *> fileNames;
    int fileNameCount = 0;
    for (int i = 1; i < argc; i++) {
        if (!isRecognizableCommand(argv[i]) && fileNameCount <= NUM_FILES) {
            fileNameCount++;
            fileNames.push_back(argv[i]);
        }
    }
    return fileNames;
}

/* Store commands arguments into a vector */
std::vector<char *> getCommands(int argc, char *argv[]) {
    std::vector<char *> commands;
    for (int i = 1; i < argc; i++) {
        if (isRecognizableCommand(argv[i])) {
            commands.push_back(argv[i]);
        }
    }
    return commands;
}