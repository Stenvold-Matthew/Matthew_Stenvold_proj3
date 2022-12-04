#ifndef HEXADECIMAL_H
#define HEXADECIMAL_H

#include <vector>
#include <string>
#include <iostream>

class Hexadecimal {
private:
    uint32_t data;

public:
    Hexadecimal(u_int32_t input);
    Hexadecimal(std::string input);

    std::string convToString();
    u_int32_t convToHexFull();

    int convToDec(char input);
    char convToHex(int input);

    u_int32_t getData();
    void operator=(Hexadecimal& inputHex2);

    Hexadecimal operator+(Hexadecimal& inputHex2);
    Hexadecimal operator-(Hexadecimal& inputHex2);
    Hexadecimal operator&(Hexadecimal& inputHex2);
    Hexadecimal operator^(Hexadecimal& inputHex2);
    Hexadecimal operator|(Hexadecimal& inputHex2);
    Hexadecimal operator!();
    
    Hexadecimal ASR(int numShifts);
    Hexadecimal LSR(int numShifts);
    Hexadecimal LSL(int numShifts);
    friend std::ostream& operator<<(std::ostream& os, Hexadecimal& hex);

    ~Hexadecimal() {};
};

#include "hexadecimal.cpp"

#endif //HEXADECIMAL_H