#include "hexadecimal.h"

// Constructor that is called by inputing a string formatted as "0x____". Works for any length
Hexadecimal::Hexadecimal() {
    data = 0;
}

Hexadecimal::Hexadecimal(std::string input) {
    data = 0;
    int multVal = 1;
    
    for(int i = input.length()-2; i > 0; i--) {
        data += multVal * convToDec(input.at(i+1));
        multVal *= 16;
    }
}

// Returns the hexidecimal as a string
std::string Hexadecimal::convToString() {
    std::string str;
    int test = 1;
    u_int32_t dataCopy = data;
    for(int i = 0; i < 8; i++) {
        int temp = dataCopy % 16;
        str.insert(0, std::to_string(temp));
        dataCopy /= 16;
    }
    return str;
}

u_int32_t Hexadecimal::convToHexFull() {
    return 0;
}

// Returns the char of the hexidecimal at the val position (0 being first)
char Hexadecimal::getData() {
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

/*
// Converts the data vector to binary and returns that vector
std::vector<bool> Hexadecimal::convToBinary() {
    std::vector<bool> output;
    int temp;
    for(int i = 0; i < length; i++) {
        temp = convToDec(data[i]);
        output.push_back(temp/8);
        output.push_back((temp/4) % 2);
        output.push_back((temp/2) % 2);
        output.push_back(temp % 2);
    }
    return output;
}

// Adds two hexadecimal together and returns the resulting hexadecimal
Hexadecimal Hexadecimal::operator+(Hexadecimal& inputHex2) {
    int maxLength, temp, carry = 0;
    int hex2Len = inputHex2.getLength();
    std::string str;

    // Checks to see if one of the hexadecimal values is longer than the others. If so, then it will add 
    // filler 0s to the beginning of whatever value is shorter until it is the same length.
    if (length > hex2Len) {
        maxLength = length;
        inputHex2.insertFiller(length-hex2Len);
    }
    else {
        maxLength = hex2Len;
        insertFiller(hex2Len-length);
    }

    // Reiterates over the length of the entire hexidecimal (they are both the same length because of the above operation) starting at the smallest value.
    for (int i = maxLength-1; i>=0; i--) {
        // Adds the two hexadecimal values after converting to dec. It accounts for the carry over from the previous calculation
        temp = convToDec(data[i]) + convToDec(inputHex2.getData(i)) + carry;
        carry = temp/16;
        temp = temp%16;

        // inserts the hexagonal value of the calculation into a string
        str.insert (0, 1, convToHex(temp));
    }

    // If the final calculation has a carry over, it will add 1 to the beginning of the string
    if (carry == 1) {
        str.insert (0, 1, '1');
    }

    // Creates and returns a hexidecimal object from the calculations
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

// Subtracts the first Hexadecimal by the second
Hexadecimal Hexadecimal::operator-(Hexadecimal& inputHex2) {
    int maxLength, temp, carry = 0;
    int hex2Len = inputHex2.getLength();
    std::string str;

    // Checks to see if one of the hexadecimal values is longer than the others. If so, then it will add 
    // filler 0s to the beginning of whatever value is shorter until it is the same length.
    if (length > hex2Len) {
        maxLength = length;
        inputHex2.insertFiller(length-hex2Len);
    }
    else {
        maxLength = hex2Len;
        insertFiller(hex2Len-length);
    }

    // Reiterates over the length of the entire hexidecimal (they are both the same length because of the above operation) starting at the smallest value.
    for (int i = maxLength-1; i>=0; i--) {
        // Subs the two hexadecimal values after converting to dec. It accounts for the carry over from the previous calculation
        temp = convToDec(data[i]) - convToDec(inputHex2.getData(i)) + carry;
        carry = (temp-15)/16;
        temp = (temp+16)%16;

        // inserts the hexagonal value of the calculation into a string
        str.insert (0, 1, convToHex(temp));
    }

    // If the final calculation has a carry over, it will add 1 to the beginning of the string
    if (carry == 1) {
        str.insert (0, 1, 'F');
    }

    // Creates and returns a hexidecimal object from the calculations
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

// Returns the hexadecimal of the AND function on 2 input hexes
Hexadecimal Hexadecimal::operator&(Hexadecimal& inputHex2) {
    int maxLength, temp;
    int hex2Len = inputHex2.getLength();
    std::string str;

    // Checks to see if one of the hexadecimal values is longer than the others. If so, then it will add 
    // filler 0s to the beginning of whatever value is shorter until it is the same length.
    if (length > hex2Len) {
        maxLength = length;
        inputHex2.insertFiller(length-hex2Len);
    }
    else {
        maxLength = hex2Len;
        insertFiller(hex2Len-length);
    }

    // Reiterates over the length of the entire hexidecimal (they are both the same length because of the above operation) starting at the smallest value.
    for (int i = maxLength-1; i>=0; i--) {
        // Using &, this will automatically return the AND of the 2 hexadecimal values at index i. 
        temp = convToDec(data[i]) & convToDec(inputHex2.getData(i));

        // inserts the hexagonal value of the calculation into a string
        str.insert (0, 1, convToHex(temp));
    }

    // Creates and returns a hexidecimal object from the calculations
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

// Returns the hexadecimal of the XOR function on 2 input hexes
Hexadecimal Hexadecimal::operator^(Hexadecimal& inputHex2) {
    int maxLength, temp;
    int hex2Len = inputHex2.getLength();
    std::string str;

    // Checks to see if one of the hexadecimal values is longer than the others. If so, then it will add 
    // filler 0s to the beginning of whatever value is shorter until it is the same length.
    if (length > hex2Len) {
        maxLength = length;
        inputHex2.insertFiller(length-hex2Len);
    }
    else {
        maxLength = hex2Len;
        insertFiller(hex2Len-length);
    }

    // Reiterates over the length of the entire hexidecimal (they are both the same length because of the above operation) starting at the smallest value.
    for (int i = maxLength-1; i>=0; i--) {
        // Using ^, this will automatically return the XOR of the 2 hexadecimal values at index i. 
        temp = convToDec(data[i]) ^ convToDec(inputHex2.getData(i));

        // inserts the hexagonal value of the calculation into a string
        str.insert (0, 1, convToHex(temp));
    }

    // Creates and returns a hexidecimal object from the calculations
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

// Returns the hexadecimal of the OR function on 2 input hexes
Hexadecimal Hexadecimal::operator|(Hexadecimal& inputHex2) {
    int maxLength, temp;
    int hex2Len = inputHex2.getLength();
    std::string str;

    // Checks to see if one of the hexadecimal values is longer than the others. If so, then it will add 
    // filler 0s to the beginning of whatever value is shorter until it is the same length.
    if (length > hex2Len) {
        maxLength = length;
        inputHex2.insertFiller(length-hex2Len);
    }
    else {
        maxLength = hex2Len;
        insertFiller(hex2Len-length);
    }

    // Reiterates over the length of the entire hexidecimal (they are both the same length because of the above operation) starting at the smallest value.
    for (int i = maxLength-1; i>=0; i--) {
        // Using |, this will automatically return the OR of the 2 hexadecimal values at index i. 
        temp = convToDec(data[i]) | convToDec(inputHex2.getData(i));

        // inserts the hexagonal value of the calculation into a string
        str.insert (0, 1, convToHex(temp));
    }

    // Creates and returns a hexidecimal object from the calculations
    str.insert(0, "0x");
    Hexadecimal hex(str);
    return hex;
}

void Hexadecimal::operator=(Hexadecimal& inputHex2) {
    for(int i = 0; i < 8; i++) {
        data[i] = inputHex2.getData(i);
        length = inputHex2.getLength();
    }
}

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