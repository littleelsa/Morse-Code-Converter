#include "morse.h"

// Functions that detect and handle errors
namespace errorsHandling {
    /* Check if no arguments were included. */
    void noArgumentsProvided(int argc) {
        if (argc == 1) {
            errorsLogging::noArgumentsProvided(NO_ARGS_PROVIDED);
            areInputErrors = true;
        }
    }

    /* Check if file names were included in the arguments list. */
    void fileNamesMissing(int argc, char *argv[]) {
        int numFileNames = countFileNames(argc, argv);
        /* Does the user want to convert a file?
        Is FALSE if only '-h' is included as a command and no file names were provided */
        int doesNeedConversion = doesArgvIncludeCommand(argc, argv, "-t")
                              || doesArgvIncludeCommand(argc, argv, "-m")
                              || doesArgvIncludeCommand(argc, argv, "-c")
                              || numFileNames == 1;
        if (argc > 1 && doesNeedConversion && numFileNames < NUM_FILES) {
            // Check if '-h' was included in the arguments list. 
            // Had it not been, 2 file names must be included as arguments
            errorsLogging::fileNamesMissing(FILE_NAMES_MISSING, NUM_FILES - numFileNames);
            areInputErrors = true;
        }
    }

    /* Check if the argument is one of program commands */
    void unrecognizedCommands(int argc, char *argv[]) {
        for (int i = 1; i < argc; i++) {
            if (!isRecognizableCommand(argv[i]) && isValidCommand(argv[i])) {
                errorsLogging::unrecognizedCommands(UNRECOGNIZED_CMDS, argv[i]);
                areInputErrors = true;
                continue;
            }
        }
    }

    /* Check if the command is of correct form (a hyphen followed by a letter) */
    void invalidCommands(int argc, char *argv[]) {
        int nonCommandArgCount = 0;
        for (int i = 1; i < argc; i++) {
            if (!isValidCommand(argv[i])) {
                nonCommandArgCount++;
                if (nonCommandArgCount <= NUM_FILES)
                    // Ignore the first two non-command arguments (file names).
                    continue;
                errorsLogging::invalidCommands(INVALID_CMDS, argv[i]);
                areInputErrors = true;
            }
        }
    }

    /* Check if the user provided both '-m' and '-t' commands */
    void conflictedCommands(int argc, char *argv[]) {
        if (doesArgvIncludeCommand(argc, argv, "-m") && doesArgvIncludeCommand(argc, argv, "-t")) {
            errorsLogging::conflictedCommands(CONFLICTED_CMDS);
            areInputErrors = true;
        }
    }

    /* Check if the argument is included more than once */
    void duplicatedArguments(int argc, char *argv[]) {
        for (int i = 1; i < argc; i++) {
            for (int j = i + 1; j < argc; j++) {
                if (!strcmp(argv[i], argv[j])) {
                    errorsLogging::duplicatedArguments(DUPLICATED_ARGS, argv[i]);
                    areInputErrors = true;
                }
            }
        }
    }

    /* Check if more than 4 arguments were included */
    void tooManyArguments(int argc, char *argv[]) {
        if (argc > MAX_NUM_ARGS + 1) {
            errorsLogging::tooManyArguments(TOO_MANY_ARGS);
            areInputErrors = true;
        }
    }

    /* Check if the input file exists */
    void inputFileNotExist(std::string inFile) {
        if (!doesFileExist(inFile)) {
            errorsLogging::fileNotExist(FILE_NOT_EXIST, inFile);
            exit(FILE_NOT_EXIST);
        } 
    }

    /* Check if the output file exists */
    void outputFileExist(std::string outFile) {
        std::string willOverwrite;
        if (!doesFileExist(outFile))
            return;
        do {
            std::cout << "This file has already existed. Would you like to overwrite it? (y/n): ";
            std::cin >> willOverwrite;
            if (isResponseNo(willOverwrite)) {
                errorsLogging::fileExist(FILE_EXIST, outFile);
                exit(FILE_EXIST);
            }
            else if (isResponseYes(willOverwrite))
                return;
            else
                std::cout << "The response must be 'y' or 'n'." << std::endl;
        } while (!(isResponseYes(willOverwrite) || isResponseNo(willOverwrite)));
    }
}