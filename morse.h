#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cctype>
#include <cstring>
#include <chrono>
#define NUM_FILES 2
#define NUM_PROGRAM_COMMANDS 4
#define MAX_NUM_ARGS 4
enum ERROR_CODE {
    NO_ERROR,
    NO_ARGS_PROVIDED,
    FILE_NAMES_MISSING,
    UNRECOGNIZED_CMDS,
    INVALID_CMDS,
    CONFLICTED_CMDS,
    DUPLICATED_ARGS,
    TOO_MANY_ARGS,
    FILE_NOT_EXIST,
    OPEN_INPUT,
    OVERWRITE_OUTPUT,
    UNRECOGNIZED_CHARS,
    UNRECOGNIZED_CODES,
    INVALID_CODES
};
enum FILE_TYPE {
    PLAIN_TEXT,
    MORSE_CODE
};

// Functions that perform micellaneous tasks

int isRecognizableCommand(std::string command);

int isValidCommand(std::string command);

int doesArgvIncludeCommand(int argc, char *argv[], std::string programCommand);

int doesArgvIncludeCommand(int argc, char *argv[], std::string programCommand);

int countFileNames(int argc, char *argv[]);

int isMorseChar(char c);

int getFileType(std::string fileName);

std::vector<char *> getFileNames(int argc, char *argv[]);

std::vector<char *> getCommands(int argc, char *argv[]);

std::string CurrentTime();


// Functions that log error messages to the console
namespace errorsLogging {
    
    // User's input related errors
    void noArgumentsProvided(int errorCode);

    void fileNamesMissing(int errorCode, int numFileNames);

    void outputFileNameMissing(int errorCode);

    void unrecognizedCommands(int errorCode, std::string command);

    void invalidCommands(int errorCode, std::string command);

    void conflictedCommands(int errorCode);

    void duplicatedArguments(int errorCode, std::string command);

    void tooManyArguments(int errorCode);

    void fileNotExist(int errorCode, char fileName);

    void openInput(int errorCode, std::string inFile);

    void overwriteOutput(int errorCode, std::string outFile);

    void unrecognizedChars(int errorCode, int lineNum, char c);

    void unrecognizedCodes(int errorCode, int lineNum, std::string code);

    void invalidCodes(int errorCode, int lineNum, std::string code);

}

namespace errorsHandling {

    void noArgumentsProvided(int argc);

    void fileNamesMissing(int argc, char *argv[]);

    void unrecognizedCommands(int argc, char *argv[]);

    void invalidCommands(int argc, char *argv[]);

    void conflictedCommands(int argc, char *argv[]);

    void duplicatedArguments(int argc, char *argv[]);

    void tooManyArguments(int argc, char *argv[]);

    void openInput(std::string inFile);

    void overwriteOutput(std::string output_file_name);
}

namespace tasks {

    void convertMorse(std::string inFile, std::string outFile);

    void convertText(std::string inFile, std::string outFile);

    void convert(std::string inFile, std::string outFile);

    void help();

    void log(std::string inFile, std::string outFile);
}

struct Node {
    int lineNum;
    std::string errorCode;
    Node* next;
};



class ConverErrorlist {
  private:
    Node* head;
  public:
    ConverErrorlist(){
    head = NULL;
    }
 
    //Add new element at the end of the list
    //specifile for conver morse error 
    void AppendMorseList(int lineNum,std::string errorCode) {
      Node* newNode = new Node();
      newNode->lineNum = lineNum;
      newNode->errorCode = errorCode;
      newNode->next = NULL; 
      //if no head node, this node is head node
      if(head == NULL) {
        head = newNode;
      } else {
        Node* temp = head;
        //append to the last
        while(temp->next != NULL)
          temp = temp->next;
        //set next node to new node
        temp->next = newNode;
      }    
    }

    //Add new element at the end of the list
    //specifile for conver text error 
    void AppendTextList(int lineNum,char errorCode) {
      Node* newNode = new Node();
      newNode->lineNum = lineNum;
      newNode->errorCode = errorCode;
      newNode->next = NULL; 
      //if no head node, this node is head node
      if(head == NULL) {
        head = newNode;
      } else {
        Node* temp = head;
        //append to the last
        while(temp->next != NULL)
          temp = temp->next;
        //set next node to new node
        temp->next = newNode;
      }    
    }


    //display the content of the list
    void PrintList(int errorCode) {
      Node* temp = head;
      if(temp != NULL) { 
        while(temp != NULL) {
          std::cout << "Error " << errorCode
                    << ": Invalid Morse code " << temp->errorCode
                    << "on line " << temp->lineNum << std::endl;
          temp = temp->next;
        }
      }
    }

};