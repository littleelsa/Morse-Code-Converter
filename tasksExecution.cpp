#include "morse.h"

// Conversion metrics
int charCount = 0;
int wordCount = 0;
int lineCount = 1;
int charErrorCount = 0;
int wordErrorCount = 0;
bool existWordError = false;
double conversionDuration = 0;

struct morseError {
    int lineNum;
    std::string error;
};

struct textError {
    int lineNum;
    char error;
};

std::vector <morseError> morseErrorList;
std::vector <textError> textErrorList;

/* A map from ASCII characters to Morse code */
extern std::map<char, std::string> asciiToMorse; 

/* A map from Morse code to ASCII character */
extern std::map<std::string, char> morseToAscii;

const std::string helpMessage =
    "+----------------------------------------------------------------------------------------+\n"
    "|                                 MORSE CODE CONVERTER                                   |\n"
    "+----------------------------------------------------------------------------------------+\n"
    "|'morse' is a command line tool for Morse code conversion.                               |\n"
    "|                                                                                        |\n"
    "|Usage: ./morse [input file] [output file] [options]                                     |\n"
    "|                                                                                        |\n"
    "|Positional arguments: [input file] [output file]                                        |\n"
    "|*positional arguments should only be omitted had the user called the '-h' command only.*|\n"
    "|                                                                                        |\n"
    "|Optionsal arguments:                                                                    |\n"
    "|  -m  | Force the program to read the input file as Morse code                          |\n"
    "|  -t  | Force the program to read the input file as plain text                          |\n"
    "|  -h  | Write the help message to the console and a help.txt file                       |\n"
    "|  -c  | Write the conversion information to a log file                                  |\n"
    "|*One shouldn't provide the program with more than 4 arguments.*                         |\n"
    "|*The '-m' and '-t commands shouldn't be used together.*                                 |\n"
    "+----------------------------------------------------------------------------------------+\n";

/* Check for error and convert morse code */
void handleMorse(std::string morseCode,std::ofstream& outStream);

// Functions that process strings used for logging information
std::string removeExtention(std::string fileName);
std::string getCurrentTime();
std::string getLogTime();

// Functions that perform the program main tasks
namespace tasks {

    /* Convert morse code file to plain text file */
    void convertMorse(std::string inFile, std::string outFile) {
        auto t_start = std::chrono::high_resolution_clock::now();
        char c;
        std::string morseCode = "";
        std::ifstream inStream(inFile, std::ios::in);    
        std::ofstream outStream(outFile, std::ios::out);
        while (inStream.get(c)) {
            if (c!=' ' && c!='/' && c!='\n') {
                    morseCode += c;
                    if (inStream.peek() == EOF) {
                        handleMorse(morseCode,outStream);
                        wordCount++;
                        if (existWordError) {
                                wordErrorCount++;
                                existWordError = false;
                            }
                    }
            }
            
            else {
                switch (c) {
                    case ' ':
                        handleMorse(morseCode, outStream);
                        if (inStream.peek() == EOF && morseCode != "") {
                            wordCount++;
                        }
                        break;
                    case '/':
                        handleMorse(morseCode, outStream);
                        if (morseCode != "") {
                            wordCount++;
                        }
                        outStream << ' ';
                        
                        if (existWordError) {
                            wordErrorCount++;
                            existWordError = false;
                        }
                        break;
                    case '\n': 
                        handleMorse(morseCode, outStream);
                        if (morseCode != "") {
                            wordCount++;
                        }
                        lineCount++;
                        outStream << '\n';
                    
                        if (existWordError) {
                            wordErrorCount++;
                            existWordError = false;
                        }
                        break;
                }
                morseCode = ""; 
            }
        }
        inStream.close();
        outStream.close();
        auto t_end = std::chrono::high_resolution_clock::now();
        conversionDuration = std::chrono::duration<double, std::milli> (t_end - t_start).count();
    }

