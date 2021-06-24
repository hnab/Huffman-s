#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream {
private:
    ostream & out;
    char buff;
    int nbits;
    //int nthChar;// Hatef

public:
    BitOutputStream(ostream & o);
    void writeBit(bool bit);
    void flush();
   // int getBits() const; //Hatef
};

#endif // BITOUTPUTSTREAM_HPP
