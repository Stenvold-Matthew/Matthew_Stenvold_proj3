#include "hexadecimal.h"

// Constructor that is called by inputing a string formatted as "0x____". Works for any length
Hexadecimal::Hexadecimal(u_int32_t input) {
    data = input;
}

Hexadecimal::Hexadecimal(std::string input) {
    data = 0;
    int multVal = 1;
    u_int32_t temp;
    
    for(int i = input.length()-2; i > 0; i--) {
        temp = multVal * convToDec(input.at(i+1));
        data += temp;
        multVal *= 16;
    }
}

// Returns the hexidecimal as a string
std::string Hexadecimal::convToString() {
    std::string str;
    u_int32_t dataCopy = data;
    for(int i = 0; i < 8; i++) {
        u_int32_t temp = dataCopy % 16;
        str.insert(0, 1, convToHex(temp));
        dataCopy /= 16;
    }
    return str;
}

u_int32_t Hexadecimal::convToHexFull() {
    return 0;
}

// Returns the char of the hexidecimal at the val position (0 being first)
u_int32_t Hexadecimal::getData() {
    return data;
}

// Converts a hex value to what it would be in decimal (ie. B = 11)
int Hexadecimal::convToDec(char input) {
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

// Converts a dec value to what it would be in hex (ie. 12 = C)
char Hexadecimal::convToHex(int input) {
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

void Hexadecimal::operator=(Hexadecimal& inputHex2) {
    data = inputHex2.getData();
}

// Adds two hexadecimal together and returns the resulting hexadecimal
Hexadecimal Hexadecimal::operator+(Hexadecimal& inputHex2) {
    u_int32_t temp = data + inputHex2.getData();
    Hexadecimal hex(temp);
    return hex;
}


// Subtracts the first Hexadecimal by the second
Hexadecimal Hexadecimal::operator-(Hexadecimal& inputHex2) {
    u_int32_t temp = data - inputHex2.getData();
    Hexadecimal hex(temp);
    return hex;
}

// Returns the hexadecimal of the AND function on 2 input hexes
Hexadecimal Hexadecimal::operator&(Hexadecimal& inputHex2) {
    u_int32_t temp = data & inputHex2.getData();
    Hexadecimal hex(temp);
    return hex;
}

// Returns the hexadecimal of the XOR function on 2 input hexes
Hexadecimal Hexadecimal::operator^(Hexadecimal& inputHex2) {
    u_int32_t temp = data ^ inputHex2.getData();
    Hexadecimal hex(temp);
    return hex;
}

// Returns the hexadecimal of the OR function on 2 input hexes
Hexadecimal Hexadecimal::operator|(Hexadecimal& inputHex2) {
    u_int32_t temp = data | inputHex2.getData();
    Hexadecimal hex(temp);
    return hex;
}

/*

// Rotates right while maintaining the most significant bit
Hexadecimal Hexadecimal::ASR(int numShifts) {
    std::vector<bool> binary = convToBinary();
    bool temp;
    int tempInt;
    std::string str;

    // Stores the most significant bit, and then rotates the binary vector right while filling in the empty spaces with that value
    temp = binary[0];
    for(int i = 0; i<numShifts; i++) {
        binary.insert(binary.begin() + 1, temp);
        binary.pop_back();
    }
    // Converts the new binary string to hex and appends it to the string
    for(int i = 0; i < length; i++) {
        tempInt = 0;
        tempInt += binary[4*i] * 8;
        tempInt += binary[4*i + 1] * 4;
        tempInt += binary[4*i + 2] * 2;
        tempInt += binary[4*i + 3];
        str += std::string{convToHex(tempInt)};
    }
    // Creates and returns the new string
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

// Rotates right while filling in the empty spaces with 0
Hexadecimal Hexadecimal::LSR(int numShifts) {
    std::vector<bool> binary = convToBinary();
    int tempInt;
    std::string str;

    for(int i = 0; i<numShifts; i++) {
        binary.insert(binary.begin() + 0, 0);
        binary.pop_back();
    }
    // Converts the new binary string to hex and appends it to the string
    for(int i = 0; i < length; i++) {
        tempInt = 0;
        tempInt += binary[4*i] * 8;
        tempInt += binary[4*i + 1] * 4;
        tempInt += binary[4*i + 2] * 2;
        tempInt += binary[4*i + 3];
        str += std::string{convToHex(tempInt)};
    }
    // Creates and returns the new string
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

// Rotates left while filling in the empty spaces with 0
Hexadecimal Hexadecimal::LSL(int numShifts) {
    std::vector<bool> binary = convToBinary();
    int tempInt;
    std::string str;

    for(int i = 0; i<numShifts; i++) {
        binary.push_back(0);
        binary.erase(binary.begin() + 0);;
    }
    // Converts the new binary string to hex and appends it to the string
    for(int i = 0; i < length; i++) {
        tempInt = 0;
        tempInt += binary[4*i] * 8;
        tempInt += binary[4*i + 1] * 4;
        tempInt += binary[4*i + 2] * 2;
        tempInt += binary[4*i + 3];
        str += std::string{convToHex(tempInt)};
    }
    // Creates and returns the new string
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

*/

std::ostream& operator<<(std::ostream& os, Hexadecimal& hex) {
    os << "0x" << hex.convToString();
    return os;
}