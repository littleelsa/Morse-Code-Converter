#include "morse.h"

/* A map from ASCII characters to Morse code */
std::map<char, std::string> asciiToMorse = {
    {'a', ".-"},
    {'b', "-..."},
    {'c', "-.-."},
    {'d', "-.."},
    {'e', "."},
    {'f', "..-."},
    {'g', "--."},
    {'h', "...."},
    {'i', ".."},
    {'j', ".---"},
    {'k', "-.-"},
    {'l', ".-.."},
    {'m', "--"},
    {'n', "-."},
    {'o', "---"},
    {'p', ".--."},
    {'q', "--.-"},
    {'r', ".-."},
    {'s', "..."},
    {'t', "-"},
    {'u', "..-"},
    {'v', "...-"},
    {'w', ".--"},
    {'x', "-..-"},
    {'y', "-.--"},
    {'z', "--.."},
    {'1', ".----"},
    {'2', "..---"},
    {'3', "...--"},
    {'4', "....-"},
    {'5', "....."},
    {'6', "-...."},
    {'7', "--..."},
    {'8', "---.."},
    {'9', "----."},
    {'0', "-----"},
    {'.', ".-.-.-"},
    {',', "--..--"},
    {':', "---..."},
    {'?', "..--.."},
    {'\'', ".----."},
    {'-', "-....-"},
    {'/', "-..-."},
    {'(', "-.--."},
    {')', "-.--.-"},
    {'=', "-...-"},
    {'+', ".-.-."},
    {'@', ".--.-."},
};

/* A map from Morse code to ASCII character */
std::map<std::string, char> morseToAscii = {
    {".-", 'a'},
    {"-...", 'b'},
    {"-.-.", 'c'},
    {"-..", 'd'},
    {".", 'e'},
    {"..-.", 'f'},
    {"--.", 'g'},
    {"....", 'h'},
    {"..", 'i'},
    {".---", 'j'},
    {"-.-", 'k'},
    {".-..", 'l'},
    {"--", 'm'},
    {"-.", 'n'},
    {"---", 'o'},
    {".--.", 'p'},
    {"--.-", 'q'},
    {".-.", 'r'},
    {"...", 's'},
    {"-", 't'},
    {"..-", 'u'},
    {"...-", 'v'},
    {".--", 'w'},
    {"-..-", 'x'},
    {"-.--", 'y'},
    {"--..", 'z'},
    {".----", '1'},
    {"..---", '2'},
    {"...--", '3'},
    {"....-", '4'},
    {".....", '5'},
    {"-....", '6'},
    {"--...", '7'},
    {"---..", '8'},
    {"----.", '9'},
    {"-----", '0'},
    {".-.-.-", '.'},
    {"--..--", ','},
    {"---...", ':'},
    {"..--..", '?'},
    {".----.", '\''},
    {"-....-", '-'},
    {"-..-.", '/'},
    {"-.--.", '('},
    {"-.--.-", ')'},
    {"-...-", '='},
    {".-.-.", '+'},
    {".--.-.", '@'}
};

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
                    if (morseCode.length() > 7) {
                        errorCount++;
                        outStream << '*';
                        // Save errors
                        errorsLogging::invalidCodes(INVALID_CODES, lineCount, morseCode);
                    }
                    else if (!morseToAscii.count(morseCode)) {
                        errorCount++;
                        outStream << '#';
                        // Save errors
                        errorsLogging::unrecognizedCodes(UNRECOGNIZED_CODES, lineCount, morseCode);
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
                    if (!asciiToMorse.count(tolower(c))) {
                        errorCount++;
                        outStream << '#';
                        // Save errors
                        errorsLogging::unrecognizedChars(UNRECOGNIZED_CHARS, lineCount, c);
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