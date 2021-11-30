#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cctype>
#include <cstring>
#include <chrono>
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
    OPEN_INPUT,
    OVERWRITE_OUTPUT,
    UNRECOGNIZED_CHARS,
    UNRECOGNIZED_CODES,
    INVALID_CODES
};
enum FILE_TYPE {
    PLAIN_TEXT,
    MORSE_CODE
};

// Functions that perform micellaneous tasks

int isRecognizableCommand(std::string command);

int isValidCommand(std::string command);

int doesArgvIncludeCommand(int argc, char *argv[], std::string programCommand);

int doesArgvIncludeCommand(int argc, char *argv[], std::string programCommand);

int countFileNames(int argc, char *argv[]);

int isMorseChar(char c);

int getFileType(std::string fileName);

std::vector<char *> getFileNames(int argc, char *argv[]);

std::vector<char *> getCommands(int argc, char *argv[]);

std::string CurrentTime();

std::string charToString(char c);

int wrongMorseFormat(std::string morseCode);

struct convertError;

// Functions that log error messages to the console
namespace errorsLogging {
    
    // User's input related errors
    void noArgumentsProvided(int errorCode);

    void fileNamesMissing(int errorCode, int numFileNames);

    void outputFileNameMissing(int errorCode);

    void unrecognizedCommands(int errorCode, std::string command);

    void invalidCommands(int errorCode, std::string command);

    void conflictedCommands(int errorCode);

    void duplicatedArguments(int errorCode, std::string command);

    void tooManyArguments(int errorCode);

    void fileNotExist(int errorCode, char fileName);

    void openInput(int errorCode, std::string inFile);

    void overwriteOutput(int errorCode, std::string outFile);

    void unrecognizedChars(int errorCode, int lineNum, char c);

    void unrecognizedCodes(int errorCode, int lineNum, std::string code);

    void invalidCodes(int errorCode, int lineNum, std::string code);

    void convertErrors(int errorCode);

}

namespace errorsHandling {

    void noArgumentsProvided(int argc);

    void fileNamesMissing(int argc, char *argv[]);

    void unrecognizedCommands(int argc, char *argv[]);

    void invalidCommands(int argc, char *argv[]);

    void conflictedCommands(int argc, char *argv[]);

    void duplicatedArguments(int argc, char *argv[]);

    void tooManyArguments(int argc, char *argv[]);

    void openInput(std::string inFile);

    void overwriteOutput(std::string output_file_name);
}

namespace tasks {

    void convertMorse(std::string inFile, std::string outFile);

    void convertText(std::string inFile, std::string outFile);

    void convert(std::string inFile, std::string outFile);

    void help();

    void log(std::string inFile, std::string outFile);

    void printConvertError(int errorCode);
}