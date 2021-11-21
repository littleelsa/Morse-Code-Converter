#include "morse.h"

std::string getErrorCode(int errorCode) {
    /* Returns the error code as a string. 
    e.g. '7' -> 'ERROR 07: ', '21' -> 'ERROR 21: '.*/
    if (errorCode < 10)
        return "ERROR 0" + std::to_string(errorCode) + ": ";
    return "ERROR " + std::to_string(errorCode) + ": ";
}

namespace errorsLogging {
    /* Functions that log error messages to the console. */
    // User's input related errors
    void noArgumentsProvided(int errorCode) {
        std::cout << getErrorCode(errorCode) 
                  << "No arguments were provided to the program." << std::endl;  
    }

    void fileNamesMissing(int errorCode, int numFileNames) {
        std::cout << getErrorCode(errorCode) 
                  << numFileNames << (numFileNames == 1 ? " file name was" : " file names were") 
                  << " missing from the arguments lists." << std::endl;
    }

    void outputFileNameMissing(int errorCode) {
        std::cout << getErrorCode(errorCode) 
                  << "Output file name was missing from the arguments lists." << std::endl;
    }

    void unrecognizedCommands(int errorCode, char *command) {
        std::cout << getErrorCode(errorCode) 
                  << "Unrecognized command '" << command << "'." << std::endl;
    }

    void invalidCommands(int errorCode, char *command) {
        std::cout << getErrorCode(errorCode)
                  << "Invalid command '" << command << "'. Commands must start with hyphens (-)." << std::endl;
    }

    void conflictedCommands(int errorCode) {
        std::cout << getErrorCode(errorCode) 
                  << "Commands '-m' and '-t' can't be used together." << std::endl;
    }

    void duplicatedArguments(int errorCode, char * command) {
        std::cout << getErrorCode(errorCode) 
                  << "Argument '" << command << "' was included more than once." << std::endl;
    }

    void tooManyArguments(int errorCode) {
        std::cout << getErrorCode(errorCode) 
                  << "More than 4 arguments isn't allowed." << std::endl;
    }
    // Files' content related errors
    void fileNotExist(int errorCode, char fileName) {
        std::cout << getErrorCode(errorCode) 
                  << "File '" << fileName << "' doesn't exist." << std::endl;
    }

    void unrecognizedChar(int errorCode, char c, int lineNum) {
        std::cout << getErrorCode(errorCode) 
                  << "Unrecognized character '" << c 
                  << "' on line" << lineNum << '.' << std::endl;
    }

    void unrecognizedCode(int errorCode, char *code, int lineNum) {
        std::cout << getErrorCode(errorCode) 
                  << "Unrecognized morse code '" << code 
                  << "' on line" << lineNum << '.' << std::endl;
    }

    void invalidCodes(int errorCode, char *code, int lineNum) {
        std::cout << getErrorCode(errorCode) 
                  << "Invalid morse code '" << code
                  << "' on line" << lineNum << '.' << std::endl;
    }
}