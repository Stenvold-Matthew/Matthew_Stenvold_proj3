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
        Hexadecimal r0("0x0");
        Hexadecimal r1("0x0");
        Hexadecimal r2("0x0");
        Hexadecimal r3("0x0");
        Hexadecimal r4("0x0");
        Hexadecimal r5("0x0");
        Hexadecimal r6("0x0");
        Hexadecimal r7("0x0");
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
            //Splits each line into the operator and two hexadecimals
            std::cout << tp << std::endl;
            std::stringstream splitString(tp);
            splitString >> operand;
            splitString >> value1;
            splitString >> value2;
            splitString >> value3;
            value1.erase(remove(value1.begin(), value1.end(), ','), value1.end());
            value2.erase(remove(value2.begin(), value2.end(), '#'), value2.end());
            value2.erase(remove(value2.begin(), value2.end(), ','), value2.end());
            value3.erase(remove(value3.begin(), value3.end(), '#'), value3.end());
            uppercase(operand);
            uppercase(value1);
            uppercase(value2);
            uppercase(value3);
            

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
            int count = 0;
            for (std::map<std::string,Hexadecimal>::iterator it=registers.begin(); it!=registers.end(); ++it) {
                std::cout << it->first << ": " << it->second << "  ";
                count++;
                if (count == 4) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl<< std::endl;
        }
        
        // Close the file and end the program
        inFile.close();
    }
    return 0;
}

// Converts a string to lowercase
void uppercase(std::string &input) {
    for (int i = 0; i < input.length(); i++) {
    input[i] = toupper(input[i]);
  }
}