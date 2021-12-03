# Morse Code Converter
A command line tool to convert morse code in a text file to plain text and vice versa 
## Compilation
Compile the program using the following command.

```
$g++ main.cpp errorsLogging.cpp errorsHandling.cpp characterMaps.cpp utils.cpp -o morse
```
## Usage
The program reads input from one text file and writes output to another. User should create an input file in the same directory as the program prior to the conversion.
### Simple conversion
```
./morse <inputfile> <outputfile>
```
Here, the type of the input file (morse code or plain text) is deduced from the file's content. Had the file contains morse code character exclusively, namely '.', '-', and whitespace, it'll be treated as morse code; had it not, then it'll be treated as plain text. <br>
The conversion is then performed accordingly.
```
./morse <morsecode> <plaintext>
```
or otherwise,
```
./morse <plaintext> <morsecode>
```
### Conversion with commands
In addition the input and output file's name, user can provide a range of arguments as commands to specify which task the program is wished to perform.
|Command|Usage|
|-|-|
|-m|Force the program to read the input file as morse code|
|-t|Force the program to read the input file as plain text|
|-h|Write the instruction that aids user with using the command line arguments to the console and a helpme.txt file|
|-c|Write the information regarding the conversion process to a log file|


*e.g. The program read the input file as plain text and write the conversion's info to a log file*
```
./morse <inputfile> <outputfile> -t -c
```
To avoid complication, program limited the number of arguments provided as many as 4.
## Demonstration
