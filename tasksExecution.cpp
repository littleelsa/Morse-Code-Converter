#include "morse.h"

//ascii to morse map
std::map< char, std::string > ascii_to_morse =
{
{'A',".-"},
{'B',"-..."},
{'C',"-.-."},
{'D',"-.."},
{'E',"."},
{'F',"..-."},
{'G',"--."},
{'H',"...."},
{'I',".."},
{'J',".---"},
{'K',"-.-"},
{'L',".-.."},
{'M',"--"},
{'N',"-."},
{'O',"---"},
{'P',".--."},
{'Q',"--.-"},
{'R',".-."},
{'S',"..."},
{'T',"-"},
{'U',"..-"},
{'V',"...-"},
{'W',".--"},
{'X',"-..-"},
{'Y',"-.--"},
{'Z',"--.."},
{'0',"-----"},
{'1',".----"},
{'2',"..---"},
{'3',"...--"},
{'4',"....-"},
{'5',"....."},
{'6',"-...."},
{'7',"--..."},
{'8',"---.."},
{'9',"----."},
{'.',".-.-.-"},
{',',"--..--"},
{'?',"..--.."},
{'=',"-...-"},
{'.',".-.-.-"},
};




// Functions that perform the program main tasks
namespace tasks {
    
    void convert(char *inFile, char *outFile) 
        if (File_type == "morse"){
            convertMorse(in_File,outFile);
        }
        else {
            convertText(in_File,outFile);
        }
        
    }

    void convertMorse(char *inFile, char *outFile) {
        //change char* to string
        std::string in_File;
        in_File = inFile;
        std::string out_File;
        out_File = outFile;
        //buil reverse map
        std::map< std::string, char > morse_to_ascii;
        for (auto kv : ascii_to_morse){
            morse_to_ascii[kv.second] = kv.first;
        }
        //initialize variable
        int line_count = 1;
        int error_count = 0;
        int char_count = 0;
        int word_count = 0;
        char ascii;
        char c;
        std::string  morse_code = "";
        //start open file
        std::ifstream input_stream;    
        std::ofstream output_stream;
        input_stream.open(in_File, std::ios::in);
        output_stream.open(out_File,std::ios::out);
        //read inputfile char by char
        while(input_stream.get(c)){
            //morse code from a char
            if (c == '.' || c == '-') {
                morse_code += c;
            } 
            //when it not morse code(end of word line or char) or error
            else {
                //end of word line or char
                if (c == '/' || c == ' ' || c == '\n' ){
                    //wrong format
                    if (invalid_morse_format(morse_code)){
                        output_stream << "*";
                        char_count += 1;
                        morse_code = "";
                        error_count += 1;
                        AppendError_para(morse_code,line_count)
                    }
                    //right format
                    else{
                        //unrecogize morse
                        if (morse_to_ascii.find(morse_code) == morse_to_ascii.end() && morse_code != ""){
                            char_count += 1;
                            output_stream << "#";
                            morse_code = "";
                            error_count += 1;
                            AppendError_para(morse_code,line_count);
                        }
                        //in map of convert
                        else{
                            if (morse_code != ""){
                                output_stream << morse_to_ascii[morse_code];
                                morse_code = "";
                                char_count += 1;
                            }
                            if (c == ' '){
                                
                            }
                            else if (c == '/'){
                                output_stream << " ";
                                word_count += 1;
                            }
                            // c = "\n"
                            else {
                                output_stream << "\n";
                                word_count += 1;
                                line_count += 1;
                            }
            
                        }
                    }
                }
                //wrong format
                else {
                    output_stream << "*";
                    char_count += 1;
                    error_count += 1;
                }
            }
        }
        //end of file morse code
        if (morse_to_ascii.find(morse_code) == morse_to_ascii.end() && morse_code != ""){
            char_count += 1;
            output_stream << "#";
            morse_code = "";
            error_count += 1;
            AppendError_para(morse_code,line_count)
        } 
        else{
            if (morse_code != ""){
                output_stream << morse_to_ascii[morse_code];
                morse_code = "";
                char_count += 1;
                word_count += 1;
            }
        }

        input_stream.close();
        output_stream.close();
        
    }

    void convertText(char *inFile, char *outFile) {
        //change char* to string
        std::string in_File;
        in_File = inFile;
        std::string out_File;
        out_File = outFile;
        //initialize variables
        int line_count = 1;
        int error_count = 0;
        int char_count = 0;
        int word_count = 0;
        char c;
        std::string  morse_code = "";
        //start open file
        std::ifstream input_stream;    
        std::ofstream output_stream;
        input_stream.open(in_File, std::ios::in);
        output_stream.open(out_File,std::ios::out);
        while (input_stream.get(c)){
            if (c != ' ' && c != '\n'){
                //error invalid char
                if (ascii_to_morse.find(c) == ascii_to_morse.end()){
                    error_count += 1;
                    output_stream << "#" ;
                    char_count += 1;
                    AppendError_para(morse_code,line_count)
                }
                else {
                    output_stream << ascii_to_morse[c];
                    char_count += 1;
                }
            }
            else {
                if ( c == ' '){
                    output_stream << "/";
                    word_count += 1;
                }
                else {
                    output_stream << "\n";
                    word_count += 1;
                    line_count += 1;
                }
            }
            output_stream << " ";
        }
    }

    void help() {
        std::cout << "'help' function is successfully called." << std::endl;
    }

    void log() {
        std::cout << "'log' function is successfully called." << std::endl;
    }
}    