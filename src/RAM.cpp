#include "RAM.h"

namespace avrel
{
    RAM::RAM(int size_)
        : size(size_)
    {
        data.resize(size);
    }
    
    uint16_t RAM::readWord(int position)
    {
        return (readChar(position))|(readChar(position+1)<<8);
    }

    uint8_t RAM::readChar(int position)
    {
        if (position < size) {
            return data[position];
        } else {
            return 0x00;
        }
    }
}
