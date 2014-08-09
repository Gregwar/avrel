#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iterator>
#include "ROM.h"

using std::string;
using std::ifstream;

namespace avrel
{
    ROM::ROM(string romFile)
        : position(0)
    {
        ifstream ifs(romFile.c_str(), ifstream::binary);
        data = string((std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>());
        ifs.close();
        size = data.size();
    }

    void ROM::jumpTo(int position_)
    {
        position = position_;
    }
            
    void ROM::jumpRelative(int position_)
    {
        position += position_;
    }

    uint16_t ROM::readWord()
    {
        uint16_t L = readChar();
        uint16_t H = readChar();

        return (H<<8)|L;
    }

    int ROM::getSize()
    {
        return size;
    }

    uint8_t ROM::readChar()
    {
        if (position < size) {
            return data[position++];
        } else {
            return 0x00;
        }
    }

    int ROM::getPosition()
    {
        return position;
    }
}
