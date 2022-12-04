#ifndef HEXADECIMAL_H
#define HEXADECIMAL_H

#include <vector>
#include <string>
#include <iostream>

class Hexadecimal {
private:
    int length;
    std::vector<char> data;

public:
    Hexadecimal();
    Hexadecimal(std::string input);

    std::string convToString();
    void insertFiller(int num);

    int getLength();
    char getData(int val);
    int convToDec(char input);
    char convToHex(int input);
    std::vector<bool> convToBinary();

    Hexadecimal operator+(Hexadecimal& inputHex2);
    Hexadecimal operator-(Hexadecimal& inputHex2);
    Hexadecimal operator&(Hexadecimal& inputHex2);
    Hexadecimal operator^(Hexadecimal& inputHex2);
    Hexadecimal operator|(Hexadecimal& inputHex2);
    Hexadecimal operator!();
    void operator=(Hexadecimal& inputHex2);

    Hexadecimal ASR(int numShifts);
    Hexadecimal LSR(int numShifts);
    Hexadecimal LSL(int numShifts);
    friend std::ostream& operator<<(std::ostream& os, Hexadecimal& hex);

    ~Hexadecimal();
};

#include "hexadecimal.cpp"

#endif //HEXADECIMAL_H