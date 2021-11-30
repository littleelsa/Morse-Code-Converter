#include "morse.h"

/* A map from ASCII characters to Morse code */
extern std::map<char, std::string> asciiToMorse; 

/* A map from Morse code to ASCII character */
extern std::map<std::string, char> morseToAscii;

struct convertError {
    int lineNum;
    std::string error;
};

std::vector <convertError> convertErrorList;



//Convert variable
int charCount = 0;
int wordCount = 0;
int lineCount = 1;
int charErrorCount = 0;
int wordErrorCount = 0;
bool exitWordError = false;
double Duration = 0;



/*funtion to check error and convert morse code*/
void handleMorse(std::string morseCode,std::ofstream& outStream){
    /*reinitialize convert error*/
    convertError error {lineCount,morseCode};
    /*handle each condition*/
    if (morseCode == "") {

        }
    // Invalid morse code
    else if (wrongMorseFormat(morseCode)) {
        charErrorCount++;
        charCount++;
        outStream << '*';
        exitWordError = true;
        // Save errors
        convertErrorList.push_back(error);
        }
        // Unrecognizable morse code
    else if (!morseToAscii.count(morseCode)) {
        charErrorCount++;
        charCount++;
        outStream << '#';
        exitWordError = true;
        // Save errors
       convertErrorList.push_back(error);
        }
    else {
        charCount++;
        outStream << morseToAscii[morseCode];
    }
}



// Functions that perform the program main tasks
namespace tasks {

    /* Convert morse code file to plain text file */
    void convertMorse(std::string inFile, std::string outFile) {
        auto t_start = std::chrono::high_resolution_clock::now();
        char c;
        std::string morseCode = "";
        std::ifstream inStream;    
        std::ofstream outStream;
        inStream.open(inFile, std::ios::in);
        outStream.open(outFile, std::ios::out);
        // Read the input file char by char
        while (inStream.get(c)) {
            /* keep add char to morse code until reaching the end like ' ', '\', '/n' */
            if (c!=' ' && c!='/' && c!='\n'){
                    morseCode += c;
                    /* if it is the end of file, start convert */
                    if (inStream.peek() == EOF){
                        handleMorse(morseCode,outStream);
                        wordCount++;
                        /* change flag variable of world error and count */
                        if (exitWordError){
                                wordErrorCount++;
                                exitWordError = false;
                            }
                    }
            }
            /* end of character, start convert */
            else {
                    switch (c) {
                        case ' ':
                            handleMorse(morseCode,outStream);
                            break;
                        case '/':
                            handleMorse(morseCode,outStream);
                            wordCount++;
                            outStream << ' ';
                            /* change flag variable of world error and count */
                            if (exitWordError){
                                wordErrorCount++;
                                exitWordError = false;
                            }
                            break;
                        case '\n': 
                            handleMorse(morseCode,outStream);
                            wordCount++;
                            lineCount++;
                            outStream << '\n';
                            /* change flag variable of world error and count */
                            if (exitWordError){
                                wordErrorCount++;
                                exitWordError = false;
                            }
                            break;
                    }
                    morseCode = ""; 
            }
        }
        inStream.close();
        outStream.close();
        auto t_end = std::chrono::high_resolution_clock::now();
        Duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    }
    /* Convert plain text file to morse code file */
    void convertText(std::string inFile, std::string outFile) {
        /*reinitialize text error*/
    
        /*initalize varaiable*/
        auto t_start = std::chrono::high_resolution_clock::now();
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
        auto t_end = std::chrono::high_resolution_clock::now();
        Duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();
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
        std::cout << "Time complete: " << CurrentTime();
        std::cout << "Word count in input file: " << wordCount << std::endl;
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