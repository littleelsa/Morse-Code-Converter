#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#define NUM_FILES 2
#define NUM_PROGRAM_COMMANDS 4
#define MAX_NUM_ARGS 4
enum ERROR_CODE {
    NO_ERROR,
    NO_ARGS_PROVIDED,
    FILE_NAMES_MISSING,
    UNRECOGNIZED_CMDS,
    INVALID_CMDS,
    CONFLICTED_CMDS,
    DUPLICATED_ARGS,
    TOO_MANY_ARGS,
    FILE_NOT_EXIST,
    UNRECOGNIZED_CHAR,
    UNRECOGNIZED_CODE,
    INVALID_CODES
};

// Functions that perform micelaneous tasks

int isRecognizableCommand(char *command);

int doesArgvIncludeCommand(int argc, char *argv[], std::string programCommand);

int isValidCommand(char *command);

int doesArgvIncludeCommand(int argc, char *argv[], std::string programCommand);

int countFileNames(int argc, char *argv[]);

std::vector<char *> getFileNames(int argc, char *argv[]);

std::vector<char *> getCommands(int argc, char *argv[]);

namespace errorsLogging {
    // Functions that log error messages to the console
    // User's input related errors
    void noArgumentsProvided(int errorCode);

    void fileNamesMissing(int errorCode, int numFileNames);

    void outputFileNameMissing(int errorCode);

    void unrecognizedCommands(int errorCode, char *command);

    void invalidCommands(int errorCode, char *command);

    void conflictedCommands(int errorCode);

    void duplicatedArguments(int errorCode, char * command);

    void tooManyArguments(int errorCode);

    // Files' content related errors
    void fileNotExist(int errorCode, char fileName);

    void unrecognizedChar(int errorCode, char c, int lineNum);

    void unrecognizedCode(int errorCode, char *code, int lineNum);

    void invalidCodes(int errorCode, char *code, int lineNum);
}

namespace errorsHandling {

    void noArgumentsProvided(int argc);

    void fileNamesMissing(int argc, char *argv[]);

    void unrecognizedCommands(int argc, char *argv[]);

    void invalidCommands(int argc, char *argv[]);

    void conflictedCommands(int argc, char *argv[]);

    void duplicatedArguments(int argc, char *argv[]);

    void tooManyArguments(int argc, char *argv[]);
}

namespace tasks {

    void convert(char *inFile, char *outFile);

    void convertMorse(char *inFile, char *outFile);

    void convertText(char *inFile, char *outFile);

    void help();

    void log();
}