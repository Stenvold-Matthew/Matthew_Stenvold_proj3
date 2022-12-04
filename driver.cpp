#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#include "hexadecimal.h"

#define INPUT_FILE "Programming-Project-3.txt"

void uppercase(std::string &input);

int main() {
    // Opens the input file as defined above
    std::fstream inFile;
    inFile.open(INPUT_FILE ,std::ios::in);
    if(!inFile.is_open()) {
        // Display an error message if the file failed to open
        std::cout << "There was an error opening your file" << std::endl;
        return 0;
    }
    else {
        
        std::string tp, operand, value1, value2, value3;
        // Initializes each register with an empty (0x0000_0000) hexidecimal value
        Hexadecimal r0("0x0");
        Hexadecimal r1("0x0");
        Hexadecimal r2("0x0");
        Hexadecimal r3("0x0");
        Hexadecimal r4("0x0");
        Hexadecimal r5("0x0");
        Hexadecimal r6("0x0");
        Hexadecimal r7("0x0");

        // Creates a map consisting of string and hexidecimals. This allows us to do registers.at(string) to access each register
        std::map<std::string, Hexadecimal> registers;
        registers.insert(std::make_pair("R0", r0));
        registers.insert(std::make_pair("R1", r1));
        registers.insert(std::make_pair("R2", r2));
        registers.insert(std::make_pair("R3", r3));
        registers.insert(std::make_pair("R4", r4));
        registers.insert(std::make_pair("R5", r5));
        registers.insert(std::make_pair("R6", r6));
        registers.insert(std::make_pair("R7", r7));

        // Reiterates over the file to get each line
        while(getline(inFile, tp)) {
            // Makes everything uppercase and splits each line into the operand/inputs
            std::cout << tp << std::endl;
            uppercase(tp);
            std::stringstream splitString(tp);
            splitString >> operand;
            splitString >> value1;
            splitString >> value2;
            splitString >> value3;
            // Removes the commas and #s from the inputs so they can easily be input into functions
            value1.erase(remove(value1.begin(), value1.end(), ','), value1.end());
            value2.erase(remove(value2.begin(), value2.end(), '#'), value2.end());
            value2.erase(remove(value2.begin(), value2.end(), ','), value2.end());
            value3.erase(remove(value3.begin(), value3.end(), '#'), value3.end());
            
            // Checks what the operand is and does the nessesary operation
            if(operand == "MOV") {
                Hexadecimal temp(value2);
                registers.at(value1) = temp;
            }

            else if(operand == "ADD") {
                Hexadecimal temp = registers.at(value2) + registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "SUB") {
                Hexadecimal temp = registers.at(value2) - registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "AND") {
                Hexadecimal temp = registers.at(value2) & registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "XOR") {
                Hexadecimal temp = registers.at(value2) ^ registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "ORR") {
                Hexadecimal temp = registers.at(value2) | registers.at(value3);
                registers.at(value1) = temp;
            }
            /*
            else if(operand == "ASR") {
                Hexadecimal temp = registers.at(value2).ASR(stoi(value3));
                registers.at(value1) = temp;
            }

            else if(operand == "LSR") {
                Hexadecimal temp = registers.at(value2).LSR(stoi(value3));
                registers.at(value1) = temp;
            }

            else if(operand == "LSL") {
                Hexadecimal temp = registers.at(value2).LSL(stoi(value3));
                registers.at(value1) = temp;
            }
            */
            else {
                std::cout << "This opperand is not recognized" << std::endl;
            }
            
            // Prints the name of each register followed by it's value
            int count = 0;
            for (std::map<std::string,Hexadecimal>::iterator it = registers.begin(); it != registers.end(); it++) {
                std::cout << it->first << ": " << it->second << "  ";
                // Adds a line break after printing 4 registers to make it more readable
                count++;
                if (count == 4) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl << std::endl;
        }
        
        
        // Close the file and end the program
        inFile.close();
    }
    return 0;
}

// Converts a string to uppercase
void uppercase(std::string &input) {
    for (int i = 0; i < input.length(); i++) {
        input[i] = toupper(input[i]);
    }
}