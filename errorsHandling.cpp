#include "morse.h"
#include "morse.h"

extern int areErrors;

namespace errorsHandling {
    // Functions that detect and handle errors
    // User's input related errors
    /* Check if no arguments were included. */
    void noArgumentsProvided(int argc) {
        if (argc == 1) {
            errorsLogging::noArgumentsProvided(NO_ARGS_PROVIDED);
            areErrors = 1;
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
            areErrors = 1;
        }
    }

    /* Check if the argument is one of program commands */
    void unrecognizedCommands(int argc, char *argv[]) {
        for (int i = 1; i < argc; i++) {
            if (!isRecognizableCommand(argv[i]) && isValidCommand(argv[i])) {
                errorsLogging::unrecognizedCommands(UNRECOGNIZED_CMDS, argv[i]);
                areErrors = 1;
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
                areErrors = 1;
            }
        }
    }

    /* Check if the user provided both '-m' and '-t' commands */
    void conflictedCommands(int argc, char *argv[]) {
        if (doesArgvIncludeCommand(argc, argv, "-m") && doesArgvIncludeCommand(argc, argv, "-t")) {
            errorsLogging::conflictedCommands(CONFLICTED_CMDS);
            areErrors = 1;
        }
    }

    /* Check if the argument is included more than once */
    void duplicatedArguments(int argc, char *argv[]) {
        for (int i = 1; i < argc; i++) {
            for (int j = i + 1; j < argc; j++) {
                if (!strcmp(argv[i], argv[j])) {
                    errorsLogging::duplicatedArguments(DUPLICATED_ARGS, argv[i]);
                    areErrors = 1;
                }
            }
        }
    }

    /* Check if more than 4 arguments were included */
    void tooManyArguments(int argc, char *argv[]) {
        if (argc > MAX_NUM_ARGS + 1) {
            errorsLogging::tooManyArguments(TOO_MANY_ARGS);
            areErrors = 1;
        }
    }
    // Files' content related errors.
}