#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#define INPUT_FILE "Programming-Project-3.txt"

void uppercase(std::string &input);
int convToDec(char input);
char convToHex(int input);
u_int32_t convToData(std::string input);
std::string convToString(u_int32_t input);

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
        // Initializes each register with an empty (0) u_int32_t value
        u_int32_t r0 = 0;
        u_int32_t r1 = 0;
        u_int32_t r2 = 0;
        u_int32_t r3 = 0;
        u_int32_t r4 = 0;
        u_int32_t r5 = 0;
        u_int32_t r6 = 0;
        u_int32_t r7 = 0;

        // Creates a map consisting of string and u_int32_t. This allows us to do registers.at(string) to access each register
        std::map<std::string, u_int32_t> registers;
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
            std::cout << tp << std::endl;
            // Makes everything uppercase and splits each line into the operand/inputs
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
                registers.at(value1) = convToData(value2);
            }
        
            else if(operand == "ADD") {
                u_int32_t temp = registers.at(value2) + registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "SUB") {
                u_int32_t temp = registers.at(value2) - registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "AND") {
                u_int32_t temp = registers.at(value2) & registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "XOR") {
                u_int32_t temp = registers.at(value2) ^ registers.at(value3);
                registers.at(value1) = temp;
            }

            else if(operand == "ORR") {
                u_int32_t temp = registers.at(value2) | registers.at(value3);
                registers.at(value1) = temp;
            }
            
            else if(operand == "ASR") {
                int32_t temp = registers.at(value2);
                registers.at(value1) = temp>>stoi(value3);
            }
            
            else if(operand == "LSR") {
                u_int32_t temp = registers.at(value2);
                registers.at(value1) = temp>>stoi(value3);
            }

            else if(operand == "LSL") {
                u_int32_t temp = registers.at(value2);
                registers.at(value1) = temp<<stoi(value3);
            }
            
            else {
                std::cout << "This opperand is not recognized" << std::endl;
            }
            
            // Prints the name of each register followed by it's value
            int count = 0;
            for (std::map<std::string,u_int32_t>::iterator it = registers.begin(); it != registers.end(); it++) {
                std::cout << it->first << ": " << convToString(it->second) << "  ";
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

// Converts an input string to u_int32_t and returns it
u_int32_t convToData(std::string input) {
    u_int32_t data = 0;
    int multVal = 1;
    u_int32_t temp;
    
    // Starting at the back of the string, it will multiply the dec value of the char by the mult value and add it to a total
    // The mult value multiplies by 16 every iteriation
    for(int i = input.length()-2; i > 0; i--) {
        temp = multVal * convToDec(input.at(i+1));
        data += temp;
        multVal *= 16;
    }
    return data;
}

// Converts an input u_int32_t value and returns it as a hexidecimal formatted string
std::string convToString(u_int32_t input) {
    std::string str;
    for(int i = 0; i < 8; i++) {
        u_int32_t temp = input % 16;
        str.insert(0, 1, convToHex(temp));
        input /= 16;
    }
    return "0x" + str;
}

// Converts an input hexidecimal char to its dec equivalent
int convToDec(char input) {
    switch (input) {
        case 'A':
            return 10;

        case 'B':
            return 11;

        case 'C':
            return 12;

        case 'D':
            return 13;

        case 'E':
            return 14;
        
        case 'F':
            return 15;

        default:
            return input - '0';
    }
}

// Converts an input dec to its hexidecimal char equivalent
char convToHex(int input) {
    switch (input) {
        case 10:
            return 'A';

        case 11:
            return 'B';

        case 12:
            return 'C';

        case 13:
            return 'D';

        case 14:
            return 'E';

        case 15:
            return 'F';

        default:
            return input + '0';
    }
}