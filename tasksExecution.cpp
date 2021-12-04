#include "morse.h"

/* A map from ASCII characters to Morse code */
extern std::map<char, std::string> asciiToMorse; 

/* A map from Morse code to ASCII character */
extern std::map<std::string, char> morseToAscii;


struct morseError {
    int lineNum;
    std::string error;
};

std::vector <morseError> morseErrorList;


struct textError {
    int lineNum;
    char error;
};

std::vector <textError> textErrorList;


//Convert variable
int charCount = 0;
int wordCount = 0;
int lineCount = 1;
int charErrorCount = 0;
int wordErrorCount = 0;
bool existWordError = false;
double duration = 0;



/*funtion to check error and convert morse code*/
void handleMorse(std::string morseCode,std::ofstream& outStream){
    morseError error {lineCount,morseCode};
    if (morseCode != ""){
        charCount++;
        if (!isValidMorse(morseCode)) {
            charErrorCount++;
            outStream << '*';
            existWordError = true;
            /* Save errors*/
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
    
        while (inStream.get(c)) {
            if (c!=' ' && c!='/' && c!='\n'){
                    morseCode += c;
                    if (inStream.peek() == EOF ){
                        handleMorse(morseCode,outStream);
                        wordCount++;
                        if (existWordError){
                                wordErrorCount++;
                                existWordError = false;
                            }
                    }
            }
            
            else {
                    switch (c) {
                        case ' ':
                            handleMorse(morseCode,outStream);
                            if (inStream.peek() == EOF && morseCode != ""){
                                wordCount++;
                            }
                            break;
                        case '/':
                            handleMorse(morseCode,outStream);
                            if (morseCode != ""){
                                wordCount++;
                            }
                            outStream << ' ';
                            
                            if (existWordError){
                                wordErrorCount++;
                                existWordError = false;
                            }
                            break;
                        case '\n': 
                            handleMorse(morseCode,outStream);
                            if (morseCode != ""){
                                wordCount++;
                            }
                            lineCount++;
                            outStream << '\n';
                        
                            if (existWordError){
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
        duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    }




    /* Convert plain text file to morse code file */
    void convertText(std::string inFile, std::string outFile) {
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
                    if (existWordError){
                        wordErrorCount++;
                        existWordError = false;
                    }
                    break;
                case '\n':
                    wordCount++;
                    lineCount++;
                    outStream << '\n';
                    if (existWordError){
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
                        /*define error (linenum, erorr code)*/
                        textError error{lineCount,c};
                        // Save errors
                        textErrorList.push_back(error);
                        continue;
                    }
                    outStream << asciiToMorse[tolower(c)];

                    if (inStream.peek() == EOF){
                         wordCount++;
                    }
                    
                    break;
            }
            outStream << ' ';
        }

        inStream.close();
        outStream.close();
        auto t_end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();
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
        
        std::string infileName = removeExtention(inFile);
        std::string outfileName = removeExtention(outFile);
        std::string fileName = infileName + "_" + outfileName + "_" + timeLogName() + ".log";
        /*write log file*/
        std::ofstream outStream;
        outStream.open(fileName,std::ios::out);
        outStream << "Input file: " << inFile << std::endl;
        outStream << "Output file: " << outFile << std::endl;
        outStream << "Duration[secound]: " << duration << std::endl;
        outStream << "Time complete: " << CurrentTime();
        outStream << "Word count in input file: " << wordCount << std::endl;
        outStream << "Word converted: " << wordCount - wordErrorCount << std::endl;
        outStream << "Word with errors: " << wordErrorCount << std::endl;
        outStream << "Total number of characters: " << charCount << std::endl;
        outStream << "Number of characters have been conveted: " << (charCount - charErrorCount) << std::endl;
        outStream << "Number of characters are NOT converted: " << charErrorCount << std::endl;
        outStream << std::endl;
        /*print log file*/
        std::ifstream f(fileName);
        std::cout << f.rdbuf();

    }



    void printmorseError(int errorCode){
        for(int i = 0; i < morseErrorList.size(); i++){
            std::cout << "Error " << errorCode
                      << ": Invalid MORSE code " << morseErrorList[i].error
                      << " on line " << morseErrorList[i].lineNum << std::endl;
        }
    }

    void printtextError(int errorCode){
        for(int i = 0; i < textErrorList.size(); i++){
            std::cout << "Error " << errorCode
                      << ": Unrecognize character " << textErrorList[i].error
                      << " on line " << textErrorList[i].lineNum << std::endl;
        }
    }

}    