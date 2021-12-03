#include "morse.h"

/* A map from ASCII characters to Morse code */
extern std::map<char, std::string> asciiToMorse; 

/* A map from Morse code to ASCII character */
extern std::map<std::string, char> morseToAscii;

// Logging informations
int charCount = 0;
int wordCount = 0;
int lineCount = 1;
int charErrorCount = 0;
int wordErrorCount = 0;
bool areWordErrors = false;
double duration = 0;

typedef struct conversionError {
    int lineNum;
    std::string error;
} conversionError;

std::vector <conversionError> conversionErrorsList;

void convertMorseCode(std::string morseCode, std::ofstream &outStream) {
    conversionError error {lineCount, morseCode};
    if (!isValidMorse(morseCode)) {
        charErrorCount++;
        outStream << '*';
        areWordErrors = true;
        conversionErrorsList.push_back(error);
        errorsLogging::invalidCodes(morseCode);
    }
    else if (!morseToAscii.count(morseCode)) {
        charErrorCount++;
        outStream << '#';
        areWordErrors = true;
        conversionErrorsList.push_back(error);
    }
    else {
        outStream << morseToAscii[morseCode];
    }
}

std::string currentTime(){
    time_t time;
    return asctime(localtime(&time));
}

// Functions that perform the program main tasks
namespace tasks {

    /* Convert morse code file to plain text file */
    void convertMorse(std::string inFile, std::string outFile) {
        auto begin = std::chrono::high_resolution_clock::now();
        char c;
        std::string morseCode = "";
        std::ifstream inStream(inFile, std::ios::in);    
        std::ofstream outStream(outFile, std::ios::out);
        /*
        // Read the input file char by char
        while (inStream.get(c)) {
            // Keep adding char to morse code until reaching an end of word char 
            // (e.g. ' ', '\', '/n', EOF)
            if (!(c == ' ' || c == '/' || c == '\n' || c == EOF))
                morseCode += c;
                continue;
            // Reached the end of a morse code, convert morse code
            charCount++;
            convertMorseCode(morseCode, outStream);
            switch (c) {
                case '/':
                    wordCount++;
                    outStream << ' ';
                    if (areWordErrors) {
                        wordErrorCount++;
                        areWordErrors = false;
                    }
                    break;
                case '\n': 
                    wordCount++;
                    lineCount++;
                    outStream << '\n';
                    if (areWordErrors){
                        wordErrorCount++;
                        areWordErrors = false;
                    }
                    break;
                case EOF:
                    wordCount++;
                    if (areWordErrors) {
                        wordErrorCount++;
                        areWordErrors = false;
                    }
                morseCode = ""; 
            }
        }
        */

        inStream.close();
        outStream.close();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli> (end - begin).count();
    }
    /* Convert plain text file to morse code file */
    void convertText(std::string inFile, std::string outFile) {
        /*reinitialize text error*/
    
        /*initalize varaiable*/
        auto begin = std::chrono::high_resolution_clock::now();
        char c;
        std::ifstream inStream;    
        std::ofstream outStream;
        inStream.open(inFile, std::ios::in);
        outStream.open(outFile,std::ios::out);
        while (inStream.get(c)) {
            switch (c) {
                case ' ':
                    wordCount++;
                    outStream << '/';
                    break;
                case '\n':
                    wordCount++;
                    lineCount++;
                    outStream << '\n';
                    break;
                default:
                    // Unrecognizable character
                    charCount++;
                    if (!asciiToMorse.count(tolower(c))) {
                        charErrorCount++;
                        outStream << '#';
                        /*define error (linenum, erorr code)*/
                        std::string s;
                        s = c;
                        convertError error{lineCount,s};
                        // Save errors
                        convertErrorList.push_back(error);
                        continue;
                    }
                    outStream << asciiToMorse[tolower(c)];
                    break;
            }
            outStream << ' ';
        }
        inStream.close();
        outStream.close();
        auto end = std::chrono::high_resolution_clock::now();
        Duration = std::chrono::duration<double, std::milli>(end-begin).count();
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
        std::cout << "'help' function is successfully called." << std::endl;
    }

    void log(std::string inFile, std::string outFile) {
     
        //start printing
        std::cout << "Input file: " << inFile << std::endl;
        std::cout << "Output file: " << outFile << std::endl;
        std::cout << "Duration[secound]: " << Duration << std::endl;
        std::cout << "Time complete: " << currentTime();
        std::cout << "Word count in the input file: " << wordCount << std::endl;
        std::cout << "Word converted: " << wordCount - wordErrorCount << std::endl;
        std::cout << "Word with errors: " << wordErrorCount << std::endl;
        std::cout << "Total number of characters: " << charCount << std::endl;
        std::cout << "Number of characters have been conveted: " << (charCount - charErrorCount) << std::endl;
        std::cout << "Number of characters are NOT converted: " << charErrorCount << std::endl;
        std::cout << std::endl;
    }

    void printConvertError(int errorCode){
        for(int i = 0; i < convertErrorList.size(); i++){
            std::cout << "Error " << errorCode
                      << ": Invalid Morse code " << convertErrorList[i].error
                      << " on line " << convertErrorList[i].lineNum << std::endl;
        }
    }
}    