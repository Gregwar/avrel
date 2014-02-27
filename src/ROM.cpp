#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iterator>
#include "ROM.h"

using std::string;
using std::ifstream;

namespace EmulAVR
{
    ROM::ROM(string romFile)
        : position(0)
    {
        ifstream ifs(romFile.c_str(), ifstream::binary);
        data = string((std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>());
        ifs.close();
    }

    uint16_t ROM::readUWord()
    {
        return (readChar())|(readChar()<<8);
    }

    uint8_t ROM::readChar()
    {
        return data[position++];
    }
}
