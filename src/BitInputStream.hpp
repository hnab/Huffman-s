#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
    istream & in;
    char buff;
    int nbits;

public:
    BitInputStream(istream & i);
    bool readBit();
   // int getBits() const;
};

#endif // BITINPUTSTREAM_HPP