    /* Convert plain text file to morse code file */
    void convertText(std::string inFile, std::string outFile) {
        auto t_start = std::chrono::high_resolution_clock::now();
        char c;
        std::ifstream inStream(inFile, std::ios::in);    
        std::ofstream outStream(outFile, std::ios::out);
        while (inStream.get(c)) {
            switch (c) {
                case ' ':
                    if (inStream.peek() != ' ' && inStream.peek() != '\n') {
                        wordCount++;
                    }
                    
                    outStream << '/';
                    if (existWordError) {
                        wordErrorCount++;
                        existWordError = false;
                    }
                    break;
                case '\n':
                    if (inStream.peek() != ' ' && inStream.peek() != '\n') {
                        wordCount++;
                    }
                    lineCount++;
                    outStream << '\n';
                    if (existWordError) {
                        wordErrorCount++;
                        existWordError = false;
                    }
                    break;
                default:
                    // Unrecognizable character
                    charCount++;
                    if (!asciiToMorse.count(tolower(c))) {
                        charErrorCount++;
                        existWordError = true;
                        outStream << '#';
                        outStream << ' ';
                        textError error{lineCount,c};
                        // Save errors
                        textErrorList.push_back(error);
                        continue;
                    }
                    outStream << asciiToMorse[tolower(c)];

                    if (inStream.peek() == EOF) {
                         wordCount++;
                    }
                    
                    break;
            }
            outStream << ' ';
        }
        inStream.close();
        outStream.close();
        auto t_end = std::chrono::high_resolution_clock::now();
        conversionDuration = std::chrono::duration<double, std::milli> (t_end-t_start).count();
        }

    /* Convert the given file from plain text to morse code
    or vice versa. */
    void convert(std::string inFile, std::string outFile) {
        if (getFileType(inFile) == MORSE_CODE) {
            convertMorse(inFile, outFile);
            return;
        }
        convertText(inFile, outFile);
    }

    void help() {
        std::cout << helpMessage;
        std::ofstream helpFile("help.txt");
        helpFile << helpMessage;
        helpFile.close();
    };

    void logFile(std::string inFile, std::string outFile) {
        std::string inFileName = removeExtention(inFile);
        std::string outFileName = removeExtention(outFile);
        std::string logFileName = inFileName + "_" + outFileName + "_" + getLogTime() + ".log";
        std::ofstream outStream(logFileName, std::ios::out);
        outStream << "Input file: " << inFile << std::endl
                  << "Output file: " << outFile << std::endl
                  << "Duration [secound]: " << conversionDuration << std::endl
                  << "Time complete: " << getCurrentTime()
                  << "Word count in input file: " << wordCount << std::endl
                  << "Word converted: " << wordCount - wordErrorCount << std::endl
                  << "Word with errors: " << wordErrorCount << std::endl
                  << "Total number of characters: " << charCount << std::endl
                  << "Number of characters have been conveted: " << (charCount - charErrorCount) << std::endl
                  << "Number of characters have NOT been converted: " << charErrorCount << std::endl;
        std::ifstream file(logFileName);
        std::cout << file.rdbuf();
    }

    void logConsoleInvalid(int errorCode) {
        for(int i = 0; i < morseErrorList.size(); i++) {
            std::cout << getErrorCode(errorCode)
                      << ": Invalid Morse code '" << morseErrorList[i].error
                      << "' on line " << morseErrorList[i].lineNum << std::endl;
        }
    }

    void logConsoleUnrecognized(int errorCode) {
        for(int i = 0; i < textErrorList.size(); i++) {
            std::cout << getErrorCode(errorCode)
                      << ": Unrecognize character '" << textErrorList[i].error
                      << "' on line " << textErrorList[i].lineNum << std::endl;
        }
    }
}    

/* Check for error and convert morse code */
void handleMorse(std::string morseCode,std::ofstream& outStream) {
    morseError error {lineCount, morseCode};
    if (morseCode != "") {
        charCount++;
        if (!isValidMorse(morseCode)) {
            charErrorCount++;
            outStream << '*';
            existWordError = true;
            // Save errors
            morseErrorList.push_back(error);
            }
        else if (!morseToAscii.count(morseCode)) {
            charErrorCount++;
            outStream << '#';
            existWordError = true;
            // Save errors
            morseErrorList.push_back(error);
            }
        else {
            outStream << morseToAscii[morseCode];
        }
    }
}

// Functions that process strings used for logging information
std::string removeExtention(std::string fileName) {
    size_t lastdot = fileName.find_last_of(".");
    if (lastdot == std::string::npos)
        return fileName;
    return fileName.substr(0, lastdot);
}

std::string getCurrentTime() {
    time_t timetoday;
    time (&timetoday);
    return asctime(localtime(&timetoday));
}

std::string getLogTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream outStream;
    outStream << std::put_time(&tm, "%d%m%Y_%H%m%S");
    auto logTime = outStream.str();
    return logTime;
}