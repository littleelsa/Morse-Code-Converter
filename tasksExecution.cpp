#include "morse.h"

/* A map from ASCII characters to Morse code */
extern std::map<char, std::string> asciiToMorse; 

/* A map from Morse code to ASCII character */
extern std::map<std::string, char> morseToAscii;

//Convert Error link list
ConverErrorlist Errorlist;


// Functions that perform the program main tasks
namespace tasks {

    /* Convert morse code file to plain text file */
    void convertMorse(std::string inFile, std::string outFile) {
        int charCount = 0;
        int wordCount = 0;
        int lineCount = 1;
        int errorCount = 0;
        char c;
        std::string morseCode = "";
        std::ifstream inStream;    
        std::ofstream outStream;
        inStream.open(inFile, std::ios::in);
        outStream.open(outFile, std::ios::out);
        // Read the input file char by char
        while (inStream.get(c)) {
            switch (c) {
                case '.': case '-':
                    morseCode += c;
                    break; 
                case ' ': case '/': case '\n':
                    charCount++;
                    switch (c) {
                        case '/':
                            wordCount++;
                            outStream << ' ';  
                            break;
                        case '\n': 
                            wordCount++;
                            lineCount++;
                            outStream << '\n';
                            break;
                    }
                    if (morseCode == "")
                        continue;    
                    // Invalid morse code
                    if (morseCode.length() > 7) {
                        errorCount++;
                        outStream << '*';
                        // Save errors
                        errorsLogging::invalidCodes(INVALID_CODES, lineCount, morseCode);
                        Errorlist.AppendMorseList(lineCount,morseCode);
                        morseCode = "";
                        continue;
                    }
                    // Unrecognizable morse code
                    if (!morseToAscii.count(morseCode)) {
                        errorCount++;
                        outStream << '#';
                        // Save errors
                        errorsLogging::unrecognizedCodes(UNRECOGNIZED_CODES, lineCount, morseCode);
                        Errorlist.AppendMorseList(lineCount,morseCode);
                        morseCode = "";
                        continue;
                    }
                    outStream << morseToAscii[morseCode];
                    morseCode = ""; 
                break;
                default:
                    charCount++;
                    errorCount++;
                    outStream << '*';
                    // Save errors
                    errorsLogging::unrecognizedChars(UNRECOGNIZED_CHARS, lineCount, c);
                    Errorlist.AppendMorseList(lineCount,morseCode);
                    break;
            }
        }
        inStream.close();
        outStream.close();
    }
    /* Convert plain text file to morse code file */
    void convertText(std::string inFile, std::string outFile) {
        int charCount = 0;
        int wordCount = 0;
        int lineCount = 1;
        int errorCount = 0;
        char c;
        std::ifstream inStream;    
        std::ofstream outStream;
        inStream.open(inFile, std::ios::in);
        outStream.open(outFile,std::ios::out);
        while (inStream.get(c)) {
            charCount++;
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
                    if (!asciiToMorse.count(tolower(c))) {
                        errorCount++;
                        outStream << '#';
                        // Save errors
                        errorsLogging::unrecognizedChars(UNRECOGNIZED_CHARS, lineCount, c);
                        Errorlist.AppendTextList(lineCount,c);
                        continue;
                    }
                    outStream << asciiToMorse[tolower(c)];
                    break;
            }
            outStream << ' ';
        }
        inStream.close();
        outStream.close();
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

    void log() {
        std::cout << "'log' function is successfully called." << std::endl;
    }
}    