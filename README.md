# Morse Code Converter
A command line tool to convert morse code in a text file to plain text and vice versa 
## A. Compilation
Compile the program using the following command.

```
g++ main.cpp errorsLogging.cpp errorsHandling.cpp characterMaps.cpp utils.cpp -o morse
```
or using CMake, simply type
```
make
```
## B. Usage
The program reads input from one text file and writes output to another. User should create an input file in the same directory as the program prior to the conversion.
### 1. Simple conversion
```
./morse inFile.txt outFile.txt
```
Here, the type of the input file (morse code or plain text) is deduced from the file's content. Had the file contains morse code character exclusively, namely '.', '-', and whitespace, it'll be treated as morse code; had it not, then it'll be treated as plain text. <br>
The conversion is then performed accordingly.
```
./morse morseCode.txt plainText.txt
```
or otherwise,
```
./morse plainText.txt morseCode.txt
```
### 2. Conversion with commands
In addition the input and output file's name, user can provide a range of arguments as commands to specify which task the program is wished to perform.
|Command|Usage|
|-|-|
|-m|Force the program to read the input file as morse code|
|-t|Force the program to read the input file as plain text|
|-h|Write the instruction that aids user with using the command line arguments to the console and a help.txt file|
|-c|Write the information regarding the conversion process to a log file|


*e.g. The program read the input file as plain text and write the conversion's info to a log file*
```
./morse inFile.txt outFile.txt -t -c
```
To avoid complication, program limited the number of arguments provided as many as 4.
## C. Demonstration
### 1. Help message
[In]:
```
./morse -h
```
[Out]:
```
+----------------------------------------------------------------------------------------+
|                                 MORSE CODE CONVERTER                                   |
+----------------------------------------------------------------------------------------+
|'morse' is a command line tool for Morse code conversion.                               |
|                                                                                        |
|Usage: ./morse [input file] [output file] [options]                                     |
|                                                                                        |
|Positional arguments: [input file] [output file]                                        |
|*positional arguments should only be omitted had the user called the '-h' command only.*|
|                                                                                        |
|Optional arguments:                                                                    |
|  -m  | Force the program to read the input file as Morse code                          |
|  -t  | Force the program to read the input file as plain text                          |
|  -h  | Write the help message to the console and a help.txt file                       |
|  -c  | Write the conversion information to a log file                                  |
|*one shouldn't provide the program with more than 4 arguments.*                         |
|*the '-m' and '-t' commands shouldn't be used together.*                                 |
+----------------------------------------------------------------------------------------+
```
### 2. Auto conversion
[In]:
```
cat plainText_1.txt
```
[Out]:
```
 A quick   `brown`
fox; jumps over t`e
lazy dog.
```
[In]:
```
./morse plainText_1.txt morseCode_1.txt 
```
[Out]:
```
ERROR 10: Unrecognize character '`' on line 1
ERROR 10: Unrecognize character '`' on line 1
ERROR 10: Unrecognize character ';' on line 2
ERROR 10: Unrecognize character '`' on line 2
```
[In]:
```
cat morseCode_1.txt
```
[Out]:
```
/ .- / --.- ..- .. -.-. -.- / / / # -... .-. --- .-- -. # 
 ..-. --- -..- # / .--- ..- -- .--. ... / --- ...- . .-. / - # . 
 .-.. .- --.. -.-- / -.. --- --. .-.-.- 
```
### 2. Forced conversion
[In]:
```
./morse morseCode_1.txt plainText_2.txt -m
```
[Out]:
```
ERROR 11: Invalid Morse code '#' on line 1
ERROR 11: Invalid Morse code '#' on line 1
ERROR 11: Invalid Morse code '#' on line 2
ERROR 11: Invalid Morse code '#' on line 2
```
[In]:
```
cat plainText_2.txt
```
[Out]:
```
 a quick   *brown*
fox* jumps over t*e
lazy dog.
```
### 3. Logging
[In]:
```
./morse morseCode_1.txt plainText_2.txt -m -c
```
[Out]:
```
"CONVERSION INFORMATION"
Input file: morseCode_1.txt
Output file: plainText_2.txt
Duration [secound]: 0.858343
Time complete: Sun Dec  5 15:56:58 2021
Word count in input file: 9
Word converted: 6
Word with errors: 3
Total number of characters: 37
Number of characters have been conveted: 33
Number of characters have NOT been converted: 4

ERROR 11: Invalid Morse code '#' on line 1
ERROR 11: Invalid Morse code '#' on line 1
ERROR 11: Invalid Morse code '#' on line 2
ERROR 11: Invalid Morse code '#' on line 2
```
[In]:
```
cat morseCode_1_plainText_2_05122021_151258.log
```
[Out]:
```
"CONVERSION INFORMATION"
Input file: morseCode_1.txt
Output file: plainText_2.txt
Duration [secound]: 0.858343
Time complete: Sun Dec  5 15:56:58 2021
Word count in input file: 9
Word converted: 6
Word with errors: 3
Total number of characters: 37
Number of characters have been conveted: 33
Number of characters have NOT been converted: 4
```