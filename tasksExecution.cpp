#include "morse.h"

/* A map from ASCII characters to Morse code */
extern std::map<char, std::string> asciiToMorse; 

/* A map from Morse code to ASCII character */
extern std::map<std::string, char> morseToAscii;

//Convert Error link list
ConverErrorlist Errorlist;

//Convert variable
int CharCount = 0;
int WordCount = 0;
int LineCount = 1;
int CharErrorCount = 0;
int WordErrorCount = 0;
bool exitWordError = false;


// Functions that perform the program main tasks
namespace tasks {

    /* Convert morse code file to plain text file */
    void convertMorse(std::string inFile, std::string outFile) {
        
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
                    CharCount++;
                    switch (c) {
                        case '/':
                            WordCount++;
                            outStream << ' ';
                            //reset word error when come to new word
                            exitWordError = false;  
                            break;
                        case '\n': 
                            WordCount++;
                            LineCount++;
                            outStream << '\n';
                            //reset word error when come to new word
                            exitWordError = false;
                            break;
                    }
                    if (morseCode == "")
                        continue;    
                    // Invalid morse code
                    if (morseCode.length() > 7) {
                        CharErrorCount++;
                        outStream << '#';
                        // Save errors
                        Errorlist.AppendMorseList(LineCount,morseCode);
                        morseCode = "";
                        // Change flag word error exist and count error word
                        if (!exitWordError){
                            WordErrorCount++;
                            exitWordError = true;
                        }
                        continue;
                    }
                    // Unrecognizable morse code
                    if (!morseToAscii.count(morseCode)) {
                        CharErrorCount++;
                        outStream << '*';
                        // Save errors
                        Errorlist.AppendMorseList(LineCount,morseCode);
                        morseCode = "";
                        // Change flag word error exist and count error word
                        if (!exitWordError){
                            WordErrorCount++;
                            exitWordError = true;
                        }
                        continue;
                    }

                    outStream << morseToAscii[morseCode];
                    morseCode = ""; 

                break;
                default:
                    CharCount++;
                    CharErrorCount++;
                    outStream << '#';
                    // Save errors
                    Errorlist.AppendMorseList(LineCount,morseCode);
                    // Change flag word error not exist and count error word
                    if (!exitWordError){
                        WordErrorCount++;
                        exitWordError = true;
                        }
                    break;
            }
        }
        inStream.close();
        outStream.close();
    }
    /* Convert plain text file to morse code file */
    void convertText(std::string inFile, std::string outFile) {
        
        char c;
        std::ifstream inStream;    
        std::ofstream outStream;
        inStream.open(inFile, std::ios::in);
        outStream.open(outFile,std::ios::out);
        while (inStream.get(c)) {
            CharCount++;
            switch (c) {
                case ' ':
                    WordCount++;
                    outStream << '/';
                    exitWordError = false;
                    break;
                case '\n':
                    WordCount++;
                    LineCount++;
                    outStream << '\n';
                    exitWordError = false;
                    break;
                default:
                    // Unrecognizable character
                    if (!asciiToMorse.count(tolower(c))) {
                        CharErrorCount++;
                        outStream << '#';
                        // Save errors
                        Errorlist.AppendTextList(LineCount,c);
                        // Change flag word error exist and count error word
                        if (!exitWordError){
                            WordErrorCount++;
                            exitWordError = true;
                        }
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

    void log(std::string inFile, std::string outFile) {
        //Caculate and execute convert funciton
        auto t_start = std::chrono::high_resolution_clock::now();
        convert(inFile,outFile);
        auto t_end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();
        //start printing
        std::cout << "Input file: " << inFile << std::endl;
        std::cout << "Output file: " << outFile << std::endl;
        std::cout << "Duration[secound]: " << duration << std::endl;
        std::cout << "Time complete: " << CurrentTime() << std::endl;
        std::cout << "Word count in input file: " << WordCount << std::endl;
        std::cout << "Word converted: " << WordCount - WordErrorCount << std::endl;
        std::cout << "Word with errors: " << WordErrorCount << std::endl;
        std::cout << "Total number of characters: " << CharCount << std::endl;
        std::cout << "Number of characters have been conveted: " << CharCount - CharErrorCount << std::endl;
        std::cout << "Number of characters are NOT converted: " << CharErrorCount << std::endl;
        Errorlist.PrintList(INVALID_CODES);
    }
}    